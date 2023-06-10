
/*

	TODO:

	Integrate picked font and sizes into the .ini theme file,

	Add ImGui window/global scale control.

	Clean duplicated and deprecated pushFont methods.

*/


// https://github.com/ocornut/imgui/blob/master/docs/FONTS.md

//--

#include "ofMain.h"
#include "ofxSurfingImGui.h"

class SurfingFonts
{
private:
	SurfingGuiManager* ui = nullptr;

public:
	// Must call before setup()! Requires a local instantiated ui
	void setUiPtr(ofxSurfingGui* _ui) {
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:setUiPtr()";
		ui = _ui;
	}

public:
	SurfingFonts()
	{
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:Constructor()";
	}

	~SurfingFonts()
	{
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:Destructor()";
		exit();
	}

	void setup()
	{
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:setup()";

		// Theme Default Font
		paramsDefaultFont.add(pathFontDefault);
		paramsDefaultFont.add(sizeFontDefault);

		// Helpers
		params.add(bGui);
		params.add(bGui_DebugTestFonts);
		params.add(sizeFont);
		params.add(bMultisize);
		params.add(bAutoBuild);

		pathSettingsDefaultFont = ui->getPathGlobal() + "/" + paramsDefaultFont.getName() + ".json";
		pathSettingsHelpers = ui->getPathGlobal() + "/" + params.getName() + ".json";

		////TODO
		//doLoadFontsFromFolder("/assets/fonts2/");

		loadSettings();
	}

	void loadSettings() {
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:loadSettings()";

		ofxImGuiSurfing::loadGroup(params, pathSettingsHelpers);

		bool b = ofxImGuiSurfing::loadGroup(paramsDefaultFont, pathSettingsDefaultFont);
		if (!b) {
			ofLogWarning("ofxSurfingImGui") << "SurfingFonts:loadSettings() File settings seems not been created yet...";
			return;
		}

		if (pathFontDefault.get() == "") {
			ofLogError("ofxSurfingImGui") << "SurfingFonts:loadSettings() Font file setting empty: " << pathFontDefault.get();
			return;
		}
		if (sizeFontDefault.get() <= 0) {
			sizeFontDefault = 12;
		}

		// Check if file exist
		ofFile f;
		if (!f.doesFileExist(pathFontDefault.get()))
		{
			ofLogError("ofxSurfingImGui") << "SurfingFonts:loadSettings() Font file not found: " << pathFontDefault.get();

			ofLogError("ofxSurfingImGui") << "SurfingFonts:loadSettings() Abort! Load Default instead of file settings!";
			ui->setupFontDefault();
		}
		else doBuildStylesFromFontByPath(pathFontDefault.get(), sizeFontDefault.get());
	}

	void exit() {
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:exit()";

		ofxImGuiSurfing::saveGroup(params, pathSettingsHelpers);

		sizeFontDefault = ui->getFontIndexSize(0);
		pathFontDefault = ui->getFontPath(0);
		ofxImGuiSurfing::saveGroup(paramsDefaultFont, pathSettingsDefaultFont);
	}

	void update()
	{
		if (ui == nullptr) {
			return;
		}
		updateFontsHelper();
	}

	void drawImGui()
	{
		if (!bGui) return;

		drawImGuiThemeFonts();
		drawImGuiDebugTestFonts();
	}

	ofParameter<bool> bGui{"Theme Fonts", true};

private:

	ofParameterGroup params{ "SurfingThemeFonts" };

	// Useful Fonts Helpers
	//ofParameterGroup paramsTester{ "Tester" };
	ofParameter<int> sizeFont{ "sizeFont", 12, 5, 50 };
	ofParameter<bool> bGui_DebugTestFonts{"Debug TestFonts", 1};
	ofParameter<bool> bMultisize{"Multisize", 1};
	ofParameter<bool> bAutoBuild{"AutoBuild", 0};

	// Theme Font
	ofParameterGroup paramsDefaultFont{ "DefaultFont" };
	ofParameter<string> pathFontDefault{"path", ""};
	ofParameter<int> sizeFontDefault{ "size", 12, 5, 100 };

	bool bBuildDefaultFontWithStyles = 0;
	bool bLoadFontsFromFolder = 0;
	bool bPreLoadSomeFonts = 0;
	bool bClearFonts = 0;

	string pathFolderExtraFonts = "/assets/fonts2/";
	string pathSettingsDefaultFont = "";
	string pathSettingsHelpers = "";

	void updateFontsHelper()
	{
		if (bLoadFontsFromFolder)
		{
			bLoadFontsFromFolder = 0;

			doLoadFontsFromFolder();
		}

		//--

		if (bBuildDefaultFontWithStyles)
		{
			bBuildDefaultFontWithStyles = 0;

			doBuildStylesFromFont();
		}

		//--

		//TODO:
		if (bClearFonts)
		{
			bClearFonts = 0;

			doClearFonts();
		}

		//--

		// An example of pushing some fonts
		if (bPreLoadSomeFonts)
		{
			bPreLoadSomeFonts = 0;

			doPreloadSomeFonts();
		}
	}

	void drawImGuiDebugTestFonts()
	{
		if (bGui_DebugTestFonts) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MEDIUM;

		if (ui->BeginWindow(bGui_DebugTestFonts))
		{
			ui->AddSpacing();

			// font index
			int i;

			// text
			string s;
			s = "DEFAULT STYLES";
			if (ui->BeginTree(s))
			{
				ui->AddSpacingBig();

				s = "DEFAULT";
				i = 0;
				if ((i == ui->getFontIndex())) ui->BeginBlinkText();
				ui->DrawImGuiTextWithFontStyle(s, i);
				if ((i == ui->getFontIndex())) ui->EndBlinkText();
				ui->AddSpacingBigSeparated();

				s = "BIG";
				i = 1;
				if ((i == ui->getFontIndex())) ui->BeginBlinkText();
				ui->DrawImGuiTextWithFontStyle(s, i);
				if ((i == ui->getFontIndex())) ui->EndBlinkText();
				ui->AddSpacingBigSeparated();

				s = "HUGE";
				i = 2;
				if ((i == ui->getFontIndex())) ui->BeginBlinkText();
				ui->DrawImGuiTextWithFontStyle(s, i);
				if ((i == ui->getFontIndex())) ui->EndBlinkText();
				ui->AddSpacingBigSeparated();

				s = "HUGE_XXL";
				i = 3;
				if ((i == ui->getFontIndex())) ui->BeginBlinkText();
				ui->DrawImGuiTextWithFontStyle(s, i);
				if ((i == ui->getFontIndex())) ui->EndBlinkText();

				ui->EndTree();
			}

			//--

			if (ui->getAmountFonts() > 4)
			{
				ui->AddSpacingBig();

				s = "EXTRA FONTS\n";
				if (ui->BeginTree(s))
				{
					ui->AddSpacingBig();

					// s = "Hello world";
					int i0 = 4;
					for (int i = i0; i < ui->getAmountFonts(); i++)
					{
						s = ui->getFontName(i);
						//ui->DrawImGuiTextWithFontStyle(s, i, false);

						i = ofClamp(i, 0, ui->getAmountFonts() - 1);
						ui->PushFontStyle(i);
						bool b = (i == ui->getFontIndex());
						if (ui->AddButton(s, b ? OFX_IM_BUTTON_BIG_BORDER_BLINK : OFX_IM_BUTTON_BIG))
						{
							ui->setFontIndex(i);

							//workflow
							if (bAutoBuild) {
								bBuildDefaultFontWithStyles = 1;

								sizeFont = ui->getFontIndexSize(i);
								//string p = ui->getFontIndexPath();
								//ui->BuildStylesFromFont(p, sizeFont);

								//ui->LoadFontsFromFolder(pathFolderExtraFonts, sizeFont, bMultisize);
							}
						}
						ui->PopFontStyle();

						//if (i < ui->getAmountFonts() - 1) ui->AddSpacingBigSeparated();
					}

					ui->EndTree();
				}
			}
			ui->EndWindow();
		}
	}

	void drawImGuiThemeFonts()
	{
		if (bGui) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW;

		if (ui->BeginWindow(bGui))
		{
			string s;

			//--

			if (ui->BeginTree("NOTE"))
			{
				// s = "NOTE \n\n";
				s = "";
				s += "Picked/selected font will apply to the other editor windows.\n\n";
				s += "These widgets are not affected by the selected index font!\n\n";
				s += "There are four style/sizes for the same default font:\n";
				s += "DEFAULT, BIG, HUGE and HUGE_XXL.\n\n";
				s += "Will be used by ui->AddLabel() methods and over widgets text.\n\n";
				s += "To replace the default font, we would need to load another font and re build.\n\n";
				s += "The four styles/sizes will be created based on this font type.\n";
				ui->AddLabel(s);

				ui->EndTree();
			}

			ui->AddSpacingBigSeparated();

			// List default styles/sizes from the default font.
			s = "DEFAULT STYLES\n";
			ui->AddLabelHugeXXL(s);
			ui->AddSpacingBig();

			s = ui->getFontName(0) + "\n";
			s += ui->getFontName(1) + "\n";
			s += ui->getFontName(2) + "\n";
			s += ui->getFontName(3) + "\n";
			ui->AddLabel(s);
			ui->AddSpacingBig();

			ui->AddLabel("DEFAULT");
			ui->AddLabelBig("BIG");
			ui->AddLabelHuge("HUGE");
			ui->AddLabelHugeXXL("HUGE_XXL");
			ui->AddSpacingBig();

			ui->AddSpacingBigSeparated();

			// Useful snippet to copy/paste to your code!
			s = "PRELOADED FONTS";
			ui->AddLabelHugeXXL(s);

			//s = "On this example, these fonts has been added on setup(). ";
			s = "By default, only one default font will be loaded, ";
			s += "but with his four styles/sizes created: \nDEFAULT, BIG, HUGE and HUGE_XXL.\n";
			ui->AddLabel(s);
			ui->AddSpacing();

			s = "FONT " + ofToString(ui->getFontIndex()) + "/" + ofToString(ui->getAmountFonts() - 1);
			ui->AddLabelBig(s);
			ui->AddSpacing();

			// We browse and select the custom index font:
			ui->DrawWidgetsFonts();

			// Move this to drawing part in your code: 
			{
				ui->AddSpacing();
				ui->PushFontByIndex();
				{
					// Here we will draw text with the customized font!
					string t = "";
					t += (ui->getFontIndexName());
					t += "\nHello, World.";
					ImGui::TextWrapped("%s", t.c_str());
				}
				ui->PopFontByIndex();
			}

			ui->AddSpacingBigSeparated();

			//--

			drawImGuiFontHelpers();

			ui->EndWindow();
		}
	}

	void drawImGuiFontHelpers()
	{
		string s;
		s = "FONT HELPERS";
		ui->AddLabelHugeXXL(s);
		ui->AddSpacingBig();

		ui->Add(bGui_DebugTestFonts, OFX_IM_TOGGLE_ROUNDED);
		ui->AddSpacingBig();

		ui->Add(sizeFont, OFX_IM_STEPPER);
		s = ("Font size for DEFAULT style. \nThe other styles (BIG/HUGE/HUGE_XXL)\n");
		s += ("The other styles will be scaled bigger.\n");
		s += ("The rest of the fonts will be added with that size too.\n");
		ui->AddTooltip(s);

		ui->Add(bAutoBuild);
		s = "If enabled, when a font (index) is picked, \nthe default font will be built based on the picked one!";
		ui->AddTooltip(s);

		ui->AddSpacingBig();

		// Clear and reload folder font files
		{
			if (ui->AddButton("Load Folder Fonts", OFX_IM_BUTTON_BIG))
			{
				bLoadFontsFromFolder = 1; // flag to execute out of the ImGui render
			}
			//s = "Clear all pre loaded and the Default fonts with his styles.\n";
			s = "Loads all the font files from the folder: \n\n";
			s += "/assets/fonts2/\n\n";
			s += "(Size will be applied from sizeFont variable and multi-sized if enabled.)";
			ui->AddTooltip(s);

			ui->Add(bMultisize);
			s = "Allows adding three different sizes to each added font, \nto allow explore your best fit for your app.";
			ui->AddTooltip(s);
		}

		ui->AddSpacingBig();

		// Re Build the styles 
		// for a new default font
		{
			s = "Browse the pre added fonts and pick the new default font. \n";
			s += "Then click Build and the styles for the new default font will be populated.\n";
			s += "The sizeFont variable will be used for the Default style and scaled big to the others!\n";
			ui->AddLabel(s);

			if (ui->AddButton("Build Default Styles", OFX_IM_BUTTON_BIG))
			{
				bBuildDefaultFontWithStyles = 1; // flag to execute out of the ImGui render
			}
			s = "The above picked font: \n\n";
			s += ui->getFontIndexName() + "\n";
			s += "(Using sizeFont " + ofToString(sizeFont.get(), 0) + "px)\n\n";
			s += "Will be loaded as Default \nand will generate the four styles:\n";
			s += "DEFAULT, BIG, HUGE and HUGE_XXL\n";
			ui->AddTooltip(s);
		}

		ui->AddSpacingBig();

		if (ui->AddButton("Clear Fonts", OFX_IM_BUTTON_BIG))
		{
			bClearFonts = 1; // flag to execute out of the ImGui render
		}
		s = "Clear all fonts and loads the default and hard-coded font. \nThen creates the four styles.\n";
		s += "Then you should click 'Load Fonts from folder' \nto add new fonts to explore.";
		ui->AddTooltip(s);

		ui->AddSpacingBig();

		if (ui->BeginTree("HELP"))
		{
			s = "";
			s += "1. Set a sizeFont. Default is 12px.\n";
			s += "2. Optionally, activate 'Multisize' \nto add three scaled fonts per file.\n";
			s += "3. Click 'Load Folder Fonts'.\n";
			s += "4. Optionally, activate 'AutoBuild'. \nThat enables auto build when a font is picked!\n";
			s += "5. Pick a font to be settled as Default. \nYou can use the combo/drop-down list, the arrows or clicking on 'Debug TestFont' window widgets.\n";
			s += "6. Click 'Build Default Styles'. \nWill create the four styles for the picked font.\n";
			ui->AddLabel(s);

			ui->EndTree();
		}

		ui->AddSpacingBigSeparated();

		//--

		// Example. Pre reload some fonts
		s = "Another Example \nfor custom fonts combinations:";
		ui->AddLabelBig(s, true);
		{
			if (ui->AddButton("Example Pre Load", OFX_IM_BUTTON_BIG))
			{
				bPreLoadSomeFonts = 1; // flag to execute out of the ImGui render
			}
			s = "This is a method EXAMPLE \nto see of how to handle many fonts around. \nLook into doPreloadSomeFonts()\n";
			s += "Will add a hard-coded path folder with many fonts with the size of 12px \nand two other files manually with 13px and 17px.";
			ui->AddTooltip(s);
		}
	}

public:

	void setPathForExtraFonts(string path) {
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:setPathForExtraFonts() " << path;
		pathFolderExtraFonts = path;
	}

	void doBuildStylesFromFont()
	{
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:doBuildStylesFromFont()";

		// Recreate and build default fonts. 
		string p;

		// A. Pass the path hard-coded
		// p = "/assets/fonts2/Inter-Black.ttf";

		// B. Get the path of the selected font by the UI index.
		p = ui->getFontIndexPath();
		ui->BuildStylesFromFont(p, sizeFont);

		//workflow
		// reload folder
		if (bAutoBuild) {
			ui->LoadFontsFromFolder(pathFolderExtraFonts, sizeFont, bMultisize);

			//pick first (default style)
			ui->setFontIndex(0);
		}
	}

	void doBuildStylesFromFontByPath(string path, float size)
	{
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:doBuildStylesFromFontByPath()" << path << ", " << size;

		sizeFont = size;

		ui->BuildStylesFromFont(path, sizeFont);

		////workflow
		//// reload folder
		//if (bAutoBuild) {
		//	ui->LoadFontsFromFolder(pathFolderExtraFonts, sizeFont, bMultisize);
		//	//pick first (default style)
		//	ui->setFontIndex(0);
		//}
	}

	void doLoadFontsFromFolder(string path) {
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:doLoadFontsFromFolder()" << path;

		if (path != "") pathFolderExtraFonts = path;
		bLoadFontsFromFolder = 1;
	}

	//TODO:
	void doClearFonts()
	{
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:doClearFonts()";

		ui->clearFonts();

		// almost one font must be loaded to avoid exception!
		ui->setupFontDefault();
		ui->setFontIndex(0);

		//ui->pushFont(OFX_TTF);

		//	/*
		//	//TODO: failing trying to load the default font..
		//	auto& io = ImGui::GetIO();
		//	ImFont*  f = io.Fonts->AddFontDefault();
		//	//f->FontSize = 14;
		//	//f->Scale = 1.f;
		//	//io.Fonts->Build();
		//	//io.FontDefault = f;
		//	*/
	}

	void doLoadFontsFromFolder()
	{
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:doLoadFontsFromFolder()";

		//workflow
		if (pathFolderExtraFonts == "") {
			ofLogWarning("ofxSurfingImGui") << "SurfingFonts:doLoadFontsFromFolder() File path pathFolderExtraFonts is empty.";

			return;
		}

		// Load all the fonts of a folder
		// will add more fonts.
		//TODO:
		//if (!bAutoBuild) ui->clearFonts();
		ui->LoadFontsFromFolder(pathFolderExtraFonts, sizeFont, bMultisize);
	}

	// An Example to see how to load some fonts
	void doPreloadSomeFonts()
	{
		ofLogNotice("ofxSurfingImGui") << "SurfingFonts:doPreloadSomeFonts()";

		string label;
		float size;
		string p;

		//// Recreate and build default styles for the font: 
		//// Note that default font is FONT_DEFAULT_FILE "JetBrainsMono-Bold.ttf"
		//ui->BuildFontStyles("/assets/fonts2/Montserrat-Black.ttf", 13.f);

		// 1. Load all the fonts of a folder
		// will add more fonts.
		p = "/assets/fonts2/";
		size = 12;
		ui->LoadFontsFromFolder(p, size);

		// 2. Load another single font
		p = "/assets/fonts2/Inter-Black.ttf";
		size = 13;
		label = "Inter-Black_" + ofToString(size);
		ui->pushFont(p, size, label);

		// 3. Load another single font
		p = "/assets/fonts2/Inter-Black.ttf";
		size = 17;
		label = "Inter-Black_" + ofToString(size);
		ui->pushFont(p, size, label);
	}
};
