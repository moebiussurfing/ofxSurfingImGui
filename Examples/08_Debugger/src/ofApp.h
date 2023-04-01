#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "surfingDebugger.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();

	ofxSurfingGui ui;

	surfingDebugger d;
};
