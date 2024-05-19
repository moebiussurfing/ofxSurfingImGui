
/*

	This is a WIP example to explore the workflow and debug how to combine multiple instances of ofxImGui
	inside an ofxSurfingImGui class, who acts as a kind of manager.

	Many classes (myClassA-B-C-D) with some instantiated objects (A, B, C, D)
	will populate widgets for ofParams but using different approaches.

	- In this example one single UI instance 
	will be passed/shared as reference between all the classes objects.

	- ui.Begin/End will be called only once in ofApp!

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
	void update();
	void draw();
	void keyPressed(int key);

	ofParameterGroup parameters;
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
	// to draw their respective widgets.
	// will populate local (ofApp) ofParams too.
	ofxSurfingGui ui;

	//--

	myClassA A;

	myClassB B; 

	myClassC C; 

	myClassD D; 

	//--

	// Advanced function
	// These are populated widget from this root/main scope,
	// but called inside the class object C.
	void drawWidgets();
};
