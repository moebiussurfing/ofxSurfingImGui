#include "ofxSurfing_ImGui_Helpers.h"

////--------------------------------------------------------------
//ofxSurfing::Settings::Settings()
//	: windowPos(kImGuiMargin2, kImGuiMargin2)
//	, windowSize(ofVec2f::zero())
//	, lockPosition(false)
//	, windowBlock(false)
//	, treeLevel(0)
//{}
//
//bool ofxSurfing::IsMouseOverGui()
//{
//	return ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
//}
//
////--------------------------------------------------------------
//const char * ofxSurfing::GetUniqueName(ofAbstractParameter& parameter)
//{
//	return GetUniqueName(parameter.getName());
//}
//
////--------------------------------------------------------------
//const char * ofxSurfing::GetUniqueName(const std::string& candidate)
//{
//	std::string result = candidate;
//	while (std::find(windowOpen.usedNames.top().begin(), windowOpen.usedNames.top().end(), result) != windowOpen.usedNames.top().end())
//	{
//		result += " ";
//	}
//	windowOpen.usedNames.top().push_back(result);
//	return windowOpen.usedNames.top().back().c_str();
//}
//
////--------------------------------------------------------------
//void ofxSurfing::SetNextWindow(Settings& settings)
//{
//	settings.windowSize.x = 0;
//	settings.windowPos.y += settings.windowSize.y + kImGuiMargin2;
//}
//
////--------------------------------------------------------------
//bool ofxSurfing::BeginWindow(ofParameter<bool>& parameter, Settings& settings, bool collapse)
//{
//	if (settings.windowBlock)
//	{
//		ofLogWarning(__FUNCTION__) << "Already inside a window block!";
//		return false;
//	}
//
//	// Reference this ofParameter until EndWindow().
//	windowOpen.parameter = std::dynamic_pointer_cast<ofParameter<bool>>(parameter.newReference());
//	windowOpen.value = parameter.get();
//
//	auto result = ofxSurfing::BeginWindow(parameter.getName(), settings, collapse, &windowOpen.value);
//	parameter = windowOpen.value;
//	return result;
//}
//
////--------------------------------------------------------------
//bool ofxSurfing::BeginWindow(const std::string& name, Settings& settings, bool collapse, bool * open)
//{
//	if (settings.windowBlock)
//	{
//		ofLogWarning(__FUNCTION__) << "Already inside a window block!";
//		return false;
//	}
//
//	settings.windowBlock = true;
//
//	// Push a new list of names onto the stack.
//	windowOpen.usedNames.push(std::vector<std::string>());
//
//	ImGui::SetNextWindowPos(settings.windowPos, settings.lockPosition ? ImGuiCond_Always : ImGuiCond_Appearing);
//	ImGui::SetNextWindowSize(settings.windowSize, ImGuiCond_Appearing);
//	//ImGui::SetNextWindowCollapsed(collapse, ImGuiCond_Appearing);
//	return ImGui::Begin(name.c_str(), open, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | (collapse ? 0 : ImGuiWindowFlags_NoCollapse));
//}
//
////--------------------------------------------------------------
//bool ofxSurfing::BeginWindow(const std::string& name, Settings& settings, ImGuiWindowFlags flags, bool * open)
//{
//	if (settings.windowBlock)
//	{
//		ofLogWarning(__FUNCTION__) << "Already inside a window block!";
//		return false;
//	}
//
//	settings.windowBlock = true;
//
//	// Push a new list of names onto the stack.
//	windowOpen.usedNames.push(std::vector<std::string>());
//
//	//ImGui::SetNextWindowPos(settings.windowPos, settings.lockPosition? ImGuiCond_Always : ImGuiCond_Appearing);
//	//ImGui::SetNextWindowSize(settings.windowSize, ImGuiCond_Appearing);
//	//ImGui::SetNextWindowCollapsed(!(flags & ImGuiWindowFlags_NoCollapse), ImGuiCond_Appearing);
//	return ImGui::Begin(name.c_str(), open, flags);
//}
//
////--------------------------------------------------------------
//void ofxSurfing::EndWindow(Settings& settings)
//{
//	if (!settings.windowBlock)
//	{
//		ofLogWarning(__FUNCTION__) << "Not inside a window block!";
//		return;
//	}
//
//	settings.windowBlock = false;
//
//	settings.windowPos = ImGui::GetWindowPos();
//	settings.windowSize = ImGui::GetWindowSize();
//	ImGui::End();
//
//	// Unlink the referenced ofParameter.
//	//TODO: crash
//	//if (windowOpen.parameter != nullptr)
//		windowOpen.parameter.reset();
//
//	// Clear the list of names from the stack.
//	windowOpen.usedNames.pop();
//
//	// Include this window's bounds in the total bounds.
//	const auto windowBounds = ofRectangle(settings.windowPos, settings.windowSize.x, settings.windowSize.y);
//	if (settings.totalBounds.isZero())
//	{
//		settings.totalBounds = windowBounds;
//	}
//	else
//	{
//		settings.totalBounds.growToInclude(windowBounds);
//	}
//}
//
////--------------------------------------------------------------
//bool ofxSurfing::BeginTree(ofAbstractParameter& parameter, Settings& settings)
//{
//	return ofxSurfing::BeginTree(parameter.getName(), settings);
//}
//
////--------------------------------------------------------------
//bool ofxSurfing::BeginTree(const std::string& name, Settings& settings)
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
//void ofxSurfing::EndTree(Settings& settings)
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

//TODO: settings + flag
//void ofxSurfing::AddGroup(ofParameterGroup& group, Settings& settings, ImGuiTreeNodeFlags flags )

//TODO:
//not used but should we include to reuse old methods or bakcwards compatible ?
//ofxSurfing::Settings settings = ofxSurfing::Settings();

//TODO:
// add customization for nested groups
// pass some list of arguments to customize items/groups to be rendered with differents design...
//https://github.com/Daandelange/ofxImGui/issues/6#issuecomment-832174921

//--------------------------------------------------------------
void ofxSurfing::AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags)
{
	//TODO:
	//widgetsManager.refreshPanelShape(); // fails

	//TODO:
	//maybe should add different types of groups: collaspe/tree/treeEx

	//TODO: BUG
	//if (ImGui::TreeNodeEx(group.getName().c_str(), flags)) // -> that's the desired tree but having sizing BUG
	//if (ImGui::TreeNode(group.getName().c_str())) // -> tree 
	// remeber to uncomment ImGui::TreePop(); below! 

	//TODO: 
	// workaround solution using this bc refreshPanelShape() not working well!
	if (ImGui::CollapsingHeader(group.getName().c_str(), flags)) // -> do not adds indentation

	{
		widgetsManager.refreshPanelShape();

		//-

		for (auto parameter : group)
		{
			// Group.
			auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);
			if (parameterGroup)
			{
				//TODO:
				//widgetsManager.refreshPanelShape();

				// Recurse through contents.
				ofxSurfing::AddGroup(*parameterGroup, flags);

				//TODO:
				//ofxSurfing::AddGroup(*parameterGroup, settings, flags);//olf+flags
				//ofxSurfing::AddGroup(*parameterGroup, settings);//old
				continue;
			}

			// Parameter, try everything we know how to handle.
#if OF_VERSION_MINOR >= 10
			auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
			if (parameterVec2f)
			{
				ofxSurfing::AddParameter(*parameterVec2f);
				continue;
			}
			auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
			if (parameterVec3f)
			{
				ofxSurfing::AddParameter(*parameterVec3f);
				continue;
			}
			auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
			if (parameterVec4f)
			{
				ofxSurfing::AddParameter(*parameterVec4f);
				continue;
			}
#endif
			auto parameterOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(parameter);
			if (parameterOfVec2f)
			{
				ofxSurfing::AddParameter(*parameterOfVec2f);
				continue;
			}
			auto parameterOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(parameter);
			if (parameterOfVec3f)
			{
				ofxSurfing::AddParameter(*parameterOfVec3f);
				continue;
			}
			auto parameterOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(parameter);
			if (parameterOfVec4f)
			{
				ofxSurfing::AddParameter(*parameterOfVec4f);
				continue;
			}
			auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
			if (parameterFloatColor)
			{
				ofxSurfing::AddParameter(*parameterFloatColor);
				continue;
			}
			auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
			if (parameterColor)
			{
				ofxSurfing::AddParameter(*parameterColor);
				continue;
			}
			auto parameterFloat = std::dynamic_pointer_cast<ofParameter<float>>(parameter);
			if (parameterFloat)
			{
				ofxSurfing::AddParameter(*parameterFloat);
				continue;
			}
			auto parameterInt = std::dynamic_pointer_cast<ofParameter<int>>(parameter);
			if (parameterInt)
			{
				ofxSurfing::AddParameter(*parameterInt);
				continue;
			}
			auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
			if (parameterBool)
			{
				ofxSurfing::AddParameter(*parameterBool);
				continue;
			}
			auto parameterString = std::dynamic_pointer_cast<ofParameter<std::string>>(parameter);
			if (parameterString)
			{
				ofxSurfing::AddParameter(*parameterString);
				continue;
			}

			ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName();
		}

		//ImGui::TreePop();// must disable when using CollapsingHeader(
	}
}

//// OLD: original helper from jvcleave
//// but modified to hardcode collapsed by default
////--------------------------------------------------------------
//void ofxSurfing::AddGroup(ofParameterGroup& group, Settings& settings)
//{
//	////TODO:
//	//bool prevWindowBlock = settings.windowBlock;
//	//if (settings.windowBlock)
//	//{
//	//	if (!ofxSurfing::BeginTree(group, settings))
//	//	{
//	//		return;
//	//	}
//	//}
//	//else
//	//{
//	//	if (!ofxSurfing::BeginWindow(group.getName().c_str(), settings))
//	//	{
//	//		ofxSurfing::EndWindow(settings);
//	//		return;
//	//	}
//	//}
//
//	//TODO:
//	//force framed and closed
//	if (ImGui::TreeNodeEx(group.getName().c_str(), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoAutoOpenOnLog))
//	//if (ImGui::CollapsingHeader(group.getName().c_str(), ImGuiWindowFlags_None))
//
//	{
//		for (auto parameter : group)
//		{
//			// Group.
//			auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);
//			if (parameterGroup)
//			{
//				// Recurse through contents.
//				ofxSurfing::AddGroup(*parameterGroup, settings);
//				continue;
//			}
//
//			// Parameter, try everything we know how to handle.
//#if OF_VERSION_MINOR >= 10
//			auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
//			if (parameterVec2f)
//			{
//				ofxSurfing::AddParameter(*parameterVec2f);
//				continue;
//			}
//			auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
//			if (parameterVec3f)
//			{
//				ofxSurfing::AddParameter(*parameterVec3f);
//				continue;
//			}
//			auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
//			if (parameterVec4f)
//			{
//				ofxSurfing::AddParameter(*parameterVec4f);
//				continue;
//			}
//#endif
//			auto parameterOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(parameter);
//			if (parameterOfVec2f)
//			{
//				ofxSurfing::AddParameter(*parameterOfVec2f);
//				continue;
//			}
//			auto parameterOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(parameter);
//			if (parameterOfVec3f)
//			{
//				ofxSurfing::AddParameter(*parameterOfVec3f);
//				continue;
//			}
//			auto parameterOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(parameter);
//			if (parameterOfVec4f)
//			{
//				ofxSurfing::AddParameter(*parameterOfVec4f);
//				continue;
//			}
//			auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
//			if (parameterFloatColor)
//			{
//				ofxSurfing::AddParameter(*parameterFloatColor);
//				continue;
//			}
//			auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
//			if (parameterColor)
//			{
//				ofxSurfing::AddParameter(*parameterColor);
//				continue;
//			}
//			auto parameterFloat = std::dynamic_pointer_cast<ofParameter<float>>(parameter);
//			if (parameterFloat)
//			{
//				ofxSurfing::AddParameter(*parameterFloat);
//				continue;
//			}
//			auto parameterInt = std::dynamic_pointer_cast<ofParameter<int>>(parameter);
//			if (parameterInt)
//			{
//				ofxSurfing::AddParameter(*parameterInt);
//				continue;
//			}
//			auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
//			if (parameterBool)
//			{
//				ofxSurfing::AddParameter(*parameterBool);
//				continue;
//			}
//			auto parameterString = std::dynamic_pointer_cast<ofParameter<std::string>>(parameter);
//			if (parameterString)
//			{
//				ofxSurfing::AddParameter(*parameterString);
//				continue;
//			}
//
//			ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName();
//		}
//
//		//TODO:
//		ImGui::TreePop();
//	}
//
//	//if (settings.windowBlock && !prevWindowBlock)
//	//{
//	//	// End window if we created it.
//	//	ofxSurfing::EndWindow(settings);
//	//}
//	//else
//	//{
//	//	// End tree.
//	//	ofxSurfing::EndTree(settings);
//	//}
//}

#if OF_VERSION_MINOR >= 10

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<glm::tvec2<int>>& parameter)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::SliderInt2(parameter.getName().c_str(), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<glm::tvec3<int>>& parameter)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::SliderInt3(parameter.getName().c_str(), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<glm::tvec4<int>>& parameter)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::SliderInt4(parameter.getName().c_str(), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<glm::vec2>& parameter)
{
	auto tmpRef = parameter.get();
	//ImGui::PushID(index++);
	if (ImGui::SliderFloat2(parameter.getName().c_str(), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<glm::vec3>& parameter)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::SliderFloat3(parameter.getName().c_str(), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<glm::vec4>& parameter)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::SliderFloat4(parameter.getName().c_str(), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

#endif

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<ofVec2f>& parameter)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::SliderFloat2(parameter.getName().c_str(), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<ofVec3f>& parameter)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::SliderFloat3(parameter.getName().c_str(), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<ofVec4f>& parameter)
{
	auto tmpRef = parameter.get();
	//ImGui::PushID(index++);
	if (ImGui::SliderFloat4(parameter.getName().c_str(), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (alpha)
	{
		if (ImGui::ColorEdit4(parameter.getName().c_str(), &tmpRef.r))
		{
			parameter.set(tmpRef);
			//ImGui::PopID();
			return true;
		}
	}
	else if (ImGui::ColorEdit3(parameter.getName().c_str(), &tmpRef.r))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<ofColor>& parameter, bool alpha)
{
	ofParameter<ofFloatColor> c;
	c.set(parameter.getName(),
		ofFloatColor(parameter.get().r / 255.f, parameter.get().g / 255.f, parameter.get().b / 255.f, parameter.get().a / 255.f),
		ofFloatColor(0, 0, 0, 0),
		ofFloatColor(1.f, 1.f, 1.f, 1.f)
	);

	auto tmpRef = c.get();

	//ImGui::PushID(index++);
	if (alpha)
	{
		if (ImGui::ColorEdit4(parameter.getName().c_str(), &tmpRef.r))
		{
			parameter.set(tmpRef);
			//ImGui::PopID();
			return true;
		}
	}
	else if (ImGui::ColorEdit3(parameter.getName().c_str(), &tmpRef.r))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<std::string>& parameter, size_t maxChars, bool multiline)
{
	auto tmpRef = parameter.get();
	char * cString = new char[maxChars];
	strcpy(cString, tmpRef.c_str());
	auto result = false;

	//ImGui::PushID(index++);
	if (multiline)
	{
		if (ImGui::InputTextMultiline(parameter.getName().c_str(), cString, maxChars))
		{
			parameter.set(cString);
			result = true;
		}
	}
	else if (ImGui::InputText(parameter.getName().c_str(), cString, maxChars))
	{
		parameter.set(cString);
		result = true;
	}
	delete[] cString;
	//ImGui::PopID();

	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddParameter(ofParameter<void>& parameter, float width)
{
	//ImGui::PushID(index++);
	if (ImGui::Button(parameter.getName().c_str(), glm::vec2(width, 0.0f)))
	{
		parameter.trigger();
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();

	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddRadio(ofParameter<int>& parameter, std::vector<std::string> labels, int columns)
{
	auto uniqueName = parameter.getName().c_str();
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
	//ImGui::PopID();

	if (result)
	{
		parameter.set(tmpRef);
	}
	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddCombo(ofParameter<int>& parameter, std::vector<std::string> labels)
{
	auto result = false;
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::BeginCombo(parameter.getName().c_str(), labels.at(parameter.get()).c_str()))
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
	if (result)
	{
		parameter.set(tmpRef);
	}
	//ImGui::PopID();

	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddStepper(ofParameter<int>& parameter, int step, int stepFast)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::InputInt(parameter.getName().c_str(), &tmpRef, step, stepFast))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();

	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddSlider(ofParameter<float>& parameter, const char* format, float power)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::SliderFloat(parameter.getName().c_str(), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), format, power))
	{
		parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();

	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddRange(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, int speed)
{
	auto tmpRefMin = parameterMin.get();
	auto tmpRefMax = parameterMax.get();

	//ImGui::PushID(index++);
	if (ImGui::DragIntRange2(name.c_str(), &tmpRefMin, &tmpRefMax, speed, parameterMin.getMin(), parameterMax.getMax()))
	{
		parameterMin.set(tmpRefMin);
		parameterMax.set(tmpRefMax);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();

	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddRange(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, float speed)
{
	auto tmpRefMin = parameterMin.get();
	auto tmpRefMax = parameterMax.get();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2(name.c_str(), &tmpRefMin, &tmpRefMax, speed, parameterMin.getMin(), parameterMax.getMax()))
	{
		parameterMin.set(tmpRefMin);
		parameterMax.set(tmpRefMax);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();

	return false;
}

#if OF_VERSION_MINOR >= 10

//--------------------------------------------------------------
bool ofxSurfing::AddRange(const std::string& name, ofParameter<glm::vec2>& parameterMin, ofParameter<glm::vec2>& parameterMax, float speed)
{
	auto result = false;
	auto tmpRefMin = parameterMin.get();
	auto tmpRefMax = parameterMax.get();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2((name + " X").c_str(), &tmpRefMin.x, &tmpRefMax.x, speed, parameterMin.getMin().x, parameterMax.getMax().x))
	{
		result |= true;
	}
	//ImGui::PopID();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2((name + " Y").c_str(), &tmpRefMin.y, &tmpRefMax.y, speed, parameterMin.getMin().y, parameterMax.getMax().y))
	{
		result |= true;
	}
	//ImGui::PopID();

	if (result)
	{
		parameterMin.set(tmpRefMin);
		parameterMax.set(tmpRefMax);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddRange(const std::string& name, ofParameter<glm::vec3>& parameterMin, ofParameter<glm::vec3>& parameterMax, float speed)
{
	auto result = false;
	auto tmpRefMin = parameterMin.get();
	auto tmpRefMax = parameterMax.get();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2((name + " X").c_str(), &tmpRefMin.x, &tmpRefMax.x, speed, parameterMin.getMin().x, parameterMax.getMax().x))
	{
		result |= true;
	}
	//ImGui::PopID();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2((name + " Y").c_str(), &tmpRefMin.y, &tmpRefMax.y, speed, parameterMin.getMin().y, parameterMax.getMax().y))
	{
		result |= true;
	}
	//ImGui::PopID();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2((name + " Z").c_str(), &tmpRefMin.z, &tmpRefMax.z, speed, parameterMin.getMin().z, parameterMax.getMax().z))
	{
		result |= true;
	}
	//ImGui::PopID();

	if (result)
	{
		parameterMin.set(tmpRefMin);
		parameterMax.set(tmpRefMax);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool ofxSurfing::AddRange(const std::string& name, ofParameter<glm::vec4>& parameterMin, ofParameter<glm::vec4>& parameterMax, float speed)
{
	auto result = false;
	auto tmpRefMin = parameterMin.get();
	auto tmpRefMax = parameterMax.get();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2((name + " X").c_str(), &tmpRefMin.x, &tmpRefMax.x, speed, parameterMin.getMin().x, parameterMax.getMax().x))
	{
		result |= true;
	}
	//ImGui::PopID();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2((name + " Y").c_str(), &tmpRefMin.y, &tmpRefMax.y, speed, parameterMin.getMin().y, parameterMax.getMax().y))
	{
		result |= true;
	}
	//ImGui::PopID();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2((name + " Z").c_str(), &tmpRefMin.z, &tmpRefMax.z, speed, parameterMin.getMin().z, parameterMax.getMax().z))
	{
		result |= true;
	}
	//ImGui::PopID();

	//ImGui::PushID(index++);
	if (ImGui::DragFloatRange2((name + " W").c_str(), &tmpRefMin.w, &tmpRefMax.w, speed, parameterMin.getMin().w, parameterMax.getMax().w))
	{
		result |= true;
	}
	//ImGui::PopID();

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
bool ofxSurfing::AddValues(const std::string& name, std::vector<glm::tvec2<int>>& values, int minValue, int maxValue)
{
	auto result = false;
	for (size_t i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		//ImGui::PushID(index++);
		if (minValue == 0 && maxValue == 0)
		{
			result |= ImGui::DragInt2(iname.c_str(), glm::value_ptr(values[i]));
		}
		else
		{
			result |= ImGui::SliderInt2(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
		}
		//ImGui::PopID();
	}
	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddValues(const std::string& name, std::vector<glm::tvec3<int>>& values, int minValue, int maxValue)
{
	auto result = false;
	for (size_t i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		//ImGui::PushID(index++);
		if (minValue == 0 && maxValue == 0)
		{
			result |= ImGui::DragInt3(iname.c_str(), glm::value_ptr(values[i]));
		}
		else
		{
			result |= ImGui::SliderInt3(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
		}
		//ImGui::PopID();
	}
	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddValues(const std::string& name, std::vector<glm::tvec4<int>>& values, int minValue, int maxValue)
{
	auto result = false;
	for (size_t i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		//ImGui::PushID(index++);
		if (minValue == 0 && maxValue == 0)
		{
			result |= ImGui::DragInt4(iname.c_str(), glm::value_ptr(values[i]));
		}
		else
		{
			result |= ImGui::SliderInt4(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
		}
		//ImGui::PopID();
	}
	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddValues(const std::string& name, std::vector<glm::vec2>& values, float minValue, float maxValue)
{
	auto result = false;
	for (size_t i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		//ImGui::PushID(index++);
		if (minValue == 0 && maxValue == 0)
		{
			result |= ImGui::DragFloat2(iname.c_str(), glm::value_ptr(values[i]));
		}
		else
		{
			result |= ImGui::SliderFloat2(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
		}
		//ImGui::PopID();
	}
	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddValues(const std::string& name, std::vector<glm::vec3>& values, float minValue, float maxValue)
{
	auto result = false;
	for (size_t i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		//ImGui::PushID(index++);
		if (minValue == 0 && maxValue == 0)
		{
			result |= ImGui::DragFloat3(iname.c_str(), glm::value_ptr(values[i]));
		}
		else
		{
			result |= ImGui::SliderFloat3(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
		}
		//ImGui::PopID();
	}
	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddValues(const std::string& name, std::vector<glm::vec4>& values, float minValue, float maxValue)
{
	auto result = false;
	for (size_t i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		//ImGui::PushID(index++);
		if (minValue == 0 && maxValue == 0)
		{
			result |= ImGui::DragFloat4(iname.c_str(), glm::value_ptr(values[i]));
		}
		else
		{
			result |= ImGui::SliderFloat4(iname.c_str(), glm::value_ptr(values[i]), minValue, maxValue);
		}
		//ImGui::PopID();
	}
	return result;
}

#endif

//--------------------------------------------------------------
bool ofxSurfing::AddValues(const std::string& name, std::vector<ofVec2f>& values, float minValue, float maxValue)
{
	auto result = false;
	for (size_t i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		//ImGui::PushID(index++);
		if (minValue == 0 && maxValue == 0)
		{
			result |= ImGui::DragFloat2(iname.c_str(), values[i].getPtr());
		}
		else
		{
			result |= ImGui::SliderFloat2(iname.c_str(), values[i].getPtr(), minValue, maxValue);
		}
		//ImGui::PopID();
	}
	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddValues(const std::string& name, std::vector<ofVec3f>& values, float minValue, float maxValue)
{
	auto result = false;
	for (size_t i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		//ImGui::PushID(index++);
		if (minValue == 0 && maxValue == 0)
		{
			result |= ImGui::DragFloat3(iname.c_str(), values[i].getPtr());
		}
		else
		{
			result |= ImGui::SliderFloat3(iname.c_str(), values[i].getPtr(), minValue, maxValue);
		}
		//ImGui::PopID();
	}
	return result;
}

//--------------------------------------------------------------
bool ofxSurfing::AddValues(const std::string& name, std::vector<ofVec4f>& values, float minValue, float maxValue)
{
	auto result = false;
	for (size_t i = 0; i < values.size(); ++i)
	{
		const auto iname = name + " " + ofToString(i);
		//ImGui::PushID(index++);
		if (minValue == 0 && maxValue == 0)
		{
			result |= ImGui::DragFloat4(iname.c_str(), values[i].getPtr());
		}
		else
		{
			result |= ImGui::SliderFloat4(iname.c_str(), values[i].getPtr(), minValue, maxValue);
		}
		//ImGui::PopID();
	}
	return result;
}

//--------------------------------------------------------------
void ofxSurfing::AddImage(const ofBaseHasTexture& hasTexture, const ofVec2f& size)
{
	ofxSurfing::AddImage(hasTexture.getTexture(), size);
}

//--------------------------------------------------------------
void ofxSurfing::AddImage(const ofTexture& texture, const ofVec2f& size)
{
	ImTextureID textureID = GetImTextureID2(texture);
	ImGui::Image(textureID, size);
}

#if OF_VERSION_MINOR >= 10

//--------------------------------------------------------------
void ofxSurfing::AddImage(const ofBaseHasTexture& hasTexture, const glm::vec2& size)
{
	ofxSurfing::AddImage(hasTexture.getTexture(), size);
}

//--------------------------------------------------------------
void ofxSurfing::AddImage(const ofTexture& texture, const glm::vec2& size)
{
	ImTextureID textureID = GetImTextureID2(texture);
	ImGui::Image(textureID, size);
}

#endif

static auto vector_getter = [](void* vec, int idx, const char** out_text)
{
	auto& vector = *static_cast<std::vector<std::string>*>(vec);
	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	*out_text = vector.at(idx).c_str();
	return true;
};

bool ofxSurfing::VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values)
{
	if (values.empty()) { return false; }
	return ImGui::Combo(label, currIndex, vector_getter,
		static_cast<void*>(&values), values.size());
}

bool ofxSurfing::VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values)
{
	if (values.empty()) { return false; }
	return ImGui::ListBox(label, currIndex, vector_getter,
		static_cast<void*>(&values), values.size());
}
