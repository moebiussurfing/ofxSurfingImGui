#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" 
#include "imgui_color_gradient.h" 

class SurfingGradient
{
public:

	SurfingGradient();
	~SurfingGradient();

	void setup();

	void update();
	void draw();
	void drawWidgets();
	void drawImGui();

	void drawGradientPreview();
	
	void setIndex(int index);

	ImGradientMark* draggingMark = nullptr;
	ImGradientMark* selectedMark = nullptr;

private:

	//void update(ofEventArgs & args);
	//void draw(ofEventArgs & args);
	//void keyPressed(ofKeyEventArgs &eventArgs);

	void exit();


	//void setBool(bool b);
	//bool getBool();

	//string path_Params_AppSettings = "SurfingGradient_AppSettings.xml";
	//ofParameterGroup params_AppSettings;
	//ofParameter<bool> bKeys;

public:

	//ofParameter<int> indexPreset;
	float prcGrad = 0.5f;
	ofFloatColor color;

	ofParameter<ofFloatColor> color_Picked{ "ColorPicked",
		ofFloatColor(0),
		ofFloatColor(0),
		ofFloatColor(1) };

	//ofColor *colorPicked_TARGET;//backwards pointer to ofApp background color
	//void setLinkColorPicked(ofColor &c)
	//{
	//	ofLogNotice(__FUNCTION__) << ofToString(c);
	//	colorPicked_TARGET = &c;
	//}

public:
	ImGradient gradient;

	void loadPalette(vector<ofColor>& palette);

//private:
	//void loadGradient(int index);

	//ofEventListener listener;

};

