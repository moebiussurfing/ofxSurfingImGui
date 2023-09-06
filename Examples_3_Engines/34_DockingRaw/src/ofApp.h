#pragma once
#include "ofMain.h"

/*

	TODO

	fix handle persistence of bGui special windows states


*/


#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);

	//-

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

	ofParameter<bool> bGui{ "ofApp", true};

	//--

	// Docking Stuff

	// To learning purposes 
	// but also to be used as template for your projects.
	void updateImGuiDockingHelpers();
	void drawImGuiDockingHelpers();
	ofParameter<bool> bGui_DockingHelpers{ "myDockingHelpers", false };

	// An extra window with some triggers
	// for hard-coded layout modifications. 
	void doDockingReset(); // Reset the layout to a hard-coded default layout.
	void doDockingRandom(); // Random the layout.

	bool bDockingReset = false;
	bool bDockingRandom = false;

	//--

	void updateScene(); // Generates random messages to test the Log window.
};
