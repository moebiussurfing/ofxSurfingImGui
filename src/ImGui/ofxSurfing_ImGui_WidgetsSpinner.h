// Taken from
// https://github.com/ocornut/imgui/issues/1901#issuecomment-552185000
// by moebiusSurfing

//--

//TODO:
// + add ofParameter 

//----


//-------

//https://github.com/ocornut/imgui/issues/1901

#include "imgui.h"
#include "imgui_internal.h"
#include <functional>

namespace ImGui {

	//--------------------------------------------------------------
	inline bool BufferingBar(const char* label, float value, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = size_arg;
		size.x -= style.FramePadding.x * 2;

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ItemSize(bb, style.FramePadding.y);
		if (!ItemAdd(bb, id))
			return false;

		// Render
		const float circleStart = size.x * 0.7f;
		const float circleEnd = size.x;
		const float circleWidth = circleEnd - circleStart;

		window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
		window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), fg_col);

		const float t = g.Time;
		const float r = size.y / 2;
		const float speed = 1.5f;

		const float a = speed * 0;
		const float b = speed * 0.333f;
		const float c = speed * 0.666f;

		const float o1 = (circleWidth + r) * (t + a - speed * (int)((t + a) / speed)) / speed;
		const float o2 = (circleWidth + r) * (t + b - speed * (int)((t + b) / speed)) / speed;
		const float o3 = (circleWidth + r) * (t + c - speed * (int)((t + c) / speed)) / speed;

		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, bg_col);
		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, bg_col);
		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, bg_col);
	}

	//--------------------------------------------------------------
	inline bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ItemSize(bb, style.FramePadding.y);
		if (!ItemAdd(bb, id))
			return false;

		// Render
		window->DrawList->PathClear();

		int num_segments = 30;
		int start = abs(ImSin(g.Time*1.8f)*(num_segments - 5));

		const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
		const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

		const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

		for (int i = 0; i < num_segments; i++) {
			const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
			window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
				centre.y + ImSin(a + g.Time * 8) * radius));
		}

		window->DrawList->PathStroke(color, false, thickness);
	}

	//----

	// https://github.com/ocornut/imgui/issues/1901#issuecomment-444929973

	//--------------------------------------------------------------
	inline void LoadingIndicatorCircle(const char* label, const float indicator_radius,
		const ImVec4& main_color, const ImVec4& backdrop_color,
		const int circle_count, const float speed) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems) {
			return;
		}

		ImGuiContext& g = *GImGui;
		const ImGuiID id = window->GetID(label);

		const ImGuiStyle& style = g.Style;

		const ImVec2 pos = window->DC.CursorPos;
		const float circle_radius = indicator_radius / 10.0f;
		const ImRect bb(pos, ImVec2(pos.x + indicator_radius * 2.0f,
			pos.y + indicator_radius * 2.0f));
		ItemSize(bb, style.FramePadding.y);
		if (!ItemAdd(bb, id)) {
			return;
		}
		const float t = g.Time;
		const auto degree_offset = 2.0f * IM_PI / circle_count;
		for (int i = 0; i < circle_count; ++i) {
			const auto x = indicator_radius * std::sin(degree_offset * i);
			const auto y = indicator_radius * std::cos(degree_offset * i);
			const auto growth = std::max(0.0f, std::sin(t * speed - i * degree_offset));
			ImVec4 color;
			color.x = main_color.x * growth + backdrop_color.x * (1.0f - growth);
			color.y = main_color.y * growth + backdrop_color.y * (1.0f - growth);
			color.z = main_color.z * growth + backdrop_color.z * (1.0f - growth);
			color.w = 1.0f;
			window->DrawList->AddCircleFilled(ImVec2(pos.x + indicator_radius + x,
				pos.y + indicator_radius - y),
				circle_radius + growth * circle_radius,
				GetColorU32(color));
		}
	}

	//--

	// A circle arc that can be controlled from 0 to 1
	// TEST:
	//const char* label = "label";
	//static float control;
	//static float radius = 40;
	//static int thickness = 20;
	//ImGui::SliderFloat("control", &control, 0, 1);
	//ImGui::SliderFloat("radius", &radius, 10, 200);
	//ImGui::SliderInt("thickness", &thickness, 0, 40);
	//ofColor _color = ofColor(128, 200);
	//static ImU32 color = ImGui::ColorConvertFloat4ToU32(_color);
	//circleCycled(label, &control);
	//circleCycled(label, &control, radius, false, thickness, color, 20);
	//--------------------------------------------------------------
	inline void circleCycled(const char* label, float *control, const float radius = 20, const bool filled = true, const int thickness = 10, const ImU32 color = IM_COL32(255, 255, 255, 200), int num_segments = 20)
	{
		static float startf = 0.0f;
		static float endf = IM_PI * 2.0f;
		static float offsetf = -IM_PI / 2.0f;
		//static int num_segments = 40;

		//float _thickness = ofMap(thickness, 0, 1, 0, radius / 2.0f);
		float _radius;
		float _thickness = thickness;

		if (filled)	{
			_radius = radius - _thickness;
			_thickness = radius / 2.0f;
		}
		else {
			_radius = (radius - _thickness) / 2.0f;
		}

		ImGui::SliderInt("num_segments", &num_segments, 0, 100);
		//ImGui::SliderFloat("offsetf", &offsetf, 0, IM_PI * 2.0f);
		//ImGui::SliderFloat("startf", &startf, 0, IM_PI * 2.0f);
		//ImGui::SliderFloat("endf", &endf, 0, IM_PI * 2.0f);

		ImGuiWindow* window = GetCurrentWindow();
		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;

		ImVec2 size(
			(radius) * 2 + style.FramePadding.x,
			(radius + style.FramePadding.y) * 2);

		const ImRect bb(pos, ImVec2(
			pos.x + size.x,
			pos.y + size.y));

		ItemSize(bb, style.FramePadding.y);
		if (!ItemAdd(bb, id)) {
			return;
		}

		// Render
		window->DrawList->PathClear();

		const ImVec2 centre = ImVec2(
			pos.x + radius + style.FramePadding.x,
			pos.y + radius + style.FramePadding.y);

		window->DrawList->PathArcTo(centre, _radius, startf + offsetf, *control * endf + offsetf, num_segments);

		window->DrawList->PathStroke(color, ImDrawFlags_RoundCornersAll, _thickness);
	}

}


/*


// https://github.com/ocornut/imgui/issues/1901#issuecomment-552185000
#include "cubic_bezier.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <functional>

static gfx::CubicBezier fast_out_slow_in(0.4, 0.0, 0.2, 1.0);

static float bezier(float t) {
	return fast_out_slow_in.Solve(t);
}

namespace ImGui {
	constexpr
		static auto lerp(float x0, float x1) {
		return [=](float t) {
			return (1 - t) * x0 + t * x1;
		};
	}

	constexpr
		static float lerp(float x0, float x1, float t) {
		return lerp(x0, x1)(t);
	}

	static auto interval(float T0, float T1, std::function<float(float)> tween = lerp(0.0, 1.0)) {
		return [=](float t) {
			return t < T0 ? 0.0f : t > T1 ? 1.0f : tween((t - T0) / (T1 - T0));
		};
	}

	template <int T>
	float sawtooth(float t) {
		return ImFmod(((float)T)*t, 1.0f);
	}

	bool Spinner2(const char* label, float radius, int thickness, const ImU32& color) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
		ItemSize(bb, style.FramePadding.y);
		if (!ItemAdd(bb, id))
			return false;

		// Render
		const ImVec2 center = ImVec2(pos.x + radius, pos.y + radius + thickness + style.FramePadding.y);

		const float start_angle = -IM_PI / 2.0f;         // Start at the top
		const int num_detents = 5;                       // how many rotations we want before a repeat
		const int skip_detents = 3;                      // how many steps we skip each rotation
		const float period = 5.0f;                       // in seconds
		const float t = ImFmod(g.Time, period) / period; // map period into [0, 1]

		// Tweening functions for each part of the spinner
		auto stroke_head_tween = [](float t) {
			t = sawtooth<num_detents>(t);
			return interval(0.0, 0.5, bezier)(t);
		};

		auto stroke_tail_tween = [](float t) {
			t = sawtooth<num_detents>(t);
			return interval(0.5, 1.0, bezier)(t);
		};

		auto step_tween = [=](float t) {
			return floor(lerp(0.0, (float)num_detents, t));
		};

		auto rotation_tween = sawtooth<num_detents>;

		const float head_value = stroke_head_tween(t);
		const float tail_value = stroke_tail_tween(t);
		const float step_value = step_tween(t);
		const float rotation_value = rotation_tween(t);

		const float min_arc = 30.0f / 360.0f * 2.0f * IM_PI;
		const float max_arc = 270.0f / 360.0f * 2.0f * IM_PI;
		const float step_offset = skip_detents * 2.0f * IM_PI / num_detents;
		const float rotation_compensation = ImFmod(4.0*IM_PI - step_offset - max_arc, 2 * IM_PI);

		const float a_min = start_angle + tail_value * max_arc + rotation_value * rotation_compensation - step_value * step_offset;
		const float a_max = a_min + (head_value - tail_value) * max_arc + min_arc;

		window->DrawList->PathClear();

		int num_segments = 24;
		for (int i = 0; i < num_segments; i++) {
			const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
			window->DrawList->PathLineTo(ImVec2(center.x + ImCos(a) * radius,
				center.y + ImSin(a) * radius));
		}

		window->DrawList->PathStroke(color, false, thickness);

		return true;
	}

}
*/