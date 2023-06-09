
/*

    TODO:

    Add a JSON file or integrate picked fonts list and sizes
        into the .ini theme file,
        to overwrite default FONT_DEFAULT_FILE "JetBrainsMono-Bold.ttf"
        from GuiConstants.h

    Add ImGui window/global scale control.

    Clean duplicated and deprecated methods.

*/

//--

#include "ofMain.h"
#include "ofxSurfingImGui.h"

class SurfingFonts
{
public:
    SurfingFonts()
    {
    }

    ~SurfingFonts()
    {
    }

    void setup(SurfingGuiManager& ui)
    {
        // doPreloadSomeFonts(ui);
    }

    void update(SurfingGuiManager& ui)
    {
        updateFontsHelper(ui);
    }

    void drawImGui(SurfingGuiManager& ui)
    {
        if(!bGui) return;
        
        drawImGuiMain(ui);
        drawImGuiDebugTestFonts(ui);
    }

    ofParameter<bool> bGui{"Theme Fonts", true};
    
private:
    // Useful Fonts Helpers
    ofParameter<int> sizeFont{"sizeFont", 12, 5, 50};
    ofParameter<bool> bGui_DebugTestFonts{"Debug TestFonts", 1};
    ofParameter<bool> bMultisize{"Multisize", 0};

    bool bBuildDefaultFontWithStyles = 0;
    bool bLoadFontsFromFolder = 0;
    bool bPreLoadSomeFonts = 0;

    void updateFontsHelper(SurfingGuiManager& ui)
    {
        if (bPreLoadSomeFonts)
        {
            bPreLoadSomeFonts = 0;

            doPreloadSomeFonts(ui);
        }

        if (bLoadFontsFromFolder)
        {
            bLoadFontsFromFolder = 0;

            // Load all the fonts of a folder
            // will add more fonts.
            ui.clearFonts();
            ui.LoadFontsFromFolder("/assets/fonts2/", sizeFont, bMultisize);
        }

        if (bBuildDefaultFontWithStyles)
        {
            bBuildDefaultFontWithStyles = 0;

            // Recreate and build default fonts. 
            string p;

            // A. Pass the path hard-coded
            // p = "/assets/fonts2/Inter-Black.ttf";

            // B. Get the path of the selected font by the UI index.
            p = ui.getFontIndexPath();
            ui.BuildStylesFromFont(p, sizeFont);
        }
    }

    void drawImGuiDebugTestFonts(SurfingGuiManager& ui)
    {
        // IMGUI_SUGAR__WINDOWS_CONSTRAINTSW;

        if (ui.BeginWindow(bGui_DebugTestFonts))
        {
            ui.AddSpacing();

            // font index
            int i;

            // text
            string s;

            // DEFAULT, BIG, HUGE, HUGE_XXL

            // s = "DEFAULT\nSTYLES";
            // ui.AddLabelBig(s);
            // ui.AddSpacingBig();
            // ui.AddSpacingBigSeparated();

            s = "DEFAULT";
            i = 0;
            ui.DrawImGuiTextWithFontStyle(s, i);
            ui.AddSpacingBigSeparated();

            s = "BIG";
            i = 1;
            ui.DrawImGuiTextWithFontStyle(s, i);
            ui.AddSpacingBigSeparated();

            s = "HUGE";
            i = 2;
            ui.DrawImGuiTextWithFontStyle(s, i);
            ui.AddSpacingBigSeparated();

            s = "HUGE_XXL";
            i = 3;
            ui.DrawImGuiTextWithFontStyle(s, i);

            //--

            if (ui.getAmountFonts() > 4)
            {
                ui.AddSpacingBigSeparated();

                s = "EXTRA FONTS\n";
                if (ui.BeginTree(s))
                {
                    ui.AddSpacingBig();

                    // s = "Hello world";
                    int i0 = 4;
                    for (int i = i0; i < ui.getAmountFonts(); i++)
                    {
                        s = ui.getFontName(i);
                        ui.DrawImGuiTextWithFontStyle(s, i, false);

                        if (i < ui.getAmountFonts() - 1) ui.AddSpacingBigSeparated();
                    }

                    ui.EndTree();
                }
            }
            ui.EndWindow();
        }
    }

    void drawImGuiMain(SurfingGuiManager& ui)
    {
        IMGUI_SUGAR__WINDOWS_CONSTRAINTSW;

        if (ui.BeginWindow(bGui))
        {
            string s;

            //--

            // List default styles/sizes from the default font.
            s = "DEFAULT STYLES\n";
            ui.AddLabelHugeXXL(s);
            ui.AddSpacingBig();

            s = ui.getFontName(3) + "\n";
            s += ui.getFontName(2) + "\n";
            s += ui.getFontName(1) + "\n";
            s += ui.getFontName(0) + "\n";
            ui.AddLabel(s);
            ui.AddSpacingBig();

            ui.AddLabelHugeXXL("HUGE_XXL");
            ui.AddLabelHuge("HUGE");
            ui.AddLabelBig("BIG");
            ui.AddLabel("DEFAULT");
            ui.AddSpacingBig();

            ui.AddSpacingBigSeparated();

            if (ui.BeginTree("NOTE"))
            {
                // s = "NOTE \n\n";
                s = "";
                s += "Picked/selected font will apply to the other editor windows.\n\n";
                s += "These widgets are not affected by the selected index font!\n\n";
                s += "There are four style/sizes for the same default font:\n";
                s += "DEFAULT, BIG, HUGE and HUGE_XXL.\n\n";
                s += "Will be used by ui.AddLabel() methods and over widgets text.\n\n";
                s += "To replace the default font, we would need to load another font and re build.\n\n";
                s += "The four styles/sizes will be created based on this font type.\n";
                ui.AddLabel(s);

                ui.EndTree();
            }

            ui.AddSpacingBigSeparated();

            // Useful snippet to copy/paste to your code!
            s = "PRELOADED FONTS";
            ui.AddLabelHugeXXL(s);

            //s = "On this example, these fonts has been added on setup(). ";
            s = "By default, only one default font will be loaded, ";
            s += "but with his four styles/sizes created: \nDEFAULT, BIG, HUGE and HUGE_XXL.\n";
            ui.AddLabel(s);
            ui.AddSpacing();

            s = "FONT " + ofToString(ui.getFontIndex()) + "/" + ofToString(ui.getAmountFonts() - 1);
            ui.AddLabel(s);
            ui.AddSpacing();

            // We browse and select the custom index font:
            ui.DrawWidgetsFonts();

            // Move this to drawing part in your code: 
            {
                ui.AddSpacing();
                ui.PushFontByIndex();
                {
                    // Here we will draw text with the customized font!
                    string t = "";
                    t += (ui.getFontIndexName());
                    t += "\nHello, World.";
                    ImGui::TextWrapped("%s", t.c_str());
                }
                ui.PopFontByIndex();
            }

            ui.AddSpacingBigSeparated();

            //--

            drawImGuiFontHelpers(ui);

            ui.EndWindow();
        }
    }

    void drawImGuiFontHelpers(SurfingGuiManager& ui)
    {
        string s;
        s = "FONT HELPERS";
        ui.AddLabelHugeXXL(s);
        ui.AddSpacingBig();

        ui.Add(bGui_DebugTestFonts, OFX_IM_TOGGLE_ROUNDED);
        ui.AddSpacingBig();

        ui.Add(sizeFont, OFX_IM_STEPPER);
        s = ("Font size for DEFAULT style. \nThe other styles (BIG/HUGE/HUGE_XXL)\n");
        s += ("The other styles will be scaled bigger.\n");
        s += ("The rest of the fonts will be added with that size too.\n");
        ui.AddTooltip(s);

        ui.AddSpacingBigSeparated();

        // Pre reload some fonts
        {
            if (ui.AddButton("Example Pre Load", OFX_IM_BUTTON_BIG))
            {
                bPreLoadSomeFonts = 1; // flag to execute out of the ImGui render
            }
            s = "This is a method EXAMPLE \nto see of how to handle many fonts around. \nLook into doPreloadSomeFonts()\n";
            s += "Will add a hardocded path folder with many fonts with the size of 12px \nand two other files manually with 13px and 17px.";
            ui.AddTooltip(s);
        }

        ui.AddSpacingBigSeparated();

        // Clear and reload folder font files
        {
            if (ui.AddButton("Load Folder Fonts", OFX_IM_BUTTON_BIG))
            {
                bLoadFontsFromFolder = 1; // flag to execute out of the ImGui render
            }
            s = "Clear all pre loaded and the Default fonts with his styles.\n";
            s += "Load all the font files from the folder: \n";
            s += "(Size will be applied from sizeFont variable.)\n\n";
            s += "/assets/fonts2/";
            ui.AddTooltip(s);
            ui.Add(bMultisize);
            s =
                "Allows adding three different sizes to each added font, \nto allow explore your best fit for your app.";
            ui.AddTooltip(s);
        }

        ui.AddSpacingBigSeparated();

        // Re build the styles 
        // for a new default font
        {
            s = "Browse the pre added fonts and pick the new default font. ";
            s += "Then click Build and the styles for the new default font will be populated.\n";
            s += "The sizeFont variable will be used for the Default style and scaled big to the others!\n";
            ui.AddLabel(s);

            if (ui.AddButton("Build Default Styles", OFX_IM_BUTTON_BIG))
            {
                bBuildDefaultFontWithStyles = 1; // flag to execute out of the ImGui render
            }
            s = "The above picked font: \n\n";
            s += ui.getFontIndexName() + "\n\n";
            s += "Will be loaded as Default \nand will generate the four styles:\n";
            s += "DEFAULT, BIG, HUGE and HUGE_XXL\n";
            s += "Click 'Load Fonts from folder' to add new fonts to explore.",
            ui.AddTooltip(s);
        }
    }

    // An Example to see how to load some fonts
    void doPreloadSomeFonts(SurfingGuiManager& ui)
    {
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
        ui.LoadFontsFromFolder(p, size);

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
    }
};
