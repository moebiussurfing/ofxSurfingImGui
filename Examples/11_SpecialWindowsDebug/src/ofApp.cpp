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

	// 1. Enable "Windows Special Organizer" mode
	// Called before setup!
	// (Can be commented, but Organizer Panel and the engine will be both disabled.)
	guiManager.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

	// 2. Common setup
	guiManager.setup();

	// 3. Add and queue "Special Windows" to the Organizer
	// Custom enablers names. 
	// These names will be used to name the windows too.
	// Internal bool toggles ofParams will be auto created too:
	// You just pass a name!

	// We customize the panel names. 
	// e.g: audio, video, advanced...etc
	guiManager.addWindowSpecial("myWindow 1");
	guiManager.addWindowSpecial("myWindow 2");
	guiManager.addWindowSpecial("myWindow 3");
	guiManager.addWindowSpecial("myWindow 4");

	//// 4. Optional: Customize names to help integrate into your App GUI's.
	//// Rename "Organizer" to a custom name.
	//guiManager.setNameWindowsSpecialsOrganizer("My Add-on");

	// 5. Startup
	// Called after windows has been added.
	guiManager.startup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui)return;

	guiManager.begin();
	{
		draw_MainWindow();

		//--

		draw_SurfingWidgets_1();
		draw_SurfingWidgets_2();
		draw_SurfingWidgets_3();
		draw_SurfingWidgets_4();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::draw_MainWindow() 
{
	float x = ofGetWidth() - 200;
	float y = 10;
	ImGuiCond flag = ImGuiCond_FirstUseEver;
	ImGui::SetNextWindowPos(ImVec2(x, y), flag);
	if (guiManager.beginWindow(bGui))
	{
		// Extra Panels
		// Useful for your own GUI's:

		//--

		// A. Toggles to show/hide Main panels.

		// "Special Windows Organizer" 
		guiManager.Add(guiManager.getWindowsSpecialsGuiToggle(), OFX_IM_TOGGLE_ROUNDED_MEDIUM);

		guiManager.AddSpacingSeparated();

		//--

		// B. Toggles to show/hide Special Windows / panels.

		guiManager.AddLabelBig("Special Windows");

		// 1. Global toggle
		guiManager.Add(guiManager.getWindowsSpecialsGuiToggleAllGlobal(), OFX_IM_TOGGLE_ROUNDED);
		guiManager.AddSpacing();

		// 2. Each Window toggle
		guiManager.drawWindowSpecialsGuiToggles();
		// We can also get each toggle instead too:
		//guiManager.Add(guiManager.getWindowSpecialGuiToggle(_index));
		//..

		//--

		// For internal debug purposes
		guiManager.Add(guiManager.bDebug, OFX_IM_TOGGLE_ROUNDED);
		if (guiManager.bDebug) guiManager.drawAdvanced();

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_1()
{
	// We begin the window like that,
	// passing which special window index is as argument.
	// This is the only attention  we must pay by our selfs.

	if (guiManager.beginWindowSpecial(0))
	{
		guiManager.AddLabelBig("> Window\nSpecial 1", false);
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
	if (guiManager.beginWindowSpecial(1))
	{
		guiManager.AddLabelBig("> Window\nSpecial 2", false);
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
	if (guiManager.beginWindowSpecial(2))
	{
		guiManager.AddLabelBig("> Window\nSpecial 3", false);
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
	if (guiManager.beginWindowSpecial(3))
	{
		guiManager.AddLabelBig("> Window\nSpecial 4", false);
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

	else if (key == '0') {
		guiManager.setWindowSpecialToggleVisibleAllGlobal();
	}
}