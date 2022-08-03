
#pragma once

/*

ofParameter Helpers to easely render different widgets styles for each ofParma types.

TODO:
+ mouse wheel for multi dim params

*/

#include "ofxImGui.h"

#include "ofxSurfing_ImGui_Widgets.h"
#include "ofxSurfing_ImGui_WidgetsTypesConstants.h"

namespace ofxImGuiSurfing
{
	//--

	// Tree folders

	//--------------------------------------------------------------
	inline bool BeginTree(string label, bool open = true, ImGuiTreeNodeFlags flagsTree = ImGuiTreeNodeFlags_Framed)
	{
		if (open) flagsTree += ImGuiTreeNodeFlags_DefaultOpen;

		return (ImGui::TreeNodeEx(label.c_str(), flagsTree));
	}

	//--------------------------------------------------------------
	inline void EndTree()
	{
		ImGui::TreePop();
	}

	//----

	//TODO: 
	//--------------------------------------------------------------
	inline bool GetMouseWheel()
	{
		ImGui::SetItemUsingMouseWheel();
		bool bReturn = false;

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
					bReturn = true;
				}
			}
		}

		return bReturn;
	}

	// Adds mouse wheel control to the last previous param widget (templated float/int)
	//--------------------------------------------------------------
	template<typename ParameterType>
	inline void AddMouseWheel(ofParameter<ParameterType>& param, float resolution = -1)
	{
		bool bUnknown = false;
		bool bIsVoid = false;
		bool bIsbool = false;
		bool bIsInt = false;
		bool bIsFloat = false;
		bool bIsMultiDim = false;
		bool bIsDim2 = false;
		bool bIsDim3 = false;
		bool bIsDim4 = false;

		const auto& info = typeid(ParameterType);

		if (info == typeid(float)) // FLOAT
		{
			bIsFloat = true;
		}
		else if (info == typeid(int)) // INT
		{
			bIsInt = true;
		}
		else if (info == typeid(bool)) // BOOL
		{
			bIsbool = true;
		}
		else if (info == typeid(void)) // VOID
		{
			bIsVoid = true;
		}

		//TODO:
		else if (info == typeid(ofDefaultVec2))
		{
			bIsMultiDim = true;
			bIsDim2 = true;
		}
		else if (info == typeid(ofDefaultVec3))
		{
			bIsMultiDim = true;
			bIsDim3 = true;
		}
		else if (info == typeid(ofDefaultVec4))
		{
			bIsMultiDim = true;
			bIsDim4 = true;
		}

		// Unknown Types
		else
		{
			bUnknown = true;

			ofLogWarning(__FUNCTION__) << "Could not add mouse wheel to " << param.getName();

			return;
		}

		//--

		{
			bool bCtrl = ImGui::GetIO().KeyCtrl; // ctrl to fine tunning

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
						// BOOL
						if (bIsbool) {
//							ofParameter<bool> p = param.cast<bool>();
                            ofParameter<bool> p = dynamic_cast<ofParameter<bool>& >(param);
                            p = !p.get();
						}

						// VOID
						else if (bIsVoid) {
//							ofParameter<void> p = param.cast<void>();
                            ofParameter<void> p = dynamic_cast<ofParameter<void>& >(param);
                            p.trigger();
						}

						//TODO:
						// must be fixed bc each dim slider could work independently...
						// MULTIDIM
						else if (bIsMultiDim)
						{
							/*
							if (resolution == -1)
							{
								//TODO:
								// hardcoded to 0.1 bc each dim could be different scale..
								resolution = 0.1f;
							}

							if (bIsDim2)
							{
								ofParameter<glm::vec2> p = param.cast<glm::vec2>();
								p += wheel * (bCtrl ? resolution : resolution * 10);
								p = ofClamp(p, p.getMin(), p.getMax()); // clamp
							}
							else if (bIsDim3)
							{
								ofParameter<glm::vec3> p = param.cast<glm::vec3>();
								p += wheel * (bCtrl ? resolution : resolution * 10);
								p = ofClamp(p, p.getMin(), p.getMax()); // clamp
							}
							else if (bIsDim2)
							{
								ofParameter<glm::vec4> p = param.cast<glm::vec4>();
								p += wheel * (bCtrl ? resolution : resolution * 10);
								p = ofClamp(p, p.getMin(), p.getMax()); // clamp
							}
							*/
						}

						// INT
						else if (bIsInt)
						{
//							ofParameter<int> p = param.cast<int>();
                            ofParameter<int> p = dynamic_cast<ofParameter<int>& >(param);
                            
							if (resolution == -1)
							{
								resolution = (p.getMax() - p.getMin()) / 100.f;
								// 100 steps for all the param range
							}

							p += wheel * (bCtrl ? resolution : resolution * 10);
							p = ofClamp(p, p.getMin(), p.getMax()); // clamp
						}

						// FLOAT
						else if (bIsFloat)
						{
//							ofParameter<float> p = param.cast<float>();
                            ofParameter<float> p = dynamic_cast<ofParameter<float>& >(param);
                            
							if (resolution == -1)
							{
								resolution = (p.getMax() - p.getMin()) / 100.f;
								// 100 steps for all the param range
							}

							p += wheel * (bCtrl ? resolution : resolution * 10);
							p = ofClamp(p, p.getMin(), p.getMax()); // clamp
						}
					}
				}
			}
		}
	}

	//--------------------------------------------------------------
	inline void AddTooltip(std::string text, bool bEnabled = true)//call after the pop up trigger widget
	{
		if (!bEnabled) return;

		//if (IsItemHovered() && GImGui->HoveredIdTimer > 1000) // delayed
		//if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 500) // delayed // not work ?
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextWrapped(text.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//----------------------

	// ofParameter's Helpers

	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen);

#if OF_VERSION_MINOR >= 10
	bool AddParameter(ofParameter<glm::ivec2>& parameter, bool bfoldered = false);
	bool AddParameter(ofParameter<glm::ivec3>& parameter, bool bfoldered = false);
	bool AddParameter(ofParameter<glm::ivec4>& parameter, bool bfoldered = false);

	bool AddParameter(ofParameter<glm::vec2>& parameter, bool bsplit = false, bool bfoldered = false); // split each arg to big sliders. make a folder container.
	bool AddParameter(ofParameter<glm::vec3>& parameter, bool bsplit = false, bool bfoldered = false); // split each arg to big sliders. make a folder container.
	bool AddParameter(ofParameter<glm::vec4>& parameter, bool bsplit = false, bool bfoldered = false); // split each arg to big sliders. make a folder container.
#endif

	//TODO:
	bool AddParameter(ofParameter<ofVec2f>& parameter);
	bool AddParameter(ofParameter<ofVec3f>& parameter);
	bool AddParameter(ofParameter<ofVec4f>& parameter);

	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha = true);
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha = true);

	//TODO:
	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha, ImGuiColorEditFlags flags);
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha, ImGuiColorEditFlags flags);

	bool AddParameter(ofParameter<ofRectangle>& parameter);

	bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars = 255, bool multiline = false);

	bool AddParameter(ofParameter<void>& parameter, float width = 0);

	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& parameter, std::string format = "%.3f");

	//--

	template<typename ParameterType>
	bool AddText(ofParameter<ParameterType>& parameter, bool label = true);

	bool AddRadio(ofParameter<int>& parameter, std::vector<std::string> labels, int columns = 1);
	bool AddCombo(ofParameter<int>& parameter, std::vector<std::string> labels);

	//-

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

	bool AddStepper(ofParameter<int>& parameter, int step = -1, int stepFast = -1);
	bool AddStepper(ofParameter<float>& parameter, float step = -1, float stepFast = -1);

	//--------------------------------------------------------------
	inline bool AddStepperInt(ofParameter<int>& parameter)
	{
		bool bChanged = false;
		auto tmpRefi = parameter.get();
		const ImU32 u32_one = 1;
		static bool inputs_step = true;

		string name = parameter.getName();
		string n = "##STEPPERint" + name;// +ofToString(1);
		ImGui::PushID(n.c_str());

		IMGUI_SUGAR__STEPPER_WIDTH_PUSH;

		//if (ImGui::InputScalar(parameter.getName().c_str(), ImGuiDataType_U32, (int*)&tmpRefi, inputs_step ? &u32_one : NULL, NULL, "%u"))

		if (ImGui::InputScalar(parameter.getName().c_str(), ImGuiDataType_S32, (int*)&tmpRefi, inputs_step ? &u32_one : NULL, NULL, "%d"))
		{
			tmpRefi = ofClamp(tmpRefi, parameter.getMin(), parameter.getMax());
			parameter.set(tmpRefi);

			bChanged = true;
		}

		ImGui::PopID();

		IMGUI_SUGAR__STEPPER_WIDTH_POP;

		return bChanged;
	}

	//--------------------------------------------------------------
	inline bool AddStepperFloat(ofParameter<float>& p)
	{
		float step = (p.getMax() - p.getMin()) / 100.f;
		float stepFast = 100.f * step;

		auto tmpRef = p.get();
		bool bReturn = false;

		string name = p.getName();
		string n = "##STEPPERfloat" + name;// +ofToString(1);
		ImGui::PushID(n.c_str());

		IMGUI_SUGAR__STEPPER_WIDTH_PUSH;

		if (ImGui::InputFloat(p.getName().c_str(), (float*)&tmpRef, step, stepFast))
		{
			tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax());//clamp
			p.set(tmpRef);
			bReturn = true;
		}

		IMGUI_SUGAR__STEPPER_WIDTH_POP;

		ImGui::PopID();

		return bReturn;
	}

	//----

	// These are mainly the original ofxImGui methods:
	// Clean of Styles with the default styles.
	//--------------------------------------------------------------
	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& parameter, std::string format)
	{
		//std::string format = "%.3f";//TODO:

		auto tmpRef = parameter.get();
		const auto& info = typeid(ParameterType);

		// FLOAT

		if (info == typeid(float))
		{
			IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
			if (ImGui::SliderFloat((parameter.getName().c_str()), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), format.c_str()))
			{
				parameter.set(tmpRef);
				IMGUI_SUGAR__WIDGETS_POP_WIDTH;
				return true;
			}
			IMGUI_SUGAR__WIDGETS_POP_WIDTH;
			return false;
		}

		// INT

		else if (info == typeid(int))
		{
			IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
			if (ImGui::SliderInt((parameter.getName().c_str()), (int*)&tmpRef, parameter.getMin(), parameter.getMax()))
			{
				parameter.set(tmpRef);

				IMGUI_SUGAR__WIDGETS_POP_WIDTH;
				return true;
			}

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;
			return false;
		}

		// BOOL

		else if (info == typeid(bool))
		{
			if (ImGui::Checkbox((parameter.getName().c_str()), (bool*)&tmpRef))
			{
				parameter.set(tmpRef);
				return true;
			}

			return false;
		}

		// UNKNOWN

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

	//--

	//--------------------------------------------------------------
	template<typename DataType>
	bool AddValues(const std::string& name, std::vector<DataType>& values, DataType minValue, DataType maxValue)
	{
		auto result = false;
		const auto& info = typeid(DataType);
		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

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

				IMGUI_SUGAR__WIDGETS_POP_WIDTH;

				return false;
			}
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return result;
	}

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

	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values);

} // namespace ofxImGuiSurfing
