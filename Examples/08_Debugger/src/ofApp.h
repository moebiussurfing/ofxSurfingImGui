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

	ofParameter<bool> bTestCpu{ "TEST CPU", false };
	ofParameter<bool> bTestGpu{ "TEST GPU", false };
	ofParameter<bool> bNoise{ "Noise", false };

	ofParameter<bool> b0{ "b0", true };
	ofParameter<bool> b1{ "b1", true };
	ofParameter<bool> b2{ "b2", true };
	ofParameter<bool> b3{ "b3", true };
	ofParameter<bool> b4{ "b4", true };
	ofParameter<bool> b5{ "b5", true };


	ofParameter<float> power{ "Power", 0,0,1};
};
