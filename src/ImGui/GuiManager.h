//#pragma once

#ifndef OFX_SURFING_IM_GUI_H
#define OFX_SURFING_IM_GUI_H

/*

	This is the main class that instantiates ofxImGui.
	So ImGui context "is here".
	Handles the API workflow too,
	helping populating windows and widgets.
	Handles some internal params too, like minimize, auto resize... or extra booleans.

*/

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "ofHelpers.h"
#include "LayoutHelpers.h"

#include "surfingHelpers.h"
#ifndef OF_APP_DEFINED_ofxSurfingHelpers 
namespace ofxSurfingHelpers = ofxImGuiSurfing;
#endif

#include "HelpTextWidget.h"
#include "Combos.h"

#include "WindowsOrganizer.h"
#include "WidgetsManager.h"

//#include "SurfingThemeEditor.h"
//TODO: breaks bc recursive including?

#include "imgui_styles.h"
#include "surfingThemesHelpers.h"

//TODO: move here! now breaks!
//#include "ImGui/WindowFbo.h"
//#include "ImGui/WindowLog.h"

#ifdef SURFING_IMGUI__USE_NOTIFIER
#include "ImGui/notifiers/surfingNotifier.h"
#endif

#ifdef SURFING_IMGUI__USE_PROFILE_DEBUGGER
#include "surfingDebugger.h"
#endif

//--

// Debug

//#define OFX_IMGUI_USE_FONTS

//----

// Aliases

using namespace ofxImGuiSurfing;
using ofxImGuiSurfing::SurfingFontTypes;
//using namespace ofxSurfingHelpers;

//----

//TODO:
// These arguments are to pass to setup(..) method 
// to simplify instantiation and define settings.
//--------------------------------------------------------------
namespace ofxImGuiSurfing
{
	// Argument to be used on ui.setup(mode);

	enum SurfingGuiMode
	{
		IM_GUI_MODE_UNKNOWN = 0,
		// Could be undefined when using LEGACY API maybe.

		IM_GUI_MODE_INSTANTIATED,
		// To include the ImGui context 
		// and requiring main begin/end.

		//TODO: should rename or add presets engine + docking
		IM_GUI_MODE_INSTANTIATED_DOCKING,
		// Allows docking between multiple instances.

		IM_GUI_MODE_INSTANTIATED_SINGLE,
		// To include the ImGui context and requiring begin/end 
		// but a single ImGui instance, no other add-ons.

		//IM_GUI_MODE_SPECIAL_WINDOWS, 
		//TODO: could simplify API, bc it's duplicated from 
		//ui.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

		IM_GUI_MODE_REFERENCED,
		//TODO: -> To receive the parent (ofApp scope) 
		// ImGui object as reference.

		IM_GUI_MODE_NOT_INSTANTIATED
		// To render windows and widgets only. 
		// Inside an external ImGui context begin/end (newFrame).
	};

	//--

	// To enable Special windows mode.
	// Then handles Organizer and Align windows.
	enum SurfingGuiModeWindows
	{
		IM_GUI_MODE_WINDOWS_SPECIAL_UNKNOWN = 0,
		IM_GUI_MODE_WINDOWS_SPECIAL_DISABLED,
		IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER
		//TODO: add other modes
	};

	//--

	//TODO:
	//// To help API memo..
	//// Can we do that and avoid to create the class functions on GuiManager?
	//#define ui.AddSpacingSmall() ofxImGuiSurfing::AddSpacingSmall() 
	//#define ui.AddSpacingDouble() ofxImGuiSurfing::AddSpacingDouble() 
	//#define ui.AddSpacing() ofxImGuiSurfing::AddSpacing() 
	//#define ui.AddSpacingBig() ofxImGuiSurfing::AddSpacingBig() 
	//#define ui.AddSpacingBigSeparated() ofxImGuiSurfing::AddSpacingBigSeparated() 
	//#define ui.AddSpacingSeparated() ofxImGuiSurfing::AddSpacingSeparated() 
	//#define ui.AddSpacingHuge() ofxImGuiSurfing::AddSpacingHuge() 
	//#define ui.AddSpacingHugeSeparated() ofxImGuiSurfing::AddSpacingHugeSeparated() 
} // namespace

//----

//--------------------------------------------------------------
class SurfingGuiManager
{
public:
	SurfingGuiManager();
	~SurfingGuiManager();

#ifdef SURFING_IMGUI__USE_PROFILE_DEBUGGER
public:
	SurfingDebugger debugger;
#endif

	//----

public:
	void setup(); // We will use the most common mode, to avoid to have to require any argument.
	void setup(ofxImGuiSurfing::SurfingGuiMode mode); // Allows fully personalize the manager features. 

	void setupParams();

private:
	// MODE A: 
	// ofxImGui is instantiated inside the class, 
	// the we can forgot of declare ofxImGui here (ofApp scope).
	void setupInitiate();

public:
	// MODE B: 
	//TODO: WIP: Not tested in depth.
	// Can be instantiated out of the class, locally
	void setup(ofxImGui::Gui& gui);

	//----

private:
#ifdef SURFING_IMGUI__CREATE_EXIT_LISTENER
	void exit(ofEventArgs& e);
#endif
	void exit();

private:
	bool bDoneExit = false;

	//--

private:
	void update(); // To manual update.
	void update(ofEventArgs& args); // subscribed after app

	void draw(); // To manual draw.
	void draw(ofEventArgs& args); // Auto draw but it's used only to draw help boxes. subscribed after app

	void keyPressed(ofKeyEventArgs& eventArgs);
	void keyReleased(ofKeyEventArgs& eventArgs);

	//----

	// The Widget Styles Manager

private:
	WidgetsManager _ui;

	//--

private:
	bool bDisableStartupReset = 1; // workflow: default behavior to not reset align
	bool bDoForceStartupResetLayout = false; // will align the windows horizontally
	bool bDoneDoForceStartupResetLayout = false;
public:
	void doResetLayout(); // must be called between Begin/End
	void setDisableStartupResetLayout(bool b = 1) { bDisableStartupReset = b; } // disables auto reset layout!

	//----

	// Styles API
	// v2.0

public:
	// ofParameters 

	// Draw styled parameter into ImGui manager
	//TODO:
	// NOTE that 4 items per row is the limit yet!
	// can be use the API methods passing width ratio
	//--------------------------------------------------------------
	bool Add(ofAbstractParameter& ap, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false,
		int spacing = -1)
	{
		return _ui.Add(ap, type, amtPerRow, bSameLine, spacing);
	}

	//TODO:
	//--------------------------------------------------------------
	bool Add(ofAbstractParameter& ap, SurfingGuiTypes type, int amtPerRow, SurfingGuiFlags flags)
	{
		return _ui.Add(ap, type, amtPerRow, flags);
	}

	//TODO:
	// New API v2
	// Passing width ratio
	//-----------------------------------------------------------------
	bool Add(ofAbstractParameter& ap, SurfingGuiTypes type/* = OFX_IM_DEFAULT*/, int amtPerRow /*= 1*/,
		float ratioWidth /*= 1.f*/, bool bSameLine = false, SurfingGuiFlags flags = SurfingGuiFlags_None)
	{
		return _ui.Add(ap, type, amtPerRow, ratioWidth, bSameLine, flags);
	}

	////TODO:
	//// New API v2
	//// Passing ImVec2
	////-----------------------------------------------------------------
	//bool Add(ofAbstractParameter& ap, SurfingGuiTypes type/* = OFX_IM_DEFAULT*/, ImVec2 sz, bool bSameLine /*= false*/, SurfingGuiFlags flags = SurfingGuiFlags_None)
	//{
	// //will require to add height for all methods!
	//	return _ui.Add(ap, type, amtPerRow, ratioWidth, bSameLine, flags);
	//}

	//TODO: New API
	// Final step method, Draws using an absolute width
	//-----------------------------------------------------------------
	//bool Add(ofAbstractParameter& ap, SurfingGuiTypes type = OFX_IM_DEFAULT, float width = -1, bool bSameLine = false, int spacing = -1, SurfingGuiFlags flags = SurfingGuiFlags_None) {
	//return _ui.Add(ap, type, width, bSameLine, spacing, flags);
	//}

	////-----------------------------------------------------------------
	//bool Add(ofAbstractParameter& ap, SurfingGuiTypes type = OFX_IM_DEFAULT, float width = -1, SurfingGuiFlags flags = SurfingGuiFlags_None) {
	//	bool bSameLine = false; 
	//	int spacing = -1;
	//		return _ui.Add(ap, type, width, bSameLine, spacing, flags);
	//}

	////TODO avoid multiple ambiguous
	//bool Add(ofAbstractParameter& ap, SurfingGuiTypes type) 
	//{
	//	return _ui.Add(ap, type, -1, false, -1, SurfingGuiFlags_None);
	// }

	//----

	// Styles

	// Queue style for the parameter
	//--------------------------------------------------------------
	void AddStyle(ofAbstractParameter& ap, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1,
		bool bSameLine = false, int spacing = -1)
	{
		_ui.AddStyle(ap, type, amtPerRow, bSameLine, spacing);
	}

	// Queue style for the parameter
	//--------------------------------------------------------------
	void AddStyle(std::string name, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false,
		int spacing = -1)
	{
		_ui.AddStyle(name, type, amtPerRow, bSameLine, spacing);
	}

	// Update style for the parameter
	//--------------------------------------------------------------
	void UpdateStyle(ofAbstractParameter& ap, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1,
		bool bSameLine = false, int spacing = -1)
	{
		_ui.UpdateStyle(ap, type, amtPerRow, bSameLine, spacing);
	}

	//--------------------------------------------------------------
	void UpdateStyle(std::string name, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false,
		int spacing = -1)
	{
		_ui.UpdateStyle(name, type, amtPerRow, bSameLine, spacing);
	}

	//--

public:
	// ofParametersGroup's 

	//--------------------------------------------------------------
	void AddStyleGroup(ofParameterGroup& g, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT,
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		_ui.AddStyleGroup(g, type, flags);
	}

	//--------------------------------------------------------------
	void AddStyleGroup(std::string name, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT,
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		_ui.AddStyleGroup(name, type, flags);
	}

	//--------------------------------------------------------------
	void UpdateStyleGroup(ofParameterGroup& g, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT,
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		_ui.UpdateStyleGroup(g, type, flags);
	}

	//--------------------------------------------------------------
	void UpdateStyleGroup(std::string name, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT,
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		_ui.UpdateStyleGroup(name, type, flags);
	}

	//TODO: New API
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
			_ui.AddStyleGroup(name, type, flagst);
			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			_ui.AddStyleGroup(name, type, flagst);
			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			_ui.AddStyleGroup(name, type, flagst);
			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			_ui.AddStyleGroup(name, type, flagst);
			return;
		}

		_ui.AddStyleGroup(name, type, flagst);
	}

	//TODO:
	//--------------------------------------------------------------
	void AddStyleGroup(ofParameterGroup& g, SurfingGuiGroupStyle flags)
	{
		SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		//TODO:
		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_Hidden)
		{
			type = OFX_IM_GROUP_HIDDEN;
			_ui.AddStyleGroup(g, type, flagst);
			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			_ui.AddStyleGroup(g, type, flagst);
			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			_ui.AddStyleGroup(g, type, flagst);
			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			_ui.AddStyleGroup(g, type, flagst);
			return;
		}

		_ui.AddStyleGroup(g, type, flagst);
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
			_ui.UpdateStyleGroup(name, type, flagst);
			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			_ui.UpdateStyleGroup(name, type, flagst);
			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			_ui.UpdateStyleGroup(name, type, flagst);
			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			_ui.UpdateStyleGroup(name, type, flagst);
			return;
		}

		_ui.UpdateStyleGroup(name, type, flagst);
	}

	//TODO:
	//--------------------------------------------------------------
	void UpdateStyleGroup(ofParameterGroup& g, SurfingGuiGroupStyle flags)
	{
		SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		//TODO:
		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_Hidden)
		{
			type = OFX_IM_GROUP_HIDDEN;
			_ui.UpdateStyleGroup(g, type, flagst);
			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			_ui.UpdateStyleGroup(g, type, flagst);
			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			_ui.UpdateStyleGroup(g, type, flagst);
			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			_ui.UpdateStyleGroup(g, type, flagst);
			return;
		}

		_ui.UpdateStyleGroup(g, type, flagst);
	}

	//--

	//TODO:
	// Helper to auto populate the styles of each type (bool, floats, int's) contained on a g.
	//--------------------------------------------------------------
	void AddStyleGroupForBools(ofParameterGroup& g, SurfingGuiTypes type = OFX_IM_TOGGLE)
	{
		for (int i = 0; i < g.size(); i++)
		{
			ofAbstractParameter& ap = g[i];
			if (ap.type() == typeid(ofParameter<bool>).name())
			{
				_ui.AddStyle(ap, type);
			}

			//TODO: make it recursive
			//else if (ap.type() == typeid(ofParameterGroup).name()) {
			//	AddStyleGroupForBools(ap, type);
			//}
		}
	}

	//--------------------------------------------------------------
	void AddStyleGroupForFloats(ofParameterGroup& g, SurfingGuiTypes type = OFX_IM_HSLIDER)
	{
		for (int i = 0; i < g.size(); i++)
		{
			ofAbstractParameter& ap = g[i];
			if (ap.type() == typeid(ofParameter<float>).name())
			{
				_ui.AddStyle(ap, type);
			}
		}
	}

	//--------------------------------------------------------------
	void AddStyleGroupForInts(ofParameterGroup& g, SurfingGuiTypes type = OFX_IM_HSLIDER)
	{
		for (int i = 0; i < g.size(); i++)
		{
			ofAbstractParameter& ap = g[i];
			if (ap.type() == typeid(ofParameter<int>).name())
			{
				_ui.AddStyle(ap, type);
			}
		}
	}

	//--

	// LEGACY
	//--------------------------------------------------------------
	void clearStyles()
	{
		_ui.clear(); // update sizes to current window shape
	}

	//--------------------------------------------------------------
	void ClearStyles()
	{
		_ui.clear(); // update sizes to current window shape
	}

	//--

	// Disables a Widget and reduces transparency of most common colors.

public:
	//TODO: copy/move to ofHelpers
	//--------------------------------------------------------------
	inline void PushInactive()
	{
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
		ImGui::PushStyleColor(ImGuiCol_SliderGrab,
			ImVec4(cSliderGrab.x, cSliderGrab.y, cSliderGrab.z, cSliderGrab.w * a));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(cBorder.x, cBorder.y, cBorder.z, cBorder.w * a));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(cText.x, cText.y, cText.z, cText.w * a));

		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
	}

	//--------------------------------------------------------------
	inline void PopInactive()
	{
		ImGui::PopItemFlag();

		ImGui::PopStyleColor(6);
	}

	//----

public:
	// Styles Engine
	// 
	// _ui

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& g, ImGuiTreeNodeFlags flags, SurfingGuiTypesGroups typeGroup,
		ImGuiCond cond = ImGuiCond_Once)
	{
		_ui.AddGroup(g, flags, typeGroup, cond);
	}

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& g, bool bOpen, ImGuiCond cond = ImGuiCond_None)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
		if (bOpen) flags = ImGuiTreeNodeFlags_DefaultOpen;
		SurfingGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT;

		_ui.AddGroup(g, flags, typeGroup, cond);
	}

	// Alias
	//--------------------------------------------------------------
	void Add(ofParameterGroup& g, SurfingGuiGroupStyle flags = SurfingGuiGroupStyle_None)
	{
		AddGroup(g, flags);
	}

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& g, SurfingGuiGroupStyle flags = SurfingGuiGroupStyle_None)
	{
		////TODO: some sub folders make grow window width..
		//refreshLayout();

		SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//TODO:
		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_None)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			_ui.AddGroup(g, flagst, type);

			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_Hidden)
		{
			type = OFX_IM_GROUP_HIDDEN;
			_ui.AddGroup(g, flagst, type);

			return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			_ui.AddGroup(g, flagst, type);

			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;

			//// ? return ?
			//_ui.AddGroup(g, flagst, type);

			//return;
		}

		if (flags & ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			_ui.AddGroup(g, flagst, type);

			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			_ui.AddGroup(g, flagst, type);

			return;
		}

		_ui.AddGroup(g, flagst, type);
	}

	//----

	//TODO: Auto creates a window for the group
	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& g, ImGuiTreeNodeFlags flags, SurfingGuiTypesGroups typeGroup)
	{
		if (bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (this->BeginWindow((string)g.getName(), NULL, flags))
		{
			_ui.AddGroup(g, flags, typeGroup);

			this->EndWindow();
		}
	}

	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& g, ofParameter<bool>& _bGui, ImGuiTreeNodeFlags flags,
		SurfingGuiTypesGroups typeGroup)
	{
		if (!_bGui) return;

		if (bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

		//if (this->BeginWindow((string)g.getName(), _bGui, flags))
		if (this->BeginWindow((string)_bGui.getName(), _bGui, flags))
		{
			_ui.AddGroup(g, flags, typeGroup);

			this->EndWindow();
		}
	}

	//TODO: API update
	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& g, ofParameter<bool>& _bGui,
		SurfingGuiGroupStyle flags = SurfingGuiGroupStyle_None)
	{
		if (!_bGui) return;

		ImGuiWindowFlags f = ImGuiWindowFlags_None;
		if (bAutoResize) f |= ImGuiWindowFlags_AlwaysAutoResize;

		if (this->BeginWindow((string)_bGui.getName(), _bGui, flags))
		{
			this->AddGroup(g, flags);
			//_ui.AddGroup(g, flags);

			this->EndWindow();
		}
	}

	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& g, SurfingGuiGroupStyle flags = SurfingGuiGroupStyle_None)
	{
		ImGuiWindowFlags f = ImGuiWindowFlags_None;
		if (bAutoResize) f |= ImGuiWindowFlags_AlwaysAutoResize;

		if (this->BeginWindow((string)g.getName(), NULL, f))
		{
			this->AddGroup(g, flags);
			//_ui.AddGroup(g, flags);

			this->EndWindow();
		}
	}

	//----

	// Multi size Labels

	// Text with optional Uppercasing and Spacing

	//--------------------------------------------------------------
	void AddLabel(std::string label, SurfingFontTypes fontType, bool bUppercase = false, bool bSpacing = false)
	{
		switch (fontType)
		{
		case ofxImGuiSurfing::OFX_IM_FONT_DEFAULT: this->pushStyleFont(0);
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_BIG: this->pushStyleFont(1);
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_HUGE: this->pushStyleFont(2);
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_HUGE_XXL: this->pushStyleFont(3);
			break;
		}

		std::string t = bUppercase ? ofToUpper(label) : label;
		if (bSpacing) this->AddSpacing();
		ImGui::TextWrapped("%s", t.c_str());
		if (bSpacing) this->AddSpacing();

		switch (fontType)
		{
		case ofxImGuiSurfing::OFX_IM_FONT_DEFAULT: this->popStyleFont();
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_BIG: this->popStyleFont();
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_HUGE: this->popStyleFont();
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_HUGE_XXL: this->popStyleFont();
			break;
		}
	}

	//--------------------------------------------------------------
	void AddLabel(const std::string label, bool bUppercase = false, bool bSpacing = false)
	{
		//TODO: remove after '##'
		string n = label;
		bool bHasID = ofIsStringInString(n, "##");
		if (bHasID)
		{
			auto ss = ofSplitString(n, "##", true, true);
			n = ss[0];
		}

		std::string t = bUppercase ? ofToUpper(n) : n;
		if (bSpacing) this->AddSpacing();
		pushStyleFont(0);
		ImGui::TextWrapped("%s", t.c_str());
		popStyleFont();
		if (bSpacing) this->AddSpacing();
	}

	//--------------------------------------------------------------
	void AddLabelStyled(const std::string label, SurfingFontTypes style, bool bUppercase = false, bool bSpacing = false)
	{
		//TODO: remove after '##'
		string n = label;
		bool bHasID = ofIsStringInString(n, "##");
		if (bHasID)
		{
			auto ss = ofSplitString(n, "##", true, true);
			n = ss[0];
		}

		std::string t = bUppercase ? ofToUpper(n) : n;
		if (bSpacing) this->AddSpacing();

		pushStyleFont(int(style));
		ImGui::TextWrapped("%s", t.c_str());
		popStyleFont();

		if (bSpacing) this->AddSpacing();
	}

	//--------------------------------------------------------------
	void AddLabelNoStyled(const std::string label, bool bUppercase = false, bool bSpacing = false)
	{
		//TODO: remove after '##'
		string n = label;
		bool bHasID = ofIsStringInString(n, "##");
		if (bHasID)
		{
			auto ss = ofSplitString(n, "##", true, true);
			n = ss[0];
		}

		std::string t = bUppercase ? ofToUpper(n) : n;
		if (bSpacing) this->AddSpacing();
		ImGui::TextWrapped("%s", t.c_str());
		if (bSpacing) this->AddSpacing();
	}

	//--------------------------------------------------------------
	void AddLabelBig(const std::string label, bool bUppercase = false, bool bSpacing = false)
	{
		//TODO: remove after '##'
		string n = label;
		bool bHasID = ofIsStringInString(n, "##");
		if (bHasID)
		{
			auto ss = ofSplitString(n, "##", true, true);
			n = ss[0];
		}

		std::string t = bUppercase ? ofToUpper(n) : n;
		if (bSpacing) this->AddSpacing();
		pushStyleFont(1);
		ImGui::TextWrapped("%s", t.c_str());
		popStyleFont();
		if (bSpacing) this->AddSpacing();
	}

	//--------------------------------------------------------------
	void AddLabelHuge(const std::string label, bool bUppercase = false, bool bSpacing = false)
	{
		//TODO: remove after '##'
		string n = label;
		bool bHasID = ofIsStringInString(n, "##");
		if (bHasID)
		{
			auto ss = ofSplitString(n, "##", true, true);
			n = ss[0];
		}

		std::string t = bUppercase ? ofToUpper(n) : n;
		if (bSpacing) this->AddSpacing();
		pushStyleFont(2);
		ImGui::TextWrapped("%s", t.c_str());
		popStyleFont();
		if (bSpacing) this->AddSpacing();
	}

	//--------------------------------------------------------------
	void AddLabelHugeXXL(const std::string label, bool bUppercase = false, bool bSpacing = false)
	{
		//TODO: remove after '##'
		string n = label;
		bool bHasID = ofIsStringInString(n, "##");
		if (bHasID)
		{
			auto ss = ofSplitString(n, "##", true, true);
			n = ss[0];
		}

		std::string t = bUppercase ? ofToUpper(n) : n;
		if (bSpacing) this->AddSpacing();
		pushStyleFont(3);
		ImGui::TextWrapped("%s", t.c_str());
		popStyleFont();
		if (bSpacing) this->AddSpacing();
	}

	//--------------------------------------------------------------
	ImVec2 CalcTextSize(const std::string s)
	{
		ImVec2 sz = ImGui::CalcTextSize(s.c_str());
		return sz;
	}

	//--------------------------------------------------------------
	ImVec2 CalcTextSize(const std::string s, int indexFont)
	{
		pushStyleFont(indexFont);
		ImVec2 sz = ImGui::CalcTextSize(s.c_str());
		popStyleFont();
		return sz;
	}

	// Applied mainly to buttons
	float CalcWidgetWidth(const std::string s) {
		float sp = this->CalcTextSize(s.c_str(), 0).x;
		//sp += this->getWidgetsSpacingX();
		sp += this->getWindowSpacingX();
		return sp;
	}

	//--

	//--------------------------------------------------------------
	void AddLinkUrlButton(const std::string label, std::string url, bool bBlink = false)
	{
		ofxImGuiSurfing::AddLinkUrlButton(label.c_str(), url.c_str(), 1.0f, bBlink);
	}

	//--------------------------------------------------------------
	void AddLabelLinkURL(const std::string label, std::string url, SurfingFontTypes fontType = OFX_IM_FONT_DEFAULT,
		bool bBlink = true)
	{
		switch (fontType)
		{
		case ofxImGuiSurfing::OFX_IM_FONT_DEFAULT: this->pushStyleFont(0);
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_BIG: this->pushStyleFont(1);
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_HUGE: this->pushStyleFont(2);
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_HUGE_XXL: this->pushStyleFont(3);
			break;
		}

		ofxImGuiSurfing::AddLabelLinkURL(label.c_str(), url.c_str(), bBlink);

		switch (fontType)
		{
		case ofxImGuiSurfing::OFX_IM_FONT_DEFAULT: this->popStyleFont();
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_BIG: this->popStyleFont();
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_HUGE: this->popStyleFont();
			break;
		case ofxImGuiSurfing::OFX_IM_FONT_HUGE_XXL: this->popStyleFont();
			break;
		}

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextWrapped("Open Internet Browser");
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//--

	//// Simplified Text without Uppercasing not Spacing

	////--------------------------------------------------------------
	//void AddText(const std::string label)
	//{
	//	AddLabel(label, false, false);
	//}
	////--------------------------------------------------------------
	//void AddTextBig(const std::string label)
	//{
	//	AddLabelBig(label, false, false);
	//}
	////--------------------------------------------------------------
	//void AddTextHuge(const std::string label)
	//{
	//	AddLabelHuge(label, false, false);
	//}

	//--

	//--------------------------------------------------------------
	void AddTooltipHelp(std::string text)
	{
		ofxImGuiSurfing::AddTooltipHelp(text.c_str());
	}

	//--------------------------------------------------------------
	void AddTooltip(std::string text, bool bEnabled = true)
	{
		ofxImGuiSurfing::AddTooltip(text, bEnabled);
	}

	//--------------------------------------------------------------
	void AddTooltipBlink(std::string text, bool bBlink = true, bool bEnabled = true)
	{
		ofxImGuiSurfing::AddTooltipBlink(text, bBlink, bEnabled);
	}

	// // To be used on combos
	// //--------------------------------------------------------------
	// void AddTooltip(ofParameter<int>& pindex,std::vector<std::string> fileNames)
	// {
	// 	ofxImGuiSurfing::AddTooltip(pindex, fileNames);
	// }

	//TODO: 
	// To insert into ofParam widgets
	// Showing the name and value.

	//--------------------------------------------------------------
	template <typename ParameterType>
	void AddTooltip(ofParameter<ParameterType>& p, bool bEnabled = true, bool bNoName = true)
	{
		ofxImGuiSurfing::AddTooltip(p, bEnabled, bNoName);
	}

	/*
	//--------------------------------------------------------------
	void AddTooltip(ofAbstractParameter& p, bool bEnabled = true)
	{
		std::string s = p.getName();
		s += "\n";

		//TODO: add other types
		if (p.type() == typeid(ofParameter<float>).name())
		{
			ofParameter<float> pm = p.cast<float>();
			s += ofToString(pm.get(), 2);
		}
		else if (p.type() == typeid(ofParameter<int>).name())
		{
			ofParameter<int> pm = p.cast<int>();
			s += ofToString(pm.get());
		}
		else if (p.type() == typeid(ofParameter<bool>).name())
		{
			ofParameter<bool> pm = p.cast<bool>();
			s += ofToString((pm.get() ? "TRUE" : "FALSE"));
		}
		else {
			ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) << ("Type not implemented!");
			return;
		}

		this->AddTooltip(s, bEnabled);
	}
	*/

	//----

	// To help API coherence and/or LEGACY
	// kind of shortcuts..
	// could be simplified using namespace's..
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
	void AddSeparated()
	{
		ofxImGuiSurfing::AddSeparator();
	}

	//--------------------------------------------------------------
	void AddSeparator() // LEGACY
	{
		AddSeparated();
	}

	// Separator Text
	//--------------------------------------------------------------
	void AddSeparatorText(const std::string label, int index = 0, bool bNoline = 1)
	{
		ImGui::Spacing();

		// line transparent
		if (bNoline) ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.f, 0.f, 0.f, 0.0f));

		pushStyleFont(index);
		ImGui::SeparatorText(label.c_str());
		popStyleFont();

		if (bNoline) ImGui::PopStyleColor(); // Pop the custom color
	}

	//--------------------------------------------------------------
	// void AddSeparatorText(std::string label, bool bUppercase = false, bool bSpacing = false)
	void AddSeparatorText(std::string label, int index, bool bNoline, bool bUppercase, bool bSpacing)
	{
		if (bUppercase) label = ofToUpper(label);

		AddSeparatorText(label, index, bNoline);

		if (bSpacing) this->AddSpacing();
	}

	//--------------------------------------------------------------
	void AddSeparatedVertical(bool bSameLine = true)
	{
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		if (bSameLine)this->SameLine();
	}

	//--------------------------------------------------------------
	void AddSeparatorVertical(bool bSameLine = true) // LEGACY
	{
		AddSeparatedVertical(bSameLine);
	}

	//--------------------------------------------------------------
	void AddSpacingBig() //triple space
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

	//--------------------------------------------------------------
	void AddSpacingX(float x)
	{
		ofxImGuiSurfing::AddSpacingX(x);
	}

	//--------------------------------------------------------------
	void AddSpacingY(float y)
	{
		ofxImGuiSurfing::AddSpacingY(y);
	}

	//--------------------------------------------------------------
	void AddSpacingOffset(ImVec2 diff)
	{
		ofxImGuiSurfing::AddSpacingOffset(diff);
	}

	//--------------------------------------------------------------
	void AddSpacingToRightAlign(float width = 100)
	{
		ofxImGuiSurfing::AddSpacingToRightAlign(width);
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
		_ui.refreshLayout(); // update sizes to current window shape
	}

	//--------------------------------------------------------------
	void resetUniqueNames()
	{
		_ui.resetUniqueNames(); // update sizes to current window shape
	}

	//--

	//--------------------------------------------------------------
	void Indent()
	{
		ImGui::Indent();
		refreshLayout(); //auto calculate widgets common sizes
	}

	//--------------------------------------------------------------
	void Unindent()
	{
		ImGui::Unindent();
		refreshLayout(); //auto calculate widgets common sizes
	}

	//--------------------------------------------------------------
	void Separator()
	{
		//ImGui::Separator();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
	}

	// Make widgets a bit smaller.
	// Useful when sliders make to grow the window automatically.
	//--------------------------------------------------------------
	void PushWidth(float prc)
	{
		ofxImGuiSurfing::PushWidth(prc);
	}

	//--------------------------------------------------------------
	void PopWidth()
	{
		ofxImGuiSurfing::PopWidth();
	}

	//----

private:
	// Special Windows Mode

	SurfingGuiModeWindows specialsWindowsMode = IM_GUI_MODE_WINDOWS_SPECIAL_UNKNOWN;

public:
	//--------------------------------------------------------------
	void setWindowsMode(SurfingGuiModeWindows mode)
	{
		// Call before setup.
		specialsWindowsMode = mode;

		////workflow
		////TODO:
		//if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		//{
		//	bGui_Organizer = true;
		//	bGui_SpecialWindows = true;
		//}
	}

	// Sorting z-order windows:
	//--------------------------------------------------------------
	void setWindowFocused(string windowName)
	{
		// Bring Window to the top of the z-order if it's not already in the front
		if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows))
		{
			ImGui::SetWindowFocus(windowName.c_str());
			// ImGui::SetWindowFocus(nullptr);//un focus
		}
	}

	//--------------------------------------------------------------
	void setWindowFocused(ofParameter<bool>& p)
	{
		setWindowFocused(p.getName());
	}

private:
	// Instantiation

	SurfingGuiMode surfingImGuiMode = IM_GUI_MODE_UNKNOWN;

	//----

private:
	// ImGui Instance/Context

	// We have two mode for instantiate ImGui

	// A. ImGui is inside the add-on
	ofxImGui::Gui gui;

	// B. To be used when ImGui is passed by reference in the parent scope (ofApp)
	ofxImGui::Gui* guiPtr = NULL;

	//--

	// Initiates ofxImGui with the common settings
	void setupImGui();

public:
	// Prepare some different font files and sizes 
	// to use on labels or any widgets.
	// (currently is only one ttf file with four styles!)
	void setupFontDefault();

private:
	//TODO:pathFont is the path for all fonts..
	//void setupFontDefault(string pathFont, float sizeFont);//TODO: better API args..
	void setupFontDefault(string pathFonts, string nameFont, float sizeFont);

	void setupImGuiTheme();

	//--

	// mono-spaced fonts
	const float fontsRatioDefault = 1.0f;
	const float fontsRatioBig = 1.5f;
	const float fontsRatioHuge = 2.5f;
	const float fontsRatioHugeXXL = 3.5f;

	string pathFontMono = OFX_IM_FONT_DEFAULT_PATH_FONTS + (string)OFX_IM_FONT_DEFAULT_MONO_FILE;
	float sizeFontMono = float(OFX_IM_FONT_DEFAULT_MONO_SIZE_MIN);
	bool bDefinedMonospacedFonts = false;

public:
	vector<int> fontsMonospacedIndexes; // queue the positions of the four mono fonts
	bool isFontsMonospacedDefined()
	{
		return bDefinedMonospacedFonts;
	}

	void clearFontsMonospaced()
	{
		fontsMonospacedIndexes.clear();
		bDefinedMonospacedFonts = false;

		log.setFontMonospacedDefined(false);

		//helpApp.setFontMonospacedDefined(false);
		//helpInternal.setFontMonospacedDefined(false);
	}

private:
	// will create all the standard sizes starting as default for the passed sizeFont
	void setupFontForDefaultStylesMonospacedInternal(string pathFont, float sizeFont);
	bool bSetupFontForDefaultStylesMonospacedInternal = 0; //flag to apply out of imgui NewFrame 
public:
	// Must be called after adding the default (maybe modern) font!
	void setupFontForDefaultStylesMonospaced(string pathFont, float sizeFont);

	//----

private:
	// Rebuild default styles by loading a default font 
	// then generating the four styles: default, big, huge and huge_XXL.
	void setupFonts(string pathFonts, string nameFont, float sizeFont);

	void setupFontForDefaultStylesInternal(string pathFont, float sizeFont);

public:
	// Call after (all imgui related) setup()'s, 
	// but before pushing extra fonts. 
	// The default style will use the passed size,
	// the other three styles will be up scaled!
	// It's an alias of BuildFontStyles().
	void setupFontForDefaultStyles(string pathFont, float sizeFont)
	{
		setupFontForDefaultStylesInternal(pathFont, sizeFont);
	}


	//----


public:
	// Helpers to share the same Gui instance
	// between/with other add-ons.

	//--------------------------------------------------------------
	ofxImGui::Gui* getGuiPtr()
	{
		if (guiPtr == NULL) return &gui;
		else return guiPtr;
	}

	//--------------------------------------------------------------
	ofxImGui::Gui& getGui()
	{
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
	ImGuiContext* getContext()
	{
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

	bool BeginWindow(std::string name);
	bool BeginWindow(std::string name, bool* p_open);
	bool BeginWindow(std::string name, bool* p_open, ImGuiWindowFlags window_flags);
	//bool BeginWindow(std::string name, bool* p_open, ImGuiWindowFlags window_flags, ImGuiCond cond);
	bool BeginWindow(char* name = "Window");
	bool BeginWindow(char* name, ImGuiWindowFlags window_flags);
	//bool BeginWindow(char* name, ImGuiWindowFlags window_flags, ImGuiCond cond);

	// Useful when we can decide afterwards which type to use for a window: special or not.
	bool BeginWindowAnyType(ofParameter<bool>& p);
	void EndWindowAnyType(ofParameter<bool>& p);

	//--

	// 2. ENDs a Window

	void EndWindow();

	//----

	// Tree / Folders Helpers

	//TODO: could improve by doing open state handled by imgui.ini. Now is forced.
	//bool BeginTree(const std::string label, bool bIndented = true, bool open = false, ImGuiTreeNodeFlags flagsTree = ImGuiTreeNodeFlags_Framed)
	//--------------------------------------------------------------
	bool BeginTree(const std::string label)
	{
		bool bIndented = true;
		bool b = (ofxImGuiSurfing::BeginTree(label));
		if (b)
		{
			if (bIndented) this->Indent();
			else this->refreshLayout();
		}

		return b;
	}

	//--------------------------------------------------------------
	bool BeginTree(const std::string label, bool open /*= false*/, bool bIndented = true,
		ImGuiTreeNodeFlags flagsTree = ImGuiTreeNodeFlags_Framed)
	{
		bool b = (ofxImGuiSurfing::BeginTree(label, open, flagsTree));
		if (b)
		{
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

	//--------------------------------------------------------------
	bool BeginChild(ImVec2 size_arg = ImVec2{ 0, 130 }, std::string label = "##child", bool border = true,
		ImGuiWindowFlags extra_flags = ImGuiWindowFlags_None)
	{
		return ImGui::BeginChild(label.c_str(), size_arg, border, extra_flags);
	}

	//TODO:
	/*
	//--------------------------------------------------------------
	bool BeginChildEx(std::string label)
	{
		this->refreshLayout();

		std::string t = "##CHILD" + label;
		bool ret = ImGui::BeginChild(t.c_str(), ImVec2(), true, ImGuiWindowFlags_MenuBar);
		//ImGui::BeginChild(t.c_str(), ImVec2(-1,-1), true, ImGuiWindowFlags_MenuBar+ ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::BeginMenuBar();
		ImGui::Text("%s", label.c_str());
		ImGui::EndMenuBar();

		ImGui::NewLine();

		return ret;
	}
	*/

	//--------------------------------------------------------------
	void EndChild()
	{
		ImGui::EndChild();
	}

	//----

	// Columns

	//--------------------------------------------------------------
	void BeginColumns(int amount, std::string labelID, bool border = false)
	{
		//this->refreshLayout();
		ImGui::Columns(amount, labelID.c_str(), border);
		this->refreshLayout();
	}

	//--------------------------------------------------------------
	void NextColumn()
	{
		ImGui::NextColumn();
		this->refreshLayout();
	}

	//--------------------------------------------------------------
	void EndColumns(int amountDefault = 1)
	{
		ImGui::Columns(amountDefault);
		this->refreshLayout();
	}

	//--------------------------------------------------------------
	void setColumnWidth(int indexColumn, float wNormalized)
	{
		//refreshLayout();
		float w = _ui.getWindowWidthAvail();
		//float w = ofxImGuiSurfing::getWindowWidthAvail();
		ImGui::SetColumnWidth(indexColumn, w * wNormalized);
	}

	//--

	// Menu

	//--------------------------------------------------------------
	bool BeginMenu(const std::string label, bool enabled = true)
	{
		bool b = BeginMenuEx(label.c_str(), NULL, enabled);
		if (b) this->refreshLayout();
		return b;
	}

	//--------------------------------------------------------------
	void EndMenu()
	{
		ImGui::EndMenu();
		this->refreshLayout();
	}

	//--------------------------------------------------------------
	bool MenuItem(const std::string label, ofParameter<bool>& b, bool enabled = true)
	{
		bool selected = b.get();
		const char* shortcut = NULL;

		// return true when activated.
		return ImGui::MenuItem(label.c_str(), shortcut, selected, enabled);
	}

	//--------------------------------------------------------------
	bool MenuItem(ofParameter<bool>& b, bool enabled = true)
	{
		std::string label = b.getName();
		bool selected = b.get();
		const char* shortcut = NULL;

		return ImGui::MenuItem(label.c_str(), shortcut, selected, enabled);
	}

	//--------------------------------------------------------------
	bool MenuItemToggle(ofParameter<bool>& pb, bool enabled = true)
	{
		std::string label = pb.getName();
		bool selected = pb.get();
		const char* shortcut = NULL;
		bool b = ImGui::MenuItem(label.c_str(), shortcut, selected, enabled);
		if (b) pb = !pb;

		return b;
	}

	//--------------------------------------------------------------
	bool MenuItemToggleNamed(ofParameter<bool>& pb, string nameTrue, string nameFalse, bool enabled = true)
	{
		std::string label = pb.get() ? nameTrue : nameFalse;
		bool selected = pb.get();
		const char* shortcut = NULL;
		bool b = ImGui::MenuItem(label.c_str(), shortcut, selected, enabled);
		if (b) pb = !pb;

		return b;
	}

	//--------------------------------------------------------------
	bool MenuItemToggleNamed(ofParameter<bool>& pb, string name, bool enabled = true)
	{
		std::string label = name;
		bool selected = pb.get();
		const char* shortcut = NULL;
		bool b = ImGui::MenuItem(label.c_str(), shortcut, selected, enabled);
		if (b) pb = !pb;

		return b;
	}

	//--------------------------------------------------------------
	bool MenuItemToggleNamedAppend(ofParameter<bool>& pb, string suffix, bool enabled = true)
	{
		std::string label = pb.getName() + suffix;
		bool selected = pb.get();
		const char* shortcut = NULL;
		bool b = ImGui::MenuItem(label.c_str(), shortcut, selected, enabled);
		if (b) pb = !pb;

		return b;
	}

	//--------------------------------------------------------------
	bool MenuItemButton(const std::string label)
	{
		const char* shortcut = NULL;
		bool selected = false;
		bool enabled = true;

		return MenuItemEx(label.c_str(), NULL, shortcut, selected, enabled);
	}

	//--------------------------------------------------------------
	bool MenuItemButtonBlinking(const std::string label, bool bEnable = true)
	{
		if (bEnable) this->BeginBlinkText();
		const char* shortcut = NULL;
		bool selected = false;
		bool enabled = true;
		bool b = MenuItemEx(label.c_str(), NULL, shortcut, selected, enabled);
		if (bEnable) this->EndBlinkText();
		return b;
	}

	////--------------------------------------------------------------
	//bool MenuItemButtonBlinkingIfHover(const std::string label)
	//{
	//	this->BeginBlinkText();
	//	const char* shortcut = NULL;
	//	bool selected = false;
	//	bool enabled = true;
	//	bool b = MenuItemEx(label.c_str(), NULL, shortcut, selected, enabled);
	//	this->EndBlinkText();
	//	return b;
	//}

	//---

	// Blink Helpers

	// Will blink the contained text 
	// on widgets between begin/end
	//--------------------------------------------------------------
	inline void BeginBlinkFrame(bool bBlink = true)
	{
		ofxImGuiSurfing::BeginBlinkFrame(bBlink);
	}

	//--------------------------------------------------------------
	inline void EndBlinkFrame(bool bBlink = true)
	{
		ofxImGuiSurfing::EndBlinkFrame(bBlink);
	}

	// Will make darker the contained text on widgets between begin/end.
	// Useful to look widget as it was disabled.
	//--------------------------------------------------------------
	inline void BeginDarkenText(bool bEnable = true)
	{
		ofxImGuiSurfing::BeginDarkenText(bEnable);
	}

	//--------------------------------------------------------------
	inline void EndDarkenText(bool bEnable = true)
	{
		ofxImGuiSurfing::EndDarkenText(bEnable);
	}

	//--------------------------------------------------------------
	inline void BeginBlinkText(bool bBlink = true, bool bSoft = false)
	{
		ofxImGuiSurfing::BeginBlinkText(bBlink, bSoft);
	}

	//--------------------------------------------------------------
	inline void EndBlinkText(bool bBlink = true)
	{
		ofxImGuiSurfing::EndBlinkText(bBlink);
	}

	// For text disabled or text inputs.
	//--------------------------------------------------------------
	inline void BeginBlinkTextDisabled(bool bBlink = true)
	{
		ofxImGuiSurfing::BeginBlinkTextDisabled(bBlink);
	}

	//--------------------------------------------------------------
	inline void EndBlinkTextDisabled(bool bBlink = true)
	{
		ofxImGuiSurfing::EndBlinkTextDisabled(bBlink);
	}

	// Change text color
	//--------------------------------------------------------------
	inline void PushColorText(ofColor color)
	{
		ofxImGuiSurfing::PushColorText(color);
	}

	//--------------------------------------------------------------
	inline void PopColorText()
	{
		ofxImGuiSurfing::PopColorText();
	}

	// Border Highlight without blinking
	//--------------------------------------------------------------
	inline void BeginBorderFrame()
	{
		ofxImGuiSurfing::BeginBorderFrame();
	}

	//--------------------------------------------------------------
	inline void EndBorderFrame()
	{
		ofxImGuiSurfing::EndBorderFrame();
	}

	// Disable spacing between item 
	//--------------------------------------------------------------
	inline void BeginDisableItemSpacing()
	{
		ofxImGuiSurfing::BeginDisableItemSpacing();
	}

	//--------------------------------------------------------------
	inline void EndDisableItemSpacing()
	{
		ofxImGuiSurfing::EndDisableItemSpacing();
	}

	//----

	// The ImGui instance options

private:
	bool bViewport = false;

	bool bDockingModeCentered = false;
	//TODO: enables full screen ImGuiDockNodeFlags_PassthruCentralNode

	bool bRestoreIniSettings = true; // allow handling of .ini settings.

#ifdef SURFING_IMGUI__USE_MOUSE_HANDLING_BY_IMGUI_INSTEAD_OF_GLFW
	bool bMouseCursorFromImGui = 1;
#else
	bool bMouseCursorFromImGui = 0;
#endif

	// true (use the ImGui mouse cursor) or false (use default system mouse cursor, 
	// note that some Windows capturers requires to force disable this 
	// if you want to see mouse or other overlays!

public:
	// Must be called before setup!
	void setEnablebMouseCursorFromImGui(bool b = 1) { bMouseCursorFromImGui = b; }
	void setEnableRestoreIniSettings(bool b = 1) { bRestoreIniSettings = b; }

private:
	//TODO: 
	// Should add another boolean as in front/background.
	// separated from bAutoDraw

	bool bAutoDraw = true; // default drawn in the background
	//bool bAutoDraw = false; // default drawn in front

public:
	//TODO: 
	// To be precise, 
	// we will use bAutoDraw not to draw manually but internally.
	// we will call gui.draw() after gui.end()
	// this way allows to draw upon the GUI panels.
	// if is set to true, like is on default, 
	// you can't draw as natively/OF in front of the gui.

	//TODO: 
	// Must be false when multiple ImGui instances created ? 
	// Currently not important, kind of DEPRECATED.

	void setEnablebAutoDraw(bool b) { bAutoDraw = b; }
	// kind of alias for a more comprehensive method name
	void setEnablebDrawInBackground(bool b) { bAutoDraw = !b; }
	void setEnablebDrawInFront(bool b) { bAutoDraw = b; }

	//--------------------------------------------------------------
	void setToggleAutoDraw()
	{
		//TODO: do not works
		// can be modified during runtime...

		bAutoDraw = !bAutoDraw;

		//setupImGui();

		ImGuiConfigFlags flags = ImGuiConfigFlags_None;
		if (bDockingLayoutPresetsEngine) flags += ImGuiConfigFlags_DockingEnable;
		if (bViewport) flags += ImGuiConfigFlags_ViewportsEnable;

		//gui.exit();//crash

		if (guiPtr != nullptr) guiPtr->setup(nullptr, bAutoDraw, flags, bRestoreIniSettings, bMouseCursorFromImGui);
		else gui.setup(nullptr, bAutoDraw, flags, bRestoreIniSettings, bMouseCursorFromImGui);
	}

	//-

public:
	// API 
	// Some options

	// Force autodraw
	// LEGACY
	//--------------------------------------------------------------
	void setImGuiAutodraw(bool b = 1) { bAutoDraw = b; }
	// Must be called before setup! default is false. For ImGui multi-instance.

	void setImGuiAutoResize(bool b = 1) { bAutoResize = b; }
	// Must be called before setup! default is false. For ImGui multi-instance.

	//--

	void setImGuiViewPort(bool b = 1) { bViewport = b; }
	// Must be called before setup! 

	void setImGuiDocking(bool b = 1) { setDocking(b); }
	// Must call before setup

	void setImGuiDockingModeCentered(bool b = 1) { bDockingModeCentered = b; }
	// Allows docking on bg window viewport. Default is enabled. Must be called before setup! 

	void setImGuiDockingShift(bool b = 1) { ImGui::GetIO().ConfigDockingWithShift = b; }


	//----

	// Fonts Runtime Management 

private:
	ImFont* customFont = nullptr;
	vector<ImFont*> customFonts;
	bool bIgnoreNextPopFont = false;
	vector<std::string> namesCustomFonts;
	vector<std::string> pathsCustomFonts;

public:
	vector<ImFont*> getFontsPtr() { return customFonts; } //Warning: setup() must be called before!
	vector<std::string> getFontsNames() { return namesCustomFonts; } //Warning: setup() must be called before!

	void clearFonts();
	int getNumFonts();
	int getAmountFonts();
	std::string getFontLabel(int index);
	std::string getFontName(int index);
	float getFontSizeForIndex(int index);
	std::string getFontPath(int index); //get the path of the selected index font
	std::string getFontIndexPath(); //duplicated? //get the path of the selected index font
	float getFontIndexSize(); //get the size of the selected index font
	void doLoadPreviousFont();
	void doLoadNextFont();

	//TODO: required? bc addFontStyle workflow..
	//bool addFont(std::string path, float size);
	// Load all the fonts from the passed folder
	bool LoadFontsFromFolder(std::string path, float size = 12.f, bool bMultisize = false);

	bool addFontStyle(std::string path, float size, string label = "");

private:
	int indexCurrFont = 0;
	//TODO: load font on runtime
	//void processOpenFileSelection(ofFileDialogResult openFileResult, int size);
	//void openFontFileDialog(int size = 10); //opens file dialog window to pick a font file, passing the desired size.

	//TODO: clean duplicated push/pop

public:
	// New API
	void PushFontStyle(int index);
	void PopFontStyle();

private:
	// LEGACY
	// Use PushFont instead!
	// Enable some previously added font
	// Take care not pushing a non existing index or it will crash!
	void pushStyleFont(int index);
	void popStyleFont();

private:
	// LEGACY
	void PushFont(SurfingFontTypes style);
	void PopFont();

public:
	void setDefaultFontIndex(int index);
	void setDefaultFont();

	ofParameter<int> fontIndex{"Font", 0, 0, 3}; // by default we use 4 font sizes/types
	void DrawWidgetsFonts(); // uses internal index
	void DrawWidgetsFontsMini(); // only combo. uses internal index

	void DrawWidgetsFonts(ofParameter<int>& index, bool bWithArrows = true); // uses an external index

	void DrawImGuiTextWithFontStyle(string text, int index, bool bShowName = 1);

	string getFontIndexName();
	int getFontIndex();
	void setFontIndex(int index);

	void PushFontByIndex(); // activates font style picked from the internal index
	void PopFontByIndex();

	//----

	// Scale Global

private:
	struct ScaleGlobalGroup {
		vector<string> names{"NONE", "100%", "125%", "150%", "175%", "200%"};
		ofParameter<int> indexScaleGlobal {"Global Scale", 0, 0, names.size() - 1};
		float getScale() {
			switch (indexScaleGlobal.get()) {
			case 0: return -1.0f; break;
			case 1: return 1.0f; break;
			case 2: return 1.25f; break;
			case 3: return 1.5f; break;
			case 4: return 1.75f; break;
			case 5: return 2.0f; break;
			default: return 1.0f; break;
			}
		}
		string getName() { return names[indexScaleGlobal]; }
	};
	ScaleGlobalGroup scaleGlobalGroup;
public:
	void DrawWidgetsGlobalScaleMini() {
		this->AddSpacing();

		float w = 60;
		if (scaleGlobalGroup.indexScaleGlobal == -1) w = 60;
		else if (scaleGlobalGroup.indexScaleGlobal == 0) w = 60 * 1.f;
		else if (scaleGlobalGroup.indexScaleGlobal == 1) w = 60 * 1.f;
		else if (scaleGlobalGroup.indexScaleGlobal == 2) w = 60 * 1.25f;
		else if (scaleGlobalGroup.indexScaleGlobal == 3) w = 60 * 1.5f;
		else if (scaleGlobalGroup.indexScaleGlobal == 4) w = 60 * 1.75f;
		else if (scaleGlobalGroup.indexScaleGlobal == 5) w = 60 * 2.f;

		ImGui::PushItemWidth(w);
		if (this->AddCombo(scaleGlobalGroup.indexScaleGlobal, scaleGlobalGroup.names, true)) {
			if (scaleGlobalGroup.indexScaleGlobal.get() != 0) {
				this->globalScale = scaleGlobalGroup.getScale();
			}
			else {
			}
		}
		ImGui::PopItemWidth();
		string s = "Global Scale";
		//s += "\n" + scaleGlobalGroup.getName();
		this->AddTooltip(s);
	}

	void DrawWidgetsGlobalScale() {
		this->AddSpacingBigSeparated();
		string s;
		s = "Global Scale";
		this->AddLabelBig(s);
		this->AddSpacing();

		float w = 60;
		if (scaleGlobalGroup.indexScaleGlobal == -1) w = 60;
		else if (scaleGlobalGroup.indexScaleGlobal == 0 || scaleGlobalGroup.indexScaleGlobal == 1) w = 60;
		else if (scaleGlobalGroup.indexScaleGlobal == 2) w = 60 * 1.25f;
		else if (scaleGlobalGroup.indexScaleGlobal == 3) w = 60 * 1.5f;
		else if (scaleGlobalGroup.indexScaleGlobal == 4) w = 60 * 1.75f;
		else if (scaleGlobalGroup.indexScaleGlobal == 5) w = 60 * 2.f;

		ImGui::PushItemWidth(w);
		if (this->AddCombo(scaleGlobalGroup.indexScaleGlobal, scaleGlobalGroup.names, true)) {
			if (scaleGlobalGroup.indexScaleGlobal.get() != 0) {
				this->globalScale = scaleGlobalGroup.getScale();
			}
			else {
			}
		}
		ImGui::PopItemWidth();

		// responsive
		if ((this->getWindowWidth() > 200) &&
			(scaleGlobalGroup.indexScaleGlobal == 0 ||
				scaleGlobalGroup.indexScaleGlobal == 1 ||
				scaleGlobalGroup.indexScaleGlobal == 2)) {
			ImGui::SameLine();
		}

		float w3;
		if (this->getWindowWidth() < 200) w3 = ImGui::GetContentRegionAvail().x;
		else w3 = 200;
		ImGui::PushItemWidth(w3);
		if (this->Add(this->globalScale, OFX_IM_STEPPER_RAW_NO_LABEL))
		{

		}
		ImGui::PopItemWidth();
		s = "Global Scale is applied\n";
		s += "to all the UI context.\n";
		s += "Press Ctrl +/- to 0.01 increments.\n";
		this->AddTooltip(s);

		if (this->Add(this->globalScale, OFX_IM_HSLIDER_MINI_NO_LABELS))
		{

		}

		if (this->AddButtonRawMini("Reset")) {
			this->globalScale = 1;
		}
		s = "Set Global Scale to unit.";
		this->AddTooltip(s);

		//if (this->getWindowWidth() > 150) this->SameLine();

		this->Add(this->bGlobalScaleWheel);
		s = "Ctrl + Mouse Wheel: \nScales the active window.";
		this->AddTooltip(s);

		this->AddSpacingBigSeparated();
	}

	//----

public:
	//--------------------------------------------------------------
	void doCheckOverGui()
	{
		// Mouse lockers helpers
		// Here we check if mouse is over gui to disable other external stuff
		// e.g. easyCam draggable moving, text input boxes, key commands...

		/*
		bMouseOverGui = false;
		bMouseOverGui |= ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
		bMouseOverGui |= ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
		bMouseOverGui |= ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
		*/

		// https://github.com/ocornut/imgui/issues/4205
		// https://github.com/ocornut/imgui/issues/6021
		//bMouseOverGui |= ImGui::IsAnyItemHovered();

		// New approach
		bMouseOverGui = ImGui::GetIO().WantCaptureMouse;

		//--

		// Text input

		ImGuiIO& io = ImGui::GetIO();
		bOverInputText = io.WantTextInput;

		//// Debug
		//{
		//	ImGuiIO& io = ImGui::GetIO();
		//	ImGui::Text("io.WantCaptureMouse: %d", io.WantCaptureMouse);
		//	ImGui::Text("io.WantCaptureMouseUnlessPopupClose: %d", io.WantCaptureMouseUnlessPopupClose);
		//	ImGui::Text("io.WantCaptureKeyboard: %d", io.WantCaptureKeyboard);
		//	ImGui::Text("io.WantTextInput: %d", io.WantTextInput);
		//	ImGui::Text("io.WantSetMousePos: %d", io.WantSetMousePos);
		//	ImGui::Text("io.NavActive: %d, io.NavVisible: %d", io.NavActive, io.NavVisible);
		//}
	}

	// To disable app interactions (like camera movements) when mouse is over any ui window.
	//--------------------------------------------------------------
	bool isOverGui() const
	{
		return (bMouseOverGui.get() && bMouseOverGui.get());
	}

	//--------------------------------------------------------------
	bool isMouseOverGui() const
	{
		return bMouseOverGui;
	}

	// To disable keyboard when typing into any ui widget.
	//--------------------------------------------------------------
	bool isOverInputText() const
	{
		return bOverInputText;
	}

	// Clicks helpers. Must call between begin/end render.
	//--------------------------------------------------------------
	bool isMouseOverAppWindowRightClicked() const
	{
		bool b = ImGui::IsMouseClicked(ImGuiMouseButton_Right) &&
			ImGui::GetIO().MousePos.x >= 0 && ImGui::GetIO().MousePos.x < ImGui::GetIO().DisplaySize.x &&
			ImGui::GetIO().MousePos.y >= 0 && ImGui::GetIO().MousePos.y < ImGui::GetIO().DisplaySize.y;
		return b;
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
	ofParameter<bool> bMinimize{"Minimize", true};
	ofParameter<bool> bAutoResize{"Auto Resize", true};
	ofParameter<bool> bGlobalScaleWheel{"Wheel Global Scale", false};
	ofParameter<float> globalScale{"GlobalScale", 1, 0.5, 2};
	//float globalScalePre = 1;
	ofParameter<bool> bKeys{"Keys", true};
	ofParameter<bool> bLogKeys{"Log Keys", false};
	ofParameter<bool> bHelp{"Help App", false};
	ofParameter<bool> bHelpInternal{"Help Internal", false};
	ofParameter<bool> bDebug{"Debug", false};
	ofParameter<bool> bDebugDebugger{"Debugger", false};
	ofParameter<bool> bExtra{"Extra", false};
	ofParameter<bool> bAdvanced{"Advanced", false};
	ofParameter<bool> bReset{"Reset", false};

	ofParameter<bool> bMouseWheel{"Mouse Wheel", true};
	ofParameter<bool> bMouseWheelFlip{"Flip Wheel", false}; //for natural direction
	bool bDisableMouseWheelOnButtonsToggles = true; //TODO:

	ofParameter<bool> bThemeUIAlt{"Theme UI", false};

	ofParameter<bool> bLog{"LOG", false}; //show log window
	ofParameter<bool> bNotifier{"NOTIFIER", true}; //show notifier

	//to allow a type of super simple window for final user!
	ofParameter<bool> bGui_GameMode{"GAME", false};
	ofParameter<bool> bSolo_GameMode{"GAME SOLO", false};
	//ofParameter<bool> bGui_GameMode{ "GAME MODE", false };

	//TODO:
	ofParameter<bool> bLockMove{"Lock Move", false}; //TODO:
	ofParameter<bool> bReset_Window{"Reset Window", false}; //TODO:
	ofParameter<bool> bNoScroll{"No Scroll", false}; //TODO:
	ofParameter<bool> bLandscape{"Orientation", false}; //TODO:
	//TODO: could add a trigger to flip orientation

	ofParameter<bool> bLinkGlobal{"Link Global", true}; //TODO:
	//TODO: link windows between contexts/add-ons/ gui instances

	ofParameter<bool> bGui_Organizer{"ORGANIZER", false};
	ofParameter<bool> bGui_Aligners{"ALIGNERS", false};
	ofParameter<bool> bGui_SpecialWindows{"SPECIAL WINDOWS", false};

	//--

	ofParameterGroup params_Advanced{ "Advanced Settings" };
	// These params are saved as settings when exit and loaded when reopen the app. 

	ofParameterGroup params_Internal{ "Internal" };
	ofParameterGroup params_InternalConfig{ "InternalConfig" };
	ofParameterGroup params_Modules{ "Modules" };
	ofParameterGroup params_ModulesWindows{ "ModulesWindows" };
	ofParameterGroup params_Help{ "Module Help" };
	ofParameterGroup params_HelpInternal{ "Help Internal" };
	ofParameterGroup params_HelpApp{ "Help App" };

	ofParameterGroup params_Windows{ "Windows" };

private:
	void doBuildHelpInfo(bool bSlient = 1); //create or freshed the help info for the drawing help box

	//--

	// Rectangles to handle main window sections 

	// Positions and shape, bc we disable the ImGui management, 
	// to exclude storing on presets and imgui.ini!

private:
	ofParameterGroup params_RectPanels{ "Rectangles Windows" };
	vector<ofParameter<ofRectangle>> rectangles_Windows;

	ofParameter<ofRectangle> rect0_Presets{
		"rect_Presets",
			ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080)
	};

	ofParameter<ofRectangle> rect1_Panels{
		"rect_Panels",
			ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080)
	};

	ofParameter<ofRectangle> rect2_Manager{
		"rect_Manager",
			ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080)
	};

	ImGuiWindowFlags flags_wPr;
	ImGuiWindowFlags flags_wPanels;

	//--

	// Presets windows
	ofParameter<bool> bReset_PresetsWindow{"Reset P", false};
	ofParameter<bool> bAutoResize_PresetsWindows{"Auto Resize P", true};
	ofParameter<bool> bMinimize_Presets{"Minimize P", true};

	// Panels windows
	ofParameter<bool> bReset_WindowPanels{"Reset", false};
	ofParameter<bool> bAutoResize_Panels{"Auto Resize", true};
	//ofParameter<bool> bMinimize_Panels{ "Minimize Panels", true };

	ofParameterGroup params_WindowPresets{ "Window Presets" };
	ofParameterGroup params_WindowPanels{ "Window Panels" };
	ofParameterGroup params_WindowsEngine{ "Engine Windows" };

public:
	ofParameter<bool> bOverInputText{ "Input Text", false }; // user is over a text input
	ofParameter<bool> bMouseOverGui{"Mouse OverGui", false}; // mouse is over gui

private:
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

	// Log System Window

	// These are the default tags
	//"INFO"
	//"VERBOSE"
	//"NOTICE"
	//"WARNING"
	//"ERROR"
	// but you can add more custom tags too.

public:
	// Window Log
	SurfingLog log;

#ifdef SURFING_IMGUI__USE_NOTIFIER
public:
	// Notifier with floating boxes
	SurfingNotifier notifier;
#endif

public:
	//--------------------------------------------------------------
	void setLogFontSize(int indexFont)
	{
		indexFont = ofClamp(indexFont, 0, 3); //hardcoded
		log.setFontSize(indexFont);
	}

	//TODO: need to fix that respect the deserialization..
	//--------------------------------------------------------------
	void setLogName(std::string name)
	{
		log.setName(name);
	}

	//--------------------------------------------------------------
	void DrawWindowLogIfEnabled()
	{
		if (bLog) log.drawImGui(bLog);
	}

	////TODO:
	////--------------------------------------------------------------
	//SurfingLog getLogPtr() {
	//	return &this->log;
	//}

	//--------------------------------------------------------------
	void AddThemeToggle()
	{
		ofxImGuiSurfing::AddToggleRoundedButtonNamed(bThemeUIAlt, "Day", "Night");
	}

	//--------------------------------------------------------------
	void DrawWidgetsTheme(bool bLabel = 1)
	{
		//bool bToggled = true
		//if (bToggled)
		//	this->Add(bThemeUIAlt);

		string s = "Theme";
		s = ofToUpper(s);
		if (bLabel) this->AddLabelBig(s);

		ofxImGuiSurfing::AddToggleRoundedButtonNamed(bThemeUIAlt, "Day", "Night");
		//ofxImGuiSurfing::AddToggleRoundedButtonNamed(bThemeUIAlt, THEME_NAME_DAY, THEME_NAME_NIGHT);

		//string s;
		//if (!bThemeUIAlt) s = THEME_NAME_NIGHT;
		//else s = THEME_NAME_DAY;
		//this->AddLabel(s);
	}

#ifdef SURFING_IMGUI__USE_NOTIFIER
	//--------------------------------------------------------------
	void DrawNotifierIfEnabled()
	{
		if (bNotifier) notifier.draw(true, &customFonts);
		//if (bNotifier) notifier.draw(bDebug.get(), &customFonts);
	}
#endif

	//--------------------------------------------------------------
	void DrawWindowLog()
	{
		log.drawImGui();

		//static ofParameter<bool>b{ "LOG", true };
		//log.drawImGui(b);
	}

public:
	//--------------------------------------------------------------
	void setLogLevel(ofLogLevel logLevel) { log.setLogLevel(logLevel); }

	//--------------------------------------------------------------
	void setLogRedirectConsole(bool b = true)
	{
		log.setRedirectConsole(b);
	}

	// Create a custom tag to be used after.
	//--------------------------------------------------------------
	void AddLogTag(SurfingLog::tagData tag)
	{
		log.AddTag(tag);
	}

	//--------------------------------------------------------------
	void AddLogTag(std::string name, ofColor color)
	{
		this->AddLogTag(SurfingLog::tagData{name, color});
	}

	//--------------------------------------------------------------
	void AddLogTag(ofColor color) //not using any tag. to remove left spacing
	{
		std::string name = "";
		AddLogTag(name, color);
	}

	// Print message to log window passing the message and the tag name. 
	// Must exist or been added previously.
	//--------------------------------------------------------------
	void AddToLog(std::string text, std::string nameTag)
	{
		// Log
		log.Add(text, nameTag);
	}

	//--------------------------------------------------------------
	void ExportLogToFile()
	{
		// Log
		log.exportLogToFile();
	}

	//--------------------------------------------------------------
	void ClearLogDefaultTags() // Remove default tags, VERBOSE, NOTICE, etc.. to clean the list a bit. 
	{
		log.clearDefaultTags();
	}

	// Print message to log window passing the message and the tag index. 
	// Must exist or been added previously.
	// if there's no passed tag we will use no tag and default text color.
	//--------------------------------------------------------------
	void AddToLog(std::string text, int tag/* = -1*/)
	{
		log.Add(text, tag);
	}

	//--------------------------------------------------------------
	void AddToLog(std::string text) //TODO:adding empty tag...
	{
		//log.Add(text, "");
		log.Add(text, OF_LOG_NOTICE);
	}

	//--------------------------------------------------------------
	void AddToLog(std::string text, ofLogLevel logLevel)
	{
		log.Add(text, logLevel);
	}

	//--------------------------------------------------------------
	void ClearLog()
	{
		log.Clear();
	}

	//--------------------------------------------------------------
	void AddToLogAndNotifier(std::string text, ofLogLevel logLevel)
	{
		log.Add(text, logLevel);
		notifier.Add(text, logLevel);
	}

	//--------------------------------------------------------------
	void AddToLogAndNotifier(std::string text, std::string nameTag)
	{
		log.Add(text, nameTag);
		notifier.Add(text, nameTag);
	}

	//----

public:
#ifdef SURFING_IMGUI__USE_NOTIFIER
	//--------------------------------------------------------------
	void doResetNotifier()
	{
		notifier.doReset();
	}

	//--------------------------------------------------------------
	void doClearNotifier()
	{
		notifier.doClear();
	}

	//--------------------------------------------------------------
	void AddToNotifier(std::string text, std::string nameTag)
	{
		notifier.Add(text, nameTag);
	}

	//--------------------------------------------------------------
	void AddToNotifier(std::string text) //TODO:adding empty tag...
	{
		notifier.Add(text, OF_LOG_NOTICE);
	}

	//--------------------------------------------------------------
	void AddToNotifier(std::string text, ofLogLevel logLevel)
	{
		notifier.Add(text, logLevel);
	}

	//TODO: add tag system..
	////--------------------------------------------------------------
	//void AddToNotifier(std::string text, int tag/* = -1*/)
	//{
	//	notifier.Add(text, tag);
	//}
#endif

	//----

	// Helper

	// Populate Common Widgets for internal toggle params

	// Some simple alias and helpers
	// to populate internal params,
	// to speed up common usage:

public:
	// Minimize state
	//--------------------------------------------------------------
	bool AddMinimize(bool bSeparated = false)
	{
		AddMinimizeToggle(bSeparated);
		return bMinimize.get();
	}

	void AddMinimizeToggle(bool bSeparated = false)
	{
		this->Add(this->bMinimize, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	bool isMinimized() const { return bMinimize.get(); }
	bool isMaximized() const { return !bMinimize.get(); }
	bool isGameMode() const { return bGui_GameMode.get(); }

	// legacy
	void AddMinimizerToggle(bool bSeparated = false)
	{
		AddMinimizeToggle(bSeparated);
	}

	//--

	//TODO: add another mini xs rounded toggle
	// WARNING: can use only one per window... bc no name no id tags!
	//--------------------------------------------------------------
	void AddMinimizerXsToggle()
	{
		AddMinimizerXsToggle(this->bMinimize);
	}

	//--------------------------------------------------------------
	void AddMinimizerXsToggle(ofParameter<bool>& b, bool bSeparated = false, bool bNoLabel = true)
	{
		//this->Add(b, OFX_IM_TOGGLE_ROUNDED_MINI_XS);

		//TODO:

		float hu = this->getWidgetsHeightUnit();
		float ht = 0.8f * hu;
		float w = 1.55f * ht;
		//float w = 1.15f * ht;

		if (!bNoLabel) // label
		{
			std::string n = b.getName();
			auto sz = ImGui::CalcTextSize(n.c_str());
			w = w + sz.x;
			w += this->getWidgetsSpacingX();
			w += this->getWidgetsSpacingX();
			//w += 2;
		}
		else // no label
		{
			//w -= getWidgetsSpacingX();
			//w -= getWindowSpacingX();
			//w += getWidgetsSpacingX();
			//w -= 4;//fix
			//w -= 8;//fix
		}

		// Right aligned

		//this->AddSpacing();
		ofxImGuiSurfing::AddSpacingToRightAlign(w);

		//remove label
		ofxImGuiSurfing::AddToggleRoundedButton(b, ht, true, bNoLabel);

		this->AddTooltip(b.get() ? "Maximize" : "Minimize");

		//this->Add(b, OFX_IM_TOGGLE_ROUNDED_MINI);

		if (bSeparated) this->AddSpacingSeparated();
		else this->AddSpacing();
	}

	//--

	// Fast toggle rendered for common internal toggles

	//--------------------------------------------------------------
	bool AddKeys(bool bSeparated = false)
	{
		AddKeysToggle(bSeparated);
		return this->isKeys();
	}

	void AddKeysToggle(bool bSeparated = false)
	{
		this->Add(this->bKeys, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	void AddKeysToggle(SurfingGuiTypes style, bool bSeparated = false)
	{
		this->Add(this->bKeys, style);
		if (bSeparated)this->AddSpacingSeparated();
	}

	bool isKeys() const { return bKeys.get() && !this->isOverInputText(); }

	//--

	//--------------------------------------------------------------
	bool AddLog(bool bSeparated = false)
	{
		AddLogToggle(bSeparated);
		return bLog.get();
	}

	void AddLogToggle(bool bSeparated = false)
	{
		this->Add(this->bLog, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	void AddLogToggle(SurfingGuiTypes style, bool bSeparated = false)
	{
		this->Add(this->bLog, style);
		if (bSeparated)this->AddSpacingSeparated();
	}

	//--

	//#ifdef SURFING_IMGUI__USE_NOTIFIER
	//--------------------------------------------------------------
	bool AddNotifier(bool bSeparated = false)
	{
		AddNotifierToggle(bSeparated);
		return bNotifier.get();
	}

	void AddNotifierToggle(bool bSeparated = false)
	{
		this->Add(this->bNotifier, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	void AddNotifierToggleEditor(bool bSeparated = false)
	{
		if (!bNotifier || !bDebug) return;

		this->Indent();
		this->Add(this->notifier.bGui_Editor, OFX_IM_TOGGLE_ROUNDED_MINI);
		if (bSeparated)this->AddSpacingSeparated();
		this->Unindent();
	}

	void AddNotifierToggle(SurfingGuiTypes style, bool bSeparated = false)
	{
		this->Add(this->bNotifier, style);
		if (bSeparated)this->AddSpacingSeparated();
	}

	//#endif

	//--

	//--------------------------------------------------------------
	bool AddAutoResize(bool bSeparated = false)
	{
		AddAutoResizeToggle(bSeparated);
		return bAutoResize.get();
	}

	void AddAutoResizeToggle(bool bSeparated = false)
	{
		this->Add(this->bAutoResize, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	void AddAutoResizeToggle(SurfingGuiTypes style, bool bSeparated = false)
	{
		this->Add(this->bAutoResize, style);
		if (bSeparated)this->AddSpacingSeparated();
	}

	//--

	//--------------------------------------------------------------
	bool AddDebug(bool bSeparated = false)
	{
		AddDebugToggle(bSeparated);
		return bDebug.get();
	}

	void AddDebugToggle(bool bSeparated = false)
	{
		this->Add(this->bDebug, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	void AddDebugToggle(SurfingGuiTypes style, bool bSeparated = false)
	{
		this->Add(this->bDebug, style);
		if (bSeparated)this->AddSpacingSeparated();
	}

	bool isDebug() const { return bDebug.get(); }
	bool isDebugEnabled() const { return bDebug.get(); }
	bool isDebugDisabled() const { return !bDebug.get(); }

	//--

	// Alias
	////--------------------------------------------------------------
	//bool AddHelp(bool bSeparated = false)
	//{
	//	AddHelpToggle(bSeparated);
	//	return bHelp.get();
	//}

	void AddHelpToggle(bool bSeparated = false)
	{
		//if (!bUseHelpApp) return;
		this->Add(this->bHelp, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	void AddHelpToggle(SurfingGuiTypes style, bool bSeparated = false)
	{
		//if (!bUseHelpApp) return;
		this->Add(this->bHelp, style);
		if (bSeparated)this->AddSpacingSeparated();
	}

	bool isHelp() const { return bHelp.get(); }
	bool isHelpEnabled() const { return bHelp.get(); }
	bool isHelpDisabled() const { return !bHelp.get(); }

	// Alias
	////--------------------------------------------------------------
	//bool AddHelpInternal(bool bSeparated = false)
	//{
	//	AddHelpInternalToggle(bSeparated);
	//	return bHelpInternal.get();
	//}

	void AddHelpInternalToggle(bool bSeparated = false)
	{
		//if (!bUseHelpInternal) return;
		this->Add(this->bHelpInternal, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	void AddHelpInternalToggle(SurfingGuiTypes style, bool bSeparated = false)
	{
		//if (!bUseHelpInternal) return;
		this->Add(this->bHelpInternal, style);
		if (bSeparated)this->AddSpacingSeparated();
	}

	bool isHelpInternal() const { return bHelpInternal.get(); }
	bool isHelpInternalEnabled() const { return bHelpInternal.get(); }
	bool isHelpInternalDisabled() const { return !bHelpInternal.get(); }

	//--

	//--------------------------------------------------------------
	bool AddAdvanced(bool bSeparated = false)
	{
		AddAdvancedToggle(bSeparated);
		return bAdvanced.get();
	}

	void AddAdvancedToggle(bool bSeparated = false)
	{
		this->Add(this->bAdvanced, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	void AddAdvancedToggle(SurfingGuiTypes style, bool bSeparated = false)
	{
		this->Add(this->bAdvanced, style);
		if (bSeparated)this->AddSpacingSeparated();
	}

	bool isAdvanced() const { return bAdvanced.get(); }
	bool isAdvancedEnabled() const { return bAdvanced.get(); }
	bool isAdvancedDisabled() const { return !bAdvanced.get(); }

	//--

	//--------------------------------------------------------------
	bool AddExtra(bool bSeparated = false)
	{
		AddExtraToggle(bSeparated);
		return bExtra.get();
	}

	void AddExtraToggle(bool bSeparated = false)
	{
		this->Add(this->bExtra, OFX_IM_TOGGLE_ROUNDED);
		if (bSeparated)this->AddSpacingSeparated();
	}

	void AddExtraToggle(SurfingGuiTypes style, bool bSeparated = false)
	{
		this->Add(this->bExtra, style);
		if (bSeparated)this->AddSpacingSeparated();
	}

	bool isExtra() const { return bExtra.get(); }
	bool isExtraEnabled() const { return bExtra.get(); }
	bool isExtraDisabled() const { return !bExtra.get(); }

	//----

	// Advanced Window

private:
	// An advanced/extra common panel
	// with some bool toggles commonly used.

	//--------------------------------------------------------------
	void DrawAdvancedControls()
	{
		DrawAdvancedBundle();
	}

public:
	//--------------------------------------------------------------
	void DrawWindowAdvanced(bool bForceVisible = false)
	{
		bool b;
		if (!bForceVisible) b = BeginWindow(bAdvanced);
		else b = BeginWindow(bAdvanced.getName());
		if (b)
		{
			//if (!bForceVisible)this->Add(bAdvanced, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);
			DrawAdvancedSubPanel(true, bForceVisible);
			EndWindow();
		}
	}

	// Simpler call. Should use this one.
	//--------------------------------------------------------------
	void DrawAdvancedBundle(bool bSeparator = false, bool bSpacing = false, bool bListenToMinimize = false)
	{
		if (bMinimize && bListenToMinimize) return;

		if (bSpacing) ImGui::Spacing();
		if (bSeparator) ImGui::Separator();
		ImGui::Spacing();

		this->Add(bAdvanced, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);

		DrawAdvancedSubPanel();
	}

private:
	// LEGACY API
	//--------------------------------------------------------------
	void DrawAdvanced(bool bSeparator = false, bool bSpacing = false)
	{
		DrawAdvancedBundle(bSeparator, bSpacing);
	}

	//--

private:
	//--------------------------------------------------------------
	void DrawAdvancedSubPanel(bool bHeader = true, bool bForceVisible = false)
	{
		if (!bForceVisible)
		{
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
			//if (bUseHelpApp) this->Add(bHelp, OFX_IM_TOGGLE_ROUNDED);
			//hide if it's not settled by the user from ofApp!

			// Help Internal
			this->Add(bHelpInternal, OFX_IM_TOGGLE_ROUNDED);

			// Menu
			Add(bGui_Menu, OFX_IM_TOGGLE_ROUNDED);

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
						this->AddSpacing();

						// Global Scale
						this->Add(globalScale);
						this->Add(bGlobalScaleWheel, OFX_IM_TOGGLE_ROUNDED_MINI);
						this->AddSpacing();

						// MouseWheel
						this->Add(bMouseWheel, OFX_IM_TOGGLE_ROUNDED_MINI);
						this->Add(bMouseWheelFlip, OFX_IM_TOGGLE_ROUNDED_MINI);
						ofxImGuiSurfing::AddTooltip("Press CTRL+ for fine tunning");

						////TODO:
						//// Lock
						//this->AddSpacing();
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
						//Add(bGui_Menu, OFX_IM_TOGGLE_ROUNDED_MEDIUM);

						//--

						// Debug
						Add(bDebug, OFX_IM_TOGGLE_ROUNDED);
						if (bDebug)
						{
							this->Indent();

							//--

							//drawSpecialWindowsPanel();
							//ImGui::Separator();

							Add(bDebugDebugger, OFX_IM_TOGGLE_ROUNDED_MINI);
							this->AddSpacing();
							Add(bOverInputText, OFX_IM_TOGGLE_ROUNDED_MINI);
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
									ImGui::TextWrapped("%s", _hwidget.c_str());

									std::string _wwidget = "Full Width:\n";
									_wwidget += ofToString(ofxImGuiSurfing::getWidgetsWidth(1));
									ImGui::TextWrapped("%s", _wwidget.c_str());

									this->AddSpacing();
									this->AddLabelBig("Window", false, true);
									std::string _wpanel = "Inner Width:\n";
									_wpanel += ofToString(ofxImGuiSurfing::getPanelWidth());
									ImGui::TextWrapped("%s", _wpanel.c_str());

									std::string _wShape = "Shape:\n";
									_wShape += ofToString(ImGui::GetWindowPos().x);
									_wShape += ", ";
									_wShape += ofToString(ImGui::GetWindowPos().y);
									_wShape += ", ";
									_wShape += ofToString(ImGui::GetWindowWidth());
									_wShape += ", ";
									_wShape += ofToString(ImGui::GetWindowHeight());
									ImGui::TextWrapped("%s", _wShape.c_str());
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
	void setUseAdvancedSubPanel(bool b)
	{
		bUseAdvancedSubPanel = b;
	}

	//----

private:
	ofParameter<bool> bAutoSaveSettings{ "Autosave", true };

private:
	// File Settings
	std::string path_Root = "";
	std::string path_Global;
	std::string path_ImLayouts;
	std::string path_AppSettings;
	std::string path_LayoutSettings;

	std::string nameLabel = "SurfingGui";

	ofParameterGroup params_AppSettings{ "ofxSurfingGui" }; // Features states
	ofParameterGroup params_AppSettingsLayout{ "LayoutSettings" }; // Layout states

public:
	//--------------------------------------------------------------
	std::string getPathRoot() const
	{
		if (path_Root == "") return path_Global;
		else return path_Root;
	}

	//--------------------------------------------------------------
	std::string getPathGlobal() const
	{
		return path_Global;
	}

	//--------------------------------------------------------------
	std::string getPath() const
	{
		return path_Global;
	}

	//----

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
		path_Root = nameLabel + "/";
		path_Global = nameLabel + "/Gui/";

#if 0
		ofxImGuiSurfing::CheckFolder(path_Global);
#endif

		// Useful toggles for internal Windows
		windowsOrganizer.setPathGlobal(path_Global);

		//--

//		//TODO: should be static to share same windows between all the ofxImGui instances
//		// Avoid multiple windows with same name with multi instances..
//
//		// Too long names..
//		/*
//		// Customize common windows duplicated on when using multiple instances.
//		// that's to avoid overlapping contents when ImGui windows have the same name!
//		bGui_Aligners.setName(nameLabel + " ALIGNERS");
//		bGui_Organizer.setName(nameLabel + " ORGANIZER");
//		bGui_SpecialWindows.setName(nameLabel + " SPECIALW");
//		*/
//
//#if 0
//		// Use first letter only
//		bGui_Aligners.setName("ALIGNERS " + ofToString(nameLabel[0]));
//		bGui_Organizer.setName("ORGANIZER " + ofToString(nameLabel[0]));
//		bGui_SpecialWindows.setName("SPECIALW " + ofToString(nameLabel[0]));
//#endif
//
//		//TODO: short names but could spread many windows when multi instances
//		bGui_Aligners.setName("ALIGNERS");
//		bGui_Organizer.setName("ORGANIZER");
//		bGui_SpecialWindows.setName("SPECIALW");
//
//		//--
//
//		// Aligners toggle
//		windowsOrganizer.bGui_Aligners.makeReferenceTo(bGui_Aligners);
//
//		// Link Organizer toggle
//		windowsOrganizer.bGui_Organizer.makeReferenceTo(bGui_Organizer);
//
//		// Special Windows toggle
//		windowsOrganizer.bGui_SpecialWindows.makeReferenceTo(bGui_SpecialWindows);
//
//		// Link both link toggles, local and the one inside the organizer object
//		windowsOrganizer.bLinked.makeReferenceTo(bLinked);
//		//TODO: expose more params
//		windowsOrganizer.bOrientation.makeReferenceTo(bOrientation);
//		windowsOrganizer.bGui_ShowWindowsGlobal.makeReferenceTo(bGui_ShowWindowsGlobal);
//		windowsOrganizer.bAlignWindowsReset.makeReferenceTo(bAlignWindowsReset);
//		windowsOrganizer.bAlignWindowsCascade.makeReferenceTo(bAlignWindowsCascade);
//
//		//--
//
//		////TODO: breaks serialization
//		////TODO: customize log window to allow multiple windows
//		//// with different names for bGui toggles too
//		//bLog.setName(nameLabel);
//		//log.setName(nameLabel);
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
	void setAutoSaveSettings(bool b)
	{
		// must call before setup. IMPORTANT: if you are using multiple instances of this add-on, must set only one to true or settings will not be handled correctly!
		bAutoSaveSettings = b;
	}


	//--------------------------------------------------------------
	void setAutoResize(bool b)
	{
		// must call before setup
		bAutoResize = b;
	}

	//--------------------------------------------------------------
	void setDocking(bool b)
	{
		// must call before setup
		bDockingLayoutPresetsEngine = b;
	}

	//---------------------------

	// Special Windows Engine

	//private:

	//TODO:
	// 
	// That simplifies the API a bit.
	// When calling EndWindowSpecial,
	// there's no need to pass what window/toggle/name is.
	// Thats bc memorizes last index called on previous BeginWindowSpecial.
	// That must coincided if API is well used!
	//  
	// Should remove. DEPRECATED
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
	void EndWindowSpecial()
	{
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

	int getWindowSpecialIndexForName(std::string name);
	// to be used if you forgot or don't know the index

	// Check if that param toggle is previously added as an special window
	// that's useful when using passed as reference ui's
	// when using multiple ui instances sharing the same object instance!
	//--------------------------------------------------------------
	bool isThereSpecialWindowFor(ofParameter<bool>& _bGui)
	{
		bool b = this->getWindowSpecialIndexForName(_bGui.getName()) != -1;
		return b;
	}

	//----

	// Organizer for the Special Windows

public:
	//--------------------------------------------------------------
	void drawWindowOrganizer() // Draws the main panel controller.
	{
		if (bGui_Organizer) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

		if (BeginWindow(bGui_Organizer))
		{
			this->Add(bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED);
			this->AddSpacingSeparated();

			windowsOrganizer.drawWidgetsOrganizer(bMinimize, !bGui_Aligners, !bGui_SpecialWindows);

			this->EndWindow();
		}
	}

	//--------------------------------------------------------------
	void setWindowsSpecialsOrientation(bool b)
	{
		// Set orientation of window special alignment! horz/vert
		windowsOrganizer.bOrientation = b;
	}

	//--------------------------------------------------------------
	void drawWindowAligners()
	{
		if (bGui_Aligners) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;

		if (BeginWindow(bGui_Aligners))
		{
			this->Add(bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED);
			this->AddSpacingSeparated();

			windowsOrganizer.drawWidgetsAligners(bMinimize);

			if (!bMinimize && !bGui_Organizer)
			{
				this->AddSpacing();
				this->Add(windowsOrganizer.pad, OFX_IM_STEPPER);
			}

			this->EndWindow();
		}
	}

	//TODO: DEPRECATED
	////--------------------------------------------------------------
	//bool getGuiToggleGlobal() {
	//	return windowsOrganizer.bGui_ShowWindowsGlobal.get();
	//}
	//--------------------------------------------------------------
	bool getGuiToggleGlobalState() const
	{
		return windowsOrganizer.bGui_ShowWindowsGlobal.get();
	}

	//--

	//TODO: WIP:
	//--------------------------------------------------------------
	struct SurfingImWindow
	{
		// We queue here the bool params 
		// that enables the show/hide for each queued window
		ofParameter<bool> bGui{"_bGui", true};

		ofParameter<bool> bAutoResize{"Auto Resize", true};

		////TODO: could be removed...not used yet..
		//ofParameter<bool> bExtra{ "Extra", false };
		//ofParameter<bool> bMinimize{ "Minimize", false };
		//ofParameter<bool> bAdvanced{ "Advanced", false };
		//ofParameter<bool> bDebug{ "Debug", false };
		//ofParameter<bool> bReset_Window{ "Reset Window", false };

		//TODO:
		// Only one special window can be flagged as master anchor,
		// then will be force to be the first window always!
		ofParameter<bool> bMasterAnchor{"MasterAnchor", false};

		//--------------------------------------------------------------
		void setMasterAnchor(bool b)
		{
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
	int getPad() { return windowsOrganizer.pad; } //used pad between windows

	//public:
	//
	//	//TODO: DEPRECATED
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
	void clearSpecialWindows()
	{
		windows.clear();
	}

	//--------------------------------------------------------------
	SurfingGuiModeWindows getModeSpecial() const
	{
		return specialsWindowsMode;
	}

	// NOTE:
	// Setup, and Startup is auto called when addWindowsSpecial is called!
	// We can omit them to speed up initialization.
	// FYI
	// The internal steps are:
	//ui.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
	//ui.setup();
	//ui.addWindowSpecial(..
	//ui.addWindowSpecial(..
	//ui.startup();

	//--------------------------------------------------------------
	void addWindowSpecial(ofParameter<bool>& _bGui, bool _bAutoResize = true, bool _bMaster = false)
	{
		SurfingImWindow win;
		win.bGui.makeReferenceTo(_bGui);
		win.bAutoResize = _bAutoResize;
		win.setMasterAnchor(_bMaster); //TODO:

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
	void addWindowSpecial(std::string name, bool _bAutoResize = true, bool _bPowered = false)
	{
		// Security Checks

		// Special windows mode
		if (specialsWindowsMode != IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		{
			ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) << ("Special Windows mode was not initiated.");
			ofLogWarning("ofxSurfingImGui") << ("Force Special Windows mode to allow add special Windows!");

			this->setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
		}

		// Also to simplify a bit the API.
		if (!bDoneSetup)
		{
			ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) << ("Setup was not previously done!");
			ofLogWarning("ofxSurfingImGui") << ("Force run SurfingGuiManager::setup() now!");

			setup();
		}

		ofParameter<bool> _bGui{name, true};

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
	std::string getWindowSpecialName(int index)
	{
		if (index > windows.size() - 1 || index == -1)
		{
			ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n" << "Out of range index for queued windows, " <<
				index;

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
	//void addWindow(std::string name, bool bPowered = false) { // LEGACY API
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
	// DEPRECATED
	// Exposed helpers to external GUIs / scope.

	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleGlobal()
	{
		// global toggle to show/hide the all panels
		return windowsOrganizer.bGui_ShowWindowsGlobal;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleLinked()
	{
		// toggle to enable or disable
		return windowsOrganizer.bLinked;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleOrganizer()
	{
		return bGui_Organizer;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleAligner()
	{
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
	//TODO: working ?
	//--------------------------------------------------------------
	void setNextWindowOnViewport(ImGuiCond cond = ImGuiCond_Appearing)
	{
		// can't be settled to ImGuiCond_Always bc will feedback/apply with the same window!
		ImGui::SetNextWindowPos(getTopRightWindowLast(), cond);
	}

	// Set next window position after the window named as the passed named and with the layout type distribution.
	// layoutType = 0 : top right 
	// layoutType = 1 : bottom left
	// layoutType = 2 : top left //TODO: BUG
	// layoutType = 3 : top up //TODO:
	//TODO: add vec2 offset...
	//--------------------------------------------------------------
	void setNextWindowAfterWindowNamed(std::string nameAnchorWindow /*= "-1"*/, int layoutType = 0,
		ImGuiCond cond = ImGuiCond_Always)
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

	// Passed anchor bGui / visible toggle to position next window next to passed window.
	//--------------------------------------------------------------
	void setNextWindowAfterWindowNamed(ofParameter<bool>& bGui)
	{
		//TODO:
		if (!bGui.get()) return;

		setNextWindowAfterWindowNamed(bGui.getName());
	}

	//--

	//TODO:
	// Set anchor first window from a parent scope:
	// That feature allows to link grouped windows from many contexts / add-ons.

	// Get the name of the last special window (the window at the end of current drawn queue)
	//--------------------------------------------------------------
	std::string getWindowSpecialLast() const
	{
		return windowsOrganizer.getWindowSpecialLast();
	}

	// Get the position of the last special window (the window at the end of current drawn queue)
	//--------------------------------------------------------------
	glm::vec2 getWindowSpecialLastTopRight() const
	{
		return windowsOrganizer.getWindowSpecialLastTopRight();
	}

	//-

	// Get anchor from first window taken from the parent scope
	//--------------------------------------------------------------
	glm::vec2 getWindowSpecialLastTopLeft() const
	{
		return windowsOrganizer.getWindowSpecialLastTopLeft();
	}

	// Set the anchor position from the parent scope
	//--------------------------------------------------------------
	void setWindowSpecialFirstPosition(glm::vec2 pos)
	{
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
	float getWidth()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	//--------------------------------------------------------------
	float getWindowWidth()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	//--------------------------------------------------------------
	float getWidgetsWidth(int amnt = 1)
	{
		return ofxImGuiSurfing::getWidgetsWidth(amnt);
	}

	//--------------------------------------------------------------
	float getWidgetsHeight()
	{
		return ofxImGuiSurfing::getWidgetsHeight();
	}

	//--------------------------------------------------------------
	float getFontSize()
	{
		return ofxImGuiSurfing::getFontSize();
	}

	// LEGACY
	//--------------------------------------------------------------
	float getWidgetsHeightUnit()
	{
		return ofxImGuiSurfing::getWidgetsHeightUnit();
	}

	//--------------------------------------------------------------
	float getWidgetsSpacingX()
	{
		return ImGui::GetStyle().ItemSpacing.x;
	}

	//--------------------------------------------------------------
	float getWidgetsSpacingY()
	{
		return ImGui::GetStyle().ItemSpacing.y;
	}

	//--------------------------------------------------------------
	float getWidgetHeightVerticalSlider()
	{
		float h = this->getWidgetsHeightUnit() * VERTICAL_AMOUNT_UNITS;
		return h;
	}

	//--------------------------------------------------------------
	float getWindowSpacingX()
	{
		return ImGui::GetStyle().WindowPadding.x;
	}

	// LEGACY API
	//--------------------------------------------------------------
	void refreshWidgetsSizes(float& _w100, float& _w50, float& _w33, float& _w25, float& _h)
	{
		ofxImGuiSurfing::refreshImGui_WidgetsSizes(_w100, _w50, _w33, _w25, _h);
	}

public:
	//----

	// Layouts Engine

	// Extra Params to include packed into layout presets too.
	// By default we will have menu and log toggles,
	// but we can add more from our ofApp

	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameterGroup& g)
	{
		params_LayoutsExtra.add(g);
	}

	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameter<bool>& param)
	{
		params_LayoutsExtra.add(param);
	}

	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameter<int>& param)
	{
		params_LayoutsExtra.add(param);
	}

	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameter<float>& param)
	{
		params_LayoutsExtra.add(param);
	}

	//--------------------------------------------------------------
	void addExtraParamToLayoutPresets(ofParameter<ofRectangle>& param)
	{
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
		//TODO: could this be problematic?
		// bc we are not storing the param neither returning a reference?

		if (index > windows.size() - 1 || index == -1)
		{
			ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n" << "Out of range index for queued windows, " <<
				index;
			ofParameter<bool> b = ofParameter<bool>{ "-1", false };
			return b;
		}

		return windows[index].bGui;
	}

	// Easy populate all the Special Windows toggles. Call inside a window.
	//--------------------------------------------------------------
	void drawWidgetsSpecialWindowsToggles(SurfingGuiTypes style = OFX_IM_TOGGLE_ROUNDED)
	{
		for (size_t i = 0; i < windows.size(); i++)
		{
			this->Add(getWindowSpecialGuiToggle(i), style);
		}
	}

	// Creates a Helper Window 
	// with auto populated all the Special Windows toggles. 
	// To be called outside a window, just between the main begin/end!
	//--------------------------------------------------------------
	void drawWidgetsSpecialWindows(bool bFoldered)
	{
		if (bFoldered)
		{
			bool b = this->BeginTree("Windows");
			if (b)
			{
				drawWidgetsSpecialWindows();
				this->EndTree();
			}
		}
		else drawWidgetsSpecialWindows();
	}

	//--------------------------------------------------------------
	void drawWidgetsSpecialWindows()
	{
		float _h = getWidgetsHeight();
		float _w1 = getWidgetsWidth(1);
		float _w2 = getWidgetsWidth(2);

		if (ImGui::Button("All", ImVec2(_w2, _h)))
		{
			for (auto& p : windowsOrganizer.windowsPanels)
			{
				p.bGui = true;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("None", ImVec2(_w2, _h)))
		{
			for (auto& p : windowsOrganizer.windowsPanels)
			{
				p.bGui = false;
			}
		}

		// Show Global
		this->Add(windowsOrganizer.bGui_ShowWindowsGlobal, OFX_IM_TOGGLE_ROUNDED);

		// All toggles
		if (windowsOrganizer.bGui_ShowWindowsGlobal)
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
		if (bGui_SpecialWindows) {
			IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;
		}
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
		windowsOrganizer.bGui_ShowWindowsGlobal = !windowsOrganizer.bGui_ShowWindowsGlobal;
	}

	//--------------------------------------------------------------
	void setWindowSpecialToggleVisible(int index)
	{
		if (index > windows.size() - 1 || index == -1)
		{
			ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n" << "Out of range index for queued windows, " <<
				index;

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
	bool loadSettings();
public:
	// Required to save the UI internal settings. The window positions and many stuff is handled bi imgui.ini itself.
	void saveSettings();
	void save() { saveSettings(); }//alias

	//----

	////TODO: WIP:
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

	void loadLayout(int mode);
	void saveLayout(int mode);

	void saveLayoutPreset(std::string path); //-> both group params and ImGui ini files
	void loadLayoutPreset(std::string path);

	void saveLayoutImGuiIni(std::string path);
	void loadLayoutImGuiIni(std::string path);
	void saveLayoutPresetGroup(std::string path);
	void loadLayoutPresetGroup(std::string path);

	ofParameter<int> appLayoutIndex{"Layout Preset", -1, -1, 0};
	// index for the selected preset. -1 is none selected, useful too.
	int appLayoutIndex_PRE = -1;

	ofParameterGroup params_Layouts{ "LayoutsPresets" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsVisible{ "PanelsVisible" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsExtra{ "Extra Params" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsExtraInternal{ "Internal" }; // add-on related params

	int numPresetsDefault;
	void createLayoutPreset(std::string namePreset = "-1");

	//-

	vector<ofParameter<bool>> bLayoutPresets{"bLayoutPresets"}; // each window show toggles
	void Changed_Params(ofAbstractParameter& e);
	ofParameterGroup params_LayoutsPanel{ "Layouts Panel" };

	//void Changed_Enablers(ofAbstractParameter& e);

	//--------------------------------------------------------------
	std::string getLayoutName(int mode)
	{
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
	void setPresetsNames(vector<std::string> names)
	{
		if (names.size() != 4)
		{
			ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n" << "Names sizes are not equals to 4";
		}

		namesPresets.clear();
		namesPresets = names;
	}

private:
	vector<std::string> namesPresets;

public:
	//-> Must call manually after adding windows and layout presets
	void setupLayout(int numPresets = DEFAULT_AMOUNT_PRESETS);

	//--------------------------------------------------------------
	void startup();

	//-

	// Reset Settings
	void DrawWidgetsResetUI();
	void resetUISettings();
private:
	bool bResetUIProgramed = false;

	//-

private:
	bool bDoneStartup = false;
	bool bDoneSetup = false;

	//public:

	void setupStartupForced(); //will be called on first frame/update() call!
	void setupDocking(); //TODO: rename as presets + docking...

	//--------------------------------------------------------------
	void setImGuiLayoutPresets(bool b)
	{
		bUseLayoutPresetsManager = b;
	}

	//--

public:
	void drawWindowsExtraManager(); //will be called at End(), 
	//to draw other internal and auto handled windows/modules.

	void drawMenu();
	void drawMenuDocked();

public:
	// Get the central space to position other panels or gui elements
	// like video viewports or scenes previews
	//--------------------------------------------------------------
	ofRectangle getRectangleCentralDocking()
	{
		return rectangle_Central_MAX;
		//return rectangle_Central;
	}

	//--

private:
	void updateLayout();

	void drawLayoutsPresetsEngine(); //all the windows of the engine
	void drawLayoutsPresetsManualWidgets();
	void drawLayoutsLayoutPresets();
	void drawLayoutsPanels();
	void drawLayoutPresetsEngine();
	void drawViewport_OF_Native();

	//TODO:
	//// For different behavior. We can disable to save some windows positions to allow them locked when changing presets.
	//ofParameter<bool> bModeFree{ "Free", true }; // A allows storing position for control windows too
	//ofParameter<bool> bModeForced{ "Forced", false }; // Locked to free space on viewport
	//ofParameter<bool> bModeLock1{ "Lock B", false }; // Cant be moved. To be used in presets panel
	//ofParameter<bool> bModeLockControls{ "Lock C", false }; // Cant be moved. To be used to lock to free viewport scenarios
	//ofParameter<bool> bModeLockPreset{ "Lock A", false }; // Cant be moved. To be used to lock to free viewport scenarios

	//TODO: 
	// It's a problem if .ini files are already present... We must ingore loading.

	ofParameter<bool> bDebugDocking{"Debug Docking", false};

	ofParameter<bool> bDrawView2{"Draw View 2", false};

	ofRectangle rectangle_Central_MAX;
	ofRectangle rectangle_Central; // current free space viewport updated when changes
	ofRectangle rectangle_Central_Transposed;

	//-

	// Customize Titles

public:
	//--------------------------------------------------------------
	void setLabelLayoutPanels(std::string label)
	{
		// Customize the app name for panels window label tittle
		bGui_LayoutsPanels.setName(label);
	}

	//--------------------------------------------------------------
	void setLabelLayoutMainWindow(std::string label)
	{
		bGui_LayoutsManager.setName(label);
	}

	//-

public:
	ofParameter<bool> bGui_Menu{ "Menu", false };

	ofParameter<bool> bLinked{"Link Windows", true}; // Align windows engine. liked to the internal aligner.
	//TODO: more to link with internal WindowsOrganizer
	ofParameter<bool> bOrientation{"Orientation", false}; // false=horizontal. true=vertical
	ofParameter<bool> bGui_ShowWindowsGlobal{"Show Windows", true}; // to force hide all windows or to show if visible
	//ofParameter<bool> bGui_ShowWindowsGlobal{"Show Global", true}; // to force hide all windows or to show if visible
	ofParameter<bool> bAlignWindowsReset{"Reset", false};
	ofParameter<bool> bAlignWindowsCascade{"Cascade", false};

private:
	ofParameter<bool> bGui_LayoutsPanels{ "PANELS", true };
	ofParameter<bool> bGui_LayoutsPresetsSelector{"LAYOUTS", true};
	ofParameter<bool> bGui_LayoutsManager{"MANAGER", false};

	ofParameter<bool> bAutoSave_Layout{"Auto Save", true};
	ofParameter<bool> bUseLayoutPresetsManager{"Layout Engine", false};
	// Can't be changed on runtime. cant include into settings

	ofParameter<bool> bDockingLayoutPresetsEngine{"Dock Engine", false};

	ofParameter<bool> bSolo{"Solo", false}; //TODO: for presets layouts engine

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
	// #include <functional>
	//std::function<void()> doCallback = nullptr

private:
	bool* bResetPtr = nullptr;

public:
	//--------------------------------------------------------------
	void setReset(bool* b)
	{
		//link to an external / parent scope bool to assing to the internal reset button.
		bResetPtr = b;
	}

	//--------------------------------------------------------------
	void setShowAllWindows(bool b)
	{
		//show main internal windows and panels too
		setShowAllPanels(b);

		//bModeLockControls = b;
		bGui_Menu = b;

		bGui_LayoutsPanels = b;
		bGui_LayoutsPresetsSelector = b;
		//bGui_LayoutsPresetsManual = false;
	}

	//--------------------------------------------------------------
	void setShowAllPanels(bool b)
	{
		for (int i = 0; i < windows.size(); i++)
		{
			windows[i].bGui.set(b);
		}
	}

	//--------------------------------------------------------------
	void doRemoveDataFiles()
	{
		// Remove all the settings folder
		const filesystem::path path = path_Global;
		ofDirectory::removeDirectory(path, true, true);

		// Remove imgui.ini file
		const filesystem::path file = ofToDataPath("../imgui.ini");
		ofFile::removeFile(file, true);
	}

	//--------------------------------------------------------------
	void doSpecialWindowToggleVisible(int index)
	{
		if (index >= windows.size()) return; //ignore
		windows[index].bGui = !windows[index].bGui;
	}

	//--

public:
	HelpTextWidget helpInternal;
	HelpTextWidget helpApp;

private:
	//TODO: replace help boxes 
	// with new ImGui classes

	// We have to independent help boxes.
	// One is intended to be use as the add-on itself help (Internal Help),
	// and another to be used as an external help (App Help).
	// Can be initialized from outer scope.

	// Help Internal: How to use the add-on itself
	std::string helpInternalText = "";

	// Help App: How to use our App 
	std::string helpAppText = "";

	// main help disablers
	bool bUseHelpInternal = false;
	bool bUseHelpApp = false;

	//--

public:
	// Must be called after ui.setup();
	//--------------------------------------------------------------
	void setEnableHelpInternal(bool b = true)
	{
		bUseHelpInternal = b;

#ifdef SURFING_IMGUI__USE_CUSTOM_FONTS_PTR
		helpInternal.setCustomFontsPtr(&customFonts, &namesCustomFonts);
#else
		helpInternal.setCustomFonts(customFonts, namesCustomFonts);
#endif
	}

	// Must be called after ui.setup();
	//--------------------------------------------------------------
	void setEnableHelpApp(bool b = true)
	{
		bUseHelpApp = b;

#ifdef SURFING_IMGUI__USE_CUSTOM_FONTS_PTR
		helpApp.setCustomFontsPtr(&customFonts, &namesCustomFonts);
#else
		helpApp.setCustomFonts(customFonts, namesCustomFonts);
#endif

		//helpApp.setFontMonospacedDefined();
	}

	// Must be called after ui.setup();
	// If we are using mono-spaced fonts, 
	// it must be called after be have been added the mono-spaced fonts.
	//--------------------------------------------------------------
	void setHelpAppText(std::string text)
	{
		//if (!bUseHelpApp) setEnableHelpApp();
		setEnableHelpApp(); //force
		helpAppText = text;
		helpApp.setText(helpAppText);
		bUseHelpApp = true;
	}
	// Must be called after ui.setup();
	//--------------------------------------------------------------
	void setHelpInternalText(std::string text)
	{
		//if (!bUseHelpInternal) setEnableHelpInternal();
		setEnableHelpInternal(); //force
		helpInternalText = text;
		helpInternal.setText(helpInternalText);
		bUseHelpInternal = true;
	}

	// Useful in some rare scenarios to populate or hide the enabler toggle
	bool isHelpInternalEnable() { return bUseHelpInternal; }
	bool isHelpAppEnable() { return bUseHelpInternal; }

	// Widgets to select font
	//--------------------------------------------------------------
	void DrawHelpWidgetsFont()
	{
		if (!helpApp.bGui) return;
		string s = helpApp.bGui.getName() + "##DRAWHELPWIDGETSFONT";
		ImGui::PushID(s.c_str());
		this->DrawWidgetsFonts(helpApp.fontIndex);
		ImGui::PopID();
	}

	//--------------------------------------------------------------
	void DrawHelpInternalWidgetsFont()
	{
		if (!helpInternal.bGui) return;
		string s = helpInternal.bGui.getName() + "##DRAWHELPINTERNALWIDGETSFONT";
		ImGui::PushID(s.c_str());
		this->DrawWidgetsFonts(helpInternal.fontIndex);
		ImGui::PopID();
	}

	//--------------------------------------------------------------
	void SameLine() { ImGui::SameLine(); };

	//----

	// Exposed widgets from namespace ofxImGuiSurf from Combos.h
	//TODO: should bypass that using aliases or something else.

	//TODO: BUG: after moving into ofHelpers. broken layouts..

	// Button and toggle to be used faster, without param.

	/*
	bool AddButton(std::string label, ImVec2 sz) {
		return ofxImGuiSurfing::AddButton(label, sz);
	}
	bool AddButton(std::string label, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		return ofxImGuiSurfing::AddButton(label, type, amtPerRow, bSameLine, spacing);
	}
	bool AddToggle(std::string label, bool& bState, ImVec2 sz)
	{
		return ofxImGuiSurfing::AddToggle(label, bState, sz);
	}
	bool AddToggle(std::string label, bool& bState, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		return ofxImGuiSurfing::AddToggle(label, bState, type, amtPerRow, bSameLine, spacing);
	}
	*/

	//TODO: back here bc bug!
	//TODO: must fix:
	// Helpers to populate non ofParams,
	// Raw CPP types instead an maintain global styles.
	// To speed up populate widgets without requiring to create ofParameters first.

	//--------------------------------------------------------------
	inline bool AddButton(std::string label, ImVec2 sz)
	{
		bool bReturn = false;

		float _ww = sz.x;
		float _h = sz.y;

		bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h);

		return bReturn;
	}

	//--------------------------------------------------------------
	inline bool AddButtonRawMini(std::string label)
	{
		return ImGui::Button(label.c_str());
	}

	//--------------------------------------------------------------
	inline bool AddButtonRaw(std::string label, ImVec2 sz)
	{
		return ImGui::Button(label.c_str(), sz);
	}

	//--------------------------------------------------------------
	inline bool AddButton(std::string label, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1,
		bool bSameLine = false, int spacing = -1)
	{
		// fixes

		//--

		bool bReturn = false;

		float _h = getWidgetsHeightUnit();

		// widget width
		// we get the sizes from the canvas layout!
		float _ww = _ui.getWidgetWidthOnRowPerAmount(amtPerRow); //TODO: BUG:
		//TODO: BUG: here we don't have access to manager!
		//float _ww = ofxImGuiSurfing::getWidgetsWidth(amtPerRow);//fix

		switch (type)
		{
		case OFX_IM_DEFAULT:
		case OFX_IM_BUTTON_SMALL:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.25f);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.5f);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 2);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 3);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 4);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

			//--

			// Adding more styles

			// Border 

		case OFX_IM_BUTTON_SMALL_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.25f, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.5f, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 2, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 3, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 4, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

			//--

			// Border Blink

		case OFX_IM_BUTTON_SMALL_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h, true, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.25f, true, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.5f, true, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 2, true, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 3, true, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 4, true, true);
			if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) bReturn |= GetMouseWheel();
			break;

		default:
		{
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
	inline bool AddToggle(std::string label, bool& bState, ImVec2 sz)
	{
		bool bReturn = false;

		float _ww = sz.x;
		float _h = sz.y;

		bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h);
		if (bMouseWheel && !bDisableMouseWheelOnButtonsToggles) ofxImGuiSurfing::AddMouseWheel(bState);

		return bReturn;
	}

	////--------------------------------------------------------------
	//bool AddToggle(std::string label, bool& bState)
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
	inline bool AddToggle(std::string label, bool& bState, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1,
		bool bSameLine = false, int spacing = -1)
	{
		bool bReturn = false;

		float _h = getWidgetsHeightUnit();

		// Widget width
		// We get the sizes from the canvas layout!
		//float _ww = ofxImGuiSurfing::getWidgetsWidth(amtPerRow);//fix
		float _ww = _ui.getWidgetWidthOnRowPerAmount(amtPerRow); //original

		switch (type)
		{
		case OFX_IM_CHECKBOX:
			bReturn = ImGui::Checkbox(label.c_str(), &bState);
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_DEFAULT:
		case OFX_IM_BUTTON_SMALL:
		case OFX_IM_TOGGLE_SMALL:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h);
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_BUTTON:
		case OFX_IM_TOGGLE:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 1.25f);
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_BUTTON_MEDIUM:
		case OFX_IM_TOGGLE_MEDIUM:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 1.5f);
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_BUTTON_BIG:
		case OFX_IM_TOGGLE_BIG:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 2);
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_BUTTON_BIG_XXL:
		case OFX_IM_TOGGLE_BIG_XXL:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 3);
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_BUTTON_BIG_XXXL:
		case OFX_IM_TOGGLE_BIG_XXXL:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 4);
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

			//--

			// Rounded Toggles

		case OFX_IM_TOGGLE_ROUNDED_MINI:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState,
				ImVec2(1.15f * _h, 1.15f * (2 / 3.f) * _h));
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_TOGGLE_ROUNDED_SMALL:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState,
				ImVec2(1.35f * _h, 1.35f * (2 / 3.f) * _h));
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_TOGGLE_ROUNDED:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState);
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_TOGGLE_ROUNDED_MEDIUM:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState, ImVec2(2 * _h, 2 * (2 / 3.f) * _h));
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
			break;

		case OFX_IM_TOGGLE_ROUNDED_BIG:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState, ImVec2(2.5f * _h, 2.5f * (2 / 3.f) * _h));
			if (!bDisableMouseWheelOnButtonsToggles)
			{
				if (bMouseWheel) AddMouseWheel(bState);
				if (bMouseWheel) bReturn |= GetMouseWheel();
			}
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

	//----

	// Bundle

	// A bundle of different widgets 
	// but for a single ofParam: int or float. 
	/*
	template<typename ParameterType>
	bool AddComboBundle(ofParameter<ParameterType>& p, bool bMinimized = false) {
		return ofxImGuiSurfing::AddComboBundle(p, bMinimized);
	}
	*/
	//--------------------------------------------------------------
	template <typename ParameterType>
	bool AddComboBundle(ofParameter<ParameterType>& p, bool bMinimized = false)
	{
		std::string name = p.getName();

		bool bReturn = false;

		const auto& t = typeid(ParameterType);
		const bool isFloat = (t == typeid(float));
		const bool isInt = (t == typeid(int));

		if (!isFloat && !isInt)
		{
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
			flags += ImGuiKnobFlags_ValueTooltip; //not works
			//flags += ImGuiKnobFlags_DragHorizontal;
			bReturn += ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_DOTKNOB, w, OFX_IM_FORMAT_KNOBS, flags);

			// mouse
			if (this->bMouseWheel)
			{
				ofxImGuiSurfing::AddMouseWheel(p, this->bMouseWheelFlip.get());
				ofxImGuiSurfing::GetMouseWheel();
				ofxImGuiSurfing::AddMouseClickRightReset(p);
			}

			// tooltip
			this->AddTooltip(p, true, false);
		}

		return bReturn;
	}

	//--

	// Combos

	bool AddCombo(ofParameter<int> pIndex, std::vector<std::string> fileNames, bool bRaw = false)
	{
		return ofxImGuiSurfing::AddCombo(pIndex, fileNames, bRaw);
	}

	bool AddCombo(ofParameter<size_t> pIndex, std::vector<std::string> fileNames, bool bRaw = false)
	{
		return ofxImGuiSurfing::AddCombo(pIndex, fileNames, bRaw);
	}

	bool AddComboButton(ofParameter<int>& pIndex, std::vector<std::string>& fileNames)
	{
		return ofxImGuiSurfing::AddComboButton(pIndex, fileNames);
	}

	bool AddComboButtonDual(ofParameter<int>& pIndex, std::vector<std::string>& fileNames, bool bCycled = false)
	{
		return ofxImGuiSurfing::AddComboButtonDual(pIndex, fileNames, bCycled);
	}

	bool AddComboButtonDualLefted(ofParameter<int>& pIndex, std::vector<std::string>& fileNames, bool bCycled = false)
	{
		return ofxImGuiSurfing::AddComboButtonDualLefted(pIndex, fileNames, bCycled);
	}

	bool AddComboButtonDualCenteredNames(ofParameter<int>& pIndex, std::vector<std::string>& fileNames,
		bool bCycled = false)
	{
		return ofxImGuiSurfing::AddComboButtonDualCenteredNames(pIndex, fileNames, bCycled);
	}

	int AddComboArrows(SurfingGuiTypes style = OFX_IM_BUTTON_SMALL)
	{
		return ofxImGuiSurfing::AddComboArrows(style);
	}

	void AddComboArrows(ofParameter<int> paramIndex, SurfingGuiTypes style = OFX_IM_BUTTON_SMALL, bool cycled = false)
	{
		return ofxImGuiSurfing::AddComboArrows(paramIndex, style, cycled);
	}

	//----

	void AddComboFontsSelector(ofParameter<int>& index)
	{
		ofxImGuiSurfing::AddComboButtonDualLefted(index, namesCustomFonts);
	}

	//----

	// NOTES

	// Optional to customize filename for the settings file for multiple instances on the same ofApp.
	//ui.setSettingsFilename("3_DockingLayoutPresetsEngine"); 

	//----


	void DrawWidgetsExampleTabs();
	int active_tab = 0;

	// ImGui Helper
	//------------------------------------------------------------------------------------------
	inline bool BeginTabItem(const string& tabName)
	{
		static float a = 0.3f;
		static ImVec4 c1 = ImGui::GetStyleColorVec4(ImGuiCol_Text);
		static ImVec4 c2 = ImVec4(c1.x, c1.y, c1.z, c1.w * a);
		static string currentTab = "";
		bool isCurrent = currentTab == tabName;

		bool bSz = 0;
		if (bSz) {
			static ImVec2 sz1(30, 30);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, sz1);

			static ImVec2 sz2(0, 0);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, sz2);
		}

		if (!isCurrent)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, c2);
			//ImGui::PushStyleColor(ImGuiCol_TabActive, c2);

		}

		bool bOpen = ImGui::BeginTabItem(tabName.c_str());

		if (!isCurrent)
		{
			ImGui::PopStyleColor();
			//ImGui::PopStyleColor();
		}

		if (bSz) {
			ImGui::PopStyleVar();//sz1
			ImGui::PopStyleVar();//sz2
		}

		if (bOpen)
		{
			currentTab = tabName;
		}
		return bOpen;
	}

};


#endif
