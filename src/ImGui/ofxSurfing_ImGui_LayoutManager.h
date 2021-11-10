
/*

TODO:

+ position applyes to 2nd window ?

+ fix make dockeable all windows on same space
+ fix multiple dock spaces that are colliding/one over another
+ fix viewport rectangle preview

+ remake mode free and lockers simpler. a flag for each window

+ aspect ratio/fit modes for game viewport
+ add help box

+ auto size per window
+ other window settings


*/

//-

// Docking help
// https://github.com/ocornut/imgui/issues/2109

// Docking demo
// https://github.com/ocornut/imgui/blob/1ad1429c6df657f9694b619d53fa0e65e482f32b/imgui_demo.cpp#L7399-L7408

// Toolbar example
// https://gist.github.com/moebiussurfing/b7652ba1ecbd583b7c4f18e25a598551

//-

// -> We have some layout presets that we can load using keys:
// F1-F2-F3-F4 -> preset
// F5: Window Presets
// F6: Window Panels
// F7: Window Extra

//-

//TODO:
// Testing central viewport
//#define FIXING_DOCKING // -> Need to fix yet
#define FIXING_DRAW_VIEWPORT // -> To debug free space

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

#define OFX_IMGUI_CONSTRAIT_WINDOW_SHAPE // -> constrait some window minimal shape sizes

//-

using namespace ofxImGuiSurfing;

//TODO:
// These argumnents are to pass to setup(..) method and simplify instantiation and settings.
//--------------------------------------------------------------
namespace ofxImGuiSurfing
{
	// Argument to be used on setup(mode);
	enum SurfingImGuiInstantiationMode {
		IM_GUI_MODE_UNKNOWN = 0, // -> Could be undefied when using legacy api maybe.
		IM_GUI_MODE_INSTANTIATED, // -> To include the ImGui context and requiring begin/end
		IM_GUI_MODE_INSTANTIATED_DOCKING,
		IM_GUI_MODE_INSTANTIATED_SINGLE, // -> To include the ImGui context and requiring begin/end but a single ImGUi instance, no other addons.
		IM_GUI_MODE_REFERENCED, // -> To receive the parent (ofApp scope) ImGui object as reference.
		IM_GUI_MODE_NOT_INSTANTIATED // -> To render windows and widgets only. Inside an external ImGui context begin/end (newFrame)
	};

	enum SurfingImGuiWindowsMode {
		IM_GUI_MODE_WINDOWS_SPECIAL_UNKNOWN = 0,
		IM_GUI_MODE_WINDOWS_SPECIAL_DISABLED,
		IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER
	};
}

//--------

//--------------------------------------------------------------
class ofxSurfing_ImGui_Manager
{
	//-

public:

	ofxSurfing_ImGui_Manager();
	~ofxSurfing_ImGui_Manager();

	//--

public:

	void initiate(); // MODE A: ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).
	void setup(ofxImGui::Gui & gui); // MODE B: can be instantiated out of the class, locally
	void update(); // to manual update...
	void draw(); // to manual draw...

private:

	void keyPressed(ofKeyEventArgs &eventArgs);
	void keyReleased(ofKeyEventArgs &eventArgs);

	//-

private:

	ofxSurfing_ImGui_WidgetsTypes widgetsManager; // -> The Widget Styles Manager

	//----

	// Styles API

public:

	// ofParam's

	//--------------------------------------------------------------
	bool Add(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		return widgetsManager.Add(aparam, type, amtPerRow, bSameLine, spacing);
	}
	//--------------------------------------------------------------
	void AddStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		widgetsManager.AddStyle(aparam, type, amtPerRow, bSameLine, spacing);
	}
	//--------------------------------------------------------------
	void AddStyle(std::string name, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
	{
		widgetsManager.AddStyle(name, type, amtPerRow, bSameLine, spacing);
	}

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

	//--------------------------------------------------------------
	void clearStyles()
	{
		widgetsManager.clear(); // update sizes to current window shape
	}

	//----

public:

	// Styles Engine
	// widgetsManager

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT)
	{
		widgetsManager.AddGroup(group, flags, typeGroup);
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

	//-

public:

	// Special Windows Mode
	SurfingImGuiWindowsMode surfingImGuiSpecialWindowsMode = IM_GUI_MODE_WINDOWS_SPECIAL_UNKNOWN;
	void setWindowsMode(SurfingImGuiWindowsMode mode) {
		surfingImGuiSpecialWindowsMode = mode;
	}

	// Instantiator
	SurfingImGuiInstantiationMode surfingImGuiMode = IM_GUI_MODE_UNKNOWN;
	void setup(ofxImGuiSurfing::SurfingImGuiInstantiationMode mode = IM_GUI_MODE_INSTANTIATED);

	//----

private:

	// ImGui instance/context

	// We have two mode for instantiate ImGui
	ofxImGui::Gui gui; // ImGui is inside the add-on
	ofxImGui::Gui * guiPtr = NULL; // To be used when ImGui is passed by reference in the parent scope (ofApp)

	// Initiates ofxImGui with the common settings
	void setupImGui();

public:

	// To share the same Gui between/with other add-ons
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

public:

	// API

	// To the Global context: 
	// All the windows are feeded in between!
	void begin(); // -> main begin feed widgets
	void end(); // -> main end feed widgets

	//----

	// Window methods

	// Begins a window
	bool beginWindow(ofParameter<bool> p); // will use the bool param for show/hide and the param name for the window name
	bool beginWindow(ofParameter<bool> p, ImGuiWindowFlags window_flags); // will use the bool param for show/hide and the param name for the window name
	bool beginWindow(std::string name, bool* p_open, ImGuiWindowFlags window_flags);
	bool beginWindow(std::string name, bool* p_open);
	bool beginWindow(std::string name = "Window"); // -> simpler. not working?

	// Ends a window
	void endWindow();

	//----

private:

	// The ImGui instance options

	bool bAutoDraw; //TODO: must be false when multiple ImGui instances created ?
	bool bViewport = false;
	bool bDockingModeCentered = false; //TODO: enables fullscreen ImGuiDockNodeFlags_PassthruCentralNode

	//-

public:

	// API 
	// Some options

	// Force autodraw
	//--------------------------------------------------------------
	void setImGuiAutodraw(bool b) { bAutoDraw = b; } // must be called before setup! default is false. For ImGui multi-instance.
	void setImGuiAutoResize(bool b) { bAutoResize = b; } // must be called before setup! default is false. For ImGui multi-instance.
	void setImGuiViewPort(bool b) { bViewport = b; } // must be called before setup! 
	void setImGuiDocking(bool b) { setDocking(b); } // must call before setup
	void setImGuiDockingModeCentered(bool b) { bDockingModeCentered = b; } // Allows docking on bg window viewport. Default is enabled. Must be called before setup! 
	void setImGuiDockingShift(bool b) { ImGui::GetIO().ConfigDockingWithShift = b; }

	// Force shared context
	//--------------------------------------------------------------
	void setImGuiSharedMode(bool b) { gui.setSharedMode(b); }

	//----

	// Fonts runtime management 

private:

	ImFont* customFont = nullptr;
	vector<ImFont*> customFonts;
	bool bIgnoreNextPopFont = false;

public:

	bool addFont(std::string path, int size);
	bool pushFont(std::string path, int size);

private:

	int currFont = 0;
	void processOpenFileSelection(ofFileDialogResult openFileResult, int size);
	void openFileFont(int size = 10);

public:

	void setDefaultFontIndex(int index);
	void setDefaultFont();
	int getNumFonts() { return customFonts.size(); }

	void pushStyleFont(int index);
	void popStyleFont();

	//----

public:

	//--------------------------------------------------------------
	bool isMouseOverGui() {
		return bMouseOverGui;
	}

	//--------------------------------------------------------------
	bool isOverInputText() {
		return bInputText;
	}

	//----

private:

	ofParameter<bool> bPreviewSceneViewport{ "Viewport", false };

	bool bUseAdvancedSubPanel = true; // enable advanced sub panel

	//-

	// Exposed useful public params

public:

	ofParameter<bool> bGui{ "Show Gui", true };
	ofParameter<bool> bGui_WindowsSpecials{ "Organizer", true }; // uses Windows Specials

	ofParameterGroup params_Advanced{ "Params Advanced" }; // -> These are saved on settings when exit the app 
	ofParameter<bool> bAutoResize{ "Auto Resize", true };
	ofParameter<bool> bMinimize{ "Minimize", true };
	ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bReset{ "Reset", false };
	ofParameter<bool> bAdvanced{ "Advanced", false };
	ofParameter<bool> bLockMove{ "Lock Move", false };
	ofParameter<bool> bNoScroll{ "No Scroll", false };
	ofParameter<bool> bHelp{ "Help", false };
	ofParameter<bool> bKeys{ "Keys", true };
	ofParameter<bool> bDebug{ "Debug", false };
	ofParameter<bool> bMouseWheel{ "MouseWheel", true };
	ofParameter<bool> bReset_Window{ "Reset Window", false };

private:

	ofParameterGroup params_RectPanels{ "Rectangles Windows" };
	vector<ofParameter<ofRectangle>> rectangles_Windows;

	ofParameter<ofRectangle> rect0_Presets{ "rect_Presets", ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080) };
	ofParameter<ofRectangle> rect1_Panels{ "rect_Panels", ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080) };
	ofParameter<ofRectangle> rect2_Manager{ "rect_Manager", ofRectangle(), ofRectangle(), ofRectangle(1920, 1080, 1920, 1080) };

	ImGuiWindowFlags flags_wPr;
	ImGuiWindowFlags flags_wPanels;

	// Presets and Panels windows
	ofParameter<bool> bResetWindowPresets{ "Reset", false };
	ofParameter<bool> bAutoResizePresets{ "AutoResize", true };
	ofParameter<bool> bMinimizePresets{ "Minimize", true };
	ofParameterGroup params_WindowPresets{ "Window Presets" };

	ofParameter<bool> bResetWindowPanels{ "Reset Panels", false };
	ofParameter<bool> bAutoResizePanels{ "AutoResize Panels", true };
	ofParameter<bool> bMinimizePanels{ "Minimize", true };
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
	ImGuiLogWindow log;

	//--------------------------------------------------------------
	void addLog(std::string text) {
		// Log
		log.AddText(text);
	}

public:

	// Snippets:
	// ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bLog); // -> enabler
	// guiManager.log.AddText(mMidiMessageHistoryStr); // -> feed
	//--------------------------------------------------------------
	void drawLogPanel() {
		if (bLog) {
			log.ImGui();
		}
	}

	//--------------------------------------------------------------
	void logAdd(std::string text) {
		if (bLog) log.AddText(text);
	}

	//----

	// Advanced Window

private:

	// An advanced/extra common panel
	// Snippet to copy/paste into out ofApp:
	//ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
	//guiManager.drawAdvancedSubPanel();
	//--------------------------------------------------------------
	void drawAdvancedControls() {
		drawAdvanced();
	}

public:

	// Snippet:
	// Example to copy/paste into out ofApp:
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;;
	//if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//if (guiManager.bLockMove) window_flags |= ImGuiWindowFlags_NoMove;
	//guiManager.beginWindow("ofApp", NULL, window_flags);
	//--------------------------------------------------------------
	void drawAdvanced(bool bNoSperator = false) { // -> Simpler call. Use this.
		ImGui::Spacing();
		if (!bNoSperator) ImGui::Separator();
		ImGui::Spacing();

		Add(bAdvanced, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);

		drawAdvancedSubPanel();
	}

	//--

private:

	//--------------------------------------------------------------
	void drawAdvancedSubPanel(bool bHeader = true) {
		if (!bAdvanced) return;
		if (!bUseAdvancedSubPanel) return;

		//--

		ImGui::Indent();
		{
			bool b = false;
			if (!bUseAdvancedSubPanel) {
				if (bHeader) b = ImGui::CollapsingHeader(params_Advanced.getName().c_str(), ImGuiTreeNodeFlags_None);
			}
			else b = true;

			// Keys
			ofxImGuiSurfing::AddToggleRoundedButton(bKeys);

			// MouseWheel
			ofxImGuiSurfing::AddToggleRoundedButton(bMouseWheel);

			// Autoresize
			ofxImGuiSurfing::AddToggleRoundedButton(bAutoResize);

			if (!bHeader || (bHeader && b))
			{
				if (ImGui::TreeNode("Windows"))
				{
					// Lock
					ofxImGuiSurfing::AddToggleRoundedButton(bLockMove);

					// No Scroll
					ofxImGuiSurfing::AddToggleRoundedButton(bNoScroll);

					// Reset
					//TODO:
					// -> must be implemented for each app.

					// Reset window
					if (ofxImGuiSurfing::AddToggleRoundedButton(bReset_Window)) {
						//TODO:
						//if (bReset_Window) {
						//	bReset_Window = false;
						//	resetWindowImGui(false, true);
						//}
					}
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("Gui"))
				{
					// Minimize
					ofxImGuiSurfing::AddToggleRoundedButton(bMinimize);

					// Extra
					ofxImGuiSurfing::AddToggleRoundedButton(bExtra);

					// Menu
					ofxImGuiSurfing::AddToggleRoundedButton(bMenu);

					// Reset
					ofxImGuiSurfing::AddToggleRoundedButton(bReset);

					// Log
					ofxImGuiSurfing::AddToggleRoundedButton(bLog);

					// Help
					ofxImGuiSurfing::AddToggleRoundedButton(bHelp);

					//--

					// Debug
					ofxImGuiSurfing::AddToggleRoundedButton(bDebug);
					if (bDebug)
					{
						ImGui::Indent();

						//--

						//drawSpecialWindowsPanel();
						//ImGui::Separator();

						//--

						//ImGui::Text("Docking");
						if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING)
						{
							AddToggleRoundedButton(bDebugDocking);
							if (bDebugDocking)
							{
								ImGui::Indent();

								AddToggleRoundedButton(bUseLayoutPresetsManager);
								AddToggleRoundedButton(bDocking);
								ToggleRoundedButton("bDockingModeCentered", &bDockingModeCentered);
								AddToggleRoundedButton(bPreviewSceneViewport);
								//ToggleRoundedButton("Viewport", &bPreviewSceneViewport);
								AddToggleRoundedButton(bDebugRectCentral);

								ImGui::Unindent();
							}
							ImGui::Separator();
						}

						ofxImGuiSurfing::AddToggleRoundedButton(bInputText);
						ofxImGuiSurfing::AddToggleRoundedButton(bMouseOverGui);
						//AddToggleRoundedButton(bPreviewSceneViewport);

						//-
						if (ImGui::TreeNode("Window Info"))
						{
							std::string _hwidget = "Widget Height: ";
							_hwidget += ofToString(ofxImGuiSurfing::getWidgetsHeightUnit());
							std::string _wwidget = "Widget Width: ";
							_wwidget += ofToString(ofxImGuiSurfing::getWidgetsWidth(1));
							std::string _wpanel = "Panel Width: ";
							_wpanel += ofToString(ofxImGuiSurfing::getPanelWidth());

							std::string _wShape = "Window Shape: ";
							_wShape += ofToString(ImGui::GetWindowPos().x);
							_wShape += ", ";
							_wShape += ofToString(ImGui::GetWindowPos().y);
							_wShape += ", ";
							_wShape += ofToString(ImGui::GetWindowWidth());
							_wShape += ", ";
							_wShape += ofToString(ImGui::GetWindowHeight());

							std::string ss = "";
							ss += _hwidget + "\n";
							ss += _wwidget + "\n";
							ss += _wpanel + "\n";
							ss += _wShape + "\n";
							ImGui::TextWrapped(ss.c_str());
						
							ImGui::TreePop();
						}

						//--

						////TODO:
						//// Check wheel
						//// Check active widget
						////https://github.com/ocornut/imgui/issues/4207
						////https://github.com/ocornut/imgui/issues/789
						////https://github.com/ocornut/imgui/issues/4303
						//if (0)
						//{
						//	auto &io = ImGui::GetIO();
						//	if (io.MouseHoveredViewport)
						//	{
						//		float wheel = io.MouseWheel;
						//		std::string ss1 = "Mouse Wheel ";
						//		if (wheel != 0)
						//		{
						//			ss1 += ofToString(wheel);
						//		}
						//		ImGui::Text(ss1.c_str());
						//	}
						//	string ss2;
						//	ss2 += "ID Hover  " + ofToString(ImGui::GetHoveredID()) + "\n";
						//	ss2 += "ID Focus  " + ofToString(ImGui::GetFocusID()) + "\n";
						//	ss2 += "ID Active " + ofToString(ImGui::GetActiveID());
						//	ImGui::Text(ss2.c_str());
						//}

						ImGui::Separator();
						ImGui::Unindent();
					}
					ImGui::TreePop();
				}
			}
		}
		ImGui::Unindent();
	}

public:

	//--------------------------------------------------------------
	void setUseAdvancedSubPanel(bool b) {
		bUseAdvancedSubPanel = b;
	}

	//----

private:

	// File Settings
	std::string path_Global;
	std::string path_ImLayouts;
	std::string path_AppSettings;
	std::string path_LayoutSettings;

	std::string path_SubPathLabel = "";

	bool bAutoSaveSettings = false;

	ofParameterGroup params_AppSettings{ "AppSettings" }; // -> Features states
	ofParameterGroup params_AppSettingsLayout{ "LayoutSettings" }; // -> Layout states

	//----

public:

	// Some tweaked settings modes
	//--------------------------------------------------------------
	void setSettingsFilename(std::string path) { // must call before setup. To allow multiple instances/windows settings
		path_SubPathLabel = path + "_";
	}

	//--------------------------------------------------------------
	void setSettingsPathLabel(std::string path) { // must call before setup. To allow multiple instances/windows settings
		path_SubPathLabel = path + "_";
	}

	//--------------------------------------------------------------
	void setAutoSaveSettings(bool b) { // must call before setup. IMPORTANT: if you are using multiple instances of this addon, must set only one to true or settings will not be handled correctly!
		bAutoSaveSettings = b;
	}

	//--------------------------------------------------------------
	void setAutoResize(bool b) { // must call before setup
		bAutoResize = b;
	}

	//--------------------------------------------------------------
	void setDocking(bool b) { // must call before setup
		bDocking = b;
	}


	//---------------------------

	// Special Windows Management

	// To simplify a bit the API

private:

	int _currWindowsSpecial = 0;

	std::string namePanel = "";

public:

	bool beginWindowSpecial();
	bool beginWindowSpecial(int index); // -> If you added windows to the engine you can begin the window passing his index
	void endWindowSpecial(int index = -1);

	//--------------------------------------------------------------
	void setNamePanelWindowsSpecial(std::string name) {
		namePanel = name;
	}

	//--------------------------------------------------------------
	void drawWindowsSpecialPanel() {

		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		if (bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;

		string ss;
		if (namePanel == "") ss = "Panels";
		else ss = namePanel;

		// Panels Toggles
		windowPanels.beginWindow(ss.c_str(), (bool*)&bGui_WindowsSpecials.get(), flags);
		{
			Add(bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);
			//Add(bAutoResize, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);

			windowPanels.drawWidgets(bMinimize);

			//if (windowPanels.bEnable)
			//{
			//	if (!bMinimize)
			//	{
			//		drawSpecialWindowsPanel();
			//		//drawAdvanced();//crashes?
			//	}
			//}
		}
		windowPanels.endWindow();
	}


	//--------------------------------------------------------------
	bool getWindowsSpecialEnableGlobal() {
		return windowPanels.bGui_Global.get();
	}

	////--------------------------------------------------------------
	//bool beginWindow(int index) { //-> legacy api
	//	return beginWindowSpecial(index);
	//}

	//--

	//TODO:
	//--------------------------------------------------------------
	struct SurfingImGuiWindowAtributes
	{
		// We queue here the bool paramms that enables the show/hide for each queued window
		ofParameter<bool> bGui{ "Show Gui", true };

		ofParameter<bool> bPoweredWindow{ "_bPoweredWindow", false }; // to include below extra toggles when rendering

		ofParameter<bool> bAutoResize{ "Auto Resize", true };
		ofParameter<bool> bExtra{ "Extra", false };
		ofParameter<bool> bMinimize{ "Minimize", false };
		ofParameter<bool> bAdvanced{ "Advanced", false };
		ofParameter<bool> bDebug{ "Debug", false };
		ofParameter<bool> bReset_Window{ "Reset Window", false };

		//--------------------------------------------------------------
		void setPowered(bool b) {
			bPoweredWindow = b;
		}

		//ofParameter<ofRectangle> rectShapeWindow{ "_WindowSpahe", ofRectangle(), ofRectangle(), ofRectangle() };
	};

	vector<SurfingImGuiWindowAtributes> windowsAtributes; // Handles only the manually pre added windows.

	//--

private:

	WindowPanels windowPanels;

public:

	//--------------------------------------------------------------
	void setNameGlobalPanelWindowsSpecial(std::string name) {
		windowPanels.setNameGlobalPanelWindowsSpecial(name);
	}

public:

	//--------------------------------------------------------------
	void clearWindowsSpecial() {
		windowsAtributes.clear();
	}

	//--------------------------------------------------------------
	void addWindowSpecial(ofParameter<bool>& _bGui, bool powered = false) {

		SurfingImGuiWindowAtributes win;
		win.bGui.makeReferenceTo(_bGui);
		win.setPowered(powered);

		windowsAtributes.push_back(win);

		params_Panels.add(_bGui);

		if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		{
			windowPanels.add(_bGui);
		}
	}

	//--------------------------------------------------------------
	void addWindowSpecial(std::string name, bool bPowered = false) {
		ofParameter<bool> _bGui{ name, true };

		SurfingImGuiWindowAtributes win;
		win.bGui.makeReferenceTo(_bGui);
		win.setPowered(bPowered);

		windowsAtributes.push_back(win);

		params_Panels.add(_bGui);

		if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		{
			windowPanels.add(_bGui);
		}
	}

	//--------------------------------------------------------------
	std::string getWindowSpecialName(int index) {
		if (index > windowsAtributes.size() - 1 || index == -1)
		{
			ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
			return "-1";
		}

		return windowsAtributes[index].bGui.getName();
	}

	////--------------------------------------------------------------
	//ofRectangle getRectangleWindowSpecial(int index) {
	//	if (index > windowsAtributes.size() - 1 || index == -1)
	//	{
	//		ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
	//	}
	//	return windowsAtributes[index].rectShapeWindow;
	//}

	////--------------------------------------------------------------
	//void addWindow(std::string name, bool bPowered = false) { // -> legacy api
	//	addWindowSpecial(name, bPowered);
	//}

	//--------------------------------------------------------------
	void initiatieWindowsSpecial() {
		windowPanels.setPath(path_Global);
		windowPanels.initiate();

		windowPanels.bModeLinkedWindowsSpecial.set(true);
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getWindowsSpecialEnabler() {
		return windowPanels.bModeLinkedWindowsSpecial;
	}

	//--------------------------------------------------------------
	ofParameter<bool>& getWindowsSpecialGui() {
		return bGui_WindowsSpecials;
	}

	//void drawSpecialWindowsPanel();

public:

	//----

	// Layouts Engine

	// Extra params to include packed into layout presets
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameterGroup& group) {
		params_LayoutsExtra.add(group);
	}
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameter<bool>& param) {
		params_LayoutsExtra.add(param);
	}
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameter<int>& param) {
		params_LayoutsExtra.add(param);
	}
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameter<float>& param) {
		params_LayoutsExtra.add(param);
	}
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameter<ofRectangle>& param) {
		params_LayoutsExtra.add(param);
	}

	//----

	//--------------------------------------------------------------
	ofParameter<bool>& getWindowSpecialVisible(int index)
	{
		if (index > windowsAtributes.size() - 1 || index == -1)
		{
			ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
			ofParameter<bool> b = ofParameter<bool>{ "-1", false };
			return b;
		}

		return windowsAtributes[index].bGui;
	}

	//----

private:

	void loadAppSettings();
	void saveAppSettings();

	//----

	////TODO:
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

	ofParameter<int> appLayoutIndex{ "Layout Preset", -1, -1, 0 }; // index for the selected preset. -1 is none selected, useful too.
	int appLayoutIndex_PRE = -1;

	ofParameterGroup params_Layouts{ "_LayoutsPresets" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsVisible{ "_LayoutsVisible" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsExtra{ "_LayoutsExtra" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsExtraInternal{ "Internal" }; // add-on related params

	int numPresetsDefault;
	void createLayoutPreset(std::string namePreset = "-1");

	//-

	vector<ofParameter<bool>> bLayoutPresets{ "bLayoutPresets" }; // each window show toggles
	void Changed_Params(ofAbstractParameter &e);
	void Changed_Params_Enablers(ofAbstractParameter &e);
	ofParameterGroup params_LayoutsPanel{ "Layouts Panel" };

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

	void setupLayout(int numPresets = 4); //-> must call manually after adding windows and layout presets

	// Some API simplificators
	//--------------------------------------------------------------
	void startup();
	void startupFirstFrame();
	void setupDocking();

	//--------------------------------------------------------------
	void setImGuiLayoutPresets(bool b) {
		bUseLayoutPresetsManager = b;
	}

	//--

public:

	void draw_ImGuiMenu();

	//--

private:

#define LAYOUT_WINDOW_WIDTH 150

	void updateLayout();

	void drawLayouts();
	void drawLayoutsExtra();
	void drawLayoutsPresets();
	void drawLayoutsPanels();
	void drawLayoutEngine();
	void drawOFnative();


	//// For different behaviour. We can disable to save some windows positions to allow them locked when changing presets.
	//ofParameter<bool> bModeFree{ "Free", true }; // -> A allows storing position for control windows too
	//ofParameter<bool> bModeForced{ "Forced", false }; // -> Locked to free space on viewport
	//ofParameter<bool> bModeLock1{ "Lock B", false }; // -> Cant be moved. To be used in presets panel
	//ofParameter<bool> bModeLockControls{ "Lock C", false }; // -> Cant be moved. To be used to lock to free viewport scenarios
	//ofParameter<bool> bModeLockPreset{ "Lock A", false }; // -> Cant be moved. To be used to lock to free viewport scenarios

	//TODO: 
	// It's a problem if .ini files are already present... We must ingore loading.

	ofParameter<bool> bDebugDocking{ "Debug Docking", false };

	//TODO:
	//ofParameter<bool> bDebugRectCentral{ "Rect Central", false };
	ofParameter<bool> bDebugRectCentral{ "Rect Central", true };

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

private:

	ofParameter<bool> bGui_LayoutsPanels{ "Panels", true };
	ofParameter<bool> bGui_LayoutsPresets{ "Layouts", true };
	//ofParameter<bool> bGui_LayoutsPresets{ "Presets", true };
	ofParameter<bool> bGui_LayoutsExtra{ "Extra", false };
	ofParameter<bool> bGui_LayoutsManager{ "Manager", false };

	ofParameter<bool> bAutoSave_Layout{ "Auto Save", true };
	ofParameter<bool> bUseLayoutPresetsManager{ "bUseLayoutPresetsManager", false }; // Can't be changed on runtime. cant include into settings
	ofParameter<bool> bDocking{ "bDocking", true };
	ofParameter<bool> bSolo{ "Solo", false };

public:

	ofParameter<bool> bLog{ "Log", false };

	//-

private:

	ofParameterGroup params_LayoutPresetsStates{ "LayoutPanels" };
	ofParameterGroup params_Panels{ "Params Panels" };

	//ImGuiWindowFlags flagsWindowsLocked1;//used for presets panel
	//ImGuiWindowFlags flagsWindowsLocked2;//used for other control panels
	//ImGuiWindowFlags flagsWindowsModeFreeStore;//used to unlink main control panels (presets, manager, extra, panels) from presets

	std::string titleWindowLabel;

	//-

	//TODO: 
	// Learn to use lambda functions
	// To callback reset
	// -> Subscribe an optional reset flagging a bool to true to reset. Uses the gui Reset button on the Presets Extra panel.

private:

	bool *bResetPtr = nullptr;

public:

	//--------------------------------------------------------------
	void setReset(bool *b) {
		bResetPtr = b;
	}

	//--------------------------------------------------------------
	void setShowAllPanels(bool b) {
		for (int i = 0; i < windowsAtributes.size(); i++)
		{
			windowsAtributes[i].bGui.set(b);
		}
		bMenu = b;

		//bModeLockControls = b;

		bGui_LayoutsPanels = b;
		bGui_LayoutsPresets = b;
		bGui_LayoutsExtra = false;
	}

	//--------------------------------------------------------------
	void doRemoveDataFiles() {

		// Remove all the settings folder
		const filesystem::path path = path_Global;
		ofDirectory::removeDirectory(path, true, true);

		// Remove ini file
		const filesystem::path file = ofToDataPath("../imgui.ini");
		ofFile::removeFile(file, true);
	}

	//-

	//TODO:
	// Should move to styles..
	// Disables a Widget and reduces transparency of most common colors.

public:

	//--------------------------------------------------------------
	inline void pushInactive() {

		const float a = 0.5f;

		ImGuiStyle *style = &ImGui::GetStyle();

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
};



// NOTES

// -> Optional to customize filename for the settings file for multiple instances on the same ofApp.
//guiManager.setSettingsFilename("3_DockingLayoutPresetsEngine"); 

