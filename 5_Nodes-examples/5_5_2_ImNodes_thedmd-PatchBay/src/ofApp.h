#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"	

#include "basic-interaction-example.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);

	ofxSurfing_ImGui_Manager guiManager;
	
	Example example;

	void drawWidgets();

	bool bOpen0 = true;
	bool bOpen1 = true;
	bool bOpen2 = false;

	bool initialized = false;
};
