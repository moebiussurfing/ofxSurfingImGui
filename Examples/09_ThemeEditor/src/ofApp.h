#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "surfingThemeEditor.h"

#define TEST_CUSTOM_FONTS 0

//--

class ofApp : public ofBaseApp
{
public:
		void setup();
		void draw();
		void drawWindowMain(); 
		void exit();
			
		ofxSurfingGui ui; 
		ofParameter<bool> bGui;		
		SurfingThemeEditor e;

		//--

		//TODO:
#if(TEST_CUSTOM_FONTS==1) 
		void setupFonts();
		void drawWindowStylizedFonts(); 
		bool bOpenWindowStylizedFonts = 0;
		bool bStyleFonts = false; 
		ofParameter<int> fontSize;
		ofParameter<int> fontIndex;
		ofParameter<bool> bEnable;
		ofParameter<int> amount;
		string s;
		string txt = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";
#endif
};
