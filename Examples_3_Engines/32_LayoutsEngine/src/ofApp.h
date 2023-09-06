 #pragma once


/*

This example shows how to use the
LAYOUT PRESETS ENGINE
Activate Help toggle to read the floating help box info.

*/


#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:

	void setup();

	void draw();
	
	void drawWindow0();
	void drawWindow1();
	void drawWindow2();
	void drawWindow3();
	void drawWindow4();

	// another approach using toggle params
	//ofParameter<bool> bGui_Main{"Main", false};
	//ofParameter<bool> bGui_Audio{"Audio", false};
	//ofParameter<bool> bGui_Video1{"Video1", false};
	//ofParameter<bool> bGui_Video2{"Video2", false};
	//ofParameter<bool> bGui_ExpertMain{"Expert", false};
	 
	//--

	// Scene Parameters

	ofParameterGroup params1;
	ofParameter<bool> bEnable;
	ofParameter<bool> bPrevious;
	ofParameter<bool> bMode1;
	ofParameter<bool> bMode2;
	ofParameter<bool> bMode3;
	ofParameter<bool> bMode4;
	ofParameter<bool> bNext;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> shapeType;
	ofParameter<int> amount;
	ofParameter<int> size;

	ofParameterGroup params2;
	ofParameter<int> shapeType2;
	ofParameter<int> amount2;
	ofParameter<int> size2;

	ofParameterGroup params3;
	ofParameter<float> lineWidth3;
	ofParameter<float> separation3;
	ofParameter<float> speed3;
	ofParameter<int> shapeType3;

	//--

	// The ImGui Manager !

	ofxSurfingGui ui;

	void setupImGui();
	void drawImGui();

	// Optional
	void setupImGuiStyles(); // -> Custom some styles for groups
	void drawImGuiDocking();

	//--

	// Scene

	void setupScene();
	void udpateScene(); // -> Generates random variations to animate variables.
	void updateLog(); // -> Generates random messages to test the Log window.

	void AddToLogAndNotifier(std::string text);
};
