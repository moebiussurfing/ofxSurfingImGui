#pragma once

#include <array>
#include <vector>

#include "ofMain.h"

#include "BangParticle.h"
#include "SurfingNeoSequencer.h"
#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp {
public:
	ofxSurfingGui ui;
	ofParameter<bool> bGuiMain { "ofApp", true };

	void setup();
	void update();
	void draw();
	void drawGui();
	void exit();
	void keyPressed(int key);

private:
	SurfingNeoSequencer sequencer_;
	double lastUpdateTime_ = 0.0;

	ofParameter<int> bangDrawInt_ { "Bang Draw Int", 0, 0, static_cast<int>(SurfingNeoSequencer::kBangCount) - 1 };

	std::array<ofFloatColor, SurfingNeoSequencer::kBangCount> laneColors_ {};
	std::vector<BangParticle> particles_;

	void drawImGuiBangs();
	void onBangEvent(std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline);
	ofVec2f getLaneAnchorPosition(std::size_t lane) const;
	void drawLaneAnchors() const;
	void spawnParticleForLane(std::size_t lane);
	void updateParticles(float deltaSeconds);
	void drawParticles() const;
};
