

#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "surfingConsole.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);
	void exit();

	ofxSurfingGui ui;
	ofParameter<bool> bGui{ "Test Console", true };

	// A custom data struct for testing.
	dataCustom* data = NULL;

	surfingConsole c = { 1 };

	void addToLog(string s);
};
