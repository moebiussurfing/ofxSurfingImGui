#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setupFonts() {
	// NOTE: We can add font manually pushing "Add Font" button.
	// then we can pick a default font setting "Font Index".
	// this is for testing styles.

	// NOTE: Then, we can add by code too to set hardcoded.
	// Push some fonts:

	std::string _fontName;
	float _fontSize;
	std::string _path = "assets/fonts/"; // assets folder

	// #0
	_fontName = "telegrama_render.otf";
	_fontSize = 12;
	guiManager.pushFont(_path + _fontName, _fontSize);
	// #1
	_fontName = "OpenSans-Bold.ttf";
	_fontSize = 14;
	guiManager.pushFont(_path + _fontName, _fontSize);
	// #2
	_fontName = "OpenSans-Light.ttf";
	_fontSize = 18;
	guiManager.pushFont(_path + _fontName, _fontSize);
	// #3
	_fontName = "overpass-mono-bold.otf";
	_fontSize = 20;
	guiManager.pushFont(_path + _fontName, _fontSize);

	int amt = guiManager.getNumFonts();
	fontSize.set("Font Size", 10, 6, 30);
	fontIndex.set("Font Index", 0, 0, amt - 1);
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(1920, 25);

	//-

	guiManager.setImGuiAutodraw(true); // -> required when only one single ImGui instance is instantiated on all the oF project.
	guiManager.setup(); // ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).

	// Pick another theme
	//ofxImGuiSurfing::ImGui_ThemeSequentity();

	guiManager.bAutoResize = false;

	//-

	setupFonts();

	//--

	// ofParameters
	params1.setName("paramsGroup1");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params1.add(bMode1.set("Mode1", false));
	params1.add(bMode2.set("Mode2", false));
	params1.add(bMode3.set("Mode3", false));
	params1.add(bMode4.set("Mode4", false));
	params1.add(bPrevious.set("<", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(bNext.set(">", false));
	params2.add(bEnable.set("Enable", false));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params3.add(bMode3.set("Mode3", false));
	params3.add(bMode4.set("Mode4", false));
	params2.add(params3);
	params1.add(params2);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		// Main Window
		drawMainWindow();

		//-----

		// Window 1
		if (bOpen1) drawWindow1();

		//-----

		// Theme editor
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
void ofApp::drawMainWindow() {
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	guiManager.beginWindow("Show Windows", &bOpen0, window_flags);
	{
		ofxImGuiSurfing::ToggleRoundedButton("Theme Editor", &show_app_style_editor);

		if (ImGui::Button("Add Font"))
		{
			guiManager.openFileFont(fontSize);
			fontIndex.setMax(guiManager.getNumFonts() - 1);
		}

		ofxImGuiSurfing::AddIntStepped(fontSize);
		if (ofxImGuiSurfing::AddIntStepped(fontIndex))
		{
			guiManager.setDefaultFontIndex(fontIndex);
		}

		string s = ofToString(fontIndex) + "/" + ofToString(fontIndex.getMax());
		ImGui::Text(s.c_str());

		ofxImGuiSurfing::ToggleRoundedButton("Stylize Fonts", &bStyleFonts); // -> will crash if styles are not queued!

		//-

		ImGui::Dummy(ImVec2(0, 20)); // spacing
		ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);
		ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize); // a public bool variable to allow handle auto-resize. Applied here to all the windows.
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::drawWindow1()
{
	// A window but using my ofxSurfing_ImGui_Manager.h class helper
	// Uses my own simpler helpers: 
	// ofxSurfing_ImGui_Helpers.h
	// Notice that you can add an ofParameterGroup out of a ofxImGui window. 
	// (TODO: but this potentially make troubles yet [WIP] bc getUniqueNames engine!)

	//-

	// Minimal sizes
	float ww = PANEL_WIDGETS_WIDTH_MIN;
	float hh = PANEL_WIDGETS_HEIGHT_MIN;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		guiManager.beginWindow("Window 1", &bOpen1, window_flags);
		{
			{
				// Snippet to handle common widgets sizes:
				float _w1; // full width
				float _w2; // half width
				float _w3; // third width
				float _w4; // quarter width
				float _h; // standard height

				// We will update the sizes on any gui drawing required point, 
				// like inside a new foldered sub-window that could be indendeted and full-width size is being smaller.
				ofxImGuiSurfing::refreshImGui_WidgetsSizes(_w1, _w2, _w3, _w4, _h);

				// Here we will add some ofParamaters usign customized responsive layout of many widgets types!

				//-

				if (!bStyleFonts) ImGui::Text("All widgets using Font #Default:");
				if (bStyleFonts) guiManager.pushStyleFont(0);
				{
					if (bStyleFonts) ImGui::Text("Font #0:");
					ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing

					ImGui::TextWrapped("This Font is a bigger style This is a bigger style This Font is a bigger style This is Font a bigger style This is a bigger style ");

					// Two custom toggles
					if (ofxImGuiSurfing::AddBigToggle(bEnable)) {} // this is full width (_w1) with standard height (_h)
					if (ofxImGuiSurfing::AddBigToggle(bMode4, _w1, _h)) {} // same width but half height

					ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing
				}
				if (bStyleFonts) guiManager.popStyleFont();

				//-

				if (bStyleFonts) guiManager.pushStyleFont(3);//Take care not pushing a non existing index or it will crash!
				{
					if (bStyleFonts) ImGui::Text("Font #3:");
					ImGui::TextWrapped("This is a bigger style This is a Font bigger style This is a bigger Font style This is a bigger style Font This is a bigger style ");
					//ImGui::TextWrapped("This Font is a bigger style This is a bigger style This Font is a bigger style This is Font a bigger style This is a bigger style ");
				}
				if (bStyleFonts) guiManager.popStyleFont();

				//-

				if (bStyleFonts) guiManager.pushStyleFont(1);
				{
					if (bStyleFonts) ImGui::Text("Font #1:");
					if (ofxImGuiSurfing::AddBigButton(bPrevious, _w2, _h))
					{
						lineWidth -= 0.1;
						separation -= 2;
						bPrevious = false;
					}
					ImGui::SameLine();
					if (ofxImGuiSurfing::AddBigButton(bNext, _w2, _h))
					{
						lineWidth += 0.1;
						separation += 2;
						bNext = false;
					}
					ImGui::TextWrapped("This Font is a bigger style This is a bigger style This Font is a bigger style This is Font a bigger style This is a bigger style ");
				}
				if (bStyleFonts) guiManager.popStyleFont();

				ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing

				//-

				if (bStyleFonts) guiManager.pushStyleFont(2);
				{
					if (bStyleFonts) ImGui::Text("Font #2:");
					ofxImGuiSurfing::AddParameter(bMode2);
					ofxImGuiSurfing::AddParameter(separation);
					ImGui::TextWrapped("This Font is a bigger style This is a bigger style This Font is a bigger style This is Font a bigger style This is a bigger style ");
					ofxImGuiSurfing::AddParameter(shapeType);
					ofxImGuiSurfing::AddParameter(amount2);
					ofxImGuiSurfing::AddParameter(bMode4);
				}
				if (bStyleFonts) guiManager.popStyleFont();

				ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing
			}
		}
		guiManager.endWindow();
	}
	ImGui::PopStyleVar();
}
