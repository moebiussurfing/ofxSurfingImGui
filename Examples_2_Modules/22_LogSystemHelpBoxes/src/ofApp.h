#pragma once

//--

/*

	This example shows how to use the logging system.
	and Help Boxes for internal and App.

*/


//--


#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:

	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);

	ofParameter<bool> bAnimate1;
	ofParameter<bool> bAnimate2;
	ofParameter<void> bPrevious;
	ofParameter<void> bNext;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> amountPauses;
	ofParameterGroup params;
	void setupParams();
	void Changed_Params(ofAbstractParameter& e);

	ofxSurfingGui ui;
	void setupImGui();
	void drawImGui();
	void setupLog();
	void setupFonts();
	void setupHelp();

	// Generates random variations to animate variables.
	// Log messages to test the Log window.
	void updateLog(); 
	ofParameter<float> progress0{ "Progress 0", 0 , 0, 1 };
	ofParameter<float> progress1{ "Progress 1", 0 , 0, 1 };
	ofParameter<float> progress2{ "Progress 2", 0 , 0, 1 };
	ofParameter<float> progress3{ "Progress 3", 0 , 0, 1 };
};
