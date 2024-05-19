/*

	This example shows how to browse themes.
	We can explore what settings defines a theme,
	and start make our own theme.

*/

#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "surfingThemeEditor.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);
	
	ofxSurfingGui ui;

	// The theme editor must be instantiated.
	// It will be required to edit the default themes.
	SurfingThemeEditor e;
};
