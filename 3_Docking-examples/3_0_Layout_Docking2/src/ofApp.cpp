#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	// Parameters
	params1.setName("paramsGroup1"); 
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));
	params2.setName("paramsGroup2"); 
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.setName("paramsGroup3"); 
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));

	// a rectangle parameter with callback
	rectParam.addListener(this, &ofApp::Changed_Rect);

	//-

	// -> To allow the full engine:
	// Custom docking layout with presets. 
	guiManager.setupDocking();

	//-

	// -> layouts presets

	// 1. Add the windows:
	// Pre add the window names that you will use and rememeber his index!
	// Each added window will be added too to the layout presets engine
	guiManager.addWindow("Window 0");
	guiManager.addWindow("Window 1");
	guiManager.addWindow("Window 2");
	guiManager.addWindow("Window 3");
	guiManager.addWindow("Window 4");

	//-

	// 2. Add parameters:
	// -> Extra params to include into layout presets
	guiManager.addParameterToLayoutPresets(params1);
	guiManager.addParameterToLayoutPresets(rectParam);

	//-

	// -> Initiates after adding windows and parameters.
	guiManager.startup();

	// This will create 4 layout presets as default. 
	// But you can customize the amount presets using other API methods like instead of startup.
	// guiManager.setupLayout(6);

	//-

	//TODO:
	// -> subscribe external button
	//guiManager.setReset((bool*)bDockingReset);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		drawImGui(); // populate all the widgets and panels
	}
	guiManager.end(); // global end

	//--

	// -> OF scene
	ofPushMatrix();
	ofPushStyle();
	const int a = ofMap(ofxSurfingHelpers::getFadeBlink(), 0, 1, 64, 96);
	ofSetColor(ofColor(ofColor::orange, a));
	ofFill();
	ofDrawRectRounded(rectParam, 5);
	ofPopStyle();
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	if (!binitiated)
	{
		binitiated = true;
		/* ... some ImGui add-ons may require to perform something once ... */
	}

	//--

	guiManager.beginDocking();
	{
		// Reset layout
		// We can setup the docking layout using hardcoded methods

		// Layout 1
		if (bDockingReset1)
		{
			bDockingReset1 = false;
			dockingReset1();
		}

		// Layout 2
		if (bDockingReset2)
		{
			bDockingReset2 = false;
			dockingReset2();
		}

		//--

		if (guiManager.bGui_Menu) drawMenu();
	}
	guiManager.endDocking();

	//---------

	// -> Render our windows now

	if (guiManager.beginWindow(0))
	{
		// Calculate layout sizes
		float _w100 = ofxImGuiSurfing::getWidgetsWidth();
		float _w50 = ofxImGuiSurfing::getWidgetsWidth(2);
		float _h = 2 * ofxImGuiSurfing::getWidgetsHeightRelative();

		//-

		// We have access to the gui show toggles for the added windows
		if (ImGui::CollapsingHeader("Added windows"))
		{
			ImGui::TextWrapped("Auto created toggles to set each added window visible");
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.getVisible(0));
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.getVisible(1));
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.getVisible(2));
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.getVisible(3));
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.getVisible(4));
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		//-

		// We expose the paremeters we added to the layout manager on setup
		ImGui::TextWrapped("The added parameters");
		ofxImGuiSurfing::AddParameter(rectParam);
		ofxImGuiSurfing::AddGroup(params1);

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		//-

		// Reset docking layout
		ImGui::TextWrapped("Reset Docking hardcoded layouts");
		if (ImGui::Button("Reset1", ImVec2(_w50, _h)))
		{
			bDockingReset1 = true; // flag to call on a preciste draw point
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset2", ImVec2(_w50, _h)))
		{
			bDockingReset2 = true; // flag to call on a preciste draw point
		}

		//-

		guiManager.endWindow(); // -> Notice that endWindow goes inside the beginWindow bracket!
	}

	//--------

	if (guiManager.beginWindow(1))
	{
		ImGui::Text("Window1 Window1 Window1");

		guiManager.AddGroup(params2, ImGuiTreeNodeFlags_None, OFX_IM_GROUP_COLLAPSED);
		guiManager.AddGroup(params3);

		guiManager.endWindow();
	}

	//---------

	if (guiManager.beginWindow(2))
	{
		float _w100 = ofxImGuiSurfing::getWidgetsWidth(1); // full width
		float _w50 = ofxImGuiSurfing::getWidgetsWidth(2); // half width
		float _h = ofxImGuiSurfing::getWidgetsHeightRelative(); // standard height

		//-

		ImGui::Text("Window2 Window2 Window2 Window2");

		if (ofxImGuiSurfing::AddBigToggle(bEnable)) {}
		if (ofxImGuiSurfing::AddBigButton(bPrevious, _w50, _h * 2)) {
			lineWidth -= 0.1;
			bPrevious = false;
		}
		ImGui::SameLine();
		if (ofxImGuiSurfing::AddBigButton(bNext, _w50, _h * 2)) {
			lineWidth += 0.1;
			bNext = false;
		}

		ofxImGuiSurfing::AddParameter(bEnable);
		ofxImGuiSurfing::AddParameter(separation);
		ofxImGuiSurfing::AddParameter(shapeType);

		guiManager.endWindow();
	}

	//--

	// more windows
	// out of the docking space. cant be docked! ?

	if (guiManager.beginWindow(3))
	{
		ImGui::Text("Hello, left!");
		ImGui::Text("Hello, left!");
		ImGui::Text("Hello, left!");

		guiManager.endWindow();
	}

	//--

	if (guiManager.beginWindow(4))
	{
		ImGui::Text("Hello, down!");
		ImGui::Text("Hello, down!");
		ImGui::Text("Hello, down!");
		ImGui::Text("Hello, down!");
		ImGui::Text("Hello, down!");

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawMenu()
{
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	static bool* p_open = NULL;

	//-

	// Menu bar

	// This is not operative. just for testing menus!

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
			ImGui::MenuItem("Padding", NULL, &opt_padding);
			ImGui::Separator();

			if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
			if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			ImGui::Separator();

			if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
				*p_open = false;
			ImGui::EndMenu();
		}
		ofxImGuiSurfing::HelpMarker(
			"This is not operative here. Just for testing menus!" "\n\n"
			"When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
			"- Drag from window title bar or their tab to dock/undock." "\n"
			"- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
			"- Hold SHIFT to disable docking." "\n"
			"This demo app has nothing to do with it!" "\n\n"
			"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)." "\n\n"
			"ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame." "\n\n"
			"(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)"
		);

		ImGui::EndMenuBar();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	guiManager.keyPressed(key); // -> we have some layout presets that we can load using keys
}

//--------------------------------------------------------------
void ofApp::exit()
{
	rectParam.removeListener(this, &ofApp::Changed_Rect);
}

//--------------------------------------------------------------
void ofApp::dockingReset1()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	//ImGuiID dockspace_id = ImGui::GetID("DockSpace");

	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
	ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	// split the dockspace into 2 nodes --
	// DockBuilderSplitNode takes in the following args in the following order
	//   window ID to split, direction, fraction (between 0 and 1),
	// the final two setting let's us choose which id we want (which ever one we DON'T set as NULL,
	// will be returned by the function)
	// out_id_at_dir is the id of the node in the direction we specified earlier,
	// out_id_at_opposite_dir is in the opposite direction
	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.2f, nullptr, &dockspace_id);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
	auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.15f, nullptr, &dockspace_id);
	//auto dock_id_left2 = ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.2f, nullptr, &dock_id_left);
	//auto dock_id_down2 = ImGui::DockBuilderSplitNode(dock_id_down, ImGuiDir_Right, 0.15f, nullptr, &dock_id_down);

	// we now dock our windows into the docking node we made above

	ImGui::DockBuilderDockWindow("Window 1", dock_id_top);
	ImGui::DockBuilderDockWindow("Window 2", dock_id_right);
	ImGui::DockBuilderDockWindow("Window 3", dock_id_left);
	ImGui::DockBuilderDockWindow("Window 4", dock_id_down);

	ImGui::DockBuilderFinish(dockspace_id);
}

//--------------------------------------------------------------
void ofApp::dockingReset2()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
	ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.1f, nullptr, &dockspace_id);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.1f, nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.1f, nullptr, &dockspace_id);
	auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.1f, nullptr, &dockspace_id);
	//auto dock_id_left2 = ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.1f, nullptr, &dock_id_left);
	//auto dock_id_down2 = ImGui::DockBuilderSplitNode(dock_id_down, ImGuiDir_Right, 0.1f, nullptr, &dock_id_down);

	// we now dock our windows into the docking node we made above
	ImGui::DockBuilderDockWindow("Window 4", dock_id_top);
	ImGui::DockBuilderDockWindow("Window 3", dock_id_right);
	ImGui::DockBuilderDockWindow("Window 2", dock_id_left);
	ImGui::DockBuilderDockWindow("Window 1", dock_id_down);

	ImGui::DockBuilderFinish(dockspace_id);
}

//--------------------------------------------------------------
void ofApp::Changed_Rect(ofRectangle & r)
{
}
