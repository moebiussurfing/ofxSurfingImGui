#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	// Parameters
	params1.setName("paramsGroup1");
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", false));
	params1.add(bMode1.set("bMode1", false));
	params1.add(bMode2.set("bMode2", true));
	params1.add(bMode3.set("bMode3", false));
	params1.add(bMode4.set("bMode4", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
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

	//-

	// Instantiate

	// -> Optional to customize filename for the settings file for multiple instances on the same ofApp.
	//guiManager.setSettingsFilename("3_DockingLayoutPresetsEngine"); 
	guiManager.setup(IM_GUI_MODE_INSTANTIATED_DOCKING);

	//// Original legacy api
	//guiManager.setImGuiViewPort(true);
	//// -> To allow the full engine:
	//// Custom docking layout with presets. 
	//guiManager.setupDocking();

	//-

	// -> layouts presets:
	// Add the windows just with a name:
	// Pre add the window names that you will use and rememeber his index!
	// Each added window will be added too to the layout presets engine
	guiManager.addWindowSpecial("Main");
	guiManager.addWindowSpecial("Audio");
	guiManager.addWindowSpecial("Video1");
	guiManager.addWindowSpecial("Video2");
	guiManager.addWindowSpecial("Expert");

	//-

	/*

	NOTE:
	Then we can render the windows:
	if (guiManager.beginWindow(index)) // -> This is our helpers to render each window passing the index
	{
		// widgets goes here!
		guiManager.endWindow();
	}

	NOTE:
	Of course, we can use also raw ImGui methods to create windows and widgets too!

	*/

	//-

	// Optional: 
	// Customize the name for the 4 default presets
	vector<std::string> names;
	names.push_back("Editor");
	names.push_back("Player");
	names.push_back("Live");
	names.push_back("Mini");
	guiManager.setPresetsNames(names);

	// -> Initiates after adding windows and parameters.
	guiManager.startup();

	//-

	// Optional:
	// We can add extra parameters to include into the layout presets
	guiManager.addParameterToLayoutPresets(bEnable);
	guiManager.addParameterToLayoutPresets(bMode1);
	guiManager.addParameterToLayoutPresets(bMode2);

	//-

	// Optional: 
	// -> Subscribe an optional reset flagging a bool to true to reset. 
	// Uses the internal addon gui Reset button on the Presets Extra panel,
	// but to call a local method on this scope (ofApp).
	guiManager.setReset(&bDockingReset);
}

//--------------------------------------------------------------
void ofApp::draw()
{

	guiManager.begin(); // Global begin
	{
		/* Here (between begin/end) we can render ImGui windows and widgets. */

		//if (0)//bypass
		{
			guiManager.beginDocking();
			//if(0)
			{
				/* Here (between beginDocking/endDocking) we can access all the docking space. */

				// Reset layout once.
				if (0)//bypass
				{
					static bool binitiated = false;
					if (!binitiated) {
						binitiated = true;
						dockingReset();
					}
				}

				// Reset layout by button gui
				if (bDockingReset) {
					bDockingReset = false;
					dockingReset();
				}

				// Random layout by button gui
				if (bDockingRandom) {
					bDockingRandom = false;
					dockingRandom();
				}
			}
			guiManager.endDocking();
		}

		//--

		// Render windows and widgets now!
		drawImGui();

		//--

		//guiManager.endDocking();
	}
	guiManager.end(); // Global end

	//----

	// Log
	const int m = ofMap(speed, 1, 0, 2, 60);
	if (ofGetFrameNum() % m == 0)
	{
		std::string ss = ofToString(ofGetFrameNum());
		float _rnd = ofRandom(1);
		if (_rnd < 0.2) guiManager.addLog(ss);
		else if (_rnd < 0.4) guiManager.addLog(ofToString(_rnd));
		else if (_rnd < 0.6) guiManager.addLog(ofToString("---------------"));
		else if (_rnd < 0.8) guiManager.addLog(ofToString("===//=====//==="));
		else guiManager.addLog(ofGetTimestampString());
	}

	//-
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	// Hardcoded Layout
	if (bEnable)
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
		flags |= ImGuiWindowFlags_NoSavedSettings; // -> exclude from layout presets

		ImGuiCond cond = ImGuiCond_None;
		cond |= ImGuiCond_Appearing;
		ImGui::SetNextWindowPos(ImVec2(400, 400), cond);
		ImGui::SetNextWindowSize(ImVec2(100, 200), cond);

		//ImGui:Begin("Debug-ofApp", NULL, flags);
		ImGui:Begin("Debug-ofApp", (bool*)bEnable.get(), flags);
		{
			ImGui::TextWrapped("Reset Docking hardcoded layouts");
			float _w = ofxImGuiSurfing::getWidgetsWidth();
			float _h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();

			// Reset docking layout
			if (ImGui::Button("Reset Layout", ImVec2(_w, _h)))
			{
				bDockingReset = true; // flag to call on a preciste draw point
			}
			// Randomize docking layout
			if (ImGui::Button("Randomize Layout", ImVec2(_w, _h)))
			{
				bDockingRandom = true; // flag to call on a preciste draw point
			}
			// Show all Panels
			if (ImGui::Button("Show All Panels", ImVec2(_w, _h / 2)))
			{
				guiManager.setShowAllPanels(true);
			}
		}
		ImGui::End();
	}

	//---------

	if (guiManager.beginWindow(0)) // -> This is our helpers to render windows
	{
		ImGui::Text("Hello, left!");
		ImGui::Text("Hello, left!");
		ImGui::Text("Hello, left!");
		ImGui::Text("Hello, left!");
		ImGui::Text("Hello, left!");

		guiManager.endWindow(); // -> Must be called inside the if / beginWindow brackets!
	}

	//---------

	if (guiManager.beginWindow(1))
	{
		ImGui::Text("Hello, down!");
		ImGui::Text("Hello, down!");
		ImGui::Text("Hello, down!");
		ImGui::Text("Hello, down!");
		ImGui::Text("Hello, down!");

		guiManager.endWindow();
	}

	//---------

	if (guiManager.beginWindow(2))
	{
		if (ImGui::BeginTabBar("myTabs"))
		{
			if (ImGui::BeginTabItem("Video"))
			{
				string str = "weqweqr qc wcrqw crqwecrqwec rqwec rqwe crqwecrqwecr qervev qervew ecrqwecr qwecrqwe cr qervev qerve";
				ImGui::Text("Blah blah");
				ImGui::TextWrapped(str.c_str());
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Audio"))
			{
				string str = "weq12341 234w eqrqcwcrqwcr 112 1233a dqervewecr qwecrqwe crqw ecr qervev qerve";
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

		guiManager.endWindow();
	}

	//--------

	if (guiManager.beginWindow(3))
	{
		ImGui::Text("myWindow3");
		guiManager.AddGroup(params1);
		guiManager.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_DEFAULT);

		guiManager.endWindow();
	}

	//---------

	if (guiManager.beginWindow(4))
	{
		ImGui::Text("myWindow4");

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

		guiManager.endWindow();
	}
}

// We can setup the docking layout using hardcoded methods:
//--------------------------------------------------------------
void ofApp::dockingReset()
{
	if (1) return;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
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

	//fixed sizes
	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.2f, nullptr, &dockspace_id);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
	auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.15f, nullptr, &dockspace_id);

	// we now dock our windows into the docking node we made above

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
void ofApp::dockingRandom()
{
	if (1) return;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
	ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	//randomized sizes
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