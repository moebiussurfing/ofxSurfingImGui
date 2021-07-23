
#pragma once

//public:
namespace ofxImGuiSurfing
{
	//TODO: 
	// make simpler namespace. or move outside the class?
	enum SurfingImGuiTypes
	{
		OFX_IM_DEFAULT = 0,	// default style for each widget. (kind of like ofxImGui does)
		OFX_IM_HIDDEN,		// omit widget. don't let spacing there
		OFX_IM_DISABLED,	// make it invisble, preserve the void spacing
		OFX_IM_INACTIVE,	// draws the widget. but makes it inactive. disables mouse control

		OFX_IM_CHECKBOX,	// bool
		OFX_IM_BUTTON_SMALL,
		OFX_IM_BUTTON_BIG,
		OFX_IM_BUTTON_BIG_XXL,
		OFX_IM_TOGGLE_SMALL,
		OFX_IM_TOGGLE_BIG,
		OFX_IM_TOGGLE_BIG_XXL,

		OFX_IM_SLIDER,		// float/int
		OFX_IM_PROGRESS_BAR,
		OFX_IM_STEPPER,
		OFX_IM_DRAG,

		OFX_IM_TEXT_DISPLAY, // strings
		OFX_IM_TEXT_INPUT,
		OFX_IM_TEXT_BIG,

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
		OFX_IM_GROUP_HIDDEN_HEADER, // hide hider
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
