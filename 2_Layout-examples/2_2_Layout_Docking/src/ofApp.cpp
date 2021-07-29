#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	// parameters
	params1.setName("paramsGroup1"); // main container
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
	guiManager.setImGuiDocking(true);
	guiManager.setImGuiDockingModeCentered(false);
	guiManager.setImGuiAutodraw(true);
	guiManager.setup();
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
void ofApp::drawLayout()
{
	if (!binitiated)
	{
		binitiated = true;

		ImGui::GetIO().ConfigDockingWithShift = true;
	}

	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", nullptr, window_flags);
		{
			ImGui::PopStyleVar();
			ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				//dockspace_flags |= ImGuiConfigFlags_DockingEnable

				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

				if (bResetLayout)
				{
					bResetLayout = false;
					reset();
				}

				static auto first_time = true;
				if (first_time)
				{
					first_time = false;

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
					auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.1f, nullptr, &dockspace_id);
					auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
					auto dock_id_left2 = ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.2f, nullptr, &dock_id_left);
					auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);
					auto dock_id_down2 = ImGui::DockBuilderSplitNode(dock_id_down, ImGuiDir_Right, 0.15f, nullptr, &dock_id_down);

					// we now dock our windows into the docking node we made above
					ImGui::DockBuilderDockWindow("Window1", dock_id_top);
					ImGui::DockBuilderDockWindow("Down", dock_id_down);
					ImGui::DockBuilderDockWindow("Left", dock_id_left);
					ImGui::DockBuilderDockWindow("Window1", dock_id_left2);
					ImGui::DockBuilderDockWindow("Window2", dock_id_down2);
					ImGui::DockBuilderFinish(dockspace_id);
				}
			}
			drawMenu();
		}
		ImGui::End();
	}

	//--

	// populate

	if (bOpen3) {
		ImGui::Begin("Left");
		ImGui::Text("Hello, left!");
		ImGui::End();
	}

	if (bOpen4) {
		ImGui::Begin("Down");
		ImGui::Text("Hello, down!");
		ImGui::End();
	}

	//---------

	// Main Window

	// A raw standard raw ImGui window
	{
		//if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		//ImGui::Begin("Show Windows", &bOpen0, window_flags);
		ImGui::Begin("Show Windows", &bOpen0);
		{
			// round toggles widgets
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 2", &bOpen2);
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 3", &bOpen3);
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 4", &bOpen4);

			// reset layout to hardcoded distribution
			if (ofxImGuiSurfing::ToggleRoundedButton("Reset", &bResetLayout)) {
				bResetLayout = false;
			}

			if (ImGui::BeginTabBar("blah"))
			{
				if (ImGui::BeginTabItem("Video"))
				{
					string str = "weqweqrqcwcrqwcrqwecrqwecrqwecrqwecrqwecrqwecr qervev qervewecrqwecrqwecrqwecr qervev qerve";
					ImGui::Text("Blah blah");
					ImGui::TextWrapped(str.c_str());
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Audio"))
				{
					string str = "weq12341234weqrqcwcrqwcr1121233adqervewecrqwecrqwecrqwecr qervev qerve";
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

			//ImGui::Dummy(ImVec2(0, 5)); // spacing

		}
		ImGui::End();
	}

	//--------

	if (bOpen1)
	{
		//guiManager.beginWindow("Window1", &bOpen1, ImGuiWindowFlags_None);
		guiManager.beginWindow("Window1", &bOpen1);
		{
			ImGui::Text("Window1Window1Window1");

			//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
			////flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
			//flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed
			//ofxImGuiSurfing::AddGroup(params3, flags);

			//BUG: CRASHES
			//guiManager.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_DEFAULT);
			//guiManager.AddGroup(params3);

		}
		guiManager.endWindow();
	}

	//---------

	if (bOpen2)
	{
		//guiManager.beginWindow("Window2", &bOpen2, ImGuiWindowFlags_None);
		guiManager.beginWindow("Window2", &bOpen2);
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
}

//--------------------------------------------------------------
void ofApp::reset() // not works
{
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiViewport* viewport = ImGui::GetMainViewport();

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
	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.5f, nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.4f, nullptr, &dockspace_id);
	auto dock_id_left2 = ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.2f, nullptr, &dock_id_left);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.5f, nullptr, &dockspace_id);
	auto dock_id_down2 = ImGui::DockBuilderSplitNode(dock_id_down, ImGuiDir_Right, 0.25f, nullptr, &dock_id_down);

	// we now dock our windows into the docking node we made above
	ImGui::DockBuilderDockWindow("Window1", dock_id_top);
	ImGui::DockBuilderDockWindow("Left", dock_id_down);
	ImGui::DockBuilderDockWindow("Down", dock_id_left);
	ImGui::DockBuilderDockWindow("Window2", dock_id_left2);
	ImGui::DockBuilderDockWindow("Window1", dock_id_down2);
	ImGui::DockBuilderFinish(dockspace_id);
}

//--------------------------------------------------------------
void ofApp::drawMenu()
{
	//-

	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	//static bool p_open = TRUE;
	static bool* p_open;

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