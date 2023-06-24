#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

using namespace ImGui;

// NOTES:
// Menu colors
// https://github.com/ocornut/imgui/issues/1903
// ImGuiCol_PopupBg, ImGuiCol_PopupBg

namespace ofxImGuiSurfing
{
    // Must be called after the ofxImGui setup()!

    //--------------------------------------------------------------
    inline void ImGui_ThemeMoebiusSurfing(bool bEnableLayout, bool bEnableColors)
    {
        ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeMoebiusSurfing";

        //resetTheme();
        ImGui::GetStyle() = ImGuiStyle();

        ImGuiStyle* style = &ImGui::GetStyle();

        //--

        // Sizes

        if (bEnableLayout)
        {
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

            // style->TabRounding = 4;
            // style->TabBorderSize = 1;

            //TODO:
            style->TabRounding = 2; // Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
            style->TabBorderSize = 1.f; // Thickness of border around tabs.
            style->TabMinWidthForCloseButton = 0; // Minimum width for close button to appear on an unselected tab when hovered. Set to 0.0f to always show when hovering, set to FLT_MAX to never show close button unless selected.
            // style->Tab

            style->FrameRounding = 4;
            style->FrameBorderSize = 1;
            style->FramePadding = ImVec2(6, 4);

            style->WindowRounding = 2;
            style->WindowBorderSize = 1;
            style->WindowPadding = ImVec2(10, 10);
        }

        //--

        // Colors

        if (bEnableColors)
        {
            ImVec4* colors = ImGui::GetStyle().Colors;

            // Original
            //colors[ImGuiCol_Text] = ImVec4(0.76f, 0.76f, 0.76f, 0.94f);
            //colors[ImGuiCol_TextDisabled] = ImVec4(0.63f, 0.63f, 0.63f, 1.00f);

            // RF more white
            colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 0.94f);
            //colors[ImGuiCol_Text] = ImVec4(0.84f, 0.84f, 0.84f, 0.94f);
            //colors[ImGuiCol_Text] = ImVec4(0.79f, 0.79f, 0.79f, 0.94f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);

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
            colors[ImGuiCol_HeaderActive] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);

            // Selected menu item
            //colors[ImGuiCol_HeaderHovered] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);//original
            //colors[ImGuiCol_HeaderHovered] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);//dark
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.24f, 0.24f, 0.90f); //gray

            colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            //colors[ImGuiCol_MenuBarBg] = ImVec4(1.f, 0.14f, 0.14f, .80f);//red

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

            colors[ImGuiCol_PlotLines] = ImVec4(0.81f, 0.79f, 0.79f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

            colors[ImGuiCol_TableHeaderBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.78f);
            colors[ImGuiCol_TableBorderStrong] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
            colors[ImGuiCol_TableBorderLight] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
            colors[ImGuiCol_TableRowBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.00f);
            colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.20f, 0.22f, 0.27f, 0.06f);
            // //TODO:
            // colors[ImGuiCol_TableRowBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.50f);
            // colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.20f, 0.22f, 0.27f, 0.50f);
            
            colors[ImGuiCol_DragDropTarget] = ImVec4(0.50f, 0.50f, 0.50f, 0.90f);

            colors[ImGuiCol_NavHighlight] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

            colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

            ImVec4 c = colors[ImGuiCol_FrameBg]; //same that frame bg but more transparent
            colors[ImGuiCol_ChildBg] = ImVec4(c.x, c.y, c.z, 0.6f);

            //--

            // Docking
            colors[ImGuiCol_DockingPreview] = ImVec4(0.000f, 0.000f, 0.000f, 0.781f);
            colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
        }
    }

    //--

    //TODO: 
    // A template to create a new V2 template. 
    // It could be a day/lighter color scheme.
    //--------------------------------------------------------------
    inline void ImGui_ThemeMoebiusSurfingV2(bool bEnableLayout, bool bEnableColors)
    {
        ofLogNotice("ofxSurfingImGui") << "ImGui_ThemeMoebiusSurfingV2";
        ImGui_ThemeMoebiusSurfing(bEnableLayout, bEnableColors);
    }
}; // namespace
