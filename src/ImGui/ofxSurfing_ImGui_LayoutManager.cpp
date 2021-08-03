#include "ofxSurfing_ImGui_LayoutManager.h"

//--------------------------------------------------------------
ofxSurfing_ImGui_Manager::ofxSurfing_ImGui_Manager() {

	params_Advanced.add(bAdvanced);
	params_Advanced.add(bAutoResize);
	params_Advanced.add(bExtra);
	params_Advanced.add(bMinimize);

	// must be here to allow to be changed before setup!
	//// EXAMPLE
	//guiManager.setImGuiAutodraw(true);
	//guiManager.setup(); // this instantiates and configurates ofxImGui inside the class object.

	// -> TODO: BUG?: 
	// it seems than requires to be false when using multi-context/instances
	// if is setted to true, sometimes it hangs and gui do not refresh/freezes.
	bAutoDraw = false;

	//bAutoDraw = true;
	//if(bAutoSaveSettings) loadGroup(params_AppSettings, path_Settings);
};

//--------------------------------------------------------------
ofxSurfing_ImGui_Manager::~ofxSurfing_ImGui_Manager() {
	ofRemoveListener(params_LayoutPanelsState.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_LayoutPanels);

	if (bAutoSaveSettings) saveGroup(params_AppSettings, path_Settings);
	if (bAutoSaveSettings) saveGroup(params_LayoutPanelsState, path_SettingsLayout);
};

//--

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setup() { // using internal instantiated gui
	setup_ImGui();

	if (bAutoSaveSettings) loadGroup(params_AppSettings, path_Settings);

	//setupLayoutPresets();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setup(ofxImGui::Gui & _gui) { // using external instantiated gui
	guiPtr = &_gui;

	setup_ImGui();
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
	//Open the Open File Dialog
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a font file, ttf or otf to add to ImGui", false, ofToDataPath(""));

	//Check if the user opened a file
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
void ofxSurfing_ImGui_Manager::setup_ImGui()
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
	_fontName = "telegrama_render.otf"; // WARNING: will crash if font not present!
	_fontSizeParam = 11;
	std::string _path = "assets/fonts/"; // assets folder

	pushFont(_path + _fontName, _fontSizeParam); // queue default font too

	addFont(_path + _fontName, _fontSizeParam);

	//// extra fonts
	//addFont(_path + "OpenSans-Light.ttf", 16);
	//addFont(_path + "OpenSans-Regular.ttf", 16);
	//addFont(_path + "OpenSans-Light.ttf", 32);
	//addFont(_path + "OpenSans-Regular.ttf", 11);
	//addFont(_path + "OpenSans-Bold.ttf", 11);

	//-

	// theme
	//ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing();
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::draw() {
	if (customFont == nullptr) gui.draw();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::update() {

	// layouts

	if (ini_to_load)
	{
		ofLogNotice(__FUNCTION__) << "LOAD!" << ini_to_load;

		ImGui::LoadIniSettingsFromDisk(ofToDataPath(ini_to_load, true).c_str());
		//ImGui::LoadIniSettingsFromDisk(ini_to_load);
		ini_to_load = NULL;
	}

	if (ini_to_save)
	{
		ofLogNotice(__FUNCTION__) << "SAVE!" << ini_to_save;

		ImGui::SaveIniSettingsToDisk(ofToDataPath(ini_to_save, true).c_str());
		//ImGui::SaveIniSettingsToDisk(ini_to_save);
		ini_to_save = NULL;

		ofxSurfingHelpers::saveGroup(params_LayoutPanelsState, ini_to_save_Str + ".json");
	}
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::begin() {
	if (guiPtr != nullptr) guiPtr->begin();
	else gui.begin();

	if (customFont != nullptr) ImGui::PushFont(customFont);

	//----

	if (bUseLayout)
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
		ImGuiDockNodeFlags flagsDock;
		flagsDock = ImGuiDockNodeFlags_PassthruCentralNode;
		if (Lock_DockingLayout)
		{
			flagsDock |= ImGuiDockNodeFlags_NoResize;
			flagsDock |= ImGuiDockNodeFlags_NoCloseButton;
			//flagsDock |= ImGuiDockNodeFlags_NoTabBar;
			//flagsDock |= ImGuiDockNodeFlags_NoWindowMenuButton;
			//flagsDock |= ImGuiDockNodeFlags_NoMove__;
		}
		ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, flagsDock);
		//ImGui::PopStyleColor();

		//----

		update();

		//--

		//beginWindow("Layout Controls", NULL);
		//beginWindow("Layout Controls");

		AddToggleRoundedButton(SHOW_LayoutsAdvanced);
		AddToggleRoundedButton(SHOW_Layouts);
		AddToggleRoundedButton(SHOW_Panels);

		if (SHOW_LayoutsAdvanced) gui_LayoutsAdvanced();
		if (SHOW_Layouts) gui_LayoutsPresets();
		if (SHOW_Panels) gui_Panels();

		//----

		// get check free space
		// central inter docks rectangle

		//TODO:
		//if (bUseLayout)
		{
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

					bool bDebug = bDebugRectCentral;
					if (bDebug)
					{
						int _wl = 3;
						ofPushStyle();
						ofSetRectMode(OF_RECTMODE_CENTER);
						int g = 0;
						//int g = 255 * ofxSurfingHelpers::Bounce(0.5);
						int a = 255.f * ofMap(ofxSurfingHelpers::Bounce(1), 0.0f, 1.0f, 0.2f, 1.0f, true);
						ofColor c = ofColor(g, a);
						ofSetColor(c);
						ofNoFill();
						ofSetLineWidth(_wl);

						ofRectangle rDebug;
						int pad = 3;
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

		//TODO:
		setDefaultFont();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh)); // minimal size

		//-

		// docking
		if (bDocking && bDockingModeCentered)
		{
			ImGuiDockNodeFlags dockingFlags = ImGuiDockNodeFlags_PassthruCentralNode; // Make the docking space transparent
			ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, dockingFlags); // Also draws the docked windows

			ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(dockNodeID);
			if (dockNode)
			{
				ImGuiDockNode* centralNode = ImGui::DockBuilderGetCentralNode(dockNodeID);

				// debug scene viewport
				if (bPreviewSceneViewport)
				{
					// Verifies if the central node is empty (visible empty space for oF)
					if (centralNode && centralNode->IsEmpty()) {
						ImRect availableSpace = centralNode->Rect();
						//availableSpace.Max = availableSpace.Min + ImGui::GetContentRegionAvail();
						ImGui::GetForegroundDrawList()->AddRect(availableSpace.GetTL() + ImVec2(8, 8), availableSpace.GetBR() - ImVec2(8, 8), IM_COL32(255, 50, 50, 255));

						ImVec2 viewCenter = availableSpace.GetCenter();
						// Depending on the viewports flag, the XY is either absolute or relative to the oF window.
						if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());
						ofPushStyle();
						ofSetRectMode(OF_RECTMODE_CENTER);
						ofSetColor(255, 0, 0, 2);
						ofNoFill();

						ofDrawRectangle(
							viewCenter.x,
							viewCenter.y,
							availableSpace.GetSize().x - 6,
							availableSpace.GetSize().y - 6
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

		//-

		//// b. Lockable settings 

		//// Fixes imgui to expected behaviour. Otherwise add in ImGui::DockSpace() [±line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
		////ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		//ImGuiDockNodeFlags flagsDock;
		//flagsDock = ImGuiDockNodeFlags_PassthruCentralNode;
		//if (Lock_DockingLayout)
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

	//----

	resetIDs(); // reset names
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::end() {

	ImGui::PopStyleVar(); // minimal size

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

	////widgets sizes
	//float _spcx;
	//float _spcy;
	//float _w100;
	//float _h100;
	//float _w99;
	//float _w50;
	//float _w33;
	//float _w25;
	//float _h;
	//ofxSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

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
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	//viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

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
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

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
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::endDocking()
{
	ImGuiIO& io = ImGui::GetIO();

	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGui::End();
	}
}

//----

// layouts presets management
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::setupLayoutPresets()
{
	params_Layouts.clear();
	for (int i = 0; i < bGuis.size(); i++) {
		params_Layouts.add(bGuis[i]);
	}

	//-

	//path_Global = "SurfingImGuiLayout/";
	//ofxSurfingHelpers::CheckFolder(path_Global);

	path_ImLayouts = "layout/ImGui/";
	ofxSurfingHelpers::CheckFolder(path_ImLayouts);

	//path_ImLayouts = ofToDataPath(path_ImLayouts, true);

	// layouts panel

	params_LayoutPanelsState.add(b0, b1, b2, b3, b4);
	params_LayoutPanelsState.add(appLayoutIndex);
	params_LayoutPanelsState.add(Lock_DockingLayout);
	params_LayoutPanelsState.add(bAutoSave_Layout);
	params_LayoutPanelsState.add(SHOW_Layouts);
	params_LayoutPanelsState.add(SHOW_LayoutsAdvanced);
	params_LayoutPanelsState.add(SHOW_Panels);

	ofAddListener(params_LayoutPanelsState.parameterChangedE(), this, &ofxSurfing_ImGui_Manager::Changed_LayoutPanels);

	//-

	//setAutoSaveSettings(true);
	setImGuiLayoutPresets(true);

	if (bAutoSaveSettings) loadGroup(params_LayoutPanelsState, path_SettingsLayout);


}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::saveAppLayout(AppLayouts mode)
{
	ini_to_save_Str = getLayoutName(mode);

	ofLogNotice(__FUNCTION__) << ini_to_save_Str;

	////TODO:
	////workaround
	////avoid empty name
	////force save
	//if (ini_to_save_Str == "")//when unknown name
	//{
	//	appLayoutIndex_PRE = -1;
	//	appLayoutIndex = 0;
	//	ini_to_save_Str = path_ImLayouts + "imgui_DEFAULT.ini";
	//	ini_to_save = ini_to_save_Str.c_str();
	//	ImGui::SaveIniSettingsToDisk(ini_to_save);
	//}

	ini_to_save = ini_to_save_Str.c_str();//flags to save on update

	//save group
	ofxSurfingHelpers::saveGroup(params_Layouts, ini_to_save_Str + ".json");
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::loadAppLayout(AppLayouts mode)
{
	ofLogNotice(__FUNCTION__) << getLayoutName(mode);

	std::string _label = APP_RELEASE_NAME; // Paletto v1.0
	_label += "       "; // spacing

	bool bEnableHardcode = false; // false makes all presets customizable!

	switch (mode)
	{
	case ofxSurfing_ImGui_Manager::APP_DEFAULT:
		if (!b0) b0 = true;
		b1 = b2 = b3 = b4 = false;
		ofSetWindowTitle(_label + " F1  " + "DEFAULT");
		ini_to_load_Str = path_ImLayouts + "imgui_DEFAULT.ini";
		ini_to_load = ini_to_load_Str.c_str();
		ofxSurfingHelpers::loadGroup(params_Layouts, ini_to_load_Str + ".json");
		//hardcoded forced
		if (bEnableHardcode) {
		}
		break;

	case ofxSurfing_ImGui_Manager::APP_PRESETS:
		if (!b1) b1 = true;
		b0 = b2 = b3 = b4 = false;
		ofSetWindowTitle(_label + " F2  " + "PRESETS");
		ini_to_load_Str = path_ImLayouts + "imgui_PRESETS.ini";
		ini_to_load = ini_to_load_Str.c_str();
		ofxSurfingHelpers::loadGroup(params_Layouts, ini_to_load_Str + ".json");
		//hardcoded forced
		if (bEnableHardcode) {
		}
		break;

	case ofxSurfing_ImGui_Manager::APP_ENGINES:
		if (!b2) b2 = true;
		b0 = b1 = b3 = b4 = false;
		ofSetWindowTitle(_label + " F3  " + "ENGINES");
		ini_to_load_Str = path_ImLayouts + "imgui_ENGINES.ini";
		ini_to_load = ini_to_load_Str.c_str();
		ofxSurfingHelpers::loadGroup(params_Layouts, ini_to_load_Str + ".json");
		//hardcoded forced
		if (bEnableHardcode) {
		}
		break;

	case ofxSurfing_ImGui_Manager::APP_MINIMAL:
		if (!b3) b3 = true;
		b0 = b1 = b2 = b4 = false;
		ofSetWindowTitle(_label + " F4  " + "MINIMAL");
		ini_to_load_Str = path_ImLayouts + "imgui_MINIMAL.ini";
		ini_to_load = ini_to_load_Str.c_str();
		ofxSurfingHelpers::loadGroup(params_Layouts, ini_to_load_Str + ".json");
		//Lock_DockingLayout = false;
		break;

	case ofxSurfing_ImGui_Manager::APP_USER:
		if (!b4) b4 = true;
		b0 = b1 = b2 = b3 = false;
		ofSetWindowTitle(_label + " F5  " + "USER");
		ini_to_load_Str = path_ImLayouts + "imgui_USER.ini";
		ini_to_load = ini_to_load_Str.c_str();
		ofxSurfingHelpers::loadGroup(params_Layouts, ini_to_load_Str + ".json");

		//Lock_DockingLayout = false;
		break;
	}

	ofLogNotice(__FUNCTION__) << "------------------------------------";
	ofLogNotice(__FUNCTION__) << "ini_to_load    : " << ini_to_load;
	ofLogNotice(__FUNCTION__) << "ini_to_load_Str: " << ini_to_load_Str;
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::gui_LayoutsPresets()
{
	static bool auto_resize = false;
	ImGuiWindowFlags flags = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;
	flags |= ImGuiWindowFlags_NoSavedSettings;//exclude from restore layouts
	//flags |= flagsWindowsLocked;

	static float CURRENT_WINDOW_MIN_HEIGHT = 220;

	//blink save button to clarify workflow
	float a = ofxSurfingHelpers::getFadeBlink();

	//----

	// center
	//is excluded from .ini
	float xw, yw, ww, hw;
	ww = LAYOUT_WINDOW_WIDTH;
	hw = CURRENT_WINDOW_MIN_HEIGHT;
	//xw = ofGetWidth() / 2 - ww / 2;
	//yw = ofGetHeight() / 2 - hw / 2;
	ImGuiCond flag;
	if (bForceLayoutPosition) {
		////upper left
		//glm::vec2 p = rectangle_Central_MAX.getTopLeft() + glm::vec2(-1, -1);
		//center upper left
		int _pad = 10;
		int _xx = rectangle_Central_MAX.getTopLeft().x + _pad;
		int _yy = rectangle_Central_MAX.getTopLeft().y + rectangle_Central_MAX.getHeight() / 2 - hw / 2;
		glm::vec2 p = glm::vec2(_xx, _yy);

		xw = p.x;
		yw = p.y;
		flag = ImGuiCond_Always;
	}
	else {
		xw = positionGuiLayout.get().x;
		yw = positionGuiLayout.get().y;
		flag = ImGuiCond_Once;
	}

	ImGui::SetNextWindowPos(ofVec2f(xw, yw), flag);
	ImGui::SetNextWindowSize(ofVec2f(ww, hw), flag);

	//----

	//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, CURRENT_WINDOW_MIN_HEIGHT));

	beginWindow(SHOW_Layouts, flags);
	//if (ofxImGui::BeginWindow("LAYOUT PRESETS", mainSettings, flags))

	{
		//get window position for advanced layout paired position
		auto posx = ImGui::GetWindowPos().x;
		auto posy = ImGui::GetWindowPos().y;
		auto w = ImGui::GetWindowWidth();
		positionGuiLayout = glm::vec2(posx, posy);
		//positionGuiLayout = glm::vec2(posx + w, posy);
		widthGuiLayout = w;

		//--

		const int NUM_WIDGETS = APP_LAYOUTS_AMOUNT + 4;

		float _spcx = ImGui::GetStyle().ItemSpacing.x;
		float _spcy = ImGui::GetStyle().ItemSpacing.y;
		float _w100 = ImGui::GetContentRegionAvail().x;
		float _h100 = ImGui::GetContentRegionAvail().y;
		float _w99 = _w100 - _spcx;
		float _h99 = _h100 - _spcy;
		float _w50 = _w99 / 2;

		//float _h99 = _h100 - _spcy;

		// buttons size
		float _w;
		float _h;

		// responsive boxed
		float maxbox = 470;
		bool bbox = false;
		if (_w100 < maxbox) bbox = true;

		if (bbox)// squared (three full height + 2 x 1/2 height rows)
		{
			_w = _w99 / 2;
			//float _units = 4.f;
			float _units = 4.5f;
			_h = _h99 / _units - _spcy;
		}
		else// panoramic (one row)
		{
			_w = _w100 / NUM_WIDGETS - _spcx;
			_h = _h99 + _spcy / 2;
		}

		// layouts
		ofxImGuiSurfing::AddBigToggle(b0, _w, _h); ImGui::SameLine();
		ofxImGuiSurfing::AddBigToggle(b1, _w, _h); if (!bbox) ImGui::SameLine();
		ofxImGuiSurfing::AddBigToggle(b2, _w, _h); ImGui::SameLine();
		ofxImGuiSurfing::AddBigToggle(b3, _w, _h); if (!bbox) ImGui::SameLine();
		ofxImGuiSurfing::AddBigToggle(b4, _w, _h); ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.5f, 0.0f, 0.0f, a));
		ImGui::PushID("##saveLayout");
		if (ImGui::Button("SAVE", ImVec2(_w, _h)))
		{
			saveAppLayout(AppLayouts(appLayoutIndex.get()));
		}
		ImGui::PopID();
		ImGui::PopStyleColor();

		if (!bbox)// a. one row
		{
			CURRENT_WINDOW_MIN_HEIGHT = 90;
			ImGui::SameLine();
		}
		else if (bbox)// b. boxes multi row
		{
			CURRENT_WINDOW_MIN_HEIGHT = 250;
			_w = _w100;
			_h = _h / 2;
		}

		//one row
		ofxImGuiSurfing::AddBigToggle(SHOW_Panels, _w, _h);
		if (!bbox) ImGui::SameLine();
		ofxImGuiSurfing::AddBigToggle(SHOW_LayoutsAdvanced, _w, _h);
		if (!bbox) ImGui::SameLine();
		ofxImGuiSurfing::AddBigToggle(Lock_DockingLayout, _w, _h);
	}
	//ofxImGui::EndWindow(mainSettings);
	endWindow();

	//ImGui::PopStyleVar();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::Changed_LayoutPanels(ofAbstractParameter &e)
{
	std::string name = e.getName();

	ofLogNotice(__FUNCTION__) << name << " : " << e;

	//----

	if (false) {}

	else if (name == b0.getName())
	{
		if (b0) {
			b1 = b2 = b3 = b4 = false;
			appLayoutIndex = 0;
		}
		else
		{
			if (!b0 && !b1 && !b2 && !b3 && !b4) b0 = true;
		}
	}

	else if (name == b1.getName())
	{
		if (b1) {
			b0 = b2 = b3 = b4 = false;
			appLayoutIndex = 1;
		}
		else
		{
			if (!b0 && !b1 && !b2 && !b3 && !b4) b1 = true;
		}
	}

	else if (name == b2.getName())
	{
		if (b2) {
			b0 = b1 = b3 = b4 = false;
			appLayoutIndex = 2;
		}
		else
		{
			if (!b0 && !b1 && !b2 && !b3 && !b4) b2 = true;
		}
	}

	else if (name == b3.getName())
	{
		if (b3) {
			b0 = b1 = b2 = b4 = false;
			appLayoutIndex = 3;
		}
		else
		{
			if (!b0 && !b1 && !b2 && !b3 && !b4) b3 = true;
		}
	}

	else if (name == b4.getName())
	{
		if (b4) {
			b0 = b1 = b2 = b3 = false;
			appLayoutIndex = 4;
		}
		else
		{
			if (!b0 && !b1 && !b2 && !b3 && !b4) b4 = true;
		}
	}

	//-

	// layout
	else if (name == SHOW_Layouts.getName())
	{
		// workflow
		if (!SHOW_Layouts)
		{
			SHOW_LayoutsAdvanced = false;
		}
	}

	//-

	// layout
	else if (name == Lock_DockingLayout.getName())
	{
		if (!Lock_DockingLayout)
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

	//// layout
	//else if (name == bResponsive_Panels.getName())
	//{
	//	if (bResponsive_Panels)
	//	{
	//		bFitLayout = false;
	//	}
	//}

	// layout modes
	else if (name == appLayoutIndex.getName())
	{
		appLayoutIndex = ofClamp(appLayoutIndex.get(), appLayoutIndex.getMin(), appLayoutIndex.getMax());

		if (appLayoutIndex != appLayoutIndex_PRE /*&& appLayoutIndex_PRE != -1*/) //changed
		{
			ofLogNotice(__FUNCTION__) << appLayoutIndex;

			// 1. autosave

			if (bAutoSave_Layout)
			{
				// workaround:
				// must save here bc usually we use the fallged on update save...
				// only once per cycle allowed this way.
				//force to ensure save bc update chain load and save below
				//saveAppLayout(AppLayouts(appLayoutIndex_PRE));
				std::string __ini_to_save_Str = getLayoutName(AppLayouts(appLayoutIndex_PRE));
				const char* __ini_to_save = NULL;
				__ini_to_save = __ini_to_save_Str.c_str();//flags to save on update
				ImGui::SaveIniSettingsToDisk(__ini_to_save);
				ofxSurfingHelpers::saveGroup(params_LayoutPanelsState, __ini_to_save_Str + ".json");
				//if (ini_to_save)
				//{
				//	ImGui::SaveIniSettingsToDisk(ini_to_save);
				//	ini_to_save = NULL;
				//}
			}

			appLayoutIndex_PRE = appLayoutIndex;

			//loadAppLayout(AppLayouts(appLayoutIndex.get()));
		//}

			// 2. load layout
			loadAppLayout(AppLayouts(appLayoutIndex.get()));
		}
	}

	//// layout
	//else if (name == bFitLayout.getName())
	//{
	//	if (bFitLayout)
	//	{
	//		bResponsive_Panels = false;
	//	}
	//}

	//--
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::gui_LayoutsAdvanced()
{
	static bool auto_resize = true;

	ImGuiWindowFlags flags = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;
	flags |= ImGuiWindowFlags_NoSavedSettings; // exclude from restore layouts
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
	//_flagc = ImGuiCond_Appearing;
	//ImGui::SetNextWindowPos(ofVec2f(xw + ww + 2, yw), _flagc);
	_flagc = ImGuiCond_Always;

	int _pad = 10;
	ImGui::SetNextWindowPos(ofVec2f(positionGuiLayout.get().x + widthGuiLayout + _pad, positionGuiLayout.get().y), _flagc);
	//ImGui::SetNextWindowSize(ofVec2f(ww, hw), _flagc);

	//----

	//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(max, CURRENT_WINDOW_MIN_HEIGHT));

	beginWindow(SHOW_LayoutsAdvanced, flags);
	//if (ofxImGui::BeginWindow("LAYOUTS", mainSettings, flags))

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
		int i = 0;

		//----

		ofxImGuiSurfing::AddBigToggle(SHOW_Panels, _w100, _h);
		ofxImGuiSurfing::AddBigToggle(bAutoSave_Layout, _w100, _h);
		ofxImGuiSurfing::AddBigToggle(bForceLayoutPosition, _w100, _h);
		ofxImGuiSurfing::AddBigToggle(Lock_DockingLayout, _w100, _h);

		//----

		// label current layout
		//std::string str;
		//switch (appLayoutIndex)
		//{
		//case APP_DEFAULT: str = "DEFAULT"; break;
		//case APP_PRESETS: str = "PRESETS"; break;
		//case APP_ENGINES: str = "ENGINES"; break;
		//case APP_MINIMAL: str = "MINIMAL"; break;
		//case APP_USER: str = "USER"; break;
		//}
		//ImGui::Text(str.c_str());

		//ImGui::Dummy(ImVec2(0.0f, 2.0f));

		if (ImGui::CollapsingHeader("TOOLS", ImGuiWindowFlags_None))
		{
			ImVec2 bb{ (bMin ? _w100 : _w50), _h };

			ImGui::Text("Default");
			if (!bMin)
			{
				ImGui::PushID(i++);
				if (ImGui::Button("Load", bb))
				{
					appLayoutIndex = APP_DEFAULT;
				}
				ImGui::SameLine();
				ImGui::PopID();
			}

			ImGui::PushID(i++);
			if (ImGui::Button("Save", bb))
			{
				ini_to_save_Str = path_ImLayouts + "imgui_DEFAULT.ini";
				ini_to_save = ini_to_save_Str.c_str();
			}
			ImGui::PopID();

			ImGui::Text("Presets");
			if (!bMin)
			{
				ImGui::PushID(i++);
				if (ImGui::Button("Load", bb))
				{
					appLayoutIndex = APP_PRESETS;
				}
				ImGui::SameLine();
				ImGui::PopID();
			}

			ImGui::PushID(i++);
			if (ImGui::Button("Save", bb))
			{
				ini_to_save_Str = path_ImLayouts + "imgui_PRESETS.ini";
				ini_to_save = ini_to_save_Str.c_str();
			}
			ImGui::PopID();

			ImGui::Text("Engines");
			if (!bMin)
			{
				ImGui::PushID(i++);
				if (ImGui::Button("Load", bb))
				{
					appLayoutIndex = APP_ENGINES;
				}
				ImGui::SameLine();
				ImGui::PopID();
			}

			ImGui::PushID(i++);
			if (ImGui::Button("Save", bb))
			{
				ini_to_save_Str = path_ImLayouts + "imgui_ENGINES.ini";
				ini_to_save = ini_to_save_Str.c_str();
			}
			ImGui::PopID();

			ImGui::Text("Minimal");
			if (!bMin)
			{
				ImGui::PushID(i++);
				if (ImGui::Button("Load", bb))
				{
					appLayoutIndex = APP_MINIMAL;
				}
				ImGui::SameLine();
				ImGui::PopID();
			}

			ImGui::PushID(i++);
			if (ImGui::Button("Save", bb))
			{
				ini_to_save_Str = path_ImLayouts + "imgui_MINIMAL.ini";
				ini_to_save = ini_to_save_Str.c_str();
			}
			ImGui::PopID();

			ImGui::Text("User");
			if (!bMin)
			{
				ImGui::PushID(i++);
				if (ImGui::Button("Load", bb))
				{
					appLayoutIndex = APP_USER;
				}
				ImGui::SameLine();
				ImGui::PopID();
			}

			ImGui::PushID(i++);
			if (ImGui::Button("Save", bb))
			{
				ini_to_save_Str = path_ImLayouts + "imgui_USER.ini";
				ini_to_save = ini_to_save_Str.c_str();
			}
			ImGui::PopID();


			ImGui::Dummy(ImVec2(0.0f, 2.0f));

			if (ImGui::Button("RESET", ImVec2(_w100, _h)))
			{

				for (int i = 0; i < bGuis.size(); i++) {
					bGuis[i].set(true);
				}

				////all params to false
				//SHOW_Palette = false;
				//SHOW_Panels = false;
				//SHOW_PanelEngines = false;
				//SHOW_Theory = false;
				//SHOW_Range = false;
				//SHOW_ColourLovers = false;
				//SHOW_Quantizer = false;
				//SHOW_Presets = false;
				//SHOW_Kit = false;
				//SHOW_Editor = false;
				//SHOW_Picker = false;
				//SHOW_Library = false;
				//SHOW_Demos = false;
				//gradientEngine.SHOW_CurveEditor = false;
				//SHOW_MINI_Preview = false;
				//SHOW_LinkExport = false;
				//SHOW_Advanced = false;
				//SHOW_MenuBar = false;

				Lock_DockingLayout = false;

				saveAppLayout(AppLayouts(appLayoutIndex.get()));
			}
		}

		//--


		if (ImGui::CollapsingHeader("EXTRA", ImGuiWindowFlags_None))
		{
			//ofxImGuiSurfing::AddBigToggle(SHOW_Engines, _w100, _h);
			//ofxImGuiSurfing::AddBigToggle(SHOW_MenuBar, _w100, _h);
			//ofxImGuiSurfing::AddBigToggle(SHOW_Advanced, _w100, _h);
			////ofxImGuiSurfing::AddBigToggle(SHOW_LayoutsAdvanced, _w100, _h);

			ImGui::Checkbox("Auto-Resize", &auto_resize);
		}
	}

	//ofxImGui::EndWindow(mainSettings);
	endWindow();

	//ImGui::PopStyleVar();
}

//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::gui_Panels()
{
	static bool auto_resize = false;

	ImGuiWindowFlags flags = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;
	flags |= flagsWindowsLocked;

	//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(625, PANEL_WIDGETS_HEIGHT));

	//----

	beginWindow(SHOW_Panels, flags);
	//if (ofxImGui::BeginWindow("PANELS", mainSettings, flags))

	{
		int NUM_WIDGETS = 5;//expected num widgets

//#ifndef USE_MINIMAL_GUI
//		NUM_WIDGETS++;//extra advanced toggle
//#endif

		float _spcx = ImGui::GetStyle().ItemSpacing.x;
		float _spcy = ImGui::GetStyle().ItemSpacing.y;
		float _h100 = ImGui::GetContentRegionAvail().y;
		float _w100 = ImGui::GetContentRegionAvail().x;
		float _w99 = _w100;// -_spcx;

		float _h = _h100 / 2 - _spcy;
		//float _h = BUTTON_BIG_HEIGHT;

		//layout
		float maxw = 850;
		//bool bMini = _w100 < maxw;
		bool bMini = true;

		float _w;
		if (!bMini)_w = _w99 / NUM_WIDGETS - _spcx;
		else _w = _w99 / 5 - _spcx;

		for (int i = 0; i < bGuis.size(); i++) {
			ofxImGuiSurfing::AddBigToggle(bGuis[i], _w, _h); ImGui::SameLine();
		}

	}
	{
		//		int NUM_WIDGETS = 11;//expected num widgets
		//
		//#ifndef USE_MINIMAL_GUI
		//		NUM_WIDGETS++;//extra advanced toggle
		//#endif
		//		float _spcx = ImGui::GetStyle().ItemSpacing.x;
		//		float _spcy = ImGui::GetStyle().ItemSpacing.y;
		//		float _h100 = ImGui::GetContentRegionAvail().y;
		//		float _w100 = ImGui::GetContentRegionAvail().x;
		//		float _w99 = _w100;// -_spcx;
		//
		//		float _h = _h100 / 2 - _spcy;
		//		//float _h = BUTTON_BIG_HEIGHT;
		//
		//		//layout
		//		float maxw = 850;
		//		//bool bMini = _w100 < maxw;
		//		bool bMini = true;
		//
		//		float _w;
		//		if (!bMini)_w = _w99 / NUM_WIDGETS - _spcx;
		//		else _w = _w99 / 6 - _spcx;

		//		ofxImGuiSurfing::AddBigToggle(SHOW_Palette, _w, _h); ImGui::SameLine();
		//		ofxImGuiSurfing::AddBigToggle(SHOW_Presets, _w, _h); ImGui::SameLine();
		//		ofxImGuiSurfing::AddBigToggle(SHOW_Kit, _w, _h); ImGui::SameLine();
		//		ofxImGuiSurfing::AddBigToggle(SHOW_Editor, _w, _h); ImGui::SameLine();
		//		ofxImGuiSurfing::AddBigToggle(SHOW_Picker, _w, _h); ImGui::SameLine();
		//
		//#ifdef MODE_BACKGROUND
		//		ofxImGuiSurfing::AddBigToggle(SHOW_BackGround, _w, _h);
		//		ImGui::SameLine();
		//#endif
		//		ofxImGuiSurfing::AddBigToggle(SHOW_Library, _w, _h);
		//		if (!bMini) ImGui::SameLine();//split if mini
		//
		//		//ImGui::Separator();
		//
		//		ofxImGuiSurfing::AddBigToggle(SHOW_PanelEngines, _w, _h); ImGui::SameLine();
		//		ofxImGuiSurfing::AddBigToggle(SHOW_Gradient, _w, _h); ImGui::SameLine();
		//		//ofxImGuiSurfing::AddBigToggle(gradientEngine.SHOW_CurveEditor, _w, _h); ImGui::SameLine();
		//		//ofxImGuiSurfing::AddBigToggle(SHOW_MINI_Preview, _w, _h);//ImGui::SameLine();

				//-

		//		// link blink
		//		float a;
		//		bool b;
		//#ifdef LINK_TCP_MASTER_CLIENT_KU
		//		b = TCP_Sender.connected() && TCP_Sender.enabled() && bExportByTCP;
		//#endif
		//#ifdef LINK_TCP_MASTER_CLIENT_OF
		//		b = TCP_Sender.isConnected() && bExportByTCP && (TCP_Sender.getNumClients() > 0);
		//#endif
		//		if (b) a = ofxSurfingHelpers::getFadeBlink();
		//		else a = 1.0f;
		//		if (b) ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)ImColor::HSV(0.5f, 0.0f, 1.0f, a));
		//
		//		//ofxImGuiSurfing::AddBigToggle(SHOW_LinkExport, _w, _h, false); ImGui::SameLine();
		//
		//		if (b) ImGui::PopStyleColor();

				//-

				//ofxImGuiSurfing::AddBigToggle(SHOW_Demos, _w, _h); ImGui::SameLine();
				//ofxImGuiSurfing::AddBigToggle(SHOW_Layouts, _w, _h);

		//#ifndef USE_MINIMAL_GUI
		//		//ImGui::SameLine();
		//		//ofxImGuiSurfing::AddBigToggle(SHOW_Advanced, _w, _h);
		//#endif
	}

	//ofxImGui::EndWindow(mainSettings);
	endWindow();

	//ImGui::PopStyleVar();
}


//--

/*
// layouts
//--------------------------------------------------------------
void ofxSurfing_ImGui_Manager::keyPressed(ofKeyEventArgs &eventArgs)
{
	const int key = eventArgs.key;

	// modifiers
	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

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
		case OF_KEY_F1: appLayoutIndex = APP_DEFAULT; break;
		case OF_KEY_F2: appLayoutIndex = APP_PRESETS; break;
		case OF_KEY_F3: appLayoutIndex = APP_ENGINES; break;
		case OF_KEY_F4: appLayoutIndex = APP_MINIMAL; break;
		case OF_KEY_F5: appLayoutIndex = APP_USER; break;
		default: break;
		}

		if (key == OF_KEY_F9)//layouts
		{
			SHOW_Layouts = !SHOW_Layouts;
		}

		if (key == OF_KEY_F10)//panels
		{
			SHOW_Panels = !SHOW_Panels;
		}
		else if (key == OF_KEY_F11)//
		{
			SHOW_Advanced = !SHOW_Advanced;
		}

		// unlock dock Ctrl+Alt+a
		else if ((key == 'L' || key == 'l')) //&& mod_CONTROL && !mod_ALT)
		{
			Lock_DockingLayout = !Lock_DockingLayout;
		}


		// layout modes

		else if (key == OF_KEY_TAB && !mod_CONTROL)
		{
			if (appLayoutIndex > appLayoutIndex.getMin()) appLayoutIndex++;
			else if (appLayoutIndex == appLayoutIndex.getMin()) appLayoutIndex = appLayoutIndex.getMax();

			//if (appLayoutIndex < 3) loadAppLayout(AppLayouts(appLayoutIndex + 1));
			//else if (appLayoutIndex == 3) loadAppLayout(AppLayouts(0));
		}
	}

}
*/