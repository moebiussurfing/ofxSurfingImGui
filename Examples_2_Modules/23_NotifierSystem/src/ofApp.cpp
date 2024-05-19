#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	setupParams();

	setupImGui();

	ofxImGuiSurfing::loadGroup(params);
}

//--------------------------------------------------------------
void ofApp::setupParams()
{
	params.setName("ofApp");
	params.add(speed.set("Speed", 0.5f, 0, 1));
	params.add(amountPauses.set("Pauses", 50, 0, 100));
	params.add(bAnimate.set("Animate", true));

	ofAddListener(params.parameterChangedE(), this, &ofApp::Changed_Params);
}

//--------------------------------------------------------------
void ofApp::setupImGui()
{
	//ui.setEnablebMouseCursorFromImGui(false);
	ui.setName("myOfApp");
	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetWindowTitle("05_NotifierSystem | FPS " + ofToString(ofGetFrameRate(), 0));

	drawImGui();

	updateLog();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	ui.Begin();

	if (ui.BeginWindow("ofApp"))
	{
		ui.AddLabelHuge("05_\nNotifier\nSystem");
		ui.AddSpacingBig();

		ui.Add(ui.bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);
		ui.Add(ui.bDebug, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);
		bool b = !ui.bMinimize; // is maximized alias

		ui.AddSpacingBigSeparated();

		ui.AddLabelBig("NOTIFIER SYSTEM");
		ui.AddSpacing();
		ui.Add(ui.bNotifier, OFX_IM_TOGGLE_BIG_XXL_BORDER);
		if (ui.AddButton("Random Notify", OFX_IM_BUTTON_BIG)) {
			doRandomNotifyLog();
		};if (ui.AddButton("Clear", OFX_IM_BUTTON)) {
			ui.doClearNotifier();
		};

		if (ui.isMaximized()) {
			ui.AddSpacingBigSeparated();

			ui.AddLabelBig("LOG SYSTEM");
			ui.AddSpacing();
			ui.Add(ui.bLog, OFX_IM_TOGGLE_BIG_XXL_BORDER);
			if (ui.bLog) {
				ui.Add(ui.bLogKeys, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
			}

			ui.AddSpacingBigSeparated();

			ui.AddLabelBig("ANIMATE");
			ui.AddSpacing();
			ui.Add(bAnimate, OFX_IM_TOGGLE_MEDIUM_BORDER_BLINK);
			ui.AddTooltip("Animate and randomize params \nto feed the Log.\nGo look into the Log window!");
			ui.AddSpacing();
			if (bAnimate)
			{
				ui.AddLabelBig("Modifiers");
				ui.Add(speed, OFX_IM_HSLIDER_SMALL);
				ui.AddTooltip("Sets the speed \nof Animation \nto feed the Log");

				ui.Add(amountPauses, OFX_IM_HSLIDER_SMALL);
				ui.AddTooltip("Density of \npause moments");
				ui.AddTooltip(amountPauses, true, false);
			}
		}

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

	// Ping every x seconds. 
	if (f % (4 * 120) == 0)
	{
		static int counter = 0;
		string s = "PING \t\t\t\t\t #" + ofToString(counter++);
		this->AddNotifyLog(s, OF_LOG_WARNING); // Raw without tag. 2nd argument empty
	}

	if (!bAnimate) return;

	// Make pauses
	float a = ofMap(amountPauses, amountPauses.getMax(), amountPauses.getMin(), 0.25f, 1.f);
	static int t1 = 600;
	if ((f % t1) == 0) t1 = (int)ofRandom(200, 600);
	if (f % t1 > (t1 * a))
	{
		return;
	}

	// Log d times per second at 60 fps
	if (1)
	{
		int d = ofMap(speed.get(), 0, 1, 120, 8);
		if (f % d == 0) doRandomNotifyLog();
	}

	// Auto populate random log messages.
	int m = ofMap(speed, 1, 0, 2, ofRandom(1) > 0.5 ? 60 : 40);

	if (f % m == 0)
	{
		auto t = ofGetElapsedTimef();
		float no = ofNoise(t);

		if (no < 0.4f) return; // skip one third

		doRandomNotifyLog();
	}
}

//--------------------------------------------------------------
void ofApp::Changed_Params(ofAbstractParameter& e)
{
	std::string name = e.getName();
	ofLogNotice() << name << ": " << e;

	string s = name + " : " + ofToString(e);
	ui.AddToLog(s);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'a') bAnimate = !bAnimate;

	doRandomNotifyLog();
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofRemoveListener(params.parameterChangedE(), this, &ofApp::Changed_Params);
	ofxImGuiSurfing::saveGroup(params);
}

//--

//--------------------------------------------------------------
void ofApp::AddNotifyLog(string text, string nameTag)
{
	ui.AddToNotifier(text, nameTag);
	ui.AddToLog(text, nameTag);
};

//--------------------------------------------------------------
void ofApp::AddNotifyLog(string text, ofLogLevel level)
{
	ui.AddToNotifier(text, level);
	ui.AddToLog(text, level);
};

//--------------------------------------------------------------
void ofApp::doRandomNotifyLog()
{
	float r = ofRandom(1.f);
	if (r < 0.5f)
	{
		ofxSurfingHelpers::logData d = ofxSurfingHelpers::getRandomLogData();
		this->AddNotifyLog(d.text, d.log);
	}
	else
	{
		ofxSurfingHelpers::logData d;
		d.log = OF_LOG_VERBOSE;
		d.text = ofxSurfingHelpers::getTextRandomSentence();
		this->AddNotifyLog(d.text, d.log);
	}
};