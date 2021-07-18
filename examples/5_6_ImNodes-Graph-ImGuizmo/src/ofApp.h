#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"	
#include "Surfing_GraphEditor.h"	

class ofApp : public ofBaseApp {

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
