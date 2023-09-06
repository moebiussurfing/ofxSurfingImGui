
/*

	This is a WIP example to explore the workflow and debug how to combine multiple instances of ofxImGui
	inside an ofxSurfingImGui class who acts as a kind of manager.

	Many classes (myClassA-B-C-D) with some instantiated objects (A, B, C, D)
	will populate widgets for ofParams but using different approaches.

	--

	ofxSurfingImGui is a kind of a ( WIP ) higher level class, with more OF ofParameters helpers and a Toolkit with more features:
	Styled widgets, layout helpers, windows management, window aligners, layout presets, log and floating notifications engine,
	docking helpers, profile and plotting tools, and much more.

	Important: ui acts as a manager, registering the populated windows and ofParams widgets
	handling internal unique IDs (to avoid params collide) and each widgets styling and layout.

	Uses the ofxImGui fork from @Daandelange: https://github.com/Daandelange/ofxImGui.
	The original repo from @jvcleave https://github.com/jvcleave/ofxImGui
	has many limitations like being limited to use only one ImGui context instance.

*/


#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "myClassA.h"
#include "myClassB.h"
#include "myClassC.h"
#include "myClassD.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);

	ofParameterGroup params;
	ofParameter<bool> bEnable1;
	ofParameter<bool> bEnable2;
	ofParameter<bool> bEnable3;
	ofParameter<void> bPrevious;
	ofParameter<void> bNext;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> shapeType;
	ofParameter<int> amount;
	ofParameter<int> size;

	ofParameter<bool> bGui{ "my_ofApp", true };

	// Local ui object that will be shared to some of the instantiated classes
	// will populate local (ofApp) ofParams too.
	ofxSurfingGui ui;

	//--

	myClassA A;
	// will draw the window. Do not calls Begin/End inside the class object. (Uses the ofApp Begin/End from the local ImGui instance)

	myClassB B; 
	// will have his own internal ImGui / ofxSurfingImGui ui instance. (Uses his own Begin/End)

	myClassC C; 
	// will receive and store this local ui into a pointer to populate widgets on there: inside the class draw method.

	myClassD D; 
	// will use the local (ofApp) instantiated ofxSurfingGui object.

	//--

	// Advanced
	void drawWidgets()
	{
		ui.AddSpacingBigSeparated();
		ui.AddLabelBig("Hello std::function<void()>");
		ui.AddLabel("Where is the drawer?");
		static bool b = true;
		ImGui::Checkbox("b", &b);
		if (b) ImGui::Text("Here it is! \nIt's defined in (parent) ofApp, \nnot myClassC object!");
		ui.AddSpacingBig();
	}
};
