#pragma once

/*

+ fix groups/trees crashes
+ fix hide headers
+ split vec3 params to 3 sliders
+ simple combo enum list

*/


#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ofxSurfingHelpers.h"

//https://github.com/iamclint/ImGuiRangeSlider
#include "ImGuiRangeSlider.h"

class ofApp : public ofBaseApp{
public:
	
    void setup();
    void setupImGuiStyles();
    void draw();
    void exit();

	ofxSurfing_ImGui_Manager guiManager;

	//-

    // Groups
    
	ofParameterGroup params1;
    ofParameterGroup params2;
    ofParameterGroup params3;
    ofParameterGroup params4;

	//-

    // Parameters
	
	ofParameter<glm::vec3> pos_1;
	ofParameter<float> value;
	ofParameter<float> valueMin;
	ofParameter<float> valueMax;

	ofParameter<glm::vec3> rot_1;
    
	ofParameter<bool> bEnable1;
    ofParameter<bool> bEnable2;
    ofParameter<bool> bEnable3;
	ofEventListener listener_bEnable1;
	ofEventListener listener_bEnable2;
	ofEventListener listener_bEnable3;

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

	//-

	// To be used to enable Gui sections
	// Could be used too to enable each window and allow close them using the top right [x]. 
	vector <ofParameter<bool>> bEnablers;
	ofParameterGroup paramsApp{ "ofApp" };
};
