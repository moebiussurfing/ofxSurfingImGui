#pragma once

#include "ofMain.h"

#include "ofxImGui.h"

#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_ofHelpers.h"

#include "ofxSurfing_ImGui_Widgets.h"
//#include "ofxSurfing_ImGui_WidgetsTypes.h"
#include "ofxSurfing_ImGui_Themes.h"

#include "ofxSurfing_Timers.h"

//---------------------

/* some helper tools */

// serializers
//--------------------------------------------------------------
inline bool loadGroup(ofParameterGroup &g, string path = "", bool debug = true)
{
	if (path == "") path = "settings.json";

	if (debug)
	{
		ofLogNotice(__FUNCTION__) << g.getName() << " to " << path;
		ofLogNotice(__FUNCTION__) << "parameters: \n\n" << g.toString();
	}
	else
	{
		ofLogVerbose(__FUNCTION__) << g.getName() << " to " << path;
		ofLogVerbose(__FUNCTION__) << "parameters: \n\n" << g.toString();
	}

	ofJson settings;
	settings = ofLoadJson(path);


	bool b = !settings.is_null();//TODO:
	//bool b = true;//TODO:

	//bool b = settings.is_null;
	//if (b) ofLogVerbose(__FUNCTION__) << "Load: " << g.getName() << " at " << path;
	//else ofLogError(__FUNCTION__) << "Error loading: " << g.getName() << " at " << path;

	return b;//returns true if its ok
}

//--------------------------------------------------------------
inline bool saveGroup(ofParameterGroup &g, string path = "", bool debug = true)
{
	if (path == "") path = "settings.json";

	if (debug) {
		ofLogNotice(__FUNCTION__) << g.getName() << " to " << path;
		ofLogNotice(__FUNCTION__) << "parameters: \n\n" << g.toString();
	}
	else
	{
		ofLogVerbose(__FUNCTION__) << g.getName() << " to " << path;
		ofLogVerbose(__FUNCTION__) << "parameters: \n\n" << g.toString();
	}

	//ofxSurfingHelpers::CheckFolder(path);

	ofJson settings;
	ofSerialize(settings, g);
	bool b = ofSavePrettyJson(path, settings);

	if (b) ofLogVerbose(__FUNCTION__) << "Save: " << g.getName() << " at " << path;
	else ofLogError(__FUNCTION__) << "Error saving: " << g.getName() << " at " << path;

	return b;
}

//-


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

	// main API

public:

	void setup(); // MODE A: ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).
	void setup(ofxImGui::Gui & gui); // MODE B: can be instantiated out of the class, locally

	//-

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

	//-

public:

	// Force autodraw
	//--------------------------------------------------------------
	void setImGuiAutodraw(bool b) { bAutoDraw = b; } // must be called before setup! default is false. For ImGui multi-instance.
	void setImGuiAutoResize(bool b) { bAutoResize = b; } // must be called before setup! default is false. For ImGui multi-instance.

	// Force shared context
	//--------------------------------------------------------------
	void setImGuiSharedMode(bool b) { gui.setSharedMode(b); }

	//-

private:

	void setup_ImGui();
	bool bAutoDraw; // must be false when multiple ImGui instances created!

	// with have two mode for instantiate ImGui
	ofxImGui::Gui * guiPtr = NULL; // passed by reference
	ofxImGui::Gui gui; // inside the addon

	//ofxImGui::Settings mainSettings = ofxImGui::Settings(); // should remove..

	//-

	// fonts runtime mangement 

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

	//-

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
	float hh = 20;
	//float hh = PANEL_WIDGETS_HEIGHT_MIN;

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

public:
	void setAutoSaveSettings(bool b) { // must call before setup
		bAutoSaveSettings = b;
	}

	////TODO:
	//public:
	//SurfingTypes widgetsManager;
	//void refreshShape() {
	//widgetsManager.refreshPanelShape(); // update sizes to current window shape
	//}
};
//} // namespace ofxImGuiSurfing
