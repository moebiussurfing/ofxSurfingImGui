
#pragma once

#include "ofxImGui.h"

// TODO:
// TESTING TOGGLE TYPES
#include "ofxSurfing_ImGui_WidgetsTypes.h"

//#define USE_FIX_BUG_2__WRONG_INDENT_UNLIMITED_GROW //-> choice between tree or collapsed group window
//#define USE_IM_GUI_INDENT //-> fails on su groups layout..


/*

	NOTE:

	This is a cleaner modified version of ImHelpers.h from the original ofxImGui with these modifications:

	- Deprecated GetUniqueName engine. Now using ImGui::PushId(1) | ImGui::PopID() for each parameter widget. [ BUG FAIL ]
	- Deprecated all old window/settings/tree management. Now much simpler and closer to raw ImGui.

	//-

	TODO:
	important BUG !

	should recreate a kind of the old ofxImGui getUniqueName or a count indexes of added params
	to use on ImGui::pushId(index) !
	why? bc when some widgets has the same name or maybe when you populate many times the same parameter
	i.e with different desing/widget type (slider/drag/stepper)

	That's a problem bc we need to star count the widgets when window begins.
	So we will need to create windows here like on ofxImGui ?

*/


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
	// unique name engine
	// NOTE: this engine seems that avoid duplicated names on the same group/tree
	// but we will use PushID too for each groups. This will allow to repeat a parameter several times
	// also in different groups/trees

	const char* GetUniqueName(ofAbstractParameter& parameter);
	const char* GetUniqueName(const std::string& candidate);

	//--

	struct WindowOpen
	{
		std::stack<std::vector<std::string>> usedNames;
		std::shared_ptr<ofParameter<bool>> parameter;
		bool value;
		int treeLevel = 0;
	};
	static WindowOpen windowOpen;

	//--

	// An extra begin/end pair
	// with snapping
	bool BeginWindow(std::string name = "Window", bool* p_open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
	void EndWindow();

	//--

	// names engine

	//--------------------------------------------------------------
	static void pushName()
	{
		//ofLogWarning(__FUNCTION__) << "-"; 

		// Push a new list of names onto the stack.
		windowOpen.usedNames.push(std::vector<std::string>());
	}

	//--------------------------------------------------------------
	static void popName()
	{
		//ofLogWarning(__FUNCTION__) << "-"; 
		windowOpen.usedNames.pop();
	}

	//--------------------------------------------------------------
	static void clearNames()
	{
		//ofLogWarning(__FUNCTION__) << "-"; 

		windowOpen.treeLevel = 0;
		// Unlink the referenced ofParameter.
		windowOpen.parameter.reset();
		// Clear the list of names from the stack.
		while (!windowOpen.usedNames.empty()) {
			windowOpen.usedNames.pop();
		}
	}

	//--

	// TODO:
	// TESTING CUSTOMIZE TYPES
	static ofxImGuiSurfing::SurfingTypes widgetsManager;

	//--

	enum SurfingTypesGroups
	{
		IM_GUI_GROUP_DEFAULT = 0,
		IM_GUI_GROUP_TREE_EX,
		IM_GUI_GROUP_TREE,
		IM_GUI_GROUP_COLLAPSED,
		IM_GUI_GROUP_SCROLLABLE,
		IM_GUI_GROUP_ONLY_FIRST_HEADER,
		IM_GUI_GROUP_HIDDE_ALL_HEADERS,
		IM_GUI_GROUP_AMOUNT
	};

	//--

	// ofParams helpers

	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values);

	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None | ImGuiTreeNodeFlags_DefaultOpen, SurfingTypesGroups typeGroup = IM_GUI_GROUP_DEFAULT);

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

	void Begin(const std::string& name);
	void End();

} // namespace ofxSurfing

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
} // namespace ofxSurfing

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
	//		if (ImGui::SliderFloat(GetUniqueName(parameter), (float *)&tmpRef, parameter.getMin(), parameter.getMax()))
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
	//		if (ImGui::SliderInt(GetUniqueName(parameter), (int *)&tmpRef, parameter.getMin(), parameter.getMax()))
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
	//		if (ImGui::Checkbox(GetUniqueName(parameter), (bool *)&tmpRef))
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

			// float
			if (info == typeid(float))
			{
				bool bReturn = false;
				ofParameter<float> &p = parameter.cast<float>();
				auto c = widgetsManager.getWidgetConf(p);

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
					if (ImGui::SliderFloat(GetUniqueName(parameter), (float *)&tmpRef, parameter.getMin(), parameter.getMax()))
					{
						parameter.set(tmpRef);
						bReturn = true;
					}
					else bReturn = false;
					ImGui::PopItemWidth();
					return bReturn;
				}
			}

			// int
			else if (info == typeid(int))
			{
				bool bReturn = false;
				ofParameter<int> &p = parameter.cast<int>();
				auto c = widgetsManager.getWidgetConf(p);

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
					if (ImGui::SliderInt(GetUniqueName(parameter), (int *)&tmpRef, parameter.getMin(), parameter.getMax()))
					{
						parameter.set(tmpRef);
						bReturn = true;
					}
					else bReturn = false;
					ImGui::PopItemWidth();

					return bReturn;
				}
			}

			// bool
			else if (info == typeid(bool))
			{
				bool bReturn = false;
				ofParameter<bool> &p = parameter.cast<bool>();
				auto c = widgetsManager.getWidgetConf(p);

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
					//if (ImGui::Checkbox(GetUniqueName(parameter), (bool *)&tmpRef))
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
			ImGui::LabelText(GetUniqueName(parameter), ofToString(parameter.get()).c_str());
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
				ofLogWarning(__FUNCTIONS__) << "Could not create GUI element for type " << info.name();
				return false;
			}
		}

		return result;
	}
} // namespace ofxSurfing
