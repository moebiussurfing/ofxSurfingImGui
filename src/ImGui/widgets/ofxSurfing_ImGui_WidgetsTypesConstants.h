
#pragma once

//TODO:
// Can't add libs bc area also defined/included too on classes that includes this class.
//#include "ofxSurfingImGui.h"
//#include "ofxSurfing_ImGui_ofHelpers.h"

#define OFX_IM_WIDGETS_RATIO_BIG 1.5f
#define OFX_IM_WIDGETS_RATIO_MINI 0.16f
#define OFX_IM_WIDGETS_RATIO_SMALL 0.4f

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
	guiManager.Add(bGui_1, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM, 2, true); // two in same line
	guiManager.Add(bGui_2, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM, 2, false); // two

	guiManager.Add(bGui_3, OFX_IM_TOGGLE, 1, false, 30); // one full width toggle but 20px spacing at end


	*/

	//These sizes are usually related to height! Because widgets widths are handled by the API args!
	//--------------------------------------------------------------
	enum SurfingImGuiTypes
	{
		OFX_IM_DEFAULT = 0,	// Default style for each widget. (kind of like ofxImGui does)
		OFX_IM_HIDDEN,		// Omit widget. don't let spacing there.
		OFX_IM_DISABLED,	// Make it invisible, preserve the void spacing. it's a common height but could differs..
		OFX_IM_SPACING,		// Make it invisible, preserve a custom (one standard line) spacing.
		OFX_IM_INACTIVE,	// Draws the widget. but makes it inactive. disables mouse control.
		//TODO: could be an extra arg to allow different appearance for inactive types..

		//-

		// Bool Styles

		// Button
		OFX_IM_BUTTON_SMALL,	// 1 = default
		OFX_IM_BUTTON,			// 1.25
		OFX_IM_BUTTON_MEDIUM,	// 1.5
		OFX_IM_BUTTON_BIG,		// 2
		OFX_IM_BUTTON_BIG_XXL,	// 3
		OFX_IM_BUTTON_BIG_XXXL,	// 4

		// Border
		OFX_IM_BUTTON_SMALL_BORDER,
		OFX_IM_BUTTON_BORDER,
		OFX_IM_BUTTON_MEDIUM_BORDER,
		OFX_IM_BUTTON_BIG_BORDER,
		OFX_IM_BUTTON_BIG_XXL_BORDER,
		OFX_IM_BUTTON_BIG_XXXL_BORDER,

		// Border Blink 
		OFX_IM_BUTTON_SMALL_BORDER_BLINK,
		OFX_IM_BUTTON_BORDER_BLINK,
		OFX_IM_BUTTON_MEDIUM_BORDER_BLINK,
		OFX_IM_BUTTON_BIG_BORDER_BLINK,
		OFX_IM_BUTTON_BIG_XXL_BORDER_BLINK,
		OFX_IM_BUTTON_BIG_XXXL_BORDER_BLINK,

		//--
		
		// Toggle
		OFX_IM_CHECKBOX, // ofxImGui standard
		OFX_IM_TOGGLE,
		OFX_IM_TOGGLE_SMALL,
		OFX_IM_TOGGLE_MEDIUM,
		OFX_IM_TOGGLE_BIG,
		OFX_IM_TOGGLE_BIG_XXL,
		OFX_IM_TOGGLE_BIG_XXXL,

		// Border
		OFX_IM_TOGGLE_SMALL_BORDER,
		OFX_IM_TOGGLE_BORDER,
		OFX_IM_TOGGLE_MEDIUM_BORDER,
		OFX_IM_TOGGLE_BIG_BORDER,
		OFX_IM_TOGGLE_BIG_XXL_BORDER,
		OFX_IM_TOGGLE_BIG_XXXL_BORDER,

		// Border Blink 
		OFX_IM_TOGGLE_SMALL_BORDER_BLINK,
		OFX_IM_TOGGLE_BORDER_BLINK,
		OFX_IM_TOGGLE_MEDIUM_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK,

		//--
		
		// Rounded
		OFX_IM_TOGGLE_ROUNDED,
		OFX_IM_TOGGLE_ROUNDED_MINI,
		OFX_IM_TOGGLE_ROUNDED_SMALL,
		OFX_IM_TOGGLE_ROUNDED_MEDIUM,
		OFX_IM_TOGGLE_ROUNDED_BIG,
		//legacy
		OFX_IM_TOGGLE_BUTTON_ROUNDED, // legacy. same size than small.
		OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG,

		//--

		// FLOAT / INT Styles

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
		OFX_IM_HSLIDER_MINI,
		OFX_IM_HSLIDER_MINI_NO_NAME,
		OFX_IM_HSLIDER_MINI_NO_LABELS,
		OFX_IM_HSLIDER_MINI_NO_NUMBER,

		// Vertical
		OFX_IM_VSLIDER,
		OFX_IM_VSLIDER_NO_NAME,
		OFX_IM_VSLIDER_NO_NUMBER,
		OFX_IM_VSLIDER_NO_LABELS,

		OFX_IM_PROGRESS_BAR,
		OFX_IM_PROGRESS_BAR_NO_TEXT,
		OFX_IM_STEPPER,
		OFX_IM_DRAG,

		OFX_IM_KNOB,//notice that full width by default. too big!
		OFX_IM_KNOB_TRAIL,//decorated
		//OFX_IM_KNOB_SMALL,//TODO:

		OFX_IM_COMBO_MULTI,//TODO: multiple controls for fine tweak: slider + drag + stepper

		//-

		// Strings
		OFX_IM_TEXT_DISPLAY,
		OFX_IM_TEXT_INPUT,
		OFX_IM_TEXT_BIG,
		//OFX_IM_LABEL,//big font not accessible here..
		//OFX_IM_LABEL_BIG,

		//-

		// Colors
		OFX_IM_COLOR_INPUT, // standard
		OFX_IM_COLOR_NO_ALPHA, // without the alpha control
		OFX_IM_COLOR_NO_INPUTS, // without inputs
		OFX_IM_COLOR_NO_NAME, //TODO: without name or controls
		OFX_IM_COLOR_BOX, // small box color without controls
		OFX_IM_COLOR_BOX_FULL_WIDTH,
		OFX_IM_COLOR_BOX_FULL_WIDTH_BIG, // double height
		OFX_IM_COLOR_BOX_FULL_WIDTH_CONTROLS,//TODO:

		//-

		//TODO: 
		// for glm::vec
		// Multidim
		OFX_IM_MULTIDIM_SPLIT_SLIDERS,
		OFX_IM_MULTIDIM_SPLIT_SLIDERS_FOLDERED,
		//OFX_IM_MULTIDIM_SPLIT_STEPPERS,//TODO:
		//OFX_IM_MULTIDIM_SPLIT_DRAGS,

		OFX_IM_NUM_TYPES
	};

	//--

	//TODO: to simplify the api
	// We can use one only flag argument and multiple possibilities at the same time are allowed.
	typedef int SurfingImGuiGroupStyle;
	enum SurfingImGuiGroupStyle_
	{
		SurfingImGuiGroupStyle_None = 1 << 0,
		SurfingImGuiGroupStyle_Collapsed = 1 << 1,
		SurfingImGuiGroupStyle_NoHeader = 1 << 2,
		SurfingImGuiGroupStyle_Hidden = 1 << 3,
		SurfingImGuiGroupStyle_HeaderSmall = 1 << 4//uses ImGui tree without big header. just arrow
		//SurfingImGuiGroupStyle_NoArrow = 1 << 5,
	};


	//--------------------------------------------------------------
	enum SurfingImGuiTypesGroups
	{
		OFX_IM_GROUP_DEFAULT = 0,// TODO: BUG: it's forced collapsed
		OFX_IM_GROUP_COLLAPSED,
		OFX_IM_GROUP_TREE_EX, // TODO: can be collapsed or opened
		OFX_IM_GROUP_TREE, // TODO: BUG: it's forced collapsed
		OFX_IM_GROUP_SCROLLABLE,
		OFX_IM_GROUP_HIDDEN_HEADER, // hide hidder. TODO; fails on first group. not working
		OFX_IM_GROUP_HIDDEN, // hide header and all the content

		//OFX_IM_GROUP_WINDOWED, // creates a windows to populate into. Notice that must be a root group. can't be a nested! 
		//guiMnager is not in scope here!

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
		//else if (i == 7) _groupInfo = "OFX_IM_GROUP_WINDOWED";
		else _groupInfo = "OFX_IM_GROUP UNKNOWN";

		return _groupInfo;
	}


	//---------------

	// SUGAR SNIPPETS

	//----

	// 1.

	// BUG:
	// Annoying behavior: sometimes the sliders are bigger bc the text long or something,
	// Then all the window panels is being resized bigger if auto resize is enabled!

	// workaround

	//TODO: 
	// A nice idea could be to get the longer param label name width 
	// and use this max width to apply to our layouting engine...

	// Some macro sugar to help fix how sliders force autoresize the panel widths.
	// It's a 'rare behavior' that I am trying to correct doing this.

	//-

//#define DEFAULT_LAYOUT_SLIDERS_BEHAVIOR // -> Comment this line to use a workaround to weird ImGui auto resize layouting on sliders widgets...

#define TEXT_LABEL_TO_RESIZE "----------" // -> This is a 10 chars string that we will use as default label width, to name wdigets.

	//--

#ifndef DEFAULT_LAYOUT_SLIDERS_BEHAVIOR

	// A. Relative to panel width
	// less than threshold will make half window width

#define IMGUI_SUGAR__WIDGETS_PUSH_WIDTH \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD) { ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x / 2.f); }

#define IMGUI_SUGAR__WIDGETS_POP_WIDTH \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD) { ImGui::PopItemWidth(); }

#endif

	// another approach depending on text label. or to use TEXT_LABEL_TO_RESIZE with a fixed chars long.
	// that could be weird because each slider will have a different width.
	//const ImVec2 sz = ImGui::CalcTextSize(TEXT_LABEL_TO_RESIZE); \
	
	//--

	//// B. Using an absolute size

	//#define IMGUI_LABELS_WIDTH_DEFAULT 95
	//#define IMGUI_SUGAR__WIDGETS_PUSH_WIDTH ImGui::PushItemWidth(-IMGUI_LABELS_WIDTH_DEFAULT);
	//#define IMGUI_SUGAR__WIDGETS_POP_WIDTH ImGui::PopItemWidth();

	//--

#ifdef DEFAULT_LAYOUT_SLIDERS_BEHAVIOR

	// C. To bypass and do nothing.

#define IMGUI_SUGAR__WIDGETS_PUSH_WIDTH ;
#define IMGUI_SUGAR__WIDGETS_POP_WIDTH ;

#endif

	//--

	// 2.

	// For OFX_IM_STEPPER

#define IMGUI_SUGAR__STEPPER_WIDTH_PUSH \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD) { ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x / 2.f); }

#define IMGUI_SUGAR__STEPPER_WIDTH_POP \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD) { ImGui::PopItemWidth(); }

//#define IMGUI_SUGAR__STEPPER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x>200 ? ImGui::GetContentRegionAvail().x * 0.6 : ImGui::GetContentRegionAvail().x * 0.6);//sometimes looks weird..
//#define IMGUI_SUGAR__STEPPER_WIDTH_POP ImGui::PopItemWidth();

// fix autoresize grow... 
//#define IMGUI_SUGAR__STEPPER_WIDTH_PUSH \
//	const auto sztx = ImGui::CalcTextSize(TEXT_LABEL_TO_RESIZE); \
//	const float gap = 40; \
//	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - sztx.x - gap);
//#define IMGUI_SUGAR__STEPPER_WIDTH_POP ImGui::PopItemWidth();

	//----

	// 3.

	// Adds mouse wheel control to the last/previous ofParam widget (float/int) rendered.

#define IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(arg1,arg2) ofxImGuiSurfing::AddMouseWheel(arg1, arg2);
#define IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(arg1) ofxImGuiSurfing::AddMouseWheel(arg1);

	//----

	// 3.

	// Adds Constraints Window Shapes

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_FULL \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 2.f, PANEL_WIDGETS_HEIGHT_MIN); \
ImVec2 size_max = ImVec2(ofGetWidth() * 0.9f, ofGetHeight() * 0.9f); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_BIG \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 2.f, PANEL_WIDGETS_HEIGHT_MIN); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 4.f, PANEL_WIDGETS_HEIGHT_MIN * 8.f); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.7f, PANEL_WIDGETS_HEIGHT_MIN * 2.f); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 1.f, PANEL_WIDGETS_HEIGHT_MIN * 5.f); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_SMALL \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.45f, PANEL_WIDGETS_HEIGHT_MIN); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.8f, PANEL_WIDGETS_HEIGHT_MIN * 2.f); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_MINI \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.3f, PANEL_WIDGETS_HEIGHT_MIN * 0.75f ); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.6f, PANEL_WIDGETS_HEIGHT_MIN); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

// Width only

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_BIG \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 2.f, -1); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 4.f, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MEDIUM \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 1.4f, -1); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 3.f, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.7f, -1); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 1.f, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.45f, -1); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.8f, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MINI \
{ \
ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.3f, -1); \
ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.6f, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

	//----

	// 4.

	// Draws a point on the ImGui cursor position for debugging when designing widgets
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
