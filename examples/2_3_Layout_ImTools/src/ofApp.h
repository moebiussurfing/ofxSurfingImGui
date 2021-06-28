#pragma once

#include "ofMain.h"

#include "ofxImGui.h"	

#include "ofxSurfingImGui.h"	// -> Add all classes. You can also simplify picking what you want to use.
// Now you can use the included ofxSurfing_ImGui_Helpers.h to improve the handling of ofParameters.

#include "ofxWindowApp.h" // -> not required

#include "App_LayoutManager/Surfing_ImTools.h"	

class ofApp : public ofBaseApp {

public:
	App_LayoutManager app_LayoutManager;

	void setup();
	void draw();
	void exit();

	//-

	ofxSurfing_ImGui_Manager guiManager; // In MODE A ofxGui will be instatiated inside the class
	// MODE B
	//ofxImGui::Gui gui; // can be instantiated outside the class (locally to maybe share with other classes)

	//void drawWidgets();

	//-

	// parameters
	ofParameterGroup params1;
	ofParameter<bool> bEnable;
	ofParameter<bool> bPrevious;
	ofParameter<bool> bMode1;
	ofParameter<bool> bMode2;
	ofParameter<bool> bMode3;
	ofParameter<bool> bMode4;
	ofParameter<bool> bNext;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> shapeType;
	ofParameter<int> amount;
	ofParameter<int> size;

	ofParameterGroup params2;
	ofParameter<int> shapeType2;
	ofParameter<int> amount2;
	ofParameter<int> size2;
	
	ofParameterGroup params3;
	ofParameter<float> lineWidth3;
	ofParameter<float> separation3;
	ofParameter<float> speed3;
	ofParameter<int> shapeType3;

	//-

	ofxWindowApp windowApp;
};