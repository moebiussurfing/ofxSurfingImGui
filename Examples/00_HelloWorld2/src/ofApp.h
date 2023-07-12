#pragma once

/*

	TO LEARN A BIT MORE
	ABOUT THE API:

	- Spacing and separators.
	- Commonly useful minimizer toggle.
	- Tool-tips for widgets.
	- The Log and Notifier Windows.
	- Custom Log tags.
	- Mouse over gui getter.
	- Note persistence of previous sessions for some settings.
	- Text labels.
	- Some key-commands examples.
	- Make blink widgets.
	- Make font bigger on widgets.
	- Set a widget inactive.
	- Reset UI methods.
	- Quaternion parameter.

*/


//----


#include "ofMain.h"

#include "ofxSurfingImGui.h"

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
	void drawGui();

	void drawGuiMain();
	ofParameter<bool> bGui{ "ofApp", true };
	ofParameter<bool> bEnable{ "Enable", true };
	ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
	ofEventListener listener;
	ofParameterGroup params{ "MyGroup", bEnable, speed };

	// Custom Log tags
	string myTag1 = "HELLO WORLD";
	string myTag2 = "MOUSE CLICK";

	// Taken from openFrameworks\examples\3d\quaternionArcballExample
	void drawSceneQuat();
	void drawGuiQuat();
	bool bGui_Quat = false;
	float dampen = .4f;
	glm::vec2 lastMouse;
	ofParameter<glm::quat> curRot{"QuatRot", glm::quat(0, 1, 0, 0), 
		glm::quat(-1, -1, -1, -1), glm::quat(1, 1, 1, 1)};
};
