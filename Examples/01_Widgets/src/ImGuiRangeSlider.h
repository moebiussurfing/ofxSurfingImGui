#pragma once

#include "ofxImGui.h"
#include "imgui_internal.h"

//#include "imgui/imgui.h"
//#include "imgui/imgui_internal.h"

namespace ImGui
{
	template <class t>
	bool RangeSlider(const char* id, const t& min, const t& max, t& low, t& high);
	bool RangeSliderInt(const char* id, const int& min, const int& max, int& low, int& high);
	bool RangeSliderFloat(const char* id, const float& min, const float& max, float& low, float& high);
}
