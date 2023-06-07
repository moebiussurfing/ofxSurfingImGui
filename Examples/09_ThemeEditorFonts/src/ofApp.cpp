#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(-1, true, true);

	ui.setup();

#ifdef CUSTOM_FONTS

	string label;
	float size;
	string p;

	//// Recreate and build default styles for the font: 
	//// Note that default font is FONT_DEFAULT_FILE "JetBrainsMono-Bold.ttf"
	//ui.BuildFontStyles("/assets/fonts2/Montserrat-Black.ttf", 13.f);

	// Load all the fonts of a folder
	// will add more fonts.
	p = "/assets/fonts2/";
	size = 12;
	ui.pushFontsFromFolder(p, size);

	// Load another single font
	p = "/assets/fonts2/Inter-Black.ttf";
	size = 13;
	label = "Inter-Black_" + ofToString(size);
	ui.pushFont(p, size, label);

	// Load another single font
	p = "/assets/fonts2/Inter-Black.ttf";
	size = 17;
	label = "Inter-Black_" + ofToString(size);
	ui.pushFont(p, size, label);

#endif

	//--

	// Theme Editor
	e.setPathGlobal(ui.getPath());
	e.setUiPtr(&ui);
	e.setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (bBuild) {
		bBuild = 0;

		// Recreate and build default fonts. 
		string p;

		// A. Pass the path hard-coded
		// p = "/assets/fonts2/Inter-Black.ttf";

		// B. Get the path of the selected font by the UI index.
		p = ui.getFontIndexPath();
		ui.BuildFontStyles(p, sizeFont);
	}

	if (bLoadFolder) {
		bLoadFolder = 0;

		// Load all the fonts of a folder
		// will add more fonts.
		ui.clearFonts();
		ui.pushFontsFromFolder("/assets/fonts2/", sizeFont);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		drawImGuiMain();
		drawImGuiDemo(); 
		drawImGuiTest();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawImGuiTest()
{
	IMGUI_SUGAR__WINDOWS_CONSTRAINTSW;

	if (ui.BeginWindow("Test"))
	{
		// font index
		int i;
		// text
		string s;

		i = 0;
		i = ofClamp(i, 0, ui.getAmountFonts() - 1);
		ui.PushFontStyle(i);
		s = "Hello world";
		ImGui::Text(s.c_str());
		s = ui.getFontName(i);
		ImGui::Text(s.c_str());
		ui.PopFontStyle();
		ui.AddSpacingBigSeparated();

		i = 2;
		i = ofClamp(i , 0, ui.getAmountFonts() - 1);
		ui.PushFontStyle(i);
		s = "Hello world";
		ImGui::Text(s.c_str());
		s = ui.getFontName(i);
		ImGui::Text(s.c_str());
		ui.PopFontStyle();
		ui.AddSpacingBigSeparated();

		i = 4;
		i = ofClamp(i , 0, ui.getAmountFonts() - 1);
		ui.PushFontStyle(i);
		s = "Hello world";
		ImGui::Text(s.c_str());
		s = ui.getFontName(i);
		ImGui::Text(s.c_str());
		ui.PopFontStyle();
		ui.AddSpacingBigSeparated();

		i = 10;
		i = ofClamp(i, 0, ui.getAmountFonts() - 1);
		ui.PushFontStyle(i);
		s = "Hello world";
		ImGui::Text(s.c_str());
		s = ui.getFontName(i);
		ImGui::Text(s.c_str());
		ui.PopFontStyle();
		ui.AddSpacingBigSeparated();

		i = ui.getAmountFonts() - 1;
		i = ofClamp(i, 0, ui.getAmountFonts() - 1);
		ui.PushFontStyle(i);
		s = "Hello world";
		ImGui::Text(s.c_str());
		s = ui.getFontName(i);
		ImGui::Text(s.c_str());
		ui.PopFontStyle();

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiMain()
{
	//IMGUI_SUGAR__WINDOWS_CONSTRAINTSW;

	if (ui.BeginWindow("ofApp"))
	{
		string s;

		ui.AddSpacingBig();
		ui.Add(e.bGui, OFX_IM_TOGGLE_ROUNDED_BIG);
		ui.AddSpacingBigSeparated();
		ui.AddAutoResizeToggle();
		ui.AddSpacingBig();

		//--

		// Select day/night theme

		// A. A simple toggle
		//ui.DrawWidgetsTheme();

		// B. A custom combo
		ui.AddLabelBig("THEME");
		ui.AddThemeToggle();
		ui.AddSpacingBigSeparated();

		//--

		// List default styles/sizes from the default font.
		s = "Default Font Styles:\n";
		ui.AddLabelBig(s);
		s = ui.getFontName(3) + "\n";
		s += ui.getFontName(2) + "\n";
		s += ui.getFontName(1) + "\n";
		s += ui.getFontName(0) + "\n";
		ui.AddLabel(s);
		ui.AddSpacingBig();

		ui.AddLabelHugeXXL("Huge_XXL");
		ui.AddLabelHuge("Huge");
		ui.AddLabelBig("Big");
		ui.AddLabel("Default");
		ui.AddSpacingBig();
		ui.AddSpacingBigSeparated();

		s = "NOTE \n\n";
		s += "These widgets are not affected by the selected index font!\n\n";
		s += "There are four style/sizes for the same default font,\n";
		s += "used by ui.AddLabel/Big/Huge/Huge_XXL methods.\n";
		s += "Styles: DEFAULT, BIG, HUGE AND HUGE_XXL.\n\n";
		s += "To replace the default font, \nwe would need to load another font and re build.\n";
		s += "The four styles will be created.\n";
		ui.AddLabel(s);

#ifdef CUSTOM_FONTS
		ui.AddSpacingBigSeparated();
		s = "PRELOADED FONTS";
		ui.AddLabelBig(s);
		s = "FONT " + ofToString(ui.getFontIndex()) + "/" + ofToString(ui.getAmountFonts() - 1);
		ui.AddLabel(s);
		ui.AddSpacing();
		ui.DrawWidgetsFonts();
		ui.AddSpacing();
		ui.PushFontByIndex();
		{
			string t = (ui.getFontIndexName());
			ImGui::TextWrapped("%s", t.c_str());
		}
		ui.PopFontByIndex();
		ui.AddSpacingBigSeparated();

		//--

		// Clear and reload folder font files
		if (ui.AddButton("Load Fonts", OFX_IM_BUTTON_BIG)) {
			bLoadFolder = 1; // flag to execute out of the ImGui render
		}
		s = "Clear pre loaded fonts and \nload all font files from the folder: \n/assets/fonts2/";
		s += "\nSize will be applied from sizeFont variable.";
		ui.AddTooltip(s);
		ui.AddSpacingBigSeparated();

		// Re build the styles 
		// for a new default font
		ui.AddTooltip("Font size for DEFAULT style. \nThe other will be scaled bigger.");
		if (ui.AddButton("Build Default and styles", OFX_IM_BUTTON_BIG)) {
			bBuild = 1; // flag to execute out of the ImGui render
		}
		s = "Picked font will generate the \nDEFAULT, BIG, HUGE AND HUGE_XXL styles.";
		s += "\nWill use as default font the picked font: \n\n" + ui.getFontIndexName();
		ui.AddTooltip(s);
		ui.Add(sizeFont, OFX_IM_STEPPER);
		s = "Browse the pre added fonts and pick the new default font. ";
		s += "\nRe build the styles for the new default font.";
		ui.AddLabel(s);
#endif

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImGuiDemo()
{
	// The Editor Windows

	// Apply font styles
#ifdef CUSTOM_FONTS
	ui.PushFontByIndex();

	e.draw();

	ui.PopFontByIndex();
#else 
	e.draw();

#endif
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