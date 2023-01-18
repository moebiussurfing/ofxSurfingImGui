#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowPosition(-1920, 25);

	setupParams();

	setupImGui();

	ofxSurfingHelpers::loadGroup(params);
}

//--------------------------------------------------------------
void ofApp::setupParams()
{
	params.setName("G");
	params.add(speed.set("Speed", 0.5f, 0, 1));
	params.add(amountPauses.set("Pauses", 50, 0, 100));
	params.add(bAnimate1.set("Animate 1", true));
	params.add(bAnimate2.set("Animate 2", false));
	params.add(bPrevious.set("<"));
	params.add(bNext.set(">"));
	params.add(lineWidth.set("Width", 0.5f, 0, 1));
	params.add(separation.set("Separation", 50, 1, 100));

	ofAddListener(params.parameterChangedE(), this, &ofApp::Changed_Params);
}

//--------------------------------------------------------------
void ofApp::setupImGui()
{
	ui.setup();

	// Add custom tags to logger
	{
		SurfingLog::tagData tagOSC{ "OSC", ofColor::turquoise };
		ui.AddLogTag(tagOSC);
		SurfingLog::tagData tagMIDI{ "MIDI", ofColor::orange };
		ui.AddLogTag(tagMIDI);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetWindowTitle("FPS " + ofToString(ofGetFrameRate(), 0));

	drawImGui();

	updateLog();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	ui.Begin();

	if (ui.BeginWindow("ofApp"))
	{
		ui.Add(ui.bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);
		bool b = !ui.bMinimize;//maximized alias
		ui.AddSpacingBigSeparated();

		if (b) ui.AddLabelHuge("LOG SYSTEM");
		ui.AddSpacing();
		ui.Add(ui.bLog, OFX_IM_TOGGLE_BIG_XXL_BORDER);
		if (b) if (ui.bLog) {
			ui.Add(ui.bLogKeys, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
		}
		ui.AddSpacingBigSeparated();

		if (b) ui.AddLabelHuge("ANIMATE");
		if (b) ui.AddSpacing();
		ui.Add(bAnimate1, OFX_IM_TOGGLE_MEDIUM_BORDER_BLINK);
		ui.AddTooltip("Animate and randomize params \nto feed the Log.\nGo look into the Log window!");
		ui.AddSpacing();
		if (bAnimate1) {
			if (b) ui.AddLabelBig("MODIFIERS");
			ui.Add(speed, OFX_IM_HSLIDER_SMALL);
			ui.AddTooltip("Sets the speed \nof Animation \nto feed the Log");

			ui.Add(amountPauses, OFX_IM_HSLIDER_SMALL);
			ui.AddTooltip("Density of \npause moments");
			ui.AddTooltip(amountPauses, true, false);

			if (b) {
				ui.AddSpacingBig();
				ui.Add(ui.bDebug, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
				if (ui.bDebug) {
					ui.Add(progress0, OFX_IM_PROGRESS_BAR_NO_TEXT);
					ui.Add(progress1, OFX_IM_PROGRESS_BAR_NO_TEXT);
					ui.Add(progress2, OFX_IM_PROGRESS_BAR_NO_TEXT);
					//ui.Add(ui.bDebugMetrics, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
				}
			}
		}
		ui.AddSpacingBigSeparated();

		//--

		// A bundle of controls
		// for a single param
		ui.AddComboBundle(lineWidth);

		//--

		ui.AddSpacingBigSeparated();

		ui.Add(separation, OFX_IM_HSLIDER_MINI);
		ui.Add(bAnimate2, OFX_IM_TOGGLE_SMALL_BORDER_BLINK);
		ui.AddTooltip("Animate Separation parameter.");

		//--

		ui.EndWindow();
	}

	ui.End();
}

//--------------------------------------------------------------
void ofApp::updateLog()
{
	// Animate some vars
	auto f = ofGetFrameNum();
	
	// Ping every 2 seconds. 
	if (f % 120 == 0)
	{
		ui.AddToLog("PING"); // Raw without tag. 2nd argument empty
	}

	// Animate 2
	if (bAnimate2 && f % 10 == 0)
	{
		float t = ofGetElapsedTimef();
		float s = ofMap(amountPauses, amountPauses.getMax(), amountPauses.getMin(), 1, 10);
		t = ofWrap(t, 0, s);
		separation = ofMap(t, 0, s, separation.getMin(), separation.getMax());
	}

	if (!bAnimate1) return;

	// Make pauses
	float a = ofMap(amountPauses, amountPauses.getMax(), amountPauses.getMin(), 0.25f, 1.f);
	static int t1 = 600;
	if ((f % t1) == 0) t1 = (int)ofRandom(200, 600);
	//if (f % t1 > (t1 * 0.75f))
	progress0 = ofMap(f % t1, 0, t1 * a, 0, 1, true);
	if (f % t1 > (t1 * a))
	{
		return;
	}

	// Log d times per second at 60 fps
	if (1)
	{
		int d = ofMap(speed.get(), 0, 1, 120, 8);
		progress1 = ofMap(f % d, 0, d, 0, 1, true);
		if (f % d == 0)
			ui.AddToLog(ofToString(separation) + " <------ " + separation.getName(), "NOTICE"); // default with no color bc no tag
	}

	// Auto populate random log messages.
	int m = ofMap(speed, 1, 0, 2, ofRandom(1) > 0.5 ? 60 : 40);
	progress2 = ofMap(f % m, 0, m, 0, 1, true);
	if (f % m == 0)
	{
		auto t = ofGetElapsedTimef();
		//progress3 = ofMap(f % m, 0, m, 0, 1, true);
		if (ofNoise(t) < 0.4f) return; // skip one third

		string ss = "FrameNum: " + ofToString(f);
		float _rnd = ofRandom(1);
		string s2 = "";

		if (_rnd < 0.2)
			ui.AddToLog(ss, "VERBOSE");

		else if (_rnd < 0.4)
			ui.AddToLog(ofToString(_rnd, 4), "ERROR");

		else if (_rnd < 0.6)
		{
			s2 += ofToString(ofToString((ofRandom(1) < 0.5 ? "..-." : "--...-.-.--..")) + "--" + ofToString((ofRandom(1) < 0.5 ? ".--.-." : "...-.--..")));
			s2 += ofToString(ofToString((ofRandom(1) < 0.5 ? "...-...-." : "---.--..")) + "..--------..-" + ofToString((ofRandom(1) < 0.5 ? ".--.-." : "...-.--..")));
		}

		else if (_rnd < 0.8)
		{
			s2 += ofToString(ofToString((ofRandom(1) < 0.5 ? "....-..-." : "---.--..")) + "---...-.---.---.." + ofToString((ofRandom(1) < 0.5 ? ".--.-." : "...-....-....-.--..")));
			s2 += ofToString((ofRandom(1) < 0.5 ? "...-....-." : "--.--") + ofToString("===//...--//--...---.."));
		}

		else
			ui.AddToLog("Now we are: " + ofGetTimestampString(), "VERBOSE");

		if (s2 != "") ui.AddToLog(s2, "NOTICE");
	}
}

//--------------------------------------------------------------
void ofApp::Changed_Params(ofAbstractParameter& e)
{
	std::string name = e.getName();
	ofLogNotice() << name << ": " << e;

	// Log using the custom added tags!

	//// all the rest are logged as "[WARNING]"
	//string s = name + ": " + ofToString(e);
	//ui.AddToLog(s, "WARNING");

	// logged as "OSC"
	if (name == bPrevious.getName() || name == bNext.getName()) {
		ui.AddToLog(name, "OSC");
		return;
	}
	if (name == amountPauses.getName()) {
		ui.AddToLog(name + ": " + ofToString(e), "OSC");
		return;
	}

	// logged as "MIDI"
	if (name == separation.getName()) {
		string s = name + ": " + ofToString(e);
		ui.AddToLog(s, "MIDI");
		return;
	}

	// all the rest are logged as "[WARNING]"
	string s = name + ": " + ofToString(e);
	ui.AddToLog(s, "WARNING");
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofRemoveListener(params.parameterChangedE(), this, &ofApp::Changed_Params);
	ofxSurfingHelpers::saveGroup(params);
}
