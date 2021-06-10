
#include "ofxSurfing_ImGui_WidgetsExtra.h"

namespace ImGuiEx {
	static inline bool Pad2D(ImDrawList* drawList, float width, float height, float *_x, float *_y) {

		// visuals
		enum { LINE_WIDTH = 2 }; // handlers: small lines width
		enum { GRAB_RADIUS = 6 }; // handlers: circle radius

		ImGuiWindow* Window = ImGui::GetCurrentWindow();

		// prepare canvas
		const float dim = width > 0 ? width : ImGui::GetContentRegionAvailWidth();
		ImVec2 Canvas(dim, height);

		ImRect bb(Window->DC.CursorPos, Window->DC.CursorPos + Canvas);
		ImGui::ItemSize(bb);

		// background grid
		if (Canvas.x >= 4) {
			for (int i = 0; i <= Canvas.x; i += static_cast<int>((Canvas.x / 4))) {
				drawList->AddLine(
					ImVec2(bb.Min.x + i, bb.Min.y),
					ImVec2(bb.Min.x + i, bb.Max.y - 1),
					IM_COL32(255, 255, 255, 20));
			}
		}

		if (Canvas.y >= 4) {
			for (int i = 0; i <= Canvas.y; i += static_cast<int>((Canvas.y / 4))) {
				drawList->AddLine(
					ImVec2(bb.Min.x, bb.Min.y + i),
					ImVec2(bb.Max.x - 1, bb.Min.y + i),
					IM_COL32(255, 255, 255, 20));
			}
		}

		drawList->AddLine(ImVec2(bb.Min.x + (Canvas.x* *_x), bb.Min.y), ImVec2(bb.Min.x + (Canvas.x* *_x), bb.Max.y - 1), ImGui::GetColorU32(ImGuiCol_TextDisabled), LINE_WIDTH);
		drawList->AddLine(ImVec2(bb.Min.x, bb.Min.y + (Canvas.y* *_y)), ImVec2(bb.Max.x - 1, bb.Min.y + (Canvas.y* *_y)), ImGui::GetColorU32(ImGuiCol_TextDisabled), LINE_WIDTH);


		// DRAG from circle
		bool changed = false;

		ImVec2 prevCursorPos = ImGui::GetCursorScreenPos();

		ImGui::SetCursorScreenPos(ImVec2(bb.Min.x + (Canvas.x* *_x) - 4, bb.Min.y + (Canvas.y* *_y) - 4));
		ImGui::InvisibleButton("circleGripBtn", ImVec2(8, 8));

		static bool isDraggingCircle = false;
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0)) {
			if (!isDraggingCircle) {
				isDraggingCircle = true;
			}

			ImVec2 _pos = ImClamp(ImVec2((ImGui::GetMousePos().x - bb.Min.x) / Canvas.x, (ImGui::GetMousePos().y - bb.Min.y) / Canvas.y), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f));
			*_x = _pos.x;
			*_y = _pos.y;

			changed = true;
		}
		else if (ImGui::IsItemDeactivated()) {
			if (isDraggingCircle) isDraggingCircle = false;
		}

		drawList->AddCircleFilled(ImVec2(bb.Min.x + (Canvas.x* *_x), bb.Min.y + (Canvas.y* *_y)), GRAB_RADIUS, IM_COL32(255, 255, 255, 245), 6);

		ImGui::SetCursorScreenPos(prevCursorPos);

		return changed;

	}

	static inline bool KnobFloat(ImDrawList* draw_list, float width, ImU32 color, const char* label, float* p_value, float v_min, float v_max, float v_step) {
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		float gap = width / 6.0f;
		float radius_outer = width;
		float labelGap = width / 1.15f;
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 center = ImVec2(pos.x + radius_outer + gap, pos.y + labelGap + radius_outer);
		float line_height = ImGui::GetTextLineHeight();

		float ANGLE_MIN = 3.141592f * 0.75f;
		float ANGLE_MAX = 3.141592f * 2.25f;

		ImGui::InvisibleButton(label, ImVec2(radius_outer * 2, radius_outer * 2 + line_height + style.ItemInnerSpacing.y));
		bool value_changed = false;
		bool is_active = ImGui::IsItemActive();
		bool is_hovered = ImGui::IsItemHovered();
		if (is_active && io.MouseDelta.x != 0.0f) {
			if (v_step <= 0) v_step = 50.f;
			float step = (v_max - v_min) / v_step;
			*p_value += io.MouseDelta.x * step;

			if (*p_value < v_min) *p_value = v_min;
			if (*p_value > v_max) *p_value = v_max;
			value_changed = true;
		}
		else if (is_hovered && (io.MouseDoubleClicked[0] || io.MouseClicked[2])) {
			*p_value = (v_max + v_min) * 0.5f;  // reset value
			value_changed = true;
		}

		float t = (*p_value - v_min) / (v_max - v_min);
		if (*p_value >= v_max) {
			t = 1.0f;
		}
		float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
		float angle_cos = cosf(angle), angle_sin = sinf(angle);
		float radius_inner = radius_outer * 0.40f;
		float radius_inner_medium = radius_outer * 0.82f;
		float line_width = width / 5.0f;

		draw_list->AddText(ImVec2(pos.x + gap + (((radius_outer * 2) - ImGui::CalcTextSize(label).x) / 2.0f), pos.y + style.ItemInnerSpacing.y), ImGui::GetColorU32(ImGuiCol_Text), label);

		draw_list->AddCircleFilled(center, radius_outer, IM_COL32(28, 28, 28, 255), 32);

		draw_list->PathArcTo(center, radius_outer - 4, ANGLE_MIN, angle, 32);
		draw_list->PathArcTo(center, radius_inner_medium, angle, ANGLE_MIN, 32);
		draw_list->PathStroke(color, true, line_width);

		draw_list->AddCircleFilled(center, radius_inner, is_active ? ImGui::GetColorU32(ImGuiCol_FrameBgActive) : is_hovered ? ImGui::GetColorU32(ImGuiCol_FrameBgHovered) : IM_COL32(28, 28, 28, 255), 32);
		draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner), ImVec2(center.x + angle_cos * (radius_outer - line_width + 1), center.y + angle_sin * (radius_outer - line_width + 1)), color, line_width);

		char buffer[64];
		snprintf(buffer, sizeof buffer, "%.2f", *p_value);
		draw_list->AddText(ImVec2(pos.x + gap + (((radius_outer * 2) - ImGui::CalcTextSize(buffer).x) / 2.0f), pos.y + labelGap + radius_outer * 2 + style.ItemInnerSpacing.y), ImGui::GetColorU32(ImGuiCol_Text), buffer);

		//tooltip
		if (is_active || is_hovered)
		{
			ImGui::SetNextWindowPos(ImVec2(pos.x + gap - style.WindowPadding.x, pos.y + labelGap + radius_outer));
			ImGui::BeginTooltip();
			ImGui::PushItemWidth(radius_outer*2);
			ImGui::DragFloat("",p_value);
			ImGui::PopItemWidth();
			ImGui::EndTooltip();
		}


		return value_changed;
	}
}