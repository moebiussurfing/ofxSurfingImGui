#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(-1920, 25);

	guiManager.setImGuiAutodraw(true);
	guiManager.setup();

}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		drawWidgets();

		//ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		//if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		//ImGui::Begin("Panels", &bOpen0, window_flags);
		//{
		//ofxImGuiSurfing::ToggleRoundedButton("Show 0", &bOpen0);
		ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
		ofxImGuiSurfing::ToggleRoundedButton("Show 2", &bOpen2);
		if (bOpen1 && bOpen2) bOpen2 = false;
		//}
		//ImGui::End();
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::drawHelloWorld()
{
	{
		static ImNodes::CanvasState canvas;

		if (ImGui::Begin("rokups/ImNodes 1", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
		{
			ImNodes::BeginCanvas(&canvas);

			struct Node
			{
				ImVec2 pos{};
				bool selected{};
				ImNodes::Ez::SlotInfo inputs[1];
				ImNodes::Ez::SlotInfo outputs[1];
			};

			static Node nodes[3] = {
				{{50, 100}, false, {{"In", 1}}, {{"Out", 1}}},
				{{250, 50}, false, {{"In", 1}}, {{"Out", 1}}},
				{{250, 100}, false, {{"In", 1}}, {{"Out", 1}}},
			};

			for (Node& node : nodes)
			{
				if (ImNodes::Ez::BeginNode(&node, "Node Title", &node.pos, &node.selected))
				{
					ImNodes::Ez::InputSlots(node.inputs, 1);
					ImNodes::Ez::OutputSlots(node.outputs, 1);
					ImNodes::Ez::EndNode();
				}
			}

			ImNodes::Connection(&nodes[1], "In", &nodes[0], "Out");
			ImNodes::Connection(&nodes[2], "In", &nodes[0], "Out");

			ImNodes::EndCanvas();
		}
		ImGui::End();
	}
}


//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	if (!initialized) {
		initialized = true;
		{
		}
	}

	if (bOpen1) drawHelloWorld();

	//ImGui::ShowDemoWindowNodes(&bOpen0);
	if (bOpen2) 
	{
		// Canvas must be created after ImGui initializes, because constructor accesses ImGui style to configure default colors.
		static ImNodes::CanvasState canvas{};

		if (ImGui::Begin("rokups/ImNodes 2", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
		{
			// We probably need to keep some state, like positions of nodes/slots for rendering connections.
			ImNodes::BeginCanvas(&canvas);
			for (auto it = nodes.begin(); it != nodes.end();)
			{
				MyNode* node = *it;

				// Start rendering node
				if (ImNodes::Ez::BeginNode(node, node->Title, &node->Pos, &node->Selected))
				{
					// Render input nodes first (order is important)
					ImNodes::Ez::InputSlots(node->InputSlots.data(), node->InputSlots.size());

					// Custom node content may go here
					ImGui::Text("Content of %s", node->Title);

					// Render output nodes first (order is important)
					ImNodes::Ez::OutputSlots(node->OutputSlots.data(), node->OutputSlots.size());

					// Store new connections when they are created
					Connection new_connection;
					if (ImNodes::GetNewConnection(&new_connection.InputNode, &new_connection.InputSlot,
						&new_connection.OutputNode, &new_connection.OutputSlot))
					{
						((MyNode*)new_connection.InputNode)->Connections.push_back(new_connection);
						((MyNode*)new_connection.OutputNode)->Connections.push_back(new_connection);
					}

					// Render output connections of this node
					for (const Connection& connection : node->Connections)
					{
						// Node contains all it's connections (both from output and to input slots). This means that multiple
						// nodes will have same connection. We render only output connections and ensure that each connection
						// will be rendered once.
						if (connection.OutputNode != node)
							continue;

						if (!ImNodes::Connection(connection.InputNode, connection.InputSlot, connection.OutputNode,
							connection.OutputSlot))
						{
							// Remove deleted connections
							((MyNode*)connection.InputNode)->DeleteConnection(connection);
							((MyNode*)connection.OutputNode)->DeleteConnection(connection);
						}
					}
				}
				// Node rendering is done. This call will render node background based on size of content inside node.
				ImNodes::Ez::EndNode();

				if (node->Selected && ImGui::IsKeyPressedMap(ImGuiKey_Delete))
				{
					// Deletion order is critical: first we delete connections to us
					for (auto& connection : node->Connections)
					{
						if (connection.OutputNode == node)
						{
							((MyNode*)connection.InputNode)->DeleteConnection(connection);
						}
						else
						{
							((MyNode*)connection.OutputNode)->DeleteConnection(connection);
						}
					}
					// Then we delete our own connections, so we don't corrupt the list
					node->Connections.clear();

					delete node;
					it = nodes.erase(it);
				}
				else
					++it;
			}

			if (ImGui::IsMouseReleased(1) && ImGui::IsWindowHovered() && !ImGui::IsMouseDragging(1))
			{
				ImGui::FocusWindow(ImGui::GetCurrentWindow());
				ImGui::OpenPopup("NodesContextMenu");
			}

			if (ImGui::BeginPopup("NodesContextMenu"))
			{
				for (const auto& desc : available_nodes)
				{
					if (ImGui::MenuItem(desc.first.c_str()))
					{
						nodes.push_back(desc.second());
						ImNodes::AutoPositionNode(nodes.back());
					}
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Reset Zoom"))
					canvas.Zoom = 1;

				if (ImGui::IsAnyMouseDown() && !ImGui::IsWindowHovered())
					ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
			}

			ImNodes::EndCanvas();
		}
		ImGui::End();

	}
}

//--------------------------------------------------------------
void ofApp::exit() {
	{
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = 'a') {
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}