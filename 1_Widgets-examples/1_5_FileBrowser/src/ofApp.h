#pragma once

//https://github.com/aiekick/ImGuiFileDialog
//https://github.com/AirGuanZ/imgui-filebrowser -> another alternative


/*

TODO:
+ folder picker
+ better calback
+ add other browserclasses

*/


#include "ofMain.h"

#include "ofxSurfingImGui.h"
//#include "ofxSurfing_ImGui_WidgetsFileBrowser.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();

	ofxImGui::Gui gui;

	string strPath = "";
	string strPathName = "";
};
