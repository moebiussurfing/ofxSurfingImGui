#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"

#define PANEL_WIDGETS_WIDTH 250 // will be applied as minimal panel shape
#define PANEL_WIDGETS_HEIGHT 100
#define BUTTON_BIG_HEIGHT 50
#define BUTTON_COLOR_SIZE 40
#define BUTTON_SLIM_HEIGHT2 20
#define COLOR_STRIP_COLOR_HEIGHT 15
#define WIDGETS_HEIGHT 50 // will be applied to tbuttons/toggles heights
#define WIDGET_PARAM_PADDING 110 // will be applied to the ofParams sliders. 110 must be the max labels width of params names

#define TEXT_INACTIVE_ALPHA 0.20f // for use on toggle buttons

//------------------------------

namespace ofxSurfingHelpers {

	//----

	//TODO:

	// WIP
	// fonts management
	//--------------------------------------------------------------
	inline void ImGui_FontCustom() {
		ofLogNotice(__FUNCTION__);
	}
	//--------------------------------------------------------------
	inline void ImGui_FontCustom(ofxImGui::Gui &gui, ImFont* customFont, string path = "assets/fonts/pathtelegrama_render.otf", float size = 10.f) {
		ofLogNotice(__FUNCTION__);

		auto normalCharRanges = ImGui::GetIO().Fonts->GetGlyphRangesDefault();
		customFont = gui.addFont(path, size, nullptr, normalCharRanges);
	}
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

	// themes

	//--------------------------------------------------------------
	inline void ImGui_ThemeMoebiusSurfing()
	{
		ofLogNotice(__FUNCTION__);

		// this must be called after the gui setup()!

		// style

		ImGuiStyle *style = &ImGui::GetStyle();

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
		//style->IndentSpacing = 3;

		// colors 

		//ImVec4* colors = ImGui::GetStyle().Colors;

		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.098f, 0.098f, 0.098f, 1.0f);

		// button
		// enabled is lighter
		style->Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);

		//// enabled is darker
		//style->Colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		//style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.80f);
		//style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.08f, 0.08f, 0.08f, 0.9f);

		// slider
		//style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		//style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.74f, 0.75f, 0.77f, 0.79f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.20f, 0.20f, 0.20f, 0.9f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.4f, 0.4f, 0.4f, 0.8f);

		// text
		style->Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.95f);
		//style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
		//style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

		style->Colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.54f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1f, 0.1f, 0.1f, 0.68f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 0.67f);

		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.12f, 0.11f, 0.11f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);

		style->Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		style->Colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.00f, 0.50f);
		style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.29f, 0.29f, 0.29f, 0.78f);
		style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.44f, 0.44f, 0.44f, 0.25f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.68f, 0.68f, 0.68f, 0.67f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.68f, 0.68f, 0.68f, 0.95f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.81f, 0.79f, 0.79f, 1.00f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
		style->Colors[ImGuiCol_DragDropTarget] = ImVec4(0.50f, 0.50f, 0.50f, 0.90f);
		style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		//-

		// tabs

		style->Colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
		style->Colors[ImGuiCol_TabHovered] = style->Colors[ImGuiCol_WindowBg];
		style->Colors[ImGuiCol_TabActive] = ImVec4(0.2f, 0.2f, 0.2f, 0.9f);
		style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2f, 0.2f, 0.2f, 0.9f);

		//-

		// docking

		style->Colors[ImGuiCol_DockingPreview] = ImVec4(0.000f, 0.000f, 0.000f, 0.781f);
		style->Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
	}

	//--------------------------------------------------------------
	inline void ImGui_ThemeModernDark()
	{
		ofLogNotice(__FUNCTION__);

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
};
