#pragma once

/*
 
    This example shows how to explore many fonts and styles on runtime, 
    to fine tune your app ui.
    Default font file and size will be serialized into data folder:
    \Examples\09_ThemeEditorFull\bin\data\Gui\DefaultFont.json

    BTW, is not necessary to instantiate SurfingThemeEditor to change
    the default font. It's just a kind of tool for exploring possibilities,
    trying different font styles.
    
    As you can see on the 09_ThemeEditor, 
    you can hard-code a default font replacement doing:

    ui.setDefaultFont(ofToDataPath("assets/fonts/telegrama_render.otf"), 14);

*/

//--

#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "surfingThemeEditor.h"
#include "SurfingFonts.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofxSurfingGui ui;

    SurfingThemeEditor e;
    SurfingFonts f;
};
