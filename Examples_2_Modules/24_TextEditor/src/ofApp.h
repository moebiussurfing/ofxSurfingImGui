/*

	This example shows a WIP text editor.
	Not specially designed to use for live coding,
	but more for other text tools.

*/

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
	void load(string path);
};
