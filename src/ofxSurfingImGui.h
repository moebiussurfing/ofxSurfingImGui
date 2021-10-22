
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"

//--------------------------------------------------------------

// This header includes the main classes: 
// layout, helpers and all my Surfing widgets.
// Some others are moved out of the /src folder bc they are less common.
// You must include them manually from OFX_ADDON/_LIBS if you want to use it in your project.

//---------
// HEADERS
//---------

#include "ImGui/ofxSurfing_ImGui_ofHelpers.h"

#include "ImGui/ofxSurfing_ImGui_LayoutManager.h"

#include "ImGui/widgets/ofxSurfing_ImGui_Widgets.h"
//#include "ImGui/widgets/ofxSurfing_ImGui_WidgetsButtons.h"
//#include "ImGui/widgets/ofxSurfing_ImGui_WidgetsExtra.h"
//#include "ImGui/widgets/ofxSurfing_ImGui_WidgetsKnob.h"
//#include "ImGui/widgets/ofxSurfing_ImGui_WidgetsRangeSlider.h"
//#include "ImGui/widgets/ofxSurfing_ImGui_WidgetsBezier.h"
//#include "ImGui/widgets/dear_widgets/dear_widgets.h"

#include "ImGui/themes/ofxSurfing_ImGui_ThemesEditor.h"
//#include "ImGui/themes/ofxSurfing_ImGui_Themes.h"
//#include "ImGui/themes/ThemeSequentity.inl"

// Must include from OFX_ADDON/_LIBS if you want to use it in your project.
//#include "ofxSurfing_ImGui_WidgetsFileBrowser.h"


using namespace ofxImGuiSurfing;

//--------------------------------------------------------------

/*
	EXAMPLE SNIPPETS
	----------------

	Typical basic usage

	Copy paste all this to your ofApp
	or you can use ofxSurfing_ImGui_Manager that bundles all this code

	Content:
	1. LAYOUT MANGER: SIMPLIFY THE WINDOW/PANELS/LAYOUT PROCESS.
	2. ofxImGui BASIC BOILERPLATE.
	3. RAW IMGUI: WINDOW, PANELS, AND SUB PANELS AND DIFFERENT TREES MODES.
	4. WINDOW PANEL SHAPE: GET WINDOW POSITION FOR ADVANCED LAYOUT LINKED TO OTHER WINDOWS/GUI'S.
	5. MORE RAW IMGUI SNIPPETS
*/


//--------------------------------------------------------------


// LEARN HOW TO CREATE
// WINDOWS, PANELS, AND SUB PANELS AND DIFFERENT TREES MODES

/*
	//--------------------------------------------------------------


	// 1. CREATE A WINDOW

	// WINDOWS USING RAW ImGui

	// 1.0 SIMPLE

	ImGui::Begin("myWindow);
	{ }
	ImGui::End();

	//--

	// 1.1 WINDOW WITH NAME WITH FLAGS

	string _name = "myWindow";
	ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
	ImGui::Begin(_name.c_str(), NULL, _flagw);
	{ }
	ImGui::End();

	//--

	// 1.2 WINDOW USING "old" ofxImGui

	// (DEPRECATED. Better to not use like this)

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
		//bool bOpen = false;
		ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
		if (ImGui::CollapsingHeader("_Collapsing", _flagw))
		{
			//guiManager.refreshLayout();
			//.. -> widgets
		}
	}

	//--

	// 2.3 treeEx - TREE WITH FLAGS

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


/*

// 1. LAYOUT MANGER

// .h
#include "ofxSurfingImGui.h"	// -> Add all classes. You can also simplify picking what you want to use.
ofxSurfing_ImGui_Manager guiManager;

// .cpp
// setup()
guiManager.setup(); // ofxImGui is instantiated inside the class, then we can forgot declare ofxImGui here (ofApp scope).

*/


//--------------------------------------------------------------


//-

//--------------------------------------------------------------

// MORE RAW IMGUI

/*

// 5.1 How to set colors
static float b = 1.0f;
static float c = 0.5f;
static int i = 3;// hue colors are from 0 to 7
ImVec4 _color1 = (ImVec4)ImColor::HSV(i / 7.0f, b, b);
ImVec4 _color2 = (ImVec4)ImColor::HSV(i / 7.0f, c, c);

*/

//-

/*

// WINDOW TESTER
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
// An extra begin/end pair
// with snapping
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

// Another extra begin/end pair
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
// An extra begin/end pair
// with snapping
bool BeginWindow(std::string name = "Window", bool* p_open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
void EndWindow();

void Begin(const std::string& name);
void End();
*/

//--

/*		
// ImGui Infos
auto io = ImGui::GetIO();
const auto label = ct::toStr("Dear ImGui %s (Docking)", ImGui::GetVersion());
const auto size = ImGui::CalcTextSize(label.c_str());
ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - size.x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));
ImGui::Text("%s", label.c_str());
*/

//--

/*
// Tabs
if (ImGui::BeginTabBar("Tabs Blah"))
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
*/

//--

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

/*

// get window shape. call between begin/end
ofRectangle rect = ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

*/


//--

/*

Docking notes

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





//-

//TODO:

//// Customize font

//std::string _fontName;
//std::string _path;
//float _fontSize;

//_fontSize = 16;
//_fontName = "overpass-mono-bold.otf";
//_path = "assets/fonts/" + _fontName;
//guiManager.pushFont(_path, _fontSize);

////_fontSize = 14;
////_fontName = "RecMonoLinear-Bold-1.082.ttf";
////_path = "assets/fonts/" + _fontName;
////guiManager.pushFont(_path, _fontSize);

////_fontSize = 17;
////_fontName = "RecMonoLinear-Regular-1.082.ttf";
////_path = "assets/fonts/" + _fontName;
////guiManager.pushFont(_path, _fontSize);

////guiManager.addFont(_path, _fontSize);
////guiManager.setDefaultFontIndex(2);

//TODO:
//// Customize Font
//static bool bCustomFont = false;
//bCustomFont = bEnable1;
//if (bCustomFont) guiManager.pushStyleFont(1);

//..

//if (bCustomFont) guiManager.popStyleFont();