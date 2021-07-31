#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "ofxImGui.h"

#include "SurfingTextEditor.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void draw();
    void keyPressed(int key);
    
    ofxImGui::Gui gui;

	bool bMouseOverGui = false;

	SurfingTextEditor textEditor;
};
