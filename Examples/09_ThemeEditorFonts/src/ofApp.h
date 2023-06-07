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

	Currently, a theme will load only one ttf file.
	But other fonts can be added on runtime,
	and to be used in different ImGui context places.

*/

/*

	TODO:

	Add a JSON file or integrate picked fonts list and sizes
	into the .ini theme file,
	to overwrite default
	FONT_DEFAULT_FILE "JetBrainsMono-Bold.ttf"
	from GuiConstants.h

	Add ImGui window/global scale control.

	Should skip exceptions if pushFonts files not found!

*/

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "surfingThemeEditor.h"

#define CUSTOM_FONTS // Comment to allow the default mode without custom fonts

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;
	void drawImGuiMain();
	void drawImGuiDemo();
	void drawImGuiTest();

	SurfingThemeEditor e;

	ofParameter<int> sizeFont{ "sizeFont", 12, 5, 50 };
	bool bBuild = 0;
	bool bLoadFolder = 0;
};
