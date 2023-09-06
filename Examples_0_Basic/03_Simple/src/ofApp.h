#pragma once

/*

	This example shows how to:

	- Populate many ofParameters.
	- Populate an ofParamterGroup.
	- Use exponential helpers for sliders.
	- Populate common internal bool toggles:
	  minimize, auto resize, help windows.
	- Set and show internal and app Help Windows.
	- Easy Push/Pop Font style using an available internal index.
	- Global Scale widgets.

*/

//--

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:

	void setup();
	void draw();
	void keyPressed(int key);
	void exit();

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
