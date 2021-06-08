#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" // -> Adds all the add-on classes. You can also simplify picking what you want to use.

#include "ofxWindowApp.h" // -> not required

using namespace ofxSurfing;
//namespace ofxSurfing = ofxSurfing::ImGuiWidgetsTypesManager;

// TODO:
// auto-resize fails /gro bc widgets refresh is no working on group tree but on window begin
// nested group spacing fails
// should pass the refresh widtgets object.. or simplify

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();

		ofxSurfing_ImGui_Manager guiManager; 

		void drawWidgets();

		// parameters
		ofParameterGroup params;
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

		bool bCustom;

		ofxWindowApp windowApp;
};
