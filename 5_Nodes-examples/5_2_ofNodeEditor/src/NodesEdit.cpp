// Implementation of a ImGui standalone node graph editor
// Thread: https://github.com/ocornut/imgui/issues/306
//
// This is based on code by:
// @ChemiaAion https://gist.github.com/ChemiaAion/0b93553b06beac9fd3824cfeb989d50e
// @emoon https://gist.github.com/emoon/b8ff4b4ce4f1b43e79f2
// @ocornut https://gist.github.com/ocornut/7e9b3ec566a333d725d4
// @flix01 https://github.com/Flix01/imgui/blob/b248df2df98af13d4b7dbb70c92430afc47a038a/addons/imguinodegrapheditor/imguinodegrapheditor.cpp#L432

#include "NodesEdit.h"

namespace ImGui
{
    NodeEditor::NodeEditor()
	{
		id_ = 0;
        cur_node_.Reset();
		canvas_scale_ = 1.0f;
	}

    NodeEditor::~NodeEditor()
	{
	}

    NodeEditor::Node* NodeEditor::GetHoverNode(ImVec2 offset, ImVec2 pos)
	{
		for (auto& node : nodes_)
		{
			ImRect rect((node->position_ * canvas_scale_) + offset, ((node->position_ + node->size_) * canvas_scale_) + offset);

			rect.Expand(2.0f);
			
			if (rect.Contains(pos))
			{
				return node->Get();
			}
		}

		return nullptr;
	}

    void NodeEditor::RenderLines(ImDrawList* draw_list, ImVec2 offset)
	{

        for (auto& link : node_links)
        {
            ImVec2 p1 = offset;
            ImVec2 p4 = offset;

            // source
            if ( link->source->owner->state_ > 0 ) // we are connected from a not collapsed source node
            {
                p1 += ((link->source->owner->position_ + link->source->position_out) * canvas_scale_);
            }
            else //we are connected from a collapsed node
            {
                p1 += ((link->source->owner->position_ + ImVec2(link->source->owner->size_.x, link->source->owner->size_.y / 2.0f)) * canvas_scale_);
            }

            // sink
            if ( link->sink->owner->state_ > 0 ) // we are connected to a not collapsed source node
            {
                p4 += ((link->sink->owner->position_ + link->sink->position) * canvas_scale_);
            }
            else //we are connected to a collapsed node
            {
                p4 += ((link->sink->owner->position_ + ImVec2(link->sink->owner->size_.x, link->sink->owner->size_.y / 2.0f)) * canvas_scale_);
            }

            // default bezier control points
            ImVec2 p2 = p1 + (ImVec2(+50.0f, 0.0f) * canvas_scale_);
            ImVec2 p3 = p4 + (ImVec2(-50.0f, 0.0f) * canvas_scale_);

            // what does this do? probably link selection???
            if (cur_node_.state_ == NodeState_Default)
            {
                const float distance_squared = GetSquaredDistanceToBezierCurve(ImGui::GetIO().MousePos, p1, p2, p3, p4);

                if (distance_squared < (10.0f * 10.0f))
                {
                    cur_node_.Reset(NodeState_HoverConnection);

                    cur_node_.rect_ = ImRect
                    (
                        (link->sink->owner->position_ + link->sink->position),
                        //(connection->target_->position_ + connection->input_->position_),
                        (link->source->owner->position_ + link->source->position_out)
                        //(node->position_ + connection->position_)
                    );

                    cur_node_.node_ = link->source->owner->Get();
                    cur_node_.selected_pad = link->source->Get();
                    cur_node_.link = link;
                }
            }

            bool selected = false;
            selected |= cur_node_.state_ == NodeState_SelectedConnection;
            selected |= cur_node_.state_ == NodeState_DraggingConnection;
            selected &= cur_node_.selected_pad == link->source->Get();

            draw_list->AddBezierCurve(p1, p2, p3, p4, ImColor(0.5f, 0.5f, 0.5f, 1.0f), 2.0f * canvas_scale_);

            if (selected)
            {
                draw_list->AddBezierCurve(p1, p2, p3, p4, ImColor(0.f, 1.0f, 0.f, 0.25f), 4.0f * canvas_scale_);
            }
        }
	}

    void NodeEditor::DisplayNodes(ImDrawList* drawList, ImVec2 offset)
	{
		ImGui::SetWindowFontScale(canvas_scale_);

		for (auto& node : nodes_)
		{
			DisplayNode(drawList, offset, *node);
		}			

		ImGui::SetWindowFontScale(1.0f);
	}

    void NodeEditor::AddNodePadLink(NodePad *source, NodePad *sink)
    {
        auto link = new NodePadLink();
        link->source = source;
        link->sink = sink;
        link->source->connections_++;
        link->sink->connections_++;
        this->node_links.push_back(link);

        //****
        // Call subscribe as a source is connected to a sink
        //****
        LinkAdded(link->source, link->sink);
    }

    void NodeEditor::DeleteNodePadLink(NodePadLink* link) {
        this->node_links.erase(
                std::remove(node_links.begin(), node_links.end(), link),
                node_links.end());
        LinkDeleted(link->source, link->sink);
        link->source->connections_--;
        link->sink->connections_--;
        delete link;
    }

    void NodeEditor::DeleteSelectedNodes() {
        std::vector<std::unique_ptr<Node>> replacement;
        replacement.reserve(nodes_.size());

        std::vector<NodePadLink*> delete_links;
        delete_links.reserve(node_links.size());
        // delete connections
        // todo iterate the nodepadlink vector instead of nodes vector???
        for (auto& node : nodes_)
        {
            if ( node->id_ > 0 ) {
                replacement.push_back(std::move(node));
                continue;  // node not selected
            }

            int connections = 0;
            for (auto& pad : node->pads)
            {
                connections += pad->connections_;
            }
            if ( connections == 0 ) continue; // no links to this node

            for (auto& link : node_links)
            {
                if ( link->source->owner == node.get() ||
                     link->sink->owner == node.get() )
                {
                    //mark this connection for deletion
                    delete_links.push_back(link);
                }
            }
        }
        for ( auto& link : delete_links)
        {
            DeleteNodePadLink(link);
        }

        // save not selected nodes
        nodes_ = std::move(replacement);
    }

    NodeEditor::Node* NodeEditor::CreateNodeFromType(ImVec2 pos, const NodeType& type)
	{
		auto node = std::make_unique<Node>();

		////////////////////////////////////////////////////////////////////////////////
		
		node->id_ = -++id_;
        node->name_ = type.name + std::to_string(id_).c_str();
		node->position_ = pos;

		{
            std::vector<NodePadType>::const_iterator it = type.pads.begin();
            while (it != type.pads.end())
            {
                auto pad = std::make_unique<NodePad>();
                pad->name = it->name;
                pad->access = it->access;
                pad->format = it->format;
                pad->owner = node.get();
                node->pads.push_back(std::move(pad));
                ++it;
            }
		}

		////////////////////////////////////////////////////////////////////////////////

		ImVec2 title_size = ImGui::CalcTextSize(node->name_.c_str());

        const float vertical_padding = 1.5f;

		////////////////////////////////////////////////////////////////////////////////

        ImVec2 pads_size;
        for (auto& pad : node->pads)
		{
            ImVec2 name_size = ImGui::CalcTextSize(pad->name.c_str());
            pads_size.x = ImMax(pads_size.x, name_size.x);
            pads_size.y += name_size.y * vertical_padding;
		}

		////////////////////////////////////////////////////////////////////////////////

        node->size_.x = ImMax(pads_size.x, title_size.x);
		node->size_.x += title_size.y * 6.0f;

		node->collapsed_height = (title_size.y * 2.0f);
        node->full_height = (title_size.y * 3.0f) + pads_size.y;

		node->size_.y = node->full_height;
		
		node->position_ -= node->size_ / 2.0f;
		
		////////////////////////////////////////////////////////////////////////////////

        // we place node connection sockets on the border of the node widget with an offset of 2px
        pads_size = ImVec2(2, title_size.y * 2.5f);
        for (auto& pad : node->pads)
		{
            //input pads
            const float half = ((ImGui::CalcTextSize(pad->name.c_str()).y * vertical_padding) / 2.0f);

            pads_size.y += half;
            pad->position = ImVec2(pads_size.x, pads_size.y);
            pad->position_out = ImVec2(pads_size.x + node->size_.x, pads_size.y);
            pads_size.y += half;
		}
	
		////////////////////////////////////////////////////////////////////////////////

		nodes_.push_back(std::move(node));
		return nodes_.back().get();
	}

    void NodeEditor::UpdateScroll()
	{
		////////////////////////////////////////////////////////////////////////////////

		{
			ImVec2 scroll;

			if (ImGui::GetIO().KeyShift && !ImGui::GetIO().KeyCtrl && !ImGui::IsMouseDown(0) && !ImGui::IsMouseDown(1) && !ImGui::IsMouseDown(2))
			{
				scroll.x = ImGui::GetIO().MouseWheel * 24.0f;
			}

			if (!ImGui::GetIO().KeyShift && !ImGui::GetIO().KeyCtrl && !ImGui::IsMouseDown(0) && !ImGui::IsMouseDown(1) && !ImGui::IsMouseDown(2))
			{
				scroll.y = ImGui::GetIO().MouseWheel * 24.0f;
			}

			if (ImGui::IsMouseDragging(1, 6.0f) && !ImGui::IsMouseDown(0) && !ImGui::IsMouseDown(2))
			{
				scroll += ImGui::GetIO().MouseDelta;
			}

			canvas_scroll_ += scroll;

		}

		////////////////////////////////////////////////////////////////////////////////

		{
			ImVec2 mouse = canvas_mouse_;

			float zoom = 0.0f;

			if (!ImGui::GetIO().KeyShift && !ImGui::IsMouseDown(0) && !ImGui::IsMouseDown(1))
			{
				if (ImGui::GetIO().KeyCtrl)
				{
					zoom += ImGui::GetIO().MouseWheel;
				}

				if (ImGui::IsMouseDragging(2, 6.0f))
				{
					zoom -= ImGui::GetIO().MouseDelta.y;
					mouse -= ImGui::GetMouseDragDelta(2, 6.0f);
				}
			}

			ImVec2 focus = (mouse - canvas_scroll_) / canvas_scale_;

			if (zoom < 0.0f)
			{
				canvas_scale_ /= 1.05f;
			}

			if (zoom > 0.0f)
			{
				canvas_scale_ *= 1.05f;
			}

			if (canvas_scale_ < 0.3f)
			{
				canvas_scale_ = 0.3f;
			}

			if (canvas_scale_ > 3.0f)
			{
				canvas_scale_ = 3.0f;
			}

			focus = canvas_scroll_ + (focus * canvas_scale_);
			canvas_scroll_ += (mouse - focus);
		}

		////////////////////////////////////////////////////////////////////////////////
	}

    void NodeEditor::UpdateState(ImVec2 offset)
	{
        // collapsing nodes
        if (cur_node_.state_ == NodeState_HoverNode && ImGui::IsMouseDoubleClicked(0))
		{		
            if (cur_node_.node_->state_ < 0)
			{	// collapsed node goes to full
                cur_node_.node_->size_.y = cur_node_.node_->full_height;
			}
			else
			{	// full node goes to collapsed
                cur_node_.node_->size_.y = cur_node_.node_->collapsed_height;
			}

            cur_node_.node_->state_ = -cur_node_.node_->state_;
		}

        switch (cur_node_.state_)
		{		
            case NodeState_Default:
            {
				if (ImGui::IsMouseDown(0) && !ImGui::IsMouseDown(1) && !ImGui::IsMouseDown(2))
				{
					ImRect canvas = ImRect(ImVec2(0.0f, 0.0f), canvas_size_);

					if (!canvas.Contains(canvas_mouse_))
					{
						break;
					}

                    cur_node_.Reset(NodeState_SelectingEmpty);

                    cur_node_.position_ = ImGui::GetIO().MousePos;
                    cur_node_.rect_.Min = ImGui::GetIO().MousePos;
                    cur_node_.rect_.Max = ImGui::GetIO().MousePos;
				}
			} break;

			// helper: just block all states till next update
            case NodeState_Block:
			{
                cur_node_.Reset();
			} break;

            case NodeState_HoverConnection:
			{
				const float distance_squared = GetSquaredDistanceToBezierCurve
				(
					ImGui::GetIO().MousePos,
                    offset + (cur_node_.rect_.Min * canvas_scale_),
                    offset + (cur_node_.rect_.Min * canvas_scale_) + (ImVec2(+50.0f, 0.0f) * canvas_scale_),
                    offset + (cur_node_.rect_.Max * canvas_scale_) + (ImVec2(-50.0f, 0.0f) * canvas_scale_),
                    offset + (cur_node_.rect_.Max * canvas_scale_)
				);
				
				if (distance_squared > (10.0f * 10.0f))
				{
                    cur_node_.Reset();
					break;
				}

				if (ImGui::IsMouseDown(0))
				{
                    cur_node_.state_ = NodeState_SelectedConnection;
				}

			} break;

            case NodeState_DraggingInput:
			{
				if (!ImGui::IsMouseDown(0) || ImGui::IsMouseClicked(1))
				{
                    cur_node_.Reset(NodeState_Block);
					break;
				}

                ImVec2 p1 = offset + (cur_node_.position_ * canvas_scale_);
				ImVec2 p2 = p1 + (ImVec2(-50.0f, 0.0f) * canvas_scale_);
				ImVec2 p3 = ImGui::GetIO().MousePos + (ImVec2(+50.0f, 0.0f) * canvas_scale_);
				ImVec2 p4 = ImGui::GetIO().MousePos;

                ImGui::GetWindowDrawList()->AddBezierCurve(p1, p2, p3, p4, ImColor(1.0f, 1.0f, 0.0f, 1.0f), 2.0f * canvas_scale_);
			} break;

            case NodeState_DraggingInputValid:
			{
                cur_node_.state_ = NodeState_DraggingInput;

				if (ImGui::IsMouseClicked(1))
				{
                    cur_node_.Reset(NodeState_Block);
					break;
				}

                ImVec2 p1 = offset + (cur_node_.position_ * canvas_scale_);
				ImVec2 p2 = p1 + (ImVec2(-50.0f, 0.0f) * canvas_scale_);
				ImVec2 p3 = ImGui::GetIO().MousePos + (ImVec2(+50.0f, 0.0f) * canvas_scale_);
				ImVec2 p4 = ImGui::GetIO().MousePos;

                ImGui::GetWindowDrawList()->AddBezierCurve(p1, p2, p3, p4, ImColor(0.0f, 1.0f, 0.0f, 1.0f), 2.0f * canvas_scale_);
			} break;

            case NodeState_DraggingOutput:
			{
				if (!ImGui::IsMouseDown(0) || ImGui::IsMouseClicked(1))
				{
                    cur_node_.Reset(NodeState_Block);
					break;
				}

                ImVec2 p1 = offset + (cur_node_.position_ * canvas_scale_);
				ImVec2 p2 = p1 + (ImVec2(+50.0f, 0.0f) * canvas_scale_);
				ImVec2 p3 = ImGui::GetIO().MousePos + (ImVec2(-50.0f, 0.0f) * canvas_scale_);
				ImVec2 p4 = ImGui::GetIO().MousePos;

                ImGui::GetWindowDrawList()->AddBezierCurve(p1, p2, p3, p4, ImColor(1.0f, 1.0f, 0.0f, 1.0f), 2.0f * canvas_scale_);
			} break;

            case NodeState_DraggingOutputValid:
			{
                cur_node_.state_ = NodeState_DraggingOutput;

				if (ImGui::IsMouseClicked(1))
				{
                    cur_node_.Reset(NodeState_Block);
					break;
				}

                ImVec2 p1 = offset + (cur_node_.position_ * canvas_scale_);
				ImVec2 p2 = p1 + (ImVec2(+50.0f, 0.0f) * canvas_scale_);
				ImVec2 p3 = ImGui::GetIO().MousePos + (ImVec2(-50.0f, 0.0f) * canvas_scale_);
				ImVec2 p4 = ImGui::GetIO().MousePos;

				ImGui::GetWindowDrawList()->AddBezierCurve(p1, p2, p3, p4, ImColor(0.0f, 1.0f, 0.0f, 1.0f), 2.0f * canvas_scale_);
			} break;

            case NodeState_SelectingEmpty:
			{
				if (!ImGui::IsMouseDown(0))
				{
                    cur_node_.Reset(NodeState_Block);
					break;
				}

                cur_node_.rect_.Min = ImMin(cur_node_.position_, ImGui::GetIO().MousePos);
                cur_node_.rect_.Max = ImMax(cur_node_.position_, ImGui::GetIO().MousePos);
			} break;

            case NodeState_SelectingValid:
			{
				if (!ImGui::IsMouseDown(0))
				{
                    cur_node_.Reset(NodeState_Selected);
					break;
				}

                cur_node_.rect_.Min = ImMin(cur_node_.position_, ImGui::GetIO().MousePos);
                cur_node_.rect_.Max = ImMax(cur_node_.position_, ImGui::GetIO().MousePos);

                cur_node_.state_ = NodeState_SelectingEmpty;
			} break;

            case NodeState_SelectingMore:
			{
                cur_node_.rect_.Min = ImMin(cur_node_.position_, ImGui::GetIO().MousePos);
                cur_node_.rect_.Max = ImMax(cur_node_.position_, ImGui::GetIO().MousePos);

				if (ImGui::IsMouseDown(0) && ImGui::GetIO().KeyShift)
				{
					break;
				}

				for (auto& node : nodes_)
				{
					ImVec2 node_rect_min = offset + (node->position_ * canvas_scale_);
					ImVec2 node_rect_max = node_rect_min + (node->size_ * canvas_scale_);

					ImRect node_rect(node_rect_min, node_rect_max);

                    if (ImGui::GetIO().KeyCtrl && cur_node_.rect_.Overlaps(node_rect))
					{
						node->id_ = -abs(node->id_); // add "selected" flag
						continue;
					}
					
                    if (!ImGui::GetIO().KeyCtrl && cur_node_.rect_.Contains(node_rect))
					{
						node->id_ = -abs(node->id_); // add "selected" flag
						continue;
					}
				}

                cur_node_.Reset(NodeState_Selected);
			} break;

            case NodeState_Selected:
			{
				// delete all selected nodes
				if (ImGui::IsKeyPressed(ImGui::GetIO().KeyMap[ImGuiKey_Delete]))
				{
                    DeleteSelectedNodes();
                    cur_node_.Reset();
					break;
				}

				// no action taken
				if (!ImGui::IsMouseClicked(0))
				{
					break;
				}

                cur_node_.Reset();
				auto hovered = GetHoverNode(offset, ImGui::GetIO().MousePos);

				// empty area under the mouse
				if (!hovered)
				{
                    cur_node_.position_ = ImGui::GetIO().MousePos;
                    cur_node_.rect_.Min = ImGui::GetIO().MousePos;
                    cur_node_.rect_.Max = ImGui::GetIO().MousePos;

					if (ImGui::GetIO().KeyShift)
					{
                        cur_node_.state_ = NodeState_SelectingMore;
					}
					else
					{
                        cur_node_.state_ = NodeState_SelectingEmpty;
					}
					break;
				}
				
				// lets select node under the mouse
				if (ImGui::GetIO().KeyShift)
				{
					hovered->id_ = -abs(hovered->id_);
                    cur_node_.state_ = NodeState_DraggingSelected;
					break;
				}

				// lets toggle selection of a node under the mouse
				if (!ImGui::GetIO().KeyShift && ImGui::GetIO().KeyCtrl)
				{
					if (hovered->id_ > 0)
					{
						hovered->id_ = -abs(hovered->id_);
                        cur_node_.state_ = NodeState_DraggingSelected;
					}
					else
					{
						hovered->id_ = abs(hovered->id_);
                        cur_node_.state_ = NodeState_Selected;
					}
					break;
				}

				// lets start dragging
				if (hovered->id_ < 0)
				{
                    cur_node_.state_ = NodeState_DraggingSelected;
					break;
				}
				
				// not selected node clicked, lets jump selection to it
				for (auto& node : nodes_)
				{
					if (node.get() != hovered)
					{
						node->id_ = abs(node->id_);
					}
				}
			} break;

            case NodeState_DraggingSelected:
			{
				if (!ImGui::IsMouseDown(0))
				{
                    if (cur_node_.node_)
					{
						if (ImGui::GetIO().KeyShift || ImGui::GetIO().KeyCtrl)
						{
                            cur_node_.Reset(NodeState_Selected);
							break;
						}

                        cur_node_.state_ = NodeState_HoverNode;
					}
					else
					{
                        cur_node_.Reset(NodeState_Selected);
					}
				}
				else
				{
					for (auto& node : nodes_)
					{
						if (node->id_ < 0)
						{
							node->position_ += ImGui::GetIO().MouseDelta / canvas_scale_;
						}
					}
				}
			} break;

            case NodeState_SelectedConnection:
			{
				if (ImGui::IsMouseClicked(1))
				{
                    cur_node_.Reset(NodeState_Block);
					break;
				}

				if (ImGui::IsMouseDown(0))
				{
					const float distance_squared = GetSquaredDistanceToBezierCurve
					(
						ImGui::GetIO().MousePos,
                        offset + (cur_node_.rect_.Min * canvas_scale_),
                        offset + (cur_node_.rect_.Min * canvas_scale_) + (ImVec2(+50.0f, 0.0f) * canvas_scale_),
                        offset + (cur_node_.rect_.Max * canvas_scale_) + (ImVec2(-50.0f, 0.0f) * canvas_scale_),
                        offset + (cur_node_.rect_.Max * canvas_scale_)
					);

					if (distance_squared > (10.0f * 10.0f))
					{
                        cur_node_.Reset();
						break;
					}

                    cur_node_.state_ = NodeState_DraggingConnection;
				}

                if (ImGui::IsKeyPressed(ImGui::GetIO().KeyMap[ImGuiKey_Delete]))
                {
                    // delete selected connection
                    // first fins the link index
                    this->DeleteNodePadLink(cur_node_.link);
                    cur_node_.Reset(NodeState_Default);
                }
			} break;

            case NodeState_DraggingConnection:
			{
				if (!ImGui::IsMouseDown(0))
				{
                    cur_node_.state_ = NodeState_SelectedConnection;
					break;
				}

				if (ImGui::IsMouseClicked(1))
				{
                    cur_node_.Reset(NodeState_Block);
					break;
				}

                cur_node_.node_->position_ += ImGui::GetIO().MouseDelta / canvas_scale_;
                // todo: only used to draw a bezier using mouse pos so don't do this in the struct?
                //cur_node_.selected_pad->target_->position_ += ImGui::GetIO().MouseDelta / canvas_scale_;
			} break;
		}
	}

    void NodeEditor::DisplayNode(ImDrawList* drawList, ImVec2 offset, Node& node)
	{
		ImGui::PushID(abs(node.id_));
		ImGui::BeginGroup();

        ImVec2 node_rect_min = offset + (node.position_ * canvas_scale_);
		ImVec2 node_rect_max = node_rect_min + (node.size_ * canvas_scale_);

		ImGui::SetCursorScreenPos(node_rect_min);
		ImGui::InvisibleButton("Node", node.size_ * canvas_scale_);
		
		////////////////////////////////////////////////////////////////////////////////

		// state machine for node hover/drag
		{
			bool node_hovered = ImGui::IsItemHovered();
			bool node_active = ImGui::IsItemActive();

            if (node_hovered && cur_node_.state_ == NodeState_HoverNode)
			{
                cur_node_.node_ = node.Get();

				if (node_active)
				{
					node.id_ = -abs(node.id_); // add "selected" flag
                    cur_node_.state_ = NodeState_DraggingSelected;
				}
			}

            if (node_hovered && cur_node_.state_ == NodeState_Default)
			{
                cur_node_.node_ = node.Get();

				if (node_active)
				{
					node.id_ = -abs(node.id_); // add "selected" flag
                    cur_node_.state_ = NodeState_DraggingSelected;
				}
				else
				{
                    cur_node_.state_ = NodeState_HoverNode;
				}
			}

            if (!node_hovered && cur_node_.state_ == NodeState_HoverNode)
			{
                if (cur_node_.node_ == node.Get())
				{
                    cur_node_.Reset();
				}
			}
		}

		////////////////////////////////////////////////////////////////////////////////

        bool consider_hover = cur_node_.node_ ? cur_node_.node_ == node.Get() : false;

		////////////////////////////////////////////////////////////////////////////////

        if (cur_node_.state_ != NodeState_Selected && cur_node_.state_ != NodeState_DraggingSelected && cur_node_.state_ != NodeState_SelectingMore)
		{
			node.id_ = abs(node.id_); // remove "selected" flag
		}

		////////////////////////////////////////////////////////////////////////////////

		bool consider_select = false;
        consider_select |= cur_node_.state_ == NodeState_SelectingEmpty;
        consider_select |= cur_node_.state_ == NodeState_SelectingValid;
        consider_select |= cur_node_.state_ == NodeState_SelectingMore;

		if (consider_select)
		{		
			bool select_it = false;
		
            ImRect node_rect(node_rect_min,	node_rect_max);
		
			if (ImGui::GetIO().KeyCtrl)
			{
                select_it |= cur_node_.rect_.Overlaps(node_rect);
			}
			else
			{
                select_it |= cur_node_.rect_.Contains(node_rect);
			}
		
			consider_hover |= select_it;

            if (select_it && cur_node_.state_ != NodeState_SelectingMore)
			{
				node.id_ = -abs(node.id_); // add "selected" flag
                cur_node_.state_ = NodeState_SelectingValid;
			}
		}

		////////////////////////////////////////////////////////////////////////////////

		ImVec2 title_name_size = ImGui::CalcTextSize(node.name_.c_str());
		const float corner = title_name_size.y / 2.0f;

		{		
			ImVec2 title_area;
			title_area.x = node_rect_max.x;
			title_area.y = node_rect_min.y + (title_name_size.y * 2.0f);

			ImVec2 title_pos;
			title_pos.x = node_rect_min.x + ((title_area.x - node_rect_min.x) / 2.0f) - (title_name_size.x / 2.0f);
			
			if (node.state_ > 0)
			{
				drawList->AddRectFilled(node_rect_min, node_rect_max, ImColor(0.25f, 0.25f, 0.25f, 0.9f), corner, ImDrawCornerFlags_All);
				drawList->AddRectFilled(node_rect_min, title_area, ImColor(0.25f, 0.0f, 0.125f, 0.9f), corner, ImDrawCornerFlags_Top);

				title_pos.y = node_rect_min.y + ((title_name_size.y * 2.0f) / 2.0f) - (title_name_size.y / 2.0f);
			}
			else
			{
				drawList->AddRectFilled(node_rect_min, node_rect_max, ImColor(0.25f, 0.0f, 0.125f, 0.9f), corner, ImDrawCornerFlags_All);

				title_pos.y = node_rect_min.y + ((node_rect_max.y - node_rect_min.y) / 2.0f) - (title_name_size.y / 2.0f);
			}

			ImGui::SetCursorScreenPos(title_pos);
			ImGui::Text("%s", node.name_.c_str());
		}

		////////////////////////////////////////////////////////////////////////////////
		
		if (node.state_ > 0)
		{
			////////////////////////////////////////////////////////////////////////////////

            for (auto& pad : node.pads)
			{
                if (pad->format.empty() ) // if empty string
				{
					continue;
				}

				bool consider_io = false;

                ImVec2 input_name_size = ImGui::CalcTextSize(pad->name.c_str());
                ImVec2 pad_pos = node_rect_min + (pad->position * canvas_scale_);

                {
                    ImVec2 pos = pad_pos;
                    pos += ImVec2(input_name_size.y * 0.75f, -input_name_size.y / 2.0f);

                    ImGui::SetCursorScreenPos(pos);
                    ImGui::Text("%s", pad->name.c_str());
                }

                if ( pad->access.find('w') != std::string::npos ) // string contains 'r'
                {
                    // TODO: rename to pad...
                    float pad_radius = input_name_size.y/2.f;
                    if ( IsPadHovered(pad_pos, pad_radius) )
                    {
                        consider_io |= cur_node_.state_ == NodeState_Default;
                        consider_io |= cur_node_.state_ == NodeState_HoverConnection;
                        consider_io |= cur_node_.state_ == NodeState_HoverNode;

                        // from nothing to hovered input
                        if (consider_io)
                        {
                            cur_node_.Reset(NodeState_HoverIO);
                            cur_node_.node_ = node.Get();
                            cur_node_.selected_pad = pad.get();
                            cur_node_.position_ = node.position_ + pad->position;
                        }

                        // we could start Dragging input now
                        if (ImGui::IsMouseClicked(0) && cur_node_.selected_pad == pad.get())
                        {
                            cur_node_.state_ = NodeState_DraggingInput;

                            // remove connection from this input
                            /* TODO this needs to be done differently in order to  allow multiple links
                            if (pad->input_)
                            {
                                pad->input_->connections_--;
                            }

                            connection->target_ = nullptr;
                            connection->input_ = nullptr;
                            connection->connections_ = 0;
                            */
                        }

                        consider_io = true;
                    }
                    else if (cur_node_.state_ == NodeState_HoverIO && cur_node_.selected_pad == pad.get())
                    {
                        cur_node_.Reset(); // we are not hovering this last hovered input anymore
                    }

                    ////////////////////////////////////////////////////////////////////////////////

                    ImColor color = ImColor(0.5f, 0.5f, 0.5f, 1.0f);

                    if (pad->connections_ > 0)
                    {
                        drawList->AddCircleFilled(pad_pos, (input_name_size.y / 3.0f), color);
                    }

                    // currently we are draggin some output, check if there is a possibilty to connect here (this input)
                    if (cur_node_.state_ == NodeState_DraggingOutput || cur_node_.state_ == NodeState_DraggingOutputValid)
                    {
                        // check is dragging output are not from the same node
                        if (cur_node_.node_ != node.Get() && cur_node_.selected_pad->format.compare(pad->format) == 0 )
                        {
                            color = ImColor(0.0f, 1.0f, 0.0f, 1.0f);

                            if (consider_io)
                            {
                                cur_node_.state_ = NodeState_DraggingOutputValid;
                                drawList->AddCircleFilled(pad_pos, (input_name_size.y / 3.0f), color);

                                if (!ImGui::IsMouseDown(0))
                                {
                                    AddNodePadLink(cur_node_.selected_pad->Get(), pad.get());

                                    cur_node_.Reset(NodeState_HoverIO);
                                    cur_node_.node_ = node.Get();
                                    cur_node_.selected_pad = pad.get();
                                    cur_node_.position_ = node_rect_min + pad->position;
                                }
                            }
                        }
                    }

                    consider_io |= cur_node_.state_ == NodeState_HoverIO;
                    consider_io |= cur_node_.state_ == NodeState_DraggingInput;
                    consider_io |= cur_node_.state_ == NodeState_DraggingInputValid;
                    consider_io &= cur_node_.selected_pad == pad.get();

                    if (consider_io)
                    {
                        color = ImColor(0.0f, 1.0f, 0.0f, 1.0f);

                        if (cur_node_.state_ != NodeState_HoverIO)
                        {
                            drawList->AddCircleFilled(pad_pos, (input_name_size.y / 3.0f), color);
                        }
                    }

                    drawList->AddCircle(pad_pos, (input_name_size.y / 3.0f), color, ((int)(6.0f * canvas_scale_) + 10), (1.5f * canvas_scale_));
                }

                if ( pad->access.find_first_of('r') != std::string::npos ) // string contains 'w'
                {
                    ImVec2 pad_output_pos = pad_pos;
                    pad_output_pos.x += (node.size_.x-4) * canvas_scale_; //position with 2px inward correction

                    if (IsPadHovered(pad_output_pos, (input_name_size.y / 2.0f)))
                    {
                        consider_io |= cur_node_.state_ == NodeState_Default;
                        consider_io |= cur_node_.state_ == NodeState_HoverConnection;
                        consider_io |= cur_node_.state_ == NodeState_HoverNode;

                        // from nothing to hovered output
                        if (consider_io)
                        {
                            cur_node_.Reset(NodeState_HoverIO);
                            cur_node_.node_ = node.Get();
                            cur_node_.selected_pad = pad.get();
                            cur_node_.position_ = node.position_ + pad->position;
                            cur_node_.position_.x += node.size_.x-4; // we need to set the output pad position
                        }

                        // we could start dragging output now
                        if (ImGui::IsMouseClicked(0) && cur_node_.selected_pad == pad.get())
                        {
                            cur_node_.state_ = NodeState_DraggingOutput;
                        }

                        consider_io = true;
                    }
                    else if (cur_node_.state_ == NodeState_HoverIO && cur_node_.selected_pad == pad.get())
                    {
                        cur_node_.Reset(); // we are not hovering this last hovered output anymore
                    }

                    ////////////////////////////////////////////////////////////////////////////////

                    ImColor color = ImColor(0.5f, 0.5f, 0.5f, 1.0f);

                    if (pad->connections_ > 0)
                    {
                        drawList->AddCircleFilled(pad_output_pos, (input_name_size.y / 3.0f), ImColor(0.5f, 0.5f, 0.5f, 1.0f));
                    }

                    // currently we are draggin some input, check if there is a possibilty to connect here (this output)
                    if (cur_node_.state_ == NodeState_DraggingInput || cur_node_.state_ == NodeState_DraggingInputValid)
                    {
                        // check is dragging input are not from the same node
                        if (cur_node_.node_ != node.Get() && cur_node_.selected_pad->format.compare(pad->format) == 0)
                        {
                            color = ImColor(0.0f, 1.0f, 0.0f, 1.0f);

                            if (consider_io)
                            {
                                cur_node_.state_ = NodeState_DraggingInputValid;
                                drawList->AddCircleFilled(pad_output_pos, (input_name_size.y / 3.0f), color);
                                // if mouse released create a new NodeLink
                                if (!ImGui::IsMouseDown(0))
                                {
                                    AddNodePadLink(pad.get(), cur_node_.selected_pad->Get());

                                    cur_node_.Reset(NodeState_HoverIO);
                                    cur_node_.node_ = node.Get();
                                    cur_node_.selected_pad = pad.get();
                                    cur_node_.position_ = node_rect_min + pad->position;
                                }
                            }
                        }
                    }

                    consider_io |= cur_node_.state_ == NodeState_HoverIO;
                    consider_io |= cur_node_.state_ == NodeState_DraggingOutput;
                    consider_io |= cur_node_.state_ == NodeState_DraggingOutputValid;
                    consider_io &= cur_node_.selected_pad == pad.get();

                    if (consider_io)
                    {
                        color = ImColor(0.0f, 1.0f, 0.0f, 1.0f);

                        if (cur_node_.state_ != NodeState_HoverIO)
                        {
                            drawList->AddCircleFilled(pad_output_pos, (input_name_size.y / 3.0f), color);
                        }
                    }

                    drawList->AddCircle(pad_output_pos, (input_name_size.y / 3.0f), color, ((int)(6.0f * canvas_scale_) + 10), (1.5f * canvas_scale_));
                }
            }


			////////////////////////////////////////////////////////////////////////////////

            /*for (auto& connection : node.outputs_)
			{
				if (connection->type_ == ConnectionType_None)
				{
					continue;
				}

				bool consider_io = false;

				ImVec2 output_name_size = ImGui::CalcTextSize(connection->name_.c_str());

            }*/
			
			////////////////////////////////////////////////////////////////////////////////		
        }

		////////////////////////////////////////////////////////////////////////////////

		if ((consider_select && consider_hover) || (node.id_ < 0))
		{
			drawList->AddRectFilled(node_rect_min, node_rect_max, ImColor(1.0f, 1.0f, 1.0f, 0.25f), corner, ImDrawCornerFlags_All);
		}

		ImGui::EndGroup();
		ImGui::PopID();
	}

    void NodeEditor::ProcessNodes()
	{
		////////////////////////////////////////////////////////////////////////////////
		
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));

		ImGui::BeginChild("NodesScrollingRegion", ImVec2(0.0f, 0.0f), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove);

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		////////////////////////////////////////////////////////////////////////////////

		if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
		{
			canvas_mouse_ = ImGui::GetIO().MousePos - ImGui::GetCursorScreenPos();
			canvas_position_ = ImGui::GetCursorScreenPos();
			canvas_size_ = ImGui::GetWindowSize();

			UpdateScroll();
		}
		
		////////////////////////////////////////////////////////////////////////////////
        // draw grid
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();

			ImU32 color = ImColor(0.5f, 0.5f, 0.5f, 0.1f);
			const float size = 64.0f * canvas_scale_;

			for (float x = fmodf(canvas_scroll_.x, size); x < canvas_size_.x; x += size)
			{
				draw_list->AddLine(ImVec2(x, 0.0f) + canvas_position_, ImVec2(x, canvas_size_.y) + canvas_position_, color);
			}

			for (float y = fmodf(canvas_scroll_.y, size); y < canvas_size_.y; y += size)
			{
				draw_list->AddLine(ImVec2(0.0f, y) + canvas_position_, ImVec2(canvas_size_.x, y) + canvas_position_, color);
			}
		}

		////////////////////////////////////////////////////////////////////////////////

		ImVec2 offset = canvas_position_ + canvas_scroll_;

		UpdateState(offset);
		RenderLines(draw_list, offset);
		DisplayNodes(draw_list, offset);

        if (cur_node_.state_ == NodeState_SelectingEmpty || cur_node_.state_ == NodeState_SelectingValid || cur_node_.state_ == NodeState_SelectingMore)
		{
            draw_list->AddRectFilled(cur_node_.rect_.Min, cur_node_.rect_.Max, ImColor(200.0f, 200.0f, 0.0f, 0.1f));
            draw_list->AddRect(cur_node_.rect_.Min, cur_node_.rect_.Max, ImColor(200.0f, 200.0f, 0.0f, 0.5f));
		}

		////////////////////////////////////////////////////////////////////////////////
		
		{
			ImGui::SetCursorScreenPos(canvas_position_);

			bool consider_menu = !ImGui::IsAnyItemHovered();
			consider_menu &= ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
            consider_menu &= cur_node_.state_ == NodeState_Default || cur_node_.state_ == NodeState_Selected;
			consider_menu &= ImGui::IsMouseReleased(1);		
			
			if (consider_menu)
			{
				ImGuiContext* context = ImGui::GetCurrentContext();

				if (context->IO.MouseDragMaxDistanceSqr[1] < 36.0f)
				{
					ImGui::OpenPopup("NodesContextMenu");
				}								
			}

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
			if (ImGui::BeginPopup("NodesContextMenu"))
			{
                cur_node_.Reset(NodeState_Block);

                for (auto& node : node_types)
				{
                    if (ImGui::MenuItem(node.name.c_str()))
					{					
                        cur_node_.Reset();
                        cur_node_.node_ = CreateNodeFromType((canvas_mouse_ - canvas_scroll_) / canvas_scale_, node);
					}
				}				
				ImGui::EndPopup();
			}
			ImGui::PopStyleVar();
		}

		////////////////////////////////////////////////////////////////////////////////

        {
            ImGui::SetCursorScreenPos(canvas_position_);

            switch (cur_node_.state_)
            {
                case NodeState_Default: ImGui::Text("NodeState_Default"); break;
                case NodeState_Block: ImGui::Text("NodeState_Block"); break;
                case NodeState_HoverIO: ImGui::Text("NodeState_HoverIO"); break;
                case NodeState_HoverConnection: ImGui::Text("NodeState_HoverConnection"); break;
                case NodeState_HoverNode: ImGui::Text("NodeState_HoverNode"); break;
                case NodeState_DraggingInput: ImGui::Text("NodeState_DraggingInput"); break;
                case NodeState_DraggingInputValid: ImGui::Text("NodeState_DraggingInputValid"); break;
                case NodeState_DraggingOutput: ImGui::Text("NodeState_DraggingOutput"); break;
                case NodeState_DraggingOutputValid: ImGui::Text("NodeState_DraggingOutputValid"); break;
                case NodeState_DraggingConnection: ImGui::Text("NodeState_DraggingConnection"); break;
                case NodeState_DraggingSelected: ImGui::Text("NodeState_DraggingSelected"); break;
                case NodeState_SelectingEmpty: ImGui::Text("NodeState_SelectingEmpty"); break;
                case NodeState_SelectingValid: ImGui::Text("NodeState_SelectingValid"); break;
                case NodeState_SelectingMore: ImGui::Text("NodeState_SelectingMore"); break;
                case NodeState_Selected: ImGui::Text("NodeState_Selected"); break;
                case NodeState_SelectedConnection: ImGui::Text("NodeState_SelectedConnection"); break;
                default: ImGui::Text("UNKNOWN"); break;
            }

            ImGui::Text("");

            ImGui::Text("Mouse: %.2f, %.2f", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
            ImGui::Text("Mouse delta: %.2f, %.2f", ImGui::GetIO().MouseDelta.x, ImGui::GetIO().MouseDelta.y);
            ImGui::Text("Offset: %.2f, %.2f", offset.x, offset.y);

            ImGui::Text("");

            ImGui::Text("Canvas_mouse: %.2f, %.2f", canvas_mouse_.x, canvas_mouse_.y);
            ImGui::Text("Canvas_position: %.2f, %.2f", canvas_position_.x, canvas_position_.y);
            ImGui::Text("Canvas_size: %.2f, %.2f", canvas_size_.x, canvas_size_.y);
            ImGui::Text("Canvas_scroll: %.2f, %.2f", canvas_scroll_.x, canvas_scroll_.y);
            ImGui::Text("Canvas_scale: %.2f", canvas_scale_);
        }

		////////////////////////////////////////////////////////////////////////////////

		ImGui::EndChild();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
	}
}
