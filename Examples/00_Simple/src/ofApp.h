#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "surfingMaths.h"

class ofApp : public ofBaseApp
{
public:

	void setup();
	void draw();
	void keyPressed(int key);

	// Parameters
	ofParameterGroup params;
	ofParameter<bool> bEnable1;
	ofParameter<bool> bEnable2;
	ofParameter<bool> bEnable3;
	ofParameter<void> bPrevious;
	ofParameter<void> bNext;
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

	ofEventListener listener;
	ofParameter<float> vIn;
	ofParameter<float> vOut1;
	ofParameter<float> vOut2;
	ofParameter<float> vOut3;

	ofParameter<bool> bGui{ "myWindow", true };

	ofxSurfingGui ui;
};
