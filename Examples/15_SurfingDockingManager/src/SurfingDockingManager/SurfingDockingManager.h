// This class is a port from https://github.com/aiekick/ImTools/tree/main/LayoutManager
// coded by @aiekick. Thanks! 

#pragma once

#include "ofxSurfingImGui.h"
#include "MainFrame.h"

class SurfingDockingManager
{
public:
	SurfingDockingManager();
	~SurfingDockingManager();

	void setup(ofxImGui::Gui& ui);
	void init();
	void draw();
	void exit();

	ImVec2 size;

	MainFrame mainFrame;

	bool bDoneSetup = 0;
	bool bDoneInit = 0;
};