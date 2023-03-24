#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "SurfingTextEditor.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;

	SurfingTextEditor textEditor;
};
