#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h" 
#include "imgui_color_gradient.h" 

class exampleSurfingGradient
{
public:

	exampleSurfingGradient();
	~exampleSurfingGradient();

	void setup();

	void update();
	void draw();
	void drawWidgets();
	void drawImGui();

private:

	void update(ofEventArgs & args);
	void draw(ofEventArgs & args);

	void keyPressed(ofKeyEventArgs &eventArgs);
	void exit();


	//void setBool(bool b);
	//bool getBool();

	string path_Params_AppSettings = "exampleSurfingGradient_AppSettings.xml";
	ofParameterGroup params_AppSettings;
	ofParameter<bool> bKeys;

public:

	ofParameter<int> indexPreset;
	float prcGrad = 0.5f;
	ofFloatColor color;

private:

	ImGradient gradient;

	void loadGradient(int index);

	ofEventListener listener;

};

