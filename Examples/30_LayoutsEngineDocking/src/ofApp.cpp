#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	// Scene Parameters
	{
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

	//--

	setupImGui();
}

//--------------------------------------------------------------
void ofApp::setupImGui()
{
	// Layout Presets Engine 
	// Setup steps

	//-

	// 1. Instantiate

	// NOTICE that
	// To enable the "Layout Presets Engine"
	// is mandatory to pass IM_GUI_MODE_INSTANTIATED_DOCKING as argument !
	guiManager.setup(IM_GUI_MODE_INSTANTIATED_DOCKING);

	//-

	// 2. Queue Windows

	// Add the "target" windows just with a name:
	// You will use these added windows easily, 
	// but you must remember his index order!
	// Each window will be added to the "Layout Presets Engine" and auto handled too.
	// The engine will auto create internal bool param toggles 
	// (like the bGui we used before)
	// to handle the show/hide window states.
	// Notice that is important to remember the index sorting when queuing!

	guiManager.addWindowSpecial("Main");	// index 0
	guiManager.addWindowSpecial("Audio");	// index 1
	guiManager.addWindowSpecial("Video1");	// index 2
	guiManager.addWindowSpecial("Video2");	// index 3
	guiManager.addWindowSpecial("Expert");	// index 4

	//-

	// Optional: before startup

	// Customize the names for the 4 default Layout Presets. 
	// Default names are P0-P1-P2-P3
	// Set to 1 to enable an to test it
	if (1) {
		vector<std::string> names;
		names.push_back("Editor");
		names.push_back("Player");
		names.push_back("Live");
		names.push_back("Mini");

		guiManager.setPresetsNames(names);
	}

	//-

	// Optional: before startup

	// We can add extra parameters to append include into the Layout Presets.
	// (Notice that this are params, not extra special windows!)
	// Set to 1 to enable an to test it
	if (1) {
		guiManager.addExtraParamToLayoutPresets(bGui_Docking);
		guiManager.addExtraParamToLayoutPresets(bEnable);
	}

	//-

	// 3. Startup:

	guiManager.startup();

	//-

	// Optional: after startup

	// Subscribe an optional Reset button
	// flagging a bool to true to reset. 
	// Uses the internal add-on GUI Reset button 
	// located on the Advanced section,
	// But notice that it will call a local method on this scope (ofApp).
	if (1) {
		guiManager.setReset(&bDockingRandom);
		//guiManager.setReset(&bDockingReset);
	}

	// Help info
	string s = "HELP ofApp\n\nThis is an Example to learn \nthe Docking features.\n\nEnjoy!";
	guiManager.setHelpInfoApp(s);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// Update Scene
	updateScene();

	//----

	drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	//----

	// Gui Manager with Docking features:
	// In between here (begin/end) 
	// we can render ImGui windows and widgets,
	// and all the docking magic.

	//--

	guiManager.begin();
	{
		// 1. Docking

		// Here (between beginDocking/endDocking)
		// but just after begin call, 
		// we can access all the docking space.
		// It's required to copy in our projects.

		guiManager.beginDocking();
		{
			updateImGuiDockingHelper();
		}
		guiManager.endDocking();

		//--

		// 2. A Window

		// An extra window with some triggers
		// for hard-coded layout modifications. 
		if (bGui_Docking) drawImGuiDockingHelper();

		//----

		// 3. The (Special Windows) 

		// The windows previously queued to the manager on setup(),
		// that are controlled by the Layout Presets Engine.
		// Render ImGui Windows and Widgets now!
		{
			drawImGuiWindows();
		}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawImGuiWindows()
{
	// -> These are our helpers 
	// to render windows using the power of the "Layout Presets Engine".

	int index;

	index = 0;
	{
		if (guiManager.beginWindowSpecial(index))
		{
			// Some useful sizes to help layouting in some scenarios.
			// e.g. when using raw ImGui widgets without the full engine.
			float _w1 = ofxImGuiSurfing::getWidgetsWidth(1); // full width
			float _w2 = ofxImGuiSurfing::getWidgetsWidth(2); // half width
			float _h = ofxImGuiSurfing::getWidgetsHeightUnit(); // standard height
			float _h2 = 2 * _h; // double height

			// if guiManager.bHelp enabled, activates help tooltips on this window!

			guiManager.AddLabelHuge("Window 0", false);

			guiManager.Add(bGui_Docking, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

			guiManager.Add(guiManager.bHelp, OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG);
			guiManager.AddTooltip("Help enables some Tooltips \nand the Help Box on this Window!");
			guiManager.Add(bEnable, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);
			guiManager.AddTooltip("Activate sep1 animation", guiManager.bHelp);
			guiManager.AddTooltip("This is a Help Tool tip! \nIt's " + (string)(bEnable ? "TRUE" : "FALSE"), guiManager.bHelp);
			guiManager.Add(guiManager.bLog, OFX_IM_TOGGLE_BIG_BORDER);
			guiManager.AddTooltip("Show Log Window", guiManager.bHelp);

			guiManager.AddSpacingBigSeparated();

			guiManager.Add(speed, OFX_IM_HSLIDER_BIG);
			guiManager.AddTooltip("Speed controls the auto populated Log window speed", guiManager.bHelp);
			guiManager.Add(amount, OFX_IM_HSLIDER);
			guiManager.AddTooltip("Speed up separation animator \nwhen bEnable is TRUE", guiManager.bHelp);

			guiManager.AddSpacingBigSeparated();

			ImGui::PushButtonRepeat(true); // -> pushing for repeats trigs
			{
				guiManager.refreshLayout();

				if (guiManager.Add(bPrevious, OFX_IM_BUTTON_BIG, 2))
				{
					bPrevious = false;
					lineWidth -= 0.1f;
					lineWidth = ofClamp(lineWidth, lineWidth.getMin(), lineWidth.getMax());
				}
				guiManager.AddTooltip("Decrease lineWidth " + ofToString(lineWidth), guiManager.bHelp);

				ImGui::SameLine();

				if (ofxImGuiSurfing::AddBigButton(bNext, _w2, _h2))
				{
					bNext = false;
					lineWidth += 0.1f;
					lineWidth = ofClamp(lineWidth, lineWidth.getMin(), lineWidth.getMax());
				}
				guiManager.AddTooltip("Increase lineWidth " + ofToString(lineWidth), guiManager.bHelp);
			}
			ImGui::PopButtonRepeat();

			guiManager.AddSpacingBigSeparated();

			guiManager.Add(lineWidth, OFX_IM_HSLIDER_SMALL);
			guiManager.AddTooltip(ofToString(lineWidth, guiManager.bHelp));
			guiManager.Add(lineWidth); // default style
			guiManager.AddTooltip(ofToString(lineWidth, guiManager.bHelp));
			guiManager.Add(lineWidth, OFX_IM_STEPPER);
			guiManager.AddTooltip(ofToString(lineWidth, guiManager.bHelp));
			guiManager.Add(lineWidth, OFX_IM_KNOB);
			guiManager.AddTooltip(ofToString(lineWidth, guiManager.bHelp));

			guiManager.AddSpacingBigSeparated();

			guiManager.Add(separation, OFX_IM_HSLIDER_BIG); // default style
			guiManager.AddTooltip(ofToString(separation, guiManager.bHelp));

			//--

			guiManager.endWindowSpecial();
		}
	}

	//----

	index = 1;
	{
		if (guiManager.beginWindowSpecial(index))
		{
			guiManager.AddLabelHuge("Window 1", false);

			guiManager.Add(bGui_Docking, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

			guiManager.AddGroup(params1);

			//--

			guiManager.endWindowSpecial();
		}
	}

	//----

	index = 2;
	{
		if (guiManager.beginWindowSpecial(index))
		{
			guiManager.AddLabelHuge("Window 2", false);

			guiManager.Add(bGui_Docking, OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK);

			guiManager.AddGroup(params2, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_DEFAULT);

			guiManager.AddSpacingBigSeparated();

			// Tabs

			if (ImGui::BeginTabBar("_myTabs"))
			{
				if (ImGui::BeginTabItem("Video"))
				{
					guiManager.AddLabelBig("Blah Blah");
					string str = R"(
Lorem Ipsum is simply dummy text of the printing and typesetting industry.Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.
)";
					guiManager.AddText(str.c_str());
					guiManager.AddSpacingBigSeparated();
					guiManager.AddGroup(params1);

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Audio"))
				{
					guiManager.AddSpacingBig();
					guiManager.AddTextHuge("Blah Blah");
					string str = R"(
It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
)";
					guiManager.AddTextBig(str.c_str());

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Controls"))
				{
					guiManager.AddSpacingBig();
					guiManager.AddTextHuge("Pump Up");
					guiManager.AddTextBig("the Volume!");
					guiManager.AddSpacingBig();

					guiManager.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_HIDDEN_HEADER);

					guiManager.drawAdvancedBundle();

					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}

			//--

			guiManager.endWindowSpecial();
		}
	}

	//----

	index = 3;
	{
		if (guiManager.beginWindowSpecial(index))
		{
			guiManager.AddLabelHuge("Window 3", false);

			guiManager.Add(bGui_Docking, OFX_IM_TOGGLE_ROUNDED_BIG);

			guiManager.AddLabelBig("Hello, down!", false, true);
			guiManager.AddTextBig("Hello, down! Hello, down! Hello, down!");
			guiManager.AddLabelBig("Hello, down!", false, true);
			guiManager.AddSpacingBigSeparated();
			guiManager.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_HIDDEN_HEADER);
			guiManager.AddSpacingBigSeparated();
			guiManager.AddLabelBig("Hello, down!", false, true);
			guiManager.AddTextHuge("Hello, down! Hello, down! Hello, down!");

			//--

			guiManager.endWindowSpecial();
		}
	}

	//----

	index = 4;
	{
		if (guiManager.beginWindowSpecial(index))
		{
			guiManager.AddLabelHuge("Window 4", false);
			
			guiManager.Add(bGui_Docking, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

			guiManager.AddLabel("Hello, left!", false, true);
			guiManager.AddLabelBig("Hello, left!");
			guiManager.AddLabelBig("Hello, left!", false);
			guiManager.AddLabelHuge("Hello, left!", true, true);
			guiManager.AddLabelHuge("Hello, left!", false, false);

			guiManager.endWindowSpecial();
		}
	}
}

//----

// We can setup the docking layout using hard-coded methods too,
// added to the user session mouse-layouting work.

//--------------------------------------------------------------
void ofApp::updateImGuiDockingHelper()
{
	// Reset layout once o startup/first frame call
	{
		static bool binitiated = false;
		if (!binitiated) {
			binitiated = true; // Called only once!

			doDockingReset();
		}
	}

	// Reset layout by button GUI
	if (bDockingReset) {
		bDockingReset = false;

		doDockingReset();
	}

	// Random layout by button GUI
	if (bDockingRandom) {
		bDockingRandom = false;

		doDockingRandom();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiDockingHelper()
{
	if (!bGui_Docking) return;

	if (guiManager.beginWindow(bGui_Docking))
	{
		guiManager.AddLabelHuge("ofApp Docking Window", false);

		ImGui::TextWrapped("Reset Docking hard-coded Layouts");
		float _w = ofxImGuiSurfing::getWidgetsWidth();
		float _h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();

		// Reset docking layout
		if (ImGui::Button("Reset Layout", ImVec2(_w, _h)))
		{
			bDockingReset = true; 
			// flag to call on a precise draw point, inside the draw begin/end context
		}

		// Randomize docking layout
		if (ImGui::Button("Randomize Layout", ImVec2(_w, _h)))
		{
			bDockingRandom = true; 
			// flag to call on a precise draw point, inside the draw begin/end context
		}

		// Show all Panels
		if (ImGui::Button("Show All Panels", ImVec2(_w, _h / 2)))
		{
			guiManager.setShowAllPanels(true);
		}

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::doDockingReset()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
	ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	// Split the dockspace into 2 nodes --
	// DockBuilderSplitNode takes in the following args in the following order
	//   window ID to split, direction, fraction (between 0 and 1),
	// the final two setting let's us choose which id we want (which ever one we DON'T set as NULL,
	// will be returned by the function)
	// out_id_at_dir is the id of the node in the direction we specified earlier,
	// out_id_at_opposite_dir is in the opposite direction

	// Fixed sizes
	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.2f, nullptr, &dockspace_id);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
	auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.15f, nullptr, &dockspace_id);

	// We now dock our windows into the docking node we made above

	//ImGui::DockBuilderDockWindow("Main Window", dock_id_top);
	//ImGui::DockBuilderDockWindow("Audio Window", dock_id_right);
	//ImGui::DockBuilderDockWindow("Video 2", dock_id_down);
	//ImGui::DockBuilderDockWindow("Video 3", dock_id_left);
	//ImGui::DockBuilderDockWindow("Advanced", dock_id_right);

	// We can get the window names by the index to rename easy, just in one place when added on setup.
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(0).c_str(), dock_id_top);
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(1).c_str(), dock_id_right);
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(2).c_str(), dock_id_down);
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(3).c_str(), dock_id_left);
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(4).c_str(), dock_id_right);

	ImGui::DockBuilderFinish(dockspace_id);
}

//--------------------------------------------------------------
void ofApp::doDockingRandom()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
	ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	// randomized sizes
	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, ofRandom(0.2, 0.35), nullptr, &dockspace_id);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, ofRandom(0.2, 0.35), nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, ofRandom(0.2, 0.35), nullptr, &dockspace_id);
	auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, ofRandom(0.2, 0.35), nullptr, &dockspace_id);

	int idice = (int)ofRandom(3);

	// we now dock our windows into the docking node we made above
	// We can get the window names by the index to rename easy, just in one place when added on setup.
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(0).c_str(), (idice == 0) ? dock_id_top : dock_id_down);
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(1).c_str(), (idice == 1) ? dock_id_right : dock_id_left);
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(2).c_str(), (idice == 2) ? dock_id_down : dock_id_top);
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(3).c_str(), (idice == 0) ? dock_id_left : dock_id_right);
	ImGui::DockBuilderDockWindow(guiManager.getWindowSpecialName(4).c_str(), (idice == 1) ? dock_id_right : dock_id_left);

	ImGui::DockBuilderFinish(dockspace_id);
}

//----

// Scene

//--------------------------------------------------------------
void ofApp::updateScene()
{
	if (!bEnable) return;

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
	if (ofGetFrameNum() % (60 / 8) == 0) guiManager.addLog(separation.getName() + " : " + ofToString(separation));

	// Auto populate random log messages.
	int m = ofMap(speed, 1, 0, 2, ofRandom(1) > 0.5 ? 60 : 40);
	if (ofGetFrameNum() % m == 0)
	{
		if (ofNoise(ofGetElapsedTimef()) < 0.4f) return; // skip one third

		std::string ss = ofToString(ofGetFrameNum());
		float _rnd = ofRandom(1);
		if (_rnd < 0.2) guiManager.addLog(ss);
		else if (_rnd < 0.4) guiManager.addLog(ofToString(_rnd));
		else if (_rnd < 0.6) guiManager.addLog(ofToString(ofToString((ofRandom(1) < 0.5 ? "..-." : "---.--..")) + "---------" + ofToString((ofRandom(1) < 0.5 ? ".--.-." : "...-.--.."))));
		else if (_rnd < 0.8) guiManager.addLog(ofToString((ofRandom(1) < 0.5 ? "...-." : "--.--") + ofToString("===//...--//-----..")));
		else guiManager.addLog(ofGetTimestampString());
	}
}