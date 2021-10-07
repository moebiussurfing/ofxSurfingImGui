
#pragma once

#include "ofxImGui.h"

#include "ofxSurfing_ImGui_Widgets.h"
#include "ofxSurfing_ImGui_WidgetsTypesConstants.h"

namespace ofxImGuiSurfing
{
	//----

	// Adds mouse wheel control to the last orevioues param widget (templated float/int)

	//--------------------------------------------------------------
	template<typename ParameterType>
	/*static*/ inline void AddMouseWheel(ofParameter<ParameterType>& param, float resolution = -1)
	{
		bool bUnknown = false;

		const auto& info = typeid(ParameterType);
		if (info == typeid(float)) // float
		{
		}
		else if (info == typeid(int)) // Int
		{
		}
		else if (info == typeid(bool)) // Bool
		{
		}
		else { // unknown types
			bUnknown = true;
			ofLogWarning(__FUNCTION__) << "Could not add wheel control to element " << param.getName();
			return;
		}

		if (!bUnknown)
		{
			if (resolution == -1) {
				resolution = (param.getMax() - param.getMin()) / 100.f;//100 steps for all the param range
				//resolution = 0.1f;//hardcoded to 0.1
			}

			bool bCtrl = ImGui::GetIO().KeyCtrl;//ctrl to fine tunning

			ImGui::SetItemUsingMouseWheel();
			if (ImGui::IsItemHovered())
			{
				float wheel = ImGui::GetIO().MouseWheel;
				if (wheel)
				{
					if (ImGui::IsItemActive())
					{
						ImGui::ClearActiveID();
					}
					else
					{
						if (info == typeid(bool)) {//bool
							param = !param.get();
						}
						else {//float, int
							param += wheel * (bCtrl ? resolution : resolution * 10);
							param = ofClamp(param, param.getMin(), param.getMax());//clamp
						}
					}
				}
			}
		}
	}

	//----

	// ofParams Helpers

	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values);

	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None);

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

	// Image Textures
	//--------------------------------------------------------------
	static ImTextureID GetImTextureID2(const ofTexture& texture)
	{
		return (ImTextureID)(uintptr_t)texture.texData.textureID;
	}
	//--------------------------------------------------------------
	static ImTextureID GetImTextureID2(const ofBaseHasTexture& hasTexture)
	{
		return GetImTextureID2(hasTexture.getTexture());
	}
	//--------------------------------------------------------------
	static ImTextureID GetImTextureID2(GLuint glID)
	{
		return (ImTextureID)(uintptr_t)glID;
	}

	//----

	// These are mainly the original ofxImGui methods:
	// Clean of Styles with the default styles.
	//--------------------------------------------------------------
	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& parameter)
	{
		auto tmpRef = parameter.get();
		const auto& info = typeid(ParameterType);

		// float
		if (info == typeid(float))
		{
			IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
			if (ImGui::SliderFloat((parameter.getName().c_str()), (float *)&tmpRef, parameter.getMin(), parameter.getMax()))
			{
				parameter.set(tmpRef);
				IMGUI_SUGAR__SLIDER_WIDTH_POP;
				return true;
			}
			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return false;
		}

		// Int
		if (info == typeid(int))
		{
			IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
			if (ImGui::SliderInt((parameter.getName().c_str()), (int *)&tmpRef, parameter.getMin(), parameter.getMax()))
			{
				parameter.set(tmpRef);

				IMGUI_SUGAR__SLIDER_WIDTH_POP;
				return true;
			}

			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return false;
		}

		// Bool
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
		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;

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
				IMGUI_SUGAR__SLIDER_WIDTH_POP;
				return false;
			}
		}

		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return result;
	}

} // namespace ofxImGuiSurfing
