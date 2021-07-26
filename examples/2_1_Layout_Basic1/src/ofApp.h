#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp{

public:
		void setup();
		void draw();
			
		ofxSurfing_ImGui_Manager guiManager; 

		void drawWidgets();
		void drawMainWindow();

		bool bOpen0 = true;
		bool bOpen1 = true;
		bool bAutoResize = true;

		//--

		// ofParameters
		
		// groups
		ofParameterGroup params2;
		ofParameterGroup params1;
		ofParameterGroup params3;

		// params
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
};
