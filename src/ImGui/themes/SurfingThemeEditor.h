
/*

	WIP

	This is a helper to:
	- Edit/test your own themes.
	- Save themes to allow loading on your apps.
	- Loading font files to check and tweak styles.
	- Add fonts tester.


	TODO

	store in data/files and list files and make a picker.
		currently saving into bin/imgui_styles.ini
	add make new ImGui_ThemeMoebiusSurfingV3
		dark theme with more 3d styled look.
		pressed toggle = darker.
	add apply by sections: sizes and layout and/or colors
	define a global color and some main colors.
		link colors between particular settings.
		but darker or lighter. add helpers.
		ex: mark what color must be linked.
			each one has his own alpha.
	add reset theme and A/B compare.
	undo history or snapshot points
		using ofParams and an addon for presets.

	OTHER LINKS
	https://github.com/Patitotective/ImThemes
	https://github.com/Patitotective/ImStyle

*/


//--

#pragma once

#include "ofMain.h"

//#include "imgui.h"
//#include "ofxSurfingImGui.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"
#include "BaseTheme.h"

// Theme serializer
// Taken from: https://github.com/pegvin/ImGooeyStyles
#include "imgui_styles.h"

#include "SurfingThemesHelpers.h"

//--

class SurfingThemeEditor
{
public:
	ofParameter<bool> bGui_Editor;
	ofParameter<bool> bGui_ThemeSelector;
	ofParameter<bool> bGui_Demo;
	ofParameterGroup params;

	SurfingThemeEditor() {
		bGui_Editor.set("Surfing Style Editor", false);
		bGui_ThemeSelector.set("Theme Selector", false);
		bGui_Demo.set("Dear ImGui Demo", false);

		params.setName("SurfingThemeEditor");
		params.add(bGui_Editor);
		params.add(bGui_Demo);
		params.add(bGui_ThemeSelector);
	};

	~SurfingThemeEditor() {
	};

private:
	SurfingGuiManager* ui = nullptr;

public:
	void setUiPtr(ofxSurfingGui* _ui) {
		ui = _ui;
	};

	void draw()
	{
		if (bGui_Editor) drawEditor();
		if (bGui_Demo) drawDemo();
		if (bGui_ThemeSelector) drawThemeSelector();
	};

	void drawDemoSurfingWidgets(SurfingGuiManager& ui)
	{
		ui.AddSpacing();
		ui.AddLabelHuge("Theme Tester", true);
		ui.AddSeparated();
		ui.AddSpacing();

		ImVec2 sz1(ImGui::GetContentRegionAvail().x, 2 * ImGui::GetFrameHeight());
		ImVec2 sz2(ImGui::GetContentRegionAvail().x / 2 - ImGui::GetStyle().ItemSpacing.x, 2 * ImGui::GetFrameHeight());

		static ofParameter<float> v1{ "Value", 0.5, 0, 1 };
		static ofParameter<float> v2{ "Value", 0.5, 0, 1 };
		static ofParameter<int> n{ "Number", 0, 0, 10 };
		static bool b1 = false;
		static bool b2 = false;
		static ofParameter<int> i{ "Index",0,0,3 };
		static std::vector<std::string> fileNames{ "ZERO", "ONE","TWO","THREE" };

		ui.AddLabelBig("Surfing API");
		if (ui.AddButton("Button", sz1)) {
		}
		if (ui.AddToggle("Toggle", b1, sz1)) {
		}
		ui.Add(v1, OFX_IM_HSLIDER);
		ui.Add(v2, OFX_IM_KNOB_TICKKNOB);
		ui.Add(i, OFX_IM_STEPPER);
		ui.AddCombo(i, fileNames);

		ui.AddSpacingBigSeparated();

		ui.AddLabelBig("ImGui RAW");
		ui.Add(n);
		if (ImGui::Button("Button")) {
		};
		ImGui::Checkbox("Toggle", &b2);
	};

	void drawDemoSurfingWidgets()
	{
		if (ui == nullptr) return;
		drawDemoSurfingWidgets(*ui);
	};

private:
	void drawEditor()
	{
		if (!bGui_Editor) return;

		ImGuiStyle& style = ImGui::GetStyle();

		static bool b = false;

		ImGui::Begin("Surfing Style Editor");

		ImVec2 sz(ImGui::GetContentRegionAvail().x / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 2 * ImGui::GetFrameHeight());

		if (ImGui::Button("Load Configuration", sz)) {
			ImGui::LoadStyleFrom("imgui_styles.ini");
			ofLogNotice("ofxSurfingImGui") << "Loaded Config From imgui_styles.ini...";
		}
		ImGui::SameLine();
		if (ImGui::Button("Save Configuration", sz)) {
			ImGui::SaveStylesTo("imgui_styles.ini");
			ofLogNotice("ofxSurfingImGui") << "Saved Config To imgui_styles.ini...";
		}
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::ShowStyleEditor(&style);

		ImGui::End();
	};

	void drawDemo()
	{
		ImGui::ShowDemoWindow(NULL);
	};

public:
	void drawThemeSelector()
	{
		if (ui == nullptr) return;

		if (ui->BeginWindow(bGui_ThemeSelector))
		{
			ofxImGuiSurfing::drawThemeSelector(NULL);

			ui->AddSpacingBigSeparated();

			ImVec2 sz1(ImGui::GetContentRegionAvail().x, 1 * ImGui::GetFrameHeight());
			if (ui->AddButton("Reset", sz1)) {
				//ImGui::StyleColorsLight();

				ofxImGui::DefaultTheme* defaultTheme = new ofxImGui::DefaultTheme();
				ui->getGuiPtr()->setTheme((ofxImGui::BaseTheme*)defaultTheme);
			}

			ui->EndWindow();
		}
	};
};
