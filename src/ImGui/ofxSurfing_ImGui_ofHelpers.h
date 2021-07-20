
#pragma once

#include "ofxImGui.h"

#include "ofxSurfing_ImGui_Widgets.h"

#include "ofxSurfing_ImGui_WidgetsTypes.h"
//#include "ofxSurfing_ImGui_LayoutHelpers.h"

//--

// TODO:
// should convert all this to a class ?
//class SurfingImGuiHelpers {
//public:
//	SurfingImGuiHelpers() {};
//	~SurfingImGuiHelpers() {};

//--

namespace ofxImGuiSurfing
{
	//--

	//ofxSurfing_ImGui_WidgetsTypes widgetsManager; // -> fails bc it seems it's instantiated many times..
	static ofxSurfing_ImGui_WidgetsTypes widgetsManager;
	
	//--

	// ofParams Helpers

	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values);

	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None | ImGuiTreeNodeFlags_DefaultOpen, ofxSurfing_ImGui_WidgetsTypes::SurfingImGuiTypesGroups typeGroup = ofxSurfing_ImGui_WidgetsTypes::OFX_IM_GROUP_DEFAULT);

#if OF_VERSION_MINOR >= 10
	bool AddParameter(ofParameter<glm::ivec2>& parameter);
	bool AddParameter(ofParameter<glm::ivec3>& parameter);
	bool AddParameter(ofParameter<glm::ivec4>& parameter);

	bool AddParameter(ofParameter<glm::vec2>& parameter);
	bool AddParameter(ofParameter<glm::vec3>& parameter);
	bool AddParameter(ofParameter<glm::vec4>& parameter);
#endif

	bool AddParameter(ofParameter<ofVec2f>& parameter);
	bool AddParameter(ofParameter<ofVec3f>& parameter);
	bool AddParameter(ofParameter<ofVec4f>& parameter);
	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha = true);
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha = true);

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

} // namespace ofxImGuiSurfing

//----

namespace ofxImGuiSurfing
{
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

} // namespace ofxImGuiSurfing

//----

namespace ofxImGuiSurfing
{
	//// clean of styles
	////--------------------------------------------------------------
	//template<typename ParameterType>
	//bool AddParameter(ofParameter<ParameterType>& parameter)
	//{
	//	auto tmpRef = parameter.get();
	//	const auto& info = typeid(ParameterType);
	//	if (info == typeid(float))
	//	{
	//		ImGui::PushItemWidth(WIDGET_PARAM_PADDING);
	//		if (ImGui::SliderFloat((parameter.getName().c_str()), (float *)&tmpRef, parameter.getMin(), parameter.getMax()))
	//		{
	//			parameter.set(tmpRef);
	//			ImGui::PopItemWidth();
	//			return true;
	//		}
	//		ImGui::PopItemWidth();
	//		return false;
	//	}
	//	if (info == typeid(int))
	//	{
	//		ImGui::PushItemWidth(WIDGET_PARAM_PADDING);
	//		if (ImGui::SliderInt((parameter.getName().c_str()), (int *)&tmpRef, parameter.getMin(), parameter.getMax()))
	//		{
	//			parameter.set(tmpRef);
	//			ImGui::PopItemWidth();
	//			return true;
	//		}
	//		ImGui::PopItemWidth();
	//		return false;
	//	}
	//	if (info == typeid(bool))
	//	{
	//		if (ImGui::Checkbox((parameter.getName().c_str()), (bool *)&tmpRef))
	//		{
	//			parameter.set(tmpRef);
	//			return true;
	//		}
	//		return false;
	//	}
	//	ofLogWarning(__FUNCTION__) << "Could not create GUI element for type " << info.name();
	//	return false;
	//}

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& parameter)
	{
		auto tmpRef = parameter.get();
		const auto& info = typeid(ParameterType);

		//--

		// customized styles
		{
			// B. if  there's a config already added for one or more parameters

			//-

			// float

			if (info == typeid(float))
			{
				bool bReturn = false;
                ofParameter<float> &p = parameter.template cast<float>();
				auto c = widgetsManager.getStyle(p);

				// if the parameter widget is not added explicitly, will populate it as the default appearance
				if (c.name != "-1")
				{
					bReturn = widgetsManager.Add(p, c.type, c.bSameLine, c.amtPerRow, c.spacing);

					return bReturn;
				}

				// default style
				else
				{
					ImGui::PushItemWidth(-WIDGET_PARAM_PADDING);
					if (ImGui::SliderFloat((parameter.getName().c_str()), (float *)&tmpRef, parameter.getMin(), parameter.getMax()))
					{
						parameter.set(tmpRef);
						bReturn = true;
					}
					else bReturn = false;
					ImGui::PopItemWidth();

					return bReturn;
				}
			}

			//-

			// int

			else if (info == typeid(int))
			{
				bool bReturn = false;
                ofParameter<int> &p = parameter.template cast<int>();
				auto c = widgetsManager.getStyle(p);

				// if the parameter widget is not added explicitly, will populate it as the default appearance
				if (c.name != "-1")
				{
					bReturn = widgetsManager.Add(p, c.type, c.bSameLine, c.amtPerRow, c.spacing);

					return bReturn;
				}

				// default style
				else
				{
					ImGui::PushItemWidth(-WIDGET_PARAM_PADDING);
					if (ImGui::SliderInt((parameter.getName().c_str()), (int *)&tmpRef, parameter.getMin(), parameter.getMax()))
					{
						parameter.set(tmpRef);
						bReturn = true;
					}
					else bReturn = false;
					ImGui::PopItemWidth();

					return bReturn;
				}
			}

			//-

			// bool

			else if (info == typeid(bool))
			{
				bool bReturn = false;
                ofParameter<bool> &p = parameter.template cast<bool>();
				auto c = widgetsManager.getStyle(p);

				// if the parameter widget is not added explicitly, will populate it as the default appearance
				if (c.name != "-1")
				{
					bReturn = widgetsManager.Add(p, c.type, c.bSameLine, c.amtPerRow, c.spacing);

					return bReturn;
				}

				// default style
				else
				{
					// Surfing customization
					bReturn = (AddBigToggle(p));

					// ofxImGui pattern
					//if (ImGui::Checkbox((parameter.getName().c_str()), (bool *)&tmpRef))
					//{
					//	parameter.set(tmpRef);
					//	bReturn = true;
					//}
					//else bReturn = false;

					return bReturn;
				}
			}
		}

		//--

		ofLogWarning(__FUNCTION__) << "Could not create ImGui element for type " << info.name();

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

		for (int i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);
			if (info == typeid(float))
			{
				result |= ImGui::SliderFloat(GetUniqueName(iname), *values[i], minValue, maxValue);
			}
			else if (info == typeid(int))
			{
				result |= ImGui::SliderInt(GetUniqueName(iname), *values[i], minValue, maxValue);
			}
			else if (info == typeid(bool))
			{

				result |= ImGui::Checkbox(GetUniqueName(iname), *values[i]);
			}
			else
			{
				ofLogWarning(/*__FUNCTIONS__*/) << "Could not create GUI element for type " << info.name();
				return false;
			}
		}

		return result;
	}

} // namespace ofxImGuiSurfing
