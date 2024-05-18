#include "SurfingGuiManager.h"

int SurfingGuiManager::instanceCount = 0;

//--------------------------------------------------------------
SurfingGuiManager::SurfingGuiManager() {
	//TODO:
	// Instances and master/salve context management
	ofLogWarning("ofxSurfingImGui") << "Instance: #" << instanceCount;
	bool b = (this->getGuiPtr()->isMaster());
	ofLogWarning("ofxSurfingImGui") << "Context:  " << (b ? "MASTER" : "SLAVE");
	if (instanceCount == 0) bIsMasterInstance = true;
	instanceNumber = instanceCount;
	instanceCount++;

	//--

	//TODO:
	// Simplify namespace's!
	namespace ofxSurfingImGui = ofxImGuiSurfing;

	// Default path that will be used appended,
	// or alone if setName(.. is not called!

	//----

	// ofApp / core callbacks
#ifdef SURFING_IMGUI__CREATE_EXIT_LISTENER
	//TODO:
	// Fix exit exceptions on RF..
	int minValue = std::numeric_limits<int>::min();
	ofAddListener(ofEvents().exit, this, &SurfingGuiManager::exit, minValue);
#endif

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES_USING_LISTENER
	autoSaveListener = params_AppSettings.parameterChangedE().newListener([&](ofAbstractParameter &) {
		this->saveSettings();
	});
#endif

	//--

	ofAddListener(ofEvents().keyPressed, this, &SurfingGuiManager::keyPressed);
	ofAddListener(ofEvents().keyReleased, this, &SurfingGuiManager::keyReleased);

	// Auto call draw. Only to draw help boxes / OF native info. ?
	ofAddListener(ofEvents().update, this, &SurfingGuiManager::update, OF_EVENT_ORDER_AFTER_APP);
	//ofAddListener(ofEvents().update, this, &SurfingGuiManager::update, OF_EVENT_ORDER_BEFORE_APP);

	ofAddListener(ofEvents().draw, this, &SurfingGuiManager::draw, OF_EVENT_ORDER_AFTER_APP);

	//----

	// Callbacks

	ofAddListener(params_AppSettings.parameterChangedE(), this, &SurfingGuiManager::Changed_Params);

	ofAddListener(params_WindowsPanels.parameterChangedE(), this, &SurfingGuiManager::Changed_WindowsPanels);
	ofAddListener(params_WindowsPanelsExtra.parameterChangedE(), this, &SurfingGuiManager::Changed_WindowsPanels);

	params_WindowsPanelsExtra.add(bGui_ShowWindowsGlobal);

	//--

	setupParams();
}

//--------------------------------------------------------------
SurfingGuiManager::~SurfingGuiManager() {
	ofLogNotice("ofxSurfingImGui") << "Destructor! Instance #" << instanceNumber;
	ofLogNotice("ofxSurfingImGui") << "Name: " << nameLabel;

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_EXIT
	// Force saving but would expect to be already called
	// by a listener if it's defined SURFING_IMGUI__CREATE_EXIT_LISTENER
	if (!bDoneExit) {
		exit();

		ofLogWarning("ofxSurfingImGui") << "exit() was not called yet as expected.";
		ofLogWarning("ofxSurfingImGui") << "Now forcing exit() here in destructor!";
	} else {
		ofLogWarning("ofxSurfingImGui") << "exit() was already called before as expected.";
		ofLogWarning("ofxSurfingImGui") << "It was already done!";
		ofLogWarning("ofxSurfingImGui") << "So we successfully omitted calling exit() herre in destructor.";
	}
#endif

#ifdef SURFING_IMGUI__CREATE_EXIT_LISTENER
	ofRemoveListener(ofEvents().exit, this, &SurfingGuiManager::exit);
#endif

	//TODO:
	// Delete font pointers
	//delete customFont;
	//for (size_t i = 0; i < customFonts.size(); i++) delete customFonts[i];//crash
}

#ifdef SURFING_IMGUI__CREATE_EXIT_LISTENER
//--------------------------------------------------------------
void SurfingGuiManager::exit(ofEventArgs & e) {
	ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << " > exit(ofEventArgs& e)";
	ofLogNotice("ofxSurfingImGui") << "Called by ofEvents().exit with maximum priority! Now calling exit().";
	ofLogNotice("ofxSurfingImGui") << "Then we avoid that is been called by the object destructor.";

	exit();
}
#endif

//--------------------------------------------------------------
void SurfingGuiManager::exit() {
	if (bDoneExit) {
		ofLogWarning("ofxSurfingImGui") << "Skipped exit() bc it seems done already previously!";
		return;
	}

	ofLogNotice("ofxSurfingImGui") << "exit()";

	ofRemoveListener(ofEvents().keyPressed, this, &SurfingGuiManager::keyPressed);
	ofRemoveListener(ofEvents().keyReleased, this, &SurfingGuiManager::keyReleased);

	ofRemoveListener(ofEvents().update, this, &SurfingGuiManager::draw, OF_EVENT_ORDER_BEFORE_APP);
	ofRemoveListener(ofEvents().draw, this, &SurfingGuiManager::draw, OF_EVENT_ORDER_BEFORE_APP);

	ofRemoveListener(params_AppSettings.parameterChangedE(), this, &SurfingGuiManager::Changed_Params);

	ofRemoveListener(params_LayoutPresetsStates.parameterChangedE(), this, &SurfingGuiManager::Changed_Params);

	ofRemoveListener(params_WindowsPanels.parameterChangedE(), this, &SurfingGuiManager::Changed_WindowsPanels);
	ofRemoveListener(params_WindowsPanelsExtra.parameterChangedE(), this, &SurfingGuiManager::Changed_WindowsPanels);

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_EXIT
	ofLogNotice("ofxSurfingImGui") << "Listeners has been removed. Now we are going to save the session settings.";
	this->saveSettingsInternal();
#endif

	bDoneExit = true;
}

//--

//--------------------------------------------------------------
void SurfingGuiManager::setupParams() {
	ofLogNotice("ofxSurfingImGui") << "setupParams()";

	//--

	// Links

#ifdef SURFING_IMGUI__USE_GLOBAL_SCALE
	scaleGlobalManager.setUiPtr(this);

	//scaleGlobalManager.globalScale.makeReferenceTo(globalScale);//breaks ref
	globalScale.makeReferenceTo(scaleGlobalManager.globalScale);
#endif

	//--

	// Most of these below params are handled into file settings!

	params_Internal.add(bGui);

	params_Internal.add(bAutoResize);
	params_Internal.add(bExtra);
	params_Internal.add(bMinimize);
	params_Internal.add(bAdvanced);
	params_Internal.add(bGui_GameMode);
	params_Internal.add(bSolo_GameMode);
	params_Internal.add(bKeys);
	params_Internal.add(bDebug);
	params_Internal.add(bGui_TopMenuBar);

	params_InternalConfig.add(bMouseWheel);
	params_InternalConfig.add(bMouseWheelFlip);
	params_InternalConfig.add(bThemeUIAlt);
	params_InternalConfig.add(fontIndex);
	params_InternalConfig.add(globalScale);
	params_InternalConfig.add(bGlobalScaleWheel);
	params_Internal.add(params_InternalConfig);

	params_Advanced.add(params_Internal);

	//--

	// Help

	//params_HelpInternal.add(bHelpInternal, helpInternal.fontIndex);
	//params_HelpApp.add(bHelp, helpApp.fontIndex);//this overwrites forced manual settings
	params_HelpInternal.add(bHelpInternal);
	params_HelpApp.add(bHelp);
	params_Help.add(params_HelpInternal);
	params_Help.add(params_HelpApp);
	params_Modules.add(params_Help);

	//--

	// Modules

	//--

	// Log

	params_ModulesWindows.add(bLog);
	params_ModulesWindows.add(bLogKeys);

	params_Modules.add(log.params);

	//--

	// Notifier

	params_ModulesWindows.add(bNotifier);
#ifdef SURFING_IMGUI__USE_NOTIFIER
	params_ModulesWindows.add(notifier.bGui_Editor);
	#ifndef SURFING_IMGUI__NOTIFIER_SETTINGS_STANDALONE
	params_Modules.add(notifier.params);
	#endif
#endif

	//--

	// Profiler Debugger

	params_ModulesWindows.add(bDebugDebuggerImGui);
#ifdef SURFING_IMGUI__USE_PROFILE_DEBUGGER
	debugger.bGui.makeReferenceTo(bDebugDebuggerImGui);
	params_Modules.add(debugger.params);
#endif

	params_ModulesWindows.add(params_Modules);

	params_Advanced.add(params_ModulesWindows);

	//--

	// Windows

	//TODO:
	params_Windows.add(bReset);
	params_Windows.add(bReset_Window);
	params_Windows.add(bLockMove);
	params_Windows.add(bNoScroll);

	params_Windows.add(bSolo); //used on layout presets engine
	//params_Windows.add(bMinimize_Presets);//need to rename

	//params_Windows.add(bLinkGlobal);
	//params_Windows.add(bLinked);
	//params_Windows.add(windowsOrganizer.pad);
	//params_Windows.add(bLandscape);//TODO:
	params_Advanced.add(params_Windows);

	//--

	//TODO: For functions not implemented yet.

	// Exclude from settings
	bLockMove.setSerializable(false);
	bNoScroll.setSerializable(false);
	bReset.setSerializable(false);
	bReset_Window.setSerializable(false);
}

//--------------------------------------------------------------
void SurfingGuiManager::setup(ofxImGuiSurfing::SurfingGuiMode mode) {
	if (bDoneSetup) {
		ofLogWarning("ofxSurfingImGui") << "setup(ofxImGuiSurfing::SurfingGuiMode mode)";
		ofLogWarning("ofxSurfingImGui") << "Setup was already done previously.";
		ofLogWarning("ofxSurfingImGui") << "Skipping this setup call!";
		//TODO
		return;
	}

	//--

	surfingImGuiMode = mode;
	ofLogWarning("ofxSurfingImGui") << "surfingImGuiMode: " << surfingImGuiMode;

	switch (surfingImGuiMode) {
	case ofxImGuiSurfing::IM_GUI_MODE_UNKNOWN:
		// Nothing to custom setup
		break;

		//--

	case ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED:
		//setImGuiAutodraw(true);
		// This instantiates and configures ofxImGui inside the class object.
		setupInitiate();
		break;

		//--

	case ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING:
		numPresetsDefault = SURFING_IMGUI__DEFAULT_AMOUNT_PRESETS;
		setupDockingWithLayoutPresetsEngine();
		setupInitiate();
		break;

		//--

	case ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING_RAW:
		setupDockingRaw();
		setupInitiate();
		break;

		//--

	case ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING_RAW_AUTOHANDLER:
		setupDockingRaw();
		setDockingAutohandlerMode(true);
		setupInitiate();
		break;

		//--

	case ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_SINGLE:

		//setImGuiAutodraw(true);
		// This instantiates and configures ofxImGui inside the class object.
		setupInitiate();
		break;

		//--

		//	//TODO:
		//case ofxImGuiSurfing::IM_GUI_MODE_SPECIAL_WINDOWS:
		//	setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
		//	setup();
		//	break;

		//--

		//TODO: Should remove these below modes?

		//TODO:
	case ofxImGuiSurfing::IM_GUI_MODE_REFERENCED:
		break;

		//--

		// ui.Begin(); it's bypassed internally then can remain uncommented.
	case ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED:
		break;
	}

	//--

	// Clear

	params_Layouts.clear();
	params_LayoutsExtra.clear();
	params_LayoutsVisible.clear();

	//--

	bDoneSetup = true;
}

//--------------------------------------------------------------
void SurfingGuiManager::setup() // We will use the most common mode, to avoid to have to require any argument.
{
	ofLogNotice("ofxSurfingImGui") << "setup()";

	setup(IM_GUI_MODE_INSTANTIATED);
}

//--------------------------------------------------------------
void SurfingGuiManager::setupDockingWithLayoutPresetsEngine() {
	ofLogNotice("ofxSurfingImGui") << "setupDockingWithLayoutPresetsEngine()";

	surfingImGuiMode = ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING;

	setImGuiDockingWithLayoutPresetsEngine(true);
	setImGuiDockingModeCentered(true);
}

//--------------------------------------------------------------
void SurfingGuiManager::setupDockingRaw() {
	ofLogNotice("ofxSurfingImGui") << "setupDockingRaw()";

	surfingImGuiMode = ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING_RAW;

	setImGuiDockingModeCentered(true);
}

//--

//--------------------------------------------------------------
void SurfingGuiManager::setupInitiate() {
	ofLogNotice("ofxSurfingImGui") << "setupInitiate()";

	// For using internal instantiated GUI.
	// Called by all modes except when using the external scope modes aka not instantiated.
	// In that case we will only use the widgets helpers into a parent/external ImGui context!
	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) {
		ofLogWarning("ofxSurfingImGui") << "Aborted setupIntitiate() bc surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED";
		return;
	}

	//----

	// MouseWheel link
	_ui.bMouseWheel.makeReferenceTo(bMouseWheel);
	_ui.bMouseWheelFlip.makeReferenceTo(bMouseWheelFlip);

	// Minimizes link
	bMinimize_Presets.makeReferenceTo(bMinimize);
	//bMinimize_Panels.makeReferenceTo(bMinimize);

	//----

	//TODO: should be static to share same windows between all the ofxImGui instances
	// Avoid multiple windows with same name with multi instances..

#if 0
	// Use first letter only to allow multiple instances full independent
	bGui_Aligners.setName("ALIGNERS " + ofToString(nameLabel[0]));
	bGui_Organizer.setName("ORGANIZER " + ofToString(nameLabel[0]));
	bGui_SpecialWindows.setName("WINDOWS " + ofToString(nameLabel[0]));
#else
	//TODO: short names but could spread many windows when multi instances
	bGui_Aligners.setName("ALIGNERS");
	bGui_Organizer.setName("ORGANIZER");
	bGui_SpecialWindows.setName("WINDOWS");
#endif

	//--

	// WindowsOrganizer
	setupInitiateWindowsOrganizer();

	//--

	//TODO:
	// When using docking/presets mode
	// we force enable special windows by default
	if (surfingImGuiMode == IM_GUI_MODE_INSTANTIATED_DOCKING) {
		this->setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

		// Add LINK to extra params
		// that allows that each presets could have his own link state enabled or disabled.
		// to allow linking or floating windows.
		this->addExtraParamToLayoutPresets(bLinked);
	}

	//TODO:
	if (surfingImGuiMode == IM_GUI_MODE_INSTANTIATED_DOCKING_RAW) {
	}

	//----

	// Main initialization for ImGui object / context!

	setupImGui();

	//----

	// Settings
	{
		// Default root path to contain all the file settings!
		//path_Global = "Gui/";

		// Layout Presets
		path_LayoutsImGui = path_Global + "Presets/";

#if 0
		// Create folders if required
		CheckFolder(path_Global);
		if (bUseLayoutPresetsManager) CheckFolder(path_LayoutsImGui);
#endif

		//--

		// Some internal settings
		path_AppSettings = path_Global + nameLabel + "_UI_Internal.json";
		//path_AppSettings = path_Global + nameLabel + "_UI_" + bGui_LayoutsPanels.getName() + ".json";
		// this allow multiple add-ons instances with non shared settings.

		// Finished prepared settings for persistent / JSON settings
		params_AppSettings.add(params_Advanced);
	}

	//----

	// Two Help Boxes
	{
		// A. Help Text Box internal

		helpInternal.bGui.makeReferenceTo(bHelpInternal); //link
		//helpInternal.setTitle(bHelpInternal.getName());
		helpInternal.setTitle("KEY COMMANDS");

		//helpInternal.setEnableHeader();

		doBuildHelpInternalInfo(false);

		//--

		// B. Help Text Box app

		helpApp.bGui.makeReferenceTo(bHelp); //link
		helpApp.setTitle(bHelp.getName());
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::setupInitiateWindowsOrganizer() {
	// MouseWheel link
	windowsOrganizer.bDebug.makeReferenceTo(bDebug);

	// Aligners toggle
	windowsOrganizer.bGui_Aligners.makeReferenceTo(bGui_Aligners);

	// Link Organizer toggle
	windowsOrganizer.bGui_Organizer.makeReferenceTo(bGui_Organizer);

	// Special Windows toggle
	windowsOrganizer.bGui_SpecialWindows.makeReferenceTo(bGui_SpecialWindows);

	// Link both link toggles, local and the one inside the organizer object
	windowsOrganizer.bLinked.makeReferenceTo(bLinked);

	windowsOrganizer.bOrientation.makeReferenceTo(bOrientation);
	windowsOrganizer.bGui_ShowWindowsGlobal.makeReferenceTo(bGui_ShowWindowsGlobal);
	windowsOrganizer.bAlignWindowsReset.makeReferenceTo(bAlignWindowsReset);
	windowsOrganizer.bAlignWindowsCascade.makeReferenceTo(bAlignWindowsCascade);

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES
	windowsOrganizer.bAutoSaveSettings.makeReferenceTo(bAutoSaveSettings);
#endif
}

//--------------------------------------------------------------
void SurfingGuiManager::setup(ofxImGui::Gui & _gui) {
	//TODO: should be tested. For using external instantiated ImGui
	ofLogNotice("ofxSurfingImGui") << (__FUNCTION__);

	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) return;

	//--

	guiPtr = &_gui;

	setupImGui();
}

//--------------------------------------------------------------
void SurfingGuiManager::doLoadPreviousFont() {
	int i = this->getFontIndex();
	if (i > 0) i--;
	this->setFontIndex(i);
}

//--------------------------------------------------------------
void SurfingGuiManager::doLoadNextFont() {
	int i = this->getFontIndex();
	if (i < this->getAmountFonts() - 1) i++;
	this->setFontIndex(i);
}

//--------------------------------------------------------------
void SurfingGuiManager::setupFontForDefaultStylesInternal(string pathFont, float sizeFont) {
	ofLogNotice("ofxSurfingImGui") << "setupFontForDefaultStylesInternal: " << pathFont << ", " << sizeFont;

	ofFile f;
	bool b = f.open(pathFont);
	if (!b) {
		ofLogError("ofxSurfingImGui") << "setupFontForDefaultStylesInternal: File not found! " << pathFont;
		return;
	}

	clearFonts();

	string pathFonts = f.getEnclosingDirectory();
	string nameFont = f.getFileName();
	setupFontDefault(pathFonts, nameFont, sizeFont);

	if (this->getAmountFonts() > 0)
		fontIndex = 0;
	else {
		fontIndex = -1;
		ofLogError("ofxSurfingImGui") << "setupFontForDefaultStylesInternal: It seems that fonts are not loaded properly!";
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::setupFonts(string pathFonts, string nameFont, float sizeFont) {
	ofLogNotice("ofxSurfingImGui") << "setupImGuiFonts() " << pathFonts << ", " << nameFont << ", " << sizeFont;

	clearFonts();
	setupFontDefault(pathFonts, nameFont, sizeFont);
}

//--------------------------------------------------------------
void SurfingGuiManager::setupFontDefault(string pathFonts, string nameFont, float sizeFont) {
	ofLogNotice("ofxSurfingImGui") << "setupFontDefault() " << pathFonts << ", " << nameFont << ", " << sizeFont;

	//TODO: pathFonts + nameFont could be merged..

	this->clearFonts();

	// We create four different sizes but for the same font type/file

	// To check if default font file exists
	ofFile fileToRead(pathFonts + nameFont);
	bool b = fileToRead.exists();

	// If font not located..
	// We can set an alternative font like a legacy font

	if (!b) {
		nameFont = OFX_IM_FONT_DEFAULT_FILE_LEGACY;
		sizeFont = OFX_IM_FONT_DEFAULT_SIZE;
	}

	// Then check if legacy font file exists

	ofFile fileToRead2(pathFonts + nameFont);
	bool b2 = fileToRead2.exists();
	if (b2) {
		namesCustomFonts.clear();
		pathsCustomFonts.clear();

		string _label;

		// Font default
		_label = "DEFAULT";
		addFontStyle(pathFonts + nameFont, sizeFont * fontsRatioDefault, _label); // queue default font too

		// Font big
		_label = "BIG";
		addFontStyle(pathFonts + nameFont, sizeFont * fontsRatioBig, _label); // queue big font too

		// Font huge
		_label = "HUGE";
		addFontStyle(pathFonts + nameFont, sizeFont * fontsRatioHuge, _label); // queue huge font too

		// Font huge xxl
		_label = "HUGE_XXL";
		addFontStyle(pathFonts + nameFont, sizeFont * fontsRatioHugeXXL, _label); // queue huge xxl font too

		//--

		// Clears mono-spaced too
		clearFontsMonospaced();
	}

	// Legacy not found neither
	else {
		ofLogError("ofxSurfingImGui") << "setupImGuiFonts() Expected file fonts not found!";
		ofLogError("ofxSurfingImGui") << "ImGui will use his own bundled default font.";
		ofLogError("ofxSurfingImGui") << "Some ofxSurfingImGui styles will be omitted.";
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::setupFontForDefaultStylesMonospaced(string pathFont, float sizeFont) {
	ofLogNotice("ofxSurfingImGui") << "setupFontForDefaultStylesMonospaced()" << pathFont << ", " << sizeFont;

	pathFontMono = pathFont;
	sizeFontMono = sizeFont;

	bSetupFontForDefaultStylesMonospacedInternal = 1;
}

//--------------------------------------------------------------
void SurfingGuiManager::setupFontForDefaultStylesMonospacedInternal(string pathFont, float sizeFont) {
	ofLogNotice("ofxSurfingImGui") << "setupFontForDefaultStylesMonospacedInternal()" << pathFont << ", " << sizeFont;

	// We create four different sizes but for the same font type/file

	// To check if default font file exists
	ofFile fileToRead(pathFont);
	bool b = fileToRead.exists();

	// If font not located..
	// We can set an alternative font like a legacy font

	if (!b) //not found
	{
		pathFont = ofToString(OFX_IM_FONT_DEFAULT_PATH_FONTS) + ofToString(OFX_IM_FONT_DEFAULT_FILE_LEGACY);
		sizeFont = OFX_IM_FONT_DEFAULT_SIZE;
	}

	// Then check if legacy font file exists

	ofFile fileToRead2(pathFont);
	bool b2 = fileToRead2.exists();
	if (b2) {
		clearFontsMonospaced();

		string _label;

		// Font default
		_label = "DEFAULT_MONO";
		addFontStyle(pathFont, sizeFont * fontsRatioDefault, _label); // queue default font too
		// Store the font index
		fontsMonospacedIndexes.push_back(customFonts.size() - 1);

		// Font big
		_label = "BIG_MONO";
		addFontStyle(pathFont, sizeFont * fontsRatioBig, _label); // queue big font too
		// Store the font index
		fontsMonospacedIndexes.push_back(customFonts.size() - 1);

		// Font huge
		_label = "HUGE_MONO";
		addFontStyle(pathFont, sizeFont * fontsRatioHuge, _label); // queue huge font too
		// Store the font index
		fontsMonospacedIndexes.push_back(customFonts.size() - 1);

		// Font huge xxl
		_label = "HUGE_XXL_MONO";
		addFontStyle(pathFont, sizeFont * fontsRatioHugeXXL, _label); // queue huge xxl font too
		// Store the font index
		fontsMonospacedIndexes.push_back(customFonts.size() - 1);

		//--

		bDoneDefinedMonospacedFonts = true;

		// Now we have 8 fonts to browse by the index!
		//fontIndex.setMax(7);
		fontIndex.setMax(customFonts.size() - 1);

		//--

		// Log

		// Prepare
		log.setCustomFonts(customFonts, namesCustomFonts);
		log.setFontMonospacedDefined();
		log.setFontIndex(OFX_IM_FONT_BIG_MONO);

		//--

#ifdef SURFING_IMGUI__USE_NOTIFIER

		// Notifier

		// Prepare
		notifier.setCustomFonts(customFonts, namesCustomFonts);
		notifier.setFontMonospacedDefined();
		notifier.setFontIndex(OFX_IM_FONT_BIG_MONO);
#endif

		//--

		//TODO:
		// Help
		if (bUseHelpApp) setEnableHelpApp();
		if (bUseHelpInternal) setEnableHelpInternal();
	}

	// Legacy not found neither
	else {
		ofLogError("ofxSurfingImGui") << "setupFontForDefaultStylesMonospacedInternal() Seems that expected file fonts not found!";
		ofLogError("ofxSurfingImGui") << "Some ofxSurfingImGui styles will be omitted.";
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::setupFontDefault() {
	ofLogNotice("ofxSurfingImGui") << "setupFontDefault()";

	// WARNING:
	// Could not crash or notify you
	// if the font files are not present!

	string _nameFont = OFX_IM_FONT_DEFAULT_FILE;
	float _sizeFont = OFX_IM_FONT_DEFAULT_SIZE_MIN;

	// Assets folder
	//string _path = "assets/fonts/";
	string _pathFonts = OFX_IM_FONT_DEFAULT_PATH_FONTS;

	setupFontDefault(_pathFonts, _nameFont, _sizeFont);
}

//--------------------------------------------------------------
void SurfingGuiManager::setupImGui() {
	ofLogNotice("ofxSurfingImGui") << "setupImGui()";

	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) return;

	//--

	ImGuiConfigFlags flags = ImGuiConfigFlags_None;

	// Hard coded settings

	// Docking
	bool bIsDocked = bDockingLayoutPresetsEngine || surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING_RAW;
	if (bIsDocked) flags += ImGuiConfigFlags_DockingEnable;

	// Viewports (floating windows out of app window)
	if (bViewport) flags += ImGuiConfigFlags_ViewportsEnable;

	//--

	// Setup ImGui with the appropriate config flags

	if (guiPtr != nullptr)
		guiPtr->setup(nullptr, bAutoDraw, flags, bRestoreIniSettings, bMouseCursorFromImGui);
	else
		gui.setup(nullptr, bAutoDraw, flags, bRestoreIniSettings, bMouseCursorFromImGui);

	//--

	// Uncomment below to perform docking with SHIFT key
	// Gives a better user experience, matter of opinion.

	if (bIsDocked) ImGui::GetIO().ConfigDockingWithShift = true;

	// Uncomment below to "force" all ImGui windows to be standalone
	//ImGui::GetIO().ConfigViewportsNoAutoMerge=true;

	if (bMouseCursorFromImGui) ofHideCursor();

	//--

	// Load Fonts

	//TODO: improve not loading more fonts than required:
	// multiple instances would use the same font files!
	//if (this->isMasterInstance()) setupFontDefault();

	setupFontDefault();

	//--

	// Assign a default font

	// To be used everywhere when is not defined.
	// (like when populating widgets without a declared window.)
	if (customFonts.size() > 0) {
		ImFont * font = customFonts[0];
		GetIO().FontDefault = font;
	}

	//--

	//TODO: Auto separate instances data folders if is not done (setName) manually!
	if (instanceCount > 1) {
		if (!bDoneCustomNameLabel) {
			if (instanceNumber != 0) {
				//path_Global = "Gui/" + path_Root + SURFING_IMGUI__DEFAULT_PATH_GLOBAL + ofToString("/");
#if 1
				this->setName(nameLabel + "_" + ofToString(instanceNumber));
#else
				string s = path_Global;
				s += ofToString(SURFING_IMGUI__DEFAULT_PATH_GLOBAL) + "_" + ofToString(instanceNumber);
				this->setName(s);
#endif
			}
		}
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::setupImGuiTheme() {
	ofLogNotice("ofxSurfingImGui") << "setupImGuiTheme()";

	//--

	// Theme
	// Colors and widgets/spacing sizes

	//// A. Hardcoded
	//ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();

	//TODO:
	// B. Loading a file
	string pNight = SURFING_IMGUI__THEME_NAME_NIGHT;
	string pDay = SURFING_IMGUI__THEME_NAME_DAY;
	bool bLoaded = false;

	//TODO: Why do not works?
	// fails when including "SurfingThemeEditor.h" into GuiManager.h.
	//if (ofxImGuiSurfing::SurfingThemes::themeStyle == THEME_NIGHT)
	//	bLoaded = ofxImGuiSurfing::SurfingThemes::loadThemeFileByName(pNight);
	//else if (ofxImGuiSurfing::SurfingThemes::themeStyle == THEME_DAY)
	//	bLoaded = ofxImGuiSurfing::SurfingThemes::loadThemeFileByName(pDay);

	string name;
	if (bThemeUIAlt)
		name = pDay;
	else
		name = pNight;
	string pathThemes = path_Global + "themes/";
	//string pathThemes = "Gui/themes/";
	string pathTheme = pathThemes + name;
	string p = ofToDataPath(pathTheme);
	ofLogNotice("ofxSurfingImGui::loadThemeFileByName") << "Load from " << p;
	ImGui::LoadStyleFrom(p.c_str());
	ofFile f;
	bLoaded = f.doesFileExist(p);

	// If theme files are not found, then it will load a hardcoded theme!
	if (!bLoaded) {
		if (!bThemeUIAlt)
			ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing(bEnableLayout, bEnableColors); //dark
		else
			ofxImGuiSurfing::ImGui_ThemeDearImGuiLight(); //light
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::resetUISettings() {
	ofLogNotice("ofxSurfingImGui") << "resetUISettings()";

	//TODO: should disable ini handling on imgui to disable saving on app exit!
	//then on the next app startup windows
	//will be positioned as default locations and stored states forbidden.
	{
		ImGuiIO & io = ImGui::GetIO();
		io.IniFilename = NULL;

		bFlagResetUIProgramed = true;
		// to hide some gui stuff that will not operate well
		// since now bc imgui.ini handling is disabled.
	}

	string s = "Reset UI";
	this->AddToLog(s, OF_LOG_WARNING);

	// bin/imgui.ini
	{
		filesystem::path p = ofToDataPath("../imgui.ini");
		//filesystem::path p = ofToDataPath("../imgui.ini");

		ofFile f(p);
		if (f.exists()) {
			f.remove();
			s = "Removed file " + ofToDataPath(p);
			AddToLog(s, OF_LOG_WARNING);
		} else {
			s = "File " + ofToDataPath(p) + " not found.";
			AddToLog(s, OF_LOG_ERROR);
		}
	}

	// folder
	{
		filesystem::path p = this->getPathRoot();
		// filesystem::path p = this->getPathGlobal();

		ofDirectory d(ofToDataPath(p));
		if (d.exists()) {
			d.remove(true);
			s = "Removed folder " + ofToDataPath(p);
			AddToLog(s, OF_LOG_WARNING);
		} else {
			s = "Folder " + ofToDataPath(p) + " not found.";
			AddToLog(s, OF_LOG_ERROR);
		}
	}

	globalScale = 1.0f;

	windowsOrganizer.reset();
}

//--------------------------------------------------------------
void SurfingGuiManager::DrawWidgetsResetUI(bool bMenuMode) {
	// Will remove imgui.ini and json settings

	//ui->BeginBlinkText();
	if (bMenuMode) {
		if (this->MenuItemButton("Reset UI")) {
			resetUISettings();
		}
	} else {
		//if (this->AddButton("Reset UI"))
		if (ImGui::Button("Reset UI")) {
			resetUISettings();
		}
	}
	//ui->EndBlinkText();

	string s = "Remove all UI layout settings files.\n";
	s += "Restart required.";
	this->AddTooltipBlink(s);
}

//--------------------------------------------------------------
void SurfingGuiManager::startup() {
	ofLogNotice("ofxSurfingImGui") << (__FUNCTION__);

	//--

	// Theme

	this->setupImGuiTheme();

	//--

	//TODO:
	// workflow
	// Force enable organizer by default.
	// no need to call manually.
	this->setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

	//--

	// Finally the last initialization process step

	if (bDockingLayoutPresetsEngine) {
		// Default Layout with 4 presets.
		this->setupLayout(SURFING_IMGUI__DEFAULT_AMOUNT_PRESETS);

		//--

		appLayoutIndex = appLayoutIndex;

		//--

		////TODO:
		// //// workflow
		//// Force enable special windows always
		//this->setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
	}

	//----

	// Special Windows Organizer

	if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER) {
		this->initiateWindowsOrganizer();

		//--

		if (surfingImGuiMode == IM_GUI_MODE_INSTANTIATED_DOCKING) {
			//// workflow
			//windowsOrganizer.setHideWindows(true);
		}

		else if (surfingImGuiMode == IM_GUI_MODE_INSTANTIATED_DOCKING_RAW) {
			//// workflow
			//windowsOrganizer.setHideWindows(true);
		}

		// Docking mode has the GUI toggles in other panels..
		else {
			//// workflow
			//// force disable to avoid collide settings layout!
			//windowsOrganizer.bGui_Organizer = false;
		}

		//TODO: disabled bc must fix behavior if enabled
		// workflow
		//bLinked = false;
	}

	//--

	//if (surfingImGuiMode != IM_GUI_MODE_INSTANTIATED_DOCKING)
	//{
	//}

	//----

	// Modules

	//--

	// Log

	//TODO:
	// Trying to redirect all logs to the imgui log window.
	//log.setRedirectConsole();

	// Pass fonts to allow styles switching
	log.setCustomFonts(customFonts, namesCustomFonts);

	//--

	// Notifier

#ifdef SURFING_IMGUI__USE_NOTIFIER
	#ifdef SURFING_IMGUI__NOTIFIER_SETTINGS_STANDALONE
	notifier.setPath(path_Global);
	#endif
	notifier.setup();
#endif

	//----

	// Startup

	//--

	// Load App Session Settings

	// When opening for first time,
	// we set some default settings.

	// Load some internal settings
	bool bDoneCheckNoFileSettingsFound = !(this->loadSettings());

	// Will return false if settings file do not exist.
	// That happens when started for first time or after OF_APP/bin cleaning!
	if (bDoneCheckNoFileSettingsFound) {
		ofLogWarning("ofxSurfingImGui") << "No file settings found! " << path_AppSettings;
		ofLogWarning("ofxSurfingImGui") << "Probably the app is opening for the the first time.";
		ofLogWarning("ofxSurfingImGui") << "We will reset the windows layout to avoid overlap of windows.";

		// Hide all the queued special windows (if they are queued).
		this->setShowAllPanels(false);

		// Forced some default parameters
		bHelp = true;
		bHelpInternal = true;
		bMinimize = false;

		// workflow
		// Will align the windows horizontally
		bFlagDoForceStartupResetLayout = true;
	}

	//--

	//TODO
	setDefaultFont();

	//--

	bDoneStartup = true;
}

//----

// Help (Internal)

//--------------------------------------------------------------
void SurfingGuiManager::doBuildHelpInternalInfo(bool bSilent) {
	if (bSilent)
		ofLogVerbose("ofxSurfingImGui") << "doBuildHelpInternalInfo() - silent";
	else
		ofLogNotice("ofxSurfingImGui") << "doBuildHelpInternalInfo()";

	//--

	// we recreate the help info during runtime when some variable changed

	string l1 = "-----------------------------------\n"; //divider
	string l2 = "\n" + l1 + "\n"; // spaced divider
	// left indent
	//string l3 = "  ";
	string l3 = "";
	string l4 = "     "; // spacing 1st column
	string l5 = "    "; // spacing 1st column

	//--

	helpInternalText = "";

	//if(!helpInternal.bHeader) helpInternalText += "HELP INTERNAL \n\n";

	//helpInternalText += "Gui Manager \n\n";
	//helpInternalText += "Double click to EDIT/LOCK \n\n";
	//helpInternalText += l;
	//helpInternalText += "\n";

	//TODO: check mode
	//if (0) {

	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING) {
		helpInternalText += "LAYOUTS PRESETS ENGINE \n\n";
		//helpInternalText += l2;
	}

	string st = "  ";

	if (bKeys)
		helpInternalText += " " + l4 + "Keys          " + st + " ON  \n";
	else
		helpInternalText += " " + l4 + "Keys          " + st + " OFF \n";

	if (bMinimize)
		helpInternalText += string(bKeys ? "`" : " ") + l4 + "Minimize      " + st + " ON  \n";
	else
		helpInternalText += string(bKeys ? "`" : " ") + l4 + "Minimize      " + st + " OFF \n";

	if (bDebug)
		helpInternalText += string(bKeys ? "D" : " ") + l4 + "Debug         " + st + " ON  \n";
	else
		helpInternalText += string(bKeys ? "D" : " ") + l4 + "Debug         " + st + " OFF \n";

	if (bExtra)
		helpInternalText += string(bKeys ? "E" : " ") + l4 + "Extra         " + st + " ON  \n";
	else
		helpInternalText += string(bKeys ? "E" : " ") + l4 + "Extra         " + st + " OFF \n";

	if (bLog)
		helpInternalText += string(bKeys ? "L" : " ") + l4 + "Log           " + st + " ON  \n";
	else
		helpInternalText += string(bKeys ? "L" : " ") + l4 + "Log           " + st + " OFF \n";

	if (bNotifier)
		helpInternalText += string(bKeys ? "N" : " ") + l4 + "Notifier      " + st + " ON  \n";
	else
		helpInternalText += string(bKeys ? "N" : " ") + l4 + "Notifier      " + st + " OFF \n";

	if (bHelpInternal)
		helpInternalText += string(bKeys ? "I" : " ") + l4 + "Help Internal " + st + " ON  \n";
	else
		helpInternalText += string(bKeys ? "I" : " ") + l4 + "Help Internal " + st + " OFF \n";

	if (bHelp)
		helpInternalText += string(bKeys ? "H" : " ") + l4 + "Help App      " + st + " ON  \n";
	else
		helpInternalText += string(bKeys ? "H" : " ") + l4 + "Help App      " + st + " OFF \n";

	//--

	//TODO
	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING) {
		if (bDockingLayoutPresetsEngine) {
			helpInternalText += l3 + "PRESETS \n";

			helpInternalText += "F1 F2 F3 F4 \n";
			helpInternalText += "\n";

			helpInternalText += l3 + "SECTIONS \n";

			helpInternalText += "F5          LAYOUTS \n";
			helpInternalText += "F6          PANELS \n";
			if (!bMinimize) helpInternalText += "F7          MANAGER \n";
			helpInternalText += "\n";

			helpInternalText += l3 + "PANELS \n";

			helpInternalText += "Ctrl+ \n";
			helpInternalText += "F1 .. F8    Panel # \n";
			helpInternalText += "A           All  \n";
			helpInternalText += "N           None \n";

			if (bSolo)
				helpInternalText += "S           Solo          " + st + " ON  \n";
			else
				helpInternalText += "S           Solo          " + st + " OFF \n";

			//--

			if (!bMinimize) {
				helpInternalText += l2;

				helpInternalText += l3 + "HOW TO \n";

				helpInternalText += "1. Click on P1 P2 P3 P4 \nto pick a PRESET \n";
				helpInternalText += "2. Toggle the PANELS \nthat you want to be visible \nor hidden \n";
				helpInternalText += "3. Layout the PANELS around \nthe App view port \n";
				helpInternalText += "4. Pick another PRESET \n";

				helpInternalText += "\n";

				helpInternalText += l3 + "MORE TIPS \n";

				helpInternalText += "- Disable the Minimize toggle \nto show more controls. \n";
				helpInternalText += "- Explore more deep into \nLAYOUT, PANELS \nand MANAGER Windows. \n";
				helpInternalText += "- Each PRESET can be defined \nas a particular App Mode \nor an activated section. \n";
				helpInternalText += "- When no PRESET is enabled \nall PANELS will be hidden. \n";
				helpInternalText += "- On Docking Mode, \npress Shift when dragging \na window \nto lock to some viewport zone. \n";
			}
		}
	}

	//--

	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING_RAW) {
		helpInternalText += "\n\n";
		helpInternalText += l3 + "WINDOWS\n\n";

		//--

		// Special windows

		if (bKeys)
			helpInternalText += l3 + tagModKey + "+";
		else
			helpInternalText += "";
		helpInternalText += "\n\n";

		helpInternalText += "0 " + l5 + bGui_ShowWindowsGlobal.getName();
		this->alignText(bGui_ShowWindowsGlobal.getName(), helpInternalText, 15);
		helpInternalText += "  ";
		helpInternalText += string(bGui_ShowWindowsGlobal.get() ? "ON " : "OFF");
		helpInternalText += "\n\n";

		if (bGui_ShowWindowsGlobal) {
			for (size_t i = 0; i < getWindowsSpecialsSize(); i++) {
				if (bKeys)
					helpInternalText += "F" + ofToString(i + 1);
				else
					helpInternalText += "  ";
				helpInternalText += l5;
				string n = getWindowSpecialGuiToggleName(i);
				helpInternalText += n;
				this->alignText(n, helpInternalText, 15);
				helpInternalText += "  ";
				helpInternalText += getIsWindowSpecialVisible(i) ? "ON " : "OFF";
				helpInternalText += "\n";
			}
		} else {
			for (size_t i = 0; i < getWindowsSpecialsSize(); i++)
				helpInternalText += "\n";
		}

		helpInternalText += "\n";

		//--

		// Extra windows

		if (windowsExtra.size() > 0) {
			for (size_t i = 0; i < windowsExtra.size(); i++) {
				int k = getWindowsSpecialsSize() + 1 + i;
				if (bKeys)
					helpInternalText += "F" + ofToString(k);
				else
					helpInternalText += "  ";
				helpInternalText += l5;
				string n = getWindowExtraGuiToggleName(i);
				helpInternalText += n;
				this->alignText(n, helpInternalText, 15);
				helpInternalText += "  ";
				helpInternalText += getIsWindowExtraVisible(i) ? "ON " : "OFF";
				helpInternalText += "\n";
			}
		}

		helpInternalText += "\n\n";

		//--

		// Monitor mod keys

		if (bKeys) {
			if (bMod_CONTROL || bMod_COMMAND || bMod_ALT || bMod_SHIFT) {
				helpInternalText += l3 + "MOD KEYS\n";
				helpInternalText += bMod_CONTROL ? "Ctrl" : "    ";
				helpInternalText += " ";
				helpInternalText += bMod_COMMAND ? "Cmd " : "    ";
				helpInternalText += " ";
				helpInternalText += bMod_ALT ? "Alt " : "    ";
				helpInternalText += " ";
				helpInternalText += bMod_SHIFT ? "Shift" : "     ";
				helpInternalText += " ";
			} else {
				helpInternalText += "\n\n";
			}
		} else {
			helpInternalText += "\n\n";
		}
	}

	helpInternal.setText(helpInternalText, bSilent);
}

//----

// Fonts

//--------------------------------------------------------------
void SurfingGuiManager::setDefaultFontIndex(int index) {
	if (customFonts.size() == 0) {
		if (ofGetFrameNum() % (4 * 60) == 0) {
			ofLogNotice("ofxSurfingImGui") << "setDefaultFontIndex(): " << index;
			ofLogError("ofxSurfingImGui") << "customFonts.size() = 0"; //slowed timed
		}
		return;
	}

	indexCurrFont = ofClamp(index, 0, customFonts.size() - 1);
	customFont = customFonts[indexCurrFont];
}

//--------------------------------------------------------------
void SurfingGuiManager::setDefaultFont() //will apply the first added font file
{
	//ofLogNotice("ofxSurfingImGui") << "setDefaultFont()";

	setDefaultFontIndex(0);
}

//TODO: make it work on runtime..
//--------------------------------------------------------------
void SurfingGuiManager::clearFonts() {
	ofLogNotice("ofxSurfingImGui") << "clearFonts()";

	customFonts.clear();

#if 0
	//TODO: should avoid clear imgui internal fonts 
	// to avoid crashing when no font file present!
	// then imgui will load the default proggy.ttf font!
	auto& io = ImGui::GetIO();
	io.Fonts->Clear();
#endif

	//fontIndex.set(-1);
	fontIndex.setMax(-1);
	namesCustomFonts.clear();
	pathsCustomFonts.clear();
}

// API user:
// workflow during setup not in draw.

//TODO: could return an int with the current index.
// Maybe could be useful to help push / changing default font.
//--------------------------------------------------------------
bool SurfingGuiManager::addFontStyle(string path, float size, string label) {
	//TODO:
	// It could be a vector with several customFont
	// to allow hot reloading..
	// if not, last added font will be used as default.

	//ofLogNotice("ofxSurfingImGui") << "addFontStyle: " << path << " : " << size;

	auto & io = ImGui::GetIO();
	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();

	// Check if file exists
	ofFile fileToRead(path);
	bool b = fileToRead.exists();

	//TODO: to be perfect it should confirm that the font is loaded by imgui,
	//not only that the file exist..

	if (b) {
		if (label == "") label = fileToRead.getBaseName();

		ImFont * _customFont = nullptr;
		if (guiPtr != nullptr) {
			_customFont = guiPtr->addFont(path, size, nullptr, normalCharRanges);
		} else {
			_customFont = gui.addFont(path, size, nullptr, normalCharRanges);
		}

		if (_customFont != nullptr) {
			customFonts.push_back(_customFont);
			customFont = _customFont;
			indexCurrFont = customFonts.size() - 1;

			namesCustomFonts.push_back(label);
			fontIndex.setMax(namesCustomFonts.size() - 1);
			//fontIndex.setMax(ImGui::GetIO().Fonts->Fonts.Size - 1);

			pathsCustomFonts.push_back(path);
		}

		ofLogNotice("ofxSurfingImGui") << "addFontStyle() File path: " << path << " size: " << size;
	} else {
		ofLogError("ofxSurfingImGui") << "addFontStyle() File path: " << path << " not found!";
	}

	//TODO: should skip exceptions if files not found!
	if (customFont != nullptr) io.FontDefault = customFont;

	return b;
}

//// API user: workflow during setup not in draw. Not during runtime neither by the coder!
////--------------------------------------------------------------
//bool SurfingGuiManager::addFont(string path, float size)
//{
//	//TODO:
//	// should be a vector with several customFont to allow hot reloading..
//	// if not, last added font will be used
//
//	auto& io = ImGui::GetIO();
//	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();
//
//	ofFile fileToRead(path); // a file that exists
//	bool b = fileToRead.exists();
//	if (b)
//	{
//		if (guiPtr != nullptr) customFont = guiPtr->addFont(path, size, nullptr, normalCharRanges);
//		else customFont = gui.addFont(path, size, nullptr, normalCharRanges);
//
//		ofLogNotice("ofxSurfingImGui") << "addFont: " << path << " size: " << size;
//	}
//	else ofLogError("ofxSurfingImGui") << "Font not found: " << path;
//
//	if (customFont != nullptr) io.FontDefault = customFont;
//
//	return b;
//}

//--------------------------------------------------------------
bool SurfingGuiManager::LoadFontsFromFolder(string path, float size, bool bMultisize) {
	// Load dragged images folder
	ofLogNotice("ofxSurfingImGui") << "addFonts from: " << path << " size: " << size;

	ofDirectory dir;
	dir.listDir(path);
	dir.allowExt("ttf");
	dir.allowExt("TTF");
	dir.allowExt("otf");
	dir.allowExt("OTF");
	dir.sort();

	if (dir.size() == 0) {
		ofLogError("ofxSurfingImGui") << "Any fonts found on " << path;
		return false;
	}

	bool b = true;
	for (int i = 0; i < dir.size(); i++) {
		string label = dir[i].getBaseName();
		if (!bMultisize)
			b = b && addFontStyle(dir[i].getAbsolutePath(), size, label);
		else // multi size
		{
			// size -1
			label = dir[i].getBaseName() + ", " + ofToString(size - 1) + "px";
			b = b && addFontStyle(dir[i].getAbsolutePath(), size - 1, label);

			// size
			label = dir[i].getBaseName() + ", " + ofToString(size) + "px";
			b = b && addFontStyle(dir[i].getAbsolutePath(), size, label);

			// size +1
			label = dir[i].getBaseName() + ", " + ofToString(size + 1) + "px";
			b = b && addFontStyle(dir[i].getAbsolutePath(), size + 1, label);
		}
	}

	return b;
}

//--

// API: workflow during draw to switch between font styles when populating widgets.
// (Not for adding new fonts to imgui!)

//--------------------------------------------------------------
void SurfingGuiManager::PushFontStyle(int index) {
	pushStyleFont(index);
}

//--------------------------------------------------------------
void SurfingGuiManager::PopFontStyle() {
	popStyleFont();
}

//TODO: Deprecated from API
//--------------------------------------------------------------
void SurfingGuiManager::pushStyleFont(int index) {
	if (index < customFonts.size()) {
		if (customFonts[index] != nullptr) ImGui::PushFont(customFonts[index]);
	} else {
		ofLogWarning("ofxSurfingImGui") << "SurfingGuiManager::pushStyleFont: index font out of range";

		bFlagIgnoreNextPopStyleFont = true; // workaround flag last call to avoid crashes
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::popStyleFont() {
	//TODO: will crash if not pushed..
	//workaround to avoid crashes
	if (bFlagIgnoreNextPopStyleFont) {
		bFlagIgnoreNextPopStyleFont = false;

		return;
	}

	ImGui::PopFont();
}

// NEW API: This is the preferred or recommended method!
//--------------------------------------------------------------
void SurfingGuiManager::PushFont(SurfingFontTypes style) {
	int index = SurfingFontTypes(style);
	//index = ofClamp(index, 0, ImGui::GetIO().Fonts->Fonts.Size - 1);
	index = ofClamp(index, 0, this->getAmountFonts() - 1);
	this->pushStyleFont(index);
}

//--------------------------------------------------------------
void SurfingGuiManager::PopFont() {
	this->popStyleFont();
}

// NEW API: We use the available internal fontIndex to simplify the API workflow.
//--------------------------------------------------------------
void SurfingGuiManager::PushFontByIndex() {
	fontIndex.setWithoutEventNotifications(ofClamp(fontIndex, 0, this->getAmountFonts() - 1));
	//fontIndex = ofClamp(fontIndex, 0, this->getAmountFonts() - 1);

	this->PushFont(SurfingFontTypes(fontIndex.get()));
}

//--------------------------------------------------------------
void SurfingGuiManager::PopFontByIndex() {
	this->PopFont();
}

//--------------------------------------------------------------
int SurfingGuiManager::getNumFonts() {
	return customFonts.size();
}

//--------------------------------------------------------------
int SurfingGuiManager::getAmountFonts() {
	return customFonts.size();
}

//--------------------------------------------------------------
string SurfingGuiManager::getFontPath(int index) {
	string s = "";
	if (index < pathsCustomFonts.size() - 1) s = pathsCustomFonts[index];
	return s;
}

//--------------------------------------------------------------
float SurfingGuiManager::getFontIndexSize() {
	float sz = this->getFontSizeForIndex(fontIndex.get());

	return sz;
}

//--------------------------------------------------------------
string SurfingGuiManager::getFontIndexPath() {
	return getFontPath(this->getFontIndex());
}

//--------------------------------------------------------------
float SurfingGuiManager::getFontSizeForIndex(int index) {
	float sz = -1;

	if (index < customFonts.size()) {
		if (customFonts[index] != nullptr) sz = (customFonts[index]->ConfigData->SizePixels);
		return sz;
	}

	return sz;
}

//--------------------------------------------------------------
string SurfingGuiManager::getFontName(int index) {
	string s = "UNKNOWN";

	if (index < customFonts.size()) {
		if (customFonts[index] != nullptr)
			s = (customFonts[index]->ConfigData->Name);
		return s;
	}

	return s;
}

//--------------------------------------------------------------
string SurfingGuiManager::getFontLabel(int index) {
	string s = "UNKNOWN";

	if (index < namesCustomFonts.size()) {
		s = namesCustomFonts[index];
		return s;
	}

	return s;
}

//--

// Same that AddComboFontsSelector(ofParameter<int>& index) does..
//--------------------------------------------------------------
void SurfingGuiManager::DrawWidgetsFonts() {
	if (customFonts.size() != 0) {
		//make smaller if the window is big
		float w = ofxImGuiSurfing::getWidgetsWidth();
		if (w > 500) {
			ImGuiOldColumnFlags fc = ImGuiOldColumnFlags_NoBorder;
			ImGui::BeginColumns("#cols", 2, fc);
			ImGui::SetColumnWidth(1, w / 2);
			ofxImGuiSurfing::AddComboButtonDualLefted(fontIndex, namesCustomFonts);
			ImGui::Columns(1);
		} else
			ofxImGuiSurfing::AddComboButtonDualLefted(fontIndex, namesCustomFonts);
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::DrawWidgetsFonts(ofParameter<int> & index, bool bWithArrows) {
	if (customFonts.size() != 0) {
		//make smaller if the window is big
		float w = ofxImGuiSurfing::getWidgetsWidth();
		if (bWithArrows) {
			if (w > 300) {
				ImGuiOldColumnFlags fc = ImGuiOldColumnFlags_NoBorder;
				ImGui::BeginColumns("#cols", 2, fc);
				ImGui::SetColumnWidth(0, 200);
				//ImGui::SetColumnWidth(1, w / 2);
				ofxImGuiSurfing::AddComboButtonDualLefted(index, namesCustomFonts);
				ImGui::Columns(1);
			} else
				ofxImGuiSurfing::AddComboButtonDualLefted(index, namesCustomFonts);

			//ofxImGuiSurfing::AddComboButtonDualLefted(index, namesCustomFonts);
		} else {
			ofxImGuiSurfing::AddCombo(index, namesCustomFonts);
		}
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::DrawWidgetsFontsMini() {
	if (customFonts.size() != 0) {
		ofxImGuiSurfing::AddCombo(fontIndex, namesCustomFonts);
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::DrawImGuiTextWithFontStyle(string text, int index, bool bShowName) {
	int i = index;
	string s = text;
	string sn = "";
	i = ofClamp(i, 0, this->getAmountFonts() - 1);
	this->PushFontStyle(i);
	ImGui::Text(s.c_str());
	if (bShowName) {
		sn = this->getFontName(i);
		ImGui::Text(sn.c_str());
	}
	this->PopFontStyle();
}

//--------------------------------------------------------------
string SurfingGuiManager::getFontIndexName() {
	return getFontName(fontIndex.get());
}

//--------------------------------------------------------------
int SurfingGuiManager::getFontIndex() {
	return fontIndex.get();
}

//--------------------------------------------------------------
void SurfingGuiManager::setFontIndex(int index) {
	fontIndex.setWithoutEventNotifications(ofClamp(index, 0, this->getAmountFonts() - 1));
	//fontIndex = index;
}

//--

/*
//--------------------------------------------------------------
void SurfingGuiManager::processOpenFileSelection(ofFileDialogResult openFileResult, int size = 10) {

	string path = openFileResult.getPath();

	ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << " Name:" << openFileResult.getName();
	ofLogNotice("ofxSurfingImGui") << " Path:" << path;

	ofFile file(path);

	if (file.exists())
	{
		ofLogNotice("ofxSurfingImGui") << (" The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());

		// We only want ttf/otf
		if (fileExtension == "TTF" || fileExtension == "ttf" || fileExtension == "OTF" || fileExtension == "otf")
		{
			ofLogNotice("ofxSurfingImGui") << "TTF or OTF found!";

				addFontStyle(path, size);
		}
		else ofLogError("ofxSurfingImGui") << "TTF or OTF not found!";
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::openFontFileDialog(int size)
{
	// Open the Open File Dialog
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a font file, TTF or OTF to add to ImGui", false, ofToDataPath(""));

	// Check if the user picked a file
	if (openFileResult.bSuccess) {

		ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << (" User selected a file");

		// We have a file, check it and process it
		processOpenFileSelection(openFileResult, size);
	}
	else {
		ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << (" User hit cancel");
	}
}
*/

//----

//--------------------------------------------------------------
void SurfingGuiManager::update(ofEventArgs & args) {
	update();
}

//--------------------------------------------------------------
void SurfingGuiManager::update() {
	// -> Not being used by default
	//if (ofGetFrameNum() == 1)
	//{
	//	appLayoutIndex = appLayoutIndex;
	//}

	//--

	// Force call Startup
	//if ((ofGetFrameNum() <= 1) && (!bDoneStartup || !bDoneSetup)
	if (!bDoneSetup || !bDoneStartup) {
		setupStartupForced();
	}

	//--

	// Build mono-spaced fonts flag
	if (bSetupFontForDefaultStylesMonospacedInternal) {
		bSetupFontForDefaultStylesMonospacedInternal = 0;

		setupFontForDefaultStylesMonospacedInternal(pathFontMono, sizeFontMono);
	}

	//--

	// Debug profiler
#ifdef SURFING_IMGUI__USE_PROFILE_DEBUGGER
	if (bDebugDebuggerImGui) {
		debugger.updateProfileTasksCpu(); //call after (before) main ofApp update
		debugger.update();
	}
#endif

	//--

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES
	if (bFlagSaveSettings) {
		bFlagSaveSettings = false;

		ofLogVerbose("ofxSurfingImGui") << "update() Attending save flag.";

		this->saveSettingsInternal();
	}
#endif

	//--

	windowsOrganizer.update();

	//--

	// Build help info max one time per frame.
	if (bFlagDoBuildHelpInternalInfo) {
		bFlagDoBuildHelpInternalInfo = false;
		doBuildHelpInternalInfo();
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::draw() {
	//TODO:
	//if (!bAutoDraw) if (customFont == nullptr) gui.draw();

#ifdef SURFING_IMGUI__USE_PROFILE_DEBUGGER
	if (bDebugDebuggerImGui) debugger.updateProfileTasksGpu(); //call after main ofApp draw
#endif
}

//--------------------------------------------------------------
void SurfingGuiManager::draw(ofEventArgs & args) // -> Auto called on each frame
{
	draw();
}

//--

//--------------------------------------------------------------
void SurfingGuiManager::updateAttendDockingPre() {
	// Save/Load ini layout

	// Load
	if (bFlagDoLoadImGuiLayout) {
		bFlagDoLoadImGuiLayout = false;

		if (pathLayout != "") {
			ImGui::LoadIniSettingsFromDisk(pathLayout.c_str());
		} else {
			ImGuiIO & io = ImGui::GetIO();
			ImGui::LoadIniSettingsFromDisk(io.IniFilename);
		}
	}

	// Save
	if (bFlagDoSaveImGuiLayout) {
		bFlagDoSaveImGuiLayout = false;

		if (pathLayout != "") {
			ImGui::SaveIniSettingsToDisk(pathLayout.c_str());
		} else {
			ImGuiIO & io = ImGui::GetIO();
			ImGui::SaveIniSettingsToDisk(io.IniFilename);
		}
	}
}
//--------------------------------------------------------------
void SurfingGuiManager::loadLayout(string path) {
	bFlagDoLoadImGuiLayout = true;
	pathLayout = ofToDataPath(path);
}
//--------------------------------------------------------------
void SurfingGuiManager::saveLayout(string path) {
	bFlagDoSaveImGuiLayout = true;
	pathLayout = ofToDataPath(path);
}

//--

//--------------------------------------------------------------
void SurfingGuiManager::updateLayout() {
	// Layouts

	if (ini_to_load) {
		ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << " LOAD! " << ini_to_load;

		loadLayoutImGuiIni(ini_to_load);

		ini_to_load = NULL;
	}

	if (ini_to_save) {
		ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << " SAVE! " << ini_to_save;

		if (ini_to_save != "-1") {
			saveLayoutPreset(ini_to_save);
		}

		ini_to_save = NULL;
	}
}

//----

//--------------------------------------------------------------
void SurfingGuiManager::drawLayoutsManager() {
	ImGuiWindowFlags flagsMng = ImGuiWindowFlags_None;

	// Exclude from imgui.ini settings.
	// will be independent from layout presets.
	flagsMng |= ImGuiWindowFlags_NoSavedSettings;

	if (bAutoResize) flagsMng |= ImGuiWindowFlags_AlwaysAutoResize;

	//--

	// Lock to the right of the Presets Window (tittled as Layouts)

	// Skip if the anchor window is hidden! to avoid being locked!

	if (bGui_LayoutsPresetsSelector) {
		ImGuiCond mngCond;
		mngCond = ImGuiCond_Appearing;

		bool blocked = true;
		if (blocked) {
			int _pad = windowsOrganizer.pad;

			glm::vec2 pos = rectangles_Windows[0].get().getTopRight();
			ofRectangle r = rectangles_Windows[2];
			r.setPosition(pos.x + _pad, pos.y);
			r.setWidth(rectangles_Windows[0].get().getWidth());

			//TODO:
			// set same height than Layouts panel if visible
			if (bGui_LayoutsPanels) r.setHeight(rectangles_Windows[0].get().getHeight());

			rectangles_Windows[2] = r;
			mngCond = ImGuiCond_Always;
		}

		const int i = 2;
		ImGui::SetNextWindowPos(ofVec2f(rectangles_Windows[i].get().getX(), rectangles_Windows[i].get().getY()),
			mngCond);
	} else {
	}

	//--

	// 1. Layouts window

	if (bGui_LayoutsManager) {
		//IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;
		float w = 150;
		ImVec2 size_min = ImVec2(w, -1);
		ImVec2 size_max = ImVec2(w, -1);
		ImGui::SetNextWindowSizeConstraints(size_min, size_max);
	}

	if (this->BeginWindow(bGui_LayoutsManager, flagsMng)) {
		const int i = 2;
		rectangles_Windows[i].setWithoutEventNotifications(ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
			ImGui::GetWindowWidth(),
			ImGui::GetWindowHeight()));

		//-

		float _w = ofxImGuiSurfing::getWidgetsWidth(1);
		float _h = 2 * ofxImGuiSurfing::getWidgetsHeightRelative();

		//--

		if (!bGui_LayoutsPanels) {
			// Panels
			AddBigToggle(bGui_LayoutsPanels, _w, _h, false);
			this->AddTooltip("F6");

			// Presets
			AddBigToggle(bGui_LayoutsPresetsSelector, _w, _h, false);
			this->AddTooltip("F5");

			this->AddSpacingSeparated();
		}

		//--

		// 1. Panels window

		// Show a mini version when the main panel is hidden!

		if (!bGui_LayoutsPanels) {
			static bool bOpen = false;
			ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);

			ImGui::PushID("##PANELS1");
			if (ImGui::CollapsingHeader("PANELS", _flagw)) {
				this->AddSpacing();

				// All the queued special windows aka panels
				for (int i = 0; i < windows.size(); i++) {
					AddToggleRoundedButton(windows[i].bGui);
				}

				this->AddSpacing();

				// All, None
				float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);
				if (ImGui::Button("All", ImVec2(_w2, _h / 2))) {
					this->setShowAllPanels(true);
				}
				ImGui::SameLine();
				if (ImGui::Button("None", ImVec2(_w2, _h / 2))) {
					this->setShowAllPanels(false);
				}
			}
			ImGui::PopID();

			this->AddSpacingSeparated();
		}

		//--

		// 2. Layout/Manager windows

		// Layouts tree
		if (ImGui::TreeNode("LAYOUTS")) {
			this->refreshLayout();
			Add(bAutoResize_PresetsWindows, OFX_IM_TOGGLE_ROUNDED_SMALL);
			Add(bReset_PresetsWindow, OFX_IM_BUTTON_SMALL);

			ImGui::TreePop();
		}

		this->AddSpacingSeparated();

		// Panels tree
		ImGui::PushID("##PANELS2");
		if (ImGui::TreeNode("PANELS")) {
			this->refreshLayout();
			Add(bAutoResize_Panels, OFX_IM_TOGGLE_ROUNDED_SMALL);
			Add(bReset_WindowPanels, OFX_IM_BUTTON_SMALL);
			//if (bAutoResize_Panels) Add(bReset_WindowPanels, OFX_IM_BUTTON_SMALL);

			// Landscape
			//Add(bLandscape, OFX_IM_TOGGLE_ROUNDED);//TODO:

			ImGui::TreePop();
		}
		ImGui::PopID();

		//--

		// Extra Params

		if (!bMinimize_Presets) {
			//if (!bGui_LayoutsPanels) this->AddSpacingSeparated();
			this->AddSpacingSeparated();

			this->AddGroup(params_LayoutsExtra);
		}

		//--

		// Advanced toggles bundled

		if (!bMinimize_Presets) {
			this->AddSpacingSeparated();

			// a toggle that expands the other widgets
			this->DrawAdvancedBundle();
		}

		this->EndWindow();
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::drawLayoutsPresetsEngine() {
	// Draws all sections except:
	// drawLayoutsManager() and drawLayoutsPresetsManualWidgets();

	//--

	//TODO:
	// How to make all windows dockeable in the same space ?

	// Main Layout Presets clicker
	// and Manager linked windows
	if (bGui_LayoutsPresetsSelector) {
		drawLayoutsLayoutPresets();

		//if (!bMinimize_Presets) if (bGui_LayoutsPresetsManual) drawLayoutsPresetsManualWidgets();
	}

	//--

	// Main Panels clicker
	if (bGui_LayoutsPanels) {
		drawLayoutsPanels();
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::drawLayoutPresetsEngine() {
	if (bUseLayoutPresetsManager && !bMinimize_Presets)
		if (bGui_LayoutsManager) drawLayoutsManager();

	//----

	if (bUseLayoutPresetsManager) {
		// Attend save/load flags
		updateLayout();

		//----

		if (bDockingLayoutPresetsEngine) {
			ImGuiID dockNodeID;
			ImGuiDockNode * dockNode;
			//ImGuiDockNode* centralNode;
			//ImGuiDockNodeFlags dockingFlags;

			//----

			// a. Define the ofWindow as a docking space

			//ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0)); // Fixes imgui to expected behaviour. Otherwise add in ImGui::DockSpace() [~line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
			//ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_PassthruCentralNode);
			//ImGui::PopStyleColor();

			//-

			// b. Lockable settings

			// Fixes imgui to expected behavior. Otherwise add in ImGui::DockSpace() [~line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
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

			if (dockNode) {
				ImGuiDockNode * centralNode = ImGui::DockBuilderGetCentralNode(dockNodeID);

				// Verifies if the central node is empty (visible empty space for oF)
				if (centralNode && centralNode->IsEmpty()) {
					ImRect availableSpace = centralNode->Rect();
					//availableSpace.Max = availableSpace.Min + ImGui::GetContentRegionAvail();
					//ImGui::GetForegroundDrawList()->AddRect(availableSpace.GetTL() + ImVec2(8, 8), availableSpace.GetBR() - ImVec2(8, 8), IM_COL32(255, 50, 50, 255));

					ImVec2 viewCenter = availableSpace.GetCenter();
					// Depending on the viewports flag, the XY is either absolute or relative to the oF window.
					//if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());

					float ww = availableSpace.GetSize().x;
					float hh = availableSpace.GetSize().y;
					rectangleCentralMAX = ofRectangle(viewCenter.x, viewCenter.y, ww, hh);

					bool bDebug_ = bDrawViewportRectangleCentralDebug2.get();
					if (bDebug_) {
						int _wl = 2;
						int pad = 10;

						ofPushStyle();
						ofSetRectMode(OF_RECTMODE_CENTER);

						int g = 0;
						ofColor cl = ofColor::white;
						//ofColor cl = ofColor::orange;

						//int g = 255 * Bounce(0.5);
						int a = 255.f * ofMap(Bounce(1), 0.0f, 1.0f, 0.2f, 1.0f, true);
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

						//ofDrawRectangle(rectangleCentralMAX);
						ofSetRectMode(OF_RECTMODE_CORNER);
						ofPopStyle();
					}
					// move to left corner mode
					rectangleCentralMAX.translate(-ww / 2, -hh / 2);

					//-

					static ofRectangle rectangle_Central_MAX_PRE;

					{
						if (rectangle_Central_MAX_PRE != rectangleCentralMAX) {
							// updates when layout changes..
							rectangle_Central_MAX_PRE = rectangleCentralMAX;

							bool bSkip = false;
							bSkip = (rectangleCentralDebug.getWidth() == 0 || rectangleCentralDebug.getHeight() == 0);
							bSkip += (rectangleCentralMAX.getWidth() == 0 || rectangleCentralMAX.getHeight() == 0);
							if (!bSkip) {
								// fit exact rectangle to borders and scaled to fit
								//rectangleCentralDebug = DEMO3_Svg.getRect();
								//if (rectangleCentralMAX.getWidth() != 0 && rectangleCentralMAX.getHeight() != 0) // avoid crash
								rectangleCentralDebug.scaleTo(rectangleCentralMAX, OF_ASPECT_RATIO_KEEP,
									OF_ALIGN_HORZ_CENTER, OF_ALIGN_VERT_CENTER);

								//// rescaled rectangle a bit
								//float _scale = 0.7f;
								//rectangleCentralTransposed = rectangleCentralDebug;
								//rectangleCentralTransposed.scaleFromCenter(_scale, _scale);//scale down to fit layout spacing better
								//rectangleCentralTransposed.translateY(rectangleCentralDebug.getHeight() * 0.07);//move down a bit
								//DEMO3_Svg.setRect(rectangleCentralTransposed);
							}
						}
					}
				}
			}
		}

		//----

		//// b. Lockable settings

		//// Fixes imgui to expected behavior. Otherwise add in ImGui::DockSpace() [~line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
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

//--------------------------------------------------------------
void SurfingGuiManager::updateCentralRect() {
	//TODO:
	// Debug central viewport.
	// Free space for OF drawing.

	ImGuiDockNodeFlags __dockingFlags;
	__dockingFlags = ImGuiDockNodeFlags_PassthruCentralNode;

	auto dockNodeID = ImGui::GetID("MyDockSpace");

	ImGuiDockNode * dockNode = ImGui::DockBuilderGetNode(dockNodeID);
	if (dockNode) {
		ImGuiDockNode * centralNode = ImGui::DockBuilderGetCentralNode(dockNodeID);

		//if (centralNode && centralNode->IsEmpty())
		if (centralNode) {
			ImRect availableSpace = centralNode->Rect();

			ImVec2 viewCenter = availableSpace.GetCenter();

			// Depending on the viewports flag,
			// the XY is either absolute or relative to the oF window.
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
				viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());

			// Debug rectangle
			rectangleCentralDebug = ofRectangle(viewCenter.x, viewCenter.y,
				availableSpace.GetWidth(), availableSpace.GetHeight());
			float v = Bounce(1);
			rectangleCentralDebug.setSize(availableSpace.GetWidth() * v, availableSpace.GetHeight() * v);

			// Useful in OF to be used as viewport:
			rectangleCentralViewport = ofRectangle(availableSpace.GetTL().x, availableSpace.GetTL().y,
				availableSpace.GetWidth(), availableSpace.GetHeight());

			// Fix some situations
			if (rectangleCentralViewport == ofRectangle(0, 0, 0, 0))
				rectangleCentralViewport = ofGetCurrentViewport();
			if (rectangleCentralViewport == ofRectangle(0, 0, 0, 0))
				rectangleCentralViewport = { 0, 0, 1920, 1080 };
		}
	} else // Get the OF viewport
	{
		auto view = ofGetCurrentViewport();

		// Debug rect
		auto viewCenter = view.getCenter();
		rectangleCentralDebug = ofRectangle(viewCenter.x, viewCenter.y, view.getWidth(), view.getHeight());
		float v = Bounce(1);
		rectangleCentralDebug.setSize(view.getWidth() * v, view.getHeight() * v);

		// Useful in OF to be used as viewport:
		rectangleCentralViewport = view;

		// Fix some situations
		if (rectangleCentralViewport == ofRectangle(0, 0, 0, 0))
			rectangleCentralViewport = ofGetCurrentViewport();
		if (rectangleCentralViewport == ofRectangle(0, 0, 0, 0))
			rectangleCentralViewport = { 0, 0, 1920, 1080 };
	}
}

#ifdef SURFING_IMGUI__FIXING_DRAW_VIEWPORT
//--------------------------------------------------------------
void SurfingGuiManager::drawViewportRectangleCentralDebug() {
	// Requires that updateCentralRect() has been called on current/lat frame!

	// Draw
	ofPushStyle();
	{
		ofSetRectMode(OF_RECTMODE_CENTER);

		ofSetLineWidth(4);
		ofColor cl = ofColor::white;
		//ofColor cl = ofColor::yellow;
		int a = 255.f * ofMap(Bounce(1), 0.0f, 1.0f, 0.2f, 1.0f, true);
		ofColor c = ofColor(cl.r, cl.g, cl.b, a);
		ofSetColor(c);
		ofFill();
		ofDrawCircle(rectangleCentralDebug.getCenter().x, rectangleCentralDebug.getCenter().y, 3);
		ofNoFill();
		ofDrawRectangle(rectangleCentralDebug);

		ofSetRectMode(OF_RECTMODE_CORNER);
	}
	ofPopStyle();
}
#endif

//--------------------------------------------------------------
void SurfingGuiManager::setupStartupForced() {
	ofLogWarning(__FUNCTION__);

	if (!bDoneSetup) {
		ofLogWarning("ofxSurfingImGui") << "Setup() was not called/done!";
		ofLogWarning("ofxSurfingImGui") << "Force a default Setup() call!";

		setup();
	}

	// Force call startup().
	// Maybe user forgets to do it or to speed up the API setup in some scenarios.
	// i.e. when not using special windows or layout engine
	if (!bDoneStartup) {
		ofLogWarning("ofxSurfingImGui") << "Startup() was not called after initiation process.";
		ofLogWarning("ofxSurfingImGui") << "Auto force call Startup()!";

		startup();
	}

	//TODO:
	{
		appLayoutIndex = appLayoutIndex;
		if (rectangles_Windows.size() > 0) rectangles_Windows[1] = rectangles_Windows[1];
	}
}

//----

// Global ImGui being/end like ofxImGui
//
// All the ImGui Stuff goes in between here,
// The RAW ImGui widgets and the API / Engine handled stuff too!
//
//--------------------------------------------------------------
void SurfingGuiManager::Begin() {
	// Check that it's property initialized!
	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) {
		ofLogError("ofxSurfingImGui") << "Begin()"
									  << "\n"
									  << ("Initialization was not done properly. \nCheck the examples / documentation.");

		return;
	}

	//--

	//TODO:
	//// Force call Startup
	//if (ofGetFrameNum() <= 1)
	//	if (!bDoneStartup || !bDoneSetup)
	//{
	//	setupStartupForced();
	//}

	//--

	//TODO:
	_indexLastBegin = -1;

	rectangleLastWindowShape = ofRectangle();

	//--

	// Reset unique names
	// Here it handles the queued ofParams names
	// to avoid colliding by using push/pop id's tags.
	resetUniqueNames();

	// This handles the name to Push/Pop widgets IDs
	// Then we can use several times the same ofParameter with many styles,
	// into the same window without colliding!
	// That collide happens when using the original legacy ofxImGui ofParam Helpers!

	//--

	//TODO:
	// Sometimes we could use an ofxImGui external or from a parent scope..
	if (guiPtr != nullptr)
		guiPtr->begin();
	else
		gui.begin();

		//--

		// Global Scale
#ifdef SURFING_IMGUI__USE_GLOBAL_SCALE
	if (customFonts.size() > 0) {
		ImGuiIO & io = ImGui::GetIO();
		io.FontGlobalScale = globalScale;
		//io.scale= globalScale;

		// Global scale by Ctrl + mouse wheel:
		io.FontAllowUserScaling = bGlobalScaleWheel;
	}
#endif

	//--

	// Font
#ifdef SURFING_IMGUI__DEBUG_FONTS
	// Reset font to default (#0).
	// this clears all the push/pop queue.
	if (customFonts.size() > 0) {
		setDefaultFont();
		if (customFont != nullptr) ImGui::PushFont(customFont);
	}
#endif

	//--

	//TODO:
	// Fix
	//if (!bDockingLayoutPresetsEngine) if (bGui_TopMenuBar) drawMenu();

	//----

	// Extra Tools / Engines

	// 1. Layout Presets Engine
	// Layout and Panels windows.

	if (bDockingLayoutPresetsEngine) drawLayoutPresetsEngine();
	// false by default as/when docking has not been initiated.

	//----

	// 2. Special Windows Engine Window Panel

	// Organizer

	if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER) {
		// Main Panels Controller
		if (windowsOrganizer.isInitiated()) {
			// Organizer
			if (bGui_Organizer) drawWindowOrganizer();

			// Special windows toggles
			if (bGui_SpecialWindows) drawWindowSpecialWindows();
		}
	}

	//----

	// 3. Aligners

	if (bGui_Aligners) drawWindowAligners();

#ifndef SURFING_IMGUI__USE_PROFILE_DEBUGGER
	if (bDebugDebuggerImGui) ImGui::ShowMetricsWindow();
#endif

	//----

	updateAttendDockingPre();

	//----

#ifdef SURFING__DOCKING_WORKFLOW_HANDLER_AUTODOCKING
	//workflow
	if (bModeDockingAutohandler) {
		this->BeginDocking();
		this->EndDocking();
	}
#endif
}

//--------------------------------------------------------------
void SurfingGuiManager::drawWindowsExtraManager() {
	// Auto handles drawing of extra windows. Not required to draw manually!

	//--

	// Log

	DrawWindowLogIfEnabled();

	//--

	// Notifier

#ifdef SURFING_IMGUI__USE_NOTIFIER
	DrawNotifierIfEnabled();
#endif

	//--

	// Profiler

#ifdef SURFING_IMGUI__USE_PROFILE_DEBUGGER
	if (bDebugDebuggerImGui) debugger.drawImGui();
		//if (bDebugDebuggerImGui) debugger.draw(this);//TODO: how to pass ui?
#endif

		//--

#ifdef SURFING_IMGUI__FIXING_DRAW_VIEWPORT
	if (bDrawViewportRectangleCentralDebug) drawViewportRectangleCentralDebug();
#endif

	//--

	// Draw Help windows

	// Internal

	if (bUseHelpInternal) {
		helpInternal.draw();
	}

	// App

	if (bUseHelpApp) {
		helpApp.draw();
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::End() {
	// Check that it's property initialized!
	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) return;

	//--

	//TODO:
	//workflow
	// if there's no settings files, it means that the app it's opened by first time,
	// then probably the windows will be overlapped..
	if (ofGetFrameNum() > 1)
		if (!bDisableStartupReset && bFlagDoForceStartupResetLayout && !bDoneDoForceStartupResetLayout) {
			doResetLayout();
			bDoneDoForceStartupResetLayout = true;
		}

	//--

	drawWindowsExtraManager();

	//--

	// Font

	//TODO: could set the default font instead of Pop..
	// bc that will be prophylactic if pushed too many fonts by error!
#ifdef SURFING_IMGUI__DEBUG_FONTS
	if (customFonts.size() > 0) {
		if (customFont != nullptr) ImGui::PopFont();
	}
#endif

	//--

	// Mouse and Keyboard
	doCheckOverGui();

	//--

	// some helpers
	xSpacingDiff = 0;
	ySpacingDiff = 0;

	//----

	// ImGui End

	//TODO:
	// Sometimes we could use an ofxImGui external or from a parent scope.
	// This should be tested. bc it's kind of a deprecated idea/feature.
	if (guiPtr != nullptr)
		guiPtr->end();
	else
		gui.end();

	//--

	//TODO: Should add a new variable like bDrawInfront to draw back/foreground...
	//TODO: Maybe it's an ofxImGui feature..
	if (!bAutoDraw) gui.draw();

	//--

	//#ifdef SURFING__DOCKING_WORKFLOW_HANDLER_AUTODOCKING
	//	//workflow
	//	if (!bModeDockingAutohandler) {
	//		if (bDoneBeginDocking && bDoneEndDocking) bModeDockingAutohandler = true;
	//	}
	//#endif
}

//--

// Begin Window Methods

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindow(char * name) {
	ImGuiWindowFlags fg = ImGuiWindowFlags_None;
	if (bAutoResize) fg |= ImGuiWindowFlags_AlwaysAutoResize;

	bool b = BeginWindow((string)name, NULL, fg);
	// required to avoid exceptions when minimizing the window.
	if (!b) this->EndWindow();

	return b;
}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindow(char * name, ImGuiWindowFlags window_flags) {
	string n = name;
	bool b = BeginWindow(n, NULL, window_flags);

	return b;
}

////--------------------------------------------------------------
//bool SurfingGuiManager::BeginWindow(char* name, ImGuiWindowFlags window_flags, ImGuiCond cond)
//{
//	string n = name;
//	bool b = BeginWindow(n, NULL, window_flags, cond);
//
//	return b;
//}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindow(string name) {
	ImGuiWindowFlags fg = ImGuiWindowFlags_None;
	if (bAutoResize) fg |= ImGuiWindowFlags_AlwaysAutoResize;

	bool b = BeginWindow(name, NULL, fg);
	// required to avoid exceptions when minimizing the window.
	if (!b) this->EndWindow();

	return b;
}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindow(string name, bool * p_open) {
	if (!&p_open) return false;

	ImGuiWindowFlags fg = ImGuiWindowFlags_None;
	if (bAutoResize) fg |= ImGuiWindowFlags_AlwaysAutoResize;

	bool b = BeginWindow(name, p_open, fg);
	// required to avoid exceptions when minimizing the window.
	if (!b) this->EndWindow();

	return b;
}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindow(ofParameter<bool> & p) {
	if (!p.get()) return false; // p is used as the "visible toggle"

	if (p.getName() == "") {
		ofLogWarning("ofxSurfingImGui") << (__FUNCTION__);
		ofLogWarning("ofxSurfingImGui") << "Current bool parameter have NO NAME!";
		ofLogWarning("ofxSurfingImGui") << "Take care and set a name to it.";
		p.setName("__NONAME__");
	}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize; // windows can be auto resized or not

	//TODO:
	// workaround
	// fix to trig the ofParams callbacks
	// when closed window by the x on the upper right corner.
	bool tmp = p.get();
	bool b = BeginWindow(p.getName().c_str(), (bool *)&tmp, window_flags);
	// trig if changed
	if (p.get() != tmp) p.set(tmp);

	// required to avoid exceptions when minimizing the window.
	//fix crashes when foldering
	if (!b) this->EndWindow();

	return b;
}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindow(string name, ofParameter<bool> & p) {
	if (!p.get()) return false;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	return BeginWindow(name.c_str(), (bool *)&p.get(), window_flags);
}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindow(string name, ofParameter<bool> & p, ImGuiWindowFlags window_flags) {
	if (!p.get()) return false;

	return BeginWindow(name.c_str(), (bool *)&p.get(), window_flags);
}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindow(ofParameter<bool> & p, ImGuiWindowFlags window_flags) {
	if (!p.get()) return false;

	//bool b = BeginWindow(p.getName().c_str(), (bool*)&p.get(), window_flags);

	//TODO:
	// workaround
	// fix to trig the ofParams callbacks
	// when closed window by the x on the upper right corner.
	bool tmp = p.get();
	bool b = BeginWindow(p.getName().c_str(), (bool *)&tmp, window_flags);
	// trig if changed
	if (p.get() != tmp) p.set(tmp);

	//TODO:
	//fix crashes when foldering
	if (!b) this->EndWindow();

	return b;
}

// This is the main BeginWindow.
// All above methods will call this one!

////--------------------------------------------------------------
//bool SurfingGuiManager::BeginWindow(string name = "Window", bool* p_open = NULL, ImGuiWindowFlags window_flags = ImGuiWindowFlags_None, ImGuiCond cond)
//{
//}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindow(string name = "Window", bool * p_open = NULL,
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None) {
	//ImGuiCond cond = ImGuiCond_None;

	//TODO:
	//if (bLockMove) window_flags |= ImGuiWindowFlags_NoMove;

	//TODO:
	//if (bReset_Window) {
	//	bReset_Window = false;
	//	resetWindowImGui(false, true);
	//}

	//--

	// Reset unique names
	// This is to handle the widgets ID to avoid repeat an used name,
	// avoiding colliding between them
	// when params are re used on the same window/scope.

	resetUniqueNames();

	//--

#if 0 // 0 to let user to control externally
	if (p_open) {
		// Default constraints
		//IMGUI_SUGAR__WINDOWS_CONSTRAINTS;
		//IMGUI_SUGAR__WINDOWS_CONSTRAINTS_SMALL;

		// Default size
		ImGui::SetNextWindowSize(ImVec2{ 100,100 }, ImGuiCond_FirstUseEver);
	}
#endif

	//--

	bool b = ImGui::Begin(name.c_str(), p_open, window_flags);

	//--

	////TODO: crashes ?
	//// Early out if the window is collapsed, as an optimization.
	//if (!b)
	//{
	//	ImGui::End();
	//	return false;
	//}

	// When we are instantiating ImGui externally,
	// not inside this addon,
	// we don't handle the font and theme.
	if (surfingImGuiMode != ofxImGuiSurfing::IM_GUI_MODE_NOT_INSTANTIATED) {
		// Set default font
		setDefaultFont();
	}

	// Refresh layout
	// Calculates sizes related to current window shape/size.
	_ui.refreshLayout();

	return b;
}

//--

// Begin Special Windows

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindowSpecial(string name) {
	int _index = getWindowSpecialIndexForName(name);

	if (_index != -1) {
		return BeginWindowSpecial(_index);
	} else {
		ofLogError("ofxSurfingImGui") << (__FUNCTION__) << " Special Window with name '" << name << "' not found!";
		return false;
	}
}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindowSpecial(int index) {
	//TODO:
	// workflow helper
	_indexLastBegin = index;

	//--

	// Skip if there's no queued special windows
	if (index > windows.size() - 1 || index == -1) {
		ofLogError("ofxSurfingImGui") << "BeginWindowSpecial: Out of range index for queued windows, " << index;
		return false;
	}

	//--

	// Skip window if hidden
	if (!windows[index].bGui.get()) return false;

	//--

	ImGuiWindowFlags flags = ImGuiWindowFlags_None;

	//--

	if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER) {
		// All can be disabled by the Global toggle
		if (!windowsOrganizer.bGui_ShowWindowsGlobal.get()) return false;

		//--

		// Run the linking engine when this is enabled
		if (windowsOrganizer.bLinked) {
			//TODO:
			// make refresh faster
			// can be moved to global begin() to reduce calls ?
			// maybe is better like that bc it's called many times.. ?
			windowsOrganizer.refreshUpdate();
			windowsOrganizer.runShapeState(index);
		}

		//--

		// Header
		if (!windowsOrganizer.bHeaders) flags += ImGuiWindowFlags_NoDecoration;
	}

	//--

	// Auto resize

	//TODO
#if 1
	// Globally settled
	if (bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;
#else
	// Per window
	if (windows[index].bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;
		// independent for each window
#endif

	//--

	bool b = BeginWindow(windows[index].bGui, flags);

	//--

	//bool b = BeginWindow(windows[index].bGui);
	//if (windows[index].bMasterAnchor.get()) // window
	//{
	//	if (windows[index].bAutoResize.get()) {
	//		flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//	}
	//}
	//bool b = BeginWindow(windows[index].bGui.getName().c_str(), (bool*)&windows[index].bGui.get(), flags);

	//--

	return b;
}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindowSpecial(ofParameter<bool> & _bGui) {
	if (!_bGui) return false;

	int i = getWindowSpecialIndexForToggle(_bGui);

	if (i != -1) {
		return BeginWindowSpecial(i);
	} else {
		ofLogError("ofxSurfingImGui") << (__FUNCTION__) << " Special Window toggle not found! " << _bGui.getName();

		//TODO:
		// detect if there is no special window with that name,
		// and then call a normal window to avoid missing drawing.
		// being prophylactic.
		//return BeginWindow(_bGui);

		return false;
	}
}

//--------------------------------------------------------------
int SurfingGuiManager::getWindowSpecialIndexForName(string name) {
	for (size_t i = 0; i < windows.size(); i++) {
		string _name = windows[i].bGui.getName();

		if (name == _name) {
			return i;
		}
	}

	ofLogVerbose("ofxSurfingImGui") << (__FUNCTION__) << "\n"
									<< "Special Window with name '" << name << "' not found!";

	return -1;
}

//--------------------------------------------------------------
int SurfingGuiManager::getWindowSpecialIndexForToggle(ofParameter<bool> & _bGui) {
	string name = _bGui.getName();

	for (size_t i = 0; i < windows.size(); i++) {
		string _name = windows[i].bGui.getName();

		if (name == _name) {
			return i;
		}
	}

	ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n"
								  << "Special Window toggle not found! " << _bGui.getName();

	return -1;
}

//TODO:
//--------------------------------------------------------------
void SurfingGuiManager::EndWindowSpecial(ofParameter<bool> & _bGui) {
	string name = _bGui.getName();
	int i = getWindowSpecialIndexForName(name);

	if (i == -1) {
		ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n"
									  << "Special Window with bool param with name '" << name
									  << "' not found!";

		return;
	}

	EndWindowSpecial(i);

	return;
}

//--------------------------------------------------------------
void SurfingGuiManager::EndWindowSpecial(int index) {
	if (index == -1) index = _indexLastBegin; // workaround

	//--

	if (index > windows.size() - 1) {
		ofLogError("ofxSurfingImGui") << (__FUNCTION__) << "\n"
									  << "Out of range index for queued windows, " << index;
		return;
	}

	//--

	//TODO: crash ?
	//// Skip window if hidden (bGui = false)
	//if (!windows[index].bGui.get()) return;

	//--

	if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER) {
		if (!windowsOrganizer.bGui_ShowWindowsGlobal.get()) return;
	}

	//--

	if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER) {
		if (windowsOrganizer.bLinked) {
			// Reads the window shape before end
			windowsOrganizer.getShapeState(index);

			//TODO: make refresh faster
			//windowsOrganizer.refreshUpdate();
		}
	}

	this->EndWindow();
}

//--------------------------------------------------------------
void SurfingGuiManager::EndWindow() {
	rectangleLastWindowShape = getWindowShape();

	ImGui::End();
}

//--------------------------------------------------------------
bool SurfingGuiManager::BeginWindowAnyType(ofParameter<bool> & p) {
	bool b;
	if (this->isThereSpecialWindowFor(p))
		b = this->BeginWindowSpecial(p);
	else
		b = this->BeginWindow(p);
	return b;
}

//--------------------------------------------------------------
void SurfingGuiManager::EndWindowAnyType(ofParameter<bool> & p) {
	if (this->isThereSpecialWindowFor(p))
		this->EndWindowSpecial();
	else
		this->EndWindow();
}

//--

// Docking Helpers

//--------------------------------------------------------------
void SurfingGuiManager::BeginDocking() {
	//dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	//static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

	if (bUseMenu && bGui_TopMenuBar) window_flags |= ImGuiWindowFlags_MenuBar;

	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;

	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	window_flags |= ImGuiWindowFlags_NoNavFocus;

	// When using ImGuiDockNodeFlags_PassthruCentralNode,
	// DockSpace() will render our background and handle the pass-thru hole,
	// so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
		window_flags |= ImGuiWindowFlags_NoBackground;
	}

	ImGuiViewport * viewport = ImGui::GetMainViewport();

	// Fit full viewport
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship
	// between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead
	// to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("DockSpace", nullptr, window_flags);
	//ImGui::Begin("MyDockSpace", nullptr, window_flags);//?

	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);

	//----

	// DockSpace
	ImGuiIO & io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	} else {
		// Docking is DISABLED - Show a warning message
		//ShowDockingDisabledMessage();
	}

	//----

	// All windows goes here before endDocking()
	if (surfingImGuiMode == ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING) {
		drawLayoutsPresetsEngine();
	}

	//----

	updateCentralRect();

#ifdef SURFING__DOCKING_WORKFLOW_HANDLER_AUTODOCKING
	bDoneBeginDocking = true;
#endif
}

//--------------------------------------------------------------
void SurfingGuiManager::EndDocking() {
	//TODO
	if (bUseMenu && bGui_TopMenuBar) drawMenuDocked();

	//--

	//ImGuiIO& io = ImGui::GetIO();
	//if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	//{
	//}

	//--

	// End the parent window that contains the Dockspace:
	ImGui::End(); // ?

	//TODO: to check if there's not central part / free space for the viewport!
	/*
	if (!dockNode || !ImGui::DockBuilderGetCentralNode(dockNodeID) || !ImGui::DockBuilderGetCentralNode(dockNodeID)->IsEmpty()) {
		static int posX = 1, posY = 1, velX = 1, velY = 1;
		ofDrawBitmapStringHighlight("No empty dock space, nowhere to draw for oF !", posX, posY);
		posX += velX * 3;
		posY += velY * 3;
		ofBitmapFont f;
		ofRectangle strSize = f.getBoundingBox("No empty dock space, nowhere to draw for oF !", posX, posY);
		if (posX <= 0) velX = 1;
		if (posY <= strSize.height) velY = 1;
		if (posX >= ofGetWidth() - strSize.width) velX = -1;
		if (posY >= ofGetHeight()) velY = -1;
	}
	*/

#ifdef SURFING__DOCKING_WORKFLOW_HANDLER_AUTODOCKING
	bDoneEndDocking = true;
#endif
}

//----

// Layouts presets management
//--------------------------------------------------------------
void SurfingGuiManager::setupLayout(int numPresets) //-> must call manually after adding windows and layout presets
{
	numPresetsDefault = numPresets; // default is 4 presets with names P0, P1, P2, P3

	//-

	//// Clear
	//params_Layouts.clear();
	//params_LayoutsExtra.clear();
	//params_LayoutsVisible.clear();

	//--

	// 1.1 Store all the window panels show toggles
	// we will remember, on each layout preset, if a window is visible or not!

	for (int i = 0; i < windows.size(); i++) {
		params_LayoutsVisible.add(windows[i].bGui);
	}

	//--

	// 1.2 Add other settings that we want to store into each presets

	//-

#if 1
	// Extra params that will be included into each preset.
	// Then can be different and memorized in different states too,
	// like the common panels.

	params_LayoutsExtra.add(bGui_TopMenuBar);
	params_LayoutsExtra.add(bLog);
	params_LayoutsExtra.add(bNotifier);
	//TODO: should be removed if handled by preset engine..

	//params_LayoutsExtraInternal.clear();
	//params_LayoutsExtraInternal.add(bGui_TopMenuBar);
	//params_LayoutsExtraInternal.add(bLog);
	//params_LayoutsExtra.add(params_LayoutsExtraInternal);
#endif

	//--

	// 1.2.2 Special Windows Helpers

	if (specialsWindowsMode == IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER) {
		this->addExtraParamToLayoutPresets(this->getGuiToggleLinked());
		//params_LayoutsExtra.add(windowsOrganizer.getParamsSettings());
	}

	//--

	// 1.3 Applied to control windows

	//params_LayoutsExtra.add(bModeFree);
	//params_LayoutsExtra.add(bModeForced);
	//params_LayoutsExtra.add(bModeLock1);
	//params_LayoutsExtra.add(bModeLockControls);

	//--

	// 1.4 Pack both groups

	params_Layouts.add(params_LayoutsVisible);
	params_Layouts.add(params_LayoutsExtra);

	//--

	// 2. Initiate

	bLayoutPresets.clear();
	params_LayoutPresetsStates.clear();
	appLayoutIndex.setMax(0);

	//--

	// 3. Populate some presets
	// if the app is opened for first time or there's no presets yet!

	for (int i = 0; i < numPresetsDefault; i++) {
		if (namesPresets.size() == 0) {
			// if names are not defined will be settled by default P0-P1-P2-P3
			createLayoutPreset();
		} else {
			if (i < namesPresets.size())
				createLayoutPreset(namesPresets[i]);
			else
				createLayoutPreset();
		}
	}

	//--

	// 4. App states for the next session

	// The main control windows

	params_AppSettings.add(bGui_LayoutsManager);

	//params_AppSettingsLayout.add(bModeFree);
	//params_AppSettingsLayout.add(bModeForced);
	//params_AppSettingsLayout.add(bModeLock1);
	//params_AppSettingsLayout.add(bModeLockControls);
	//params_AppSettingsLayout.add(bModeLockPreset);

	params_AppSettingsLayout.add(bGui_LayoutsPresetsSelector);
	params_AppSettingsLayout.add(bGui_LayoutsPanels);
	//params_AppSettingsLayout.add(bGui_LayoutsPresetsManual);

	//params_AppSettingsLayout.add(bGui_Organizer);
	//params_AppSettingsLayout.add(bGui_SpecialWindows);

	params_AppSettingsLayout.add(bAutoSave_Layout);
	params_AppSettingsLayout.add(bDrawViewportRectangleCentralDebug);
	params_AppSettingsLayout.add(appLayoutIndex);
	params_AppSettingsLayout.add(bSolo);

	params_AppSettings.add(params_AppSettingsLayout);

	//--

	// Exclude from settings but to use the grouped callback
	//bSolo.setSerializable(false);

	//---------------

	// Engine Windows

	// Initiate the 3 control windows
	// We store the shapes using ofRectangles to "split" them from ImGui .ini store manager...

	float x, y, w, h, pad;
	x = ofGetWidth() * 0.6;
	y = 30;
	w = 200;
	h = 1;
	pad = windowsOrganizer.pad;

	//--

	rect0_Presets.set(ofRectangle(10, y, w, h));
	rect1_Panels.set(ofRectangle(x, y, w, h));
	rect2_Manager.set(ofRectangle(x + 2 * (pad + w), y, w, h));

	//rect1_Panels.set(ofRectangle(x + (pad + w), y, w, h));
	//rect0_Presets.set(ofRectangle(x, y, w, h));

	//--

	rectangles_Windows.clear();
	rectangles_Windows.emplace_back(rect0_Presets);
	rectangles_Windows.emplace_back(rect1_Panels);
	rectangles_Windows.emplace_back(rect2_Manager);

	// To store settings to disk

	params_RectPanels.clear();
	params_RectPanels.add(rect0_Presets);
	params_RectPanels.add(rect1_Panels);
	params_RectPanels.add(rect2_Manager);

	params_WindowsEngine.clear();
	params_WindowsEngine.add(params_RectPanels);

	//--

	// Presets and Panels Windows

	params_WindowPresets.add(bReset_PresetsWindow);
	params_WindowPresets.add(bAutoResize_PresetsWindows);
	params_WindowPresets.add(bMinimize_Presets);

	params_WindowPanels.add(bReset_WindowPanels);
	params_WindowPanels.add(bAutoResize_Panels);

	//params_WindowPresets.add(bMinimize_Panels);

	params_WindowsEngine.add(params_WindowPresets);
	params_WindowsEngine.add(params_WindowPanels);

	params_AppSettings.add(params_WindowsEngine);

	//----

	//TODO: Simplify calls merging to one group only...

	// Callbacks
	ofAddListener(params_LayoutPresetsStates.parameterChangedE(), this, &SurfingGuiManager::Changed_Params);

	//--

	//TODO:
	//// Gui - > which panels enabled but overwritten by Layout Presets Engine
	//params_AppSettings.add(params_WindowsPanels);

	//--

	setImGuiLayoutPresets(true);
}

//--------------------------------------------------------------
bool SurfingGuiManager::loadSettings() {
	ofLogNotice("ofxSurfingImGui") << "loadSettings()"
								   << " " << path_AppSettings;
	bool b = loadGroup(params_AppSettings, path_AppSettings, false);
	if (!b) ofLogWarning("ofxSurfingImGui") << "Not found " << path_AppSettings;

	return b;

	// Will return false if settings file do not exist.
	// That happens when started for first time or after OF_APP/bin cleaning
}

//--------------------------------------------------------------
void SurfingGuiManager::saveSettingsInternal() {
	if (bFlagResetUIProgramed) return;
	// Respect not saving settings on exit.
	// Then next startup will have default settings

	ofLogNotice("ofxSurfingImGui") << "saveSettingsInternal()"
								   << " " << path_AppSettings;
	saveGroup(params_AppSettings, path_AppSettings, false);
}

//--------------------------------------------------------------
void SurfingGuiManager::saveSettings() {
	if (bFlagResetUIProgramed) return;
	// Respect not saving settings on exit.
	// Then next startup will have default settings

	ofLogNotice("ofxSurfingImGui") << "saveAppSettings()";

	// Save GuiManager
	this->saveSettingsInternal();

	// Save WindowsOrganizer
#ifndef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES_USING_LISTENER
	windowsOrganizer.saveSettings();
#endif
}

//--------------------------------------------------------------
void SurfingGuiManager::saveLayoutPresetIndex(int _index) {
	if (_index == -1) return;

	ini_to_save_Str = getLayoutName(_index);

	ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << " " << ini_to_save_Str;

	if (ini_to_save_Str == "-1") return; // skip

	// Flag to save .ini on update
	ini_to_save = ini_to_save_Str.c_str();

	// Save group
	saveLayoutPresetGroup(ini_to_save);
}

//--------------------------------------------------------------
void SurfingGuiManager::loadLayoutPresetIndex(int _index) {
	if (_index == -1) return;

	//if (appLayoutIndex == _index) return; // skip

	appLayoutIndex = ofClamp(_index, appLayoutIndex.getMin(), appLayoutIndex.getMax());

	string _name = getLayoutName(appLayoutIndex.get());
	ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << " " << appLayoutIndex << ":" << _name;

	//string _label = APP_RELEASE_NAME;
	string _label = "";
	_label += "App Layout ";
	_label += " "; // spacing

	if (!bLayoutPresets[appLayoutIndex.get()]) {
		for (int i = 0; i < bLayoutPresets.size(); i++) {
			bLayoutPresets[i].set(false);
		}
		bLayoutPresets[_index].set(true);
	}

	// ini
	ini_to_load_Str = _name;
	ini_to_load = ini_to_load_Str.c_str();

	// Group
	loadLayoutPresetGroup(ini_to_load_Str);

	ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << " ------------------------------------";
	ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << " ini_to_load    : " << ini_to_load;
}

//--------------------------------------------------------------
void SurfingGuiManager::drawLayoutsLayoutPresets() // That's the window tittled as "Layout"
{
	flags_wPr = ImGuiWindowFlags_None;
	flags_wPr += ImGuiWindowFlags_NoSavedSettings;

	if (bAutoResize_PresetsWindows) flags_wPr += ImGuiWindowFlags_AlwaysAutoResize;

	//--

	/*
	//// Viewport Center
	////
	//// is excluded from .ini
	//float xw, yw, ww, hw;
	//{
	//	if (bModeForced)
	//	{
	//		// Forced inside a free viewport
	//		//// Upper left
	//		//glm::vec2 p = rectangleCentralMAX.getTopLeft() + glm::vec2(-1, -1);
	//		// Center upper left
	//		int _pad = 10;
	//		int _xx = rectangleCentralMAX.getTopLeft().x + _pad;
	//		int _yy = rectangleCentralMAX.getTopLeft().y + rectangleCentralMAX.getHeight() / 2 - hw / 2;
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

	//--

	// Reset trigger

	ImGuiCond prCond = ImGuiCond_None;
	prCond += ImGuiCond_Appearing;

	if (bReset_PresetsWindow) {
		bReset_PresetsWindow = false;

		const int i = 0;
		ofRectangle r = rectangles_Windows[i];
		r.setWidth(100);
		r.setHeight(100);
		rectangles_Windows[i].set(r);
		prCond = ImGuiCond_Always;

		// workflow
		bAutoResize_PresetsWindows = true;
		bMinimize_Presets = true;
		bGui_LayoutsManager = false;
	}

	//----

	// Position and size the window

	if (bGui_LayoutsPresetsSelector) {
		const int i = 0;
		ImGui::SetNextWindowPos(ImVec2(rectangles_Windows[i].get().getX(), rectangles_Windows[i].get().getY()), prCond);
		ImGui::SetNextWindowSize(
			ImVec2(rectangles_Windows[i].get().getWidth(), rectangles_Windows[i].get().getHeight()), prCond);
	}

	//--

	// Window

	if (bGui_LayoutsPresetsSelector) {
		//IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MINI;
		//IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;
		float w = 180;
		ImVec2 size_min = ImVec2(w, -1);
		ImVec2 size_max = ImVec2(w, -1);
		ImGui::SetNextWindowSizeConstraints(size_min, size_max);
	}

	if (this->BeginWindow(bGui_LayoutsPresetsSelector, flags_wPr)) {
		float _h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
		float _w1 = ofxImGuiSurfing::getWidgetsWidth(1);
		float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);
		float _w = _w2;

		//--

		const int i = 0;
		rectangles_Windows[i].setWithoutEventNotifications(ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
			ImGui::GetWindowWidth(),
			ImGui::GetWindowHeight()));

		//--

		// 1. Minimize (global)

		this->Add(bMinimize_Presets, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);
		this->AddSpacingSeparated();

		//--

		// Panels

		//ofxImGuiSurfing::AddBigToggle(bGui_LayoutsPanels, _w1, (bMinimize_Presets ? _h * 0.75f : _h)); // variable size
		ofxImGuiSurfing::AddBigToggle(bGui_LayoutsPanels, _w1, _h); // fixed size
		this->AddTooltip("F6");

		// Manager

		//if (!bMinimize_Presets) ofxImGuiSurfing::AddBigToggle(bGui_LayoutsManager, _w1, (bMinimize_Presets ? _h / 2 : _h));
		if (!bMinimize_Presets) {
			this->AddSpacing();
			this->Add(bGui_LayoutsManager, OFX_IM_TOGGLE_ROUNDED);
			this->AddTooltip("F7");
		}

		this->AddSpacingSeparated();

		//--

		// 2. The 4 Preset Toggles

		// label
		if (!bMinimize_Presets) {
			this->AddLabelBig("PRESETS");
			this->AddSpacing();
		}

		// toggles
		for (int i = 0; i < bLayoutPresets.size(); i++) {
			ofxImGuiSurfing::AddBigToggle(bLayoutPresets[i], _w2, _h);

			string s = "F" + ofToString(i + 1);
			this->AddTooltip(s);

			if (i % 2 == 0) ImGui::SameLine(); //two toggles per row
		}

		//--

		// 3. Save / Load

		if (!bMinimize_Presets) {
			this->AddSpacingSeparated();

			// Auto save

			ofxImGuiSurfing::AddBigToggle(bAutoSave_Layout, _w1, 0.5 * _h, true);

			// Save Button

			if (!bAutoSave_Layout.get()) {
				ImGui::PushID("##SaveLayout");
				if (ImGui::Button("Save", ImVec2(_w1, 0.5 * _h))) {
					saveLayoutPresetIndex(appLayoutIndex.get());
				}
				ImGui::PopID();
			}

			this->AddSpacing();

			//--

			// Manual

			drawLayoutsPresetsManualWidgets();

			this->AddSpacingSeparated();
			this->AddSpacing();
		}

		//--

		if (!bMinimize_Presets) //maximized
		{
			// Organizer panel visible toggle

			this->Add(bGui_Organizer, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
			this->AddSpacing();

			// Link mode toggle

			this->Add(this->getGuiToggleLinked());
		}

		//--

		if (!bMinimize_Presets) {
			// Extra Params

			// when is minimized or manager window hidden
			if (bMinimize_Presets || !bGui_LayoutsManager) {
				this->AddSpacingSeparated();
				this->AddGroup(params_LayoutsExtra, SurfingGuiGroupStyle_Collapsed);
			}
		}

		this->EndWindow();
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::drawLayoutsPresetsManualWidgets() {
	bool bMin = false; // hide load buttons to simplify
	float max = (bMin ? 150 : 175);

	//----

	{
		float _h = ofxImGuiSurfing::getWidgetsHeightUnit();
		float _w1 = ofxImGuiSurfing::getWidgetsWidth(1);
		float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);

		//--

		if (!bMinimize_Presets) {
			if (ImGui::CollapsingHeader("Manual", ImGuiWindowFlags_None)) {
				ImVec2 bb { (bMin ? _w1 : _w2), _h };

				//--

				int _id = 0;
				for (int i = 0; i < bLayoutPresets.size(); i++) {
					string _name = (bLayoutPresets[i].getName());

					ImGui::Text(_name.c_str());
					if (!bMin) {
						ImGui::PushID(_id++);
						if (ImGui::Button("Load", bb)) {
							appLayoutIndex = i;
						}
						ImGui::PopID();

						ImGui::SameLine();
					}

					ImGui::PushID(_id++);

					if (ImGui::Button("Save", bb)) {
						ini_to_save_Str = _name;
						ini_to_save = ini_to_save_Str.c_str();
					}

					ImGui::PopID();
				}

				//--

				this->AddSpacingSeparated();

				if (ImGui::Button("Reset", ImVec2(_w2, _h))) {
					//TODO: to trig an external function..
					if (bResetPtr != nullptr) {
						*bResetPtr = true;
					}

					// Toggle panels to true
					for (int i = 0; i < windows.size(); i++) {
						windows[i].bGui.set(true);
					}

					saveLayoutPresetIndex((appLayoutIndex.get()));
				}
				this->AddTooltip("Reset all the Presets");

				ImGui::SameLine();

				if (ImGui::Button("Clear", ImVec2(_w2, _h))) {
					doRemoveDataFiles();
				}
				this->AddTooltip("Clear all the Presets");
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
	}
}

//--------------------------------------------------------------
void SurfingGuiManager::Changed_WindowsPanels(ofAbstractParameter & e) {
	string name = e.getName();
	ofLogNotice("ofxSurfingImGui") << "Changed_WindowsPanels: " << name << ": " << e;

	doFlagBuildHelpInternalInfo();
}

//--------------------------------------------------------------
void SurfingGuiManager::Changed_Params(ofAbstractParameter & e) {
	string name = e.getName();

	bool bskip = true;
	if (name != "position" && name != log.amountLinesLimitedBuffered.getName() && //workaround
		name != "rect_Manager") {
		bskip = false;
		ofLogNotice("ofxSurfingImGui") << "Changed_Params: " << name << ": " << e;
	}
	if (bskip) return;

		//--

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES
	this->saveSettingsFlag();
#endif

	//--

	if (0) {
	}

	//--

	// Update Help Info

	// Help internal
	else if (name == bHelpInternal.getName() && bHelpInternal) {
		doFlagBuildHelpInternalInfo(); //recreate info
		return;
	}

	// Help App / global. To be handled externally
	else if (name == bHelp.getName()) {
		doFlagBuildHelpInternalInfo();
		return;
	}

	// Debug
	else if (name == bDebug.getName()) {
		doFlagBuildHelpInternalInfo();
		return;
	}

	// Extra
	else if (name == bExtra.getName()) {
		doFlagBuildHelpInternalInfo();
		return;
	}

	// Log
	else if (name == bLog.getName()) {
		doFlagBuildHelpInternalInfo();
		return;
	}

	// Notifier
	else if (name == bNotifier.getName()) {
		doFlagBuildHelpInternalInfo();
		return;
	}

	// Solo
	else if (name == bSolo.getName()) {
		doFlagBuildHelpInternalInfo();
		return;
	}

	// Keys
	else if (name == bKeys.getName()) {
		doFlagBuildHelpInternalInfo();
		return;
	}

	// Minimize
	else if (name == bMinimize.getName()) {
		doFlagBuildHelpInternalInfo();
		return;
	}

	// Theme
	else if (name == bThemeUIAlt.getName()) {
		setupImGuiTheme();
		return;
	}

	//else if (name == bMinimize_Presets.getName())
	//{
	//	doFlagBuildHelpInternalInfo();
	//}

	//--

	// Global Scale
	else if (name == globalScale.getName()) {
		return;
	}

	//----

	// Layout Presets Engine

	//TODO:
	// Skip below callbacks
	// when not using the Layout Presets Engine!
	// to improve the performance a bit
	// by skipping the not required callbacks.
	if (surfingImGuiMode != ofxImGuiSurfing::IM_GUI_MODE_INSTANTIATED_DOCKING)
		if (!bDockingLayoutPresetsEngine) return;

	//--

	if (0) {
	}

	// Gui layout
	else if (name == bGui_LayoutsPresetsSelector.getName()) {
		return;
	}

	//--

	// Reset
	// This toggle/flag is "sent" to the parent scope (ofApp), to resets something in our apps.
	// Example: to resets the layout.
	// That pointer must be created externally!
	else if (name == bReset.getName() && bReset.get()) {
		bReset = false;

		if (bResetPtr != nullptr) {
			*bResetPtr = true;
		}
		return;
	}

	else if (name == bReset_Window.getName() && bReset_Window.get()) {
		bReset_Window = false;
		return;
	}

	//--

	// Solo Panel

	else if (name == bSolo.getName() && bSolo.get()) {
		// workflow
		appLayoutIndex = -1;

		// disable preset
		for (int i = 0; i < bLayoutPresets.size(); i++) {
			bLayoutPresets[i].setWithoutEventNotifications(false);
		}
		return;
	}

	//--

	// Layout preset index

	else if (name == appLayoutIndex.getName()) {
		//appLayoutIndex = ofClamp(appLayoutIndex.get(), appLayoutIndex.getMin(), appLayoutIndex.getMax());

		//if (appLayoutIndex != appLayoutIndex_PRE /*&& appLayoutIndex_PRE != -1*/)

		if (appLayoutIndex != appLayoutIndex_PRE) {
			ofLogNotice("ofxSurfingImGui") << "Changed: " << appLayoutIndex;

			//-

			// 1. Auto save

			if (bAutoSave_Layout) {
				// workaround:
				// must save here bc usually we use the fallged on update save...
				// only once per cycle allowed this way.
				// force to ensure save bc update chain load and save below
				//saveAppLayout(AppLayouts(appLayoutIndex_PRE));
				string __ini_to_save_Str = getLayoutName(appLayoutIndex_PRE);

				if (__ini_to_save_Str != "-1") {
					const char * _iniSave = NULL;
					_iniSave = __ini_to_save_Str.c_str(); // flags to save on update

					if (_iniSave != "-1") {
						saveLayoutPreset(_iniSave);
					}
				}
			}

			appLayoutIndex_PRE = appLayoutIndex.get();
		}

		//-

		// We get notified of special window toggles changes here!
		// not inside the WindowsOrganizer object!

		// 2. index preset selected is -1
		// Hide all panels

		if (appLayoutIndex == -1) // When no preset selected, puts all panels to false
		{
			for (int i = 0; i < windows.size(); i++) {
				if (windows[i].bGui)
					windows[i].bGui.set(false);
			}

			return; // not required bc loadAppLayout will be skipped when passed -1
		}

		//-

		// 2. Load layout
		loadLayoutPresetIndex(appLayoutIndex.get());

		return;
	}

	//--

	// Presets Selector
	// exclusive toggles
	// Solo behavior
	{
		bool bSomeTrue = false;

		// iterate each preset toggle
		for (int i = 0; i < bLayoutPresets.size(); i++) {
			// if that toggle changed
			if (name == bLayoutPresets[i].getName()) {
				// is changed to true
				if (bLayoutPresets[i].get()) {
					// workflow
					if (bSolo.get()) bSolo = false;

					appLayoutIndex = i;
					bSomeTrue = true;

					continue; // bc only one will be changed at once. no need to check the others.
				}

				// is changed to false
				else {
					// avoid all false
					bool bAllFalse = true;
					for (int i = 0; i < bLayoutPresets.size(); i++) {
						if (bLayoutPresets[i].get()) {
							bAllFalse = false;
						}
					}
					if (bAllFalse) {
						// workflow A
						////force back to true if it's there's no other enabled..
						//bLayoutPresets[appLayoutIndex].set(true);

						// workflow B
						//set to -1
						//appLayoutIndex = -1;

						//TODO:
						appLayoutIndex.set(-1);
						//appLayoutIndex.setWithoutEventNotifications(-1);
					}
				}
			}
		}

		if (bSomeTrue) {
			for (int i = 0; i < bLayoutPresets.size(); i++) {
				// the preset toggle that currently changed has been to true
				// put the other toggles to false
				if (i != appLayoutIndex.get()) {
					bLayoutPresets[i].set(false);
					//bLayoutPresets[i].setWithoutEventNotifications(false);
				}
			}
			return;
		}
	}

	//-

	//TODO: bug
	// fix

	// Solo Panels Selectors behavior

	if (bSolo.get()) {
		// iterate all panels
		// search for which one changed and to true
		for (int i = 0; i < windows.size(); i++) {
			// if that one has changed and it goes to true
			if (name == windows[i].bGui.getName() && windows[i].bGui) {
				// set the others to false and return
				for (int k = 0; k < windows.size(); k++) {
					// i is the index of the panel toggle that just changed
					if (k != i) //put the others to false
					{
						if (windows[k].bGui)
							windows[k].bGui.set(false);
					}
				}
				return;
			}
		}
	}

	//--

	//TODO:
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
void SurfingGuiManager::saveLayoutPreset(string path) {
	saveLayoutImGuiIni(path);
	saveLayoutPresetGroup(path);
}

//--------------------------------------------------------------
void SurfingGuiManager::loadLayoutPreset(string path) {
	loadLayoutImGuiIni(ini_to_load);
	loadLayoutPresetGroup(path);
}

//--------------------------------------------------------------
void SurfingGuiManager::saveLayoutImGuiIni(string path) {
	ImGui::SaveIniSettingsToDisk(ofToDataPath(path_LayoutsImGui + path + ".ini", true).c_str());
}

//--------------------------------------------------------------
void SurfingGuiManager::loadLayoutImGuiIni(string path) {
	ImGui::LoadIniSettingsFromDisk(ofToDataPath(path_LayoutsImGui + path + ".ini", true).c_str());
}

//--------------------------------------------------------------
void SurfingGuiManager::saveLayoutPresetGroup(string path) {
	saveGroup(params_Layouts, path_LayoutsImGui + path + ".json");
}

//--------------------------------------------------------------
void SurfingGuiManager::loadLayoutPresetGroup(string path) {
	loadGroup(params_Layouts, path_LayoutsImGui + path + ".json");
}

//----

//--------------------------------------------------------------
void SurfingGuiManager::createLayoutPreset(string namePreset) {
	string n;
	//int i = bLayoutPresets.size();
	int i = bLayoutPresets.size() + 1;

	if (namePreset == "-1")
		n = "P" + ofToString(i);
	else
		n = namePreset;

	ofParameter<bool> _b = ofParameter<bool> { n, false };
	bLayoutPresets.push_back(_b);
	appLayoutIndex.setMax(bLayoutPresets.size() - 1);
	params_LayoutPresetsStates.add(bLayoutPresets[i - 1]);
	//params_LayoutPresetsStates.add(bLayoutPresets[i]);
}

//----

//--------------------------------------------------------------
void SurfingGuiManager::drawLayoutsPanels() {
	flags_wPanels = ImGuiWindowFlags_None;
	flags_wPanels += ImGuiWindowFlags_NoSavedSettings;

	if (bAutoResize_Panels) flags_wPanels += ImGuiWindowFlags_AlwaysAutoResize;

	//--

	// Used to read the window shape below
	// that's done to re arrange the toggles distribution with a responsive behavior.
	static bool _bLandscape = false;

	// Docking mode ignores these constraints... ?

#ifdef OFX_IMGUI_CONSTRAIT_WINDOW_SHAPE

	// Notice that _bLandscape on first frame is not updated!

	const int NUM_WIDGETS = windows.size(); // expected num widgets
	float ww = 450;
	float hh = 300;

	// set variable sizes to make all the text visible! (specially all/none) 
	if (NUM_WIDGETS > 5) {
		ww = 600 + 200;
		hh = 450;
	} else if (NUM_WIDGETS > 4) {
		ww = 600 + 100;
		hh = 450;
	} else if (NUM_WIDGETS > 3) {
		ww = 600;
		hh = 450;
	}

	// Landscape
	if (_bLandscape)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, 100));
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(450, 100));
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(700, 150));

	// Portrait
	else
		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(95, hh));
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(95, 300));
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(105, 300));

#endif

	//--

	// Reset window trigger

	ImGuiCond pnCond = ImGuiCond_None;
	pnCond += ImGuiCond_Appearing;

	if (bReset_WindowPanels) {
		bReset_WindowPanels = false;

		const int i = 1;
		ofRectangle r = rectangles_Windows[i];
		r.setWidth(150);
		r.setHeight(150);
		rectangles_Windows[i].set(r);
		pnCond = ImGuiCond_Always;
	}

	//-

	// Position and Shape

	const int i = 1;

	if (bGui_LayoutsPanels) {
		ImGui::SetNextWindowPos(ofVec2f(rectangles_Windows[i].get().getX(),
									rectangles_Windows[i].get().getY()),
			pnCond);
		ImGui::SetNextWindowSize(ofVec2f(rectangles_Windows[i].get().getWidth(),
									 rectangles_Windows[i].get().getHeight()),
			pnCond);
	}

	//-

	// Draw window

	if (this->BeginWindow(bGui_LayoutsPanels, flags_wPanels))
	{
		const int i = 1;
		rectangles_Windows[i].setWithoutEventNotifications(ofRectangle(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
			ImGui::GetWindowWidth(),
			ImGui::GetWindowHeight()));

		_bLandscape = false;
		float __w = ImGui::GetWindowWidth();
		float __h = ImGui::GetWindowHeight();
		if (__w > __h) _bLandscape = true;

		//-

		const int NUM_WIDGETS = windows.size(); // expected num widgets
		const int NUM_WIDGETS_EXTRA_LANDSCAPE = 5;
		//const int NUM_WIDGETS_EXTRA_LANDSCAPE = 6; // with autoresize

		float _spcx = ImGui::GetStyle().ItemSpacing.x;
		float _spcy = ImGui::GetStyle().ItemSpacing.y;
		float _h100 = ImGui::GetContentRegionAvail().y;

		float _w;
		float _h;
		float _hWid;

		//-

		// A. Landscape

		if (_bLandscape) {
			//_w = ofxImGuiSurfing::getWidgetsWidth(NUM_WIDGETS + 2);
			const int amntColumns = NUM_WIDGETS + 2;
			float __w100 = ImGui::GetContentRegionAvail().x - (3 * _spcx);
			// remove extra columns x spacing added!
			_w = (__w100 - _spcx * (amntColumns - 1)) / amntColumns;

			_h = _h100 - _spcy;
			_hWid = (_h - _spcy) / 2;
			//_hWid = (_h - _spcy) / 3; // with autoResize
		}

		//-

		// B. Portrait

		else {
			_hWid = ofxImGuiSurfing::getWidgetsHeightRelative();
			float _hTotal = _h100 - (_hWid * NUM_WIDGETS_EXTRA_LANDSCAPE + (NUM_WIDGETS_EXTRA_LANDSCAPE + 1) * _spcy);
			_w = ofxImGuiSurfing::getWidgetsWidth();
			_h = _hTotal / NUM_WIDGETS - _spcy;
		}

		//-

		// Landscape

		if (_bLandscape) {
			ImGui::Columns(3, "", false);
			//ImGui::Columns(3);
			ImGui::SetColumnWidth(0, _spcx + (_w + _spcx) * NUM_WIDGETS);
		}

		//-

		// 1. Panels big toggles
		// Populate all windows (aka panels)

		for (int i = 0; i < windows.size(); i++) {
			ofxImGuiSurfing::AddBigToggle(windows[i].bGui, _w, _h);
			if (_bLandscape) ImGui::SameLine();
		}

		//-

		float _w100;
		float _w50;

		// Landscape
		if (_bLandscape) {
			ImGui::SameLine();
			_w100 = _w;
			_w50 = (_w - _spcx) / 2.0f;
		}

		// Portrait
		else {
			//this->AddSpacing();
			this->AddSeparator();
			this->AddSpacing();

			_w100 = ofxImGuiSurfing::getWidgetsWidth(1);
			_w50 = ofxImGuiSurfing::getWidgetsWidth(2);
		}

		//-

		// Landscape
		if (_bLandscape) {
			ImGui::NextColumn();
			ImGui::SetColumnWidth(1, _w100 + 2 * _spcx);
		}

		//--

		// 2. More extra widgets

		// all
		if (ImGui::Button("All", ImVec2(_w50, _hWid))) {
			// workflow
			if (bSolo) bSolo.set(false);

			bool b = true;
			this->setShowAllPanels(b);
		}

		ImGui::SameLine();

		// none
		if (ImGui::Button("None", ImVec2(_w50, _hWid))) {
			bool b = false;
			this->setShowAllPanels(b);
		}

		// solo
		ofxImGuiSurfing::AddBigToggle(bSolo, _w100, _hWid, true, true);

		//--

		// 3. Panels Toggles

		// Landscape
		if (_bLandscape) {
			ImGui::NextColumn();
			ImGui::SetColumnWidth(2, _w100 + _spcx + _spcx);
		}

		// Portrait
		else {
			//this->AddSpacing();
			this->AddSeparator();
			this->AddSpacing();
		}

		//-

		// Layout

		float _hUnit = ofxImGuiSurfing::getWidgetsHeightRelative();

		ofxImGuiSurfing::AddBigToggle(bGui_LayoutsPresetsSelector, _w100,
			(bMinimize_Presets ? ofxImGuiSurfing::getPanelHeight() : _hWid), false);
		this->AddTooltip("F5");

		if (!bMinimize_Presets) {
			ofxImGuiSurfing::AddBigToggle(bGui_LayoutsManager, _w100, _hWid, false);
			this->AddTooltip("F7");
		}

		//--

		// Landscape

		if (_bLandscape) {
			ImGui::Columns();
		}

		//--

		//TODO
		// weird layout fixes for looped resizing..
		if (bAutoResize_Panels) {
			this->AddSpacing();
			this->AddSpacing();
			this->AddSpacing();
		}

		this->EndWindow();
	}

	//-

#ifdef OFX_IMGUI_CONSTRAIT_WINDOW_SHAPE
	ImGui::PopStyleVar();
#endif
}

//--

// Keys
//--------------------------------------------------------------
void SurfingGuiManager::keyPressed(ofKeyEventArgs & eventArgs) {
	if (!bKeys || this->bOverInputText) return;

	const int & key = eventArgs.key; //OF_KEY_*
	const int & keycode = eventArgs.keycode; //GLFW_KEY_*
	// Note: when keystrokes like Ctrtl+0,
	// we need to use keycode instead of 0 to know if '0; is pressed.

	//const int& scancode = eventArgs.scancode;//OS/hardware
	//const uint32_t& codepoint = eventArgs.codepoint;//Unicode

	// Modifiers
	bool _bMod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool _bMod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool _bMod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool _bMod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	if (!_bMod_CONTROL && !_bMod_COMMAND && _bMod_ALT && _bMod_SHIFT)
		ofLogNotice("ofxSurfingImGui") << "keyPressed: " << (char)key;

	//--

	if (_bMod_CONTROL && !bMod_CONTROL) {
		bMod_CONTROL = true;
		ofLogNotice("ofxSurfingImGui") << "CONTROL " << (bMod_CONTROL ? "ON" : "OFF");
		doFlagBuildHelpInternalInfo();
		return;
	}

	if (_bMod_COMMAND && !bMod_COMMAND) {
		bMod_COMMAND = true;
		ofLogNotice("ofxSurfingImGui") << "COMMAND " << (bMod_COMMAND ? "ON" : "OFF");
		doFlagBuildHelpInternalInfo();
		return;
	}

	if (_bMod_ALT && !bMod_ALT) {
		bMod_ALT = true;
		ofLogNotice("ofxSurfingImGui") << "ALT " << (bMod_ALT ? "ON" : "OFF");
		doFlagBuildHelpInternalInfo();
		return;
	}

	if (_bMod_SHIFT && !bMod_SHIFT) {
		bMod_SHIFT = true;
		ofLogNotice("ofxSurfingImGui") << "SHIFT " << (bMod_SHIFT ? "ON" : "OFF");
		doFlagBuildHelpInternalInfo();
		return;
	}

	//----

	if (!bMod_CONTROL) {
		if (toggleParamByKey(key, 'H', bHelp, "H")) {
			doFlagBuildHelpInternalInfo();
			return;
		}
		if (toggleParamByKey(key, 'I', bHelpInternal, "I")) {
			doFlagBuildHelpInternalInfo();
			return;
		}
		if (toggleParamByKey(key, '`', bMinimize, "`")) {
			doFlagBuildHelpInternalInfo();
			return;
		}
		if (toggleParamByKey(key, 'E', bExtra, "E")) {
			doFlagBuildHelpInternalInfo();
			return;
		}
		if (toggleParamByKey(key, 'D', bDebug, "D")) {
			doFlagBuildHelpInternalInfo();
			return;
		}
		if (toggleParamByKey(key, 'L', bLog, "L")) {
			doFlagBuildHelpInternalInfo();
			return;
		}
		if (toggleParamByKey(key, 'N', bNotifier, "N")) {
			doFlagBuildHelpInternalInfo();
			return;
		}
	}

	//--

	// Layout Presets Engine

	//if (!bDockingLayoutPresetsEngine && !bUseLayoutPresetsManager) return; //skip is not enabled!

	//--

	//TODO: fix
	// CONTROL not pressed
	if (!bMod_CONTROL) {
		if (!bDockingLayoutPresetsEngine && !bUseLayoutPresetsManager) return; //skip is not enabled!

		switch (key) {
		case OF_KEY_F1:
			bLayoutPresets[0] = !bLayoutPresets[0];
			logKeyParamToggle(bLayoutPresets[0], "F1");
			doFlagBuildHelpInternalInfo();
			return;
			break;

		case OF_KEY_F2:
			bLayoutPresets[1] = !bLayoutPresets[1];
			logKeyParamToggle(bLayoutPresets[1], "F2");
			doFlagBuildHelpInternalInfo();
			return;
			break;

		case OF_KEY_F3:
			bLayoutPresets[2] = !bLayoutPresets[2];
			logKeyParamToggle(bLayoutPresets[2], "F3");
			doFlagBuildHelpInternalInfo();
			return;
			break;

		case OF_KEY_F4:
			bLayoutPresets[3] = !bLayoutPresets[3];
			logKeyParamToggle(bLayoutPresets[3], "F4");
			doFlagBuildHelpInternalInfo();
			return;
			break;
			//TODO: amount of presets is hard-coded
		}

		//--

		if (key == OF_KEY_F5) // Presets
		{
			bGui_LayoutsPresetsSelector = !bGui_LayoutsPresetsSelector;
			logKeyParamToggle(bGui_LayoutsPresetsSelector, "F5");
			doFlagBuildHelpInternalInfo();
			return;
		}

		else if (key == OF_KEY_F6) // Panels
		{
			bGui_LayoutsPanels = !bGui_LayoutsPanels;
			logKeyParamToggle(bGui_LayoutsPanels, "F6");
			doFlagBuildHelpInternalInfo();
			return;
		}

		else if (key == OF_KEY_F7) // Manager
		{
			bGui_LayoutsManager = !bGui_LayoutsManager;
			logKeyParamToggle(bGui_LayoutsManager, "F7");
			doFlagBuildHelpInternalInfo();
			return;
		}

		//else if (key == OF_KEY_F8) // Tools
		//{
		//	bGui_LayoutsPresetsManual = !bGui_LayoutsPresetsManual;
		//}
	}

	// CONTROL pressed
	else {
		// Special Windows

		string s = "";

		if (toggleParamByKey(keycode, '0', bGui_ShowWindowsGlobal, "Ctrl+0")) {
			//doFlagBuildHelpInternalInfo();
			return;
		}

		if (key >= OF_KEY_F1 && key <= OF_KEY_F11) {
			switch (key) {
				//--

				// All special windows

			case OF_KEY_F1:
				if (getWindowsSpecialsSize() > 0) {
					doSpecialWindowToggleVisible(0);
					s = tagModKey + string("+F1");
					logKeyParamToggle(key, getWindowSpecialGuiToggle(0), s);
					return;
				}
				break;

				//TODO: simplify by using a for loop

			case OF_KEY_F2:
				if (getWindowsSpecialsSize() > 1) {
					doSpecialWindowToggleVisible(1);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(1), "Ctrl+F2");
					return;
				}
				break;

			case OF_KEY_F3:
				if (getWindowsSpecialsSize() > 2) {
					doSpecialWindowToggleVisible(2);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(2), "Ctrl+F3");
					return;
				}
				break;

			case OF_KEY_F4:
				if (getWindowsSpecialsSize() > 3) {
					doSpecialWindowToggleVisible(3);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(3), "Ctrl+F4");
					return;
				}
				break;

			case OF_KEY_F5:
				if (getWindowsSpecialsSize() > 4) {
					doSpecialWindowToggleVisible(4);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(4), "Ctrl+F5");
					return;
				}
				break;

			case OF_KEY_F6:
				if (getWindowsSpecialsSize() > 5) {
					doSpecialWindowToggleVisible(5);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(5), "Ctrl+F6");
					return;
				}
				break;

			case OF_KEY_F7:
				if (getWindowsSpecialsSize() > 6) {
					doSpecialWindowToggleVisible(6);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(6), "Ctrl+F7");
					return;
				}
				break;

			case OF_KEY_F8:
				if (getWindowsSpecialsSize() > 7) {
					doSpecialWindowToggleVisible(7);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(7), "Ctrl+F8");
					return;
				}
				break;

			case OF_KEY_F9:
				if (getWindowsSpecialsSize() > 8) {
					doSpecialWindowToggleVisible(8);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(7), "Ctrl+F9");
					return;
				}
				break;

			case OF_KEY_F10:
				if (getWindowsSpecialsSize() > 9) {
					doSpecialWindowToggleVisible(9);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(7), "Ctrl+F10");
					doFlagBuildHelpInternalInfo();
					return;
				}
				break;

			case OF_KEY_F11:
				if (getWindowsSpecialsSize() > 10) {
					doSpecialWindowToggleVisible(10);
					logKeyParamToggle(key, getWindowSpecialGuiToggle(7), "Ctrl+F11");
					return;
				}
				break;

				//OF_KEY_F12 usually crashes OF
				//TODO: limited as is hardcoded!
			}
		}

		//--

		// Extra windows
		if (windowsExtra.size() > 0) {
			if (key >= OF_KEY_F1 && key <= OF_KEY_F11) {
				for (size_t i = 0; i < windowsExtra.size(); i++) {
					int k = int(OF_KEY_F1) + getWindowsSpecialsSize() + i;
					int z = getWindowsSpecialsSize() + i + 1;
					if (key == k) {
						s = tagModKey + "+F" + ofToString(z);
						toggleParamByKey(key, k, getWindowExtraGuiToggle(i), s);
						return;
					}
				}
			}
		}

		//--
	}

	//----

	//TODO: not working

	// Solo
	if ((key == 's' && bMod_CONTROL) || key == 19) {
		bSolo = !bSolo;
		logKeyParamToggle(bSolo, "Ctrl + s");
		doFlagBuildHelpInternalInfo();
		return;
	}

	//TODO: Bug: collides with some other keys like shift + drag docking...
	//// All
	//if ((key == 'a' && bMod_CONTROL) || key == 1)
	//{
	//	this->setShowAllPanels(true);
	//}

	// None
	//if ((key == 'n' && bMod_CONTROL) || key == 14)
	//{
	//	this->setShowAllPanels(false);
	//	logKeyText("Ctrl + n");
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

	//----

	//// Layout Modes

	//else if (key == OF_KEY_TAB && !bMod_CONTROL)
	//{
	//	if (appLayoutIndex > appLayoutIndex.getMin()) appLayoutIndex++;
	//	else if (appLayoutIndex == appLayoutIndex.getMin()) appLayoutIndex = appLayoutIndex.getMax();
	//	//if (appLayoutIndex < 3) loadAppLayout(AppLayouts(appLayoutIndex + 1));
	//	//else if (appLayoutIndex == 3) loadAppLayout(AppLayouts(0));
	//}

	doFlagBuildHelpInternalInfo();
}

//--------------------------------------------------------------
void SurfingGuiManager::keyReleased(ofKeyEventArgs & eventArgs) {
	if (!bKeys || this->bOverInputText) return;

	const int & key = eventArgs.key;

	// Modifiers
	bool _bMod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool _bMod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool _bMod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool _bMod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	if (!_bMod_CONTROL && bMod_CONTROL) {
		bMod_CONTROL = false;
		ofLogNotice("ofxSurfingImGui") << "CONTROL " << (bMod_CONTROL ? "ON" : "OFF");
		doFlagBuildHelpInternalInfo();
		return;
	}

	if (!_bMod_COMMAND && bMod_COMMAND) {
		bMod_COMMAND = false;
		ofLogNotice("ofxSurfingImGui") << "COMMAND " << (bMod_COMMAND ? "ON" : "OFF");
		doFlagBuildHelpInternalInfo();
		return;
	}

	if (!_bMod_ALT && bMod_ALT) {
		bMod_ALT = false;
		ofLogNotice("ofxSurfingImGui") << "ALT " << (bMod_ALT ? "ON" : "OFF");
		doFlagBuildHelpInternalInfo();
		return;
	}

	if (!_bMod_SHIFT && bMod_SHIFT) {
		bMod_SHIFT = false;
		ofLogNotice("ofxSurfingImGui") << "SHIFT " << (bMod_SHIFT ? "ON" : "OFF");
		doFlagBuildHelpInternalInfo();
		return;
	}

	ofLogNotice("ofxSurfingImGui") << "keyReleased: " << (char)key;
	doFlagBuildHelpInternalInfo();
}

//--

//--------------------------------------------------------------
void SurfingGuiManager::drawMenuDocked() {
	static bool opt_fullscreen = true;
	static bool * p_open = NULL;
	static bool opt_exit = false;

	//-

	// Menu bar

	// This is not operative. just for testing menus!

	if (ImGui::BeginMenuBar()) {
		if (BeginMenu("File")) {
			if (MenuItemButton("Load")) {
				//TODO
				// add referenced functions
				//loadSettingsProjectDialog();
			}
			string s = "Load Project.";
			AddTooltipBlink(s);

			if (MenuItemButton("Save")) {
				//saveSettingsProjectDialog();
			}
			s = "Save Project";
			AddTooltipBlink(s);

			if (ImGui::MenuItem("Save as..")) {
			}
			s = "Save Project as";
			AddTooltipBlink(s);

			//if (ImGui::MenuItem("Exit", NULL, &opt_exit))
			//{
			//	ofExit();
			//	//*opt_exit = false;
			//}

			// Exit.
			// Blink if hover
			static bool bExitHover = false;
			bool bExit = this->MenuItemButtonBlinkingWithKeystrokeInfo("Exit", "ESC", bExitHover);
			bExitHover = ImGui::IsItemHovered();
			if (bExit) {
				ofExit();
			}

			EndMenu();
		}

		//--

		if (BeginMenu("Edit")) {
			if (ImGui::MenuItem("Copy", NULL)) {
			}

			if (ImGui::MenuItem("Paste", NULL)) {
			}

			EndMenu();
		}

		//--

		// Layouts Engine

		//TODO
		if (surfingImGuiMode == IM_GUI_MODE_INSTANTIATED_DOCKING) {
			if (BeginMenu("Layouts")) {
				for (int i = 0; i < bLayoutPresets.size(); i++) {
					if (ImGui::MenuItem(bLayoutPresets[i].getName().c_str(), "", (bool *)&bLayoutPresets[i].get())) {
						bLayoutPresets[i] = bLayoutPresets[i]; // to trig
					}
				}
				//this->AddSpacingSeparated();
				//if (ImGui::MenuItem("All", NULL)) { this->setShowAllPanels(true); }
				//if (ImGui::MenuItem("None", NULL)) { this->setShowAllPanels(false); }

				EndMenu();
			}
		}

		//--

		/*

		//TODO
		//static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		if (surfingImGuiMode == IM_GUI_MODE_INSTANTIATED_DOCKING || surfingImGuiMode == IM_GUI_MODE_INSTANTIATED_DOCKING)
		{
			if (BeginMenu("Docking"))
			{
				if (ImGui::MenuItem("WARNING", ""))
				{
				}
				ofxImGuiSurfing::AddTooltip2(
					"Don't pay attention for this! \nThis is not operative here. \nJust for testing menus!\nPotential CRASH!");

				dockspace_flags = ImGui::GetIO().ConfigFlags;

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
				}
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
				}
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "",
					(dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				}
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				}
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "",
					(dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen))
				{
					dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
				}
				//if (ImGui::MenuItem("Flag: ConfigDockingWithShift", "", (dockspace_flags & ImGuiDockNodeFlags_) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				//this->AddSpacingSeparated();

				ImGui::GetIO().ConfigFlags = dockspace_flags;
				//ImGui::GetIO().ConfigDockingWithShift = true;

				EndMenu();
			}
		}
		*/

		//--

		//IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_LOCKED_RESIZE;
		float w = 210;
		ImVec2 size_min = ImVec2(w, -1);
		ImVec2 size_max = ImVec2(w, -1);
		ImGui::SetNextWindowSizeConstraints(size_min, size_max);
		if (BeginMenuBlink("Windows", bMod_CONTROL)) {
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ofWindowMode windowMode = ofGetCurrentWindow()->getWindowMode();
			if (windowMode == OF_WINDOW)
				opt_fullscreen = false;
			else if (windowMode == OF_FULLSCREEN)
				opt_fullscreen = true;
			else if (windowMode == OF_GAME_MODE)
				opt_fullscreen = false;

			if (ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen)) {
				ofSetFullscreen(opt_fullscreen);
			}

			//TODO
			if (ImGui::MenuItem("Reset Window")) {
				SurfingGui::setWindowShape(-1); //left monitor
				//SurfingGui::setWindowShape(1, true);//right monitor portrait
			}

			this->AddSpacingSeparated();

			//--

			// Show global

			//TODO
			string tagMod = tagModKey + "+";

			bool b = bGui_ShowWindowsGlobal.get(); // Catch before to avoid crash when modifying.
			if (!b) BeginBlinkText();
			string n = bGui_ShowWindowsGlobal.getName();
			MenuItemToggleWithKeystrokeInfo(bGui_ShowWindowsGlobal, tagMod + "0");
			string s = "Momentary Show/Hide \nall Windows.";
			AddTooltip(s);
			if (!b) EndBlinkText();

			if (bGui_ShowWindowsGlobal) {
				Indent();

				static ofParameter<bool> bAllWindowsAreVisible { "All", false };

				bAllWindowsAreVisible = getAllWindowsSpecialAreVisible();

				if (MenuItemToggle(bAllWindowsAreVisible)) {
					setShowAllWindowsSpecial(true);
				}
				s = "Show all Windows.";
				AddTooltip(s);

				if (MenuItemButton("None")) {
					setShowAllWindowsSpecial(false);
				}
				s = "Hide all Windows.";
				AddTooltip(s);

				Unindent();
			}

			if (b) // Show Global
			{
				AddSpacingSeparated();

				for (size_t i = 0; i < getWindowsSpecialsSize(); i++) {
					string s = tagMod + "F" + ofToString(i + 1);
					MenuItemToggleWithKeystrokeInfo(getWindowSpecialGuiToggle(i), s);
				}
			}

			//--

			// Extra windows
			if (windowsExtra.size() > 0) {
				AddSpacingBigSeparated();

				//AddLabel("Extra Windows");
				//Indent();

				for (size_t i = 0; i < windowsExtra.size(); i++) {
					string s = tagMod + "F" + ofToString(i + 1 + getWindowsSpecialsSize());

					MenuItemToggleWithKeystrokeInfo(getWindowExtraGuiToggle(i), s);
				}

				//Unindent();
			}

			//--

			// Log and Notifier

			AddSpacingBigSeparated();

			MenuItemToggleWithKeystrokeInfo(bLog, "L");
			s = "Show Log Window.";
			AddTooltip(s);

			MenuItemToggleWithKeystrokeInfo(bNotifier, "N");
			s = "Show Notifier Messages.";
			AddTooltip(s);

			if (this->isHelpAppEnable()) {
				MenuItemToggleWithKeystrokeInfo(bHelp, "H");
				s = "Help App";
				AddTooltip(s);
			}

			if (this->isHelpInternalEnabled()) {
				MenuItemToggleWithKeystrokeInfo(bHelpInternal, "I");
				s = "Help Internal";
				AddTooltip(s);
			}

			EndMenu();
		}

		//--

		if (BeginMenu("About")) {
			string s = "WARNING !\n\nDON'T PAY ATTENTION FOR THIS TEXT! \NTHIS IS NOT OPERATIVE HERE. \NJUST FOR TESTING MENUS!"
					   "\n\n"
					   "When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!"
					   "\n"
					   "- Drag from window title bar or their tab to dock/undock."
					   "\n"
					   "- Drag from window menu button (upper-left button) to undock an entire node (all windows)."
					   "\n"
					   "- Hold SHIFT to enable dragging docking."
					   "\n"
					   "This demo app has nothing to do with it!"
					   "\n\n"
					   "This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)."
					   "\n\n"
					   "ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame."
					   "\n\n"
					   "(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)";

			AddTooltipHelp(s);

			EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

//--

//TODO
/*
//--------------------------------------------------------------
void SurfingGuiManager::drawMenu()
{
	static bool opt_fullscreen = 0;
	static bool* p_open = NULL;
	static bool opt_exit = false;

	//-

	// Menu bar

	// This is not operative. just for testing menus!
	ImGui::BeginMainMenuBar();

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

			this->AddSpacingSeparated();


			// Exit. Blink if hover
			static bool bExitHover = false;
			bool bExit = this->MenuItemButtonBlinkingWithKeystrokeInfo("Exit", "ESC", bExitHover);
			bExitHover = ImGui::IsItemHovered();
			if (bExit)
			{
				ofExit();
			}

			//if (ImGui::MenuItem("Exit", NULL, &opt_exit))
			//{
			//	ofExit();
			//	//*opt_exit = false;
			//}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Copy", NULL))
			{
			}
			if (ImGui::MenuItem("Paste", NULL))
			{
			}

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
				"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)."
				"\n\n"
				"ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame."
				"\n\n"
				"(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)"
			);

			ImGui::EndMenu();
		}
	}

	ImGui::EndMainMenuBar();

}
*/

//--

//--------------------------------------------------------------
void SurfingGuiManager::doResetLayout() {
	ofLogNotice("ofxSurfingImGui") << "Reset layout of windows.";

	windowsOrganizer.doAlignWindowsReset();

	ofLogNotice("ofxSurfingImGui") << "The more lefted window is named: " << windowsOrganizer.getWindowMoreLefted();
}

//----

/*
//TODO:
//--------------------------------------------------------------
void SurfingGuiManager::drawSpecialWindowsPanel()
{
	if (ImGui::TreeNode("Special Windows"))
	{
		//ImGui::Text("Special Windows");

		//ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		//if (bAutoResize_Panels) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		//if (this->BeginWindow("Specials", NULL, window_flags))
		{
			const int NUM_WIDGETS = windows.size(); // expected num widgets

			float _spcx = ImGui::GetStyle().ItemSpacing.x;
			float _spcy = ImGui::GetStyle().ItemSpacing.y;
			//float _h100 = ImGui::GetContentRegionAvail().y;

			// 1. populate all toggles

			const int _amnt = 1;

			float _w = ofxImGuiSurfing::getWidgetsWidth(_amnt);
			float _h = 1 * ofxImGuiSurfing::getWidgetsHeightRelative();
			//float _w = ofxImGuiSurfing::getWidgetsWidth(windows.size());

			for (int i = 0; i < NUM_WIDGETS; i++)
			{
				if (i > windows.size() - 1) continue;

				ofxImGuiSurfing::AddBigToggle(windows[i].bGui, _w, _h);

				//if ((i + 1) % _amnt != 0 && i < NUM_WIDGETS - 1) ImGui::SameLine();
			}
		}

		ImGui::TreePop();
	}
}*/

//--

// Special behavior to control windows

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
