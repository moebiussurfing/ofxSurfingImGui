#pragma once


/*

	This example shows how to use the "Layout Presets Engine".

	It has some (special) Windows Engine to speed-up the creation of windows and their states/settings.
	
	The ofParameter widgets are populated using different approaches.
	( Sometimes uses guiManager.Add(.. and some uses ofxImGuiSurfing::Add.. or raw ImGui::Button(.. )
	Look to other widget or styles examples to learn more about this topic.
	
	The main topic of this examples is to learn how to use the "Layout Presets Engine" and Docking.
	All the added windows will be auto included and handled on the "Layout Presets Engine".

*/


#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp 
{
public:

	void setup();
	void draw();

	//-

	// Parameters

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

	//-

	// -> The ImGui Manager !
	ofxSurfing_ImGui_Manager guiManager; 

	void setupImGui();
	void setupImGuiStyles();
	void drawImGui();

	void logPopulate(); // -> Generates random messages to test logging.
	void doAnimate(); // -> Generates random variations to animate variables.
};
