#pragma once

#include "ofMain.h"

#include "Surfing_Bezier.h"

//-

//#include "ofxImGui.h" // requires  https://github.com/Daandelange/ofxImGui
#include "ofxSurfingImGui.h"

using namespace ofxImGuiSurfing;

//-

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    
	// for a typical ofxImGui "clean" setup
	void setup_ImGui();
	ofxImGui::Gui gui;
	ofxImGui::Settings mainSettings = ofxImGui::Settings();
	ImFont* customFont = nullptr;


    // parameters
    ofParameterGroup params;
    ofParameter<bool> bEnable1;
    ofParameter<bool> bEnable2;
    ofParameter<bool> bEnable3;
    ofParameter<bool> bPrevious;
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
};
