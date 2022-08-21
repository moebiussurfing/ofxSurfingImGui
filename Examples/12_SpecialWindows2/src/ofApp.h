#pragma once

#include "ofMain.h"

/*

	This example shows two of the extra engines of the ofxSurfingImGui Toolkit,
	
    1. WINDOWS SPECIAL ORGANIZER.
	Many grouped windows, defined as specials, can be arranged linked together. 
    Can be auto distributed horizontally or vertically.
    
    2. ALIGN WINDOWS ENGINE: 
    Helpers to align/cascade/layout all visible windows.

    3. We will learn how to create Special Windows using different workflows / API methods:
    passing names and handling with indexes 
    or by passing visible toggles (ofParameter<bool> bGui), 
    that will be used to name the windows headers too.

    4. We will learn how to add an Help Info box to the GUI manager.
    As help boxes could be commonly used in our apps, 
    an internal help box is bundled inside.

*/


#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:
    
    void setup();
    void draw();
	void keyPressed(int key);

	//--

    // Parameters
    
    ofParameterGroup params_0;
    ofParameter<bool> bEnable0;
    ofParameter<bool> bPrevious0;
    ofParameter<bool> bNext0;
    ofParameter<float> speed0;

	ofParameterGroup params_1;
    ofParameter<bool> bEnable1;
    ofParameter<float> lineWidth1;
    ofParameter<float> separation1;
    ofParameter<int> shapeType1;
    ofParameter<int> size1;

    ofParameterGroup params_2;
    ofParameter<bool> bEnable2;
    ofParameter<int> shapeType2;
    ofParameter<int> amount2;
    ofParameter<int> size2;

    ofParameterGroup params_3;
    ofParameter<bool> bEnable3;
    ofParameter<float> lineWidth3;
    ofParameter<float> separation3;
    ofParameter<float> speed3;
    ofParameter<int> shapeType3;

	//--

	// Gui

	ofxSurfing_ImGui_Manager ui;

	void setup_ImGui();

    // this is the only visible toggle that will not be added as special window.
    ofParameter<bool> bGui;
    void draw_MainWindow();

	void draw_SurfingWidgets_1(); 
    // this window will be handle without using special windows workflow, 
    // passing by name instead of passing the visible toggle param.

	void draw_SurfingWidgets_2();
	void draw_SurfingWidgets_3();
	void draw_SurfingWidgets_4();
    void draw_SurfingWidgets_5();
	void draw_SurfingWidgets_6();

    ofParameter<bool> bGui_2;
    ofParameter<bool> bGui_3;
    ofParameter<bool> bGui_4;
    ofParameter<bool> bGui_5;
    ofParameter<bool> bGui_6;

    // Help info
    void buildHelpInfo();
    string helpInfo;
};
