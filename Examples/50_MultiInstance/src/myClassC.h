#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class myClassC
{
public:

	myClassC();
	~myClassC();

	void setup();
	void draw();

	void setUiPtr(ofxSurfingGui* _ui);

	ofParameterGroup params;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> shapeType;

	ofxSurfingGui* ui;

	ofParameter<bool> bGui{ "myClassC", true };
};
