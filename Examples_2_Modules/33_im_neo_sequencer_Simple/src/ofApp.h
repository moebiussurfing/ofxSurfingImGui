#pragma once

#include <array>
#include <vector>

#include "ofMain.h"

#include "SurfingNeoSequencer.h"
#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp {
public:
	ofxSurfingGui ui;
	ofParameter<bool> bGui_ofApp { "ofApp", true };

	void setup();
	void update();
	void draw();
	void drawGui();
	void exit();
	void keyPressed(int key);

private:
	SurfingNeoSequencer sequencer_;

	ofParameter<int> targetBangsInt { "Bang Int", 0, 0, static_cast<int>(SurfingNeoSequencer::kBangCount) - 1 };

	std::array<ofFloatColor, SurfingNeoSequencer::kBangCount> laneColors_ {};

	void drawImGuiBangs();
	void onBangEvent(std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline);
};
