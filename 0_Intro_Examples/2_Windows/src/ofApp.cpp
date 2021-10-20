#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(1920, 25);

	// Parameters
	params0.setName("paramsGroup0");
	params1.setName("paramsGroup1");
	params2.setName("paramsGroup2");
	params3.setName("paramsGroup3");

	params0.add(bEnable0.set("Enable0", false));
	params0.add(speed0.set("speed0", 0.5, 0, 1));
	params0.add(bPrevious0.set("<", false));
	params0.add(bNext0.set(">", false));

	params1.add(bEnable1.set("Enable1", false));
	params1.add(shapeType1.set("shapeType1", 0, -50, 50));
	params1.add(size1.set("size1", 100, 0, 100));
	params1.add(lineWidth1.set("lineWidth1", 0.5, 0, 1));
	params1.add(separation1.set("separation1", 50, 1, 100));

	params2.add(bEnable2.set("Enable2", false));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));

	params3.add(bEnable3.set("Enable3", false));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));

	setup_ImGui();
}

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	bGui_0.set("Window 0", true);
	bGui_1.set("Window 1", true);
	bGui_2.set("Window 2", true);
	bGui_3.set("Window 3", true);

	windowPanels.add(bGui_0);
	windowPanels.add(bGui_1);
	windowPanels.add(bGui_2);
	windowPanels.add(bGui_3);

	windowPanels.initiate();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(32);
	//ofBackground(255);

	guiManager.begin();
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;

		// Panels Toggles
		windowPanels.beginWindow("Panels", NULL, flags);
		{
			guiManager.Add(guiManager.bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);
			guiManager.Add(guiManager.bAutoResize, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);

			windowPanels.drawWidgets();

			if (!guiManager.bMinimize)
			{
				guiManager.drawAdvanced();
			}
		}
		windowPanels.endWindow();

		//--

		if (windowPanels.bEnable)
		{
			if (bGui_0) draw_SurfingWidgets0();
			if (bGui_1) draw_SurfingWidgets1();
			if (bGui_2) draw_SurfingWidgets2();
			if (bGui_3) draw_SurfingWidgets3();
		}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets0() {
	windowPanels.runState(0);

	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (windowPanels.bHeaders) flags += ImGuiWindowFlags_NoDecoration;
	if (guiManager.bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;
	
	windowPanels.checkWidthMax();

	if (guiManager.beginWindow(bGui_0, flags));
	{
		guiManager.AddGroup(params0);

		windowPanels.getState(0);
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets1() {
	windowPanels.runState(1);

	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (windowPanels.bHeaders) flags += ImGuiWindowFlags_NoDecoration;
	if (guiManager.bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;

	windowPanels.checkWidthMax();

	if (guiManager.beginWindow(bGui_1, flags));
	{
		guiManager.AddGroup(params1);

		windowPanels.getState(1);
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets2() {
	windowPanels.runState(2);

	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (windowPanels.bHeaders) flags += ImGuiWindowFlags_NoDecoration;
	if (guiManager.bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;

	windowPanels.checkWidthMax();

	if (guiManager.beginWindow(bGui_2, flags));
	{
		guiManager.AddGroup(params2);

		windowPanels.getState(2);
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets3() {
	windowPanels.runState(3);

	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (windowPanels.bHeaders) flags += ImGuiWindowFlags_NoDecoration;
	if (guiManager.bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;

	windowPanels.checkWidthMax();

	if (guiManager.beginWindow(bGui_3, flags));
	{
		guiManager.AddGroup(params3);

		windowPanels.getState(3);
	}
	guiManager.endWindow();
}
