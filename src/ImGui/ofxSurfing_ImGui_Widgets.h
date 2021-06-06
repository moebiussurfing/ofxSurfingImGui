#pragma once
#include "ofxImGui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"
#define M_PI 3.14159265358979323846264338327950288

//TODO:
//WIP
// to add more uncoming new widgets here

//cute widgets !
//https://github.com/soufianekhiat/DearWidgets

//spin arrows widget
//https://github.com/ocornut/imgui/issues/2649

//spinners, loading bars 
//https://github.com/ocornut/imgui/issues/1901#issuecomment-552185000
//https://github.com/ocornut/imgui/issues/1901

//Rotating text and icon demo for dear imgui 
//https://gist.github.com/ice1000/865c7666d13b945628254aa00bd9d62d

//-

namespace ofxImGui
{
	//bool RangeSliderFloat(const char* label, float* v1, float* v2, float v_min, float v_max, const char* display_format = "(%.3f, %.3f)", float power = 1.0f);

	//----

	//TODO:
	// knob from https://github.com/yumataesu/ImGui_Widgets
	// https://github.com/yumataesu/ofxImGui_v3/blob/master/src/Helper.cpp
	//example:
	//static float val = 0.0;
	//ofxImGui::Knob("value", &val, 0, 1); ImGui::SameLine();
	//ImGui::KnobNeedleTrail("value", &val, 0, 1);
	//--------------------------------------------------------------
	static inline bool Knob(const char* label, float* value_p, float minv, float maxv) {
		ImGuiStyle& style = ImGui::GetStyle();
		//style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
		//style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
		//style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);

		float sz = 36.0f;

		float line_height = ImGui::GetTextLineHeight();

		ImVec2 p = ImGui::GetCursorScreenPos();
		float radio = sz * 0.5f;
		ImVec2 center = ImVec2(p.x + radio, p.y + radio);
		float val1 = (value_p[0] - minv) / (maxv - minv);
		char textval[32];
		ImFormatString(textval, IM_ARRAYSIZE(textval), "%04.1f", value_p[0]);

		ImVec2 textpos = p;
		float gamma = M_PI / 4.0f;//0 value in knob
		float alpha = (M_PI - gamma)*val1*2.0f + gamma;

		float x2 = -sinf(alpha)*radio + center.x;
		float y2 = cosf(alpha)*radio + center.y;

		ImGui::InvisibleButton(label, ImVec2(sz, sz + line_height + style.ItemInnerSpacing.y));

		bool is_active = ImGui::IsItemActive();
		bool is_hovered = ImGui::IsItemHovered();
		bool touched = false;

		if (is_active) {
			touched = true;
			ImVec2 mp = ImGui::GetIO().MousePos;
			alpha = atan2f(mp.x - center.x, center.y - mp.y) + M_PI;
			//alpha = MAX(gamma, MIN(2.0f*M_PI - gamma, alpha));
			//alpha = ImMax(gamma, ImMin(2.0f*M_PI - gamma, alpha));
			float value = 0.5f*(alpha - gamma) / (M_PI - gamma);
			value_p[0] = value * (maxv - minv) + minv;
		}

		ImVec2 offset = ImVec2(0, 25);

		ImU32 col32 = ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
		ImU32 col32line = ImGui::GetColorU32(ImGuiCol_SliderGrabActive);
		ImU32 col32text = ImGui::GetColorU32(ImGuiCol_Text);
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->AddCircleFilled(center, radio, col32, 16);
		draw_list->AddLine(center, ImVec2(x2, y2), col32line, 3);
		draw_list->AddText(ImVec2(p.x, p.y + sz + style.ItemInnerSpacing.y), col32text, textval);
		draw_list->AddText(ImVec2(p.x, p.y + sz + style.ItemInnerSpacing.y + 20), col32text, label);

		//style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
		//style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
		//style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);

		return touched;
	}


	///



	//https://gist.github.com/nariakiiwatani/dabf4cd2d04ad015bb6fabdedef7b2aa
	//namespace ImGui
	//{
	//	static bool SelectFile(const std::string &path, std::string &selected, const std::vector<std::string> &ext = {}) {
	//		bool ret = false;
	//		if (ofFile(path).isDirectory()) {
	//			if (TreeNode(ofFilePath::getBaseName(path).c_str())) {
	//				ofDirectory dir;
	//				if (!ext.empty()) {
	//					dir.allowExt("");
	//					for (auto &&e : ext) {
	//						dir.allowExt(e);
	//					}
	//				}
	//				dir.listDir(path);
	//				for (auto &f : dir) {
	//					ret |= SelectFile(f.path(), selected, ext);
	//				}
	//				TreePop();
	//			}
	//		}
	//		else if (Button(ofFilePath::getFileName(path).c_str())) {
	//			selected = path;
	//			ret = true;
	//		}
	//		return ret;
	//	}
	//}

	//TODO:
	//BUG:
	//when drawing two plots both are sharing variables ?? so only drawing one
	//--------------------------------------------------------------
	inline void AddPlot(ofParameter<float>& parameter, ImVec2 v2 = ImVec2(100, 80.0f))
	{
		ImGui::PushID(1);

		static float min = parameter.getMin();
		static float max = parameter.getMax();
		static std::string name = parameter.getName();
		//ImGui::Text(name.c_str());

		static bool animate = true;

		// Fill an array of contiguous float values to plot
		// Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
		// and the sizeof() of your structure in the "stride" parameter.

		//static const size_t duration = 60 * 4;//fps * secs
		//static float values[duration] = {};
		static float values[120] = {};

		static int values_offset = 0;
		static double refresh_time = 0.0;

		if (!animate || refresh_time == 0.0)
			refresh_time = ImGui::GetTime();
		while (refresh_time < ImGui::GetTime()) // Create data at fixed 60 Hz rate for the demo
		{
			static float phase = 0.0f;
			values[values_offset] = parameter.get();
			//values[values_offset] = cosf(phase);

			values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
			phase += 0.10f * values_offset;
			refresh_time += 1.0f / 60.0f;
		}

		static bool bOverlayAvg = false;
		static char overlay[32] = "";
		if (bOverlayAvg)
		{
			float average = 0.0f;
			for (int n = 0; n < IM_ARRAYSIZE(values); n++)
				average += values[n];
			average /= (float)IM_ARRAYSIZE(values);
			sprintf(overlay, "avg %f", average);
		}

		//ImGui::PushID(1);
		//ImGui::PlotLines("Plot", values, IM_ARRAYSIZE(values), values_offset, overlay, min, max, v2);
		ImGui::PlotLines(name.c_str(), values, IM_ARRAYSIZE(values), values_offset, overlay, min, max, v2);

		//ImGui::PushID(1);
		ImGui::Checkbox("Animate", &animate);

		ImGui::PopID();
	}

	//----

	////TODO:
	////snap engine
	//auto snap = [=](float value, float snap_threshold) -> float {
	//	float modulo = std::fmodf(value, snap_threshold);
	//	float moduloRatio = std::fabsf(modulo) / snap_threshold;
	//	if (moduloRatio < 0.5f)
	//		value -= modulo;
	//	else if (moduloRatio > (1.f - 0.5f))
	//		value = value - modulo + snap_threshold * ((value < 0.f) ? -1.f : 1.f);
	//	return value;
	//};
	////ImGui::Begin(name.data());
	////if (ImGui::IsItemActive()) 
	//{
	//	auto p = ImGui::GetWindowPos();
	//	auto size = ImGui::GetWindowSize();

	//	float x = snap(p.x, 16.f);
	//	float y = snap(p.y, 16.f);
	//	float sizex = snap(size.x, 16.f);
	//	float sizey = snap(size.y, 16.f);
	//	ImGui::SetWindowPos(ImFloor(ImVec2(x, y)));
	//}
};

//-----

//TODO:
//extra widgets
//https://github.com/MacFurax/ofxImGui/blob/docking/libs/imgui/src/imgui_widgets.cpp
namespace ImGui {
	//used by AddKnob
	inline bool KnobNeedleTrail(const char* label, float* p_value, float v_min, float v_max, float trailZero, float radius = 20, float incPrecision = 0.001)
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


		//draw label
		float texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);
		draw_list->AddText(ImVec2(texPos, pos.y + space_height), ImGui::GetColorU32(ImGuiCol_Text), label);
		// draw knob
		if (style.FrameBorderSize > 0.0f)
		{
			draw_list->AddCircleFilled(center, radius + style.FrameBorderSize + 1.0f, ImGui::GetColorU32(ImGuiCol_BorderShadow), 32);
			draw_list->AddCircleFilled(center, radius + style.FrameBorderSize, ImGui::GetColorU32(ImGuiCol_Border), 32);
		}
		// draw outer knob
		draw_list->AddCircleFilled(center, radius, ImGui::GetColorU32(ImGuiCol_FrameBg), 32);

		// draw needle
		/*draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner),
			ImVec2(center.x + angle_cos * (radius-1.5f), center.y + angle_sin * (radius-1.5f)),
			ImGui::GetColorU32(ImGuiCol_SliderGrabActive), 2.0f);*/

		draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner),
			ImVec2(center.x + angle_cos * (radius - 1.5f), center.y + angle_sin * (radius - 1.5f)),
			ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), 2.0f);

		//ImGuiCol_SliderGrab



		// draw needle trail
		if (refZeroTrailAngle < angle)
		{
			draw_list->PathArcTo(center, radius - 4.5f, refZeroTrailAngle, angle, 2 + (4 * (angle - refZeroTrailAngle))); // draw needle trail
		}
		else {
			draw_list->PathArcTo(center, radius - 4.5f, angle, refZeroTrailAngle, 2 + (4 * (refZeroTrailAngle - angle))); // draw needle trail
		}

		draw_list->PathStroke(ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), false, 6.0f);

		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16); // draw inner knob
		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_FrameBg), 16); // draw inner knob
		draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_FrameBg), 16); // draw inner knob

		// draw value
		char temp_buf[64];
		sprintf(temp_buf, "%.2f", *p_value);
		labelLength = ImGui::CalcTextSize(temp_buf);
		texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);

		draw_list->AddText(ImVec2(texPos, pos.y + space_height * 3 + line_height + radius * 2), ImGui::GetColorU32(ImGuiCol_Text), temp_buf);

		return value_changed;
	}
};//ImGui

//-----

namespace ofxSurfingHelpers {

	//TODO:
	//knob

	//bool AddKnob(ofParameter<float>& parameter);
	//bool AddKnob(ofParameter<float>& parameter, float zeroRef);
	//bool AddKnob(std::string label, ofParameter<float>& parameter);
	//bool AddKnob(std::string label, ofParameter<float>& parameter, float zeroRef);

	inline bool AddKnob(ofParameter<float>& parameter)
	{
		std::string name = parameter.getName();
		//string name = parameter.getName();

		auto tmpRef = parameter.get();
		if (ImGui::KnobNeedleTrail(name.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), parameter.getMin()))
		{
			parameter.set(tmpRef);
			return true;
		}
		return false;
	}

	//inline bool AddKnob(ofParameter<float>& parameter, float zeroRef)
	//{
	//	string name = parameter.getName();
	//	auto tmpRef = parameter.get();
	//	if (ImGui::KnobNeedleTrail(name, &tmpRef, parameter.getMin(), parameter.getMax(), zeroRef))
	//	{
	//		parameter.set(tmpRef);
	//		return true;
	//	}
	//	return false;
	//}

	//inline bool AddKnob(std::string label, ofParameter<float>& parameter)
	//{
	//	string name = parameter.getName();
	//	auto tmpRef = parameter.get();
	//	if (ImGui::KnobNeedleTrail(name, &tmpRef, parameter.getMin(), parameter.getMax(), parameter.getMin()))
	//	{
	//		parameter.set(tmpRef);
	//		return true;
	//	}
	//	return false;
	//}

	//inline bool AddKnob(std::string label, ofParameter<float>& parameter, float zeroRef)
	//{
	//	string name = parameter.getName();
	//	auto tmpRef = parameter.get();
	//	if (ImGui::KnobNeedleTrail(name, &tmpRef, parameter.getMin(), parameter.getMax(), zeroRef))
	//	{
	//		parameter.set(tmpRef);
	//		return true;
	//	}
	//	return false;
	//}
};

//-----

// how to set colors
//static float b = 1.0f;
//static float c = 0.5f;
//static int i = 3;// hue colors are from 0 to 7
//ImVec4 _color1 = (ImVec4)ImColor::HSV(i / 7.0f, b, b);
//ImVec4 _color2 = (ImVec4)ImColor::HSV(i / 7.0f, c, c);