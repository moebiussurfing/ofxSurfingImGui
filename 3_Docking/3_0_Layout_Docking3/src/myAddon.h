
#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

class myAddon /*: public ofBaseApp*/ {

public:

	myAddon() {};
	~myAddon() {};

	string name;
	int val = 0;
	int x, y;

	void setup(string name = "guiManager-myAddon", int val = 0, int x = 0, int y = 0);
	void draw();
	void exit();

	void drawWindow(string _title, int& _value, int _x = 300, int _y = 300, ImGuiWindowFlags _flags = ImGuiWindowFlags_None);

	ofxSurfing_ImGui_Manager guiManager;

protected:
	float value1;
	float value2;
};
