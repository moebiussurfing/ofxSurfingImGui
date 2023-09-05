#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class myClassD
{
public:

	myClassD();
	~myClassD();

	void setup();
	void draw(ofxSurfingGui* _ui);

	ofParameterGroup params;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> shapeType;
	ofParameter<int> amount;
	ofParameter<int> size;

	ofParameter<bool> bGui{ "myClassD", true };
};
