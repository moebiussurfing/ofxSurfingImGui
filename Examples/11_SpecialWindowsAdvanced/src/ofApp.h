#pragma once

#include "ofMain.h"

/*

	This example complements the previous 10_SpecialWindows example,
    but also shows two instances of the ofxSurfingImGui Toolkit add-on,
    both working together without colliding their ImGui windows nor widgets,
    nor the extra engine features neither.
    One instance of the Gui Manager is in ofApp, 
    and the other into the instantiated myClass object.

*/


#include "ofxSurfingImGui.h"
#include "myClass.h"

class ofApp : public ofBaseApp
{
public:
    
    void setup();
    void setupParams();
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

	SurfingGuiManager ui;

	void setup_ImGui();

    // This is the only visible toggle 
    // that will not be added as special window.
    ofParameter<bool> bGui;
    void draw_MainWindow();
	
    // Non Special Window
    void draw_SurfingWidgets_1(); 
    // This window will be handle without using special windows workflow, 
    // passing by name instead of passing the visible toggle param.

    // Special Windows
	void draw_SurfingWidgets_2();
	void draw_SurfingWidgets_3();
	void draw_SurfingWidgets_4();
    void draw_SurfingWidgets_5();
	void draw_SurfingWidgets_6();

    // Visible toggles for the Special Windows
    ofParameter<bool> bGui_2;
    ofParameter<bool> bGui_3;
    ofParameter<bool> bGui_4;
    ofParameter<bool> bGui_5;
    ofParameter<bool> bGui_6;

    // Help info
    void buildHelpInfo();
    string helpInfo;

    //--

    // Another ImGui "context" is running inside!
    MyClass myClassObject;
};
