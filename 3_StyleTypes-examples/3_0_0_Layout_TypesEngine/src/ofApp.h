
#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
using namespace ofxImGuiSurfing;

#include "ofxWindowApp.h" // not required

class ofApp : public ofBaseApp {

public:

	void setup();
	void draw();
	void exit();
	void drawImGui();
	void drawImGuiGroup();

	// groups
	ofParameterGroup params1;
	ofParameterGroup params3;
	ofParameterGroup params2;

	// parameters
	ofParameter<bool> bEnable;
	ofParameter<int> shapeType;
	ofParameter<bool> bPrevious;
	ofParameter<bool> bNext;
	ofParameter<bool> bMode1;
	ofParameter<bool> bMode2;
	ofParameter<bool> bMode3;
	ofParameter<bool> bMode4;
	ofParameter<bool> bModeA;
	ofParameter<bool> bModeB;
	ofParameter<bool> bModeC;
	ofParameter<bool> bModeD;
	ofParameter<float> line1;
	ofParameter<float> separation1;
	ofParameter<float> speed1;
	ofParameter<int> amount1;
	ofParameter<int> size1;
	ofParameter<float> line2;
	ofParameter<float> sep2min;
	ofParameter<float> sep2max;
	ofParameter<float> speed2;
	ofParameter<int> shape3;
	ofParameter<int> amount3;
	ofParameter<int> size3;

	//-

	ofxSurfing_ImGui_Manager guiManager;

	//-

	// customize groups
	bool bCustom;

	void setupCustomizators();
	
	ofParameter<int> typeGroup1;
	ofParameter<int> typeGroup2;
	ofParameter<int> typeGroup3;

	ofParameter<int> typeFlags1;
	ofParameter<int> typeFlags2;
	ofParameter<int> typeFlags3;
	
	ofParameterGroup paramsSettings;

	void Changed_Params(ofAbstractParameter &e);

	ImGuiTreeNodeFlags flags_typeFlags1 = ImGuiTreeNodeFlags_None;
	ImGuiTreeNodeFlags flags_typeFlags2 = ImGuiTreeNodeFlags_None;
	ImGuiTreeNodeFlags flags_typeFlags3 = ImGuiTreeNodeFlags_None;
	
	string flagInfo1;
	string flagInfo2;
	string flagInfo3;

	void refreshFlag(int indexType, ImGuiTreeNodeFlags &flag, std::string &flagInfo);

	// add styles
	void setupStyles();
	void clearStyles();
	void resetStyles();
	
	//-

	ofxWindowApp windowApp;
};
