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

	//--

	string s = "Shift drag windows \nto different windows zones to dock.";
	ui.setHelpAppText(s);
	ui.setEnableHelpInternal();

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

	ui.addWindowExtra(bGui_DockingHelp);

	//--

	// Optional
	//ui.setUseMenu(false);//disable top menu

	//--

	// 3. Startup

	ui.startup();
}

//--------------------------------------------------------------
void ofApp::update()
{

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
		// 1. Docking magic

		// We can access all the docking space
		// here (between BeginDocking/EndDocking)
		// but just after the main ui.Begin call.
		// This snippet it's required to be copied into our projects.

		ui.BeginDocking();
		{
			// Our custom docking related functions goes here,
			// to customize the docking layout on runtime by code.
			updateImGuiDockingHelpers();
		}
		ui.EndDocking();

		//----


		// 2.1 An extra window with helpers

		// An extra window with some triggers
		// for hard-coded layout modifications.
		drawImGuiDockingHelp();

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

		ui.AddSpacingSeparated();
		ui.Add(bGui_DockingHelp, OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK);
		
		ui.DrawWidgetsGlobalScaleMini();
		
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

		//raw imgui
		static float v = 0;
		if (ImGui::Button("Button")) {
			v = 0;
			ui.AddToNotifier("Button Window0", OF_LOG_WARNING);
		}
		if(ImGui::SliderFloat("Slider", &v, 0, 1)){
			ui.AddToLog("Slider Window0 " + ofToString(v), OF_LOG_NOTICE);
		}
		ImGui::Text("Text");
		
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

		//raw imgui
		static float v = 0;
		if (ImGui::Button("Button")) {
			v = 0;
			ui.AddToNotifier("Button Window1", OF_LOG_WARNING);
		}
		if(ImGui::SliderFloat("Slider", &v, 0, 1))
		{
			ui.AddToLog("Slider Window1" + ofToString(v), OF_LOG_WARNING);
		}
		ImGui::Text("Text");

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

		//raw imgui
		static float v = 0;
		if (ImGui::Button("Button")) {
			v = 0;
			ui.AddToNotifier("Button Window2", OF_LOG_WARNING);
		}
		if(ImGui::SliderFloat("Slider", &v, 0, 1)){
			ui.AddToLog("Slider Window2 " + ofToString(v), OF_LOG_ERROR);
		}
		ImGui::Text("Text");

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

		//raw imgui
		static float v = 0;
		if (ImGui::Button("Button")) {
			v = 0;
			ui.AddToNotifier("Button Window3", OF_LOG_WARNING);
		}
		if(ImGui::SliderFloat("Slider", &v, 0, 1)){
			ui.AddToNotifier("Slider Window3 " + ofToString(v), OF_LOG_NOTICE);
		}
		ImGui::Text("Text");

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

		//raw imgui
		static float v = 0;
		if (ImGui::Button("Button")) {
			v = 0;
			ui.AddToNotifier("Button Window4", OF_LOG_WARNING);
		}
		if(ImGui::SliderFloat("Slider", &v, 0, 1)){
			ui.AddToNotifier("Slider Window4 " + ofToString(v), OF_LOG_NOTICE);
		}
		ImGui::Text("Text");

		ui.EndWindowSpecial();
	}
}

////--------------------------------------------------------------
//void ofApp::keyPressed(int key)
//{
//	if (key == 'g') bGui = !bGui;
//
//	if (key == OF_KEY_BACKSPACE) bFlagDockingReset = true;
//}

//----

// Useful Docking snippets

// On runtime, the user session could design his layout using shift+mouse dragging.
// But we can setup the docking layout using hard-coded methods.

//--------------------------------------------------------------
void ofApp::updateImGuiDockingHelpers()
{
	// Reset layout by a button
	if (bFlagDockingReset)
	{
		bFlagDockingReset = false;

		doDockingReset();
	}
}

//----

// Custom Helpers widgets

//--------------------------------------------------------------
void ofApp::drawImGuiDockingHelp()
{
	if (!bGui_DockingHelp) return;

	string s;

	//TODO: Fix sizing bug
	IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

	if (ui.BeginWindow(bGui_DockingHelp))
	{
		//--

		s = "Layout";
		ui.AddLabelBig(s);

		// Reset docking layout

		if (ui.AddButton("Reset", OFX_IM_BUTTON))
		{
			bFlagDockingReset = true;
			// Flag to call on a precise draw point,
			// inside the draw begin/end context
		}
		s = "Layout Reset Docking \nto a hard-coded layout.";
		ui.AddTooltip(s);

		ui.AddSpacingSeparated();

		//--

		s = "Manager";
		ui.AddLabelBig(s);

		if (ui.AddButton("Load", OFX_IM_BUTTON_SMALL, 2))
		{
			ui.loadLayout(path);
		}
		ui.SameLine();

		if (ui.AddButton("Save", OFX_IM_BUTTON_SMALL, 2))
		{
			ui.saveLayout(path);
		}

		ui.AddSpacingSeparated();

		//--

		s = "Internal";
		ui.AddLabelBig(s);
		ui.DrawInternalToggles();

		ui.EndWindow();
	}
}

// Custom Helpers functions

//--------------------------------------------------------------
void ofApp::doDockingReset()
{
	ofLogNotice(__FUNCTION__);

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
	ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	// Split the dockspace into 2 nodes --
	// DockBuilderSplitNode takes in the following args in the following order
	// window ID to split, direction, fraction (between 0 and 1),
	// the final two setting let's us choose which id we want (which ever one we DON'T set as NULL,
	// will be returned by the function)
	// out_id_at_dir is the id of the node in the direction we specified earlier,
	// out_id_at_opposite_dir is in the opposite direction

	// Fixed sizes
	const float v1 = 0.2f;
	const float v2 = 0.34f;
	const float v3 = 0.13f;
	const float v4 = 0.13f;

	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, v1, nullptr, &dockspace_id);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, v2, nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, v3, nullptr, &dockspace_id);
	auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, v4, nullptr, &dockspace_id);

	//--

	// We now dock our windows into the docking node we made above

	// We can get the window names by the index to rename easy, just in one place when added on setup.
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(0).c_str(), dock_id_left);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(1).c_str(), dock_id_right);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(2).c_str(), dock_id_right);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(3).c_str(), dock_id_top);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(4).c_str(), dock_id_down);

	ImGui::DockBuilderFinish(dockspace_id);
}


//--------------------------------------------------------------
void ofApp::exit(){
	
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::lostFocus(){
	
}

//--------------------------------------------------------------
void ofApp::gotFocus(){
	
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){
	
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
	
}

//--------------------------------------------------------------
void ofApp::launchedWithURL(std::string url){
	
}
