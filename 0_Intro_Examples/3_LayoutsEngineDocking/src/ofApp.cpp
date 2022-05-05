#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	//----

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


	//-----------

	// Gui Manager
	
	//-

	// Optional:
	// TODO:
	// A windows organizer engine..
	//guiManager.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

	//-

	// Instantiate

	guiManager.setup(IM_GUI_MODE_INSTANTIATED_DOCKING);

	//-

	// Layouts Presets

	// Add the windows just with a name:
	// You will use theese added windows easely, 
	// but you must rememeber his index order!
	// Each added window will be added too to the Layout Presets Engine and auto handled.

	guiManager.addWindowSpecial("Main"); // index 0
	guiManager.addWindowSpecial("Audio"); // index 1
	guiManager.addWindowSpecial("Video1"); // index 2
	guiManager.addWindowSpecial("Video2"); // index 3
	guiManager.addWindowSpecial("Expert"); // index 4

	/*
		NOTE:
		Then we can render the windows:
		if (guiManager.beginWindow(0)) // -> This is our helpers to render each window passing the index
		{
			// ..  window widgets goes here!
		}
		guiManager.endWindow();

		NOTICE:
		We can use also raw ImGui methods and widgets,
		combined with the add-on helpers to create windows and widgets too!
	*/

	//-

	// Optional: 

	// Customize the names for the 4 default Layout Presets. Default names are P0-P1-P2-P3

	//vector<std::string> names;
	//names.push_back("Editor");
	//names.push_back("Player");
	//names.push_back("Live");
	//names.push_back("Mini");
	//guiManager.setPresetsNames(names);

	//-

	// Optional:

	// We can add extra parameters to append include into the Layout Presets

	guiManager.addParameterToLayoutPresets(guiManager.bReset);
	guiManager.addParameterToLayoutPresets(bEnable);
	//guiManager.addParameterToLayoutPresets(bMode1);
	//guiManager.addParameterToLayoutPresets(bMode2);

	//-

	// Startup:

	guiManager.startup();

	//-

	// Optional: 

	// Subscribe an optional Reset button
	// flagging a bool to true to reset. 
	// Uses the internal addon gui Reset button on the Presets Extra panel,
	// But notice that it will call a local method on this scope (ofApp).
	guiManager.setReset(&bDockingReset);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// Animate a bit
	if (bEnable)
	{
		float t = ofGetElapsedTimef();
		float s = ofMap(amount, amount.getMax(), amount.getMin(), 1, 10);
		t = ofWrap(t, 0, s);
		separation = ofMap(t, 0, s, separation.getMin(), separation.getMax());

		// Log 8 times per second at 60 fps
		if (ofGetFrameNum() % (60 / 8) == 0) guiManager.addLog(separation.getName() + " : " + ofToString(separation));
	}

	//----

	// Gui Manager with Docking features:

	guiManager.begin();
	{
		// In between here (begin/end) we can render ImGui windows and widgets.

		//--

		// Here (between beginDocking/endDocking) we can access all the docking space.

		guiManager.beginDocking();
		{
			dockingHelperUpdate();
		}
		guiManager.endDocking();

		//--

		// An extra window with some hardcoded layout triggers
		if (bEnable) dockingHelperDraw();

		//--

		// Render windows and widgets now!

		drawImGui();
	}
	guiManager.end();

	//----

	// Animate a Log
	logPopulate();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	// -> These are our helpers to render windows using the power of the Layout Engine.

	int index;

	index = 0;
	{
		if (guiManager.beginWindowSpecial(index))
		{
			// Some useful pre calculated sizes to speed up and help layouting in some scenarios.
			// Notice that these are sizes at this point of indenting/foldering!
			float _w1 = ofxImGuiSurfing::getWidgetsWidth(1); // full width
			float _w2 = ofxImGuiSurfing::getWidgetsWidth(2); // half width
			float _h = ofxImGuiSurfing::getWidgetsHeightUnit(); // standard height

			ImGui::Text("myWindow_0");

			guiManager.Add(bEnable, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);
			ofxImGuiSurfing::AddTooltip("This is a Help Tooltip! It's " + (string)(bEnable ? "TRUE" : "FALSE"));//-> When bEnable is true, we add a tooltip to the previous widget.

			guiManager.Add(guiManager.bHelp, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);
			ofxImGuiSurfing::AddTooltip("Help enables some ToolTips");

			guiManager.Add(guiManager.bLog, OFX_IM_TOGGLE_BIG);

			guiManager.Add(speed, OFX_IM_HSLIDER_BIG);
			ofxImGuiSurfing::AddTooltip("Speed controls the autopopulated Log window speed", guiManager.bHelp);

			guiManager.Add(amount, OFX_IM_HSLIDER);
			ofxImGuiSurfing::AddTooltip("Speed up separation animator when bEnable is TRUE", guiManager.bHelp);

			ImGui::PushButtonRepeat(true);//-> pushing repeats trigs
			{
				guiManager.refreshLayout();

				if (guiManager.Add(bPrevious, OFX_IM_BUTTON_BIG, 2)) //-> Using the Manager API
					//if (ofxImGuiSurfing::AddBigButton(bPrevious, _w2, _h * 2)) //-> Using the Layout API
				{
					bPrevious = false;
					lineWidth -= 0.1;
					lineWidth = ofClamp(lineWidth, lineWidth.getMin(), lineWidth.getMax());
				}
				ofxImGuiSurfing::AddTooltip("Decrease lineWidth", guiManager.bHelp);

				ImGui::SameLine();

				//if (guiManager.Add(bNext, OFX_IM_BUTTON_BIG, 2)) //-> Using the Manager API
				if (ofxImGuiSurfing::AddBigButton(bNext, _w2, _h * 2)) //-> Using the Layout API
				{
					bNext = false;
					lineWidth += 0.1;
					lineWidth = ofClamp(lineWidth, lineWidth.getMin(), lineWidth.getMax());
				}
				ofxImGuiSurfing::AddTooltip("Increase lineWidth", guiManager.bHelp);
			}
			ImGui::PopButtonRepeat();

			//ofxImGuiSurfing::AddParameter(lineWidth); //-> Using the Legacy API
			// -> Using this below style (guiManager.add(..) vs the above line legacy style, 
			// we will gain new features like:
			// some resposive layouting or mouse wheel control...
			guiManager.Add(lineWidth, OFX_IM_HSLIDER_SMALL); //-> Using the Manager API

			guiManager.Add(separation);
			guiManager.Add(lineWidth);
		}
		guiManager.endWindowSpecial(index);
	}

	//----

	index = 1;
	{
		if (guiManager.beginWindowSpecial(index))
		{
			ImGui::Text("myWindow_1");
			guiManager.AddGroup(params1);
			guiManager.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_DEFAULT);
		}
		guiManager.endWindowSpecial();
	}

	//----

	index = 2;
	{
		if (guiManager.beginWindowSpecial(index))
		{
			if (ImGui::BeginTabBar("myTabs"))
			{
				if (ImGui::BeginTabItem("Controls"))
				{
					guiManager.drawAdvanced();
					ImGui::EndTabItem();
				}
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

				ImGui::EndTabBar();
			}
		}
		guiManager.endWindowSpecial();
	}

	//----

	index = 3;
	{
		if (guiManager.beginWindowSpecial(index))
		{
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
		}
		guiManager.endWindowSpecial();
	}

	//----

	index = 4;
	//if (guiManager.getWindowSpecialVisible(index)) //-> Window state can be checked for other feedback.
	{
		if (guiManager.beginWindowSpecial(index))
		{
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
		}
		guiManager.endWindowSpecial();
	}
}

//----

// We can setup the docking layout using hardcoded methods too,
// added to the user session mouse-layouting work.

//--------------------------------------------------------------
void ofApp::dockingHelperUpdate()
{
	// Reset layout once o startup/first frame call
	{
		static bool binitiated = false;
		if (!binitiated) {
			binitiated = true; // Called only once!
			doDockingReset();
		}
	}

	// Reset layout by button gui
	if (bDockingReset) {
		bDockingReset = false;
		doDockingReset();
	}

	// Random layout by button gui
	if (bDockingRandom) {
		bDockingRandom = false;
		doDockingRandom();
	}
}

//--------------------------------------------------------------
void ofApp::dockingHelperDraw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
	flags |= ImGuiWindowFlags_NoSavedSettings; // -> exclude from layout presets

	ImGuiCond cond = ImGuiCond_None;
	cond |= ImGuiCond_Appearing;
	ImGui::SetNextWindowPos(ImVec2(400, 400), cond);
	ImGui::SetNextWindowSize(ImVec2(100, 200), cond);

	//-

ImGui:Begin("ofApp-Resets", (bool*)bEnable.get(), flags);
{
	ImGui::TextWrapped("Reset Docking Hardcoded Layouts");
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

//--------------------------------------------------------------
void ofApp::logPopulate()
{
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
		else if (_rnd < 0.8) guiManager.addLog(ofToString((ofRandom(1) < 0.5 ? "...-." : "--------.--") + ofToString("===//...--//-----..")));
		else guiManager.addLog(ofGetTimestampString());
	}
}