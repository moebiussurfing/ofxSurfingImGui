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
	ui.setup(IM_GUI_MODE_INSTANTIATED_DOCKING);

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

	ui.addWindowSpecial("Main");	// index 0
	ui.addWindowSpecial("Audio");	// index 1
	ui.addWindowSpecial("Video1");	// index 2
	ui.addWindowSpecial("Video2");	// index 3
	ui.addWindowSpecial("Expert");	// index 4

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

		ui.setPresetsNames(names);
	}

	//-

	// Optional: before startup

	// We can add extra parameters to append include into the Layout Presets.
	// (Notice that this are params, not extra special windows!)
	// Set to 1 to enable an to test it
	if (1) {
		ui.addExtraParamToLayoutPresets(bGui_Docking);
		ui.addExtraParamToLayoutPresets(bEnable);
	}

	//-

	// 3. Startup:

	ui.startup();

	//-

	// Optional: after startup

	// Subscribe an optional Reset button
	// flagging a bool to true to reset. 
	// Uses the internal add-on GUI Reset button 
	// located on the Advanced section,
	// But notice that it will call a local method on this scope (ofApp).
	if (1) {
		ui.setReset(&bDockingRandom);
		//ui.setReset(&bDockingReset);
	}

	// Help info
	string s = "HELP ofApp\n\nThis is an Example to learn \nthe Docking features.\n\nEnjoy!";
	ui.setHelpAppText(s);
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

	ui.Begin();
	{
		// 1. Docking

		// Here (between beginDocking/endDocking)
		// but just after begin call, 
		// we can access all the docking space.
		// It's required to copy in our projects.

		ui.BeginDocking();
		{
			updateImGuiDockingHelper();
		}
		ui.EndDocking();

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
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawImGuiWindows()
{
	// -> These are our helpers 
	// to render windows using the power of the "Layout Presets Engine".

	int index;

	index = 0;
	{
		if (ui.BeginWindowSpecial(index))
		{
			// Some useful sizes to help layouting in some scenarios.
			// e.g. when using raw ImGui widgets without the full engine.
			float _w1 = ofxImGuiSurfing::getWidgetsWidth(1); // full width
			float _w2 = ofxImGuiSurfing::getWidgetsWidth(2); // half width
			float _h = ofxImGuiSurfing::getWidgetsHeightUnit(); // standard height
			float _h2 = 2 * _h; // double height

			// if ui.bHelp enabled, activates help tooltips on this window!

			ui.AddLabelHuge("Window 0", false);

			ui.Add(bGui_Docking, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

			ui.Add(ui.bHelp, OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG);
			ui.AddTooltip("Help enables some Tooltips \nand the Help Box on this Window!");
			ui.Add(bEnable, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);
			ui.AddTooltip("Activate sep1 animation", ui.bHelp);
			ui.AddTooltip("This is a Help Tool tip! \nIt's " + (string)(bEnable ? "TRUE" : "FALSE"), ui.bHelp);
			ui.Add(ui.bLog, OFX_IM_TOGGLE_BIG_BORDER);
			ui.AddTooltip("Show Log Window", ui.bHelp);

			ui.AddSpacingBigSeparated();

			ui.Add(speed, OFX_IM_HSLIDER_BIG);
			ui.AddTooltip("Speed controls the auto populated Log window speed", ui.bHelp);
			ui.Add(amount, OFX_IM_HSLIDER);
			ui.AddTooltip("Speed up separation animator \nwhen bEnable is TRUE", ui.bHelp);

			ui.AddSpacingBigSeparated();

			ImGui::PushButtonRepeat(true); // -> pushing for repeats trigs
			{
				ui.refreshLayout();

				if (ui.Add(bPrevious, OFX_IM_BUTTON_BIG, 2))
				{
					bPrevious = false;
					lineWidth -= 0.1f;
					lineWidth = ofClamp(lineWidth, lineWidth.getMin(), lineWidth.getMax());
				}
				ui.AddTooltip("Decrease lineWidth " + ofToString(lineWidth), ui.bHelp);

				ImGui::SameLine();

				if (ofxImGuiSurfing::AddBigButton(bNext, _w2, _h2))
				{
					bNext = false;
					lineWidth += 0.1f;
					lineWidth = ofClamp(lineWidth, lineWidth.getMin(), lineWidth.getMax());
				}
				ui.AddTooltip("Increase lineWidth " + ofToString(lineWidth), ui.bHelp);
			}
			ImGui::PopButtonRepeat();

			ui.AddSpacingBigSeparated();

			ui.Add(lineWidth, OFX_IM_HSLIDER_SMALL);
			ui.AddTooltip(ofToString(lineWidth, ui.bHelp));
			ui.Add(lineWidth); // default style
			ui.AddTooltip(ofToString(lineWidth, ui.bHelp));
			ui.Add(lineWidth, OFX_IM_STEPPER);
			ui.AddTooltip(ofToString(lineWidth, ui.bHelp));
			ui.Add(lineWidth, OFX_IM_KNOB);
			ui.AddTooltip(ofToString(lineWidth, ui.bHelp));

			ui.AddSpacingBigSeparated();

			ui.Add(separation, OFX_IM_HSLIDER_BIG); // default style
			ui.AddTooltip(ofToString(separation, ui.bHelp));

			//--

			ui.EndWindowSpecial();
		}
	}

	//----

	index = 1;
	{
		if (ui.BeginWindowSpecial(index))
		{
			ui.AddLabelHuge("Window 1", false);

			ui.Add(bGui_Docking, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

			ui.AddGroup(params1);

			//--

			ui.EndWindowSpecial();
		}
	}

	//----

	index = 2;
	{
		if (ui.BeginWindowSpecial(index))
		{
			ui.AddLabelHuge("Window 2", false);

			ui.Add(bGui_Docking, OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK);

			ui.AddGroup(params2, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_DEFAULT);

			ui.AddSpacingBigSeparated();

			// Tabs

			if (ImGui::BeginTabBar("_myTabs"))
			{
				if (ImGui::BeginTabItem("Video"))
				{
					ui.AddLabelBig("Blah Blah");
					string str = R"(
Lorem Ipsum is simply dummy text of the printing and typesetting industry.Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.
)";
					ui.AddLabel(str.c_str());
					ui.AddSpacingBigSeparated();
					ui.AddGroup(params1);

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Audio"))
				{
					ui.AddSpacingBig();
					ui.AddLabelHuge("Blah Blah");
					string str = R"(
It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.
)";
					ui.AddLabelBig(str.c_str());

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Controls"))
				{
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

			//--

			ui.EndWindowSpecial();
		}
	}

	//----

	index = 3;
	{
		if (ui.BeginWindowSpecial(index))
		{
			ui.AddLabelHuge("Window 3", false);

			ui.Add(bGui_Docking, OFX_IM_TOGGLE_ROUNDED_BIG);

			ui.AddLabelBig("Hello, down!", false, true);
			ui.AddLabelBig("Hello, down! Hello, down! Hello, down!");
			ui.AddLabelBig("Hello, down!", false, true);
			ui.AddSpacingBigSeparated();
			ui.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_HIDDEN_HEADER);
			ui.AddSpacingBigSeparated();
			ui.AddLabelBig("Hello, down!", false, true);
			ui.AddLabelHuge("Hello, down! Hello, down! Hello, down!");

			//--

			ui.EndWindowSpecial();
		}
	}

	//----

	index = 4;
	{
		if (ui.BeginWindowSpecial(index))
		{
			ui.AddLabelHuge("Window 4", false);
			
			ui.Add(bGui_Docking, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

			ui.AddLabel("Hello, left!", false, true);
			ui.AddLabelBig("Hello, left!");
			ui.AddLabelBig("Hello, left!", false);
			ui.AddLabelHuge("Hello, left!", true, true);
			ui.AddLabelHuge("Hello, left!", false, false);

			ui.EndWindowSpecial();
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

	if (ui.BeginWindow(bGui_Docking))
	{
		ui.AddLabelHuge("ofApp Docking Window", false);

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

		ui.AddSpacingSeparated();

		// Show all Panels
		if (ImGui::Button("Show All Panels", ImVec2(_w, _h / 2)))
		{
			ui.setShowAllPanels(true);
		}

		ui.EndWindow();
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
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(0).c_str(), dock_id_top);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(1).c_str(), dock_id_right);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(2).c_str(), dock_id_down);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(3).c_str(), dock_id_left);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(4).c_str(), dock_id_right);

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
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(0).c_str(), (idice == 0) ? dock_id_top : dock_id_down);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(1).c_str(), (idice == 1) ? dock_id_right : dock_id_left);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(2).c_str(), (idice == 2) ? dock_id_down : dock_id_top);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(3).c_str(), (idice == 0) ? dock_id_left : dock_id_right);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(4).c_str(), (idice == 1) ? dock_id_right : dock_id_left);

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
	if (ofGetFrameNum() % (60 / 8) == 0) ui.AddToLog(separation.getName() + " : " + ofToString(separation));

	// Auto populate random log messages.
	int m = ofMap(speed, 1, 0, 2, ofRandom(1) > 0.5 ? 60 : 40);
	if (ofGetFrameNum() % m == 0)
	{
		if (ofNoise(ofGetElapsedTimef()) < 0.4f) return; // skip one third

		std::string ss = ofToString(ofGetFrameNum());
		float _rnd = ofRandom(1);
		if (_rnd < 0.2) ui.AddToLog(ss);
		else if (_rnd < 0.4) ui.AddToLog(ofToString(_rnd));
		else if (_rnd < 0.6) ui.AddToLog(ofToString(ofToString((ofRandom(1) < 0.5 ? "..-." : "---.--..")) + "---------" + ofToString((ofRandom(1) < 0.5 ? ".--.-." : "...-.--.."))));
		else if (_rnd < 0.8) ui.AddToLog(ofToString((ofRandom(1) < 0.5 ? "...-." : "--.--") + ofToString("===//...--//-----..")));
		else ui.AddToLog(ofGetTimestampString());
	}
}