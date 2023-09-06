#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"

class myClassA
{
public:
	myClassA();
	~myClassA();

	void setup();
	void drawImGui(ofxSurfingGui* ui);

	ofParameterGroup parametersA;
	ofParameter<int> shapeType2;
	ofParameter<int> amount2;
	ofParameter<int> size2;

	ofParameter<bool> bGui{ "myClassA", true };
};
