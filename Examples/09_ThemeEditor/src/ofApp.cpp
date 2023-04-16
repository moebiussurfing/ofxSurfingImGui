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

	//TODO: not working
	//ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingBlue();
	//e.loadThemeHardcoded(5);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		e.draw();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	ofLogNotice() << "Key: " << (char)key;

	//Here we can see how to load the created themes into your app.
	//Do not requires to instantiate the editor in every app to use the themes.
	//We will see different approaches.

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