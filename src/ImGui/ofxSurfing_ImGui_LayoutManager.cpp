
#include "ofxSurfing_ImGui_LayoutManager.h"

//--------------------------------------------------------------
ofxSurfing_ImGui_Manager::ofxSurfing_ImGui_Manager()
{
	ofAddListener(ofEvents().keyPressed, this, &ofxSurfing_ImGui_Manager::keyPressed);

	params_Advanced.add(bAutoResize);
	params_Advanced.add(bExtra);
	params_Advanced.add(bReset);
	params_Advanced.add(bLockMove);
	params_Advanced.add(bNoScroll);
	params_Advanced.add(bMinimize);
	params_Advanced.add(bAdvanced);
	params_Advanced.add(bKeys);
	params_Advanced.add(bMouseWheel);
	params_Advanced.add(bHelp);
	params_Advanced.add(bDebug);

	// Exclude from settings
	//bExtra.setSerializable(false);
	bReset.setSerializable(false);

	//-

	// -> TODO: BUG?: 
	// it seems than requires to be false when using multi-context/instances
	// if is setted to true, sometimes it hangs and gui do not refresh/freezes.
	bAutoDraw = false;

	//-

	// Enable "Windows Special Organizer"
	// Customize names
	windowPanels.setNameWindowsSpecialsEnableGlobal("Show All");
	setNameWindowsSpecialsPanel("Organizer");
}

//--------------------------------------------------------------
ofxSurfing_ImGui_Manager::~ofxSurfing_ImGui_Manager() {

	ofRemoveListener(ofEvents().keyPressed, this, &ofxSurfing_ImGui_Manager::keyPressed);

	ofRemoveListener(params_LayoutPresetsStates.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);
	ofRemoveListener(params_AppSettings.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);
	ofRemoveListener(params_Panels.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);

	/*if (bAutoSaveSettings) */saveAppSettings();
}

//--

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setup(ofxImGuiSurfing::SurfingImGuiInstantiationMode mode) {
	surfingImGuiMode = mode;

	switch (surfingImGuiMode)
	{
	case ofxImGuiSurfing::IM_GUI_MODE_UNKNOWN:
		break;

	case ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED:
		setAutoSaveSettings(true); // -> Enables store/recall some settings from previous app session
		setImGuiAutodraw(true);
		initiate(); // This instantiates and configures ofxImGui inside the class object.
		break;

	case ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING:
		numPresetsDefault = 4;

		setAutoSaveSettings(true); // -> Enables store/recall some settings from previous app session
		setupDocking();
		break;

	case ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_SINGLE:
		setAutoSaveSettings(true); // -> Enables store/recall some settings from previous app session
		setImGuiAutodraw(true);
		initiate(); // This instantiates and configures ofxImGui inside the class object.
		break;

	case ofxImGuiSurfing::IM_GUI_MODE_REFERENCED://TODO:
		break;

	case ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED: // -> guiManager.begin(); it's bypassed internally then can be remain uncommented.
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setupDocking()
{
	surfingImGuiMode = ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING;

	setAutoSaveSettings(true);
	setImGuiDocking(true);
	setImGuiDockingModeCentered(true);
	setImGuiAutodraw(true);

	initiate();
}

//--

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::initiate() { // For using internal instantiated gui

	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) return;

	//-

	// MouseWheel link
	widgetsManager.bMouseWheel.makeReferenceTo(bMouseWheel);

	//-

	setupImGui();

	//-

	path_Global = "ImGui_Layout/";
	path_ImLayouts = path_Global + "Presets/";

	// Create folders if required
	if (bAutoSaveSettings)
	{
		ofxImGuiSurfing::CheckFolder(path_Global);
		if (bUseLayoutPresetsManager) ofxImGuiSurfing::CheckFolder(path_ImLayouts);
	}

	path_AppSettings = path_Global + "GuiManager_" + bGui_LayoutsPanels.getName() + path_SubPathLabel + ".json";//this allow multiple addons instaces with settings

	// Add the basic param settings
	if (!bUseLayoutPresetsManager)
	{
		params_AppSettings.add(params_Advanced);
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setup(ofxImGui::Gui & _gui) { // using external instantiated gui

	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) return;

	//-

	guiPtr = &_gui;

	setupImGui();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setupImGui()
{
	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) return;

	//-

	ImGuiConfigFlags flags = ImGuiConfigFlags_None;

	// Hardcoded settings

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

	// Font
	std::string _fontName;
	float _fontSizeParam;
	_fontName = FONT_DEFAULT_FILE; // WARNING: will not crash or notify you if the file font not present
	_fontSizeParam = FONT_DEFAULT_SIZE;
	std::string _path = "assets/fonts/"; // assets folder

	pushFont(_path + _fontName, _fontSizeParam); // queue default font too

	addFont(_path + _fontName, _fontSizeParam);

	//-

	// Theme: colors and sizes
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::startup()
{
	//-

	// Last setup step

	if (bDocking)
	{
		setupLayout(4); // Init Default Layout with 4 presets.
	}

	//-

	// Special Windows Organizer

	if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
	{
		// Cascade / Organizer Mode
		// Special windows manager

		initiatieSpecialWindowsOrganizer();

		//// Customize names
		//windowPanels.setNameWindowsSpecialsEnableGlobal("Show Global");
		//setNameWindowsSpecialsPanel("Organizer");
		////setNameWindowsSpecialsPanel("Organizer");

		if (surfingImGuiMode == IM_GUI_MODE_INSTANTIATED_DOCKING)
		{
			windowPanels.setHideWindows(true);

			// Docking mode has the gui toggles in other panels..
			if (surfingImGuiMode != IM_GUI_MODE_INSTANTIATED_DOCKING)
			{
				windowPanels.bGui_WindowsSpecials = false;
				windowPanels.bGui_WindowsSpecials.setSerializable(false);
			}
		}

		if (surfingImGuiMode != IM_GUI_MODE_INSTANTIATED_DOCKING)
		{
			// Link show gui
			bGui_WindowsSpecials.makeReferenceTo(windowPanels.bGui_WindowsSpecials);
			//windowPanels.bGui_WindowsSpecials.makeReferenceTo(bGui_WindowsSpecials);
		}
	}

	//--

	// Startup

	loadAppSettings();

	//--

	//TODO:
	//BUG: toggle states are not recalled well...
	//if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
	{
		windowPanels.startup();
	}

	//for (size_t i = 0; i < windowsAtributes.size(); i++)
	//{
	//	//windowsAtributes[i].bGui = params_Panels[i];
	//	//windowsAtributes[i].bGui = windowPanels[i];
	//	bool b = windowsAtributes[i].bGui;
	//	ofLogNotice(__FUNCTION__) << b;

	//	////params_Panels[i] = b;
	//	bPanels[i].set(b);
	//}
	//
	////if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
	////{
	////	windowPanels.add(_bGui);
	////}

	//--

	appLayoutIndex = appLayoutIndex;

	//--
}

//----

// Fonts

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setDefaultFontIndex(int index)
{
	if (customFonts.size() == 0) return;

	currFont = ofClamp(index, 0, customFonts.size() - 1);
	customFont = customFonts[currFont];
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setDefaultFont()//will apply the first added font file
{
	setDefaultFontIndex(0);
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::pushFont(std::string path, int size)
{
	//TODO:
	// should be a vector with several customFont to allow hot reloading..
	// if not, last added font will be used
	ofLogNotice(__FUNCTION__) << path << " : " << size;

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
	else {
		bIgnoreNextPopFont = true; // workaround to avoid crashes
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::popStyleFont()
{
	//TODO: will crash if not pushed..
	//workaround to avoid crashes
	if (bIgnoreNextPopFont)
	{
		bIgnoreNextPopFont = false;
		return;
	}

	ImGui::PopFont();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::processOpenFileSelection(ofFileDialogResult openFileResult, int size = 10) {

	std::string path = openFileResult.getPath();

	ofLogNotice(__FUNCTION__) << "getName(): " << openFileResult.getName();
	ofLogNotice(__FUNCTION__) << "getPath(): " << path;

	ofFile file(path);

	if (file.exists())
	{
		ofLogNotice(__FUNCTION__) << ("The file exists - now checking the type via file extension");
		std::string fileExtension = ofToUpper(file.getExtension());

		// We only want ttf/otf
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

		// We have a file, check it and process it
		processOpenFileSelection(openFileResult, size);
	}
	else {
		ofLogNotice(__FUNCTION__) << ("User hit cancel");
	}
}

//----

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::update() { // -> Not being used by default
	//if (ofGetFrameNum() == 1)
	//{
	//	appLayoutIndex = appLayoutIndex;
	//}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::draw() { // -> Not being used by default
	if (!bAutoDraw) if (customFont == nullptr) gui.draw();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::updateLayout() {

	// Layouts

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

//----

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutsManager() {

	ImGuiWindowFlags flagsMng = ImGuiWindowFlags_None;
	flagsMng += ImGuiWindowFlags_NoSavedSettings;

	if (bAutoResize) flagsMng += ImGuiWindowFlags_AlwaysAutoResize;

	//--

	ImGuiCond mngCond;
	mngCond = ImGuiCond_Appearing;

	// Right to the Presets Window
	bool blocked = true;
	if (blocked) {
		int _pad = PADDING_PANELS;
		glm::vec2 pos = rectangles_Windows[0].get().getTopRight();
		ofRectangle r = rectangles_Windows[2];
		r.setPosition(pos.x + _pad, pos.y);
		r.setWidth(rectangles_Windows[0].get().getWidth());
		if (bGui_LayoutsPanels) r.setHeight(rectangles_Windows[0].get().getHeight());
		rectangles_Windows[2] = r;
		mngCond = ImGuiCond_Always;
	}

	const int i = 2;
	ImGui::SetNextWindowPos(ofVec2f(rectangles_Windows[i].get().getX(), rectangles_Windows[i].get().getY()), mngCond);
	ImGui::SetNextWindowSize(ofVec2f(rectangles_Windows[i].get().getWidth(), rectangles_Windows[i].get().getHeight()), mngCond);

	//-

	if (beginWindow(bGui_LayoutsManager, flagsMng))
	{
		const int i = 2;
		rectangles_Windows[i].setWithoutEventNotifications(ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()));

		//-

		float _w = ofxImGuiSurfing::getWidgetsWidth();
		float _h = 2 * ofxImGuiSurfing::getWidgetsHeightRelative();

		//-

		// Minimize
		//ofxImGuiSurfing::AddToggleRounded(bMinimizePresets);

		// Panels & Presets
		AddBigToggle(bGui_LayoutsPanels, _w, _h, false);
		AddBigToggle(bGui_LayoutsPresets, _w, _h, false);

		if (!bMinimizePresets && !bGui_LayoutsPanels)
		{
			ofxImGuiSurfing::AddSpacingSeparated();
		}

		//--

		// Extra

		if (!bMinimizePresets)
		{
			AddGroup(params_LayoutsExtra);
		}

		//-

		if (!bGui_LayoutsPanels)
		{
			static bool bOpen = false;
			ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
			if (ImGui::CollapsingHeader("Panels", _flagw))
			{
				ImGui::Spacing();

				for (int i = 0; i < windowsAtributes.size(); i++)
				{
					AddToggleRoundedButton(windowsAtributes[i].bGui);
				}

				ImGui::Spacing();

				float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);
				if (ImGui::Button("All", ImVec2(_w2, _h / 2)))
				{
					setShowAllPanels(true);
				}
				ImGui::SameLine();
				if (ImGui::Button("None", ImVec2(_w2, _h / 2)))
				{
					setShowAllPanels(false);
				}
			}
		}

		//if (!bMinimizePresets)
		//{
		//	this->Add(bAutoResizePanels, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
		//	this->Add(bResetWindowPanels, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
		//}

		//--

		if (!bMinimizePresets)
		{
			drawAdvanced();
		}
	}

	this->endWindow();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayouts() {

	//TODO:
	// How to make all windows dockeable in the same space ?
	if (bGui_LayoutsPresets) {
		drawLayoutsPresets();
		if (!bMinimizePresets) if (bGui_LayoutsExtra) drawLayoutsExtra();
	}
	if (bGui_LayoutsPanels) drawLayoutsPanels();
	// Draws all sections except drawLayoutsManager();

	// Log
	if (appLayoutIndex != -1)
		if (bLog) log.ImGui("Log");
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutEngine() {

	if (bUseLayoutPresetsManager && bGui_LayoutsManager && !bMinimizePresets)
		drawLayoutsManager();

	//----

	if (bUseLayoutPresetsManager)
	{
		updateLayout(); // to attend save load flags

		//----

		if (bDocking)
		{

			ImGuiID dockNodeID;
			ImGuiDockNode* dockNode;
			//ImGuiDockNode* centralNode;
			//ImGuiDockNodeFlags dockingFlags;

			//----

			// a. Define the ofWindow as a docking space

			//ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0)); // Fixes imgui to expected behaviour. Otherwise add in ImGui::DockSpace() [±line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
			//ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_PassthruCentralNode);
			//ImGui::PopStyleColor();

			//-

			// b. Lockable settings 

			// Fixes imgui to expected behaviour. Otherwise add in ImGui::DockSpace() [±line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
			//ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
			//ImGuiDockNodeFlags flagsDock;
			//flagsDock = ImGuiDockNodeFlags_PassthruCentralNode;
			//if (bModeLockControls)
			//{
			//	flagsDock |= ImGuiDockNodeFlags_NoResize;
			//	flagsDock |= ImGuiDockNodeFlags_NoCloseButton;
			//	//flagsDock |= ImGuiDockNodeFlags_NoTabBar;
			//	//flagsDock |= ImGuiDockNodeFlags_NoWindowMenuButton;
			//	//flagsDock |= ImGuiDockNodeFlags_NoMove__;
			//}

			//TODO:
			//dockNodeID = ImGui::DockSpaceOverViewport(NULL, flagsDock);
			//dockNodeID = ImGui::GetID("MyDockSpace");
			//dockNodeID = ImGui::GetID("DockSpace");

			//ImGui::PopStyleColor();

			//----

			// Get check free space
			// central inter docks rectangle

			ImGuiDockNodeFlags flagsDock = ImGuiDockNodeFlags_None;
			//flagsDock += ImGuiDockNodeFlags_DockSpace;
			flagsDock += ImGuiDockNodeFlags_PassthruCentralNode;

			// A
			dockNodeID = ImGui::DockSpaceOverViewport(NULL, flagsDock);
			dockNode = ImGui::DockBuilderGetNode(dockNodeID);

			// B
			//ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(dockNodeID);

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
					//if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());

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
						ofColor cl = ofColor::white;
						//ofColor cl = ofColor::orange;

						//int g = 255 * ofxImGuiSurfing::Bounce(0.5);
						int a = 255.f * ofMap(ofxImGuiSurfing::Bounce(1), 0.0f, 1.0f, 0.2f, 1.0f, true);
						ofColor c = ofColor(cl.r, cl.g, cl.b, a);
						//ofColor c = ofColor(g, a);
						ofSetColor(c);

						ofNoFill();
						ofSetLineWidth(_wl);

						float ww = availableSpace.GetSize().x - pad;
						float hh = availableSpace.GetSize().y - pad;

						ofRectangle rDebug;
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
					if (rectangle_Central_MAX_PRE != rectangle_Central_MAX) { // updates when layout changes..
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
		}

		//----

		//// b. Lockable settings 

		//// Fixes imgui to expected behaviour. Otherwise add in ImGui::DockSpace() [±line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
		////ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		//ImGuiDockNodeFlags flagsDock;
		//flagsDock = ImGuiDockNodeFlags_PassthruCentralNode;
		//if (bModeLockControls)
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

#ifdef FIXING_DRAW_VIEWPORT
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawOFnative() {

	//TODO: debug viewport. freew space for OF drawing

	ImGuiDockNodeFlags __dockingFlags;
	__dockingFlags = ImGuiDockNodeFlags_PassthruCentralNode;

	//ImGuiViewport* viewport = ImGui::GetMainViewport();

	//auto dockNodeID = ImGui::DockSpaceOverViewport(NULL, __dockingFlags);
	//auto dockNodeID = ImGui::GetID("DockSpace");
	auto dockNodeID = ImGui::GetID("MyDockSpace");

	ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(dockNodeID);
	if (dockNode)
	{
		ImGuiDockNode* centralNode = ImGui::DockBuilderGetCentralNode(dockNodeID);
		if (centralNode)
			//if (centralNode && centralNode->IsEmpty()) 
		{
			ImRect availableSpace = centralNode->Rect();
			//availableSpace.Max = availableSpace.Min + ImGui::GetContentRegionAvail();
			//ImGui::GetForegroundDrawList()->AddRect(availableSpace.GetTL() + ImVec2(8, 8), availableSpace.GetBR() - ImVec2(8, 8), IM_COL32(255, 50, 50, 255));

			ImVec2 viewCenter = availableSpace.GetCenter();

			// Depending on the viewports flag, the XY is either absolute or relative to the oF window.
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());

			// create rectangle
			rectangle_Central = ofRectangle(viewCenter.x, viewCenter.y, availableSpace.GetWidth(), availableSpace.GetHeight());
			float v = ofxImGuiSurfing::Bounce(1);
			rectangle_Central.setSize(availableSpace.GetWidth() * v, availableSpace.GetHeight() * v);
		}
	}
	else // get the OF viewport
	{
		auto view = ofGetCurrentViewport();
		auto viewCenter = view.getCenter();
		rectangle_Central = ofRectangle(viewCenter.x, viewCenter.y, view.getWidth(), view.getHeight());
		float v = ofxImGuiSurfing::Bounce(1);
		rectangle_Central.setSize(view.getWidth() * v, view.getHeight() * v);
	}

	ofPushStyle();
	{
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofSetLineWidth(4);
		ofColor cl = ofColor::yellow;
		int a = 255.f * ofMap(ofxImGuiSurfing::Bounce(1), 0.0f, 1.0f, 0.2f, 1.0f, true);
		ofColor c = ofColor(cl.r, cl.g, cl.b, a);
		ofSetColor(c);
		ofFill();
		ofDrawCircle(rectangle_Central.getCenter().x, rectangle_Central.getCenter().y, 3);
		ofNoFill();
		ofDrawRectangle(rectangle_Central);

		ofSetRectMode(OF_RECTMODE_CORNER);
	}
	ofPopStyle();
}
#endif

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::startupFirstFrame() {
	//if (ofGetFrameNum() == 1)
	if (ofGetFrameNum() == 2)
	{
		appLayoutIndex = appLayoutIndex;
		if (rectangles_Windows.size() > 0) rectangles_Windows[1] = rectangles_Windows[1];
	}
}

//----

// Global ImGui being/end like ofxImGui
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::begin() {

	//--

	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) return;

	//--

	//TODO:
	//windowPanels.update();
	//update();

	//TODO:
	if (ofGetFrameNum() == 1)
	{
		startupFirstFrame();
	}

	//TODO:
	_currWindowsSpecial = -1;

	resetUniqueNames(); // reset unique names

	//--

	if (guiPtr != nullptr) guiPtr->begin();
	else gui.begin();

	if (customFont != nullptr) ImGui::PushFont(customFont);

	//TODO:
	setDefaultFont();

	//--

	if (bDocking) drawLayoutEngine();

	//--

	// Special Windows Engine
	// Organizer

	if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
	{
		// Main Panels Controller
		if (windowPanels.isIntitiated())
		{
			//if (windowPanels.bModeLinkedWindowsSpecial) windowPanels.update();

			windowPanels.update();

			// Docking mode has the gui toggles in other panels..
			if (surfingImGuiMode != IM_GUI_MODE_INSTANTIATED_DOCKING)
			{
				if (bGui_WindowsSpecials) drawWindowsSpecialPanel();
			}
		}
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::end() {

	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) return;

	//--

	drawLogPanel();

	//--

#ifdef FIXING_DRAW_VIEWPORT
	if (bPreviewSceneViewport) drawOFnative();
#endif

	//--

	if (customFont != nullptr) ImGui::PopFont();

	// mouse lockers
	bMouseOverGui = false;
	bMouseOverGui |= ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
	bMouseOverGui |= ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
	bMouseOverGui |= ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);

	//--

	if (guiPtr != nullptr) guiPtr->end();
	else gui.end();
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(char* name)
{
	return beginWindow((string)name, NULL, ImGuiWindowFlags_None);
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(std::string name)
{
	return beginWindow(name, NULL, ImGuiWindowFlags_None);
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindow(std::string name, bool* p_open)
{
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
bool ofxSurfing_ImGui_Manager::beginWindow(std::string name = "Window", bool* p_open = NULL, ImGuiWindowFlags window_flags = ImGuiWindowFlags_None)
{
	//TODO: must be moved to special windows?
	//if (bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//if (bLockMove) window_flags |= ImGuiWindowFlags_NoMove;

	//if (bReset_Window) {
	//	bReset_Window = false;
	//	resetWindowImGui(false, true);
	//}

	//--

	//TODO:
	// reset unique names
	resetUniqueNames();
	//resetIDs();
	//widgetsManager.resetUniqueNames();

	//--

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

	//--

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

	// Refresh layout
	widgetsManager.refreshLayout(); // calculate sizes realted to window shape/size

	// When we are instantiating ImGui externally, not inside this addon,
	// we don't handle the font and theme.
	if (surfingImGuiMode != ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED)
	{
		// Set default font
		setDefaultFont();
	}

	// Leave a fixed amount of width for labels (by passing a negative value), the rest goes to widgets.
	//ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	//currWindow++;

	return b;
}

//TODO: a faster mode to avoid use indexes..
//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindowSpecial() {
	_currWindowsSpecial++;
	bool b = beginWindowSpecial(_currWindowsSpecial);
	return b;
}

//--------------------------------------------------------------
bool ofxSurfing_ImGui_Manager::beginWindowSpecial(int index)
{
	//TODO:
	_currWindowsSpecial = index; // workflow

	ImGuiWindowFlags flags = ImGuiWindowFlags_None;

	// Skip window if hidden

	if (index > windowsAtributes.size() - 1 || index == -1)
	{
		ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
		return false;
	}

	if (!windowsAtributes[index].bGui.get()) return false;

	if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
	{
		if (!windowPanels.bGui_Global.get()) return false;

		//--

		if (windowPanels.bModeLinkedWindowsSpecial) windowPanels.runState(index);

		if (windowPanels.bHeaders) flags += ImGuiWindowFlags_NoDecoration;
	}

	if (bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;

	//if (windowsAtributes[index].bPoweredWindow.get())
	//{
	//	if (windowsAtributes[index].bAutoResize.get()) {
	//		flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//	}
	//}

	bool b = beginWindow(windowsAtributes[index].bGui.getName().c_str(), (bool*)&windowsAtributes[index].bGui.get(), flags);

	//TODO:
	// workaround
	////if (!windowPanels.bGui_Global.get()) return false;
	//if (!windowsAtributes[index].bGui.get()) return false;

	//refreshLayout();

	return b;
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::endWindowSpecial(int index)
{
	if (index == -1) index = _currWindowsSpecial; // workaround

	if (index > windowsAtributes.size() - 1)
	{
		ofLogError(__FUNCTION__) << "Out of range index for queued windows, " << index;
		return;
	}

	// skip window if hidden

	if (!windowsAtributes[index].bGui.get()) return;

	if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
	{
		if (!windowPanels.bGui_Global.get()) return;
	}

	//-

	//if (windowsAtributes[_currWindowsSpecial].bPoweredWindow.get())
	//{
	//	drawAdvancedControls();
	//}

	if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
	{
		if (windowPanels.bModeLinkedWindowsSpecial)
		{
			windowPanels.getState(index);
		}
	}

	//--

	//workflow: to avoid use the index. but requires sequencial calling
	//_currWindowsSpecial++;

	ImGui::End();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::endWindow()
{
	ImGui::End();
}

//--

// Docking Helpers

#ifdef FIXING_DOCKING
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::beginDocking()
{
	// Make windows transparent, to demonstrate drawing behind them.
	//ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(200, 200, 200, 128)); // This styles the docked windows

	ImGuiDockNodeFlags dockingFlags = ImGuiDockNodeFlags_PassthruCentralNode; // Make the docking space transparent
	// Fixes imgui to expected behaviour, having a transparent central node in passthru mode.
	// Alternative: Otherwise add in ImGui::DockSpace() [±line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
	//ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));

	//dockingFlags |= ImGuiDockNodeFlags_NoDockingInCentralNode; // Uncomment to always keep an empty "central node" (a visible oF space)
	//dockingFlags |= ImGuiDockNodeFlags_NoTabBar; // Uncomment to disable creating tabs in the main view

	// Define the ofWindow as a docking space
	ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, dockingFlags); // Also draws the docked windows
	//ImGui::PopStyleColor(2);
}
#endif

#ifndef FIXING_DOCKING
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::beginDocking()
{
	//dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	if (bMenu) window_flags |= ImGuiWindowFlags_MenuBar;

	ImGuiViewport* viewport = ImGui::GetMainViewport();

	// fit full viewport
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
	//ImGui::Begin("MyDockSpace", nullptr, window_flags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);

	//----

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	else
	{
		// Docking is DISABLED - Show a warning message
		//ShowDockingDisabledMessage();
	}

	//----

	// All windows goes here before endDocking()

	drawLayouts();
}
#endif

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::endDocking()
{
#ifdef FIXING_DOCKING
	return;
#endif

	if (bMenu) draw_ImGuiMenu();

	//-

	//ImGuiIO& io = ImGui::GetIO();
	//if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	//{
	//}

	 // End the parent window that contains the Dockspace:
	ImGui::End(); // ?
}

//----

// Layouts presets management
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setupLayout(int numPresets) //-> must call manually after adding windows and layout presets
{
	numPresetsDefault = numPresets; // default is 4 presets with names P0, P1, P2, P3

	//-

	// Clear

	params_Layouts.clear();
	params_LayoutsExtra.clear();
	params_LayoutsVisible.clear();

	//-

	params_LayoutsExtra.setName("Extra Params");

	//-

	// 1.1 Store all the window panels show toggles

	//params_Layouts.clear();
	for (int i = 0; i < windowsAtributes.size(); i++)
	{
		params_LayoutsVisible.add(windowsAtributes[i].bGui);
	}

	params_LayoutsExtra.add(bMenu);
	params_LayoutsExtra.add(bLog);

	//// 1.2 Add other settings that we want to store into each presets

	//params_LayoutsExtraInternal.clear();
	//params_LayoutsExtraInternal.add(bMenu);
	//params_LayoutsExtraInternal.add(bLog);
	//params_LayoutsExtra.add(params_LayoutsExtraInternal);

	// 1.2.2 Special Windows Helpers

	if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
	{
		params_LayoutsExtra.add(windowPanels.getParamsUser());

		//params_LayoutsExtra.add(windowPanels.bGui_WindowsSpecials);
		//params_LayoutsExtra.add(windowPanels.bModeLinkedWindowsSpecial);
		//params_LayoutsExtra.add(windowPanels.bOrientation);
		//params_LayoutsExtra.add(windowPanels.bFitSizes);			
		//params_LayoutsExtra.add(windowPanels.bHeaders);
		//params_LayoutsExtra.add(windowPanels.pad);
		//params_LayoutsExtra.add(windowPanels.position);
	}

	// 1.3 Applied to control windows

	//params_LayoutsExtra.add(bModeFree);
	//params_LayoutsExtra.add(bModeForced);
	//params_LayoutsExtra.add(bModeLock1);
	//params_LayoutsExtra.add(bModeLockControls);

	// 1.4 Pack both groups

	params_Layouts.add(params_LayoutsVisible);
	params_Layouts.add(params_LayoutsExtra);

	//-

	// Initiate

	bLayoutPresets.clear();
	params_LayoutPresetsStates.clear();
	appLayoutIndex.setMax(0);

	// Populate some presets

	for (int i = 0; i < numPresetsDefault; i++)
	{
		if (namesPresets.size() == 0) {//if names are not defined will be setted by default P0-P1-P2-P3
			createLayoutPreset();
		}
		else {
			if (i < namesPresets.size()) createLayoutPreset(namesPresets[i]);
			else createLayoutPreset();
		}
	}

	//--

	// 4. App states for the next session

	// The main control windows

	//params_AppSettingsLayout.add(bModeFree);
	//params_AppSettingsLayout.add(bModeForced);
	//params_AppSettingsLayout.add(bModeLock1);
	//params_AppSettingsLayout.add(bModeLockControls);
	//params_AppSettingsLayout.add(bModeLockPreset);

	params_AppSettingsLayout.add(bGui_LayoutsPresets);
	params_AppSettingsLayout.add(bGui_LayoutsExtra);
	params_AppSettingsLayout.add(bGui_LayoutsPanels);
	params_AppSettingsLayout.add(bAutoSave_Layout);
	params_AppSettingsLayout.add(bPreviewSceneViewport);
	params_AppSettingsLayout.add(appLayoutIndex);
	params_AppSettingsLayout.add(bSolo);

	params_AppSettings.add(params_AppSettingsLayout);
	params_AppSettings.add(bGui_LayoutsManager);
	params_AppSettings.add(params_Advanced);

	//if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
	//{
	//	if (surfingImGuiMode != IM_GUI_MODE_INSTANTIATED_DOCKING)
	//	{
	//		//params_AppSettings.add(bGui_WindowsSpecials);
	//		//params_AppSettings.add(windowPanels.getParamsUser());
	//	}
	//}

	//-

	// Exclude from settings but to use the grouped callback
	//bSolo.setSerializable(false);

	//---------------

	// Engine Windows

	// Initiate the 3 control windows
	// We store the shapes using ofRectangles to "split" them from ImGui .ini store manager...

	float x, y, w, h, pad;
	x = ofGetWidth() * 0.4;
	y = ofGetHeight() * 0.3;
	w = 200;
	h = 1;
	pad = 2;

	rect0_Presets.set(ofRectangle(x, y, w, h));
	rect1_Panels.set(ofRectangle(x + (pad + w), y, w, h));
	rect2_Manager.set(ofRectangle(x + 2 * (pad + w), y, w, h));

	rectangles_Windows.clear();
	rectangles_Windows.emplace_back(rect0_Presets);
	rectangles_Windows.emplace_back(rect1_Panels);
	rectangles_Windows.emplace_back(rect2_Manager);

	params_RectPanels.clear();
	params_RectPanels.add(rect0_Presets);
	params_RectPanels.add(rect1_Panels);
	params_RectPanels.add(rect2_Manager);

	params_WindowsEngine.clear();
	params_WindowsEngine.add(params_RectPanels);

	//-

	// Presets and Panles Widnows

	params_WindowPresets.add(bResetWindowPresets);
	params_WindowPresets.add(bAutoResizePresets);
	params_WindowPresets.add(bMinimizePresets);

	params_WindowPanels.add(bResetWindowPanels);
	params_WindowPanels.add(bAutoResizePanels);
	params_WindowPresets.add(bMinimizePanels);

	params_WindowsEngine.add(params_WindowPresets);
	params_WindowsEngine.add(params_WindowPanels);

	params_AppSettings.add(params_WindowsEngine);


	//----

	// Callbacks
	ofAddListener(params_LayoutPresetsStates.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);
	ofAddListener(params_AppSettings.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);
	ofAddListener(params_Panels.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_Params);

	//-

	//// Gui - > wich panels enabled but overwritten by Layout Presets Engine
	//params_AppSettings.add(params_Panels);

	//--

	setImGuiLayoutPresets(true);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadAppSettings()
{
	/*if (bAutoSaveSettings) */ofxImGuiSurfing::loadGroup(params_AppSettings, path_AppSettings, true);


}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveAppSettings()
{
	/*if (bAutoSaveSettings) */ofxImGuiSurfing::saveGroup(params_AppSettings, path_AppSettings, true);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveAppLayout(int _index)
{
	if (_index == -1) return;

	ini_to_save_Str = getLayoutName(_index);

	ofLogNotice(__FUNCTION__) << ini_to_save_Str;

	if (ini_to_save_Str == "-1") return; // skip

	// Flag to save .ini on update
	ini_to_save = ini_to_save_Str.c_str();

	// Save group
	saveLayoutPresetGroup(ini_to_save);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadAppLayout(int _index)
{
	if (_index == -1) return;

	//if (appLayoutIndex == _index) return; // skip

	appLayoutIndex = ofClamp(_index, appLayoutIndex.getMin(), appLayoutIndex.getMax());

	std::string _name = getLayoutName(appLayoutIndex.get());
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

	// Window title
	titleWindowLabel = _label + " " + _name;
	//titleWindowLabel = _label + " " + ofToString(appLayoutIndex.get()) + " " + _name;

	//// Apply window title
	//ofSetWindowTitle(titleWindowLabel);

	// ini
	ini_to_load_Str = _name;
	ini_to_load = ini_to_load_Str.c_str();

	// Group
	loadLayoutPresetGroup(ini_to_load_Str);

	ofLogNotice(__FUNCTION__) << "------------------------------------";
	ofLogNotice(__FUNCTION__) << "ini_to_load    : " << ini_to_load;
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutsPresets()
{
	flags_wPr = ImGuiWindowFlags_None;
	flags_wPr += ImGuiWindowFlags_NoSavedSettings;

	if (bAutoResizePresets) flags_wPr += ImGuiWindowFlags_AlwaysAutoResize;

	//--

	/*
	//// Viewport Center
	//// is excluded from .ini
	//float xw, yw, ww, hw;
	//{
	//	if (bModeForced)
	//	{
	//		// Forced inside a free viewport
	//		//// Upper left
	//		//glm::vec2 p = rectangle_Central_MAX.getTopLeft() + glm::vec2(-1, -1);
	//		// Center upper left
	//		int _pad = 10;
	//		int _xx = rectangle_Central_MAX.getTopLeft().x + _pad;
	//		int _yy = rectangle_Central_MAX.getTopLeft().y + rectangle_Central_MAX.getHeight() / 2 - hw / 2;
	//		glm::vec2 p = glm::vec2(_xx, _yy);
	//		// Shape
	//		xw = p.x;
	//		yw = p.y;
	//		flagCond = ImGuiCond_Always;
	//		ImGui::SetNextWindowPos(ofVec2f(xw, yw), flagCond);
	//		//ImGui::SetNextWindowSize(ofVec2f(ww, hw), flagCond); // exclude shape
	//	}
	//}
	*/

	ImGuiCond prCond = ImGuiCond_None;
	prCond += ImGuiCond_Appearing;

	if (bResetWindowPresets)
	{
		bResetWindowPresets = false;

		const int i = 0;
		ofRectangle r = rectangles_Windows[i];
		r.setWidth(100);
		r.setHeight(100);
		rectangles_Windows[i].set(r);
		prCond = ImGuiCond_Always;

		// workflow
		bAutoResizePresets = true;
		bMinimizePresets = true;
		bGui_LayoutsManager = false;
	}

	//----

	const int i = 0;
	ImGui::SetNextWindowPos(ImVec2(rectangles_Windows[i].get().getX(), rectangles_Windows[i].get().getY()), prCond);
	ImGui::SetNextWindowSize(ImVec2(rectangles_Windows[i].get().getWidth(), rectangles_Windows[i].get().getHeight()), prCond);

	//-

	if (beginWindow(bGui_LayoutsPresets, flags_wPr))
	{
		float _h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
		float _w1 = ofxImGuiSurfing::getWidgetsWidth(1);
		float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);
		float _w = _w2;

		//--

		const int i = 0;
		rectangles_Windows[i].setWithoutEventNotifications(ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()));

		//--

		// Minimize (global)

		//ofxImGuiSurfing::AddToggleRounded(bMinimizePresets);
		this->Add(bMinimizePresets, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);

		//--

		// Preset Toggles

		const int NUM_WIDGETS = bLayoutPresets.size() + 4;
		for (int i = 0; i < bLayoutPresets.size(); i++)
		{
			ofxImGuiSurfing::AddBigToggle(bLayoutPresets[i], _w2, _h);
			if (i % 2 == 0) ImGui::SameLine();
		}

		//// Autosave/Save when minimized
		//if (bMinimizePresets)
		//{
		//	// Autosave
		//	ofxImGuiSurfing::AddBigToggle(bAutoSave_Layout, _w1, 0.75 * _h, true);
		//	//ofxImGuiSurfing::AddBigToggle(bAutoSave_Layout, _w1, 0.75 * _h);

		//	// Save Button
		//	if (!bAutoSave_Layout.get())
		//	{
		//		ImGui::PushID("##SaveLayout0");
		//		if (ImGui::Button("Save", ImVec2(_w1, 0.5 * _h)))
		//		{
		//			saveAppLayout(appLayoutIndex.get());
		//		}
		//		ImGui::PopID();
		//	}
		//}

		ofxImGuiSurfing::AddSpacingSeparated();

		//--

		if (bLayoutPresets.size() % 2 == 0) _w = _w1;

		//--

		// Panels & Manager

		ofxImGuiSurfing::AddBigToggle(bGui_LayoutsPanels, _w1, (bMinimizePresets ? _h * 0.75f : _h));
		//ofxImGuiSurfing::AddBigToggle(bGui_LayoutsPanels, _w1, (bMinimizePresets ? _h / 2 : _h));
		if (!bMinimizePresets) ofxImGuiSurfing::AddBigToggle(bGui_LayoutsManager, _w1, (bMinimizePresets ? _h / 2 : _h));

		//--

		if (!bMinimizePresets)
		{
			ofxImGuiSurfing::AddSpacingSeparated();

			// Autosave
			ofxImGuiSurfing::AddBigToggle(bAutoSave_Layout, _w1, 0.75 * _h, true);

			// Save Button
			if (!bAutoSave_Layout.get())
			{
				ImGui::PushID("##SaveLayout");
				if (ImGui::Button("Save", ImVec2(_w1, 0.5 * _h)))
				{
					saveAppLayout(appLayoutIndex.get());
				}
				ImGui::PopID();
			}

			ImGui::Spacing();
		}

		//-

		if (!bMinimizePresets)
		{
			// Reset Window

			//if (ofxImGuiSurfing::AddButtonMini(bResetWindowPresets))
			if (this->Add(bResetWindowPresets, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL))
			{
				bResetWindowPresets = true;
			}

			//--

			// Help

			this->Add(bHelp, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);

			//--

			// Autoresize & Extra

			this->Add(bAutoResizePresets, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);
			this->Add(bGui_LayoutsExtra, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);

			//ofxImGuiSurfing::AddToggleRoundedButton(bAutoResizePresets);
			//ofxImGuiSurfing::AddToggleRoundedButton(bGui_LayoutsExtra);
		}
	}

	this->endWindow();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutsExtra()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	window_flags |= ImGuiWindowFlags_NoTitleBar;//hide header

	if (bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	//--

	bool bMin = false; // hide load buttons to simplify
	float max = (bMin ? 150 : 175);

	//----

	int _pad = PADDING_PANELS;

	ImGuiCond _flagc;
	_flagc = ImGuiCond_Always;

	const int i = 0;
	ImGui::SetNextWindowPos(ofVec2f(rectangles_Windows[i].get().getX(), rectangles_Windows[i].get().getY() + rectangles_Windows[i].get().getHeight() + _pad), _flagc);
	ImGui::SetNextWindowSize(ofVec2f(rectangles_Windows[i].get().getWidth(), -1), _flagc);

	//----

	if (beginWindow(bGui_LayoutsExtra, window_flags))
	{
		float _h = ofxImGuiSurfing::getWidgetsHeightUnit();
		float _w1 = ofxImGuiSurfing::getWidgetsWidth(1);
		float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);

		if (!bMinimizePresets)
		{
			ofxImGuiSurfing::AddToggleRounded(bMenu);
			ofxImGuiSurfing::AddToggleRounded(bLog);
			ofxImGuiSurfing::AddToggleRounded(bKeys);
		}

		//--

		if (!bMinimizePresets)
		{
			if (ImGui::CollapsingHeader("Presets", ImGuiWindowFlags_None))
			{
				ImVec2 bb{ (bMin ? _w1 : _w2), _h };

				//--

				int _id = 0;
				for (int i = 0; i < bLayoutPresets.size(); i++)
				{
					std::string _name = (bLayoutPresets[i].getName());

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

				if (ImGui::Button("Reset", ImVec2(_w1, _h)))
				{
					if (bResetPtr != nullptr) {
						*bResetPtr = true;
					}

					// Toggle panels to true
					for (int i = 0; i < windowsAtributes.size(); i++) {
						windowsAtributes[i].bGui.set(true);
					}

					saveAppLayout((appLayoutIndex.get()));
				}

				if (ImGui::Button("Clear", ImVec2(_w1, _h)))
				{
					doRemoveDataFiles();
				}
			}
		}

		//-

		//if (!bMinimizePresets)
		if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		{
			if (ImGui::CollapsingHeader(nameWindowSpecialsPanel.c_str(), ImGuiWindowFlags_None))
				//if (ImGui::CollapsingHeader("Organizer", ImGuiWindowFlags_None)) 
			{
				windowPanels.drawWidgets(bMinimizePresets);
			}
		}

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

		////TODO:
		//if (surfingImGuiSpecialWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER)
		//{
		//	if (ImGui::Button("Reset Layout", ImVec2(_w1, _h)))
		//	{
		//	}
		//}

		//--

		this->endWindow();
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::Changed_Params(ofAbstractParameter &e)
{
	std::string name = e.getName();

	if (name != "position" &&
		name != "rect_Manager")
	{
		ofLogNotice(__FUNCTION__) << name << " : " << e;
	}

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

	// Reset 
	// This toggle/flag is "sended" to the parent scope (ofApp), to resets something in our apps.
	// Example: to resets the layout.
	else if (name == bReset.getName() && bReset.get())
	{
		bReset = false;

		if (bResetPtr != nullptr) {
			*bResetPtr = true;
		}
	}

	//-

	// Solo Panel

	else if (name == bSolo.getName() && bSolo.get())
	{
		// workflow
		appLayoutIndex = -1;

		// disable preset
		for (int i = 0; i < bLayoutPresets.size(); i++)
		{
			bLayoutPresets[i].setWithoutEventNotifications(false);
		}
	}

	//--

	// Layout preset index

	else if (name == appLayoutIndex.getName())
	{
		//appLayoutIndex = ofClamp(appLayoutIndex.get(), appLayoutIndex.getMin(), appLayoutIndex.getMax());

		if (appLayoutIndex != appLayoutIndex_PRE /*&& appLayoutIndex_PRE != -1*/) //changed
		{
			ofLogNotice(__FUNCTION__) << "Changed: " << appLayoutIndex;

			//-

			// 1. Autosave
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

		// Hide all modules / gui toggles
		if (appLayoutIndex == -1)
		{
			for (int i = 0; i < windowsAtributes.size(); i++)
			{
				windowsAtributes[i].bGui.set(false);
			}
			return; // not required bc loadAppLayout will be skipped when -1
		}

		//-

		// 2. Load layout
		loadAppLayout(appLayoutIndex.get());
	}

	//-

	// Presets Selector exclusive toggles

	{
		bool bSomeTrue = false;
		for (int i = 0; i < bLayoutPresets.size(); i++)
		{
			if (name == bLayoutPresets[i].getName())
			{
				if (bLayoutPresets[i].get()) // true
				{
					// workflow
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
					if (bAllFalse)
					{
						// workflow A
						////force back to true if it's there's no other enabled..
						//bLayoutPresets[appLayoutIndex].set(true);

						// workflow B
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

	// Solo Panels Selectors
	{
		bool bSomeTrue = false;
		for (int i = 0; i < windowsAtributes.size(); i++)
		{
			int iTrue = -1;
			if (name == windowsAtributes[i].bGui.getName() && windowsAtributes[i].bGui.get()) {
				iTrue = i;
				if (bSolo.get())
				{
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

	//// Rectangles
	//{
	//	for (int i = 0; i < rectangles_Windows.size(); i++)
	//	{
	//		if (name == rectangles_Windows[i].getName())
	//		{
	//		}
	//	}
	//}
}

//----

// Layout Preset Loaders / Savers

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveLayoutPreset(std::string path)
{
	saveLayoutImGuiIni(path);
	saveLayoutPresetGroup(path);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadLayoutPreset(std::string path)
{
	loadLayoutImGuiIni(ini_to_load);
	loadLayoutPresetGroup(path);
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveLayoutImGuiIni(std::string path)
{
	ImGui::SaveIniSettingsToDisk(ofToDataPath(path_ImLayouts + path + ".ini", true).c_str());
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadLayoutImGuiIni(std::string path)
{
	ImGui::LoadIniSettingsFromDisk(ofToDataPath(path_ImLayouts + path + ".ini", true).c_str());
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveLayoutPresetGroup(std::string path)
{
	ofxImGuiSurfing::saveGroup(params_Layouts, path_ImLayouts + path + ".json");
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadLayoutPresetGroup(std::string path)
{
	ofxImGuiSurfing::loadGroup(params_Layouts, path_ImLayouts + path + ".json");
}

//----

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::createLayoutPreset(std::string namePreset)
{
	std::string n;
	int i = bLayoutPresets.size();

	if (namePreset == "-1") n = "P" + ofToString(i);
	else n = namePreset;

	ofParameter<bool> _b = ofParameter<bool>{ n, false };
	bLayoutPresets.push_back(_b);
	appLayoutIndex.setMax(bLayoutPresets.size() - 1);
	params_LayoutPresetsStates.add(bLayoutPresets[i]);
}

//----

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawLayoutsPanels()
{
	flags_wPanels = ImGuiWindowFlags_None;
	flags_wPanels += ImGuiWindowFlags_NoSavedSettings;
	if (bAutoResizePanels) flags_wPanels += ImGuiWindowFlags_AlwaysAutoResize;

	//--

	static bool bLandscape;
	// Docking mode ignores these constraints...
#ifdef OFX_IMGUI_CONSTRAIT_WINDOW_SHAPE
	// Landscape
	if (bLandscape) ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(700, 150)); // ?
	// Portrait
	else ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(105, 300));
#endif

	//--

	ImGuiCond pnCond = ImGuiCond_None;
	pnCond += ImGuiCond_Appearing;

	if (bResetWindowPanels)
	{
		bResetWindowPanels = false;

		const int i = 1;
		ofRectangle r = rectangles_Windows[i];
		r.setWidth(150);
		r.setHeight(150);
		rectangles_Windows[i].set(r);
		pnCond = ImGuiCond_Always;
	}

	//-

	const int i = 1;
	ImGui::SetNextWindowPos(ofVec2f(rectangles_Windows[i].get().getX(), rectangles_Windows[i].get().getY()), pnCond);
	ImGui::SetNextWindowSize(ofVec2f(rectangles_Windows[i].get().getWidth(), rectangles_Windows[i].get().getHeight()), pnCond);

	if (beginWindow(bGui_LayoutsPanels, flags_wPanels))
	{
		const int i = 1;
		rectangles_Windows[i].setWithoutEventNotifications(ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight()));

		bLandscape = false;
		float __w = ImGui::GetWindowWidth();
		float __h = ImGui::GetWindowHeight();
		if (__w > __h) bLandscape = true;

		//-

		const int NUM_WIDGETS = windowsAtributes.size(); // expected num widgets
		const int NUM_WIDGETS_EXTRA_LANDSCAPE = 5;
		//const int NUM_WIDGETS_EXTRA_LANDSCAPE = 6; // with autoresize

		float _spcx = ImGui::GetStyle().ItemSpacing.x;
		float _spcy = ImGui::GetStyle().ItemSpacing.y;
		float _h100 = ImGui::GetContentRegionAvail().y;

		float _w;
		float _h;
		float _hWid;

		// A. Landscape

		if (bLandscape)
		{
			//_w = ofxImGuiSurfing::getWidgetsWidth(NUM_WIDGETS + 2);
			const int amntColumns = NUM_WIDGETS + 2;
			float __w100 = ImGui::GetContentRegionAvail().x - (3 * _spcx); // remove extra columns x spacing added!
			_w = (__w100 - _spcx * (amntColumns - 1)) / amntColumns;

			_h = _h100 - _spcy;
			_hWid = (_h - _spcy) / 2;
			//_hWid = (_h - _spcy) / 3; // with autoResize
		}

		// B. Portrait

		else
		{
			_hWid = ofxImGuiSurfing::getWidgetsHeightRelative();
			float _hTotal = _h100 - (_hWid * NUM_WIDGETS_EXTRA_LANDSCAPE + (NUM_WIDGETS_EXTRA_LANDSCAPE + 1) * _spcy);
			_w = ofxImGuiSurfing::getWidgetsWidth();
			_h = _hTotal / NUM_WIDGETS - _spcy;
		}

		// Landscape
		if (bLandscape)
		{
			ImGui::Columns(3);
			ImGui::SetColumnWidth(0, _spcx + (_w + _spcx) * NUM_WIDGETS);
		}

		//-

		// 1. Populate all toggles

		for (int i = 0; i < windowsAtributes.size(); i++)
		{
			ofxImGuiSurfing::AddBigToggle(windowsAtributes[i].bGui, _w, _h);
			if (bLandscape) ImGui::SameLine();
		}

		//-

		float _w100;
		float _w50;

		// Landscape
		if (bLandscape)
		{
			ImGui::SameLine();
			_w100 = _w;
			_w50 = (_w - _spcx) / 2.0f;
		}
		// Portrait
		else
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
			_w100 = ofxImGuiSurfing::getWidgetsWidth(1);
			_w50 = ofxImGuiSurfing::getWidgetsWidth(2);
		}

		// Landscape
		if (bLandscape) {
			ImGui::NextColumn();
			ImGui::SetColumnWidth(1, _w100 + 2 * _spcx);
		}

		//-

		// 2. Extra widgets

		if (ImGui::Button("All", ImVec2(_w50, _hWid)))
		{
			// workflow
			if (bSolo) bSolo.set(false);

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

		// 3. Panels Toggles

		// Landscape
		if (bLandscape)
		{
			ImGui::NextColumn();
			ImGui::SetColumnWidth(2, _w100 + _spcx + _spcx);
		}
		// Portrait
		else
		{
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
		}

		// Layout
		float _hUnit = ofxImGuiSurfing::getWidgetsHeightRelative();
		//ofxImGuiSurfing::AddBigToggle(bGui_LayoutsPresets, _w100, _hWid, false);
		ofxImGuiSurfing::AddBigToggle(bGui_LayoutsPresets, _w100, (bMinimizePresets ? ofxImGuiSurfing::getPanelHeight() : _hWid), false);

		if (!bMinimizePresets) ofxImGuiSurfing::AddBigToggle(bGui_LayoutsManager, _w100, _hWid, false);

		//ofxImGuiSurfing::AddToggleRoundedButton(bAutoResizePanels);

		// Landscape
		if (bLandscape)
		{
			ImGui::Columns();
		}

		this->endWindow();
	}

	//-

#ifdef OFX_IMGUI_CONSTRAIT_WINDOW_SHAPE
	ImGui::PopStyleVar();
#endif
}

//--

// Keys
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::keyPressed(ofKeyEventArgs &eventArgs)
{
	if (!bKeys || !bUseLayoutPresetsManager) return;

	const int &key = eventArgs.key;
	ofLogNotice(__FUNCTION__) << (char)key << " [" << key << "]";

	// Modifiers
	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	// Log
	if (key != OF_KEY_SHIFT && !mod_COMMAND && !mod_CONTROL && !mod_ALT && !mod_SHIFT) {
		std::string ss = ofToString((char)key);
		log.AddText(ss);
	}

	//-

	bool debug = false;
	if (debug)
	{
		ofLogNotice(__FUNCTION__) << "mod_COMMAND: " << (mod_COMMAND ? "ON" : "OFF");
		ofLogNotice(__FUNCTION__) << "mod_CONTROL: " << (mod_CONTROL ? "ON" : "OFF");
		ofLogNotice(__FUNCTION__) << "mod_ALT: " << (mod_ALT ? "ON" : "OFF");
		ofLogNotice(__FUNCTION__) << "mod_SHIFT: " << (mod_SHIFT ? "ON" : "OFF");
	}	if (!bKeys) return;

	{
		switch (key)
		{

			// Layout Presets

		case OF_KEY_F1: bLayoutPresets[0] = !bLayoutPresets[0]; break;
		case OF_KEY_F2: bLayoutPresets[1] = !bLayoutPresets[1]; break;
		case OF_KEY_F3: bLayoutPresets[2] = !bLayoutPresets[2]; break;
		case OF_KEY_F4: bLayoutPresets[3] = !bLayoutPresets[3]; break;
		default: break;
		}

		if (key == OF_KEY_F5 /*|| key == 'p'*/) // Presets
		{
			bGui_LayoutsPresets = !bGui_LayoutsPresets;
		}

		if (key == OF_KEY_F6) // Panels
		{
			bGui_LayoutsPanels = !bGui_LayoutsPanels;
		}

		else if (key == OF_KEY_F7) // Extra
		{
			bGui_LayoutsExtra = !bGui_LayoutsExtra;
		}

		//// Solo
		//else if (key == 's')
		//{
		//	bSolo = !bSolo;
		//}

		//// Unlock Dock 
		//else if (key == 'l')
		//{
		//	bModeLock1 = !bModeLock1;
		//}
		//else if (key == 'L')
		//{
		//	bModeLockControls = !bModeLockControls;
		//}

		//--

		//// Layout Modes

		//else if (key == OF_KEY_TAB && !mod_CONTROL)
		//{
		//	if (appLayoutIndex > appLayoutIndex.getMin()) appLayoutIndex++;
		//	else if (appLayoutIndex == appLayoutIndex.getMin()) appLayoutIndex = appLayoutIndex.getMax();
		//	//if (appLayoutIndex < 3) loadAppLayout(AppLayouts(appLayoutIndex + 1));
		//	//else if (appLayoutIndex == 3) loadAppLayout(AppLayouts(0));
		//}
	}

	//--

	//// Key Enabler
	//if (key == 'k')
	//{
	//	bKeys = !bKeys;
	//	ofLogNotice(__FUNCTION__) << "KEYS: " << (bKeys ? "ON" : "OFF");
	//	if (!bKeys)
	//	{
	//		ofLogNotice(__FUNCTION__) << "ALL KEYS DISABLED. PRESS 'k' TO ENABLE GAIN!";
	//	}
	//	else
	//	{
	//		ofLogNotice(__FUNCTION__) << "KEYS ENABLED BACK";
	//	}
	//}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::keyReleased(ofKeyEventArgs &eventArgs)
{
	const int &key = eventArgs.key;
	ofLogNotice(__FUNCTION__) << (char)key << " [" << key << "]";

	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);
}

//--

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::draw_ImGuiMenu()
{
	static bool opt_fullscreen = true;
	static bool* p_open = NULL;
	static bool opt_exit = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	//-

	// Menu bar

	// This is not operative. just for testing menus!

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ofWindowMode windowMode = ofGetCurrentWindow()->getWindowMode();
			if (windowMode == OF_WINDOW) opt_fullscreen = false;
			else if (windowMode == OF_FULLSCREEN) opt_fullscreen = true;
			else if (windowMode == OF_GAME_MODE) opt_fullscreen = false;

			if (ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen))
			{
				ofSetFullscreen(opt_fullscreen);
			}

			ofxImGuiSurfing::AddSpacingSeparated();

			if (ImGui::MenuItem("Exit", NULL, &opt_exit))
			{
				ofExit();
				//*opt_exit = false;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Copy", NULL)) {}
			if (ImGui::MenuItem("Paste", NULL)) {}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Layouts"))
		{
			for (int i = 0; i < bLayoutPresets.size(); i++)
			{
				if (ImGui::MenuItem(bLayoutPresets[i].getName().c_str(), "", (bool*)&bLayoutPresets[i].get()))
				{
					bLayoutPresets[i] = bLayoutPresets[i]; // to trig
				}
			}
			//ofxImGuiSurfing::AddSpacingSeparated();
			//if (ImGui::MenuItem("All", NULL)) { setShowAllPanels(true); }
			//if (ImGui::MenuItem("None", NULL)) { setShowAllPanels(false); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Docking"))
		{
			dockspace_flags = ImGui::GetIO().ConfigFlags;

			if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
			if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			//if (ImGui::MenuItem("Flag: ConfigDockingWithShift", "", (dockspace_flags & ImGuiDockNodeFlags_) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			//ofxImGuiSurfing::AddSpacingSeparated();

			ImGui::GetIO().ConfigFlags = dockspace_flags;
			//ImGui::GetIO().ConfigDockingWithShift = true;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("About"))
		{
			ofxImGuiSurfing::AddTooltipHelp(
				"This is not operative here. Just for testing menus!" "\n\n"
				"When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n"
				"- Drag from window title bar or their tab to dock/undock." "\n"
				"- Drag from window menu button (upper-left button) to undock an entire node (all windows)." "\n"
				"- Hold SHIFT to enable dragging docking." "\n"
				"This demo app has nothing to do with it!" "\n\n"
				"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)." "\n\n"
				"ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame." "\n\n"
				"(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)"
			);

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}


//----

/*
//TODO:
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::drawSpecialWindowsPanel()
{
	if (ImGui::TreeNode("Special Windows"))
	{
		//ImGui::Text("Special Windows");

		//ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		//if (bAutoResizePanels) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		//if (beginWindow("Specials", NULL, window_flags))
		{
			const int NUM_WIDGETS = windowsAtributes.size(); // expected num widgets

			float _spcx = ImGui::GetStyle().ItemSpacing.x;
			float _spcy = ImGui::GetStyle().ItemSpacing.y;
			//float _h100 = ImGui::GetContentRegionAvail().y;

			// 1. populate all toggles

			const int _amnt = 1;

			float _w = ofxImGuiSurfing::getWidgetsWidth(_amnt);
			float _h = 1 * ofxImGuiSurfing::getWidgetsHeightRelative();
			//float _w = ofxImGuiSurfing::getWidgetsWidth(windowsAtributes.size());

			for (int i = 0; i < NUM_WIDGETS; i++)
			{
				if (i > windowsAtributes.size() - 1) continue;

				ofxImGuiSurfing::AddBigToggle(windowsAtributes[i].bGui, _w, _h);

				//if ((i + 1) % _amnt != 0 && i < NUM_WIDGETS - 1) ImGui::SameLine();
			}
		}

		ImGui::TreePop();
	}
}*/

//--

// Special behaviour to control windows

//// Free layout
//else if (name == bModeFree.getName())
//{
//	if (bModeFree.get())
//	{
//		flagsWindowsModeFreeStore = ImGuiWindowFlags_NoSavedSettings;
//	}
//	else
//	{
//		flagsWindowsModeFreeStore = ImGuiWindowFlags_None;
//	}
//}

//-

//// Lock layout
//else if (name == bModeLock1.getName())
//{
//	if (!bModeLock1)
//	{
//		flagsWindowsLocked1 = ImGuiWindowFlags_None;
//	}
//	else
//	{
//		flagsWindowsLocked1 = ImGuiWindowFlags_NoMove;
//		flagsWindowsLocked1 |= ImGuiWindowFlags_NoSavedSettings;
//		//flagsWindowsLocked1 |= ImGuiWindowFlags_NoResize;
//		//flagsWindowsLocked1 |= ImGuiWindowFlags_NoTitleBar;
//		//flagsWindowsLocked1 |= ImGuiWindowFlags_NoCollapse;
//		//flagsWindowsLocked1 |= ImGuiWindowFlags_NoDecoration;
//		//flagsWindowsLocked1 |= ImGuiWindowFlags_NoBackground;
//		//flagsWindowsLocked1 |= ImGuiDockNodeFlags_AutoHideTabBar;
//		//flagsWindowsLocked1 |= ImGuiDockNodeFlags_NoTabBar;
//		//flagsWindowsLocked1 |= ImGuiDockNodeFlags_NoCloseButton;
//	}
//}
//else if (name == bModeLockControls.getName())
//{
//	if (!bModeLockControls)
//	{
//		flagsWindowsLocked2 = ImGuiWindowFlags_None;
//	}
//	else
//	{
//		flagsWindowsLocked2 = ImGuiWindowFlags_NoMove;
//		//flagsWindowsLocked2 |= ImGuiWindowFlags_NoResize;
//		//flagsWindowsLocked2 |= ImGuiWindowFlags_NoTitleBar;
//		//flagsWindowsLocked2 |= ImGuiWindowFlags_NoCollapse;
//		//flagsWindowsLocked2 |= ImGuiWindowFlags_NoDecoration;
//		//flagsWindowsLocked2 |= ImGuiWindowFlags_NoBackground;
//		//flagsWindowsLocked2 |= ImGuiDockNodeFlags_AutoHideTabBar;
//		//flagsWindowsLocked2 |= ImGuiDockNodeFlags_NoTabBar;
//		//flagsWindowsLocked2 |= ImGuiDockNodeFlags_NoCloseButton;
//	}
//}