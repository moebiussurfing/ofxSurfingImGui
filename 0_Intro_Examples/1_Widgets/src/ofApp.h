#pragma once

/*

+ fix groups/trees crashes
+ split vec3 params to 3 sliders
+ simple combo enum list

*/


#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp{
public:
	
    void setup();
    void setupStyles();
    void draw();

	ofxSurfing_ImGui_Manager guiManager;

    // groups
    ofParameterGroup params1;
    ofParameterGroup params2;
    ofParameterGroup params3;
    ofParameterGroup params4;

    // parameters
	ofParameter<glm::vec3> pos1;
	ofParameter<float> value;
	ofParameter<float> valueMin;
	ofParameter<float> valueMax;

	ofParameter<glm::vec3> rto1;
    ofParameter<bool> bEnable1;
    ofParameter<bool> bEnable2;
    ofParameter<bool> bEnable3;
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

	vector <ofParameter<bool>> bEnablers;
};
