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
	//--------

	// Float
	//--------------------------------------------------------------
	inline bool AddBigSlider(ofParameter<float>& parameter, float w = -1, float h = -1, string name = "-1", string format = "%.3f")
	{
		if (w == -1) w = ImGui::GetContentRegionAvail().x; // full width
		if (h == -1) h = getWidgetsHeightUnit(); // one unit height

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
	inline bool AddBigSlider(ofParameter<float>& parameter, ImVec2 sz, string format = "%.3f")// button but using a bool not void param
	//inline bool AddBigSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), string format = "%.3f")// button but using a bool not void param
	{
		return AddBigSlider(parameter, sz.x, sz.y, format);
	}
	//--------------------------------------------------------------
	inline bool AddBigSlider(ofParameter<int>& parameter, ImVec2 sz, string format = "%.3f")// button but using a bool not void param
	//inline bool AddBigSlider(ofParameter<int>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), string format = "%.3f")// button but using a bool not void param
	{
		return AddBigSlider(parameter, sz.x, sz.y, format);
	}


	//--------

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
			if (!bNoName) {
				ImGui::Text(name.c_str());
				name = "";
			}

			string format;
			if (bNoNumber) format = "";
			else format = "%.3f";

			bChanged = AddBigSlider(parameter, sz.x, sz.y, name, format.c_str());
		}
		ImGui::PopID();

		return bChanged;
	}

	//-

	// TODO: marked as range limits..

	//--------------------------------------------------------------
	inline bool AddHSliderRanged(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), float rmin = 0.1f, float rmax = 0.9f, bool bNoName = false, bool bNoNumber = false)
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

		//-

		// markers zones
		float x1, x2, y1, y2;
		float gap, yy, ww, hh;

		//ww = ofxImGuiSurfing::getPanelWidth();
		ww = sz.x;
		hh = sz.y;
		//hh = ofxImGuiSurfing::getWidgetsHeightRelative();
		//hh = ofxImGuiSurfing::getPanelHeight();

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2 p = ImGui::GetCursorScreenPos();
		float linew = 3.f;
		float linea = 0.25f;
		ImVec4 cm = ImVec4(0.0f, 0.0f, 0.0f, linea);
		auto _cm = ImGui::GetColorU32(cm);

		//gap = 0;
		//ww -= 2 * gap;
		//x1 = p.x + gap;
		//x2 = x1 + ww;

		//gap = 10;
		//ww -= 2 * gap;

		x1 = p.x + ww * rmin;
		x2 = p.x + ww * rmax;
		y1 = p.y;
		y2 = y1 + hh; //* 2;//?

		//yy = p.y + 0.33 * hh;
		//yy = p.y + 0.66 * hh;

		//-

		ImGui::PushID(("##HSLIDERRNG" + name).c_str());
		{
			if (!bNoName) {
				ImGui::Text(name.c_str());
				name = "";
			}

			string format;
			if (bNoNumber) format = "";
			else format = "%.3f";

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
			if (!bNoName) {
				ImGui::Text(name.c_str());
				name = "";//-> to do not label name again. the right one to the fader
			}

			string format;
			if (bNoNumber) format = "";
			else format = "%.3f";

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
				else format = "%.3f";

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


	// Float
	//--------------------------------------------------------------
	inline bool AddVSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false, bool bNoNumber = false)
	{
		// default ImVec2 (-1,-1) is full panel shape.

		auto tmpRef = parameter.get();
		string name = parameter.getName();
		bool bChanged = false;

		if ((sz.x == -1) || (sz.y == -1))
		{
			float w = ImGui::GetContentRegionAvail().x;
			float h = ImGui::GetContentRegionAvail().y;
			float spcx = ImGui::GetStyle().ItemSpacing.x;
			float spcy = ImGui::GetStyle().ItemSpacing.y;
			if (sz.x == -1) sz.x = w - spcx;
			if (sz.y == -1) sz.y = h - 2 * spcy;
		}

		ImGui::PushID(("##VSLIDER" + name).c_str());
		{
			ImGui::BeginGroup();

			if (bNoName) {
				name = "";
			}
			else {
				ImGui::Text(name.c_str());//doubles name
				//ImGui::SameLine();
			}

			string format;
			if (bNoNumber) format = "";
			else format = "%.3f";

			name = "";//clear to not draw again right after the fader
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
	inline bool AddVSlider(ofParameter<int>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false, bool bNoNumber = false)
	{
		//TODO:
		//default (-1,-1) is full panel shape

		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();

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

			if (bNoName) {
				name = "";
			}
			else {
				ImGui::Text(name.c_str());
				//ImGui::SameLine();
			}

			string format;
			if (bNoNumber)format = "";
			else format = "%d";

			name = "";//clear to not draw again right after the fader
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
//	if (ImGui::VSliderFloat(GetUniqueName2(parameter), size, &tmpRef, parameter.getMin(), parameter.getMax(), "%.3f", ImGuiSliderFlags_None))
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
//	if (ImGui::VSliderFloat(GetUniqueName2(label), size, &tmpRef, parameter.getMin(), parameter.getMax(), "%.3f", ImGuiSliderFlags_None))
//	{
//		parameter.set(tmpRef);
//		return true;
//	}
//	return false;
//}