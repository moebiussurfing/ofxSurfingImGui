#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "surfingThemeEditor.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void exit();

	ofxSurfingGui ui;

	SurfingThemeEditor e;
};
