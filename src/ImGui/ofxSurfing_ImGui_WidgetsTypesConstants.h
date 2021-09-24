
#pragma once

//public:
namespace ofxImGuiSurfing
{

	//--

	// workaround

	//TODO: a nice ide should be to get the longer pamra label name width and use this max width...

	// Some macro sugar to help fix how sliders force autoresize the panel widths.
	// It's a 'rare behaviour' that I am trying to correct doing this.

	// A. Relative to panel width
	//#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x / 2);
	#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x-90);
	#define IMGUI_SUGAR_SLIDER_WIDTH_POP ImGui::PopItemWidth();

	//// B. Using absolute size
	//#define IMGUI_LABELS_WIDTH_DEFAULT 95
	//#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(-IMGUI_LABELS_WIDTH_DEFAULT);
	//#define IMGUI_SUGAR_SLIDER_WIDTH_POP ImGui::PopItemWidth();

	//// C. To bypass and do nothing.
	//#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ;
	//#define IMGUI_SUGAR_SLIDER_WIDTH_POP ;

//--

	//TODO: 
	// make simpler namespace. or move outside the class?
	enum SurfingImGuiTypes
	{
		OFX_IM_DEFAULT = 0,	// default style for each widget. (kind of like ofxImGui does)
		OFX_IM_HIDDEN,		// omit widget. don't let spacing there
		OFX_IM_DISABLED,	// make it invisble, preserve the void spacing
		OFX_IM_INACTIVE,	// draws the widget. but makes it inactive. disables mouse control

		// bool

		// button
		OFX_IM_BUTTON_SMALL,
		OFX_IM_BUTTON_BIG,
		OFX_IM_BUTTON_BIG_XXL,
		// toggle
		OFX_IM_CHECKBOX,
		OFX_IM_TOGGLE_SMALL,
		OFX_IM_TOGGLE_BIG,
		OFX_IM_TOGGLE_BIG_XXL,
		// border
		OFX_IM_TOGGLE_SMALL_BORDER,
		OFX_IM_TOGGLE_BIG_BORDER,
		OFX_IM_TOGGLE_BIG_XXL_BORDER,
		// blink border
		OFX_IM_TOGGLE_SMALL_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK,
		// rounded
		OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG,

		// float/int
		OFX_IM_SLIDER,
		OFX_IM_PROGRESS_BAR,
		OFX_IM_PROGRESS_BAR_NO_TEXT,//TODO:
		OFX_IM_STEPPER,
		OFX_IM_DRAG,
		OFX_IM_KNOB,
		OFX_IM_KNOB_TRAIL,

		// multidim
		OFX_IM_MULTIDIM_SPLIT_SLIDERS,
		//OFX_IM_MULTIDIM_SPLIT_STEPPERS,//TODO:
		//OFX_IM_MULTIDIM_SPLIT_DRAGS,

		// strings
		OFX_IM_TEXT_DISPLAY,
		OFX_IM_TEXT_INPUT,
		OFX_IM_TEXT_BIG,

		// colors
		OFX_IM_COLOR_INPUT,
		OFX_IM_COLOR_BOX,

		OFX_IM_NUM_TYPES
	};

	//--

	//TODO:
	// centralize name types
	// try to mix ImHelpers with ImTypes..
	enum SurfingImGuiTypesGroups
	{
		OFX_IM_GROUP_DEFAULT = 0,
		OFX_IM_GROUP_COLLAPSED,
		OFX_IM_GROUP_TREE_EX,
		OFX_IM_GROUP_TREE,
		OFX_IM_GROUP_SCROLLABLE,
		OFX_IM_GROUP_HIDDEN_HEADER, // hide hidder
		OFX_IM_GROUP_HIDDEN, // hide header and all the content

		OFX_IM_GROUP_NUM_TYPES
	};

	inline static std::string getSurfingImGuiTypesGroupsName(int i)
	{
		string _groupInfo;
		if (i == 0) _groupInfo = "OFX_IM_GROUP_DEFAULT";
		else if (i == 1) _groupInfo = "OFX_IM_GROUP_COLLAPSED";
		else if (i == 2) _groupInfo = "OFX_IM_GROUP_TREE_EX";
		else if (i == 3) _groupInfo = "OFX_IM_GROUP_TREE";
		else if (i == 4) _groupInfo = "OFX_IM_GROUP_SCROLLABLE";
		else if (i == 5) _groupInfo = "OFX_IM_GROUP_HIDDEN_HEADER";

		return _groupInfo;
	}
}
