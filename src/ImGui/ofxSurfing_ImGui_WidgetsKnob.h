#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
//#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"

#define M_PI 3.14159265358979323846264338327950288
#define VALUEPRECISION 400 // 400

using namespace ImGui;

// Take from
// https://github.com/MacFurax/ofxImGui/blob/docking/

namespace ImGui
{
	//--------------------------------------------------------------
	inline bool Knob(const char* label, float* p_value, float v_min, float v_max, float radius = 25.0f, string format = "%.2f", int valuePrecision = VALUEPRECISION)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		float radius_outer = radius;
		ImVec2 pos = ImGui::GetCursorScreenPos(); // get top left of current widget
		float line_height = ImGui::GetTextLineHeight();
		float space_height = line_height * 0.1; // to add between top, text, knob, value and bottom
		float space_width = radius * 0.1; // to add on left and right to diameter of knob
		ImVec4 widgetRec = ImVec4(pos.x, pos.y, radius*2.0f + space_width * 2.0f, space_height*4.0f + radius * 2.0f + line_height * 2.0f);
		ImVec2 labelLength = ImGui::CalcTextSize(label);

		ImVec2 center = ImVec2(pos.x + space_width + radius, pos.y + space_height * 2 + line_height + radius);

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float ANGLE_MIN = 3.141592f * 0.75f;
		float ANGLE_MAX = 3.141592f * 2.25f;

		ImGui::InvisibleButton(label, ImVec2(widgetRec.z, widgetRec.w));
		bool value_changed = false;
		bool is_active = ImGui::IsItemActive();
		bool is_hovered = ImGui::IsItemActive();
		if (is_active && io.MouseDelta.x != 0.0f)
		{
			float step = (v_max - v_min) / valuePrecision;
			*p_value += io.MouseDelta.x * step;
			if (*p_value < v_min) *p_value = v_min;
			if (*p_value > v_max) *p_value = v_max;
			value_changed = true;
		}

		float t = (*p_value - v_min) / (v_max - v_min);
		float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
		float angle_cos = cosf(angle), angle_sin = sinf(angle);
		float radius_inner = radius_outer * 0.40f;

		// draw label
		float texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);
		draw_list->AddText(ImVec2(texPos, pos.y + space_height), ImGui::GetColorU32(ImGuiCol_Text), label);

		// draw outer knob
		draw_list->AddCircleFilled(center, radius_outer, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : ImGuiCol_FrameBg), 16);

		// line
		draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner),
			ImVec2(
				center.x + angle_cos * (radius_outer - 2),
				center.y + angle_sin * (radius_outer - 2)),
			ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), 2.0f);

		// inner circle
		draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_ButtonActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_SliderGrab), 16);
		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);

		// draw value
		char temp_buf[64];
		sprintf(temp_buf, format.c_str(), *p_value);
		labelLength = ImGui::CalcTextSize(temp_buf);
		texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);

		draw_list->AddText(ImVec2(texPos, pos.y + space_height * 3 + line_height + radius * 2), ImGui::GetColorU32(ImGuiCol_Text), temp_buf);

		return value_changed;
	}
}

namespace ImGui
{
	//--------------------------------------------------------------
	inline bool KnobNeedleTrail2(const char* label, float* p_value, float v_min, float v_max, float trailZero, float radius = 25, float incPrecision = VALUEPRECISION)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		ImVec2 pos = ImGui::GetCursorScreenPos(); // get top left pos of current widget
		float line_height = ImGui::GetTextLineHeight();
		float space_height = line_height * 0.1; // to add between top, label, knob, value and bottom
		float space_width = radius * 0.1; // to add on left and right to diameter of knob
		ImVec4 widgetRec = ImVec4(pos.x, pos.y, radius*2.0f + space_width * 2.0f, space_height*4.0f + radius * 2.0f + line_height * 2.0f);
		ImVec2 labelLength = ImGui::CalcTextSize(label);

		ImVec2 center = ImVec2(pos.x + space_width + radius, pos.y + space_height * 2 + line_height + radius);

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float ANGLE_MIN = 3.141592f * 0.75f;
		float ANGLE_MAX = 3.141592f * 2.25f;

		ImGui::InvisibleButton(label, ImVec2(widgetRec.z, widgetRec.w));
		bool value_changed = false;
		bool is_active = ImGui::IsItemActive();
		bool is_hovered = ImGui::IsItemHovered();
		if (is_active && io.MouseDelta.x != 0.0f)
		{
			float step = (v_max - v_min) / incPrecision;
			*p_value += io.MouseDelta.x * step;
			if (*p_value < v_min) *p_value = v_min;
			if (*p_value > v_max) *p_value = v_max;
			value_changed = true;
		}

		float t = (*p_value - v_min) / (v_max - v_min);
		float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
		float angle_cos = cosf(angle), angle_sin = sinf(angle);
		float radius_inner = radius * 0.35f;

		float refZeroTrailVal = (trailZero - v_min) / (v_max - v_min);
		float refZeroTrailAngle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * refZeroTrailVal;


		// draw label
		float texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);
		draw_list->AddText(ImVec2(texPos, pos.y + space_height), ImGui::GetColorU32(ImGuiCol_Text), label);

		// draw knob
		if (style.FrameBorderSize > 0.0f)
		{
			draw_list->AddCircleFilled(center, radius + style.FrameBorderSize + 1.0f, ImGui::GetColorU32(ImGuiCol_BorderShadow), 32);
			draw_list->AddCircleFilled(center, radius + style.FrameBorderSize, ImGui::GetColorU32(ImGuiCol_Border), 32);
		}
		// draw outer knob
		//draw_list->AddCircleFilled(center, radius, ImGui::GetColorU32(ImGuiCol_FrameBg), 32);
		draw_list->AddCircleFilled(center, radius, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : ImGuiCol_FrameBg), 16);

		// draw needle
		/*draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner),
			ImVec2(center.x + angle_cos * (radius-1.5f), center.y + angle_sin * (radius-1.5f)),
			ImGui::GetColorU32(ImGuiCol_SliderGrabActive), 2.0f);*/

			// line
		draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner),
			ImVec2(
				center.x + angle_cos * (radius - 1.5f),
				center.y + angle_sin * (radius - 1.5f)),
			ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), 2.0f);

		// draw needle trail
		if (refZeroTrailAngle < angle)
		{
			draw_list->PathArcTo(center, radius - 4.5f, refZeroTrailAngle, angle, 2 + (4 * (angle - refZeroTrailAngle))); // draw needle trail
		}
		else {
			draw_list->PathArcTo(center, radius - 4.5f, angle, refZeroTrailAngle, 2 + (4 * (refZeroTrailAngle - angle))); // draw needle trail
		}

		draw_list->PathStroke(ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), false, 6.0f);

		// inner circle
		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16); // draw inner knob
		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_FrameBg), 16); // draw inner knob
		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_FrameBg), 16); // draw inner knob
		draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_ButtonActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_SliderGrab), 16);

		// draw value
		char temp_buf[64];
		sprintf(temp_buf, "%.2f", *p_value);
		labelLength = ImGui::CalcTextSize(temp_buf);
		texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);

		draw_list->AddText(ImVec2(texPos, pos.y + space_height * 3 + line_height + radius * 2), ImGui::GetColorU32(ImGuiCol_Text), temp_buf);

		return value_changed;
	}
}

//-

namespace ofxImGuiSurfing
{
	bool AddKnob(ofParameter<int>& parameter, bool bTrail = false, float width = -1);
	bool AddKnob(ofParameter<float>& parameter, bool bTrail = false, float width = -1);
	bool AddKnob(ofParameter<float>& parameter, float zeroRef, bool bTrail = false);
	bool AddKnob(std::string label, ofParameter<float>& parameter, bool bTrail = false);
	bool AddKnob(std::string label, ofParameter<float>& parameter, float zeroRef, bool bTrail = false);

	//--------------------------------------------------------------
	inline const char * GetUniqueName2(ofAbstractParameter& parameter)
	{
		return (parameter.getName().c_str());
	}

	//--------------------------------------------------------------
	inline const char * GetUniqueName2(const std::string& candidate)
	{
		//std::string result = candidate;
		//while (std::find(windowOpen.usedNames.top().begin(), windowOpen.usedNames.top().end(), result) != windowOpen.usedNames.top().end())
		//{
		//	result += " ";
		//}
		//windowOpen.usedNames.top().push_back(result);
		//return windowOpen.usedNames.top().back().c_str();

		return candidate.c_str();
	}
}

//-

// Int Knob

//--------------------------------------------------------------
inline bool ofxImGuiSurfing::AddKnob(ofParameter<int>& parameter, bool bTrail, float width)
{
	float w = (width * 0.9f) / 2;//TODO: fix tweak
	//float w = (width - ImGui::GetStyle().FramePadding.x) / 2;//TODO: fix tweak

	float tmpRef = parameter.get();
	string n = parameter.getName();
	bool b;
	if (bTrail) b = ImGui::KnobNeedleTrail2(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), parameter.getMin());
	else b = ImGui::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), w, "%.f"/*"%d"*/);
	if (b)
	{
		parameter.set((int)tmpRef);
		return true;
	}
	return false;
}

//-

// Float Knob

//--------------------------------------------------------------
inline bool ofxImGuiSurfing::AddKnob(ofParameter<float>& parameter, bool bTrail, float width)
{
	float w = (width * 0.9f) / 2;//TODO: fix tweak
	//float w = (width - ImGui::GetStyle().FramePadding.x) / 2;//TODO: fix tweak

	auto tmpRef = parameter.get();
	string n = parameter.getName();
	bool b;
	if (bTrail) b = ImGui::KnobNeedleTrail2(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), parameter.getMin());
	else b = ImGui::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), w, "%.2f");
	if (b)
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
inline bool ofxImGuiSurfing::AddKnob(ofParameter<float>& parameter, float zeroRef, bool bTrail)
{
	auto tmpRef = parameter.get();
	string n = parameter.getName();
	bool b;
	//if (bTrail) b = ImGui::KnobNeedleTrail2(GetUniqueName2(parameter), &tmpRef, parameter.getMin(), parameter.getMax(), zeroRef);
	if (bTrail) b = ImGui::KnobNeedleTrail2(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), zeroRef);
	else b = ImGui::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax());
	if (b)
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
inline bool ofxImGuiSurfing::AddKnob(std::string label, ofParameter<float>& parameter, bool bTrail)
{
	auto tmpRef = parameter.get();
	if (bTrail)
	{
		if (ImGui::KnobNeedleTrail2(GetUniqueName2(label), &tmpRef, parameter.getMin(), parameter.getMax(), parameter.getMin()))
		{
			parameter.set(tmpRef);
			return true;
		}
		return false;
	}
	else
	{
		if (ImGui::Knob(GetUniqueName2(label), &tmpRef, parameter.getMin(), parameter.getMax()))
		{
			parameter.set(tmpRef);
			return true;
		}
		return false;
	}
}

//--------------------------------------------------------------
inline bool ofxImGuiSurfing::AddKnob(std::string label, ofParameter<float>& parameter, float zeroRef, bool bTrail)
{
	auto tmpRef = parameter.get();
	bool b;
	if (bTrail) b = ImGui::KnobNeedleTrail2(GetUniqueName2(label), &tmpRef, parameter.getMin(), parameter.getMax(), zeroRef);
	else b = ImGui::Knob(GetUniqueName2(label), &tmpRef, parameter.getMin(), parameter.getMax());
	if (b)
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//----

// v slider

namespace ofxImGuiSurfing
{
	//TODO:
	//bLabel 

	bool AddVSlider2(ofParameter<float>& parameter, ImVec2 &size, bool bLabel = true);
	bool AddVSlider2(std::string label, ofParameter<float>& parameter, ImVec2 &size, bool bLabel = true);
}

//--------------------------------------------------------------
inline bool ofxImGuiSurfing::AddVSlider2(ofParameter<float>& parameter, ImVec2& size, bool bLabel)
{
	auto tmpRef = parameter.get();

	if (ImGui::VSliderFloat(GetUniqueName2(parameter), size, &tmpRef, parameter.getMin(), parameter.getMax(), "%.3f", ImGuiSliderFlags_None))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
inline bool ofxImGuiSurfing::AddVSlider2(std::string label, ofParameter<float>& parameter, ImVec2& size, bool bLabel)
{
	auto tmpRef = parameter.get();
	if (ImGui::VSliderFloat(GetUniqueName2(label), size, &tmpRef, parameter.getMin(), parameter.getMax(), "%.3f", ImGuiSliderFlags_None))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}



//-

////------------------------------------------------
//
//// Taken from
//// https://github.com/d3cod3/ofxVisualProgramming
//
//namespace ofxImGuiSurfing
//{
//	//--------------------------------------------------------------
//	inline bool KnobFloat(ImDrawList* draw_list, float width, ImU32 color, const char* label, float* p_value, float v_min, float v_max, float v_step) {
//		ImGuiIO& io = ImGui::GetIO();
//		ImGuiStyle& style = ImGui::GetStyle();
//
//		float gap = width / 6.0f;
//		float radius_outer = width;
//		float labelGap = width / 1.15f;
//		ImVec2 pos = ImGui::GetCursorScreenPos();
//		ImVec2 center = ImVec2(pos.x + radius_outer + gap, pos.y + labelGap + radius_outer);
//		float line_height = ImGui::GetTextLineHeight();
//
//		float ANGLE_MIN = 3.141592f * 0.75f;
//		float ANGLE_MAX = 3.141592f * 2.25f;
//
//		ImGui::InvisibleButton(label, ImVec2(radius_outer * 2, radius_outer * 2 + line_height + style.ItemInnerSpacing.y));
//		bool value_changed = false;
//		bool is_active = ImGui::IsItemActive();
//		bool is_hovered = ImGui::IsItemHovered();
//		if (is_active && io.MouseDelta.x != 0.0f) {
//			if (v_step <= 0) v_step = 50.f;
//			float step = (v_max - v_min) / v_step;
//			*p_value += io.MouseDelta.x * step;
//
//			if (*p_value < v_min) *p_value = v_min;
//			if (*p_value > v_max) *p_value = v_max;
//			value_changed = true;
//		}
//		else if (is_hovered && (io.MouseDoubleClicked[0] || io.MouseClicked[2])) {
//			*p_value = (v_max + v_min) * 0.5f;  // reset value
//			value_changed = true;
//		}
//
//		float t = (*p_value - v_min) / (v_max - v_min);
//		if (*p_value >= v_max) {
//			t = 1.0f;
//		}
//		float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
//		float angle_cos = cosf(angle), angle_sin = sinf(angle);
//		float radius_inner = radius_outer * 0.40f;
//		float radius_inner_medium = radius_outer * 0.82f;
//		float line_width = width / 5.0f;
//
//		draw_list->AddText(ImVec2(pos.x + gap + (((radius_outer * 2) - ImGui::CalcTextSize(label).x) / 2.0f), pos.y + style.ItemInnerSpacing.y), ImGui::GetColorU32(ImGuiCol_Text), label);
//
//		draw_list->AddCircleFilled(center, radius_outer, IM_COL32(28, 28, 28, 255), 32);
//
//		draw_list->PathArcTo(center, radius_outer - 4, ANGLE_MIN, angle, 32);
//		draw_list->PathArcTo(center, radius_inner_medium, angle, ANGLE_MIN, 32);
//		draw_list->PathStroke(color, true, line_width);
//
//		draw_list->AddCircleFilled(center, radius_inner, is_active ? ImGui::GetColorU32(ImGuiCol_FrameBgActive) : is_hovered ? ImGui::GetColorU32(ImGuiCol_FrameBgHovered) : IM_COL32(28, 28, 28, 255), 32);
//		draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner), ImVec2(center.x + angle_cos * (radius_outer - line_width + 1), center.y + angle_sin * (radius_outer - line_width + 1)), color, line_width);
//
//		char buffer[64];
//		snprintf(buffer, sizeof buffer, "%.2f", *p_value);
//		draw_list->AddText(ImVec2(pos.x + gap + (((radius_outer * 2) - ImGui::CalcTextSize(buffer).x) / 2.0f), pos.y + labelGap + radius_outer * 2 + style.ItemInnerSpacing.y), ImGui::GetColorU32(ImGuiCol_Text), buffer);
//
//		////tooltip
//		//if (is_active || is_hovered)
//		//{
//		//	ImGui::SetNextWindowPos(ImVec2(pos.x + gap - style.WindowPadding.x, pos.y + labelGap + radius_outer));
//		//	ImGui::BeginTooltip();
//		//	ImGui::PushItemWidth(radius_outer * 2);
//		//	ImGui::DragFloat("", p_value);
//		//	ImGui::PopItemWidth();
//		//	ImGui::EndTooltip();
//		//}
//
//		return value_changed;
//	}
//};
//
////-
//
//namespace ofxImGuiSurfing
//{
//	//bool RangeSliderFloat(const char* label, float* v1, float* v2, float v_min, float v_max, const char* display_format = "(%.3f, %.3f)", float power = 1.0f);
//
//	//----
//
//	//TODO:
//	// knob from https://github.com/yumataesu/ImGui_Widgets
//	// https://github.com/yumataesu/ofxImGui_v3/blob/master/src/Helper.cpp
//	//example:
//	//static float val = 0.0;
//	//ofxImGui::Knob("value", &val, 0, 1); ImGui::SameLine();
//	//ImGui::KnobNeedleTrail2("value", &val, 0, 1);
//	//--------------------------------------------------------------
//	static inline bool Knob(const char* label, float* value_p, float minv, float maxv) {
//		ImGuiStyle& style = ImGui::GetStyle();
//		//style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
//		//style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
//		//style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
//
//		float sz = 36.0f;
//
//		float line_height = ImGui::GetTextLineHeight();
//
//		ImVec2 p = ImGui::GetCursorScreenPos();
//		float radio = sz * 0.5f;
//		ImVec2 center = ImVec2(p.x + radio, p.y + radio);
//		float val1 = (value_p[0] - minv) / (maxv - minv);
//		char textval[32];
//		ImFormatString(textval, IM_ARRAYSIZE(textval), "%04.1f", value_p[0]);
//
//		ImVec2 textpos = p;
//		float gamma = M_PI / 4.0f;//0 value in knob
//		float alpha = (M_PI - gamma)*val1*2.0f + gamma;
//
//		float x2 = -sinf(alpha)*radio + center.x;
//		float y2 = cosf(alpha)*radio + center.y;
//
//		ImGui::InvisibleButton(label, ImVec2(sz, sz + line_height + style.ItemInnerSpacing.y));
//
//		bool is_active = ImGui::IsItemActive();
//		bool is_hovered = ImGui::IsItemHovered();
//		bool touched = false;
//
//		if (is_active) {
//			touched = true;
//			ImVec2 mp = ImGui::GetIO().MousePos;
//			alpha = atan2f(mp.x - center.x, center.y - mp.y) + M_PI;
//			//alpha = MAX(gamma, MIN(2.0f*M_PI - gamma, alpha));
//			//alpha = ImMax(gamma, ImMin(2.0f*M_PI - gamma, alpha));
//			float value = 0.5f*(alpha - gamma) / (M_PI - gamma);
//			value_p[0] = value * (maxv - minv) + minv;
//		}
//
//		ImVec2 offset = ImVec2(0, 25);
//
//		ImU32 col32 = ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
//		ImU32 col32line = ImGui::GetColorU32(ImGuiCol_SliderGrabActive);
//		ImU32 col32text = ImGui::GetColorU32(ImGuiCol_Text);
//		ImDrawList* draw_list = ImGui::GetWindowDrawList();
//		draw_list->AddCircleFilled(center, radio, col32, 16);
//		draw_list->AddLine(center, ImVec2(x2, y2), col32line, 3);
//		draw_list->AddText(ImVec2(p.x, p.y + sz + style.ItemInnerSpacing.y), col32text, textval);
//		draw_list->AddText(ImVec2(p.x, p.y + sz + style.ItemInnerSpacing.y + 20), col32text, label);
//
//		//style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
//		//style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
//		//style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
//
//		return touched;
//	}
//};
//
////-----