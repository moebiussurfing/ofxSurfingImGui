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
			ofxImGuiSurfing::ToggleRoundedButton("Show 0", &bOpen0);
			ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
			ofxImGuiSurfing::ToggleRoundedButton("Show 2", &bOpen2);
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

		if (ImGui::Begin("ImNodes", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
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
	
	if(bOpen1)drawHelloWorld();

	//ImGui::ShowDemoWindowNodes(&bOpen0);
	//ImGui::ShowDemoWindowNodes(NULL);
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