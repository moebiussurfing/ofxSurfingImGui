#include "ofxSurfing_ImGui_LayoutManager.h"

//--------------------------------------------------------------
ofxSurfing_ImGui_Manager::ofxSurfing_ImGui_Manager() {

	params_Advanced.add(bAdvanced);
	params_Advanced.add(bAutoResize);
	params_Advanced.add(bExtra);
	params_Advanced.add(bMinimize);

	//-

	// must be here to allow to be changed before setup!
	//// EXAMPLE
	//guiManager.setImGuiAutodraw(true);
	//guiManager.setup(); // this instantiates and configurates ofxImGui inside the class object.

	// -> TODO: BUG?: 
	// it seems than requires to be false when using multi-context/instances
	// if is setted to true, sometimes it hangs and gui do not refresh/freezes.
	bAutoDraw = false;

	//bAutoDraw = true;
	//if(bAutoSaveSettings) loadGroup(params_AppSettings, path_AppSettings);
}

//--------------------------------------------------------------
ofxSurfing_ImGui_Manager::~ofxSurfing_ImGui_Manager() {
	ofRemoveListener(params_LayoutPresetsStates.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);
	ofRemoveListener(params_AppSettings.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);
	ofRemoveListener(params_Panels.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);

	if (bAutoSaveSettings) saveAppSettings();
	//if (bAutoSaveSettings) ofxImGuiSurfing::saveGroup(params_AppSettings, path_AppSettings);
	//if (bAutoSaveSettings) ofxImGuiSurfing::saveGroup(params_AppSettings, path_AppSettings);//now into layout presets
}

//--

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setup() { // using internal instantiated gui

	setupImGui();

	//-

	path_Global = "ImGuiLayout/";
	ofxImGuiSurfing::CheckFolder(path_Global);

	path_ImLayouts = path_Global + "Presets/";
	ofxImGuiSurfing::CheckFolder(path_ImLayouts);

	path_AppSettings = path_Global + bGui_Panels.getName() + "_" + "AppSettings.json";//this allow multiple addons instaces with settings
	//path_AppSettings = path_Global + "AppSettings.json";//file will be shared between all addon instances! take care or set to not autosave (setAutoSaveSettings(false))
	//path_LayoutSettings = path_Global + "imgui_LayoutPresets.json";

	//setupLayout(); //-> must call manually after adding windows and layout presets
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setup(ofxImGui::Gui & _gui) { // using external instantiated gui
	guiPtr = &_gui;

	setupImGui();
}

//----

// fonts

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setDefaultFontIndex(int index)
{
	if (customFonts.size() == 0) return;

	currFont = ofClamp(index, 0, customFonts.size() - 1);
	customFont = customFonts[currFont];
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setDefaultFont()
{
	setDefaultFontIndex(0);
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::pushFont(std::string path, int size)
{
	//TODO:
	// should be a vector with several customFont to allow hot reloading..
	// if not, last added font will be used
	ofLogNotice(__FUNCTION__) << path << ":" << size;

	auto &io = ImGui::GetIO();
	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();

	ofFile fileToRead(path); // a file that exists
	bool b = fileToRead.exists();
	if (b)
	{
		ImFont* _customFont = nullptr;
		if (guiPtr != nullptr) {
			_customFont = guiPtr->addFont(path, size, nullptr, normalCharRanges);
		}
		else {
			_customFont = gui.addFont(path, size, nullptr, normalCharRanges);
		}

		if (_customFont != nullptr)
		{
			customFonts.push_back(_customFont);
			customFont = _customFont;
			currFont = customFonts.size() - 1;
		}
	}
	if (customFont != nullptr) io.FontDefault = customFont;

	return b;
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::addFont(std::string path, int size)
{
	//TODO:
	// should be a vector with several customFont to allow hot reloading..
	// if not, last added font will be used

	auto &io = ImGui::GetIO();
	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();

	ofFile fileToRead(path); // a file that exists
	bool b = fileToRead.exists();
	if (b)
	{
		if (guiPtr != nullptr) customFont = guiPtr->addFont(path, size, nullptr, normalCharRanges);
		else customFont = gui.addFont(path, size, nullptr, normalCharRanges);
	}

	if (customFont != nullptr) io.FontDefault = customFont;

	return b;
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::pushStyleFont(int index)
{
	if (index <= customFonts.size() - 1)
	{
		if (customFonts[index] != nullptr)
			ImGui::PushFont(customFonts[index]);
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::popStyleFont()
{
	ImGui::PopFont();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::processOpenFileSelection(ofFileDialogResult openFileResult, int size = 10) {

	string path = openFileResult.getPath();

	ofLogNotice(__FUNCTION__) << "getName(): " << openFileResult.getName();
	ofLogNotice(__FUNCTION__) << "getPath(): " << path;

	ofFile file(path);

	if (file.exists())
	{
		ofLogNotice(__FUNCTION__) << ("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());

		//We only want images
		if (fileExtension == "TTF" || fileExtension == "OTF") {

			ofLogNotice(__FUNCTION__) << ("TTF or OTF found!");

			pushFont(path, size);
		}
		else ofLogError(__FUNCTION__) << ("TTF or OTF not found!");
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::openFileFont(int size)
{
	// Open the Open File Dialog
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a font file, ttf or otf to add to ImGui", false, ofToDataPath(""));

	// Check if the user opened a file
	if (openFileResult.bSuccess) {

		ofLogNotice(__FUNCTION__) << ("User selected a file");

		//We have a file, check it and process it
		processOpenFileSelection(openFileResult, size);

	}
	else {
		ofLogNotice(__FUNCTION__) << ("User hit cancel");
	}
}

//----

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setupImGui()
{
	ImGuiConfigFlags flags = ImGuiConfigFlags_None;

	bool bRestore = true;
	bool bMouse = false;

	if (bDocking) flags += ImGuiConfigFlags_DockingEnable;
	if (bViewport) flags += ImGuiConfigFlags_ViewportsEnable;

	// Setup imgui with the appropriate config flags
	if (guiPtr != nullptr) guiPtr->setup(nullptr, bAutoDraw, flags, bRestore, bMouse);
	else gui.setup(nullptr, bAutoDraw, flags, bRestore, bMouse);

	// Uncomment below to perform docking with SHIFT key
	// Gives a better user experience, matter of opinion.
	if (bDocking) ImGui::GetIO().ConfigDockingWithShift = true;

	// Uncomment below to "force" all imgui windows to be standalone
	//ImGui::GetIO().ConfigViewportsNoAutoMerge=true;

	//-

	//TODO: crashes if font not present!

	// font
	std::string _fontName;
	float _fontSizeParam;
	_fontName = FONT_DEFAULT_FILE; // WARNING: will crash if font not present!
	_fontSizeParam = FONT_DEFAULT_SIZE;
	std::string _path = "assets/fonts/"; // assets folder

	pushFont(_path + _fontName, _fontSizeParam); // queue default font too

	addFont(_path + _fontName, _fontSizeParam);

	//-

	// Theme: colors and sizes
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::draw() {
	if (customFont == nullptr) gui.draw();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::updateLayout() {

	// layouts

	if (ini_to_load)
	{
		ofLogNotice(__FUNCTION__) << "LOAD! " << ini_to_load;

		loadLayoutImGuiIni(ini_to_load);

		ini_to_load = NULL;
	}

	if (ini_to_save)
	{
		ofLogNotice(__FUNCTION__) << "SAVE! " << ini_to_save;

		if (ini_to_save != "-1")
		{
			saveLayoutPreset(ini_to_save);
		}

		ini_to_save = NULL;
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutsManager() {

	static bool _bAutoResize = true;
	static ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (_bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	window_flags |= ImGuiWindowFlags_NoSavedSettings; // exclude from restore preset layouts

	//-

	if (bModeFreeStore)
	{
		ImGuiCond flagCond;
		flagCond = ImGuiCond_Appearing;
		//flagCond = ImGuiCond_Always;
		const int i = 2;
		ImGui::SetNextWindowPos(ofVec2f(rectPanels[i].get().getX(), rectPanels[i].get().getY()), flagCond);
		ImGui::SetNextWindowSize(ofVec2f(rectPanels[i].get().getWidth(), rectPanels[i].get().getHeight()), flagCond);
	}

	//-

	beginWindow(bGui_LayoutsManager, window_flags);
	//if (beginWindow(bGui_LayoutsManager, window_flags))
	{
		const int i = 2;
		rectPanels[i].setWithoutEventNotifications(ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()));

		//-

		//ImGui::Text("Layout Presets");

		float _w = ofxImGuiSurfing::getWidgetsWidth();
		float _h = 2 * ofxImGuiSurfing::getWidgetsHeightRelative();

		AddBigToggle(bGui_Panels, _w, _h, true);
		AddBigToggle(bGui_LayoutsPresets, _w, _h, true);
		//AddToggleRoundedButton(bGui_Panels);
		//AddToggleRoundedButton(bGui_LayoutsPresets);
		//AddToggleRoundedButton(bGui_LayoutsExtra);

		ImGui::Separator();

		//-

		ImGui::Text("Panels");
		for (int i = 0; i < windowsAtributes.size(); i++)
		{
			AddToggleRoundedButton(windowsAtributes[i].bGui);
		}

		//ImGui::Spacing();

		float _w50 = ofxImGuiSurfing::getWidgetsWidth(2);
		if (ImGui::Button("All", ImVec2(_w50, _h / 2)))
		{
			bool b = true;
			for (int i = 0; i < windowsAtributes.size(); i++)
			{
				windowsAtributes[i].bGui.set(b);
			}
			bGui_Menu = b;
			bLockLayout = b;
			bGui_Panels = b;
			bGui_LayoutsPresets = b;
			bGui_LayoutsExtra = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("None", ImVec2(_w50, _h / 2)))
		{
			bool b = false;
			for (int i = 0; i < windowsAtributes.size(); i++)
			{
				windowsAtributes[i].bGui.set(b);
			}
			bGui_Menu = b;
			bLockLayout = b;
			bGui_Panels = b;
			bGui_LayoutsPresets = b;
			bGui_LayoutsExtra = false;
		}

		ImGui::Separator();

		//-

		ImGui::Text("Parameters");
		AddToggleRoundedButton(bGui_Menu);
		ImGui::Separator();

		//-

		ImGui::Text("Docking");
		AddToggleRoundedButton(bDebugDocking);
		if (bDebugDocking) {
			ImGui::Indent();
			//AddToggleRoundedButton(bUseLayoutPresetsManager);
			AddToggleRoundedButton(bDocking);
			ToggleRoundedButton("bDockingModeCentered", &bDockingModeCentered);
			ToggleRoundedButton("Viewport", &bPreviewSceneViewport);
			AddToggleRoundedButton(bDebugRectCentral);
			ImGui::Unindent();
		}

		//endWindow();
	}
	endWindow();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayouts() {

	//TODO:
	// how to make all windows dockeable in the same space?
	if (bGui_LayoutsExtra) drawLayoutsExtra();
	if (bGui_LayoutsPresets) drawLayoutsPresets();
	if (bGui_Panels) drawLayoutsPanels();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutScene() {

	if (bGui_LayoutsManager) drawLayoutsManager();

	//----

	if (bUseLayoutPresetsManager)
	{
		updateLayout();

		//drawLayouts();

		//----

		ImGuiDockNodeFlags flagsDock;
		ImGuiID dockNodeID;
		ImGuiDockNode* centralNode;
		ImGuiDockNode* dockNode;
		ImGuiDockNodeFlags dockingFlags;

		if (bDocking)
		{
			//----

			// a. Define the ofWindow as a docking space

			//ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0)); // Fixes imgui to expected behaviour. Otherwise add in ImGui::DockSpace() [±line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
			//ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_PassthruCentralNode);
			//ImGui::PopStyleColor();

			//-

			// b. Lockable settings 

			// Fixes imgui to expected behaviour. Otherwise add in ImGui::DockSpace() [±line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
			//ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
			flagsDock = ImGuiDockNodeFlags_PassthruCentralNode;
			if (bLockLayout)
			{
				flagsDock |= ImGuiDockNodeFlags_NoResize;
				flagsDock |= ImGuiDockNodeFlags_NoCloseButton;
				//flagsDock |= ImGuiDockNodeFlags_NoTabBar;
				//flagsDock |= ImGuiDockNodeFlags_NoWindowMenuButton;
				//flagsDock |= ImGuiDockNodeFlags_NoMove__;
			}
			dockNodeID = ImGui::DockSpaceOverViewport(NULL, flagsDock);
			//ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, flagsDock);
			//ImGui::PopStyleColor();

			//----

			// get check free space
			// central inter docks rectangle
			//ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, flagsDock);

			ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(dockNodeID);
			if (dockNode)
			{
				ImGuiDockNode* centralNode = ImGui::DockBuilderGetCentralNode(dockNodeID);
				// Verifies if the central node is empty (visible empty space for oF)
				if (centralNode && centralNode->IsEmpty())
				{
					ImRect availableSpace = centralNode->Rect();
					//availableSpace.Max = availableSpace.Min + ImGui::GetContentRegionAvail();
					//ImGui::GetForegroundDrawList()->AddRect(availableSpace.GetTL() + ImVec2(8, 8), availableSpace.GetBR() - ImVec2(8, 8), IM_COL32(255, 50, 50, 255));

					ImVec2 viewCenter = availableSpace.GetCenter();
					// Depending on the viewports flag, the XY is either absolute or relative to the oF window.
					if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());

					float ww = availableSpace.GetSize().x;
					float hh = availableSpace.GetSize().y;
					rectangle_Central_MAX = ofRectangle(viewCenter.x, viewCenter.y, ww, hh);

					bool bDebug = bDebugRectCentral.get();
					if (bDebug)
					{
						int _wl = 2;
						int pad = 10;

						ofPushStyle();
						ofSetRectMode(OF_RECTMODE_CENTER);

						int g = 0;
						ofColor cl(0, 255, 255, 200);

						//int g = 255 * ofxSurfingHelpers::Bounce(0.5);
						int a = 255.f * ofMap(ofxSurfingHelpers::Bounce(1), 0.0f, 1.0f, 0.2f, 1.0f, true);
						ofColor c = ofColor(cl.r, cl.g, cl.b, a);
						//ofColor c = ofColor(g, a);
						ofSetColor(c);

						ofNoFill();
						ofSetLineWidth(_wl);

						ofRectangle rDebug;
						float ww = availableSpace.GetSize().x - pad;
						float hh = availableSpace.GetSize().y - pad;
						rDebug = ofRectangle(viewCenter.x, viewCenter.y, ww, hh);
						ofDrawRectangle(rDebug);

						//ofDrawRectangle(rectangle_Central_MAX);
						ofSetRectMode(OF_RECTMODE_CORNER);
						ofPopStyle();
					}
					// move to left corner mode
					rectangle_Central_MAX.translate(-ww / 2, -hh / 2);

					//-

					static ofRectangle rectangle_Central_MAX_PRE;
					if (rectangle_Central_MAX_PRE != rectangle_Central_MAX) {//update when layout canges..
						rectangle_Central_MAX_PRE = rectangle_Central_MAX;

						// fit exact rectangle to borders and scaled to fit
						//rectangle_Central = DEMO3_Svg.getRect();
						//if (rectangle_Central_MAX.getWidth() != 0 && rectangle_Central_MAX.getHeight() != 0) // avoid crash
						rectangle_Central.scaleTo(rectangle_Central_MAX, OF_ASPECT_RATIO_KEEP, OF_ALIGN_HORZ_CENTER, OF_ALIGN_VERT_CENTER);

						//// rescaled rectangle a bit
						//float _scale = 0.7f;
						//rectangle_Central_Transposed = rectangle_Central;
						//rectangle_Central_Transposed.scaleFromCenter(_scale, _scale);//scale down to fit layout spacing better
						//rectangle_Central_Transposed.translateY(rectangle_Central.getHeight() * 0.07);//move down a bit
						//DEMO3_Svg.setRect(rectangle_Central_Transposed);
					}
				}
			}

			//endWindow();
		}

		//----

		////TODO:
		//setDefaultFont();

		//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh)); // minimal size

		//-

		/*
		// docking
		if (bDocking && bDockingModeCentered)
		{
			dockingFlags = ImGuiDockNodeFlags_PassthruCentralNode; // Make the docking space transparent
			dockNodeID = ImGui::DockSpaceOverViewport(NULL, dockingFlags); // Also draws the docked windows
			dockNode = ImGui::DockBuilderGetNode(dockNodeID);

			//ImGuiDockNodeFlags dockingFlags = ImGuiDockNodeFlags_PassthruCentralNode; // Make the docking space transparent
			//ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, dockingFlags); // Also draws the docked windows
			//ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(dockNodeID);

			if (dockNode)
			{
				ImGuiDockNode* centralNode = ImGui::DockBuilderGetCentralNode(dockNodeID);

				// debug scene viewport
				if (bPreviewSceneViewport)
				{
					// Verifies if the central node is empty (visible empty space for oF)
					if (centralNode && centralNode->IsEmpty())
					{
						ImRect availableSpace = centralNode->Rect();
						//availableSpace.Max = availableSpace.Min + ImGui::GetContentRegionAvail();
						ImGui::GetForegroundDrawList()->AddRect(availableSpace.GetTL() + ImVec2(8, 8), availableSpace.GetBR() - ImVec2(8, 8), IM_COL32(255, 50, 50, 255));

						ImVec2 viewCenter = availableSpace.GetCenter();
						// Depending on the viewports flag, the XY is either absolute or relative to the oF window.
						if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());
						ofPushStyle();
						ofSetRectMode(OF_RECTMODE_CENTER);
						ofSetColor(255, 0, 0, 200);
						ofNoFill();

						static int pad = 15;

						ofDrawRectangle(
							viewCenter.x,
							viewCenter.y,
							availableSpace.GetSize().x - pad,
							availableSpace.GetSize().y - pad
						);
						//ofNoFill();
						//ofSetColor(255, 255, 255, 30);
						//ofDrawRectangle(
						//	(viewCenter.x),
						//	(viewCenter.y),
						//	(availableSpace.GetSize().x - 20)*fmodf(abs(sin(ofGetElapsedTimef())), 1.f),
						//	(availableSpace.GetSize().y - 20)*fmodf(abs(sin(ofGetElapsedTimef())), 1.f)
						//);
						ofSetRectMode(OF_RECTMODE_CORNER);
						ofPopStyle();
					}
				}
			}
		}
		*/

		//-

		//// b. Lockable settings 

		//// Fixes imgui to expected behaviour. Otherwise add in ImGui::DockSpace() [±line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
		////ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		//ImGuiDockNodeFlags flagsDock;
		//flagsDock = ImGuiDockNodeFlags_PassthruCentralNode;
		//if (bLockLayout)
		//{
		//	flagsDock |= ImGuiDockNodeFlags_NoResize;
		//	flagsDock |= ImGuiDockNodeFlags_NoCloseButton;
		//	//flagsDock |= ImGuiDockNodeFlags_NoTabBar;
		//	//flagsDock |= ImGuiDockNodeFlags_NoWindowMenuButton;
		//	//flagsDock |= ImGuiDockNodeFlags_NoMove__;
		//}
		//ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, flagsDock);
		////ImGui::PopStyleColor();
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::begin() {
	if (guiPtr != nullptr) guiPtr->begin();
	else gui.begin();

	resetIDs(); // reset names

	if (customFont != nullptr) ImGui::PushFont(customFont);

	//TODO:
	setDefaultFont();

	//----

	drawLayoutScene();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::end() {

	//ImGui::PopStyleVar(); // minimal size

	if (customFont != nullptr) ImGui::PopFont();

	// mouse lockers
	bMouseOverGui = false;
	bMouseOverGui = bMouseOverGui | ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
	bMouseOverGui = bMouseOverGui | ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
	bMouseOverGui = bMouseOverGui | ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);

	if (guiPtr != nullptr) guiPtr->end();
	else gui.end();
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(string name)
{
	return beginWindow(name, NULL, ImGuiWindowFlags_None);
}
//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(std::string name, bool* p_open) {
	return beginWindow(name, p_open, ImGuiWindowFlags_None);
}
//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(ofParameter<bool> p)
{
	return beginWindow(p.getName().c_str(), (bool*)&p.get(), ImGuiWindowFlags_None);
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(ofParameter<bool> p, ImGuiWindowFlags window_flags)
{
	return beginWindow(p.getName().c_str(), (bool*)&p.get(), window_flags);
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(string name = "Window", bool* p_open = NULL, ImGuiWindowFlags window_flags = ImGuiWindowFlags_None)
{
	//static bool no_close = true;
	//if (no_close) p_open = NULL; // Don't pass our bool* to Begin

	// force
	//window_flags |= ImGuiWindowFlags_NoDecoration;

	// bAutoResize mode
	//static bool bAutoResize = true;

	// minimal sizes
	//float ww = PANEL_WIDGETS_WIDTH_MIN;
	//float hh = PANEL_WIDGETS_HEIGHT_MIN;
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));

	//// Demonstrate the various window flags. Typically you would just use the default!
	//static bool no_titlebar = false;
	//static bool no_scrollbar = false;
	//static bool no_menu = false;
	//static bool no_move = false;
	//static bool no_resize = false;
	//static bool no_collapse = false;
	//static bool no_nav = false;
	//static bool no_background = false;
	//static bool no_bring_to_front = false;
	//static bool no_docking = false;

	////ImGuiWindowFlags window_flags = false;
	//if (bAutoResize)        window_flags |= ImGuiWindowFlags_AlwaysAutoResize;//not working, not ending expands..
	//if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	//if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	//if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	//if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	//if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	//if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	//if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	//if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	//if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	//if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;

	//-

	//// We specify a default position/size in case there's no data in the .ini file.
	//// We only do it to make the demo applications a little more welcoming, but typically this isn't required.
	//const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	//ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	// Main body of the Demo window starts here.
	bool b = ImGui::Begin(name.c_str(), p_open, window_flags);
	//if (!b)
	//{
	//	//// Early out if the window is collapsed, as an optimization.
	//	//ImGui::End();
	//	//return;
	//}

	// refresh layout
	widgetsManager.refresh();

	// set default font
	setDefaultFont();

	// Leave a fixed amount of width for labels (by passing a negative value), the rest goes to widgets.
	//ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	return b;
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::endWindow()
{
	//ImGui::PopItemWidth();
	//ImGui::PopStyleVar();

	ImGui::End();
}

//--

// docking helpers
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::beginDocking()
{
	//dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	if (bGui_Menu) window_flags |= ImGuiWindowFlags_MenuBar;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	//viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	window_flags
		|= ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove;

	window_flags
		|= ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoNavFocus;

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", nullptr, window_flags);

	//----

	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		//dockspace_flags |= ImGuiConfigFlags_DockingEnable

		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		//ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

		//--

		// original code example:
		//	static auto first_time = true;
		//	if (first_time)
		//	{
		//		first_time = false;
		//		ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
		//		ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
		//		ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);
		//		// split the dockspace into 2 nodes -- 
		//		// DockBuilderSplitNode takes in the following args in the following order
		//		//   window ID to split, direction, fraction (between 0 and 1), 
		//		// the final two setting let's us choose which id we want (which ever one we DON'T set as NULL, 
		//		// will be returned by the function)
		//		// out_id_at_dir is the id of the node in the direction we specified earlier, 
		//		// out_id_at_opposite_dir is in the opposite direction
		//		auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.1f, nullptr, &dockspace_id);
		//		auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
		//		auto dock_id_left2 = ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.2f, nullptr, &dock_id_left);
		//		auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);
		//		auto dock_id_down2 = ImGui::DockBuilderSplitNode(dock_id_down, ImGuiDir_Right, 0.15f, nullptr, &dock_id_down);
		//		// we now dock our windows into the docking node we made above
		//		ImGui::DockBuilderDockWindow("Window1", dock_id_top);
		//		ImGui::DockBuilderDockWindow("Down", dock_id_down);
		//		ImGui::DockBuilderDockWindow("Left", dock_id_left);
		//		ImGui::DockBuilderDockWindow("Window1", dock_id_left2);
		//		ImGui::DockBuilderDockWindow("Window2", dock_id_down2);
		//		ImGui::DockBuilderFinish(dockspace_id);
		//	}
		//}
		//ImGui::End();
	}

	//--

	drawLayouts();

}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::endDocking()
{
	//if (bGui_Menu) draw_ImGuiMenu();

	//-

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
	}

	ImGui::End();
}

//----

// layouts presets management
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setupLayout(int numPresets) //-> must call manually after adding windows and layout presets
{
	numPresetsDefault = numPresets;//default is 4

	//-

	bGui_LayoutsManager = true;
	//bGui_Menu = true;

	//-

	// 1.1 define all the panel show toggles

	//params_Layouts.clear();
	for (int i = 0; i < windowsAtributes.size(); i++)
	{
		params_Layouts.add(windowsAtributes[i].bGui);
	}

	// 1.2 add other settings that we want to store into each presets
	params_Layouts.add(bGui_Menu);

	//-

	/*
	// 2. define the layouts presets
	// adds toggles to preset states

	// NOTE: define your layout presets here!
	// TODO: can be performed on runtime!

	// queue each preset pushing his bool toggle at the same time
	// so the amnount and name of the presets are variable!
	ofParameter<bool> b0{ "Default", false };
	ofParameter<bool> b1{ "User", false };
	ofParameter<bool> b2{ "Minimal", false };
	//ofParameter<bool> b3{ "MINIMAL", false };
	//ofParameter<bool> b4{ "USER", false };

	bLayoutPresets.clear();
	bLayoutPresets.push_back(b0);
	bLayoutPresets.push_back(b1);
	bLayoutPresets.push_back(b2);
	//bLayoutPresets.push_back(b3);
	//bLayoutPresets.push_back(b4);

	appLayoutIndex.setMax(bLayoutPresets.size() - 1);

	//-

	// 3. adds the app param settings that will be linked with the presets

	// will change and memorized on each layout preset!
	for (int i = 0; i < bLayoutPresets.size(); i++) {
		params_LayoutPresetsStates.add(bLayoutPresets[i]);
	}
	//params_LayoutPresetsStates.add(b0, b1, b2, b3, b4);
	*/

	//--

	// initiate
	bLayoutPresets.clear();
	params_LayoutPresetsStates.clear();
	appLayoutIndex.setMax(0);

	// populate some presets
	for (int i = 0; i < numPresetsDefault; i++) {
		createLayoutPreset();
	}

	//--

	// 4. app states for the next session

	// the main control windows
	params_LayoutSettings.add(bGui_LayoutsPresets);
	params_LayoutSettings.add(bGui_LayoutsExtra);
	params_LayoutSettings.add(bGui_Panels);

	params_LayoutSettings.add(bAutoSave_Layout);
	params_LayoutSettings.add(bForceLayoutPosition);
	params_LayoutSettings.add(bLockLayout);
	params_LayoutSettings.add(bModeFreeStore);
	//params_LayoutSettings.add(bGui_Menu);
	//params_LayoutSettings.add(bDebugRectCentral);
	params_LayoutSettings.add(appLayoutIndex);

	params_AppSettings.add(bGui_LayoutsManager);
	params_AppSettings.add(params_LayoutSettings);
	params_AppSettings.add(params_Advanced);

	//-

	// exclude from settings but to use the grouped callback
	bSolo.setSerializable(false);
	params_AppSettings.add(bSolo);

	//-

	ofAddListener(params_LayoutPresetsStates.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);
	ofAddListener(params_AppSettings.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);
	ofAddListener(params_Panels.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);

	//-

	// initiate the 3 control windows
	// we store the shapes using ofrectangles to split them from ImGui .ini store manager..

	ofParameter<ofRectangle> r1{ "rect_Presets", ofRectangle(), ofRectangle(), ofRectangle() };
	ofParameter<ofRectangle> r2{ "rect_Panels", ofRectangle(), ofRectangle(), ofRectangle() };
	ofParameter<ofRectangle> r3{ "rect_Manager", ofRectangle(), ofRectangle(), ofRectangle() };

	rectPanels.clear();
	rectPanels.emplace_back(r1);
	rectPanels.emplace_back(r2);
	rectPanels.emplace_back(r3);

	params_RectPanels.clear();
	params_RectPanels.add(r1);
	params_RectPanels.add(r2);
	params_RectPanels.add(r3);
	params_AppSettings.add(params_RectPanels);

	//--

	setImGuiLayoutPresets(true);
	//setAutoSaveSettings(true);

	// startup
	loadAppSettings();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadAppSettings()
{
	if (bAutoSaveSettings) ofxImGuiSurfing::loadGroup(params_AppSettings, path_AppSettings, true);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveAppSettings()
{
	if (bAutoSaveSettings) ofxImGuiSurfing::saveGroup(params_AppSettings, path_AppSettings, true);
	//if (bAutoSaveSettings) ofxImGuiSurfing::saveGroup(params_AppSettings, path_AppSettings, true);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveAppLayout(int _index)
{
	if (_index == -1) return;

	ini_to_save_Str = getLayoutName(_index);

	ofLogNotice(__FUNCTION__) << ini_to_save_Str;

	if (ini_to_save_Str == "-1") return; // skip

	// flag to save .ini on update
	ini_to_save = ini_to_save_Str.c_str();

	// save group
	saveLayoutPresetGroup(ini_to_save);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadAppLayout(int _index)
{
	if (_index == -1) return;

	//if (appLayoutIndex == _index) return; // skip

	appLayoutIndex = ofClamp(_index, appLayoutIndex.getMin(), appLayoutIndex.getMax());

	string _name = getLayoutName(appLayoutIndex.get());
	ofLogNotice(__FUNCTION__) << appLayoutIndex << ":" << _name;

	//std::string _label = APP_RELEASE_NAME;
	std::string _label = "";
	_label += "App Layout ";
	_label += " "; // spacing

	if (!bLayoutPresets[appLayoutIndex.get()])
	{
		for (int i = 0; i < bLayoutPresets.size(); i++) {
			bLayoutPresets[i].set(false);
		}
		bLayoutPresets[_index].set(true);
	}

	// window title
	titleWindowLabel = _label + " " + _name;
	//titleWindowLabel = _label + " " + ofToString(appLayoutIndex.get()) + " " + _name;

	//// apply window title
	//ofSetWindowTitle(titleWindowLabel);

	// ini
	ini_to_load_Str = _name;
	ini_to_load = ini_to_load_Str.c_str();

	// group
	loadLayoutPresetGroup(ini_to_load_Str);

	ofLogNotice(__FUNCTION__) << "------------------------------------";
	ofLogNotice(__FUNCTION__) << "ini_to_load    : " << ini_to_load;
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutsPresets()
{
	static bool auto_resize = true;
	ImGuiWindowFlags window_flags = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;
	window_flags |= ImGuiWindowFlags_NoSavedSettings; // exclude from restore preset layouts
	//window_flags |= ImGuiWindowFlags_NoSavedSettings;//exclude from restore layouts
	//window_flags |= flagsWindowsLocked;

	static float CURRENT_WINDOW_MIN_HEIGHT = 220;

	// blink save button to clarify workflow
	float a = ofxSurfingHelpers::getFadeBlink(0.2, 0.8, 0.15);

	//----

	// center
	// is excluded from .ini
	float xw, yw, ww, hw;

	ww = LAYOUT_WINDOW_WIDTH;
	hw = CURRENT_WINDOW_MIN_HEIGHT;

	//xw = ofGetWidth() / 2 - ww / 2;
	//yw = ofGetHeight() / 2 - hw / 2;

	if (!bModeFreeStore.get())
	{
		ImGuiCond flagCond;

		if (bForceLayoutPosition)
		{
			//// upper left
			//glm::vec2 p = rectangle_Central_MAX.getTopLeft() + glm::vec2(-1, -1);

			// center upper left
			int _pad = 10;
			int _xx = rectangle_Central_MAX.getTopLeft().x + _pad;
			int _yy = rectangle_Central_MAX.getTopLeft().y + rectangle_Central_MAX.getHeight() / 2 - hw / 2;
			glm::vec2 p = glm::vec2(_xx, _yy);

			// shape
			xw = p.x;
			yw = p.y;

			flagCond = ImGuiCond_Always;
		}
		else
		{
			//TODO:
			//// shape
			//xw = shapeGuiLayout.get().x;
			//yw = shapeGuiLayout.get().y;
			xw = positionGuiLayout.get().x;
			yw = positionGuiLayout.get().y;

			flagCond = ImGuiCond_Once;
		}

		ImGui::SetNextWindowPos(ofVec2f(xw, yw), flagCond);
		//ImGui::SetNextWindowSize(ofVec2f(ww, hw), flagCond); // exclude shape
	}
	else // bModeFreeStore
	{
		ImGuiCond flagCond;
		flagCond = ImGuiCond_Appearing;
		//flagCond = ImGuiCond_Always;
		const int i = 0;
		ImGui::SetNextWindowPos(ofVec2f(rectPanels[i].get().getX(), rectPanels[i].get().getY()), flagCond);
		ImGui::SetNextWindowSize(ofVec2f(rectPanels[i].get().getWidth(), rectPanels[i].get().getHeight()), flagCond);
	}


	//----

	beginWindow(bGui_LayoutsPresets, window_flags);
	{
		// get window position for advanced layout paired position
		positionGuiLayout = glm::vec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
		shapeGuiLayout = glm::vec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

		const int i = 0;
		rectPanels[i].setWithoutEventNotifications(ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()));

		//--

		const int NUM_WIDGETS = bLayoutPresets.size() + 4;

		float _spcx = ImGui::GetStyle().ItemSpacing.x;
		float _spcy = ImGui::GetStyle().ItemSpacing.y;
		float _w100 = ImGui::GetContentRegionAvail().x;
		float _h100 = ImGui::GetContentRegionAvail().y;
		float _w99 = _w100 - _spcx;
		float _h99 = _h100 - _spcy;
		float _w50 = _w99 / 2;

		float _w;
		float _h;
		_w = ofxImGuiSurfing::getWidgetsWidth(2);
		_h = ofxImGuiSurfing::getWidgetsHeightRelative() * 2;
		//_h = ofxImGuiSurfing::getWidgetsHeight();

		for (int i = 0; i < bLayoutPresets.size(); i++) {
			ofxImGuiSurfing::AddBigToggle(bLayoutPresets[i], _w, _h);
			if (i % 2 == 0) ImGui::SameLine();
		}

		//-

		if (bLayoutPresets.size() % 2 == 0) _w = ofxImGuiSurfing::getWidgetsWidth(1);

		// save button
		if (!bAutoSave_Layout.get())
		{
			ImGuiStyle *style = &ImGui::GetStyle();

			//TODO: get color from button/theme
			ImVec4 butColor = style->Colors[ImGuiCol_FrameBg];
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(butColor.x, butColor.y, butColor.z, butColor.w * a));
			//ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.5f, 0.0f, 0.0f, a));

			// border
			ImVec4 borderLineColor = style->Colors[ImGuiCol_SliderGrab];
			float borderLineWidth = 1.0;

			ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);

			ImGui::PushID("##SaveLayout");
			if (ImGui::Button("Save", ImVec2(_w, _h)))
			{
				saveAppLayout(appLayoutIndex.get());
			}
			ImGui::PopID();

			// border
			ImGui::PopStyleColor();
			ImGui::PopStyleVar(1);

			ImGui::PopStyleColor();
		}

		//-

		_w = ofxImGuiSurfing::getWidgetsWidth(1);
		_h /= 2;

		// one row
		ofxImGuiSurfing::AddBigToggle(bGui_Panels, _w, _h);
		ofxImGuiSurfing::AddBigToggle(bGui_LayoutsExtra, _w, _h);

		/*
		ofxImGuiSurfing::AddBigToggle(bLockLayout, _w50, _h);
		ImGui::SameLine();
		ofxImGuiSurfing::AddBigToggle(bForceLayoutPosition, _w50, _h);
		*/

		//AddToggleRoundedButton(bModeFreeStore);
		ToggleRoundedButton("Auto Resize", &auto_resize);
	}
	endWindow();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::Changed_Params(ofAbstractParameter &e)
{
	std::string name = e.getName();

	ofLogNotice(__FUNCTION__) << name << " : " << e;

	//----

	if (false) {}

	//-

	// gui layout
	else if (name == bGui_LayoutsPresets.getName())
	{
		// workflow
		if (!bGui_LayoutsPresets)
		{
			bGui_LayoutsExtra = false;
		}
	}

	//-

	// solo
	else if (name == bSolo.getName() && bSolo.get())
	{
		// workflow
		appLayoutIndex = -1;
		for (int i = 0; i < bLayoutPresets.size(); i++)
		{
			bLayoutPresets[i].setWithoutEventNotifications(false);
		}
	}

	//-

	// lock layout
	else if (name == bLockLayout.getName())
	{
		if (!bLockLayout)
		{
			flagsWindowsLocked = ImGuiWindowFlags_None;
		}
		else
		{
			flagsWindowsLocked = ImGuiWindowFlags_NoMove;
			//flagsWindowsLocked |= ImGuiWindowFlags_NoResize;
			//flagsWindowsLocked |= ImGuiWindowFlags_NoTitleBar;
			//flagsWindowsLocked |= ImGuiWindowFlags_NoCollapse;
			//flagsWindowsLocked |= ImGuiWindowFlags_NoDecoration;
			//flagsWindowsLocked |= ImGuiWindowFlags_NoBackground;
			//flagsWindowsLocked |= ImGuiDockNodeFlags_AutoHideTabBar;
			//flagsWindowsLocked |= ImGuiDockNodeFlags_NoTabBar;
			//flagsWindowsLocked |= ImGuiDockNodeFlags_NoCloseButton;
		}
	}

	//--

	// layout preset index
	else if (name == appLayoutIndex.getName())
	{
		//appLayoutIndex = ofClamp(appLayoutIndex.get(), appLayoutIndex.getMin(), appLayoutIndex.getMax());

		if (appLayoutIndex != appLayoutIndex_PRE /*&& appLayoutIndex_PRE != -1*/) //changed
		{
			ofLogNotice(__FUNCTION__) << "Changed: " << appLayoutIndex;

			//-

			// 1. autosave
			if (bAutoSave_Layout)
			{
				// workaround:
				// must save here bc usually we use the fallged on update save...
				// only once per cycle allowed this way.
				//force to ensure save bc update chain load and save below
				//saveAppLayout(AppLayouts(appLayoutIndex_PRE));
				std::string __ini_to_save_Str = getLayoutName(appLayoutIndex_PRE);

				if (__ini_to_save_Str != "-1")
				{
					const char* _iniSave = NULL;
					_iniSave = __ini_to_save_Str.c_str(); // flags to save on update

					if (_iniSave != "-1")
					{
						saveLayoutPreset(_iniSave);
					}
				}
			}

			appLayoutIndex_PRE = appLayoutIndex.get();
		}

		//-

		// hide all modules/gui toggles
		if (appLayoutIndex == -1) {
			for (int i = 0; i < windowsAtributes.size(); i++)
			{
				windowsAtributes[i].bGui.set(false);
			}
			return; // not required bc loadAppLayout will be skipped when -1
		}

		//-

		// 2. load layout
		loadAppLayout(appLayoutIndex.get());
	}

	//-

	// presets selector exclusive toggles
	{
		bool bSomeTrue = false;
		for (int i = 0; i < bLayoutPresets.size(); i++)
		{
			if (name == bLayoutPresets[i].getName())
			{
				if (bLayoutPresets[i].get()) // true
				{
					//workflow
					if (bSolo.get()) bSolo = false;

					appLayoutIndex = i;
					bSomeTrue = true;
				}
				else { // false
					// avoid all false
					bool bAllFalse = true;
					for (int i = 0; i < bLayoutPresets.size(); i++)
					{
						if (bLayoutPresets[i].get()) {
							bAllFalse = false;
						}
					}
					if (bAllFalse) {
						//workflow A
						////force back to true if it's there's no other enabled..
						//bLayoutPresets[appLayoutIndex].set(true);

						//workflow B
						//set to -1
						appLayoutIndex = -1;
					}
				}
			}
		}
		if (bSomeTrue) {
			for (int i = 0; i < bLayoutPresets.size(); i++)
			{
				if (i != appLayoutIndex.get())
					bLayoutPresets[i].set(false);
			}
			return;
		}
	}

	//-

	// solo panels selectors
	{
		bool bSomeTrue = false;
		for (int i = 0; i < windowsAtributes.size(); i++)
		{
			int iTrue = -1;
			if (name == windowsAtributes[i].bGui.getName() && windowsAtributes[i].bGui.get()) {
				iTrue = i;
				if (bSolo.get()) {
					for (int i = 0; i < windowsAtributes.size(); i++)
					{
						if (iTrue != i && iTrue != -1) windowsAtributes[i].bGui.set(false);
					}
					return;
				}
			}
		}
	}

	//--
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutsExtra()
{
	static bool auto_resize = true;

	ImGuiWindowFlags flags = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;
	flags |= ImGuiWindowFlags_NoSavedSettings; // exclude from restore preset layouts
	//flags |= flagsWindowsLocked;

	bool bMin = false; // hide load buttons to simplify
	float max = (bMin ? 150 : 175);

	//----

	static float CURRENT_WINDOW_MIN_HEIGHT = 100;

	// position is linked to main layout window
	// is excluded from .ini
	float xw, yw, ww, hw;
	ww = LAYOUT_WINDOW_WIDTH;
	hw = CURRENT_WINDOW_MIN_HEIGHT;
	xw = ofGetWidth() / 2 - ww / 2;
	yw = ofGetHeight() / 2 - hw / 2;

	ImGuiCond _flagc;
	_flagc = ImGuiCond_Always;
	//_flagc = ImGuiCond_FirstUseEver;
	//_flagc = ImGuiCond_Appearing;

	int _pad = PADDING_PANELS;

	//ImGui::SetNextWindowPos(ofVec2f(xw + ww + 2, yw), _flagc);
	//ImGui::SetNextWindowSize(ofVec2f(ww, hw), _flagc);

	//right
	//ImGui::SetNextWindowPos(ofVec2f(positionGuiLayout.get().x + shapeGuiLayout.get().x + _pad, positionGuiLayout.get().y), _flagc);

	//down
	ImGui::SetNextWindowPos(ofVec2f(positionGuiLayout.get().x, positionGuiLayout.get().y + shapeGuiLayout.get().y + _pad), _flagc);


	//----

	//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(max, CURRENT_WINDOW_MIN_HEIGHT));

	beginWindow(bGui_LayoutsExtra, flags);
	{
		float _spcx;
		float _spcy;
		float _w100;
		float _h100;
		float _w99;
		float _w50;
		float _w33;
		float _w25;
		float _h;
		ofxImGuiSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);
		//_h = _h / 2;

		int _id = 0;

		//----

		ofxImGuiSurfing::AddBigToggle(bGui_Panels, _w100, _h);
		ofxImGuiSurfing::AddBigToggle(bAutoSave_Layout, _w100, _h);
		ofxImGuiSurfing::AddBigToggle(bModeFreeStore, _w100, _h);
		//AddToggleRoundedButton(bModeFreeStore);

		ofxImGuiSurfing::AddBigToggle(bLockLayout, _w50, _h);
		ImGui::SameLine();
		ofxImGuiSurfing::AddBigToggle(bForceLayoutPosition, _w50, _h);

		//----

		//ImGui::Dummy(ImVec2(0.0f, 2.0f));

		if (ImGui::CollapsingHeader("Presets", ImGuiWindowFlags_None))
		{
			ImVec2 bb{ (bMin ? _w100 : _w50), _h };

			//--

			/*
			//TODO: not storing new presets yet!
			//presets amounts can be defined on setupLayout(4);
			// create a new layout preset
			if (ImGui::Button("Create", ImVec2(_w100, _h)))
			{
				createLayoutPreset();
			}
			*/

			//--

			for (int i = 0; i < bLayoutPresets.size(); i++) {
				string _name = (bLayoutPresets[i].getName());

				ImGui::Text(_name.c_str());
				if (!bMin)
				{
					ImGui::PushID(_id++);
					if (ImGui::Button("Load", bb))
					{
						appLayoutIndex = i;
					}
					ImGui::PopID();

					ImGui::SameLine();
				}

				ImGui::PushID(_id++);

				if (ImGui::Button("Save", bb))
				{
					ini_to_save_Str = _name;
					ini_to_save = ini_to_save_Str.c_str();
				}

				ImGui::PopID();

			}

			//--

			ImGui::Dummy(ImVec2(0.0f, 2.0f));

			if (ImGui::Button("Reset Preset", ImVec2(_w100, _h)))
			{
				// toggle panels to true
				for (int i = 0; i < windowsAtributes.size(); i++) {
					windowsAtributes[i].bGui.set(true);
				}

				bLockLayout = false;

				saveAppLayout((appLayoutIndex.get()));
			}
		}

		//--

		//if (ImGui::CollapsingHeader("EXTRA", ImGuiWindowFlags_None))
		//{
		//	//ofxImGuiSurfing::AddBigToggle(SHOW_Engines, _w100, _h);
		//	//ofxImGuiSurfing::AddBigToggle(SHOW_MenuBar, _w100, _h);
		//	//ofxImGuiSurfing::AddBigToggle(SHOW_Advanced, _w100, _h);
		//	////ofxImGuiSurfing::AddBigToggle(bGui_LayoutsExtra, _w100, _h);
		//	ImGui::Checkbox("Auto-Resize", &auto_resize);
		//}
	}
	endWindow();

	//ImGui::PopStyleVar();
}

//----

// layout preset loaders / savers

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveLayoutPreset(string path)
{
	saveLayoutImGuiIni(path);
	saveLayoutPresetGroup(path);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadLayoutPreset(string path)
{
	loadLayoutImGuiIni(ini_to_load);
	loadLayoutPresetGroup(path);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveLayoutImGuiIni(string path)
{
	ImGui::SaveIniSettingsToDisk(ofToDataPath(path_ImLayouts + path + ".ini", true).c_str());
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadLayoutImGuiIni(string path)
{
	ImGui::LoadIniSettingsFromDisk(ofToDataPath(path_ImLayouts + path + ".ini", true).c_str());
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveLayoutPresetGroup(string path)
{
	ofxImGuiSurfing::saveGroup(params_Layouts, path_ImLayouts + path + ".json");
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadLayoutPresetGroup(string path)
{
	ofxImGuiSurfing::loadGroup(params_Layouts, path_ImLayouts + path + ".json");
}

//----

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::createLayoutPreset()
{
	int i = bLayoutPresets.size();
	/*static*/ ofParameter<bool> _b = ofParameter<bool>{ "P" + ofToString(i), false };
	bLayoutPresets.push_back(_b);
	appLayoutIndex.setMax(bLayoutPresets.size() - 1);
	params_LayoutPresetsStates.add(bLayoutPresets[i]);
}

//----

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutsPanels()
{
	static bool bLandscape;

	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (bAutoResizePanels) flags = ImGuiWindowFlags_AlwaysAutoResize;//TODO: bug
	flags |= ImGuiWindowFlags_NoSavedSettings; // exclude from restore preset layouts
	//flags |= flagsWindowsLocked;

	/*
	if (bLandscape) ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(4 * PANEL_WIDTH_MIN, PANEL_HEIGHT_MIN));
	else ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(PANEL_WIDTH_MIN, 3 * PANEL_HEIGHT_MIN));
	*/

	if (bModeFreeStore)
	{
		ImGuiCond flagCond;
		flagCond = ImGuiCond_Appearing;
		//flagCond = ImGuiCond_Always;
		const int i = 1;
		ImGui::SetNextWindowPos(ofVec2f(rectPanels[i].get().getX(), rectPanels[i].get().getY()), flagCond);
		ImGui::SetNextWindowSize(ofVec2f(rectPanels[i].get().getWidth(), rectPanels[i].get().getHeight()), flagCond);
	}

	beginWindow(bGui_Panels, flags);
	{
		const int i = 1;
		rectPanels[i].setWithoutEventNotifications(ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()));

		//-

		const int NUM_WIDGETS = windowsAtributes.size(); // expected num widgets
		const int NUM_WIDGETS_EXTRA_LANDSCAPE = 5;
		//const int NUM_WIDGETS_EXTRA_LANDSCAPE = 6;//with autoresize

		float _spcx = ImGui::GetStyle().ItemSpacing.x;
		float _spcy = ImGui::GetStyle().ItemSpacing.y;
		float _h100 = ImGui::GetContentRegionAvail().y;

		float _h;
		float _w;

		//float _wUnit;
		float _hWid;

		bLandscape = false;
		float __w = ImGui::GetWindowWidth();
		float __h = ImGui::GetWindowHeight();
		if (__w > __h) bLandscape = true;

		if (bLandscape) { // A. landscape
			//_w = ofxImGuiSurfing::getWidgetsWidth(NUM_WIDGETS + 2);
			const int amntColumns = NUM_WIDGETS + 2;
			float __w100 = ImGui::GetContentRegionAvail().x - (3 * _spcx);//remove extra columns x spacing added!
			_w = (__w100 - _spcx * (amntColumns - 1)) / amntColumns;

			_h = _h100 - _spcy;
			_hWid = (_h - _spcy) / 2;
			//_hWid = (_h - _spcy) / 3;//with autoResize
		}
		else { // B. portrait
			_hWid = ofxImGuiSurfing::getWidgetsHeightRelative();
			float _hTotal = _h100 - (_hWid * NUM_WIDGETS_EXTRA_LANDSCAPE + (NUM_WIDGETS_EXTRA_LANDSCAPE + 1) * _spcy);
			_w = ofxImGuiSurfing::getWidgetsWidth();
			_h = _hTotal / NUM_WIDGETS - _spcy;
		}

		if (bLandscape) {//landscape
			ImGui::Columns(3);
			ImGui::SetColumnWidth(0, _spcx + (_w + _spcx) * NUM_WIDGETS);
		}

		//-

		// 1. populate all toggles

		for (int i = 0; i < windowsAtributes.size(); i++)
		{
			ofxImGuiSurfing::AddBigToggle(windowsAtributes[i].bGui, _w, _h);
			if (bLandscape) ImGui::SameLine();
		}

		//-

		float _w100;
		float _w50;
		if (bLandscape) {//landscape
			ImGui::SameLine();
			_w100 = _w;
			_w50 = (_w - _spcx) / 2.0f;
		}
		else {//portrait
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
			_w100 = ofxImGuiSurfing::getWidgetsWidth(1);
			_w50 = ofxImGuiSurfing::getWidgetsWidth(2);
		}

		if (bLandscape) {//landscape
			ImGui::NextColumn();
			ImGui::SetColumnWidth(1, _w100 + 2 * _spcx);
		}

		//-

		// 2. extra widgets

		if (ImGui::Button("All", ImVec2(_w50, _hWid)))
		{
			bool b = true;
			for (int i = 0; i < windowsAtributes.size(); i++)
			{
				windowsAtributes[i].bGui.set(b);
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("None", ImVec2(_w50, _hWid)))
		{
			bool b = false;
			for (int i = 0; i < windowsAtributes.size(); i++)
			{
				windowsAtributes[i].bGui.set(b);
			}
		}

		ofxImGuiSurfing::AddBigToggle(bSolo, _w100, _hWid, true);

		//-

		// 3. panels toggles

		if (bLandscape) {//landscape
			ImGui::NextColumn();
			ImGui::SetColumnWidth(2, _w100 + _spcx + _spcx);
		}
		else {//portrait
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
		}

		// layout
		float _hUnit = ofxImGuiSurfing::getWidgetsHeightRelative();
		ofxImGuiSurfing::AddBigToggle(bGui_LayoutsPresets, _w100, _hWid, true);
		ofxImGuiSurfing::AddBigToggle(bGui_LayoutsManager, _w100, _hWid, true);
		//ofxImGuiSurfing::AddToggleRoundedButton(bAutoResizePanels);

		if (bLandscape) {//landscape
			ImGui::Columns();
		}
	}
	endWindow();

	//ImGui::PopStyleVar();
}

//--

//TODO:
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::keyPressed(int key)
{
	//const int key = eventArgs.key;

	//// modifiers
	//bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	//bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	//bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	//bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	//bool bDebug = true;
	//if (bDebug)
	//{
	//	if (!ENABLE_keys || bBlockedKeys) {
	//		ofLogError(__FUNCTION__) << "Key commands are disabled!";
	//		ofLogError(__FUNCTION__) << "ENABLE_keys: " << (ENABLE_keys ? "TRUE" : "FALSE");
	//		ofLogError(__FUNCTION__) << "bBlockedKeys : " << (bBlockedKeys ? "TRUE" : "FALSE");
	//	}
	//	else
	//		ofLogNotice(__FUNCTION__)
	//		<< "keycode: " << key
	//		<< " char: " << (char)key
	//		<< (mod_CONTROL ? " + CONTROL" : "")
	//		<< (mod_SHIFT ? " + SHIFT" : "")
	//		<< (mod_ALT ? " + ALT" : "");
	//}

	{
		switch (key)
		{
		case OF_KEY_F1: appLayoutIndex = 0; break;
		case OF_KEY_F2: appLayoutIndex = 1; break;
		case OF_KEY_F3: appLayoutIndex = 2; break;
		case OF_KEY_F4: appLayoutIndex = 3; break;

		case OF_KEY_F5: loadAppSettings(); break;

		default: break;
		}

		if (key == OF_KEY_F9)//layouts
		{
			bGui_LayoutsPresets = !bGui_LayoutsPresets;
		}

		if (key == OF_KEY_F10)//panels
		{
			bGui_Panels = !bGui_Panels;
		}

		else if (key == OF_KEY_F11)//
		{
			bGui_LayoutsExtra = !bGui_LayoutsExtra;
		}

		// unlock dock Ctrl+Alt+a
		else if ((key == 'L' || key == 'l')) //&& mod_CONTROL && !mod_ALT)
		{
			bLockLayout = !bLockLayout;
		}

		//--

		//// layout modes

		//else if (key == OF_KEY_TAB && !mod_CONTROL)
		//{
		//	if (appLayoutIndex > appLayoutIndex.getMin()) appLayoutIndex++;
		//	else if (appLayoutIndex == appLayoutIndex.getMin()) appLayoutIndex = appLayoutIndex.getMax();
		//	//if (appLayoutIndex < 3) loadAppLayout(AppLayouts(appLayoutIndex + 1));
		//	//else if (appLayoutIndex == 3) loadAppLayout(AppLayouts(0));
		//}
	}

}

////--------------------------------------------------------------
//void ofxSurfing_ImGui_Manager::draw_ImGuiMenu()
//{
//	static bool opt_fullscreen = true;
//	static bool opt_padding = false;
//	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
//	static bool* p_open = NULL;
//
//	//-
//
//	// menu bar
//
//	// This is not operative. just for testing menus!
//
//	if (ImGui::BeginMenuBar())
//	{
//		if (ImGui::BeginMenu("Options"))
//		{
//			// Disabling fullscreen would allow the window to be moved to the front of other windows,
//			// which we can't undo at the moment without finer window depth/z control.
//			ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
//			ImGui::MenuItem("Padding", NULL, &opt_padding);
//			ImGui::Separator();
//
//			if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
//			if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
//			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
//			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
//			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
//			ImGui::Separator();
//
//			if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
//				*p_open = false;
//			ImGui::EndMenu();
//		}
//		ofxImGuiSurfing::HelpMarker(
//			"This is not operative here. Just for testing menus!" "\n\n"
//			"When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
//			"- Drag from window title bar or their tab to dock/undock." "\n"
//			"- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
//			"- Hold SHIFT to disable docking." "\n"
//			"This demo app has nothing to do with it!" "\n\n"
//			"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)." "\n\n"
//			"ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame." "\n\n"
//			"(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)"
//		);
//
//		ImGui::EndMenuBar();
//	}
//}