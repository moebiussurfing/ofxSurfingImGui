#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(1, true, true);

	ui.setup();

	// Font Helpers
	f.setUiPtr(&ui);
	f.setup();

	//--

	// Theme Editor
	e.setPathGlobal(ui.getPath());
	e.setUiPtr(&ui);
	e.setup();
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

	// The Editor Windows
	// Apply picked as font style
	ui.PushFontByIndex();
	{

		drawMyDemoWindow();

		e.draw();
	}
	ui.PopFontByIndex();

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