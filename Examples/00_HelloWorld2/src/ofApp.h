#pragma once

/*

    TO LEARN A BIT MORE 
    ABOUT THE API:

    - Spacing and separators.
    - Commontly useful minimizer toggle.
    - Tooltips for widgets.
    - The Log Window.
    - Mouse over gui.
    - Note persistence of previous sessions for some settings.
    - Text labels.
    - Some keycommands examples.

*/


//----


#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void exit();

    ofxSurfingGui ui;
    ofParameter<bool> bGui{ "Show", true };
    ofParameter<bool> bEnable{ "Enable", true };
    ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
    ofEventListener listener;
    ofParameterGroup params{ "MyGroup", bEnable, speed };

    string myTag1 = "HELLO WORLD";
    string myTag2 = "MOUSE";
};
