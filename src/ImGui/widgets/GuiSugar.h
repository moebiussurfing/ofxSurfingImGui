
#pragma once

#include "GuiConstants.h"

/*
 
	This class has widgets sugar

*/

//----

namespace ofxImGuiSurfing
{
	//---------------

	// SUGAR SNIPPETS

	//----

	// 1.

	// BUG:
	// Annoying behavior: 
	// sometimes the sliders are bigger bc the text long or something,
	// Then all the window panels is being resized bigger 
	// if auto resize is enabled!

	// workaround

	//TODO: 
	// A nice idea could be to get the longer param label name width 
	// and use this max width to apply to our layouting engine...

	// Some macro sugar to help fix how sliders force auto resize the panel widths.
	// It's a 'rare behavior' that I am trying to correct doing this.

	//--

	//#define DEFAULT_LAYOUT_SLIDERS_BEHAVIOR 
	// Comment this line to use a workaround 
	// to weird ImGui auto resize layouting on sliders widgets...

	//--

#ifndef DEFAULT_LAYOUT_SLIDERS_BEHAVIOR

	// A. Relative to panel width
	// less than threshold will make half window width

#define IMGUI_SUGAR__WIDGETS_PUSH_WIDTH \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x / 2.f); }

#define IMGUI_SUGAR__WIDGETS_POP_WIDTH \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { ImGui::PopItemWidth(); }

#endif

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

#define STEP_FACTOR_WINDOW_IS_SMALL .67f // now using this. we centralized all types together (int/float)

#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_INT .72f
//#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_INT .67f

//#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_FLOAT .72f 
//#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_FLOAT .7f 
#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_FLOAT .67f 
// To allow see 3 visible decimals, 
// but requires preferably a short label name.

#define IMGUI_SUGAR__STEPPER_WIDTH_PUSH_FLOAT \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * STEP_FACTOR_WINDOW_IS_SMALL_FOR_FLOAT); }

#define IMGUI_SUGAR__STEPPER_WIDTH_POP_FLOAT \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { ImGui::PopItemWidth(); }

	/*
#define IMGUI_SUGAR__STEPPER_WIDTH_PUSH \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * STEP_FACTOR_WINDOW_IS_SMALL_FOR_INT); }

#define IMGUI_SUGAR__STEPPER_WIDTH_POP \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { ImGui::PopItemWidth(); }
	*/

#define IMGUI_SUGAR__STEPPER_WIDTH_PUSH \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * STEP_FACTOR_WINDOW_IS_SMALL); }

#define IMGUI_SUGAR__STEPPER_WIDTH_POP \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { ImGui::PopItemWidth(); }

	//--

#define TEXT_LABEL_TO_RESIZE "0123456789"
//#define TEXT_LABEL_TO_RESIZE "----------" 

	//TODO:
	// This is a 10 chars string that we will use as default label width, to name widgets.
	// another approach depending on text label. or to use TEXT_LABEL_TO_RESIZE with a fixed chars long.
	// that could be weird because each slider will have a different width.
	//const ImVec2 sz = ImGui::CalcTextSize(TEXT_LABEL_TO_RESIZE); \
	 
	//TODO:
	// Fix auto resize loop grow...
	// Using an standard text size for the widgets 
	//#define IMGUI_SUGAR__STEPPER_WIDTH_PUSH \
	//	const auto sztx = ImGui::CalcTextSize(TEXT_LABEL_TO_RESIZE); \
	//	const float gap = 40; \
	//	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - sztx.x - gap);
	//#define IMGUI_SUGAR__STEPPER_WIDTH_POP ImGui::PopItemWidth();

	//----

	// 3.

	// Adds mouse wheel control to the last/previous ofParam widget (float/int) rendered.

//#define IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(arg1, arg2, arg3) ofxImGuiSurfing::AddMouseWheel(arg1, arg2, arg3);
#define IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(arg1, arg2) ofxImGuiSurfing::AddMouseWheel(arg1, arg2); // param, flip

//--

//// macOS fix
//#define IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(arg1) ofxImGuiSurfing::AddMouseWheel(arg1, false); // param, flip

//--

// Amount of steps per widgets. will calculate range between max/min.
#define MOUSE_WHEEL_STEPS 100.f

// How more fine is when CTRL pressed 
#define MOUSE_WHEEL_FINETUNE_CTRL_RATIO 0.20f
//#define MOUSE_WHEEL_FINETUNE_CTRL_RATIO 5

//----

// 3.

//TODO: should DEPRECATE these ratio constants a make absolute sizes.

// Adds Constraints Window Shapes (width and height)

// Width and height

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

//--

// Width only

//#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_BIG \
//{ \
//ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 2.f, -1); \
//ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 4.f, -1); \
//ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
//} \

//#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MEDIUM \
//{ \
//ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 1.4f, -1); \
//ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 3.f, -1); \
//ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
//} \

//#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW \
//{ \
//ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.75f, -1); \
//ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 1.30f, -1); \
//ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
//} \

//#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL \
//{ \
//ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.45f, -1); \
//ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.8f, -1); \
//ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
//} \

//#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MINI \
//{ \
//ImVec2 size_min = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.3f, -1); \
//ImVec2 size_max = ImVec2(PANEL_WIDGETS_WIDTH_MIN * 0.6f, -1); \
//ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
//} \


#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_BIG \
{ \
ImVec2 size_min = ImVec2(400, -1); \
ImVec2 size_max = ImVec2(600, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MEDIUM \
{ \
ImVec2 size_min = ImVec2(300, -1); \
ImVec2 size_max = ImVec2(500, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW \
{ \
ImVec2 size_min = ImVec2(220, -1); \
ImVec2 size_max = ImVec2(400, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL \
{ \
ImVec2 size_min = ImVec2(150, -1); \
ImVec2 size_max = ImVec2(250, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MINI \
{ \
ImVec2 size_min = ImVec2(100, -1); \
ImVec2 size_max = ImVec2(100, -1); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

};
