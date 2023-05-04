#include "ofHelpers.h"

//--

namespace ofxImGuiSurfing
{
	//--

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& g, ImGuiTreeNodeFlags flags)
	{
		//TODO: now we are using 
		// mainly WidgetsManager.h helpers!
		// but these methods should work too.

		//--

		ImGui::PushID(("##" + g.getName()).c_str());
		{
			bool bOpened;

			{
				bOpened = ImGui::CollapsingHeader(g.getName().c_str(), flags);
				//bOpened = (!ImGui::TreeNodeEx(g.getName().c_str()));
				//bOpened = (!ImGui::TreeNode(g.getName().c_str()));
			}

			if (!bOpened)
			{
				ImGui::PopID();
				return;
			}

			//--

			for (auto p : g)
			{
				// Param Group
				auto pg = std::dynamic_pointer_cast<ofParameterGroup>(p);
				if (pg)
				{
					// Recurse through contents.
					AddGroup(*pg, ImGuiTreeNodeFlags_None);

					// -> default: all with same style and non indent ?
					//ImGui::Indent();

					continue;
				}

				// Parameter, try everything we know how to handle.
#if OF_VERSION_MINOR >= 10
				auto pVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(p);
				if (pVec2f)
				{
					ofxImGuiSurfing::AddParameter(*pVec2f);
					continue;
				}
				auto pVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(p);
				if (pVec3f)
				{
					ofxImGuiSurfing::AddParameter(*pVec3f);
					continue;
				}
				auto pVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(p);
				if (pVec4f)
				{
					ofxImGuiSurfing::AddParameter(*pVec4f);
					continue;
				}
#endif
				auto pOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(p);
				if (pOfVec2f)
				{
					ofxImGuiSurfing::AddParameter(*pOfVec2f);
					continue;
				}
				auto pOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(p);
				if (pOfVec3f)
				{
					ofxImGuiSurfing::AddParameter(*pOfVec3f);
					continue;
				}
				auto pOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(p);
				if (pOfVec4f)
				{
					ofxImGuiSurfing::AddParameter(*pOfVec4f);
					continue;
				}
				auto pFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(p);
				if (pFloatColor)
				{
					ofxImGuiSurfing::AddParameter(*pFloatColor);
					continue;
				}
				auto pFloat = std::dynamic_pointer_cast<ofParameter<float>>(p);
				if (pFloat)
				{
					ofxImGuiSurfing::AddParameter(*pFloat);
					continue;
				}
				auto pInt = std::dynamic_pointer_cast<ofParameter<int>>(p);
				if (pInt)
				{
					ofxImGuiSurfing::AddParameter(*pInt);
					continue;
				}
				auto pBool = std::dynamic_pointer_cast<ofParameter<bool>>(p);
				if (pBool)
				{
					ofxImGuiSurfing::AddParameter(*pBool);
					continue;
				}
				auto pRect = std::dynamic_pointer_cast<ofParameter<ofRectangle>>(p);
				if (pRect)
				{
					ofxImGuiSurfing::AddParameter(*pRect);
					continue;
				}

				// don't debug if it's unnamed
				if (p->getName() == "" && p->getName() == " ")
					ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) <<
					"Could not create GUI element for p " << p->getName() << "'";

				//--

				//if (pg) ImGui::Unindent();
			}

			//--

			{
				// End tree.
				//ImGui::TreePop();
			}

		}
		ImGui::PopID();
	}

	//--

#if OF_VERSION_MINOR >= 10

	//TODO: 
	// Should remake all multi dim sliders templated and/or from scratch..

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::tvec2<int>>& p, bool bfoldered)
	{
		auto tmp = p.get();

		if (ImGui::SliderInt2((p.getName().c_str()), glm::value_ptr(tmp), p.getMin().x, p.getMax().x))
		{
			p.set(tmp);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::tvec3<int>>& p, bool bfoldered)
	{
		auto tmp = p.get();

		if (ImGui::SliderInt3((p.getName().c_str()), glm::value_ptr(tmp), p.getMin().x, p.getMax().x))
		{
			p.set(tmp);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::tvec4<int>>& p, bool bfoldered)
	{
		auto tmp = p.get();

		if (ImGui::SliderInt4((p.getName().c_str()), glm::value_ptr(tmp), p.getMin().x, p.getMax().x))
		{
			p.set(tmp);

			return true;
		}

		return false;
	}

	//--

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::vec2>& p, bool bsplit, bool bfoldered)
	{
		auto tmp = p.get();

		if (!bsplit) {
			if (ImGui::SliderFloat2((p.getName().c_str()), glm::value_ptr(tmp), p.getMin().x, p.getMax().x))
			{
				p.set(tmp);

				//TODO: should include sugar here
				//wheel for multi dim params
				//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
				//ofxImGuiSurfing::AddMouseWheel(arg1);

				return true;
			}
			return false;
		}
		else
		{
			bool bExpanded = false;
			if (bfoldered)
			{
				static bool bOpen = false;
				ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
				_flagt |= ImGuiTreeNodeFlags_Framed;
				bExpanded = (ImGui::TreeNodeEx(p.getName().c_str(), _flagt));
			}
			//else bExpanded = true;

			//if (bfoldered && bExpanded) ImGui::TreePop();

			bool bchanged = false;
			//if (bExpanded)
			if (bExpanded || !bfoldered)
			{
				IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

				ImGui::Dummy(ImVec2(0, 1));
				//ImGui::Spacing();
				bchanged += ImGui::SliderFloat(((p.getName() + " X").c_str()), &tmp.x, p.getMin().x, p.getMax().x);
				bchanged += ImGui::SliderFloat(((p.getName() + " Y").c_str()), &tmp.y, p.getMin().y, p.getMax().y);
				ImGui::Dummy(ImVec2(0, 1));
			}

			if (bchanged)
			{
				p.set(tmp);

				IMGUI_SUGAR__WIDGETS_POP_WIDTH;

				if (bfoldered && bExpanded) ImGui::TreePop();
				
				return true;
			}
			if (bExpanded || !bfoldered) IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			if (bfoldered && bExpanded) ImGui::TreePop();
			
			return false;
		}
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::vec3>& p, bool bsplit, bool bfoldered)
	{
		auto tmp = p.get();

		if (!bsplit)
		{
			if (ImGui::SliderFloat3((p.getName().c_str()), glm::value_ptr(tmp), p.getMin().x, p.getMax().x))
			{
				p.set(tmp);

				return true;
			}
			return false;
		}
		else // splitted
		{
			bool bExpanded = false;
			if (bfoldered)
			{
				static bool bOpen = false;
				ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
				_flagt |= ImGuiTreeNodeFlags_Framed;
				bExpanded = (ImGui::TreeNodeEx(p.getName().c_str(), _flagt));
			}
			//else bExpanded = true;

			bool bchanged = false;

			//if (bExpanded)
			if (bExpanded || !bfoldered)//bsplit= true
			{
				IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
				ImGui::Dummy(ImVec2(0, 1));
				bchanged += ImGui::SliderFloat(((p.getName() + " X").c_str()), &tmp.x, p.getMin().x, p.getMax().x);
				bchanged += ImGui::SliderFloat(((p.getName() + " Y").c_str()), &tmp.y, p.getMin().y, p.getMax().y);
				bchanged += ImGui::SliderFloat(((p.getName() + " Z").c_str()), &tmp.z, p.getMin().z, p.getMax().z);
				ImGui::Dummy(ImVec2(0, 1));
			}

			if (bchanged)
			{
				p.set(tmp);

				IMGUI_SUGAR__WIDGETS_POP_WIDTH;
				if (bfoldered && bExpanded) ImGui::TreePop();
				return true;
			}
			if (bExpanded || !bfoldered)
				IMGUI_SUGAR__WIDGETS_POP_WIDTH;
			if (bfoldered && bExpanded) ImGui::TreePop();
			return false;
		}
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<glm::vec4>& p, bool bsplit, bool bfoldered)
	{
		auto tmp = p.get();

		if (!bsplit) {
			if (ImGui::SliderFloat4((p.getName().c_str()), glm::value_ptr(tmp), p.getMin().x, p.getMax().x))
			{
				p.set(tmp);

				return true;
			}
			return false;
		}
		else
		{
			bool bExpanded = false;
			if (bfoldered)
			{
				static bool bOpen = false;
				ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
				_flagt |= ImGuiTreeNodeFlags_Framed;
				bExpanded = (ImGui::TreeNodeEx(p.getName().c_str(), _flagt));
			}
			//else bExpanded = true;

			//TODO: BUG:
			bool bchanged = false;
			//if (bExpanded)
			if (bExpanded || !bfoldered)
			{
				IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

				//ImGui::Spacing();
				ImGui::Dummy(ImVec2(0, 1));
				bchanged += ImGui::SliderFloat(((p.getName() + " X").c_str()), &tmp.x, p.getMin().x, p.getMax().x);
				bchanged += ImGui::SliderFloat(((p.getName() + " Y").c_str()), &tmp.y, p.getMin().y, p.getMax().y);
				bchanged += ImGui::SliderFloat(((p.getName() + " Z").c_str()), &tmp.z, p.getMin().z, p.getMax().z);
				bchanged += ImGui::SliderFloat(((p.getName() + " W").c_str()), &tmp.w, p.getMin().w, p.getMax().w);
				ImGui::Dummy(ImVec2(0, 1));
			}

			if (bchanged)
			{
				p.set(tmp);

				IMGUI_SUGAR__WIDGETS_POP_WIDTH;

				if (bfoldered && bExpanded) ImGui::TreePop();
				return true;
			}
			if (bExpanded || !bfoldered) IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			if (bfoldered && bExpanded) ImGui::TreePop();

			return false;
		}
	}
#endif

	//--

	//TODO: kind of deprecated. not all features implemented
	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofVec2f>& p)
	{
		auto tmp = p.get();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (ImGui::SliderFloat2((p.getName().c_str()), tmp.getPtr(), p.getMin().x, p.getMax().x))
		{
			p.set(tmp);

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			return true;
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofVec3f>& p)
	{
		auto tmp = p.get();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (ImGui::SliderFloat3((p.getName().c_str()), tmp.getPtr(), p.getMin().x, p.getMax().x))
		{
			p.set(tmp);

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			return true;
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofVec4f>& p)
	{
		auto tmp = p.get();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (ImGui::SliderFloat4((p.getName().c_str()), tmp.getPtr(), p.getMin().x, p.getMax().x))
		{
			p.set(tmp);

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			return true;
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return false;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofRectangle>& p)
	{
		auto result = false;
		auto tmp = p.get();

		float x = tmp.getX();
		float y = tmp.getY();
		float w = tmp.getWidth();
		float h = tmp.getHeight();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		result |= ImGui::SliderFloat(((p.getName() + " x").c_str()), &x, p.getMin().x, p.getMax().x);
		result |= ImGui::SliderFloat(((p.getName() + " y").c_str()), &y, p.getMin().y, p.getMax().y);
		result |= ImGui::SliderFloat(((p.getName() + " w").c_str()), &w, p.getMin().width, p.getMax().width);
		result |= ImGui::SliderFloat(((p.getName() + " h").c_str()), &h, p.getMin().height, p.getMax().height);

		if (result) p.set(ofRectangle(x, y, w, h));

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return result;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofFloatColor>& p, bool alpha/*, ImGuiColorEditFlags flags = ImGuiColorEditFlags_None*/)
	{
		auto tmp = p.get();
		ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;

		if (alpha)
		{
			if (ImGui::ColorEdit4((p.getName().c_str()), &tmp.r, flags))
			{
				p.set(tmp);

				return true;
			}
		}
		else if (ImGui::ColorEdit3((p.getName().c_str()), &tmp.r, flags))
		{
			p.set(tmp);

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	//bool AddParameter(ofParameter<ofColor>& p, bool alpha, ImGuiColorEditFlags flags = ImGuiColorEditFlags_None)
	bool AddParameter(ofParameter<ofColor>& p, bool alpha)
	{
		ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;

		ofParameter<ofFloatColor> c;
		c.set(p.getName(),
			ofFloatColor(p.get().r / 255.f, p.get().g / 255.f, p.get().b / 255.f, p.get().a / 255.f),
			ofFloatColor(0, 0, 0, 0),
			ofFloatColor(1.f, 1.f, 1.f, 1.f)
		);

		auto tmp = c.get();

		if (alpha)
		{
			if (ImGui::ColorEdit4((p.getName().c_str()), &tmp.r, flags))
			{
				p.set(tmp);

				return true;
			}
		}
		else if (ImGui::ColorEdit3((p.getName().c_str()), &tmp.r, flags))
		{
			p.set(tmp);

			return true;
		}

		return false;
	}

	//TODO:
	// full customizable flags
	// ofColor
	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofColor>& p, bool alpha, ImGuiColorEditFlags flags)
	{
		//ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;

		ofParameter<ofFloatColor> c;

		c.set(p.getName(),
			ofFloatColor(
				p.get().r / 255.f,
				p.get().g / 255.f,
				p.get().b / 255.f,
				p.get().a / 255.f),
			ofFloatColor(0, 0, 0, 0),
			ofFloatColor(1.f, 1.f, 1.f, 1.f)
		);

		auto tmp = c.get();

		if (alpha)
		{
			if (ImGui::ColorEdit4((p.getName().c_str()), &tmp.r, flags))
			{
				p.set(tmp);

				return true;
			}
		}
		else if (ImGui::ColorEdit3((p.getName().c_str()), &tmp.r, flags))
		{
			p.set(tmp);

			return true;
		}

		return false;
	}

	// ofFloatColor
	//--------------------------------------------------------------
	bool AddParameter(ofParameter<ofFloatColor>& p, bool alpha, ImGuiColorEditFlags flags = ImGuiColorEditFlags_None)
	{
		auto tmp = p.get();

		if (alpha)
		{
			if (ImGui::ColorEdit4((p.getName().c_str()), &tmp.r, flags))
			{
				p.set(tmp);

				return true;
			}
		}
		else if (ImGui::ColorEdit3((p.getName().c_str()), &tmp.r, flags))
		{
			p.set(tmp);

			return true;
		}

		return false;
	}

	//----

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<std::string>& p, size_t maxChars, bool multiline)
	{
		auto tmp = p.get();
		char* cString = new char[maxChars];
		strcpy(cString, tmp.c_str());
		auto result = false;

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (multiline)
		{
			if (ImGui::InputTextMultiline((p.getName().c_str()), cString, maxChars))
			{
				p.set(cString);
				result = true;
			}
		}
		else if (ImGui::InputText((p.getName().c_str()), cString, maxChars))
		{
			p.set(cString);
			result = true;
		}
		delete[] cString;

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return result;
	}

	//--------------------------------------------------------------
	bool AddParameter(ofParameter<void>& p, float width)
	{
		if (ImGui::Button((p.getName().c_str()), glm::vec2(width, 0.0f)))
		{
			p.trigger();

			return true;
		}

		return false;
	}

	//--------------------------------------------------------------
	bool AddRadio(ofParameter<int>& p, std::vector<std::string> labels, int columns)
	{
		auto uniqueName = (p.getName().c_str());
		ImGui::Text("%s", uniqueName);
		auto result = false;
		auto tmp = p.get();

		ImGui::PushID(uniqueName);
		{
			ImGui::Columns(columns);
			for (size_t i = 0; i < labels.size(); ++i)
			{
				result |= ImGui::RadioButton((labels[i]).c_str(), &tmp, i);
				ImGui::NextColumn();
			}
			ImGui::Columns(1);
		}
		ImGui::PopID();

		if (result)
		{
			p.set(tmp);
		}
		return result;
	}

	/*
	//--------------------------------------------------------------
	bool AddCombo(ofParameter<int>& p, std::vector<std::string> labels, bool bRaw)
	{
		if (p.get() < 0) return false;
		if (labels.size() == 0) return false;

		const ImVec2 sz = ImGui::CalcTextSize(p.getName().c_str());

		if (!bRaw) ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - sz.x - 0.5f * PADDING_COMBO);

		auto result = false;
		auto tmp = p.get();

		auto uniqueName = (("##COMBO" + p.getName()).c_str());
		ImGui::PushID(uniqueName);

		if (ImGui::BeginCombo((p.getName().c_str()), labels.at(p.get()).c_str()))
		{
			for (size_t i = 0; i < labels.size(); ++i)
			{
				bool selected = (i == tmp);
				if (ImGui::Selectable(labels[i].c_str(), selected))
				{
					tmp = i;
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
			p.set(tmp);
		}

		if (!bRaw) ImGui::PopItemWidth();

		return result;
	}
	*/

	//--------------------------------------------------------------
	bool AddStepper(ofParameter<int>& p, int step, int stepFast, bool bRaw = false)
	{
		if (step == -1 || stepFast == -1) {
			step = (p.getMax() - p.getMin()) / 100.f;
			stepFast = (int)100.f * step;
		}

		auto tmp = p.get();

		auto uniqueName = (("##StepperInt" + p.getName()).c_str());
		ImGui::PushID(uniqueName);

		if (!bRaw) IMGUI_SUGAR__STEPPER_WIDTH_PUSH;

		bool bChanged = false;
		if (ImGui::InputInt((p.getName().c_str()), &tmp, step, stepFast))
		{
			p.set(ofClamp(tmp, p.getMin(), p.getMax()));

			bChanged = true;
		}

		if (!bRaw) IMGUI_SUGAR__STEPPER_WIDTH_POP;

		ImGui::PopID();

		return bChanged;
	}

	//--------------------------------------------------------------
	bool AddStepper(ofParameter<float>& p, float step, float stepFast, bool bRaw = false)
	{
		if (step == -1 || stepFast == -1) {
			step = (p.getMax() - p.getMin()) / 100.f;
			stepFast = 100.f * step;
		}

		auto tmp = p.get();

		auto uniqueName = (("##StepperFloat" + p.getName()).c_str());
		ImGui::PushID(uniqueName);

		if (!bRaw) IMGUI_SUGAR__STEPPER_WIDTH_PUSH;

		bool bChanged = false;
		if (ImGui::InputFloat((p.getName().c_str()), &tmp, step, stepFast))
		{
			p.set(ofClamp(tmp, p.getMin(), p.getMax()));

			bChanged = true;
		}

		if (!bRaw) IMGUI_SUGAR__STEPPER_WIDTH_POP;

		ImGui::PopID();

		return bChanged;
	}

	////TODO:
	////--------------------------------------------------------------
	//bool AddStepper(ofParameter<float>& p, float step = 0, float stepFast = 0)
	//{
	//	auto tmp = p.get();
	//	IMGUI_SUGAR__STEPPER_WIDTH_PUSH;
	//	if (ImGui::InputFloat((p.getName().c_str()), &tmp, step, stepFast))
	//	{
	//		p.set(ofClamp(tmp, p.getMin(), p.getMax()));
	//		IMGUI_SUGAR__STEPPER_WIDTH_POP;
	//		return true;
	//	}
	//	IMGUI_SUGAR__STEPPER_WIDTH_POP;
	//	return false;
	//}

	//--------------------------------------------------------------
	bool AddSlider(ofParameter<float>& p, const char* format, float power)
	{
		auto tmp = p.get();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (ImGui::SliderFloat((p.getName().c_str()), (float*)&tmp, p.getMin(), p.getMax(), format, power))
		{
			p.set(tmp);

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			return true;
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<int>& pMin, ofParameter<int>& pMax, int speed)
	{
		auto tmpMin = pMin.get();
		auto tmpMax = pMax.get();

		auto uniqueName = name.c_str();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (ImGui::DragIntRange2(uniqueName, &tmpMin, &tmpMax, speed, pMin.getMin(), pMax.getMax()))
		{
			pMin.set(tmpMin);
			pMax.set(tmpMax);

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			return true;
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<float>& pMin, ofParameter<float>& pMax, float speed)
	{
		auto tmpMin = pMin.get();
		auto tmpMax = pMax.get();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (ImGui::DragFloatRange2(name.c_str(), &tmpMin, &tmpMax, speed, pMin.getMin(), pMax.getMax()))
		{
			pMin.set(tmpMin);
			pMax.set(tmpMax);

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			return true;
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return false;
	}

#if OF_VERSION_MINOR >= 10

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<glm::vec2>& pMin, ofParameter<glm::vec2>& pMax, float speed)
	{
		auto result = false;
		auto tmpMin = pMin.get();
		auto tmpMax = pMax.get();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (ImGui::DragFloatRange2((name + " X").c_str(), &tmpMin.x, &tmpMax.x, speed, pMin.getMin().x, pMax.getMax().x))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Y").c_str(), &tmpMin.y, &tmpMax.y, speed, pMin.getMin().y, pMax.getMax().y))
		{
			result |= true;
		}

		if (result)
		{
			pMin.set(tmpMin);
			pMax.set(tmpMax);

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			return true;
		}
		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<glm::vec3>& pMin, ofParameter<glm::vec3>& pMax, float speed)
	{
		auto result = false;
		auto tmpMin = pMin.get();
		auto tmpMax = pMax.get();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (ImGui::DragFloatRange2((name + " X").c_str(), &tmpMin.x, &tmpMax.x, speed, pMin.getMin().x, pMax.getMax().x))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Y").c_str(), &tmpMin.y, &tmpMax.y, speed, pMin.getMin().y, pMax.getMax().y))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Z").c_str(), &tmpMin.z, &tmpMax.z, speed, pMin.getMin().z, pMax.getMax().z))
		{
			result |= true;
		}

		if (result)
		{
			pMin.set(tmpMin);
			pMax.set(tmpMax);

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			return true;
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return false;
	}

	//--------------------------------------------------------------
	bool AddRange(const std::string& name, ofParameter<glm::vec4>& pMin, ofParameter<glm::vec4>& pMax, float speed)
	{
		auto result = false;
		auto tmpMin = pMin.get();
		auto tmpMax = pMax.get();

		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		if (ImGui::DragFloatRange2((name + " X").c_str(), &tmpMin.x, &tmpMax.x, speed, pMin.getMin().x, pMax.getMax().x))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Y").c_str(), &tmpMin.y, &tmpMax.y, speed, pMin.getMin().y, pMax.getMax().y))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " Z").c_str(), &tmpMin.z, &tmpMax.z, speed, pMin.getMin().z, pMax.getMax().z))
		{
			result |= true;
		}

		if (ImGui::DragFloatRange2((name + " W").c_str(), &tmpMin.w, &tmpMax.w, speed, pMin.getMin().w, pMax.getMax().w))
		{
			result |= true;
		}

		if (result)
		{
			pMin.set(tmpMin);
			pMax.set(tmpMax);

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;

			return true;
		}
		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

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

	// Image and Texture helpers
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

	// Lists and drop down enum / lists

	////--------------------------------------------------------------
	//static auto vector_getter = [](void* vec, int idx, const char** out_text)
	//{
	//	auto& vector = *static_cast<std::vector<std::string>*>(vec);
	//	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	//	*out_text = vector.at(idx).c_str();
	//	return true;
	//};

	////--------------------------------------------------------------
	//bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values, bool bRaw)
	//{
	//	const int PADDING = 0;

	//	// fix oversizes
	//	// pass bRaw true to disable the widget padding and to draw it raw.
	//	if (!bRaw)
	//	{
	//		if (label != "") ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - PADDING_COMBO);
	//		else ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - PADDING);
	//	}


	//	if (values.empty())
	//	{
	//		if (!bRaw) ImGui::PopItemWidth();
	//		return false;
	//	}

	//	bool b = ImGui::Combo(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());

	//	if (!bRaw) ImGui::PopItemWidth();

	//	return b;
	//}

	////--------------------------------------------------------------
	//bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	//{
	//	if (values.empty()) { return false; }
	//	return ImGui::ListBox(label, currIndex, vector_getter,
	//		static_cast<void*>(&values), values.size());
	//}

	////TODO:
	//// Combo list. 
	//// Selector index directly with an int ofParam
	//// without name label
	////--------------------------------------------------------------
	//static bool VectorCombo2(ofParameter<int> pIndex, std::vector<std::string> fileNames, bool braw)
	//{
	//	if (fileNames.empty()) return false;
	//	string t = "##" + pIndex.getName();
	//	ImGui::PushID(t.c_str());
	//	int i = pIndex.get();
	//	bool b = (ofxImGuiSurfing::VectorCombo(" ", &i, fileNames));
	//	if (b) {
	//		i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
	//		pIndex.set(i);
	//		ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
	//	}
	//	ImGui::Spacing();
	//	ImGui::PopID();
	//	return b;
	//}
}

//--