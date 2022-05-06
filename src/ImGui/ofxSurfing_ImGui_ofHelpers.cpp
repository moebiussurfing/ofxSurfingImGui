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
	//void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen)//fails..
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags)
	{
		//TODO: now we are using ofxSurfing_ImGui_WidgetsTypes.h helpers!
		// but these methods should work too.

		//-

		//ImGui::PushID(group.getName().c_str());
		ImGui::PushID(("##" + group.getName()).c_str());
		{
			bool bOpened;

			bOpened = ImGui::CollapsingHeader(group.getName().c_str(), flags);
			//bOpened = (!ImGui::TreeNodeEx(group.getName().c_str()));
			//bOpened = (!ImGui::TreeNode(group.getName().c_str()));

			if (!bOpened)
			{
				ImGui::PopID();
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
					AddGroup(*parameterGroup, ImGuiTreeNodeFlags_None); // -> default: all with same style and non indent ?
					//ImGui::Indent();

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
				auto parameterRect = std::dynamic_pointer_cast<ofParameter<ofRectangle>>(parameter);
				if (parameterRect)
				{
					ofxImGuiSurfing::AddParameter(*parameterRect);
					continue;
				}

				// don't debug if it's unnamed
				if (parameter->getName() == "" && parameter->getName() == " ")
					ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName() << "'";

				//-

				//if (parameterGroup) ImGui::Unindent();
			}

			//-

			{
				// End tree.
				//ImGui::TreePop();
			}

		}
		ImGui::PopID();
	}

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
	bool AddParameter(ofParameter<glm::vec2>& parameter, bool bsplit)
	{
		auto tmpRef = parameter.get();

		if (!bsplit) {
			if (ImGui::SliderFloat2((parameter.getName().c_str()), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
			{
				parameter.set(tmpRef);
				//wheel for multi dim params
				//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);//TODO: should include sguar here
				//ofxImGuiSurfing::AddMouseWheel(arg1);
				return true;
			}
			return false;
		}
		else
		{
			bool bchanged = false;
			IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
			ImGui::Dummy(ImVec2(0, 1));
			//ImGui::Spacing();
			bchanged += ImGui::SliderFloat(((parameter.getName() + " X").c_str()), &tmpRef.x, parameter.getMin().x, parameter.getMax().x);
			bchanged += ImGui::SliderFloat(((parameter.getName() + " Y").c_str()), &tmpRef.y, parameter.getMin().y, parameter.getMax().y);
			ImGui::Dummy(ImVec2(0, 1));
			if (bchanged)
			{
				parameter.set(tmpRef);

				IMGUI_SUGAR__SLIDER_WIDTH_POP;
				return true;
			}
			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return false;
		}
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::vec3>& parameter, bool bsplit)
	{
		auto tmpRef = parameter.get();

		if (!bsplit) {
			if (ImGui::SliderFloat3((parameter.getName().c_str()), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
			{
				parameter.set(tmpRef);

				return true;
			}
			return false;
		}
		else
		{
			bool bchanged = false;
			IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
			ImGui::Dummy(ImVec2(0, 1));
			//ImGui::Spacing();
			bchanged += ImGui::SliderFloat(((parameter.getName() + " X").c_str()), &tmpRef.x, parameter.getMin().x, parameter.getMax().x);
			bchanged += ImGui::SliderFloat(((parameter.getName() + " Y").c_str()), &tmpRef.y, parameter.getMin().y, parameter.getMax().y);
			bchanged += ImGui::SliderFloat(((parameter.getName() + " Z").c_str()), &tmpRef.z, parameter.getMin().z, parameter.getMax().z);
			ImGui::Dummy(ImVec2(0, 1));
			if (bchanged)
			{
				parameter.set(tmpRef);

				IMGUI_SUGAR__SLIDER_WIDTH_POP;
				return true;
			}
			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return false;
		}
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::vec4>& parameter, bool bsplit)
	{
		auto tmpRef = parameter.get();

		if (!bsplit) {
			if (ImGui::SliderFloat4((parameter.getName().c_str()), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
			{
				parameter.set(tmpRef);

				return true;
			}
			return false;
		}
		else
		{
			bool bchanged = false;
			IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
			//ImGui::Spacing();
			ImGui::Dummy(ImVec2(0, 1));
			bchanged += ImGui::SliderFloat(((parameter.getName() + " X").c_str()), &tmpRef.x, parameter.getMin().x, parameter.getMax().x);
			bchanged += ImGui::SliderFloat(((parameter.getName() + " Y").c_str()), &tmpRef.y, parameter.getMin().y, parameter.getMax().y);
			bchanged += ImGui::SliderFloat(((parameter.getName() + " Z").c_str()), &tmpRef.z, parameter.getMin().z, parameter.getMax().z);
			bchanged += ImGui::SliderFloat(((parameter.getName() + " W").c_str()), &tmpRef.w, parameter.getMin().w, parameter.getMax().w);
			ImGui::Dummy(ImVec2(0, 1));
			if (bchanged)
			{
				parameter.set(tmpRef);

				IMGUI_SUGAR__SLIDER_WIDTH_POP;
				return true;
			}
			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return false;
		}
	}
#endif

	//--

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofVec2f>& parameter)
	{
		auto tmpRef = parameter.get();

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
		if (ImGui::SliderFloat2((parameter.getName().c_str()), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}

		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofVec3f>& parameter)
	{
		auto tmpRef = parameter.get();
		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;

		if (ImGui::SliderFloat3((parameter.getName().c_str()), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}

		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofVec4f>& parameter)
	{
		auto tmpRef = parameter.get();

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
		if (ImGui::SliderFloat4((parameter.getName().c_str()), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.set(tmpRef);

			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}

		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofRectangle>& parameter)
	{
		auto result = false;
		auto tmpRef = parameter.get();

		float x = tmpRef.getX();
		float y = tmpRef.getY();
		float w = tmpRef.getWidth();
		float h = tmpRef.getHeight();

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
		result |= ImGui::SliderFloat(((parameter.getName() + " x").c_str()), &x, parameter.getMin().x, parameter.getMax().x);
		result |= ImGui::SliderFloat(((parameter.getName() + " y").c_str()), &y, parameter.getMin().y, parameter.getMax().y);
		result |= ImGui::SliderFloat(((parameter.getName() + " w").c_str()), &w, parameter.getMin().width, parameter.getMax().width);
		result |= ImGui::SliderFloat(((parameter.getName() + " h").c_str()), &h, parameter.getMin().height, parameter.getMax().height);

		if (result) parameter.set(ofRectangle(x, y, w, h));

		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return result;
	}

	//TODO:
	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha/*, ImGuiColorEditFlags flags = ImGuiColorEditFlags_None*/)
	{
		auto tmpRef = parameter.get();
		ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;

		if (alpha)
		{
			if (ImGui::ColorEdit4((parameter.getName().c_str()), &tmpRef.r, flags))
			{
				parameter.set(tmpRef);

				return true;
			}
		}
		else if (ImGui::ColorEdit3((parameter.getName().c_str()), &tmpRef.r, flags))
		{
			parameter.set(tmpRef);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha/*, ImGuiColorEditFlags flags = ImGuiColorEditFlags_None*/)
	{
		ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;

		ofParameter<ofFloatColor> c;
		c.set(parameter.getName(),
			ofFloatColor(parameter.get().r / 255.f, parameter.get().g / 255.f, parameter.get().b / 255.f, parameter.get().a / 255.f),
			ofFloatColor(0, 0, 0, 0),
			ofFloatColor(1.f, 1.f, 1.f, 1.f)
		);

		auto tmpRef = c.get();

		if (alpha)
		{
			if (ImGui::ColorEdit4((parameter.getName().c_str()), &tmpRef.r, flags))
			{
				parameter.set(tmpRef);

				return true;
			}
		}
		else if (ImGui::ColorEdit3((parameter.getName().c_str()), &tmpRef.r, flags))
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

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;

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

		IMGUI_SUGAR__SLIDER_WIDTH_POP;

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
		if (parameter.get() < 0) return false;
		if (labels.size() == 0) return false;

		//-

		auto result = false;
		auto tmpRef = parameter.get();

		auto uniqueName = (("##COMBO" + parameter.getName()).c_str());

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

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
		if (ImGui::InputInt((parameter.getName().c_str()), &tmpRef, step, stepFast))
		{
			parameter.set(ofClamp(tmpRef, parameter.getMin(), parameter.getMax()));

			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}

		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return false;
	}

	//--------------------------------------------------------------
	bool AddSlider(ofParameter<float>& parameter, const char* format, float power)
	{
		auto tmpRef = parameter.get();

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
		if (ImGui::SliderFloat((parameter.getName().c_str()), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), format, power))
		{
			parameter.set(tmpRef);

			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}

		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, int speed)
	{
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		auto uniqueName = name.c_str();
		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
		if (ImGui::DragIntRange2(uniqueName, &tmpRefMin, &tmpRefMax, speed, parameterMin.getMin(), parameterMax.getMax()))
		{
			parameterMin.set(tmpRefMin);
			parameterMax.set(tmpRefMax);

			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}

		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, float speed)
	{
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
		if (ImGui::DragFloatRange2(name.c_str(), &tmpRefMin, &tmpRefMax, speed, parameterMin.getMin(), parameterMax.getMax()))
		{
			parameterMin.set(tmpRefMin);
			parameterMax.set(tmpRefMax);

			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}

		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return false;
	}

#if OF_VERSION_MINOR >= 10

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<glm::vec2>& parameterMin, ofParameter<glm::vec2>& parameterMax, float speed)
	{
		auto result = false;
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
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
			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}
		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<glm::vec3>& parameterMin, ofParameter<glm::vec3>& parameterMax, float speed)
	{
		auto result = false;
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
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
			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}
		IMGUI_SUGAR__SLIDER_WIDTH_POP;
		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<glm::vec4>& parameterMin, ofParameter<glm::vec4>& parameterMax, float speed)
	{
		auto result = false;
		auto tmpRefMin = parameterMin.get();
		auto tmpRefMax = parameterMax.get();

		IMGUI_SUGAR__SLIDER_WIDTH_PUSH;
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
			IMGUI_SUGAR__SLIDER_WIDTH_POP;
			return true;
		}
		IMGUI_SUGAR__SLIDER_WIDTH_POP;
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

	// lists and drop down enum/lists
	//--------------------------------------------------------------
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};
	//--------------------------------------------------------------
	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values /*,bool bUpperCase = true*/)
	{
		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - 20); // fix oversizes
		if (values.empty())
		{
			ImGui::PopItemWidth();
			return false;
		}
		bool b = ImGui::Combo(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());
		ImGui::PopItemWidth();
		return b;
	}
	//--------------------------------------------------------------
	bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ImGui::ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}
}

//--
