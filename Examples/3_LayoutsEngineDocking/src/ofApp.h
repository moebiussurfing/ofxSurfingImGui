#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "ofxWindowApp.h" // -> Not required

class ofApp : public ofBaseApp 
{
public:

	//-

	void setup();
	void draw();

	//-

	// Parameters

	ofParameterGroup params1;
	ofParameter<bool> bEnable;
	ofParameter<bool> bPrevious;
	ofParameter<bool> bMode1;
	ofParameter<bool> bMode2;
	ofParameter<bool> bMode3;
	ofParameter<bool> bMode4;
	ofParameter<bool> bNext;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> shapeType;
	ofParameter<int> amount;
	ofParameter<int> size;
	ofParameterGroup params2;
	ofParameter<int> shapeType2;
	ofParameter<int> amount2;
	ofParameter<int> size2;
	ofParameterGroup params3;
	ofParameter<float> lineWidth3;
	ofParameter<float> separation3;
	ofParameter<float> speed3;
	ofParameter<int> shapeType3;

	//-

	ofxSurfing_ImGui_Manager guiManager; // The Gui Manager !

	void drawImGui();

	void logPopulate();

	//-

	void dockingHelperUpdate();
	void dockingHelperDraw();
	void doDockingReset();
	void doDockingRandom();
	bool bDockingReset = false;
	bool bDockingRandom = false;

	//-

	ofxWindowApp windowApp;
};
