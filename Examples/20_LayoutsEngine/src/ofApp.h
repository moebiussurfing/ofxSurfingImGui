#pragma once


/*

This example shows how to use the

LAYOUT PRESETS ENGINE


OVERVIEW

Speed-up the creation
of Windows and their shape,
states and settings.
Powered with the Presets of 4 Layouts.


WIDGETS

The ofParameter widgets are populated
using different approaches:

* guiManager.Add(..       | API
* ofxImGuiSurfing::Add(.. | Legacy
* ImGui::Button(..        | Raw

Look to other widget or styles examples
to learn more about this topic.


MORE INFO

- All the Special Windows (aka Panels)
added to the manager will be
auto handled on the Layout Presets Engine.

- It will memorize the windows positions,
sizes and which ones are activated or hidden.

- Some optional Extra Params
can be included into what
each preset memorizes too.

- By default we will have 4 Layout Presets.
Then we will organize that different modes,
sections or behaviors of our App,
by customizing our layout distribution,
and some Extra Params states.

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

	// The ImGui Manager !

	ofxSurfing_ImGui_Manager guiManager;

	void setupImGui();
	void setupImGuiStyles(); // -> Custom styles for groups

	void drawImGui();
	void drawImGuiDocking();

	//-

	// Scene

	void setupScene();
	void udpateScene(); // -> Generates random variations to animate variables.
	void updateLog(); // -> Generates random messages to test logging.
};
