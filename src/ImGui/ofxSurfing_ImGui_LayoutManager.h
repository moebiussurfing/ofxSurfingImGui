
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"

#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_Themes.h"
#include "ofxSurfing_Serializer.h"
#include "ofxSurfing_ImGui_ofHelpers.h"
#include "ofxSurfing_ImGui_WidgetsTypes.h"
//#include "ofxSurfing_ImGui_WidgetsTypesUniqueNames.h"

//-

using namespace ofxImGuiSurfing;

//-

//static ofxSurfing_ImGui_WidgetsTypes widgetsManager;

/* Layout Mangager Engine */
//namespace ofxImGuiSurfing
//{

//--------------------------------------------------------------
class ofxSurfing_ImGui_Manager
{

public:

	ofxSurfing_ImGui_Manager();
	~ofxSurfing_ImGui_Manager();

	//-

private:
//public:

	//static ofxSurfing_ImGui_WidgetsTypes widgetsManager;
	ofxSurfing_ImGui_WidgetsTypes widgetsManager; // -> fails bc it seems it's instantiated many times..

	//ofParamUniqueName uniqueName;

	//-

public:

	//--------------------------------------------------------------
	bool Add(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
	{
		return widgetsManager.Add(aparam, type, bSameLine, amtPerRow, spacing);
	}

	//--------------------------------------------------------------
	void AddStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
	{
		widgetsManager.AddStyle(aparam, type, bSameLine, amtPerRow, spacing);
	}

	//--------------------------------------------------------------
	void AddGroupStyle(ofParameterGroup& group, SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
	{
		widgetsManager.AddGroupStyle(group, type, flags);
	}

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT)
	{
		widgetsManager.AddGroup(group, flags, typeGroup);
	}

	//-

	//TODO:
	//ofxSurfing_ImGui_WidgetsTypes widgetsManager;

public:
	//--------------------------------------------------------------
	void refresh()
	{
		widgetsManager.refresh(); // update sizes to current window shape
	}
	//--------------------------------------------------------------
	void clear()
	{
		widgetsManager.clear(); // update sizes to current window shape
	}
	//--------------------------------------------------------------
	void reset()
	{
		widgetsManager.resetUniqueNames(); // update sizes to current window shape
	}
	//--------------------------------------------------------------
	void resetIDs()
	{
		widgetsManager.resetUniqueNames(); // update sizes to current window shape
	}

	//-

public:

	void setup(); // MODE A: ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).
	void setup(ofxImGui::Gui & gui); // MODE B: can be instantiated out of the class, locally

	//-

private:

	// initiate ofxImGui
	void setup_ImGui();
	bool bAutoDraw; // must be false when multiple ImGui instances created!

	// with have two mode for instantiate ImGui
	ofxImGui::Gui * guiPtr = NULL; // passed by reference
	ofxImGui::Gui gui; // inside the addon

	//-

public:

	void draw(); // to manual draw...

	//-

	// global
	// all the windows are feeded between
	void begin();
	void end();

	// begin a window
	void beginWindow(std::string name = "Window"); // -> simpler
	void beginWindow(ofParameter<bool> p); // will use the bool param for show/hide and the param name for the window name
	void beginWindow(ofParameter<bool> p, ImGuiWindowFlags window_flags); // will use the bool param for show/hide and the param name for the window name
	void beginWindow(std::string name, bool* p_open, ImGuiWindowFlags window_flags);

	// end a window
	void endWindow();

	//----

public:

	// Force autodraw
	//--------------------------------------------------------------
	void setImGuiAutodraw(bool b) { bAutoDraw = b; } // must be called before setup! default is false. For ImGui multi-instance.
	void setImGuiAutoResize(bool b) { bAutoResize = b; } // must be called before setup! default is false. For ImGui multi-instance.

	// Force shared context
	//--------------------------------------------------------------
	void setImGuiSharedMode(bool b) { gui.setSharedMode(b); }

	//----

	// Fonts runtime mangement 

private:

	ImFont* customFont = nullptr;
	vector<ImFont*> customFonts;

public:

	bool addFont(std::string path, int size);
	bool pushFont(std::string path, int size);

private:

	int currFont = 0;
	void processOpenFileSelection(ofFileDialogResult openFileResult, int size);
	void openFileFont(int size = 10);

public:

	void setDefaultFontIndex(int index);
	int getNumFonts() { return customFonts.size(); }

	void pushStyleFont(int index);
	void popStyleFont();

	//----

public:

	//--------------------------------------------------------------
	bool isMouseOverGui() {
		return bMouseOverGui;
	}

private:

	bool bUseAdvancedSubPanel = true; // enable advanced sub panel

	// panels minimal sizes
	float xx = 10;
	float yy = 10;
	float ww = PANEL_WIDGETS_WIDTH_MIN;
	float hh = PANEL_WIDGETS_HEIGHT_MIN;
	//float hh = 50;

	//-

	// exposed useful public params

public:

	ofParameterGroup params_Advanced{ "Advanced" };

	ofParameter<bool> bGui{ "Show Gui", true };
	ofParameter<bool> bAutoResize{ "Auto Resize", true }; // auto resize panel
	ofParameter<bool> bReset_Window{ "Reset Window", false };
	ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bAdvanced{ "Advanced", false };
	ofParameter<bool> bDebug{ "Debug", false };
	ofParameter<bool> bMinimize{ "Minimize", false };

private:

	ofParameter<bool> bMouseOverGui{ "Mouse OverGui", false }; // mouse is over gui
	//ofParameter<bool> auto_lockToBorder{ "Lock GUI", false }; // force position

	//-

//public:

	// An extra common panel with some usefull toggles:
	// auto-resize, debug mouse over gui, ...

	// snippet to copy/paste
	/*
	// EXTRA MENU
	{
		ImGui::Dummy(ImVec2(0, 5)); // spacing

		ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bExtra);
		if (guiManager.bExtra)
		{
			ImGui::Indent();

			// add your extra (hidden by default) controls
			//ofxImGuiSurfing::AddBigToggle(SHOW_Plot, _w100, _h / 2, false);

			//--

			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
			if (guiManager.bExtra) guiManager.drawAdvancedSubPanel();

			ImGui::Unindent();
		}
	}
	*/

	//-

public:

	//--------------------------------------------------------------
	void resetWindowImGui(bool pos = true, bool size = true)
	{
		float xx = 10;
		float yy = 10;
		float ww = 200;
		float hh = 600;

		//float ww = PANEL_WIDGETS_WIDTH_MIN;
		//float hh = PANEL_WIDGETS_HEIGHT;

		ImGuiCond flagsCond = ImGuiCond_Appearing;
		//flagsCond |= ImGuiCond_Appearing;
		//flagsCond |= ImGuiCond_Once;

		if (size) ImGui::SetWindowSize(ImVec2(ww, hh), flagsCond);
		if (pos)ImGui::SetWindowPos(ImVec2(xx, yy), flagsCond);
	}

	//--

public:

	// snippet to copy/paste
	//ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
	//--------------------------------------------------------------
	void drawAdvancedSubPanel(bool bHeader = true) {
		if (!bAdvanced) return;
		if (!bUseAdvancedSubPanel) return;

		//--

		//ImGui::Dummy(ImVec2(0.0f, 2.0f));

		ImGui::Indent();
		{
			bool b = false;
			if (bHeader) b = ImGui::CollapsingHeader(params_Advanced.getName().c_str(), ImGuiTreeNodeFlags_None);
			if (!bHeader || (bHeader && b))
			{
				// reset window
				if (ofxImGuiSurfing::AddToggleRoundedButton(bReset_Window)) {
					if (bReset_Window) {
						bReset_Window = false;
						resetWindowImGui(false, true);
					}
				}

				ofxImGuiSurfing::AddToggleRoundedButton(bAutoResize);
				ofxImGuiSurfing::AddToggleRoundedButton(bDebug);
				ofxImGuiSurfing::AddToggleRoundedButton(bMouseOverGui);
			}
		}
		ImGui::Unindent();

		//ofxImGuiSurfing::refreshImGui_WidgetsSizes();//fails
		// this is full width (_w100) with standard height (_h)
		//float _w;
		//float _h;
		//_w = ofxImGuiSurfing::getWidgetsWidth(1);
		//_h = ofxImGuiSurfing::getWidgetsHeight(-1);
		//ofxImGuiSurfing::AddBigToggle(bAutoResize, _w, _h / 2);
		//ofxImGuiSurfing::AddBigToggle(bExtra, _w, _h / 2);
		//ofxImGuiSurfing::AddBigToggle(bMouseOverGui, _w, _h / 2);
	}

	//--------------------------------------------------------------
	void setUseAdvancedSubPanel(bool b) {
		bUseAdvancedSubPanel = b;
	}

	//-

private:

	// settings
	string path_Settings = "imgui_SurfingLayout.xml";
	ofParameterGroup params_AppSettings{ "ofxSurfing_ImGui_LayoutManager" };
	bool bAutoSaveSettings = false;

	//-

public:

	//--------------------------------------------------------------
	void setAutoSaveSettings(bool b) { // must call before setup
		bAutoSaveSettings = b;
	}
};

//} // namespace ofxImGuiSurfing