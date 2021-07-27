#pragma once

#include "ofMain.h"

#include "ImGui/ofxSurfing_ImGui_WidgetsBezier.h"

#include "ofxSurfingImGui.h" // -> this headers includes all the available sttuff

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    void keyPressed(int key);
    
	void setup_ImGui();

	ofxSurfing_ImGui_Manager gui;

	ofxImGuiSurfing::SurfingCurve surfingCurve;
	ofParameter<float> value{ "Value", 0, 0, 1 };
};
