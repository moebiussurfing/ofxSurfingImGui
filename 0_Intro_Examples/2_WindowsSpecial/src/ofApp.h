#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:
    
    void setup();
    void draw();
	
	//-

    // Parameters
    
    ofParameterGroup params0;
    ofParameter<bool> bEnable0;
    ofParameter<bool> bPrevious0;
    ofParameter<bool> bNext0;
    ofParameter<float> speed0;

	ofParameterGroup params1;
    ofParameter<bool> bEnable1;
    ofParameter<float> lineWidth1;
    ofParameter<float> separation1;
    ofParameter<int> shapeType1;
    ofParameter<int> size1;

    ofParameterGroup params2;
    ofParameter<bool> bEnable2;
    ofParameter<int> shapeType2;
    ofParameter<int> amount2;
    ofParameter<int> size2;

    ofParameterGroup params3;
    ofParameter<bool> bEnable3;
    ofParameter<float> lineWidth3;
    ofParameter<float> separation3;
    ofParameter<float> speed3;
    ofParameter<int> shapeType3;

	//-

	// Gui

	ofxSurfing_ImGui_Manager guiManager;

	void setup_ImGui();

	void draw_SurfingWidgets0();
	void draw_SurfingWidgets1();
	void draw_SurfingWidgets2();
	void draw_SurfingWidgets3();
};
