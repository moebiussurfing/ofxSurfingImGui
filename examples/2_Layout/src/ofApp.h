#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"


/*

NOTE:
Set if (1) to the window you want to draw/test

*/


using namespace ofxSurfing;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();

		ofxImGui::Gui gui; // can be instantiated outside the class
		ofxSurfing_ImGui_LayoutManager guiManager; // or gui will be instatiated inside the class

		void drawWidgets();

		// parameters
		ofParameterGroup params;
		ofParameter<bool> bEnable;
		ofParameter<bool> bPrevious;
		ofParameter<bool> bMode1;
		ofParameter<bool> bMode2;
		ofParameter<bool> bMode3;
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
};
