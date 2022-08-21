#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	bGui.set("ofApp", true);

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

	setup_ImGui();
}

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	// Setup, and Startup is auto called when addWindowsSpecial is called!
	// We can omit theme to speed up initialization.
	 
	// The internal steps are:
	//ui.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
	//ui.setup();
	//ui.addWindowSpecial(..
	//ui.addWindowSpecial(..
	//ui.startup();

	// Queue windows
	ui.addWindowSpecial("myWindow 1");
	ui.addWindowSpecial("myWindow 2");
	ui.addWindowSpecial("myWindow 3");
	ui.addWindowSpecial("myWindow 4");
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui)return;

	ui.begin();
	{
		draw_MainWindow();

		draw_SurfingWidgets_1();
		draw_SurfingWidgets_2();
		draw_SurfingWidgets_3();
		draw_SurfingWidgets_4();
	}
	ui.end();
}

//--------------------------------------------------------------
void ofApp::draw_MainWindow() {

	// Notice that this is a standard window,
	// not an special one with their features.

	if (ui.beginWindow(bGui))
	{
		// Some optional useful common toggles exposed
		 
		// Special Windows Organizer 
		ui.Add(ui.getWindowsSpecialsGuiToggle(), OFX_IM_TOGGLE_ROUNDED_MEDIUM);
		ui.AddSpacingSeparated();

		// Show global
		ui.Add(ui.getWindowsSpecialsGuiToggleAllGlobal(), OFX_IM_TOGGLE_ROUNDED_MEDIUM);
		if (ui.getWindowsSpecialsGuiToggleAllGlobal()) {
			// Draw each Special Window toggle
			ui.drawWidgetsSpecialWindowsToggles();
		}

		ui.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_1()
{
	if (ui.beginWindowSpecial(0))
	{
		ui.AddLabelBig("> Special\nWindow 1", false);
		ui.Add(bPrevious0, OFX_IM_TOGGLE_BIG, 2, true);//next on same line
		ui.Add(bNext0, OFX_IM_TOGGLE_BIG, 2);
		ui.AddGroup(params_0);
		ui.Add(speed0, OFX_IM_VSLIDER_NO_LABELS);// hide labels

		ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_2()
{
	if (ui.beginWindowSpecial(1))
	{
		ui.AddLabelBig("> Special\nWindow 2", false);
		ui.AddGroup(params_1);
		ui.Add(lineWidth1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
		ui.Add(separation1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
		ui.Add(shapeType1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
		ui.Add(size1, OFX_IM_VSLIDER_NO_LABELS, 4);

		ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_3()
{
	if (ui.beginWindowSpecial(2))
	{
		ui.AddLabelBig("> Special\nWindow 3", false);
		ui.Add(shapeType2, OFX_IM_KNOB, 2, true);
		ui.Add(amount2, OFX_IM_KNOB, 2);
		ui.Add(size2, OFX_IM_VSLIDER_NO_LABELS);
		ui.AddSpacingBigSeparated();
		ui.AddGroup(params_2);

		ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_4()
{
	if (ui.beginWindowSpecial(3))
	{
		ui.AddLabelBig("> Special\nWindow 4", false);
		ui.AddGroup(params_3);
		ui.AddSpacingSeparated();
		ui.Add(size2, OFX_IM_HSLIDER_BIG);
		ui.Add(lineWidth3, OFX_IM_HSLIDER);
		ui.Add(speed3, OFX_IM_HSLIDER_SMALL);
		ui.Add(separation3, OFX_IM_HSLIDER_MINI);

		ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == 'g') {
		bGui = !bGui;
	}
}