#pragma once

// Taken from: https://github.com/d3cod3/ofxVisualProgramming

// https://github.com/d3cod3/ofxVisualProgramming/blob/master/src/objects/data/FileToData.h
// https://github.com/d3cod3/ofxVisualProgramming/blob/master/src/objects/data/FileToData.cpp

/*

TODO:
WIP
not working..
nothing appears

*/


#include "ofMain.h"

//#include "ofxImGui.h"
#include "ofxSurfingImGui.h"

#include "ImGuiFileBrowser.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();

	ofxImGui::Gui gui;

	imgui_addons::ImGuiFileBrowser fileBrowser;

	string strPath = "";
	string strPathName = "";
};
