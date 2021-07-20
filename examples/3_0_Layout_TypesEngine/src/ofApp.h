
#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" // -> Adds all the add-on classes. You can also simplify picking what you want to use.

#include "ofxWindowApp.h" // not required


//#define IM_GUI_REFRESH_LOCAL // -> TODO: TEST
// refresh can be called onyl from here. not from helpers nor from layout


// NOTE:
// If you get some errors on compiling, could be related to some -not required- included files.
// Go to 'Solution Explorer' and remove manually from 'addons/ofxSurfingImGui/src/ImGui/' 
// /ImNodes/, /ImGuizmo/ !!


class ofApp : public ofBaseApp{

	public:

		void setup();
		void draw();

		void drawWindowMain();
		void drawWindow1();
		void drawWindow2();
		void drawMoreWidgets();

		// groups
		ofParameterGroup params1;
		ofParameterGroup params2;
		ofParameterGroup params3;
		// parameters
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
		ofParameter<float> separation3min;
		ofParameter<float> separation3max;
		ofParameter<float> speed3;
		ofParameter<int> shapeType3;

		//-

		bool bOpenMain;
		bool bOpen1;
		bool bOpen2;

		bool bReset1;
		bool bReset2;
		bool bReset3;

		glm::vec2 pos0;
		glm::vec2 pos1;
		glm::vec2 pos2;

		//-

		ofxSurfing_ImGui_Manager guiManager;

		// debug customize

		bool bCustom1;
		bool bCustom2;

		ofParameter<int> typeGroups;
		ofParameter<int> typeFlags;
		string flagInfo;

		//void SetupStyles();
		//void ClearStyles();

		//-

		ofxWindowApp windowApp;
};
