#include "ImGuiRangeSlider.h"
#include <sstream>
namespace ImGui
{
	
	static float bar_width = 3;

	template <typename T>
	void clip(T& n, const T& lower, const T& upper) {
		n= std::max(lower, std::min(n, upper));
	}

	template <class t>
	bool drawGrabber(const char* id, ImVec2 &pos, t& input, const t& min, const t& max, float width, float height, int idnum)
	{
		ImGuiWindow* win = GetCurrentWindow();
		const ImU32 inactive_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_SliderGrab]);
		const ImU32 active_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_SliderGrabActive]);
		
		float scale = max / width;
		bool changed = false;
		bool hovered = false;
		int current_draw_bar = input / scale;
		static float previous_delta;
		hovered = false;
		SetCursorScreenPos({ pos.x + current_draw_bar /*- (width / max)*/, pos.y });
		std::string nid = id + std::to_string(idnum);
		PushID(nid.c_str());
		ImGui::InvisibleButton(nid.c_str(), { bar_width, height });
		if (IsItemActive() || IsItemHovered())
		{
			ImGui::SetTooltip(std::to_string(input).c_str());
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		}
		if (IsItemActive() && IsMouseDragging(0))
		{
			input += (GetIO().MousePos.x - (pos.x + current_draw_bar)) * scale;
			clip(input, min, max);
			changed = hovered = true;
		}
		win->DrawList->AddRectFilled({ pos.x + current_draw_bar, pos.y }, { pos.x + current_draw_bar + bar_width, pos.y + height }, IsItemActive() || IsItemHovered() || hovered ? active_color : inactive_color);
		PopID();
		return changed;
	}


	template <class t>
	bool RangeSlider(const char* id, const t& min, const t& max, t& low, t& high)
	{
		const ImU32 line_color = ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_Button]);
		ImGuiWindow* win = GetCurrentWindow();
		ImGuiContext& g = *GImGui;
		ImGuiStyle& style = g.Style;
		const float button_size = GetFrameHeight();
		float width = CalcItemWidth() - (button_size + style.ItemInnerSpacing.x) * 2;
		float height = ImGui::GetTextLineHeightWithSpacing();
		bool changed = false;
		SetNextItemWidth(ImMax(1.0f, width));
		ImVec2 pos = win->DC.CursorPos;
		ImVec2 end = { pos.x+width, pos.y + height };
		float scale = (max / width);
		win->DrawList->AddRectFilled(pos, end, ColorConvertFloat4ToU32(GImGui->Style.Colors[ImGuiCol_FrameBg]));
		win->DrawList->AddRectFilled({ pos.x + low /  scale, pos.y }, { pos.x + high / scale, pos.y + height }, line_color); //bar between the 2 grabbers
		if (drawGrabber(id, pos, low, min, max, width, height, 0))
			changed = true;
		if (drawGrabber(id, pos, high, min, max, width, height, 1))
			changed = true;
		if (low >= high)
			std::swap(low, high);
		SetCursorScreenPos({ pos.x + width + style.ItemInnerSpacing.x,pos.y-1 });
		return changed;
	}
	bool RangeSliderInt(const char* id, const int& min, const int& max, int& low, int& high)
	{
		bool r = RangeSlider<int>(id, min, max, low, high);
		ImGui::SetNextItemWidth(40);
		if (ImGui::InputInt("##Val1", &low, 0))
			r = true;
		ImGui::SameLine(0);
		ImGui::SetNextItemWidth(40);
		if (ImGui::InputInt("##Val2", &high, 0))
			r = true;
		clip(low, min, max);
		clip(high, min, max);
		return r;
	}
	
	bool RangeSliderFloat(const char* id, const float& min, const float& max, float& low, float& high)
	{
		bool r =  RangeSlider<float>(id, min, max, low, high);
		ImGui::SetNextItemWidth(60);
		if (ImGui::InputFloat("##Val1", &low, 0))
			r = true;
		ImGui::SameLine(0);
		ImGui::SetNextItemWidth(60);
		if (ImGui::InputFloat("##Val2", &high, 0))
			clip(high, min, max);

		clip(low, min, max);
		clip(high, min, max);
		return r;
	}
}
