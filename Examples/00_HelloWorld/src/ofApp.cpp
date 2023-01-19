#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::draw()
{
    ui.Begin();
    {
        /* Put windows here */

        if (ui.BeginWindow(bGui))
        {
            /* Put widgets here */

            ui.AddLabelBig("Hello World");
            ui.Add(bEnable, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
            ui.Add(speed, OFX_IM_HSLIDER_MINI);
            ui.AddSpacingSeparated();
            ui.AddGroup(params, SurfingGuiGroupStyle_Collapsed);

            ui.EndWindow();
        }
    }
    ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) 
{
	if (key == ' ') bGui = !bGui;
}