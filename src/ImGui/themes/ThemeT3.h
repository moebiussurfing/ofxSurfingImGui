#pragma once

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

namespace ofxImGuiSurfing
{
	inline void ImGui_ThemeT3()
	{
		ofLogNotice(__FUNCTION__);

		auto mult = [](const ImVec4& vec, const float value) {
			return ImVec4{ vec.x * value, vec.y * value, vec.z * value, vec.w };
		};

		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		//----

		ImVec4 Rgba;
		ImVec4 Transparent = ImVec4(1.f, 1.f, 1.f, 0.f);
		ImVec4 TransparentBlack = ImVec4(0.f, 0.f, 0.f, 0.f);
		ImVec4 White = ImVec4(1.f, 1.f, 1.f, 1.f);
		ImVec4 Gray = ImVec4(0.6f, 0.6f, 0.6f, 1);
		ImVec4 DarkGray = ImVec4(0.3f, 0.3f, 0.3f, 1);
		ImVec4 Black = ImVec4(0, 0, 0, 1.f);
		ImVec4 Red = ImVec4(1.f, 0.2f, 0.2f, 1.f);
		ImVec4 Green = ImVec4(0.2f, 0.9f, 0.2f, 1.f);
		ImVec4 Blue = ImVec4(0.4f, 0.5f, 1.f, 1);
		ImVec4 Orange = ImVec4(1.f, 0.46f, 0.f, 1.f);

		ImVec4 ConnectedParameterColor = ImVec4(0.6f, 0.6f, 1.f, 1.f);
		ImVec4 ValueLabelColor = ImVec4(1, 1, 1, 0.5f);
		ImVec4 ValueLabelColorHover = ImVec4(1, 1, 1, 1.2f);

		ImVec4 GraphLineColor = ImVec4(1, 1, 1, 0.3f);
		ImVec4 GraphLineColorHover = ImVec4(1, 1, 1, 0.7f);

		ImVec4 GraphAxisColor = ImVec4(0, 0, 0, 0.3f);

		ImVec4 ButtonColor = ImVec4(0.15f, 0.15f, 0.15f, 1.f);
		ImVec4 ButtonHoverColor = ImVec4(43, 65, 80, 255);
		ImVec4 TextMuted = ImVec4(0.5f, 0.5f, 0.5f, 0.5f);
		ImVec4 TextDisabled = ImVec4(0.328f, 0.328f, 0.328f, 1.000f);
		ImVec4 WarningColor = ImVec4(203, 19, 113, 255);

		ImVec4 WindowBackground = ImVec4(0.05f, 0.05f, 0.05f, 1);

		ImVec4 FragmentLineColor = Orange;

		float ToolBarHeight = 25;

		colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 0.85f);
		colors[ImGuiCol_TextDisabled] = TextDisabled;
		colors[ImGuiCol_Button] = ButtonColor;
		colors[ImGuiCol_ButtonHovered] = ButtonHoverColor;
		colors[ImGuiCol_Border] = ImVec4(0, 0.00f, 0.00f, 0.97f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.80f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.55f, 0.8f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 0.33f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.25f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.98f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.1f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

		ImVec2 Zero = ImVec2(0, 0);
		ImVec2 ItemSpacing = ImVec2(1, 1);
		ImVec2 FramePadding = ImVec2(7, 4);
		ImVec2 ItemInnerSpacing = ImVec2(3, 2);
		ImVec2 WindowPadding = Zero;

		float GrabMinSize = 2;
		float FrameBorderSize = 0;
		float WindowRounding = 0;
		float ChildRounding = 0;
		float ScrollbarRounding = 2;
		float FrameRounding = 0.f;

		style.WindowPadding = WindowPadding;
		style.FramePadding = FramePadding;
		style.ItemSpacing = ItemSpacing;
		style.ItemInnerSpacing = ItemInnerSpacing;
		style.GrabMinSize = GrabMinSize;
		style.FrameBorderSize = FrameBorderSize;
		style.WindowRounding = WindowRounding;
		style.ChildRounding = ChildRounding;
		style.ScrollbarRounding = ScrollbarRounding;
		style.FrameRounding = FrameRounding;
		style.DisplayWindowPadding = Zero;
		style.DisplaySafeAreaPadding = Zero;
		style.ChildBorderSize = 0;

		//----

		/*
		//ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6.0f, -1.0f));
		//ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(2.0f, 3.0f));
		//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 1.0f));
		//ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));
		//ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 0.0f);
		//ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 0.0f);
		//ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 0.0f);

		//colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		//colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		//colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		//colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		//colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		//colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
		//colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		//colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
		//colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
		//colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
		//colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		//colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		//colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		//colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		//colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		//colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		//colors[ImGuiCol_TitleBgActive] = ImVec4(0.211f, 0.276f, 0.318f, 1.000f);
		//colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
		//colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
		//colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
		//colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		//colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
		//colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
		//colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
		//colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
		//colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
		//colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
		//colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
		//colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
		//colors[ImGuiCol_Header] = colors[ImGuiCol_TitleBg];
		//colors[ImGuiCol_HeaderHovered] = ImVec4(0.250f, 0.400f, 0.500f, 1.000f);
		//colors[ImGuiCol_HeaderActive] = mult(colors[ImGuiCol_HeaderHovered], 0.9f);
		//colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
		//colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
		//colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
		//colors[ImGuiCol_ResizeGrip] = colors[ImGuiCol_Header];
		//colors[ImGuiCol_ResizeGripHovered] = mult(colors[ImGuiCol_Header], 1.4f);
		//colors[ImGuiCol_ResizeGripActive] = mult(colors[ImGuiCol_Header], 1.6f);
		//colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		//colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		//colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		//colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		//colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
		//colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		//colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		//colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		//colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		//colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

		////ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
		////ImGui::GetIO().ConfigWindowsResizeFromEdges = true;
		////ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		////ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		////ImGui::GetIO().ConfigDockingWithShift = true;
		////// Default is 6, which leaves a lag between dragging and actually having an effect.
		////ImGui::GetIO().MouseDragThreshold = 0.0f;
		////style.AntiAliasedLines = true;
		////style.WindowMenuButtonPosition = ImGuiDir_Right;

		//style.PopupRounding = 3;

		//style.WindowPadding = ImVec2(4, 4);
		//style.FramePadding = ImVec2(6, 4);
		//style.ItemSpacing = ImVec2(6, 2);

		//style.ScrollbarSize = 18;

		//style.WindowBorderSize = 1;
		//style.ChildBorderSize = 1;
		//style.PopupBorderSize = 1;
		//style.FrameBorderSize = 1;

		//style.WindowRounding = 3;
		//style.ChildRounding = 3;
		//style.FrameRounding = 0;
		//style.ScrollbarRounding = 2;
		//style.GrabRounding = 0;

		//style.TabBorderSize = 0;
		//style.TabRounding = 3;

		//colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		//colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

		//style.WindowRounding = 0.0f;
		//style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		*/
	}
}