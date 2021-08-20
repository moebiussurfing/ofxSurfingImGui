#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"	// -> Add all classes. You can also simplify picking what you want to use.
// Now you can use the included ofxSurfing_ImGui_Helpers.h to improve the handling of ofParameters.
// NOTE: Inside the header file, there's some snippets and tutorials than you can use to learn or to use by yourself.

//-

class ofApp : public ofBaseApp{

public:
		void setup();
		void draw();
			
		//-
		
		ofxSurfing_ImGui_Manager guiManager; // In MODE A ofxGui will be instatiated inside the class
		// then you can simplify the ofxImGui setup procces and:
		// - initialize ofxImGui 
		// - speed up creation of windows and trees
		// Also you use the ofxSurfing_ImGui_WidgetsTypes.h aka Types Engine Manager. 
		// this class helps to populate responsive layouts or to define wich widget type to draw a typed parameter.
		// then you can draw a float ofParameter as a slider, drag number or +/- stepped buttons.
		// * hide a parameter of a group
		// * define to draw in same line next param
		// * define to add vertical spacing after the parameter

		// MODE B
		//ofxImGui::Gui gui; // can be instantiated outside the class (locally to maybe share with other classes)

		//-
		
		void drawMainWindow(); // -> a panel window with widgets
		void drawWindow1(); // -> a panel window with widgets
		void drawWindow2(); // -> a panel window with widgets
		void drawWindow3(); // -> a panel window with widgets

		void drawWidgets(); // -> some widgets
		
		bool bOpen0 = true;
		bool bOpen1 = false;
		bool bOpen2 = true;
		bool bOpen3 = false;
		bool bOpenStyleEditor = false;

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
