#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    // move window to my left monitor and portrait
    ofxImGuiSurfing::setMonitorsLayout(-1, true, true);

    //--

    ui.setup();

    // Optional customizations
    // Custom path for multinstances
    // or to organize bin/data
    // bigTextInput.setPathGlobal("Gpt");
    // bigTextInput.setName("Prompt");
    // Change the hint text:
    // bigTextInput.setHint("Type search");

    ui.setDisableStartupResetLayout();
    //small trick to disable auto layout
    //this default behavior is not desired here with this big widget!

    //--

    // Callback to get the submitted text

#ifdef USE_ADVANCED_CALLBACK
    // Advanced callback
    // Easy approach:
    // we can use the public
    // ofParameter<string> bigTextInput.textInput
    // Using his listener!
    callback_t myFunctionCallback = std::bind(&ofApp::doCallbackAttend, this);
    //std::function<void()> myFunctionCallback = std::bind(&ofApp::doCallbackAttend, this);
    bigTextInput.setFunctionCallbackSubmit(myFunctionCallback);
#else
    // There's another ofParam based callback approach

    // A. Listener to the internal ofParam:
    e = bigTextInput.textInput.newListener([this](string& s)
    {
        doCallbackAttend();
    });
    // B. Using a local ofParameter<string> and makeReferenceTo.
    // and then to create a listener to him:
    // ptext.makeReferenceTo(bigTextInput.textInput);
#endif
}

//--------------------------------------------------------------
void ofApp::doCallbackAttend()
{
    text = bigTextInput.getText();
    ofLogNotice(__FUNCTION__) << text;
    ui.AddToLog("ofApp -> TextInput: " + text, OF_LOG_NOTICE);

    v = 1;
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // Bg
    {
        int bgmin = 100;
        if (v > 0) v -= 0.05f;
        else v = 0;
        ofClear(bgmin + (255 - bgmin) * v);
        // if (v == 0) ofClear(ofColor::yellow);
        // else ofClear(bgmin + (255 - bgmin) * v);
    }

    //--

    drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
    ui.Begin();
    {
        if (ui.BeginWindow(bGui))
        {
            ui.AddMinimizerToggle();
            if (ui.isMaximized())
            {
                ui.AddLogToggle();
                ui.AddDebugToggle();
                ui.AddAutoResizeToggle();
                ui.AddSpacingBigSeparated();

                //--

                // TextInput
                ui.Add(bigTextInput.bGui, OFX_IM_TOGGLE_ROUNDED);
                ui.Add(bigTextInput.bGui_Config, OFX_IM_TOGGLE_ROUNDED);
            }

            ui.EndWindow();
        }

        // TextInput
        bigTextInput.draw(ui);
    }
    ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // ignore keys
    if (ui.isOverInputText()) return;
    if (ui.isOverGui()) return; // could be commented if preferred

    if (key == 'g')
    {
        bGui = !bGui;

        //workflow
        if (!bGui && bigTextInput.bGui_Config)
            bigTextInput.bGui_Config = 0;
    }

    if (key == 'd') bigTextInput.bDebug = !bigTextInput.bDebug;
}
