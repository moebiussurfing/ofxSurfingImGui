#pragma once

/*

+ fix groups/trees crashes
+ split vec3 params to 3 sliders
+ simple combo enum list

*/


#include "ofMain.h"

#include "ofxSurfingImGui.h"

#define MAX_CAMERA_DISTANCE 500.0f

class ofApp : public ofBaseApp{
    
public:

    void setup();
    void draw();

	ofxSurfing_ImGui_Manager guiManager;

    // parameters
    ofParameterGroup params;
    ofParameterGroup params2;
    ofParameterGroup params3;

	ofParameter<glm::vec3> pos1;
	ofParameter<glm::vec3> pos2;

    ofParameter<bool> bEnable1;
    ofParameter<bool> bEnable2;
    ofParameter<bool> bEnable3;
    ofParameter<bool> bPrevious;
    ofParameter<bool> bNext;

    ofParameter<float> lineWidth;
    ofParameter<float> separation;

	//ofParameter<float> speed;
	//ofParameter<int> shapeType;
	//ofParameter<int> size;
	//ofParameter<int> shapeType2;
	//ofParameter<int> amount2;
	//ofParameter<int> size2;
	//ofParameter<float> lineWidth3;
	//ofParameter<float> separation3;
	//ofParameter<float> speed3;
	//ofParameter<int> shapeType3;
	//ofParameter<float> valueKnob1{ "Value1", 0.5f, 0.f, 1.0f };
	//ofParameter<float> valueKnob2{ "Value2", 5.f, -10.f, 10.0f };
};
