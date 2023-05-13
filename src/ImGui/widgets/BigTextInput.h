/*
 *
 *  BigTextInput.h
 *  
 *  This widget is a big text input widget.
 *  Useful to integrate text like prompts.
 *  Features single line with hint and multiline.
 *  Style customizations.
 *  Responsive layout.
 *  Persistent settings.
 *
 */

#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "imgui_stdlib.h"

// Required for custom callback when submit button pressed
#include <functional>
using callback_t = std::function<void()>;

class BigTextInput
{
public:
    //TODO: improve API for ofParam strings
    //ofParameter<string> textA{ "TextA","" };
    //ofParameter<string> textB{ "TextB","" };
    //ofParameter<string> textC{ "TextC","" };

public:
    BigTextInput()
    {
        ofAddListener(ofEvents().update, this, &BigTextInput::update);
        ofAddListener(ofEvents().windowResized, this, &BigTextInput::windowResized);
    }

    ~BigTextInput()
    {
        exit();
    }

public:
    ofParameter<string> textInput{"Text", ""}; //last submit text
    //could be used as receiver/destination of the input text widget
    //and also the event listener toi be used as callback
    //to be notified and to receive/get the submitted text.

    ofParameter<bool> bGui{"TextInput", true}; //show widget
    ofParameter<bool> bGui_Config{"Config TextInput", false}; //show config
    ofParameter<bool> bDebug{"Debug", false}; //debug/edit mode

private:
    ofParameterGroup params{"TextInputBubble"};
    ofParameter<bool> bGui_Global{"BigTextInput", true}; //TODO:

private:
    ofParameterGroup g{"BigTextInput"};
    ofParameter<bool> bGui_Headers{"Headers", true};
    ofParameter<bool> bGui_Bg{"Bg", true};
    ofParameter<bool> bGui_ResizePin{"Resizer", true};
    ofParameter<bool> bGui_LockMove{"Lock", false};

    ofParameter<bool> bLabel{"Label", false}; //TODO:
    ofParameter<int> szFont{"Font Size", 0, 0, 3};
    ofParameter<float> rounded{"Rounded", 0, 0, 1};

    ofParameter<float> heightReset{"Height", 0, 0, 1};
    ofEventListener eHeightReset;
    ofParameter<float> padxReset{"PadWindow", 0, 0, 1};
    ofEventListener ePadxReset;

    ofParameter<ofColor> colorBubble{"C Bg", ofColor::grey, ofColor(), ofColor()};
    ofParameter<bool> bShadow{"Shadow", false};

    ofParameterGroup paramsShadow{"Shadow"};
    ofParameter<ofColor> colorShadow{"C Shadow", ofColor::black, ofColor(), ofColor()};
    ofParameter<glm::vec2> positionshadow{"Pos", glm::vec2(0), glm::vec2(0), glm::vec2(1.f)};
    ofParameter<float> padBubbleX{"PadBubbleX", 0.f, 0, 1};
    ofParameter<float> padBubbleY{"PadBubbleY", 0.f, 0, 1};
    ofParameter<float> padTextX{"PadTextX", 0.f, 0, 1};
    ofParameter<float> padSubmitBut{"PadSubmit", 1.f, 0, 1};
    ofParameter<float> padTextY{"PadTextY", 0.f, -1, 1};
    ofParameter<int> typeInput{"Type", 0, 0, 2};
    ofParameter<string> typeInputName{"TypeName", ""};
    ofEventListener eTypeInput;
    vector<string> typeInputNames{"InputText", "InputTextWithHint", "InputTextMultiline"};

    // ofParameter<void> vResetBubble{"Reset"};
    // ofEventListener eResetBubble;
    // bool bResetBubble = 0;

    bool bBlink = 1; //hint text bubble blink when empty
    bool bIntegrate = 1; //put the intenal input text transparent
    bool bButtons = 0; //alternative buttons//TODO:

    ofEventListener eDebug;
    bool bFlagResetWindow = 0;

    string strHint = "Prompt";
    string strLabel = "TextInput";

private:
    //settings file
    string path_Global = ""; //main folder where nested folder goes inside
    string path_Settings = "BigTextInput_Settings.json";

public:
    void setPathGlobal(std::string path)
    {
        path_Global = path;
        ofxImGuiSurfing::CheckFolder(path_Global);
    }

    void setName(std::string name)
    {
        g.setName(name);
        bGui.setName(name);

        string s = name;
        s += ofToString("_Settings.json");
        path_Settings = s;

        ofxImGuiSurfing::CheckFolder(path_Global);
    }

public:
    void setHint(string s) { strHint = s; };
    void setLabel(string s) { strLabel = s; };

    //--

    // Advanced submit callback
private:
    // Pointer to store a function
    callback_t functionCallbackSubmit = nullptr;
    //std::function<void()> functionCallbackSubmit = nullptr;

public:
    // To get the text when notified.
    string getText() const { return textInput.get(); }

    void setFunctionCallbackSubmit(callback_t f = nullptr)
    {
        functionCallbackSubmit = f;
    }

private:
    void doSubmit(string s)
    {
        textInput = s;
        ofLogNotice("ofxSurfingImGui::doSubmit") << s;

        // Trigs callback to parent / ofApp
        if (functionCallbackSubmit != nullptr) functionCallbackSubmit();
    }

    //--

private:
    bool bDoneSetup = 0;
    bool bDoneStartup = 0;

    void setup()
    {
        typeInputName.setSerializable(false);
        bDebug.setSerializable(false);

        g.add(bGui);
        g.add(bGui_Config);
        g.add(bGui_Headers);
        g.add(bGui_Bg);
        g.add(bGui_ResizePin);
        g.add(bGui_LockMove);
        g.add(bDebug);

        params.add(rounded);
        params.add(colorBubble);
        params.add(szFont);
        params.add(padBubbleX, padBubbleY);
        params.add(padTextX);
        params.add(padSubmitBut);
        params.add(padTextY);
        params.add(typeInput);
        params.add(typeInputName);
        params.add(bLabel);
        paramsShadow.add(bShadow);
        paramsShadow.add(colorShadow);
        paramsShadow.add(positionshadow);
        params.add(paramsShadow);
        params.add(heightReset);
        params.add(padxReset);
        // params.add(vResetBubble);
        g.add(params);

        // eResetBubble = vResetBubble.newListener([this]()
        // {
        //     bResetBubble = 1;
        // });

        eTypeInput = typeInput.newListener([this](int& v)
        {
            switch (typeInput.get())
            {
            case 0: typeInputName = typeInputNames[0];
                break;
            case 1: typeInputName = typeInputNames[1];
                break;
            case 2: typeInputName = typeInputNames[2];
                break;
            default: typeInputName = "unknown";
                break;
            }
        });

        //workflow: edit
        eDebug = bDebug.newListener([this](bool& b)
        {
            bGui_Headers = bDebug;
            bGui_ResizePin = bDebug;
            bGui_Bg = bDebug;
            bIntegrate = !bDebug;
        });

        eHeightReset = heightReset.newListener([this](float& v)
        {
            doFlagResetWindow();
        });
        ePadxReset = padxReset.newListener([this](float& v)
        {
            doFlagResetWindow();
        });

        //default 
        // doResetConfig();
        doResetAll();

        //--

        bDoneSetup = 1;
    }

    void startup()
    {
        string s;
        if (path_Global == "") s = path_Settings;
        else s = path_Global + "/" + path_Settings;
        ofxImGuiSurfing::loadGroup(g, s);

        //--

        bDoneStartup = 1;
    }

    void exit()
    {
        ofRemoveListener(ofEvents().update, this, &BigTextInput::update);
        ofRemoveListener(ofEvents().windowResized, this, &BigTextInput::windowResized);

        string s;
        if (path_Global == "") s = path_Settings;
        else s = path_Global + "/" + path_Settings;
        ofxImGuiSurfing::saveGroup(g, s);
    }

    void update(ofEventArgs& args)
    {
        // if (ofGetFrameNum() < 1) return;

        if (!bDoneSetup) setup();
        else if (!bDoneStartup)
        {
            startup();
        }
    }

    void windowResized(ofResizeEventArgs& resize)
    {
        doFlagResetWindow();
        ofLogNotice("ofxSurfingImGui::windowResized") << resize.width << "," << resize.height;
    }
    
public:
    void draw(ofxSurfingGui& ui)
    {
        // Init Style
        static bool b = 0;
        if (!b)
        {
            b = 1;
            ui.AddStyle(typeInputName, OFX_IM_TEXT_DISPLAY); //hide label. disable input mode.
            ui.AddStyleGroup(paramsShadow, OFX_IM_GROUP_COLLAPSED);
            // ui.AddStyle(vResetBubble, OFX_IM_BUTTON_BIG);
        }

        //--

        drawImGui_Config(ui);
        drawImGui_Widget(ui);
    }

private:
    // Configuration window
    // Settings will be presistent
    void drawImGui_Config(ofxSurfingGui& ui)
    {
        if (!bGui_Config) return;

        if (ui.BeginWindow(bGui_Config))
        {
            if (ui.isMaximized())
            {
                ui.AddLabelBig("Window");
                ui.Add(bGui_Headers, OFX_IM_TOGGLE_ROUNDED);
                ui.Add(bGui_Bg, OFX_IM_TOGGLE_ROUNDED);
                ui.Add(bGui_ResizePin, OFX_IM_TOGGLE_ROUNDED);
                ui.Add(bGui_LockMove, OFX_IM_TOGGLE_ROUNDED);
                ui.AddSpacingBigSeparated();
            }

            ui.Add(bGui, OFX_IM_TOGGLE_ROUNDED);
            ui.AddSpacing();
            ui.AddGroup(params);
            ui.AddSpacing();

            if (ui.AddButton(("Reset Config"), OFX_IM_BUTTON_SMALL))
            {
                doResetConfig();
            }

            /*
            if (ui.AddButton(("Reset Config"), OFX_IM_BUTTON_SMALL, 2))
            {
                doResetConfig();
                // doResetAll();
            }
            ui.SameLine();
            if (ui.AddButton(("Reset Window"), OFX_IM_BUTTON_SMALL, 2))
            {
                //TODO: default
                // heightReset = 0.9;
                // padxReset = 0.2;

                doFlagResetWindow();
            }
            */

            ui.AddSpacing();

            ui.Add(bDebug, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
            if (ui.isMaximized() && bDebug)
            {
                ImGui::Checkbox("Integrate", &bIntegrate);
                ImGui::Checkbox("Buttons", &bButtons);
                ImGui::Checkbox("Blink", &bBlink);
            }

            //TODO: params
            /*
            ui.AddSpacingBigSeparated();
            ui.Add(textA, OFX_IM_TEXT_INPUT);
            ui.AddSpacingBigSeparated();

            ui.Add(textB, OFX_IM_TEXT_INPUT_NAMED);
            ui.AddSpacingBigSeparated();

            ui.Add(textC, OFX_IM_TEXT_INPUT_NO_NAME);
            ui.AddSpacingBigSeparated();
            */

            ui.EndWindow();
        }
    }

    // The main widget!
    void drawImGui_Widget(ofxSurfingGui& ui)
    {
        if (!bGui) return;

        //--

        if (bFlagResetWindow)
        {
            bFlagResetWindow = 0;
            doResetWindow();
        }

        //--

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
        if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
        if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
        if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

        static float x, y, w, h;

        ImVec2 size_min = ImVec2(700, 100);
        ImVec2 size_max = ImVec2(FLT_MAX, FLT_MAX);
        ImGui::SetNextWindowSizeConstraints(size_min, size_max);

        //--

        // if (bResetBubble)
        // {
        //     bResetBubble = 0;
        //     doReset();
        // }

        if (ui.BeginWindow(bGui, window_flags))
        {
            //TODO: remove pad
            // RemoveHeaderHeight();
            //if (!bGui_Headers) ofxImGuiSurfing::AddSpacingY(ImGui::GetStyle().WindowPadding.y);

            if (!bGui_Headers) AddHeaderHeight();

            static string text = "";
            const char* label = strLabel.c_str();
            const char* hint = strHint.c_str();
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;

            //--

            ImGuiInputTextCallback callback = NULL;

            //TODO:
            //std::function<int(ImGuiInputTextCallbackData*)> callback =
            //	[this](ImGuiInputTextCallbackData* data) -> int {
            //	ui.AddToLog(text, OF_LOG_WARNING);
            //	text = "";
            //	return 0;
            //};

            //TODO:
            //ImGuiInputTextCallback callback = [this](ImGuiInputTextCallbackData* data) -> int {
            //	if (data->EventFlag == ImGuiInputTextFlags_EnterReturnsTrue) {
            //		ui.AddToLog(text, OF_LOG_WARNING);
            //		text = "";
            //	}
            //	return 0;
            //};

            //--

            void* user_data = NULL;
            static bool isChanged = false;

            float xx, yy;
            float _wTextBB;
            float _padButtonR;

            w = ImGui::GetContentRegionAvail().x;
            h = ImGui::GetContentRegionAvail().y;

            ui.PushFont(SurfingFontTypes(szFont.get()));
            {
                ImDrawList* draw_list = ImGui::GetWindowDrawList();

                ImVec2 p = ImGui::GetCursorScreenPos();
                ImDrawFlags flags = ImDrawFlags_None;

                //--

                // Bubble

                float pxBubble = padBubbleX * (w * 0.25f);
                float pyBubble = padBubbleY * (h * 0.25f);

                x = p.x + pxBubble;
                y = p.y + pyBubble;

                w -= 2 * pxBubble;
                h -= 2 * pyBubble;

                w -= 2 * padBubbleX;
                h -= 2 * padBubbleY;

                // Bubble bb
                ImRect rBB(x, y, w, h);

                float round = rounded * (h / 2);

                // Shadow
                if (bShadow)
                {
                    ImU32 col2 = ImGui::GetColorU32(colorShadow.get());
                    float _diffMax = h * 0.2;
                    ImVec2 _diff = positionshadow * ImVec2(_diffMax, _diffMax);
                    draw_list->AddRectFilled(rBB.Min + _diff, rBB.Min + _diff + rBB.Max, col2, round);
                }

                // Bubble rect
                ImU32 col = ImGui::GetColorU32(colorBubble.get());
                //ImU32 col = IM_COL32(colorBubble.get().r, colorBubble.get().g, colorBubble.get().b, colorBubble.get().a);
                //ImU32 col = ImGui::GetColorU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                //ImU32 col = IM_COL32(255, 0, 0, 255);
                draw_list->AddRectFilled(rBB.Min, rBB.Min + rBB.Max, col, round);

                float _hTextBB = ui.getWidgetsHeightUnit(); //one line

                // offset to center in the bubble
                xx = ImGui::GetCursorPosX();
                yy = ImGui::GetCursorPosY();

                xx += padTextX * (w * 0.25f);
                //xx += _offsetx;
                xx += pxBubble;

                yy += h / 2;
                yy += padTextY * (h * 0.25f);
                yy += pyBubble;

                float hl = ui.getWidgetsHeightUnit();
                yy -= hl / 2;

                ////TODO:
                //if (bDebug) {
                //	ImRect r2(10, 10, 50, 50);
                //	//ImRect r2(xx, yy, _ww, _hh);
                //	draw_list->AddRect(r2.Min, r2.Min + r2.Max, IM_COL32(255, 0, 0, 255), 0);
                //}

                //float _offsetx = scalex * (w / 2);
                //float _ww = w - 2 * _offsetx;

                //TODO:
                _wTextBB = w;
                _wTextBB -= padTextX * (w * 0.25f);

                _padButtonR = ofMap(padSubmitBut, 1, 0, 0, w * 0.25);
                _wTextBB -= _padButtonR;
                //_wBb -= pxBubble/2;

                //--

                ImGui::SetCursorPosX(xx);
                ImGui::SetCursorPosY(yy);

                //--

                // Text input

                if (!bLabel) label = "##label";
                bool _bBlink = bBlink && (text == "");

                PushItemWidth(_wTextBB);
                {
                    if (_bBlink) ui.BeginBlinkTextDisabled();
                    if (bIntegrate)
                    {
                        ImVec4 c = ImVec4(0, 0, 0, 0); //transparent
                        ImGui::PushStyleColor(ImGuiCol_Border, c);
                        ImGui::PushStyleColor(ImGuiCol_FrameBg, c);
                    }

                    if (typeInput == 0)
                    {
                        // A
                        isChanged = ImGui::InputText(label, &text, flags, callback, user_data);
                    }
                    else if (typeInput == 1)
                    {
                        // B
                        isChanged = ImGui::InputTextWithHint(label, hint, &text, flags, callback, user_data);
                    }
                    else if (typeInput == 2)
                    {
                        // C
                        _hTextBB = 2 * ui.getWidgetsHeightUnit(); //two lines
                        //// int nlines = ofMap(rBB.GetHeight(), 0, ui.getWidgetsHeightUnit())
                        // int nlines = rBB.GetHeight() / ui.getWidgetsHeightUnit();
                        // nlines = MAX(1, nlines + 1);
                        // _hTextBB = nlines * ui.getWidgetsHeightUnit(); //n lines
                        // cout << "nlines:" << nlines << endl;

                        ui.AddSpacingY(-_hTextBB * 0.25);
                        ImVec2 _sz = ImVec2(_wTextBB, _hTextBB);
                        ImGuiInputTextFlags _flags = ImGuiInputTextFlags_None;
                        //_flags |= ImGuiInputTextFlags_CallbackResize;
                        isChanged = ImGui::InputTextMultiline(label, &text, _sz, _flags, callback, user_data);
                    }

                    if (bIntegrate) ImGui::PopStyleColor(2);
                    if (_bBlink) ui.EndBlinkTextDisabled();
                }
                PopItemWidth();

                //--

                // Submit Button
                
                bool bSmallerSizeTextButton = 1;
                if (!bButtons)
                {
                    if (bSmallerSizeTextButton)ui.PushFont(SurfingFontTypes(MAX(0, szFont.get()-1)));

                    string s = "Send";
                    float pad = 40;
                    ImVec2 szButton(pad + ImGui::CalcTextSize(s.c_str()).x, ui.getWidgetsHeightUnit());
                    //TODO: layout

                    float _xx = xx + _wTextBB + 0.2 * szButton.x;
                    float _yy = yy;
                    if (typeInput == 2)
                    {
                        _yy -= hl / 2;
                    }
                    _yy += _hTextBB / 2;
                    _yy -= szButton.y / 2;

                    ImGui::SetCursorPosX(_xx);
                    ImGui::SetCursorPosY(_yy);

                    ImVec4 c = ImGui::GetStyle().Colors[ImGuiCol_Text];
                    ImVec4 _c = ImVec4(c.x, c.y, c.z, c.w * 0.6);
                    ImGui::PushStyleColor(ImGuiCol_Text, _c);

                    if (ImGui::Button(s.c_str(), szButton))
                    {
                        doSubmit(text);
                        text = "";
                    }

                    ImGui::PopStyleColor();

                    if (bSmallerSizeTextButton) ui.popStyleFont();
                }
            }
            ui.popStyleFont();

            //--

            //TODO:
            if (bButtons)
            {
                ImGui::SetCursorPosX(xx);
                //ImGui::SetCursorPosY(yy);

                if (ImGui::Button("Enter"))
                {
                    doSubmit(text);
                }
                ImGui::SameLine();
                if (ImGui::Button("Clear"))
                {
                    if (bDebug) ui.AddToLog("BigTextInput -> Clear", OF_LOG_ERROR);
                    text = "";
                    doSubmit(text);
                }
            }

            // Get enter as submit button
            bool b = ImGui::GetIO().WantTextInput;
            if (b && ImGui::IsKeyPressed(ImGuiKey_Enter))
            {
                doSubmit(text);
                text = "";
            }

            //--

            ui.EndWindow();

            if (isChanged)
            {
                isChanged = 0;
                if (bDebug) ui.AddToLog("BigTextInput -> " + text, OF_LOG_VERBOSE);
            }
        }
    }

    //--

    // Reset
    void doResetAll()
    {
        doResetConfig();
        doFlagResetWindow();
    }

    void doResetConfig()
    {
        //TODO: default
        heightReset = 0.9;
        padxReset = 0.2;

        rounded = .5;
        padBubbleX = padBubbleY = 0;
        padTextX = 0.3;
        padSubmitBut = 0.2;
        typeInput = 1; //hint
        szFont = 2;
        colorBubble = ofColor(32, 255);
        bShadow = true;
        colorShadow = ofColor(32, 64);
        positionshadow = glm::vec2(0.f, 0.25);
        bDebug = 0;
        bButtons = 0;
        bBlink = 0;
    }

    void doFlagResetWindow() { bFlagResetWindow = 1; }

    void doResetWindow()
    {
        //TODO:
        // bool b=0;
        // static float _heightReset = -1;
        // static float _padxReset = -1;
        // if (heightReset != _heightReset) _heightReset = heightReset;
        // if (padxReset != _padxReset) _padxReset = padxReset;
        //
        // //TODO: default
        // heightReset.setWithoutEventNotifications(0.9);
        // padxReset.setWithoutEventNotifications(0.2);

        //--

        float xx, yy, ww, hh, pad; //bubble bb

        //--

        // x

        //to borders
        // pad = 120;
        pad = ofMap(padxReset, 0, 1,
                    0, 0.15 * ofGetWidth(),
                    true);

        xx = pad; //x centered
        ww = ofGetWidth() - (2 * pad); //width

        //--

        // y

        hh = 175; //bubble height

        // yy = ofGetHeight() / 2 - hh / 2; //v centered

        float ho = 0;
        ho += ofxImGuiSurfing::getWidgetsHeightUnit();
        // ho += ImGui::GetWindowHeight() - ImGui::GetContentRegionAvail().y; //header height

        yy = ofMap(heightReset, 0, 1,
                   hh * 0.5 - ho, ofGetHeight() - hh * 0.5,
                   true); //height centered
        yy -= hh * 0.5f;

        ImGuiCond flagsCond = ImGuiCond_None;
        flagsCond |= ImGuiCond_FirstUseEver;
        flagsCond = ImGuiCond_None;

        ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
        ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
    }
};
