#pragma once

/*

*/

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "surfingThemeEditor.h"
#include "SurfingFonts.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofxSurfingGui ui;

    SurfingThemeEditor e;
    SurfingFonts f;

};
