
/*

	WIP

	This is a helper to:
	- Edit/test themes.
	- Save themes to allow loading on your apps.
	TODO:
	- Loading font files to check and tweak styles.
	- Add fonts tester.

	TODO

	share path with ui
	store in data/files and list files and make a picker.
		currently saving into bin/imgui_styles.ini
	add make new ImGui_ThemeMoebiusSurfingV3
		dark theme with more 3d styled look.
		pressed toggle = darker.
	define a global color and some main colors.
		link colors between particular settings.
		but darker or lighter. add helpers.
		ex: mark what color must be linked.
			each one has his own alpha.
		//https://github.com/ocornut/imgui/issues/438
		SetupStyleFromHue() / ofxImGui::DefaultTheme
	undo history or snapshot points
		using ofParams and an addon for presets.

	add list files in a path / open dialog
		pick theme files on runtime
		ex: day/night

*/


//--

#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

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

//--

class SurfingThemeEditor
{
public:
	ofParameterGroup params;

	ofParameter<bool> bGui;
	ofParameter<bool> bGui_StyleEditor;
	ofParameter<bool> bGui_ThemeManager;
	ofParameter<bool> bGui_DemoImGui;
	ofParameter<bool> bGui_DemoWidgets;
	ofParameter<bool> bEnableColors;
	ofParameter<bool> bEnableLayout;
	ofParameter<bool> bClickerCombo;
	ofParameter<string> nameTheme;
	ofParameter<int> indexTheme;

	SurfingThemeEditor()
	{
		ofAddListener(ofEvents().keyPressed, this, &SurfingThemeEditor::keyPressed);
		ofAddListener(ofEvents().exit, this, &SurfingThemeEditor::exit);

		//setup();
	};

	~SurfingThemeEditor()
	{
		ofRemoveListener(ofEvents().keyPressed, this, &SurfingThemeEditor::keyPressed);
		ofRemoveListener(ofEvents().exit, this, &SurfingThemeEditor::exit);
		ofRemoveListener(params.parameterChangedE(), this, &SurfingThemeEditor::Changed);

		//exit();
	};

	void setup()
	{
		bGui.set("Theme Editor", true);
		bGui_StyleEditor.set("Style Editor", false);
		bGui_ThemeManager.set("Theme Manager", false);
		bGui_DemoWidgets.set("Demo Widgets", false);
		bGui_DemoImGui.set("Dear ImGui Demo", false);
		bEnableColors.set("Colors", true);
		bEnableLayout.set("Layout", true);
		bClickerCombo.set("ClickerCombo", true);
		nameTheme.set("ThemeName", "");
		indexTheme.set("Theme", 0, 0, 0);

		params.setName("SurfingThemeEditor");
		params.add(bGui);
		params.add(bGui_StyleEditor);
		params.add(bGui_ThemeManager);
		params.add(bGui_DemoWidgets);
		params.add(bGui_DemoImGui);
		params.add(bEnableColors);
		params.add(bEnableLayout);
		params.add(nameTheme);
		params.add(indexTheme);
		params.add(bClickerCombo);

		//ofxImGuiSurfing::setIndexTheme(5);
		////ofxImGuiSurfing::indexTheme = 5;

		setPathGlobal(pathGlobal);

		ofxSurfingHelpers::loadGroup(params, pathGlobal + params.getName() + ".json");

		pathThemes = pathGlobal + subPathThemes;
		ofxSurfingHelpers::CheckFolder(pathThemes);

		pathCompares = pathThemes + subPathCompare;
		ofxSurfingHelpers::CheckFolder(pathCompares);

		filename = nameTheme.get();
		pathTheme = pathThemes + filename;

		files.setPathDirectory(pathThemes);

		//files.index.makeReferenceTo(indexTheme);
		indexTheme.makeReferenceTo(files.index);

		ofAddListener(params.parameterChangedE(), this, &SurfingThemeEditor::Changed);
	};

public:
	void setPathGlobal(string path) {//call before setup
		pathGlobal = path;
		ofxSurfingHelpers::CheckFolder(pathGlobal);

		pathThemes = pathGlobal + subPathThemes;
		pathCompares = pathThemes + subPathCompare;

		ofxSurfingHelpers::CheckFolder(pathThemes);
		ofxSurfingHelpers::CheckFolder(pathCompares);
	};

private:
	string pathGlobal = "ThemeEditor/";

	string pathTheme = "";
	string pathThemes = "";
	string subPathThemes = "themes/";
	string pathCompares = "";
	string subPathCompare = "compare/";
	string filename = ""; //"imgui_styles.ini"

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
	};

	void resetTheme() {
		ImGui::GetStyle() = ImGuiStyle();
	};

	void loadThemeHardcoded(int index) {
		ofxImGuiSurfing::setIndexTheme(index);
	};

private:
	void exit(ofEventArgs& args) { exit(); };
	void exit() {
		ofxSurfingHelpers::saveGroup(params, pathGlobal + params.getName() + ".json");
	};

	void keyPressed(ofKeyEventArgs& eventArgs) {
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
	};

	SurfingGuiManager* ui = nullptr;

public:
	void setUiPtr(ofxSurfingGui* _ui) {
		ui = _ui;
	};

	//--

	void drawDemoSurfingWidgets(SurfingGuiManager& ui)
	{
		static ofParameter<float> v1{ "Value1", 0.5, 0, 1 };
		static ofParameter<float> v2{ "Value2", 0, -1, 1 };
		static ofParameter<int> n1{ "Number1", 4, 0, 8 };
		static ofParameter<int> n2{ "Number2", 0, -10, 10 };
		static int n3 = 0;
		static float v3 = 0;
		static bool b1 = 1;
		static bool b2 = false;
		static ofParameter<int> i{ "Index",2,0,3 };
		static std::vector<std::string> fileNames{ "ZERO", "ONE","TWO","THREE" };

		ImVec2 sz1(ImGui::GetContentRegionAvail().x, 2 * ImGui::GetFrameHeight());
		ImVec2 sz2(ImGui::GetContentRegionAvail().x / 2 - ImGui::GetStyle().ItemSpacing.x, 2 * ImGui::GetFrameHeight());

		ui.AddLabelHuge("Theme Tester", true);
		ui.AddSpacingSeparated();
		ui.AddLabelBig("Surfing API");
		ui.AddButton("Button", sz1);
		ui.AddToggle("Toggle", b1, sz1);
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
		ui.AddLabelBig("ImGui RAW");
		ImGui::SliderInt("Number3", &n3, 0, 5);
		ImGui::SliderFloat("Value3", &v3, -1, 1);
		ImGui::Button("Button1");
		ui.SameLine();
		ImGui::Button("Button2");
		ImGui::Checkbox("Toggle1", &b1);
		ImGui::Checkbox("Toggle2", &b2);
	};

	void drawDemoSurfingWidgets()
	{
		if (ui == nullptr) return;

		if (!bGui_DemoWidgets) return;

		//IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;
		ImVec2 size_min = ImVec2(150, -1);
		ImVec2 size_max = ImVec2(200, -1);
		ImGui::SetNextWindowSizeConstraints(size_min, size_max);

		if (ui->BeginWindow(bGui_DemoWidgets))
		{
			drawDemoSurfingWidgets(*ui);

			ui->EndWindow();
		}
	};

	void draw()
	{
		if (!bGui) return;

		IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;

		if (ui->BeginWindow(bGui))
		{
			//static bool bExpand = 0;
			//ui->AddToggle("Expand", bExpand, OFX_IM_TOGGLE_ROUNDED_MINI);
			//if (bExpand)
			{
				ui->AddLabelBig("Surfing\nThemeEditor");
				ui->AddSpacing();
				ui->Add(bGui_ThemeManager, OFX_IM_TOGGLE_ROUNDED);
				ui->Add(bGui_StyleEditor, OFX_IM_TOGGLE_ROUNDED);
				ui->AddSpacingSeparated();
				ui->Add(bGui_DemoWidgets, OFX_IM_TOGGLE_ROUNDED);
				ui->Add(bGui_DemoImGui, OFX_IM_TOGGLE_ROUNDED);
				ui->AddSpacingSeparated();
				ui->Add(ui->bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);
			}
			//ui->AddSpacingBigSeparated();

			ui->EndWindow();
		}

		//--

		if (bGui_ThemeManager) drawThemeManager();
		if (bGui_StyleEditor) drawStyleEditor();
		if (bGui_DemoWidgets) drawDemoSurfingWidgets();
		if (bGui_DemoImGui) drawDemoImGui();
	};

	//--

	void saveThemeFile(string path) {
		//ofLogNotice("ofxSurfingImGui") << "filename: " << filename;
		string p = ofToDataPath(path);
		ImGui::SaveStylesTo(p.c_str());
		ofLogNotice("ofxSurfingImGui") << "Save config to " << path;

		files.refreshFiles();
	};

	void loadThemeFile(string path) {
		//ofLogNotice("ofxSurfingImGui") << "filename: " << filename;
		ofLogNotice("ofxSurfingImGui") << "Load config from " << path;
		string p = ofToDataPath(path);
		ImGui::LoadStyleFrom(p.c_str());
	};

	void reloadThemeFile() {
		ofLogNotice("ofxSurfingImGui") << "Reload config from " << pathTheme;
		string p = ofToDataPath(pathTheme);
		ImGui::LoadStyleFrom(p.c_str());
	};

	//--

private:
	void drawStyleEditor()
	{
		if (!bGui_StyleEditor) return;

		if (ui->BeginWindow(bGui_StyleEditor)) {

			ImGuiStyle& style = ImGui::GetStyle();

			ImGui::ShowStyleEditor(&style);

			ui->EndWindow();
		}
	};

	void drawDemoImGui()
	{
		ImGui::ShowDemoWindow(NULL);
	};

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

			//TODO: 
			// add text input
			ui->Add(nameTheme, OFX_IM_TEXT_INPUT);

			if (ImGui::Button("Load", sz)) {
				loadThemeFile(pathTheme);
			}
			ImGui::SameLine();
			if (ImGui::Button("Save", sz)) {
				saveThemeFile(pathTheme);
			}

			if (ImGui::Button("Reload##THEME")) {
				reloadThemeFile();
			}

			ui->AddSpacing();

			ui->Add(indexTheme, OFX_IM_HSLIDER_SMALL);

			ui->AddSpacing();
			ofxImGuiSurfing::AddToggleRoundedButtonNamed(bClickerCombo, "Clicker", "List");
			ui->AddSpacing();

			if (bClickerCombo) files.draw();
			else ui->AddCombo(indexTheme, files.getNames());

			ui->AddSpacingBigSeparated();

			//--

			ui->AddLabelBig("Hardcoded Themes", true);

			// arrows, hardcoded themes combo, fonts combo
			ofxImGuiSurfing::drawThemeSelector(NULL);

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
			ui->AddTooltipHelp("Press Control to Save");
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
				ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
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
	};

	//--

	//TODO: WIP
	// Trying to make a font loader/tester on runtime..
#define TEST_CUSTOM_FONTS 0

#if(TEST_CUSTOM_FONTS==1) 
	bool bOpenWindowStylizedFonts = 0;
	bool bStyleFonts = false;
	ofParameter<int> fontSize;
	ofParameter<int> fontIndex;
	ofParameter<bool> bEnable;
	ofParameter<int> amount;
	string s;
	string txt = "Lorem Ipsum is simply dummy text of the printing and typesetting industry.";

	//--------------------------------------------------------------
	void setupFonts()
	{
		ui.clearFonts();

		// NOTE: We can add font manually pushing "Add Font" button.
		// then we can pick a default font setting "Font Index".
		// this is for testing styles.

		// NOTE: Then, we can add by code too to set hardcoded.
		// Push some fonts:

		std::string _fontName;
		float _fontSize;
		std::string _path = "assets/fonts/"; // assets folder

		// Font #0
		_fontName = "AnonymousPro-Regular.ttf";
		_fontSize = 12;
		ui.pushFont(_path + _fontName, _fontSize);

		// Font #1
		_fontName = "OpenSans-Regular.ttf";
		_fontSize = 14;
		ui.pushFont(_path + _fontName, _fontSize);

		// Font #2
		_fontName = "overpass-mono-bold.otf";
		_fontSize = 16;
		ui.pushFont(_path + _fontName, _fontSize);

		// Font #3
		_fontName = "JetBrainsMonoNL-ExtraBold.ttf";
		_fontSize = 18;
		ui.pushFont(_path + _fontName, _fontSize);

		//--

		//TODO:
		//// default
		//ui.addFont(_path + _fontName, FONT_DEFAULT_SIZE);

		int amt = ui.getNumFonts();
		fontSize.set("Font Size", 10, 6, 30);
		fontIndex.set("Font Index", 0, 0, amt - 1);
	}

	//--------------------------------------------------------------
	void drawFonts()
	{
		ui.AddSpacingBigSeparated();

		if (ui.Add(fontIndex))
		{
			//ui.setDefaultFontIndex(fontIndex);
		}

		s = ofToString(fontIndex) + "/" + ofToString(fontIndex.getMax());
		ui.AddLabel(s.c_str());

		s = ofToString(ui.getFontName(fontIndex));
		ui.AddLabel(s.c_str());

		//if (ImGui::Button("Set Font")) {
		//	ui.setDefaultFontIndex(fontIndex);
		//}

		ui.AddSpacingBigSeparated();

		ui.AddToggle("STYLIZED WINDOW", bOpenWindowStylizedFonts);

		if (bOpenWindowStylizedFonts)
		{
			ui.AddSpacing();
			ui.AddToggle("STYLIZE FONTS", bStyleFonts);
			// -> will crash if styles are not queued!
		}
	}

	//--------------------------------------------------------------
	void drawWindowStylizedFonts()
	{
		// A window but using my ofxSurfingGui.h class helper
		// Uses my own simpler helpers: 
		// ofxSurfing_ImGui_Helpers.h
		// Notice that you can add an ofParameterGroup out of a ofxImGui window. 
		// (TODO: but this potentially make troubles yet [WIP] bc getUniqueNames engine!)

		//--

		// Minimal sizes
		float ww = 300;
		float hh = 600;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));
		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (ui.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			if (ui.BeginWindow("STYLIZED WINDOW", &bOpenWindowStylizedFonts, window_flags))
			{
				ui.AddToggle("STYLIZE FONTS", bStyleFonts);
				// -> will crash if styles are not queued!

				ui.AddSpacing();

				if (!bStyleFonts) ui.AddLabelHuge("All widgets now using DEFAULT style");
				else ui.AddLabelHuge("Each widget now using CUSTOM styles");

				ui.AddSpacingSeparated();

				if (bStyleFonts) ui.pushStyleFont(0);
				{
					if (bStyleFonts) {
						ui.AddLabel("Font 0");
						ui.AddLabel(ui.getFontName(0));
					}

					ui.Add(bEnable, OFX_IM_TOGGLE);
					ui.Add(amount);
					ui.AddLabel(txt);
				}
				if (bStyleFonts) ui.popStyleFont();

				ui.AddSpacingSeparated();

				//-

				if (bStyleFonts) ui.pushStyleFont(1);
				{
					if (bStyleFonts) {
						ui.AddLabel("Font 1");
						ui.AddLabel(ui.getFontName(1));
					}

					ui.Add(bEnable, OFX_IM_TOGGLE);
					ui.Add(amount);
					ui.AddLabel(txt);
				}
				if (bStyleFonts) ui.popStyleFont();

				ui.AddSpacingSeparated();

				//-

				if (bStyleFonts) ui.pushStyleFont(2);
				{
					if (bStyleFonts) {
						ui.AddLabel("Font 2");
						ui.AddLabel(ui.getFontName(2));
					}

					ui.Add(bEnable, OFX_IM_TOGGLE);
					ui.Add(amount);
					ui.AddLabel(txt);
				}
				if (bStyleFonts) ui.popStyleFont();

				ui.AddSpacingSeparated();

				//-

				// Take care not pushing a non existing index or it will crash!
				if (bStyleFonts) ui.pushStyleFont(3);
				{
					if (bStyleFonts) {
						ui.AddLabel("Font 3");
						ui.AddLabel(ui.getFontName(3));
					}

					ui.Add(bEnable, OFX_IM_TOGGLE);
					ui.Add(amount);
					ui.AddLabel(txt);
				}
				if (bStyleFonts) ui.popStyleFont();

				ui.EndWindow();
			}
		}
		ImGui::PopStyleVar();
}
#endif

#if(TEST_CUSTOM_FONTS==1) 
	setupFonts();
	bEnable.set("Enable", false);
	amount.set("amount", 10, 0, 25);
	bGui.set("ofApp", true);
#endif

#if(TEST_CUSTOM_FONTS==1) 
	if (bOpenWindowStylizedFonts) drawWindowStylizedFonts();
#endif

};
