#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	int h = 35;
	ofSetWindowPosition(1920, h);
	ofSetWindowShape(1920, 1080 - h);

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

	ofAddListener(params.parameterChangedE(), this, &ofApp::Changed_Params);
}

//--------------------------------------------------------------
void ofApp::setupImGui()
{
	//ui.setEnablebMouseCursorFromImGui(false);
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

		ui.AddLabelHuge("NOTIFIER SYSTEM");
		ui.AddSpacing();
		ui.Add(ui.bNotifier, OFX_IM_TOGGLE_BIG_XXL_BORDER);
		if (ui.AddButton("Random Notify", OFX_IM_BUTTON_BIG)) {
			doRandomNotifyLog();
		};

		ui.AddSpacingBigSeparated();

		ui.AddLabelHuge("LOG SYSTEM");
		ui.AddSpacing();
		ui.Add(ui.bLog, OFX_IM_TOGGLE_BIG_XXL_BORDER);
		if (b) if (ui.bLog) {
			ui.Add(ui.bLogKeys, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
		}

		if (ui.isMaximized()) {
			ui.AddSpacingBigSeparated();

			if (b) ui.AddLabelBig("ANIMATE");
			if (b) ui.AddSpacing();
			ui.Add(bAnimate1, OFX_IM_TOGGLE_MEDIUM_BORDER_BLINK);
			ui.AddTooltip("Animate and randomize params \nto feed the Log.\nGo look into the Log window!");
			ui.AddSpacing();
			if (bAnimate1)
			{
				if (b) ui.AddLabelBig("MODIFIERS");
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

	// Ping every 2 seconds. 
	if (f % 120 == 0)
	{
		static int counter = 0;
		string s = "PING \t\t\t\t\t #" + ofToString(counter++);
		this->AddNotifyLog(s); // Raw without tag. 2nd argument empty
	}

	if (!bAnimate1) return;

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
	doRandomNotifyLog();
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofRemoveListener(params.parameterChangedE(), this, &ofApp::Changed_Params);
	ofxSurfingHelpers::saveGroup(params);
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
		auto d = ofxSurfingHelpers::getRandomLogData();
		this->AddNotifyLog(d.text, d.log);
	}
	else
	{
		ofxSurfingHelpers::logData d;
		d.text = getTextRandomSentence();
		this->AddNotifyLog(d.text, d.log);
	}
};