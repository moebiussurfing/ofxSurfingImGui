#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//--

	// Parameters

	params_0.setName("paramsGroup0");
	params_0.add(bEnable0.set("Enable0", false));
	params_0.add(speed0.set("speed0", 0.5, 0, 1));
	params_0.add(bPrevious0.set("<", false));
	params_0.add(bNext0.set(">", false));

	params_1.setName("paramsGroup1");
	params_1.add(bEnable1.set("Enable1", false));
	params_1.add(shapeType1.set("shapeType1", 0, -50, 50));
	params_1.add(size1.set("size1", 100, 0, 100));
	params_1.add(lineWidth1.set("lineWidth1", 0.5, 0, 1));
	params_1.add(separation1.set("separation1", 50, 1, 100));

	params_2.setName("paramsGroup2");
	params_2.add(bEnable2.set("Enable2", false));
	params_2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params_2.add(size2.set("size2", 100, 0, 100));
	params_2.add(amount2.set("amount2", 10, 0, 25));

	params_3.setName("paramsGroup3");
	params_3.add(bEnable3.set("Enable3", false));
	params_3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params_3.add(speed3.set("speed3", 0.5, 0, 1));
	params_3.add(separation3.set("separation3", 50, 1, 100));

	//--

	bGui.set("ofApp", true);

	bGui_2.set("Window 2", true);
	bGui_3.set("Window 3", true);
	bGui_4.set("Window 4", true);
	bGui_5.set("Window 5", true);
	bGui_6.set("Window 6", true);

	buildHelpInfo();

	//--

	setup_ImGui();
}

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	guiManager.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
	guiManager.setup();

	// when adding by name you need to use indexes when drawing the window!
	guiManager.addWindowSpecial("myWindow 1");//using legacy style by name

	// when can add special windows passing the visible toggle by argument.
	// ofParameter name will be used to name the windows headers too.

	guiManager.addWindowSpecial(bGui_2);
	guiManager.addWindowSpecial(bGui_3);
	guiManager.addWindowSpecial(bGui_4);
	guiManager.addWindowSpecial(bGui_5);
	guiManager.addWindowSpecial(bGui_6);

	// all the window visible toggle states are auto handled between sessions.

	guiManager.startup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	buildHelpInfo();

	if (!bGui) return;

	guiManager.begin();
	{
		draw_MainWindow();

		draw_SurfingWidgets_1();
		draw_SurfingWidgets_2();
		draw_SurfingWidgets_3();
		draw_SurfingWidgets_4();
		draw_SurfingWidgets_5();
		draw_SurfingWidgets_6();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::draw_MainWindow() {

	if (guiManager.beginWindow(bGui))
	{
		// Useful common toggles exposed:

		// "Special Windows Organizer" 
		guiManager.Add(guiManager.getWindowsSpecialsGuiToggle(), OFX_IM_TOGGLE_ROUNDED_MEDIUM);
		guiManager.Add(guiManager.bHelp, OFX_IM_TOGGLE_ROUNDED);
		guiManager.AddSpacingSeparated();

		// Show global
		guiManager.Add(guiManager.getWindowsSpecialsGuiToggleAllGlobal(), OFX_IM_TOGGLE_ROUNDED);
		guiManager.AddSpacingSeparated();

		// Draw each Special Window toggle
		guiManager.drawWindowSpecialsGuiToggles();

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_1()
{
	if (guiManager.beginWindowSpecial(0))
	{
		guiManager.AddLabelBig("> Window \n Special 1", false);
		guiManager.Add(bPrevious0, OFX_IM_TOGGLE_BIG, 2, true);//next on same line
		guiManager.Add(bNext0, OFX_IM_TOGGLE_BIG, 2);
		guiManager.AddGroup(params_0);
		guiManager.Add(speed0, OFX_IM_VSLIDER_NO_LABELS);// hide labels

		guiManager.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_2()
{
	if (!bGui_2) return;

	//// A. we can begin the window passing the index, that we want to remember!
	//if (guiManager.beginWindowSpecial(1)) 

	// B. but we can remember the name used on setup too.
	// it's the same that use the index 1. (as first starts with zero)

	if (guiManager.beginWindowSpecial(bGui_2))
	{
		guiManager.AddLabelBig("> Window \n Special 2", false);
		guiManager.AddGroup(params_1);
		guiManager.Add(lineWidth1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
		guiManager.Add(separation1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
		guiManager.Add(shapeType1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
		guiManager.Add(size1, OFX_IM_VSLIDER_NO_LABELS, 4);

		guiManager.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_3()
{
	if (!bGui_3) return;

	if (guiManager.beginWindowSpecial(bGui_3))
	{
		guiManager.AddLabelBig("> Window \n Special 3", false);
		guiManager.Add(shapeType2, OFX_IM_KNOB, 2, true);
		guiManager.Add(amount2, OFX_IM_KNOB, 2);
		guiManager.Add(size2, OFX_IM_VSLIDER_NO_LABELS);
		guiManager.AddSpacingBigSeparated();
		guiManager.AddGroup(params_2);

		guiManager.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_4()
{
	if (!bGui_4) return;

	if (guiManager.beginWindowSpecial(bGui_4))
	{
		guiManager.AddLabelBig("> Window \n Special 4", false);
		guiManager.AddGroup(params_3);
		guiManager.AddSpacingSeparated();
		guiManager.Add(size2, OFX_IM_HSLIDER_BIG);
		guiManager.Add(lineWidth3, OFX_IM_HSLIDER);
		guiManager.Add(speed3, OFX_IM_HSLIDER_SMALL);
		guiManager.Add(separation3, OFX_IM_HSLIDER_MINI);

		guiManager.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_5()
{
	if (!bGui_5) return;

	if (guiManager.beginWindowSpecial(bGui_5))
	{
		guiManager.AddLabelBig("> Window \nSpecial 5", false);
		guiManager.Add(lineWidth1, OFX_IM_VSLIDER_NO_LABELS);

		guiManager.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_6()
{
	if (!bGui_6) return;

	if (guiManager.beginWindowSpecial(bGui_6))
	{
		guiManager.AddLabelBig("> Window \n Special 6", false);
		guiManager.Add(amount2, OFX_IM_KNOB);
		guiManager.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (false) {}

	else if (key == 'g') {
		bGui = !bGui;
	}
	else if (key == '1') {
		guiManager.setWindowSpecialToggleVisible(0);
	}
	else if (key == '2') {
		guiManager.setWindowSpecialToggleVisible(1);
	}
	else if (key == '3') {
		guiManager.setWindowSpecialToggleVisible(2);
	}
	else if (key == '4') {
		guiManager.setWindowSpecialToggleVisible(3);
	}

	else if (key == '5') {
		guiManager.setWindowSpecialToggleVisible(4);
	}
	else if (key == '6') {
		guiManager.setWindowSpecialToggleVisible(5);
	}

	else if (key == '0') {
		guiManager.setWindowSpecialToggleVisibleAllGlobal();
	}
}

//--------------------------------------------------------------
void ofApp::buildHelpInfo()
{
	helpInfo = "";
	helpInfo += "HELP \n\n";
	helpInfo += "12_SpecialWindows2 \n";
	helpInfo += "\n";
	helpInfo += "KEY COMMANDS \n";
	helpInfo += "\n";
	helpInfo += "g      GUI " + ofToString(bGui.get() ? "ON" : "OFF");
	if (bGui)
	{
		helpInfo += "\n\n";
		helpInfo += "0      GLOBAL VISIBLE " + ofToString(guiManager.getWindowSpecialVisibleGlobalState() ? "ON" : "OFF") + "\n";
		if (guiManager.getWindowSpecialVisibleGlobalState())
		{
			helpInfo += "\n";
			helpInfo += "1      WINDOW 1 " + ofToString(guiManager.getWindowSpecialVisibleState(0) ? "ON" : "OFF") + "\n";
			helpInfo += "2      WINDOW 2 " + ofToString(guiManager.getWindowSpecialVisibleState(1) ? "ON" : "OFF") + "\n";
			helpInfo += "3      WINDOW 3 " + ofToString(guiManager.getWindowSpecialVisibleState(2) ? "ON" : "OFF") + "\n";
			helpInfo += "4      WINDOW 4 " + ofToString(guiManager.getWindowSpecialVisibleState(3) ? "ON" : "OFF") + "\n";
			helpInfo += "5      WINDOW 5 " + ofToString(guiManager.getWindowSpecialVisibleState(4) ? "ON" : "OFF") + "\n";
			helpInfo += "6      WINDOW 6 " + ofToString(guiManager.getWindowSpecialVisibleState(5) ? "ON" : "OFF") + "\n";
		}
	}
	helpInfo += "\n\n";
	helpInfo += "Double click to Edit/Lock \n";

	guiManager.setHelpInfoApp(helpInfo);
}