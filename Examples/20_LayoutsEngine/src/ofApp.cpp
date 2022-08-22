#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	//ofSetFrameRate(60);
	//ofSetWindowPosition(-1920, 25);

	//----

	// Parameters

	setupScene();

	//-----------

	// Gui Manager

	setupImGui();

	//--

	setupImGuiStyles();
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

	// 3. Startup

	ui.startup();

	//-

	// 4. Optional Help Info for your App
	// Must set after startup	

	string s = R"(

HELP APP 

About this example: 
Learn to use the

LAYOUT PRESETS ENGINE

----------------------------------------------

1. OVERVIEW

Speed-Up the creation and management 
of the Windows (aka Panels) of an App: 
their positions, shape, visible states 
and other settings.
Powered with 4 Layout Presets and
an improved user Workflow. 

----------------------------------------------

2. FEATURES

- All the Special Windows (aka Panels) 
are added to the Manager 
on ofApp::setup() (.addWindowSpecial)
They will be auto handled by 
the LAYOUT PRESETS ENGINE.

- It will memorize the windows positions, 
sizes and which ones are visible or hidden.

- Some optional EXTRA PARAMS can be included 
into what each Preset too.
Menu and Log toggles are included by default.

- By default we will have 4 Layout Presets. 
Then we will organize that different modes, 
sections or behaviors of our App,
by customizing that Presets for each scenario.

----------------------------------------------

3. WIDGETS

The ofParameter widgets are populated 
as usual, using (in order of preference) 
different approaches:

* ui.Add(..       | API
* ofxImGuiSurfing::Add(.. | API Helpers  
* ImGui::Button(..        | RAW ImGui 

Look to other Widgets or Styles Examples 
to learn more about this topic.

)";

	ui.setHelpInfoApp(s);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//----

	// In between here (begin/end) we can render ImGui windows and widgets.

	ui.Begin();
	{
		//TODO: currently required but not used.
		// should remove to simplify.
		drawImGuiDocking();

		//--

		// Render windows and widgets now!

		// NOTICE than common and Raw ImGui windows and widgets can be drawn here too,
		// But if you want to use the "Layout Presets Engine",
		// you need to use the API to populate windows (aka panels) 
		// and to follow some rules!

		drawImGui();
	}
	ui.End();

	//----

	// Scene

	udpateScene();
}

//--------------------------------------------------------------
void ofApp::drawImGuiDocking()
{
	//TODO: this cant be removed for the moment...
	// Should allow to disable!

	// Here (between beginDocking/endDocking) 
	// we can access all the docking space.
	ui.BeginDocking();
	{
	}
	ui.EndDocking();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
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

			ui.AddLabelBig("myWindow_0", false);
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
			ui.AddLabelBig("myWindow_1", false);
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
					ui.AddLabel(str.c_str());

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
			ui.AddLabelBig("Hello, down!", false, true);
			ui.AddLabelBig("Hello, down!", true, true);
			ui.AddLabelBig("Hello, down!", false, true);
			ui.AddSpacingBigSeparated();
			ui.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_HIDDEN_HEADER);
			ui.AddSpacingBigSeparated();
			ui.AddLabelBig("Hello, down!", false, true);
			ui.AddLabelBig("Hello, down!", true, true);

			//--

			ui.EndWindowSpecial();
		}
	}

	//----

	index = 4;
	// ->This method can get the state (if it's open) of the special window.
	// if (ui.getWindowSpecialVisible(index))
	{
		if (ui.BeginWindowSpecial(index))
		{
			ui.AddLabel("Hello, left!", false, true);
			ui.AddLabelBig("Hello, left!");
			ui.AddLabelBig("Hello, left!", false);
			ui.AddLabelHuge("Hello, left!", true, true);
			ui.AddLabelHuge("Hello, left!", false, false);
		}

		// ->Notice that could be out or inside of the brackets, like the above 1 to 3 windows.
		// On raw ImGui windows it will crash if you don't handle the endWindows well.
		// Here's is auto controlled, more resilient to avoid errors.
		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::setupImGuiStyles()
{
	ui.clearStyles();

	// Queue styles to params that will be applied 
	// when drawing their widgets when populating the group where they are contained.

	// params1
	ui.AddStyle(lineWidth, OFX_IM_STEPPER);
	//ui.AddStyle(lineWidth, OFX_IM_VSLIDER);
	//ui.AddStyle(lineWidth, OFX_IM_DRAG);

	ui.AddStyle(bEnable, OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK);

	ui.AddStyle(bPrevious, OFX_IM_BUTTON_SMALL, 2, true);//two per row. half size. next line same row.
	ui.AddStyle(bNext, OFX_IM_BUTTON_SMALL, 2, false);//two per row. half size. next line not in same row.

	ui.AddStyle(bMode1, OFX_IM_TOGGLE_BIG_BORDER, 2, true);
	ui.AddStyle(bMode2, OFX_IM_TOGGLE_BIG_BORDER, 2, false);
	ui.AddStyle(bMode3, OFX_IM_TOGGLE_BIG_BORDER, 2, true);
	ui.AddStyle(bMode4, OFX_IM_TOGGLE_BIG_BORDER, 2, false);

	// params2
	ui.AddStyle(shapeType2, OFX_IM_STEPPER);
	ui.AddStyle(size2, OFX_IM_HSLIDER_BIG_NO_LABELS);
	ui.AddStyle(amount2, OFX_IM_DRAG);

	// params3
	ui.AddStyle(lineWidth3, OFX_IM_KNOB, 2, true);
	ui.AddStyle(separation3, OFX_IM_KNOB, 2, false);
	ui.AddStyle(speed3, OFX_IM_KNOB);
}

//--

// A common Scene with ofParameters
// just for this testing purposes.

//--------------------------------------------------------------
void ofApp::setupScene()
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

//--------------------------------------------------------------
void ofApp::udpateScene()
{
	// Animate some vars

	if (!bEnable) return;

	// Animate
	float t = ofGetElapsedTimef();
	float s = ofMap(amount, amount.getMax(), amount.getMin(), 1, 10);
	t = ofWrap(t, 0, s);
	separation = ofMap(t, 0, s, separation.getMin(), separation.getMax());

	// Log
	updateLog();
}

//--------------------------------------------------------------
void ofApp::updateLog()
{
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