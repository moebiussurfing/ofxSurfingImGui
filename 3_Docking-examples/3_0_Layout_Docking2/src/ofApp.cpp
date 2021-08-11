#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	// parameters
	params1.setName("paramsGroup1"); // container
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));

	params2.setName("paramsGroup2"); // nested
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));

	params3.setName("paramsGroup3"); // nested
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));

	// -> required to allow custom docking layout. 
	// instead of the default centralized.
	guiManager.setAutoSaveSettings(true);
	guiManager.setImGuiDocking(true);
	guiManager.setImGuiDockingModeCentered(true);
	guiManager.setImGuiAutodraw(true);
	guiManager.setup();

	// -> layouts presets
	// this bool toggles will control the show of the added window
	// and will be added too to layout presets engine
	guiManager.addWindow(bOpen0);
	guiManager.addWindow(bOpen1);
	guiManager.addWindow(bOpen2);
	guiManager.addWindow(bOpen3);
	guiManager.addWindow(bOpen4);

	// -> initiates when adding finished
	guiManager.setupLayout();

	//guiManager.setReset((bool*)bDockingReset);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		drawLayout();
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::dockingPopulate()
{
	static auto bDockingFirstTime = true;
	if (bDockingFirstTime)
	{
		bDockingFirstTime = false;
		dockingReset();
	}
}

//--------------------------------------------------------------
void ofApp::dockingReset() // not works on runtime..?
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

	//ImGui::DockBuilderDockWindow("Window 0", dock_id_right);
	//ImGui::DockBuilderDockWindow("Main Window", dock_id_left);
	//ImGui::DockBuilderDockWindow("Layouts", dock_id_left);
	//ImGui::DockBuilderDockWindow("Panels", dock_id_top);

	ImGui::DockBuilderFinish(dockspace_id);
}

//--------------------------------------------------------------
void ofApp::drawLayout()
{
	if (!binitiated)
	{
		binitiated = true;
		//.. some ImGui addons may require
	}

	//--

	guiManager.beginDocking();
	{
		dockingPopulate(); // -> initialize and "bypass" layout presets system if required

		//--

		if (bDockingReset)
		{
			bDockingReset = false;

			dockingReset();
		}

		//--

		if (guiManager.bGui_Menu) drawMenu();
	}
	guiManager.endDocking();

	//---------

	// -> render our windows now

	// main Window

	// a raw standard raw ImGui window
	if (bOpen0) {
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Window 0", (bool*)&bOpen0.get(), window_flags);
		{
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bGui_MainWindow);

			ofxImGuiSurfing::AddToggleRoundedButton(bOpen1);
			ofxImGuiSurfing::AddToggleRoundedButton(bOpen2);
			ofxImGuiSurfing::AddToggleRoundedButton(bOpen3);
			ofxImGuiSurfing::AddToggleRoundedButton(bOpen4);

			ImGui::Separator();

			// reset docking layout
			float _w = ofxImGuiSurfing::getWidgetsWidth();
			float _h = 2 * ofxImGuiSurfing::getWidgetsHeightRelative();
			if (ImGui::Button("Reset", ImVec2(_w, _h)))
			{
				bDockingReset = true; // flag to call on a preciste draw point
			}

			ImGui::Separator();
			ImGui::Spacing();

			// tabs
			if (ImGui::BeginTabBar("Blah"))
			{
				if (ImGui::BeginTabItem("Video"))
				{
					std::string str = "Erqwcrqwecrqwecrqwecrqwecrqwecrqwecr qervev qervewecrqwecrqwecrqwecr qervev qerve";
					ImGui::Text("Blah blah");
					ImGui::TextWrapped(str.c_str());
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Audio"))
				{
					std::string str = "Wcwcrqwcr1121233adqervewecrqwecrqwecrqwecr qervev qerve";
					ImGui::Text("Blah blah");
					ImGui::TextWrapped(str.c_str());
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Controls"))
				{
					guiManager.drawAdvanced();
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}

	//--------

	if (bOpen1)
	{
		guiManager.beginWindow("Window 1", (bool*)&bOpen1.get());
		{
			ImGui::Text("Window1Window1Window1");

			//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
			////flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
			//flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed
			//ofxImGuiSurfing::AddGroup(params3, flags);

			//BUG: CRASHES
			guiManager.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_DEFAULT);
			//guiManager.AddGroup(params3);
		}
		guiManager.endWindow();
	}

	//---------

	if (bOpen2)
	{
		guiManager.beginWindow("Window 2", (bool*)&bOpen2.get());
		{
			ImGui::Text("Window2Window2Window2Window2");

			float _w100 = ofxImGuiSurfing::getWidgetsWidth(1); // full width
			float _w50 = ofxImGuiSurfing::getWidgetsWidth(2); // half width
			float _h = ofxImGuiSurfing::getWidgetsHeightRelative(); // standard height

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
		}
		guiManager.endWindow();
	}

	//--

	// more windows
	// out of the docking space. cant be docked! ?

	if (bOpen3) {
		guiManager.beginWindow("Window 3", (bool*)&bOpen3.get());
		{
			//ImGui::Begin("Window 3");
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
			//ImGui::End();
		}	
		guiManager.endWindow();
	}

	//--

	if (bOpen4) {
		guiManager.beginWindow("Window 4", (bool*)&bOpen4.get());
		//ImGui::Begin("Window 4");
		{
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
		}
		//ImGui::End();
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

	// menu bar

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
void ofApp::exit()
{
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	guiManager.keyPressed(key);
}
