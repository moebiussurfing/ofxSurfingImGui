#pragma once

/*

	This example shows how to load some fonts
	to test how they work under the UI.
	Then you should learn how to hard-code
	to force default fonts
	and customize your ui/theme.

	There are four size/styles DEFAULT/BIG/HUGE/HUGE_XXL
	That styles are made from a default loaded font.
	These four styles are from the same ttf file,
	but in different sizes.

	So, currently, a theme will load only one ttf file.
	But other extra fonts can be added on runtime,
	and can be used in different ImGui windows/places.

*/

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "SurfingFonts.h"
#include "surfingThemeEditor.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;

	SurfingThemeEditor e;
	SurfingFonts f;

	void drawMyDemoWindow();
	bool bUseFontMonospaced = 0;
	bool bUseFontIndex = 0;
};
