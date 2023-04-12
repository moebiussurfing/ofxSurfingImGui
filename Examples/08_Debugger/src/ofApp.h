#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void drawGui();
	void keyPressed(int key);

	ofxSurfingGui ui;

	ofParameter<bool> bStressCpu{ "STRESS CPU", false };

	ofParameter<bool> bStressGpu{ "STRESS GPU", false };
	ofParameter<bool> bNoise{ "Noise", false };
	ofParameter<float> power{ "Power", 0,0,1 };

	ofParameter<bool> b0{ "STRESS_CPU", true };
	ofParameter<bool> b1{ "DO-A", true };
	ofParameter<bool> b2{ "DO-B", true };
	ofParameter<bool> b3{ "SLEEP", true };
	ofParameter<bool> b4{ "IMGUI", true };
};
