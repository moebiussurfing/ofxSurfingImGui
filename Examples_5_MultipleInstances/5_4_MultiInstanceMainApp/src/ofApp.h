
/*

	This is a WIP example to explore the workflow
	of how to combine multiple instances of ImGui/ofxImGui
	inside an ofxSurfingImGui class, who acts as a kind of manager.

	- Here we will see a pattern for separating the ui from the main ofApp class.
	We will use an instance of an 'unique_ptr<Gui>'

	- We will have also an instantiated myClassA object.
	This class will own an instance of ofxSurfingGui / UI Manager.

*/


#pragma once
#include "ofMain.h"

#include "mySurfingAppGui.h"
using namespace mySurfingApp;

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

	unique_ptr<Gui> gui = nullptr;
};
