
//TODO:
// Testing central view-port
//#define FIXING_DOCKING		// -> Need to fix yet
#define FIXING_DRAW_VIEWPORT	// -> To debug free space

//-

#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_Themes.h"
#include "ofxSurfing_ImGui_ofHelpers.h"
#include "ofxSurfing_ImGui_WidgetsTypes.h"
#include "ofxSurfing_Serializer.h"
#include "ofxSurfing_ImGui_WindowsOrganizer.h"
#include "TextBoxWidget.h"

#define OFX_IMGUI_CONSTRAIT_WINDOW_SHAPE // -> Constraint some window minimal shape sizes.

#define DEFAULT_AMOUNT_PRESETS 4

//--

using namespace ofxImGuiSurfing;

//TODO:
// These arguments are to pass to setup(..) method 
// to simplify instantiation and define settings.
//--------------------------------------------------------------
namespace ofxImGuiSurfing
{
	// Argument to be used on setup(mode);
	enum SurfingImGuiInstantiationMode
	{
		IM_GUI_MODE_UNKNOWN = 0, // -> Could be undefied when using legacy api maybe.

		IM_GUI_MODE_INSTANTIATED, // -> To include the ImGui context and requiring main begin/end.

		//TODO: should rename or add presets engine + docking
		IM_GUI_MODE_INSTANTIATED_DOCKING, // -> Allows docking between multiple instances.

		IM_GUI_MODE_INSTANTIATED_SINGLE, // -> To include the ImGui context and requiring begin/end but a single ImGui instance, no other add-ons.

		//IM_GUI_MODE_SPECIAL_WINDOWS, // TODO: could simplify API, bc it's duplicated from 
		//guiManager.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

		IM_GUI_MODE_REFERENCED, // TODO: -> To receive the parent (ofApp scope) ImGui object as reference.

		IM_GUI_MODE_NOT_INSTANTIATED // -> To render windows and widgets only. Inside an external ImGui context begin/end (newFrame).
	};

	//--

	// To enable Special windows mode.
	// Then handles Organizer and Align windows.
	enum SurfingImGuiWindowsMode
	{
		IM_GUI_MODE_WINDOWS_SPECIAL_UNKNOWN = 0,
		IM_GUI_MODE_WINDOWS_SPECIAL_DISABLED,
		IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER
	};
}

//--------

//--------------------------------------------------------------
class ofxSurfing_ImGui_Manager
{

public:

	ofxSurfing_ImGui_Manager();
	~ofxSurfing_ImGui_Manager();

	//--

public:

	//--------------------------------------------------------------
	void setup() // -> We will use the most common use to avoid to have to require any argument.
	{
		setup(IM_GUI_MODE_INSTANTIATED);
	}

	void setup(ofxImGuiSurfing::SurfingImGuiInstantiationMode mode);

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

	ofxSurfing_ImGui_WidgetsTypes widgetsManager;

	//----

	// Styles API

public:

	// ofParameters 

	// Draw styled parameter into ImGui manager
	//--------------------------------------------------------------
	bool Add(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		return widgetsManager.Add(aparam, type, amtPerRow, bSameLine, spacing);
	}

	//----

	// Queue style for the parameter
	//--------------------------------------------------------------
	void AddStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		widgetsManager.AddStyle(aparam, type, amtPerRow, bSameLine, spacing);
	}

	// Queue style for the parameter
	//--------------------------------------------------------------
	void AddStyle(std::string name, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		widgetsManager.AddStyle(name, type, amtPerRow, bSameLine, spacing);
	}

	// Update style for the parameter
	//--------------------------------------------------------------
	void UpdateStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		widgetsManager.UpdateStyle(aparam, type, amtPerRow, bSameLine, spacing);
	}

	//--

public:

	// ofParametersGroup's 

	//--------------------------------------------------------------
	void AddStyleGroup(ofParameterGroup& group, SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		widgetsManager.AddStyleGroup(group, type, flags);
	}
	//--------------------------------------------------------------
	void AddStyleGroup(std::string name, SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		widgetsManager.AddStyleGroup(name, type, flags);
	}

	//TODO:
	//--------------------------------------------------------------
	void AddStyleGroup(ofParameterGroup& group, SurfingImGuiGroupStyle flags)
	{
		SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		if (flags & ofxImGuiSurfing::SurfingImGuiGroupStyle_Hidden)
		{
			//type = OFX_IM_GROUP_HIDDEN;
			//widgetsManager.AddStyleGroup(group, type, flagst);
			return;
		}

		if (flags & ofxImGuiSurfing::SurfingImGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			widgetsManager.AddStyleGroup(group, type, flagst);
			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingImGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingImGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			widgetsManager.AddStyleGroup(group, type, flagst);
			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingImGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE_EX;
			widgetsManager.AddStyleGroup(group, type, flagst);
			return;
		}

		widgetsManager.AddStyleGroup(group, type, flagst);
	}

	//--

	//TODO:
	// Helper to auto populate the styles of each type (bool, floats, ints) contained on a group.
	//--------------------------------------------------------------
	void AddStyleGroupForBools(ofParameterGroup& group, SurfingImGuiTypes type = OFX_IM_TOGGLE)
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
	void AddStyleGroupForFloats(ofParameterGroup& group, SurfingImGuiTypes type = OFX_IM_HSLIDER)
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
	void AddStyleGroupForInts(ofParameterGroup& group, SurfingImGuiTypes type = OFX_IM_HSLIDER)
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

	//-

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
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags, SurfingImGuiTypesGroups typeGroup, ImGuiCond cond = ImGuiCond_Once)
	{
		widgetsManager.AddGroup(group, flags, typeGroup, cond);
	}

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& group, bool bOpen, ImGuiCond cond = ImGuiCond_None)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
		if (bOpen) flags = ImGuiTreeNodeFlags_DefaultOpen;
		SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT;

		widgetsManager.AddGroup(group, flags, typeGroup, cond);
	}

	//TODO:
	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& group, SurfingImGuiGroupStyle flags = SurfingImGuiGroupStyle_None)
	{
		SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
		ImGuiTreeNodeFlags flagst = ImGuiTreeNodeFlags_None;

		//TODO:
		//if (flags & ImGuiKnobFlags_ValueTooltip &&

		if (flags & ofxImGuiSurfing::SurfingImGuiGroupStyle_None)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			widgetsManager.AddGroup(group, flagst, type);

			return;
		}

		if (flags & ofxImGuiSurfing::SurfingImGuiGroupStyle_Hidden)
		{
			type = OFX_IM_GROUP_HIDDEN;
			widgetsManager.AddGroup(group, flagst, type);

			return;
		}

		if (flags & ofxImGuiSurfing::SurfingImGuiGroupStyle_NoHeader)
		{
			type = OFX_IM_GROUP_HIDDEN_HEADER;
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
			widgetsManager.AddGroup(group, flagst, type);

			return;
		}

		if (flags & !ofxImGuiSurfing::SurfingImGuiGroupStyle_Collapsed)
		{
			flagst = ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (flags & ofxImGuiSurfing::SurfingImGuiGroupStyle_HeaderSmall)
		{
			type = OFX_IM_GROUP_TREE;
			widgetsManager.AddGroup(group, flagst, type);

			return;
		}
		if (flags & !ofxImGuiSurfing::SurfingImGuiGroupStyle_HeaderSmall)
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
	void AddGroupWindowed(ofParameterGroup& group, ImGuiTreeNodeFlags flags, SurfingImGuiTypesGroups typeGroup)
	{
		if (bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (this->beginWindow((string)group.getName(), NULL, flags))
		{
			widgetsManager.AddGroup(group, flags, typeGroup);

			this->endWindow();
		}
	}
	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& group, ofParameter<bool>& _bGui, ImGuiTreeNodeFlags flags, SurfingImGuiTypesGroups typeGroup)
	{
		if (!_bGui) return;

		if (bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

		//if (this->beginWindow((string)group.getName(), _bGui, flags))
		if (this->beginWindow((string)_bGui.getName(), _bGui, flags))
		{
			widgetsManager.AddGroup(group, flags, typeGroup);

			this->endWindow();
		}
	}

	//TODO: API update
	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& group, ofParameter<bool>& _bGui, SurfingImGuiGroupStyle flags = SurfingImGuiGroupStyle_None)
	{
		if (!_bGui) return;

		ImGuiWindowFlags f = ImGuiWindowFlags_None;
		if (bAutoResize) f |= ImGuiWindowFlags_AlwaysAutoResize;

		if (this->beginWindow((string)_bGui.getName(), _bGui, flags))
		{
			this->AddGroup(group, flags);
			//widgetsManager.AddGroup(group, flags);

			this->endWindow();
		}
	}
	//--------------------------------------------------------------
	void AddGroupWindowed(ofParameterGroup& group, SurfingImGuiGroupStyle flags = SurfingImGuiGroupStyle_None)
	{
		ImGuiWindowFlags f = ImGuiWindowFlags_None;
		if (bAutoResize) f |= ImGuiWindowFlags_AlwaysAutoResize;

		if (this->beginWindow((string)group.getName(), NULL, f))
		{
			this->AddGroup(group, flags);
			//widgetsManager.AddGroup(group, flags);

			this->endWindow();
		}
	}

	//----

	// More Widgets

	// Combo list. 

	// Selector index directly with an int ofParam
	// without name label
	//--------------------------------------------------------------
	bool AddCombo(ofParameter<int> pIndex, std::vector<std::string> fileNames)
	{
		if (fileNames.empty()) return false;

		int i = pIndex.get();
		bool b = (ofxImGuiSurfing::VectorCombo(" ", &i, fileNames));
		if (b) {
			i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
			pIndex.set(i);
			ofLogNotice(__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
		}

		ImGui::Spacing();

		return b;
	}

	//----

	// Text with Uppercasing and Spacing

	//--------------------------------------------------------------
	void AddLabel(std::string label, bool bUppercase = true, bool bNoSpacing = false)
	{
		std::string t = bUppercase ? ofToUpper(label) : label;
		if (!bNoSpacing) ofxImGuiSurfing::AddSpacing();
		ImGui::TextWrapped(t.c_str());
		if (!bNoSpacing) ofxImGuiSurfing::AddSpacing();
	}
	//--------------------------------------------------------------
	void AddLabelBig(std::string label, bool bUppercase = true, bool bNoSpacing = false)
	{
		std::string t = bUppercase ? ofToUpper(label) : label;
		if (!bNoSpacing) ofxImGuiSurfing::AddSpacing();
		pushStyleFont(1);
		ImGui::TextWrapped(t.c_str());
		popStyleFont();
		if (!bNoSpacing) ofxImGuiSurfing::AddSpacing();
	}
	//--------------------------------------------------------------
	void AddLabelHuge(std::string label, bool bUppercase = true, bool bNoSpacing = false)
	{
		std::string t = bUppercase ? ofToUpper(label) : label;
		if (!bNoSpacing) ofxImGuiSurfing::AddSpacing();
		pushStyleFont(2);
		ImGui::TextWrapped(t.c_str());
		popStyleFont();
		if (!bNoSpacing) ofxImGuiSurfing::AddSpacing();
	}

	//--

	// Simplified Text without Uppercasing not Spacing

	//--------------------------------------------------------------
	void AddText(std::string label)
	{
		AddLabel(label, false, true);
	}
	//--------------------------------------------------------------
	void AddTextBig(std::string label)
	{
		AddLabelBig(label, false, true);
	}
	//--------------------------------------------------------------
	void AddTextHuge(std::string label)
	{
		AddLabelHuge(label, false, true);
	}

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

	//----

private:

	// Special Windows Mode

	SurfingImGuiWindowsMode specialsWindowsMode = IM_GUI_MODE_WINDOWS_SPECIAL_UNKNOWN;

public:

	//--------------------------------------------------------------
	void setWindowsMode(SurfingImGuiWindowsMode mode) { // Call before setup.
		specialsWindowsMode = mode;
	}

private:

	// Instantiation

	SurfingImGuiInstantiationMode surfingImGuiMode = IM_GUI_MODE_UNKNOWN;

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

	// -> 1. Main BEGIN feed widgets!
	void begin();

	// -> 2. Main END feed widgets!
	void end();

	//----

	// Window methods

	// -> 1. BEGINs a Window

	bool beginWindow(ofParameter<bool>& p);
	// will use the bool param for show/hide
	// and the param name for the window name

	bool beginWindow(std::string name, ofParameter<bool>& p);
	//  to change the name, and not use the param name.

	bool beginWindow(std::string name, ofParameter<bool>& p, ImGuiWindowFlags window_flags);

	bool beginWindow(ofParameter<bool>& p, ImGuiWindowFlags window_flags);
	// will use the bool param for show/hide and the param name for the window name

	bool beginWindow(std::string name, bool* p_open, ImGuiWindowFlags window_flags);
	bool beginWindow(std::string name, bool* p_open);
	bool beginWindow(std::string name);
	bool beginWindow(char* name = "Window");

	//--

	// -> 2. ENDs a Window

	void endWindow();

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
	void pushStyleFont(int index);//Take care not pushing a non existing index or it will crash!
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

	ofParameter<bool> bDrawView1{ "Draw View 1", false }; // debug drawing central zone for docking help

	bool bUseAdvancedSubPanel = true; // enable advanced sub panel

	//-

	// Exposed useful public params:

public:

	ofParameter<bool> bGui{ "Show Gui", true };
	ofParameter<bool> bGui_WindowsAlignHelpers{ "ALIGNERS", false };
	ofParameter<bool> bMinimize{ "Minimize", true };
	ofParameter<bool> bAutoResize{ "Auto Resize", true };
	ofParameter<bool> bKeys{ "Keys", true };
	ofParameter<bool> bHelp{ "Help App", false };
	ofParameter<bool> bHelpInternal{ "Help Internal", false };
	ofParameter<bool> bDebug{ "Debug", false };
	ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bAdvanced{ "Advanced", false };
	ofParameter<bool> bReset{ "Reset", false };
	ofParameter<bool> bMouseWheel{ "MouseWheel", true };

	ofParameter<bool> bLockMove{ "Lock Move", false };//TODO:
	ofParameter<bool> bReset_Window{ "Reset Window", false };//TODO:
	ofParameter<bool> bNoScroll{ "No Scroll", false };//TODO:
	ofParameter<bool> bLandscape{ "Orientation", false };//TODO:could add a trigger to flip orientation

	ofParameterGroup params_Advanced{ "Params Advanced" };
	// -> These params are saved too on settings when exit and loaded when reopen the App. 

private:

	void buildHelpInfo();//create or freshed the help info for the drawing help box

	//--

	// Rectangles to handle main window sections 

	// Positions and shape, bc we disable the ImGui management, 
	// to exclude storing on presets and imgui.ini!

private:

	ofParameterGroup params_RectPanels{ "Rectangles Windows" };
	vector<ofParameter<ofRectangle>> rectangles_Windows;

	ofParameter<ofRectangle> rect0_Presets{ "rect_Presets", ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080) };
	ofParameter<ofRectangle> rect1_Panels{ "rect_Panels", ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080) };
	ofParameter<ofRectangle> rect2_Manager{ "rect_Manager", ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080) };

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
	//ofParameter<bool> bMinimizePanels{ "Minimize", true };

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
		float xx = 10;
		float yy = 10;

		float ww = 200;
		float hh = 600;

		//float ww = PANEL_WIDGETS_WIDTH_MIN;
		//float hh = PANEL_WIDGETS_HEIGHT;

		ImGuiCond flagsCond = ImGuiCond_Always;
		//ImGuiCond flagsCond = ImGuiCond_Appearing;
		//flagsCond |= ImGuiCond_Appearing;
		//flagsCond |= ImGuiCond_Once;

		if (size) ImGui::SetWindowSize(ImVec2(ww, hh), flagsCond);
		if (pos) ImGui::SetWindowPos(ImVec2(xx, yy), flagsCond);
	}

	//----

	// Log Window

public:

	// Window Log
	ImGuiLogWindow log;//public to allow acces from parent scope/ofApp

	//--------------------------------------------------------------
	void drawLogPanel() {
		if (bLog) log.ImGui(bLog);
	}

	// Legacy API
	//--------------------------------------------------------------
	void addLog(std::string text)//print message to log window
	{
		// Log
		log.AddText(text);
	}

public:

	//--------------------------------------------------------------
	void printToLog(std::string text)//print message to log window
	{
		addLog(text);
	}
	//// Legacy API
	////--------------------------------------------------------------
	//void logAdd(std::string text) {
	//	addLog(text);
	//}
	////--------------------------------------------------------------
	//void AddLog(std::string text) {
	//	addLog(text);
	//}

	//----

	// Advanced Window

private:

	// An advanced/extra common panel
	// with some bool toggles commonly used.

	// Example:
	// Snippet to copy/paste into out ofApp:
	//ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
	//guiManager.drawAdvancedSubPanel();

	//--------------------------------------------------------------
	void drawAdvancedControls() {
		drawAdvancedBundle();
	}

public:

	// Example:
	// Snippet to copy/paste into out ofApp:
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;;
	//if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//if (guiManager.bLockMove) window_flags |= ImGuiWindowFlags_NoMove;
	//guiManager.beginWindow("ofApp", NULL, window_flags);

	//--------------------------------------------------------------
	void drawAdvancedBundle(bool bNoSperator = false, bool bNoSpacing = false) { // -> Simpler call. Use this.

		if (bMinimize) return;

		if (!bNoSpacing) ImGui::Spacing();
		if (!bNoSperator) ImGui::Separator();
		ImGui::Spacing();

		this->Add(bAdvanced, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);

		drawAdvancedSubPanel();
	}

	// Legacy API
	//--------------------------------------------------------------
	void drawAdvanced(bool bNoSperator = false, bool bNoSpacing = false) {
		drawAdvancedBundle(bNoSperator, bNoSpacing);
	}

	//--

private:

	//--------------------------------------------------------------
	void drawAdvancedSubPanel(bool bHeader = true)
	{
		if (!bAdvanced) return;
		if (!bUseAdvancedSubPanel) return;

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
			if (bUseHelpInfoApp) this->Add(bHelp, OFX_IM_TOGGLE_ROUNDED);
			//hide if it's not settled by the user from ofApp!

			// Help Internal
			this->Add(bHelpInternal, OFX_IM_TOGGLE_ROUNDED);

			// Menu
			Add(bMenu, OFX_IM_TOGGLE_ROUNDED);

			// Log
			Add(bLog, OFX_IM_TOGGLE_ROUNDED);

			// Main Reset
			// that can be linked using a pointer to an external trigger!
			// Example: guiManager.setReset(&bResetDocking);
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

				if (ImGui::TreeNode("Layouts"))
				{
					this->refreshLayout();
					Add(bAutoResize_PresetsWindows, OFX_IM_TOGGLE_ROUNDED_SMALL);
					Add(bReset_PresetsWindow, OFX_IM_BUTTON_SMALL);

					ImGui::TreePop();
				}

				//--

				// Window Panels 

				if (ImGui::TreeNode("Panels"))
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

			ofxImGuiSurfing::AddSpacingSeparated();

			// Extra
			Add(bExtra, OFX_IM_TOGGLE_ROUNDED);
			if (bExtra)
			{
				//--

				if (!bHeader || (bHeader && b))
				{
					// Windows
					ofxImGuiSurfing::AddSpacing();

					if (ImGui::TreeNode("MORE"))
					{
						this->Indent();
						
						ofxImGuiSurfing::AddSpacing();

						/*
						// Align Helpers
						Add(bGui_WindowsAlignHelpers, OFX_IM_TOGGLE_ROUNDED);

						// Organizer Special Windows
						if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER) {
							Add(windowsSpecialsOrganizer.bGui_WindowsSpecials, OFX_IM_TOGGLE_ROUNDED);
						}
						*/

						// Auto resize
						Add(bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);

						// MouseWheel
						this->Add(bMouseWheel, OFX_IM_TOGGLE_ROUNDED_MINI);
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

					ofxImGuiSurfing::AddSpacing();

					//--

					// Gui
					ofxImGuiSurfing::AddSpacing();

					if (ImGui::TreeNode("GUI"))
					{
						this->Indent();

						ofxImGuiSurfing::AddSpacing();

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

							Add(bInputText, OFX_IM_TOGGLE_ROUNDED_MINI);
							Add(bMouseOverGui, OFX_IM_TOGGLE_ROUNDED_MINI);

							//AddToggleRoundedButton(bDrawView1);

							//-

							ofxImGuiSurfing::AddSpacing();
							ofxImGuiSurfing::AddSpacing();

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
					ofxImGuiSurfing::AddSpacing();

					if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING)
					{
						ofxImGuiSurfing::AddSpacing();

						if (ImGui::TreeNode("DOCKING"))
						{
							this->Indent();
							
							ofxImGuiSurfing::AddSpacing();

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

	std::string path_SubPathLabel = "";

	ofParameterGroup params_AppSettings{ "guiManager" }; // -> Features states
	//ofParameterGroup params_AppSettings{ "AppSettings" }; // -> Features states
	ofParameterGroup params_AppSettingsLayout{ "LayoutSettings" }; // -> Layout states

	//----

public:

	// Some tweaked settings modes

	// New API
	//--------------------------------------------------------------
	void setName(std::string name) { // must call before setup. To allow multiple instances/windows settings
		path_SubPathLabel = "_" + name;
		windowsSpecialsOrganizer.setName(name);
	}

private: // hide to simplify

	//--------------------------------------------------------------
	void setSettingsFilename(std::string path) { // must call before setup. To allow multiple instances/windows settings
		path_SubPathLabel = path + "_";
	}

	////--------------------------------------------------------------
	//void setSettingsPathLabel(std::string path) { // must call before setup. To allow multiple instances/windows settings
	//	path_SubPathLabel = "_" + path;
	//}

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

	// Special Windows Management

private:

	//TODO:
	// To simplify a bit more the API workflow.
	// Allows to omit the index argument on begin a window...
	int _indexWindowsSpecials = 0;

	std::string nameWindowSpecialsPanel = "";

	//--

public:

	// Main Important 
	// API methods to populate widgets in between,
	// inside previously queued Special Windows!
	// to be called on DrawImGui()

	// Begin

	bool beginWindowSpecial();

	bool beginWindowSpecial(int index);
	// -> If you added windows to the engine you can begin the window passing his index

	bool beginWindowSpecial(string name);
	// -> If you added windows to the engine you can begin the window passing his SAME name.

	bool beginWindowSpecial(ofParameter<bool>& _bGui);

	//-

	// End

	void endWindowSpecial(int index = -1);
	void endWindowSpecial(ofParameter<bool>& _bGui);

	//--

	// Rarely useful Helpers

	int getWindowSpecialIndexForToggle(ofParameter<bool>& _bGui);
	//to get the index of an special window passing the toggle

	int getWindowSpecialIndexForName(string name);
	//to be used if you forgot or don't know the index

	//----

	// Organizer Special Windows

	//--------------------------------------------------------------
	void setNameWindowsSpecialsOrganizer(std::string name) // Just optional to customize name.
	{
		nameWindowSpecialsPanel = name;
		windowsSpecialsOrganizer.bGui_WindowsSpecials.setName(name);
	}

	//--------------------------------------------------------------
	void drawWindowsSpecialsOrganizer() // Draws the main panel controller.
	{
		IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;

		if (beginWindow(windowsSpecialsOrganizer.bGui_WindowsSpecials))
		{
			Add(bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED);
			AddSpacing();

			windowsSpecialsOrganizer.drawWidgetsOrganizer(bMinimize);

			endWindow();
		}
	}

	//--------------------------------------------------------------
	void drawWindowsAlignHelpers()
	{
		IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;

		if (beginWindow(bGui_WindowsAlignHelpers))
		{
			Add(bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED);
			AddSpacing();

			windowsSpecialsOrganizer.drawWidgetsAlignHelpers(bMinimize);

			if (!bMinimize) {
				AddSpacing();
				ofxImGuiSurfing::AddStepperInt(windowsSpecialsOrganizer.pad);
			}

			endWindow();
		}
	}

	//--------------------------------------------------------------
	bool getWindowsSpecialEnableGlobal() {
		return windowsSpecialsOrganizer.bGui_ShowAll.get();
	}
	//--------------------------------------------------------------
	bool getWindowSpecialVisibleGlobalState() const {
		return windowsSpecialsOrganizer.bGui_ShowAll.get();
	}

	//--

	//TODO: WIP
	//--------------------------------------------------------------
	struct SurfingImGuiWindowAtributes
	{
		// We queue here the bool params that enables the show/hide for each queued window
		ofParameter<bool> bGui{ "_bGui", true };

		////TODO: could be removed...not used..
		//ofParameter<bool> bAutoResize{ "Auto Resize", true };
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

	vector<SurfingImGuiWindowAtributes> windowsSpecialsLayouts;
	// Handles only the manually pre added special windows.

	//----

	// Windows Special Engine

private:

	WindowPanels windowsSpecialsOrganizer;

public:

	int getPad() { return windowsSpecialsOrganizer.pad; }//used pad between windows

public:

	//--------------------------------------------------------------
	void setNameWindowsSpecialsEnableGlobal(std::string name) {
		windowsSpecialsOrganizer.setNameWindowsSpecialsEnableGlobal(name);
	}

	////--------------------------------------------------------------
	//void setName(std::string name) {
	//	windowsSpecialsOrganizer.setName(name);
	//}

public:

	//--------------------------------------------------------------
	void clearWindowsSpecial() {
		windowsSpecialsLayouts.clear();
	}

	//--------------------------------------------------------------
	void addWindowSpecial(ofParameter<bool>& _bGui, bool bMaster = false) {

		SurfingImGuiWindowAtributes win;
		win.bGui.makeReferenceTo(_bGui);
		win.setMasterAnchor(bMaster);

		windowsSpecialsLayouts.push_back(win);

		params_WindowSpecials.add(_bGui);

		if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		{
			windowsSpecialsOrganizer.add(_bGui);
		}
	}

	//--------------------------------------------------------------
	void addWindowSpecial(std::string name, bool bPowered = false) {
		ofParameter<bool> _bGui{ name, true };

		SurfingImGuiWindowAtributes win;
		win.bGui.makeReferenceTo(_bGui);
		win.setMasterAnchor(bPowered);

		windowsSpecialsLayouts.push_back(win);

		params_WindowSpecials.add(_bGui);
		bWindowSpecials.push_back(_bGui);

		if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		{
			windowsSpecialsOrganizer.add(_bGui);
		}
	}

	//--------------------------------------------------------------
	std::string getWindowSpecialName(int index) {
		if (index > windowsSpecialsLayouts.size() - 1 || index == -1)
		{
			ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;

			return "-1";
		}

		return windowsSpecialsLayouts[index].bGui.getName();
	}

	////--------------------------------------------------------------
	//ofRectangle getRectangleWindowSpecial(int index) {
	//	if (index > windowsSpecialsLayouts.size() - 1 || index == -1)
	//	{
	//		ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
	//	}
	//	return windowsSpecialsLayouts[index].rectShapeWindow;
	//}

	////--------------------------------------------------------------
	//void addWindow(std::string name, bool bPowered = false) { // -> legacy api
	//	addWindowSpecial(name, bPowered);
	//}

	//--------------------------------------------------------------
	void initiatieSpecialWindowsOrganizer()
	{
		windowsSpecialsOrganizer.setPath(path_Global);

		windowsSpecialsOrganizer.setupInitiate();

		//windowsSpecialsOrganizer.bLinkedWindowsSpecial.set(true);//force
	}

	//--

	// Exposed helpers to external GUIs / scope.

	//--------------------------------------------------------------
	ofParameter<bool>& getWindowsSpecialEnablerLinker() { // toggle to enable or disable
		return windowsSpecialsOrganizer.bLinkedWindowsSpecial;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getWindowsSpecialsGuiToggle() { // main toggle to show the panel
		return windowsSpecialsOrganizer.bGui_WindowsSpecials;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getWindowsSpecialsGuiToggleAllGlobal() { // global toggle to show/hide the all panels
		return windowsSpecialsOrganizer.bGui_ShowAll;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getWindowsAlignHelpersGuiToggle() { // align windows toggle to show the panel
		return bGui_WindowsAlignHelpers;
	}

	// New API alias
	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleAlignHelpers() { // align windows toggle to show the panel
		return bGui_WindowsAlignHelpers;
	}
	//--------------------------------------------------------------
	ofParameter<bool>& getGuiToggleOrganizer() { // organizer window for special windows only! Required to add. See the examples.
		return windowsSpecialsOrganizer.bGui_WindowsSpecials;
	}

	//----

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
		// can't be setted to ImGuiCond_Always bc will feedback/apply with the same window!

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
		int _pad = windowsSpecialsOrganizer.pad;

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

				//TODO: BUG: we don't know the width of next window...
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
	string getWindowSpecialLast() const {
		return windowsSpecialsOrganizer.getWindowSpecialLast();
	}

	//// Orientation cascade windows
	////--------------------------------------------------------------
	//void setSpecialWindowsOrganizerOrientationHorizontal() {
	//	windowsSpecialsOrganizer.bOrientation.set(false);
	//}

	////--------------------------------------------------------------
	//void setSpecialWindowsOrganizerOrientationVertical() {
	//	windowsSpecialsOrganizer.bOrientation.set(true);
	//}

	////--------------------------------------------------------------
	//void setToggleSpecialWindowsOrganizerOrientation() {
	//	windowsSpecialsOrganizer.bOrientation.set(!windowsSpecialsOrganizer.bOrientation.get());
	//}

	//--

	//--------------------------------------------------------------
	float getWidgetsWidth(int amnt) {
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
		if (windowsSpecialsLayouts.size() == 0) return false;
		else if (index > windowsSpecialsLayouts.size() - 1 || index == -1) return false;
		else return windowsSpecialsLayouts[index].bGui.get();
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getWindowSpecialVisible(int index) // return bool parameter visible toggle
	{
		if (index > windowsSpecialsLayouts.size() - 1 || index == -1)
		{
			ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
			ofParameter<bool> b = ofParameter<bool>{ "-1", false };
			return b;
		}

		return windowsSpecialsLayouts[index].bGui;
	}

	// Easy populate all the Special Windows toggles. Call inside a window.
	//--------------------------------------------------------------
	void drawWindowSpecialsGuiToggles() {
		for (size_t i = 0; i < windowsSpecialsLayouts.size(); i++)
		{
			Add(getWindowSpecialGuiToggle(i), OFX_IM_TOGGLE_ROUNDED_MEDIUM);
		}
	}

	//--------------------------------------------------------------
	void setWindowSpecialToggleVisibleAllGlobal()
	{
		windowsSpecialsOrganizer.bGui_ShowAll = !windowsSpecialsOrganizer.bGui_ShowAll;
	}

	//--------------------------------------------------------------
	void setWindowSpecialToggleVisible(int index)
	{
		if (index > windowsSpecialsLayouts.size() - 1 || index == -1)
		{
			ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;

			return;
		}

		windowsSpecialsLayouts[index].bGui = !windowsSpecialsLayouts[index].bGui;
	}

	//----

private:

	bool loadAppSettings();//we store some internal stuff	
	// Will return false if settings file do not exist.
	// That happens when started for first time or after OF_APP/bin cleaning
	// Then we can reset to some default variables and layout positions of our windows.

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

	void beginDocking();
	void endDocking();

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

	//void Changed_Params_Enablers(ofAbstractParameter& e);

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
			ofLogError(__FUNCTION__) << "Names sizes are not equals to 4";
		}

		namesPresets.clear();
		namesPresets = names;
	}

private:

	vector <std::string> namesPresets;

public:

	//-> Must call manually after adding windows and layout presets
	void setupLayout(int numPresets = DEFAULT_AMOUNT_PRESETS);

	// Some API simplifications 
	//--------------------------------------------------------------
	void startup();

	//-

private:

	bool bStartupCalled = false;

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
	//ofParameter<bool> bModeFree{ "Free", true }; // -> A allows storing position for control windows too
	//ofParameter<bool> bModeForced{ "Forced", false }; // -> Locked to free space on viewport
	//ofParameter<bool> bModeLock1{ "Lock B", false }; // -> Cant be moved. To be used in presets panel
	//ofParameter<bool> bModeLockControls{ "Lock C", false }; // -> Cant be moved. To be used to lock to free viewport scenarios
	//ofParameter<bool> bModeLockPreset{ "Lock A", false }; // -> Cant be moved. To be used to lock to free viewport scenarios

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
	void setLabelLayoutPanels(std::string label) { // -> Customize the app name for panels window label tittle
		bGui_LayoutsPanels.setName(label);
	}
	//--------------------------------------------------------------
	void setLabelLayoutMainWindow(std::string label) {
		bGui_LayoutsManager.setName(label);
	}

	//-

public:

	ofParameter<bool> bMenu{ "Menu", false };

	ofParameter <bool> bLinkWindows{ "Link Windows", true };//align windows engine. liked to the internal aligner.

private:

	ofParameter<bool> bGui_LayoutsPanels{ "Panels", true };
	ofParameter<bool> bGui_LayoutsPresetsSelector{ "Layouts", true };
	ofParameter<bool> bGui_LayoutsManager{ "Manager", false };

	ofParameter<bool> bAutoSave_Layout{ "Auto Save", true };
	ofParameter<bool> bUseLayoutPresetsManager{ "Layout Engine", false };
	// Can't be changed on runtime. cant include into settings

	ofParameter<bool> bDockingLayoutPresetsEngine{ "Dock Engine", false };

	ofParameter<bool> bSolo{ "Solo", false };

public:

	ofParameter<bool> bLog{ "Log", false };//show log window

	//-

private:

	ofParameterGroup params_LayoutPresetsStates{ "LayoutPanels" };

	ofParameterGroup params_WindowSpecials{ "_WindowSpecials" };//to store the gui show toggles for each window

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
	// -> Subscribe an optional reset flagging a bool to true to reset. Uses the gui Reset button on the Presets Extra panel.

private:

	bool* bResetPtr = nullptr;

public:

	//--------------------------------------------------------------
	void setReset(bool* b) {//link to an axternal / parent scope bool to assing to the internal reset button.
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
		for (int i = 0; i < windowsSpecialsLayouts.size(); i++)
		{
			windowsSpecialsLayouts[i].bGui.set(b);
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
		if (index >= windowsSpecialsLayouts.size()) return;//ignore
		windowsSpecialsLayouts[index].bGui = !windowsSpecialsLayouts[index].bGui;
	}

	//--

private:

	// We have to independent help boxes.
	// One is intended to be use as the add-on itself help (Internal Help),
	// and another to be used as an external help (App Help).
	// Can be initialized from outer scope.

	// Help Internal: How to use the add-on itself
	std::string helpInfo = "";
	TextBoxWidget textBoxWidgetInternal;

	// Help App: How to use our App 
	std::string helpInfoApp = "";
	TextBoxWidget textBoxWidgetApp;

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
		textBoxWidgetApp.setText(helpInfoApp);
		bUseHelpInfoApp = true;
	}

	//--------------------------------------------------------------
	void setHelpInfoInternal(string text) {
		helpInfo = text;
		textBoxWidgetInternal.setText(helpInfo);
		bUseHelpInfoInternal = true;
	}

	//----

	// NOTES

	// -> Optional to customize filename for the settings file for multiple instances on the same ofApp.
	//guiManager.setSettingsFilename("3_DockingLayoutPresetsEngine"); 

	//----


public:

	// Helpers to populate non ofParams,
	// CPP types instead an mantain global styles.
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
	bool AddButton(string label, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
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
		}

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