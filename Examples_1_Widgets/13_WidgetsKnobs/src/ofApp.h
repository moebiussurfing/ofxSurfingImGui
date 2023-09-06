/*

	Test knobs and styles

*/


#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" 

class ofApp : public ofBaseApp 
{
public:

	void setup();
	void draw();

	ofxSurfingGui ui;

	ofParameter<float> valueKnob1{ "Float1", 0.f, -10.f, 10.0f };
	ofParameter<float> valueKnob2{ "Float2", 5.f, 0.f, 10.0f };
	ofParameter<float> valueKnob3{ "Float3", -5.f, -10.f, 10.0f };
	ofParameter<float> valueKnob4{ "Float4", 5.f, -10.f, 10.0f };

	ofParameter<int> valueKnob5{ "Int5", 0, -5, 5 };
	ofParameter<int> valueKnob6{ "Int6", 0, 0, 100 };
	ofParameter<int> valueKnob7{ "Int7", 5, 0, 100 };
	ofParameter<int> valueKnob8{ "Int8", 50, 0, 100 };
};
