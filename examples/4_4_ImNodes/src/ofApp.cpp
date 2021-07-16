#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(-1920, 25);
	guiManager.setImGuiAutodraw(true);
	guiManager.setup();

	ImNodes::CreateContext();

	if (bInit) {
		bInit = false;
		ImNodes::SetNodeGridSpacePos(1, ImVec2(200.0f, 200.0f));
	}
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Panels", &bOpen0, window_flags);
		{
			//// round toggles widgets
			ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
			//ofxImGuiSurfing::ToggleRoundedButton("Show 2", &bOpen2);
			//ImGui::Dummy(ImVec2(0, 10)); // spacing

			//-

			//ImGui::Dummy(ImVec2(0, 5)); // spacing
			//ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);// a public bool variable to allow handle auto-resize. Applied here to all the windows.
		}
		ImGui::End();

		//-

		drawWidgets();
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	if (bInit) {
		bInit = false;
		ImNodes::SetNodeGridSpacePos(1, ImVec2(200.0f, 200.0f));
	}

	{
		ImGui::Begin("simple node editor");

		ImNodes::BeginNodeEditor();
		ImNodes::BeginNode(1);

		ImNodes::BeginNodeTitleBar();
		ImGui::TextUnformatted("simple node :)");
		ImNodes::EndNodeTitleBar();

		ImNodes::BeginInputAttribute(2);
		ImGui::Text("input");
		ImNodes::EndInputAttribute();

		ImNodes::BeginOutputAttribute(3);
		ImGui::Indent(40);
		ImGui::Text("output");
		ImNodes::EndOutputAttribute();

		ImNodes::EndNode();
		ImNodes::EndNodeEditor();

		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = ' ') {
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
