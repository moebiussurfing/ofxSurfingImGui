#pragma once
#include "ofxImGui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imconfig.h"
#define M_PI 3.14159265358979323846264338327950288

//#include "ofGLBaseTypes.h"
//#include "ofParameter.h"
//#include "ofRectangle.h"
//#include "ofTexture.h"
//#include "ofGLBaseTypes.h"
//#include "imgui.h"
//
//static const int kImGuiMargin = 10;
//
//
//
//
namespace ofxImGui
{
//    bool RangeSliderFloat(const char* label, float* v1, float* v2, float v_min, float v_max, const char* display_format = "(%.3f, %.3f)", float power = 1.0f);

    //-----

	//    
	//    bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values);
	//    bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values);
	//
	//    
	//	struct WindowOpen
	//	{
	//		std::stack<std::vector<std::string>> usedNames;
	//		std::shared_ptr<ofParameter<bool>> parameter;
	//		bool value;
	//	};
	//
	//	struct Settings
	//	{
	//		Settings();
	//
	//		ofVec2f windowPos;
	//		ofVec2f windowSize;
	//		bool lockPosition;
	//		
	//		bool mouseOverGui;
	//		bool windowBlock;
	//		int treeLevel;
	//
	//		ofRectangle totalBounds;
	//		ofRectangle screenBounds;
	//	};
	//
	//	static WindowOpen windowOpen;
	//
	//	bool IsMouseOverGui();
	//
	//	const char * GetUniqueName(ofAbstractParameter& parameter);
	//	const char * GetUniqueName(const std::string& candidate);
	//
	//	void SetNextWindow(Settings& settings);
	//	bool BeginWindow(ofParameter<bool>& parameter, Settings& settings, bool collapse = true);
	//	bool BeginWindow(const std::string& name, Settings& settings, bool collapse = true, bool * open = nullptr);
	//	bool BeginWindow(const std::string& name, Settings& settings, ImGuiWindowFlags flags, bool * open = nullptr);
	//	void EndWindow(Settings& settings);
	//
	//	bool BeginTree(ofAbstractParameter& parameter, Settings& settings);
	//	bool BeginTree(const std::string& name, Settings& settings);
	//	void EndTree(Settings& settings);
	//
	//  void AddGroup(ofParameterGroup& group, Settings& settings);
	//
	//#if OF_VERSION_MINOR >= 10
	//	bool AddParameter(ofParameter<glm::ivec2>& parameter);
	//	bool AddParameter(ofParameter<glm::ivec3>& parameter);
	//	bool AddParameter(ofParameter<glm::ivec4>& parameter);
	//
	//	bool AddParameter(ofParameter<glm::vec2>& parameter);
	//	bool AddParameter(ofParameter<glm::vec3>& parameter);
	//	bool AddParameter(ofParameter<glm::vec4>& parameter);
	//#endif
	//
	//	bool AddParameter(ofParameter<ofVec2f>& parameter);
	//	bool AddParameter(ofParameter<ofVec3f>& parameter);
	//	bool AddParameter(ofParameter<ofVec4f>& parameter);
	//
	//	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha = true);
	//	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha = true);
	//	
	//	bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars = 255, bool multiline = false);
	//
	//	bool AddParameter(ofParameter<void>& parameter);
	//
	//	template<typename ParameterType>
	//	bool AddParameter(ofParameter<ParameterType>& parameter);
	//
	//	template<typename ParameterType>
	//	bool AddParameter(std::string overridelabel, ofParameter<ParameterType>& parameter);
	//
	//
	//	bool AddRadio(ofParameter<int>& parameter, std::vector<std::string> labels, int columns = 1);
	//	bool AddCombo(ofParameter<int>& parameter, std::vector<std::string> labels);
	//	bool AddCombo(std::string overrideLabel, ofParameter<int>& parameter, std::vector<std::string> labels);
	//	bool AddStepper(ofParameter<int>& parameter, int step = 1, int stepFast = 100);
	//	bool AddKnob(ofParameter<float>& parameter);
	//	bool AddKnob(ofParameter<float>& parameter, float zeroRef);
	//	bool AddKnob(std::string label, ofParameter<float>& parameter);
	//	bool AddKnob(std::string label, ofParameter<float>& parameter, float zeroRef);
	//
	//	bool AddVSlider(ofParameter<float>& parameter, ImVec2 &size);
	//
	//	bool AddVSlider(std::string label, ofParameter<float>& parameter, ImVec2 &size);
	//
	//	bool AddRange(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, int speed = 1);
	//	bool AddRange(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, float speed = 0.01f);
	//#if OF_VERSION_MINOR >= 10
	//	bool AddRange(const std::string& name, ofParameter<glm::vec2>& parameterMin, ofParameter<glm::vec2>& parameterMax, float speed = 0.01f);
	//	bool AddRange(const std::string& name, ofParameter<glm::vec3>& parameterMin, ofParameter<glm::vec3>& parameterMax, float speed = 0.01f);
	//	bool AddRange(const std::string& name, ofParameter<glm::vec4>& parameterMin, ofParameter<glm::vec4>& parameterMax, float speed = 0.01f);
	//#endif
	//
	//#if OF_VERSION_MINOR >= 10
	//	bool AddValues(const std::string& name, std::vector<glm::ivec2>& values, int minValue, int maxValue);
	//	bool AddValues(const std::string& name, std::vector<glm::ivec3>& values, int minValue, int maxValue);
	//	bool AddValues(const std::string& name, std::vector<glm::ivec4>& values, int minValue, int maxValue);
	//
	//	bool AddValues(const std::string& name, std::vector<glm::vec2>& values, float minValue, float maxValue);
	//	bool AddValues(const std::string& name, std::vector<glm::vec3>& values, float minValue, float maxValue);
	//	bool AddValues(const std::string& name, std::vector<glm::vec4>& values, float minValue, float maxValue);
	//#endif
	//
	//	bool AddValues(const std::string& name, std::vector<ofVec2f>& values, float minValue, float maxValue);
	//	bool AddValues(const std::string& name, std::vector<ofVec3f>& values, float minValue, float maxValue);
	//	bool AddValues(const std::string& name, std::vector<ofVec4f>& values, float minValue, float maxValue);
	//
	//	template<typename DataType>
	//	bool AddValues(const std::string& name, std::vector<DataType>& values, DataType minValue, DataType maxValue);
	//
	//	void AddImage(ofBaseHasTexture& hasTexture, const ofVec2f& size);
	//	void AddImage(ofTexture& texture, const ofVec2f& size);
	//	
	//    bool AddDrag(ofParameter<float>& parameter, float speed = 0.01);
	//    bool AddDrag(ofParameter<int>& parameter, float speed = 0.01);
	//}
	//
	//static ImTextureID GetImTextureID(ofTexture& texture)
	//{
	//    return (ImTextureID)(uintptr_t)texture.texData.textureID;
	//}
	//
	//static ImTextureID GetImTextureID(ofBaseHasTexture& hasTexture)
	//{
	//    
	//    return GetImTextureID(hasTexture.getTexture());
	//}
	//
	//static ImTextureID GetImTextureID(GLuint glID)
	//{
	//    
	//    return (ImTextureID)(uintptr_t)glID;
	//
	//}
	//
	////--------------------------------------------------------------
	//template<typename ParameterType>
	//bool ofxImGui::AddParameter(ofParameter<ParameterType>& parameter)
	//{
	//	auto tmpRef = parameter.get();
	//	const auto& info = typeid(ParameterType);
	//	if (info == typeid(float))
	//	{
	//		if (ImGui::SliderFloat(GetUniqueName(parameter), (float *)&tmpRef, parameter.getMin(), parameter.getMax()))
	//		{
	//			parameter.set(tmpRef);
	//			return true;
	//		}
	//		return false;
	//	}
	//	if (info == typeid(int))
	//	{
	//		if (ImGui::SliderInt(GetUniqueName(parameter), (int *)&tmpRef, parameter.getMin(), parameter.getMax()))
	//		{
	//			parameter.set(tmpRef);
	//			return true;
	//		}
	//		return false;
	//	}
	//	if (info == typeid(bool))
	//	{
	//		if (ImGui::Checkbox(GetUniqueName(parameter), (bool *)&tmpRef))
	//		{
	//			parameter.set(tmpRef);
	//			return true;
	//		}
	//		return false;
	//	}
	//
	//	ofLogVerbose(__FUNCTION__) << "Could not create GUI element for type " << info.name();
	//	//ofLogWarning(__FUNCTION__) << "Could not create GUI element for type " << info.name();
	//	return false;
	//}
	//
	//template<typename ParameterType>
	//bool ofxImGui::AddParameter(std::string overridelabel, ofParameter<ParameterType>& parameter)
	//{
	//	auto tmpRef = parameter.get();
	//	const auto& info = typeid(ParameterType);
	//	if (info == typeid(float))
	//	{
	//		if (ImGui::SliderFloat(GetUniqueName(overridelabel), (float *)&tmpRef, parameter.getMin(), parameter.getMax()))
	//		{
	//			parameter.set(tmpRef);
	//			return true;
	//		}
	//		return false;
	//	}
	//	if (info == typeid(int))
	//	{
	//		if (ImGui::SliderInt(GetUniqueName(overridelabel), (int *)&tmpRef, parameter.getMin(), parameter.getMax()))
	//		{
	//			parameter.set(tmpRef);
	//			return true;
	//		}
	//		return false;
	//	}
	//	if (info == typeid(bool))
	//	{
	//		if (ImGui::Checkbox(GetUniqueName(overridelabel), (bool *)&tmpRef))
	//		{
	//			parameter.set(tmpRef);
	//			return true;
	//		}
	//		return false;
	//	}
	//
	//	ofLogVerbose(__FUNCTION__) << "Could not create GUI element for type " << info.name();
	//	//ofLogWarning(__FUNCTION__) << "Could not create GUI element for type " << info.name();
	//	return false;
	//}
	//
	////--------------------------------------------------------------
	//template<typename DataType>
	//bool ofxImGui::AddValues(const std::string& name, std::vector<DataType>& values, DataType minValue, DataType maxValue)
	//{
	//	auto result = false;
	//	const auto& info = typeid(DataType);
	//	for (int i = 0; i < values.size(); ++i)
	//	{
	//		const auto iname = name + " " + ofToString(i);
	//		if (info == typeid(float))
	//		{
	//			result |= ImGui::SliderFloat(GetUniqueName(iname), *values[i], minValue, maxValue);
	//		}
	//		else if (info == typeid(int))
	//		{
	//			result |= ImGui::SliderInt(GetUniqueName(iname), *values[i], minValue, maxValue);
	//		}
	//		else if (info == typeid(bool))
	//		{
	//			result |= ImGui::Checkbox(GetUniqueName(iname), *values[i]);
	//		}
	//		else
	//		{
	//			ofLogVerbose("Gui::AddValues") << "Could not create GUI element for type " << info.name();
	//			//ofLogWarning("Gui::AddValues") << "Could not create GUI element for type " << info.name();
	//			return false;
	//		}
	//	}
	//	return result;
	//}

	//----

	//TODO:
	// knob from https://github.com/yumataesu/ImGui_Widgets
	// https://github.com/yumataesu/ofxImGui_v3/blob/master/src/Helper.cpp
	//example:
	//static float val = 0.0;
	//ofxImGui::Knob("value", &val, 0, 1); ImGui::SameLine();
	//ImGui::KnobNeedleTrail("value", &val, 0, 1);
	//--------------------------------------------------------------
	static inline bool Knob(const char* label, float* value_p, float minv, float maxv) {
		ImGuiStyle& style = ImGui::GetStyle();
		//style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
		//style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
		//style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);

		float sz = 36.0f;

		float line_height = ImGui::GetTextLineHeight();

		ImVec2 p = ImGui::GetCursorScreenPos();
		float radio = sz * 0.5f;
		ImVec2 center = ImVec2(p.x + radio, p.y + radio);
		float val1 = (value_p[0] - minv) / (maxv - minv);
		char textval[32];
		ImFormatString(textval, IM_ARRAYSIZE(textval), "%04.1f", value_p[0]);

		ImVec2 textpos = p;
		float gamma = M_PI / 4.0f;//0 value in knob
		float alpha = (M_PI - gamma)*val1*2.0f + gamma;

		float x2 = -sinf(alpha)*radio + center.x;
		float y2 = cosf(alpha)*radio + center.y;

		ImGui::InvisibleButton(label, ImVec2(sz, sz + line_height + style.ItemInnerSpacing.y));

		bool is_active = ImGui::IsItemActive();
		bool is_hovered = ImGui::IsItemHovered();
		bool touched = false;

		if (is_active) {
			touched = true;
			ImVec2 mp = ImGui::GetIO().MousePos;
			alpha = atan2f(mp.x - center.x, center.y - mp.y) + M_PI;
			//alpha = MAX(gamma, MIN(2.0f*M_PI - gamma, alpha));
			//alpha = ImMax(gamma, ImMin(2.0f*M_PI - gamma, alpha));
			float value = 0.5f*(alpha - gamma) / (M_PI - gamma);
			value_p[0] = value * (maxv - minv) + minv;
		}

		ImVec2 offset = ImVec2(0, 25);

		ImU32 col32 = ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
		ImU32 col32line = ImGui::GetColorU32(ImGuiCol_SliderGrabActive);
		ImU32 col32text = ImGui::GetColorU32(ImGuiCol_Text);
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->AddCircleFilled(center, radio, col32, 16);
		draw_list->AddLine(center, ImVec2(x2, y2), col32line, 3);
		draw_list->AddText(ImVec2(p.x, p.y + sz + style.ItemInnerSpacing.y), col32text, textval);
		draw_list->AddText(ImVec2(p.x, p.y + sz + style.ItemInnerSpacing.y + 20), col32text, label);

		//style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.10f, 0.38f, 0.68f);
		//style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.59f, 0.66f, 1.00f);
		//style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);

		return touched;
	}

};
