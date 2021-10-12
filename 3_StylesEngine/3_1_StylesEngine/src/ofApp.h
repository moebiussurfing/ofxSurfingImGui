
#pragma once

#include "ofMain.h"


/*

	This example shows many different approaches
	to render ofParams widgets and ImGui windows.
	From Raw to Styled Engine ways.
	Maybe too many text to fast understanding...
	Maybe I should remove this example and to include the more simple stuff.

*/


#include "ofxSurfingImGui.h" 

#include "ofxWindowApp.h" // Not required

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
		void exit();

		void drawWindowMain();
		void drawWindow1();
		void drawWindow2();
		void drawMoreWidgets();

		// Groups
		ofParameterGroup params1;
		ofParameterGroup params2;
		ofParameterGroup params3;

		// Parameters
		ofParameter<bool> bEnable;
		ofParameter<int> shapeType;
		ofParameter<bool> bPrevious; // To use as button. kind of void type
		ofParameter<bool> bNext; // To use as button. kind of void type
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

		ofxSurfing_ImGui_Manager guiManager;

		//-

		// Windows and states controls

		bool bOpenMain;

		// To position layout
#define MAX_WINDOW_HEIGHT 950
		bool bReset0;
		bool bReset1;
		bool bReset2;
		glm::vec2 pos0;
		glm::vec2 pos1;
		glm::vec2 pos2;

		//-
		
		ofParameter<bool> bOpen1{ "Window 1", true }; // This bool will be used to name the window and to toggle if visible too
		ofParameter<bool> bOpen2{ "Window 2", false };
		ofParameter<bool> bCustom1{ "bCustom1", false };
		ofParameter<bool> bCustom2{ "bCustom2", false };
		ofParameter<bool> bCustomGroups{ "bCustomGroups", false };

		//-
		
		// Styles
		void SetupStyles();
		void ClearStyles();

		// Debug customize
		ofParameter<int> typeGroups;
		ofParameter<int> typeFlags;
		ImGuiTreeNodeFlags flags_typeFlags = ImGuiTreeNodeFlags_None;
		std::string flagInfo;

		//-

		// Settings
		string path_AppSettings = "AppSettings.xml";
		ofParameterGroup params_AppSettings{ "AppSettings" };

		// Window
		ofxWindowApp windowApp;
};
