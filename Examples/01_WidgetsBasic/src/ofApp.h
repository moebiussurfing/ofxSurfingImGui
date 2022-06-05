#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ofxSurfingHelpers.h"

class ofApp : public ofBaseApp
{

public:
	
    void setup();
    void draw();
    void keyPressed(int key);

	//-

	// ImGui

	ofxSurfing_ImGui_Manager guiManager;

	ofParameter<bool> bGui;
    void drawImWindowMain();

	ofParameter<bool> bGui_1;
	ofParameter<bool> bGui_2;
	ofParameter<bool> bGui_3;
	ofParameter<bool> bGui_4;

    void drawImWindow1();
    void drawImWindow2();
    void drawImWindow3();
    void drawImWindow4();

	//-

    // Groups
    
	ofParameterGroup params1;
    ofParameterGroup params2;
    ofParameterGroup params3;
    ofParameterGroup params4;

	//-

    // Parameters
	
	ofParameter<glm::vec3> rotation;
	ofParameter<glm::vec3> position;
	ofParameter<float> value;
	ofParameter<float> valueMin;
	ofParameter<float> valueMax;
    ofParameter<bool> bPrevious;
    ofParameter<bool> bNext;
	ofParameter<float> knob1;
	ofParameter<float> knob2;
	ofParameter<int> amount2;
    ofParameter<float> lineWidth2;
    ofParameter<float> separation2;
	ofParameter<int> shapeType2;
	ofParameter<float> speed3;
	ofParameter<int> shapeType3;
	ofParameter<int> size3;
	ofParameter<int> shapeType4;
	ofParameter<int> size4;
	ofParameter<float> lineWidth4;
	ofParameter<float> separation4;
	ofParameter<float> speed4;
    ofParameter<ofColor> color1;
    ofParameter<ofFloatColor> color2;
};
