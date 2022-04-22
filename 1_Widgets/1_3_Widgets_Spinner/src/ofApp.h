#pragma once

#include "ofMain.h"

#include "ofxImGui.h" // requires  https://github.com/Daandelange/ofxImGui
#include "ImGui/themes/ofxSurfing_ImGui_Themes.h"
#include "ofxSurfingImGui.h" // -> this headers includes all the available sttuff
//using namespace ofxImGuiSurfing;

//#include "ImGui/widgets/ofxSurfing_ImGui_WidgetsSpinner.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    
	void setup_ImGui();
	ofxImGui::Gui gui;
	ofxImGui::Settings mainSettings = ofxImGui::Settings();
};
