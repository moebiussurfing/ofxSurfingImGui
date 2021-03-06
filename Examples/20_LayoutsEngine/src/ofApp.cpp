#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowPosition(-1920, 25);

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

	// 3. Startup

	guiManager.startup();

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

* guiManager.Add(..       | API
* ofxImGuiSurfing::Add(.. | API Helpers  
* ImGui::Button(..        | RAW ImGui 

Look to other Widgets or Styles Examples 
to learn more about this topic.

)";

	guiManager.setHelpInfoApp(s);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//----

	// In between here (begin/end) we can render ImGui windows and widgets.

	guiManager.begin();
	{
		//TODO: curreently required but not used.
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
	guiManager.end();

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
	guiManager.beginDocking();
	{
	}
	guiManager.endDocking();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
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

			guiManager.AddLabelBig("myWindow_0", false);
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
			guiManager.AddLabelBig("myWindow_1", false);
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
			guiManager.AddLabelBig("Hello, down!", false, true);
			guiManager.AddLabelBig("Hello, down!", true, true);
			guiManager.AddLabelBig("Hello, down!", false, true);
			guiManager.AddSpacingBigSeparated();
			guiManager.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_HIDDEN_HEADER);
			guiManager.AddSpacingBigSeparated();
			guiManager.AddLabelBig("Hello, down!", false, true);
			guiManager.AddLabelBig("Hello, down!", true, true);

			//--

			guiManager.endWindowSpecial();
		}
	}

	//----

	index = 4;
	// ->This method can get the state (if it's open) of the special window.
	// if (guiManager.getWindowSpecialVisible(index))
	{
		if (guiManager.beginWindowSpecial(index))
		{
			guiManager.AddLabel("Hello, left!", false, true);
			guiManager.AddLabelBig("Hello, left!");
			guiManager.AddLabelBig("Hello, left!", false);
			guiManager.AddLabelHuge("Hello, left!", true, true);
			guiManager.AddLabelHuge("Hello, left!", false, false);
		}

		// ->Notice that could be out or inside of the brackets, like the above 1 to 3 windows.
		// On raw ImGui windows it will crash if you don't handle the endWindows well.
		// Here's is auto controlled, more resilient to avoid errors.
		guiManager.endWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::setupImGuiStyles()
{
	guiManager.clearStyles();

	// Queue styles to params that will be applied 
	// when drawing their widgets when populating the group where they are contained.

	// params1
	guiManager.AddStyle(lineWidth, OFX_IM_STEPPER);
	//guiManager.AddStyle(lineWidth, OFX_IM_VSLIDER);
	//guiManager.AddStyle(lineWidth, OFX_IM_DRAG);

	guiManager.AddStyle(bEnable, OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK);

	guiManager.AddStyle(bPrevious, OFX_IM_BUTTON_SMALL, 2, true);//two per row. half size. next line same row.
	guiManager.AddStyle(bNext, OFX_IM_BUTTON_SMALL, 2, false);//two per row. half size. next line not in same row.

	guiManager.AddStyle(bMode1, OFX_IM_TOGGLE_BIG_BORDER, 2, true);
	guiManager.AddStyle(bMode2, OFX_IM_TOGGLE_BIG_BORDER, 2, false);
	guiManager.AddStyle(bMode3, OFX_IM_TOGGLE_BIG_BORDER, 2, true);
	guiManager.AddStyle(bMode4, OFX_IM_TOGGLE_BIG_BORDER, 2, false);

	// params2
	guiManager.AddStyle(shapeType2, OFX_IM_STEPPER);
	guiManager.AddStyle(size2, OFX_IM_HSLIDER_BIG_NO_LABELS);
	guiManager.AddStyle(amount2, OFX_IM_DRAG);

	// params3
	guiManager.AddStyle(lineWidth3, OFX_IM_KNOB, 2, true);
	guiManager.AddStyle(separation3, OFX_IM_KNOB, 2, false);
	guiManager.AddStyle(speed3, OFX_IM_KNOB);
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