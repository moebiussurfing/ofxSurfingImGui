#include "ofApp.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup() {
	ui.setName("NeoBangSequencer");
	ui.setup();
	ui.bLog = true;

	sequencer_.setup(this, &ui);

	sequencer_.setBangCallback([this](std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline) {
		onBangEvent(lane, step, fromTimeline);
	});

}

//--------------------------------------------------------------
void ofApp::update() {

	sequencer_.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	drawGui();
}

//--------------------------------------------------------------
void ofApp::drawGui() {
	ui.Begin();
	{
		drawImGuiBangs();

		sequencer_.drawImGui();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawImGuiBangs() {
	if (ui.BeginWindow(bGui_ofApp)) {
		ui.Add(sequencer_.bGui, OFX_IM_TOGGLE_ROUNDED);
		ui.AddSeparated();

		ui.AddLabelBig("Bang Actions");
		ui.AddLabel("Manual bangs + preview int (driven by timeline bangs).");

		ui.Add(targetBangsInt, OFX_IM_HSLIDER_BIG);
		ui.AddSpacingSeparated();

		ui.AddLabelBig("Manual Bang Buttons");

		auto & bangs = sequencer_.getBangParameters();
		for (std::size_t i = 0; i < bangs.size(); ++i) {
			const bool sameLine = (i % 2 == 0);
			ui.Add(bangs[i], OFX_IM_BUTTON_BIG, 2, sameLine);
		}

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::onBangEvent(std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline) {
	if (lane >= SurfingNeoSequencer::kBangCount) return;

	targetBangsInt = static_cast<int>(lane);

	string message = "bang " + ofToString(lane) + " @ step " + ofToString(step);
	ui.AddToLog(message, fromTimeline ? "NOTICE" : "WARNING");

	switch (targetBangsInt) {
	case 0:
		ui.AddToLog("action: lane 0", "VERBOSE");
		break;
	case 1:
		ui.AddToLog("action: lane 1", "VERBOSE");
		break;
	case 2:
		ui.AddToLog("action: lane 2", "VERBOSE");
		break;
	case 3:
		ui.AddToLog("action: lane 3", "VERBOSE");
		break;
	case 4:
		ui.AddToLog("action: lane 4", "VERBOSE");
		break;
	case 5:
		ui.AddToLog("action: lane 5", "VERBOSE");
		break;
	case 6:
		ui.AddToLog("action: lane 6", "VERBOSE");
		break;
	case 7:
		ui.AddToLog("action: lane 7", "VERBOSE");
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
	sequencer_.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	sequencer_.keyPressed(key);

	if (key == 'g' || key == 'G') bGui_ofApp = !bGui_ofApp;

	if (key == 'u' || key == 'U') sequencer_.bGuiTransport = !sequencer_.bGuiTransport;
	if (key == 't' || key == 'T') sequencer_.bGuiTimeline = !sequencer_.bGuiTimeline;
}
