#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void keyPressed(int key);

	ofxSurfingGui ui;
	ofParameter<bool> bGui{ "ofApp", true };

	void ShowExampleTable();
	struct Data {
		int id; 
		std::string name; 
		float value; 
		double largeValue; 
		int anotherInt; 
		std::string description;
	};
	std::vector<Data> data;

	void ShowAngledHeaders();
};
