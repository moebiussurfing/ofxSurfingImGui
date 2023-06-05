#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(1, true, true);

	ui.setup();

#ifdef CUSTOM_FONTS
	// Load all the fonts of a folder
	string p = "/assets/fonts2/";
	float size = 12;
	ui.pushFontsFromFolder(p, size);

	// Load another single font
	p = "/assets/fonts2/Inter-Black.ttf";
	size = 17;
	string label = "Inter-Black_" + ofToString(size);
	ui.pushFont(p, size, label);
#endif

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
		IMGUI_SUGAR__WINDOWS_CONSTRAINTS_MEDIUM;

		if (ui.BeginWindow("ofApp"))
		{
			ui.Add(e.bGui, OFX_IM_TOGGLE_ROUNDED_BIG);
			string s = "Note that these widgets are not affected by the selected index font!";
			ui.AddLabel(s);
			ui.AddSpacingBigSeparated();

			ui.DrawWidgetsFonts();
			ui.AddSpacingBig();

			ui.PushFontByIndex();
			{
				// Select day/night theme

				// A. A simple toggle
				//ui.DrawWidgetsTheme();

				// B. A custom combo
				ui.AddLabel("THEME");
				ui.AddThemeToggle();
				ui.AddSpacingBig();

				string s = "Font: " + ofToString(ui.getFontIndex()) + "/" + ofToString(ui.getAmountFonts() - 1);
				ui.AddLabel(s);
				ui.AddSpacing();

				ui.AddLabel(ui.getFontIndexName());
			}
			ui.PopFontByIndex();

			ui.EndWindow();
		}

		//--

		// The Editor Windows

#ifdef CUSTOM_FONTS
		// Apply font styles
		ui.PushFontByIndex();

		e.draw();

		ui.PopFontByIndex();
#else 
		e.draw();

#endif
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	ofLogNotice("ofApp") << "keyPressed: " << (char)key;

	if (0) {}

	else if (key == OF_KEY_LEFT)
	{
		int i = ui.getFontIndex();
		if (i > 0) i--;
		ui.setFontIndex(i);
	}

	else if (key == OF_KEY_RIGHT)
	{
		int i = ui.getFontIndex();
		if (i < ui.getAmountFonts() - 1) i++;
		ui.setFontIndex(i);
	}
};