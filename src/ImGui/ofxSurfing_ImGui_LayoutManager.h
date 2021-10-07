
/*

TODO:

+ bug when chaining multiple groups on a window.
//guiManager.resetUniqueNames();//-> requires a reset
//guiManager.AddGroup(params_pointLight);
+ fix make dockeable all windows on same space
+ fix multiple dock spaces that are colliding/one over another
+ fix viewport rectangle preview

+ remake mode free and lockers simpler. a flag for each window

+ aspect ratio /fit modes for game viewport
+ add help box

+ add global reset
+ add minimal toggle
+ auto size per window
+ other window settings

*/


//#define FIXING_DOCKING // -> Need to fix yet
#define FIXING_DRAW_VIEWPORT // -> To debug free space

// -> We have some layout presets that we can load using keys:
// F1-F2-F3-F4 -> preset
// F9: Window Presets
// F10: Window Panels
// F11: Window Extra
// f/l/L: locks

//-

// Docking help
// https://github.com/ocornut/imgui/issues/2109

// Docking demo
// https://github.com/ocornut/imgui/blob/1ad1429c6df657f9694b619d53fa0e65e482f32b/imgui_demo.cpp#L7399-L7408

// Toolbar example
// https://gist.github.com/moebiussurfing/b7652ba1ecbd583b7c4f18e25a598551

//-

#pragma once

#include "ofMain.h"

#include "ofxImGui.h"

#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_Themes.h"
#include "ofxSurfing_ImGui_ofHelpers.h"
#include "ofxSurfing_ImGui_WidgetsTypes.h"

#include "ofxSurfing_Serializer.h"
////#include "ofxSurfingHelpers.h"

#define OFX_IMGUI_CONSTRAIT_WINDOW_SHAPE // -> constrait some window minimal shape sizes

//#define APP_RELEASE_NAME "ofxSurfing_ImGui_Manager"


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
}

//--------------------------------------------------------------
class ofxSurfing_ImGui_Manager
{
	//-

public:

	SurfingImGuiInstantiationMode surfingImGuiMode = IM_GUI_MODE_UNKNOWN;

	void setup(ofxImGuiSurfing::SurfingImGuiInstantiationMode mode);

public:

	// window log
	ImGuiLogWindow log;

	//--------------------------------------------------------------
	void addLog(std::string text) {
		// log
		log.AddText(text);
	}

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
	void AddStyle(std::string name, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
	{
		widgetsManager.AddStyle(name, type, bSameLine, amtPerRow, spacing);
	}

	//TODO:
	//--------------------------------------------------------------
	void UpdateStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT)
	{
		widgetsManager.UpdateStyle(aparam, type);
	}

	//TODO: group styles are recursive! must fix!

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

	////--------------------------------------------------------------
	//void AddGroup(ofParameterGroup& group, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT)
	//{
	//	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
	//	widgetsManager.AddGroup(group, flags, typeGroup);
	//}

	//--

	//--------------------------------------------------------------
	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT)
	{
		//refresh();//TODO:
		widgetsManager.AddGroup(group, flags, typeGroup);
	}

	//--

public:

	// many repeated methods. need to pick a good name...
	////--------------------------------------------------------------
	//void refresh()
	//{
	//	widgetsManager.refresh(); // update sizes to current window shape
	//}
	//--------------------------------------------------------------
	void refreshLayout()
	{
		widgetsManager.refreshLayout(); // update sizes to current window shape
	}

	//--------------------------------------------------------------
	void clearStyles()
	{
		widgetsManager.clear(); // update sizes to current window shape
	}
	////--------------------------------------------------------------
	//void clear() //-> legacy api
	//{
	//	widgetsManager.clear(); // update sizes to current window shape
	//}
	////--------------------------------------------------------------
	//void reset()
	//{
	//	widgetsManager.resetUniqueNames(); // update sizes to current window shape
	//}
	////--------------------------------------------------------------
	//void resetIDs()
	//{
	//	widgetsManager.resetUniqueNames(); // update sizes to current window shape
	//}
	//--------------------------------------------------------------
	void resetUniqueNames()
	{
		widgetsManager.resetUniqueNames(); // update sizes to current window shape
	}

	//-

public:

	void setup(); // MODE A: ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).
	void setup(ofxImGui::Gui & gui); // MODE B: can be instantiated out of the class, locally

	void keyPressed(ofKeyEventArgs &eventArgs);
	void keyReleased(ofKeyEventArgs &eventArgs);

	//-

private:

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

	//-

public:

	void update(); // to manual update...
	void draw(); // to manual draw...

	//-

	// To the Global context: all the windows are feeded in between!
	void begin();
	void end();

	//-

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

	//
	// Special windows
	//
	//// We can add some special windows that have more features, with a simplified api.
	//// This type of windows can be included into the Layout Presets Engine!
	////
	//// EXAMPLE CODE:
	//// Will be added on: 
	////
	//// setup():
	//guiManager.addWindowSpecial("mySpecialWin0", true);//index 0
	//guiManager.addWindowSpecial("mySpecialWin1", true);//index 1
	//guiManager.addWindowSpecial("mySpecialWin2");//index 2
	//guiManager.addWindowSpecial("mySpecialWin3");//index 3
	////
	//// draw():
	// You must rememeber the index to manually call like:
	//guiManager.beginWindowSpecial(1);{}
	//guiManager.beginWindowSpecial();
	// or remember and respect the original setup() sorting when draw():
	//guiManager.beginWindowSpecial();{}
	//guiManager.endWindow();
	//guiManager.beginWindowSpecial();{}
	//guiManager.endWindow();

	//-

	// To simplify a bit the api

private:
	int _currWindowsSpecial = 0;

public:
	bool beginWindowSpecial();
	bool beginWindowSpecial(int index); // -> If you added windows to the engine you can begin the window passing his index
	void endWindowSpecial();

	//--------------------------------------------------------------
	bool beginWindow(int index) { //-> legacy api
		return beginWindowSpecial(index);
	}

	//----

	/*
	//TODO:
	// a window management engine
	//to cascade all window or to distribute into the the viewport in some ways...
	//it seems that could be used only on the special windows not over all...
private:
	vector<ofRectangle> rectWindows;
	int currWindow = -1;
public:
	//--------------------------------------------------------------
	void log_RectWindows() {
		ofLogNotice(__FUNCTION__) << "--------------------------------------------------------------";
		int i = 0;
		for (auto &r : rectWindows) {
			ofLogNotice(__FUNCTION__) << "Window #" << i++ << " " << ofToString(r);
		}
	}
	*/

	//----

private:

	// The ImGui instance options

	bool bAutoDraw; // must be false when multiple ImGui instances created!
	bool bViewport = false;
	bool bDockingModeCentered = false; // enables fullscreen ImGuiDockNodeFlags_PassthruCentralNode

	//-

public:

	// some api configs

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

	// Fonts runtime management 

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

	//--------------------------------------------------------------
	bool isOverInputText() {
		return bInputText;
	}

	//----

private:

	ofParameter<bool> bPreviewSceneViewport{ "Viewport", false };
	//bool bPreviewSceneViewport = false;

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

	ofParameter<bool> bGui{ "Show Gui", true };

	ofParameterGroup params_Advanced{ "Params Advanced" };

	ofParameter<bool> bAutoResize{ "Auto Resize", true };
	ofParameter<bool> bMinimize{ "Minimize", true };
	ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bReset{ "Reset", false };
	ofParameter<bool> bAdvanced{ "Advanced", false };
	ofParameter<bool> bLockMove{ "Lock Move", false };

	ofParameter<bool> bHelp{ "Help", true };
	ofParameter<bool> bKeys{ "Keys", true };
	ofParameter<bool> bDebug{ "Debug", false };

	ofParameter<bool> bReset_Window{ "Reset Window", false };

	ofParameterGroup params_RectPanels{ "Rect Panels" };
	vector<ofParameter<ofRectangle>> rectPanels;

private:

	ofParameter<bool> bMouseOverGui{ "Mouse OverGui", false }; // mouse is over gui
	ofParameter<bool> bInputText{ "Input Text", false }; // user is over a text input
	//ofParameter<bool> bAutoLockGuiToBorder{ "Lock GUI", false }; // force position

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

		ImGuiCond flagsCond = ImGuiCond_Always;
		//ImGuiCond flagsCond = ImGuiCond_Appearing;
		//flagsCond |= ImGuiCond_Appearing;
		//flagsCond |= ImGuiCond_Once;

		if (size) ImGui::SetWindowSize(ImVec2(ww, hh), flagsCond);
		if (pos) ImGui::SetWindowPos(ImVec2(xx, yy), flagsCond);
	}

	//--

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
	// Example Snippet to copy/paste into out ofApp:
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;;
	//if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//if (guiManager.bLockMove) window_flags |= ImGuiWindowFlags_NoMove;
	//guiManager.beginWindow("ofApp", NULL, window_flags);
	//--------------------------------------------------------------
	void drawAdvanced() { // -> Simpler call. Use this.
		ImGui::Spacing();
		ofxImGuiSurfing::AddToggleRoundedButton(bAdvanced);
		drawAdvancedSubPanel();
	}

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
			// Autoresize
			ofxImGuiSurfing::AddToggleRoundedButton(bAutoResize);

			if (!bHeader || (bHeader && b))
			{
				if (ImGui::TreeNode("Windows"))
				{

					// Lock
					ofxImGuiSurfing::AddToggleRoundedButton(bLockMove);

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

						drawSpecialWindowsPanel();

						ImGui::Separator();

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

						//--

						//TODO:
						// Check wheel
						// Check active widget
						//https://github.com/ocornut/imgui/issues/4207
						//https://github.com/ocornut/imgui/issues/789
						//https://github.com/ocornut/imgui/issues/4303
						if (0)
						{
							auto &io = ImGui::GetIO();
							if (io.MouseHoveredViewport)
							{
								float wheel = io.MouseWheel;
								string ss1 = "Mouse Wheel ";
								if (wheel != 0)
								{
									ss1 += ofToString(wheel);
								}
								ImGui::Text(ss1.c_str());
							}
							string ss2;
							ss2 += "ID Hover  " + ofToString(ImGui::GetHoveredID()) + "\n";
							ss2 += "ID Focus  " + ofToString(ImGui::GetFocusID()) + "\n";
							ss2 += "ID Active " + ofToString(ImGui::GetActiveID());
							ImGui::Text(ss2.c_str());
						}

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

	// settings
	string path_Global;
	string path_ImLayouts;
	string path_AppSettings;
	string path_LayoutSettings;

	string path_SubPathLabel = "";

	//bool bAutoSaveSettings = true;
	bool bAutoSaveSettings = false;

	ofParameterGroup params_AppSettings{ "AppSettings" };
	ofParameterGroup params_AppSettingsLayout{ "LayoutSettings" };

	//----

public:

	// Some tweaked settings modes
	//--------------------------------------------------------------
	void setSettingsFilename(string path) { // must call before setup. To allow multiple instances/windows settings
		path_SubPathLabel = path + "_";
	}
	//--------------------------------------------------------------
	void setSettingsPathLabel(string path) { // must call before setup. To allow multiple instances/windows settings
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

	//----

	// Windows management

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
	}

	//--------------------------------------------------------------
	string getWindowSpecialName(int index) {
		if (index > windowsAtributes.size() - 1 || index == -1)
		{
			ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
			return "-1";
		}

		return windowsAtributes[index].bGui.getName();
	}

	//--------------------------------------------------------------
	ofRectangle getRectangleWindowSpecial(int index) {
		if (index > windowsAtributes.size() - 1 || index == -1)
		{
			ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
		}

		return windowsAtributes[index].rectShapeWindow;
	}
private:
	//--------------------------------------------------------------
	void addWindow(std::string name, bool bPowered = false) { // -> legacy api
		addWindowSpecial(name, bPowered);
	}
public:
	//--------------------------------------------------------------
	void addWindowSpecial(std::string name, bool bPowered = false) {
		ofParameter<bool> _bGui{ name, true };

		SurfingImGuiWindowAtributes win;
		win.bGui.makeReferenceTo(_bGui);
		win.setPowered(bPowered);

		windowsAtributes.push_back(win);

		params_Panels.add(_bGui);
	}

	//----

	/*
	// params to include packed into layout presets
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameterGroup& group) {
		params_Layouts.add(group);
	}
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameter<bool>& param) {
		params_Layouts.add(param);
	}
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameter<int>& param) {
		params_Layouts.add(param);
	}
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameter<float>& param) {
		params_Layouts.add(param);
	}
	//--------------------------------------------------------------
	void addParameterToLayoutPresets(ofParameter<ofRectangle>& param) {
		params_Layouts.add(param);
	}
	*/

	//----

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
	ofParameter<bool>& getVisible(int index)
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

	struct SurfingImGuiWindowAtributes
	{
		// we queue here the bool paramms that enables the show/hide for each queued window
		ofParameter<bool> bGui{ "Show Gui", true };

		ofParameter<bool> bPoweredWindow{ "_bPoweredWindow", false }; // to include below extra toggles when rendering

		ofParameter<bool> bAutoResize{ "Auto Resize", true };
		ofParameter<bool> bExtra{ "Extra", false };
		ofParameter<bool> bMinimize{ "Minimize", false };
		ofParameter<bool> bAdvanced{ "Advanced", false };
		ofParameter<bool> bDebug{ "Debug", false };

		ofParameter<bool> bReset_Window{ "Reset Window", false };
		void setPowered(bool b) {
			bPoweredWindow = b;
		}

		ofParameter<ofRectangle> rectShapeWindow{ "_WindowSpahe", ofRectangle(), ofRectangle(), ofRectangle() };

	};

	vector<SurfingImGuiWindowAtributes> windowsAtributes;//handles only the manually pre added windows.

	void loadAppSettings();
	void saveAppSettings();

	//----

	//TODO:
	// To be marked outside the scope to populate widgets inside this execution point... ?
	// Should use lambda functions here!

	void beginExtra();
	void endExtra();

	void beginAdvanced();
	void endAdvanced();

	void beginMenu();
	void endMenu();

	//----

	// Docking helpers

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

	void saveLayoutPreset(string path); //-> both group params and ImGui ini files
	void loadLayoutPreset(string path);
	void saveLayoutImGuiIni(string path);
	void loadLayoutImGuiIni(string path);
	void saveLayoutPresetGroup(string path);
	void loadLayoutPresetGroup(string path);

	ofParameter<int> appLayoutIndex{ "Layout Preset", -1, -1, 0 }; // index for the selected preset. -1 is none selected, useful too.
	int appLayoutIndex_PRE = -1;

	ofParameterGroup params_Layouts{ "_LayoutsPresets" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsVisible{ "_LayoutsVisible" }; // all these params will be stored on each layout preset
	ofParameterGroup params_LayoutsExtra{ "_LayoutsExtra" }; // all these params will be stored on each layout preset

	int numPresetsDefault;
	void createLayoutPreset(std::string namePreset = "-1");

	//-

	vector<ofParameter<bool>> bLayoutPresets{ "bLayoutPresets" }; // each window show toggles
	void Changed_Params(ofAbstractParameter &e);
	ofParameterGroup params_LayoutsPanel{ "Layouts Panel" };

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

	// some api simplificators
	//--------------------------------------------------------------
	void startup()
	{
		if (bDocking)
		{
			setupLayout(4); // Default Layout with 4 presets.
			//setupLayout(4); // Default Layout with 4 presets.
		}
	}

	//--------------------------------------------------------------
	void setupDocking() {
		surfingImGuiMode = ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING;
		//surfingImGuiMode = ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED;

		//setupLayout(4);
		setAutoSaveSettings(true);
		setImGuiDocking(true);
		setImGuiDockingModeCentered(true);
		setImGuiAutodraw(true);

		setup();

		////TODO:
		//params_Layouts.clear();
		//params_LayoutsExtra.clear();
		//params_LayoutsVisible.clear();
	}

	//--------------------------------------------------------------
	void setImGuiLayoutPresets(bool b) {
		bUseLayoutPresetsManager = b;
	}

public:

	void drawSpecialWindowsPanel();
	void draw_ImGuiMenu();

private:

#define LAYOUT_WINDOW_WIDTH 150

	void updateLayout();

	void drawLayouts();
	void drawLayoutsExtra();
	void drawLayoutsPresets();
	void drawLayoutsPanels();
	void drawLayoutEngine();
	void drawOFnative();

	ofParameter<bool> bAutoResizePanels{ "AutoResize Panels ", false };

	// For different behaviour. We can disable to save some windows positions to allow them locked when changing presets.
	ofParameter<bool> bModeFree{ "Free", true }; // -> A allows storing position for control windows too
	ofParameter<bool> bModeForced{ "Forced", false }; // -> Locked to free space on viewport
	ofParameter<bool> bModeLock1{ "Lock B", false }; // -> Cant be moved. To be used in presets panel
	ofParameter<bool> bModeLockControls{ "Lock C", false }; // -> Cant be moved. To be used to lock to free viewport scenarios
	ofParameter<bool> bModeLockPreset{ "Lock A", false }; // -> Cant be moved. To be used to lock to free viewport scenarios
	//TODO: it's a problem if .ini files are already present... We must ingore loading.

	ofParameter<bool> bDebugDocking{ "Debug Docking", false };

	ofParameter<bool> bDebugRectCentral{ "Rectangle Central", false };
	ofRectangle rectangle_Central_MAX;
	ofRectangle rectangle_Central; // current free space viewport updated when changes
	ofRectangle rectangle_Central_Transposed;

	// standalone window not handled by .ini layout
	// but for the app settings
	//float widthGuiLayout;

	//ofParameter<glm::vec2> positionGuiLayout{ "Gui Layout Position",
	//glm::vec2(ofGetWidth() / 2,ofGetHeight() / 2),//center
	//	glm::vec2(0,0),
	//	glm::vec2(ofGetWidth(), ofGetHeight())
	//};

	//ofParameter<glm::vec2> shapeGuiLayout{ "Gui Layout Shape",
	//	glm::vec2(ofGetWidth() / 2,ofGetHeight() / 2),//center
	//	glm::vec2(0,0),
	//	glm::vec2(ofGetWidth(), ofGetHeight())
	//};

	//-

	// customize titles

public:

	//--------------------------------------------------------------
	void setLabelLayoutPanels(string label) { // -> customize the app name for panels window label tittle
		bGui_LayoutsPanels.setName(label);
	}
	//--------------------------------------------------------------
	void setLabelLayoutMainWindow(string label) {
		bGui_LayoutsManager.setName(label);
	}

	//-

public:

	ofParameter<bool> bMenu{ "Menu", false };

private:

	ofParameter<bool> bGui_LayoutsPanels{ "Panels", true };
	ofParameter<bool> bGui_LayoutsPresets{ "Presets", true };
	ofParameter<bool> bGui_LayoutsExtra{ "Extra Tools", false };
	ofParameter<bool> bGui_LayoutsManager{ "Manager", false };

	ofParameter<bool> bAutoSave_Layout{ "Auto Save", true };
	ofParameter<bool> bUseLayoutPresetsManager{ "bUseLayoutPresetsManager", false };//cant be changed on runtime. cant include into settings
	ofParameter<bool> bDocking{ "bDocking", true };
	ofParameter<bool> bSolo{ "Solo", false };
	ofParameter<bool> bLog{ "Log", false };

	//-

	ofParameterGroup params_LayoutPresetsStates{ "LayoutPanels" };
	ofParameterGroup params_Panels{ "Params Panels" };

	ImGuiWindowFlags flagsWindowsLocked1;//used for presets panel
	ImGuiWindowFlags flagsWindowsLocked2;//used for other control panels
	ImGuiWindowFlags flagsWindowsModeFreeStore;//used to unlink main control panels (presets, manager, extra, panels) from presets

	string titleWindowLabel;

	//-

	//TODO: learn to use lambda functions
	// to callback reset
	// -> subscribe an optional reset flagging a bool to true to reset. Uses the gui Reset button on the Presets Extra panel.
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
		bModeLockControls = b;
		bGui_LayoutsPanels = b;
		bGui_LayoutsPresets = b;
		bGui_LayoutsExtra = false;
	}

	//--------------------------------------------------------------
	void doRemoveDataFiles() {

		// remove all the settings folder
		const filesystem::path path = path_Global;
		ofDirectory::removeDirectory(path, true, true);

		// remove ini file
		const filesystem::path file = ofToDataPath("../imgui.ini");
		ofFile::removeFile(file, true);
	}


};
