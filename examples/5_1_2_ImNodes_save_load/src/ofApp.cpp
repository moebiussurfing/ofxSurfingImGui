#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetWindowPosition(-1920, 25);

	guiManager.setImGuiAutodraw(true);
	guiManager.setup();

	ImNodes::CreateContext();
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

		//-
		
		//ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		//if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		//ImGui::Begin("Panels", &bOpen0, window_flags);
		//{
		//	ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
		//}
		//ImGui::End();
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	if (!initialized) {
		initialized = true;
		{
			ImNodes::GetIO().LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
			ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);
			editor.load();
		}
	}

	editor.show();
}

//--------------------------------------------------------------
void ofApp::exit() {
	//example::NodeEditorShutdown();
	{
		ImNodes::PopAttributeFlag();
		editor.save();

		ImNodes::DestroyContext();
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