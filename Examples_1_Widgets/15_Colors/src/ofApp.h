#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#define AUTO_CASE_CREATE(a) case a: return #a

class ofApp : public ofBaseApp {

public:

	void setup();
	void draw();
	void keyPressed(int key);

	// parameters
	ofParameterGroup params;
	ofParameter<ofColor> c1;
	ofParameter<ofColor> c2;
	ofParameter<ofFloatColor> c3;
	ofParameter<ofFloatColor> c4;

	ofxSurfingGui ui;
	ofParameter<bool> bGui{ "Show", true };

	//--

	// Debugger / Tester

	ofParameter<int> index{ "Style", 0, 0, 0 };

	SurfingGuiTypes styleColor = OFX_IM_COLOR;
	vector<string> namesStylesColor;

	ofEventListener listener;

};
