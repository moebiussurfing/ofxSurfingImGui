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
	ofBackground(255);

	guiManager.begin();
	{
		if (bGui_0) draw_SurfingWidgets0();
		if (bGui_1) draw_SurfingWidgets1();
		if (bGui_2) draw_SurfingWidgets2();
		if (bGui_3) draw_SurfingWidgets3();

		// Panels toggles
		windowPanels.beginWindow("Panels", NULL, guiManager.bAutoResize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None);
		{
			guiManager.Add(guiManager.bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);
			windowPanels.drawWidgets();
			guiManager.Add(guiManager.bAutoResize);
			if (!guiManager.bMinimize) {
				guiManager.drawAdvanced();
			}
		}
		windowPanels.endWindow();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets0() {
	windowPanels.panels[0].runState();

	if (guiManager.beginWindow(bGui_0, guiManager.bAutoResize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None));
	{
		guiManager.AddGroup(params0);

		windowPanels.panels[0].getState();
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets1() {
	windowPanels.panels[1].runState();

	if (guiManager.beginWindow(bGui_1, guiManager.bAutoResize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None));
	{
		guiManager.AddGroup(params1);

		windowPanels.panels[1].getState();
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets2() {
	windowPanels.panels[2].runState();

	if (guiManager.beginWindow(bGui_2, guiManager.bAutoResize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None));
	{
		guiManager.AddGroup(params2);

		windowPanels.panels[2].getState();
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets3() {
	windowPanels.panels[3].runState();

	if (guiManager.beginWindow(bGui_3));
	{
		guiManager.AddGroup(params3);

		windowPanels.panels[3].getState();
	}
	guiManager.endWindow();
}
