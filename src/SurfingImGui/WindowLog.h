#pragma once

/*

		This code is initially based on the snippet:
		https://github.com/ocornut/imgui/issues/5796#issuecomment-1288128069
		from @karl0st: https://github.com/karl0st

*/

/*

		TODO:

		remove logLevel. just the colors.

		add constant log to file mode!

		add set public shape size method

		add feature to allow addLog without any explicit tag, but a custom color.
			this is a big upgrade of how it's implemented the engine now.
			could be an "UNKNOWN" tag and storing the color..
			could create an struct of a message: string msg + ofColor color

		add filter by log level as ofLog does

		highlight last message

		improve implemented filter performance.
		could be a little slow bc it handles strings instead of const chars.
		for some situations we should replace by:
		filter search from ImGui Demo
		https://github.com/ocornut/imgui/issues/300
		Better and newer from the ImGui Demo:
		https://github.com/ocornut/imgui/blob/0359f6e94fb540501797de1f320082e4ad96ce9c/imgui_demo.cpp#L6859

		could add log level (>) using the filter tags

		could be instantiated kind of static to be shared between all the ofxSurfingImGui instances ?
			maybe we prefer individual windows with different window name.

*/


//----

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "imgui_stdlib.h"

//TODO: 
// Some widget fails.. recursive includes
// so we can't not use some methods... 
// like pushing font styles...
//#include "ofxSurfingImGui.h"
//#include "ofHelpers.h"
//#include "GuiManager.h"

// This namespace is required to access some widgets helpers used below.
// no other classes are included, so I don't know why they are included.
// maybe bc they are on the project. 
// but some widgets are not found so, I had to add the AddComboAux...

namespace ofxImGuiSurfing
{
    //------

    class SurfingLog
    {
    public:
        SurfingLog()
        {
            // Unlimited mode
            this->clearUnlimited();

            // Buffered mode
            bufferBufferedLimited = std::deque<std::string>();
            this->clearBuffered();

            maxTagLengthSession = maxTagLengthDefault;
            buildTagsDefault();

            // to fix overwrite filter enable on startup
            //indexTagFilter.setSerializable(false);

            params.add(bPause); 
            params.add(bTight); 
            params.add(bSeparators);
            params.add(bOneLine);
            params.add(bAutoScroll);
            params.add(bLimitedBuffered); 
            params.add(amountLinesLimitedBuffered);
            params.add(bOptions);
            params.add(bAutoFit); 
            params.add(bFilter);
            params.add(strFilterKeyword); 
            params.add(bTimeStamp);
            params.add(fontIndex); 
            params.add(indexTagFilter);
            params.add(bHideTags); 
            params.add(bMinimize);

            ofAddListener(params.parameterChangedE(), this, &SurfingLog::Changed_Params);
        }

        ~SurfingLog()
        {
            this->clearUnlimited();
            this->clearBuffered();

            ofRemoveListener(params.parameterChangedE(), this, &SurfingLog::Changed_Params);
        }

        //----

    public:
        void Add(std::string msg, string nameTag)
        {
            // A. search if tag exists
            for (size_t i = 0; i < tags.size(); i++)
            {
                nameTag = strAlign(nameTag);

                if (nameTag == tags[i].name)
                {
                    Add(msg, (int)i);
                    return;
                }
            }

            // B. tag do not exists
            // print as default
            ofLogWarning("ofxSurfingImGui:SurfingLog") << "The tag " << nameTag <<
                " do not exist. We will use the default tag.";
            Add(msg);
        }

        // all the other "add methods" will pass through this main method...
        void Add(std::string msg, int itag = -1)
        {
            if (bPause) return;

            string s = "";

            // Timestamp
            if (bTimeStamp)
            {
                string timeFormat = "%H:%M:%S ";
                //string timeFormat = "%H-%M-%S-%i";//+ms
                //string timeFormat = "%H:%M:%S.%i ";//Protokol style

                s += ofGetTimestampString(timeFormat);

                //s += strSpacer2;//not required bc alignment adds some starting spaces
            }

            //TODO:
            //if (!bHideTags)
            {
                // not passed any tag
                if (itag == -1)
                {
                    s += strEmptyTag;
                    s += strSpacer;
                }
                // a tag has been passed
                else
                {
                    if (itag < tags.size())
                    {
                        s += tags[itag].name;
                        s += strSpacer;
                    }
                }
            }

            // messages
            s += msg;

            //--

            if (!bLimitedBuffered)
            {
                addUnlimited(s);
            }
            else
            {
                addBuffered(s);
            }
        }

        void Add(std::string msg, ofLogLevel logLevel)
        {
            if (logLevel == OF_LOG_VERBOSE && logLevelUi <= OF_LOG_VERBOSE) Add(msg, "VERBOSE");
            else if (logLevel == OF_LOG_NOTICE && logLevelUi <= OF_LOG_NOTICE) Add(msg, "NOTICE");
            else if (logLevel == OF_LOG_WARNING && logLevelUi <= OF_LOG_WARNING) Add(msg, "WARNING");
            else if (logLevel == OF_LOG_ERROR && logLevelUi <= OF_LOG_ERROR) Add(msg, "ERROR");
            else if (logLevel == OF_LOG_FATAL_ERROR && logLevelUi <= OF_LOG_FATAL_ERROR) Add(msg, "ERROR");
            //TODO: add fatal error
            else
            {
                ofLogWarning("ofxSurfingImGui:SurfingLog") << "ofLogLevel " << ofToString((short)logLevel) <<
                    " Unknown";
            }

            //TODO:
            static bool bLogToOF = true;
            if (bLogToOF)
            {
                if (logLevel == OF_LOG_VERBOSE) ofLogVerbose() << msg;
                else if (logLevel == OF_LOG_NOTICE) ofLogNotice() << msg;
                else if (logLevel == OF_LOG_WARNING) ofLogWarning() << msg;
                else if (logLevel == OF_LOG_ERROR) ofLogError() << msg;
                else if (logLevel == OF_LOG_FATAL_ERROR) ofLogFatalError() << msg;
            }
        }

        //----

    public:

        void drawImGui(ofParameter<bool>& bGui)
        {
            if (!bGui) return;

            //--

            if (bRedirect)
            {
                if (_oldStdout)
                {
                    std::string text("");
                    std::getline(_stdout, text);
                    while (text != "")
                    {
                        string s = text + "\n";
                        this->Add(s);

                        //_terminalBuffer += text + '\n';

                        text = "";
                        std::getline(_stdout, text);
                    }
                    _stdout.clear();
                }
            }

            //--

            startupOnce();

            // Minimal window width as default
            float wWindowMin = 400;
            // float wWindowMin = 200;
            
            float hWindowMin;
            float wWidgets = 110; //width for next widgets

            // calculate how many lines are being drawn
            // that depends on modes or settings
            if (bLimitedBuffered)
            {
                if (bAutoFit) amountLinesCurr = bufferBufferedLimited.size();
                else amountLinesCurr = amountLinesLimitedBuffered.get();
            }
            else
            {
                amountLinesCurr = bufferUnlimited.size();
            }

            //--

            ImGuiWindowFlags flags;
            flags = ImGuiWindowFlags_None;
            flags |= ImGuiWindowFlags_NoScrollbar;

            string s;

            // Window shape
            {
                hWindowMin = (bOptions.get() ? 200 : 150); //minimal height
                ImGuiCond cond = ImGuiCond_FirstUseEver;

                // App window
                float w = ofGetWidth();
                float h = ofGetHeight();
                ImGui::SetNextWindowPos(ImVec2(w - wWindowMin - 25, 25), cond);
                ImGui::SetNextWindowSize(ImVec2(wWindowMin, 2 * hWindowMin), cond);
                //ImGui::SetNextWindowSize(ImVec2(wWindowMin, h - 100), cond);

                // Constraints
                ImVec2 size_min = ImVec2(wWindowMin, hWindowMin);
                ImVec2 size_max = ImVec2(FLT_MAX, FLT_MAX);
                ImGui::SetNextWindowSizeConstraints(size_min, size_max);
            }

            //----

            // Window Begin
            bool tmp = bGui.get();

            std::string name = bGui.getName();
            bool b = ImGui::Begin(name.c_str(), (bool*)&tmp, flags);
           
            if (!b)
            {
                if (bGui.get() != tmp) bGui.set(tmp);
                ImGui::End();
                return;
            }

            // Debug for responsive layout
            bool bDebug = 0;
            if (bDebug) ofxImGuiSurfing::DebugContentRegionAvailX();

            // Some useful sizes
            float _hu = ofxImGuiSurfing::getWidgetsHeightUnit();
            float _wu = 1.15f * _hu;
            float _hb = _hu * 1.5f;
            float _w1 = ofxImGuiSurfing::getWidgetsWidth(1);
            float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);
            float _spx = ofxImGuiSurfing::getWidgetsSpacingX();

            //--

            // Rounded toggle
            float ht = 0.8f * _hu;
            float wt = 1.15f * ht;

            if (bMinimize)
            {
                // Right aligned if 1 or left aligned if 0.
                if (0)
                {
                    float _ww3 = ofxImGuiSurfing::getWidgetButtomToggleWidth(bPause, true);
                    _ww3 += ofxImGuiSurfing::getWidgetButtomToggleWidth("CLEAR", true);

                    // make the space of both buttons from the right window border
                    ofxImGuiSurfing::AddSpacingToRightAlign(_ww3);

                    ofxImGuiSurfing::AddSpacingX(-_wu); // mini toggle
                    float _sp3 = ImGui::GetStyle().ItemSpacing.x;
                    _sp3 += ImGui::GetStyle().WindowPadding.x;
                    ofxImGuiSurfing::AddSpacingX(-_sp3); // item spacing
                }

                float _hh = _hu * 1.0f;
                float _ww1 = ofxImGuiSurfing::getWidgetButtomToggleWidth(bPause);
                float _ww2 = ofxImGuiSurfing::getWidgetButtomToggleWidth("CLEAR");

                //float _spy = ImGui::GetStyle().ItemSpacing.y;
                //ofxImGuiSurfing::AddSpacingY(-_spy);
                {
                    // Pause
                    ofxImGuiSurfing::AddBigToggle(bPause, ImVec2(_ww1, _hh), true, true);
                    ImGui::SameLine();

                    // Clear
                    if (ImGui::Button("CLEAR", ImVec2(_ww2, _hh))) Clear();
                    ImGui::SameLine();
                }
                //ofxImGuiSurfing::AddSpacingY(_spy);
            }

            //--

            // Minimize XS toggle
            AddToggleRoundedMiniXsRightAligned(bMinimize);

            ofxImGuiSurfing::AddSpacing();

            // Reduce y spacing
            if (bMinimize)
            {
                if (1) ofxImGuiSurfing::AddSpacingY(-5); //empty reduced space
                else ofxImGuiSurfing::Separator(); //draw a line
            }

            //--

            // Maximized
            if (!bMinimize)
            {
                // Pause
                ofxImGuiSurfing::AddBigToggle(bPause, ImVec2(_w2, _hb), true, true);
                ImGui::SameLine();

                // Clear
                if (ImGui::Button("CLEAR", ImVec2(_w2, _hb)))
                {
                    Clear();
                }

                ofxImGuiSurfing::AddSpacingSeparated();

                //--

                // Filter
                {
                    ofxImGuiSurfing::AddBigToggle(bFilter, _w1, _hb, true, true);
                    {
                        s = bFilter ? "Write your keyword \nor pick a Tag \nto filter the Log" : "Disabled";
                        ofxImGuiSurfing::AddTooltip2(s);
                    }
                    if (bFilter)
                    {
                        float _w = _w1;

                        string sf;
                        auto& tmpRef = strFilterKeyword.get();
                        s = tmpRef.c_str();
                        ImGui::PushItemWidth(_w);
                        static bool b;
                        b = ImGui::InputText("##Filter", &s);
                        if (b)
                        {
                            ofLogNotice("ofxSurfingImGui:SurfingLog") << "InputText:" << s.c_str();
                            strFilterKeyword.set(s);
                        }
                        ImGui::PopItemWidth();
                        sf = "Input keyword";
                        ofxImGuiSurfing::AddTooltip2(sf);

                        //ImGui::SameLine();

                        this->AddComboAux(indexTagFilter, namesTagsFiler, _w);
                        sf = "Tags";
                        ofxImGuiSurfing::AddTooltip2(sf);
                    }

                    ofxImGuiSurfing::AddSpacingSeparated();
                }

                //--

                // Options
                ofxImGuiSurfing::AddToggleRoundedButton(bOptions, 1.25 * _hu, true);
                if (bOptions)
                {
                    ImGui::Spacing();
                    //ImGui::Indent();

                    //--

                    // Modes toggle: 
                    // LIMITED or UNLIMITED

                    ofxImGuiSurfing::AddBigToggleNamed(bLimitedBuffered, 140, _hu, "LIMITED", "UNLIMITED");

                    // Tool tip
                    {
                        s = (bLimitedBuffered
                                 ? "Buffer size \nof lines is limited"
                                 : "Buffer size \nof lines is \nunlimited.");
                        if (bLimitedBuffered) s += "\n\nYou can set AutoFit \nor to specify an \namount manually.";
                        //s += "\n\nAmountLines: \n" + ofToString(amountLinesCurr);
                        ofxImGuiSurfing::AddTooltip2(s);
                    }

                    // Amount lines counter
                    {
                        ofxImGuiSurfing::SameLineFit(160, bDebug);
                        string s = ofToString(amountLinesCurr);
                        ImGui::Text("%s", s.c_str());
                        s = "Amount of \nbuffered lines:\n" + s;
                        ofxImGuiSurfing::AddTooltip2(s);
                    }

                    //--

                    ofxImGuiSurfing::SameLineFit(280, bDebug);
                    bool bCopy = ImGui::Button("Copy", ImVec2{wWidgets / 2 - _spx / 2, _hu});
                    s = "Copy Log \nto Clipboard";
                    ofxImGuiSurfing::AddTooltip2(s);
                    if (bCopy) ImGui::LogToClipboard();

                    //--

                    ImGui::SameLine();
                    bool bExport = ImGui::Button("Export", ImVec2{wWidgets / 2 - _spx / 2, _hu});
                    s = "Export Log \nto a file \nin data/ folder";
                    ofxImGuiSurfing::AddTooltip2(s);
                    if (bExport) exportLogToFile();

                    //--

                    ofxImGuiSurfing::AddCheckBox(bTimeStamp);
                    s = "Print timestamps";
                    ofxImGuiSurfing::AddTooltip2(s);

                    // Unlimited
                    if (!bLimitedBuffered)
                    {
                        ofxImGuiSurfing::SameLineFit(180, bDebug);
                        ofxImGuiSurfing::AddCheckBox(bAutoScroll);
                    }

                    ofxImGuiSurfing::SameLineFit(350);
                    ofxImGuiSurfing::AddCheckBox(bTight);
                    s = "Compact interline height";
                    ofxImGuiSurfing::AddTooltip2(s);

                    ofxImGuiSurfing::SameLineFit(45, bDebug);
                    ofxImGuiSurfing::AddCheckBox(bOneLine);
                    s = (bOneLine
                             ? "Forces only one line per message.\nAvoids wrapping format."
                             : "Allows multi-line wrapping \nto window width.");
                    ofxImGuiSurfing::AddTooltip2(s);

                    ofxImGuiSurfing::SameLineFit(45, bDebug);
                    ofxImGuiSurfing::AddCheckBox(bHideTags);

                    ofxImGuiSurfing::AddCheckBox(bSeparators);
                    s = "Add separator line between messages.";
                    ofxImGuiSurfing::AddTooltip2(s);

                    //--

                    // Modes

                    // Limited buffered
                    if (bLimitedBuffered)
                    {
                        ofxImGuiSurfing::SameLineFit(180, bDebug);
                        ofxImGuiSurfing::AddCheckBox(bAutoFit);
                        s = "Resizes buffer to fit \nwindow height, \nas expected amount \nof text lines.";
                        s += "\nWill be affected by \nthe OneLine state.";
                        ofxImGuiSurfing::AddTooltip2(s);
                        if (!bAutoFit)
                        {
                            ofxImGuiSurfing::SameLine();

                            {
                                ImGui::PushItemWidth(90);
                                string name = amountLinesLimitedBuffered.getName();
                                auto tmpRefi = amountLinesLimitedBuffered.get();
                                string n = "##STEPPERint" + name; // +ofToString(1);
                                const ImU32 u32_one = 1;
                                ImGui::PushID(n.c_str());
                                if (ImGui::InputScalar(amountLinesLimitedBuffered.getName().c_str(), ImGuiDataType_S32,
                                                       (int*)&tmpRefi, &u32_one, NULL, "%d"))
                                {
                                    tmpRefi = ofClamp(tmpRefi, amountLinesLimitedBuffered.getMin(),
                                                      amountLinesLimitedBuffered.getMax());
                                    amountLinesLimitedBuffered.set(tmpRefi);
                                }
                                ImGui::PopID();
                                ImGui::PopItemWidth();
                            }
                        }
                    }

                    ofxImGuiSurfing::SameLineFit(480, bDebug);
                    this->AddComboAux(fontIndex, namesCustomFonts, wWidgets);
                    //ofxImGuiSurfing::DebugContentRegionAvailX();

                    //--

                    // Move to always visible top zone
                    //// Filter
                    //{
                    //	ofxImGuiSurfing::AddBigToggle(bFilter, wWidgets, _hu, true, true);
                    //	{
                    //		s = bFilter ? "Write your keyword \nor pick a Tag \nto filter the Log" : "Disabled";
                    //		ofxImGuiSurfing::AddTooltip2(s);
                    //	}
                    //	if (bFilter)
                    //	{
                    //		ofxImGuiSurfing::SameLineFit(220);
                    //		static bool bReturn;//not used
                    //		auto& tmpRef = strFilterKeyword.get();
                    //		float _w1 = wWidgets;
                    //		s = tmpRef.c_str();
                    //		ImGui::PushItemWidth(_w1);
                    //		bReturn = ImGui::InputText("##Filter", &s);
                    //		if (bReturn)
                    //		{
                    //			ofLogNotice("ofxSurfingImGui:SurfingLog") << "InputText:" << s.c_str();
                    //			strFilterKeyword.set(s);
                    //		}
                    //		ImGui::PopItemWidth();
                    //		ofxImGuiSurfing::SameLineFit(350);
                    //		this->AddComboAux(indexTagFilter, namesTagsFiler, wWidgets);
                    //	}
                    //}

                    //ImGui::Unindent();
                }

                //--

                ofxImGuiSurfing::AddSpacingSeparated();
            }

            ofxImGuiSurfing::AddSpacing();
            ofxImGuiSurfing::AddSpacing();

            //--

            // Log Messages

            //ImVec4 c = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
            ImVec4 c(0, 0, 0, 0);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, c);

            drawLogMessages();

            ImGui::PopStyleColor();

            //--
            
            if (bGui.get() != tmp) bGui.set(tmp);

            ImGui::End();
        }

        //void setName(std::string name)
        //{
        //    bGui.setName(name);
        //}

        //--

    public:
        //ofParameter<bool> bGui{"LOG", true};

        ofParameterGroup params{"Module Log"};
        // settings are handled by the parent class. 
        // will be serialized on exit and loaded on start.

        ofParameter<int> amountLinesLimitedBuffered{"Amount", 20, 1, 200};
        //TODO: workaround: public for disable log on parent classes

        //TODO: clamp
        void setFontSize(int i)
        {
            i = ofClamp(i, 0, customFonts.size() - 1);
            fontIndex = i;
        }
        // alias
        void setFontIndex(int i)
        {
            i = ofClamp(i, 0, customFonts.size() - 1);
            fontIndex = i;
        }

        void setFontMonospacedDefined(bool b = true)
        {
            bDefinedMonospacedFonts = b;

            fontIndex.setMax(customFonts.size() - 1);

            //workflow. pick the mono-spaced
            // if (fontIndex < 4) fontIndex += 4;//set relative mono-spaced by default
        }

        ofParameter<int> fontIndex{"Font", 0, 0, 0};

    private:
        bool bDefinedMonospacedFonts = false;

        ofParameter<bool> bOptions{"OPTIONS", false};
        ofParameter<bool> bLimitedBuffered{"Limited", false};
        ofParameter<bool> bPause{"PAUSE", false};
        ofParameter<bool> bTight{"Tight", true};
        ofParameter<bool> bHideTags{"HideTags", 1};
        ofParameter<bool> bOneLine{"OneLine", 0};
        ofParameter<bool> bSeparators{"Separators", false};
        ofParameter<bool> bAutoFit{"AutoFit", true};
        ofParameter<bool> bAutoScroll{"AutoScroll", true};
        ofParameter<bool> bTimeStamp{"TimeStamps", false};
        ofParameter<bool> bFilter{"FILTER", false};
        ofParameter<string> strFilterKeyword{"Keyword", ""};
        ofParameter<int> indexTagFilter{"Tag", 0, 0, 0};
        vector<string> namesTagsFiler;
        ofParameter<bool> bMinimize{"MinimizeLog", true};

        int amountLinesCurr = 0;
        bool bDoneStartup = false;

    private:
        // Columns formatting
        const int maxTagLengthDefault = 8; // first column or tag width. to make tags right aligned.
        int maxTagLengthSession = -1;
        string strSpacer = "   "; // space between tags column and the second column with the message .
        //const string strSpacer2 = " "; // not required bc alignment adds some starting spaces

    private:
        void startupOnce()
        {
            if (bDoneStartup) return;

            if (strFilterKeyword.get() == "")
            {
                //refresh
                indexTagFilter = indexTagFilter;
            }

            //bFilter = bFilter;

            // if (bDefinedMonospacedFonts) if (fontIndex < 4) fontIndex = 4;//set first mono-spaced by default

            bDoneStartup = true;
            ofLogNotice("ofxSurfingImGui:SurfingLog") << "Startup done";
        }

    private:
        void Changed_Params(ofAbstractParameter& e)
        {
            std::string n = e.getName();
            if (n != amountLinesLimitedBuffered.getName())
            {
                ofLogNotice("ofxSurfingImGui:SurfingLog") << n << ": " << e;
            }

            //workaround to fix combo behavior
            if (n == strFilterKeyword.getName())
            {
                if (strFilterKeyword.get() == strAlign("NONE"))
                    strFilterKeyword.setWithoutEventNotifications("");
                return;
            }

            if (n == indexTagFilter.getName())
            {
                string t = "";
                if (indexTagFilter < namesTagsFiler.size() + 1)
                {
                    t = namesTagsFiler[indexTagFilter.get()];
                    if (t == strAlign("NONE")) t = ""; //clear
                    strFilterKeyword.set(t);

                    //workflow
                    //avoid overwrite with init callback
                    if (bDoneStartup && !bFilter) bFilter = true;
                }
                return;
            }

            if (n == amountLinesLimitedBuffered.getName())
            {
                static int sizeLimitedBuffered_ = -1;
                if (amountLinesLimitedBuffered != sizeLimitedBuffered_)
                {
                    amountLinesLimitedBuffered = ofClamp(amountLinesLimitedBuffered.get(),
                                                         amountLinesLimitedBuffered.getMin(),
                                                         amountLinesLimitedBuffered.getMax());

                    sizeLimitedBuffered_ = amountLinesLimitedBuffered;
                    int diff = bufferBufferedLimited.size() - amountLinesLimitedBuffered.get();
                    // reduce resize
                    if (diff > 0)
                    {
                        for (size_t i = 0; i < diff; i++)
                        {
                            bufferBufferedLimited.pop_front();
                        }
                    }
                    ofLogNotice("ofxSurfingImGui:SurfingLog") << n << ": " << e;
                }
                return;
            }
        }

        //----

    public:
        struct tagData
        {
            string name;
            ofColor color;
        };

        void clearDefaultTags()
        {
            tags.clear();

            namesTagsFiler.clear();
            //namesTagsFiler.push_back(strAlign(""));
            namesTagsFiler.push_back(strAlign("NONE"));

            maxTagLengthSession = 0;
        }

    private:
        vector<tagData> tags;

        void buildTagsDefault()
        {
            // To be used when log a message without tag.
            // will use common text color
            // this empty tag will have the size 
            // of the bigger tag to maintain alignment
            strEmptyTag = "";
            //maxTagLengthSession = maxTagLengthDefault;
            for (size_t i = 0; i < maxTagLengthSession; i++)
            {
                strEmptyTag += " ";
            }

            tags.clear();

            namesTagsFiler.clear();
            namesTagsFiler.push_back(strAlign("NONE"));

            // These tags are the hardcoded default tag
            // But can be removed befor adding new custom tags using 
            // the clearDefaultTags() method.

            this->AddTag({"INFO", ofColor::white});
            this->AddTag({"VERBOSE", ofColor::white});
            this->AddTag({"NOTICE", ofColor::green});
            this->AddTag({"WARNING", ofColor::yellow});
            this->AddTag({"ERROR", ofColor::red});
        }

        string strEmptyTag = "";

        // inserts spaces at left to align all tags
        string strAlign(string s) const
        {
            //TODO:
            // to make right aligned
            int l = s.length();
            int diff = maxTagLengthSession - l;
            if (diff > 0)
            {
                string spre = "";
                for (size_t i = 0; i < diff; i++)
                {
                    spre += " ";
                }
                s = spre + s;
            }

            //s += " ";//end spacing

            return s;
        }

        ofLogLevel logLevelUi = OF_LOG_VERBOSE;

    public:
        void setLogLevel(ofLogLevel logLevel) { this->logLevelUi = logLevel; }

        // This feature will redirect all std::cout logs to the ui log window.
        // TODO: could redirect ofLog too..
        void setRedirectConsole(bool b = true)
        {
            bRedirect = b;

            if (bRedirect)
            {
                _oldStdout = std::cout.rdbuf();
                std::cout.rdbuf(_stdout.rdbuf());
            }
        }

    private:
        bool bRedirect = false;
        std::streambuf* _oldStdout = nullptr;
        std::stringstream _stdout;

    public:
        // add custom tags passing name and color
        void AddTag(tagData tag)
        {
            // if tag is bigger in chars than the default tags adapt max size (8 chars by default)
            if (tag.name.size() > maxTagLengthSession)
            {
                maxTagLengthSession = tag.name.size();
                buildTagsDefault();
            }

            //TODO:
            //remove margin when not using tags, or an empty tag
            if (maxTagLengthSession == 0)
            {
                strSpacer = "";
            }

            ////TODO:
            //// to make right aligned
            //const int maxTagLengthDefault = 10;
            //int l = tag.name.length();
            //int diff = maxTagLengthDefault - l;
            //if (diff > 0) {
            //	string spre = "";
            //	for (size_t i = 0; i < diff; i++)
            //	{
            //		spre += " ";
            //	}
            //	tag.name = spre + tag.name;
            //}

            tag.name = strAlign(tag.name);

            tags.push_back(tag);

            // filter
            indexTagFilter.setMax(tags.size());
            namesTagsFiler.push_back(tag.name);
        }

        //--

        void Clear()
        {
            this->clearUnlimited();
            this->clearBuffered();
            //this->ClearFilter();
        }

    private:
        void addBuffered(string msg)
        {
            bufferBufferedLimited.emplace_back(msg);
            if (amountLinesLimitedBuffered.get() < bufferBufferedLimited.size())
            {
                bufferBufferedLimited.pop_front();
            }

            if (bAutoScroll) this->scroll_to_bottom = true;
        }

        void addUnlimited(string msg, ...)
        {
            //void add(const char* fmt, ...) 
            const char* fmt = msg.c_str();
            char buf[1024];
            va_list args;
            va_start(args, fmt);
            vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
            buf[IM_ARRAYSIZE(buf) - 1] = 0;
            va_end(args);
            bufferUnlimited.push_back(strdup(buf));

            if (bAutoScroll) this->scroll_to_bottom = true;
        }

        void clearUnlimited()
        {
            for (int i = 0; i < bufferUnlimited.Size; i++)
                free(bufferUnlimited[i]);
            bufferUnlimited.clear();
        }

        void drawUnlimited()
        {
            float p = 0; //padding
            float w = ofxImGuiSurfing::getWidgetsWidth(1);
            float h = ofxImGuiSurfing::getWindowHeightFree();
            bool bBorder = 0; //used?

            drawUnlimited("Logger", ImGui::GetCursorPos(), {w - p, h - p}, bBorder);
        }

        void drawUnlimited(const char* str_id, const ImVec2 pos, const ImVec2 size, const bool border)
        {
            ImGui::SetCursorPos(pos);

            ImGuiWindowFlags flags = ImGuiWindowFlags_None;

            // border not used?
            ImGui::BeginChild(str_id, size, border, flags);
            {
                for (int i = 0; i < bufferUnlimited.Size; i++)
                {
                    const char* item = bufferUnlimited[i];

                    //--

                    // filter
                    if (bFilter)
                    {
                        bool bFound = true;
                        string s1 = strFilterKeyword.get();
                        string s2(item);
                        if (s1 != "")
                        {
                            bFound = ofIsStringInString(s2, s1);
                        }
                        if (!bFound) continue; // skip if the filter keyword is not found into the text line!
                    }

                    //--

                    ImVec4 color;
                    bool has_color = false;

                    for (auto t : tags)
                    {
                        if (strstr(item, t.name.c_str()))
                        {
                            color = t.color;
                            has_color = true;
                            break;
                        }
                    }

                    if (has_color) ImGui::PushStyleColor(ImGuiCol_Text, color);

                    //--

                    // draw text
                    drawText(item);

                    //--

                    if (has_color) ImGui::PopStyleColor();
                }

                //--

                if (bAutoScroll)
                {
                    if (this->scroll_to_bottom) ImGui::SetScrollHereY(1.0f);
                    this->scroll_to_bottom = false;
                }
            }
            ImGui::EndChild();
        }

        void drawLimitedBuffered()
        {
            ImGui::BeginChild("LoggerBuffered");
            {
                // force log size to current window size
                if (bAutoFit)
                {
                    ImGuiContext& g = *GImGui;
                    float h = g.FontSize;
                    if (!bTight) h += g.Style.FramePadding.y;
                    float hFree = ofxImGuiSurfing::getWindowContentHeight();
                    int amountLines = hFree / h;
                    amountLinesLimitedBuffered = amountLines;
                }

                //--

                for (auto& m : bufferBufferedLimited)
                {
                    // macOS bug
                    // for each (string l in logs)

                    const char* item = m.c_str();

                    //--

                    // filter
                    if (bFilter)
                    {
                        bool bFound = true;
                        string s1 = strFilterKeyword.get();
                        if (s1 != "")
                        {
                            bFound = ofIsStringInString(m, s1);
                        }
                        if (!bFound) continue; // skip!
                    }

                    //--

                    ImVec4 color;
                    bool has_color = false;

                    for (auto t : tags)
                    {
                        if (strstr(item, t.name.c_str()))
                        {
                            color = t.color;
                            has_color = true;
                        }
                    }

                    if (has_color) ImGui::PushStyleColor(ImGuiCol_Text, color);

                    //--

                    // draw text
                    drawText(item);

                    //--

                    if (has_color) ImGui::PopStyleColor();
                }

                //--

                if (bAutoScroll)
                {
                    if (this->scroll_to_bottom) ImGui::SetScrollHereY(1.0f);
                    this->scroll_to_bottom = false;
                }
            }
            ImGui::EndChild();
        }

    private:
        ImVector<char*> bufferUnlimited;
        bool scroll_to_bottom;

        static char* strdup(const char* s)
        {
            IM_ASSERT(s);
            size_t len = strlen(s) + 1;
            void* buf = malloc(len);
            IM_ASSERT(buf);
            return (char*)memcpy(buf, (const void*)s, len);
        }

        //--

        // Buffered mode

    public:
        void clearBuffered() { bufferBufferedLimited.clear(); };

    private:
        std::deque<std::string> bufferBufferedLimited;

        //---

    public:
        //TODO: could be problematic if required to be called out of ImGui begin/end
        // Save log file to disk
        // pass path folder. the name will be auto settled by timestamp
        void exportLogToFile(string path = "")
        {
            ofLogNotice("ofxSurfingImGui:SurfingLog") << "exportLogToFile:" << path;

            if (path == "") path = ofToDataPath("", true);
            path += "\\logs"; //add subfolder
            CheckFolder(path); //create folder if required

            string timeFormat = "%Y-%m-%d"; //+date
            timeFormat += "___%H-%M-%S"; //+time

            string n = ""; //filename with ext
            string s = ""; //path complete 

            //filename
            n += "LogSurfing___";
            n += ofGetTimestampString(timeFormat);
            n += ".txt";

            s = path + "\\" + n;

            // A. using ImGui internal methods
            ImGui::LogToFile(-1, s.c_str());

            // log that action too!
            this->Add("LOG FILE:");
            this->Add(n);
            this->Add("SAVED TO:");
            this->Add(path);

            //TODO: could auto open the log file by using system commands

            //--

            //TODO:
            //fails
            //// B. using custom methods
            //string text = "";

            //if (!bLimitedBuffered)
            //{
            //	for (int i = 0; i < bufferUnlimited.Size; i++)
            //	{
            //		const char* item = bufferUnlimited[i];
            //		string _s = string(item);
            //		text += _s;
            //		text += "\n";
            //	}
            //}
            //else
            //{
            //	for (auto& m : bufferBufferedLimited)
            //	{
            //		text += m;
            //		text += "\n";
            //	}
            //}

            //cout << endl << text << endl;

            //std::cin >> text;

            //std::ofstream out(s.c_str());
            //out << text;
            //out.close();
        }

        //--

    private:
        void drawText(const char* item)
        {
            if (bSeparators)
            {
                if (!bTight) ImGui::Spacing();
                ImGui::Separator();
                if (!bTight) ImGui::Spacing();
            }

            if (bTight) ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

            if (bOneLine) ImGui::TextUnformatted(item);
            else ImGui::TextWrapped("%s", item);

            if (bTight) ImGui::PopStyleVar();
        }

        void drawLogMessages()
        {
            pushStyleFont(fontIndex.get());
            {
                if (!bLimitedBuffered)
                {
                    drawUnlimited();
                }
                else
                {
                    drawLimitedBuffered();
                }
            }
            popStyleFont();
        }

        //----

        // API: workflow during draw to switch between font styles

    public:
        void setCustomFonts(vector<ImFont*> f, vector<string> names)
        {
            setCustomFontsNames(names);
            setCustomFonts(f);
        }
        void setCustomFontsNames(vector<string> names)
        {
            namesCustomFonts = names;
        }
        void setCustomFonts(vector<ImFont*> f)
        {
            customFonts = f;

            if (customFonts.size() == 0)
            {
                ofLogError("ofxSurfingImGui:SurfingLog") << "It looks that not any extra font styles are added!";
            }

            fontIndex.setMax(customFonts.size() - 1);
        }
    private:
        vector<ImFont*> customFonts;
        vector<string> namesCustomFonts;

        //--

        bool bFlagIgnoreNextPopStyleFont = false;

        void pushStyleFont(int index)
        {
            int i;
#if 1
            i = index;
#else//TODO: limit to mono-spaced
			if (!bDefinedMonospacedFonts) i = index;
			else i = index + 4;
#endif
            if (i < customFonts.size())
            {
                if (customFonts[i] != nullptr) ImGui::PushFont(customFonts[i]);
            }
            else
            {
                bFlagIgnoreNextPopStyleFont = true; // workaround to avoid crashes
            }
        }

        void popStyleFont()
        {
            //TODO: will crash if not previously pushed..
            //workaround to avoid crashes
            if (bFlagIgnoreNextPopStyleFont)
            {
                bFlagIgnoreNextPopStyleFont = false;

                return;
            }

            ImGui::PopFont();
        }

        //--

        //TODO:
        // added here as workaround bc some headers are not included here.
        // and they can't not be included bc colliding between them...
        bool AddComboAux(ofParameter<int>& parameter, std::vector<std::string> labels, float width = 90)
        {
            if (parameter.get() < 0) return false;
            if (labels.size() == 0) return false;
            if (parameter > labels.size() - 1) parameter = labels.size() - 1;

            //const ImVec2 sz = ImGui::CalcTextSize(parameter.getName().c_str());
            //ImGui::PushItemWidth(sz.x);

            ImGui::PushItemWidth(width);

            auto bReturn = false;
            auto tmpRef = parameter.get();

            auto uniqueName = (("##COMBO" + parameter.getName()).c_str());
            ImGui::PushID(uniqueName);

            if (ImGui::BeginCombo((parameter.getName().c_str()), labels.at(parameter.get()).c_str()))
            {
                for (size_t i = 0; i < labels.size(); ++i)
                {
                    bool selected = (i == tmpRef);
                    if (ImGui::Selectable(labels[i].c_str(), selected))
                    {
                        tmpRef = i;
                        bReturn = true;
                    }
                    if (selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }

            ImGui::PopID();

            if (bReturn)
            {
                parameter.set(tmpRef);
            }

            ImGui::PopItemWidth();

            return bReturn;
        }
    }; //class
} //namespace
