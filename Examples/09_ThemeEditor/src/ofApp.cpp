#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(1);

	ui.setup();

	//--

	e.setPathGlobal(ui.getPath());
	e.setUiPtr(&ui);
	e.setup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		// There is a toggle to alternate Night/Day themes.
		// This toggle is available always, 
		// and it will work only if the default files are on bin/data/..
		//IMGUI_SUGAR__WINDOWS_CONSTRAINTS_MEDIUM;
		if (ui.BeginWindow("ofApp"))
		{
			ui.Add(e.bGui, OFX_IM_TOGGLE_ROUNDED);
			ui.AddSpacingSeparated();

			ui.AddLabelBig("Theme");
			ofxImGuiSurfing::AddToggleRoundedButtonNamed(ui.bThemeUiAlt, "Day", "Night");

			string s;
			if (!ui.bThemeUiAlt) s = THEME_NAME_NIGHT;
			else s = THEME_NAME_DAY;
			ui.AddLabel(s);

			ui.EndWindow();
		}

		//--

		// The editor windows
		e.draw();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	ofLogNotice() << "keyPressed: " << (char)key;

	// Here we can see how to load the created themes into your app.
	// Do not requires to instantiate the editor in every app to use the themes.
	// We will see different approaches.

	if (0) {}

	else if (key == '1')
	{
		// Standalone without the editor instantiated.
		// Loading from default themes path:
		// \09_ThemeEditor\bin\data\Gui\themes
		string p = "mygoo.ini";
		ofxImGuiSurfing::SurfingThemes::loadThemeFileByName(p);
	}

	else if (key == '2')
	{
		// To load this file theme:
		// \09_ThemeEditor\bin\data\Gui\themes\t22222.ini

		// We can pass just the filename without path:
		string p = "t22222.ini";

		// A. With the editor instantiated:
		// Will allow to run the theme editor over your app.
		//e.loadThemeFileByName(p);

		// B. Standalone without the editor instantiated:
		ofxImGuiSurfing::SurfingThemes::loadThemeFileByName(p);
	}

	else if (key == '3')
	{
		// Standalone without the editor instantiated:
		// bin/data
		string p = "mytheme2.ini";
		ofxImGuiSurfing::SurfingThemes::loadThemeFile(p);
	}
};