#pragma once
#include "ofMain.h"

/*

	This example shows a workflow for the docking mode
	(Here without the layout presets engine activated)
	Also to learn how the top menu is handled, with some automatic workflow,
		adding some windows visible toggles on there.
	Note that:
	- Layout is persistent.
	- We can reset layout to a default layout.
	- We can save current layout and recall. load/save
	- Menus are automatically filled with the special windows.

*/

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();
	void keyPressed(int key);

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

	ofParameter<bool> bGui { "APP", true };

	//--

	// Docking Helpers Stuff

	ofParameter<bool> bGui_DockingHelp { "DOCKING HELP", true };

	// To learning purposes
	// but also to be used as template for your projects.
	void updateImGuiDockingHelpers();
	void drawImGuiDockingHelp();

	// An extra window with some triggers
	// for hard-coded layout modifications.
	void doDockingReset(); // Reset the layout to a hard-coded default layout.

	// Flags
	bool bFlagDockingReset = false;

	//--

	// Manager to Save/Load Layout manually
	string path = "myLayout.ini";
};
