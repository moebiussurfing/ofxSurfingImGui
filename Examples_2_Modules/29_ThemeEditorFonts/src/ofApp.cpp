#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(1, true, true);//right monitor and portrait

	ui.setup();

	//--

	// Font Helpers
	f.setUiPtr(&ui);
	f.setup();

	//--

	// Theme Editor
	e.setPathGlobal(ui.getPath());
	e.setUiPtr(&ui);
	e.setup();

	//--

	// Customize default fonts
#if 0
	// Force replace:
	// The default font
	// The default mono-spaced font
	string p = "assets/fonts2/Inter-Black.ttf";
	float sz = OFX_IM_FONT_DEFAULT_MONO_SIZE_MIN;
	ui.setupFontForDefaultStyles(p, sz);

	p = "assets/fonts2/overpass-mono-bold.otf";
	sz = OFX_IM_FONT_DEFAULT_MONO_SIZE_MIN;
	ui.setupFontForDefaultStylesMonospaced(p, sz);
#endif
}

//--------------------------------------------------------------
void ofApp::update()
{
	f.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow("ofApp"))
		{
			ui.AddSpacingBig();
			ui.Add(f.bGui, OFX_IM_TOGGLE_ROUNDED_BIG);
			ui.Add(e.bGui, OFX_IM_TOGGLE_ROUNDED_BIG);
			ui.AddSpacingBigSeparated();
			ui.AddAutoResizeToggle();
			ui.AddSpacingBig();

			//--

			// Select day/night theme

			// A. A simple toggle
			ui.DrawWidgetsTheme();

			// // B. A custom combo
			// ui.AddLabelBig("THEME");
			// ui.AddThemeToggle();

			//--

#if 0
			ui.AddSpacingBigSeparated();

			// Global scale
			static ofParameter<float> scale{"Scale", 1, 0.5, 10};
			if (ui.Add(scale)) {
				ImGui::SetGlobalScale(scale);
				//ui.setS
			}
			if (ui.AddButton("Reset")) {
				scale = 1;
			}
#endif

			ui.EndWindow();
		}
	}

	//--

	f.drawImGui();

	//--

	// Demo Window

	if (!ui.isFontsMonospacedDefined())
	{
		// Apply picked selected index as font style
		ui.PushFontByIndex();
		{
			drawMyDemoWindow();

			e.draw();
		}
		ui.PopFontByIndex();
	}
	else {
		// Apply custom font style

		if (bUseFontMonospaced) ui.PushFontStyle(4);//default mono-spaced
		else ui.PushFontByIndex();
		{
			drawMyDemoWindow();

			e.draw();
		}
		ui.PopFontStyle();
	}

	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ofLogNotice("ofApp") << "keyPressed: " << (char)key;

	if (key == OF_KEY_LEFT)
	{
		ui.doLoadPreviousFont();
	}

	else if (key == OF_KEY_RIGHT)
	{
		ui.doLoadNextFont();
	}
}

//--------------------------------------------------------------
void ofApp::drawMyDemoWindow() {

	ImGui::Begin("MyDemoWindow");

	ImGui::TextWrapped("NOTE: ON THIS WINDOW WE ARE USING THE SELECTED FONT FOR ALL THE WIDGETS!");

	if (ui.isFontsMonospacedDefined()) {
		ImGui::Spacing();
		if (ImGui::Checkbox("Font Monospaced", &bUseFontMonospaced)) {
			if (bUseFontMonospaced)bUseFontIndex = 0;
		};
		if (ImGui::Checkbox("Font Index", &bUseFontIndex)) {
			if (bUseFontIndex) bUseFontMonospaced = 0;
		};

		if (!bUseFontIndex && !bUseFontMonospaced)bUseFontIndex = 1;
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();

	ofxImGuiSurfing::AddParameter(ui.bAutoResize);
	ImGui::Button("Button0", { ImGui::GetContentRegionAvail().x, 40 });

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();

	// Widgets
	ImGui::Text("Sliders:");
	static float sliderValue = 0.5f;
	ImGui::SliderFloat("Float Slider", &sliderValue, 0.0f, 1.0f);

	static int intSliderValue = 50;
	ImGui::SliderInt("Integer Slider", &intSliderValue, 0, 100);

	ImGui::Text("Range Slider:");
	static float rangeStart = 25.0f;
	static float rangeEnd = 75.0f;
	ImGui::DragFloatRange2("Float Range", &rangeStart, &rangeEnd, 0.1f, 0.0f, 100.0f, "Min: %.1f", "Max: %.1f");

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();

	// Help
	string s = "";
	string sp = "\t"; //column spacer
	s += "H    " + sp + "HIDE SELECTED\n";
	s += "S    " + sp + "SHOW ALL\n";
	s += "\n";
	s += "F1   " + sp + "HELP WINDOW\n";
	s += "F2   " + sp + "SETTINGS WINDOW\n";
	s += "`    " + sp + "MINIMIZE\n";
	s += "\n";
	s += "WINDOWS\n";
	s += "\n";
	s += "1    " + sp + "CAMERAS\n";
	s += "2    " + sp + "OUTPUT\n";
	s += "3    " + sp + "SYNC\n";
	s += "4    " + sp + "TRACKER DATA\n";
	s += "5    " + sp + "TRACKER INPUTS\n";
	s += "6    " + sp + "DATA\n";
	s += "\n";
	s += "0    " + sp + "GLOBAL\n";
	ImGui::TextWrapped(s.c_str());

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::Text("Buttons:");
	if (ImGui::Button("Button1", { 150, 40 }))
	{
		// Button action
	}
	ImGui::SameLine();
	if (ImGui::Button("Disabled Button", { 200, 100 }))
	{
		// Button action
	}
	ImGui::Text("Tooltip on Hover");
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip("This is a tooltip");
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Spacing();

	// Columns
	ImGuiOldColumnFlags flags = ImGuiOldColumnFlags_NoResize;
	ImGui::BeginColumns("Columns", 3, flags);
	ImGui::Text("Column 1");
	ImGui::NextColumn();
	ImGui::Text("Column 2");
	ImGui::NextColumn();
	ImGui::Text("Column 3");
	ImGui::NextColumn();
	ImGui::Separator();
	for (int i = 0; i < 9; ++i)
	{
		ImGui::Text("Item %d", i);
		ImGui::NextColumn();
	}
	ImGui::EndColumns();

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	// Tabs
	if (ImGui::BeginTabBar("TabBar"))
	{
		if (ImGui::BeginTabItem("Tab 1"))
		{
			// Contents of Tab 1
			ImGui::Text("Hello Tab 1");
			ImGui::Text("Hello Tab 1");
			ImGui::Text("Hello Tab 1");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Tab 2"))
		{
			// Contents of Tab 2
			ImGui::Text("Hello Tab 2");
			ImGui::Text("Hello Tab 2");
			ImGui::Text("Hello Tab 2");

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Tab 3"))
		{
			// Contents of Tab 3
			ImGui::Text("Hello Tab 3");
			ImGui::Text("Hello Tab 3");
			ImGui::Text("Hello Tab 3");

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}