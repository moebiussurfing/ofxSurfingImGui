#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:
    
    void draw();
    void keyPressed(int key);

    ofxSurfingGui ui;
    ofParameter<bool> bGui{ "Show", true };

    ofParameter<bool> bEnable{ "Enable", true };
    ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
    ofParameterGroup params{ "MyGroup", bEnable, speed };
};
