#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	setupImGui();
}

//--------------------------------------------------------------
void ofApp::setupImGui()
{
	// Docking Raw mode
	// (Without Layout Presets engine)
	 
	// Setup steps:

	//--

	// 1. Initiate

	// NOTICE that
	// To enable the "raw docking" workflow
	// is mandatory to pass an argument: 
	ui.setup(IM_GUI_MODE_INSTANTIATED_DOCKING_RAW);

	ui.setAutoDockingMode(true);

	//--

	string s = "Shift drag windows \nto different windows zones to dock.";
	ui.setHelpAppText(s);

	//--

	// 2. Queue Special Windows

	// Add the "target" windows just with a name:
	// You will use these added windows easily, 
	// but you must remember his index order!
	// Each window will be added to the "Layout Presets Engine" and auto handled too.
	// The engine will auto create internal bool param toggles 
	// (like the bGui we used before)
	// to handle the show/hide window states.
	// Notice that is important to remember the index sorting when queuing!

	ui.addWindowSpecial("Window 0");
	ui.addWindowSpecial("Window 1");
	ui.addWindowSpecial("Window 2");
	ui.addWindowSpecial("Window 3");
	ui.addWindowSpecial("Window 4");

	// Extra windows to be auto included in windows menu
	ui.addWindowExtra(bGui);

	//--

	//TODO
	// Optional
	//ui.setUseMenu(false);//disable top menu

	//--

	// 3. Startup

	ui.startup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	// Gui Manager with Docking features:
	// In between here (Begin/End) 
	// we can render ImGui windows and widgets,
	// and all the docking magic.

	//--

	ui.Begin();
	{
#ifndef SURFING__DOCKING_WORKFLOW_HANDLER_AUTODOCKING
		// 1. Docking magic
		// Not required to call manually when we don't need to use some docking stuff,
		// like reseting or hard coding a layout by code.
		// So it's auto handled internally also! 
		ui.BeginDocking();
		ui.EndDocking();
#endif

		//--

		// 2.2 Populate the visible toggles

		drawImGuiApp();

		//--

		// 3. The Special Windows 

		// The windows previously queued to the manager on setup(),
		// that are controlled by the Layout Presets Engine.
		// Render ImGui Windows and Widgets now!
		drawImGuiSpecialWindows();
	}
	ui.End();
}

//----

//--------------------------------------------------------------
void ofApp::drawImGuiApp()
{
	// For all the queued especial windows in setup()!
	if (ui.BeginWindow(bGui))
	{
		ui.AddMinimizerToggle();
		ui.AddMenuBarToggle();
		ui.drawWidgetsSpecialWindowsManager();

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindows()
{
	drawImGuiSpecialWindow0();
	drawImGuiSpecialWindow1();
	drawImGuiSpecialWindow2();
	drawImGuiSpecialWindow3();
	drawImGuiSpecialWindow4();
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow0()
{
	// fix to forcing a minimum width for empty window. 
	// as they are auto resized as default.
	if (ui.getIsWindowSpecialVisible(0)) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

	if (ui.BeginWindowSpecial(0))
	{
		ui.AddLabelHuge("Window 0");
		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow1()
{
	if (ui.getIsWindowSpecialVisible(1)) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

	if (ui.BeginWindowSpecial(1))
	{
		ui.AddLabelHuge("Window 1");
		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow2()
{
	if (ui.getIsWindowSpecialVisible(2)) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

	if (ui.BeginWindowSpecial(2))
	{
		ui.AddLabelHuge("Window 2");
		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow3()
{
	//if (ui.getIsWindowSpecialVisible(3)) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

	if (ui.BeginWindowSpecial(3))
	{
		ui.AddLabelHuge("Window 3");
		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow4()
{
	//if (ui.getIsWindowSpecialVisible(4)) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

	if (ui.BeginWindowSpecial(4))
	{
		ui.AddLabelHuge("Window 4");
		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}
