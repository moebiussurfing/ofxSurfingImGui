#pragma once

#include "ofMain.h"

// Useful links
// https://github.com/nem0/LumixEngine/blob/timeline_gui/external/imgui/imgui_user.inl#L814

// ImGui Widgets
// - Big Sliders

//------------------------------

#include "ofxImGui.h"
#include "imgui_internal.h"

#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_WidgetsTypesConstants.h"

#include "ofxSurfing_Timers.h"
//#include "ofxSurfingHelpers.h"

//#include "ofxSurfing_ImGui_ofHelpers.h"

//------------------------------

namespace ofxImGuiSurfing
{
	//----

	// Float
	//--------------------------------------------------------------
	inline bool AddBigSlider(ofParameter<float>& parameter, float w = -1, float h = -1, string name = "-1", string format = "%.3f")
	{
		if (w == -1) w = ImGui::GetContentRegionAvail().x;//full width
		if (h == -1) h = getWidgetsHeightUnit();//one unit height
		//if (h == -1) h = BUTTON_BIG_HEIGHT;//TODO: get widget height

		ImGuiSliderFlags flag = ImGuiSliderFlags_Logarithmic;

		bool bChanged = false;
		auto tmpRef = parameter.get();

		if (name == "-1") name = parameter.getName();

		//TODO: name label is duplicated..
		//TODO: make space for label..
		//if (name != "") sz.x = sz.x - 100;

		string n = "##BIGSLIDER" + name + ofToString(1);
		ImGui::PushID(n.c_str());
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(w, h));//doesn't uses the width..
			if (name == "") ImGui::PushItemWidth(w);//-> name != "" will enable standard aligned resizing with labels
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
	// Int. cloned from float.
	//--------------------------------------------------------------
	inline bool AddBigSlider(ofParameter<int>& parameter, float w = -1, float h = -1, string name = "-1", string format = "%.3f")
	{
		if (w == -1) w = ImGui::GetContentRegionAvail().x;//full width
		if (h == -1) h = getWidgetsHeightUnit();//one unit height
		//if (h == -1) h = BUTTON_BIG_HEIGHT;//TODO: get widget height

		ImGuiSliderFlags flag = ImGuiSliderFlags_Logarithmic;

		bool bChanged = false;
		auto tmpRef = parameter.get();

		if (name == "-1") name = parameter.getName();

		//TODO: name label is duplicated..
		//TODO: make space for label..
		//if (name != "") sz.x = sz.x - 100;

		string n = "##BIGSLIDER" + name + ofToString(1);
		ImGui::PushID(n.c_str());
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(w, h));//doesn't uses the width..
			if (name == "") ImGui::PushItemWidth(w);//-> name != "" will enable standard aligned resizing with labels
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
	inline bool AddBigSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), string format = "%.3f")// button but using a bool not void param
	{
		return AddBigSlider(parameter, sz.x, sz.y, format);
	}
	//--------------------------------------------------------------
	inline bool AddBigSlider(ofParameter<int>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), string format = "%.3f")// button but using a bool not void param
	{
		return AddBigSlider(parameter, sz.x, sz.y, format);
	}

	//----

	 // H Sliders

	// TODO: move label on top/bottom
	//--------------------------------------------------------------
	inline bool AddHSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false, bool bNoNumber = false)
	{
		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name;
		if (bNoName) { name = ""; }
		else name = parameter.getName();

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetContentRegionAvail().y;
		float spcx = ImGui::GetStyle().ItemSpacing.x;
		float spcy = ImGui::GetStyle().ItemSpacing.y;
		if (sz.x == -1) sz.x = w - spcx;
		if (sz.y == -1) sz.y = h - spcy;

		ImGui::PushID(("##HSLIDER" + name).c_str());
		{
			if (!bNoName) { ImGui::Text(name.c_str()); }

			string format;
			if (bNoNumber) format = "";
			else format = "%.3f";

			bChanged = AddBigSlider(parameter, sz.x, sz.y, name, format.c_str());
		}
		ImGui::PopID();

		//IMGUI_SUGAR_ADD_MOUSE_WHEEL_CONTROL2(parameter);
		//ofxImGuiSurfing::AddMouseWheel(parameter);
		//AddMouseWheel(parameter);

		return bChanged;
	}
	//int. cloned from float
	//--------------------------------------------------------------
	inline bool AddHSlider(ofParameter<int>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false, bool bNoNumber = false)
	{
		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name;
		if (bNoName) { name = ""; }
		else name = parameter.getName();

		//const float gap = 0;//fix oversize

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetContentRegionAvail().y;
		float spcx = ImGui::GetStyle().ItemSpacing.x;
		float spcy = ImGui::GetStyle().ItemSpacing.y;
		if (sz.x == -1) sz.x = w - spcx;
		if (sz.y == -1) sz.y = h - spcy;

		ImGui::PushID(("##HSLIDER" + name).c_str());
		{
			if (!bNoName) { ImGui::Text(name.c_str()); }

			string format;
			if (bNoNumber) format = "";
			else format = "%.3f";

			bChanged = AddBigSlider(parameter, sz.x, sz.y, name, format.c_str());
		}
		ImGui::PopID();

		//IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(parameter);

		return bChanged;
	}

	//----

	// V Sliders

	// TODO: move name label on top/bottom or inside the slider..
	
	// Float
	//--------------------------------------------------------------
	inline bool AddVSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false, bool bNoNumber = false)
	{
		//TODO:
		//default (-1,-1) is full panel shape

		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetContentRegionAvail().y;

		float spcx = ImGui::GetStyle().ItemSpacing.x;
		float spcy = ImGui::GetStyle().ItemSpacing.y;

		//ImGui::Dummy(ImVec2(0, spcy));//make top space

		//if (sz.x == -1) sz.x = w;
		//if (sz.y == -1) sz.y = h;
		if (sz.x == -1) sz.x = w - spcx;
		if (sz.y == -1) sz.y = h - spcy;

		//ImGui::BeginGroup();
		ImGui::PushID(("##VSLIDER" + name).c_str());

		if (bNoName) {
			name = "";
		}
		else {
			ImGui::Text(name.c_str());
		}

		string format;
		if (bNoNumber)format = "";
		else format = "%.3f";

		//bool ImGui::VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		if (ImGui::VSliderFloat(name.c_str(), sz, &tmpRef, parameter.getMin(), parameter.getMax(), format.c_str()))
		{
			parameter.set(tmpRef);

			bChanged = true;
		}

		ImGui::PopID();
		//ImGui::EndGroup();

		//TODO:
		//IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(parameter);

		return bChanged;
	}

	// Int
	//--------------------------------------------------------------
	inline bool AddVSlider(ofParameter<int>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false)
	{
		//TODO:
		//default is full panel shape

		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetContentRegionAvail().y;

		float spcx = ImGui::GetStyle().ItemSpacing.x;
		float spcy = ImGui::GetStyle().ItemSpacing.y;

		//if (sz.x == -1) sz.x = w;
		//if (sz.y == -1) sz.y = h;
		if (sz.x == -1) sz.x = w - spcx;
		if (sz.y == -1) sz.y = h - spcy;

		ImGui::PushID(("##VSLIDER" + name).c_str());
		if (bNoName) name = "";

		if (ImGui::VSliderInt(name.c_str(), sz, &tmpRef, parameter.getMin(), parameter.getMax()))
		{
			parameter.set(tmpRef);

			bChanged = true;
		}

		ImGui::PopID();

		//IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(parameter);

		return bChanged;
	}

	//----

	//--------------------------------------------------------------
	inline bool AddDragFloatSlider(ofParameter<float>& parameter/*, float w = 100*/)// button but using a bool not void param
	{
		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();
		float v_speed = 0.001f;//1ms

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
