#pragma once
#include "ofMain.h"

/*

	This example shows a workflow for the docking mode
	(Here without the layout presets engine activated)
	Also to learn how the top menu is handled, with some automatic workflow,
		adding some windows visible toggles on there.
	Note that:
	- Layout is persistent on exit and startup app.
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
};
