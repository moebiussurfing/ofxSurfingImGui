
/*

	WIP

	This is a helper to:
	- Edit/test themes.
	- Save themes to allow loading on your apps.
	TODO:
	- Loading font files to check and tweak styles.
	- Add fonts tester.

	TODO

	add dual theme day/night.
	add rename theme.
	add make new ImGui_ThemeMoebiusSurfingV3
		dark theme with more 3d styled look.
		pressed toggle = darker.
	define a global accent color
		and some main colors.
		link colors between particular settings.
		but darker or lighter / transparent.
		ex: mark what color must be linked.
			each one has his own alpha.
		//https://github.com/ocornut/imgui/issues/438
		SetupStyleFromHue() / ofxImGui::DefaultTheme
	undo history or snapshot points
		using ofParams and an addon for presets.

*/


//--

#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

namespace ofxSurfingHelpers = ofxImGuiSurfing;//fix for removing ofxSurfingHelpers dependency

// ImGui Theme serializer
// Taken from: https://github.com/pegvin/ImGooeyStyles
#include "imgui_styles.h"

#include "surfingThemesHelpers.h"
#include "surfingFiles.h"

/*
	// We can force load one of the bundled Themes:
	// Must be called after setup()
	// to overwrite the default loaded theme:
	//ImGui::StyleColorsLight();
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingBlue();
*/

//----

#if(1)
// Standalone 
/*
EXAMPLE
ofxImGuiSurfing::SurfingThemes::loadThemeFileByName("t22222.ini");
*/
namespace ofxImGuiSurfing
{
	namespace SurfingThemes
	{
		static string pathThemes = "";

		enum THEME_STYLE
		{
			THEME_NIGHT = 0,
			THEME_DAY
		};

		static THEME_STYLE themeStyle = THEME_NIGHT;

		inline bool loadThemeFileByName(string name) {
			ofLogNotice("ofxSurfingImGui::loadThemeFileByName") << name;
			string pathTheme = pathThemes + name;
			string p = ofToDataPath(pathTheme);
			ofLogNotice("ofxSurfingImGui::loadThemeFileByName") << "Load from " << p;
			ImGui::LoadStyleFrom(p.c_str());

			ofFile f;
			return f.doesFileExist(p);
		};

		inline bool loadThemeFile(string path, bool bAbsolute = false) {
			ofLogNotice("ofxSurfingImGui::loadThemeFile") << path << " bAbsolute:" << bAbsolute;
			string p;
			if (bAbsolute) p = path;
			else p = ofToDataPath(path);
			ofLogNotice("ofxSurfingImGui::loadThemeFile") << "Load from " << p;
			ImGui::LoadStyleFrom(p.c_str());

			ofFile f;
			return f.doesFileExist(p);
		};
	}
}
#endif

//--

class SurfingThemeEditor
{
public:
	ofParameterGroup params;

	ofParameter<bool> bGui;
	ofParameter<bool> bGui_DearImGuiStyleEditor;
	ofParameter<bool> bGui_ThemeManager;
	ofParameter<bool> bGui_DearImGuiDemo;
	ofParameter<bool> bGui_DemoWidgets;
	ofParameter<bool> bEnableColors;
	ofParameter<bool> bEnableLayout;
	ofParameter<bool> bClickerCombo;
	ofParameter<string> nameTheme;
	ofParameter<int> indexTheme;

	bool bWindowWidth = 0;
	bool bWindowScale = 0;
	bool bWindowConstraints = 1;
	ofParameter<float> windowWidth{ "Window Width", 200, 200, 400 };
	ofParameter<float> windowScale{ "Window Scale", 0.f, -1.f, 1.f };
	ofParameter<float> scaleGlobal{ "Global Scale", 0.f, -1.f, 1.f };

	SurfingThemeEditor()
	{
		//ofAddListener(ofEvents().keyPressed, this, &SurfingThemeEditor::keyPressed);
		ofAddListener(ofEvents().exit, this, &SurfingThemeEditor::exit);
	}

	~SurfingThemeEditor()
	{
		//ofRemoveListener(ofEvents().keyPressed, this, &SurfingThemeEditor::keyPressed);
		ofRemoveListener(ofEvents().exit, this, &SurfingThemeEditor::exit);
		ofRemoveListener(params.parameterChangedE(), this, &SurfingThemeEditor::Changed);
	}

	void setup()
	{
		bGui.set("Theme Editor", true);
		bGui_ThemeManager.set("Theme Manager", false);
		bGui_DemoWidgets.set("Demo Widgets", false);
		bGui_DearImGuiStyleEditor.set("DearImGui Style Editor", false);
		bGui_DearImGuiDemo.set("DearImGui Demo", false);

		bEnableColors.set("Colors", true);
		bEnableLayout.set("Layout", true);
		bClickerCombo.set("ClickerCombo", true);
		nameTheme.set("ThemeName", "");
		indexTheme.set("Theme", 0, 0, 0);

		files.setPathDirectory(pathThemes);
		indexTheme.makeReferenceTo(files.index);

		params.setName("SurfingThemeEditor");
		params.add(bGui);
		params.add(bGui_DearImGuiStyleEditor);
		params.add(bGui_ThemeManager);
		params.add(bGui_DemoWidgets);
		params.add(bGui_DearImGuiDemo);
		params.add(bEnableColors);
		params.add(bEnableLayout);
		params.add(nameTheme);
		params.add(indexTheme);
		params.add(bClickerCombo);
		params.add(windowScale);
		params.add(scaleGlobal);

		setPathGlobal(pathGlobal);

		pathThemes = pathGlobal + subPathThemes;
		ofxSurfingHelpers::CheckFolder(pathThemes);

		pathCompares = pathThemes + subPathCompare;
		ofxSurfingHelpers::CheckFolder(pathCompares);

		filename = nameTheme.get();
		pathTheme = pathThemes + filename;

		ofxImGuiSurfing::SurfingThemes::pathThemes = pathThemes;

		//--

		ofAddListener(params.parameterChangedE(), this, &SurfingThemeEditor::Changed);

		ofxSurfingHelpers::loadGroup(params, pathGlobal + params.getName() + ".json");
	}

public:
	void setPathGlobal(string path) {//call before setup
		pathGlobal = path;
		ofxSurfingHelpers::CheckFolder(pathGlobal);

		pathThemes = pathGlobal + subPathThemes;
		pathCompares = pathThemes + subPathCompare;

		ofxSurfingHelpers::CheckFolder(pathThemes);
		ofxSurfingHelpers::CheckFolder(pathCompares);
	}

private:
	string pathGlobal = "ThemeEditor/";

	string pathTheme = "";
	string pathThemes = "";
	string subPathThemes = "themes/";
	string pathCompares = "";
	string subPathCompare = "compare/";
	string filename = ""; // "imgui_styles.ini"

	SurfingFiles files;

	void Changed(ofAbstractParameter& e) {
		std::string name = e.getName();
		ofLogNotice("ofxSurfingImGui:SurfingThemeEditor") << "Changed: " << name << ": " << e;

		if (0) {}

		else if (name == indexTheme.getName())
		{
			if (files.getSize() == 0) return;

			nameTheme = files.getName(indexTheme);

			filename = nameTheme.get() + ".ini";
			pathThemes = pathGlobal + subPathThemes;
			pathTheme = pathThemes + filename;

			loadThemeFile(pathTheme);

			return;
		}

		else if (name == nameTheme.getName())
		{
			if (nameTheme.get() == "") return;

			filename = nameTheme.get() + ".ini";
			pathThemes = pathGlobal + subPathThemes;
			pathTheme = pathThemes + filename;

			return;
		}
	}

	void resetTheme() {
		ImGui::GetStyle() = ImGuiStyle();
	}

	void loadThemeHardcoded(int index) {
		ofxImGuiSurfing::setIndexThemeHardcoded(index);
	}

private:
	void exit(ofEventArgs& args) { exit(); };

	void exit() {
		ofxSurfingHelpers::saveGroup(params, pathGlobal + params.getName() + ".json");
	}

	void keyPressed(ofKeyEventArgs& eventArgs) {
		/*
		const int& key = eventArgs.key;
		ofLogVerbose("ofxSurfingImGui:SurfingThemeEditor") << "Key: " << (char)key;

		// Modifiers
		bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
		//bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
		//bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
		//bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

		if (0) {}

		else if (key == OF_KEY_LEFT)
		{
		}

		else if (key == OF_KEY_RIGHT)
		{
		}
		*/
	}

	//ofxSurfingImGui* ui = nullptr;
	SurfingGuiManager* ui = nullptr;

public:
	void setUiPtr(ofxSurfingGui* _ui) {
		ui = _ui;
	}

	//--

public:
	void drawDemoWidgets(SurfingGuiManager& ui)
	{
		//if (ui == nullptr) return;

		if (ImGui::Button("Reset")) {
			bWindowWidth = 0;
			bWindowScale = 0;
			bWindowConstraints = 1;
			windowWidth = 200;
			windowScale = 0;
			scaleGlobal = 0;
		}
		ImGui::Checkbox("WindowScale", &bWindowScale);
		if (bWindowScale) {
			if (ImGui::Button("R")) {
				windowScale = 0;
			}
			ui.SameLine();
			ui.Add(windowScale, OFX_IM_STEPPER);
			ui.Add(windowScale, OFX_IM_HSLIDER_MINI_NO_LABELS);
		}

		ImGui::Checkbox("WindowConstraints", &bWindowConstraints);
		ImGui::Checkbox("WindowWidth", &bWindowWidth);
		if (bWindowWidth) ui.Add(windowWidth, OFX_IM_HSLIDER_MINI);
		ui.Add(ui.bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);
		ui.AddSpacingBigSeparated();

		static ofParameter<float> v1{ "Value1", 0.5, 0, 1 };
		static ofParameter<float> v2{ "Value2", 0, -1, 1 };
		static ofParameter<int> n1{ "Number1", 4, 0, 8 };
		static ofParameter<int> n2{ "Number2", 0, -10, 10 };
		static int n3 = 0;
		static float v3 = 0;
		static ofParameter<int> i{ "Index", 2, 0, 3 };
		static std::vector<std::string> fileNames{ "ZERO", "ONE", "TWO", "THREE" };
		static bool bt = 0;

		ImVec2 sz1(ImGui::GetContentRegionAvail().x, 2 * ImGui::GetFrameHeight());
		ImVec2 sz2(ImGui::GetContentRegionAvail().x / 2 - ImGui::GetStyle().ItemSpacing.x, 2 * ImGui::GetFrameHeight());

		ui.AddLabelHugeXXL(bGui_DemoWidgets.getName());
		ui.AddLabelHuge("Theme Tester", true);
		ui.AddSpacingSeparated();
		ui.AddLabelBig("Surfing API");

		ui.AddButton("Button", sz1);
		ui.AddToggle("Toggle", bt, sz1);
		ui.Add(v1, OFX_IM_HSLIDER);
		ui.Add(v1, OFX_IM_KNOB_DOTKNOB, 2, true);
		ui.Add(v2, OFX_IM_KNOB_TICKKNOB, 2);
		ui.AddSpacingSeparated();
		ui.AddCombo(i, fileNames);
		ui.Add(i, OFX_IM_STEPPER);
		ui.AddSpacingSeparated();
		ofxImGuiSurfing::AddMatrixClicker(n1);
		ui.Add(n1);
		ui.Add(n2);

		// using cpp types instead of ofParameter's
		ui.AddLabelBig("ImGui RAW");
		ImGui::PushItemWidth(sz1.x);
		ImGui::SliderInt("Number3", &n3, 0, 5);
		ImGui::SliderFloat("Value3", &v3, -1, 1);
		ImGui::PopItemWidth();

		ImGui::Button("Button1");
		ui.SameLine();
		ImGui::Button("Button2");
	}

	void drawDemoWidgets()
	{
		if (ui == nullptr) return;
		if (!bGui_DemoWidgets) return;

		if (bWindowConstraints) {
			ImVec2 size_min = ImVec2(windowWidth.getMin(), -1);
			ImVec2 size_max = ImVec2(windowWidth.getMax(), -1);
			ImGui::SetNextWindowSizeConstraints(size_min, size_max);
		}

		if (bWindowWidth) {
			ImVec2 size = ImVec2(windowWidth, -1);
			ImGui::SetNextWindowSize(size, ImGuiCond_Always);
		}

		if (ui->BeginWindow(bGui_DemoWidgets))
		{
			if (bWindowScale) {
				float v = 1.f;
				if (windowScale.get() != 0.f) v = ofMap(windowScale, -1, 1, 0.4f, 4.f, true);
				ImGui::SetWindowFontScale(v);
			}
			else ImGui::SetWindowFontScale(1);

			drawDemoWidgets(*ui);

			ui->EndWindow();
		}
	}

	void draw()
	{
		if (!bGui) return; // "Theme Editor"
		if (ui == nullptr) return;

		//IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;
		ImVec2 size_min = ImVec2(150, -1);
		ImVec2 size_max = ImVec2(-1, -1);
		ImGui::SetNextWindowSizeConstraints(size_min, size_max);

		if (ui->BeginWindow(bGui))
		{
			//static bool bExpand = 0;
			//ui->AddToggle("Expand", bExpand, OFX_IM_TOGGLE_ROUNDED_MINI);
			//if (bExpand)
			{
				ui->AddLabelBig("Surfing\nThemeEditor");
				ui->AddSpacing();
				ui->Add(bGui_ThemeManager, OFX_IM_TOGGLE_ROUNDED);
				ui->Add(bGui_DemoWidgets, OFX_IM_TOGGLE_ROUNDED);
				ui->AddSpacingSeparated();
				ui->Add(bGui_DearImGuiStyleEditor, OFX_IM_TOGGLE_ROUNDED);
				ui->Add(bGui_DearImGuiDemo, OFX_IM_TOGGLE_ROUNDED);
				ui->AddSpacingSeparated();
				ui->Add(ui->bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);
			}
			//ui->AddSpacingBigSeparated();

			ui->EndWindow();
		}

		//--

		if (bGui_DemoWidgets) drawDemoWidgets();
		if (bGui_ThemeManager) drawThemeManager();
		if (bGui_DearImGuiStyleEditor) drawStyleEditor();
		if (bGui_DearImGuiDemo) drawDemoImGui();
	}

	//--

	void saveThemeFile(string path) {
		string p = ofToDataPath(path);
		ImGui::SaveStylesTo(p.c_str());
		ofLogNotice("ofxSurfingImGui") << "Save to " << path;

		files.refreshFiles();

		//workflow
		//set current
		ofFile f(path);
		indexTheme = files.getIndexForName(f.getBaseName());
	};

	void loadThemeFileByName(string name) {
		ofLogNotice("ofxSurfingImGui") << "Load named " << name;

		filename = name;
		pathTheme = pathThemes + filename;

		string p = ofToDataPath(pathTheme);
		ofLogNotice("ofxSurfingImGui") << "Load from " << p;
		ImGui::LoadStyleFrom(p.c_str());
	}

	void loadThemeFile(string path) {
		ofLogNotice("ofxSurfingImGui") << "Load from " << path;
		string p = ofToDataPath(path);
		ImGui::LoadStyleFrom(p.c_str());
	}

	void reloadThemeFile() {
		ofLogNotice("ofxSurfingImGui") << "Reload from " << pathTheme;
		string p = ofToDataPath(pathTheme);
		ImGui::LoadStyleFrom(p.c_str());
	}

	void deleteThemeFile() {
		ofLogNotice("ofxSurfingImGui") << "Delete from " << pathTheme;

		files.deleteThemeFile();

		////workflow
		////set current
		//ofFile f(pathTheme);
		//indexTheme = files.getIndexForName(f.getBaseName());
	}

	void copyThemeFile() {
		ofLogNotice("ofxSurfingImGui") << "Copy from " << pathTheme;
		string pFrom = pathTheme;

		filename = nameTheme.get() + "_.ini";
		pathThemes = pathGlobal + subPathThemes;
		pathTheme = pathThemes + filename;
		string pTo = pathTheme;

		ofFile f(pFrom);
		f.copyTo(pTo);

		files.refreshFiles();
		indexTheme++;

		//files.copyThemeFile();
	}

	//--

private:
	void drawStyleEditor()
	{
		if (!bGui_DearImGuiStyleEditor) return;
		if (ui == nullptr) return;

		if (ui->BeginWindow(bGui_DearImGuiStyleEditor)) {

			ImGuiStyle& style = ImGui::GetStyle();

			ImGui::ShowStyleEditor(&style);

			ui->EndWindow();
		}
	}

	void drawDemoImGui()
	{
		if (ui == nullptr) return;
		ImGui::ShowDemoWindow(NULL);
	}

public:
	void drawThemeManager()
	{
		if (ui == nullptr) return;
		if (!bGui_ThemeManager) return;

		IMGUI_SUGAR__WINDOWS_CONSTRAINTSW;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (1) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (ui->BeginWindow(bGui_ThemeManager, window_flags))
		{
			string s = "";

			string filenameA = pathCompares + "imgui_styles_A.ini";
			string pathA = ofToDataPath(filenameA);

			string filenameB = pathCompares + "imgui_styles_B.ini";
			string pathB = ofToDataPath(filenameB);

			bool bKeyCtrl = ImGui::GetIO().KeyCtrl;

			ImVec2 sz(ImGui::GetContentRegionAvail().x / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 1.5 * ImGui::GetFrameHeight());

			//--

			ui->AddLabelBig("Files Manager", true);

			ui->Add(nameTheme, OFX_IM_TEXT_INPUT);

			if (ImGui::Button("Load", sz)) {
				loadThemeFile(pathTheme);
			}
			ImGui::SameLine();
			if (ImGui::Button("Save", sz)) {
				saveThemeFile(pathTheme);
			}

			if (ImGui::Button("Reload##RETHEME")) {
				reloadThemeFile();
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete")) {
				deleteThemeFile();
			}
			ImGui::SameLine();
			if (ImGui::Button("Copy")) {
				copyThemeFile();
			}

			ui->AddSpacing();

			ui->Add(indexTheme, OFX_IM_HSLIDER_SMALL);
			s = "Loading files from:\n";
			s += pathThemes;
			ui->AddTooltipHelp(s);
			ImVec2 sz2 = ImVec2(ofxImGuiSurfing::getWidgetsWidth(2), 1.5 * ofxImGuiSurfing::getWidgetsHeightUnit());
			ofxImGuiSurfing::AddIndexArrows(indexTheme, sz2);

			ui->AddSpacing();
			ofxImGuiSurfing::AddToggleRoundedButtonNamed(bClickerCombo, "Clicker", "List");
			ui->AddSpacing();

			if (bClickerCombo) files.draw();
			else ui->AddCombo(indexTheme, files.getNames());

			ui->AddSpacingBigSeparated();

			//--

			ui->AddLabelBig("Hardcoded Themes", true);

			// arrows, hardcoded themes combo, fonts combo
			ofxImGuiSurfing::drawThemeHardcodedSelector(NULL);

			ui->AddSpacingBigSeparated();

			//--

			ui->Add(bEnableColors, OFX_IM_TOGGLE_BORDER_BLINK, 2, true);
			s = bEnableColors ? "Include Colors" : "Exclude Colors";
			ui->AddTooltip(s);

			ui->Add(bEnableLayout, OFX_IM_TOGGLE_BORDER_BLINK, 2);
			s = bEnableLayout ? "Include Layout" : "Exclude Layout";
			ui->AddTooltip(s);

			ofxImGuiSurfing::SurfingThemes::bEnableColors = bEnableColors;
			ofxImGuiSurfing::SurfingThemes::bEnableLayout = bEnableLayout;

			ofxImGuiSurfing::AddSpacingBigSeparated();

			ui->AddLabelBig("Compare", true);
			s = ofToString(bKeyCtrl ? "" : "Press Control to Save");
			ui->AddTooltip(s);

			if (ImGui::Button("A", sz)) {
				if (bKeyCtrl) ImGui::SaveStylesTo(pathA.c_str());
				else ImGui::LoadStyleFrom(pathA.c_str());
				ofLogNotice("ofxSurfingImGui") << (bKeyCtrl ? "Saved Config A" : "Loaded Config A");
			}
			s = ofToString(bKeyCtrl ? "Save A" : "Load A");
			ui->AddTooltip(s);

			ImGui::SameLine();

			if (ImGui::Button("B", sz)) {
				if (bKeyCtrl) ImGui::SaveStylesTo(pathB.c_str());
				else ImGui::LoadStyleFrom(pathB.c_str());
				ofLogNotice("ofxSurfingImGui") << (bKeyCtrl ? "Saved Config B" : "Loaded Config B");
			}
			s = ofToString(bKeyCtrl ? "Save B" : "Load B");
			ui->AddTooltip(s);
			s = "Press Control to Save,\n\n";
			s += "Loading files from:\n";
			s += "path A: " + filenameA + "\n";
			s += "path B: " + filenameB + "\n";
			ui->AddTooltipHelp(s);
			ofxImGuiSurfing::AddSpacingBigSeparated();

			size_t n = 6;
			float w = ui->getWidgetsWidth(n);
			float h = 1.5 * ImGui::GetFrameHeight();
			ImVec2 sz1(w, h);

			ui->AddLabelBig("Resets", true);

			if (ui->AddButton("R1", sz1))
			{
				resetTheme();
			}
			s = "Default ImGuiStyle";
			ui->AddTooltip(s);
			ui->SameLine();

			if (ui->AddButton("R2", sz1))
			{
				resetTheme();
				ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing(bEnableLayout, bEnableColors);
				//ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingBlue();
			}
			s = "ImGui_ThemeMoebiusSurfingV2";
			ui->AddTooltip(s);
			ui->SameLine();

			if (ui->AddButton("R3", sz1))
			{
				resetTheme();
				ofxImGui::DefaultTheme* defaultTheme = new ofxImGui::DefaultTheme();
				ui->getGuiPtr()->setTheme((ofxImGui::BaseTheme*)defaultTheme);
			}
			s = "ofxImGui::DefaultTheme";
			ui->AddTooltip(s);
			ui->SameLine();

			if (ui->AddButton("R4", sz1))
			{
				ImGui::StyleColorsDark();
			}
			s = "StyleColorsDark";
			ui->AddTooltip(s);
			ui->SameLine();

			if (ui->AddButton("R5", sz1))
			{
				ImGui::StyleColorsLight();
			}
			s = "StyleColorsLight";
			ui->AddTooltip(s);
			ui->SameLine();

			if (ui->AddButton("R6", sz1))
			{
				ImGui::StyleColorsClassic();
			}
			s = "StyleColorsClassic";
			ui->AddTooltip(s);

			ui->EndWindow();
		}
	}

	//--

//	//TODO: WIP
//	// Trying to make a font loader/tester on runtime..
//#define TEST_CUSTOM_FONTS 0
//
//#if(TEST_CUSTOM_FONTS==1) 
//	bool bOpenWindowStylizedFonts = 0;
//	bool bStyleFonts = false;
//	ofParameter<int> fontSize;
//	ofParameter<int> fontIndex;
//	ofParameter<bool> bEnable;
//	ofParameter<int> amount;
//	string s;
//	string txt = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";
//
//	//--------------------------------------------------------------
//	void setupFonts()
//	{
//		ui.clearFonts();
//
//		// NOTE: We can add font manually pushing "Add Font" button.
//		// then we can pick a default font setting "Font Index".
//		// this is for testing styles.
//
//		// NOTE: Then, we can add by code too to set hardcoded.
//		// Push some fonts:
//
//		std::string _fontName;
//		float _fontSize;
//		std::string _path = "assets/fonts/"; // assets folder
//
//		// Font #0
//		_fontName = "AnonymousPro-Regular.ttf";
//		_fontSize = 12;
//		ui.pushFont(_path + _fontName, _fontSize);
//
//		// Font #1
//		_fontName = "OpenSans-Regular.ttf";
//		_fontSize = 14;
//		ui.pushFont(_path + _fontName, _fontSize);
//
//		// Font #2
//		_fontName = "overpass-mono-bold.otf";
//		_fontSize = 16;
//		ui.pushFont(_path + _fontName, _fontSize);
//
//		// Font #3
//		_fontName = "JetBrainsMonoNL-ExtraBold.ttf";
//		_fontSize = 18;
//		ui.pushFont(_path + _fontName, _fontSize);
//
//		//--
//
//		//TODO:
//		//// default
//		//ui.addFont(_path + _fontName, OFX_IM_FONT_DEFAULT_SIZE_MIN);
//
//		int amt = ui.getNumFonts();
//		fontSize.set("Font Size", 10, 6, 30);
//		fontIndex.set("Font Index", 0, 0, amt - 1);
//	}
//
//	//--------------------------------------------------------------
//	void drawFonts()
//	{
//		ui.AddSpacingBigSeparated();
//
//		if (ui.Add(fontIndex))
//		{
//			//ui.setDefaultFontIndex(fontIndex);
//		}
//
//		s = ofToString(fontIndex) + "/" + ofToString(fontIndex.getMax());
//		ui.AddLabel(s.c_str());
//
//		s = ofToString(ui.getFontName(fontIndex));
//		ui.AddLabel(s.c_str());
//
//		//if (ImGui::Button("Set Font")) {
//		//	ui.setDefaultFontIndex(fontIndex);
//		//}
//
//		ui.AddSpacingBigSeparated();
//
//		ui.AddToggle("STYLIZED WINDOW", bOpenWindowStylizedFonts);
//
//		if (bOpenWindowStylizedFonts)
//		{
//			ui.AddSpacing();
//			ui.AddToggle("STYLIZE FONTS", bStyleFonts);
//			// -> will crash if styles are not queued!
//		}
//	}
//
//	//--------------------------------------------------------------
//	void drawWindowStylizedFonts()
//	{
//		// A window but using my ofxSurfingGui.h class helper
//		// Uses my own simpler helpers: 
//		// ofxSurfing_ImGui_Helpers.h
//		// Notice that you can add an ofParameterGroup out of a ofxImGui window. 
//		// (TODO: but this potentially make troubles yet [WIP] bc getUniqueNames engine!)
//
//		//--
//
//		// Minimal sizes
//		float ww = 300;
//		float hh = 600;
//
//		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));
//		{
//			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
//			if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
//
//			if (ui.BeginWindow("STYLIZED WINDOW", &bOpenWindowStylizedFonts, window_flags))
//			{
//				ui.AddToggle("STYLIZE FONTS", bStyleFonts);
//				// -> will crash if styles are not queued!
//
//				ui.AddSpacing();
//
//				if (!bStyleFonts) ui.AddLabelHuge("All widgets now using DEFAULT style");
//				else ui.AddLabelHuge("Each widget now using CUSTOM styles");
//
//				ui.AddSpacingSeparated();
//
//				if (bStyleFonts) ui.pushStyleFont(0);
//				{
//					if (bStyleFonts) {
//						ui.AddLabel("Font 0");
//						ui.AddLabel(ui.getFontName(0));
//					}
//
//					ui.Add(bEnable, OFX_IM_TOGGLE);
//					ui.Add(amount);
//					ui.AddLabel(txt);
//				}
//				if (bStyleFonts) ui.popStyleFont();
//
//				ui.AddSpacingSeparated();
//
//				//-
//
//				if (bStyleFonts) ui.pushStyleFont(1);
//				{
//					if (bStyleFonts) {
//						ui.AddLabel("Font 1");
//						ui.AddLabel(ui.getFontName(1));
//					}
//
//					ui.Add(bEnable, OFX_IM_TOGGLE);
//					ui.Add(amount);
//					ui.AddLabel(txt);
//				}
//				if (bStyleFonts) ui.popStyleFont();
//
//				ui.AddSpacingSeparated();
//
//				//-
//
//				if (bStyleFonts) ui.pushStyleFont(2);
//				{
//					if (bStyleFonts) {
//						ui.AddLabel("Font 2");
//						ui.AddLabel(ui.getFontName(2));
//					}
//
//					ui.Add(bEnable, OFX_IM_TOGGLE);
//					ui.Add(amount);
//					ui.AddLabel(txt);
//				}
//				if (bStyleFonts) ui.popStyleFont();
//
//				ui.AddSpacingSeparated();
//
//				//-
//
//				// Take care not pushing a non existing index or it will crash!
//				if (bStyleFonts) ui.pushStyleFont(3);
//				{
//					if (bStyleFonts) {
//						ui.AddLabel("Font 3");
//						ui.AddLabel(ui.getFontName(3));
//					}
//
//					ui.Add(bEnable, OFX_IM_TOGGLE);
//					ui.Add(amount);
//					ui.AddLabel(txt);
//				}
//				if (bStyleFonts) ui.popStyleFont();
//
//				ui.EndWindow();
//			}
//		}
//		ImGui::PopStyleVar();
//}
//#endif
//
//#if(TEST_CUSTOM_FONTS==1) 
//	setupFonts();
//	bEnable.set("Enable", false);
//	amount.set("amount", 10, 0, 25);
//	bGui.set("ofApp", true);
//#endif
//
//#if(TEST_CUSTOM_FONTS==1) 
//	if (bOpenWindowStylizedFonts) drawWindowStylizedFonts();
//#endif

};
