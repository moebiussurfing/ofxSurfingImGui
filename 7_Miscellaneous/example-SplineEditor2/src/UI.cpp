//
//  UI.cpp
//  ImGUI
//
//  Created by Akira Hayasaka on 2017/04/25.
//
//

#include "UI.hpp"

UI::UI() :
num_preview_frame(0),
selected_frame(0)
{
    controlPoints.push_back(ImVec2(0, 200));
    controlPoints.push_back(ImVec2(200, 0));
    gui.setup();
}

void UI::draw()
{
    gui.begin();
    
    bool p_open = true;
    ImGui::Begin("Selected Item", &p_open, ImVec2(200, 300), 0.5f,
                 ImGuiWindowFlags_NoResize |
                 //                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoCollapse);
    ImGui::PushItemWidth(-1);
    static int item = 1;
    //ImGui::Combo("", &item, "movie\0sequece\0still\0\0");   // Combo using
    ImGui::Combo("", &item, "movie\0\0");   // Combo using
    static bool check = true;
    //    ImGui::Checkbox("drop credit image", &check);
    ImGui::Dummy(ImVec2(200, 210));
    ImGui::Button("Play"); ImGui::SameLine();
    static float pct = 0.0;
    ImGui::SliderFloat("pct", &pct, 0.0f, 1.0f, "pct = %.3f");
    ImGui::PopItemWidth();
    ImGui::End();
    
    ImGui::SetNextWindowSize(ImVec2(250, 520), ImGuiSetCond_Always);
    ImGui::Begin("Tweaker");
    if (ImGui::CollapsingHeader("Gamma Curve",
                                ImGuiTreeNodeFlags_CollapsingHeader |
                                ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::CurveEditor editor = ImGui::BeginCurveEditor("", 200);
        if (editor.valid)
        {
            ImGui::SplineCurve(200, controlPoints, editor);
            ImGui::EndCurveEditor(editor);
        }
    }
    if (ImGui::CollapsingHeader("Color",
                                ImGuiTreeNodeFlags_CollapsingHeader |
                                ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::PushItemWidth(-1);
        static float bri = 0.5, sat = 0.5, cont = 0.5, hue = 0.5;
        ImGui::SliderFloat("brightness", &bri, 0.0f, 1.0f, "brightness = %.3f");
        ImGui::SliderFloat("saturation", &sat, 0.0f, 1.0f, "saturation = %.3f");
        ImGui::SliderFloat("contrast", &cont, 0.0f, 1.0f, "contrast = %.3f");
        ImGui::SliderFloat("hue", &hue, 0.0f, 1.0f, "hue = %.3f");
        ImGui::PopItemWidth();
    }
    if (ImGui::CollapsingHeader("Translation",
                                ImGuiTreeNodeFlags_CollapsingHeader |
                                ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::PushItemWidth(-1);
        static int xpos = 0, ypos = 0, rot = 0;
        static float scale = 1.0;
        ImGui::SliderInt("xpos", &xpos, -500, 500, "xPos = %.0f%");
        ImGui::SliderInt("ypos", &ypos, -500, 500, "yPos = %.0f%");
        ImGui::SliderFloat("scale", &scale, 0.5f, 2.0f, "scale = %.3f");
        ImGui::SliderInt("rot", &rot, 0, 360, "rotation = %.0f%");
        ImGui::PopItemWidth();
    }
    ImGui::End();
    
    
    ImGui::Begin("Global UI", &p_open, ImVec2(600, 35), 0.5f,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoCollapse);
    ImGui::PushItemWidth(-1);
    if (ImGui::Button("Play"))
        ofNotifyEvent(toggle_play_event);
    ImGui::SameLine();
    ImGui::Button("Render");ImGui::SameLine();
    if (ImGui::SliderInt("preview_frame", &selected_frame, 0, num_preview_frame-1, "preview frame = %.0f%"))
        ofNotifyEvent(preview_frame_change_event, selected_frame);
    ImGui::PopItemWidth();
    ImGui::End();
    
    gui.end();
}
