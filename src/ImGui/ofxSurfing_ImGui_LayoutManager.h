
/*

TODO:

+ fix make dockeable all windows on same space
+ fix multiple dock spaces that are colliding/one over another
+ fix viewport rectangle preview
+ add global reset
+ add minimal toggle
+ auto size per window
+ other window settings
+ layout ctrl+preset = solo
+ size debugger?

*/


#pragma once

#include "ofMain.h"

#include "ofxImGui.h"

#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_Themes.h"
#include "ofxSurfing_ImGui_ofHelpers.h"
#include "ofxSurfing_ImGui_WidgetsTypes.h"

#include "ofxSurfing_Serializer.h"
//#include "ofxSurfingHelpers.h"

//-

using namespace ofxImGuiSurfing;

//--------------------------------------------------------------
class ofxSurfing_ImGui_Manager
{

public:

	ofxSurfing_ImGui_Manager();
	~ofxSurfing_ImGui_Manager();

	//-

private:

	ofxSurfing_ImGui_WidgetsTypes widgetsManager; // -> fails bc it seems it's instantiated many times..

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
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT)
	{
		widgetsManager.AddGroup(group, flags, typeGroup);
	}

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

	void keyPressed(int key);

	//-

private:

	// initiate ofxImGui
	void setupImGui();

	// with have two mode for instantiate ImGui
	ofxImGui::Gui * guiPtr = NULL; // passed by reference
	ofxImGui::Gui gui; // inside the addon

public:

	// To share Gui with other add-ons
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

	//-

public:

	void draw(); // to manual draw...

	//-

	// global
	// all the windows are feeded between
	void begin();
	void end();

	// begin a window
	bool beginWindow(ofParameter<bool> p); // will use the bool param for show/hide and the param name for the window name
	bool beginWindow(ofParameter<bool> p, ImGuiWindowFlags window_flags); // will use the bool param for show/hide and the param name for the window name
	bool beginWindow(std::string name, bool* p_open, ImGuiWindowFlags window_flags);
	bool beginWindow(std::string name, bool* p_open);
	bool beginWindow(std::string name = "Window"); // -> simpler. not working?

	// end a window
	void endWindow();

	//----

private:

	bool bAutoDraw; // must be false when multiple ImGui instances created!
	bool bViewport = false;
	//bool bDocking = true;
	bool bDockingModeCentered = false; // enables fullscreen ImGuiDockNodeFlags_PassthruCentralNode
	bool bPreviewSceneViewport = false;

public:

	// force autodraw
	//--------------------------------------------------------------
	void setImGuiAutodraw(bool b) { bAutoDraw = b; } // must be called before setup! default is false. For ImGui multi-instance.
	void setImGuiAutoResize(bool b) { bAutoResize = b; } // must be called before setup! default is false. For ImGui multi-instance.
	void setImGuiViewPort(bool b) { bViewport = b; } // must be called before setup! 
	void setImGuiDocking(bool b) { setDocking(b); } // must call before setup
	void setImGuiDockingModeCentered(bool b) { bDockingModeCentered = b; } // Allows docking on bg window viewport. Default is enabled. Must be called before setup! 
	void setImGuiDockingShift(bool b) { ImGui::GetIO().ConfigDockingWithShift = b; }

	// force shared context
	//--------------------------------------------------------------
	void setImGuiSharedMode(bool b) { gui.setSharedMode(b); }

	//----

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

	ofParameterGroup params_Advanced{ "Params Advanced" };

	ofParameter<bool> bGui{ "Show Gui", true };
	ofParameter<bool> bAutoResize{ "Auto Resize", true };
	ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bMinimize{ "Minimize", false };
	ofParameter<bool> bReset_Window{ "Reset Window", false };
	ofParameter<bool> bAdvanced{ "Advanced", false };
	ofParameter<bool> bDebug{ "Debug", false };

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

	// An advanced/extra common panel
	// snippet to copy/paste into out orApp:
	//ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
	//guiManager.drawAdvancedSubPanel();

	//--------------------------------------------------------------
	void drawAdvanced() { // -> simpler call
		ofxImGuiSurfing::AddToggleRoundedButton(bAdvanced);
		drawAdvancedSubPanel();
	}
	//--------------------------------------------------------------
	void drawAdvancedSubPanel(bool bHeader = true) {
		if (!bAdvanced) return;
		if (!bUseAdvancedSubPanel) return;

		//--

		//ImGui::Dummy(ImVec2(0.0f, 2.0f));

		ImGui::Indent();
		{
			bool b = false;
			if (!bUseAdvancedSubPanel) {
				if (bHeader) b = ImGui::CollapsingHeader(params_Advanced.getName().c_str(), ImGuiTreeNodeFlags_None);
			}
			else b = true;

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
				if (bDebug) {
					ImGui::Indent();
					ofxImGuiSurfing::AddToggleRoundedButton(bMouseOverGui);
					ofxImGuiSurfing::ToggleRoundedButton("Scene Viewport", &bPreviewSceneViewport);
					ImGui::Unindent();
				}
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
	string path_Global;
	string path_ImLayouts;
	string path_AppSettings;
	string path_LayoutSettings;

	//bool bAutoSaveSettings = true;
	bool bAutoSaveSettings = false;

	ofParameterGroup params_AppSettings{ "AppSettings" };
	ofParameterGroup params_LayoutSettings{ "LayoutSettings" };

	//-

public:

	// some tweak modes

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

	//-

	// windows management
	// TODO:
	// to populate windows only subscribing the toggle show/enabler
public:

	//--------------------------------------------------------------
	void clearWindows() {
		windowAtributes.clear();
	}

	//--------------------------------------------------------------
	void addWindow(ofParameter<bool>& _bGui, bool powered = false) {

		WindowAtributes win;
		win.bGui.makeReferenceTo(_bGui);
		win.setPowered(powered);

		windowAtributes.push_back(win);

		params_Panels.add(_bGui);

	}

	//--------------------------------------------------------------
	void addWindow(std::string name) {
		ofParameter<bool> _bGui{ name, true };

		WindowAtributes win;
		win.bGui.makeReferenceTo(_bGui);
		win.setPowered(false);

		windowAtributes.push_back(win);
	}

	//--------------------------------------------------------------
	bool beginWindow(int index) {
		if (index > windowAtributes.size() - 1 || index == -1) {
			ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
			return false;
		}

		// maximize window
		float x = 10;
		float y = 10;
		float w = 200;
		float h = 600;

		ImGuiCond cond = ImGuiCond_None;
		cond |= ImGuiCond_FirstUseEver;
		//cond |= ImGuiCond_Appearing;

		ImGui::SetNextWindowPos(ImVec2(x, y), cond);
		ImGui::SetNextWindowSize(ImVec2(w, h), cond);

		bool b = false;
		//if ((bool)windowAtributes[index].bGui.get()) // -> fails
		{
			b = beginWindow(windowAtributes[index].bGui.getName().c_str(), (bool*)&windowAtributes[index].bGui.get(), ImGuiWindowFlags_None);
			//b = beginWindow(windowAtributes[index].bGui, ImGuiWindowFlags_None);
		}

		//if(!b) endWindow();

		return b;
		//return windowAtributes[index].bGui.get();
	}

	//--------------------------------------------------------------
	//ofParameter<bool> *getVisible(int index) 
	//ofParameter<bool> getVisible(int index) 
	ofParameter<bool>& getVisible(int index)
	{
		if (index > windowAtributes.size() - 1 || index == -1)
		{
			ofLogError(__FUNCTION__) << "out of range index for queued windows";
			//return ofParameter<bool>{"-1", false};
			//return &ofParameter<bool>{"-1", false};
			static ofParameter<bool> staticFalseResponse = ofParameter<bool>{ "-1", false };
			return staticFalseResponse;
		}

		return windowAtributes[index].bGui;
		//return &windowAtributes[index].bGui;
	}

private:
	struct WindowAtributes
	{
		// we queue here the bool paramms that enables the show/hide for each queued window
		ofParameter<bool> bGui{ "Show Gui", true };

		ofParameter<bool> bPoweredWindow{ "bPoweredWindow", false }; // to include extra toggles when rendering

		ofParameter<bool> bAutoResize{ "Auto Resize", true };
		ofParameter<bool> bExtra{ "Extra", false };
		ofParameter<bool> bMinimize{ "Minimize", false };
		ofParameter<bool> bReset_Window{ "Reset Window", false };
		ofParameter<bool> bAdvanced{ "Advanced", false };
		ofParameter<bool> bDebug{ "Debug", false };

		void setPowered(bool b) {
			bPoweredWindow = b;
		}
	};
	vector<WindowAtributes> windowAtributes;

	void loadAppSettings();
	void saveAppSettings();

	//----

	// docking helpers

public:

	void beginDocking();
	void endDocking();

	//----

	//ImGuiViewport* viewport = nullptr;
	//ImGuiDockNodeFlags dockspace_flags;
	////static ImGuiDockNodeFlags dockspace_flags;
	//ImGuiIO& io = ImGui::GetIO();

	//ImGuiViewport& getDockingViewPort() {
	//	return *viewport;
	//}
	//ImGuiDockNodeFlags getDockingFlags() {
	//	return dockspace_flags;
	//}

//----

// layout presets for docking engine

// ImGui layouts engine
// on each layout preset we store:
// 1. some parameters states
// 2. ImGui ini positions

private:

	void drawLayoutsManagerWindow();

#define APP_RELEASE_NAME "ofxSurfing_ImGui_Manager"

	const char* ini_to_load = NULL;
	const char* ini_to_save = NULL;
	std::string ini_to_load_Str;
	std::string ini_to_save_Str;

	void loadAppLayout(int mode);
	void saveAppLayout(int mode);

	void saveLayoutPreset(string path); //-> both group params and ImGui ini files
	void loadLayoutPreset(string path);
	void saveLayoutImGuiIni(string path);
	void loadLayoutImGuiIni(string path);
	void saveLayoutPresetGroup(string path);
	void loadLayoutPresetGroup(string path);

	ofParameter<int> appLayoutIndex{ "App Layout", 0, 0, -1 };
	int appLayoutIndex_PRE = -1;

	ofParameterGroup params_Layouts{ "Layout Presets" };

	int numPresetsDefault;
	void createLayoutPreset();

	//-

	vector<ofParameter<bool>> bLayoutPresets{ "bLayoutPresets" }; // each window show toggles
	void Changed_Params(ofAbstractParameter &e);
	ofParameterGroup params_LayoutSPanel{ "Layouts Panel" };

	//--------------------------------------------------------------
	std::string getLayoutName(int mode) {
		std::string s = "";

		if (mode > bLayoutPresets.size() - 1) return "-1";

		s = bLayoutPresets[mode].getName();
		//s += ".ini";
		string _path = s;
		return _path;
	}

	//----

public:

	void setupLayout(int numPresets = 4); //-> must call manually after adding windows and layout presets

	//--------------------------------------------------------------
	void setImGuiLayoutPresets(bool b) {
		bUseLayoutPresetsManager = b;
	}

	ofParameter<bool> bGui_LayoutsManagerWindow{ "Layout Manager", false };
	ofParameter<bool> bGui_Menu{ "Menu", false };

private:

#define LAYOUT_WINDOW_WIDTH 150

	void updateLayout();

	void drawLayouts();
	void drawLayoutsExtra();
	void drawLayoutsPresets();
	void drawLayoutScene();

	void drawLayoutsPanels();

	ofParameter<bool> bForceLayoutPosition{ "Forced", false };
	ofParameter<bool> bDebugDocking{ "Debug", false };

	ofParameter<bool> bDebugRectCentral{ "Rectangle Central", false };
	ofRectangle rectangle_Central_MAX;
	ofRectangle rectangle_Central;
	ofRectangle rectangle_Central_Transposed;

	// standalone window not handled by .ini layout
	// but for the app settings
	float widthGuiLayout;
	ofParameter<glm::vec2> positionGuiLayout{ "Gui Layout Position",
	glm::vec2(ofGetWidth() / 2,ofGetHeight() / 2),//center
		glm::vec2(0,0),
		glm::vec2(ofGetWidth(), ofGetHeight())
	};

	// customize titles
public:
	void setLabelLayoutPanels(string label) {
		bGui_Panels.setName(label);
	}
	void setLabelLayoutMainWindow(string label) {
		bGui_LayoutsManagerWindow.setName(label);
	}

	//-

private:
	ofParameter<bool> bGui_Panels{ "Layout Panels", true };
	ofParameter<bool> bGui_LayoutsPresets{ "Layouts Presets", false };
	ofParameter<bool> bGui_LayoutsExtra{ "Layouts Extra", false };
	//shows advanced panels to tweak layout or workflow behaviour
	ofParameter<bool> bLockLayout{ "Lock", false };
	ofParameter<bool> bAutoSave_Layout{ "Auto Save Layout", true };
	//ofParameter<bool> bResponsive_Panels;
	ofParameter<bool> bUseLayoutPresetsManager{ "bUseLayoutPresetsManager", false };//cant be changed on runtime. cant include into settings
	ofParameter<bool> bDocking{ "bDocking", true };

	ofParameter<bool> bSolo{ "Solo", false };

	ofParameterGroup params_LayoutPresetsStates{ "LayoutPanels" };
	ofParameterGroup params_Panels{ "Params Panels" };

	ImGuiWindowFlags flagsWindowsLocked;

	string titleWindowLabel;

	//-

	// to callback reset
private:
	bool *bReset = nullptr;

public:
	//--------------------------------------------------------------
	void setReset(bool *b) {
		bReset = b;
	}

};


/*
// Flags for ImGui::DockSpace()
enum ImGuiDockNodeFlags_
{
ImGuiDockNodeFlags_None                         = 0,
ImGuiDockNodeFlags_KeepAliveOnly                = 1 << 0,   // Don't display the dockspace node but keep it alive. Windows docked into this dockspace node won't be undocked.
//ImGuiDockNodeFlags_NoCentralNode              = 1 << 1,   // Disable Central Node (the node which can stay empty)
ImGuiDockNodeFlags_NoDockingInCentralNode       = 1 << 2,   // Disable docking inside the Central Node, which will be always kept empty. Note: when turned off, existing docked nodes will be preserved.
ImGuiDockNodeFlags_NoSplit                      = 1 << 3,   // Disable splitting the node into smaller nodes. Useful e.g. when embedding dockspaces into a main root one (the root one may have splitting disabled to reduce confusion). Note: when turned off, existing splits will be preserved.
ImGuiDockNodeFlags_NoResize                     = 1 << 4,   // Disable resizing child nodes using the splitter/separators. Useful with programatically setup dockspaces.
ImGuiDockNodeFlags_PassthruCentralNode          = 1 << 5,   // Enable passthru dockspace: 1) DockSpace() will render a ImGuiCol_WindowBg background covering everything excepted the Central Node when empty. Meaning the host window should probably use SetNextWindowBgAlpha(0.0f) prior to Begin() when using this. 2) When Central Node is empty: let inputs pass-through + won't display a DockingEmptyBg background. See demo for details.
ImGuiDockNodeFlags_AutoHideTabBar               = 1 << 6    // Tab bar will automatically hide when there is a single window in the dock node.
};
*/