#pragma once

#include "ofMain.h"


//TODO: reuse mouse wheel methods from ofxSurfingImGui
// collides with scope troubles..
//#include "ofxSurfingImGui.h"
//#include "ofxSurfing_ImGui_ofHelpers.h"
//ofParameter<bool> bMouseWheel{ "MouseWheel", true };
//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(parameter);
//if (bMouseWheel) ofxImGuiSurfing::AddMouseWheel(parameter);


#include "ofxImGui.h"
#include "imgui_internal.h"

#include "imgui-knobs.h"

using namespace ImGui;

enum ImGuiKnobType {
	OFX_IMGUI_KNOB_TICKKNOB = 0,
	OFX_IMGUI_KNOB_DOTKNOB,
	OFX_IMGUI_KNOB_WIPERKNOB,
	OFX_IMGUI_KNOB_WIPERONLYKNOB,
	OFX_IMGUI_KNOB_WIPERDOTKNOB,
	OFX_IMGUI_KNOB_STEPPEDKNOB,
	OFX_IMGUI_KNOB_SPACEKNOB
};

//#define SPEED_RATIO 250

//-

namespace ofxImGuiSurfing
{
	//--------------------------------------------------------------
	template<typename ParameterType>
	/*inline*/ bool AddKnobStyled(ofParameter<ParameterType>& parameter, ImGuiKnobType type = OFX_IMGUI_KNOB_TICKKNOB, float size = 0, string format = "-1", ImGuiKnobFlags flags = 0, float speed = 0)
	{
		auto tmpRef = parameter.get();
		string n = parameter.getName();
		const auto& info = typeid(ParameterType);

		bool b = false;
		bool bUnknown = false;

		if (info == typeid(float)) // Float
		{
			if (format == "-1") format = "%.1f";
		}
		else if (info == typeid(int)) // Int
		{
			if (format == "-1") format = "%i";
		}
		else { // Unknown Types
			bUnknown = true;
			ofLogWarning(__FUNCTION__) << "Could not add a Styled Knob control to element " << parameter.getName() << " bc this type!";
			return false;
		}

		//--

		//// Fix speed bug
		//if (speed == -1)
		//{
		//	speed = (abs)(parameter.getMax() - parameter.getMin()) / (float)SPEED_RATIO;
		//}

		// Drag horizontal
		if (flags == 0)
		{
			flags = ImGuiKnobFlags_DragHorizontal;
		}

		if (info == typeid(float)) // Float
		{
			if (type == OFX_IMGUI_KNOB_TICKKNOB) b = ImGuiKnobs::Knob(n.c_str(), (float *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Tick, size, flags);
			else if (type == OFX_IMGUI_KNOB_DOTKNOB) b = ImGuiKnobs::Knob(n.c_str(), (float *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Dot, size, flags);
			else if (type == OFX_IMGUI_KNOB_WIPERKNOB) b = ImGuiKnobs::Knob(n.c_str(), (float *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Wiper, size, flags);
			else if (type == OFX_IMGUI_KNOB_WIPERONLYKNOB) b = ImGuiKnobs::Knob(n.c_str(), (float *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperOnly, size, flags);
			else if (type == OFX_IMGUI_KNOB_WIPERDOTKNOB) b = ImGuiKnobs::Knob(n.c_str(), (float *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperDot, size, flags);
			else if (type == OFX_IMGUI_KNOB_STEPPEDKNOB) b = ImGuiKnobs::Knob(n.c_str(), (float *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Stepped, size, flags);
			else if (type == OFX_IMGUI_KNOB_SPACEKNOB) b = ImGuiKnobs::Knob(n.c_str(), (float *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Space, size, flags);
		}
		else if (info == typeid(int)) // Int
		{
			if (type == OFX_IMGUI_KNOB_TICKKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), (int *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Tick, size, flags);
			else if (type == OFX_IMGUI_KNOB_DOTKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), (int *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Dot, size, flags);
			else if (type == OFX_IMGUI_KNOB_WIPERKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), (int *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Wiper, size, flags);
			else if (type == OFX_IMGUI_KNOB_WIPERONLYKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), (int *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperOnly, size, flags);
			else if (type == OFX_IMGUI_KNOB_WIPERDOTKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), (int *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperDot, size, flags);
			else if (type == OFX_IMGUI_KNOB_STEPPEDKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), (int *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Stepped, size, flags);
			else if (type == OFX_IMGUI_KNOB_SPACEKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), (int *)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Space, size, flags);
		}

		//-

		//TODO: 
		// Mouse wheel control
		//if(0)
		{
			float resolution;
			resolution = (abs)(parameter.getMax() - parameter.getMin()) / 100.f; // 100 steps for all the param range
			//resolution = 0.1f; // hardcoded to 0.1

			bool bCtrl = ImGui::GetIO().KeyCtrl; // ctrl to fine tunning

			ImGui::SetItemUsingMouseWheel();
			if (ImGui::IsItemHovered())
			{
				float wheel = ImGui::GetIO().MouseWheel;
				if (wheel)
				{
					if (ImGui::IsItemActive()) ImGui::ClearActiveID();
					else
					{
						if (info == typeid(float)) // Float
						{
							parameter += wheel * (bCtrl ? resolution : resolution * 10);
							parameter = ofClamp(parameter, parameter.getMin(), parameter.getMax()); // clamp
						}
						else if (info == typeid(int)) // Int
						{
							if (bCtrl)
							{
								int step = MAX((int)(resolution), 1);//minim 1 unit
								parameter += wheel * step;
								parameter = (int)ofClamp(parameter, parameter.getMin(), parameter.getMax()); // clamp
							}
							else
							{
								parameter += wheel * (int)(resolution * 10);
								parameter = (int)ofClamp(parameter, parameter.getMin(), parameter.getMax()); // clamp
							}
						}
					}
				}
			}
		}

		//-

		if (b)
		{
			parameter.set(tmpRef);
			return true;
		}

		return false;
	}
}

//--

////--------------------------------------------------------------
//inline const char * GetUniqueName2(ofAbstractParameter& parameter)
//{
//	return (parameter.getName().c_str());
//}

////--------------------------------------------------------------
//inline const char * GetUniqueName2(const std::string& candidate)
//{
//	//std::string result = candidate;
//	//while (std::find(windowOpen.usedNames.top().begin(), windowOpen.usedNames.top().end(), result) != windowOpen.usedNames.top().end())
//	//{
//	//	result += " ";
//	//}
//	//windowOpen.usedNames.top().push_back(result);
//	//return windowOpen.usedNames.top().back().c_str();
//	return candidate.c_str();
//}

//--
