#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "ofxWindowApp.h" // -> Not required

/*

Docking features is a bit WIP yet!
Some zones are not allowed or not memorized..

*/


class ofApp : public ofBaseApp
{

public:

	//-

	void setup();
	void draw();

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

	//-

	// The Gui Manager !
	ofxSurfing_ImGui_Manager guiManager;

	void setupImGui();
	void drawImGui();
	void drawImGuiWindows();

	ofParameter<bool> bGui_Docking{ "ofApp Docking", false };

	//-

	// Docking Stuff

	// To learning purposes but also to be used as template for your projects.
	void updateImGuiDockingHelper();
	void drawImGuiDockingHelper();

	// An extra window with some triggers
	// for hard-coded layout modifications. 
	void doDockingReset(); // Reset the layout to a hard-coded default layout.
	void doDockingRandom(); // Random the layout.
	bool bDockingReset = false;
	bool bDockingRandom = false;

	//-

	void updateScene(); // Generates random messages to test the Log window.

	ofxWindowApp windowApp;
};
