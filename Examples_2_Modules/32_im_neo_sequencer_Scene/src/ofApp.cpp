#include "ofApp.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup() {
	ui.setName("NeoBangSequencer");
	ui.setup();
	//ui.bAutoResize = false;
	//ui.bLog = true;

	sequencer_.setup(&ui);
	laneColors_ = sequencer_.getLaneColors();
	particles_.reserve(256);

	sequencer_.setBangCallback([this](std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline) {
		onBangEvent(lane, step, fromTimeline);
	});

	lastUpdateTime_ = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update() {
	const double now = ofGetElapsedTimef();
	const double deltaSeconds = std::max(0.0, now - lastUpdateTime_);
	lastUpdateTime_ = now;
	updateParticles(static_cast<float>(deltaSeconds));

	sequencer_.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	drawLaneAnchors();
	drawParticles();
	drawGui();
}

//--------------------------------------------------------------
void ofApp::drawGui() {
	ui.Begin();
	{
		if (ui.BeginWindow(bGuiMain)) {
			drawImGuiBangs();
			ui.EndWindow();
		}

		sequencer_.drawImGui();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawImGuiBangs() {
	ui.Add(sequencer_.bGui, OFX_IM_TOGGLE_ROUNDED);
	ui.AddSeparated();

	ui.AddLabelBig("Bang Actions");
	ui.AddLabel("Manual bangs + preview int (driven by timeline bangs).");

	ui.Add(bangDrawInt_, OFX_IM_HSLIDER_BIG);
	ui.AddSpacingSeparated();

	ui.AddLabelBig("Manual Bang Buttons");

	auto & bangs = sequencer_.getBangParameters();
	for (std::size_t i = 0; i < bangs.size(); ++i) {
		const bool sameLine = (i % 2 == 0);
		ui.Add(bangs[i], OFX_IM_BUTTON_BIG, 2, sameLine);
	}
}

//--------------------------------------------------------------
void ofApp::onBangEvent(std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline) {
	if (lane >= SurfingNeoSequencer::kBangCount) return;

	bangDrawInt_ = static_cast<int>(lane);
	spawnParticleForLane(lane);

	const int r = ofClamp(static_cast<int>(laneColors_[lane].r * 255.0f), 0, 255);
	const int g = ofClamp(static_cast<int>(laneColors_[lane].g * 255.0f), 0, 255);
	const int b = ofClamp(static_cast<int>(laneColors_[lane].b * 255.0f), 0, 255);
	std::ostringstream colorHex;
	colorHex << '#' << std::uppercase << std::hex << std::setfill('0')
			 << std::setw(2) << r << std::setw(2) << g << std::setw(2) << b;

	const std::string source = fromTimeline ? "[SEQ] " : "[MAN] ";
	std::string message;
	if (fromTimeline)
		message = source + "bang " + ofToString(lane) + " @ step " + ofToString(step);
	else
		message = source + "bang " + ofToString(lane);
	ui.AddToLog(message, fromTimeline ? "NOTICE" : "WARNING");
}

//--------------------------------------------------------------
void ofApp::spawnParticleForLane(std::size_t lane) {
	if (lane >= SurfingNeoSequencer::kBangCount) return;

	const ofVec2f position = getLaneAnchorPosition(lane);
	particles_.emplace_back(position, laneColors_[lane], 56.0f, 1.0f);
}

//--------------------------------------------------------------
ofVec2f ofApp::getLaneAnchorPosition(std::size_t lane) const {
	const float laneCount = static_cast<float>(SurfingNeoSequencer::kBangCount);
	const float w = static_cast<float>(ofGetWidth());
	const float h = static_cast<float>(ofGetHeight());
	const float laneWidth = std::max(1.0f, w / laneCount);

	const float x = laneWidth * static_cast<float>(lane) + laneWidth * 0.5f;
	const float y = std::max(16.0f, h - 56.0f);
	return { x, y };
}

//--------------------------------------------------------------
void ofApp::drawLaneAnchors() const {
	ofPushStyle();
	ofFill();
	for (std::size_t lane = 0; lane < SurfingNeoSequencer::kBangCount; ++lane) {
		ofFloatColor color = laneColors_[lane];
		color.a = 0.9f;
		ofSetColor(color);
		ofDrawCircle(getLaneAnchorPosition(lane), 10.0f);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::updateParticles(float deltaSeconds) {
	for (auto & particle : particles_) {
		particle.update(deltaSeconds);
	}

	particles_.erase(std::remove_if(
						 particles_.begin(), particles_.end(), [](const BangParticle & particle) {
							 return !particle.isAlive();
						 }),
		particles_.end());
}

//--------------------------------------------------------------
void ofApp::drawParticles() const {
	ofPushStyle();
	ofFill();
	for (const auto & particle : particles_) {
		particle.draw();
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::exit() {
	sequencer_.exit();
	ui.save();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	sequencer_.keyPressed(key);

	if (key == 'g' || key == 'G') bGuiMain = !bGuiMain;
	if (key == 'u' || key == 'U') sequencer_.bGuiTransport = !sequencer_.bGuiTransport;
	if (key == 't' || key == 'T') sequencer_.bGuiTimeline = !sequencer_.bGuiTimeline;
}
