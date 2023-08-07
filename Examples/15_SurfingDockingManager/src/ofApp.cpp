#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofLogNotice(__FUNCTION__);

	//--

#ifdef SURF_IM
	ui.setup(ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING_RAW);
	ui.startup();
#endif

	//--

#ifndef SURF_IM
	bool autoDraw = true;
	ofxImGui::BaseTheme* theme = nullptr;

	ImGuiConfigFlags customFlags = ImGuiConfigFlags_DockingEnable;
	//customFlags |= ImGuiConfigFlags_ViewportsEnable;

	bool restoreGuiState = true;
	bool showImGuiMouseCursor = false;
	ui.setup(theme, autoDraw, customFlags, restoreGuiState, showImGuiMouseCursor);

	// Uncomment below to perform docking with SHIFT key
	// Gives a better user experience, matter of opinion.
	ImGui::GetIO().ConfigDockingWithShift = true;

	// Uncomment below to "force" all imgui windows to be standalone
	//ImGui::GetIO().ConfigViewportsNoAutoMerge = true;

	// Activate zoom feature with ctrl + mousewheel
	ImGui::GetIO().FontAllowUserScaling = true;
#endif

	//--

#ifdef SURF_IM
	manager.setup(ui.getGui());
#else
	manager.setup(ui);
#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 1));

	ofClear(ofColor::grey);

	//--

	if (!bGui) return;

	ui.begin();
	{
		manager.draw();
	}
	ui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ofLogNotice(__FUNCTION__) << char(key);

	if (key == 'g' || key == 'G') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ofLogNotice(__FUNCTION__);

	manager.exit();
}