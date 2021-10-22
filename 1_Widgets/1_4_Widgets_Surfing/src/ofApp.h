#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" // -> This header includes ALL the add-on classes. 

#include "exampleSurfingGradient.h" // -> This is an example about how to build a complex "widget",
// using small raw ImGui widgets from other users community.


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();

    // Parameters

    ofParameterGroup params;
    ofParameterGroup params2;
    ofParameterGroup params3;
    ofParameter<bool> bEnable1;
    ofParameter<bool> bEnable2;
    ofParameter<bool> bEnable3;
    ofParameter<bool> bPrevious;
    ofParameter<bool> bNext;
    ofParameter<float> lineWidth;
    ofParameter<float> separation;
    ofParameter<float> speed;
    ofParameter<int> shapeType;
    ofParameter<int> size;
    ofParameter<int> shapeType2;
    ofParameter<int> amount2;
    ofParameter<int> size2;
    ofParameter<float> lineWidth3;
    ofParameter<float> separation3;
    ofParameter<float> speed3;
    ofParameter<int> shapeType3;
	ofParameter<float> valueKnob1{ "Value1", 0.5f, 0.f, 1.0f };
	ofParameter<float> valueKnob2{ "Value2", 5.f, -10.f, 10.0f };
	ofParameter<int> indexPreset;

	//-

	void setup_ImGui();

	ofxSurfing_ImGui_Manager guiManager;

	void draw_SurfingWidgets_1();
	void draw_SurfingWidgets_2();

	exampleSurfingGradient surfingGradient;
};
