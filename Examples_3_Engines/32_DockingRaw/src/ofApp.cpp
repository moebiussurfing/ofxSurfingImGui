#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	setupParameters();

	//--

	setupImGui();
}

//--------------------------------------------------------------
void ofApp::setupParameters()
{
	// Scene Parameters

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

	//--

	// 3. Startup:

	ui.startup();

	//--

	// Optional: 
	// After startup

#if 0
	// Subscribe an optional Reset button
	// flagging a bool to true to reset. 
	// Uses the internal add-on GUI Reset button 
	// located on the Advanced section,
	// But notice that it will call a local method on this scope (ofApp).
	ui.setResetPtr(&bDockingRandom);
	//ui.setResetPtr(&bDockingReset);
#endif

	// Customize Help info
	string s = "HELP ofApp\n\nThis is an Example to learn \nthe Docking features.\n\nEnjoy!";
	ui.setHelpAppText(s);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	updateScene();

	//----

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
			updateImGuiDockingHelpers();
		}
		ui.EndDocking();

		//----

		// 2.1 An extra window with helpers

		// An extra window with some triggers
		// for hard-coded layout modifications. 
		if (bGui_DockingHelpers) drawImGuiDockingHelpers();

		//--

		// 2.2 Populate the visible toggles

		// for all the queued especial windows in setup()!
		if (ui.BeginWindow(bGui))
		{
			ui.drawWidgetsSpecialWindows();
			ui.AddSpacingSeparated();
			ui.Add(bGui_DockingHelpers, OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK);
			ui.EndWindow();
		}

		//----

		// 3. The Special Windows 

		// The windows previously queued to the manager on setup(),
		// that are controlled by the Layout Presets Engine.
		// Render ImGui Windows and Widgets now!
		{
			drawImGuiSpecialWindows();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindows()
{
	int index;

	index = 0;
	{
		if (ui.BeginWindowSpecial(index))
		{
			// Some useful sizes to help layouting in some scenarios.
			// e.g. when using raw ImGui widgets without the full engine.
			float _w1 = ofxImGuiSurfing::getWidgetsWidth(1); // full width
			float _w2 = ofxImGuiSurfing::getWidgetsWidth(2); // half width
			float _h1 = ofxImGuiSurfing::getWidgetsHeightUnit(); // standard height
			float _h2 = 2 * _h1; // double height

			// if ui.bHelp enabled, activates help tooltips on this window!

			ui.AddLabelHuge("Window 0", false);

			ui.Add(bGui_DockingHelpers, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

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

				if (ui.Add(bPrevious, OFX_IM_BUTTON_BIG, 2))
				{
					bPrevious = false;

					lineWidth -= 0.1f;
					lineWidth = ofClamp(lineWidth, lineWidth.getMin(), lineWidth.getMax());
				}
				ui.AddTooltip("Decrease lineWidth " + ofToString(lineWidth));

				ImGui::SameLine();

				if (ofxImGuiSurfing::AddBigButton(bNext, _w2, _h2))
				{
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

	//----

	index = 1;
	{
		if (ui.BeginWindowSpecial(index))
		{
			ui.AddLabelHuge("Window 1", false);

			ui.Add(bGui_DockingHelpers, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

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

			ui.Add(bGui_DockingHelpers, OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK);

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

			ui.Add(bGui_DockingHelpers, OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK);

			ui.AddLabelHuge("Hello, down Huge!", false, true);
			ui.AddLabelBig("Hello, down Big!", false, true);
			ui.AddLabelBig("Hello, down Big! Hello, down! Hello, down!");
			ui.AddSpacingBigSeparated();
			ui.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_HIDDEN_HEADER);
			ui.AddSpacingBigSeparated();
			ui.AddLabelBig("Hello, down Big!", false, true);
			ui.AddLabelHuge("Hello, down Huge! Hello, down! Hello, down!");

			//--

			ui.EndWindowSpecial();
		}
	}

	//----

	index = 4;
	{
		//TODO: Fix sizing bug
		if (ui.getIsWindowSpecialVisible(index))
		{
			IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;
		}

		if (ui.BeginWindowSpecial(index))
		{
			ui.AddLabelHuge("Window 4", false);

			ui.Add(bGui_DockingHelpers, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

			ui.AddLabelHuge("Hello, left Huge!", true, true);
			ui.AddLabelHuge("Hello, left Huge!", false, false);
			ui.AddLabelBig("Hello, left Big!");
			ui.AddLabel("Hello, left!", false, true);
			ui.AddLabelBig("Hello, left Big!", false);

			ui.EndWindowSpecial();
		}
	}
}

//----

// Scene

//--------------------------------------------------------------
void ofApp::updateScene()
{
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
	if (ofGetFrameNum() % m == 0)
	{
		if (ofNoise(ofGetElapsedTimef()) < 0.4f) return; // skip one third

		std::string ss = ofToString(ofGetFrameNum());
		float _rnd = ofRandom(1);

		if (_rnd < 0.2)
			ui.AddToLogAndNotifier(ss);

		else if (_rnd < 0.4)
			ui.AddToLogAndNotifier(ofToString(_rnd));

		else if (_rnd < 0.6)
			ui.AddToLogAndNotifier(ofToString(ofToString((ofRandom(1) < 0.5 ? "..-." : "---.--..")) + "---------" + ofToString((ofRandom(1) < 0.5 ? ".--.-." : "...-.--.."))));

		else if (_rnd < 0.8)
			ui.AddToLogAndNotifier(ofToString((ofRandom(1) < 0.5 ? "...-." : "--.--") + ofToString("===//...--//-----..")));

		else
			ui.AddToLogAndNotifier(ofGetTimestampString());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ofLogNotice(__FUNCTION__) << " " << char(key);

	if (key == 'g')bGui = !bGui;
}

//----

// Useful Docking snippets

// On runtime, the user session could design his layout using shift+mouse dragging.
// But we can setup the docking layout using hard-coded methods.

//--------------------------------------------------------------
void ofApp::updateImGuiDockingHelpers()
{
	// Reset layout once o startup/first frame call.
	// Called only once!
	if(bStartupDockingReset)
	{
		static bool binitiated = false;
		if (!binitiated) {
			binitiated = true;

			doDockingReset();
		}
	}

	//----

	// Reset layout by a button
	if (bDockingReset)
	{
		bDockingReset = false;

		doDockingReset();
	}

	//--

	// Random layout by a button
	if (bDockingRandom)
	{
		bDockingRandom = false;

		doDockingRandom();
	}

	//--

	//TODO:

#ifdef SURFING_USE_MANAGER
	bool bDoRefresh = 0;

	// Manager save/load
	if (bFlagLoadLayout) {
		bFlagLoadLayout = false;

		loadLayoutImGuiIni();
		bDoRefresh = 1;
	}
	if (bFlagSaveLayout) {
		bFlagSaveLayout = false;

		saveLayoutImGuiIni();
		bDoRefresh = 1;
	}

#if 1
	//if(bDoRefresh)
	{
		ofRectangle rectangle_Central_MAX;
		ofRectangle rectangle_Central; // current free space viewport updated when changes
		ofParameter<bool> bDrawView2{ "Draw View 2", false };



		ImGuiID dockNodeID;
		ImGuiDockNode* dockNode;

		//----

		// Get check free space
		// central inter docks rectangle

		ImGuiDockNodeFlags flagsDock = ImGuiDockNodeFlags_None;
		//flagsDock += ImGuiDockNodeFlags_DockSpace;
		flagsDock += ImGuiDockNodeFlags_PassthruCentralNode;

		// A
		dockNodeID = ImGui::DockSpaceOverViewport(NULL, flagsDock);
		dockNode = ImGui::DockBuilderGetNode(dockNodeID);

		// B
		//ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(dockNodeID);

		if (dockNode)
		{
			ImGuiDockNode* centralNode = ImGui::DockBuilderGetCentralNode(dockNodeID);

			// Verifies if the central node is empty (visible empty space for oF)
			if (centralNode && centralNode->IsEmpty())
			{
				ImRect availableSpace = centralNode->Rect();
				//availableSpace.Max = availableSpace.Min + ImGui::GetContentRegionAvail();
				//ImGui::GetForegroundDrawList()->AddRect(availableSpace.GetTL() + ImVec2(8, 8), availableSpace.GetBR() - ImVec2(8, 8), IM_COL32(255, 50, 50, 255));

				ImVec2 viewCenter = availableSpace.GetCenter();
				// Depending on the viewports flag, the XY is either absolute or relative to the oF window.
				//if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());

				float ww = availableSpace.GetSize().x;
				float hh = availableSpace.GetSize().y;
				rectangle_Central_MAX = ofRectangle(viewCenter.x, viewCenter.y, ww, hh);

				bool bDebug_ = bDrawView2.get();
				if (bDebug_)
				{
					int _wl = 2;
					int pad = 10;

					ofPushStyle();
					ofSetRectMode(OF_RECTMODE_CENTER);

					int g = 0;
					ofColor cl = ofColor::white;
					//ofColor cl = ofColor::orange;

					//int g = 255 * Bounce(0.5);
					int a = 255.f * ofMap(Bounce(1), 0.0f, 1.0f, 0.2f, 1.0f, true);
					ofColor c = ofColor(cl.r, cl.g, cl.b, a);
					//ofColor c = ofColor(g, a);
					ofSetColor(c);

					ofNoFill();
					ofSetLineWidth(_wl);

					float ww = availableSpace.GetSize().x - pad;
					float hh = availableSpace.GetSize().y - pad;

					ofRectangle rDebug;
					rDebug = ofRectangle(viewCenter.x, viewCenter.y, ww, hh);
					ofDrawRectangle(rDebug);

					//ofDrawRectangle(rectangle_Central_MAX);
					ofSetRectMode(OF_RECTMODE_CORNER);
					ofPopStyle();
				}
				// move to left corner mode
				rectangle_Central_MAX.translate(-ww / 2, -hh / 2);

				//-

				static ofRectangle rectangle_Central_MAX_PRE;

				{
					if (rectangle_Central_MAX_PRE != rectangle_Central_MAX)
					{
						// updates when layout changes..
						rectangle_Central_MAX_PRE = rectangle_Central_MAX;

						bool bSkip = false;
						bSkip = (rectangle_Central.getWidth() == 0 || rectangle_Central.getHeight() == 0);
						bSkip += (rectangle_Central_MAX.getWidth() == 0 || rectangle_Central_MAX.getHeight() == 0);
						if (!bSkip)
						{
							// fit exact rectangle to borders and scaled to fit
							//rectangle_Central = DEMO3_Svg.getRect();
							//if (rectangle_Central_MAX.getWidth() != 0 && rectangle_Central_MAX.getHeight() != 0) // avoid crash
							rectangle_Central.scaleTo(rectangle_Central_MAX, OF_ASPECT_RATIO_KEEP,
								OF_ALIGN_HORZ_CENTER, OF_ALIGN_VERT_CENTER);

							//// rescaled rectangle a bit
							//float _scale = 0.7f;
							//rectangle_Central_Transposed = rectangle_Central;
							//rectangle_Central_Transposed.scaleFromCenter(_scale, _scale);//scale down to fit layout spacing better
							//rectangle_Central_Transposed.translateY(rectangle_Central.getHeight() * 0.07);//move down a bit
							//DEMO3_Svg.setRect(rectangle_Central_Transposed);
						}
					}
				}
			}
		}
	}
#endif

#endif
}

//--------------------------------------------------------------
void ofApp::drawImGuiDockingHelpers()
{
	if (!bGui_DockingHelpers) return;

	string s;

	//TODO: Fix sizing bug
	IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

	if (ui.BeginWindow(bGui_DockingHelpers))
	{
		float _w = ofxImGuiSurfing::getWidgetsWidth();
		float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);
		float _h = ofxImGuiSurfing::getWidgetsHeightUnit();

		//--

		s = "Layout";
		ui.AddLabelBig(s);

		// Reset docking layout

		if (ImGui::Button("Reset", ImVec2(_w, _h)))
		{
			bDockingReset = true;
			// Flag to call on a precise draw point, 
			// inside the draw begin/end context
		}
		s = "Layout Reset Docking \nto a hard-coded layout.";
		ui.AddTooltip(s);

		//--

		// Randomize docking layout

		if (ImGui::Button("Random", ImVec2(_w, _h)))
		{
			bDockingRandom = true;
			// Flag to call on a precise draw point,
			// inside the draw begin/end context
		}
		s = "Layout Reset Docking \nto a randomized layout.";
		ui.AddTooltip(s);

		ui.AddSpacingSeparated();

		//--

		//TODO:

#ifdef SURFING_USE_MANAGER
		s = "Manager";
		ui.AddLabelBig(s);

		if (ui.AddButton("Load", OFX_IM_BUTTON, 2)) {
			bFlagLoadLayout = true;
			//loadLayoutImGuiIni();
		}
		ui.SameLine();

		if (ui.AddButton("Save", OFX_IM_BUTTON, 2)) {
			bFlagSaveLayout = true;
			//saveLayoutImGuiIni();
		}

		ui.AddSpacingSeparated();
#endif

		//--

		s = "Windows";
		ui.AddLabelBig(s);

		// Show/hide all Special Windows / Panels

		if (ImGui::Button("All", ImVec2(_w2, _h)))
		{
			ui.setShowAllPanels(true);
		}
		ui.SameLine();

		if (ImGui::Button("None", ImVec2(_w2, _h)))
		{
			ui.setShowAllPanels(false);
		}

		ui.AddSpacingSeparated();

		//--

		s = "Internal";
		ui.AddLabelBig(s);

		ui.AddMinimizerToggle();
		if (ui.isMaximized()) {
			ui.AddAutoResizeToggle();
			ui.AddLogToggle();
			ui.AddNotifierToggle();
		}

		ui.EndWindow();
	}
}

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
	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.2f, nullptr, &dockspace_id);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.34f, nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.13f, nullptr, &dockspace_id);
	auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.13f, nullptr, &dockspace_id);

	//--

	// We now dock our windows into the docking node we made above

	// A Autogetting names
	// We can get the window names by the index to rename easy, just in one place when added on setup.
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(0).c_str(), dock_id_left);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(1).c_str(), dock_id_right);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(2).c_str(), dock_id_right);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(3).c_str(), dock_id_top);
	ImGui::DockBuilderDockWindow(ui.getWindowSpecialName(4).c_str(), dock_id_down);

	// B hardcoded names
	//ImGui::DockBuilderDockWindow("Main Window", dock_id_top);
	//ImGui::DockBuilderDockWindow("Audio Window", dock_id_right);
	//ImGui::DockBuilderDockWindow("Video 2", dock_id_down);
	//ImGui::DockBuilderDockWindow("Video 3", dock_id_left);
	//ImGui::DockBuilderDockWindow("Advanced", dock_id_right);

	ImGui::DockBuilderFinish(dockspace_id);
}

//--------------------------------------------------------------
void ofApp::doDockingRandom()
{
	ofLogNotice(__FUNCTION__);

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
	ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

	// Randomized sizes
	auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, ofRandom(0.2, 0.35), nullptr, &dockspace_id);
	auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, ofRandom(0.2, 0.35), nullptr, &dockspace_id);
	auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, ofRandom(0.2, 0.35), nullptr, &dockspace_id);
	auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, ofRandom(0.2, 0.35), nullptr, &dockspace_id);

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
