#pragma once

#include "ofMain.h"

// Useful links
// https://github.com/nem0/LumixEngine/blob/timeline_gui/external/imgui/imgui_user.inl#L814

// ImGui Widgets
// - Big Sliders

//------------------------------

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "LayoutHelpers.h"
#include "SurfingGuiConstants.h"

#include "SurfingHelpers.h"


//------------------------------

namespace ofxImGuiSurfing
{
    //--------

    // Float
    //--------------------------------------------------------------
    inline bool AddBigSlider(ofParameter<float>& parameter, float w = -1, float h = -1, string name = "-1",
                             string format = OFX_IM_FORMAT_SLIDERS)
    {
        if (w == -1) w = ImGui::GetContentRegionAvail().x; // full width
        if (h == -1) h = getWidgetsHeightUnit(); // one unit height

        //ImGuiSliderFlags flag = ImGuiSliderFlags_Logarithmic;

        bool bChanged = false;
        auto tmpRef = parameter.get();

        if (name == "-1") name = parameter.getName();

        //TODO: remove after '##'
        bool bHasID = ofIsStringInString(name, "##");
        if (bHasID)
        {
            auto ss = ofSplitString(name, "##", true, true);
            name = ss[0];
        }

        //TODO: name label is duplicated..
        //TODO: make space for label..
        //if (name != "") sz.x = sz.x - 100;

        string n = "##BIGSLIDER" + name;
        ImGui::PushID(n.c_str());
        {
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(w, h)); //TODO: doesn't uses the width..
            if (name == "") ImGui::PushItemWidth(w); // -> name != "" will enable standard aligned resizing with labels
            {
                if (ImGui::SliderFloat(name.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), format.c_str()))
                {
                    parameter.set(tmpRef);

                    bChanged = true;
                }
            }
            if (name == "") ImGui::PopItemWidth();
            ImGui::PopStyleVar(1);
        }
        ImGui::PopID();

        return bChanged;
    }

    // Int. Cloned from float.
    // TODO: should make templed with float..
    //--------------------------------------------------------------
    inline bool AddBigSlider(ofParameter<int>& parameter, float w = -1, float h = -1, string name = "-1",
                             string format = OFX_IM_FORMAT_SLIDERS_INT)
    {
        if (w == -1) w = ImGui::GetContentRegionAvail().x; //full width
        if (h == -1) h = getWidgetsHeightUnit(); //one unit height
        //if (h == -1) h = BUTTON_BIG_HEIGHT;//TODO: get widget height

        ImGuiSliderFlags flag = ImGuiSliderFlags_Logarithmic;

        bool bChanged = false;
        auto tmpRef = parameter.get();

        if (name == "-1") name = parameter.getName();

        //TODO: remove after '##'
        bool bHasID = ofIsStringInString(name, "##");
        if (bHasID)
        {
            auto ss = ofSplitString(name, "##", true, true);
            name = ss[0];
        }

        //TODO: name label is duplicated..
        //TODO: make space for label..
        //if (name != "") sz.x = sz.x - 100;

        string n = "##BIGSLIDER" + name + ofToString(1);
        ImGui::PushID(n.c_str());
        {
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(w, h)); //doesn't uses the width..
            if (name == "") ImGui::PushItemWidth(w); //-> name != "" will enable standard aligned resizing with labels
            {
                if (ImGui::SliderInt(name.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), format.c_str()))
                {
                    parameter.set(tmpRef);

                    bChanged = true;
                }
            }
            if (name == "") ImGui::PopItemWidth();
            ImGui::PopStyleVar(1);
        }
        ImGui::PopID();

        return bChanged;
    }

    //--------------------------------------------------------------
    inline bool AddBigSlider(ofParameter<float>& parameter, ImVec2 sz, string format = OFX_IM_FORMAT_SLIDERS)
    // button but using a bool not void param
    //inline bool AddBigSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), string format = OFX_IM_FORMAT_SLIDERS)// button but using a bool not void param
    {
        return AddBigSlider(parameter, sz.x, sz.y, format);
    }

    //--------------------------------------------------------------
    inline bool AddBigSlider(ofParameter<int>& parameter, ImVec2 sz, string format = OFX_IM_FORMAT_SLIDERS_INT)
    // button but using a bool not void param
    //inline bool AddBigSlider(ofParameter<int>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), string format = OFX_IM_FORMAT_SLIDERS)// button but using a bool not void param
    {
        return AddBigSlider(parameter, sz.x, sz.y, format);
    }


    //--------

    // H Sliders

    // TODO: move label on top/bottom
    //--------------------------------------------------------------
    inline bool AddHSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false,
                           bool bNoNumber = false)
    {
        bool bChanged = false;
        auto tmpRef = parameter.get();
        string name;
        if (bNoName) { name = ""; }
        else name = parameter.getName();

        //TODO: remove after '##'
        bool bHasID = ofIsStringInString(name, "##");
        if (bHasID)
        {
            auto ss = ofSplitString(name, "##", true, true);
            name = ss[0];
        }

        float w = ImGui::GetContentRegionAvail().x;
        float h = ImGui::GetContentRegionAvail().y;
        float spcx = ImGui::GetStyle().ItemSpacing.x;
        float spcy = ImGui::GetStyle().ItemSpacing.y;
        if (sz.x == -1) sz.x = w - spcx;
        if (sz.y == -1) sz.y = h - spcy;

        ImGui::PushID(("##HSLIDER" + name).c_str());
        {
            if (!bNoName)
            {
                ImGui::Text("%s", name.c_str());
                name = "";
            }

            string format;
            if (bNoNumber) format = "";
            else format = OFX_IM_FORMAT_SLIDERS;

            bChanged = AddBigSlider(parameter, sz.x, sz.y, name, format.c_str());
        }
        ImGui::PopID();

        return bChanged;
    }

    //-

    // TODO: marked as range limits..

    // This is custom widget. A one controllable value slider 
    // with 2 values used as limits.
    // can be used to show a kind of looped ranged.
    // it's colored using a red alpha rectangle too.

    //--------------------------------------------------------------
    inline bool AddHSliderRanged2(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), float rmin = 0.1f,
                                  float rmax = 0.9f, bool bNoName = false, bool bNoNumber = false)
    {
        bool bChanged = false;
        auto tmpRef = parameter.get();
        string name;
        if (bNoName) { name = ""; }
        else name = parameter.getName();

        //TODO: remove after '##'
        bool bHasID = ofIsStringInString(name, "##");
        if (bHasID)
        {
            auto ss = ofSplitString(name, "##", true, true);
            name = ss[0];
        }

        float w = ImGui::GetContentRegionAvail().x;
        float h = ImGui::GetContentRegionAvail().y;
        float spcx = ImGui::GetStyle().ItemSpacing.x;
        float spcy = ImGui::GetStyle().ItemSpacing.y;
        if (sz.x == -1) sz.x = w - spcx;
        if (sz.y == -1) sz.y = h - spcy;

        //-

        // markers zones
        float x1, x2, y1, y2;
        float gap, yy, ww, hh;

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetCursorScreenPos();

        // lines
        float linew = 2.f;
        float linea = 0.4f;
        ImVec4 cm = ImVec4(0.0f, 0.0f, 0.0f, linea);
        auto _cm = ImGui::GetColorU32(cm);

        float ra = 0.1f;
        ImVec4 cr = ImVec4(1.0f, 0.0f, 0.0f, ra);
        auto _cr = ImGui::GetColorU32(cr);
        float gap2 = 5;

        // kind of workaround bc I dont know where is the bellow slider height...

        //ww = ofxImGuiSurfing::getPanelWidth();
        ww = sz.x;
        hh = sz.y;
        //hh = ofxImGuiSurfing::getWidgetsHeightRelative();
        //hh = ofxImGuiSurfing::getPanelHeight();

        gap = 4;

        x1 = p.x + ww * rmin;
        x2 = p.x + ww * rmax;
        y1 = p.y - gap;
        y2 = y1 + hh * 3 - 2;

        //-

        ImGui::PushID(("##HSLIDERRNG" + name).c_str());
        {
            if (!bNoName)
            {
                ImGui::Text("%s", name.c_str());
                name = "";
            }

            string format;
            if (bNoNumber) format = "";
            else format = OFX_IM_FORMAT_SLIDERS;

            // big slider
            bChanged = AddBigSlider(parameter, sz.x, sz.y, name, format.c_str());

            // red rectangle
            ImDrawFlags flags = ImDrawFlags_None;
            draw_list->AddRectFilled(ImVec2(x1, y1 + gap2), ImVec2(x2, y2 - 4), _cr, 0, flags);

            // limit lines
            draw_list->AddLine(ImVec2(x1, y1), ImVec2(x1, y2), _cm, linew);
            draw_list->AddLine(ImVec2(x2, y1), ImVec2(x2, y2), _cm, linew);
        }
        ImGui::PopID();

        return bChanged;
    }

    //-

    //--------------------------------------------------------------
    inline bool AddHSliderRanged(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), float rmin = 0.1f,
                                 float rmax = 0.9f, bool bNoName = false, bool bNoNumber = false)
    {
        bool bChanged = false;
        auto tmpRef = parameter.get();
        string name;
        if (bNoName) { name = ""; }
        else name = parameter.getName();

        //TODO: remove after '##'
        bool bHasID = ofIsStringInString(name, "##");
        if (bHasID)
        {
            auto ss = ofSplitString(name, "##", true, true);
            name = ss[0];
        }

        float w = ImGui::GetContentRegionAvail().x;
        float h = ImGui::GetContentRegionAvail().y;
        float spcx = ImGui::GetStyle().ItemSpacing.x;
        float spcy = ImGui::GetStyle().ItemSpacing.y;
        if (sz.x == -1) sz.x = w - spcx;
        if (sz.y == -1) sz.y = h - spcy;

        //-

        // markers zones
        float x1, x2, y1, y2;
        float gap, yy, ww, hh;

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetCursorScreenPos();

        // lines
        float linew = 2.f;
        float linea = 0.4f;
        ImVec4 cm = ImVec4(0.0f, 0.0f, 0.0f, linea);
        auto _cm = ImGui::GetColorU32(cm);

        // kind of workaround bc I dont know where is the bellow slider height...

        //ww = ofxImGuiSurfing::getPanelWidth();
        ww = sz.x;
        hh = sz.y;
        //hh = ofxImGuiSurfing::getWidgetsHeightRelative();
        //hh = ofxImGuiSurfing::getPanelHeight();

        gap = 4;

        x1 = p.x + ww * rmin;
        x2 = p.x + ww * rmax;
        y1 = p.y - gap;
        y2 = y1 + hh * 3 - 2;

        //-

        ImGui::PushID(("##HSLIDERRNG" + name).c_str());
        {
            if (!bNoName)
            {
                ImGui::Text("%s", name.c_str());
                name = "";
            }

            string format;
            if (bNoNumber) format = "";
            else format = OFX_IM_FORMAT_SLIDERS;

            bChanged = AddBigSlider(parameter, sz.x, sz.y, name, format.c_str());

            draw_list->AddLine(ImVec2(x1, y1), ImVec2(x1, y2), _cm, linew);
            draw_list->AddLine(ImVec2(x2, y1), ImVec2(x2, y2), _cm, linew);
        }
        ImGui::PopID();

        return bChanged;
    }

    //-

    // Int. cloned from Float
    //--------------------------------------------------------------
    inline bool AddHSlider(ofParameter<int>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false,
                           bool bNoNumber = false)
    {
        bool bChanged = false;
        auto tmpRef = parameter.get();
        string name;
        if (bNoName) { name = ""; }
        else name = parameter.getName();

        //TODO: remove after '##'
        bool bHasID = ofIsStringInString(name, "##");
        if (bHasID)
        {
            auto ss = ofSplitString(name, "##", true, true);
            name = ss[0];
        }

        //const float gap = 0;//fix oversize

        float w = ImGui::GetContentRegionAvail().x;
        float h = ImGui::GetContentRegionAvail().y;
        float spcx = ImGui::GetStyle().ItemSpacing.x;
        float spcy = ImGui::GetStyle().ItemSpacing.y;
        if (sz.x == -1) sz.x = w - spcx;
        if (sz.y == -1) sz.y = h - spcy;

        ImGui::PushID(("##HSLIDER" + name).c_str());
        {
            if (!bNoName)
            {
                ImGui::Text("%s", name.c_str());
                name = ""; //-> to do not label name again. the right one to the fader
            }

            string format;
            if (bNoNumber) format = "";
            else format = OFX_IM_FORMAT_SLIDERS_INT;

            bChanged = AddBigSlider(parameter, sz.x, sz.y, name, format.c_str());
        }
        ImGui::PopID();

        return bChanged;
    }


    //------

    // V Sliders

    // TODO: move name label on top/bottom or inside the slider..

    /*
    //TODO: templating
    //--------------------------------------------------------------
    template<typename ParameterType>
    inline bool AddVSlider(ofParameter<ParameterType>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false, bool bNoNumber = false)
    {
        // default ImVec2 (-1,-1) is full panel shape.

        auto tmpRef = parameter.get();
        string name = parameter.getName();
        bool bChanged = false;

        const auto& info = typeid(ParameterType);
        if (info == typeid(float)) // float
        {
        }
        else if (info == typeid(int)) // Int
        {
        }
        else { // unknown types
            ofLogWarning(__FUNCTION__) << "Could not add wheel control to element " << name;
            return false;
        }

        if ((sz.x == -1) || (sz.y == -1))
        {
            float w = ImGui::GetContentRegionAvail().x;
            float h = ImGui::GetContentRegionAvail().y;
            float spcx = ImGui::GetStyle().ItemSpacing.x;
            float spcy = ImGui::GetStyle().ItemSpacing.y;
            if (sz.x == -1) sz.x = w - spcx;
            if (sz.y == -1) sz.y = h - spcy;
        }

        ImGui::PushID(("##VSLIDER" + name).c_str());
        {
            if (bNoName) {
                name = "";
            }
            else {
                ImGui::Text(name.c_str());//doubles name to the top left
            }

            string format;

            if (info == typeid(float)) // float
            {
                if (bNoNumber) format = "";
                else format = OFX_IM_FORMAT_SLIDERS;

                if (ImGui::VSliderFloat(name.c_str(), sz, &tmpRef, (float)parameter.getMin(), (float)parameter.getMax(), format.c_str()))
                {
                    parameter.set(tmpRef);
                    bChanged = true;
                }
            }
            else if (info == typeid(int)) // Int
            {
                if (bNoNumber) format = "";
                else format = "";
                //else format = "%d";

                if (ImGui::VSliderInt(name.c_str(), sz, &tmpRef, (int)parameter.getMin(), (int)parameter.getMax(), format.c_str()))
                {
                    parameter.set(tmpRef);
                    bChanged = true;
                }
            }
        }
        ImGui::PopID();

        //TODO: collides with namespaces.. ?
        //IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(parameter);

        return bChanged;
    }
    */


    // Floating Big V Slider
    //TODO: add name and number over the grab knob!
    // big text label.
    //--------------------------------------------------------------
    inline bool AddVSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false,
                           bool bNoNumber = false)
    {
        // default ImVec2 (-1,-1) is full panel shape.

        bool bChanged = false;
        auto tmpRef = parameter.get();
        string name = parameter.getName();

        //TODO: remove after '##'
        bool bHasID = ofIsStringInString(name, "##");
        if (bHasID)
        {
            auto ss = ofSplitString(name, "##", true, true);
            name = ss[0];
        }

        //if ((sz.x == -1) || (sz.y == -1))
        //{
        //	float w = ImGui::GetContentRegionAvail().x;
        //	float h = ImGui::GetContentRegionAvail().y;
        //	float spcx = ImGui::GetStyle().ItemSpacing.x;
        //	float spcy = ImGui::GetStyle().ItemSpacing.y;
        //	if (sz.x == -1) sz.x = w - spcx;
        //	if (sz.y == -1) sz.y = h - 2 * spcy;
        //}

        if (sz.x == -1)
        {
            float w = ImGui::GetContentRegionAvail().x;
            sz.x = w;
            //if (sz.x == -1) sz.x = w;
            //float spcx = ImGui::GetStyle().ItemSpacing.x;
            //if (sz.x == -1) sz.x = w - spcx;
        }
        if (sz.y == -1)
        {
            //TODO:
            float spcy = ImGui::GetStyle().ItemSpacing.y;
            float h = ImGui::GetContentRegionAvail().y;
            //sz.y = h - 2 * spcy;
            float offset = bNoName ? 0 : (2 * spcy);
            sz.y = h - 1 * spcy - offset;

            //float h = ImGui::GetFrameHeight();
            //sz.y = h * 5;
        }

        //--

        ImGui::PushID(("##VSLIDER" + name).c_str());
        {
            ImGui::BeginGroup();

            if (bNoName)
            {
                name = "";
            }
            else
            {
                ImGui::Text("%s", name.c_str()); //doubles name
                //ImGui::SameLine();
            }

            string format;
            if (bNoNumber) format = "";
            else format = OFX_IM_FORMAT_SLIDERS;

            name = ""; //clear to not draw again right after the fader
            if (ImGui::VSliderFloat(name.c_str(), sz, &tmpRef, parameter.getMin(), parameter.getMax(), format.c_str()))
            {
                parameter.set(tmpRef);
                bChanged = true;
            }

            ImGui::EndGroup();
        }
        ImGui::PopID();

        //TODO: collides with namespaces.. ?
        //IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(parameter);

        return bChanged;
    }

    // Int
    //--------------------------------------------------------------
    inline bool AddVSlider(ofParameter<int>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false,
                           bool bNoNumber = false)
    {
        //TODO:
        //default (-1,-1) is full panel shape

        bool bChanged = false;
        auto tmpRef = parameter.get();
        string name = parameter.getName();

        //TODO: remove after '##'
        bool bHasID = ofIsStringInString(name, "##");
        if (bHasID)
        {
            auto ss = ofSplitString(name, "##", true, true);
            name = ss[0];
        }

        if ((sz.x == -1) || (sz.y == -1))
        {
            float w = ImGui::GetContentRegionAvail().x;
            float h = ImGui::GetContentRegionAvail().y;
            float spcx = ImGui::GetStyle().ItemSpacing.x;
            float spcy = ImGui::GetStyle().ItemSpacing.y;
            if (sz.x == -1) sz.x = w - spcx;
            if (sz.y == -1) sz.y = h - spcy;
        }

        ImGui::PushID(("##VSLIDER" + name).c_str());
        {
            ImGui::BeginGroup();

            if (bNoName)
            {
                name = "";
            }
            else
            {
                ImGui::Text("%s", name.c_str());
                //ImGui::SameLine();
            }

            string format;
            if (bNoNumber)format = "";
            else format = "%d";

            name = ""; //clear to not draw again right after the fader
            if (ImGui::VSliderInt(name.c_str(), sz, &tmpRef, parameter.getMin(), parameter.getMax(), format.c_str()))
            {
                parameter.set(tmpRef);
                bChanged = true;
            }

            ImGui::EndGroup();
        }
        ImGui::PopID();

        //TODO:
        //IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(parameter);

        return bChanged;
    }


    //--------

    // Drag

    //--------------------------------------------------------------
    inline bool AddDragFloatSlider(ofParameter<float>& parameter/*, float w = 100*/)
    // button but using a bool not void param
    {
        bool bChanged = false;
        auto tmpRef = parameter.get();
        string name = parameter.getName();
        float v_speed = 0.001f; //1ms

        //TODO: remove after '##'
        bool bHasID = ofIsStringInString(name, "##");
        if (bHasID)
        {
            auto ss = ofSplitString(name, "##", true, true);
            name = ss[0];
        }

        string n = "##DRAGSLIDERfloat" + name + ofToString(1);
        ImGui::PushID(n.c_str());

        //bool ImGui::DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
        if (ImGui::DragFloat(name.c_str(), &tmpRef, v_speed, parameter.getMin(), parameter.getMax()))
        {
            parameter.set(tmpRef);
            bChanged = true;
        }

        ImGui::PopID();

        return bChanged;
    }
};


//----


// used ?

//// v slider
//
//namespace ofxImGuiSurfing
//{
//	//TODO:
//	//bLabel 
//
//	bool AddVSlider2(ofParameter<float>& parameter, ImVec2 &size, bool bLabel = true);
//	bool AddVSlider2(std::string label, ofParameter<float>& parameter, ImVec2 &size, bool bLabel = true);
//}
//
////--------------------------------------------------------------
//inline bool ofxImGuiSurfing::AddVSlider2(ofParameter<float>& parameter, ImVec2& size, bool bLabel)
//{
//	auto tmpRef = parameter.get();
//
//	if (ImGui::VSliderFloat(GetUniqueName2(parameter), size, &tmpRef, parameter.getMin(), parameter.getMax(), OFX_IM_FORMAT_SLIDERS, ImGuiSliderFlags_None))
//	{
//		parameter.set(tmpRef);
//		return true;
//	}
//	return false;
//}
//
////--------------------------------------------------------------
//inline bool ofxImGuiSurfing::AddVSlider2(std::string label, ofParameter<float>& parameter, ImVec2& size, bool bLabel)
//{
//	auto tmpRef = parameter.get();
//	if (ImGui::VSliderFloat(GetUniqueName2(label), size, &tmpRef, parameter.getMin(), parameter.getMax(), OFX_IM_FORMAT_SLIDERS, ImGuiSliderFlags_None))
//	{
//		parameter.set(tmpRef);
//		return true;
//	}
//	return false;
//}
