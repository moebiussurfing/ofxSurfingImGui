#pragma once

// this header includes all the ImGui classes: layout, helpers and widgets

#include "ofMain.h"

#include "ofxImGui.h"

//-

//---------
// HEADERS
//---------

#include "ImGui/ofxSurfing_ImGui_Helpers.h"
#include "ImGui/ofxSurfing_ImGui_WidgetsButtons.h"
#include "ImGui/ofxSurfing_ImGui_WidgetsExtra.h"
#include "ImGui/ofxSurfing_ImGui_LayoutManager.h"
#include "ImGui/ofxSurfing_ImGui_Themes.h"
#include "ImGui/ofxSurfing_ImGui_RangeSlider.h"
#include "ImGui/dear_widgets/dear_widgets.h"

using namespace ofxImGuiSurfing;

//-

//----------
// SNIPPETS
//----------

// typical basic usage
// copy paste all this to your ofApp
// or you can use ofxSurfing_ImGui_Manager that bundles all this code

//-

/*

// EXAMPLE SNIPPET:

// . LAYOUT MANGER

#include "ofxSurfingImGui.h"	// -> Add all classes. You can also simplify picking what you want to use.

ofxSurfing_ImGui_Manager guiManager; // In MODE A ofxGui will be instatiated inside the class

guiManager.setup(); // ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).

void ofApp::draw() {

	guiManager.begin(); // global begin
	{
		static bool bOpen0 = true;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		guiManager.beginWindow("Show Windows", &bOpen0, window_flags);
		{
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen0);

			ImGui::Dummy(ImVec2(0, 5)); // spacing

				ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bExtra);
				if (guiManager.bExtra)
					//if (ImGui::CollapsingHeader("EXTRA", flagst))
					{
						ImGui::Indent();

						ofxImGuiSurfing::refreshImGui_WidgetsSizes(_w100, _w50, _w33, _w25, _h);

						ofxImGuiSurfing::AddBigToggle(SHOW_Plot, _w100, _h / 2, false);

						ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
						if (guiManager.bExtra) guiManager.drawAdvancedSubPanel();

						ImGui::Unindent();
					}
		}
		guiManager.endWindow();

	}
	guiManager.end(); // global end
}

*/

//-

/*

// . ofxGui Basic boilerplate

//ofApp.h

//#include "ofxSurfingImGui.h"

void setup_ImGui();
void draw_ImGui();
ofxImGui::Gui gui;
ofxImGui::Settings mainSettings = ofxImGui::Settings();
ImFont* customFont = nullptr;
ofParameter<bool> bGui{ "Show Gui", true };
ofParameter<bool> bAutoResize{ "Auto Resize", true };
ofParameter<bool> bMouseOverGui{ "Mouse Locked", false };
ofParameter<bool> auto_lockToBorder{ "Lock GUI", false };

//-

//ofApp.cpp

setup_ImGui();
draw_ImGui();

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	ImGuiConfigFlags flags = ImGuiConfigFlags_DockingEnable;
	bool bAutoDraw = true;
	bool bRestore = true;
	bool bMouse = false;
	gui.setup(nullptr, bAutoDraw, flags, bRestore, bMouse);

	auto &io = ImGui::GetIO();
	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();

	//-

	// font
	std::string fontName;
	float fontSizeParam;
	fontName = "telegrama_render.otf"; //  WARNING: will crash if font not present!
	fontSizeParam = 11;

	//-

	std::string _path = "assets/fonts/"; // assets folder
	customFont = gui.addFont(_path + fontName, fontSizeParam, nullptr, normalCharRanges);
	io.FontDefault = customFont;

	// theme
	ofxSurfingHelpers::ImGui_ThemeMoebiusSurfing();
	//ofxSurfingHelpers::ImGui_ThemeModernDark();
}

//--------------------------------------------------------------
void ofApp::draw_ImGui()
{
	guiManager.begin();
	{
		// panels minimal sizes
		float xx = 10;
		float yy = 10;
		float ww = PANEL_WIDGETS_WIDTH;
		float hh = PANEL_WIDGETS_HEIGHT;
		int pad = 10;

		// helpers to assist layout widget sizes to fit panel width or height
		// example:
		// declare size vars for typical sizes 100%, 50%, 33% ..etc
		// pass external variables as references

		// APPROACH A
		// widgets sizes
		float _w100;
		float _w50;
		float _w33;
		float _w25;
		float _h = WIDGETS_HEIGHT;
		_w100 = getWidgetsWidth(1);
		_w50 = getWidgetsWidth(2);
		_w33 = getWidgetsWidth(3);
		_w25 = getWidgetsWidth(4);

		// APPROACH B
		// widgets sizes
		float _spcx; // space between widgets
		float _spcy; // space between widgets
		float _w100; // full width
		float _h100; // full height
		float _w99; // a bit less than full width
		float _w50; // half width
		float _w33; // third width
		float _w25; // quarter width
		float _h; // standard height

		// snippet to use inside ImGui window/tree adapting for his shape
		// every indented sub tree/folder of a gui window panel can have different/less width, so we need to update sizes with the below method:
		ofxSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

		//--

		ImGuiWindowFlags flagsw = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) flagsw |= ImGuiWindowFlags_AlwaysAutoResize;
		flagsw |= ImGuiCond_FirstUseEver;

		// whindow shape
		ImGuiCond flagsCond = ImGuiCond_None;
		flagsCond |= ImGuiCond_FirstUseEver;
		ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
		ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
		// xx + = ww + pad;

		// window
		n = params.getName();
	
		guiManager.beginWindow(n.c_str(), &bOpen0, flagsw);
		{
			widgetsManager.refreshPanelShape();

			// A
			_w100 = getWidgetsWidth(1);
			_w50 = getWidgetsWidth(2);
			_w33 = getWidgetsWidth(3);
			_w25 = getWidgetsWidth(4);

			// B
			//ofxSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

			// 1. param
			//ImGui::PushItemWidth(-100);
			//ofxSurfing::AddParameter(_param);
			//ImGui::PopItemWidth();

			// 2. buttons
			//if (ImGui::Button("_Button", ImVec2(_w100, _h / 2))) {}

			// 3. param toggle
			//ofxSurfing::AddBigToggle(_param, _w100, _h);

			// 4. buttons
			//ImGui::PushButtonRepeat(true);
			//float __w = ofxSurfing::getWidgetsWidth(w, 2); // get width for two widgets per row
			//if (ImGui::Button("<", ImVec2(__w, _h))) {} ImGui::SameLine();
			//if (ImGui::Button(">", ImVec2(__w, _h))) {}
			//ImGui::PopButtonRepeat();

			// 5. spacing
			//ImGui::Dummy(ImVec2(0.0f, 2.0f));

			// group
			ImGuiTreeNodeFlags flagst;
			flagst = ImGuiTreeNodeFlags_None;
			flagst |= ImGuiTreeNodeFlags_DefaultOpen;
			flagst |= ImGuiTreeNodeFlags_Framed;
			ofxSurfing::AddGroup(params, flagst);

		}
		guiManager.endWindow();
	}
	guiManager.end();

*/

//-----

// . raw ImGui
// WINDOW, PANELS, AND SUB PANELS AND DIFFERENT TREES MODES

/*

// 1. windows

// 1.1 window using ofxImGui

ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
string name = "myWindow";
if (ofxImGui::BeginWindow(name.c_str(), mainSettings, _flagw))
{..}
ofxImGui::EndWindow(mainSettings);


// 1.2 window using RAW ImGui
ImGui::Begin("name");
{..}
ImGui::End();

//-

// 2. trees

// 2.1 tree
if (ImGui::TreeNode("_Tree"))
{..
	ImGui::TreePop();
}

//-

// 2.2 collapsing panel

bool bOpen = false;
ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
if (ImGui::CollapsingHeader("_Collapsing", _flagw))
{..}

// 2.3 treeEx

bool bOpen = true;
ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
_flagt |= ImGuiTreeNodeFlags_Framed;
if (ImGui::TreeNodeEx("_TreeEx", _flagt)) 
{..
	ImGui::TreePop();
}

*/

//-

/*

// . WINDOW PANEL SHAPE 
// Get window position/shape of a window panel. for advanced layout paired position

//.h

//standalone window not handled by .ini layout
//but for the app settings
float widthGuiLayout;
float heightGuiLayout;
ofParameter<glm::vec2> positionGuiLayout{ "Gui Layout Position",
glm::vec2(ofGetWidth() / 2,ofGetHeight() / 2),//center
	glm::vec2(0,0),
	glm::vec2(ofGetWidth(), ofGetHeight())
};

//-

//.cpp

//get window position for advanced layout paired position
auto posx = ImGui::GetWindowPos().x;
auto posy = ImGui::GetWindowPos().y;
widthGuiLayout = ImGui::GetWindowWidth();
heightGuiLayout = ImGui::GetWindowHeight();
positionGuiLayout = glm::vec2(posx, posy);

//-

*/