#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "NodesEdit.h"
#include "ofNodeEditor.h"

// This is based on https://github.com/sphaero/ofNodeEditor
// is an experimental simple approach

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void drawImGui();
    void draw();
    void keyPressed(int key);

    ofxImGui::Gui gui;
    ofNodeEditor nodes;
};
