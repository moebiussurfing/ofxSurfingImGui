#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "surfingImageInspect.h"
// It's an specialized class that is not included as default.

/*

	Right mouse buttons enables Inspector.
	Left mouse button picks the color from image or from inspector.

*/

//--

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);
	void exit();

	void drawImGui();
	void loadImage(string path);

	ofxSurfingGui ui;

	ofParameterGroup g{ "ofApp" };
	ofParameter<bool> bGui{ "ofApp", true };
	ofParameter<bool> bDrawImg{ "Draw Image", false };
	ofParameter<int> index{ "Index", 0, 0, 2 };
	ofEventListener eventIndex;

	string path1 = pathImages + "image1.png";//32 bits
	string path2 = pathImages + "image2.jpg";//24 bits
	string path3 = pathImages + "image3.bmp";//32 bits

	string pathImages = "images";//file path
	string path = "";//file name

	ofFloatImage imageFloat;
	bool bLoaded = false;

	//--

	SurfImageInspect imageInspect;

	ofParameter<ofColor> color{ "Color", ofColor(128, 128) };
};
