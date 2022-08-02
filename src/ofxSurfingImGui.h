
/*

	TODO:
	
	GENERAL
	+ fix draw in front the ImGui. not working drawing OF_EVENT_ORDER_AFTER_APP.
	+ fix workflow handling layout presets breaks when Link is enabled.
	+ fix reset aligners that populates out of the view port.
		must apply only over special windows maybe ?

	DOCKING
		+ allow panel and presets dockable too!
		+ fix make dockeable all windows on same space.
		+ fix multiple dock spaces that are colliding/one over another.
		+ fix view-port rectangle preview.
		+ add video view-port example.
		+ docking overlaps sometimes on layout management

	HELPERS
	+ fix fails ofParams for string on groups
		+ add text input widget.
	+ add the cool knobs.
	+ fix toggles do not trigs/return true when changes?
	+ add clickable label toggle widget.
	+ add tool-tip types on styles on a new guiManager.Add(..arg
	https://github.com/d3cod3/ofxMosaicPlugin/blob/master/src/core/imgui_helpers.h
	+ next / nested groups headers are weird hidden!
	+ nested groups are (inheriting) expanded when parent is expanded.

	SMALL THINGS
	+ remake mode free and lockers simpler. a flag for each window ?
	+ aspect ratio/fit modes for game view port.
	+ fix log ofxImGuiSurfing::WindowPanels::isUsing: 

	NEW FEATURES
	+ auto midi knobs to FX:
		set the master 6 knobs.
		auto assign to these 6 knobs 
		from current GUI editing / first plane page.

*/

/*

	BUGS:

*/

/*

	NOTES:

	Docking Help
	https://github.com/ocornut/imgui/issues/2109

	Docking Demo
	https://github.com/ocornut/imgui/blob/1ad1429c6df657f9694b619d53fa0e65e482f32b/imgui_demo.cpp#L7399-L7408

	Tool-bar Example
	https://gist.github.com/moebiussurfing/b7652ba1ecbd583b7c4f18e25a598551

*/

//--------------------------------------------------------------


/*
 
// HOW TO:
// RECOMMENDED OR COMMON USAGE
// TOP SNIPPETS HERE !

// #1 
{
	// ofApp.h
	{
		#include "ofxSurfingImGui.h"

		ofxSurfing_ImGui_Manager guiManager;
		ofParameter<bool> bGui{ "ShowWindow", true };
	}

	// ofApp.cpp
	{
		// ofApp::setup()

		guiManager.setup(); 

		//-------------------------------

		// ofApp::draw()

		IMGUI_SUGAR__WINDOWS_CONSTRAINTS;

		guiManager.begin();
		{
			if(!bGui) return;
			if (guiManager.beginWindow(bGui))
			{
				guiManager.Add(guiManager.bMinimize, OFX_IM_TOGGLE_ROUNDED);
				if (!guiManager.bMinimize){}

				//..

				guiManager.endWindow();
			}
		}
		guiManager.end();
	}
}
*/


//--------------------------------------------------------------


#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"
#define IMGUI_DEFINE_MATH_OPERATORS

//--

//TODO:
//namespace ofxSurfingImGui = ofxImGuiSurfing;

//--------------------------------------------------------------

// This header includes the main classes: 
// Layout, helpers and all my Surfing widgets.
// Some others are moved out of the /src folder bc they are less common.
// You must include them manually from OFX_ADDON/_LIBS if you want to use it in your project.

//---------
// HEADERS
//---------

#include "ImGui/ofxSurfing_ImGui_ofHelpers.h"
#include "ImGui/ofxSurfing_ImGui_LayoutManager.h"
#include "ImGui/widgets/ofxSurfing_ImGui_Widgets.h"
#include "ImGui/themes/ofxSurfing_ImGui_ThemesEditor.h"

using namespace ofxImGuiSurfing;

//--------------------------------------------------------------

/*
		-----------------------
		 MORE EXAMPLE SNIPPETS
		-----------------------

		LOOK RECOMMENDED USAGE ABOVE!
		THESE ARE NOT RECOMMENDED / LEGACY AND DEPRECATED MODES!

		LEARN HOW TO CREATE
		WINDOWS, PANELS, 
		AND SUB PANELS 
		AND DIFFERENT TREES MODES
		...etc

*/


//--


/*
	//--------------------------------------------------------------

	// 1. HOW TO CREATE A WINDOW ?

	THESE ARE DEPRECATED/LEGACY MODES THAT DO NOT USES THE ADDON POWERED API !

	//--

	// WINDOWS USING RAW ImGui (LEGACY)
	// KIND OF DEPRECATED. 
	// Better to use the add-on engine,
	// but it will work using RAW ImGui too!

	// 1.0 SIMPLE

	ImGui::Begin("myWindow");
		{ }
	ImGui::End();

	//--

	// 1.1 WINDOW WITH NAME WITH FLAGS (LEGACY)

	string _name = "myWindow";
	ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
	ImGui::Begin(_name.c_str(), NULL, _flagw);
		{ }
	ImGui::End();

	//--

	// 1.2 WINDOW USING MORE RAW (LEGACY)

	ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
	string _name = "myWindow";
	ofxImGui::Settings mainSettings = ofxImGui::Settings();
	if (ofxImGui::BeginWindow(_name.c_str(), mainSettings, _flagw))
		{ }
	ofxImGui::EndWindow(mainSettings);


	//--------------------------------------------------------------


	// 2. TREES

	// 2.1 Simple TREE (no framed)

	if (ImGui::TreeNode("_Tree"))
	{
		//guiManager.refreshLayout();
		//.. -> widgets
		ImGui::TreePop();
	}

	//--

	// 2.2 COLLAPSING PANEL (framed and closed by default)

	{
		static bool bOpen = true;
		ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
		if (ImGui::CollapsingHeader("_Collapsing", _flagw))
		{
			//guiManager.refreshLayout();
			//.. -> widgets
		}
	}

	//--

	// 2.3 TREE EX - TREE WITH FLAGS

	{
		static bool bOpen = true;
		ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
		_flagt |= ImGuiTreeNodeFlags_Framed;
		if (ImGui::TreeNodeEx("_TreeEx", _flagt))
		{
			//guiManager.refreshLayout();
			//.. -> widgets
			ImGui::TreePop();
		}
	}

	//--

*/

//--------------------------------------------------------------

// MORE RAW IMGUI

/*

// HOW TO SET COLORS?

static float b = 1.0f;
static float c = 0.5f;
static int i = 3; // hue colors are from 0 to 7
ImVec4 _color1 = (ImVec4)ImColor::HSV(i / 7.0f, b, b);
ImVec4 _color2 = (ImVec4)ImColor::HSV(i / 7.0f, c, c);

*/


//--


/*

// WINDOW TESTER


// FORCE WINDOW POSITION & SHAPE
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

// WINDOW CONSTRAINTS FOR SHAPE SIZE
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


//--


/*

// AN EXTRA BEGIN/END PAIR.
// WITH A SNAPPING GRID.

//--------------------------------------------------------------
void Begin(const std::string& name) {
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


//--


// ANOTHER EXTRA BEGIN/END PAIR

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


//--


/*

// ANOTHER WINDOW WITH SNAPPING

bool BeginWindow(std::string name = "Window", bool* p_open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
void EndWindow();

void Begin(const std::string& name);
void End();

*/


//--


/*

// IMGUI INFOS

auto io = ImGui::GetIO();
const auto label = ct::toStr("Dear ImGui %s (Docking)", ImGui::GetVersion());
const auto size = ImGui::CalcTextSize(label.c_str());
ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - size.x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));
ImGui::Text("%s", label.c_str());

*/


//--


/*

// TABS

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
		guiManager.drawAdvancedBundle();

		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();
}

*/


//--


/*

// EXAMPLE 2:
// PREV / NEXT DUAL BUTTONS

{
	static ofParameter<bool> bPrev{ "<", false };
	static ofParameter<bool> bNext{ ">", false };

	guiManager.Add(bPrev, OFX_IM_BUTTON, 2, true);
	guiManager.Add(bNext, OFX_IM_BUTTON, 2);

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

// EXAMPLE 3:
// ADD MOUSE WHEEL TO THE FLOAT PARAM

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


//--


// DOCKSPACE

/*

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


//--


//// DEMONSTRATE THE VARIOUS WINDOW FLAGS. TYPICALLY YOU WOULD JUST USE THE DEFAULT!

//static bool no_titlebar = false;
//static bool no_scrollbar = false;
//static bool no_menu = false;
//static bool no_move = false;
//static bool no_resize = false;
//static bool no_collapse = false;
//static bool no_nav = false;
//static bool no_background = false;
//static bool no_bring_to_front = false;
//static bool no_docking = false;

////ImGuiWindowFlags window_flags = false;
//if (bAutoResize)        window_flags |= ImGuiWindowFlags_AlwaysAutoResize;//not working, not ending expands..
//if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
//if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
//if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
//if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
//if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
//if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
//if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
//if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
//if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
//if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;

//--

/*

// GET WINDOW SHAPE. CALL BETWEEN BEGIN/END

ofRectangle rect = ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

*/


//--


/*

DOCKING NOTES

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


//--


// HOW TO CUSTOMIZE FONT
// AND USE DIFFERENT FONT STYLES?

/*

{
	std::string _fontName;
	std::string _path;
	float _fontSize;

	_fontSize = 11;
	_fontName = "overpass-mono-bold.otf";
	_path = "assets/fonts/" + _fontName;
	guiManager.pushFont(_path, _fontSize);//index 0

	_fontSize = 14;
	_fontName = "RecMonoLinear-Bold-1.082.ttf";
	_path = "assets/fonts/" + _fontName;
	guiManager.pushFont(_path, _fontSize);//index 1

	_fontSize = 17;
	_fontName = "RecMonoLinear-Regular-1.082.ttf";
	_path = "assets/fonts/" + _fontName;
	guiManager.pushFont(_path, _fontSize);//index 2

	guiManager.addFont(_path, _fontSize);
	guiManager.setDefaultFontIndex(2);

	// Customize Font
	static bool bCustomFont = true;
	if (bCustomFont) guiManager.pushStyleFont(1);
	{
		//.. Will draw widgets using this font
	}
	if (bCustomFont) guiManager.popStyleFont();
}

*/