#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

/*

ABOUT THIS EXAMPLE:
This is a kind of helper to edit your own themes.

IMPORTANT:
Must remove /ofxSurfingImGui/ImGui/node folder from the project!

*/

//-

class ofApp : public ofBaseApp{

public:
		void setup();
		void setupFonts();
		void draw();
			
		//-
		
		ofxSurfing_ImGui_Manager guiManager; 

		//-
		
		void drawMainWindow(); // -> a panel window with widgets
		void drawWindow1(); // -> a panel window with widgets

		bool bOpen0 = true;
		bool bOpen1 = true;
		bool bStyleFonts = false;
		bool show_app_style_editor = true;

		ofParameter<int> fontSize;
		ofParameter<int> fontIndex;

		//-

		// ofParameters

		ofParameterGroup params1;
		ofParameterGroup params2;
		ofParameterGroup params3;

		ofParameter<bool> b1{ "b1", false };
		ofParameter<bool> b2{ "b2", false };
		ofParameter<bool> b3{ "b3", false };
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
		ofParameter<int> shapeType2;
		ofParameter<int> amount2;
		ofParameter<int> size2;
		ofParameter<float> lineWidth3;
		ofParameter<float> separation3;
		ofParameter<float> speed3;
		ofParameter<int> shapeType3;
};
