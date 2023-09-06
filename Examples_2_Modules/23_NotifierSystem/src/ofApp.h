#pragma once

//--

/*

	This example shows how to use the Notifier system.
	Most settings are customizable.
	
	Also will show the Log system together.

*/


//--

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "surfingSceneTesters.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void exit();
	void keyPressed(int key);

	void setupParams();

	ofParameter<bool> bAnimate;
	ofParameter<float> speed;
	ofParameter<int> amountPauses;
	ofParameter<float> separation;

	ofParameterGroup params;
	void Changed_Params(ofAbstractParameter& e);

	ofxSurfingGui ui;
	void setupImGui();
	void drawImGui();

	// Generates random variations to animate variables.
	void updateLog(); 

	void AddNotifyLog(string text, string nameTag);
	void AddNotifyLog(string text, ofLogLevel level = OF_LOG_NOTICE);

	void doRandomNotifyLog();
};
