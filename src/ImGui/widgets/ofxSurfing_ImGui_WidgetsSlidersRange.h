#pragma once

#include "ofMain.h"

// https://github.com/ocornut/imgui/issues/76
// Taken from: https://github.com/wasikuss/imgui/commit/a50515ace6d9a62ebcd69817f1da927d31c39bb1

#include "ofxImGui.h"

#include "ofxSurfing_ImGui_WidgetsTypesConstants.h"

#include "imgui_internal.h"

using namespace ImGui;

//namespace ImGui
namespace ofxImGuiSurfing
{
	//--------------
	// Range Sliders
	//--------------

	//// Exmaple Snippet:
	//static float v1 = 0;
	//static float v2 = 1;
	//static float v_min = 0;
	//static float v_max = 1;
	//static float v3 = 0;
	//static float v4 = 1;
	//ImGui::RangeSliderFloat("range1", &v1, &v2, v_min, v_max, "%.3f  %.3f", 1.0f);
	//ImGui::RangeSliderFloat("range2", &v3, &v4, v_min, v_max);

	//// Exmaple Snippet:
	//// Vanilla slider
	//static float begin = 10, end = 90;
	//static int begin_i = 100, end_i = 1000;
	//ImGui::DragFloatRange2("range", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
	//ImGui::DragIntRange2("range int (no bounds)", &begin_i, &end_i, 5, 0, 0, "Min: %.0f units", "Max: %.0f units");

	//----

	// Tools

	///*IMGUI_API*/ bool RangeSliderFloat(const char* label, float* v1, float* v2, float v_min, float v_max, const char* display_format = "(%.3f, %.3f)", float power = 1.0f);

	// Sanitize format
	// - Zero terminate so extra characters after format (e.g. "%f123") don't confuse atof/atoi
	// - stb_sprintf.h supports several new modifiers which format numbers in a way that also makes them incompatible atof/atoi.
	//--------------------------------------------------------------
	inline static void SanitizeFormatString(const char* fmt, char* fmt_out, size_t fmt_out_size)
	{
		IM_UNUSED(fmt_out_size);
		const char* fmt_end = ImParseFormatFindEnd(fmt);
		IM_ASSERT((size_t)(fmt_end - fmt + 1) < fmt_out_size); // Format is too long, let us know if this happens to you!
		while (fmt < fmt_end)
		{
			char c = *(fmt++);
			if (c != '\'' && c != '$' && c != '_') // Custom flags provided by stb_sprintf.h. POSIX 2008 also supports '.
				*(fmt_out++) = c;
		}
		*fmt_out = 0; // Zero-terminate
	}

	//--------------------------------------------------------------
	template<typename TYPE>
	inline static const char* ImAtoi(const char* src, TYPE* output)
	{
		int negative = 0;
		if (*src == '-') { negative = 1; src++; }
		if (*src == '+') { src++; }
		TYPE v = 0;
		while (*src >= '0' && *src <= '9')
			v = (v * 10) + (*src++ - '0');
		*output = negative ? -v : v;
		return src;
	}

	//--------------------------------------------------------------
	template<typename TYPE, typename SIGNEDTYPE>
	TYPE /*ImGui::*/RoundScalarWithFormatT(const char* format, ImGuiDataType data_type, TYPE v)
	{
		const char* fmt_start = ImParseFormatFindStart(format);
		if (fmt_start[0] != '%' || fmt_start[1] == '%') // Don't apply if the value is not visible in the format string
			return v;

		// Sanitize format
		char fmt_sanitized[32];
		SanitizeFormatString(fmt_start, fmt_sanitized, IM_ARRAYSIZE(fmt_sanitized));
		fmt_start = fmt_sanitized;

		// Format value with our rounding, and read back
		char v_str[64];
		ImFormatString(v_str, IM_ARRAYSIZE(v_str), fmt_start, v);
		const char* p = v_str;
		while (*p == ' ')
			p++;
		if (data_type == ImGuiDataType_Float || data_type == ImGuiDataType_Double)
			v = (TYPE)ImAtof(p);
		else
			ImAtoi(p, (SIGNEDTYPE*)&v);
		return v;
	}

	//--------------------------------------------------------------
	inline float RoundScalarWithFormatFloat(const char* format, ImGuiDataType data_type, float v)
	{
		return RoundScalarWithFormatT<float, float>(format, data_type, v);
	}

	//--------------------------------------------------------------
	inline float SliderCalcRatioFromValueFloat(ImGuiDataType data_type, float v, float v_min, float v_max, float power, float linear_zero_pos)
	{
		return ScaleRatioFromValueT<float, float, float>(data_type, v, v_min, v_max, false, power, linear_zero_pos);
	}

	//extern float RoundScalarWithFormatFloat(const char* format, ImGuiDataType data_type, float v);
	//extern float SliderCalcRatioFromValueFloat(ImGuiDataType data_type, float v, float v_min, float v_max, float power, float linear_zero_pos);

	//----

	// ~80% Common code with ImGui::SliderBehavior
	//--------------------------------------------------------------
	inline bool RangeSliderBehavior(const ImRect& frame_bb, ImGuiID id, float* v1, float* v2, float v_min, float v_max, float power, int decimal_precision, ImGuiSliderFlags flags)
	{
		ImGuiContext& g = *GImGui;
		ImGuiWindow* window = GetCurrentWindow();
		const ImGuiStyle& style = g.Style;

		// Draw frame
		RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

		const bool is_non_linear = (power < 1.0f - 0.00001f) || (power > 1.0f + 0.00001f);
		const bool is_horizontal = (flags & ImGuiSliderFlags_Vertical) == 0;

		const float grab_padding = 2.0f;
		const float slider_sz = is_horizontal ? (frame_bb.GetWidth() - grab_padding * 2.0f) : (frame_bb.GetHeight() - grab_padding * 2.0f);
		float grab_sz;
		if (decimal_precision > 0) grab_sz = ImMin(style.GrabMinSize, slider_sz);
		else grab_sz = ImMin(ImMax(1.0f * (slider_sz / ((v_min < v_max ? v_max - v_min : v_min - v_max) + 1.0f)), style.GrabMinSize), slider_sz);  // Integer sliders, if possible have the grab size represent 1 unit
		const float slider_usable_sz = slider_sz - grab_sz;
		const float slider_usable_pos_min = (is_horizontal ? frame_bb.Min.x : frame_bb.Min.y) + grab_padding + grab_sz * 0.5f;
		const float slider_usable_pos_max = (is_horizontal ? frame_bb.Max.x : frame_bb.Max.y) - grab_padding - grab_sz * 0.5f;

		// For logarithmic sliders that cross over sign boundary we want the exponential increase to be symmetric around 0.0f
		float linear_zero_pos = 0.0f;   // 0.0->1.0f
		if (v_min * v_max < 0.0f)
		{
			// Different sign
			const float linear_dist_min_to_0 = powf(fabsf(0.0f - v_min), 1.0f / power);
			const float linear_dist_max_to_0 = powf(fabsf(v_max - 0.0f), 1.0f / power);
			linear_zero_pos = linear_dist_min_to_0 / (linear_dist_min_to_0 + linear_dist_max_to_0);
		}
		else
		{
			// Same sign
			linear_zero_pos = v_min < 0.0f ? 1.0f : 0.0f;
		}

		// Process clicking on the slider
		bool value_changed = false;
		if (g.ActiveId == id)
		{
			if (g.IO.MouseDown[0])
			{
				const float mouse_abs_pos = is_horizontal ? g.IO.MousePos.x : g.IO.MousePos.y;
				float clicked_t = (slider_usable_sz > 0.0f) ? ImClamp((mouse_abs_pos - slider_usable_pos_min) / slider_usable_sz, 0.0f, 1.0f) : 0.0f;
				if (!is_horizontal)
					clicked_t = 1.0f - clicked_t;

				float new_value;
				if (is_non_linear)
				{
					// Account for logarithmic scale on both sides of the zero
					if (clicked_t < linear_zero_pos)
					{
						// Negative: rescale to the negative range before powering
						float a = 1.0f - (clicked_t / linear_zero_pos);
						a = powf(a, power);
						new_value = ImLerp(ImMin(v_max, 0.0f), v_min, a);
					}
					else
					{
						// Positive: rescale to the positive range before powering
						float a;
						if (fabsf(linear_zero_pos - 1.0f) > 1.e-6f)
							a = (clicked_t - linear_zero_pos) / (1.0f - linear_zero_pos);
						else
							a = clicked_t;
						a = powf(a, power);
						new_value = ImLerp(ImMax(v_min, 0.0f), v_max, a);
					}
				}
				else
				{
					// Linear slider
					new_value = ImLerp(v_min, v_max, clicked_t);
				}

				char fmt[64];
				snprintf(fmt, 64, "%%.%df", decimal_precision);

				// Round past decimal precision
				new_value = RoundScalarWithFormatFloat(fmt, ImGuiDataType_Float, new_value);
				if (*v1 != new_value || *v2 != new_value)
				{
					if (fabsf(*v1 - new_value) < fabsf(*v2 - new_value))
					{
						*v1 = new_value;
					}
					else
					{
						*v2 = new_value;
					}
					value_changed = true;
				}
			}
			else
			{
				ClearActiveID();
			}
		}

		// Calculate slider grab positioning
		float grab_t = SliderCalcRatioFromValueFloat(ImGuiDataType_Float, *v1, v_min, v_max, power, linear_zero_pos);

		// Draw
		if (!is_horizontal)
			grab_t = 1.0f - grab_t;
		float grab_pos = ImLerp(slider_usable_pos_min, slider_usable_pos_max, grab_t);
		ImRect grab_bb1;
		if (is_horizontal) grab_bb1 = ImRect(ImVec2(grab_pos - grab_sz * 0.5f, frame_bb.Min.y + grab_padding), ImVec2(grab_pos + grab_sz * 0.5f, frame_bb.Max.y - grab_padding));
		else grab_bb1 = ImRect(ImVec2(frame_bb.Min.x + grab_padding, grab_pos - grab_sz * 0.5f), ImVec2(frame_bb.Max.x - grab_padding, grab_pos + grab_sz * 0.5f));
		window->DrawList->AddRectFilled(grab_bb1.Min, grab_bb1.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

		// Calculate slider grab positioning
		grab_t = SliderCalcRatioFromValueFloat(ImGuiDataType_Float, *v2, v_min, v_max, power, linear_zero_pos);

		// Draw
		if (!is_horizontal) grab_t = 1.0f - grab_t;
		grab_pos = ImLerp(slider_usable_pos_min, slider_usable_pos_max, grab_t);
		ImRect grab_bb2;
		if (is_horizontal) grab_bb2 = ImRect(ImVec2(grab_pos - grab_sz * 0.5f, frame_bb.Min.y + grab_padding), ImVec2(grab_pos + grab_sz * 0.5f, frame_bb.Max.y - grab_padding));
		else grab_bb2 = ImRect(ImVec2(frame_bb.Min.x + grab_padding, grab_pos - grab_sz * 0.5f), ImVec2(frame_bb.Max.x - grab_padding, grab_pos + grab_sz * 0.5f));
		window->DrawList->AddRectFilled(grab_bb2.Min, grab_bb2.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

		ImRect connector(grab_bb1.Min, grab_bb2.Max);
		connector.Min.x += grab_sz;
		connector.Min.y += grab_sz * 0.3f;
		connector.Max.x -= grab_sz;
		connector.Max.y -= grab_sz * 0.3f;

		window->DrawList->AddRectFilled(connector.Min, connector.Max, GetColorU32(ImGuiCol_SliderGrab), style.GrabRounding);

		return value_changed;
	}

	//--

	// ~95% Common code with ImGui::SliderFloat
	//--------------------------------------------------------------
	inline /*IMGUI_API*/ bool RangeSliderFloat(const char* label, float* v1, float* v2, float v_min, float v_max, const char* display_format = "(%.3f, %.3f)", float power = 1.0f, ImVec2 shape = ImVec2(-1, -1), bool bfullsize = true)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems) return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		//ImVec2 pcursor = ImGui::GetCursorScreenPos();//TODO: fix size ?

		bool fixedWidth = true;//to align multiple range sliders
		ImVec2 label_size;
		if (fixedWidth) label_size = ImVec2(120, 10);//hardcoded size
		else label_size = CalcTextSize(label, NULL, true);//sized by text long

		//TODO:
		float w;
		//if (bfullsize) w = ImGui::GetContentRegionAvail().x - label_size.x;
		if (bfullsize) w = CalcItemWidth();
		else if (shape.x == -1 && shape.y == -1)
		{
			//if (bfullsize) w = ImGui::GetContentRegionAvail().x - label_size.x;
			//else w = 200;//?
			w = 200;//? default width when bfullsize = false and shape = -1,-1 
		}
		else
		{
			w = shape.x - label_size.x - 20;
		}

		const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y*2.0f));
		const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

		// NB- we don't call ItemSize() yet because we may turn into a text edit box below
		if (!ItemAdd(total_bb, id))
		{
			ItemSize(total_bb, style.FramePadding.y);
			return false;
		}

		const bool hovered = ItemHoverable(frame_bb, id);
		if (hovered) SetHoveredID(id);

		if (!display_format) display_format = "(%.3f, %.3f)";
		//display_format = "%.3f - %.3f";

		int decimal_precision = ImParseFormatPrecision(display_format, 3);

		// Tabbing or CTRL-clicking on Slider turns it into an input box
		bool start_text_input = false;
		const bool tab_focus_requested = (GetItemStatusFlags() /*& ImGuiItemStatusFlags_Focused*/) != 0;
		if (tab_focus_requested || (hovered && g.IO.MouseClicked[0]))
		{
			SetActiveID(id, window);
			FocusWindow(window);

			if (tab_focus_requested || g.IO.KeyCtrl)
			{
				start_text_input = true;
				g.TempInputId = 0;
			}
		}

		// Text input
		// Crash
		//if (start_text_input || (g.ActiveId == id && g.TempInputId == id))
		//{
		//    char fmt[64];
		//    snprintf(fmt, 64, "%%.%df", decimal_precision);
		//    return TempInputScalar(frame_bb, id, label, ImGuiDataType_Float, v1, fmt);
		//}

		//-

		//TODO: this breaks the width whe auto resize...
		//ItemSize(total_bb, style.FramePadding.y);

		// workaround
		//float h = (ImGui::GetIO().FontDefault->FontSize + ImGui::GetStyle().FramePadding.y * 2);
		//float h = label_size.y + 2 * style.FramePadding.y;
		float h = ofxImGuiSurfing::getWidgetsHeightUnit() + style.FramePadding.y;
		const ImRect _bb(10, style.FramePadding.y, 400, h);
		//const ImRect _bb(pcursor.x, pcursor.y, w + label_size.x, 1);
		ItemSize(_bb, style.FramePadding.y);

		//-

		// Actual slider behavior + render grab
		const bool value_changed = RangeSliderBehavior(frame_bb, id, v1, v2, v_min, v_max, power, decimal_precision, 0);

		// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
		char value_buf[64];
		const char* value_buf_end = value_buf + ImFormatString(value_buf, IM_ARRAYSIZE(value_buf), display_format, *v1, *v2);
		RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));

		// Render Text
		if (label_size.x > 0.0f) RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

		//fixing auto resize infinite grow..
		//ImGui::Dummy(ImVec2(100, 0));//?
		//ImGui::Dummy(ImVec2(0, 0));//?
		//ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));

		return value_changed;
	}


	//----


	// ofParameters Helpers

	// Float
	//--------------------------------------------------------------
	inline static bool AddRangeParam(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, const char* display_format = "%.3f  %.3f", float power = 1.0f, ImVec2 shape = ImVec2(-1, -1), bool bfullsize = false)
		//inline static bool AddRangeParam(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, const char* display_format = "%.3f  %.3f", float power = 1.0f, ImVec2 shape = ImVec2(-1, -1), bool bfullsize = true)
	{
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		if (bfullsize) IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		ImGui::PushID(name.c_str());
		if (RangeSliderFloat(name.c_str(), &tmpRefMin, &tmpRefMax, parameterMin.getMin(), parameterMax.getMax(), display_format, power, shape, bfullsize))
		{
			parameterMin.set(tmpRefMin);
			parameterMax.set(tmpRefMax);

			if (bfullsize) IMGUI_SUGAR__WIDGETS_POP_WIDTH;
			ImGui::PopID();
			return true;
		}
		if (bfullsize) IMGUI_SUGAR__WIDGETS_POP_WIDTH;
		ImGui::PopID();
		return false;
	}

	// Int
	//--------------------------------------------------------------
	inline static bool AddRangeParam(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, const char* display_format = "%d   %d", int power = 1, ImVec2 shape = ImVec2(-1, -1), bool bfullsize = false)
	{
		float tmpRefMin = parameterMin.get();
		float tmpRefMax = parameterMax.get();

		if (bfullsize) IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
		ImGui::PushID(name.c_str());

		if (RangeSliderFloat(name.c_str(), &tmpRefMin, &tmpRefMax, parameterMin.getMin(), parameterMax.getMax(), display_format, power))
		{
			parameterMin.set(tmpRefMin);
			parameterMax.set(tmpRefMax);

			if (bfullsize) IMGUI_SUGAR__WIDGETS_POP_WIDTH;
			ImGui::PopID();
			return true;
		}
		if (bfullsize) IMGUI_SUGAR__WIDGETS_POP_WIDTH;
		ImGui::PopID();
		return false;
	}

	//----

	// Widgets to pass a referenced vec2/3/4 and edit/modify the 
	// min max range of one of the coords (0-1-2 / x-y-z)
	// selected by the dim argument

	//// Snippet
	//ofxImGuiSurfing::AddRangeOneVec3Param("Range", pos1, valueMin, valueMax, value, coord.get());


	//--------------------------------------------------------------
	inline static bool AddRangeOneVec2Param(const std::string& name, ofParameter<glm::vec2> vecTarget, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, ofParameter<float>& parameterCtrl, int dimTar = 0, const char* display_format = "%.3f  %.3f", float power = 1.0f)
	{
		string n = name;
		switch (dimTar) {
		case 0: n += "X"; break;
		case 1: n += "Y"; break;
		}

		switch (dimTar) { // modify the selected dim
		case 0: vecTarget.set(glm::vec2(parameterCtrl.get(), vecTarget.get().y)); break;
		case 1: vecTarget.set(glm::vec2(vecTarget.get().x, parameterCtrl.get())); break;
		}

		bool changed = false;
		if (AddRangeParam(n, parameterMin, parameterMax))
		{
			changed = true;
		}
		return changed;
	}

	//--------------------------------------------------------------
	inline static bool AddRangeOneVec3Param(const std::string& name, ofParameter<glm::vec3> vecTarget, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, ofParameter<float>& parameterCtrl, int dimTar = 0, const char* display_format = "%.3f  %.3f", float power = 1.0f)
	{
		string n = name;
		switch (dimTar) {
		case 0: n += " X"; break;
		case 1: n += " Y"; break;
		case 2: n += " Z"; break;
		case 3: n += " W"; break;
		}

		switch (dimTar) { // modify the selected dim
		case 0: vecTarget.set(glm::vec3(parameterCtrl.get(), vecTarget.get().y, vecTarget.get().z)); break;
		case 1: vecTarget.set(glm::vec3(vecTarget.get().x, parameterCtrl.get(), vecTarget.get().z)); break;
		case 2: vecTarget.set(glm::vec3(vecTarget.get().x, vecTarget.get().y, parameterCtrl.get())); break;
		}

		bool changed = false;
		if (AddRangeParam(n, parameterMin, parameterMax))
		{
			changed = true;
		}
		return changed;
	}

	//--------------------------------------------------------------
	inline static bool AddRangeOneVec4Param(const std::string& name, ofParameter<glm::vec4> vecTarget, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, ofParameter<float>& parameterCtrl, int dimTar = 0, const char* display_format = "%.3f  %.3f", float power = 1.0f)
	{
		string n = name;
		switch (dimTar) {
		case 0: n += "X"; break;
		case 1: n += "Y"; break;
		case 2: n += "Z"; break;
		case 3: n += "W"; break;
		}

		switch (dimTar) { // modify the selected dim
		case 0: vecTarget.set(glm::vec4(parameterCtrl.get(), vecTarget.get().y, vecTarget.get().z, vecTarget.get().w)); break;
		case 1: vecTarget.set(glm::vec4(vecTarget.get().x, parameterCtrl.get(), vecTarget.get().z, vecTarget.get().w)); break;
		case 2: vecTarget.set(glm::vec4(vecTarget.get().x, vecTarget.get().y, parameterCtrl.get(), vecTarget.get().w)); break;
		case 3: vecTarget.set(glm::vec4(vecTarget.get().x, vecTarget.get().y, vecTarget.get().z, parameterCtrl.get())); break;
		}

		bool changed = false;
		if (AddRangeParam(n, parameterMin, parameterMax))
		{
			changed = true;
		}
		return changed;
	}


	//----


	/*

	//TODO:
	// Range spreaded

//#include "dear_widgets.h"
//#include "dear_widgets.cpp"

	//static inline bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, float power) { return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, power); }
	//bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
	//{
	//	return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
	//}

	//// Note: p_data, p_min and p_max are _pointers_ to a memory address holding the data. For a slider, they are all required.
	//// Read code of e.g. SliderFloat(), SliderInt() etc. or examples in 'Demo->Widgets->Data Types' to understand how to use this function directly.
	//bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
	//{
	//	ImGuiWindow* window = GetCurrentWindow();
	//	if (window->SkipItems)
	//		return false;

	//	ImGuiContext& g = *GImGui;
	//	const ImGuiStyle& style = g.Style;
	//	const ImGuiID id = window->GetID(label);
	//	const float w = CalcItemWidth();

	//	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	//	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f));
	//	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

	//	ItemSize(total_bb, style.FramePadding.y);
	//	if (!ItemAdd(total_bb, id, &frame_bb))
	//		return false;

	//	// Default format string when passing NULL
	//	if (format == NULL)
	//		format = DataTypeGetInfo(data_type)->PrintFmt;
	//	//else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0) // (FIXME-LEGACY: Patch old "%.0f" format string to use "%d", read function more details.)
	//	//	format = PatchFormatStringFloatToInt(format);//? not found

	//	// Tabbing or CTRL-clicking on Slider turns it into an input box
	//	const bool hovered = ItemHoverable(frame_bb, id);
	//	const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
	//	bool temp_input_is_active = temp_input_allowed && TempInputIsActive(id);
	//	if (!temp_input_is_active)
	//	{
	//		const bool focus_requested = temp_input_allowed && FocusableItemRegister(window, id);
	//		const bool clicked = (hovered && g.IO.MouseClicked[0]);
	//		if (focus_requested || clicked || g.NavActivateId == id || g.NavInputId == id)
	//		{
	//			SetActiveID(id, window);
	//			SetFocusID(id, window);
	//			FocusWindow(window);
	//			g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
	//			if (temp_input_allowed && (focus_requested || (clicked && g.IO.KeyCtrl) || g.NavInputId == id))
	//			{
	//				temp_input_is_active = true;
	//				FocusableItemUnregister(window);
	//			}
	//		}
	//	}

	//	if (temp_input_is_active)
	//	{
	//		// Only clamp CTRL+Click input when ImGuiSliderFlags_AlwaysClamp is set
	//		const bool is_clamp_input = (flags & ImGuiSliderFlags_AlwaysClamp) != 0;
	//		return TempInputScalar(frame_bb, id, label, data_type, p_data, format, is_clamp_input ? p_min : NULL, is_clamp_input ? p_max : NULL);
	//	}

	//	// Draw frame
	//	const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	//	RenderNavHighlight(frame_bb, id);
	//	RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, g.Style.FrameRounding);

	//	// Slider behavior
	//	ImRect grab_bb;
	//	const bool value_changed = SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);
	//	if (value_changed)
	//		MarkItemEdited(id);

	//	// Render grab
	//	if (grab_bb.Max.x > grab_bb.Min.x)
	//		window->DrawList->AddRectFilled(grab_bb.Min, grab_bb.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

	//	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	//	char value_buf[64];
	//	const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);
	//	if (g.LogEnabled)
	//		LogSetNextTextDecoration("{", "}");
	//	RenderTextClipped(frame_bb.Min, frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.5f));

	//	if (label_size.x > 0.0f)
	//		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

	//	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
	//	return value_changed;
	//}

	*/








	//-----------
/*
//    // 2. Timeline
//    // Snippet
//    static float v[]{0,1};
//    static float v1 = 0.25;
//    static float v2 = 0.75;
//    ImGui::BeginTimeline("timeline", 2);
//    ImGui::TimelineEvent("one", &v1);
//    ImGui::TimelineEvent("two", &v2);
//    //    ImGui::TimelineEvent("three", &v3);
//    //    ImGui::TimelineEvent("four", &v4);
//    ImGui::EndTimeline();
//
//    // time line style
//    //https://github.com/nem0/LumixEngine/blob/timeline_gui/external/imgui/imgui_user.inl#L814
//
//    static const float TIMELINE_RADIUS = 6;
//    static float s_max_timeline_value;
//
//    static bool BeginTimeline(const char* str_id, float max_value)
//    {
//        s_max_timeline_value = max_value;
//        return BeginChild(str_id);
//    }
//
//    static bool TimelineEvent(const char* str_id, float* values)
//    {
//        ImGuiWindow* win = GetCurrentWindow();
//        const ImU32 inactive_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
//        const ImU32 active_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonHovered]);
//        const ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonActive]);
//        bool changed = false;
//        ImVec2 cursor_pos = win->DC.CursorPos;
//
//        for (int i = 0; i < 2; ++i)
//        {
//            ImVec2 pos = cursor_pos;
//            pos.x += win->Size.x * values[i] / s_max_timeline_value + TIMELINE_RADIUS;
//            pos.y += TIMELINE_RADIUS;
//
//            SetCursorScreenPos(pos - ImVec2(TIMELINE_RADIUS, TIMELINE_RADIUS));
//            PushID(i);
//            InvisibleButton(str_id, ImVec2(2 * TIMELINE_RADIUS, 2 * TIMELINE_RADIUS));
//            if (IsItemActive() || IsItemHovered())
//            {
//                ImGui::SetTooltip("%f", values[i]);
//                ImVec2 a(pos.x, GetWindowContentRegionMin().y + win->Pos.y);
//                ImVec2 b(pos.x, GetWindowContentRegionMax().y + win->Pos.y);
//                win->DrawList->AddLine(a, b, line_color);
//            }
//            if (IsItemActive() && IsMouseDragging(0))
//            {
//                values[i] += GetIO().MouseDelta.x / win->Size.x * s_max_timeline_value;
//                changed = true;
//            }
//            PopID();
//            win->DrawList->AddCircleFilled(
//                                           pos, TIMELINE_RADIUS, IsItemActive() || IsItemHovered() ? active_color : inactive_color);
//        }
//
//        ImVec2 start = cursor_pos;
//        start.x += win->Size.x * values[0] / s_max_timeline_value + 2 * TIMELINE_RADIUS;
//        start.y += TIMELINE_RADIUS * 0.5f;
//        ImVec2 end = start + ImVec2(win->Size.x * (values[1] - values[0]) / s_max_timeline_value - 2 * TIMELINE_RADIUS,
//                                    TIMELINE_RADIUS);
//
//        PushID(-1);
//        SetCursorScreenPos(start);
//        InvisibleButton(str_id, end - start);
//        if (IsItemActive() && IsMouseDragging(0))
//        {
//            values[0] += GetIO().MouseDelta.x / win->Size.x * s_max_timeline_value;
//            values[1] += GetIO().MouseDelta.x / win->Size.x * s_max_timeline_value;
//            changed = true;
//        }
//        PopID();
//
//        SetCursorScreenPos(cursor_pos + ImVec2(0, GetTextLineHeightWithSpacing()));
//
//        win->DrawList->AddRectFilled(start, end, IsItemActive() || IsItemHovered() ? active_color : inactive_color);
//
//        if (values[0] > values[1])
//        {
//            float tmp = values[0];
//            values[0] = values[1];
//            values[1] = tmp;
//        }
//        if (values[1] > s_max_timeline_value) values[1] = s_max_timeline_value;
//        if (values[0] < 0) values[0] = 0;
//        return changed;
//    }
//
//    static void EndTimeline()
//    {
//        ImGuiWindow* win = GetCurrentWindow();
//
//        ImU32 color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
//        ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Border]);
//        ImU32 text_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Text]);
//        float rounding = GImGui->Style.ScrollbarRounding;
//        ImVec2 start(GetWindowContentRegionMin().x + win->Pos.x,
//                     GetWindowContentRegionMax().y - GetTextLineHeightWithSpacing() + win->Pos.y);
//        ImVec2 end = GetWindowContentRegionMax() + win->Pos;
//
//        win->DrawList->AddRectFilled(start, end, color, rounding);
//
//        const int LINE_COUNT = 5;
//        const ImVec2 text_offset(0, GetTextLineHeightWithSpacing());
//        for (int i = 0; i < LINE_COUNT; ++i)
//        {
//            ImVec2 a = GetWindowContentRegionMin() + win->Pos + ImVec2(TIMELINE_RADIUS, 0);
//            a.x += i * GetWindowContentRegionWidth() / LINE_COUNT;
//            ImVec2 b = a;
//            b.y = start.y;
//            win->DrawList->AddLine(a, b, line_color);
//            char tmp[256];
//            ImFormatString(tmp, sizeof(tmp), "%.2f", i * s_max_timeline_value / LINE_COUNT);
//            win->DrawList->AddText(b, text_color, tmp);
//        }
//
//        EndChild();
//    }
*/

} // namespace ImGui



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