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

*/

// Uncomment/enable this line
// to show the minimal expression of a simple docking workflow.
// without the reset and save/load methods.

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
