#pragma once
#include "ofMain.h"

/*

    This example is for testing purposes
    Allows debugging about how to handles many ui instances:
    - Look how the fonts are added to the ImGui context.
    - Look how bin/data/ settings are created with separated folders for each instance.
    - Debug how ofxImGui handles internal master/slave instances and the context management.

*/


#include "ofxSurfingImGui.h"

#define NUM_INSTANCES 7

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    void keyPressed(int key);

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

    ofParameter<bool> bGui{"Show Gui", true};

    ofxSurfingGui ui_;

    ofxSurfingGui ui[NUM_INSTANCES];
};
