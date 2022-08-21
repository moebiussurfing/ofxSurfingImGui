#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowPosition(-1920, 20);

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

	bGui.set("ofApp", true); // all the gui

	// the first window don't have a visible bool toggle,
	// and it's creating by passing a name, and drawn by passing his index when was created.
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
	ui.setName("ofApp"); // -> Recommended to set a name when using multiple instances of the Gui Manager!
	ui.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
	ui.setup();

	// when adding by name you need to use indexes when drawing the window!
	ui.addWindowSpecial("Window 1"); // using legacy style by name

	// when can add special windows passing the visible toggle by argument.
	// ofParameter name will be used to name the windows headers too.

	ui.addWindowSpecial(bGui_2);
	ui.addWindowSpecial(bGui_3);
	ui.addWindowSpecial(bGui_4);
	ui.addWindowSpecial(bGui_5);
	ui.addWindowSpecial(bGui_6);

	// bundle the object here too,
	// to group on the toggles too
	// we do not use beginWindowSpecial/endWindowSpecial methods.
	ui.addWindowSpecial(myClassObject.bGui);

	// all the window visible toggle states are auto handled between sessions.

	ui.startup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	buildHelpInfo();

	if (!bGui) return;

	ui.begin();
	{
		draw_MainWindow();

		draw_SurfingWidgets_1();
		draw_SurfingWidgets_2();
		draw_SurfingWidgets_3();
		draw_SurfingWidgets_4();
		draw_SurfingWidgets_5();
		draw_SurfingWidgets_6();
	}
	ui.end();

	//--

	//TODO:
	// link by anchor
	auto p = ui.getWindowSpecialLastTopRight();
	myClassObject.ui.setWindowSpecialFirstPosition(p);
	//myClassObject.ui.specialWindowsOrganizer.doReOrganize();
	//myClassObject.ui.specialWindowsOrganizer.doApplyLinkWindows();
	//myClassObject.ui.specialWindowsOrganizer.update();
	//myClassObject.ui.specialWindowsOrganizer.runShapeState(index);
	myClassObject.draw();
}

//--------------------------------------------------------------
void ofApp::draw_MainWindow() {

	if (ui.beginWindow(bGui))
	{
		ui.AddLabelBig("Main Window");

		// Some internal optional stuff,
		// as common toggles are exposed
		  
		// Special Windows Organizer toggle 
		ui.Add(ui.getWindowsSpecialsGuiToggle(), OFX_IM_TOGGLE_ROUNDED_MEDIUM);
		ui.AddSpacing();

		// Show global
		ui.Add(ui.getWindowsSpecialsGuiToggleAllGlobal(), OFX_IM_TOGGLE_ROUNDED);
		
		if (ui.getWindowsSpecialsGuiToggleAllGlobal()) {
			ui.AddSpacing();
			// Draw each Special Window toggle
			ui.drawWidgetsSpecialWindowsToggles(OFX_IM_CHECKBOX);
		}
		ui.AddSpacingSeparated();

		//-

		ui.AddLabelBig("Another ofxImGuiSurfing instance", false);
		ui.AddLabel("We can use many instances of the add-on simultaneously. Then we can combine multiple classes/add-ons without colliding their ImGui windows.", false);
		ui.Add(myClassObject.bGui, OFX_IM_TOGGLE_ROUNDED_BIG);
		ui.AddSpacingSeparated();

		//-
		
		ui.Add(ui.bHelp, OFX_IM_TOGGLE_ROUNDED);

		ui.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_1()
{
	// NOTICE that 
	// we need to recall and pass the index of this first window! 
	// That's because, instead of the other windows,
	// for this window, we queued the window by adding a name.
	// 
	// So, there's two ways of adding and drawing Special Windows: 
	// 1. by passing a bool param (acting as a visible toggle)
	// 2. by passing a name when adding and passing which index was to drawing!

	if (ui.beginWindowSpecial(0))
	{
		ui.AddLabelBig("> Special \nWindow 1", false);
		ui.Add(bPrevious0, OFX_IM_TOGGLE_BIG, 2, true);//next on same line
		ui.Add(bNext0, OFX_IM_TOGGLE_BIG, 2);
		ui.AddGroup(params_0);
		ui.Add(speed0, OFX_IM_VSLIDER_NO_LABELS); // hide labels

		ui.endWindowSpecial(0);
		//ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_2()
{
	if (!bGui_2) return;

	//// A. we can begin the window passing the index, that we want to remember!
	//if (ui.beginWindowSpecial(1)) 

	// B. but we can remember the name used on setup too.
	// it's the same that use the index 1. (as first starts with zero)

	if (ui.beginWindowSpecial(bGui_2))
	{
		ui.AddLabelBig("> Special \nWindow 2", false);
		ui.AddGroup(params_1);
		ui.Add(lineWidth1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
		ui.Add(separation1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
		ui.Add(shapeType1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
		ui.Add(size1, OFX_IM_VSLIDER_NO_LABELS, 4);

		ui.endWindowSpecial(bGui_2);
		//ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_3()
{
	if (!bGui_3) return;

	if (ui.beginWindowSpecial(bGui_3))
	{
		ui.AddLabelBig("> Special \nWindow 3", false);
		ui.Add(shapeType2, OFX_IM_KNOB, 2, true);
		ui.Add(amount2, OFX_IM_KNOB, 2);
		ui.Add(size2, OFX_IM_VSLIDER_NO_LABELS);
		ui.AddSpacingBigSeparated();
		ui.AddGroup(params_2);

		ui.endWindowSpecial(bGui_3);
		//ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_4()
{
	if (!bGui_4) return;

	if (ui.beginWindowSpecial(bGui_4))
	{
		ui.AddLabelBig("> Special \nWindow 4", false);
		ui.AddGroup(params_3);
		ui.AddSpacingSeparated();
		ui.Add(size2, OFX_IM_HSLIDER_BIG);
		ui.Add(lineWidth3, OFX_IM_HSLIDER);
		ui.Add(speed3, OFX_IM_HSLIDER_SMALL);
		ui.Add(separation3, OFX_IM_HSLIDER_MINI);

		ui.endWindowSpecial(bGui_4);
		//ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_5()
{
	if (!bGui_5) return;

	if (ui.beginWindowSpecial(bGui_5))
	{
		ui.AddLabelBig("> Special \nWindow 5", false);
		ui.Add(lineWidth1, OFX_IM_VSLIDER_NO_LABELS);

		ui.endWindowSpecial(bGui_5);
		//ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_6()
{
	if (!bGui_6) return;

	if (ui.beginWindowSpecial(bGui_6))
	{
		ui.AddLabelBig("> Special \nWindow 6", false);
		ui.Add(amount2, OFX_IM_KNOB);

		ui.endWindowSpecial(bGui_6);
		//ui.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (false) {}

	else if (key == 'g') {
		bGui = !bGui;
	}

	else if (key == '0') {
		ui.setWindowSpecialToggleVisibleAllGlobal();
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
	else if (key == '5') {
		ui.setWindowSpecialToggleVisible(4);
	}
	else if (key == '6') {
		ui.setWindowSpecialToggleVisible(5);
	}
}

//--------------------------------------------------------------
void ofApp::buildHelpInfo()
{
	// We can use an internal Help Manager on the Gui Manager

	helpInfo = "";
	helpInfo += "HELP ofApp \n\n";
	helpInfo += "13_SpecialWindowsAdvanced \n\n";
	helpInfo += "KEY COMMANDS \n\n";
	helpInfo += "g      GUI " + ofToString(bGui.get() ? "ON" : "OFF");

	if (bGui)
	{
		helpInfo += "\n\n";
		helpInfo += "0      GLOBAL VISIBLE " + ofToString(ui.getWindowSpecialVisibleGlobalState() ? "ON" : "OFF") + "\n";

		if (ui.getWindowSpecialVisibleGlobalState())
		{
			helpInfo += "\n";
			helpInfo += "1      WINDOW 1 " + ofToString(ui.getWindowSpecialVisibleState(0) ? "ON" : "OFF") + "\n";
			helpInfo += "2      WINDOW 2 " + ofToString(ui.getWindowSpecialVisibleState(1) ? "ON" : "OFF") + "\n";
			helpInfo += "3      WINDOW 3 " + ofToString(ui.getWindowSpecialVisibleState(2) ? "ON" : "OFF") + "\n";
			helpInfo += "4      WINDOW 4 " + ofToString(ui.getWindowSpecialVisibleState(3) ? "ON" : "OFF") + "\n";
			helpInfo += "5      WINDOW 5 " + ofToString(ui.getWindowSpecialVisibleState(4) ? "ON" : "OFF") + "\n";
			helpInfo += "6      WINDOW 6 " + ofToString(ui.getWindowSpecialVisibleState(5) ? "ON" : "OFF") + "\n";
		}
	}
	helpInfo += "\n\n";
	helpInfo += "DoubleClick to Edit/Lock \n";
	helpInfo += "LeftClick + RightClick to Close \n";

	ui.setHelpInfoApp(helpInfo);
}