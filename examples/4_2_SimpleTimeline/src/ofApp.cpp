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
	if (bOpen1)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		//if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Timeline", &bOpen1, window_flags);
		{
			//sequencer.draw();

			//// alternative color picker
			//static float color[4];
			//ImGui::ColorPicker(color, false);

			//ImGui::Dummy(ImVec2(0, 20)); // spacing

			// simple timeline
			static double time_in = 0;
			static double time_out = 1;

			float pixel_offset = 0;
			float max_value = 1.0f;
			int num_visible_rows = 4;

			bool b = ImGui::BeginTimeline("Timeline", pixel_offset, max_value, num_visible_rows);
			static double position[]{ 0.25f, 0.75f };
			static double scale[]{ 0.1f, 0.9f };
			ImGui::TimelineEvent("Position", position[0], position[1] );
			ImGui::TimelineEvent("Scale", scale[0], scale[1]);
			ImGui::EndTimeline(5, time_in, time_out);

			//// simple timeline
			//bool b = ImGui::BeginTimeline("Timeline", 1.0);
			//static float position[]{ 0.25f, 0.75f };
			//static float scale[]{ 0.1f, 0.9f };
			//ImGui::TimelineEvent("Position", position);
			//ImGui::TimelineEvent("Scale", scale);
			//ImGui::EndTimeline();

			//ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);// a public bool variable to allow handle auto-resize. Applied here to all the windows.


			//// simple timeline
			//bool b = ImGuiSurfing::BeginTimeline2("Timeline", 1.0);
			//static float position[]{ 0.25f, 0.75f };
			//static float scale[]{ 0.1f, 0.9f };
			//ImGuiSurfing::TimelineEvent2("Position", position);
			//ImGuiSurfing::TimelineEvent2("Scale", scale);
			//ImGuiSurfing::EndTimeline2(5);

			//	if (ImGuiSurfing::BeginTimeline("MyTimeline", 50.f, 4, 6))  // label, max_value, num_visible_rows, opt_exact_num_rows (for item culling)
			//	{
			//		static float events[12] = { 10.f,20.f,0.5f,30.f,40.f,50.f,20.f,40.f,15.f,22.5f,35.f,45.f };
			//		if (ImGui::TimelineEvent("Event1", &events[0])) {/*events[0] and/or events[1] modified*/ }
			//		ImGuiSurfing::TimelineEvent("Event2", &events[2]);
			//		ImGuiSurfing::TimelineEvent("Event3", &events[4], true);    // Event3 can only be shifted
			//		ImGuiSurfing::TimelineEvent("Event4", &events[6]);
			//		ImGuiSurfing::TimelineEvent("Event5", &events[8]);
			//		ImGuiSurfing::TimelineEvent("Event6", &events[10]);
			//	}
			//const float elapsedTime = (float)(((unsigned)(ImGui::GetTime() * 1000)) % 50000) / 1000.f;    // So that it's always in [0,50]
			//ImGuiSurfing::EndTimeline(5, elapsedTime);  // num_vertical_grid_lines, current_time (optional), timeline_running_color (optional)

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
