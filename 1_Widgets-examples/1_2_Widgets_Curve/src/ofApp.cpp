#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	ImGuiConfigFlags flags = ImGuiConfigFlags_DockingEnable;
	bool bRestore = true;
	bool bMouse = false;
	bool bAutoDraw = true;
	// NOTE: it seems that must be false when multiple ImGui instances created!

	gui.setImGuiAutodraw(true);
	gui.setup();

	//-

	// theme
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing();
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	setup_ImGui();

	surfingCurve.setup(value);
}

////--------------------------------------------------------------
//void ofApp::draw() {
//	
//	// curve tensors
//	static float v[5] = { 0.50f, 0.020f, 0.95f, 0.35f };
//	// input
//	static int cycle = 120;
//	//const int cycle = 120;
//	int frame = ofGetFrameNum() % cycle;
//	float i = ofMap(frame, 0, cycle, 0.0f, 1.0f);
//	// output
//	float o = ImGui::BezierValue(i, v); // x delta in [0..1] range
//
//	// draw
//	float hh = 30;
//	float y = ofGetHeight() - hh;
//	ofRectangle ro(0, y, ofGetWidth()* o, hh);
//	ofRectangle ri(ofGetWidth()* i, y-5, 5, hh+5);
//	ofPushStyle();
//	ofFill();
//	ofSetColor(ofColor(255, 255));
//	ofDrawRectangle(ro);
//	ofSetColor(ofColor(0, 255));
//	ofDrawRectangle(ri);
//	cout << "i:" << i << "  \t   o:" << o << endl;
//	ofPopStyle();
//
//	gui.begin();
//	{
//		static bool bOpen = true;;
//		auto mainSettings = ofxImGui::Settings();
//		ImGuiColorEditFlags _flagw;
//		string name;
//
//		_flagw = ImGuiWindowFlags_None;
//		//if (bOpen) _flagw =| ImGuiWindowFlags_;
//
//		//mainSettings.windowBlock = bOpen;
//		name = "Window";
//		if (ofxImGui::BeginWindow(name.c_str(), mainSettings, _flagw))
//		{
//			ImGui::SliderInt("Cycle Duration", &cycle, 60, 60 * 5);
//			ImGui::Dummy(ImVec2(0, 10));
//			ImGui::Bezier("SurfingCurve", v);
//
//			//--
//
//			ImGui::Dummy(ImVec2(0, 50));
//
//			surfingCurve.draw();
//
//		}
//		ofxImGui::EndWindow(mainSettings);
//	}
//	gui.end();
//}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(24);

	float i = surfingCurve.gerPercent();
	float o = surfingCurve.gerValue();

	// draw
	int pad = 5;
	float hh = 30;
	float y = ofGetHeight() - 2 * (hh + pad);
	ofRectangle ri(pad, y, ofGetWidth() * i - 2 * pad, hh);
	ofRectangle ro(pad, y + hh + 1, ofGetWidth() * o - 2 * pad, hh);

	ofPushStyle();
	ofFill();
	ofSetColor(ofColor(255, 255));
	ofDrawRectangle(ro);
	ofDrawRectangle(ri);
	ofPopStyle();

	//cout << "i:" << i << "  \t   o:" << o << endl;

	gui.begin();
	{
		static bool bOpen = true;;
		auto mainSettings = ofxImGui::Settings();
		ImGuiColorEditFlags _flagw;
		string name;

		_flagw = ImGuiWindowFlags_None;

		name = "Window";
		gui.beginWindow(name.c_str(), &bOpen, _flagw);
		//if (ImGui::Begin(name.c_str(), &bOpen, _flagw))
		{
			surfingCurve.draw();
		}
		//ImGui::End();
		gui.endWindow();
	}
	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ')surfingCurve.start();
}
