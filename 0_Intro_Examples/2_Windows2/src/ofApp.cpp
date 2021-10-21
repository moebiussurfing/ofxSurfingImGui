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

	guiManager.addWindowSpecial(bGui_0);
	guiManager.addWindowSpecial(bGui_1);
	guiManager.addWindowSpecial(bGui_2);
	guiManager.addWindowSpecial(bGui_3);

	guiManager.initiatieSpecialWindows();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(32);

	guiManager.begin();
	{
		guiManager.drawSpecialWindowsPanels(); // -> Main Panels Controller
		
		if (guiManager.getSpecialWindowsEnableGlobal())
		{
			draw_SurfingWidgets0();
			draw_SurfingWidgets1();
			draw_SurfingWidgets2();
			draw_SurfingWidgets3();
		}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets0() {

	const int i = 0;
	if (guiManager.getVisible(i))
	{
		if (guiManager.beginWindowSpecial(i))
		{
			guiManager.AddGroup(params0);
		}
		guiManager.endWindowSpecial(i);
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets1() {

	const int i = 1;
	if (guiManager.getVisible(i))
	{
		if (guiManager.beginWindowSpecial(i))
		{
			guiManager.AddGroup(params1);
		}
		guiManager.endWindowSpecial(i);
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets2() {

	const int i = 2;
	if (guiManager.getVisible(i))
	{
		if (guiManager.beginWindowSpecial(i))
		{
			guiManager.AddGroup(params2);
		}
		guiManager.endWindowSpecial(i);
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets3() {

	const int i = 3;
	if (guiManager.getVisible(i))
	{
		if (guiManager.beginWindowSpecial(i))
		{
			guiManager.AddGroup(params3);
		}
		guiManager.endWindowSpecial(i);
	}
}
