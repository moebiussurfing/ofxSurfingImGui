
#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" // -> Adds all the add-on classes. You can also simplify picking what you want to use.
using namespace ofxImGuiSurfing;

#include "ofxWindowApp.h" // not required

//#define IM_GUI_REFRESH_LOCAL // -> TODO: TEST
// refresh can be called onyl from here. not from helpers nor from layout


// NOTE:
// If you get some errors on compiling, could be related to some -not required- included files.
// Go to 'Solution Explorer' and remove manually from 'addons/ofxSurfingImGui/src/ImGui/' 
// /ImNodes/
// /ImGuizmo/ !!


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
		ofParameterGroup params3;
		ofParameterGroup params2;

		// parameters
		ofParameter<bool> bEnable;
		ofParameter<int> shapeType;
		ofParameter<bool> bPrevious; // to use as button. kind of void type
		ofParameter<bool> bNext; // to use as button. kind of void type
		ofParameter<bool> bMode1;
		ofParameter<bool> bMode2;
		ofParameter<bool> bMode3;
		ofParameter<bool> bMode4;
		ofParameter<bool> bModeA;
		ofParameter<bool> bModeB;
		ofParameter<bool> bModeC;
		ofParameter<bool> bModeD;
		ofParameter<float> lineWidth1;
		ofParameter<float> separation1;
		ofParameter<float> speed1;
		ofParameter<int> amount1;
		ofParameter<int> size1;
		ofParameter<float> lineWidth2;
		ofParameter<float> separation2min;
		ofParameter<float> separation2max;
		ofParameter<float> speed2;
		ofParameter<int> shapeType3;
		ofParameter<int> amount3;
		ofParameter<int> size3;

		//-

		bool bOpenMain;
		bool bOpen1;
		bool bOpen2;

		bool bReset1;
		bool bReset2;
		bool bReset3;
#define MAX_WINDOW_HEIGHT 950

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
		ImGuiTreeNodeFlags flags_typeFlags = ImGuiTreeNodeFlags_None;
		string flagInfo;

		void SetupStyles();
		void ClearStyles();

		//-

		ofxWindowApp windowApp;
};
