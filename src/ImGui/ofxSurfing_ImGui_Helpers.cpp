#include "ofxSurfing_ImGui_Helpers.h"

////--------------------------------------------------------------
//ofxImGuiSurfing::Settings::Settings()
//	: windowPos(kImGuiMargin2, kImGuiMargin2)
//	, windowSize(ofVec2f::zero())
//	, lockPosition(false)
//	, windowBlock(false)
//	, treeLevel(0)
//{}
//
//bool ofxImGuiSurfing::IsMouseOverGui()
//{
//	return ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
//}
//
////--------------------------------------------------------------
//const char * ofxImGuiSurfing::GetUniqueName(ofAbstractParameter& parameter)
//{
//	return GetUniqueName(parameter.getName());
//}
//
////--------------------------------------------------------------
//const char * ofxImGuiSurfing::GetUniqueName(const std::string& candidate)
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
//void ofxImGuiSurfing::SetNextWindow(Settings& settings)
//{
//	settings.windowSize.x = 0;
//	settings.windowPos.y += settings.windowSize.y + kImGuiMargin2;
//}
//
////--------------------------------------------------------------
//bool ofxImGuiSurfing::BeginWindow(ofParameter<bool>& parameter, Settings& settings, bool collapse)
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
//	auto result = ofxImGuiSurfing::BeginWindow(parameter.getName(), settings, collapse, &windowOpen.value);
//	parameter = windowOpen.value;
//	return result;
//}
//
////--------------------------------------------------------------
//bool ofxImGuiSurfing::BeginWindow(const std::string& name, Settings& settings, bool collapse, bool * open)
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
//bool ofxImGuiSurfing::BeginWindow(const std::string& name, Settings& settings, ImGuiWindowFlags flags, bool * open)
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
//void ofxImGuiSurfing::EndWindow(Settings& settings)
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
//bool ofxImGuiSurfing::BeginTree(ofAbstractParameter& parameter, Settings& settings)
//{
//	return ofxImGuiSurfing::BeginTree(parameter.getName(), settings);
//}
//
////--------------------------------------------------------------
//bool ofxImGuiSurfing::BeginTree(const std::string& name, Settings& settings)
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
//void ofxImGuiSurfing::EndTree(Settings& settings)
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
//void ofxImGuiSurfing::AddGroup(ofParameterGroup& group, Settings& settings, ImGuiTreeNodeFlags flags )

//TODO:
//not used but should we include to reuse old methods or bakcwards compatible ?
//ofxImGuiSurfing::Settings settings = ofxImGuiSurfing::Settings();

//TODO:
// add customization for nested groups
// pass some list of arguments to customize items/groups to be rendered with differents design...
//https://github.com/Daandelange/ofxImGui/issues/6#issuecomment-832174921

//--------------------------------------------------------------
void ofxImGuiSurfing::AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags)
{
	//TODO:
	//widgetsManager.refreshPanelShape(); // fails

	//TODO:
	//maybe should add different types of groups: collaspe/tree/treeEx

#ifndef	USE_FIX_BUG_2__WRONG_INDENT_UNLIMITED_GROW
	//TODO: BUG
	// remeber to uncomment ImGui::TreePop(); below! 
	if (ImGui::TreeNodeEx(group.getName().c_str(), flags)) // -> that's the desired tree but having sizing BUG
	//if (ImGui::TreeNode(group.getName().c_str())) // -> tree 
#endif

	//TODO: 
	// workaround solution using this bc refreshPanelShape() not working well!
	// TESTING
#ifdef	USE_FIX_BUG_2__WRONG_INDENT_UNLIMITED_GROW
		if (ImGui::CollapsingHeader(group.getName().data(), flags)) // -> do not adds indentation. to avoid layout bug
#endif
		{
			//widgetsManager.refreshPanelShape(); // not working

			//-

			for (auto parameter : group)
			{
				// Group.
				auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);

				//if (parameterGroup)
				//{
				//	//TODO:
				//	//widgetsManager.refreshPanelShape();

				//	// Recurse through contents.
				//	ofxImGuiSurfing::AddGroup(*parameterGroup, flags);

				//	//TODO:
				//	//ofxImGuiSurfing::AddGroup(*parameterGroup, settings, flags);//olf+flags
				//	//ofxImGuiSurfing::AddGroup(*parameterGroup, settings);//old
				//	continue;
				//}

				// TESTING
				// https://github.com/yumataesu/ofxImGui_v3/blob/master/src/Helper.cpp

				if (parameterGroup)
				{
					// Recurse through contents.

					// Styles

					// 0.
					ofxImGuiSurfing::AddGroup(*parameterGroup);

					//// 1. yumataesu (per group scroll bar)
					//if (ImGui::CollapsingHeader(parameterGroup->getName().data())) {
					//	auto& style = ImGui::GetStyle();
					//	int h = style.FramePadding.y + style.ItemSpacing.y + 14;
					//	ImGui::BeginChild(parameterGroup->getName().data(), ImVec2(0, parameterGroup->size() * h), false);
					//	ofxImGuiSurfing::AddGroup(*parameterGroup);
					//	ImGui::EndChild();
					//}

					//// 2. collapse (per window scroll bar)
					//if (ImGui::CollapsingHeader(parameterGroup->getName().data())) {
					//	ofxImGuiSurfing::AddGroup(*parameterGroup);
					//}

					//// 3. tree (indented + per window scroll bar)
					//if (ImGui::TreeNodeEx(parameterGroup->getName().data(), flags)) {
					//	widgetsManager.refreshPanelShape(); // required bc indent changes window width!
					//	ofxImGuiSurfing::AddGroup(*parameterGroup);
					//	ImGui::TreePop();
					//}

					continue;
				}

				//-

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
				auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
				if (parameterColor)
				{
					ofxImGuiSurfing::AddParameter(*parameterColor);
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
				auto parameterString = std::dynamic_pointer_cast<ofParameter<std::string>>(parameter);
				if (parameterString)
				{
					ofxImGuiSurfing::AddParameter(*parameterString);
					continue;
				}

				ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName();
			}

			//-

#ifndef	USE_FIX_BUG_2__WRONG_INDENT_UNLIMITED_GROW
			ImGui::TreePop(); // must disable when using CollapsingHeader(..
#endif	
		}
}

//// OLD: original helper from jvcleave
//// but modified to hardcode collapsed by default
////--------------------------------------------------------------
//void ofxImGuiSurfing::AddGroup(ofParameterGroup& group, Settings& settings)
//{
//	////TODO:
//	//bool prevWindowBlock = settings.windowBlock;
//	//if (settings.windowBlock)
//	//{
//	//	if (!ofxImGuiSurfing::BeginTree(group, settings))
//	//	{
//	//		return;
//	//	}
//	//}
//	//else
//	//{
//	//	if (!ofxImGuiSurfing::BeginWindow(group.getName().c_str(), settings))
//	//	{
//	//		ofxImGuiSurfing::EndWindow(settings);
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
//				ofxImGuiSurfing::AddGroup(*parameterGroup, settings);
//				continue;
//			}
//
//			// Parameter, try everything we know how to handle.
//#if OF_VERSION_MINOR >= 10
//			auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
//			if (parameterVec2f)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterVec2f);
//				continue;
//			}
//			auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
//			if (parameterVec3f)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterVec3f);
//				continue;
//			}
//			auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
//			if (parameterVec4f)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterVec4f);
//				continue;
//			}
//#endif
//			auto parameterOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(parameter);
//			if (parameterOfVec2f)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterOfVec2f);
//				continue;
//			}
//			auto parameterOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(parameter);
//			if (parameterOfVec3f)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterOfVec3f);
//				continue;
//			}
//			auto parameterOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(parameter);
//			if (parameterOfVec4f)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterOfVec4f);
//				continue;
//			}
//			auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
//			if (parameterFloatColor)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterFloatColor);
//				continue;
//			}
//			auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
//			if (parameterColor)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterColor);
//				continue;
//			}
//			auto parameterFloat = std::dynamic_pointer_cast<ofParameter<float>>(parameter);
//			if (parameterFloat)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterFloat);
//				continue;
//			}
//			auto parameterInt = std::dynamic_pointer_cast<ofParameter<int>>(parameter);
//			if (parameterInt)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterInt);
//				continue;
//			}
//			auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
//			if (parameterBool)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterBool);
//				continue;
//			}
//			auto parameterString = std::dynamic_pointer_cast<ofParameter<std::string>>(parameter);
//			if (parameterString)
//			{
//				ofxImGuiSurfing::AddParameter(*parameterString);
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
//	//	ofxImGuiSurfing::EndWindow(settings);
//	//}
//	//else
//	//{
//	//	// End tree.
//	//	ofxImGuiSurfing::EndTree(settings);
//	//}
//}

#if OF_VERSION_MINOR >= 10

//--------------------------------------------------------------
bool ofxImGuiSurfing::AddParameter(ofParameter<glm::tvec2<int>>& parameter)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<glm::tvec3<int>>& parameter)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<glm::tvec4<int>>& parameter)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<glm::vec2>& parameter)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<glm::vec3>& parameter)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<glm::vec4>& parameter)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<ofVec2f>& parameter)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<ofVec3f>& parameter)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<ofVec4f>& parameter)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<ofColor>& parameter, bool alpha)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<std::string>& parameter, size_t maxChars, bool multiline)
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
bool ofxImGuiSurfing::AddParameter(ofParameter<void>& parameter, float width)
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
bool ofxImGuiSurfing::AddRadio(ofParameter<int>& parameter, std::vector<std::string> labels, int columns)
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
bool ofxImGuiSurfing::AddCombo(ofParameter<int>& parameter, std::vector<std::string> labels)
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
bool ofxImGuiSurfing::AddStepper(ofParameter<int>& parameter, int step, int stepFast)
{
	auto tmpRef = parameter.get();

	//ImGui::PushID(index++);
	if (ImGui::InputInt(parameter.getName().c_str(), &tmpRef, step, stepFast))
	{
		parameter.set(ofClamp(tmpRef, parameter.getMin(), parameter.getMax()));
		//parameter.set(tmpRef);
		//ImGui::PopID();
		return true;
	}
	//ImGui::PopID();

	return false;
}

//--------------------------------------------------------------
bool ofxImGuiSurfing::AddSlider(ofParameter<float>& parameter, const char* format, float power)
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
bool ofxImGuiSurfing::AddRange(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, int speed)
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
bool ofxImGuiSurfing::AddRange(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, float speed)
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
bool ofxImGuiSurfing::AddRange(const std::string& name, ofParameter<glm::vec2>& parameterMin, ofParameter<glm::vec2>& parameterMax, float speed)
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
bool ofxImGuiSurfing::AddRange(const std::string& name, ofParameter<glm::vec3>& parameterMin, ofParameter<glm::vec3>& parameterMax, float speed)
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
bool ofxImGuiSurfing::AddRange(const std::string& name, ofParameter<glm::vec4>& parameterMin, ofParameter<glm::vec4>& parameterMax, float speed)
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
bool ofxImGuiSurfing::AddValues(const std::string& name, std::vector<glm::tvec2<int>>& values, int minValue, int maxValue)
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
bool ofxImGuiSurfing::AddValues(const std::string& name, std::vector<glm::tvec3<int>>& values, int minValue, int maxValue)
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
bool ofxImGuiSurfing::AddValues(const std::string& name, std::vector<glm::tvec4<int>>& values, int minValue, int maxValue)
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
bool ofxImGuiSurfing::AddValues(const std::string& name, std::vector<glm::vec2>& values, float minValue, float maxValue)
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
bool ofxImGuiSurfing::AddValues(const std::string& name, std::vector<glm::vec3>& values, float minValue, float maxValue)
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
bool ofxImGuiSurfing::AddValues(const std::string& name, std::vector<glm::vec4>& values, float minValue, float maxValue)
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
bool ofxImGuiSurfing::AddValues(const std::string& name, std::vector<ofVec2f>& values, float minValue, float maxValue)
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
bool ofxImGuiSurfing::AddValues(const std::string& name, std::vector<ofVec3f>& values, float minValue, float maxValue)
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
bool ofxImGuiSurfing::AddValues(const std::string& name, std::vector<ofVec4f>& values, float minValue, float maxValue)
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
void ofxImGuiSurfing::AddImage(const ofBaseHasTexture& hasTexture, const ofVec2f& size)
{
	ofxImGuiSurfing::AddImage(hasTexture.getTexture(), size);
}

//--------------------------------------------------------------
void ofxImGuiSurfing::AddImage(const ofTexture& texture, const ofVec2f& size)
{
	ImTextureID textureID = GetImTextureID2(texture);
	ImGui::Image(textureID, size);
}

#if OF_VERSION_MINOR >= 10

//--------------------------------------------------------------
void ofxImGuiSurfing::AddImage(const ofBaseHasTexture& hasTexture, const glm::vec2& size)
{
	ofxImGuiSurfing::AddImage(hasTexture.getTexture(), size);
}

//--------------------------------------------------------------
void ofxImGuiSurfing::AddImage(const ofTexture& texture, const glm::vec2& size)
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

bool ofxImGuiSurfing::VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values)
{
	if (values.empty()) { return false; }
	return ImGui::Combo(label, currIndex, vector_getter,
		static_cast<void*>(&values), values.size());
}

bool ofxImGuiSurfing::VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values)
{
	if (values.empty()) { return false; }
	return ImGui::ListBox(label, currIndex, vector_getter,
		static_cast<void*>(&values), values.size());
}
