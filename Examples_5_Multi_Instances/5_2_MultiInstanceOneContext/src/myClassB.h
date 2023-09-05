#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class myClassB
{
public:

	myClassB();
	~myClassB();

	void setup();
	void draw();

	ofParameterGroup params;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> shapeType;

	ofxSurfingGui* ui = nullptr;
	void setUiPtr(ofxSurfingGui* _ui);

	ofParameter<bool> bGui{ "myClassB", true };
};
