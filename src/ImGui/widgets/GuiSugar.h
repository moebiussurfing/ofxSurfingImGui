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

	//TODO: WIP:
	//	
	// This is required to be commented bc if not,
	// all nested sliders inside groups, 
	// or into resized windows, could be too big,
	// and then being bigger than the window right border!
	// 
	//#define DEFAULT_LAYOUT_SLIDERS_BEHAVIOR 
	// Comment this line to use a workaround 
	// to weird ImGui auto resize layouting on sliders widgets...

	//--

	// This adjust the width of mainly sliders.

#ifndef DEFAULT_LAYOUT_SLIDERS_BEHAVIOR

	//--

	// A. Relative to panel width
	// less than threshold will make a ratio (half) window width

#define IMGUI_SUGAR__WIDGETS_PUSH_WIDTH \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { \
	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.7f); \
	}

#define IMGUI_SUGAR__WIDGETS_POP_WIDTH \
	if (ImGui::GetContentRegionAvail().x < WINDOW_WIDTH_THRESHOLD_TO_CONSIDER_SMALL) { \
	ImGui::PopItemWidth(); \
	}

	//--

	//	// B: Using max minus the label
	//	#define IMGUI_LABELS_WIDTH_DEFAULT 75
	//#define IMGUI_SUGAR__WIDGETS_PUSH_WIDTH \
    //	ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - IMGUI_LABELS_WIDTH_DEFAULT);
	//#define IMGUI_SUGAR__WIDGETS_POP_WIDTH \
    //	ImGui::PopItemWidth();

#endif

	//--

	//// C. Using an absolute size

	//#define IMGUI_SUGAR__WIDGETS_PUSH_WIDTH ImGui::PushItemWidth(-IMGUI_LABELS_WIDTH_DEFAULT);
	//#define IMGUI_SUGAR__WIDGETS_POP_WIDTH ImGui::PopItemWidth();

	//--

#ifdef DEFAULT_LAYOUT_SLIDERS_BEHAVIOR

	// D. To bypass and do nothing.

#define IMGUI_SUGAR__WIDGETS_PUSH_WIDTH ;
#define IMGUI_SUGAR__WIDGETS_POP_WIDTH ;

#endif


	//----


	// 2.

	// For OFX_IM_STEPPER

#define STEP_FACTOR_WINDOW_IS_SMALL .67f // now using this. we centralized all types together (int/float)

#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_INT .72f
	//#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_INT .67f

	//#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_FLOAT .72f 
	#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_FLOAT .7f 
//#define STEP_FACTOR_WINDOW_IS_SMALL_FOR_FLOAT .67f
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

// Adds Constraints Window Shapes (width and height)

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_MAX \
{ \
ImVec2 size_min = ImVec2(750, 600); \
ImVec2 size_max = ImVec2(ofGetWidth(), ofGetHeight()); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_FULL \
{ \
ImVec2 size_min = ImVec2(550, 500); \
ImVec2 size_max = ImVec2(ofGetWidth() * 0.9f, ofGetHeight() * 0.9f); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_BIG \
{ \
ImVec2 size_min = ImVec2(400, 400); \
ImVec2 size_max = ImVec2(600, 600); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_MEDIUM \
{ \
ImVec2 size_min = ImVec2(300, 300); \
ImVec2 size_max = ImVec2(500, 500); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS \
{ \
ImVec2 size_min = ImVec2(220, 220); \
ImVec2 size_max = ImVec2(400, 400); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_SMALL \
{ \
ImVec2 size_min = ImVec2(150, 150); \
ImVec2 size_max = ImVec2(250, 250); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTS_MINI \
{ \
ImVec2 size_min = ImVec2(100, 100); \
ImVec2 size_max = ImVec2(100, 100); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

//--

// Constraint for width only

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MAX \
{ \
ImVec2 size_min = ImVec2(750, -1); \
ImVec2 size_max = ImVec2(ofGetWidth(), ofGetHeight()); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

#define IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_FULL \
{ \
ImVec2 size_min = ImVec2(550, -1); \
ImVec2 size_max = ImVec2(ofGetWidth() * 0.9f, ofGetHeight() * 0.9f); \
ImGui::SetNextWindowSizeConstraints(size_min, size_max); \
} \

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

#define IMGUI_SUGAR__WINDOW_FIT_APP_HEIGHT ofGetHeight()-ImGui::GetTextLineHeightWithSpacing()
	
};
