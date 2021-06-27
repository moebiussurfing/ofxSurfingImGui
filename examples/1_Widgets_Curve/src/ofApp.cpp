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

	// parameters
	params.setName("paramsGroup");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable1.set("Enable1", false));
	params.add(bEnable2.set("Enable2", false));
	params.add(bEnable3.set("Enable3", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params2.add(params3);
	params.add(params2);
}

//--------------------------------------------------------------
void ofApp::draw() {

	const int cycle = 120;
	int frame = ofGetFrameNum() % cycle;
	float f = ofMap(frame, 0, cycle, 0.0f, 1.0f);
	// tensors
	static float v[5] = { 0.50f, 0.020f, 0.95f, 0.35f };
	float y = ImGui::BezierValue(f, v); // x delta in [0..1] range
	float hh = 30;
	float h = ofGetHeight() - hh;
	ofRectangle r(0, h, ofGetWidth()* y, hh);
	ofFill();
	ofColor(255);
	ofDrawRectangle(r);
	cout << "v:" << v << "  \t   y:" << y << endl;

	gui.begin();
	{
		static bool bOpen = true;;
		auto mainSettings = ofxImGui::Settings();
		ImGuiColorEditFlags _flagw;
		string name;

		_flagw = ImGuiWindowFlags_None;
		//if (bOpen) _flagw =| ImGuiWindowFlags_;

		name = "Window";
		if (ofxImGui::BeginWindow(name.c_str(), mainSettings, _flagw, &bOpen))
		{
			//ImGui::ShowBezierDemo();

			//static float v[5] = { 0.50f, 0.020f, 0.95f, 0.35f }; 
			ImGui::Bezier("SurfingCurve", v);
		}
		ofxImGui::EndWindow(mainSettings);
	}
	gui.end();
}
