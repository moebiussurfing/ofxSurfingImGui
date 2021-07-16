//
//// https://github.com/ocornut/imgui/issues/76
//// https://github.com/ocornut/imgui/issues/76#issuecomment-287739415
//
//#include "ofxImGui.h"
////#include "imgui.h"
//#include "imgui_internal.h"
//#include "imconfig.h"
//
//using namespace ImGui;
//
////-
//
//// h
////
////namespace ImGuiSurfing {
////
////    bool BeginTimeline2(const char* str_id, float max_time);
////    bool TimelineEvent2(const char* str_id, float times[2]);
////    void EndTimeline2(float current_time = -1);
////
////}
//
//// cpp
//
//// https://github.com/ocornut/imgui/issues/76
//
//namespace ImGuiSurfing {
//
//	static float s_max_timeline_value;
//
//	inline bool BeginTimeline2(const char* str_id, float max_time)
//	{
//		s_max_timeline_value = max_time;
//		return BeginChild(str_id);
//	}
//
//
//	static const float TIMELINE_RADIUS = 6;
//
//
//	inline bool TimelineEvent2(const char* str_id, float values[2])
//	{
//		ImGuiWindow* win = GetCurrentWindow();
//		const ImU32 inactive_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_TextDisabled]);
//		//const ImU32 inactive_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
//		const ImU32 active_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Separator]);
//		//const ImU32 active_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonHovered]);
//		const ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Text]);
//		//const ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_SeparatorActive]);
//		bool changed = false;
//		ImVec2 cursor_pos = win->DC.CursorPos;
//
//		// @r-lyeh {
//		Button(str_id, ImVec2(120, 0)); // @todo: enable/disable track channel here
//		SameLine();
//		cursor_pos = cursor_pos + ImVec2(0, GetTextLineHeightWithSpacing() / 3);
//		//cursor_pos += ImVec2(0, GetTextLineHeightWithSpacing() / 3);
//		// }
//
//		for (int i = 0; i < 2; ++i)
//		{
//			ImVec2 pos = cursor_pos;
//			pos.x += win->Size.x * values[i] / s_max_timeline_value + TIMELINE_RADIUS;
//			pos.y += TIMELINE_RADIUS;
//
//			SetCursorScreenPos(pos - ImVec2(TIMELINE_RADIUS, TIMELINE_RADIUS));
//			PushID(i);
//			InvisibleButton(str_id, ImVec2(2 * TIMELINE_RADIUS, 2 * TIMELINE_RADIUS));
//			if (IsItemActive() || IsItemHovered())
//			{
//				ImGui::SetTooltip("%f", values[i]);
//				ImVec2 a(pos.x, GetWindowContentRegionMin().y + win->Pos.y + win->Scroll.y);
//				ImVec2 b(pos.x, GetWindowContentRegionMax().y + win->Pos.y + win->Scroll.y);
//				win->DrawList->AddLine(a, b, line_color);
//			}
//			if (IsItemActive() && IsMouseDragging(0))
//			{
//				values[i] += GetIO().MouseDelta.x / win->Size.x * s_max_timeline_value;
//				changed = true;
//			}
//			PopID();
//			win->DrawList->AddCircleFilled(
//				pos, TIMELINE_RADIUS, IsItemActive() || IsItemHovered() ? active_color : inactive_color);
//		}
//
//		ImVec2 start = cursor_pos;
//		start.x += win->Size.x * values[0] / s_max_timeline_value + 2 * TIMELINE_RADIUS;
//		start.y += TIMELINE_RADIUS * 0.5f;
//		ImVec2 end = start + ImVec2(win->Size.x * (values[1] - values[0]) / s_max_timeline_value - 2 * TIMELINE_RADIUS,
//			TIMELINE_RADIUS);
//
//		PushID(-1);
//		SetCursorScreenPos(start);
//		InvisibleButton(str_id, end - start);
//		if (IsItemActive() && IsMouseDragging(0))
//		{
//			values[0] += GetIO().MouseDelta.x / win->Size.x * s_max_timeline_value;
//			values[1] += GetIO().MouseDelta.x / win->Size.x * s_max_timeline_value;
//			changed = true;
//		}
//		PopID();
//
//		SetCursorScreenPos(cursor_pos + ImVec2(0, GetTextLineHeightWithSpacing()));
//
//		win->DrawList->AddRectFilled(start, end, IsItemActive() || IsItemHovered() ? active_color : inactive_color);
//
//		if (values[0] > values[1])
//		{
//			float tmp = values[0];
//			values[0] = values[1];
//			values[1] = tmp;
//		}
//		if (values[1] > s_max_timeline_value) values[1] = s_max_timeline_value;
//		if (values[0] < 0) values[0] = 0;
//		return changed;
//	}
//
//	inline void EndTimeline2(float t)
//	{
//		ImGuiWindow* win = GetCurrentWindow();
//
//		// @r-lyeh {
//		if (t >= 0) {
//			if (t > s_max_timeline_value) t = s_max_timeline_value; t /= s_max_timeline_value;
//			const ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_SeparatorActive]);
//			ImVec2 a(win->Pos.x + GetWindowContentRegionMin().x + t * GetWindowContentRegionWidth(), GetWindowContentRegionMin().y + win->Pos.y + win->Scroll.y);
//			ImVec2 b(win->Pos.x + GetWindowContentRegionMin().x + t * GetWindowContentRegionWidth(), GetWindowContentRegionMax().y + win->Pos.y + win->Scroll.y);
//			win->DrawList->AddLine(a, b, line_color);
//		}
//		// }
//
//		ImU32 color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
//		ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Border]);
//		ImU32 text_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Text]);
//		float rounding = GImGui->Style.ScrollbarRounding;
//		ImVec2 start(GetWindowContentRegionMin().x + win->Pos.x,
//			GetWindowContentRegionMax().y - GetTextLineHeightWithSpacing() + win->Pos.y + win->Scroll.y);
//		ImVec2 end = GetWindowContentRegionMax() + win->Pos + ImVec2(0, win->Scroll.y);
//
//		win->DrawList->AddRectFilled(start, end, color, rounding);
//
//		const int LINE_COUNT = 5;
//		const ImVec2 text_offset(0, GetTextLineHeightWithSpacing());
//		for (int i = 0; i <= LINE_COUNT; ++i)
//		{
//			ImVec2 a = GetWindowContentRegionMin() + win->Pos; // @r-lyeh: - ImVec2(TIMELINE_RADIUS, 0);
//			a.x += i * (GetWindowContentRegionWidth() - 1) / LINE_COUNT; // @r-lyeh: -1
//			ImVec2 b = a;
//			b.y = start.y;
//			win->DrawList->AddLine(a, b, line_color);
//			char tmp[256];
//			ImFormatString(tmp, sizeof(tmp), "%.2f", i * s_max_timeline_value / LINE_COUNT);
//			win->DrawList->AddText(b, text_color, tmp);
//		}
//
//		EndChild();
//	}
//
//}


//--------------


// last topic
// https://github.com/ocornut/imgui/issues/76#issuecomment-288304286

#include "ofxImGui.h"
//#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"


#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

#include <functional>

// original source of timeline code is
// https://github.com/nem0/LumixEngine
//
// modified further according to imgui issue 76
// and adding a panzoomer
// https://github.com/ocornut/imgui/issues/76
//

static float s_max_timeline_value = 100.f;
static float s_pixel_offset = 0.f;

static double s_time_in = 0.f;
static double s_time_out = 1.f;

static double s_time_offset = 0;
static double s_time_scale = 1;

namespace ImGui {

	inline bool BeginTimeline(const char* str_id, float pixel_offset, float max_value, int num_visible_rows)
	{
		s_time_scale = 1.0 / (s_time_out - s_time_in);
		s_time_offset = s_time_in * s_time_scale;


		if (num_visible_rows <= 0)
			num_visible_rows = 5;

		ImGuiWindow * win = GetCurrentWindow();

		//float height = win->ContentsRegionRect.Max.y - win->ContentsRegionRect.Min.y
		float height = win->ContentRegionRect.Max.y - win->ContentRegionRect.Min.y
			- ImGui::GetTextLineHeightWithSpacing()   // space for the time bar
			- ImGui::GetTextLineHeightWithSpacing();  // space for horizontal scroller


		bool rv = BeginChild(str_id, ImVec2(0, height), false);

		ImGui::PushStyleColor(ImGuiCol_Separator, GImGui->Style.Colors[ImGuiCol_Border]);
		ImGui::Columns(2, str_id);

		static float _pixel_offset = 0;
		if (pixel_offset != _pixel_offset) {
			_pixel_offset = pixel_offset;
			ImGui::SetColumnOffset(1, pixel_offset);
		}
		s_max_timeline_value = max_value >= 0 ? max_value : (ImGui::GetWindowContentRegionWidth() * 0.85f);
		return rv;
	}


	static const float TIMELINE_RADIUS = 12;


	inline bool TimelineEvent(const char* str_id, double & val1, double & val2)
	{
		double values[2] = { val1, val2 };
		ImGuiWindow* win = GetCurrentWindow();
		//const ImU32 inactive_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
		//const ImU32 active_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonHovered]);
		//const ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_SeparatorActive]);
		const ImU32 inactive_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonActive]);
		const ImU32 active_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Text]);
		const ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_TextDisabled]);
		bool changed = false;
		bool hovered = false;
		bool active = false;

		ImGui::Text("%s", str_id);
		ImGui::NextColumn();

		const float columnOffset = ImGui::GetColumnOffset(1);
		const float columnWidth = ImGui::GetColumnWidth(1) - GImGui->Style.ScrollbarSize;

		ImVec2 cursor_pos(GetWindowContentRegionMin().x + win->Pos.x + columnOffset - TIMELINE_RADIUS, win->DC.CursorPos.y);

		float posx[2] = { 0,0 };

		for (int i = 0; i < 2; ++i)
		{
			ImVec2 pos = cursor_pos;
			pos.x += s_time_scale * columnWidth * float(values[i]) / s_max_timeline_value - columnWidth * s_time_offset + TIMELINE_RADIUS;
			pos.y += TIMELINE_RADIUS;
			posx[i] = pos.x;

			SetCursorScreenPos(pos - ImVec2(TIMELINE_RADIUS, TIMELINE_RADIUS));
			PushID(i);
			InvisibleButton(str_id, ImVec2(2 * TIMELINE_RADIUS, 2 * TIMELINE_RADIUS));
			active = IsItemActive();
			if (active || IsItemHovered())
			{
				ImGui::SetTooltip("%f", float(values[i]));
				ImVec2 a(pos.x, GetWindowContentRegionMin().y + win->Pos.y + win->Scroll.y);

				ImGuiWindow * parent_win = win->ParentWindow;
				float endy = parent_win->ContentRegionRect.Max.y + win->Pos.y; // draw all the way to the bottom of the parent window

				ImVec2 b(pos.x, endy);
				win->DrawList->AddLine(a, b, line_color);
				hovered = true;
			}
			if (IsItemActive() && IsMouseDragging(0))
			{
				values[i] += GetIO().MouseDelta.x / win->Size.x * s_max_timeline_value;
				changed = hovered = true;
			}
			PopID();
			win->DrawList->AddCircleFilled(
				pos, TIMELINE_RADIUS, IsItemActive() || IsItemHovered() ? active_color : inactive_color);
		}

		ImVec2 start = cursor_pos;
		start.x = posx[0];
		start.y += TIMELINE_RADIUS * 0.5f;
		ImVec2 end = start;
		end.x = posx[1];
		end.y += TIMELINE_RADIUS;

		PushID(-1);
		SetCursorScreenPos(start);
		InvisibleButton(str_id, end - start);
		if (IsItemActive() && IsMouseDragging(0))
		{
			values[0] += GetIO().MouseDelta.x / win->Size.x * s_max_timeline_value;
			values[1] += GetIO().MouseDelta.x / win->Size.x * s_max_timeline_value;
			changed = hovered = true;
		}
		PopID();

		SetCursorScreenPos(cursor_pos + ImVec2(0, GetTextLineHeightWithSpacing()));

		win->DrawList->AddRectFilled(start, end, IsItemActive() || IsItemHovered() ? active_color : inactive_color);

		if (values[0] > values[1])
		{
			std::swap(values[0], values[1]);
		}
		if (values[1] > s_max_timeline_value) values[1] = s_max_timeline_value;
		if (values[0] < 0) values[0] = 0;

		if (hovered)
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			//ImGui::SetMouseCursor(ImGuiMouseCursor_Move);

		ImGui::NextColumn();

		val1 = values[0];
		val2 = values[1];

		return changed;
	}


	inline void EndTimeline(int num_vertical_grid_lines, double & time_in, double & time_out)
	{
		ImGui::NextColumn();

		ImGuiWindow* win = GetCurrentWindow();

		const float columnOffset = ImGui::GetColumnOffset(1);
		const float columnWidth = ImGui::GetColumnWidth(1) - GImGui->Style.ScrollbarSize;
		const float horizontal_interval = columnWidth / num_vertical_grid_lines;

		const ImU32 pz_inactive_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
		const ImU32 pz_active_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_ButtonHovered]);
		const ImU32 pz_line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_SeparatorActive]);

		const ImU32 color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
		const ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Border]);
		const ImU32 text_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Text]);
		const float rounding = GImGui->Style.ScrollbarRounding;
		const float startY = ImGui::GetWindowHeight() + win->Pos.y;

		// vertical lines
		for (int i = 0; i <= num_vertical_grid_lines; ++i)
		{
			ImVec2 a = GetWindowContentRegionMin() + win->Pos;
			a.x += s_time_scale * i * horizontal_interval + columnOffset - columnWidth * s_time_offset;
			win->DrawList->AddLine(a, ImVec2(a.x, startY), line_color);
		}

		ImGui::Columns(1);
		ImGui::PopStyleColor();

		EndChild();

		// draw bottom axis ribbon outside scrolling region
		win = GetCurrentWindow();

		float startx = ImGui::GetCursorScreenPos().x + columnOffset;
		float endy = GetWindowContentRegionMax().y + win->Pos.y;
		ImVec2 start(startx, endy - 2 * ImGui::GetTextLineHeightWithSpacing());
		ImVec2 end(startx + columnWidth, endy - ImGui::GetTextLineHeightWithSpacing());
		win->DrawList->AddRectFilled(start, end, color, rounding);

		char tmp[256] = "";
		for (int i = 0; i < num_vertical_grid_lines; ++i)
		{
			ImVec2 a = start;
			a.x = start.x + s_time_scale * i * horizontal_interval - columnWidth * s_time_offset;

			if (a.x < startx)
				continue;

			a.y = start.y;
			ImFormatString(tmp, sizeof(tmp), "%.2f", i * s_max_timeline_value / num_vertical_grid_lines);
			win->DrawList->AddText(a, text_color, tmp);
		}

		// draw time panzoomer

		float posx[2] = { 0,0 };
		double values[2] = { time_in, time_out };

		bool active = false;
		bool hovered = false;
		bool changed = false;
		ImVec2 cursor_pos = { start.x, end.y };

		for (int i = 0; i < 2; ++i)
		{
			ImVec2 pos = cursor_pos;
			pos.x += columnWidth * float(values[i]) + TIMELINE_RADIUS;
			pos.y += TIMELINE_RADIUS;
			posx[i] = pos.x;

			SetCursorScreenPos(pos - ImVec2(TIMELINE_RADIUS, TIMELINE_RADIUS));
			PushID(i);
			InvisibleButton("zoompanner", ImVec2(2 * TIMELINE_RADIUS, 2 * TIMELINE_RADIUS));
			active = IsItemActive();
			if (active || IsItemHovered())
			{
				hovered = true;
			}
			if (IsItemActive() && IsMouseDragging(0))
			{
				values[i] += GetIO().MouseDelta.x / columnWidth;
				changed = hovered = true;
			}
			PopID();

			win->DrawList->AddCircleFilled(
				pos, TIMELINE_RADIUS, IsItemActive() || IsItemHovered() ? pz_active_color : pz_inactive_color);
		}

		if (values[0] > values[1])
			std::swap(values[0], values[1]);

		start.x = posx[0];
		start.y += TIMELINE_RADIUS * 0.5f + ImGui::GetTextLineHeightWithSpacing();
		end.x = posx[1];
		end.y = start.y + TIMELINE_RADIUS;

		PushID(-1);
		SetCursorScreenPos(start);
		InvisibleButton("zoompanner", end - start);
		if (IsItemActive() && IsMouseDragging(0))
		{
			values[0] += GetIO().MouseDelta.x / columnWidth;
			values[1] += GetIO().MouseDelta.x / columnWidth;
			changed = hovered = true;
		}
		PopID();

		win->DrawList->AddRectFilled(start, end, IsItemActive() || IsItemHovered() ? pz_active_color : pz_inactive_color);

		for (int i = 0; i < 2; ++i)
		{
			if (values[i] < 0)
				values[i] = 0;
			if (values[i] > 1)
				values[i] = 1;
		}

		time_in = values[0];
		time_out = values[1];

		s_time_in = time_in;
		s_time_out = time_out;

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2 * ImGui::GetTextLineHeightWithSpacing());
	}


} // ImGui
