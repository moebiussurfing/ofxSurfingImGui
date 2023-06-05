#pragma once

/*

	DEFAULT/BIG/HUGE/HUGE_XXL 
	are the labels for the default loaded fonts.

	This example show how to load some fonts
	to test how they work under the UI.
	The you should hard-code to force default fonts
	and customize your ui/theme.

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

#define CUSTOM_FONTS // comment to allow the default mode without custom fonts

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);
	
	ofxSurfingGui ui;

	SurfingThemeEditor e;
};
