#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include <imgui_internal.h>
#include "ImNodesEz.h"	
//#include "ImNodes.h"	
//#include "sample.cpp"	

//-

/// A structure defining a connection between two slots of two nodes.
struct Connection
{
	/// `id` that was passed to BeginNode() of input node.
	void* InputNode = nullptr;
	/// Descriptor of input slot.
	const char* InputSlot = nullptr;
	/// `id` that was passed to BeginNode() of output node.
	void* OutputNode = nullptr;
	/// Descriptor of output slot.
	const char* OutputSlot = nullptr;

	bool operator==(const Connection& other) const
	{
		return InputNode == other.InputNode &&
			InputSlot == other.InputSlot &&
			OutputNode == other.OutputNode &&
			OutputSlot == other.OutputSlot;
	}

	bool operator!=(const Connection& other) const
	{
		return !operator ==(other);
	}
};

enum NodeSlotTypes
{
	NodeSlotPosition = 1,   // ID can not be 0
	NodeSlotRotation,
	NodeSlotMatrix,
};

/// A structure holding node state.
struct MyNode
{
	/// Title which will be displayed at the center-top of the node.
	const char* Title = nullptr;
	/// Flag indicating that node is selected by the user.
	bool Selected = false;
	/// Node position on the canvas.
	ImVec2 Pos{};
	/// List of node connections.
	std::vector<Connection> Connections{};
	/// A list of input slots current node has.
	std::vector<ImNodes::Ez::SlotInfo> InputSlots{};
	/// A list of output slots current node has.
	std::vector<ImNodes::Ez::SlotInfo> OutputSlots{};

	explicit MyNode(const char* title,
		const std::vector<ImNodes::Ez::SlotInfo>&& input_slots,
		const std::vector<ImNodes::Ez::SlotInfo>&& output_slots)
	{
		Title = title;
		InputSlots = input_slots;
		OutputSlots = output_slots;
	}

	/// Deletes connection from this node.
	void DeleteConnection(const Connection& connection)
	{
		for (auto it = Connections.begin(); it != Connections.end(); ++it)
		{
			if (connection == *it)
			{
				Connections.erase(it);
				break;
			}
		}
	}
};

//-

class ofApp : public ofBaseApp {

public:
	std::map<std::string, MyNode*(*)()> available_nodes{
	{"Compose", []() -> MyNode* { return new MyNode("Compose", {
		{"Position", NodeSlotPosition}, {"Rotation", NodeSlotRotation}  // Input slots
	}, {
		{"Matrix", NodeSlotMatrix}                                      // Output slots
	}); }},
	{"Decompose", []() -> MyNode* { return new MyNode("Decompose", {
		{"Matrix", NodeSlotMatrix}                                      // Input slots
	}, {
		{"Position", NodeSlotPosition}, {"Rotation", NodeSlotRotation}  // Output slots
	}); }},
	};
	std::vector<MyNode*> nodes;

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxSurfing_ImGui_Manager guiManager;

	void drawWidgets();
	void drawHelloWorld();

	bool bOpen0 = true;
	bool bOpen1 = true;
	bool bOpen2 = false;

	bool initialized = false;
};
