#pragma once

// Users Themes
// https://github.com/ocornut/imgui/issues/707

// Some themes from here:
// https://github.com/Raais/ImguiCandy

//--

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

using namespace ImGui;

//------------------------------

namespace ofxImGuiSurfing
{
	//----

	//TODO:
	// WIP
	// fonts management

	//--------------------------------------------------------------
	inline void ImGui_FontCustom() {
		ofLogNotice("ofxSurfingImGui") << (__FUNCTION__);
	}

	//--------------------------------------------------------------
	inline void ImGui_FontCustom(ofxImGui::Gui& gui, ImFont* customFont, string path = "assets/fonts/telegrama_render.otf", float size = 10.f) {
		ofLogNotice("ofxSurfingImGui") << (__FUNCTION__);

		auto& io = ImGui::GetIO();
		auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();
		customFont = gui.addFont(path, size, nullptr, normalCharRanges);
		//if (customFont != nullptr) io.FontDefault = customFont;
	}

	//--------------------------------------------------------------
	inline void setDefaultFont(ofxImGui::Gui& gui, std::string path = "assets/fonts/telegrama_render.otf", int size = 10)
	{
		//if (gui == nullptr) return;
		auto customFont = gui.addFont(path, size, nullptr); // WARNING: will crash if font not present!
		auto& io = ImGui::GetIO();
		if (customFont != nullptr) io.FontDefault = customFont;
	}

	//--------------------------------------------------------------
	//inline void ImGui_FontCustom() {
	//ImGuiIO& io = ImGui::GetIO();
	////float _size = 14.f;
	////string _name = "FiraCodeRegular.ttf";
	////float _size = 13.f;
	////string _name = "overpass-mono-bold.otf";
	//float _size = 10.f;
	//string _name = "telegrama_render.otf";
	//string _path = "assets/fonts/" + _name;//assets folder
	//io.Fonts->AddFontFromFileTTF(&ofToDataPath(_path)[0], _size);
	//}	


	//-------


	// Themes

	//TODO:
	// Testing ImStyle
	// https://github.com/Patitotective/ImStyle
	//--------------------------------------------------------------
	inline void ImGui_ThemeImStyle()
	{
		ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeImStyle";

		// ms style from ImThemes
		ImGuiStyle& style = ImGui::GetStyle();

		style.Alpha = 1.0f;
		style.DisabledAlpha = 1.0f;
		style.WindowPadding = ImVec2(11.10000038146973f, 6.199999809265137f);
		style.WindowRounding = 12.10000038146973f;
		style.WindowBorderSize = 1.0f;
		style.WindowMinSize = ImVec2(20.0f, 4.400000095367432f);
		style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
		style.WindowMenuButtonPosition = ImGuiDir_Left;
		style.ChildRounding = 0.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupRounding = 0.0f;
		style.PopupBorderSize = 1.0f;
		style.FramePadding = ImVec2(20.0f, 20.0f);
		style.FrameRounding = 19.39999961853027f;
		style.FrameBorderSize = 0.0f;
		style.ItemSpacing = ImVec2(20.0f, 4.0f);
		style.ItemInnerSpacing = ImVec2(20.0f, 4.0f);
		style.CellPadding = ImVec2(4.0f, 2.0f);
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 8.0f;
		style.ScrollbarSize = 20.0f;
		style.ScrollbarRounding = 20.0f;
		style.GrabMinSize = 20.0f;
		style.GrabRounding = 20.0f;
		style.TabRounding = 20.0f;
		style.TabBorderSize = 1.0f;
		style.TabMinWidthForCloseButton = 20.0f;
		style.ColorButtonPosition = ImGuiDir_Right;
		style.ButtonTextAlign = ImVec2(0.4000000059604645f, 0.5f);
		style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

		style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 0.999991774559021f, 0.9999899864196777f, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05882352963089943f, 0.05882352963089943f, 0.05882352963089943f, 0.9399999976158142f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9399999976158142f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.1798082292079926f, 0.0f, 0.4721029996871948f, 0.5400000214576721f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.5321369171142578f, 0.0f, 1.0f, 0.4000000059604645f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.6918025016784668f, 0.5751073360443115f, 1.0f, 0.6700000166893005f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1568627506494522f, 0.2862745225429535f, 0.47843137383461f, 1.0f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.5299999713897705f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.2599999904632568f, 0.5899999737739563f, 0.9800000190734863f, 1.0f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.4324520230293274f, 0.1888412237167358f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2599999904632568f, 0.5899999737739563f, 0.9800000190734863f, 1.0f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.4034333229064941f, 0.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 0.9785406589508057f, 0.0f, 1.0f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3100000023841858f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.800000011920929f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 0.7799999713897705f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.2000000029802322f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.6700000166893005f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.949999988079071f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886f, 0.3490196168422699f, 0.5764706134796143f, 0.8619999885559082f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.800000011920929f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.196078434586525f, 0.407843142747879f, 0.6784313917160034f, 1.0f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 0.9724000096321106f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
		style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
		style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
		style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
		style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
		style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
	}

	//--------------------------------------------------------------
	inline void ImGui_ThemeMoebiusSurfingV2() // Must be called after the ofxImGui setup()!
	{
		ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeMoebiusSurfingV2";

		ImGuiStyle* style = &ImGui::GetStyle();

		//--

		// Sizes

		style->ItemInnerSpacing = ImVec2(5, 4);
		style->ItemSpacing = ImVec2(6, 4);
		style->Alpha = 0.97f;
		style->ColumnsMinSpacing = 50;
		style->GrabMinSize = 18;
		style->GrabRounding = 2;
		style->IndentSpacing = 5;

		style->ScrollbarSize = 17.0f;
		style->ScrollbarRounding = 4;
		style->ChildBorderSize = 1.0f;
		style->ChildRounding = 4.0f;

		style->TabRounding = 4;
		style->TabBorderSize = 1;

		style->FrameRounding = 4;
		style->FrameBorderSize = 1;
		style->FramePadding = ImVec2(6, 4);

		style->WindowRounding = 2;
		style->WindowBorderSize = 1;
		style->WindowPadding = ImVec2(10, 10);

		//--

		// Colors

		ImVec4* colors = ImGui::GetStyle().Colors;

		colors[ImGuiCol_Text] = ImVec4(0.76f, 0.76f, 0.76f, 0.94f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.63f, 0.63f, 0.63f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);

		colors[ImGuiCol_WindowBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.96f);
		colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.10f, 0.10f, 0.10f, 0.78f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 0.78f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.94f);

		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.53f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);

		colors[ImGuiCol_CheckMark] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);

		colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.33f, 0.33f, 0.33f, 0.80f);

		colors[ImGuiCol_Button] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		
		colors[ImGuiCol_Header] = ImVec4(0.09f, 0.09f, 0.09f, 0.50f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.00f, 0.00f, 0.4f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.37f, 0.37f, 0.37f, 0.3f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.29f, 0.29f, 0.29f, 0.2f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.44f, 0.44f, 0.44f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.68f, 0.68f, 0.68f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.68f, 0.68f, 0.68f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.90f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.00f, 0.00f, 0.00f, 0.78f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.81f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.78f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.20f, 0.22f, 0.27f, 0.06f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.50f, 0.50f, 0.50f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		//colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		ImVec4 c = colors[ImGuiCol_FrameBg];
		colors[ImGuiCol_ChildBg] = ImVec4(c.x, c.y, c.z, 0.6f);

		//--

		// Docking

		colors[ImGuiCol_DockingPreview] = ImVec4(0.000f, 0.000f, 0.000f, 0.781f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
	}

	//--------------------------------------------------------------
	inline void ImGui_ThemeMoebiusSurfing() // Must be called after the ofxImGui setup()!
	{
		ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeMoebiusSurfing";
		ImGui_ThemeMoebiusSurfingV2();//-> To bypass. Legacy api..
		return;

		//--

		/*
		// Style

		ImGuiStyle* style = &ImGui::GetStyle();

		style->FramePadding = ImVec2(6, 4);
		style->ItemInnerSpacing = ImVec2(5, 4);
		style->ItemSpacing = ImVec2(6, 4);
		style->Alpha = 0.97f;
		style->WindowRounding = 0;
		style->FrameBorderSize = 1;
		style->FrameRounding = 4;
		style->ColumnsMinSpacing = 50;
		style->GrabMinSize = 18;
		style->ScrollbarSize = 14;
		style->ScrollbarRounding = 4;
		style->TabRounding = 4;
		style->WindowRounding = 2;
		style->GrabRounding = 2;
		style->IndentSpacing = 5;

		//-

		// Colors

		ImVec4* colors = ImGui::GetStyle().Colors;

		colors[ImGuiCol_WindowBg] = ImVec4(0.098f, 0.098f, 0.098f, 1.0f);
		// button
		// enabled is lighter
		colors[ImGuiCol_Button] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		//// enabled is darker
		//colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		//colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.80f);
		//colors[ImGuiCol_ButtonHovered] = ImVec4(0.08f, 0.08f, 0.08f, 0.9f);
		// slider
		//colors[ImGuiCol_SliderGrab] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		//colors[ImGuiCol_SliderGrabActive] = ImVec4(0.74f, 0.75f, 0.77f, 0.79f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.20f, 0.20f, 0.20f, 0.9f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.4f, 0.4f, 0.4f, 0.8f);
		// text
		colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.95f);
		//colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
		//colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1f, 0.1f, 0.1f, 0.68f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.12f, 0.11f, 0.11f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.00f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.29f, 0.29f, 0.29f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.44f, 0.44f, 0.44f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.68f, 0.68f, 0.68f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.68f, 0.68f, 0.68f, 0.95f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.81f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.50f, 0.50f, 0.50f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabHovered] = colors[ImGuiCol_WindowBg];
		colors[ImGuiCol_TabActive] = ImVec4(0.2f, 0.2f, 0.2f, 0.9f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2f, 0.2f, 0.2f, 0.9f);

		//-

		// Docking
		colors[ImGuiCol_DockingPreview] = ImVec4(0.000f, 0.000f, 0.000f, 0.781f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
		*/
	}

	//--------------------------------------------------------------
	inline void ImGui_ThemeMoebiusSurfingBlue()
	{
		ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeMoebiusSurfingBlue";

		ImGuiStyle* style = &ImGui::GetStyle();

		ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;

		style->WindowPadding = ImVec2(8, 8);
		style->FramePadding = ImVec2(4, 2);
		style->ItemSpacing = ImVec2(6, 4);
		style->ItemInnerSpacing = ImVec2(6, 4);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 18.0f;
		style->GrabMinSize = 14.0f;
		style->GrabRounding = 3.0f;
		style->WindowBorderSize = 0.0f;
		style->ChildBorderSize = 1.0f;
		style->PopupBorderSize = 1.0f;
		style->FrameBorderSize = 0.0f;
		style->WindowRounding = 4.0f;
		style->ChildRounding = 4.0f;
		style->FrameRounding = 4.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 3.0f;
		style->GrabRounding = 2.0f;

		style->FramePadding = ImVec2(8, 6);

		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);

		style->Colors[ImGuiCol_Border] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);

		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);

		style->Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 100, 200, 255);
		style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 140, 230, 255);

		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);

		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);

		style->Colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);

		style->Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
		style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);

		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.23f, 0.23f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.56f, 0.56f, 0.58f, 0.50f);

		style->Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.23f, 0.23f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 0.50f);

		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.52f, 0.88f, 0.35f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.24f, 0.52f, 0.88f, 0.50f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.24f, 0.52f, 0.88f, 0.67f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.24f, 0.52f, 0.88f, 0.95f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	}

	//--------------------------------------------------------------
	inline void ImGui_ThemeModernDark()
	{
		ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeModernDark";

		auto& style = ImGui::GetStyle();

		style.ChildRounding = 0;
		style.GrabRounding = 0;
		style.FrameRounding = 2;
		style.PopupRounding = 0;
		style.ScrollbarRounding = 0;
		style.TabRounding = 2;
		style.WindowRounding = 0;
		style.FramePadding = { 4, 4 };

		style.WindowTitleAlign = { 0.0, 0.5 };
		style.ColorButtonPosition = ImGuiDir_Left;

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = { 1.0f, 1.0f, 1.0f, 1.00f };				//
		colors[ImGuiCol_TextDisabled] = { 0.25f, 0.25f, 0.25f, 1.00f };		//
		colors[ImGuiCol_WindowBg] = { 0.09f, 0.09f, 0.09f, 0.94f };			//
		colors[ImGuiCol_ChildBg] = { 0.11f, 0.11f, 0.11f, 1.00f };			//
		colors[ImGuiCol_PopupBg] = { 0.11f, 0.11f, 0.11f, 0.94f };			//
		colors[ImGuiCol_Border] = { 0.07f, 0.08f, 0.08f, 1.00f };
		colors[ImGuiCol_BorderShadow] = { 0.00f, 0.00f, 0.00f, 0.00f };
		colors[ImGuiCol_FrameBg] = { 0.35f, 0.35f, 0.35f, 0.54f };			//
		colors[ImGuiCol_FrameBgHovered] = { 0.3f, 0.3f, 0.3f, 1.00f };
		//colors[ImGuiCol_FrameBgHovered] = { 0.31f, 0.29f, 0.27f, 1.00f };
		colors[ImGuiCol_FrameBgActive] = { 0.40f, 0.36f, 0.33f, 0.67f };
		colors[ImGuiCol_TitleBg] = { 0.1f, 0.1f, 0.1f, 1.00f };
		colors[ImGuiCol_TitleBgActive] = { 0.3f, 0.3f, 0.3f, 1.00f };		//
		colors[ImGuiCol_TitleBgCollapsed] = { 0.0f, 0.0f, 0.0f, 0.61f };
		colors[ImGuiCol_MenuBarBg] = { 0.18f, 0.18f, 0.18f, 0.94f };		//
		colors[ImGuiCol_ScrollbarBg] = { 0.00f, 0.00f, 0.00f, 0.16f };
		colors[ImGuiCol_ScrollbarGrab] = { 0.24f, 0.22f, 0.21f, 1.00f };
		colors[ImGuiCol_ScrollbarGrabHovered] = { 0.3f, 0.3f, 0.3f, 1.00f };
		colors[ImGuiCol_ScrollbarGrabActive] = { 0.40f, 0.36f, 0.33f, 1.00f };
		colors[ImGuiCol_CheckMark] = { 0.84f, 0.84f, 0.84f, 1.0f };			//
		colors[ImGuiCol_SliderGrab] = { 0.4f, 0.4f, 0.4f, 1.0f };			//		
		//colors[ImGuiCol_SliderGrab] = { 0.8f, 0.8f, 0.8f, 1.0f };			//		
		colors[ImGuiCol_SliderGrabActive] = { 0.35f, 0.35f, 0.35f, 1.00f }; //
		//colors[ImGuiCol_SliderGrabActive] = { 0.55f, 0.55f, 0.55f, 1.00f }; //
		colors[ImGuiCol_Button] = { 0.55f, 0.55f, 0.55f, 0.40f };			//
		colors[ImGuiCol_ButtonHovered] = { 0.15f, 0.15f, 0.15f, 0.62f };	//	
		colors[ImGuiCol_ButtonActive] = { 0.60f, 0.60f, 0.60f, 1.00f };		//
		colors[ImGuiCol_Header] = { 0.84f, 0.36f, 0.05f, 0.0f };			//
		colors[ImGuiCol_HeaderHovered] = { 0.25f, 0.25f, 0.25f, 0.80f };	//
		colors[ImGuiCol_HeaderActive] = { 0.42f, 0.42f, 0.42f, 1.00f };
		colors[ImGuiCol_Separator] = { 0.35f, 0.35f, 0.35f, 0.50f };		//
		colors[ImGuiCol_SeparatorHovered] = { 0.3f, 0.3f, 0.3f, 0.78f };
		colors[ImGuiCol_SeparatorActive] = { 0.40f, 0.36f, 0.33f, 1.00f };
		colors[ImGuiCol_ResizeGrip] = { 1.0f, 1.0f, 1.0f, 0.25f };			//
		colors[ImGuiCol_ResizeGripHovered] = { 1.00f, 1.0f, 1.0f, 0.4f };	//
		colors[ImGuiCol_ResizeGripActive] = { 1.00f, 1.00f, 1.0f, 0.95f };	//
		colors[ImGuiCol_Tab] = { 0.18f, 0.18f, 0.18f, 1.0f };				//
		colors[ImGuiCol_TabHovered] = { 0.58f, 0.58f, 0.58f, 0.80f };		//
		colors[ImGuiCol_TabActive] = { 0.6f, 0.60f, 0.60f, 1.00f };
		colors[ImGuiCol_TabUnfocused] = { 0.07f, 0.10f, 0.15f, 0.97f };
		colors[ImGuiCol_TabUnfocusedActive] = { 0.14f, 0.26f, 0.42f, 1.00f };
		colors[ImGuiCol_PlotLines] = { 0.66f, 0.60f, 0.52f, 1.00f };
		colors[ImGuiCol_PlotLinesHovered] = { 0.98f, 0.29f, 0.20f, 1.00f };
		colors[ImGuiCol_PlotHistogram] = { 0.60f, 0.59f, 0.10f, 1.00f };
		colors[ImGuiCol_PlotHistogramHovered] = { 0.72f, 0.73f, 0.15f, 1.00f };
		colors[ImGuiCol_TextSelectedBg] = { 0.27f, 0.52f, 0.53f, 0.35f };
		colors[ImGuiCol_DragDropTarget] = { 0.60f, 0.59f, 0.10f, 0.90f };
		colors[ImGuiCol_NavHighlight] = { 0.51f, 0.65f, 0.60f, 1.00f };
		colors[ImGuiCol_NavWindowingHighlight] = { 1.00f, 1.00f, 1.00f, 0.70f };
		colors[ImGuiCol_NavWindowingDimBg] = { 0.80f, 0.80f, 0.80f, 0.20f };
		colors[ImGuiCol_ModalWindowDimBg] = { 0.11f, 0.13f, 0.13f, 0.35f };
	}

	//--

	//// https://github.com/erickjung/SwiftGUI
	//// ImGui theme
	//inline void ImGui_ThemeDarcula()
	//{
	//	//		//
	//	//// Copyright (c) 2020, Erick Jung.
	//	//// All rights reserved.
	//	////
	//	//// This source code is licensed under the MIT-style license found in the
	//	//// LICENSE file in the root directory of this source tree.
	//	////
	//	//
	//	//		import Foundation
	//	//
	//	//			public class DarculaTheme : Theme {
	//	//
	//	//			public var colors : [GuiColorProperty:GuiColor]{
	//	//
	//	//				return[
	//	//					.text:.white,
	//	//					.textDisabled : GuiColor(r : 0.54, g : 0.54, b : 0.54, a : 1),
	//	//					.windowBg : GuiColor(r : 0.23, g : 0.24, b : 0.25, a : 1),
	//	//					.childBg : GuiColor(r : 0.23, g : 0.24, b : 0.25, a : 1),
	//	//					.popupBg : GuiColor(r : 0.23, g : 0.24, b : 0.25, a : 1),
	//	//					.border : GuiColor(r : 0.36, g : 0.36, b : 0.36, a : 1),
	//	//					.borderShadow : GuiColor(r : 0.15, g : 0.15, b : 0.15, a : 0),
	//	//					.frameBg : GuiColor(r : 0.27, g : 0.28, b : 0.29, a : 1),
	//	//					.frameBgHovered : GuiColor(r : 0.27, g : 0.28, b : 0.29, a : 1),
	//	//					.frameBgActive : GuiColor(r : 0.47, g : 0.47, b : 0.47, a : 0.67),
	//	//					.titleBg : GuiColor(r : 0.04, g : 0.04, b : 0.04, a : 1),
	//	//					.titleBgActive : GuiColor(r : 0, g : 0, b : 0, a : 0.51),
	//	//					.titleBgCollapsed : GuiColor(r : 0.16, g : 0.29, b : 0.48, a : 1),
	//	//					.menuBarBg : GuiColor(r : 0.27, g : 0.28, b : 0.29, a : 0.8),
	//	//					.scrollbarBg : GuiColor(r : 0.39, g : 0.4, b : 0.4, a : 0),
	//	//					.scrollbarGrab : GuiColor(r : 0.39, g : 0.4, b : 0.4, a : 1),
	//	//					.scrollbarGrabHovered : GuiColor(r : 0.39, g : 0.4, b : 0.4, a : 1),
	//	//					.scrollbarGrabActive : GuiColor(r : 0.39, g : 0.4, b : 0.4, a : 1),
	//	//					.checkMark : GuiColor(r : 0.65, g : 0.65, b : 0.65, a : 1),
	//	//					.sliderGrab : GuiColor(r : 0.7, g : 0.7, b : 0.7, a : 0.62),
	//	//					.sliderGrabActive : GuiColor(r : 0.3, g : 0.3, b : 0.3, a : 0.84),
	//	//					.button : GuiColor(r : 0.29, g : 0.31, b : 0.32, a : 1),
	//	//					.buttonHovered : GuiColor(r : 0.29, g : 0.31, b : 0.32, a : 1),
	//	//					.buttonActive : GuiColor(r : 0.21, g : 0.34, b : 0.5, a : 1),
	//	//					.header : GuiColor(r : 0.32, g : 0.33, b : 0.34, a : 1),
	//	//					.headerHovered : GuiColor(r : 0.30, g : 0.32, b : 0.32, a : 1),
	//	//					.headerActive : GuiColor(r : 0.47, g : 0.47, b : 0.47, a : 0.67),
	//	//					.separator : GuiColor(r : 0.31, g : 0.31, b : 0.31, a : 1),
	//	//					.separatorHovered : GuiColor(r : 0.31, g : 0.31, b : 0.31, a : 1),
	//	//					.separatorActive : GuiColor(r : 0.31, g : 0.31, b : 0.31, a : 1),
	//	//					.resizeGrip : GuiColor(r : 1, g : 1, b : 1, a : 0.85),
	//	//					.resizeGripHovered : GuiColor(r : 1, g : 1, b : 1, a : 0.6),
	//	//					.resizeGripActive : GuiColor(r : 0.47, g : 0.47, b : 0.47, a : 0.67),
	//	//					.tab : GuiColor(r : 0.32, g : 0.33, b : 0.34, a : 1),
	//	//					.tabHovered : GuiColor(r : 0.21, g : 0.34, b : 0.5, a : 1),
	//	//					.tabActive : GuiColor(r : 0.21, g : 0.34, b : 0.5, a : 1),
	//	//					.tabUnfocused : GuiColor(r : 0.06, g : 0.53, b : 0.98, a : 0.8),
	//	//					.tabUnfocusedActive : GuiColor(r : 0.06, g : 0.53, b : 0.98, a : 0.4),
	//	//					.plotLines : GuiColor(r : 0.61, g : 0.61, b : 0.61, a : 1),
	//	//					.plotLinesHovered : GuiColor(r : 1, g : 0.43, b : 0.35, a : 1),
	//	//					.plotHistogram : GuiColor(r : 0.9, g : 0.7, b : 0, a : 1),
	//	//					.plotHistogramHovered : GuiColor(r : 1, g : 0.6, b : 0, a : 1),
	//	//					.textSelectedBg : GuiColor(r : 0.18, g : 0.39, b : 0.79, a : 0.9),
	//	//					.modalWindowDimBg : GuiColor(r : 0.18, g : 0.39, b : 0.79, a : 1)
	//	//				]
	//	//			}
	//	//
	//	//				public var windowRounding : Float{
	//	//					return 5.3
	//	//					}
	//	//
	//	//						public var grabRounding : Float{
	//	//							return 2.3
	//	//					}
	//	//
	//	//						public var frameRounding : Float{
	//	//							return 2.3
	//	//					}
	//	//
	//	//						public var scrollbarRounding : Float{
	//	//							return 5
	//	//					}
	//	//
	//	//						public var frameBorderSize : Float{
	//	//							return 1
	//	//					}
	//	//
	//	//						public var itemSpacing : GuiPoint{
	//	//							return GuiPoint(x: 8, y : 6.5)
	//	//					}
	//	//
	//	//						public init() {}
	//	//		}

	//	auto& style = ImGui::GetStyle();
	//	style.ChildRounding = 0;
	//	style.GrabRounding = 0;
	//	style.FrameRounding = 2;
	//	style.PopupRounding = 0;
	//	style.ScrollbarRounding = 0;
	//	style.TabRounding = 2;
	//	style.WindowRounding = 0;
	//	style.FramePadding = { 4, 4 };
	//	style.WindowTitleAlign = { 0.0, 0.5 };
	//	style.ColorButtonPosition = ImGuiDir_Left;
	//	ImVec4* colors = ImGui::GetStyle().Colors;
	//	colors[ImGuiCol_Text] = { 1.0f, 1.0f, 1.0f, 1.00f };				//
	//	colors[ImGuiCol_TextDisabled] = { 0.25f, 0.25f, 0.25f, 1.00f };		//
	//	colors[ImGuiCol_WindowBg] = { 0.09f, 0.09f, 0.09f, 0.94f };			//
	//	colors[ImGuiCol_ChildBg] = { 0.11f, 0.11f, 0.11f, 1.00f };			//
	//	colors[ImGuiCol_PopupBg] = { 0.11f, 0.11f, 0.11f, 0.94f };			//
	//	colors[ImGuiCol_Border] = { 0.07f, 0.08f, 0.08f, 1.00f };
	//	colors[ImGuiCol_BorderShadow] = { 0.00f, 0.00f, 0.00f, 0.00f };
	//	colors[ImGuiCol_FrameBg] = { 0.35f, 0.35f, 0.35f, 0.54f };			//
	//	colors[ImGuiCol_FrameBgHovered] = { 0.31f, 0.29f, 0.27f, 1.00f };
	//	colors[ImGuiCol_FrameBgActive] = { 0.40f, 0.36f, 0.33f, 0.67f };
	//	colors[ImGuiCol_TitleBg] = { 0.1f, 0.1f, 0.1f, 1.00f };
	//	colors[ImGuiCol_TitleBgActive] = { 0.3f, 0.3f, 0.3f, 1.00f };		//
	//	colors[ImGuiCol_TitleBgCollapsed] = { 0.0f, 0.0f, 0.0f, 0.61f };
	//	colors[ImGuiCol_MenuBarBg] = { 0.18f, 0.18f, 0.18f, 0.94f };		//
	//	colors[ImGuiCol_ScrollbarBg] = { 0.00f, 0.00f, 0.00f, 0.16f };
	//	colors[ImGuiCol_ScrollbarGrab] = { 0.24f, 0.22f, 0.21f, 1.00f };
	//	colors[ImGuiCol_ScrollbarGrabHovered] = { 0.31f, 0.29f, 0.27f, 1.00f };
	//	colors[ImGuiCol_ScrollbarGrabActive] = { 0.40f, 0.36f, 0.33f, 1.00f };
	//	colors[ImGuiCol_CheckMark] = { 0.84f, 0.84f, 0.84f, 1.0f };			//
	//	colors[ImGuiCol_SliderGrab] = { 0.8f, 0.8f, 0.8f, 1.0f };			//		
	//	colors[ImGuiCol_SliderGrabActive] = { 0.55f, 0.55f, 0.55f, 1.00f }; //
	//	colors[ImGuiCol_Button] = { 0.55f, 0.55f, 0.55f, 0.40f };			//
	//	colors[ImGuiCol_ButtonHovered] = { 0.15f, 0.15f, 0.15f, 0.62f };	//	
	//	colors[ImGuiCol_ButtonActive] = { 0.60f, 0.60f, 0.60f, 1.00f };		//
	//	colors[ImGuiCol_Header] = { 0.84f, 0.36f, 0.05f, 0.0f };			//
	//	colors[ImGuiCol_HeaderHovered] = { 0.25f, 0.25f, 0.25f, 0.80f };	//
	//	colors[ImGuiCol_HeaderActive] = { 0.42f, 0.42f, 0.42f, 1.00f };
	//	colors[ImGuiCol_Separator] = { 0.35f, 0.35f, 0.35f, 0.50f };		//
	//	colors[ImGuiCol_SeparatorHovered] = { 0.31f, 0.29f, 0.27f, 0.78f };
	//	colors[ImGuiCol_SeparatorActive] = { 0.40f, 0.36f, 0.33f, 1.00f };
	//	colors[ImGuiCol_ResizeGrip] = { 1.0f, 1.0f, 1.0f, 0.25f };			//
	//	colors[ImGuiCol_ResizeGripHovered] = { 1.00f, 1.0f, 1.0f, 0.4f };	//
	//	colors[ImGuiCol_ResizeGripActive] = { 1.00f, 1.00f, 1.0f, 0.95f };	//
	//	colors[ImGuiCol_Tab] = { 0.18f, 0.18f, 0.18f, 1.0f };				//
	//	colors[ImGuiCol_TabHovered] = { 0.58f, 0.58f, 0.58f, 0.80f };		//
	//	colors[ImGuiCol_TabActive] = { 0.6f, 0.60f, 0.60f, 1.00f };
	//	colors[ImGuiCol_TabUnfocused] = { 0.07f, 0.10f, 0.15f, 0.97f };
	//	colors[ImGuiCol_TabUnfocusedActive] = { 0.14f, 0.26f, 0.42f, 1.00f };
	//	colors[ImGuiCol_PlotLines] = { 0.66f, 0.60f, 0.52f, 1.00f };
	//	colors[ImGuiCol_PlotLinesHovered] = { 0.98f, 0.29f, 0.20f, 1.00f };
	//	colors[ImGuiCol_PlotHistogram] = { 0.60f, 0.59f, 0.10f, 1.00f };
	//	colors[ImGuiCol_PlotHistogramHovered] = { 0.72f, 0.73f, 0.15f, 1.00f };
	//	colors[ImGuiCol_TextSelectedBg] = { 0.27f, 0.52f, 0.53f, 0.35f };
	//	colors[ImGuiCol_DragDropTarget] = { 0.60f, 0.59f, 0.10f, 0.90f };
	//	colors[ImGuiCol_NavHighlight] = { 0.51f, 0.65f, 0.60f, 1.00f };
	//	colors[ImGuiCol_NavWindowingHighlight] = { 1.00f, 1.00f, 1.00f, 0.70f };
	//	colors[ImGuiCol_NavWindowingDimBg] = { 0.80f, 0.80f, 0.80f, 0.20f };
	//	colors[ImGuiCol_ModalWindowDimBg] = { 0.11f, 0.13f, 0.13f, 0.35f };
	//}

	//--

	//// slider enum
	//// Using the format string to display a name instead of an integer.
	//// Here we completely omit '%d' from the format string, so it'll only display a name.
	//// This technique can also be used with DragInt().
	////DemoCode_("Widgets/Basic/Inputs/Slider Enum");
	//enum Element { Element_Fire, Element_Earth, Element_Air, Element_Water, Element_COUNT };
	//static int elem = Element_Fire;
	//const char* elems_names[Element_COUNT] = { "Fire", "Earth", "Air", "Water" };
	//const char* elem_name = (elem >= 0 && elem < Element_COUNT) ? elems_names[elem] : "Unknown";
	//ImGui::SliderInt("slider enum", &elem, 0, Element_COUNT - 1, elem_name);
	////ImGui::SameLine(); 
	////HelpMarker("Using the format string parameter to display a name instead of the underlying integer.");

	//// drop list
	//// Using the _simplified_ one-liner Combo() api here
	//// See "Combo" section for examples of how to use the more complete BeginCombo()/EndCombo() api.
	//const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
	//static int item_current = 0;
	//ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));

	//--------------------------------------------------------------
	inline void ImGui_ThemeGrey()
	{
		ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeGrey";

		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
		colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
		colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);

		// docking
		colors[ImGuiCol_DockingPreview] = ImVec4(1.000f, 0.391f, 0.000f, 0.781f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 14.0f;
		style->TabBorderSize = 1.0f;
		style->TabRounding = 0.0f;
		style->WindowRounding = 4.0f;

	}

	// taken from: https://github.com/ocornut/imgui/issues/539#issuecomment-233914952
	//--------------------------------------------------------------
	inline void ImGui_ThemeOlekristensen()
	{
		ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeOlekristensen";

		//ImGuiIO& io = ImGui::GetIO();
		//io.Fonts->Clear();
		//io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/OpenSans-Light.ttf", true).c_str(), 16);
		//io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/OpenSans-Regular.ttf", true).c_str(), 16);
		//io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/OpenSans-Light.ttf", true).c_str(), 32);
		//io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/OpenSans-Regular.ttf", true).c_str(), 11);
		//io.Fonts->AddFontFromFileTTF(ofToDataPath("fonts/OpenSans-Bold.ttf", true).c_str(), 11);
		//io.Fonts->Build();

		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 5.0f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 4.0f;
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;

		style->Colors[ImGuiCol_Text] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.39f, 0.38f, 0.77f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.92f, 0.91f, 0.88f, 0.70f);
		style->Colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.58f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.92f, 0.91f, 0.88f, 0.92f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.84f, 0.83f, 0.80f, 0.65f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.99f, 1.00f, 0.40f, 0.78f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.47f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.21f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.90f, 0.91f, 0.00f, 0.78f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.25f, 1.00f, 0.00f, 0.80f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.99f, 1.00f, 0.22f, 0.86f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.25f, 1.00f, 0.00f, 0.76f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.86f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.00f, 0.00f, 0.32f);
		style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
		style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);

		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
		style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	}

	//----

	// Taken from xemu from mborgerson 
	// https://github.com/mborgerson/xemu

	//--------------------------------------------------------------
	static void ImGui_Xemu()
	{
		ofLogNotice("ofxSurfingImGui") << "ImGui_Xemu";

		//g_font_mgr.Rebuild();

		ImGui::StyleColorsDark();
		ImVec4* c = ImGui::GetStyle().Colors;
		c[ImGuiCol_Text] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
		c[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
		c[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		c[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.98f);
		c[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		c[ImGuiCol_Border] = ImVec4(0.11f, 0.11f, 0.11f, 0.60f);
		c[ImGuiCol_BorderShadow] = ImVec4(0.16f, 0.16f, 0.16f, 0.00f);
		c[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		c[ImGuiCol_FrameBgHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
		c[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
		c[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.51f, 0.18f, 1.00f);
		c[ImGuiCol_TitleBgActive] = ImVec4(0.26f, 0.66f, 0.23f, 1.00f);
		c[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.16f, 0.75f);
		c[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.00f);
		c[ImGuiCol_ScrollbarBg] = ImVec4(0.16f, 0.16f, 0.16f, 0.00f);
		c[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
		c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
		c[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
		c[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.66f, 0.23f, 1.00f);
		c[ImGuiCol_SliderGrab] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
		c[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		c[ImGuiCol_Button] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
		c[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
		c[ImGuiCol_ButtonActive] = ImVec4(0.26f, 0.66f, 0.23f, 1.00f);
		c[ImGuiCol_Header] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
		c[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
		c[ImGuiCol_HeaderActive] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
		c[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 0.25f);
		c[ImGuiCol_SeparatorHovered] = ImVec4(0.13f, 0.87f, 0.16f, 0.78f);
		c[ImGuiCol_SeparatorActive] = ImVec4(0.25f, 0.75f, 0.10f, 1.00f);
		c[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.83f, 0.49f, 0.04f);
		c[ImGuiCol_ResizeGripHovered] = ImVec4(0.28f, 0.71f, 0.25f, 0.78f);
		c[ImGuiCol_ResizeGripActive] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
		c[ImGuiCol_Tab] = ImVec4(0.26f, 0.67f, 0.23f, 0.95f);
		c[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
		c[ImGuiCol_TabActive] = ImVec4(0.24f, 0.60f, 0.00f, 1.00f);
		c[ImGuiCol_TabUnfocused] = ImVec4(0.21f, 0.54f, 0.19f, 0.99f);
		c[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.60f, 0.21f, 1.00f);
		c[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		c[ImGuiCol_PlotLinesHovered] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
		c[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		c[ImGuiCol_PlotHistogramHovered] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
		c[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.66f, 0.23f, 1.00f);
		c[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		c[ImGuiCol_NavHighlight] = ImVec4(0.28f, 0.71f, 0.25f, 1.00f);
		c[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		c[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		c[ImGuiCol_ModalWindowDimBg] = ImVec4(0.16f, 0.16f, 0.16f, 0.73f);

		ImGuiStyle& s = ImGui::GetStyle();
		s.WindowRounding = 6.0;
		s.FrameRounding = 6.0;
		s.PopupRounding = 6.0;
		//g_base_style = s;
	}

	//----

	// Taken from Yave by gan74
	// Source: https://github.com/gan74/Yave

#define none ofFloatColor(0,0,0)

	static ofFloatColor grey(int g, float a = 1.f) {
		ofColor c = ofColor(g, g, g, a * 255);
		return ofFloatColor(c);
	};

	static ofFloatColor rgb(int r, int g, int b) {
		ofColor c = ofColor(r, g, b);
		return ofFloatColor(c);
	};

	//--------------------------------------------------------------
	static void ImGui_ThemeYave()
	{
		ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeYave";

		auto& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		//const math::Vec4 none = {};

		//const float lightness = 1.0f;
		//auto rgb = [=](u8 r, u8 g, u8 b, float alpha = 1.0f) {
		//    return math::Vec4(math::Vec3(r, g, b) / 255.0f * lightness, alpha).min(math::Vec4(1.0f));
		//};
		//auto grey = [=](u8 g, float alpha = 1.0f) {
		//    return rgb(g, g, g, alpha);
		//};

		//for (usize i = 0; i != ImGuiCol_COUNT; ++i) {
		//    colors[i] = rgb(255, 0, 0);
		//}

		colors[ImGuiCol_ChildBg] = none;
		colors[ImGuiCol_BorderShadow] = none;
		colors[ImGuiCol_FrameBgActive] = none;
		colors[ImGuiCol_Tab] = none;
		colors[ImGuiCol_TabUnfocused] = none;
		colors[ImGuiCol_DockingEmptyBg] = none;

		colors[ImGuiCol_Text] = grey(180);
		colors[ImGuiCol_TextDisabled] = grey(90);

		colors[ImGuiCol_CheckMark] = rgb(0, 112, 224);
		colors[ImGuiCol_DragDropTarget] = rgb(0, 112, 224);
		colors[ImGuiCol_NavWindowingHighlight] = rgb(0, 112, 224);

		colors[ImGuiCol_PlotHistogram] = rgb(0, 112, 224);
		colors[ImGuiCol_PlotHistogramHovered] = rgb(0, 112, 224);
		colors[ImGuiCol_PlotLines] = rgb(0, 112, 224);
		colors[ImGuiCol_PlotLinesHovered] = rgb(0, 112, 224);

		colors[ImGuiCol_NavWindowingHighlight] = rgb(128, 168, 224);

		colors[ImGuiCol_Border] = grey(21, 0.75f);
		colors[ImGuiCol_PopupBg] = grey(21, 0.9f);
		colors[ImGuiCol_FrameBg] = grey(15, 0.5f);
		colors[ImGuiCol_TableRowBgAlt] = grey(20, 0.25f);

		colors[ImGuiCol_NavWindowingDimBg] = grey(128, 0.75f);
		colors[ImGuiCol_ModalWindowDimBg] = grey(128, 0.75f);
		colors[ImGuiCol_DockingPreview] = grey(128, 0.25f);
		colors[ImGuiCol_FrameBgHovered] = grey(128, 0.25f);
		colors[ImGuiCol_TextSelectedBg] = grey(128, 0.25f);

		colors[ImGuiCol_SliderGrabActive] = grey(128);
		colors[ImGuiCol_ScrollbarGrabActive] = grey(128);
		colors[ImGuiCol_ScrollbarGrabHovered] = grey(128);
		colors[ImGuiCol_ResizeGripActive] = grey(128);
		colors[ImGuiCol_ResizeGripHovered] = grey(128);

		colors[ImGuiCol_SliderGrab] = grey(87);
		colors[ImGuiCol_ScrollbarGrab] = grey(87);
		colors[ImGuiCol_ResizeGrip] = grey(87);

		colors[ImGuiCol_Button] = grey(60);

		colors[ImGuiCol_ButtonHovered] = grey(47);
		colors[ImGuiCol_ButtonActive] = grey(47);
		colors[ImGuiCol_Header] = grey(47);
		colors[ImGuiCol_HeaderHovered] = grey(47);
		colors[ImGuiCol_HeaderActive] = grey(47);
		colors[ImGuiCol_SeparatorActive] = grey(47);
		colors[ImGuiCol_SeparatorHovered] = grey(47);
		colors[ImGuiCol_TabHovered] = grey(47);

		colors[ImGuiCol_WindowBg] = grey(36);
		colors[ImGuiCol_TabActive] = grey(36);
		colors[ImGuiCol_TabUnfocusedActive] = grey(36);
		colors[ImGuiCol_TableRowBg] = grey(36);

		colors[ImGuiCol_Separator] = grey(26);
		colors[ImGuiCol_TableBorderLight] = grey(26);
		colors[ImGuiCol_TableBorderStrong] = grey(26);
		colors[ImGuiCol_ScrollbarBg] = grey(26);

		colors[ImGuiCol_TitleBg] = grey(21);
		colors[ImGuiCol_TitleBgActive] = grey(21);
		colors[ImGuiCol_TitleBgCollapsed] = grey(21);
		colors[ImGuiCol_MenuBarBg] = grey(21);


		style.WindowPadding = ImVec2(4, 4);
		style.FramePadding = ImVec2(6, 6);
		style.ItemSpacing = ImVec2(4, 2);

		style.ScrollbarSize = 12;
		style.ScrollbarRounding = 12;

		style.IndentSpacing = 12;

		style.WindowBorderSize = 0;
		style.ChildBorderSize = 0;
		style.PopupBorderSize = 0;
		style.FrameBorderSize = 0;
		style.PopupRounding = 0;

		style.FrameRounding = 3;
		style.GrabRounding = 3;

		style.WindowRounding = 0;
		style.ChildRounding = 0;
		style.TabBorderSize = 0;
		style.TabRounding = 0;


		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
	}

	//--

	// https://github.com/Raais/ImguiCandy
	//---------------------------------------------------------------------------------------------------------

	static void Theme_Blender(ImGuiStyle* dst = NULL)
	{
		// 'Blender Dark' theme from v3.0.0 [Improvised]
		// Colors grabbed using X11 Soft/xcolor
		ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
		ImVec4* colors = style->Colors;
		ImGui::StyleColorsDark(style);//Reset to base/dark theme
		colors[ImGuiCol_Text] = ImVec4(0.84f, 0.84f, 0.84f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.10f, 0.10f, 0.10f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.54f, 0.54f, 0.54f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.19f, 0.39f, 0.69f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.20f, 0.39f, 0.69f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.28f, 0.45f, 0.70f, 1.00f);
		style->WindowPadding = ImVec2(12.00f, 8.00f);
		style->ItemSpacing = ImVec2(7.00f, 3.00f);
		style->GrabMinSize = 20.00f;
		style->WindowRounding = 8.00f;
		style->FrameBorderSize = 0.00f;
		style->FrameRounding = 4.00f;
		style->GrabRounding = 12.00f;
	}

	static void Theme_Cyberpunk(ImGuiStyle* dst = NULL)
	{
		// Cyberpunk Neon [Improvised]
		// https://github.com/Roboron3042/Cyberpunk-Neon
		ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
		ImVec4* colors = style->Colors;
		ImGui::StyleColorsDark(style);//Reset to base/dark theme
		colors[ImGuiCol_Text] = ImVec4(0.00f, 0.82f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.36f, 0.63f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.04f, 0.12f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.03f, 0.04f, 0.22f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.06f, 0.27f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.75f, 1.00f, 0.20f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.34f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.08f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.81f, 0.95f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.25f, 0.00f, 0.54f, 0.81f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.88f, 1.00f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.01f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.95f, 0.19f, 0.67f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.95f, 0.19f, 0.92f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 0.95f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.81f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.00f, 0.98f, 1.00f, 0.52f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.94f, 0.00f, 1.00f, 0.80f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.01f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.00f, 0.95f, 1.00f, 0.40f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.94f, 0.00f, 1.00f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.01f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.74f, 0.00f, 1.00f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.34f, 0.00f, 1.00f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.00f, 1.00f, 0.85f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.61f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.89f, 0.26f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.88f, 1.00f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.36f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.92f, 1.00f, 0.80f);
		colors[ImGuiCol_TabActive] = ImVec4(0.62f, 0.00f, 0.80f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 1.00f, 0.88f, 1.00f);
		style->FrameBorderSize = 0.00f;
		style->WindowRounding = 0.00f;
		style->FrameRounding = 0.00f;
		style->ScrollbarRounding = 0.00f;
		style->GrabRounding = 0.00f;
	}

	static void Theme_Nord(ImGuiStyle* dst = NULL)
	{
		// Nord/Nordic GTK [Improvised]
		// https://github.com/EliverLara/Nordic
		ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
		ImVec4* colors = style->Colors;
		ImGui::StyleColorsDark(style);//Reset to base/dark theme
		colors[ImGuiCol_Text] = ImVec4(0.85f, 0.87f, 0.91f, 0.88f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.49f, 0.50f, 0.53f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.16f, 0.17f, 0.20f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.23f, 0.26f, 0.32f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.09f, 0.09f, 0.09f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.23f, 0.26f, 0.32f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.56f, 0.74f, 0.73f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.53f, 0.75f, 0.82f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.16f, 0.20f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.23f, 0.26f, 0.32f, 0.60f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.23f, 0.26f, 0.32f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.23f, 0.26f, 0.32f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.37f, 0.51f, 0.67f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.63f, 0.76f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.51f, 0.67f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.51f, 0.63f, 0.76f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.37f, 0.51f, 0.67f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.51f, 0.63f, 0.76f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.53f, 0.75f, 0.82f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.37f, 0.51f, 0.67f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.56f, 0.74f, 0.73f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.53f, 0.75f, 0.82f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.53f, 0.75f, 0.82f, 0.86f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.61f, 0.74f, 0.87f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.37f, 0.51f, 0.67f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.20f, 0.25f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.22f, 0.24f, 0.31f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.26f, 0.32f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.15f, 0.18f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.17f, 0.19f, 0.23f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.56f, 0.74f, 0.73f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.53f, 0.75f, 0.82f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.37f, 0.51f, 0.67f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.53f, 0.75f, 0.82f, 0.86f);
		style->WindowBorderSize = 1.00f;
		style->ChildBorderSize = 1.00f;
		style->PopupBorderSize = 1.00f;
		style->FrameBorderSize = 1.00f;
	}

};//namespace
