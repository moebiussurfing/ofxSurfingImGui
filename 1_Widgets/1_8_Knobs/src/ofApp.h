#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" // -> This header includes ALL the add-on classes. 

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	ofxSurfing_ImGui_Manager guiManager;

	ofParameter<float> valueKnob1{ "Value1", 0.f, -10.f, 10.0f };
	ofParameter<float> valueKnob2{ "Value2", 5.f, 0.f, 10.0f };
	ofParameter<float> valueKnob3{ "Value3", -5.f, -10.f, 10.0f };
	ofParameter<float> valueKnob4{ "Value4", 5.f, -10.f, 10.0f };

	ofParameter<int> valueKnob5{ "Value5", 0, -10, 10 };
	ofParameter<int> valueKnob6{ "Value6", 0, 0, 10 };
	ofParameter<int> valueKnob7{ "Value7", 5, 0, 10 };
	ofParameter<int> valueKnob8{ "Value8", 50, 0, 100 };
};
