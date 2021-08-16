#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ofxImGui.h"

#include "SurfingNotify.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void draw();
    void keyPressed(int key);
    
    ofxImGui::Gui gui;

	SurfingNotify notify;
};
