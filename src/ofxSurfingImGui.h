
#pragma once


/*

	This class has is the main header.
	The only one you need to include into your ofApp/Class

*/


//----

/*

	TODO:

	STYLE
	+ check toggles color theme. correlate with slider grab.
		hover do not change color!
		the fix the knobs colors too.
		push buttons could be darken as if it was a 3D button..
	+ enable floating windows/context
	+ fix param colors
	+ fix param string not drawn

	API UPDATE v3 
	/ ofParams helpers
	+ pass ImVec2 to all widgets
	+ make templated for all types
	+ add multi choice flags

	HELPERS
	+ fix range slider to a new widget
		add drag from range center
	+ useful for multi dim params
	https://github.com/yumataesu/ofxImGui_v3/blob/master/src/Helper.cpp
	+ fix toggles do not trigs/return true when changes ?
	+ add clickable label toggle widget.
	+ add tool-tip types on styles on a new ui.Add(..arg
	https://github.com/d3cod3/ofxMosaicPlugin/blob/master/src/core/imgui_helpers.h
	+ API v2: fix nested groups with different styles
		+ next / nested groups headers are weird hidden sometimes ?
		+ nested groups are (inheriting) expanded when parent is expanded.

	GENERAL
	+ add disabler for avoid store settings
	+ fix draw in front the ImGui. not working drawing OF_EVENT_ORDER_AFTER_APP.
		something WIP with bAutoDraw..
	+ fix workflow handling layout presets breaks when Link is enabled.
	+ fix reset aligners that populates out of the view port.
		must apply only over special windows maybe ?

	DOCKING ( WIP )
	+ allow panel and presets dockeable too!
	+ fix make dockeable all windows on same space.
	+ fix multiple dock spaces that are colliding/one over another.
	+ fix view-port rectangle preview.
	+ add video view-port example.
	+ docking overlaps sometimes on layout management

	SMALL THINGS
	+ remake mode free move and move locked simpler. 
		a flag for each window ?
	+ aspect ratio/fit modes for game view port.
	+ fix log ofxImGuiSurfing::WindowsOrganizer::isInitiated:

	NEW FEATURES
	+ auto midi knobs to FX:
		set the master 6 knobs.
		auto assign to these 6 knobs
		from current GUI editing / first plane page.

	FEATURE
	+ Probably not required.
		But could think about linking multiple instances.
		Or populate as a kind of static to share between instances ?
		for example, to share organizer windows:
		// Link internal stuff
		ui.getGuiToggleOrganizer().makeReferenceTo(myClassObject.ui.getGuiToggleOrganizer());
		Probably a better fix/workaround is to rename each common windows on each gui manager instance
		or the pad between windows setting. we could pass pointers to all instances.

*/


/*

	BUGS:

	Strings inside paramGroups are not rendered ?
	It seems than special windows engine
	puts all toggles to false by default ?

*/


/*

	NOTES:

	Docking Help
	https://github.com/ocornut/imgui/issues/2109

	Docking Demo
	https://github.com/ocornut/imgui/blob/1ad1429c6df657f9694b619d53fa0e65e482f32b/imgui_demo.cpp#L7399-L7408

	Tool-Bar Example
	https://gist.github.com/moebiussurfing/b7652ba1ecbd583b7c4f18e25a598551

*/


//--------------------------------------------------------------

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"
#define IMGUI_DEFINE_MATH_OPERATORS

//--------------------------------------------------------------

// This header includes the main classes: 
// Layout, helpers and all my Surfing widgets.
// Some others are moved out of the /src folder 
// bc they are less commonly used.
// You must include them manually from 
// OFX_ADDON/_LIBS if you want to use it in your project.

#include "ImGui/GuiManager.h"

#include "ImGui/themes/ofxSurfing_ImGui_ThemesEditor.h"


//--

// Alias and namespace's

using namespace ofxImGuiSurfing;

// Short alias for the main class.
using ofxSurfingGui = SurfingGuiManager;

//--------------------------------------------------------------

//TODO: 
// make an index/summary/list of
// all the below EXAMPLES aNd SNIPPETS

/*

		MORE EXAMPLE SNIPPETS
		---------------------

		LOOK RECOMMENDED USAGE BELOW!

		LEARN HOW TO CREATE
		WINDOWS, PANELS,
		AND SUB PANELS
		AND DIFFERENT TREES MODES
		...etc

*/


//----


// 0. TOP SNIPPETS HERE !

/*

	// HOW TO
	// MINIMAL SNIPPET

	#include "ofxSurfingImGui.h"
	ofxSurfingGui ui;

	void ofApp::drawGui()
	{
		ui.Begin();
		{
			if (ui.BeginWindow("ofApp")) {

				ui.EndWindow();
			}
		}
		ui.End();
	}

/*


//--


/*

	// HOW TO
	// COMMON USAGE

	// #1
	{
		// ofApp.h
		{
			#include "ofxSurfingImGui.h"

			ofxSurfingGui ui;
			ofParameter<bool> bGui{ "Show", true };
		}

		// ofApp.cpp
		{
			ofApp::setup()
			{
				//ui.setup(); //-> in some cases can be omitted.
			}

			ofApp::draw()
			{
				ui.Begin();
				{
					//if (bGui) IMGUI_SUGAR__WINDOWS_CONSTRAINTS;

					if (ui.BeginWindow(bGui))
					{
						ui.Add(ui.bMinimize, OFX_IM_TOGGLE_ROUNDED);

						if (!ui.bMinimize) { // not minimized
						}

						//..

						ui.EndWindow();
					}
				}
				ui.End();
			}
		}
	}
*/


//----


/*

	//--------------------------------------------------------------

	// 1. HOW TO CREATE A WINDOW ?

	THESE ARE DEPRECATED/LEGACY MODES
	THAT DO NOT USES THE ADD-ON POWERED API !

	//---

	// WINDOWS USING RAW ImGui (LEGACY)
	// KIND OF DEPRECATED.
	// Better to use the add-on engine,
	// but it will work using RAW ImGui too!

	// 1.0 SIMPLE

	ImGui::Begin("myWindow");
	{ }
	ImGui::End();

	//----

	// 1.1 WINDOW WITH NAME WITH FLAGS (LEGACY)

	string _name = "myWindow";
	ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
	ImGui::Begin(_name.c_str(), NULL, _flagw);
	{ }
	ImGui::End();

	//----

	// 1.2 WINDOW USING MORE RAW (LEGACY)

	ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
	string _name = "myWindow";
	ofxImGui::Settings mainSettings = ofxImGui::Settings();
	if (ofxImGui::BeginWindow(_name.c_str(), mainSettings, _flagw))
	{ }
	ofxImGui::EndWindow(mainSettings);

/*


//--------------------------------------------------------------
// WINDOW HELPERS


/*

	SNIPPET
	FORCE WINDOW POSITION & SHAPE

	{
		float x = 10;
		float y = 10;
		float w = 200;
		float h = 200;
		ImGuiCond flag = ImGuiCond_Appearing;
		ImGui::SetNextWindowPos(ImVec2(x, y), flag);
		ImGui::SetNextWindowSize(ImVec2(w, h), flag);
	}


	//--


	SNIPPET
	WINDOW CONSTRAINTS
	FOR LIMITING SHAPE SIZE

	{
		ImGuiCond flagsc = ImGuiCond_Appearing;
		static int type = 0;
		if (type == 0) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0), ImVec2(-1, FLT_MAX)); // Vertical only
		if (type == 1) ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1)); // Horizontal only
		if (type == 2) ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
		if (type == 3) ImGui::SetNextWindowSizeConstraints(ImVec2(400, -1), ImVec2(500, -1)); // Width 400-500
		if (type == 4) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 400), ImVec2(-1, 500)); // Height 400-500
		ImGui::SetNextWindowPos(ImVec2(10, 10), flagsc);
		ImGui::SetNextWindowSize(ImVec2(100, 100), flagsc);
		ImGui::Begin("Window Control");
		{
			ImGui::SliderInt("TypeConstraints", &type, 0, 4);

			int open_action = -1;
			if (ImGui::Button("Expand"))
				open_action = 0;
			ImGui::SameLine();
			if (ImGui::Button("collapse"))
				open_action = 1;
			ImGui::SameLine();

			if (open_action != -1) {
				ImGui::SetNextWindowCollapsed(open_action != 0);
				//ImGui::SetNextItemOpen(open_action != 0);
			}
		}
		ImGui::End();
	}

*/


//----


/*

	EXAMPLE
	ANOTHER WINDOW WITH SNAPPING TO A GRID
	AN EXTRA BEGIN/END PAIR.
	WITH A SNAPPING GRID.


	//--------------------------------------------------------------
	void Begin(const std::string& name)
	{
		const int snapSz = 20;
		//const int snapSz = 16;

		auto snap = [=](float value, float snap_threshold) -> float {
			float modulo = std::fmodf(value, snap_threshold);
			float moduloRatio = std::fabsf(modulo) / snap_threshold;
			if (moduloRatio < 0.5f)
				value -= modulo;
			else if (moduloRatio > (1.f - 0.5f))
				value = value - modulo + snap_threshold * ((value < 0.f) ? -1.f : 1.f);
			return value;
		};

		ImGui::Begin(name.data());
		if (ImGui::IsItemActive()) {
			auto p = ImGui::GetWindowPos();
			auto size = ImGui::GetWindowSize();

			float x = snap(p.x, snapSz);
			float y = snap(p.y, snapSz);
			float sizex = snap(size.x, snapSz);
			float sizey = snap(size.y, snapSz);
			ImGui::SetWindowPos(ImFloor(ImVec2(x, y)));
		}
	}

	//--------------------------------------------------------------
	void End() {
		ImGui::End();
	}


	//----

	EXAMPLE
	ImGui RAW without the API add-on helpers.
	ANOTHER EXTRA BEGIN/END PAIR

	//--------------------------------------------------------------
	bool BeginWindow(std::string name, bool* p_open, ImGuiWindowFlags flags)
	{
		return ImGui::Begin(name.c_str(), p_open, flags);
	}

	//--------------------------------------------------------------
	void EndWindow()
	{
		ImGui::End();
	}

*/


//----


/*

	EXAMPLE
	GET WINDOW SHAPE.
	CALL BETWEEN BEGIN/END

	ofRectangle r = ofRectangle(
		ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
		ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

*/


//--------------------------------------------------------------


/*

	// 2. TREES / Folders

	// 2.0 Simple TREE (RECOMMENDED)

	if (ui.BeginTree("COLORS"))
	{
		//.. -> widgets

		ui.EndTree();
	}

	//----

	// 2.1 Simple TREE RAW / LEGACY (no framed)

	if (ImGui::TreeNode("_Tree"))
	{
		//ui.refreshLayout();
		//.. -> widgets

		ImGui::TreePop();
	}

	//----

	// 2.2 COLLAPSING RAW PANEL (framed and closed by default)

	{
		static bool bOpen = true;
		ImGuiColorEditFlags _flagw = 
			(bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);

		if (ImGui::CollapsingHeader("_Collapsing", _flagw))
		{
			//ui.refreshLayout();
			//.. -> widgets
		}
	}

	//----

	// 2.3 TREE EX - RAW TREE WITH FLAGS

	{
		static bool bOpen = true;
		ImGuiTreeNodeFlags _flagt = 
			(bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);

		_flagt |= ImGuiTreeNodeFlags_Framed;

		if (ImGui::TreeNodeEx("_TreeEx", _flagt))
		{
			//ui.refreshLayout();
			//.. -> widgets

			ImGui::TreePop();
		}
	}

*/


//----


//--------------------------------------------------------------
// RAW IMGUI EXAMPLES

/*

	EXAMPLE
	HOW TO SET COLORS?

	static float b = 1.0f;
	static float c = 0.5f;
	static int i = 3; // hue colors are from 0 to 7
	ImVec4 _color1 = (ImVec4)ImColor::HSV(i / 7.0f, b, b);
	ImVec4 _color2 = (ImVec4)ImColor::HSV(i / 7.0f, c, c);

*/


/*

	EXAMPLE
	IMGUI INFOS

	auto io = ImGui::GetIO();
	const auto label = ct::toStr("Dear ImGui %s (Docking)", ImGui::GetVersion());
	const auto size = ImGui::CalcTextSize(label.c_str());
	ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - size.x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));
	ImGui::Text("%s", label.c_str());

*/


/*

	EXAMPLE
	TABS

	if (ImGui::BeginTabBar("Tabs Blah"))
	{
		if (ImGui::BeginTabItem("Video"))
		{
			ImGui::Text("Blah blah");
			std::string str = "text";
			ImGui::TextWrapped(str.c_str());

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Audio"))
		{
			ImGui::Text("Blah blah");
			std::string str = "text";
			ImGui::TextWrapped(str.c_str());

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Controls"))
		{
			ui.DrawAdvancedBundle();

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

*/


//--


//--------------------------------------------------------------
// EXAMPLES AND SNIPPETS
// MAINLY NOT IMGUI / RAW: 
// USING THE ADD-ON API AND HELPERS


/*

	EXAMPLE
	COMBO USING A PARAM INT WITH DEFINED NAMES

	static vector<string>names{ "IGNORE","LEFT","RIGHT","CENTER" };
	ui.AddCombo(indexParam, names);

*/


/*

	EXAMPLE
	PREV / NEXT DUAL BUTTONS
	THAT IS IMPLEMENTED NOW
	INTO A CUSTOM WIDGET CALLED 
	AddComboArrows(..

	{
		static ofParameter<bool> bPrev{ "<", false };
		static ofParameter<bool> bNext{ ">", false };

		ui.Add(bPrev, OFX_IM_BUTTON, 2, true);
		ui.Add(bNext, OFX_IM_BUTTON, 2);

		if (bPrev)
		{
			bPrev = false;
			index_FX = ofClamp(index_FX - 1, index_FX.getMin(), index_FX.getMax());
		}
		if (bNext)
		{
			bNext = false;
			index_FX = ofClamp(index_FX + 1, index_FX.getMin(), index_FX.getMax());
		}
	}

*/


/*

	EXAMPLE
	ADD MOUSE WHEEL 
	TO TWEAK A FLOAT PARAM

	ofxImGuiSurfing::AddParameter(bpm);

	// Add mouse wheel to the float param
	{
		float wheel = ImGui::GetIO().MouseWheel;
		bool bCtrl = ImGui::GetIO().KeyCtrl; // ctrl to fine tunning
		{
			ofParameter<float> p = dynamic_cast<ofParameter<float>&>(bpm);
			float resolution = -1;

			resolution = (p.getMax() - p.getMin()) / 800.f;//make smaller

			//resolution = (p.getMax() - p.getMin()) / 100.f;
			// 100 steps for all the param range

			p += wheel * (bCtrl ? resolution : resolution * 10);
			p = ofClamp(p, p.getMin(), p.getMax()); // clamp
		}
	}

*/


/*

	EXAMPLE
	RESPONSIVE LAYOUT

	2 DOUBLE HEIGHT BUTTONS IN ONE LINE +
	3 SINGLE HEIGHT BUTTONS IN ONE LINE
	WITH DIFFERENT PROPORTIONS

	float w = ImGui::GetContentRegionAvail().x;
	float h = ImGui::GetFrameHeight(); // single unit height
	float hh = 2 * h; // double height
	float spx = ImGui::GetStyle().ItemSpacing.x; // spacing between two widgets
	float _spx;
	// Calculate spacing for each line:
	// _spx = (spx * (amount - 1)) / amount;  // amount widgets per line
	_spx = (spx * (2 - 1)) / 2;
	ImGui::Button("B1", ImVec2(w * 0.25 - _spx, hh));
	ImGui::SameLine();
	ImGui::Button("B2", ImVec2(w * 0.75 - _spx, hh));
	_spx = (spx * (3 - 1)) / 3;
	ImGui::Button("B3", ImVec2(w * 1 / 3.f - _spx, h));
	ImGui::SameLine();
	ImGui::Button("B4", ImVec2(w * 1 / 3.f - _spx, h));
	ImGui::SameLine();
	ImGui::Button("B5", ImVec2(w * 1 / 3.f - _spx, h));

*/


/*

	EXAMPLE
	INPUT TEXT 
	WITH HUGE FONT

	static ofParameter<string>i{ "input text", "" };
	ui.PushFont(OFX_IM_FONT_HUGE);
	if (ui.Add(i, OFX_IM_TEXT_INPUT_NO_NAME))
	{
	};
	ui.PopFont();

*/


/*

	EXAMPLE
	HOW TO CUSTOMIZE FONTS
	AND USE DIFFERENT FONT STYLES?

	NOTICE: 
	This is also done on GuiManager.h in the method
	SurfingGuiManager::setupImGuiFonts()
	By default there is 4 different font styles and sizes.
	Maybe could be recommended to hardcoded your personalized fonts.
	But also you can queue other fonts next to the default ones
	maybe, like icons or fonts awesome stuff.

	{
		std::string _fontName;
		std::string _path;
		float _fontSize;

		_fontSize = 11;
		_fontName = "overpass-mono-bold.otf";
		_path = "assets/fonts/" + _fontName;
		ui.pushFont(_path, _fontSize);//index 0

		_fontSize = 14;
		_fontName = "RecMonoLinear-Bold-1.082.ttf";
		_path = "assets/fonts/" + _fontName;
		ui.pushFont(_path, _fontSize);//index 1

		_fontSize = 17;
		_fontName = "RecMonoLinear-Regular-1.082.ttf";
		_path = "assets/fonts/" + _fontName;
		ui.pushFont(_path, _fontSize);//index 2

		ui.addFont(_path, _fontSize);
		ui.setDefaultFontIndex(2);

		// Customize Font
		static bool bCustomFont = true;
		if (bCustomFont) ui.pushStyleFont(1);
		{
			//.. Will draw widgets using this font
		}
		if (bCustomFont) ui.popStyleFont();
	}

*/


/*

	EXAMPLE
	COMMON LEFT RIGHT ARROWS
	TO BROWSE AN INDEX

		// That is implemented now
		// into a widget called AddComboArrows(..

		if (ui.AddButton("<", OFX_IM_BUTTON_SMALL, 2)) {
			////cycled
			//if (index == index.getMin()) index = index.getMax();
			//index--;
			//limited
			if (index > index.getMin()) index--;
		};
		ui.SameLine();
		if (ui.AddButton(">", OFX_IM_BUTTON_SMALL, 2)) {
			////cycled
			//if (index == index.getMax()) index = index.getMin();
			//index++;
			//limited
			if (index < index.getMax()) index++;
		};

*/


/*

	EXAMPLE
	IMPROVE LAYOUT ENGINE
	WITH TABLES/COLUMNS
	AND AUTORESIZE WIDGETS
	WITH COLUMN DIVIDERS DRAGGING

{
	ui.AddSpacingBigSeparated();

	ui.AddLabelBig("IMPROVE LAYOUT ENGINE WITH TABLES / COLUMNS AND AUTORESIZE WIDGETS WITH COLUMN DIVIDERS DRAGGING");

	ui.AddSpacingBig();

	float spcx = ImGui::GetStyle().ItemSpacing.x;
	float w100 = ImGui::GetContentRegionAvail().x;
	float w = ofxImGuiSurfing::getWidgetsWidth(1) - spcx;
	float w1 = w * 0.3f;
	float w2 = w * 0.7f;

	ImVec2 sz;
	float h = 50;
	float h2 = 150;

	ImGui::Columns(2, "##table1");

	//ImGui::SetCursorPosX(w100 * 0.3f);
	//ImGui::SetColumnWidth(0, w100 * 0.3f);
	//ImGui::SetColumnWidth(1, w100 * 0.7f);

	sz = ImVec2(ImGui::GetContentRegionAvail().x, h);
	ImGui::Button("but1", sz);

	ImGui::NextColumn();

	sz = ImVec2(ImGui::GetContentRegionAvail().x, h);
	ImGui::Button("but2", sz);

	ImGui::Columns(1);

	ui.AddSpacingBig();

	//--

	ImGui::Columns(2, "##table2");

	static float wc = (ImGui::GetWindowWidth() - spcx);
	//ImGui::SetColumnWidth(0, wc * 0.4f);
	//wc = ImGui::GetColumnWidth();//allow edit
	//ImGui::SetColumnWidth(1, 100.0f);

	static float tmpRef1 = 1;
	static float tmpRef2 = 1;

	sz = ImVec2(ImGui::GetContentRegionAvail().x, h2);
	ImGui::VSliderFloat("v1", sz, &tmpRef1, 0, 1);

	ImGui::NextColumn();

	sz = ImVec2(ImGui::GetContentRegionAvail().x, h2);
	ImGui::VSliderFloat("v2", sz, &tmpRef2, 0, 1);

	ImGui::Columns(1);

	ui.AddSpacingBigSeparated();
}

*/


/*

	TODO: WIP:

	EXAMPLE
	TWO COLUMNS WITH 2 VERTICAL SLIDERS
	USING TWO DIFERENT MODES / TEMPLATES
	WITH A RESET BUTTON ON EACH ONE.

	//--

	static ofParameter<float> v1{ "v1",0.5, 0,1 };
	static ofParameter<float> v2{ "v2",0, -1,1 };
	static ofParameter<float> v3{ "v3",0, 0,1 };
	static int bangDetectorIndex = 0;

	ui.AddSpacingBigSeparated();

	ImGui::Columns(2, "t1", false);
	ui.Add(v1, OFX_IM_VSLIDER_NO_NUMBER, 2);
	ImGui::PushID("##RESET1");
	if (ui.AddButton("Reset", OFX_IM_BUTTON_SMALL, 2)) {
		v1 = 0;
	}
	ImGui::PopID();
	ImGui::NextColumn();

	// Template A
	if (bangDetectorIndex == 0)
	{
		ui.Add(v2, OFX_IM_VSLIDER_NO_NUMBER, 2);
		ui.AddTooltip(ofToString(v2.get(), 2));
		ImGui::PushID("##RESET2");
		if (ui.AddButton("Reset", OFX_IM_BUTTON_SMALL, 2)) {
			v2 = 0.5f;
		}
		ImGui::PopID();
	}

	// Template B
	else if (bangDetectorIndex == 1)
	{
		ImGui::Columns(2, "t2", false);
		ui.Add(v3, OFX_IM_VSLIDER_NO_LABELS);
		ImGui::NextColumn();
		ui.Add(v3, OFX_IM_VSLIDER_NO_LABELS);
		ImGui::Columns(1);
	}

	ImGui::Columns(1);

	//--

*/


/*

	EXAMPLE
	THREE COLUMNS 
	WITH A KNOB AND 
	2 VERTICAL SLIDERS
	WITH A RESET BUTTON.
	UI USED AS A POINTER REFERENCED.

		ui->Add(bSmooth, OFX_IM_TOGGLE_ROUNDED_SMALL);
		if (bSmooth)
		{
			ImGui::Columns(3, "", false);
			ui->Add(smoothGain, OFX_IM_KNOB_DOTKNOB, 3);
			ImGui::PushID("##R");
			if (ui->AddButton("Reset", OFX_IM_BUTTON_SMALL, 3)) {
				smoothGain = 0;
				smoothVal1 = 0.5;
				smoothVal2 = 0.5;
			}
			ImGui::PopID();
			ImGui::NextColumn();
			ui->Add(smoothVal1, OFX_IM_VSLIDER_NO_LABELS, 3);
			string s;
			s = smoothVal1.getName() + ofToString(smoothVal1.get(), 2);
			ui->AddTooltip(s);
			ImGui::NextColumn();
			ui->Add(smoothVal2, OFX_IM_VSLIDER_NO_LABELS, 3);
			s = smoothVal2.getName() + ofToString(smoothVal2.get(), 2);
			ui->AddTooltip(s);
			ImGui::Columns(1);
		}

*/


/*

	EXAMPLE
	A BIG COMBO SELECTOR
	WITH AN INDEX PARAM, 
	ARROWS, NAMES VECTOR
	CUTE STYLED

	{
			// Style selector

			ui.AddSpacingBigSeparated();
			ui.AddLabelBig("Style Selector", true);

			vector<string> knobStyles;
			knobStyles.push_back("TICKKNOB");
			knobStyles.push_back("DOTKNOB");
			knobStyles.push_back("WIPERKNOB");
			knobStyles.push_back("WIPERONLYKNOB");
			knobStyles.push_back("WIPERDOTKNOB");
			knobStyles.push_back("STEPPEDKNOB");
			knobStyles.push_back("SPACEKNOB");
			const int sz = (int)(knobStyles.size()) - 1;
			static ofParameter<int> index{ "Style", 0, 0, sz };

			ui.Add(index, OFX_IM_HSLIDER_NO_LABELS);

			ui.AddComboButtonDualLefted(index, knobStyles);
			switch (index)
			{
			case 0: style = OFX_IM_KNOB_TICKKNOB; break;
			case 1: style = OFX_IM_KNOB_DOTKNOB; break;
			case 2: style = OFX_IM_KNOB_WIPERKNOB; break;
			case 3: style = OFX_IM_KNOB_WIPERONLYKNOB; break;
			case 4: style = OFX_IM_KNOB_WIPERDOTKNOB; break;
			case 5: style = OFX_IM_KNOB_STEPPEDKNOB; break;
			case 6: style = OFX_IM_KNOB_SPACEKNOB; break;
			}

			ui.AddSpacingBigSeparated();
	}

*/


/*
 
	EXAMPLE
	MAKE SOME WIDGET 
	SMALLER THAN MINIMUM 
	IN HEIGHT

	static ofParameter<float> progress0{ "Progress 0", 0 , 0, 1 };
	static ofParameter<float> progress1{ "Progress 1", 0 , 0, 1 };
	static ofParameter<float> progress2{ "Progress 2", 0 , 0, 1 };
	static ofParameter<float> progress3{ "Progress 3", 0 , 0, 1 };

	ui.Add(ui.bDebug, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
	if (ui.bDebug)
	{
		ui.Indent();

		// make all smaller heights
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec2 sp1 = style->ItemSpacing;
		ImVec2 sp2 = style->FramePadding;
		sp1 = ImVec2{ sp.x, 1.f };
		sp2 = ImVec2{ 0, 0 };

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, sp1);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, sp2);

		ui.Add(progress0, OFX_IM_PROGRESS_BAR_NO_TEXT);
		ui.Add(progress1, OFX_IM_PROGRESS_BAR_NO_TEXT);
		ui.Add(progress2, OFX_IM_PROGRESS_BAR_NO_TEXT);
		ui.Add(progress3, OFX_IM_PROGRESS_BAR_NO_TEXT);

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();

		ui.Unindent();
	}

*/


/*

	EXAMPLE
	AN INPUT TEXT
	BUT WITH A BIG FONT

	static ofParameter<string> i{ "input","" };
	ui.PushFont(OFX_IM_FONT_BIG);
	if (ui.Add(i, OFX_IM_TEXT_INPUT_NO_NAME))
	{
		//..
	};
	ui.PopFont();

*/


/*

	SNIPPET

	RESPONSIVE LAYOUT

	bool bDebug = true;
	ofxImGuiSurfing::SameLineFit(200);
	this->AddComboAux(index, names, w);
	if(bDebug) ofxImGuiSurfing::DebugContentRegionAvailX(); // -> stretch window

	//--

	HANDLE LABELS WIDTH

	// PushItemWidth(n);
	// with n being a negative number.
	// -n is the distance you want to be available for labels.
	float w = ImGui::GetWindowContentRegionWidth() - ImGui::CalcItemWidth();
	ImGui::PushItemWidth(-w);

*/


/*

	SNIPPET

	RIGHT 
	ALIGNED
	WIDGETS
	https://github.com/ocornut/imgui/issues/934#issuecomment-340231002

	ImGui::SetNextWindowSize(ImVec2{400,400}, ImGuiCond_FirstUseEver);
	if (ui.BeginWindow("Hello", ImGuiWindowFlags_None)) {

		const float ItemSpacing = ImGui::GetStyle().ItemSpacing.x;
		const float wpad = ImGui::GetStyle().WindowPadding.x;

		static float HostButtonWidth = 100.0f; //The 100.0f is just a guess size for the first frame.
		float offset = 0;
		//float pos = HostButtonWidth + ItemSpacing ;
		float pos = HostButtonWidth + wpad;
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		if (ImGui::SmallButton("Become host"))
		{
		}
		HostButtonWidth = ImGui::GetItemRectSize().x; //Get the actual width for next frame.

		static float ClientButtonWidth = 100.0f;
		pos += ClientButtonWidth + ItemSpacing;
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		if (ImGui::SmallButton("Connect as client"))
		{
		}
		ClientButtonWidth = ImGui::GetItemRectSize().x; //Get the actual width for next frame.

		static float LocalButtonWidth = 100.0f;
		pos += LocalButtonWidth + ItemSpacing;
		ImGui::SameLine(ImGui::GetWindowWidth() - pos);
		if (ImGui::SmallButton("Play local"))
		{
		}
		LocalButtonWidth = ImGui::GetItemRectSize().x; //Get the actual width for next frame.

		ui.EndWindow();
	}

*/


/*

	EXAMPLE
	POP UP. 
	CONTEXT MENU

	// 1
	// Options menu
	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Auto-scroll", &AutoScroll);
		ImGui::EndPopup();
	}

	// 2
	if (ImGui::Button("OPTIONS"))
		ImGui::OpenPopup("popup from button");

	if (ImGui::BeginPopup("popup from button"))
	{
		ImGui::Text("hello");
		ImGui::ShoweDemoWindow();
		ImGui::EndPopup();
	}


	// 3
	static float value = 0.5f;
	ImGui::PushItemWidth(100); ImGui::DragFloat("Context Menu", &value); ImGui::PopItemWidth();
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(1))
		ImGui::OpenPopup("context menu");
	ImGui::OpenPopup("context menu");
	ImGui::SameLine(); ImGui::Text("<-- right-click");
	if (ImGui::BeginPopup("context menu"))
		if (ImGui::BeginPopup("context menu"))
		{
			{
				ImGui::Text("hello");
				//ShowExampleMenuFile();
				if (ImGui::Selectable("Set to zero")) value = 0.0f;
				if (ImGui::Selectable("Set to PI")) value = PI;
				ImGui::EndPopup();
				ImGui::EndPopup();
			}
		}
		ImGui::TreePop();
	}

*/




//--------------------------------------------------------------
// RAM IMGUI 
 

// WIDGET DESIGN


/*

	DEBUG HELPERS
	USEFUL WHE CREATING
	YOUR OWN WIDGETS FROM SCRATCH.
	to debug the drawList

	IMGUI_SUGAR__DEBUG_POINT(bDebug);
	IMGUI_SUGAR__DEBUG_POINT2;

*/


/*

	SNIPPET
	DUAL TOOLTIP

	ImGui::Begin("Test Multi Tooltip");
	ImGui::Button("Hello");
	if (ImGui::IsItemHovered())
	{
		ImVec2 m = ImGui::GetIO().MousePos;
		ImGui::SetNextWindowPos(ImVec2(m.x - 10, m.y));
		ImGui::Begin("1", NULL, ImGuiWindowFlags_Tooltip | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
		ImGui::Text("FIRST TOOLTIP");
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(m.x + 100, m.y));
		ImGui::Begin("2", NULL, ImGuiWindowFlags_Tooltip | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
		ImGui::Text("SECOND TOOLTIP");
		ImGui::End();
	}
	ImGui::End();

*/




//--------------------------------------------------------------
// DRAFT NOTES


/*

	GRADIENT
	COLORED 
	BUTTONS

	ofxImGuiSurfing::ColoredButtonV1("Hello", ImVec2(-FLT_MIN, 0.0f), IM_COL32(255, 255, 255, 255), IM_COL32(200, 60, 60, 255), IM_COL32(180, 40, 90, 255));

	ofxImGuiSurfing::ColoredButtonV1("You", ImVec2(-FLT_MIN, 50), IM_COL32(255, 255, 255, 255), IM_COL32(50, 220, 60, 255), IM_COL32(69, 150, 255, 255));

*/


 
 
//--------------------------------------------------------------
// DOCKSPACE


/*

	DOCKING FLAGS

	// Flags for ImGui::DockSpace()
	enum ImGuiDockNodeFlags_
	{
		ImGuiDockNodeFlags_None                         = 0,
		ImGuiDockNodeFlags_KeepAliveOnly                = 1 << 0,   // Don't display the dockspace node but keep it alive. Windows docked into this dockspace node won't be undocked.
		//ImGuiDockNodeFlags_NoCentralNode              = 1 << 1,   // Disable Central Node (the node which can stay empty)
		ImGuiDockNodeFlags_NoDockingInCentralNode       = 1 << 2,   // Disable docking inside the Central Node, which will be always kept empty. Note: when turned off, existing docked nodes will be preserved.
		ImGuiDockNodeFlags_NoSplit                      = 1 << 3,   // Disable splitting the node into smaller nodes. Useful e.g. when embedding dockspaces into a main root one (the root one may have splitting disabled to reduce confusion). Note: when turned off, existing splits will be preserved.
		ImGuiDockNodeFlags_NoResize                     = 1 << 4,   // Disable resizing child nodes using the splitter/separators. Useful with programatically setup dockspaces.
		ImGuiDockNodeFlags_PassthruCentralNode          = 1 << 5,   // Enable passthru dockspace: 1) DockSpace() will render a ImGuiCol_WindowBg background covering everything excepted the Central Node when empty. Meaning the host window should probably use SetNextWindowBgAlpha(0.0f) prior to Begin() when using this. 2) When Central Node is empty: let inputs pass-through + won't display a DockingEmptyBg background. See demo for details.
		ImGuiDockNodeFlags_AutoHideTabBar               = 1 << 6    // Tab bar will automatically hide when there is a single window in the dock node.
	};

*/


/*

	DOCKING 
	NOTES

	https://github.com/ocornut/imgui/issues/3521#issuecomment-737249739
	https://github.com/ocornut/imgui/issues/3521

	For now the slightly more legal way to do same hack as above is to set the
	DockNodeFlagsOverrideSet / DockNodeFlagsOverrideClear members of ImGuiWindowClass + calling
	SetNextWindowClass() to trigger this override but it's not solving the possibility of a conflict
	between multiple windows with different requests, so it'll only fully work if there are also
	constraints applied on how windows are docked with each others.

	SetNextWindowClass()

	https://github.com/ocornut/imgui/issues/2423#issuecomment-473539196

*/


/*
 
	SNIPPET
	VARIOUS WINDOW FLAGS. 
	TYPICALLY YOU WOULD JUST USE THE DEFAULT!

	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool no_docking = false;

	//ImGuiWindowFlags window_flags = false;
	if (bAutoResize)        window_flags |= ImGuiWindowFlags_AlwaysAutoResize;//not working, not ending expands..
	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;

*/




//--------------------------------------------------------------
// RARE DEMOS


/*
	EXAMPLE
	This is a rotating text demo.

	if (ui.BeginWindow("DEMO", ImGuiWindowFlags_None))
	{
		//ofxImGuiSurfing::DebugCheckVersionAndDataLayout();

		ImVec2 diff{ 40, 40 };
		//ImVec2 diff{ ImGui::GetWindowWidth() / 2, ImGui::GetWindowHeight() / 2 };
		ofxImGuiSurfing::AddSpacingOffset(diff);

		demo.ImRotateStart();
		ui.AddLabelHugeXXL("HELLO WORLD");
		demo.ImRotateEnd(0.0005f * ::GetTickCount());

		//demo.ImRotateDemo("HelloWorld");

		ui.EndWindow();
	}
*/


//--------------------------------------------------------------
// MISCELLANEOUS


/*

	 SNIPPET
	 Allows to make exact width of n widgets 
	 to fit panel size for two buttons or columns per row:

	 float h = getWidgetsHeightRelative(); // One unit height
	 float w = getWidgetsWidth(2); // A button with the half window panel width.
	 if (ImGui::Button("A", ImVec2(w, h))) { }
	 ImGui::SameLine();
	 if (ImGui::Button("B", ImVec2(w, h))) { }

*/


/*

	ADVANCED WINDOW

	EXAMPLE
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;;
	if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	if (ui.bLockMove) window_flags |= ImGuiWindowFlags_NoMove;
	ui.BeginWindow("ofApp", NULL, window_flags);

	EXAMPLE
	ofxImGuiSurfing::AddToggleRoundedButton(ui.bAdvanced);
	ui.DrawAdvancedSubPanel();

*/


/*

	NOTES
	
	Trying rare chars text
	string s = "hello";
	ofUTF8Append(s, '▽');
	ui.AddLabel(s);

*/



//TODO: blur fx
/*

public:

	// Helper function to apply blur effect on an ImGui window
	inline void ApplyBlur(ImGuiWindow *window)
	{
		auto g = ImGui::GetCurrentContext();
		//ImGuiContext& g = ImGui::GetCurrentContext();
		//ImGuiContext& g = GImGui;

		//auto window = ImGui::GetCurrentWindow();
		ImVec2 pad_pos = window->DC.CursorPos;
		ImVec2 pad_size = window->Size;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::BeginChild("##blur", pad_size, true, 0);
		ImGui::PopStyleVar();
		ImGui::GetWindowDrawList()->AddRectFilled(pad_pos, ImVec2(pad_pos.x + pad_size.x, pad_pos.y + pad_size.y), ImColor(0, 0, 0, 128));
		ImGui::EndChild();
	}

	// Usage example
	inline void Example() {
		ImGui::Begin("Blurred window");

		ImGui::Text("This window has a blur effect applied to it.");

		auto window = ImGui::GetCurrentWindow();
		ApplyBlur(window);

		I

*/