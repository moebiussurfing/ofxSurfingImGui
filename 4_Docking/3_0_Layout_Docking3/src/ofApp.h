
#pragma once

// Some code taken from: https://github.com/Daandelange/ofxImGui/tree/master/example-dockingandviewports

//--------------------------------------------------------------


/*

OVERVIEW:

This example shows how to populate many ImGui windows from different scopes on the same viewport.
Uses different approaches: 
from ofApp, from an add-on/class, or with Surfing Layout tools as guiManager and special windows too
Also useful to check viewport modes, docking merging windows or autodraw modes.

HOW TO:

Press SPACE to add a new ImGui window
BAKSPACE to clear windows dynamically (fails. broken..)
Drag with SHIFT to dock a window.

*/


//--

// Enable only ONE of the modes to TESTING
// a local ImGui instance or internal to the classes
//#define TEST__LOCAL_IM_GUI // a.
#define TEST__MULTIINSTANCE_IM_GUI // b.

//--------------------------------------------------------------


#include "ofMain.h"

#include "ofxSurfingImGui.h"
//#include "ofxImGui.h"

#include "myAddon.h"

#include "ofxWindowApp.h" // not required

class ofApp : public ofBaseApp {

public:

	void setup();
	void exit();
	void draw();
	void keyPressed(int key);

	// parameters
	// groups
	ofParameterGroup params1;
	ofParameterGroup params3;
	ofParameterGroup params2;
	ofParameter<bool> bEnable;
	ofParameter<int> shapeType;
	ofParameter<bool> bPrevious;
	ofParameter<bool> bNext;
	ofParameter<bool> bMode1;
	ofParameter<bool> bMode2;
	ofParameter<bool> bMode3;
	ofParameter<bool> bMode4;
	ofParameter<bool> bModeA;
	ofParameter<bool> bModeB;
	ofParameter<bool> bModeC;
	ofParameter<bool> bModeD;
	ofParameter<float> line1;
	ofParameter<float> separation1;
	ofParameter<float> speed1;
	ofParameter<int> amount1;
	ofParameter<int> size1;
	ofParameter<float> line2;
	ofParameter<float> sep2min;
	ofParameter<float> sep2max;
	ofParameter<float> speed2;
	ofParameter<int> shape3;
	ofParameter<int> amount3;
	ofParameter<int> size3;

	void setupParams();

	//-

	// different approaches:

	// A. -> ofxImGui
	ofxImGui::Gui gui;

	// B. -> SurfingImGui
	ofxSurfing_ImGui_Manager guiManager;

	// C. -> ofxImGui class/add-on
	myAddon guiInstance;

	// D. -> ofxImGui class vector
	vector<myAddon*> guiInstances;

	void addImGuiWindow();
	void clearImGuiWindows();
	bool bFlagClear = false;

	void setupImGuiManager();
	void drawImGui();
	void drawImGuiGroup();

	void setupImGuiSpecialWindows();
	void drawImGuiSpecialWindows();

	void setupDocking();

	//-

private:

	//--------------------------------------------------------------
	void drawWindow(const char* _title, int& _value, int _x = 300, int _y = 300, ImGuiWindowFlags _flags = ImGuiWindowFlags_None)
	{
		ImGuiCond cond = ImGuiCond_FirstUseEver;

		ImGui::SetNextWindowSize(ImVec2(200, 200), cond);
		ImGui::SetNextWindowPos(ImVec2(_x + ofGetWindowPositionX(), _y + ofGetWindowPositionY()), cond);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 255, 255, 128)); // This styles the special windows

		ImGui::Begin(_title, NULL, _flags);
		ImGui::Text("ofxImGui");
		ImGui::InputInt("InputInt", &_value);
		ImGui::SliderInt("SliderInt", &_value, 0, 10);
		ImGui::DragInt("DragInt", &_value);
		ImGui::End();

		ImGui::PopStyleColor(1);
	}

	//-

	ofxWindowApp windowApp;
};
