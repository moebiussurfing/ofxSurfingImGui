#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    // move window to my left monitor and portrait
    ofxImGuiSurfing::setMonitorsLayout(-1, true, true);

    //--

    //ui.setImGuiViewPort();
    ui.setup();

    // Optional customizations
    // Custom path for multi-instances 
    // avoid "collide folders".
    // or to organize bin/data
    // bigTextInput.setPathGlobal("Gpt");
    // bigTextInput.setName("Prompt");
    // Change the hint text:
    // bigTextInput.setHint("Type search");
    // Change the submit button text:
     //bigTextInput.setSubmit("Send");

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
    callback_t myFunctionCallbackSubmit = std::bind(&ofApp::doAttendCallback, this);
    bigTextInput.setFunctionCallbackSubmit(myFunctionCallbackSubmit);
#else
    // There's another ofParam based callback approach

    // A. Listener to the internal ofParam:
    e = bigTextInput.textInput.newListener([this](string& s)
    {
        doAttendCallback();
    });

    // B. Using a local ofParameter<string> and makeReferenceTo.
    // and then to create a listener to him:
    // ptext.makeReferenceTo(bigTextInput.textInput);
    //e = ptext.newListener([this](string& s)
    //{
    //    doAttendCallback();
    //});
#endif
}

//--------------------------------------------------------------
void ofApp::doAttendCallback()
{
    // will be called when submitted text changed!
    text = bigTextInput.getText();
    ofLogNotice(__FUNCTION__) << text;
    ui.AddToLog("ofApp -> TextInput: " + text, OF_LOG_NOTICE);
    ofSetWindowTitle(text);

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
                ui.Add(bigTextInput.bGui, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
                ui.Add(bigTextInput.bGui_Config, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
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
