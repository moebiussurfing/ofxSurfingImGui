#include "ofxSurfing_ImGui_ofHelpers.h"

//TODO:
// add customization for nested groups
// pass some list of arguments to customize items/groups to be rendered with differents design...
//https://github.com/Daandelange/ofxImGui/issues/6#issuecomment-832174921

//--

namespace ofxImGuiSurfing
{
	//--

	//--------------------------------------------------------------
	//void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags)
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags)
	{
		//TODO: now we are using ofxSurfing_ImGui_WidgetsTypes.h helpers!
		// but these methods should work too.

		if (!ImGui::TreeNode(group.getName().c_str()))
		{
			return;
		}

		//-

		for (auto parameter : group)
		{
			// Group.
			auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);
			if (parameterGroup)
			{
				// Recurse through contents.
				AddGroup(*parameterGroup, ImGuiTreeNodeFlags_None);
				continue;
			}

			// Parameter, try everything we know how to handle.
#if OF_VERSION_MINOR >= 10
			auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
			if (parameterVec2f)
			{
				ofxImGuiSurfing::AddParameter(*parameterVec2f);
				continue;
			}
			auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
			if (parameterVec3f)
			{
				ofxImGuiSurfing::AddParameter(*parameterVec3f);
				continue;
			}
			auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
			if (parameterVec4f)
			{
				ofxImGuiSurfing::AddParameter(*parameterVec4f);
				continue;
			}
#endif
			auto parameterOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(parameter);
			if (parameterOfVec2f)
			{
				ofxImGuiSurfing::AddParameter(*parameterOfVec2f);
				continue;
			}
			auto parameterOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(parameter);
			if (parameterOfVec3f)
			{
				ofxImGuiSurfing::AddParameter(*parameterOfVec3f);
				continue;
			}
			auto parameterOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(parameter);
			if (parameterOfVec4f)
			{
				ofxImGuiSurfing::AddParameter(*parameterOfVec4f);
				continue;
			}
			auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
			if (parameterFloatColor)
			{
				ofxImGuiSurfing::AddParameter(*parameterFloatColor);
				continue;
			}
			auto parameterFloat = std::dynamic_pointer_cast<ofParameter<float>>(parameter);
			if (parameterFloat)
			{
				ofxImGuiSurfing::AddParameter(*parameterFloat);
				continue;
			}
			auto parameterInt = std::dynamic_pointer_cast<ofParameter<int>>(parameter);
			if (parameterInt)
			{
				ofxImGuiSurfing::AddParameter(*parameterInt);
				continue;
			}
			auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
			if (parameterBool)
			{
				ofxImGuiSurfing::AddParameter(*parameterBool);
				continue;
			}

			ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName();
		}

		{
			// End tree.
			ImGui::TreePop();
		}
	}

	//--

//	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags, ofxSurfing_ImGui_WidgetsTypes::SurfingImGuiTypesGroups typeGroup)
//	{
//		//ofxImGuiSurfing::widgetsManager.refresh(); // is static -> not works
//
//		//-
//
//		for (auto parameter : group)
//		{
//			// group
//
//			auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);
//
//			if (parameterGroup) // detects nested groups
//			{
//				ImGui::PushID(parameterGroup->getName().c_str()); // -> finally fix unique id for repeated params inside many groups
//				{
//					if (typeGroup == ofxSurfing_ImGui_WidgetsTypes::OFX_IM_GROUP_ONLY_FIRST_HEADER)
//					{
//						ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
//					}
//					else
//					{
//						if (typeGroup == ofxSurfing_ImGui_WidgetsTypes::OFX_IM_GROUP_HIDDE_ALL_HEADERS)
//						{
//							ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
//						}
//
//						else if (typeGroup == ofxSurfing_ImGui_WidgetsTypes::OFX_IM_GROUP_COLLAPSED)
//						{
//							bool b = ImGui::CollapsingHeader(parameterGroup->getName().data(), flags);
//							if (b) ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
//						}
//
//						else if (typeGroup == ofxSurfing_ImGui_WidgetsTypes::OFX_IM_GROUP_DEFAULT)
//						{
//							//ImGui::Indent();
//
//							bool b = ImGui::CollapsingHeader(parameterGroup->getName().data(), flags);
//							if (b) ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
//
//							//ImGui::Unindent();
//						}
//
//						else if (typeGroup == ofxSurfing_ImGui_WidgetsTypes::OFX_IM_GROUP_TREE)
//						{
//							if (ImGui::TreeNode(parameterGroup->getName().data()))
//							{
//								//TODO:
//								//ImGui::Indent();
//
//								ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
//
//								//ImGui::Unindent();
//
//								ImGui::TreePop();
//							}
//						}
//
//						else if (typeGroup == ofxSurfing_ImGui_WidgetsTypes::OFX_IM_GROUP_TREE_EX)
//						{
//							if (ImGui::TreeNodeEx(parameterGroup->getName().data(), flags))
//							{
//								ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
//
//								ImGui::TreePop();
//							}
//						}
//
//						else if (typeGroup == ofxSurfing_ImGui_WidgetsTypes::OFX_IM_GROUP_SCROLLABLE)
//						{
//							auto& style = ImGui::GetStyle();
//							int hh = 40;
//							int h = style.FramePadding.y + style.ItemSpacing.y + hh;
//							ImGui::BeginChild(parameterGroup->getName().data(), ImVec2(0, parameterGroup->size() * h), false);
//
//
//							AddGroup(*parameterGroup);
//							ImGui::EndChild();
//						}
//					}
//				}
//				ImGui::PopID();
//
//				//-
//
//				continue;
//			}
//
//			//----
//
//			// Parameter, try everything we know how to handle.
//#if OF_VERSION_MINOR >= 10
//			auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
//			if (parameterVec2f)
//			{
//				AddParameter(*parameterVec2f);
//				continue;
//			}
//			auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
//			if (parameterVec3f)
//			{
//				AddParameter(*parameterVec3f);
//				continue;
//			}
//			auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
//			if (parameterVec4f)
//			{
//				AddParameter(*parameterVec4f);
//				continue;
//			}
//#endif
//			auto parameterOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(parameter);
//			if (parameterOfVec2f)
//			{
//				AddParameter(*parameterOfVec2f);
//				continue;
//			}
//			auto parameterOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(parameter);
//			if (parameterOfVec3f)
//			{
//				AddParameter(*parameterOfVec3f);
//				continue;
//			}
//			auto parameterOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(parameter);
//			if (parameterOfVec4f)
//			{
//				AddParameter(*parameterOfVec4f);
//				continue;
//			}
//			auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
//			if (parameterFloatColor)
//			{
//				AddParameter(*parameterFloatColor);
//				continue;
//			}
//			auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
//			if (parameterColor)
//			{
//				AddParameter(*parameterColor);
//				continue;
//			}
//			auto parameterFloat = std::dynamic_pointer_cast<ofParameter<float>>(parameter);
//			if (parameterFloat)
//			{
//				AddParameter(*parameterFloat);
//				continue;
//			}
//			auto parameterInt = std::dynamic_pointer_cast<ofParameter<int>>(parameter);
//			if (parameterInt)
//			{
//				AddParameter(*parameterInt);
//				continue;
//			}
//			auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
//			if (parameterBool)
//			{
//				AddParameter(*parameterBool);
//				continue;
//			}
//			auto parameterString = std::dynamic_pointer_cast<ofParameter<std::string>>(parameter);
//			if (parameterString)
//			{
//				AddParameter(*parameterString);
//				continue;
//			}
//
//			ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName();
//		}
//	}

//--

#if OF_VERSION_MINOR >= 10

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::tvec2<int>>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderInt2((parameter.getName().c_str()), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::tvec3<int>>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderInt3((parameter.getName().c_str()), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::tvec4<int>>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderInt4((parameter.getName().c_str()), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::vec2>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderFloat2((parameter.getName().c_str()), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::vec3>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderFloat3((parameter.getName().c_str()), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::vec4>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderFloat4((parameter.getName().c_str()), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

#endif

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofVec2f>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderFloat2((parameter.getName().c_str()), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofVec3f>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderFloat3((parameter.getName().c_str()), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofVec4f>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderFloat4((parameter.getName().c_str()), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha)
	{
		auto tmpRef = parameter.get();

		if (alpha)
		{
			if (ImGui::ColorEdit4((parameter.getName().c_str()), &tmpRef.r))
			{
				parameter.set(tmpRef);

				return true;
			}
		}
		else if (ImGui::ColorEdit3((parameter.getName().c_str()), &tmpRef.r))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha)
	{
		ofParameter<ofFloatColor> c;
		c.set(parameter.getName(),
			ofFloatColor(parameter.get().r / 255.f, parameter.get().g / 255.f, parameter.get().b / 255.f, parameter.get().a / 255.f),
			ofFloatColor(0, 0, 0, 0),
			ofFloatColor(1.f, 1.f, 1.f, 1.f)
		);

		auto tmpRef = c.get();

		if (alpha)
		{
			if (ImGui::ColorEdit4((parameter.getName().c_str()), &tmpRef.r))
			{
				parameter.set(tmpRef);

				return true;
			}
		}
		else if (ImGui::ColorEdit3((parameter.getName().c_str()), &tmpRef.r))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars, bool multiline)
	{
		auto tmpRef = parameter.get();
		char * cString = new char[maxChars];
		strcpy(cString, tmpRef.c_str());
		auto result = false;

		if (multiline)
		{
			if (ImGui::InputTextMultiline((parameter.getName().c_str()), cString, maxChars))
			{
				parameter.set(cString);
				result = true;
			}
		}
		else if (ImGui::InputText((parameter.getName().c_str()), cString, maxChars))
		{
			parameter.set(cString);
			result = true;
		}
		delete[] cString;

		return result;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<void>& parameter, float width)
	{
		if (ImGui::Button((parameter.getName().c_str()), glm::vec2(width, 0.0f)))
		{
			parameter.trigger();

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddRadio(ofParameter<int>& parameter, std::vector<std::string> labels, int columns)
	{
		auto uniqueName = (parameter.getName().c_str());
		ImGui::Text("%s", uniqueName);
		auto result = false;
		auto tmpRef = parameter.get();

		ImGui::PushID(uniqueName);
		{
			ImGui::Columns(columns);
			for (size_t i = 0; i < labels.size(); ++i)
			{
				result |= ImGui::RadioButton((labels[i]).c_str(), &tmpRef, i);
				ImGui::NextColumn();
			}
			ImGui::Columns(1);
		}
		ImGui::PopID();

		if (result)
		{
			parameter.set(tmpRef);
		}
		return result;
	}

	//--------------------------------------------------------------
	bool AddCombo(ofParameter<int>& parameter, std::vector<std::string> labels)
	{
		auto result = false;
		auto tmpRef = parameter.get();

		auto uniqueName = (parameter.getName().c_str());

		ImGui::PushID(uniqueName);
		if (ImGui::BeginCombo((parameter.getName().c_str()), labels.at(parameter.get()).c_str()))
		{
			for (size_t i = 0; i < labels.size(); ++i)
			{
				bool selected = (i == tmpRef);
				if (ImGui::Selectable(labels[i].c_str(), selected))
				{
					tmpRef = i;
					result = true;
				}
				if (selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
		ImGui::PopID();

		if (result)
		{
			parameter.set(tmpRef);
		}

		return result;
	}

	//--------------------------------------------------------------
	bool AddStepper(ofParameter<int>& parameter, int step, int stepFast)
	{
		auto tmpRef = parameter.get();

		if (ImGui::InputInt((parameter.getName().c_str()), &tmpRef, step, stepFast))
		{
			parameter.set(ofClamp(tmpRef, parameter.getMin(), parameter.getMax()));

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddSlider(ofParameter<float>& parameter, const char* format, float power)
	{
		auto tmpRef = parameter.get();

		ImGui::PushItemWidth(-WIDGET_PARAM_PADDING);
		if (ImGui::SliderFloat((parameter.getName().c_str()), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), format, power))
		{
			parameter.set(tmpRef);

			ImGui::PopItemWidth();
			return true;
		}

		ImGui::PopItemWidth();
		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, int speed)
	{
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		auto uniqueName = name.c_str();

		if (ImGui::DragIntRange2(uniqueName, &tmpRefMin, &tmpRefMax, speed, parameterMin.getMin(), parameterMax.getMax()))
		{
			parameterMin.set(tmpRefMin);
			parameterMax.set(tmpRefMax);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, float speed)
	{
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		if (ImGui::DragFloatRange2(name.c_str(), &tmpRefMin, &tmpRefMax, speed, parameterMin.getMin(), parameterMax.getMax()))
		{
			parameterMin.set(tmpRefMin);
			parameterMax.set(tmpRefMax);

			return true;
		}

		return false;
	}

#if OF_VERSION_MINOR >= 10

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<glm::vec2>& parameterMin, ofParameter<glm::vec2>& parameterMax, float speed)
	{
		auto result = false;
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		if (ImGui::DragFloatRange2((name + " X").c_str(), &tmpRefMin.x, &tmpRefMax.x, speed, parameterMin.getMin().x, parameterMax.getMax().x))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Y").c_str(), &tmpRefMin.y, &tmpRefMax.y, speed, parameterMin.getMin().y, parameterMax.getMax().y))
		{
			result |= true;
		}

		if (result)
		{
			parameterMin.set(tmpRefMin);
			parameterMax.set(tmpRefMax);
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<glm::vec3>& parameterMin, ofParameter<glm::vec3>& parameterMax, float speed)
	{
		auto result = false;
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		if (ImGui::DragFloatRange2((name + " X").c_str(), &tmpRefMin.x, &tmpRefMax.x, speed, parameterMin.getMin().x, parameterMax.getMax().x))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Y").c_str(), &tmpRefMin.y, &tmpRefMax.y, speed, parameterMin.getMin().y, parameterMax.getMax().y))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Z").c_str(), &tmpRefMin.z, &tmpRefMax.z, speed, parameterMin.getMin().z, parameterMax.getMax().z))
		{
			result |= true;
		}

		if (result)
		{
			parameterMin.set(tmpRefMin);
			parameterMax.set(tmpRefMax);
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<glm::vec4>& parameterMin, ofParameter<glm::vec4>& parameterMax, float speed)
	{
		auto result = false;
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		if (ImGui::DragFloatRange2((name + " X").c_str(), &tmpRefMin.x, &tmpRefMax.x, speed, parameterMin.getMin().x, parameterMax.getMax().x))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Y").c_str(), &tmpRefMin.y, &tmpRefMax.y, speed, parameterMin.getMin().y, parameterMax.getMax().y))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Z").c_str(), &tmpRefMin.z, &tmpRefMax.z, speed, parameterMin.getMin().z, parameterMax.getMax().z))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " W").c_str(), &tmpRefMin.w, &tmpRefMax.w, speed, parameterMin.getMin().w, parameterMax.getMax().w))
		{
			result |= true;
		}

		if (result)
		{
			parameterMin.set(tmpRefMin);
			parameterMax.set(tmpRefMax);
			return true;
		}
		return false;
	}

#endif

#if OF_VERSION_MINOR >= 10

	//--------------------------------------------------------------
	bool AddValues(const std::string& name, std::vector<glm::tvec2<int>>& values, int minValue, int maxValue)
	{
		auto result = false;
		for (size_t i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);

			if (minValue == 0 && maxValue == 0)
			{
				result |= ImGui::DragInt2(iname.c_str(), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderInt2(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
			}
		}
		return result;
	}

	//--------------------------------------------------------------
	bool AddValues(const std::string& name, std::vector<glm::tvec3<int>>& values, int minValue, int maxValue)
	{
		auto result = false;
		for (size_t i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);

			if (minValue == 0 && maxValue == 0)
			{
				result |= ImGui::DragInt3(iname.c_str(), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderInt3(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
			}
		}
		return result;
	}

	//--------------------------------------------------------------
	bool AddValues(const std::string& name, std::vector<glm::tvec4<int>>& values, int minValue, int maxValue)
	{
		auto result = false;
		for (size_t i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);

			if (minValue == 0 && maxValue == 0)
			{
				result |= ImGui::DragInt4(iname.c_str(), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderInt4(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
			}
		}
		return result;
	}

	//--------------------------------------------------------------
	bool AddValues(const std::string& name, std::vector<glm::vec2>& values, float minValue, float maxValue)
	{
		auto result = false;
		for (size_t i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);

			if (minValue == 0 && maxValue == 0)
			{
				result |= ImGui::DragFloat2(iname.c_str(), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderFloat2(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
			}
		}
		return result;
	}

	//--------------------------------------------------------------
	bool AddValues(const std::string& name, std::vector<glm::vec3>& values, float minValue, float maxValue)
	{
		auto result = false;
		for (size_t i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);

			if (minValue == 0 && maxValue == 0)
			{
				result |= ImGui::DragFloat3(iname.c_str(), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderFloat3(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
			}
		}
		return result;
	}

	//--------------------------------------------------------------
	bool AddValues(const std::string& name, std::vector<glm::vec4>& values, float minValue, float maxValue)
	{
		auto result = false;
		for (size_t i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);

			if (minValue == 0 && maxValue == 0)
			{
				result |= ImGui::DragFloat4(iname.c_str(), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderFloat4(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
			}
		}
		return result;
	}
#endif

	//--------------------------------------------------------------
	bool AddValues(const std::string& name, std::vector<ofVec2f>& values, float minValue, float maxValue)
	{
		auto result = false;
		for (size_t i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);

			if (minValue == 0 && maxValue == 0)
			{
				result |= ImGui::DragFloat2(iname.c_str(), values[i].getPtr());
			}
			else
			{
				result |= ImGui::SliderFloat2(iname.c_str(), values[i].getPtr(), minValue, maxValue);
			}

		}
		return result;
	}

	//--------------------------------------------------------------
	bool AddValues(const std::string& name, std::vector<ofVec3f>& values, float minValue, float maxValue)
	{
		auto result = false;
		for (size_t i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);

			if (minValue == 0 && maxValue == 0)
			{
				result |= ImGui::DragFloat3(iname.c_str(), values[i].getPtr());
			}
			else
			{
				result |= ImGui::SliderFloat3(iname.c_str(), values[i].getPtr(), minValue, maxValue);
			}

		}
		return result;
	}

	//--------------------------------------------------------------
	bool AddValues(const std::string& name, std::vector<ofVec4f>& values, float minValue, float maxValue)
	{
		auto result = false;
		for (size_t i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);

			if (minValue == 0 && maxValue == 0)
			{
				result |= ImGui::DragFloat4(iname.c_str(), values[i].getPtr());
			}
			else
			{
				result |= ImGui::SliderFloat4(iname.c_str(), values[i].getPtr(), minValue, maxValue);
			}

		}
		return result;
	}

	//--

	// image
	//--------------------------------------------------------------
	void AddImage(const ofBaseHasTexture& hasTexture, const ofVec2f& size)
	{
		AddImage(hasTexture.getTexture(), size);
	}
	//--------------------------------------------------------------
	void AddImage(const ofTexture& texture, const ofVec2f& size)
	{
		ImTextureID textureID = GetImTextureID2(texture);
		ImGui::Image(textureID, size);
	}
#if OF_VERSION_MINOR >= 10
	//--------------------------------------------------------------
	void AddImage(const ofBaseHasTexture& hasTexture, const glm::vec2& size)
	{
		AddImage(hasTexture.getTexture(), size);
	}
	//--------------------------------------------------------------
	void AddImage(const ofTexture& texture, const glm::vec2& size)
	{
		ImTextureID textureID = GetImTextureID2(texture);
		ImGui::Image(textureID, size);
	}
#endif

	//--

	// list
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};
	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ImGui::Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}
	bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ImGui::ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}
}

//--
