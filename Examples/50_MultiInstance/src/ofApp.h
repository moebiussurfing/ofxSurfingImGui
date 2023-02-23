
/*

	This is a WIP example to explore the workflow and debug how to combine multiple instances of ofxImGui 
	inside an ofxSurfingImGui class. Is a kind of a higher level class, with more OF helpers and a Toolkit with new features.
	Many classes with some instantiated objects will populate widgets for ofParams but using different approaches.

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
	ofxSurfingGui ui;

	//--

	myClassA A;
	myClassB B;
	myClassC C;
	myClassD D;

};
