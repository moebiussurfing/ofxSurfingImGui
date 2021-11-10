
#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "ofxWindowApp.h" // -> not required

//#define USE_FBOS_DEMO // -> fbo testing

/*

This example shows how to use the presets engine for panels layouts distribution,
and for added parameters to presets system.

*/

//--------------------------------------------------------------
class ofApp : public ofBaseApp {

public:

	void setup();
	void draw();
	void keyPressed(int key);
	void exit();

	//-

	// parameters

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

	ofParameter<ofRectangle> rectParam{ "Rect", ofRectangle(500,500,100,100), ofRectangle(1,1,1,1), ofRectangle(1920,1080,1920,1080) };
	void Changed_Rect(ofRectangle & r);

	//--

	ofxSurfing_ImGui_Manager guiManager;

	//--

	void drawMenu();

	void drawImGui();

	//--

	bool binitiated = false; // runs once to perform some required initialization

	void dockingReset1();
	void dockingReset2();
	bool bDockingReset1 = false;
	bool bDockingReset2 = false;

	//-

	// window fbo

#ifdef USE_FBOS_DEMO
	void setupFbos();
	void updateFbos();
	void drawFboTest();
	ofFbo rgbaFbo; // with alpha
	ofFbo rgbaFboFloat; // with alpha
	int fadeAmnt;
#endif

	//--

	ofxWindowApp windowApp;

};
