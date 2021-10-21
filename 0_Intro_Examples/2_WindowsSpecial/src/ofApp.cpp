#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetWindowPosition(1920, 25);

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

	//-

	setup_ImGui();
}

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	// Add special windows
	guiManager.addWindowSpecial("myWindow 0"); // -> Custom enablers names
	guiManager.addWindowSpecial("myWindow 1");
	guiManager.addWindowSpecial("myWindow 2");
	guiManager.addWindowSpecial("myWindow 3");

	//// Customize names
	//guiManager.setNamePanelWindowsSpecial("Example Windows");
	//guiManager.setNameGlobalPanelWindowsSpecial("Enable Global");

	// Startup
	guiManager.initiatieWindowsSpecial();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(32);

	guiManager.begin();
	{
		draw_SurfingWidgets0();
		draw_SurfingWidgets1();
		draw_SurfingWidgets2();
		draw_SurfingWidgets3();

		//-

		//ImGui::Begin("TEST");
		//ofxImGuiSurfing::AddParameter(guiManager.getWindowsSpecialGui());
		//ImGui::End();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets0() {

	if (guiManager.beginWindowSpecial(0))
	{
		guiManager.AddGroup(params0);
	}
	guiManager.endWindowSpecial(0);
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets1() {

	if (guiManager.beginWindowSpecial(1))
	{
		guiManager.AddGroup(params1);
	}
	guiManager.endWindowSpecial(1);
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets2() {

	if (guiManager.beginWindowSpecial(2))
	{
		guiManager.AddGroup(params2);
	}
	guiManager.endWindowSpecial(2);
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets3() {

	if (guiManager.beginWindowSpecial(3))
	{
		guiManager.AddGroup(params3);
	}
	guiManager.endWindowSpecial(3);
}
