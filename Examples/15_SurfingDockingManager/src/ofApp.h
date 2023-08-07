
//#define SURF_IM // Uncomment to use ofxSurfingImGui instead of ofxImGui

#pragma once
#include "ofMain.h"

#include "SurfingDockingManager.h"

#ifdef SURF_IM
#include "ofxSurfingImGui.h"
#else
#include "ofxImGui.h"
#endif

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);
	void exit();
	
#ifdef SURF_IM
	ofxSurfingGui ui;
#else
	ofxImGui::Gui ui;
#endif
	
	SurfingDockingManager manager;
	
	// Some parameters
	ofParameter<bool> bGui{ "ofApp", true };
	ofParameter<bool> bEnable{ "Enable", true };
	ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
	ofParameter<string> name{ "Name", ""};
	ofParameterGroup params{ "MyParamGroup", bEnable, speed, name };
};
