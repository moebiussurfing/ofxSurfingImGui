#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp{

public:
		void setup();
		void draw();
			
		ofxSurfing_ImGui_Manager guiManager; 

		// debug ImGui flags
		ofParameter<int> typeGroups;
		ofParameter<int> typeFlags;
		string flagInfo;

		void drawWidgets(); // -> populate some widgets from ofParameters
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
		ofParameter<int> shapeType2;
		ofParameter<int> amount2;
		ofParameter<int> size2;
		ofParameter<float> lineWidth3;
		ofParameter<float> separation3;
		ofParameter<float> speed3;
		ofParameter<int> shapeType3;
};
