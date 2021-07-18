#pragma once

//TODO; broken

#include "ofMain.h"

#include "ofxSurfingImGui.h"	

#include "node_editor.h"
#include <imnodes.h>
#include <imgui.h>

//-

#include "color_node_editor.cpp"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <ios> // for std::streamsize
#include <stddef.h>
#include <vector>

//static SaveLoadEditor editor;

//-

class ofApp : public ofBaseApp {
public:

public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);

	ofxSurfing_ImGui_Manager guiManager;

	void drawWidgets();

	bool bOpen0 = true;
	bool bOpen1 = true;
	bool bOpen2 = false;

	bool initialized = false;
};
