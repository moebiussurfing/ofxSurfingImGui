
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"	

#include "ofxSurfingImGui.h"

#include "ofxWindowApp.h" // -> not required


// Docking help
// https://github.com/ocornut/imgui/issues/2109

// Docking demo
// https://github.com/ocornut/imgui/blob/1ad1429c6df657f9694b619d53fa0e65e482f32b/imgui_demo.cpp#L7399-L7408

// Toolbar example
// https://gist.github.com/moebiussurfing/b7652ba1ecbd583b7c4f18e25a598551


class ofApp : public ofBaseApp {

public:

	void setup();
	void draw();
	void exit();

	//-

	ofxSurfing_ImGui_Manager guiManager;

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

	//-

	bool binitiated = false;

	ofxWindowApp windowApp;
	
	//bool bOpen0 = true;
	//bool bOpen1 = true;
	//bool bOpen2 = true;
	//bool bOpen3 = true;
	//bool bOpen4 = true;

	ofParameter<bool> bOpen0{ "Window 0", true };
	ofParameter<bool> bOpen1{ "Window 1", true };
	ofParameter<bool> bOpen2{ "Window 2", true };
	ofParameter<bool> bOpen3{ "Window 3", true };
	ofParameter<bool> bOpen4{ "Window 4", true };

	bool bResetLayout = false;

	void drawMenu();

	void drawLayout();

	//----

	void dockingReset();
	void dockingPopulate();

	/*
	// Flags for ImGui::DockSpace()
	enum ImGuiDockNodeFlags_
	{
	ImGuiDockNodeFlags_None                         = 0,
	ImGuiDockNodeFlags_KeepAliveOnly                = 1 << 0,   // Don't display the dockspace node but keep it alive. Windows docked into this dockspace node won't be undocked.
	//ImGuiDockNodeFlags_NoCentralNode              = 1 << 1,   // Disable Central Node (the node which can stay empty)
	ImGuiDockNodeFlags_NoDockingInCentralNode       = 1 << 2,   // Disable docking inside the Central Node, which will be always kept empty. Note: when turned off, existing docked nodes will be preserved.
	ImGuiDockNodeFlags_NoSplit                      = 1 << 3,   // Disable splitting the node into smaller nodes. Useful e.g. when embedding dockspaces into a main root one (the root one may have splitting disabled to reduce confusion). Note: when turned off, existing splits will be preserved.
	ImGuiDockNodeFlags_NoResize                     = 1 << 4,   // Disable resizing child nodes using the splitter/separators. Useful with programatically setup dockspaces.
	ImGuiDockNodeFlags_PassthruCentralNode          = 1 << 5,   // Enable passthru dockspace: 1) DockSpace() will render a ImGuiCol_WindowBg background covering everything excepted the Central Node when empty. Meaning the host window should probably use SetNextWindowBgAlpha(0.0f) prior to Begin() when using this. 2) When Central Node is empty: let inputs pass-through + won't display a DockingEmptyBg background. See demo for details.
	ImGuiDockNodeFlags_AutoHideTabBar               = 1 << 6    // Tab bar will automatically hide when there is a single window in the dock node.
	};
	*/
};
