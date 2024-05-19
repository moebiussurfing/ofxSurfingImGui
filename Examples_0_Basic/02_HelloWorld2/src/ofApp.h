#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "imgui_tricks.hpp"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void exit();

	ofxSurfingGui ui;
	void setupGui();
	void drawGui();

	void drawGuiMain();
	ofParameter<bool> bGui{ "ofApp", true }; // using an ofParameter<bool>
	ofParameter<bool> bEnable{ "Enable", true };
	ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
	ofEventListener listener;
	ofParameterGroup params{ "MyGroup", bEnable, speed };

	// Custom Log tags
	string myTag1 = "HELLO WORLD";
	string myTag2 = "MOUSE CLICK";

	// quat
	void drawGuiQuat();
	bool bGui_Quat = false; // using a bool instead of an ofParameter<bool>
	float dampen = .4f;
	glm::vec2 lastMouse;
	ofParameter<glm::quat> curRot{"QuatRot", glm::quat(0, 1, 0, 0), glm::quat(-1, -1, -1, -1), glm::quat(1, 1, 1, 1)};
	void drawSceneQuat(); // taken from openFrameworks\examples\3d\quaternionArcballExample

	// tabs
	void drawGuiTabs();
	ofParameter<bool> bGui_Tabs{ "Tabs", true }; // using an ofParameter<bool>
	SurfingTabsManager tabs;

	// combo
	void drawGuiCombos();
	ofParameter<bool> bGui_Combos{ "Combos", true }; // using an ofParameter<bool>
	ofParameter<int> index{ "index", 0, 0, 0 };
	vector<string> names;

};
