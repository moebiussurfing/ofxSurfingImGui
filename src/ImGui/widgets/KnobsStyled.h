/*

	TODO:
	add double click to reset.

*/

//--

#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"
#include "GuiConstants.h"

#include "imgui-knobs.h" // All the magic is here!

using namespace ImGui;


//#define SPEED_RATIO 250

//-

namespace ofxImGuiSurfing
{
	//--------------------------------------------------------------
	template<typename ParameterType>
	inline bool AddKnobStyled(ofParameter<ParameterType>& parameter, SurfingGuiTypes type = OFX_IM_KNOB_TICKKNOB, float size = 0, string format = "-1", SurfingGuiFlags flags = 0, float speed = 0)
	{
		ImGuiKnobFlags _flags = 0;

		// Activate the enabled flags
		if (flags & SurfingGuiFlags_NoInput) _flags += ImGuiKnobFlags_NoInput;
		if (flags & SurfingGuiFlags_NoTitle) _flags += ImGuiKnobFlags_NoTitle;
		if (flags & SurfingGuiFlags_TooltipValue) _flags += ImGuiKnobFlags_ValueTooltip;
		if (flags & SurfingGuiFlags_DragHorizontal) _flags += ImGuiKnobFlags_DragHorizontal;

		auto tmpRef = parameter.get();
		string n = parameter.getName();
		const auto& info = typeid(ParameterType);

		bool b = false;
		bool bUnknown = false;

		//--

		// Float

		if (info == typeid(float))
		{
			if (format == "-1") format = "%.1f";//one decimal by default
		}

		//--

		// Int

		else if (info == typeid(int))
		{
			if (format == "-1") format = "%i";//no decimal by default
		}

		//--

		// Unknown Types

		else 
		{
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

		//--

		// Float

		if (info == typeid(float))
		{
			if (type == OFX_IM_KNOB_TICKKNOB) b =
				ImGuiKnobs::Knob(n.c_str(), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Tick, size, _flags);

			else if (type == OFX_IM_KNOB_DOTKNOB) b =
				ImGuiKnobs::Knob(n.c_str(), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Dot, size, _flags);

			else if (type == OFX_IM_KNOB_WIPERKNOB) b =
				ImGuiKnobs::Knob(n.c_str(), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Wiper, size, _flags);

			else if (type == OFX_IM_KNOB_WIPERONLYKNOB) b =
				ImGuiKnobs::Knob(n.c_str(), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperOnly, size, _flags);

			else if (type == OFX_IM_KNOB_WIPERDOTKNOB) b =
				ImGuiKnobs::Knob(n.c_str(), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperDot, size, _flags);

			else if (type == OFX_IM_KNOB_STEPPEDKNOB) b =
				ImGuiKnobs::Knob(n.c_str(), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Stepped, size, _flags);

			else if (type == OFX_IM_KNOB_SPACEKNOB) b =
				ImGuiKnobs::Knob(n.c_str(), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Space, size, _flags);
		}

		//--

		// Int

		else if (info == typeid(int))
		{
			if (type == OFX_IM_KNOB_TICKKNOB) b =
				ImGuiKnobs::KnobInt(n.c_str(), (int*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Tick, size, _flags);

			else if (type == OFX_IM_KNOB_DOTKNOB) b =
				ImGuiKnobs::KnobInt(n.c_str(), (int*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Dot, size, _flags);

			else if (type == OFX_IM_KNOB_WIPERKNOB) b =
				ImGuiKnobs::KnobInt(n.c_str(), (int*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Wiper, size, _flags);

			else if (type == OFX_IM_KNOB_WIPERONLYKNOB) b =
				ImGuiKnobs::KnobInt(n.c_str(), (int*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperOnly, size, _flags);

			else if (type == OFX_IM_KNOB_WIPERDOTKNOB) b =
				ImGuiKnobs::KnobInt(n.c_str(), (int*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperDot, size, _flags);

			else if (type == OFX_IM_KNOB_STEPPEDKNOB) b =
				ImGuiKnobs::KnobInt(n.c_str(), (int*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Stepped, size, _flags);

			else if (type == OFX_IM_KNOB_SPACEKNOB) b =
				ImGuiKnobs::KnobInt(n.c_str(), (int*)&tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Space, size, _flags);
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