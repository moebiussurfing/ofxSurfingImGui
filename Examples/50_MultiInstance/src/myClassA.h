#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class myClassA
{
public:

	myClassA();
	~myClassA();

	void setup();
	void draw();

	ofParameterGroup params2;
	ofParameter<int> shapeType2;
	ofParameter<int> amount2;
	ofParameter<int> size2;

	ofxSurfingGui ui;

	ofParameter<bool> bGui{ "myClassA", true };
};
