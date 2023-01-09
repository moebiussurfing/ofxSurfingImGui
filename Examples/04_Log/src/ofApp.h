#pragma once


/*

	This example shows how to use the logging system.

	TODO

	check if intuitive direction
	add filter serach from ImGui Demo

	Try and merge
	Colored log
	https://github.com/ocornut/imgui/issues/5796
	https://github.com/ocornut/imgui/issues/5796#issuecomment-1288128069

*/



#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:

	void setup();
	void draw();
	void exit();

	void setupParams();

	ofParameter<bool> bEnable;
	ofParameter<void> bPrevious;
	ofParameter<void> bNext;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> amount;

	ofParameterGroup params;
	void Changed_Params(ofAbstractParameter& e);

	ofxSurfingGui ui;
	void setupImGui();
	void drawImGui();

	void udpateScene(); // -> Generates random variations to animate variables.
	void updateLog(); // -> Generates random messages to test the Log window.
};
