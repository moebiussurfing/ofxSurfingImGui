#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//ofSetWindowPosition(-1920, 25);
	//ofSetWindowShape(1920, 1080 - 25);

	//--

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
	/*

		NOTE:

		The "Special Windows Organizer".
		Speeds Up the creation of ImGui windows.
		An Internal bool toggle (commonly named as bGui in other examples)
		will be auto created for each added Special Window.
		Another window called "Organizer" (by default) will be auto drawn!
		This happens internally, and we don't need to handle that.
		It's a panel who controls all the special windows.

		Features: Creates toggles and controls

		- Show / Hide each queued Special Window.
		- Show / Hide all/none.
		- Align windows as vertical or horizontal cascade.
		- Custom spacing between windows, hide headers...
		- Lock sizes between windows
		- Debug positions.

	*/

	// Currently these steps 1-2-(4)-5 can be omitted:

	/*
	// 1. Enable "Windows Special Organizer" mode
	// Called before setup!
	// (Can be commented, but Organizer Panel and the engine will be both disabled.)
	ui.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

	// 2. Common setup
	ui.setup();
	*/

	// 3. Add and queue "Special Windows" to the Organizer
	// Custom enablers names. 
	// These names will be used to name the windows too.
	// Internal bool toggles ofParams will be auto created too:
	// You just pass a name!

	// We customize the panel names. 
	// e.g: audio, video, advanced...etc
	ui.addWindowSpecial("myWindow 1");
	ui.addWindowSpecial("myWindow 2");
	ui.addWindowSpecial("myWindow 3");
	ui.addWindowSpecial("myWindow 4");

	/*
	//// 4. Optional: Customize names to help integrate into your App GUI's.
	//// Rename "Organizer" to a custom name.
	//ui.setNameWindowsSpecialsOrganizer("My Add-on");

	// 5. Startup
	// Called after windows has been added.
	ui.startup();
	*/
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return;

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
void ofApp::draw_MainWindow()
{
	// Optional: set an initial position
	if (bGui) 
	{
		float x = ofGetWidth() - 200;
		float y = 10;
		ImGuiCond flag = ImGuiCond_FirstUseEver;
		ImGui::SetNextWindowPos(ImVec2(x, y), flag);
	}

	if (ui.beginWindow(bGui))
	{
		// Extra Panels
		// Useful for your own GUI's:

		//--

		// A. Toggles to show/hide Main panels.

		// "Special Windows Organizer" 
		ui.Add(ui.getWindowsSpecialsGuiToggle(), OFX_IM_TOGGLE_ROUNDED_MEDIUM);

		ui.AddSpacingSeparated();

		//--

		// B. Toggles to show/hide Special Windows / panels.

		ui.AddLabelBig("Special Windows");

		// 1. Global toggle
		ui.Add(ui.getWindowsSpecialsGuiToggleAllGlobal(), OFX_IM_TOGGLE_ROUNDED_MEDIUM);
		ui.AddSpacing();

		// 2. Each Window toggle
		if (ui.getWindowsSpecialsGuiToggleAllGlobal())
			ui.drawWidgetsSpecialWindowsToggles();
		// We can also get each toggle instead too:
		//ui.Add(ui.getWindowSpecialGuiToggle(_index));
		//..

		//--

		ui.AddSpacingBigSeparated();

		// For internal debug purposes
		ui.Add(ui.bDebug, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
		if (ui.bDebug) ui.drawAdvanced();

		ui.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_1()
{
	// We begin the window like that,
	// passing which special window index is as argument.
	// This is the only attention  we must pay by our selfs.

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

	if (false) {}

	else if (key == 'g') {
		bGui = !bGui;
	}

	else if (key == '1') {
		ui.setWindowSpecialToggleVisible(0);
	}
	else if (key == '2') {
		ui.setWindowSpecialToggleVisible(1);
	}
	else if (key == '3') {
		ui.setWindowSpecialToggleVisible(2);
	}
	else if (key == '4') {
		ui.setWindowSpecialToggleVisible(3);
	}

	else if (key == '0') {
		ui.setWindowSpecialToggleVisibleAllGlobal();
	}
}