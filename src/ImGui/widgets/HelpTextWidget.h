#pragma once

#include "ofMain.h"

class HelpTextWidget
{
public:
    HelpTextWidget()
    {
    };

    ~HelpTextWidget()
    {
    };

private:
    std::string text = "HelpTextWidget\nEmpty content";
    std::string title = "myHelpWidget";

    bool bBg = true;

private:
    bool bHeader = false;
    bool bBlink = 0;

    bool bMouseLeft = false;
    bool bMouseRight = false;
    bool bMouseDrag = false;

public:
    void setEnableHeader(bool b) { bHeader = b; }

    ofParameter<bool> bGui{"HelpTextWidget", true};

    void setTitle(string _title, bool bCapitalize = true)
    {
        ofLogVerbose("ofxSurfingImGui:HelpTextWidget") << "setTitle:" << _title;
        title = _title;

        if (bCapitalize) title = ofToUpper(title);
    }

    void setText(string _text)
    {
        ofLogVerbose("ofxSurfingImGui:HelpTextWidget") << "SetText:" << _text;
        text = _text;
    }

    void setName(string name)
    {
        bGui.setName(name);
        title = name;
    }

    void draw()
    {
        if (bMouseLeft && bMouseRight)
        {
            bMouseLeft = bMouseRight = bMouseDrag = false;
            bGui = false;
        }

        if (!bGui) return;

        float r = 3; // window rounded 
        float p = 25; // window padding to borders

        // Spacing after title
        //string sp = "\n\n";
        string sp = "\n";

        //--

        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        if (!bHeader) flags += ImGuiWindowFlags_NoDecoration;
        if (!bBg) flags += ImGuiWindowFlags_NoBackground;
        flags += ImGuiWindowFlags_AlwaysAutoResize;

        // bg color
        //ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_FrameBgHovered);

        ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_HeaderActive);

        ////alpha
        //float a = 0.8f;
        //cbg = ImVec4(cbg.x, cbg.y, cbg.z, cbg.w * a);

        // no alpha
        //float abg = ImGui::GetStyleColorVec4(ImGuiCol_HeaderActive).w;

        // alpha
        float abg = 0.82;

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(cbg.x, cbg.y, cbg.z, abg));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{p, p});
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, r);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        if (bBlink)
        {
            ImVec4 tc = ImGui::GetStyleColorVec4(ImGuiCol_Text);
            float ta = ofxImGuiSurfing::getFadeBlink();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(tc.x, tc.y, tc.z, tc.w * ta));
        }

        bool tmp = bGui.get();
        ImGui::Begin(bGui.getName().c_str(), (bool*)&tmp, flags);
        {
            // Title
            if (!bHeader)
            {
                string s = title;
                //string s = title + sp;

                if (fontIndex < customFonts.size())
                {
                    ImGui::PushFont(customFonts[MAX(fontIndex + 1, customFonts.size()-1)]);
                    ImGui::TextWrapped(s.c_str());
                    ImGui::PopFont();
                }
                else ImGui::TextWrapped(s.c_str());
            }

            //--

            // Body
            {
                string s = sp + text;
                //string s = text;

                if (fontIndex < customFonts.size())
                {
                    ImGui::PushFont(customFonts[fontIndex]);
                    ImGui::TextWrapped(s.c_str());
                    ImGui::PopFont();
                }
                else ImGui::TextWrapped(s.c_str());
            }

            //--

            //TODO:
            // Left + right mouse closes window
            //if()
            //{
            //	bMouseDrag = true;
            //}
            if (!bMouseLeft)
            {
                if (ImGui::IsMouseClicked(0))
                {
                    bMouseLeft = true;
                    if (!bMouseRight) bMouseDrag = true;
                }
            }
            if (bMouseLeft) if (ImGui::IsMouseReleased(0)) bMouseLeft = false;

            if (!bMouseRight) if (ImGui::IsMouseClicked(1)) bMouseRight = true;
            if (bMouseRight) if (ImGui::IsMouseReleased(1)) bMouseRight = false;

            //string s = "";
            //(bMouseLeft ? s = "x" : s = "-");
            //s += " ";
            //(bMouseRight ? s += "x" : s += "-");
            //ImGui::Text(s.c_str());
        }
        ImGui::End();
        if (bGui.get() != tmp) bGui.set(tmp);

        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        if (bBlink) ImGui::PopStyleColor();
    }

private:
    vector<ImFont*> customFonts;

public:
    void setCustomFonts(vector<ImFont*> f)
    {
        customFonts = f;
        if (customFonts.size() == 0)
        {
            ofLogError("ofxSurfingImGui:HelpTextWidget") << "It looks that not any extra font styles are added!";
        }
    }

public:
    void setFontMonospacedDefined(bool b = true)
    {
        bDefinedMonospacedFonts = b;
        fontIndex.setMax(customFonts.size() - 1);
        if (fontIndex < 4) fontIndex += 4; //set relative mono-spaced by default
    }

private:
    ofParameter<int> fontIndex{"Font", 0, 0, 0};
    bool bDefinedMonospacedFonts = false;
};
