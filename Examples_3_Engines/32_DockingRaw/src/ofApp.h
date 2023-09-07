#pragma once
#include "ofMain.h"

/*

	This example show a docking mode
	(without the layout presets engine activated)

	- Layout is persistent.
	- We can reset layout to a default layout.
	- We can randomize the layout.


	TODO

	Fix handle persistence of bGui special windows states
	Add manual save/load 
		(we could use the imgui.ini or another file)
	Get center rectangle to draw a viewport.
	Make some of these helpers internal to the GuiManger

*/


#include "ofxSurfingImGui.h"

//#define SURFING_USE_MANAGER

class ofApp : public ofBaseApp
{
public:
	void setup();
	void setupParameters();
	void draw();
	void keyPressed(int key);

	//--

	// Scene Parameters
	ofParameterGroup params1;
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
	ofParameterGroup params2;
	ofParameter<int> shapeType2;
	ofParameter<int> amount2;
	ofParameter<int> size2;
	ofParameterGroup params3;
	ofParameter<float> lineWidth3;
	ofParameter<float> separation3;
	ofParameter<float> speed3;
	ofParameter<int> shapeType3;

	//--

	// Gui manager
	ofxSurfingGui ui;

	void setupImGui();
	void drawImGui();
	void drawImGuiSpecialWindows();

	ofParameter<bool> bGui{ "ofApp", true };

	//--

	// Docking Helpers Stuff

	// Mode/workflow Can be configured:
	bool bStartupDockingReset = false;
	// false: the layout will be persistent and auto saved on exit and loaded on setup.
	// true: the layout will be reseted on each startup.

	ofParameter<bool> bGui_DockingHelpers{ "myDockingHelpers", true };

	// To learning purposes 
	// but also to be used as template for your projects.
	void updateImGuiDockingHelpers();
	void drawImGuiDockingHelpers();

	// An extra window with some triggers
	// for hard-coded layout modifications. 
	void doDockingReset(); // Reset the layout to a hard-coded default layout.
	void doDockingRandom(); // Random the layout.

	// Flags
	bool bDockingReset = false;
	bool bDockingRandom = false;

	//--

	// Manager to Save/Load Layout manually
#ifdef SURFING_USE_MANAGER
	string path = "myLayout";
	bool bFlagLoadLayout = 0;
	bool bFlagSaveLayout = 0;
	
	//--------------------------------------------------------------
	void saveLayoutImGuiIni()
	{
		ImGui::SaveIniSettingsToDisk(ofToDataPath(path + ".ini", true).c_str());
	}

	//--------------------------------------------------------------
	void loadLayoutImGuiIni()
	{
		ImGui::LoadIniSettingsFromDisk(ofToDataPath(path + ".ini", true).c_str());
	}
#endif

	//--

	void updateScene(); // Generates random messages to test the Log window.
};
