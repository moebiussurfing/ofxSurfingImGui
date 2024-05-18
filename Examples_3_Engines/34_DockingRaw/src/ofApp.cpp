#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	setupParameters();

	cam.setupPerspective();
	cam.setNearClip(0.0001);
	cam.setFarClip(1000);
	cam.setDistance(35);
	cam.lookAt(glm::vec3(0, 0, 0));

	//--

	setupImGui();
}

//--------------------------------------------------------------
void ofApp::setupParameters() {
	params1.setName("paramsGroup1");
	params1.add(speed.set("speed1", 0.5f, 0, 1));
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", true));
	params1.add(bMode1.set("bMode1", false));
	params1.add(bMode2.set("bMode2", true));
	params1.add(bMode3.set("bMode3", false));
	params1.add(bMode4.set("bMode4", false));
	params1.add(lineWidth.set("width1", 0.5f, 0, 1));
	params1.add(separation.set("sep1", 50, 1, 100));
	params1.add(shapeType.set("shape1", 0, -50, 50));
	params1.add(size.set("size1", 100, 0, 100));
	params1.add(amount.set("amount1", 10, 0, 25));

	params2.setName("paramsGroup2");
	params2.add(shapeType2.set("shape2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amnt2", 10, 0, 25));

	params3.setName("paramsGroup3");
	params3.add(lineWidth3.set("width3", 0.5f, 0, 1));
	params3.add(separation3.set("sep3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
}

//--------------------------------------------------------------
void ofApp::setupImGui() {
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

	// 2. Queue Special Windows

	// Add the "target" windows just with a name:
	// You will use these added windows easily,
	// but you must remember his index order!
	// Each window will be added to the "Layout Presets Engine" and auto handled too.
	// The engine will auto create internal bool param toggles
	// (like the bGui we used before)
	// to handle the show/hide window states.
	// Notice that is important to remember the index sorting when queuing!

	ui.addWindowSpecial("Main"); // index 0
	ui.addWindowSpecial("Audio"); // index 1
	ui.addWindowSpecial("Video1"); // index 2
	ui.addWindowSpecial("Video2"); // index 3
	ui.addWindowSpecial("Expert"); // index 4

	// Extra windows to be auto included in windows menu
	ui.addWindowExtra(bGui);
	ui.addWindowExtra(bGui_DockingHelp);

	//--

	// 3. Startup:

	ui.startup();

	//--

	// Optional:
	// After startup

	//--

	// Customize Help info

	// App
	string s = "This is an Example to learn \nthe Docking features.\n";
	s += "\nShift drag windows \nto different windows zones to dock.\n";
	s += "\nEnjoy!";

	//ui.setEnableHelpApp();//not required if text settled after
	ui.setHelpAppTitle("Example 23_DockingRaw");
	ui.setHelpAppText(s);

	// Internal
	ui.setEnableHelpInternal(); //disabled/hidden by default
}

//--------------------------------------------------------------
void ofApp::draw() {
	updateScene();
	drawScene();

	//----

	drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui() {
	// Gui Manager with Docking features:
	// In between here (Begin/End)
	// we can render ImGui windows and widgets,
	// and all the docking magic.

	//--

	ui.Begin();
	{
		//--

		// 1. Docking magic

		// We can access all the docking space
		// here (between BeginDocking/EndDocking)
		// but just after the main ui.Begin call.
		// This snippet it's required to be copied into our projects.

		ui.BeginDocking();
		{
			// Our custom docking related functions
			// to customize the docking layout on runtime by code.
			updateImGuiDockingHelpers();
		}
		ui.EndDocking();

		//----

		// 2.1 An extra window with helpers

		// An extra window with some triggers
		// for hard-coded layout modifications.
		if (bGui_DockingHelp) drawImGuiDockingHelp();

		//--

		// 2.2 Populate the visible toggles
		drawImGuiApp();

		//--

		// 3. The Special Windows

		// The windows previously queued to the manager on setup(),
		// that are controlled by the Layout Presets Engine.
		// Render ImGui Windows and Widgets now!
		{
			drawImGuiSpecialWindows();
		}

		//--
	}
	ui.End();
}

//----

//--------------------------------------------------------------
void ofApp::drawImGuiApp() {
	// for all the queued especial windows in setup()!
	if (ui.BeginWindow(bGui)) {
		ui.drawWidgetsSpecialWindowsManager();
		ui.AddSpacingSeparated();

		ui.Add(bGui_DockingHelp, OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK);
		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindows() {

	drawImGuiSpecialWindow0();

	//--

	drawImGuiSpecialWindow1();

	//--

	drawImGuiSpecialWindow2();

	//--

	drawImGuiSpecialWindow3();

	//--

	drawImGuiSpecialWindow4();
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow0() {

	if (ui.BeginWindowSpecial(0)) {
		ui.AddLabelHuge("Window 0", false);

		ui.Add(bGui_DockingHelp, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

		ui.Add(ui.bHelp, OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG);
		ui.AddTooltip("Help enables some Tooltips \nand the Help Box on this Window!");
		ui.Add(bEnable, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);
		ui.AddTooltip("Activate sep1 animation");
		ui.AddTooltip("This is a Help Tool tip! \nIt's " + (string)(bEnable ? "TRUE" : "FALSE"));
		ui.Add(ui.bLog, OFX_IM_TOGGLE_BIG_BORDER);
		ui.AddTooltip("Show Log Window");

		ui.AddSpacingBigSeparated();

		ui.Add(speed, OFX_IM_HSLIDER_BIG);
		ui.AddTooltip("Speed controls the auto populated Log window speed");
		ui.Add(amount, OFX_IM_HSLIDER);
		ui.AddTooltip("Speed up separation animator \nwhen bEnable is TRUE");

		ui.AddSpacingBigSeparated();

		ImGui::PushButtonRepeat(true); // pushing for repeats trigs
		{
			ui.refreshLayout();

			if (ui.Add(bPrevious, OFX_IM_BUTTON_BIG, 2)) {
				bPrevious = false;

				lineWidth -= 0.1f;
				lineWidth = ofClamp(lineWidth, lineWidth.getMin(), lineWidth.getMax());
			}
			ui.AddTooltip("Decrease lineWidth " + ofToString(lineWidth));

			ImGui::SameLine();

			if (ui.Add(bNext, OFX_IM_BUTTON_BIG, 2)) {
				bNext = false;

				lineWidth += 0.1f;
				lineWidth = ofClamp(lineWidth, lineWidth.getMin(), lineWidth.getMax());
			}
			ui.AddTooltip("Increase lineWidth " + ofToString(lineWidth));
		}
		ImGui::PopButtonRepeat();

		ui.AddSpacingBigSeparated();

		ui.Add(lineWidth, OFX_IM_HSLIDER_SMALL);
		ui.AddTooltip(ofToString(lineWidth));
		ui.Add(lineWidth);
		ui.AddTooltip(ofToString(lineWidth));
		ui.Add(lineWidth, OFX_IM_STEPPER);
		ui.AddTooltip(ofToString(lineWidth));
		ui.Add(lineWidth, OFX_IM_KNOB_DOTKNOB);
		ui.AddTooltip(ofToString(lineWidth));

		ui.AddSpacingBigSeparated();

		ui.Add(separation, OFX_IM_HSLIDER_BIG); // default style
		ui.AddTooltip(ofToString(separation));

		//--

		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow1() {

	if (ui.BeginWindowSpecial(1)) {
		ui.AddLabelHuge("Window 1", false);
		ui.Add(bGui_DockingHelp, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
		ui.AddGroup(params1);

		//--

		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow2() {
	/*
		// Constraints do not works on docking!
		if (ui.getIsWindowSpecialVisible(index))
		{
			IMGUI_SUGAR__WINDOWS_CONSTRAINTSW;
		}
		*/

	if (ui.BeginWindowSpecial(2)) {
		ui.BeginColumns(4);

		ui.AddLabelHuge("Window 2", false);
		ui.NextColumn();

		ui.Add(bGui_DockingHelp, OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK);
		ui.NextColumn();

		ui.AddGroup(params2, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_DEFAULT);
		ui.NextColumn();

		// Tabs
		if (ImGui::BeginTabBar("_myTabs")) {
			if (ImGui::BeginTabItem("Video")) {
				ui.AddLabelBig("Blah Blah");
				string str = R"(
Lorem Ipsum is simply dummy text of the printing and typesetting industry.Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.
)";
				ui.AddLabel(str.c_str());
				ui.AddSpacingBigSeparated();
				ui.AddGroup(params1);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Audio")) {
				ui.AddSpacingBig();
				ui.AddLabelHuge("Blah Blah");
				string str = R"(
It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
)";
				ui.AddLabelBig(str.c_str());

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Controls")) {
				ui.AddSpacingBig();
				ui.AddLabelHuge("Pump Up");
				ui.AddLabelBig("the Volume!");
				ui.AddSpacingBig();

				ui.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_HIDDEN_HEADER);

				ui.DrawAdvancedBundle();

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ui.EndColumns();

		//--

		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow3() {
	if (ui.BeginWindowSpecial(3)) {
		ui.BeginColumns(3);
		ui.AddLabelHuge("Window 3");
		ui.AddSpacingBig();
		ui.NextColumn();

		ui.Add(bGui_DockingHelp, OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK);
		ui.AddLabelHuge("Hello, down Huge!", false, true);
		ui.NextColumn();

		ui.AddLabelBig("Hello, down Big!", false, true);
		ui.AddLabelBig("Hello, down Big! \nHello, down! Hello, down!");
		ui.AddLabelBig("Hello, down Big!", false, true);
		ui.EndColumns();

		ui.AddSpacingHugeSeparated();

		ui.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_HIDDEN_HEADER);
		ui.AddLabelHuge("Hello, down Huge! \nHello, down! Hello, down!");

		//--

		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindow4() {
	//TODO: Fix sizing bug
	if (ui.getIsWindowSpecialVisible(4)) {
		IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;
	}

	if (ui.BeginWindowSpecial(4)) {
		ui.AddLabelHuge("Window 4", false);

		ui.BeginColumns(3);

		ui.Add(bGui_DockingHelp, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
		ui.AddLabelHuge("Hello, left Huge!", true, true);
		ui.NextColumn();

		ui.AddLabelHuge("Hello, left Huge!", false, false);
		ui.AddLabelBig("Hello, left Big!");
		ui.NextColumn();

		ui.AddLabel("Hello, left!", false, true);
		ui.AddLabelBig("Hello, left Big!", false);
		ui.EndColumns();

		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//ofLogNotice(__FUNCTION__) << " " << char(key);

	if (key == 'g') bGui = !bGui;
	if (key == ' ') bFlagDockingRandom = true;
	if (key == OF_KEY_BACKSPACE) bFlagDockingReset = true;
}

//----

// Useful Docking snippets

// On runtime, the user session could design his layout using shift+mouse dragging.
// But we can setup the docking layout using hard-coded methods.

//--------------------------------------------------------------
void ofApp::updateImGuiDockingHelpers() {
#if 0
	// Reset layout once o startup/first frame call.
	// Called only once!
	if (bModeDockingResetAtStartup)
	{
		static bool b = false;
		if (!b) {
			b = true;

			doDockingReset();
		}
	}
#endif

	//----

	// Reset layout by a button
	if (bFlagDockingReset) {
		bFlagDockingReset = false;

		doDockingReset();
	}

	//--

	// Random layout by a button
	if (bFlagDockingRandom) {
		bFlagDockingRandom = false;

		doDockingRandom();
	}
}

//----

// Scene

//--------------------------------------------------------------
void ofApp::updateScene() {
	if (!ui.isDebug()) return;
	if (!bEnable) return;
	if (!ui.bLog && !ui.bNotifier) return;

	// Animate
	float t = ofGetElapsedTimef();
	float s = ofMap(amount, amount.getMax(), amount.getMin(), 1, 10);
	t = ofWrap(t, 0, s);
	separation = ofMap(t, 0, s, separation.getMin(), separation.getMax());

	// Animate a Log

	// Make pauses
	static int t1 = 600;
	if ((ofGetFrameNum() % t1) == 0) t1 = (int)ofRandom(200, 600);
	if (ofGetFrameNum() % t1 > (t1 * 0.75f)) {
		return;
	}

	// Log 8 times per second at 60 fps
	if (ofGetFrameNum() % (60 / 8) == 0) ui.AddToLog(separation.getName() + " : " + ofToString(separation));

	// Auto populate random log messages.
	int m = ofMap(speed, 1, 0, 2, ofRandom(1) > 0.5 ? 60 : 40);
	if (ofGetFrameNum() % m == 0) {
		if (ofNoise(ofGetElapsedTimef()) < 0.4f) return; // skip one third

		std::string ss = ofToString(ofGetFrameNum());
		float _rnd = ofRandom(1);

		if (_rnd < 0.2)
			ui.AddToLogAndNotifier(ss, OF_LOG_VERBOSE);

		else if (_rnd < 0.4)
			ui.AddToLogAndNotifier(ofToString(_rnd), OF_LOG_VERBOSE);

		else if (_rnd < 0.6)
			ui.AddToLogAndNotifier(ofToString(ofToString((ofRandom(1) < 0.5 ? "..-." : "---.--..")) + "---------" + ofToString((ofRandom(1) < 0.5 ? ".--.-." : "...-.--.."))), OF_LOG_VERBOSE);

		else if (_rnd < 0.8)
			ui.AddToLogAndNotifier(ofToString((ofRandom(1) < 0.5 ? "...-." : "--.--") + ofToString("===//...--//-----..")), OF_LOG_VERBOSE);

		else
			ui.AddToLogAndNotifier(ofGetTimestampString(), OF_LOG_VERBOSE);
	}
}

//--------------------------------------------------------------
void ofApp::drawScene() {
	auto & r = ui.getRectangleCentralViewport();

	if (ui.isDebug()) {
		// viewport rect
		ofPushMatrix();
		ofPushStyle();
		ofSetRectMode(OF_RECTMODE_CENTER);
		float l = 2;
		float o = 1; //offset
		ofSetLineWidth(l);
		ofColor c = ofColor(ofColor::yellow, 255 * SurfingGui::Bounce());
		ofSetColor(c);
		ofNoFill();
		ofRectangle r_ = ofRectangle(r.getCenter().x + o, r.getCenter().y + o, r.getWidth() - 2 * o, r.getHeight() - 2 * o);
		ofDrawRectangle(r_);
		ofPopStyle();
		ofPopMatrix();
	}

	// scene camera
	{
		// cam using central docking space as viewport
		if (cam.getMouseInputEnabled()) {
			if (ui.isMouseOverGui()) cam.disableMouseInput();
		} else if (!ui.isMouseOverGui())
			cam.enableMouseInput();

		cam.begin(r);
		ofPushMatrix();
		float a = ofWrap(ofGetFrameNum(), 0, 359);
		ofRotateYDeg(a + 90);
		//ofColor c = ofColor(ofColor::white, ofMap(SurfingGui::Bounce(), 0, 1, 32, 150));
		ofColor c = ofColor(ofColor::white, 64);
		ofSetColor(c);
		ofPushStyle();
		//ofDrawGrid();
		ofDrawGridPlane();
		ofPopStyle();
		ofPopMatrix();
		cam.end();
	}
}

//----

// Custom Helpers widgets

//--------------------------------------------------------------
void ofApp::drawImGuiDockingHelp() {
	if (!bGui_DockingHelp) return;

	string s;

	//TODO: Fix sizing bug
	IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

	if (ui.BeginWindow(bGui_DockingHelp)) {
		//--

		s = "Layout";
		ui.AddLabelBig(s);

		// Reset docking layout

		if (ui.AddButton("Reset", OFX_IM_BUTTON, 2, true)) {
			bFlagDockingReset = true;
			// Flag to call on a precise draw point,
			// inside the draw begin/end context
		}
		s = "Layout Reset Docking \nto a hard-coded layout.";
		ui.AddTooltip(s);

		//--

		// Randomize docking layout

		if (ui.AddButton("Random", OFX_IM_BUTTON, 2)) {
			bFlagDockingRandom = true;
			// Flag to call on a precise draw point,
			// inside the draw begin/end context
		}
		s = "Layout Reset Docking \nto a randomized layout.";
		ui.AddTooltip(s);

		ui.AddSpacingSeparated();

		//--

		s = "Manager";
		ui.AddLabelBig(s);

		if (ui.AddButton("Load", OFX_IM_BUTTON_SMALL, 2)) {
			ui.loadLayout(path);
		}
		ui.SameLine();

		if (ui.AddButton("Save", OFX_IM_BUTTON_SMALL, 2)) {
			ui.saveLayout(path);
		}

		ui.AddSpacingSeparated();

		//--

		s = "Internal";
		ui.AddLabelBig(s);

		ui.AddMinimizerToggle();
		if (ui.isMaximized()) {
			ui.AddAutoResizeToggle();
			ui.AddKeysToggle();
			ui.AddDebugToggle();
			ui.AddExtraToggle();
			ui.AddHelpInternalToggle();
			ui.AddMenuBarToggle();
			ui.AddAdvancedToggle();

			ui.AddSpacingSeparated();

			ui.AddLogToggle();
			ui.AddNotifierToggle();
		}

		ui.EndWindow();

		// Debug
		ui.DrawWindowAdvanced();
	}
}

// Custom Helpers functions

//--------------------------------------------------------------
void ofApp::doDockingReset() {
	ofLogNotice(__FUNCTION__);

	ImGuiViewport * viewport = ImGui::GetMainViewport();
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

	// A Autogetting names
	// We can get the window names by the index to rename easy, just in one place when added on setup.
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(0).c_str(), dock_id_left);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(1).c_str(), dock_id_right);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(2).c_str(), dock_id_right);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(3).c_str(), dock_id_top);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(4).c_str(), dock_id_down);

	// B Hardcoded names
	//ImGui::DockBuilderDockWindow("Main Window", dock_id_top);
	//ImGui::DockBuilderDockWindow("Audio Window", dock_id_right);
	//ImGui::DockBuilderDockWindow("Video 2", dock_id_down);
	//ImGui::DockBuilderDockWindow("Video 3", dock_id_left);
	//ImGui::DockBuilderDockWindow("Advanced", dock_id_right);

	ImGui::DockBuilderFinish(dockspace_id);
}

//--------------------------------------------------------------
void ofApp::doDockingRandom() {
	ofLogNotice(__FUNCTION__);

	ImGuiViewport * viewport = ImGui::GetMainViewport();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
	ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	// Randomized sizes
	float min = 0.2;
	float max = 0.3;
	const float v1 = ofRandom(min, max);
	const float v2 = ofRandom(min, max);
	const float v3 = ofRandom(min, max);
	const float v4 = ofRandom(min, max);

	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, v1, nullptr, &dockspace_id);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, v2, nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, v3, nullptr, &dockspace_id);
	auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, v4, nullptr, &dockspace_id);

	int idice = (int)ofRandom(3);

	// We now dock our windows into the docking node we made above
	// We can get the window names by the index to rename easy, just in one place when added on setup.
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(0).c_str(), (idice == 0) ? dock_id_top : dock_id_down);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(1).c_str(), (idice == 1) ? dock_id_right : dock_id_left);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(2).c_str(), (idice == 2) ? dock_id_down : dock_id_top);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(3).c_str(), (idice == 0) ? dock_id_left : dock_id_right);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(4).c_str(), (idice == 1) ? dock_id_right : dock_id_left);

	ImGui::DockBuilderFinish(dockspace_id);
}
