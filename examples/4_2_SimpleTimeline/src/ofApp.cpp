#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(-1920, 25);
	guiManager.setImGuiAutodraw(true);
	guiManager.setup();

	//sequencer.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (bPlay) {
		//sequencer.nextFrame();
		//sequencer.setFrame(int frame);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		drawWidgets();
		drawTimeline();
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Panels", &bOpen0, window_flags);
		{

			// round toggles widgets
			ofxImGuiSurfing::ToggleRoundedButton("Show Timeline", &bOpen1);
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 2", &bOpen2);

			ImGui::Dummy(ImVec2(0, 5)); // spacing

			ofxImGuiSurfing::ToggleRoundedButton("PLAY", &bPlay);

			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);// a public bool variable to allow handle auto-resize. Applied here to all the windows.
		}
		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::drawTimeline()
{
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		//if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Timeline", &bOpen1, window_flags);
		{
			//sequencer.draw();

			// alternative color picker
			static float color[4];
			ImGui::ColorPicker(color, false);
			ImGui::Dummy(ImVec2(0, 20)); // spacing

			// simple timeline
			bool b = ImGui::BeginTimeline("Timeline", 1.0);
			static float position[]{ 0.25f, 0.75f };
			static float scale[]{ 0.1f, 0.9f };
			ImGui::TimelineEvent("Position", position);
			ImGui::TimelineEvent("Scale", scale);
			ImGui::EndTimeline();

			//ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);// a public bool variable to allow handle auto-resize. Applied here to all the windows.
		}
		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = ' ') { bPlay = !bPlay; }
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
