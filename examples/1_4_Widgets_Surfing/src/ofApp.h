#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" // -> This header includes ALL the classes. 
using namespace ofxImGuiSurfing;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    
	void setup_ImGui();
	ofxImGui::Gui gui;
	ImFont* customFont = nullptr;

    void draw_SurfingWidgets1();
    void draw_SurfingWidgets2();

    // parameters
    ofParameter<int> indexPreset;
	ofEventListener listener;

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

	ImGradient gradient;
	float prcGrad = 0.5f;
	ofFloatColor color;

	void loadGradient(int index);
};
