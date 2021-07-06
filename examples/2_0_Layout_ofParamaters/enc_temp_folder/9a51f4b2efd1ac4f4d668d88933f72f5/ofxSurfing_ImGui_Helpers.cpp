#include "ofxSurfing_ImGui_Helpers.h"

//TODO:
// add customization for nested groups
// pass some list of arguments to customize items/groups to be rendered with differents design...
//https://github.com/Daandelange/ofxImGui/issues/6#issuecomment-832174921

//--

namespace ofxImGuiSurfing
{
	//--------------------------------------------------------------
	const char* GetUniqueName(ofAbstractParameter& parameter)
	{
		return GetUniqueName(parameter.getName());
	}
	//--------------------------------------------------------------
	const char* GetUniqueName(const std::string& candidate)
	{
		std::string result = candidate;

		// this fix allows paras out a group/window
		{
			if (windowOpen.usedNames.size() == 0) windowOpen.usedNames.push(std::vector<std::string>());

			//if (windowOpen.usedNames.size() == 0) {
			//	result = candidate;
			//	windowOpen.usedNames.top().push_back(result);
			//	return windowOpen.usedNames.top().back().c_str();
			//}

			//if (windowOpen.usedNames.size() == 0) result = candidate.c_str();
			//else
			//	while (std::find(windowOpen.usedNames.top().begin(), windowOpen.usedNames.top().end(), result) != windowOpen.usedNames.top().end())
			//	{
			//		result += " ";
			//	}
			//windowOpen.usedNames.top().push_back(result);
			//return windowOpen.usedNames.top().back().c_str();
		}

		while (std::find(windowOpen.usedNames.top().begin(), windowOpen.usedNames.top().end(), result) != windowOpen.usedNames.top().end())
		{
			result += " ";
		}
		windowOpen.usedNames.top().push_back(result);
		return windowOpen.usedNames.top().back().c_str();
	}

	//--

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags, SurfingTypesGroups typeGroup)
	{
		ofLogNotice(__FUNCTION__) << "usedNames:" << windowOpen.usedNames.size() << " level:" << windowOpen.treeLevel;

		// push a new list of names onto the stack.
		windowOpen.usedNames.push(std::vector<std::string>());

		// first root group always has a tree collapsed header
		if (windowOpen.treeLevel == 0 && typeGroup != IM_GUI_GROUP_HIDDE_ALL_HEADERS)
		{
			bool b = ImGui::CollapsingHeader(group.getName().data(), flags);
			if (!b)
			{
				return;
			}
			windowOpen.treeLevel++;
		}

		//-

		//TODO:
		// do not adds indentation. to avoid layout bug
		//ImGui::Indent();
		//ImGui::Unindent();
		//widgetsManager.refreshPanelShape(); // required bc indent changes window width!

		//-

		for (auto parameter : group)
		{
			// group

			auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);

			if (parameterGroup)
			{
				ImGui::PushID(parameterGroup->getName().c_str());

				if (typeGroup == IM_GUI_GROUP_ONLY_FIRST_HEADER)
				{
					ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
				}
				else
				{
					if (typeGroup == IM_GUI_GROUP_HIDDE_ALL_HEADERS)
					{
						ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
					}

					else if (typeGroup == IM_GUI_GROUP_COLLAPSED)
					{
						bool b = ImGui::CollapsingHeader(parameterGroup->getName().data(), flags);
						if (b) ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
					}

					else if (typeGroup == IM_GUI_GROUP_DEFAULT)
					{
						bool b = ImGui::CollapsingHeader(parameterGroup->getName().data(), flags);
						if (b) ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
					}

					else if (typeGroup == IM_GUI_GROUP_TREE)
					{
						if (ImGui::TreeNode(parameterGroup->getName().data()))
						{
							ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
							ImGui::TreePop();
						}
					}

					else if (typeGroup == IM_GUI_GROUP_TREE_EX)
					{
						if (ImGui::TreeNodeEx(parameterGroup->getName().data(), flags))
						{
							ofxImGuiSurfing::AddGroup(*parameterGroup, flags, typeGroup);
							ImGui::TreePop();
						}
					}

					else if (typeGroup == IM_GUI_GROUP_SCROLLABLE)
					{
						auto& style = ImGui::GetStyle();
						int h = style.FramePadding.y + style.ItemSpacing.y + 14;
						ImGui::BeginChild(parameterGroup->getName().data(), ImVec2(0, parameterGroup->size() * h), false);
						AddGroup(*parameterGroup);
						ImGui::EndChild();
					}
				}

				ImGui::PopID();

				//-

				////TODO: is not called..¿?
				//windowOpen.parameter.reset(); // Unlink the referenced ofParameter.
				//windowOpen.usedNames.pop(); // Clear the list of names from the stack.
				//windowOpen.treeLevel = 0;
				////cout << "-" << endl;
				////ofLogWarning(__FUNCTION__) << "-" << endl;

				//-

				continue;
			}

			//-

			// Parameter, try everything we know how to handle.
#if OF_VERSION_MINOR >= 10
			auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
			if (parameterVec2f)
			{
				AddParameter(*parameterVec2f);
				continue;
			}
			auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
			if (parameterVec3f)
			{
				AddParameter(*parameterVec3f);
				continue;
			}
			auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
			if (parameterVec4f)
			{
				AddParameter(*parameterVec4f);
				continue;
			}
#endif
			auto parameterOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(parameter);
			if (parameterOfVec2f)
			{
				AddParameter(*parameterOfVec2f);
				continue;
			}
			auto parameterOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(parameter);
			if (parameterOfVec3f)
			{
				AddParameter(*parameterOfVec3f);
				continue;
			}
			auto parameterOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(parameter);
			if (parameterOfVec4f)
			{
				AddParameter(*parameterOfVec4f);
				continue;
			}
			auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
			if (parameterFloatColor)
			{
				AddParameter(*parameterFloatColor);
				continue;
			}
			auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
			if (parameterColor)
			{
				AddParameter(*parameterColor);
				continue;
			}
			auto parameterFloat = std::dynamic_pointer_cast<ofParameter<float>>(parameter);
			if (parameterFloat)
			{
				AddParameter(*parameterFloat);
				continue;
			}
			auto parameterInt = std::dynamic_pointer_cast<ofParameter<int>>(parameter);
			if (parameterInt)
			{
				AddParameter(*parameterInt);
				continue;
			}
			auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
			if (parameterBool)
			{
				AddParameter(*parameterBool);
				continue;
			}
			auto parameterString = std::dynamic_pointer_cast<ofParameter<std::string>>(parameter);
			if (parameterString)
			{
				AddParameter(*parameterString);
				continue;
			}

			ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName();
		}

		//--

		//TODO:
		// names engine
		ofxImGuiSurfing::resetNames();
	}

#if OF_VERSION_MINOR >= 10

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::tvec2<int>>& parameter)
	{
		auto tmpRef = parameter.get();

		if (ImGui::SliderInt2(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
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

		if (ImGui::SliderInt3(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
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

		if (ImGui::SliderInt4(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
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

		if (ImGui::SliderFloat2(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
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

		if (ImGui::SliderFloat3(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
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

		if (ImGui::SliderFloat4(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
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

		if (ImGui::SliderFloat2(GetUniqueName(parameter), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
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

		if (ImGui::SliderFloat3(GetUniqueName(parameter), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
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

		if (ImGui::SliderFloat4(GetUniqueName(parameter), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
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
			if (ImGui::ColorEdit4(GetUniqueName(parameter), &tmpRef.r))
			{
				parameter.set(tmpRef);

				return true;
			}
		}
		else if (ImGui::ColorEdit3(GetUniqueName(parameter), &tmpRef.r))
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
			if (ImGui::ColorEdit4(GetUniqueName(parameter), &tmpRef.r))
			{
				parameter.set(tmpRef);

				return true;
			}
		}
		else if (ImGui::ColorEdit3(GetUniqueName(parameter), &tmpRef.r))
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
			if (ImGui::InputTextMultiline(GetUniqueName(parameter), cString, maxChars))
			{
				parameter.set(cString);
				result = true;
			}
		}
		else if (ImGui::InputText(GetUniqueName(parameter), cString, maxChars))
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
		if (ImGui::Button(GetUniqueName(parameter), glm::vec2(width, 0.0f)))
		{
			parameter.trigger();

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddRadio(ofParameter<int>& parameter, std::vector<std::string> labels, int columns)
	{
		auto uniqueName = GetUniqueName(parameter);
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

		auto uniqueName = GetUniqueName(parameter);

		ImGui::PushID(uniqueName);
		if (ImGui::BeginCombo(GetUniqueName(parameter), labels.at(parameter.get()).c_str()))
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

		if (ImGui::InputInt(GetUniqueName(parameter), &tmpRef, step, stepFast))
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

		if (ImGui::SliderFloat(GetUniqueName(parameter), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), format, power))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, int speed)
	{
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		auto uniqueName = GetUniqueName(name);

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

		if (ImGui::DragFloatRange2(GetUniqueName(name), &tmpRefMin, &tmpRefMax, speed, parameterMin.getMin(), parameterMax.getMax()))
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

		if (ImGui::DragFloatRange2(GetUniqueName(GetUniqueName(name + " X")), &tmpRefMin.x, &tmpRefMax.x, speed, parameterMin.getMin().x, parameterMax.getMax().x))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2(GetUniqueName(GetUniqueName(name + " Y")), &tmpRefMin.y, &tmpRefMax.y, speed, parameterMin.getMin().y, parameterMax.getMax().y))
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

		if (ImGui::DragFloatRange2(GetUniqueName(name + " X"), &tmpRefMin.x, &tmpRefMax.x, speed, parameterMin.getMin().x, parameterMax.getMax().x))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2(GetUniqueName(name + " Y"), &tmpRefMin.y, &tmpRefMax.y, speed, parameterMin.getMin().y, parameterMax.getMax().y))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2(GetUniqueName(name + " Z"), &tmpRefMin.z, &tmpRefMax.z, speed, parameterMin.getMin().z, parameterMax.getMax().z))
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

		if (ImGui::DragFloatRange2(GetUniqueName(name + " X"), &tmpRefMin.x, &tmpRefMax.x, speed, parameterMin.getMin().x, parameterMax.getMax().x))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2(GetUniqueName(name + " Y"), &tmpRefMin.y, &tmpRefMax.y, speed, parameterMin.getMin().y, parameterMax.getMax().y))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2(GetUniqueName(name + " Z"), &tmpRefMin.z, &tmpRefMax.z, speed, parameterMin.getMin().z, parameterMax.getMax().z))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2(GetUniqueName(name + " W"), &tmpRefMin.w, &tmpRefMax.w, speed, parameterMin.getMin().w, parameterMax.getMax().w))
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
				result |= ImGui::DragInt2(GetUniqueName(iname), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderInt2(GetUniqueName(iname), glm::value_ptr(values[i]), minValue, maxValue);
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
				result |= ImGui::DragInt3(GetUniqueName(iname), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderInt3(GetUniqueName(iname), glm::value_ptr(values[i]), minValue, maxValue);
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
				result |= ImGui::DragInt4(GetUniqueName(iname), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderInt4(GetUniqueName(iname), glm::value_ptr(values[i]), minValue, maxValue);
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
				result |= ImGui::DragFloat2(GetUniqueName(iname), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderFloat2(GetUniqueName(iname), glm::value_ptr(values[i]), minValue, maxValue);
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
				result |= ImGui::DragFloat3(GetUniqueName(iname), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderFloat3(GetUniqueName(iname), glm::value_ptr(values[i]), minValue, maxValue);
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
				result |= ImGui::DragFloat4(GetUniqueName(iname), glm::value_ptr(values[i]));
			}
			else
			{
				result |= ImGui::SliderFloat4(GetUniqueName(iname), glm::value_ptr(values[i]), minValue, maxValue);
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
				result |= ImGui::DragFloat2(GetUniqueName(iname), values[i].getPtr());
			}
			else
			{
				result |= ImGui::SliderFloat2(GetUniqueName(iname), values[i].getPtr(), minValue, maxValue);
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
				result |= ImGui::DragFloat3(GetUniqueName(iname), values[i].getPtr());
			}
			else
			{
				result |= ImGui::SliderFloat3(GetUniqueName(iname), values[i].getPtr(), minValue, maxValue);
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
				result |= ImGui::DragFloat4(GetUniqueName(iname), values[i].getPtr());
			}
			else
			{
				result |= ImGui::SliderFloat4(GetUniqueName(iname), values[i].getPtr(), minValue, maxValue);
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

	//--

	// extra begin/end
	// with snapping

	//--------------------------------------------------------------
	void Begin(const std::string& name) {
		const int snapSz = 20;
		//const int snapSz = 16;

		auto snap = [=](float value, float snap_threshold) -> float {
			float modulo = std::fmodf(value, snap_threshold);
			float moduloRatio = std::fabsf(modulo) / snap_threshold;
			if (moduloRatio < 0.5f)
				value -= modulo;
			else if (moduloRatio > (1.f - 0.5f))
				value = value - modulo + snap_threshold * ((value < 0.f) ? -1.f : 1.f);
			return value;
		};

		ImGui::Begin(name.data());
		if (ImGui::IsItemActive()) {
			auto p = ImGui::GetWindowPos();
			auto size = ImGui::GetWindowSize();

			float x = snap(p.x, snapSz);
			float y = snap(p.y, snapSz);
			float sizex = snap(size.x, snapSz);
			float sizey = snap(size.y, snapSz);
			ImGui::SetWindowPos(ImFloor(ImVec2(x, y)));
		}
	}

	//--------------------------------------------------------------
	void End() {
		ImGui::End();
	}

	//--

	//TODO:

	//--------------------------------------------------------------
	bool BeginWindow(std::string name, bool* p_open, ImGuiWindowFlags flags)
	{
		//// Reference this ofParameter until EndWindow().
		//windowOpen.parameter = std::dynamic_pointer_cast<ofParameter<bool>>(parameter.newReference());
		//windowOpen.value = parameter.get();

		// Push a new list of names onto the stack.
		windowOpen.usedNames.push(std::vector<std::string>());

		return ImGui::Begin(name.c_str(), p_open, flags);
	}

	//--------------------------------------------------------------
	void EndWindow()
	{
		ImGui::End();
	}
}

//--

/*
////--------------------------------------------------------------
//bool BeginTree(ofAbstractParameter& parameter, Settings& settings)
//{
//	return BeginTree(parameter.getName(), settings);
//}
//
////--------------------------------------------------------------
//bool BeginTree(const std::string& name, Settings& settings)
//{
//	bool result;
//	ImGui::SetNextItemOpen(true, ImGuiCond_Appearing);
//	if (settings.treeLevel == 0)
//	{
//		result = ImGui::TreeNodeEx(GetUniqueName(name), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoAutoOpenOnLog);
//	}
//	else
//	{
//		result = ImGui::TreeNode(GetUniqueName(name));
//	}
//	if (result)
//	{
//		settings.treeLevel += 1;
//
//		// Push a new list of names onto the stack.
//		windowOpen.usedNames.push(std::vector<std::string>());
//	}
//	return result;
//}
//
////--------------------------------------------------------------
//void EndTree(Settings& settings)
//{
//	ImGui::TreePop();
//
//	settings.treeLevel = std::max(0, settings.treeLevel - 1);
//
//	// Clear the list of names from the stack.
//	windowOpen.usedNames.pop();
//}
//
////NEW: add flags and clean all the old settings
////BUG: BROKEN: crashes..
//////treeEx
////bool bOpen = true;
////ImGuiColorEditFlags _flagw = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
////_flagw |= ImGuiTreeNodeFlags_Framed;
////if (ImGui::TreeNodeEx("_TreeEx", _flagw)) {
////	//..
////	ImGui::TreePop();
////}
*/