
#pragma once

//TODO:
// Can't add libs bc area also defined/included too on classes that includes this class.
//#include "ofxSurfingImGui.h"
//#include "ofxSurfing_ImGui_ofHelpers.h"

namespace ofxImGuiSurfing
{
	/*

	Arguments to the Styles Engine:
	You can pass it as argument when adding each ofParameter to the guiManager.

	Examples:

	guiManager.Add(bEnable, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);
	guiManager.Add(floatValue, OFX_IM_VSLIDER);
	guiManager.AddGroup(params, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_TREE);

	// Two toggles in one row
	guiManager.Add(bEnable1, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM, 2, true); // two in same line
	guiManager.Add(bEnable2, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM, 2, false); // two

	guiManager.Add(bEnable3, OFX_IM_TOGGLE, 1, false, 30); // one full width toggle but 20px spacing at end


	*/


	//--------------------------------------------------------------
	enum SurfingImGuiTypes
	{
		OFX_IM_DEFAULT = 0,	// Default style for each widget. (kind of like ofxImGui does)
		OFX_IM_HIDDEN,		// Omit widget. don't let spacing there
		OFX_IM_DISABLED,	// Make it invisble, preserve the void spacing
		OFX_IM_INACTIVE,	// Draws the widget. but makes it inactive. disables mouse control
		//TODO: could be an extra arg to allow different appearance for inactive types..

		//-

		// Bool Styles

		// Button
		OFX_IM_BUTTON_SMALL,
		OFX_IM_BUTTON_BIG,
		OFX_IM_BUTTON_BIG_XXL,
		OFX_IM_BUTTON_BIG_XXXL,

		// Toggle
		OFX_IM_CHECKBOX,
		OFX_IM_TOGGLE_SMALL,
		OFX_IM_TOGGLE_BIG,
		OFX_IM_TOGGLE_BIG_XXL,
		OFX_IM_TOGGLE_BIG_XXXL,

		// Border
		OFX_IM_TOGGLE_SMALL_BORDER,
		OFX_IM_TOGGLE_BIG_BORDER,
		OFX_IM_TOGGLE_BIG_XXL_BORDER,
		OFX_IM_TOGGLE_BIG_XXXL_BORDER,

		// Blink border
		OFX_IM_TOGGLE_SMALL_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK,

		// Rounded
		OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG,

		//-

		// Float/Int Styles

		OFX_IM_SLIDER, // ofxImGui standard

		// Big Sliders

		// Horizontal
		OFX_IM_HSLIDER_BIG,
		OFX_IM_HSLIDER_BIG_NO_NAME,
		OFX_IM_HSLIDER_BIG_NO_NUMBER,
		OFX_IM_HSLIDER_BIG_NO_LABELS,
		OFX_IM_HSLIDER_SMALL,
		OFX_IM_HSLIDER_SMALL_NO_NAME,
		OFX_IM_HSLIDER_SMALL_NO_NUMBER,
		OFX_IM_HSLIDER_SMALL_NO_LABELS,
		OFX_IM_HSLIDER,
		OFX_IM_HSLIDER_NO_NAME,
		OFX_IM_HSLIDER_NO_NUMBER,
		OFX_IM_HSLIDER_NO_LABELS,
		OFX_IM_HSLIDER_MINI, //TODO:
		OFX_IM_HSLIDER_MINI_NO_NAME, //TODO:
		OFX_IM_HSLIDER_MINI_NO_LABELS, //TODO:
		OFX_IM_HSLIDER_MINI_NO_NUMBER, //TODO:

		// Vertical
		OFX_IM_VSLIDER,
		OFX_IM_VSLIDER_NO_NAME,
		OFX_IM_VSLIDER_NO_NUMBER,
		OFX_IM_VSLIDER_NO_LABELS,

		OFX_IM_PROGRESS_BAR,
		OFX_IM_PROGRESS_BAR_NO_TEXT,
		OFX_IM_STEPPER,
		OFX_IM_DRAG,
		OFX_IM_KNOB,
		OFX_IM_KNOB_TRAIL,
		OFX_IM_KNOB_SMALL,//TODO:
		OFX_IM_COMBO,//TODO: multiple controls for fine tweak: slider + drag + stepper

		//-

		// Strings
		OFX_IM_TEXT_DISPLAY,
		OFX_IM_TEXT_INPUT,
		OFX_IM_TEXT_BIG,

		//-

		// Colors
		OFX_IM_COLOR_INPUT,
		OFX_IM_COLOR_NO_ALPHA, // without the alpha control
		OFX_IM_COLOR_NO_NAME, //TODO: without name or controls
		OFX_IM_COLOR_BOX, // small box color without controls
		OFX_IM_COLOR_BOX_FULL_WIDTH,
		OFX_IM_COLOR_BOX_FULL_WIDTH_BIG, // double height

		//-

		//TODO: 
		// for glm::vec
		// Multidim
		OFX_IM_MULTIDIM_SPLIT_SLIDERS,
		//OFX_IM_MULTIDIM_SPLIT_STEPPERS,//TODO:
		//OFX_IM_MULTIDIM_SPLIT_DRAGS,

		OFX_IM_NUM_TYPES
	};

	//--

	//--------------------------------------------------------------
	enum SurfingImGuiTypesGroups
	{
		OFX_IM_GROUP_DEFAULT = 0,
		OFX_IM_GROUP_COLLAPSED,
		OFX_IM_GROUP_TREE_EX,
		OFX_IM_GROUP_TREE,
		OFX_IM_GROUP_SCROLLABLE,
		OFX_IM_GROUP_HIDDEN_HEADER, // hide hidder. TODO; fails on first group. not working
		OFX_IM_GROUP_HIDDEN, // hide header and all the content

		OFX_IM_GROUP_NUM_TYPES
	};

	//-

	// Helper to get the styles name for debugging purposes
	//--------------------------------------------------------------
	inline static std::string getSurfingImGuiTypesGroupsName(int i)
	{
		std::string _groupInfo;
		if (i == 0) _groupInfo = "OFX_IM_GROUP_DEFAULT";
		else if (i == 1) _groupInfo = "OFX_IM_GROUP_COLLAPSED";
		else if (i == 2) _groupInfo = "OFX_IM_GROUP_TREE_EX";
		else if (i == 3) _groupInfo = "OFX_IM_GROUP_TREE";
		else if (i == 4) _groupInfo = "OFX_IM_GROUP_SCROLLABLE";
		else if (i == 5) _groupInfo = "OFX_IM_GROUP_HIDDEN_HEADER";
		else if (i == 6) _groupInfo = "OFX_IM_GROUP_HIDDEN";
		else _groupInfo = "OFX_IM_GROUP UNKNOWN";

		return _groupInfo;
	}


	//---------------

	// SUGAR SNIPPETS

	//----

	// 1.

	// BUG:
	// Annoying behaviour: sometimes the sliders are bigger bc the text long or something,
	// Then all the window panels is being resized bigger if auto resize is enabled!

	// workaround

	//TODO: 
	// A nice idea could be to get the longer param label name width 
	// and use this max width to apply to our layouting engine...

	// Some macro sugar to help fix how sliders force autoresize the panel widths.
	// It's a 'rare behaviour' that I am trying to correct doing this.

	//-

	//TODO:

#define DEFAULT_LAYOUT_SLIDERS_BEHAVIOUR // -> Comment this line to use a workaround to weird ImGui auto resize layouting on sliders widgets...

#define TEXT_LABEL_TO_RESIZE "----------" // -> This is a 10 chars string that we will use as default label width, to name wdigets.

	//-

#ifndef DEFAULT_LAYOUT_SLIDERS_BEHAVIOUR

	// A. Relative to panel width
//TODO:
//#define IMGUI_SUGAR__SLIDER_WIDTH_PUSH \
//const ImVec2 sztx = ImGui::CalcTextSize(TEXT_LABEL_TO_RESIZE); \
//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - sztx.x);

//#define IMGUI_SUGAR__SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x>200?ImGui::GetContentRegionAvail().x-110:ImGui::GetContentRegionAvail().x-90);//sometimes looks weird..
#define IMGUI_SUGAR__SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x-65);
//#define IMGUI_SUGAR__SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x-90);
//#define IMGUI_SUGAR__SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x / 2);
#define IMGUI_SUGAR__SLIDER_WIDTH_POP ImGui::PopItemWidth();

#endif

	//-

	//// B. Using absolute size

	//#define IMGUI_LABELS_WIDTH_DEFAULT 95
	//#define IMGUI_SUGAR__SLIDER_WIDTH_PUSH ImGui::PushItemWidth(-IMGUI_LABELS_WIDTH_DEFAULT);
	//#define IMGUI_SUGAR__SLIDER_WIDTH_POP ImGui::PopItemWidth();

	//-

#ifdef DEFAULT_LAYOUT_SLIDERS_BEHAVIOUR

	// C. To bypass and do nothing.

#define IMGUI_SUGAR__SLIDER_WIDTH_PUSH ;
#define IMGUI_SUGAR__SLIDER_WIDTH_POP ;

#endif

	//--

	// 2.

	// For OFX_IM_STEPPER

//#define IMGUI_SUGAR__STEPPER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x>200 ? ImGui::GetContentRegionAvail().x * 0.6 : ImGui::GetContentRegionAvail().x * 0.6);//sometimes looks weird..
//#define IMGUI_SUGAR__STEPPER_WIDTH_POP ImGui::PopItemWidth();

//fix autoresize grow... 
#define IMGUI_SUGAR__STEPPER_WIDTH_PUSH \
	const auto sztx = ImGui::CalcTextSize(TEXT_LABEL_TO_RESIZE); \
	const float gap = 40; \
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - sztx.x - gap);
#define IMGUI_SUGAR__STEPPER_WIDTH_POP ImGui::PopItemWidth();

	//----

	// 3.

	// Adds mouse wheel control to the last/previoues ofParam widget (float/int) rendered.

#define IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(arg1,arg2) ofxImGuiSurfing::AddMouseWheel(arg1, arg2);
#define IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(arg1) ofxImGuiSurfing::AddMouseWheel(arg1);

	//----

	// 3.

	// Adds Constraint Window Shapes

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN / 2, 2 * PANEL_WIDGETS_HEIGHT_MIN); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN + 40, ofGetHeight() - 100); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_SMALL \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN / 2, PANEL_WIDGETS_HEIGHT_MIN); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN, ofGetHeight() / 2); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \

	//----

	// 4.

	// Draws a point on the ImGui cursor positon for debugging when designing widgets
	//#define IMGUI_SUGAR__TEST_POINT \ 
	//	{ \
	//		ImDrawList* draw_list = ImGui::GetWindowDrawList(); \
	//		const ImVec2 pdebug = ImGui::GetCursorScreenPos(); \
	//		draw_list->AddCircleFilled(ImVec2(pdebug.x, pdebug.y), 2, IM_COL32(255, 0, 255, 255)); \
	//	} \

	//#define IMGUI_SUGAR__TEST_POINT \ 
	//	ImDrawList* draw_list = ImGui::GetWindowDrawList(); \
	//		const ImVec2 pdebug = ImGui::GetCursorScreenPos(); \
	//		draw_list->AddCircleFilled(ImVec2(pdebug.x, pdebug.y), 2, IM_COL32(255, 0, 255, 255)); \

	//----

	//// NOTES
	//
	////ImGui::SetCursorPosX(ImGui::GetCursorPosX() + sztx.x);
	////ImGui::SetCursorPosY(ImGui::GetCursorPosY() + sztx.y);
	//
	////IMGUI_SUGAR__TEST_POINT;
	//
	//const ImVec2 pdebug = ImGui::GetCursorScreenPos();
	//draw_list->AddCircleFilled(ImVec2(pdebug.x, pdebug.y), 2, IM_COL32(255, 0, 255, 255));//can't use macros..

}