#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" // -> Adds all the add-on classes. You can also simplify picking what you want to use.

#include "ofxWindowApp.h" // not required

// Remove ImNodes, ImGuizmo folder from Solution Explorer

class ofApp : public ofBaseApp{

	public:

		void setup();
		void draw();

		ofxSurfing_ImGui_Manager guiManager; 

		void drawWindowMain();
		void drawWindow1();
		void drawWindow2();
		void drawMoreWidgets();

		// parameters
		
		ofParameterGroup params1;
		ofParameterGroup params2;
		ofParameterGroup params3;

		ofParameter<bool> bEnable;
		ofParameter<bool> bPrevious;//to use as button. kind of void type
		ofParameter<bool> bNext;//to use as button. kind of void type
		ofParameter<bool> bMode1;
		ofParameter<bool> bMode2;
		ofParameter<bool> bMode3;
		ofParameter<bool> bMode4;
		ofParameter<bool> bModeA;
		ofParameter<bool> bModeB;
		ofParameter<bool> bModeC;
		ofParameter<bool> bModeD;
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

		// debug
		bool bCustom1;
		bool bCustom2;

		bool bOpenMain;
		bool bOpen1;
		bool bOpen2;

		bool bReset1;
		bool bReset2;
		bool bReset3;

		glm::vec2 pos0;
		glm::vec2 pos1;
		glm::vec2 pos2;

		ofxWindowApp windowApp;

		// debug ImGui flags
		ofParameter<int> typeGroups;
		ofParameter<int> typeFlags;
		string flagInfo;
};
