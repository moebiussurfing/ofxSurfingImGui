#pragma once

#include "ofMain.h"

/*

	This example shows two of the extra engines of the ofxSurfingImGui Toolkit,
	
    1. SPECIAL WINDOWS ORGANIZER ENGINE
	Many grouped windows, defined as specials, can be arranged linked together. 
    Can be auto distributed horizontally or vertically.
    
    2. WINDOWS ALIGN ENGINE 
    Helpers to align/cascade/layout all visible windows (except some internal ones).


    NOTE:  

    The "Special Windows Organizer" windows. 
    Speeds Up the creation of windows.  
    An Internal bool toggle will be auto created for each added Special Window.  
    Another window called "Organizer" (by default) will be auto drawn!  
    This happens internally, and we don't need to handle that.  
    It's a panel who controls all the Special Windows.  

    You only need to queue windows on setup:
	ui.addWindowSpecial("myWindow 0");
	ui.addWindowSpecial("myWindow 1");
	ui.addWindowSpecial("myWindow 2");
	ui.addWindowSpecial("myWindow 3");

    Features: 
    - Autocreates toggles and controls for each queued window. 
    - Show/Hide each queued Special Window. all/none.  
    - Align windows as vertical or horizontal cascade.
    - Custom spacing between windows, hide headers or vertical/horizontal mode.
    - Ready to feed Layout Presets Engine.
    - Ready to help on Docking workflow.

*/


#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void setupParams();
    void draw();
	void keyPressed(int key);
    void exit();

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

	ofxSurfingGui ui;

	void setup_ImGui();
    ofParameter<bool> bGui; 
    // Toggle to show visible the window panel

    void draw_MainWindow();

	void draw_SurfingWidgets_0();
	void draw_SurfingWidgets_1();
	void draw_SurfingWidgets_2();
	void draw_SurfingWidgets_3();
};
