#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	//-

	// Must uncomment only one mode!

	// MODE A
	guiManager.setImGuiAutodraw(true); // -> required when only one single ImGui instance is instantiated on all the oF project.
	guiManager.setup(); // ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).

	// MODE B
	//guiManager.setup(gui); // can be instantiated out of the class, locally
	
	// pick a theme
	//ofxImGuiSurfing::ImGui_ThemeSequentity();

	//-

	// ofParameters
	params.setName("paramsGroup");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params.add(bMode1.set("Mode1", false));
	params.add(bMode2.set("Mode2", false));
	params.add(bMode3.set("Mode3", false));
	params.add(bMode4.set("Mode4", false));
	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable.set("Enable", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params2.add(params3);
	params.add(params2);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		static bool bOpen0 = true;
		static bool bOpen1 = false;
		static bool bOpen2 = true;
		static bool show_app_style_editor = false;

		//---------

		// Main Window

		// A raw standard raw ImGui window
		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Show Windows", &bOpen0, window_flags);
			{
				// round toggles widgets
				ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);
				ofxImGuiSurfing::ToggleRoundedButton("Show Window 2", &bOpen2);
				ofxImGuiSurfing::ToggleRoundedButton("Show Window 3", &bOpen3);
				ofxImGuiSurfing::ToggleRoundedButton("Theme Editor", &show_app_style_editor);

				ImGui::Dummy(ImVec2(0, 5)); // spacing

				ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);// a public bool variable to allow handle auto-resize. Applied here to all the windows.
			}
			ImGui::End();
		}

		//---------

		// Window 1

		// A window but using my ofxSurfing_ImGui_Manager.h class helper
		// Uses my own simpler helpers: 
		// ofxSurfing_ImGui_Helpers.h
		// Notice that you can add an ofParameterGroup out of a ofxImGui window. 
		// (TODO: but this potentially make troubles yet [WIP] bc getUniqueNames engine!)

		if (bOpen1)
		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			guiManager.beginWindow("Window 1", &bOpen1, window_flags);
			{
				// A group of parameters with customized tree/folder type
				// will be applied to all nested groups inside this parent group

				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
				flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
				flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed

				ofxImGuiSurfing::AddGroup(params, flags);

				//-

				// An advanced panel with some typical toggles for extra config 
				// (autosize, get mouse over, lock..etc)
				guiManager.drawAdvancedSubPanel();
			}
			guiManager.endWindow();
		}

		//---------

		// window 2

		if (bOpen2)
		{
			// Minimal sizes
			float ww = PANEL_WIDGETS_WIDTH_MIN;
			float hh = PANEL_WIDGETS_HEIGHT_MIN;
			ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			guiManager.beginWindow("Window 2", &bOpen2, window_flags);
			{
				// Snippet to handle common widgets sizes:
				float _spcx;	// space between widgets
				float _spcy;	// space between widgets
				float _w100;	// full width
				float _h100;	// full height
				float _w99;		// a bit less than full width
				float _w50;		// half width
				float _w33;		// third width
				float _w25;		// quarter width
				float _h;		// standard height

				// We will update the sizes on any gui drawing required point, 
				// like inside a new foldered sub-window that could be indendeted and full-width size is being smaller.
				ofxImGuiSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

				// Here we will add some ofParamaters usign customized responsive layout of many widgets types!

				//-

				ImGui::Text("Responsive Widgets:");

				// Two custom toggles
				if (ofxImGuiSurfing::AddBigToggle(bEnable)) {} // this is full width (_w1) with standard height (_h)
				//if (ofxImGuiSurfing::AddBigToggle(bEnable, _w100, _h / 2)) {} // same width but half height

				// Two custom buttons in the same line/row
				// 50% width aka two widgets on current same line/row
				if (ofxImGuiSurfing::AddBigButton(bPrevious, _w50, _h)) {
					lineWidth -= 0.1;
					bPrevious = false;
				}
				ImGui::SameLine();
				if (ofxImGuiSurfing::AddBigButton(bNext, _w50, _h)) {
					lineWidth += 0.1;
					bNext = false;
				}

				ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing

				// Three standard widget params

				ImGui::Text("Some ofParameters:");
				ofxImGuiSurfing::AddParameter(bEnable);
				ofxImGuiSurfing::AddParameter(separation);
				ofxImGuiSurfing::AddParameter(shapeType);

				//-
				
				ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing

				//-

				// more widgets inside this window

				drawWidgets();

				//-

				// A responsive button. filling the below panel area

				ImGui::Text("A responsive button:");
				float __w100 = ImGui::GetContentRegionAvail().x;
				float __h100 = ImGui::GetContentRegionAvail().y;
				ofxImGuiSurfing::AddBigButton(bPrevious, __w100, __h100);
			}
			guiManager.endWindow();

			ImGui::PopStyleVar();
		}

		//-----

		if (bOpen3) drawWindow3();

		//-----

		// theme editor
		if (show_app_style_editor)
		{
			ImGui::Begin("Dear ImGui Style Editor", &show_app_style_editor);
			ofxImGuiSurfing::ShowStyleEditor2(NULL);
			ImGui::End();
		}
	}

	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::drawWidgets() {

	// These are pure widgets without window/tree/container
	// to be drawn inside a panel window

	//-

	// Some custom widgets
	ImGui::Text("Custom Range Sliders:");

	// range_slider.h
	static float v_min = 0; // limits
	static float v_max = 1;

	static float v1min = 0.4;
	static float v1max = 0.9;
	ofxImGuiSurfing::RangeSliderFloat("Range 1", &v1min, &v1max, v_min, v_max, "%.3f  %.3f", 1.0f);

	static float v2min = 0.1;
	static float v2max = 0.6;
	ofxImGuiSurfing::RangeSliderFloat("Range 2", &v2min, &v2max, v_min, v_max);

	ImGui::Dummy(ImVec2(0.0f, 10.0f)); // spacing

	//--

	bool bOpen = false;
	ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
	_flagt |= ImGuiTreeNodeFlags_Framed;

	if (ImGui::TreeNodeEx("A folder opened", _flagt))
	{
		ImGui::Text("Vanilla Range Sliders:");

		static float begin = 10, end = 90;
		static int begin_i = 100, end_i = 1000;
		ofxImGuiSurfing::DragFloatRange2("Range float", &begin, &end, 0.25f, 0.0f, 100.0f);
		ofxImGuiSurfing::DragIntRange2("Range int", &begin_i, &end_i, 5, 0, 0, "Min: %.0f units", "Max: %.0f units");

		ImGui::TreePop();
	}

	ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing

	//-

	// This is a typical extra menu with advanced options
	{
		ImGui::Dummy(ImVec2(0, 5)); // spacing
		{

			ImGui::Text("A hidden by default Extra section");
			ImGui::Text("An Advanced section inside to debug:");

			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bExtra);
			if (guiManager.bExtra)
			{
				ImGui::Indent();
				{
					//--

					ofxImGuiSurfing::AddToggleRoundedButton(bEnable);
					ofxImGuiSurfing::AddToggleRoundedButton(bMode1);
					ofxImGuiSurfing::AddToggleRoundedButton(bMode2);
					ofxImGuiSurfing::AddToggleRoundedButton(bMode3);
					//ofxImGuiSurfing::AddParameter(shapeType);

					ImGui::Dummy(ImVec2(0.0f, 10.0f));

					//--

					ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
					if (guiManager.bExtra) guiManager.drawAdvancedSubPanel();
				}
				ImGui::Unindent();
			}
		}
	}

	ImGui::Dummy(ImVec2(0.0f, 40.0f)); // spacing
}

//--------------------------------------------------------------
void ofApp::drawWindow3()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	guiManager.beginWindow("Window3", &bOpen3, window_flags);
	{
		ofxImGuiSurfing::AddToggleRoundedButton(bEnable);
		if (bEnable)
		{
			// Precalculate common widgets sizes to fit current window, "to be responsive".
			// Takes care of ImGui spacing between widgets.
			// Remeber to recall when panel is indented or inside an smaller tree!
			float _w1 = ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
			float _w2 = ofxImGuiSurfing::getWidgetsWidth(2); // 2 widgets half width
			float _w3 = ofxImGuiSurfing::getWidgetsWidth(3); // 3 widgets third width
			float _w4 = ofxImGuiSurfing::getWidgetsWidth(4); // 4 widgets quarter width
			float _h = WIDGETS_HEIGHT;

			//-

			// Draw RAW ImGui or SurfingWidgets with ofParameters

			// One widget full with and half height
			if (AddBigToggle(b1, _w1, _h / 2)) {}

			// Two widgets same line/row with the 50% of window panel width 
			if (AddBigButton(b2, _w2, _h)) {}
			ImGui::SameLine();
			if (AddBigButton(b3, _w2, _h)) {}

			// Or using raw ImGui
			// Three widgets and fit width in one line
			if (ImGui::Button("START", ImVec2(_w3, _h))) {}
			ImGui::SameLine();
			if (ImGui::Button("STOP", ImVec2(_w3, _h))) {}
			ImGui::SameLine();
			if (ImGui::Button("REPLAY", ImVec2(_w3, _h))) {}
		}
	}
	guiManager.endWindow();
}