
#pragma once

#include "ofxImGui.h"

#include "ofxSurfing_ImGui_Widgets.h"
#include "ofxSurfing_ImGui_WidgetsTypesConstants.h"
//#include "ofxSurfing_ImGui_WidgetsTypes.h"
//#include "ofxSurfing_ImGui_LayoutHelpers.h"


//--

// workaround
// Some macro sugar to help fix how sliders force autoresize the panel widths.
// It's a 'rare behaviour' that I am trying to correct doing this.

// A. Relative to panel width
#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x / 2);
//#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x-200);
#define IMGUI_SUGAR_SLIDER_WIDTH_POP ImGui::PopItemWidth();

//// B. Using absolute size
//#define IMGUI_LABELS_WIDTH_DEFAULT 95
//#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ImGui::PushItemWidth(-IMGUI_LABELS_WIDTH_DEFAULT);
//#define IMGUI_SUGAR_SLIDER_WIDTH_POP ImGui::PopItemWidth();

//// C. To bypass and do nothing.
//#define IMGUI_SUGAR_SLIDER_WIDTH_PUSH ;
//#define IMGUI_SUGAR_SLIDER_WIDTH_POP ;

//--


namespace ofxImGuiSurfing
{
	//--

	// ofParams Helpers

	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values);

	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None);
	//void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None);
	//void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None | ImGuiTreeNodeFlags_DefaultOpen, ofxSurfing_ImGui_WidgetsTypes::SurfingImGuiTypesGroups typeGroup = ofxSurfing_ImGui_WidgetsTypes::OFX_IM_GROUP_DEFAULT);

#if OF_VERSION_MINOR >= 10
	bool AddParameter(ofParameter<glm::ivec2>& parameter);
	bool AddParameter(ofParameter<glm::ivec3>& parameter);
	bool AddParameter(ofParameter<glm::ivec4>& parameter);

	bool AddParameter(ofParameter<glm::vec2>& parameter, bool bsplit = false);//split each arg to big sliders
	bool AddParameter(ofParameter<glm::vec3>& parameter, bool bsplit = false);
	bool AddParameter(ofParameter<glm::vec4>& parameter, bool bsplit = false);
#endif

	bool AddParameter(ofParameter<ofVec2f>& parameter);
	bool AddParameter(ofParameter<ofVec3f>& parameter);
	bool AddParameter(ofParameter<ofVec4f>& parameter);
	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha = true);
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha = true);

	bool AddParameter(ofParameter<ofRectangle>& parameter);

	bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars = 255, bool multiline = false);

	bool AddParameter(ofParameter<void>& parameter, float width = 0);

	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& parameter);

	template<typename ParameterType>
	bool AddText(ofParameter<ParameterType>& parameter, bool label = true);

	bool AddRadio(ofParameter<int>& parameter, std::vector<std::string> labels, int columns = 1);
	bool AddCombo(ofParameter<int>& parameter, std::vector<std::string> labels);
	bool AddStepper(ofParameter<int>& parameter, int step = 1, int stepFast = 100);

	bool AddSlider(ofParameter<float>& parameter, const char* format = "%.3f", float power = 1.0f);

	bool AddRange(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, int speed = 1);
	bool AddRange(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, float speed = 0.01f);

#if OF_VERSION_MINOR >= 10
	bool AddRange(const std::string& name, ofParameter<glm::vec2>& parameterMin, ofParameter<glm::vec2>& parameterMax, float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec3>& parameterMin, ofParameter<glm::vec3>& parameterMax, float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec4>& parameterMin, ofParameter<glm::vec4>& parameterMax, float speed = 0.01f);
#endif

#if OF_VERSION_MINOR >= 10
	bool AddValues(const std::string& name, std::vector<glm::ivec2>& values, int minValue = 0, int maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::ivec3>& values, int minValue = 0, int maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::ivec4>& values, int minValue = 0, int maxValue = 0);

	bool AddValues(const std::string& name, std::vector<glm::vec2>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::vec3>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::vec4>& values, float minValue = 0, float maxValue = 0);
#endif

	bool AddValues(const std::string& name, std::vector<ofVec2f>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<ofVec3f>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<ofVec4f>& values, float minValue = 0, float maxValue = 0);

	template<typename DataType>
	bool AddValues(const std::string& name, std::vector<DataType>& values, DataType minValue, DataType maxValue);

	void AddImage(const ofBaseHasTexture& hasTexture, const ofVec2f& size);
	void AddImage(const ofTexture& texture, const ofVec2f& size);

#if OF_VERSION_MINOR >= 10
	void AddImage(const ofBaseHasTexture& hasTexture, const glm::vec2& size);
	void AddImage(const ofTexture& texture, const glm::vec2& size);
#endif

	//----

	static ImTextureID GetImTextureID2(const ofTexture& texture)
	{
		return (ImTextureID)(uintptr_t)texture.texData.textureID;
	}

	static ImTextureID GetImTextureID2(const ofBaseHasTexture& hasTexture)
	{
		return GetImTextureID2(hasTexture.getTexture());
	}

	static ImTextureID GetImTextureID2(GLuint glID)
	{
		return (ImTextureID)(uintptr_t)glID;
	}

	//----

	// clean of styles
	//--------------------------------------------------------------
	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& parameter)
	{
		auto tmpRef = parameter.get();
		const auto& info = typeid(ParameterType);

		// float
		if (info == typeid(float))
		{
			IMGUI_SUGAR_SLIDER_WIDTH_PUSH;
			if (ImGui::SliderFloat((parameter.getName().c_str()), (float *)&tmpRef, parameter.getMin(), parameter.getMax()))
			{
				parameter.set(tmpRef);
				IMGUI_SUGAR_SLIDER_WIDTH_POP;
				return true;
			}
			IMGUI_SUGAR_SLIDER_WIDTH_POP;
			return false;
		}

		// int
		if (info == typeid(int))
		{
			IMGUI_SUGAR_SLIDER_WIDTH_PUSH;
			if (ImGui::SliderInt((parameter.getName().c_str()), (int *)&tmpRef, parameter.getMin(), parameter.getMax()))
			{
				parameter.set(tmpRef);

				IMGUI_SUGAR_SLIDER_WIDTH_POP;
				return true;
			}

			IMGUI_SUGAR_SLIDER_WIDTH_POP;
			return false;
		}

		// bool
		if (info == typeid(bool))
		{
			if (ImGui::Checkbox((parameter.getName().c_str()), (bool *)&tmpRef))
			{
				parameter.set(tmpRef);
				return true;
			}

			return false;
		}

					if (info.name() == "" || info.name() == " ")
		ofLogWarning(__FUNCTION__) << "Could not create GUI element for type " << info.name();

		return false;
	}

	//--

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool AddText(ofParameter<ParameterType>& parameter, bool label)
	{
		if (label)
		{
			ImGui::LabelText((parameter.getName().c_str()), ofToString(parameter.get()).c_str());
		}
		else
		{
			ImGui::Text(ofToString(parameter.get()).c_str());
		}

		return true;
	}

	//--------------------------------------------------------------
	template<typename DataType>
	bool AddValues(const std::string& name, std::vector<DataType>& values, DataType minValue, DataType maxValue)
	{
		auto result = false;
		const auto& info = typeid(DataType);
		IMGUI_SUGAR_SLIDER_WIDTH_PUSH;

		for (int i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);
			if (info == typeid(float))
			{
				result |= ImGui::SliderFloat(GetUniqueName2(iname), *values[i], minValue, maxValue);
			}
			else if (info == typeid(int))
			{
				result |= ImGui::SliderInt(GetUniqueName2(iname), *values[i], minValue, maxValue);
			}
			else if (info == typeid(bool))
			{

				result |= ImGui::Checkbox(GetUniqueName2(iname), *values[i]);
			}
			else
			{
				if (info.name() == "" || info.name() == " ")
					ofLogWarning(__FUNCTION__) << "Could not create GUI element for type " << info.name();
				IMGUI_SUGAR_SLIDER_WIDTH_POP;
				return false;
			}
		}

		IMGUI_SUGAR_SLIDER_WIDTH_POP;
		return result;
	}

} // namespace ofxImGuiSurfing
