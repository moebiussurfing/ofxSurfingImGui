// Prototype of standalone node graph editor for ImGui
// Thread: https://github.com/ocornut/imgui/issues/306
//
// This is based on code by:
// @emoon https://gist.github.com/emoon/b8ff4b4ce4f1b43e79f2
// @ocornut https://gist.github.com/ocornut/7e9b3ec566a333d725d4
// @flix01 https://github.com/Flix01/imgui/blob/b248df2df98af13d4b7dbb70c92430afc47a038a/addons/imguinodegrapheditor/imguinodegrapheditor.cpp#L432

#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui_internal.h"

#include <memory>
#include <string>
#include <vector>
#include <algorithm>

namespace ImGui
{
	////////////////////////////////////////////////////////////////////////////////

    struct NodePadType
    {
        std::string name;
        std::string access;
        std::string format;
    };

    struct NodeType
    {
        std::string name;
        std::vector<NodePadType> pads;
    };

	template<int n>
	struct BezierWeights
	{
		constexpr BezierWeights() : x_(), y_(), z_(), w_()
		{
//            for (int i = 1; i <= n; ++i)
//            {
//                float t = (float)i / (float)(n + 1);
//                float u = 1.0f - t;
//
//                x_[i - 1] = u * u * u;
//                y_[i - 1] = 3 * u * u * t;
//                z_[i - 1] = 3 * u * t * t;
//                w_[i - 1] = t * t * t;
//            }
		}

		float x_[n];
		float y_[n];
		float z_[n];
		float w_[n];
	};

	static constexpr auto bezier_weights_ = BezierWeights<16>();


    //DEFINE NODE TYPES
	////////////////////////////////////////////////////////////////////////////////
    static const std::vector<ImGui::NodeType> node_types =
    {
        ////////////////////////////////////////////////////////////////////////////////
        {
            { std::string("MOCAPBridge") },

            {
                { std::string("Trigger"), std::string("sw"), std::string("f") },
                { std::string("Markers"), std::string("re"), std::string("f") },
                { std::string("Skeleton"), std::string("re"), std::string("f") }
            }
        },
        {
            { std::string("OSCSender") },

            {
                { std::string("Host Address"), std::string("sw"), std::string("s") },
                { std::string("data"), std::string("w"), std::string("f") },
            }
        },

        {
            { std::string("CHANNEL ") },

            {
                { std::string("IN"), std::string("ew"), std::string("f") },
                { std::string("OUT"), std::string("er"), std::string("f") },
            }
        },
        {
            { std::string("MIXER") },

            {
                { std::string("channel1"), std::string("ew"), std::string("f") },
                { std::string("channel2"), std::string("ew"), std::string("f") },
                { std::string("mixer"), std::string("ew"), std::string("f") },
            }
        }

    };


	////////////////////////////////////////////////////////////////////////////////

    class NodeEditor
	{
    protected:
		////////////////////////////////////////////////////////////////////////////////

        struct Node;

        struct NodePad
        {
            ImVec2 position;            // position in node canvas
            ImVec2 position_out;        // position ofoutput pad, in case pad is an output pad, as a convenience
            std::string name;           // human readable name
            //TODO: std::string widget_type   // type of widget for the gui
            std::string access;         // access string, ie r,w,e
            // || s, this also determines whether it is an output(r) or input(w) pad!
            std::string format;         // to determine data type
            Node* owner;                // owner of the pad
            //TODO: std::set<NodePad*> subscriptions; // list of subscriptions (only used  for output pads)

            uint32_t connections_;

            //constructor
            NodePad()
            {
                position = ImVec2(0.0f, 0.0f);
                name = std::string("noname");
                access = std::string("r");
                format = std::string("f");
                owner = nullptr;
                //widget_type = std::string("default");
                //subscriptions = std::set<NodePad*>();

                connections_ = 0;
            }

            NodePad* Get() {

                return this;
            }
        };

        struct NodePadLink
        {
            NodePad* source;
            NodePad* sink;
        };

		////////////////////////////////////////////////////////////////////////////////

		enum NodeStateFlag : int32_t
		{
			NodeStateFlag_Default = 1,
		};

        struct Node
        {
            int32_t id_; // 0 = empty, positive/negative = not selected/selected
            int32_t state_;

            ImVec2 position_;
            ImVec2 size_;

            float collapsed_height;
            float full_height;

            std::string name_;
            std::vector<std::unique_ptr<NodePad>> pads;

            Node()
            {
                id_ = 0;
                state_ = NodeStateFlag_Default;

                position_ = ImVec2(0.0f, 0.0f);
                size_ = ImVec2(0.0f, 0.0f);

                collapsed_height = 0.0f;
                full_height = 0.0f;
            }

            Node* Get()
            {
                return this;
            }
        };

		////////////////////////////////////////////////////////////////////////////////

        enum NodeState : uint32_t
		{
            NodeState_Default = 0,
            NodeState_Block, // helper: just block all states till next update (frame)
            NodeState_HoverIO,
            NodeState_HoverConnection,
            NodeState_HoverNode,
            NodeState_DraggingInput,
            NodeState_DraggingInputValid,
            NodeState_DraggingOutput,
            NodeState_DraggingOutputValid,
            NodeState_DraggingConnection,
            NodeState_DraggingSelected,
            NodeState_SelectingEmpty,
            NodeState_SelectingValid,
            NodeState_SelectingMore,
            NodeState_Selected,
            NodeState_SelectedConnection
		};

        struct currentNode
		{
            NodeState state_;

			ImVec2 position_;
			ImRect rect_;

			Node* node_;
            NodePad* selected_pad;
            NodePadLink* link;

            void Reset(NodeState state = NodeState_Default)
			{
				state_ = state;

				position_ = ImVec2(0.0f, 0.0f);
				rect_ = ImRect(0.0f, 0.0f, 0.0f, 0.0f);

				node_ = nullptr;
                selected_pad = nullptr;
                link = nullptr;
			}
		};

		////////////////////////////////////////////////////////////////////////////////

		std::vector<std::unique_ptr<Node>> nodes_;
        std::vector<NodePadLink*> node_links;

		int32_t id_;
        currentNode cur_node_;
		
		ImVec2 canvas_mouse_;
		ImVec2 canvas_position_;
		ImVec2 canvas_size_;
		ImVec2 canvas_scroll_;
		
		float canvas_scale_;

		////////////////////////////////////////////////////////////////////////////////

		float ImVec2Dot(const ImVec2& S1, const ImVec2& S2)
		{
			return (S1.x * S2.x + S1.y * S2.y);
		}

		float GetSquaredDistancePointSegment(const ImVec2& P, const ImVec2& S1, const ImVec2& S2)
		{
			const float l2 = (S1.x - S2.x) * (S1.x - S2.x) + (S1.y - S2.y) * (S1.y - S2.y);

			if (l2 < 1.0f)
			{
				return (P.x - S2.x) * (P.x - S2.x) + (P.y - S2.y) * (P.y - S2.y);
			}

			ImVec2 PS1(P.x - S1.x, P.y - S1.y);
			ImVec2 T(S2.x - S1.x, S2.y - S2.y);
			
			const float tf = ImVec2Dot(PS1, T) / l2;
			const float minTf = 1.0f < tf ? 1.0f : tf;
			const float t = 0.0f > minTf ? 0.0f : minTf;
			
			T.x = S1.x + T.x * t;
			T.y = S1.y + T.y * t;

			return (P.x - T.x) * (P.x - T.x) + (P.y - T.y) * (P.y - T.y);
		}

		float GetSquaredDistanceToBezierCurve(const ImVec2& point, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4)
		{
			float minSquaredDistance = FLT_MAX;
			float tmp;

			ImVec2 L = p1;
			ImVec2 temp;

			for (int i = 1; i < 16 - 1; ++i)
			{
				const ImVec4& W = ImVec4(bezier_weights_.x_[i], bezier_weights_.y_[i], bezier_weights_.z_[i], bezier_weights_.w_[i]);

				temp.x = W.x * p1.x + W.y * p2.x + W.z * p3.x + W.w * p4.x;
				temp.y = W.x * p1.y + W.y * p2.y + W.z * p3.y + W.w * p4.y;

				tmp = GetSquaredDistancePointSegment(point, L, temp);

				if (minSquaredDistance > tmp)
				{
					minSquaredDistance = tmp;
				}

				L = temp;
			}

			tmp = GetSquaredDistancePointSegment(point, L, p4);

			if (minSquaredDistance > tmp)
			{
				minSquaredDistance = tmp;
			}

			return minSquaredDistance;
		}

		////////////////////////////////////////////////////////////////////////////////

        bool IsPadHovered(ImVec2 connection, float radius)
		{

			ImVec2 delta = ImGui::GetIO().MousePos - connection;

			return ((delta.x * delta.x) + (delta.y * delta.y)) < (radius * radius);
		}

		Node* GetHoverNode(ImVec2 offset, ImVec2 pos);
		void DisplayNode(ImDrawList* drawList, ImVec2 offset, Node& node);
        void AddNodePadLink(NodePad* source, NodePad* sink);
        void DeleteNodePadLink(NodePadLink* link);
        void DeleteSelectedNodes();
		////////////////////////////////////////////////////////////////////////////////
		
		void UpdateScroll();
		void UpdateState(ImVec2 offset);
		void RenderLines(ImDrawList* draw_list, ImVec2 offset);
		void DisplayNodes(ImDrawList* drawList, ImVec2 offset);

        ////////////////////////////////////////////////////////////////////////////////

	public:
        explicit NodeEditor();
        ~NodeEditor();

		void ProcessNodes();
        NodeEditor::Node*  CreateNodeFromType(ImVec2 pos, const NodeType& type);
        virtual void LinkAdded(NodeEditor::NodePad*& src, NodePad*& sink) {};
        virtual void LinkDeleted(NodeEditor::NodePad*& src, NodePad*& sink) {};
        virtual void NodeAdded(NodeEditor::Node& node) {};
        virtual void NodeDeleted(NodeEditor::Node& node) {};
    };
}
