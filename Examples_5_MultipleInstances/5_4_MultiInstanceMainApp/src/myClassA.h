#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"

class myClassA
{
public:
	myClassA();
	~myClassA();

	void setup();

	ofParameterGroup parameters;
	ofParameter<int> shapeType2;
	ofParameter<int> amount2;
	ofParameter<int> size2;

	ofParameter<bool> bGui{ "myClassA", true };

	void drawImGui();

	ofxSurfingGui ui_;
};
