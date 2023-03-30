#pragma once

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "GuiConstants.h"
#include "ofHelpers.h"

using namespace ImGui;

namespace ofxImGuiSurfing
{
	//--------------------------------------------------------------
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	//--------------------------------------------------------------
	static bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values, bool bRaw = false)
	{
		//const int PADDING = 0;

		// fix oversizes
		// pass bRaw true to disable the widget padding and to draw it raw.
		if (!bRaw)
		{
			if (label != "") ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - PADDING_COMBO);
			else ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
		}


		if (values.empty())
		{
			if (!bRaw) ImGui::PopItemWidth();
			return false;
		}

		bool b = ImGui::Combo(label, currIndex, vector_getter, static_cast<void*>(&values), values.size());

		if (!bRaw) ImGui::PopItemWidth();

		return b;
	};

	//----

	// More Widgets

	// A bundle of controls
	// for a single param

	////TODO: move to ofHelpers.h (#1049) 
	////--------------------------------------------------------------
	//template<typename ParameterType>
	//bool AddComboBundle(ofParameter<ParameterType>& p, bool bMinimized = false)
	//{
	//	ofxImGuiSurfing::AddComboBundle(p, bMinimized);
	//}

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool AddComboBundle(ofParameter<ParameterType>& p, bool bMinimized = false)
	{
		string name = p.getName();

		bool bReturn = false;

		const auto& t = typeid(ParameterType);
		const bool isFloat = (t == typeid(float));
		const bool isInt = (t == typeid(int));

		if (!isFloat && !isInt) {
			ofLogWarning("ofxSurfingImGui") << "AddComboBundle: ofParam type named " + name + " is not a Float or Int";
			return false;
		}

		// label
		if (!bMinimized) this->AddLabelHuge(p.getName(), true, true);
		else this->AddLabelBig(p.getName(), true, true);

		// stepper
		bReturn += this->Add(p, OFX_IM_STEPPER_NO_LABEL);
		//bReturn += this->Add(p, bMinimized ? OFX_IM_STEPPER : OFX_IM_STEPPER_NO_LABEL);

		// slider
		bReturn += this->Add(p, bMinimized ? OFX_IM_HSLIDER_MINI_NO_LABELS : OFX_IM_HSLIDER_SMALL_NO_LABELS);

		// arrows
		ImGui::PushButtonRepeat(true); // -> pushing to repeat trigs
		{
			float step = 0;
			if (isInt) step = 1;
			else if (isFloat) step = (p.getMax() - p.getMin()) / 100.f;

			if (this->AddButton("<", bMinimized ? OFX_IM_BUTTON_MEDIUM : OFX_IM_BUTTON_BIG, 2))
			{
				p -= step;
				p = ofClamp(p, p.getMin(), p.getMax());
				bReturn += true;
			}
			ImGui::SameLine();
			if (this->AddButton(">", bMinimized ? OFX_IM_BUTTON_MEDIUM : OFX_IM_BUTTON_BIG, 2))
			{
				p += step;
				p = ofClamp(p, p.getMin(), p.getMax());
				bReturn += true;
			}
		}
		ImGui::PopButtonRepeat();

		if (!bMinimized)
		{
			// knob
			//this->Add(p, OFX_IM_KNOB_DOTKNOB);
			float w = this->getWidgetsWidth(1);
			ImGuiKnobFlags flags = 0;
			flags += ImGuiKnobFlags_NoInput;
			flags += ImGuiKnobFlags_NoTitle;
			flags += ImGuiKnobFlags_ValueTooltip;//not works
			//flags += ImGuiKnobFlags_DragHorizontal;
			bReturn += ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_DOTKNOB, w, OFX_IM_FORMAT_KNOBS, flags);

			// mouse
			if (this->bMouseWheel) {
				ofxImGuiSurfing::AddMouseWheel(p, this->bMouseWheelFlip.get());
				ofxImGuiSurfing::GetMouseWheel();
				ofxImGuiSurfing::AddMouseClickRightReset(p);
			}

			// tooltip
			this->AddTooltip(p, true, false);
		}

		return bReturn;
	}

	//----

	// moved from ofHelpers.h

	// Combo List. 

	// Selector index directly with an int ofParam
	// without name label
	//--------------------------------------------------------------
	inline bool AddCombo(ofParameter<int> pIndex, std::vector<std::string> fileNames, bool bRaw = false)
	{
		if (fileNames.empty()) return false;

		string t = "##" + pIndex.getName();
		ImGui::PushID(t.c_str());

		int i = pIndex.get();
		bool b = (VectorCombo("", &i, fileNames, bRaw));
		if (b) {
			i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
			pIndex.set(i);
			ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
		}

		//ImGui::Spacing();

		ImGui::PopID();

		return b;
	}

	// Selector index directly with an int ofParam
	// without name label and a button to browse next element. Processed inside this combo.
	//--------------------------------------------------------------
	inline bool AddComboButton(ofParameter<int>& pIndex, std::vector<std::string>& fileNames)
	{
		// Button is to trig/set next index.

		if (fileNames.empty()) return false;

		string t = "##" + pIndex.getName();
		ImGui::PushID(t.c_str());

		int i = pIndex.get();

		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.7f);
		bool b = (VectorCombo("", &i, fileNames, true));
		if (b)
		{
			i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
			pIndex.set(i);
			ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
		}
		ImGui::PopItemWidth();

		ImGui::PopID();

		ImGui::SameLine();

		float w = ImGui::GetContentRegionAvail().x;
		t += ">";
		ImGui::PushID(t.c_str());
		if (ImGui::Button(">", ImVec2(w, 0)))
		{
			if (pIndex < pIndex.getMax()) pIndex++;
			else pIndex = 0;
			b = true;
		}
		ImGui::PopID();

		ImGui::Spacing();

		return b;
	}
	// Same that above but with left/right arrows, place to the right.
	//--------------------------------------------------------------
	inline bool AddComboButtonDual(ofParameter<int>& pIndex, std::vector<std::string>& fileNames, bool bCycled = false)
	{
		if (fileNames.empty()) return false;

		string t = "##" + pIndex.getName();
		ImGui::PushID(t.c_str());

		int i = pIndex.get();

		//ImGui::PushItemWidth(20);//hide name
		//ImGui::PushItemWidth(30);
		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.2f);//small name
		//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.4f);
		//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.25f);
		//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.5f);
		//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.6f);

		bool b = (VectorCombo("", &i, fileNames, true));
		if (b)
		{
			i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
			pIndex.set(i);
			ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
		}
		ImGui::PopItemWidth();

		ImGui::PopID();

		ImGui::SameLine();

		float  __spcx = ImGui::GetStyle().ItemSpacing.x; // x spacing between widgets
		float w = ImGui::GetContentRegionAvail().x / 2 - __spcx;

		string t1 = t + "<";
		ImGui::PushID(t.c_str());
		if (ImGui::Button("<", ImVec2(w, 0)))
		{
			if (pIndex <= pIndex.getMin()) {
				if (bCycled) pIndex = pIndex.getMax();
				else pIndex = pIndex.getMin();
			}
			else {
				pIndex--;
			}
			b = true;
		}
		ImGui::PopID();
		ImGui::SameLine();

		string t2 = t + ">";
		ImGui::PushID(t.c_str());
		if (ImGui::Button(">", ImVec2(w, 0)))
		{
			if (pIndex < pIndex.getMax()) pIndex++;
			else if (bCycled) pIndex = 0;
			b = true;
		}
		ImGui::PopID();

		ImGui::Spacing();

		return b;
	}

	// Same than above (with left/right arrows) but, placed to the left.
	//--------------------------------------------------------------
	inline bool AddComboButtonDualLefted(ofParameter<int>& pIndex, std::vector<std::string>& fileNames, bool bCycled = false)
	{
		if (fileNames.empty()) return false;

		float div = 0.7f;//proportion used for the combo
		// 70% of the width is for the names and 30% for both arrows
		// 1 - div (0.3) will be the proportion used by the arrows.

		string t = "##" + pIndex.getName();
		bool b = false;

		float  __spcx = ImGui::GetStyle().ItemSpacing.x; // x spacing between widgets
		float w = 0.5f * (ImGui::GetContentRegionAvail().x * (1 - div) - __spcx);

		string t1 = t + "<";
		ImGui::PushID(t.c_str());
		if (ImGui::Button("<", ImVec2(w, 0)))
		{
			if (pIndex <= pIndex.getMin())
				if (bCycled) pIndex.getMax();
				else pIndex = pIndex.getMin();
			else pIndex--;
			b = true;
		}
		ImGui::PopID();
		ImGui::SameLine();

		string t2 = t + ">";
		ImGui::PushID(t.c_str());
		if (ImGui::Button(">", ImVec2(w, 0)))
		{
			if (pIndex < pIndex.getMax()) pIndex++;
			else if (bCycled)
				pIndex = 0;
			b = true;
		}
		ImGui::PopID();

		ImGui::SameLine();

		//--

		ImGui::PushID(t.c_str());

		int i = pIndex.get();

		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
		//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * div);

		b = (VectorCombo("", &i, fileNames, true));
		if (b)
		{
			i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
			pIndex.set(i);
			ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
		}

		ImGui::PopItemWidth();

		ImGui::PopID();

		ImGui::Spacing();

		return b;
	}

	//--

	// Same than above (with left/right arrows) but, placed to the left and right and centered names.
	//--------------------------------------------------------------
	inline bool AddComboButtonDualCenteredNames(ofParameter<int>& pIndex, std::vector<std::string>& fileNames, bool bCycled = false)
	{
		if (fileNames.empty()) return false;

		float div = 0.7f; // proportion used for the combo names 
		// 70% of the width is for the names and 30% for both arrows
		// 1 - div (0.3) will be the proportion used by the arrows.

		string t = "##" + pIndex.getName();
		bool b = false;

		float  __spcx = ImGui::GetStyle().ItemSpacing.x; // x spacing between widgets
		float w = 0.5f * (ImGui::GetContentRegionAvail().x * (1 - div) - __spcx);

		string t1 = t + "<";
		ImGui::PushID(t.c_str());
		if (ImGui::Button("<", ImVec2(w, 0)))
		{
			if (pIndex <= pIndex.getMin())
				if (bCycled) pIndex.getMax();
				else pIndex = pIndex.getMin();
			else pIndex--;
			b = true;
		}
		ImGui::PopID();
		ImGui::SameLine();

		//--

		ImGui::PushID(t.c_str());

		int i = pIndex.get();

		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - w - __spcx);
		//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * div);

		b = (VectorCombo("", &i, fileNames, true));
		if (b)
		{
			i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
			pIndex.set(i);
			ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
		}

		ImGui::PopItemWidth();

		ImGui::PopID();

		ImGui::SameLine();

		//--

		string t2 = t + ">";
		ImGui::PushID(t.c_str());
		if (ImGui::Button(">", ImVec2(w, 0)))
		{
			if (pIndex < pIndex.getMax()) pIndex++;
			else if (bCycled)
				pIndex = 0;
			b = true;
		}
		ImGui::PopID();

		return b;
	}

	//--

	// Dual arrows for common use to browse an index to be processed outside.
	// returns -1 to push-left or 1 to push-right pressed!
	//--------------------------------------------------------------
	inline int AddComboArrows(SurfingGuiTypes style = OFX_IM_BUTTON_SMALL) {
		int iReturn = 0;
		if (AddButton("<", style, 2)) {
			iReturn = -1;
		};
		SameLine();
		if (AddButton(">", style, 2)) {
			iReturn = 1;
		};
		return iReturn;
	}

	//--

	// Dual arrows for common use to browse an index to be inside directly into the int parameter
	//--------------------------------------------------------------
	inline void AddComboArrows(ofParameter<int> paramIndex, SurfingGuiTypes style = OFX_IM_BUTTON_SMALL, bool cycled = false) {

		//bool bchanged = false;//can be ignored
		if (AddButton("<", style, 2)) {
			//bchanged = true;
			if (cycled) {
				if (paramIndex == paramIndex.getMin()) paramIndex = paramIndex.getMax();
				paramIndex--;
			}
			else {
				if (paramIndex > paramIndex.getMin()) paramIndex--;
			}
		};
		SameLine();
		if (AddButton(">", style, 2)) {
			//bchanged = true;
			if (cycled) {
				if (paramIndex == paramIndex.getMax()) paramIndex = paramIndex.getMin();
				paramIndex++;
			}
			else {
				if (paramIndex < paramIndex.getMax()) paramIndex++;
			}
		};
		//return bchanged;
	}

	//---

	//TODO: moved from ofHelpers.h

	// Lists and drop down enum / lists


	/*
	//TODO:
	inline bool VectorCombo2(ofParameter<int> pIndex, std::vector<std::string> fileNames, bool braw = false);

	//TODO:
	// Combo list. 
	// Selector index directly with an int ofParam
	// without name label
	//--------------------------------------------------------------
	inline bool VectorCombo2(ofParameter<int> pIndex, std::vector<std::string> fileNames, bool braw)
	{
		if (fileNames.empty()) return false;

		string t = "##" + pIndex.getName();
		ImGui::PushID(t.c_str());

		int i = pIndex.get();
		bool b = (VectorCombo(" ", &i, fileNames));
		if (b) {
			i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
			pIndex.set(i);
			ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
		}

		ImGui::Spacing();

		ImGui::PopID();

		return b;
	};
	*/

	//--------------------------------------------------------------
	inline bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ImGui::ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}
};