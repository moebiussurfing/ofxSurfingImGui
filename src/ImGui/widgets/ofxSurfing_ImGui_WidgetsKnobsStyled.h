//#pragma once
//
//#include "ofMain.h"
//
//#include "ofxImGui.h"
//#include "imgui_internal.h"
//
//#include "imgui-knobs.h"
//
//using namespace ImGui;
//
//enum ImGuiKnobType {
//	OFX_IMGUI_KNOB_TICKKNOB = 0,
//	OFX_IMGUI_KNOB_DOTKNOB,
//	OFX_IMGUI_KNOB_WIPERKNOB,
//	OFX_IMGUI_KNOB_WIPERONLYKNOB,
//	OFX_IMGUI_KNOB_WIPERDOTKNOB,
//	OFX_IMGUI_KNOB_STEPPEDKNOB,
//	OFX_IMGUI_KNOB_SPACEKNOB
//};
//
////-
//
//namespace ofxImGuiSurfing
//{
//	bool AddKnobStyled(ofParameter<float>& parameter, ImGuiKnobType type = OFX_IMGUI_KNOB_TICKKNOB, float size = 0, string format = "%.1f", ImGuiKnobFlags flags = 0, float speed = 1.f);
//	bool AddKnobStyled(ofParameter<int>& parameter, ImGuiKnobType type = OFX_IMGUI_KNOB_TICKKNOB, float size = 0, string format = "%i", ImGuiKnobFlags flags = 0, float speed = 1.f);
//
//	//-
//
//	////--------------------------------------------------------------
//	//inline const char * GetUniqueName2(ofAbstractParameter& parameter)
//	//{
//	//	return (parameter.getName().c_str());
//	//}
//
//	////--------------------------------------------------------------
//	//inline const char * GetUniqueName2(const std::string& candidate)
//	//{
//	//	//std::string result = candidate;
//	//	//while (std::find(windowOpen.usedNames.top().begin(), windowOpen.usedNames.top().end(), result) != windowOpen.usedNames.top().end())
//	//	//{
//	//	//	result += " ";
//	//	//}
//	//	//windowOpen.usedNames.top().push_back(result);
//	//	//return windowOpen.usedNames.top().back().c_str();
//	//	return candidate.c_str();
//	//}
//}
//
////--
//
//// Float Knob
//
////--------------------------------------------------------------
//inline bool ofxImGuiSurfing::AddKnobStyled(ofParameter<float>& parameter, ImGuiKnobType type, float size, string format, ImGuiKnobFlags flags, float speed)
//{
//	auto tmpRef = parameter.get();
//	string n = parameter.getName();
//	bool b = false;
//
//	// API
//	// if (ImGuiKnobs::Knob("Volume", &value, -6.0f, 6.0f, 0.1f, "%.1fdB", ImGuiKnobVariant_Tick)) {
//	// bool Knob(const char *label, float *p_value, float v_min, float v_max, float speed = 1.f, const char *format = NULL, ImGuiKnobVariant variant = ImGuiKnobVariant_Tick, float size = 0, ImGuiKnobFlags flags = 0, int steps = 10);
//	
//	if (type == OFX_IMGUI_KNOB_TICKKNOB) b = ImGuiKnobs::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Tick, size, flags);
//	else if (type == OFX_IMGUI_KNOB_DOTKNOB) b = ImGuiKnobs::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Dot, size, flags);
//	else if (type == OFX_IMGUI_KNOB_WIPERKNOB) b = ImGuiKnobs::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Wiper, size, flags);
//	else if (type == OFX_IMGUI_KNOB_WIPERONLYKNOB) b = ImGuiKnobs::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperOnly, size, flags);
//	else if (type == OFX_IMGUI_KNOB_WIPERDOTKNOB) b = ImGuiKnobs::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperDot, size, flags);
//	else if (type == OFX_IMGUI_KNOB_STEPPEDKNOB) b = ImGuiKnobs::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Stepped, size, flags);
//	else if (type == OFX_IMGUI_KNOB_SPACEKNOB) b = ImGuiKnobs::Knob(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Space, size, flags);
//
//	if (b)
//	{
//		parameter.set(tmpRef);
//		return true;
//	}
//
//	return false;
//}
//
////--
//
//// Int Knob
//
////--------------------------------------------------------------
//inline bool ofxImGuiSurfing::AddKnobStyled(ofParameter<int>& parameter, ImGuiKnobType type, float size, string format, ImGuiKnobFlags flags, float speed)
//{
//	auto tmpRef = parameter.get();
//	string n = parameter.getName();
//	bool b = false;
//
//	// API
//	// if (ImGuiKnobs::Knob("Volume", &value, -6.0f, 6.0f, 0.1f, "%.1fdB", ImGuiKnobVariant_Tick)) {
//	// bool Knob(const char *label, float *p_value, float v_min, float v_max, float speed = 1.f, const char *format = NULL, ImGuiKnobVariant variant = ImGuiKnobVariant_Tick, float size = 0, ImGuiKnobFlags flags = 0, int steps = 10);
//
//	if (type == OFX_IMGUI_KNOB_TICKKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Tick, size, flags);
//	else if (type == OFX_IMGUI_KNOB_DOTKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Dot, size, flags);
//	else if (type == OFX_IMGUI_KNOB_WIPERKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Wiper, size, flags);
//	else if (type == OFX_IMGUI_KNOB_WIPERONLYKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperOnly, size, flags);
//	else if (type == OFX_IMGUI_KNOB_WIPERDOTKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_WiperDot, size, flags);
//	else if (type == OFX_IMGUI_KNOB_STEPPEDKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Stepped, size, flags);
//	else if (type == OFX_IMGUI_KNOB_SPACEKNOB) b = ImGuiKnobs::KnobInt(n.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), speed, format.c_str(), ImGuiKnobVariant_Space, size, flags);
//
//
//	if (b)
//	{
//		parameter.set((int)tmpRef);
//		return true;
//	}
//
//	return false;
//}
