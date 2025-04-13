/*

	TODO

	fix ofParams string
	substract window header to correlate hide/show header
	add anim show/hide

*/

 #define USE_ADVANCED_CALLBACK

#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "BigTextInput.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void draw();
    void keyPressed(int key);

    ofxSurfingGui ui;
    void drawImGui();
    ofParameter<bool> bGui{"ofApp", true};

    BigTextInput bigTextInput;

    void doAttendCallback();
#ifndef USE_ADVANCED_CALLBACK
    ofEventListener e;
#endif

    string text = ""; // A.
    // ofParameter<string> ptext{"myText", ""}; // B.

    float v = 0;
};
