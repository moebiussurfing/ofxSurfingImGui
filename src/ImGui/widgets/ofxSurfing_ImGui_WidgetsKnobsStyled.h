#pragma once

#include "ofMain.h"

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

//-

namespace ofxImGuiSurfing
{
	bool AddKnobStyled(ofParameter<float>& parameter, ImGuiKnobType type = OFX_IMGUI_KNOB_TICKKNOB, float size = 0, string resolution = "%.1f");

	//TODO: fix decimal format wrong drag
	bool AddKnobStyled(ofParameter<int>& parameter, ImGuiKnobType type = OFX_IMGUI_KNOB_TICKKNOB, float size = 0, string resolution = "%.1f");

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
}

//--

// Float Knob

//--------------------------------------------------------------
inline bool ofxImGuiSurfing::AddKnobStyled(ofParameter<float>& parameter, ImGuiKnobType type, float size, string resolution)
{
	auto tmpRef = parameter.get();
	string n = parameter.getName();
	bool b = false;

	if (type == OFX_IMGUI_KNOB_TICKKNOB) b = ImGuiKnobs::TickKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_DOTKNOB) b = ImGuiKnobs::DotKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_WIPERKNOB) b = ImGuiKnobs::WiperKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_WIPERONLYKNOB) b = ImGuiKnobs::WiperOnlyKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_WIPERDOTKNOB) b = ImGuiKnobs::WiperDotKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_STEPPEDKNOB) b = ImGuiKnobs::SteppedKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_SPACEKNOB) b = ImGuiKnobs::SpaceKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);

	if (b)
	{
		parameter.set(tmpRef);
		return true;
	}

	return false;
}

//--

// Int Knob

//--------------------------------------------------------------
inline bool ofxImGuiSurfing::AddKnobStyled(ofParameter<int>& parameter, ImGuiKnobType type, float size, string resolution)
{
	float tmpRef = parameter.get();
	string n = parameter.getName();
	bool b = false;

	if (type == OFX_IMGUI_KNOB_TICKKNOB) b = ImGuiKnobs::TickKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_DOTKNOB) b = ImGuiKnobs::DotKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_WIPERKNOB) b = ImGuiKnobs::WiperKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_WIPERONLYKNOB) b = ImGuiKnobs::WiperOnlyKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_WIPERDOTKNOB) b = ImGuiKnobs::WiperDotKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_STEPPEDKNOB) b = ImGuiKnobs::SteppedKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);
	else if (type == OFX_IMGUI_KNOB_SPACEKNOB) b = ImGuiKnobs::SpaceKnob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), resolution.c_str(), size);

	if (b)
	{
		parameter.set((int)tmpRef);
		return true;
	}

	return false;
}
