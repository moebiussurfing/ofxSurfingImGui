#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	ImGuiConfigFlags flags = ImGuiConfigFlags_DockingEnable;
	bool bRestore = true;
	bool bMouse = false;
	bool bAutoDraw = true;
	// NOTE: it seems that must be false when multiple ImGui instances created!

	gui.setup(nullptr, bAutoDraw, flags, bRestore, bMouse);

	//-

	// theme
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing();
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	setup_ImGui();
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	//// curve tensors
	//static float v[5] = { 0.50f, 0.020f, 0.95f, 0.35f };
	//// input
	//static int cycle = 120;
	////const int cycle = 120;
	//int frame = ofGetFrameNum() % cycle;
	//float i = ofMap(frame, 0, cycle, 0.0f, 1.0f);
	//// output
	//float o = ImGui::BezierValue(i, v); // x delta in [0..1] range

	//// draw
	//float hh = 30;
	//float y = ofGetHeight() - hh;
	//ofRectangle ro(0, y, ofGetWidth()* o, hh);
	//ofRectangle ri(ofGetWidth()* i, y-5, 5, hh+5);
	//ofPushStyle();
	//ofFill();
	//ofSetColor(ofColor(255, 255));
	//ofDrawRectangle(ro);
	//ofSetColor(ofColor(0, 255));
	//ofDrawRectangle(ri);
	//cout << "i:" << i << "  \t   o:" << o << endl;
	//ofPopStyle();

	gui.begin();
	{
		ImGui::Begin("Progress Indicators");

		const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
		const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

		ImGui::Spinner("##spinner", 15, 6, col);
		ImGui::BufferingBar("##buffer_bar", 0.7f, ImVec2(400, 6), bg, col);

		ImGui::Dummy(ImVec2(0, 30));
		ImGui::LoadingIndicatorCircle("loading", 40, ImVec4(1, 0, 0, 1), ImVec4(0, 1, 0, 1), 10, 5);

		//ImGui::Spinner2("label", 40, 5, col);


		ImGui::End();


		//static bool bOpen = true;;
		//auto mainSettings = ofxImGui::Settings();
		//ImGuiColorEditFlags _flagw;
		//string name;

		//_flagw = ImGuiWindowFlags_None;
		////if (bOpen) _flagw =| ImGuiWindowFlags_;

		////mainSettings.windowBlock = bOpen;
		//name = "Window";
		//if (ofxImGui::BeginWindow(name.c_str(), mainSettings, _flagw))
		//{			
		//	//ImGui::SliderInt("Cycle Duration", &cycle, 60, 60 * 5);
		//	//ImGui::Dummy(ImVec2(0, 10));
		//	//ImGui::Bezier("SurfingCurve", v);
		//}
		//ofxImGui::EndWindow(mainSettings);
	}
	gui.end();
}
