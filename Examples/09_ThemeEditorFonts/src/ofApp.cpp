#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofxSurfingHelpers::setMonitorsLayout(-1, true, true);

    ui.setup();

    // f.setup(ui);

    //--

    // Theme Editor
    e.setPathGlobal(ui.getPath());
    e.setUiPtr(&ui);
    e.setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
    f.update(ui);
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
        }

        //--

        // Select day/night theme

        // A. A simple toggle
        ui.DrawWidgetsTheme();

        // // B. A custom combo
        // ui.AddLabelBig("THEME");
        // ui.AddThemeToggle();

        ui.EndWindow();
    }

    //--

    f.drawImGui(ui);

    //--

    // The Editor Windows
    // Apply picked as font style
    ui.PushFontByIndex();
    {
        ImGui::Begin("MyDemoWindow");
        ImGui::Text("Hello World");
        ImGui::Button("Button");
        ImGui::End();

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
