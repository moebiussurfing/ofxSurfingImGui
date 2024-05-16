#pragma once
#include "ofMain.h"

/*

	This example shows a workflow for the docking mode
	(Here without the layout presets engine activated)
	Also to learn how the top menu is handled, with some automatic workflows,
		adding some windows visibles toggles on there.

	- Layout is persistent.
	- We can reset layout to a default layout.
	- We can save/load the layout.
	- We can randomize the layout.
	- we can use the free zone / available viewport space to draw a 3d scene.
	- Menus are automatically filled with the special windows.

	TODO

	Add manual save/load layout. (we could use the imgui.ini or another file)
	Make some of these helpers internal to the GuiManger

*/


#include "ofxSurfingImGui.h"

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
	void drawImGuiApp();
	void drawImGuiSpecialWindows();
	void drawImGuiSpecialWindow0();
	void drawImGuiSpecialWindow1();
	void drawImGuiSpecialWindow2();
	void drawImGuiSpecialWindow3();
	void drawImGuiSpecialWindow4();

	ofParameter<bool> bGui{ "APP", true };

	//--

	// Docking Helpers Stuff

	// Mode/workflow 
	
#if 0
	// Can be configured:
	bool bModeDockingResetAtStartup = true;
	// false: the layout will be persistent and auto saved on exit and loaded on setup.
	// true: the layout will be reseted by code on each startup.
#endif

	ofParameter<bool> bGui_DockingHelp{ "DOCKING HELP", true };

	// To learning purposes 
	// but also to be used as template for your projects.
	void updateImGuiDockingHelpers();
	void drawImGuiDockingHelp();

	// An extra window with some triggers
	// for hard-coded layout modifications. 
	void doDockingReset(); // Reset the layout to a hard-coded default layout.
	void doDockingRandom(); // Random the layout.

	// Flags
	bool bFlagDockingReset = false;
	bool bFlagDockingRandom = false;

	//--

	// Manager to Save/Load Layout manually

	string path = "myLayout.ini";
	
	//--

	// Scene functions

	void updateScene(); // Generates random messages to test the Log window.
	void drawScene();// Draws a Central Rectangle getting from the docking layout.

	ofEasyCam cam;
};
