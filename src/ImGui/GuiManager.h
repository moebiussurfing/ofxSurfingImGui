
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"

#include "ofHelpers.h"
#include "LayoutHelpers.h"
#include "WindowsOrganizer.h"

#include "ofxSurfing_ImGui_Themes.h"
#include "WidgetsManager.h"

#include "ofxSurfingHelpers.h"
#include "TextBoxWidget.h"

//--

#define OFX_IMGUI_CONSTRAIT_WINDOW_SHAPE 
// Constraint some window minimal shape sizes.

#define DEFAULT_AMOUNT_PRESETS 4

//TODO:
// Testing central view-port
//#define FIXING_DOCKING		// Need to fix yet
#define FIXING_DRAW_VIEWPORT	// To debug free space

//--

using namespace ofxImGuiSurfing;

//----

//TODO:
// These arguments are to pass to setup(..) method 
// to simplify instantiation and define settings.
//--------------------------------------------------------------
namespace ofxImGuiSurfing
{
	// Argument to be used on setup(mode);

	enum SurfingGuiMode
	{
		IM_GUI_MODE_UNKNOWN = 0,
		// Could be un defied when using legacy API maybe.

		IM_GUI_MODE_INSTANTIATED,
		// To include the ImGui context and requiring main begin/end.

		//TODO: should rename or add presets engine + docking
		IM_GUI_MODE_INSTANTIATED_DOCKING,
		// Allows docking between multiple instances.

		IM_GUI_MODE_INSTANTIATED_SINGLE,
		// To include the ImGui context and requiring begin/end but a single ImGui instance, no other add-ons.

		//IM_GUI_MODE_SPECIAL_WINDOWS, 
		// // TODO: could simplify API, bc it's duplicated from 
		//ui.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

		IM_GUI_MODE_REFERENCED,
		// TODO: -> To receive the parent (ofApp scope) ImGui object as reference.

		IM_GUI_MODE_NOT_INSTANTIATED
		// To render windows and widgets only. Inside an external ImGui context begin/end (newFrame).
	};

	//--

	// To enable Special windows mode.
	// Then handles Organizer and Align windows.
	enum SurfingGuiModeWindows
	{
		IM_GUI_MODE_WINDOWS_SPECIAL_UNKNOWN = 0,
		IM_GUI_MODE_WINDOWS_SPECIAL_DISABLED,
		IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER
	};
}

//--------

//--------------------------------------------------------------
class SurfingGuiManager
{

public:

	SurfingGuiManager();
	~SurfingGuiManager();

	//--

public:

	//--------------------------------------------------------------
	void setup() // We will use the most common mode, to avoid to have to require any argument.
	{
		setup(IM_GUI_MODE_INSTANTIATED);
	}

	void setup(ofxImGuiSurfing::SurfingGuiMode mode);

private:

	// MODE A: 
	// ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).
	void setupInitiate();

public:

	// MODE B: 
	// TODO: WIP. Not tested in depth.
	// Can be instantiated out of the class, locally
	void setup(ofxImGui::Gui& gui);

	//--

private:

	void update(); // To manual update...
	void draw(ofEventArgs& args); // Auto draw but it's used only to draw help boxes.

	void keyPressed(ofKeyEventArgs& eventArgs);
	void keyReleased(ofKeyEventArgs& eventArgs);

	//----

	// The Widget Styles Manager

private:

	WidgetsManager widgetsManager;

	//----

	// Styles API

public:

	// ofParameters 

	// Draw styled parameter into ImGui manager
	// 
	//--------------------------------------------------------------
	bool Add(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		return widgetsManager.Add(aparam, type, amtPerRow, bSameLine, spacing);
	}

	//TODO:
	//--------------------------------------------------------------
	bool Add(ofAbstractParameter& aparam, SurfingGuiTypes type, int amtPerRow, SurfingGuiFlags flags)
	{
		return widgetsManager.Add(aparam, type, amtPerRow, flags);
	}

	//TODO: New API
	// Final step method, Draws using an absolute width
	//-----------------------------------------------------------------
	//bool Add(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, float width = -1, bool bSameLine = false, int spacing = -1, SurfingGuiFlags flags = SurfingGuiFlags_None) {
		//return widgetsManager.Add(aparam, type, width, bSameLine, spacing, flags);
	//}

	////-----------------------------------------------------------------
	//bool Add(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, float width = -1, SurfingGuiFlags flags = SurfingGuiFlags_None) {
	//	bool bSameLine = false; 
	//	int spacing = -1;

	//		return widgetsManager.Add(aparam, type, width, bSameLine, spacing, flags);
	//}

	////TODO avoid multiple ambiguous
	//bool Add(ofAbstractParameter& aparam, SurfingGuiTypes type) 
	//{
	//	return widgetsManager.Add(aparam, type, -1, false, -1, SurfingGuiFlags_None);
	// }

	//----

	// STYLES

	// Queue style for the parameter
	//--------------------------------------------------------------
	void AddStyle(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		widgetsManager.AddStyle(aparam, type, amtPerRow, bSameLine, spacing);
	}

	// Queue style for the parameter
	//--------------------------------------------------------------
	void AddStyle(std::string name, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		widgetsManager.AddStyle(name, type, amtPerRow, bSameLine, spacing);
	}

	// Update style for the parameter
	//--------------------------------------------------------------
	void UpdateStyle(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		widgetsManager.UpdateStyle(aparam, type, amtPerRow, bSameLine, spacing);
	}
	//--------------------------------------------------------------
	void UpdateStyle(std::string name, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		widgetsManager.UpdateStyle(name, type, amtPerRow, bSameLine, spacing);
	}

	//--

public:

	// ofParametersGroup's 

	//--------------------------------------------------------------
	void AddStyleGroup(ofParameterGroup& group, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		widgetsManager.AddStyleGroup(group, type, flags);
	}
	//--------------------------------------------------------------
	void AddStyleGroup(std::string name, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		widgetsManager.AddStyleGroup(name, type, flags);
	}
	//--------------------------------------------------------------
	void UpdateStyleGroup(ofParameterGroup& group, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		widgetsManager.UpdateStyleGroup(group, type, flags);
	}
	//--------------------------------------------------------------
	void UpdateStyleGroup(std::string name, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		widgetsManager.UpdateStyleGroup(name, type, flags);
	}

	//TODO: new API
	//--------------------------------------------------------------
	void AddStyleGroup(std::string name, SurfingGuiGroupStyle flags)
	{
		SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		//TODO:
		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_Hidden)
		{
			type = OFX_IM_GROUP_HIDDEN;
			widgetsManager.AddStyleGroup(name, type, flagst);
			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			widgetsManager.AddStyleGroup(name, type, flagst);
			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			widgetsManager.AddStyleGroup(name, type, flagst);
			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			widgetsManager.AddStyleGroup(name, type, flagst);
			return;
		}

		widgetsManager.AddStyleGroup(name, type, flagst);
	}

	//TODO:
	//--------------------------------------------------------------
	void AddStyleGroup(ofParameterGroup& group, SurfingGuiGroupStyle flags)
	{
		SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		//TODO:
		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_Hidden)
		{
			type = OFX_IM_GROUP_HIDDEN;
			widgetsManager.AddStyleGroup(group, type, flagst);
			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			widgetsManager.AddStyleGroup(group, type, flagst);
			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			widgetsManager.AddStyleGroup(group, type, flagst);
			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			widgetsManager.AddStyleGroup(group, type, flagst);
			return;
		}

		widgetsManager.AddStyleGroup(group, type, flagst);
	}

	//--------------------------------------------------------------
	void UpdateStyleGroup(std::string name, SurfingGuiGroupStyle flags)
	{
		SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		//TODO:
		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_Hidden)
		{
			type = OFX_IM_GROUP_HIDDEN;
			widgetsManager.UpdateStyleGroup(name, type, flagst);
			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			widgetsManager.UpdateStyleGroup(name, type, flagst);
			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			widgetsManager.UpdateStyleGroup(name, type, flagst);
			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			widgetsManager.UpdateStyleGroup(name, type, flagst);
			return;
		}

		widgetsManager.UpdateStyleGroup(name, type, flagst);
	}

	//TODO:
	//--------------------------------------------------------------
	void UpdateStyleGroup(ofParameterGroup& group, SurfingGuiGroupStyle flags)
	{
		SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		//TODO:
		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_Hidden)
		{
			type = OFX_IM_GROUP_HIDDEN;
			widgetsManager.UpdateStyleGroup(group, type, flagst);
			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			widgetsManager.UpdateStyleGroup(group, type, flagst);
			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			widgetsManager.UpdateStyleGroup(group, type, flagst);
			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			widgetsManager.UpdateStyleGroup(group, type, flagst);
			return;
		}

		widgetsManager.UpdateStyleGroup(group, type, flagst);
	}

	//--

	//TODO:
	// Helper to auto populate the styles of each type (bool, floats, ints) contained on a group.
	//--------------------------------------------------------------
	void AddStyleGroupForBools(ofParameterGroup& group, SurfingGuiTypes type = OFX_IM_TOGGLE)
	{
		for (int i = 0; i < group.size(); i++)
		{
			ofAbstractParameter& ap = group[i];
			if (ap.type() == typeid(ofParameter<bool>).name()) {
				widgetsManager.AddStyle(ap, type);
			}

			//TODO: make it recursive
			//else if (ap.type() == typeid(ofParameterGroup).name()) {
			//	AddStyleGroupForBools(ap, type);
			//}
		}
	}
	//--------------------------------------------------------------
	void AddStyleGroupForFloats(ofParameterGroup& group, SurfingGuiTypes type = OFX_IM_HSLIDER)
	{
		for (int i = 0; i < group.size(); i++)
		{
			ofAbstractParameter& ap = group[i];
			if (ap.type() == typeid(ofParameter<float>).name()) {
				widgetsManager.AddStyle(ap, type);
			}
		}
	}
	//--------------------------------------------------------------
	void AddStyleGroupForInts(ofParameterGroup& group, SurfingGuiTypes type = OFX_IM_HSLIDER)
	{
		for (int i = 0; i < group.size(); i++)
		{
			ofAbstractParameter& ap = group[i];
			if (ap.type() == typeid(ofParameter<int>).name()) {
				widgetsManager.AddStyle(ap, type);
			}
		}
	}

	//--

	// Legacy
	//--------------------------------------------------------------
	void clearStyles()
	{
		widgetsManager.clear(); // update sizes to current window shape
	}

	//--------------------------------------------------------------
	void ClearStyles()
	{
		widgetsManager.clear(); // update sizes to current window shape
	}

	//--

	// Disables a Widget and reduces transparency of most common colors.

public:

	//--------------------------------------------------------------
	inline void pushInactive() {

		const float a = 0.5f;

		ImGuiStyle* style = &ImGui::GetStyle();

		const ImVec4 cFrameBg = style->Colors[ImGuiCol_FrameBg];
		const ImVec4 cButton = style->Colors[ImGuiCol_Button];
		const ImVec4 cActive = style->Colors[ImGuiCol_ButtonActive];
		const ImVec4 cSliderGrab = style->Colors[ImGuiCol_SliderGrab];
		const ImVec4 cBorder = style->Colors[ImGuiCol_Border];
		const ImVec4 cText = style->Colors[ImGuiCol_Text];

		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(cFrameBg.x, cFrameBg.y, cFrameBg.z, cFrameBg.w * a));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(cButton.x, cButton.y, cButton.z, cButton.w * a));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(cActive.x, cActive.y, cActive.z, cActive.w * a));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(cSliderGrab.x, cSliderGrab.y, cSliderGrab.z, cSliderGrab.w * a));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(cBorder.x, cBorder.y, cBorder.z, cBorder.w * a));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(cText.x, cText.y, cText.z, cText.w * a));

		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
	}
	//--------------------------------------------------------------
	inline void popInactive() {
		ImGui::PopItemFlag();

		ImGui::PopStyleColor(6);
	}

	//----

public:

	// Styles Engine
	// 
	// widgetsManager

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags, SurfingGuiTypesGroups typeGroup, ImGuiCond cond = ImGuiCond_Once)
	{
		widgetsManager.AddGroup(group, flags, typeGroup, cond);
	}

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& group, bool bOpen, ImGuiCond cond = ImGuiCond_None)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
		if (bOpen) flags = ImGuiTreeNodeFlags_DefaultOpen;
		SurfingGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT;

		widgetsManager.AddGroup(group, flags, typeGroup, cond);
	}

	//TODO:
	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& group, SurfingGuiGroupStyle flags = SurfingGuiGroupStyle_None)
	{
		////TODO: some subfolders make grow window width..
		//refreshLayout();

		SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//TODO:
		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_None)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			widgetsManager.AddGroup(group, flagst, type);

			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_Hidden)
		{
			type = OFX_IM_GROUP_HIDDEN;
			widgetsManager.AddGroup(group, flagst, type);

			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			widgetsManager.AddGroup(group, flagst, type);

			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;

			//// ? return ?
			//widgetsManager.AddGroup(group, flagst, type);

			//return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			widgetsManager.AddGroup(group, flagst, type);

			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			widgetsManager.AddGroup(group, flagst, type);

			return;
		}

		widgetsManager.AddGroup(group, flagst, type);
	}

	//----

	//TODO: Auto creates a window for the group
	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& group, ImGuiTreeNodeFlags flags, SurfingGuiTypesGroups typeGroup)
	{
		if (bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (this->BeginWindow((string)group.getName(), NULL, flags))
		{
			widgetsManager.AddGroup(group, flags, typeGroup);

			this->EndWindow();
		}
	}
	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& group, ofParameter<bool>& _bGui, ImGuiTreeNodeFlags flags, SurfingGuiTypesGroups typeGroup)
	{
		if (!_bGui) return;

		if (bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

		//if (this->BeginWindow((string)group.getName(), _bGui, flags))
		if (this->BeginWindow((string)_bGui.getName(), _bGui, flags))
		{
			widgetsManager.AddGroup(group, flags, typeGroup);

			this->EndWindow();
		}
	}

	//TODO: API update
	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& group, ofParameter<bool>& _bGui, SurfingGuiGroupStyle flags = SurfingGuiGroupStyle_None)
	{
		if (!_bGui) return;

		ImGuiWindowFlags f = ImGuiWindowFlags_None;
		if (bAutoResize) f |= ImGuiWindowFlags_AlwaysAutoResize;

		if (this->BeginWindow((string)_bGui.getName(), _bGui, flags))
		{
			this->AddGroup(group, flags);
			//widgetsManager.AddGroup(group, flags);

			this->EndWindow();
		}
	}
	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& group, SurfingGuiGroupStyle flags = SurfingGuiGroupStyle_None)
	{
		ImGuiWindowFlags f = ImGuiWindowFlags_None;
		if (bAutoResize) f |= ImGuiWindowFlags_AlwaysAutoResize;

		if (this->BeginWindow((string)group.getName(), NULL, f))
		{
			this->AddGroup(group, flags);
			//widgetsManager.AddGroup(group, flags);

			this->EndWindow();
		}
	}

	//----

	// More Widgets

	// Combo list. 

	// Selector index directly with an int ofParam
	// without name label
	//--------------------------------------------------------------
	bool AddCombo(ofParameter<int> pIndex, std::vector<std::string> fileNames, bool braw = false)
	{
		if (fileNames.empty()) return false;

		string t = "##" + pIndex.getName();
		ImGui::PushID(t.c_str());

		int i = pIndex.get();
		bool b = (ofxImGuiSurfing::VectorCombo("", &i, fileNames));
		if (b) {
			i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
			pIndex.set(i);
			ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
		}

		ImGui::Spacing();

		ImGui::PopID();

		return b;
	}

	// Selector index directly with an int ofParam
	// without name label and a button to browse next element. Processed inside this combo.
	//--------------------------------------------------------------
	bool AddComboButton(ofParameter<int> pIndex, std::vector<std::string> fileNames)
	{
		// Button is to trig/set next index.

		if (fileNames.empty()) return false;

		string t = "##" + pIndex.getName();
		ImGui::PushID(t.c_str());

		int i = pIndex.get();

		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.7f);
		bool b = (ofxImGuiSurfing::VectorCombo("", &i, fileNames, true));
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
	bool AddComboButtonDual(ofParameter<int>& pIndex, std::vector<std::string> fileNames, bool bCycled = false)
	{
		if (fileNames.empty()) return false;

		string t = "##" + pIndex.getName();
		ImGui::PushID(t.c_str());

		int i = pIndex.get();

		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.6f);
		bool b = (ofxImGuiSurfing::VectorCombo("", &i, fileNames, true));
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
	// Same that above (with left/right arrows) but, placed to the left.
	//--------------------------------------------------------------
	bool AddComboButtonDualLefted(ofParameter<int> pIndex, std::vector<std::string> fileNames, bool bCycled = false)
	{
		if (fileNames.empty()) return false;

		float div = 0.7f;//proportion used for the combo
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

		b = (ofxImGuiSurfing::VectorCombo("", &i, fileNames, true));
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

	// Dual arrows for common use to browse an index to be processed outside.
	//--------------------------------------------------------------
	int AddComboArrows(SurfingGuiTypes style = OFX_IM_BUTTON_SMALL) {
		//returns -1 to left or 1 to right pressed
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
	void AddComboArrows(ofParameter<int> paramIndex, SurfingGuiTypes style = OFX_IM_BUTTON_SMALL, bool cycled = false) {

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

	//----

	// Text with Uppercasing and Spacing

	//--------------------------------------------------------------
	void AddLabel(std::string label, bool bUppercase = false, bool bSpacing = false)
	{
		std::string t = bUppercase ? ofToUpper(label) : label;
		if (bSpacing) this->AddSpacing();
		ImGui::TextWrapped(t.c_str());
		if (bSpacing) this->AddSpacing();
	}
	//--------------------------------------------------------------
	void AddLabelBig(std::string label, bool bUppercase = false, bool bSpacing = false)
	{
		std::string t = bUppercase ? ofToUpper(label) : label;
		if (bSpacing) this->AddSpacing();
		pushStyleFont(1);
		ImGui::TextWrapped(t.c_str());
		popStyleFont();
		if (bSpacing) this->AddSpacing();
	}
	//--------------------------------------------------------------
	void AddLabelHuge(std::string label, bool bUppercase = false, bool bSpacing = false)
	{
		std::string t = bUppercase ? ofToUpper(label) : label;
		if (bSpacing) this->AddSpacing();
		pushStyleFont(2);
		ImGui::TextWrapped(t.c_str());
		popStyleFont();
		if (bSpacing) this->AddSpacing();
	}

	//--------------------------------------------------------------
	void AddLinkURL(string label, string url, bool bBlink = false)
	{
		ofxImGuiSurfing::AddLinkURL(label.c_str(), url.c_str(), 1.0f, bBlink);
	}

	//--

	//// Simplified Text without Uppercasing not Spacing

	////--------------------------------------------------------------
	//void AddText(std::string label)
	//{
	//	AddLabel(label, false, false);
	//}
	////--------------------------------------------------------------
	//void AddTextBig(std::string label)
	//{
	//	AddLabelBig(label, false, false);
	//}
	////--------------------------------------------------------------
	//void AddTextHuge(std::string label)
	//{
	//	AddLabelHuge(label, false, false);
	//}

	//--

	//--------------------------------------------------------------
	void AddTooltip(std::string text, bool bEnabled = true)
	{
		ofxImGuiSurfing::AddTooltip(text, bEnabled);
	}

	//----

	// To help API coherence and/or Legacy
	//--------------------------------------------------------------
	void AddSpacingSmall()
	{
		ofxImGuiSurfing::AddSpacingSmall();
	}
	//--------------------------------------------------------------
	void AddSpacingDouble()
	{
		ofxImGuiSurfing::AddSpacingDouble();
	}
	//--------------------------------------------------------------
	void AddSpacing()
	{
		ofxImGuiSurfing::AddSpacing();
	}
	//--------------------------------------------------------------
	void AddSeparator()
	{
		ofxImGuiSurfing::AddSeparator();
	}
	//--------------------------------------------------------------
	void AddSeparated()
	{
		ofxImGuiSurfing::AddSeparator();
	}
	//--------------------------------------------------------------
	void AddSpacingBig()
	{
		ofxImGuiSurfing::AddSpacingBig();
	}
	//--------------------------------------------------------------
	void AddSpacingBigSeparated()
	{
		ofxImGuiSurfing::AddSpacingBigSeparated();
	}
	//--------------------------------------------------------------
	void AddSpacingSeparated()
	{
		ofxImGuiSurfing::AddSpacingSeparated();
	}
	//--------------------------------------------------------------
	void AddSpacingHuge()
	{
		ofxImGuiSurfing::AddSpacingHuge();
	}
	//--------------------------------------------------------------
	void AddSpacingHugeSeparated()
	{
		ofxImGuiSurfing::AddSpacingHugeSeparated();
	}

	//--

	// Button Repeats
	//--------------------------------------------------------------
	void PushButtonRepeat(bool b = true)
	{
		ImGui::PushButtonRepeat(b);
	}

	//--------------------------------------------------------------
	void PopButtonRepeat()
	{
		ImGui::PopButtonRepeat();
	}

	//----

public:

	//--------------------------------------------------------------
	void refreshLayout()
	{
		widgetsManager.refreshLayout(); // update sizes to current window shape
	}
	//--------------------------------------------------------------
	void resetUniqueNames()
	{
		widgetsManager.resetUniqueNames(); // update sizes to current window shape
	}

	//--

	//--------------------------------------------------------------
	void Indent()
	{
		ImGui::Indent();
		refreshLayout();//auto calculate widgets common sizes
	}

	//--------------------------------------------------------------
	void Unindent()
	{
		ImGui::Unindent();
		refreshLayout();//auto calculate widgets common sizes
	}

	//--------------------------------------------------------------
	void Separator()
	{
		ImGui::Separator();
	}

	//----

private:

	// Special Windows Mode

	SurfingGuiModeWindows specialsWindowsMode = IM_GUI_MODE_WINDOWS_SPECIAL_UNKNOWN;

public:

	//--------------------------------------------------------------
	void setWindowsMode(SurfingGuiModeWindows mode) { // Call before setup.
		specialsWindowsMode = mode;

		////workflow
		////TODO:
		//if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		//{
		//	bGui_Organizer = true;
		//	bGui_SpecialWindows = true;
		//}
	}

private:

	// Instantiation

	SurfingGuiMode surfingImGuiMode = IM_GUI_MODE_UNKNOWN;

	//----

private:

	// ImGui instance/context

	// We have two mode for instantiate ImGui
	ofxImGui::Gui gui; // ImGui is inside the add-on
	ofxImGui::Gui* guiPtr = NULL; // To be used when ImGui is passed by reference in the parent scope (ofApp)

	// Initiates ofxImGui with the common settings
	void setupImGui();

	// Prepare 3 different font sizes to use on labels or any widgets.
	void setupImGuiFonts();

	//--

public:

	//TODO: WIP
	// To share the same Gui between/with other add-ons.

	//--------------------------------------------------------------
	ofxImGui::Gui* getGuiPtr() {
		if (guiPtr == NULL) return &gui;
		else return guiPtr;
	}

	//--------------------------------------------------------------
	ofxImGui::Gui& getGui() {
		if (guiPtr == NULL) return gui;
		else return *guiPtr;
	}

	//----

	// Context getter shortcut
	// sometimes useful,
	// when requiring to access to some deep functions,
	// like positioning windows on the view-port 
	// like on Aligners and Organizer sections.
	//https://github.com/ocornut/imgui/issues/5287

//public:
private:

	//--------------------------------------------------------------
	ImGuiContext* getContext() {
		return ImGui::GetCurrentContext();
	}

	//----

public:

	// API

	// To the global context: 
	// All the windows MUST be populated in between!

	// 1. Main BEGIN feed widgets!
	void Begin();

	// 2. Main END feed widgets!
	void End();

	//----

	// Window methods

	// 1. BEGINs a Window

	bool BeginWindow(ofParameter<bool>& p);
	// will use the bool param for show/hide
	// and the param name for the window name

	bool BeginWindow(std::string name, ofParameter<bool>& p);
	//  to change the name, and not use the param name.

	bool BeginWindow(std::string name, ofParameter<bool>& p, ImGuiWindowFlags window_flags);

	bool BeginWindow(ofParameter<bool>& p, ImGuiWindowFlags window_flags);
	// will use the bool param for show/hide and the param name for the window name

	bool BeginWindow(std::string name, bool* p_open, ImGuiWindowFlags window_flags);
	bool BeginWindow(std::string name, bool* p_open);
	bool BeginWindow(std::string name);
	bool BeginWindow(char* name = "Window");

	//--

	// 2. ENDs a Window

	void EndWindow();

	//----
	// 
	// Tree / Folders Helpers
	// 
	//TODO: could improve by doing open stat handled by ImGui.. now is forced
	//--------------------------------------------------------------
	bool BeginTree(string label, bool open = false, bool bIndented = true, ImGuiTreeNodeFlags flagsTree = ImGuiTreeNodeFlags_Framed)
		//bool BeginTree(string label, bool bIndented = true, bool open = false, ImGuiTreeNodeFlags flagsTree = ImGuiTreeNodeFlags_Framed)
	{
		bool b = (ofxImGuiSurfing::BeginTree(label, open, flagsTree));
		if (b) {
			if (bIndented) this->Indent();
			else this->refreshLayout();
		}

		return b;
	}
	//--------------------------------------------------------------
	void EndTree(bool bIndented = true)
	{
		ImGui::TreePop();
		if (bIndented) this->Unindent();
		else this->refreshLayout();
	}

	//--


	//---

	// Blink Helpers

//#define BLINK_MIN 0.2f 
//#define BLINK_MAX 0.5f 

	// Will Blink the contained widgets between begin/end
	 
	//--------------------------------------------------------------
	inline void BeginBlinkFrame(bool bBlink = true)
	{
		if (bBlink)
		{
			// Border when selected
			float a = 0.5f;
			float borderLineWidth = 1.0f;
			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
			ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			float blinkValue = ofxSurfingHelpers::getFadeBlink();
			a = ofClamp(blinkValue, BLINK_MIN, BLINK_MAX);
			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
		}
	}
	//--------------------------------------------------------------
	inline void EndBlinkFrame(bool bBlink = true)
	{
		if (bBlink)
		{
			ImGui::PopStyleColor();
			ImGui::PopStyleVar(1);
		}
	}

	//--------------------------------------------------------------
	inline void BeginBlinkText(bool bBlink = true)
	{
		if (bBlink)
		{
			float a = 0.5f;
			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 c_ = style->Colors[ImGuiCol_Text];
			ImVec4 c = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			float v = ofxSurfingHelpers::getFadeBlink();
			a = ofClamp(v, BLINK_MIN, BLINK_MAX);
			c = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			ImGui::PushStyleColor(ImGuiCol_Text, c);
		}
	}
	//--------------------------------------------------------------
	inline void EndBlinkText(bool bBlink = true)
	{
		if (bBlink)
		{
			ImGui::PopStyleColor();
		}
	}

	// Border Highlight without blinking
	//--------------------------------------------------------------
	inline void BeginBorderFrame()
	{
		float a = 1.f;
		float borderLineWidth = 1.0f;
		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

		ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
	}
	//--------------------------------------------------------------
	inline void EndBorderFrame()
	{
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(1);
	}

	//----

private:

	// The ImGui instance options

	bool bAutoDraw;
	//TODO: must be false when multiple ImGui instances created ? 
	// Currently not important, kind of deprecated.

	bool bViewport = false;
	bool bDockingModeCentered = false; //TODO: enables full screen ImGuiDockNodeFlags_PassthruCentralNode

	//-

public:

	// API 
	// Some options

	// Force autodraw
	//--------------------------------------------------------------
	void setImGuiAutodraw(bool b) { bAutoDraw = b; }
	// must be called before setup! default is false. For ImGui multi-instance.

	void setImGuiAutoResize(bool b) { bAutoResize = b; }
	// must be called before setup! default is false. For ImGui multi-instance.

	//--

	void setImGuiViewPort(bool b) { bViewport = b; }
	// must be called before setup! 

	void setImGuiDocking(bool b) { setDocking(b); }
	// must call before setup

	void setImGuiDockingModeCentered(bool b) { bDockingModeCentered = b; } // Allows docking on bg window viewport. Default is enabled. Must be called before setup! 

	void setImGuiDockingShift(bool b) { ImGui::GetIO().ConfigDockingWithShift = b; }

	//--

public:

	// Force shared context

	//--------------------------------------------------------------
	void setImGuiSharedMode(bool b) { gui.setSharedMode(b); }

	//----

	// Fonts Runtime Management 

private:

	ImFont* customFont = nullptr;
	vector<ImFont*> customFonts;
	bool bIgnoreNextPopFont = false;

public:

	void clearFonts();

	bool addFont(std::string path, int size);//TODO: required? bc pushFont workflow..
	bool pushFont(std::string path, int size);

private:

	int currFont = 0;
	void processOpenFileSelection(ofFileDialogResult openFileResult, int size);

public:

	void openFontFileDialog(int size = 10);//opens file dialog window to pick a font file, passing the desired size.

public:

	void setDefaultFontIndex(int index);
	void setDefaultFont();

	// Enable some previously added font
	// Take care not pushing a non existing index or it will crash!
	void pushStyleFont(int index);
	void popStyleFont();

	int getNumFonts() { return customFonts.size(); }

	//--------------------------------------------------------------
	string getFontName(int index) {
		string s = "UNKNOWN";

		if (index < customFonts.size())
		{
			if (customFonts[index] != nullptr)
				s = (customFonts[index]->ConfigData->Name);
			return s;
		}

		return s;
	}

	//----

public:

	//--------------------------------------------------------------
	bool isMouseOverGui() {
		return bMouseOverGui;
	}

	//TODO: WIP
	//--------------------------------------------------------------
	bool isOverInputText() {
		return bInputText;
	}

	//----

private:

	ofParameter<bool> bDrawView1{ "Draw View 1", false };
	// debug drawing central zone for docking help

	bool bUseAdvancedSubPanel = true;
	// enable advanced sub panel

	//-

	// Exposed useful public params:

public:

	ofParameter<bool> bGui{ "Show Gui", true };
	ofParameter<bool> bMinimize{ "Minimize", true };
	ofParameter<bool> bAutoResize{ "Auto Resize", true };
	ofParameter<bool> bKeys{ "Keys", true };
	ofParameter<bool> bLogKeys{ "Log Keys", false };
	ofParameter<bool> bHelp{ "Help App", false };
	ofParameter<bool> bHelpInternal{ "Help Internal", false };
	ofParameter<bool> bDebug{ "Debug", false };
	ofParameter<bool> bDebugMetrics{ "Metrics", false };
	ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bAdvanced{ "Advanced", false };
	ofParameter<bool> bReset{ "Reset", false };
	ofParameter<bool> bMouseWheel{ "Mouse Wheel", true };
	ofParameter<bool> bMouseWheelFlip{ "Flip Wheel" , false };
	ofParameter<bool> bGui_GameMode{ "Game Mode", false };
	//to allow a type of super simple window for final user!

	ofParameter<bool> bLockMove{ "Lock Move", false };//TODO:
	ofParameter<bool> bReset_Window{ "Reset Window", false };//TODO:
	ofParameter<bool> bNoScroll{ "No Scroll", false };//TODO:
	ofParameter<bool> bLandscape{ "Orientation", false };
	//TODO: could add a trigger to flip orientation

	ofParameter<bool> bLinkGlobal{ "Link Global", true };//TODO:
	//TODO: link windows between contexts/add-ons/ gui instances

	ofParameter<bool> bGui_Organizer{ "ORGANIZER", false };
	ofParameter<bool> bGui_Aligners{ "ALIGNERS", false };
	ofParameter<bool> bGui_SpecialWindows{ "SPECIAL WINDOWS", false };

	//--

	ofParameterGroup params_Advanced{ "Params Advanced" };
	// These params are saved as settings when exit and loaded when reopen the App. 

private:

	void buildHelpInfo();//create or freshed the help info for the drawing help box

	//--

	// Rectangles to handle main window sections 

	// Positions and shape, bc we disable the ImGui management, 
	// to exclude storing on presets and imgui.ini!

private:

	ofParameterGroup params_RectPanels{ "Rectangles Windows" };
	vector<ofParameter<ofRectangle>> rectangles_Windows;

	ofParameter<ofRectangle> rect0_Presets{ "rect_Presets",
		ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080) };

	ofParameter<ofRectangle> rect1_Panels{ "rect_Panels",
		ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080) };

	ofParameter<ofRectangle> rect2_Manager{ "rect_Manager",
		ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080) };

	ImGuiWindowFlags flags_wPr;
	ImGuiWindowFlags flags_wPanels;

	//--

	// Presets windows
	ofParameter<bool> bReset_PresetsWindow{ "Reset", false };
	ofParameter<bool> bAutoResize_PresetsWindows{ "Auto Resize", true };
	ofParameter<bool> bMinimize_Presets{ "Minimize", true };

	// Panels windows
	ofParameter<bool> bReset_WindowPanels{ "Reset", false };
	ofParameter<bool> bAutoResize_Panels{ "Auto Resize", true };
	//ofParameter<bool> bMinimize_Panels{ "Minimize Panels", true };

	ofParameterGroup params_WindowPresets{ "Window Presets" };
	ofParameterGroup params_WindowPanels{ "Window Panels" };
	ofParameterGroup params_WindowsEngine{ "Engine Windows" };

private:

	ofParameter<bool> bMouseOverGui{ "Mouse OverGui", false }; // mouse is over gui
	ofParameter<bool> bInputText{ "Input Text", false }; // user is over a text input
	//ofParameter<bool> bAutoLockGuiToBorder{ "Lock GUI", false }; // force position
	//--

public:

	//TODO:

	// Some methods to reset windows layouts..

	//--------------------------------------------------------------
	void resetWindowImGui(bool pos = true, bool size = true)
	{
		//float ww = PANEL_WIDGETS_WIDTH_MIN;
		//float hh = PANEL_WIDGETS_HEIGHT;

		float xx = 10;
		float yy = 10;
		float ww = 200;
		float hh = 600;

		ImGuiCond flagsCond = ImGuiCond_Always;
		//flagsCond |= ImGuiCond_Appearing;
		//flagsCond |= ImGuiCond_Once;

		if (size) ImGui::SetWindowSize(ImVec2(ww, hh), flagsCond);
		if (pos) ImGui::SetWindowPos(ImVec2(xx, yy), flagsCond);
	}

	//----

	// Log Window

private:

	// Window Log
	ImGuiLogWindow log; // could be public 

public:

	//--------------------------------------------------------------
	void DrawWindowLogIfEnabled() {
		if (bLog) log.ImGui(bLog);
	}

	//--------------------------------------------------------------
	void DrawWindowLog() {
		static ofParameter<bool>b{ "LOG", true };
		log.ImGui(b);
	}

	// Legacy API
	//--------------------------------------------------------------
	void AddToLog(std::string text)//print message to log window
	{
		// Log
		log.AddText(text);
	}

	//public:
		//// Legacy API
		////--------------------------------------------------------------
		//void printToLog(std::string text)//print message to log window
		//{
		//	AddToLog(text);
		//}
		////--------------------------------------------------------------
		//void logAdd(std::string text) {
		//	AddToLog(text);
		//}
		////--------------------------------------------------------------
		//void AddLog(std::string text) {
		//	AddToLog(text);
		//}

		//----

		// Advanced Window

private:

	// An advanced/extra common panel
	// with some bool toggles commonly used.

	// Example:
	// Snippet to copy/paste into out ofApp:
	//ofxImGuiSurfing::AddToggleRoundedButton(ui.bAdvanced);
	//ui.DrawAdvancedSubPanel();

	//--------------------------------------------------------------
	void DrawAdvancedControls() {
		DrawAdvancedBundle();
	}

public:

	// Example:
	// Snippet to copy/paste into out ofApp:
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;;
	//if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//if (ui.bLockMove) window_flags |= ImGuiWindowFlags_NoMove;
	//ui.BeginWindow("ofApp", NULL, window_flags);

	//--------------------------------------------------------------
	void DrawWindowAdvanced(bool bForceVisible = false)
	{
		bool b;
		if (!bForceVisible) b = BeginWindow(bAdvanced);
		else b = BeginWindow(bAdvanced.getName());
		if (b) {
			//if (!bForceVisible)this->Add(bAdvanced, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);
			DrawAdvancedSubPanel(true, bForceVisible);
			EndWindow();
		}
	}

	//--------------------------------------------------------------
	void DrawAdvancedBundle(bool bSeparator = false, bool bSpacing = false, bool bListenToMinimize = false) { // Simpler call. Use this.

		if (bMinimize && bListenToMinimize) return;

		if (bSpacing) ImGui::Spacing();
		if (bSeparator) ImGui::Separator();
		ImGui::Spacing();

		this->Add(bAdvanced, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);

		DrawAdvancedSubPanel();
	}

private:

	// Legacy API
	//--------------------------------------------------------------
	void DrawAdvanced(bool bSeparator = false, bool bSpacing = false) {
		DrawAdvancedBundle(bSeparator, bSpacing);
	}

	//--

private:

	//--------------------------------------------------------------
	void DrawAdvancedSubPanel(bool bHeader = true, bool bForceVisible = false)
	{
		if (!bForceVisible) {
			if (!bAdvanced) return;
			if (!bUseAdvancedSubPanel) return;
		}

		//--

		this->Indent();
		{
			bool b = false;
			if (!bUseAdvancedSubPanel)
			{
				if (bHeader) b = ImGui::CollapsingHeader(params_Advanced.getName().c_str(), ImGuiTreeNodeFlags_None);
			}
			else b = true;

			// Keys
			this->Add(bKeys, OFX_IM_TOGGLE_ROUNDED);

			// Help App
			this->Add(bHelp, OFX_IM_TOGGLE_ROUNDED);
			//if (bUseHelpInfoApp) this->Add(bHelp, OFX_IM_TOGGLE_ROUNDED);
			//hide if it's not settled by the user from ofApp!

			// Help Internal
			this->Add(bHelpInternal, OFX_IM_TOGGLE_ROUNDED);

			// Menu
			Add(bMenu, OFX_IM_TOGGLE_ROUNDED);

			// Log
			Add(bLog, OFX_IM_TOGGLE_ROUNDED);

			// Main Reset
			// that can be linked using a pointer to an external trigger!
			// Example: ui.setReset(&bResetDocking);
			if (bResetPtr != nullptr)
			{
				Add(bReset, OFX_IM_BUTTON_SMALL);
				//this->AddTooltip("Must be assigned \nfrom parent scope \nby passing a bool \ntrigger as reference!");
			}

			if (ImGui::TreeNode("Windows"))
			{
				this->refreshLayout();

				//--

				// Window 

				/*
				if (ImGui::TreeNode("_"))
				{
					this->refreshLayout();
					Add(bAutoResize_PresetsWindows, OFX_IM_TOGGLE_ROUNDED_SMALL);
					Add(bReset_Window, OFX_IM_BUTTON_SMALL);
					if (bReset_Window) {
						bReset_Window = false;
						resetWindowImGui(false, true);
					}
					ImGui::TreePop();
				}
				*/

				//--

				// Window Layouts

				if (ImGui::TreeNode("LAYOUTS"))
				{
					this->refreshLayout();
					Add(bAutoResize_PresetsWindows, OFX_IM_TOGGLE_ROUNDED_SMALL);
					Add(bReset_PresetsWindow, OFX_IM_BUTTON_SMALL);

					ImGui::TreePop();
				}

				//--

				// Window Panels 

				if (ImGui::TreeNode("PANELS"))
				{
					this->refreshLayout();
					Add(bAutoResize_Panels, OFX_IM_TOGGLE_ROUNDED_SMALL);
					Add(bReset_WindowPanels, OFX_IM_BUTTON_SMALL);
					//if (bAutoResize_Panels) Add(bReset_WindowPanels, OFX_IM_BUTTON_SMALL);

					// Landscape
					//Add(bLandscape, OFX_IM_TOGGLE_ROUNDED);//TODO:

					ImGui::TreePop();
				}

				ImGui::TreePop();
			}

			this->refreshLayout();

			//--

			this->AddSpacingSeparated();

			// Extra
			Add(bExtra, OFX_IM_TOGGLE_ROUNDED);
			if (bExtra)
			{
				//--

				if (!bHeader || (bHeader && b))
				{
					// Windows
					this->AddSpacing();

					if (ImGui::TreeNode("MORE"))
					{
						this->Indent();

						this->AddSpacing();

						/*
						// Align Helpers
						Add(bGui_Aligners, OFX_IM_TOGGLE_ROUNDED);

						// Organizer Special Windows
						if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER) {
							Add(windowsOrganizer.bGui_Organizer, OFX_IM_TOGGLE_ROUNDED);
						}
						*/

						// Auto resize
						Add(bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);

						// MouseWheel
						this->Add(bMouseWheel, OFX_IM_TOGGLE_ROUNDED_MINI);
						this->Add(bMouseWheelFlip, OFX_IM_TOGGLE_ROUNDED_MINI);
						ofxImGuiSurfing::AddTooltip("Press CTRL+ for fine tunning");

						////TODO:
						//// Lock
						//Add(bLockMove, OFX_IM_TOGGLE_ROUNDED_MINI);

						//TODO:
						//// No Scroll
						//Add(bNoScroll, OFX_IM_TOGGLE_ROUNDED_MINI);

						this->Unindent();

						ImGui::TreePop();
					}

					this->AddSpacing();

					//--

					// Gui
					this->AddSpacing();

					if (ImGui::TreeNode("GUI"))
					{
						this->Indent();

						this->AddSpacing();

						//// Minimize
						//Add(bMinimize, OFX_IM_TOGGLE_ROUNDED_MEDIUM);

						//// Log
						//Add(bLog, OFX_IM_TOGGLE_ROUNDED_MEDIUM);

						//// Menu
						//Add(bMenu, OFX_IM_TOGGLE_ROUNDED_MEDIUM);

						//--

						// Debug
						Add(bDebug, OFX_IM_TOGGLE_ROUNDED);
						if (bDebug)
						{
							this->Indent();

							//--

							//drawSpecialWindowsPanel();
							//ImGui::Separator();

							Add(bDebugMetrics, OFX_IM_TOGGLE_ROUNDED_MINI);
							this->AddSpacing();
							Add(bInputText, OFX_IM_TOGGLE_ROUNDED_MINI);
							Add(bMouseOverGui, OFX_IM_TOGGLE_ROUNDED_MINI);

							//AddToggleRoundedButton(bDrawView1);

							//-

							this->AddSpacing();
							this->AddSpacing();

							if (ImGui::TreeNode("ELEMENTS"))
							{
								this->Indent();
								{
									this->AddSpacing();

									this->AddLabelBig("Widget", false, true);
									std::string _hwidget = "Unit Height:\n";
									_hwidget += ofToString(ofxImGuiSurfing::getWidgetsHeightUnit());
									ImGui::TextWrapped(_hwidget.c_str());

									std::string _wwidget = "Full Width:\n";
									_wwidget += ofToString(ofxImGuiSurfing::getWidgetsWidth(1));
									ImGui::TextWrapped(_wwidget.c_str());

									this->AddSpacing();
									this->AddLabelBig("Window", false, true);
									std::string _wpanel = "Inner Width:\n";
									_wpanel += ofToString(ofxImGuiSurfing::getPanelWidth());
									ImGui::TextWrapped(_wpanel.c_str());

									std::string _wShape = "Shape:\n";
									_wShape += ofToString(ImGui::GetWindowPos().x);
									_wShape += ", ";
									_wShape += ofToString(ImGui::GetWindowPos().y);
									_wShape += ", ";
									_wShape += ofToString(ImGui::GetWindowWidth());
									_wShape += ", ";
									_wShape += ofToString(ImGui::GetWindowHeight());
									ImGui::TextWrapped(_wShape.c_str());
									this->AddSpacing();
								}
								this->Unindent();

								ImGui::TreePop();
							}

							this->Unindent();
						}

						this->Unindent();

						ImGui::TreePop();
					}

					//--

					// Docking
					this->AddSpacing();

					if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING)
					{
						this->AddSpacing();

						if (ImGui::TreeNode("DOCKING"))
						{
							this->Indent();

							this->AddSpacing();

							//--

							//ImGui::Text("Docking");
							AddToggleRoundedButton(bDebugDocking);
							//TODO:
							if (bDebugDocking)
							{
								ImGui::Indent();
								{
									//AddToggleRoundedButton(bUseLayoutPresetsManager);
									//AddToggleRoundedButton(bDockingLayoutPresetsEngine);
									ToggleRoundedButton("Dock Center", &bDockingModeCentered);
									AddToggleRoundedButton(bDrawView1);
									AddToggleRoundedButton(bDrawView2);
								}
								ImGui::Unindent();
							}

							this->Unindent();

							ImGui::TreePop();
						}
					}
				}
			}
		}
		this->Unindent();
	}

public:

	//--------------------------------------------------------------
	void setUseAdvancedSubPanel(bool b) {
		bUseAdvancedSubPanel = b;
	}

	//----

private:

	ofParameter<bool> bAutoSaveSettings{ "Autosave", true };

private:

	// File Settings
	std::string path_Global;
	std::string path_ImLayouts;
	std::string path_AppSettings;
	std::string path_LayoutSettings;

	std::string nameLabel = "SurfingGui";

	ofParameterGroup params_AppSettings{ "ofxSurfingGui" }; // Features states
	ofParameterGroup params_AppSettingsLayout{ "LayoutSettings" }; // Layout states

	//----

public:

	// Some tweaked settings modes

	// API
	//--------------------------------------------------------------
	void setName(std::string name)
	{
		// Must call before setup! 
		// To allow the correct behavior when multiple instances/windows settings. 
		// Notice that each instance will have his own folder path for setting files! 
		// This name will be used on the folder name too.
		nameLabel = name;
		windowsOrganizer.setName(nameLabel);

		// split possible instances on different folders
		path_Global = nameLabel + "/Gui/";
		ofxSurfingHelpers::CheckFolder(path_Global);
		// Useful toggles for internal Windows

		windowsOrganizer.setPathGlobal(path_Global);

		//--

		// too long names..
		/*
		// Customize common windows duplicated on when using multiple instances.
		// that's to avoid overlapping contents when ImGui windows have the same name!
		bGui_Aligners.setName(nameLabel + " ALIGNERS");
		bGui_Organizer.setName(nameLabel + " ORGANIZER");
		bGui_SpecialWindows.setName(nameLabel + " SPECIALW");
		*/
		// use first letter only
		bGui_Aligners.setName("ALIGNERS " + ofToString(nameLabel[0]));
		bGui_Organizer.setName("ORGANIZER " + ofToString(nameLabel[0]));
		bGui_SpecialWindows.setName("SPECIALW " + ofToString(nameLabel[0]));

		//--

		// Aligners toggle
		windowsOrganizer.bGui_Aligners.makeReferenceTo(bGui_Aligners);

		// Link Organizer toggle
		windowsOrganizer.bGui_Organizer.makeReferenceTo(bGui_Organizer);

		// Special Windows toggle
		windowsOrganizer.bGui_SpecialWindows.makeReferenceTo(bGui_SpecialWindows);

		// Link both link toggles, local and the one inside the organizer object
		windowsOrganizer.bLinked.makeReferenceTo(bLinked);

	}

	//--------------------------------------------------------------
	void setMouseWheelFlip(bool bFlip = true)
	{
		bMouseWheelFlip = bFlip;
	}

	//--

private:

	// Hide to simplify

	////--------------------------------------------------------------
	//void setSettingsFilename(std::string path) { // must call before setup. To allow multiple instances/windows settings
	//	nameLabel = path + "_";
	//}

	//////--------------------------------------------------------------
	////void setSettingsPathLabel(std::string path) { // must call before setup. To allow multiple instances/windows settings
	////	nameLabel = "_" + path;
	////}

	//--------------------------------------------------------------
	void setAutoSaveSettings(bool b) { // must call before setup. IMPORTANT: if you are using multiple instances of this add-on, must set only one to true or settings will not be handled correctly!
		bAutoSaveSettings = b;
	}


	//--------------------------------------------------------------
	void setAutoResize(bool b) { // must call before setup
		bAutoResize = b;
	}

	//--------------------------------------------------------------
	void setDocking(bool b) { // must call before setup
		bDockingLayoutPresetsEngine = b;
	}

	//---------------------------

	// Special Windows Engine

	//private:

	//TODO:
	// 
	// That simplifies the API a bit..
	// When calling EndWindowSpecial,
	// there's no need to pass what window/toggle/name is.
	// Thats bc memorizes last index called on previous BeginWindowSpecial.
	// That must coincided if API is well used!
	//  
	// Should remove. deprecated
	// To simplify a bit more the API workflow.
	// Allows to omit the index argument on begin a window...
	int _indexLastBegin = -1;

	//TODO:
	//std::string nameWindowSpecialsPanel = "";

	//--

public:

	// Main Important 
	// API methods to populate widgets in between,
	// inside previously queued Special Windows!
	// to be called on DrawImGui()

	// Begin

	bool BeginWindowSpecial(int index);
	// If you added windows to the engine you can begin the window passing his index

	bool BeginWindowSpecial(string name);
	// If you added windows to the engine you can begin the window passing his SAME name.

	bool BeginWindowSpecial(ofParameter<bool>& _bGui);

	//-

	// End

	// Notice that when you don't pass an argument or -1, 
	// it will use the last BeginWindowSpecial index!
	// Use it with care!
	void EndWindowSpecial(int index);
	//--------------------------------------------------------------
	void EndWindowSpecial() {
		EndWindowSpecial(-1);
	};

	// Notice that preferred usage is 
	// by passing the bool toggle or the window name, 
	// not only like when opening/BeginWindowSpecial, 
	// but also when closing/EndWindowSpecial too!
	void EndWindowSpecial(ofParameter<bool>& _bGui);

	//--

	// Rarely useful Helpers but internal too.
//private:
public:
	int getWindowSpecialIndexForToggle(ofParameter<bool>& _bGui);
	// to get the index of an special window passing the toggle

	int getWindowSpecialIndexForName(string name);
	// to be used if you forgot or don't know the index

	// Check if that param toggle is previously added as an special window
	// that's useful when using passed as reference ui's
	// when using multiple ui instances sharing the same object instance!
	//--------------------------------------------------------------
	bool isThereSpecialWindowFor(ofParameter<bool>& _bGui) {
		bool b = this->getWindowSpecialIndexForName(_bGui.getName()) != -1;
		return b;
	}

	//----

	// Organizer for the Special Windows

public:

	//--------------------------------------------------------------
	void drawWindowOrganizer() // Draws the main panel controller.
	{
		if (bGui_Organizer) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;

		if (BeginWindow(bGui_Organizer))
		{
			Add(bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED);
			AddSpacing();

			windowsOrganizer.drawWidgetsOrganizer(bMinimize);

			EndWindow();
		}
	}

	//--------------------------------------------------------------
	void setWindowsSpecialsOrientation(bool b) { // Set orientation of window special alignment! horz/vert
		windowsOrganizer.bOrientation = b;
	}

	//--------------------------------------------------------------
	void drawWindowAlignHelpers()
	{
		if (bGui_Aligners) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;

		if (BeginWindow(bGui_Aligners))
		{
			Add(bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED);
			AddSpacing();

			windowsOrganizer.drawWidgetsAlignHelpers(bMinimize);

			if (!bMinimize) {
				AddSpacing();
				ofxImGuiSurfing::AddStepperInt(windowsOrganizer.pad);
			}

			EndWindow();
		}
	}

	//TODO: deprecated
	////--------------------------------------------------------------
	//bool getGuiToggleGlobal() {
	//	return windowsOrganizer.bGui_Global.get();
	//}
	//--------------------------------------------------------------
	bool getGuiToggleGlobalState() const {
		return windowsOrganizer.bGui_Global.get();
	}

	//--

	//TODO: WIP
	//--------------------------------------------------------------
	struct SurfingImWindow
	{
		// We queue here the bool params 
		// that enables the show/hide for each queued window
		ofParameter<bool> bGui{ "_bGui", true };

		ofParameter<bool> bAutoResize{ "Auto Resize", true };

		////TODO: could be removed...not used yet..
		//ofParameter<bool> bExtra{ "Extra", false };
		//ofParameter<bool> bMinimize{ "Minimize", false };
		//ofParameter<bool> bAdvanced{ "Advanced", false };
		//ofParameter<bool> bDebug{ "Debug", false };
		//ofParameter<bool> bReset_Window{ "Reset Window", false };

		//TODO:
		// Only one special window can be flagged as master anchor,
		// then will be force to be the first window always!
		ofParameter<bool> bMasterAnchor{ "MasterAnchor", false };

		//--------------------------------------------------------------
		void setMasterAnchor(bool b) {
			bMasterAnchor = b;
		}

		//ofParameter<ofRectangle> rectShapeWindow{ "_WindowSpahe", ofRectangle(), ofRectangle(), ofRectangle() };
	};

	vector<SurfingImWindow> windows;
	// Handles only the manually pre added special windows.

	//----

	// Windows Special Engine

//private:
public:

	WindowsOrganizer windowsOrganizer;

public:

	int getPad() { return windowsOrganizer.pad; }//used pad between windows

	//public:
	//
	//	//TODO: deprecated
	//	//--------------------------------------------------------------
	//	void setNameWindowsSpecialsEnableGlobal(std::string name) {
	//		windowsOrganizer.setNameWindowsSpecialsEnableGlobal(name);
	//	}

		////--------------------------------------------------------------
		//void setName(std::string name) {
		//	windowsOrganizer.setName(name);
		//}

public:

	//--------------------------------------------------------------
	void clearSpecialWindows() {
		windows.clear();
	}

	//--------------------------------------------------------------
	SurfingGuiModeWindows getModeSpecial() const
	{
		return specialsWindowsMode;
	}

	//--------------------------------------------------------------
	void addWindowSpecial(ofParameter<bool>& _bGui, bool _bAutoResize = true, bool _bMaster = false) {

		SurfingImWindow win;
		win.bGui.makeReferenceTo(_bGui);
		win.bAutoResize = _bAutoResize;
		win.setMasterAnchor(_bMaster);//TODO:

		// Queue Window
		windows.push_back(win);

		// Queue Toggle. only for callbacks ?
		params_bGuiToggles.add(_bGui);

		// Queue Toggle
		if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		{
			windowsOrganizer.add(_bGui);
		}
	}

	//--------------------------------------------------------------
	void addWindowSpecial(std::string name, bool _bAutoResize = true, bool _bPowered = false) {

		// Security Checks

		// Special windows mode
		if (specialsWindowsMode != IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER) {
			ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) << ("Special Windows mode was not initiated.");
			ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) << ("Force Special Windows mode to allow add special Windows!");

			this->setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
		}

		// Also to simplify a bit the API.
		if (!bDoneSetup) {

			ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) << ("Setup was not previously done!");
			ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) << ("Force run SurfingGuiManager::setup() now!");

			setup();
		}

		ofParameter<bool> _bGui{ name, true };

		SurfingImWindow win;
		win.bGui.makeReferenceTo(_bGui);
		win.bAutoResize = _bAutoResize;
		win.setMasterAnchor(_bPowered);

		// Queue

		windows.push_back(win);
		params_bGuiToggles.add(_bGui);

		bWindowSpecials.push_back(_bGui);

		if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		{
			windowsOrganizer.add(_bGui);
		}
	}

	//--------------------------------------------------------------
	std::string getWindowSpecialName(int index) {
		if (index > windows.size() - 1 || index == -1)
		{
			ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n" << "Out of range index for queued windows, " << index;

			return "-1";
		}

		return windows[index].bGui.getName();
	}

	////--------------------------------------------------------------
	//ofRectangle getRectangleWindowSpecial(int index) {
	//	if (index > windows.size() - 1 || index == -1)
	//	{
	//		ofLogError("ofxSurfingImGui") <<(__FUNCTION__) << "Out of range index for queued windows, " << index;
	//	}
	//	return windows[index].rectShapeWindow;
	//}

	////--------------------------------------------------------------
	//void addWindow(std::string name, bool bPowered = false) { // legacy API
	//	addWindowSpecial(name, bPowered);
	//}

	//--------------------------------------------------------------
	void initiateWindowsOrganizer()
	{
		//windowsOrganizer.setPathGlobal(path_Global);
		windowsOrganizer.setupInitiate();
	}

	//--

private:

	// removed. Exposed helpers to external GUIs / scope.

	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleGlobal() { // global toggle to show/hide the all panels
		return windowsOrganizer.bGui_Global;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleLinked() { // toggle to enable or disable
		return windowsOrganizer.bLinked;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleOrganizer() {
		return bGui_Organizer;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleAligner() {
		return bGui_Aligners;
	}

	//----

public:

	// Helpers to position ImGui windows 
	// on the main ImGui viewport / canvas:

	// Call to auto place to queue. to the right of the last window populated on the viewport!
	// Could be weird bc some window can could be populated from other scopes...
	// This is improved using the Special Windows Engine!
	//--------------------------------------------------------------
	ImVec2 getTopRightWindowLast()
	{
		ImVec2 posTopRight{ 0, 0 };

		ImGuiContext* g = ImGui::GetCurrentContext();
		ImVector<ImGuiWindow*> windows;

		for (ImGuiWindow* window : g->WindowsFocusOrder)
		{
			if (window->WasActive)
			{
				ImVec2 base_pos = ImGui::GetMainViewport()->Pos;
				ImVec2 wTopRight = base_pos + window->Pos + ImVec2(window->Size.x, 0);

				if (posTopRight.x < wTopRight.x)
				{
					posTopRight = ImVec2(wTopRight.x, wTopRight.y);
				}
			}
		}

		return posTopRight;
	}

	// Set next window position after last window. 
	// Notice that could be chaotic bc don't know from which add-on is each ImGui populated window.
	//--------------------------------------------------------------
	void setNextWindowOnViewport(ImGuiCond cond = ImGuiCond_Appearing) {

		// can't be settled to ImGuiCond_Always bc will feedback/apply with the same window!
		ImGui::SetNextWindowPos(getTopRightWindowLast(), cond);
	}

	// Set next window position after the window named as the passed named and with the layout type distribution.
	// layoutType=0 : top right 
	// layoutType=1 : bottom left
	// layoutType=2 : top left //TODO: BUG
	// layoutType=3 : top up //TODO:
	//--------------------------------------------------------------
	void setNextWindowAfterWindowNamed(string nameAnchorWindow /*= "-1"*/, int layoutType = 0, ImGuiCond cond = ImGuiCond_Always)
	{
		//// Default for unnamed is queued after last window on screen..
		//if (nameAnchorWindow == "-1") {
		//	setNextWindowOnViewport();
		//	return;
		//}

		// ImGuiCond_Always is for forced linking!

		ImVec2 p;
		ImGuiContext* GImGui = ImGui::GetCurrentContext();
		ImGuiContext& g = *GImGui;
		bool bready = false;
		int _pad = windowsOrganizer.pad;

		for (ImGuiWindow* window : g.WindowsFocusOrder)
		{
			if (window->WasActive && window->Name == nameAnchorWindow)
			{
				// To the top right
				if (layoutType == 0)
				{
					p = window->Pos + ImVec2(window->Size.x + _pad, 0);
					bready = true;
				}

				// To the bottom left
				else if (layoutType == 1)
				{
					p = window->Pos + ImVec2(0, window->Size.y);
					bready = true;
				}

				//TODO: BUG: 
				// we don't know the width of next window...
				// To the top left 
				else if (layoutType == 2)
				{
					p = window->Pos + ImVec2(window->Size.x - _pad - window->Size.x, 0);
					bready = true;
				}

				//// Top up
				//else if (layoutType == 3) {
				//	p = window->Pos + ImVec2(0, 0 - _pad - window->Size.y);
				//	bready = true;
				//}

				break;
			}
		}

		if (bready) ImGui::SetNextWindowPos(ImVec2(p.x, p.y), cond);

		return;
	}

	//--------------------------------------------------------------
	void setNextWindowAfterWindowNamed(ofParameter<bool>& bGui) {//passed anchor bGui / visible toggle 
		//if (!bGui.get()) return;
		setNextWindowAfterWindowNamed(bGui.getName());
	}

	//--

	//TODO:
	// Set anchor first window from a parent scope:
	// That feature allows to link grouped windows from many contexts / add-ons.

	// Get the name of the last special window (the window at the end of current drawn queue)
	//--------------------------------------------------------------
	string getWindowSpecialLast() const {
		return windowsOrganizer.getWindowSpecialLast();
	}

	// Get the position of the last special window (the window at the end of current drawn queue)
	//--------------------------------------------------------------
	glm::vec2 getWindowSpecialLastTopRight() const {

		return windowsOrganizer.getWindowSpecialLastTopRight();
	}

	//-

	// Get anchor from first window taken from the parent scope
	//--------------------------------------------------------------
	glm::vec2 getWindowSpecialLastTopLeft() const {

		return windowsOrganizer.getWindowSpecialLastTopLeft();
	}

	// Set the anchor position from the parent scope
	//--------------------------------------------------------------
	void setWindowSpecialFirstPosition(glm::vec2 pos) {
		windowsOrganizer.setWindowSpecialFirstPosition(pos);
	}

	//--

	//// Orientation cascade windows
	////--------------------------------------------------------------
	//void setSpecialWindowsOrganizerOrientationHorizontal() {
	//	windowsOrganizer.bOrientation.set(false);
	//}

	////--------------------------------------------------------------
	//void setSpecialWindowsOrganizerOrientationVertical() {
	//	windowsOrganizer.bOrientation.set(true);
	//}

	////--------------------------------------------------------------
	//void setToggleSpecialWindowsOrganizerOrientation() {
	//	windowsOrganizer.bOrientation.set(!windowsOrganizer.bOrientation.get());
	//}

	//--	

	//--------------------------------------------------------------
	inline ofRectangle getWindowShape()
	{
		return ofxImGuiSurfing::getWindowShape();
	}

	//--	

	//--------------------------------------------------------------
	float getWidgetsWidth(int amnt = 1) {
		return ofxImGuiSurfing::getWidgetsWidth(amnt);
	}

	//--------------------------------------------------------------
	float getWidgetsHeight() {
		return ofxImGuiSurfing::getWidgetsHeight();
	}

	// Legacy
	//--------------------------------------------------------------
	float getWidgetsHeightUnit() {
		return ofxImGuiSurfing::getWidgetsHeightUnit();
	}

	//--------------------------------------------------------------
	float getWidgetsSpacingX() {
		return ImGui::GetStyle().ItemSpacing.x;
	}
	//--------------------------------------------------------------
	float getWidgetsSpacingY() {
		return ImGui::GetStyle().ItemSpacing.y;
	}

	// Legacy API
	//--------------------------------------------------------------
	void refreshWidgetsSizes(float& _w100, float& _w50, float& _w33, float& _w25, float& _h) {
		ofxImGuiSurfing::refreshImGui_WidgetsSizes(_w100, _w50, _w33, _w25, _h);
	}

public:

	//----

	// Layouts Engine

	// Extra Params to include packed into layout presets too.
	// By default we wil have menu and log toggles,
	// but we can add more from our ofApp

	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameterGroup& group) {
		params_LayoutsExtra.add(group);
	}
	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameter<bool>& param) {
		params_LayoutsExtra.add(param);
	}
	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameter<int>& param) {
		params_LayoutsExtra.add(param);
	}
	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameter<float>& param) {
		params_LayoutsExtra.add(param);
	}
	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameter<ofRectangle>& param) {
		params_LayoutsExtra.add(param);
	}

	//--

	//--------------------------------------------------------------
	int getWindowSpecialPadSize() const
	{
		int pad = windowsOrganizer.pad;
		//glm::vec2 p(pad, pad);
		return pad;
	}

	//----

	// Getter for the internal show GUI toggles for each queued special Windows!
	// Both does the same! Just to beauty method name...
	//--------------------------------------------------------------
	ofParameter<bool>& getWindowSpecialGuiToggle(int index)
	{
		return getWindowSpecialVisible(index);
	}

	//--------------------------------------------------------------
	bool getWindowSpecialVisibleState(int index) const // return visible toggle state
	{
		if (windows.size() == 0) return false;
		else if (index > windows.size() - 1 || index == -1) return false;
		else return windows[index].bGui.get();
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getWindowSpecialVisible(int index) // return bool parameter visible toggle
	{
		if (index > windows.size() - 1 || index == -1)
		{
			ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n" << "Out of range index for queued windows, " << index;
			ofParameter<bool> b = ofParameter<bool>{ "-1", false };
			return b;
		}

		return windows[index].bGui;
	}

	// Easy populate all the Special Windows toggles. Call inside a window.
	//--------------------------------------------------------------
	void drawWidgetsSpecialWindowsToggles(SurfingGuiTypes style = OFX_IM_TOGGLE_ROUNDED) {
		for (size_t i = 0; i < windows.size(); i++)
		{
			this->Add(getWindowSpecialGuiToggle(i), style);
		}
	}

	// Creates a Helper Window 
	// with auto populated all the Special Windows toggles. 
	// To be called outside a window, just between the main begin/end!
	//--------------------------------------------------------------
	void drawWidgetsSpecialWindows()
	{
		float _h = getWidgetsHeight();
		float _w1 = getWidgetsWidth(1);
		float _w2 = getWidgetsWidth(2);

		if (ImGui::Button("All", ImVec2(_w2, _h)))
		{
			for (auto& p : windowsOrganizer.windowsPanels) {
				p.bGui = true;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("None", ImVec2(_w2, _h)))
		{
			for (auto& p : windowsOrganizer.windowsPanels) {
				p.bGui = false;
			}
		}

		// Show Global
		this->Add(windowsOrganizer.bGui_Global, OFX_IM_TOGGLE_ROUNDED);

		// All toggles
		if (windowsOrganizer.bGui_Global)
		{
			ImGui::Indent();
			drawWidgetsSpecialWindowsToggles(OFX_IM_TOGGLE_ROUNDED_SMALL);
			ImGui::Unindent();
		}

		//// Special Windows Organizer toggle 
		//this->AddSpacingSeparated();
		//this->Add(bGui_Organizer, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
	}

	//--------------------------------------------------------------
	void drawWindowSpecialWindows()
	{
		if (BeginWindow(bGui_SpecialWindows))
		{
			this->AddLabelBig("Special \nWindows", false);
			ImGui::Spacing();

			drawWidgetsSpecialWindows();

			this->EndWindow();
		}
	}

	//--------------------------------------------------------------
	void setWindowSpecialToggleVisibleAllGlobal()
	{
		windowsOrganizer.bGui_Global = !windowsOrganizer.bGui_Global;
	}

	//--------------------------------------------------------------
	void setWindowSpecialToggleVisible(int index)
	{
		if (index > windows.size() - 1 || index == -1)
		{
			ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n" << "Out of range index for queued windows, " << index;

			return;
		}

		windows[index].bGui = !windows[index].bGui;
	}

	//----

private:

	// We store many internal stuff like: minimize, advanced, extra, debug states...etc.	
	// Will return false if settings file do not exist.
	// That happens when started for first time or after OF_APP/bin cleaning
	// Then we can reset to some default variables and layout positions of our windows.

	bool loadAppSettings();
	void saveAppSettings();

	//----

	////TODO: WIP
	//// To be marked outside the scope to populate widgets inside this execution point... ?
	//// Should use lambda functions here!
	////TODO: learn lambda functions..
	//void beginExtra();
	//void endExtra();

	//void beginAdvanced();
	//void endAdvanced();

	//void beginMenu();
	//void endMenu();

	//----

	// Docking Helpers

public:

	void BeginDocking();
	void EndDocking();

	//----

	// Docking Layout Engine for Layout Presets Engine

	// ImGui layouts engine
	// on each layout preset we store:
	// 1. some parameters states
	// 2. ImGui ini positions

private:

	void drawLayoutsManager();

	const char* ini_to_load = NULL;
	const char* ini_to_save = NULL;
	std::string ini_to_load_Str;
	std::string ini_to_save_Str;

	void loadAppLayout(int mode);
	void saveAppLayout(int mode);

	void saveLayoutPreset(std::string path); //-> both group params and ImGui ini files
	void loadLayoutPreset(std::string path);

	void saveLayoutImGuiIni(std::string path);
	void loadLayoutImGuiIni(std::string path);
	void saveLayoutPresetGroup(std::string path);
	void loadLayoutPresetGroup(std::string path);

	ofParameter<int> appLayoutIndex{ "Layout Preset", -1, -1, 0 };
	// index for the selected preset. -1 is none selected, useful too.
	int appLayoutIndex_PRE = -1;

	ofParameterGroup params_Layouts{ "LayoutsPresets" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsVisible{ "PanelsVisible" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsExtra{ "Extra Params" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsExtraInternal{ "Internal" }; // add-on related params

	int numPresetsDefault;
	void createLayoutPreset(std::string namePreset = "-1");

	//-

	vector<ofParameter<bool>> bLayoutPresets{ "bLayoutPresets" }; // each window show toggles
	void Changed_Params(ofAbstractParameter& e);
	ofParameterGroup params_LayoutsPanel{ "Layouts Panel" };

	//void Changed_Enablers(ofAbstractParameter& e);

	//--------------------------------------------------------------
	std::string getLayoutName(int mode) {
		std::string s = "";

		if (mode > bLayoutPresets.size() - 1) return "-1";

		s = bLayoutPresets[mode].getName();
		//s += ".ini";
		std::string _path = s;
		return _path;
	}

	//----

public:

	// We can customize the default preset names
	// that are P1-P2-P3-P4 by default.

	//--------------------------------------------------------------
	void setPresetsNames(vector <std::string > names) {
		if (names.size() != 4) {
			ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n" << "Names sizes are not equals to 4";
		}

		namesPresets.clear();
		namesPresets = names;
	}

private:

	vector <std::string> namesPresets;

public:

	//-> Must call manually after adding windows and layout presets
	void setupLayout(int numPresets = DEFAULT_AMOUNT_PRESETS);

	//--------------------------------------------------------------
	void startup();

	//-

private:

	bool bDoneStartup = false;
	bool bDoneSetup = false;

	//public:

	void startupFirstFrame();
	void setupDocking();//TODO: rename as presets + docking...

	//--------------------------------------------------------------
	void setImGuiLayoutPresets(bool b) {
		bUseLayoutPresetsManager = b;
	}

	//--

public:

	void drawMenu();
	void drawMenuDocked();

public:

	// Get the central space to position other panels or gui elements
	// like video viewports or scenes previews
	//--------------------------------------------------------------
	ofRectangle getRectangleCentralDocking() {
		return rectangle_Central_MAX;
		//return rectangle_Central;
	}

	//--

private:

	void updateLayout();

	void drawLayoutsPresetsEngine();//all the windows of the engine
	void drawLayoutsPresetsManualWidgets();
	void drawLayoutsLayoutPresets();
	void drawLayoutsPanels();
	void drawLayoutPresetsEngine();
	void drawViewport_oFNative();


	//// For different behavior. We can disable to save some windows positions to allow them locked when changing presets.
	//ofParameter<bool> bModeFree{ "Free", true }; // A allows storing position for control windows too
	//ofParameter<bool> bModeForced{ "Forced", false }; // Locked to free space on viewport
	//ofParameter<bool> bModeLock1{ "Lock B", false }; // Cant be moved. To be used in presets panel
	//ofParameter<bool> bModeLockControls{ "Lock C", false }; // Cant be moved. To be used to lock to free viewport scenarios
	//ofParameter<bool> bModeLockPreset{ "Lock A", false }; // Cant be moved. To be used to lock to free viewport scenarios

	//TODO: 
	// It's a problem if .ini files are already present... We must ingore loading.

	ofParameter<bool> bDebugDocking{ "Debug Docking", false };

	ofParameter<bool> bDrawView2{ "Draw View 2", false };

	ofRectangle rectangle_Central_MAX;
	ofRectangle rectangle_Central; // current free space viewport updated when changes
	ofRectangle rectangle_Central_Transposed;

	//-

	// Customize Titles

public:

	//--------------------------------------------------------------
	void setLabelLayoutPanels(std::string label) { // Customize the app name for panels window label tittle
		bGui_LayoutsPanels.setName(label);
	}
	//--------------------------------------------------------------
	void setLabelLayoutMainWindow(std::string label) {
		bGui_LayoutsManager.setName(label);
	}

	//-

public:

	ofParameter<bool> bMenu{ "Menu", false };

	ofParameter <bool> bLinked{ "Link Windows", true };//align windows engine. liked to the internal aligner.

private:

	ofParameter<bool> bGui_LayoutsPanels{ "PANELS", true };
	ofParameter<bool> bGui_LayoutsPresetsSelector{ "LAYOUTS", true };
	ofParameter<bool> bGui_LayoutsManager{ "MANAGER", false };

	ofParameter<bool> bAutoSave_Layout{ "Auto Save", true };
	ofParameter<bool> bUseLayoutPresetsManager{ "Layout Engine", false };
	// Can't be changed on runtime. cant include into settings

	ofParameter<bool> bDockingLayoutPresetsEngine{ "Dock Engine", false };

	ofParameter<bool> bSolo{ "Solo", false };

public:

	ofParameter<bool> bLog{ "LOG", false };//show log window

	//-

private:

	ofParameterGroup params_LayoutPresetsStates{ "LayoutPanels" };

	ofParameterGroup params_bGuiToggles{ "_GuiToggles_" };
	//TODO:
	// To store the gui show toggles for each added special window. ?
	// Only for callbacks!

	//TODO:
	vector<ofParameter<bool>> bWindowSpecials;

	//TODO:
	//ImGuiWindowFlags flagsWindowsLocked1;//used for presets panel
	//ImGuiWindowFlags flagsWindowsLocked2;//used for other control panels
	//ImGuiWindowFlags flagsWindowsModeFreeStore;//used to unlink main control panels (presets, manager, extra, panels) from presets

	//-

	//TODO: 
	// Learn to use lambda functions
	// To callback reset
	// Subscribe an optional reset flagging a bool to true to reset. Uses the gui Reset button on the Presets Extra panel.

private:

	bool* bResetPtr = nullptr;

public:

	//--------------------------------------------------------------
	void setReset(bool* b) {//link to an external / parent scope bool to assing to the internal reset button.
		bResetPtr = b;
	}

	//--------------------------------------------------------------
	void setShowAllWindows(bool b) {//show main internal windows and panels too
		setShowAllPanels(b);

		//bModeLockControls = b;
		bMenu = b;

		bGui_LayoutsPanels = b;
		bGui_LayoutsPresetsSelector = b;
		//bGui_LayoutsPresetsManual = false;
	}

	//--------------------------------------------------------------
	void setShowAllPanels(bool b) {
		for (int i = 0; i < windows.size(); i++)
		{
			windows[i].bGui.set(b);
		}
	}

	//--------------------------------------------------------------
	void doRemoveDataFiles() {

		// Remove all the settings folder
		const filesystem::path path = path_Global;
		ofDirectory::removeDirectory(path, true, true);

		// Remove imgui.ini file
		const filesystem::path file = ofToDataPath("../imgui.ini");
		ofFile::removeFile(file, true);
	}

	//--------------------------------------------------------------
	void doSpecialWindowToggleVisible(int index) {
		if (index >= windows.size()) return;//ignore
		windows[index].bGui = !windows[index].bGui;
	}

	//--

private:

	// We have to independent help boxes.
	// One is intended to be use as the add-on itself help (Internal Help),
	// and another to be used as an external help (App Help).
	// Can be initialized from outer scope.

	// Help Internal: How to use the add-on itself
	std::string helpInfo = "";
	TextBoxWidget boxHelpInternal;

	// Help App: How to use our App 
	std::string helpInfoApp = "";
	TextBoxWidget boxHelpApp;

	// main help disablers
	bool bUseHelpInfoInternal = false;
	bool bUseHelpInfoApp = false;

	//--

public:

	//--------------------------------------------------------------
	void setEnableHelpInfoInternal(bool b) {
		bUseHelpInfoInternal = b;
	}

	//--------------------------------------------------------------
	void setEnableHelpInfoApp(bool b) {
		bUseHelpInfoApp = b;
	}

	//--------------------------------------------------------------
	void setHelpInfoApp(string text) {
		helpInfoApp = text;
		boxHelpApp.setText(helpInfoApp);
		bUseHelpInfoApp = true;
	}

	//--------------------------------------------------------------
	void setHelpInfoInternal(string text) {
		helpInfo = text;
		boxHelpInternal.setText(helpInfo);
		bUseHelpInfoInternal = true;
	}
	// Useful in some rare scenarios to populate or hide the enabler toggle
	bool isHelpInternalEnable() { return bUseHelpInfoInternal; }
	bool isHelpAppEnable() { return bUseHelpInfoInternal; }


	//----

	// NOTES

	// Optional to customize filename for the settings file for multiple instances on the same ofApp.
	//ui.setSettingsFilename("3_DockingLayoutPresetsEngine"); 

	//----


public:

	// Helpers to populate non ofParams,
	// Raw CPP types instead an maintain global styles.
	// To speed up populate widgets without requiring to create ofParameters first.

	//--------------------------------------------------------------
	bool AddButton(string label, ImVec2 sz)
	{
		bool bReturn = false;

		float _ww = sz.x;
		float _h = sz.y;

		bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h);

		return bReturn;
	}

	//--------------------------------------------------------------
	bool AddButton(string label, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		bool bReturn = false;

		// widget width
		// we get the sizes from the canvas layout!
		float _ww = widgetsManager.getWidgetWidthOnRowPerAmount(amtPerRow);
		float _h = getWidgetsHeightUnit();

		switch (type)
		{

		case OFX_IM_DEFAULT:
		case OFX_IM_BUTTON_SMALL:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.25f);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.5f);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 2);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 3);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 4);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

			//--

			// Adding more styles

			// Border 

		case OFX_IM_BUTTON_SMALL_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.25f);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.5f);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 2);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 3);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 4);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

			//--

			// Border Blink

		case OFX_IM_BUTTON_SMALL_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h/*, true, true*/);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.25f);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.5f);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 2);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 3);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 4);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		default: {
			ofLogWarning(__FUNCTION__) << "Could not create passed style for that widget button!";
			ofLogWarning(__FUNCTION__) << "Widget is ignored and not drawn!";
			break;
		}
		}

		//----

		// Extra options
		// - Same line flag.
		// - Final y spacing.

		if (bSameLine) ImGui::SameLine();
		if (spacing != -1 && spacing != 0)
		{
			ImGui::Dummy(ImVec2(0.0f, (float)spacing)); // spacing
		}

		return bReturn;
	}

	//--

	// Toggle

	// Helpers to populate non ofParams,
	// Raw CPP types instead an maintain global styles.
	// To speed up populate widgets without requiring to create ofParameters first.
	// A toggle passing a name and a boolean to show and get the boolean state.
	//--------------------------------------------------------------
	bool AddToggle(string label, bool& bState, ImVec2 sz)
	{
		bool bReturn = false;

		float _ww = sz.x;
		float _h = sz.y;

		bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h);
		if (bMouseWheel) ofxImGuiSurfing::AddMouseWheel(bState);

		return bReturn;
	}

	////--------------------------------------------------------------
	//bool AddToggle(string label, bool& bState)
	//{
	//	int w = ofxImGuiSurfing::getWidgetsWidth(1);
	//	int h = ofxImGuiSurfing::getWidgetsHeightUnit();
	//	ImVec2 sz(w, h);
	//	bool bReturn = false;
	//	float _ww = sz.x;
	//	float _h = sz.y;
	//	bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h);
	//	return bReturn;
	//}

	//--------------------------------------------------------------
	bool AddToggle(string label, bool& bState, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		bool bReturn = false;

		// Widget width
		// We get the sizes from the canvas layout!
		float _ww = widgetsManager.getWidgetWidthOnRowPerAmount(amtPerRow);
		float _h = getWidgetsHeightUnit();

		switch (type)
		{

		case OFX_IM_DEFAULT:
		case OFX_IM_BUTTON_SMALL:
		case OFX_IM_TOGGLE_SMALL:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON:
		case OFX_IM_TOGGLE:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 1.25f);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM:
		case OFX_IM_TOGGLE_MEDIUM:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 1.5f);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG:
		case OFX_IM_TOGGLE_BIG:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 2);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL:
		case OFX_IM_TOGGLE_BIG_XXL:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 3);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL:
		case OFX_IM_TOGGLE_BIG_XXXL:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 4);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

			//--

			// Rounded Toggles

		case OFX_IM_TOGGLE_ROUNDED_MINI:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI://Legacy
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState, ImVec2(1.15f * _h, 1.15f * (2 / 3.f) * _h));
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_TOGGLE_ROUNDED_SMALL:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL://Legacy
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState, ImVec2(1.35f * _h, 1.35f * (2 / 3.f) * _h));
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_TOGGLE_ROUNDED:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED://Legacy
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_TOGGLE_ROUNDED_MEDIUM:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM://Legacy
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState, ImVec2(2 * _h, 2 * (2 / 3.f) * _h));
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_TOGGLE_ROUNDED_BIG:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG://Legacy
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState, ImVec2(2.5f * _h, 2.5f * (2 / 3.f) * _h));
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

			//--

		default:
			ofLogWarning("ofxSurfingImGui") << (__FUNCTION__);
			ofLogWarning("ofxSurfingImGui") << "Could not create passed style for that Toggle widget!";
			break;

		}

		//----

		// Extra options
		// - Same line flag.
		// - Final y spacing.

		if (bSameLine) ImGui::SameLine();
		if (spacing != -1 && spacing != 0)
		{
			ImGui::Dummy(ImVec2(0.0f, (float)spacing)); // spacing
		}

		return bReturn;
	}

	//--------------------------------------------------------------
	void SameLine() { ImGui::SameLine(); };
};



/*
SNAP ENGINE
auto snap = [=](float value, float snap_threshold) -> float {
	float modulo = std::fmodf(value, snap_threshold);
	float moduloRatio = std::fabsf(modulo) / snap_threshold;
	if (moduloRatio < 0.5f)
		value -= modulo;
	else if (moduloRatio > (1.f - 0.5f))
		value = value - modulo + snap_threshold * ((value < 0.f) ? -1.f : 1.f);
	return value;
};

if (ui.BeginWindowSpecial(bGui_Main))
{
	//ImGui::Begin(name.data());
	if (ImGui::IsItemActive()) {
		auto p = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();

		float x = snap(p.x, 16.f);
		float y = snap(p.y, 16.f);
		float sizex = snap(size.x, 16.f);
		float sizey = snap(size.y, 16.f);
		ImGui::SetWindowPos(ImFloor(ImVec2(x, y)));
	}
*/