#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	setupParams();

	setupImGui();
}

//--------------------------------------------------------------
void ofApp::setupParams()
{
	params.setName("G");
	params.add(speed.set("Speed", 0.5f, 0, 1));
	params.add(bPrevious.set("<"));
	params.add(bNext.set(">"));
	params.add(lineWidth.set("Width", 0.5f, 0, 1));
	params.add(separation.set("Separation", 50, 1, 100));
	params.add(amount.set("Amount", 10, 0, 25));
	params.add(bEnable.set("Enable", true));

	ofAddListener(params.parameterChangedE(), this, &ofApp::Changed_Params);
}

//--------------------------------------------------------------
void ofApp::setupImGui()
{
	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawImGui();

	udpateScene();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	ui.Begin();

	if (ui.BeginWindow("ofApp"))
	{
		ui.Add(ui.bMinimize, OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL);
		ui.AddSpacingBigSeparated();

		ui.AddLabelBig("LOG SYSTEM");
		ui.AddSpacing();
		ui.Add(ui.bLog, OFX_IM_TOGGLE_BIG_XXL_BORDER);
		ui.Add(ui.bLogKeys, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
		ui.AddSpacing();

		ui.AddLabel("Animate");
		ui.Add(bEnable, OFX_IM_TOGGLE_MEDIUM_BORDER_BLINK);
		ui.AddTooltip("Animate and randomize params \nto feed the Log.\nGo look into the Log window!");
		ui.AddSpacingBigSeparated();

		ui.Add(speed, OFX_IM_HSLIDER_BIG);
		ui.AddTooltip("Sets the speed \nof animation to Log");

		ui.Add(amount, OFX_IM_HSLIDER_NO_LABELS);
		ui.AddTooltip(amount, true, false);
		ui.AddSpacingBigSeparated();

		//--

		// A bundle of controls
		// for a single param
		ui.AddComboBundle(lineWidth);

		//--

		ui.AddSpacingBigSeparated();

		ui.Add(separation, OFX_IM_HSLIDER_BIG);

		//--

		ui.EndWindow();
	}

	ui.End();
}

//--------------------------------------------------------------
void ofApp::udpateScene()
{
	// Animate some vars

	if (!bEnable) return;

	// Animate
	if (0) {
		float t = ofGetElapsedTimef();
		float s = ofMap(amount, amount.getMax(), amount.getMin(), 1, 10);
		t = ofWrap(t, 0, s);
		separation = ofMap(t, 0, s, separation.getMin(), separation.getMax());
	}

	// Log
	updateLog();
}

//--------------------------------------------------------------
void ofApp::updateLog()
{
	// Make pauses
	static int t1 = 600;
	if ((ofGetFrameNum() % t1) == 0) t1 = (int)ofRandom(200, 600);
	if (ofGetFrameNum() % t1 > (t1 * 0.75f)) {
		return;
	}

	// Log d times per second at 60 fps
	if (1) {
		int d = ofMap(speed.get(), 0, 1, 120, 8);
		if (ofGetFrameNum() % d == 0)
			ui.AddToLog(separation.getName() + " : " + ofToString(separation));
	}

	// Auto populate random log messages.
	int m = ofMap(speed, 1, 0, 2, ofRandom(1) > 0.5 ? 60 : 40);
	if (ofGetFrameNum() % m == 0)
	{
		if (ofNoise(ofGetElapsedTimef()) < 0.4f) return; // skip one third

		std::string ss = ofToString(ofGetFrameNum());
		float _rnd = ofRandom(1);
		if (_rnd < 0.2) ui.AddToLog(ss);
		else if (_rnd < 0.4) ui.AddToLog(ofToString(_rnd));
		else if (_rnd < 0.6) ui.AddToLog(ofToString(ofToString((ofRandom(1) < 0.5 ? "..-." : "---.--..")) + "---------" + ofToString((ofRandom(1) < 0.5 ? ".--.-." : "...-.--.."))));
		else if (_rnd < 0.8) ui.AddToLog(ofToString((ofRandom(1) < 0.5 ? "...-." : "--.--") + ofToString("===//...--//-----..")));
		else ui.AddToLog(ofGetTimestampString());
	}
}

//--------------------------------------------------------------
void ofApp::Changed_Params(ofAbstractParameter& e)
{
	std::string name = e.getName();
	ofLogNotice() << name << " : " << e;

	if (name == bPrevious.getName() || name == bNext.getName()) return;

	string s = name + " : " + ofToString(e);
	ui.AddToLog(s);
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofRemoveListener(params.parameterChangedE(), this, &ofApp::Changed_Params);
}
