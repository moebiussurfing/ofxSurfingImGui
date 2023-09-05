
/*

	This is a WIP example to explore the workflow and debug how to combine multiple instances of ofxImGui
	inside an ofxSurfingImGui class who acts as a kind of manager.

*/


#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "myClassA.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofParameterGroup parameters;
	ofParameter<bool> bEnable1;
	ofParameter<void> bPrevious;
	ofParameter<void> bNext;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<int> amount;
	ofParameter<int> size;

	ofParameter<bool> bGui{ "my_ofApp", true };

	// Local ui object that will be shared to some of the instantiated classes
	// will populate local (ofApp) ofParams too.
	ofxSurfingGui ui;

	//--

	myClassA A;
};
