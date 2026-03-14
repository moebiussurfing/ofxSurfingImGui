#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>
#include <string>
#include <vector>

#include "ofMain.h"

#include "imgui_neo_internal.h"
#include "imgui_neo_sequencer.h"
#include "ofxSurfingImGui.h"

class SurfingNeoSequencer {
public:
	static constexpr std::size_t kBangCount = 9;
	using BangCallback = std::function<void(std::size_t lane, ImGui::FrameIndexType step, bool fromTimeline)>;

	ofParameter<bool> bGuiTransport { "Transport", true };
	ofParameter<bool> bGuiTimeline { "Timeline", true };
	ofParameter<bool> bGui { "NeoSequencer", true };

	double lastUpdateTime_ = 0.0;

	void setUiPtr(ofxSurfingGui * ui) {
		ui_ = ui;
	}

	void setup(ofxSurfingGui * ui) {
		setUiPtr(ui);

		setupBangParameters();
		setupBangListeners();
		setupActionListeners();

		timelineKeys_.assign(kBangCount, {});
		lanesOpen_.assign(kBangCount, true);
		laneMute_.assign(kBangCount, false);
		laneSolo_.assign(kBangCount, false);

		laneColors_ = {
			ofFloatColor::fromHex(0xFF4D6D),
			ofFloatColor::fromHex(0xF59E0B),
			ofFloatColor::fromHex(0xFDE047),
			ofFloatColor::fromHex(0x22C55E),
			ofFloatColor::fromHex(0x06B6D4),
			ofFloatColor::fromHex(0x3B82F6),
			ofFloatColor::fromHex(0x8B5CF6),
			ofFloatColor::fromHex(0xEC4899),
			ofFloatColor::fromHex(0x14B8A6)
		};

		timelineKeys_[0] = { 0, 8, 16, 24, 32, 40, 48, 56 };
		timelineKeys_[1] = { 4, 12, 20, 28, 36, 44, 52, 60 };
		timelineKeys_[2] = { 0, 16, 32, 48 };
		timelineKeys_[3] = { 8, 24, 40, 56 };

		updateTimelineBounds();
		sanitizeAllLanes();
		resolveScenePath();
		loadSceneIfAvailable();

		auto & style = ImGui::GetNeoSequencerStyle();
		style.MaxSizePerTick = 8.0f;
		style.Colors[ImGuiNeoSequencerCol_Bg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiNeoSequencerCol_TimelinesBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		style.Colors[ImGuiNeoSequencerCol_TopBarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
		style.Colors[ImGuiNeoSequencerCol_ZoomBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.95f);
		style.Colors[ImGuiNeoSequencerCol_ZoomBarSlider] = ImVec4(0.30f, 0.30f, 0.30f, 0.88f);
		style.Colors[ImGuiNeoSequencerCol_ZoomBarSliderHovered] = ImVec4(0.38f, 0.38f, 0.38f, 0.93f);
		style.Colors[ImGuiNeoSequencerCol_ZoomBarSliderEnds] = ImVec4(0.24f, 0.24f, 0.24f, 0.90f);
		style.Colors[ImGuiNeoSequencerCol_ZoomBarSliderEndsHovered] = ImVec4(0.34f, 0.34f, 0.34f, 0.95f);
		style.Colors[ImGuiNeoSequencerCol_SelectedTimeline] = ImVec4(0.0f, 0.0f, 0.0f, 0.34f);

		lastUpdateTime_ = ofGetElapsedTimef();
	}

	void update() {
		const double now = ofGetElapsedTimef();
		const double deltaSeconds = std::max(0.0, now - lastUpdateTime_);
		lastUpdateTime_ = now;

		update(deltaSeconds);
	}

	void update(double deltaSeconds) {
		updateTransport(deltaSeconds);
	}

	void drawImGuiTimeline() {
		if (!ui_) return;
		drawTimelineSequencer();
	}

	void drawImGuiTransport() {
		if (!ui_) return;
		drawTransportControls();
	}

	void keyPressed(int key) {
		//if (key == ' ') play_ = !play_;
		//if (key == 'r' || key == 'R') currentFrame_ = startFrame_;
		//if (key == 's' || key == 'S') stopTransport();

		//if (key >= '0' && key <= '7') {
		//	triggerBang(static_cast<std::size_t>(key - '0'));
		//}
	}

	void exit() {
		saveSceneToDisk();
	}

	void setBangCallback(BangCallback callback) {
		bangCallback_ = std::move(callback);
	}

	std::vector<ofParameter<void>> & getBangParameters() {
		return bangs_;
	}

	const std::vector<ofParameter<void>> & getBangParameters() const {
		return bangs_;
	}

	std::size_t getBangCount() const {
		return kBangCount;
	}

	const std::array<ofFloatColor, kBangCount> & getLaneColors() const {
		return laneColors_;
	}

	int getSelectedLane() const {
		return selectedLane_;
	}

	void triggerBang(std::size_t laneIndex) {
		if (laneIndex >= kBangCount) return;

		timelineTriggerContext_ = false;
		timelineTriggerStep_ = currentFrame_;
		bangs_[laneIndex].trigger();
	}

private:
	ofxSurfingGui * ui_ = nullptr;

	BangCallback bangCallback_;

	std::vector<ofParameter<void>> bangs_;
	std::array<ofEventListener, kBangCount> bangListeners_;
	std::array<ofEventListener, 6> actionListeners_;

	std::vector<std::vector<ImGui::FrameIndexType>> timelineKeys_;
	std::vector<bool> lanesOpen_;
	std::vector<bool> laneMute_;
	std::vector<bool> laneSolo_;

	std::array<ofFloatColor, kBangCount> laneColors_ {};

	ofParameter<float> bpm_ { "BPM", 120.0f, 40.0f, 240.0f };
	ofParameter<int> bars_ { "Bars", 4, 1, 32 };
	ofParameter<bool> play_ { "Play", false };
	ofParameter<bool> replay_ { "Replay", false };
	ofParameter<bool> loop_ { "Loop", true };

	ofParameter<void> stop_ { "Stop" };
	ofParameter<void> clearAll_ { "Clear All" };
	ofParameter<void> clearSelected_ { "Clear Selected" };
	ofParameter<void> saveScene_ { "Save Scene" };
	ofParameter<void> loadScene_ { "Load Scene" };

	ImGui::FrameIndexType currentFrame_ = 0;
	ImGui::FrameIndexType startFrame_ = 0;
	ImGui::FrameIndexType endFrame_ = 63;

	bool channelsGroupOpen_ = true;
	bool timelineTriggerContext_ = false;
	ImGui::FrameIndexType timelineTriggerStep_ = 0;
	ImGui::FrameIndexType previousScrubFrame_ = 0;
	bool hasPreviousScrubFrame_ = false;

	int selectedLane_ = -1;
	int pendingSelectedLane_ = -1;

	double transportAccumulator_ = 0.0;
	bool wasPlaying_ = false;

	std::string scenePath_ = "bang_timeline_scene.json";
	std::string scenePathAbsolute_ = "bang_timeline_scene.json";

	static ImVec4 toImVec4(const ofFloatColor & color, float alpha = -1.0f) {
		const float finalAlpha = (alpha < 0.0f) ? color.a : alpha;
		return { color.r, color.g, color.b, finalAlpha };
	}

	void resolveScenePath() {
		try {
			scenePathAbsolute_ = ofToDataPath(scenePath_, true);
		} catch (const std::exception & exception) {
			scenePathAbsolute_ = scenePath_;
			ofLogWarning("SurfingNeoSequencer") << "Using fallback scene path due filesystem exception: " << exception.what();
		}
	}

	void loadSceneIfAvailable() {
		ofFile file(scenePathAbsolute_);
		if (file.exists()) {
			loadSceneFromDisk();
		}
	}

	void setupBangParameters() {
		bangs_.clear();
		bangs_.reserve(kBangCount);
		for (std::size_t i = 0; i < kBangCount; ++i) {
			bangs_.emplace_back();
			bangs_.back().set(ofToString(i));
		}
	}

public:
	void drawImGuiMainWidgets() {
		ui_->Add(bGui, OFX_IM_TOGGLE_ROUNDED);
		ui_->Indent();
		ui_->Add(bGuiTimeline, OFX_IM_TOGGLE_ROUNDED);
		ui_->Add(bGuiTransport, OFX_IM_TOGGLE_ROUNDED);
		ui_->Unindent();
		ui_->Add(ui_->bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);
		ui_->Add(ui_->bLog, OFX_IM_TOGGLE_ROUNDED_MINI);
		//ui_->AddSpacingBigSeparated();
	}

	void drawImGui() {
		if (!bGui) return;

		if (bGuiTransport) IMGUI_SUGAR__WINDOWS_CONSTRAINTS_MEDIUM
		if (ui_->BeginWindow(bGuiTransport)) {
			drawImGuiTransport();
			ui_->EndWindow();
		}

		if (bGuiTimeline) {
			ImGuiCond cond = ImGuiCond_FirstUseEver;
			//ImGuiCond cond = ImGuiCond_Always;
			ImGui::SetNextWindowPos(ImVec2(100, 100), cond);
			ImGui::SetNextWindowSize(ImVec2(600, 400), cond);
		}
		if (ui_->BeginWindow(bGuiTimeline)) {
			drawImGuiTimeline();
			ui_->EndWindow();
		}
	}

private:
	void drawTransportControls() {
		ui_->AddLabel("Transport");
		ui_->Add(play_, OFX_IM_TOGGLE_BIG_BORDER_BLINK, 4, true);
		ui_->Add(replay_, OFX_IM_TOGGLE_BIG, 4, true);
		ui_->Add(stop_, OFX_IM_BUTTON_BIG, 4, true);
		ui_->Add(loop_, OFX_IM_TOGGLE_BIG_BORDER, 4);

		ui_->AddLabel("Duration");
		ui_->Add(bars_, OFX_IM_STEPPER);

		//ui_->Add(bpm_, OFX_IM_HSLIDER);
		ui_->Add(bpm_);
		if (ui_->AddButton("Reset")) {
			bpm_.set(120);
		}

		ui_->AddLabel("Scene");
		ui_->Add(saveScene_, OFX_IM_BUTTON_BORDER, 2, true);
		ui_->Add(loadScene_, OFX_IM_BUTTON_BORDER, 2);

		ui_->Add(clearAll_, OFX_IM_BUTTON_BORDER_BLINK, 2, true);
		ImGui::BeginDisabled(selectedLane_ < 0);
		ui_->Add(clearSelected_, OFX_IM_BUTTON_BORDER, 2);
		ImGui::EndDisabled();
		ui_->AddSpacing();
		ui_->AddDebug();
		if (ui_->isDebug()) {
			if (selectedLane_ >= 0) {
				ui_->AddLabel("Selected lane: " + getLaneLabel(static_cast<std::size_t>(selectedLane_)));
			} else {
				ui_->AddLabel("Selected lane: none");
			}

			ui_->AddLabel("Cursor: " + formatStepMusical(currentFrame_) + " (step " + ofToString(currentFrame_) + ")");
			ui_->AddLabel("JSON: " + scenePathAbsolute_);
		}
	}

	void setupBangListeners() {
		for (std::size_t i = 0; i < kBangCount; ++i) {
			bangListeners_[i] = bangs_[i].newListener([this, i](const void *) {
				onBangTriggered(i);
			});
		}
	}

	void setupActionListeners() {
		actionListeners_[0] = replay_.newListener([this](bool & value) {
			if (!value) return;
			replayTransport();
			replay_ = false;
		});

		actionListeners_[1] = stop_.newListener([this](const void *) {
			stopTransport();
		});

		actionListeners_[2] = clearAll_.newListener([this](const void *) {
			clearAllLanes();
		});

		actionListeners_[3] = clearSelected_.newListener([this](const void *) {
			clearSelectedLane();
		});

		actionListeners_[4] = saveScene_.newListener([this](const void *) {
			saveSceneToDisk();
		});

		actionListeners_[5] = loadScene_.newListener([this](const void *) {
			loadSceneFromDisk();
		});
	}

	void drawInlineLaneControls(std::size_t laneIndex) {
		const ImVec4 rect = ImGui::NeoGetCurrentTimelineLabelRect();
		const ImVec2 backupCursor = ImGui::GetCursorScreenPos();
		const float laneHeight = rect.w - rect.y;
		const auto & style = ImGui::GetStyle();
		const float frameHeight = ImGui::GetFrameHeight();
		const float controlsY = rect.y + std::max(0.0f, (laneHeight - frameHeight) * 0.5f);
		const float controlsX = rect.x + 4.0f;

		const float wSolo = ImGui::CalcTextSize("solo").x + style.FramePadding.x * 2.0f;
		const float wMute = ImGui::CalcTextSize("mute").x + style.FramePadding.x * 2.0f;
		const float spacing = 2.0f;
		const float controlsWidth = wSolo + spacing + wMute;
		const float labelMinWidth = 40.0f;
		const float labelColumnX = std::min(controlsX + controlsWidth + 8.0f, rect.z - labelMinWidth - 2.0f);
		const float labelWidth = std::max(labelMinWidth, rect.z - labelColumnX - 4.0f);

		auto * drawList = ImGui::GetWindowDrawList();
		drawList->AddRectFilled(ImVec2(rect.x, rect.y), ImVec2(labelColumnX - 4.0f, rect.w), IM_COL32(0, 0, 0, 34));
		drawList->AddRectFilled(ImVec2(labelColumnX - 4.0f, rect.y), ImVec2(rect.z, rect.w), IM_COL32(0, 0, 0, 14));
		drawList->AddLine(ImVec2(labelColumnX - 4.0f, rect.y), ImVec2(labelColumnX - 4.0f, rect.w), IM_COL32(255, 255, 255, 35), 1.0f);

		ImGui::SetCursorScreenPos(ImVec2(controlsX, controlsY));

		ImGui::PushID(static_cast<int>(laneIndex) + 1000);
		const bool wasSoloEnabled = laneSolo_[laneIndex];
		if (wasSoloEnabled) {
			ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(60, 160, 60, 255));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(80, 190, 80, 255));
		}
		if (ImGui::SmallButton(laneSolo_[laneIndex] ? "SOLO" : "solo")) {
			laneSolo_[laneIndex] = !laneSolo_[laneIndex];
		}
		if (wasSoloEnabled) {
			ImGui::PopStyleColor(2);
		}

		ImGui::SameLine(0.0f, 2.0f);
		const bool wasMuteEnabled = laneMute_[laneIndex];
		if (wasMuteEnabled) {
			ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(190, 60, 60, 255));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(220, 80, 80, 255));
		}
		if (ImGui::SmallButton(laneMute_[laneIndex] ? "MUTE" : "mute")) {
			laneMute_[laneIndex] = !laneMute_[laneIndex];
		}
		if (wasMuteEnabled) {
			ImGui::PopStyleColor(2);
		}

		ImGui::SetCursorScreenPos(ImVec2(labelColumnX, controlsY));
		ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(0, 0, 0, 36));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(0, 0, 0, 52));
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertFloat4ToU32(toImVec4(laneColors_[laneIndex], 1.0f)));
		if (ImGui::Button(getLaneLabel(laneIndex).c_str(), ImVec2(labelWidth, frameHeight))) {
			pendingSelectedLane_ = static_cast<int>(laneIndex);
			selectedLane_ = static_cast<int>(laneIndex);
			triggerBang(laneIndex);
		}
		ImGui::PopStyleColor(4);

		ImGui::PopID();
		ImGui::SetCursorScreenPos(backupCursor);
	}

	void drawTimelineSequencer() {
		updateTimelineBounds();

		const ImGuiNeoSequencerFlags flags = ImGuiNeoSequencerFlags_EnableSelection | ImGuiNeoSequencerFlags_Selection_EnableDragging | ImGuiNeoSequencerFlags_Selection_EnableDeletion | ImGuiNeoSequencerFlags_AlwaysShowHeader;

		const ImVec2 size { 0.0f, std::max(260.0f, ImGui::GetContentRegionAvail().y) };

		if (!ImGui::BeginNeoSequencer("BangSequencer", &currentFrame_, &startFrame_, &endFrame_, size, flags)) {
			return;
		}

		if (!hasPreviousScrubFrame_) {
			previousScrubFrame_ = currentFrame_;
			hasPreviousScrubFrame_ = true;
		}

		if (pendingSelectedLane_ >= 0 && pendingSelectedLane_ < static_cast<int>(kBangCount)) {
			ImGui::SetSelectedTimeline(getLaneTimelineId(static_cast<std::size_t>(pendingSelectedLane_)).c_str());
			selectedLane_ = pendingSelectedLane_;
			pendingSelectedLane_ = -1;
		}

		if (ImGui::BeginNeoGroup("Bang Channels", &channelsGroupOpen_)) {
			for (std::size_t i = 0; i < kBangCount; ++i) {
				const ImVec4 keyColor = toImVec4(laneColors_[i], 0.55f);
				const ImVec4 hoverColor = toImVec4(laneColors_[i], 0.95f);
				const ImVec4 selectedColor = toImVec4(laneColors_[i].getLerped(ofFloatColor::white, 0.2f), 1.0f);

				ImGui::PushNeoSequencerStyleColor(ImGuiNeoSequencerCol_Keyframe, keyColor);
				ImGui::PushNeoSequencerStyleColor(ImGuiNeoSequencerCol_KeyframeHovered, hoverColor);
				ImGui::PushNeoSequencerStyleColor(ImGuiNeoSequencerCol_KeyframeSelected, selectedColor);

				bool laneOpen = lanesOpen_[i];
				const std::string laneId = getLaneTimelineId(i);

				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 0));
				const bool timelineOpened = ImGui::BeginNeoTimelineEx(laneId.c_str(), &laneOpen);
				ImGui::PopStyleColor();

				if (timelineOpened) {
					if (ImGui::IsNeoTimelineSelected()) {
						selectedLane_ = static_cast<int>(i);
					}

					drawInlineLaneControls(i);

					auto & lane = timelineKeys_[i];
					bool hoveredAnyKey = false;
					bool removeOne = false;
					ImGui::FrameIndexType removeFrame = 0;

					for (auto & frame : lane) {
						ImGui::NeoKeyframe(&frame);
						hoveredAnyKey = hoveredAnyKey || ImGui::IsNeoKeyframeHovered();
						if (ImGui::IsNeoKeyframeRightClicked()) {
							removeOne = true;
							removeFrame = frame;
						}
					}

					if (removeOne) {
						removeKeyframe(i, removeFrame);
					}

					const bool canInsert = ImGui::IsNeoTimelineSelected() && !ImGui::NeoIsSelecting() && !ImGui::NeoIsDraggingSelection();

					if (canInsert && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && !hoveredAnyKey) {
						insertKeyframe(i, currentFrame_);
					}

					if (canInsert && ImGui::IsMouseClicked(ImGuiMouseButton_Right) && !hoveredAnyKey && !ImGui::IsNeoKeyframeSelectionRightClicked()) {
						insertKeyframe(i, currentFrame_);
					}

					if (ImGui::NeoCanDeleteSelection()) {
						const bool deleteByKeyboard = ImGui::IsKeyPressed(ImGuiKey_Delete, false) || ImGui::IsKeyPressed(ImGuiKey_Backspace, false);
						const bool deleteByMouse = ImGui::IsNeoKeyframeSelectionRightClicked();
						if (deleteByKeyboard || deleteByMouse) {
							removeSelectedKeyframesFromLane(i);
						}
					}

					ImGui::EndNeoTimeLine();
				}

				lanesOpen_[i] = laneOpen;
				ImGui::PopNeoSequencerStyleColor(3);
			}

			ImGui::EndNeoGroup();
		}

		if (!ImGui::NeoIsSelecting() && !ImGui::NeoIsDraggingSelection()) {
			sanitizeAllLanes();
		}

		if (!play_) {
			const bool scrubbingWithMouse = ImGui::IsMouseDown(ImGuiMouseButton_Left);
			if (scrubbingWithMouse && currentFrame_ != previousScrubFrame_) {
				processTimelineRange(previousScrubFrame_, currentFrame_);
			}
			previousScrubFrame_ = currentFrame_;
		} else {
			previousScrubFrame_ = currentFrame_;
		}

		ImGui::EndNeoSequencer();
	}

	void processTimelineRange(ImGui::FrameIndexType fromStep, ImGui::FrameIndexType toStep) {
		if (fromStep == toStep) return;

		const int64_t from = static_cast<int64_t>(fromStep);
		const int64_t to = static_cast<int64_t>(toStep);

		if (from < to) {
			for (int64_t step = from + 1; step <= to; ++step) {
				processTimelineStep(static_cast<ImGui::FrameIndexType>(step));
			}
		} else {
			for (int64_t step = from - 1; step >= to; --step) {
				processTimelineStep(static_cast<ImGui::FrameIndexType>(step));
			}
		}
	}

	void onBangTriggered(std::size_t index) {
		if (index >= kBangCount) return;

		const ImGui::FrameIndexType step = timelineTriggerContext_ ? timelineTriggerStep_ : currentFrame_;
		const bool fromTimeline = timelineTriggerContext_;

		if (bangCallback_) {
			bangCallback_(index, step, fromTimeline);
		}
	}

	void triggerBangFromTimeline(std::size_t index, ImGui::FrameIndexType step) {
		if (index >= kBangCount) return;

		timelineTriggerContext_ = true;
		timelineTriggerStep_ = step;
		bangs_[index].trigger();
		timelineTriggerContext_ = false;
	}

	bool isLanePlayable(std::size_t index) const {
		if (index >= kBangCount) return false;

		const bool anySolo = std::any_of(laneSolo_.begin(), laneSolo_.end(), [](bool enabled) {
			return enabled;
		});

		if (anySolo) {
			return laneSolo_[index] && !laneMute_[index];
		}

		return !laneMute_[index];
	}

public:
	void stopTransport() {
		play_ = false;
		currentFrame_ = startFrame_;
		transportAccumulator_ = 0.0;
		wasPlaying_ = false;
	}

	void replayTransport() {
		currentFrame_ = startFrame_;
		transportAccumulator_ = 0.0;
		wasPlaying_ = false;
		play_ = true;
	}

private:
	void updateTransport(double deltaSeconds) {
		updateTimelineBounds();

		if (!play_) {
			wasPlaying_ = false;
			transportAccumulator_ = 0.0;
			return;
		}

		const float safeBpm = std::max(1.0f, bpm_.get());
		const double secondsPer16th = 60.0 / (static_cast<double>(safeBpm) * 4.0);

		if (!wasPlaying_) {
			processTimelineStep(currentFrame_);
			wasPlaying_ = true;
		}

		transportAccumulator_ += std::max(0.0, deltaSeconds);
		while (transportAccumulator_ >= secondsPer16th) {
			transportAccumulator_ -= secondsPer16th;

			if (currentFrame_ >= endFrame_) {
				if (loop_) {
					currentFrame_ = startFrame_;
				} else {
					currentFrame_ = endFrame_;
					play_ = false;
					break;
				}
			} else {
				currentFrame_++;
			}

			processTimelineStep(currentFrame_);
		}
	}

	void processTimelineStep(ImGui::FrameIndexType step) {
		for (std::size_t i = 0; i < kBangCount; ++i) {
			if (!isLanePlayable(i)) continue;

			const auto & lane = timelineKeys_[i];
			if (std::binary_search(lane.begin(), lane.end(), step)) {
				triggerBangFromTimeline(i, step);
			}
		}
	}

	bool insertKeyframe(std::size_t laneIndex, ImGui::FrameIndexType step) {
		if (laneIndex >= kBangCount) return false;

		const ImGui::FrameIndexType clamped = std::clamp(step, startFrame_, endFrame_);
		auto & lane = timelineKeys_[laneIndex];
		if (std::find(lane.begin(), lane.end(), clamped) != lane.end()) return false;

		lane.push_back(clamped);
		sanitizeLane(laneIndex);
		return true;
	}

	bool removeKeyframe(std::size_t laneIndex, ImGui::FrameIndexType step) {
		if (laneIndex >= kBangCount) return false;

		auto & lane = timelineKeys_[laneIndex];
		const auto it = std::remove(lane.begin(), lane.end(), step);
		if (it == lane.end()) return false;

		lane.erase(it, lane.end());
		sanitizeLane(laneIndex);
		return true;
	}

	void removeSelectedKeyframesFromLane(std::size_t laneIndex) {
		if (laneIndex >= kBangCount) return;

		const uint32_t count = ImGui::GetNeoKeyframeSelectionSize();
		if (count == 0) return;

		std::vector<ImGui::FrameIndexType> toRemove(count);
		ImGui::GetNeoKeyframeSelection(toRemove.data());

		auto & lane = timelineKeys_[laneIndex];
		for (const auto frame : toRemove) {
			lane.erase(std::remove(lane.begin(), lane.end(), frame), lane.end());
		}

		sanitizeLane(laneIndex);
		ImGui::NeoClearSelection();
	}

	void clearAllLanes() {
		for (auto & lane : timelineKeys_) {
			lane.clear();
		}
	}

	void clearSelectedLane() {
		if (selectedLane_ < 0 || selectedLane_ >= static_cast<int>(kBangCount)) {
			return;
		}

		timelineKeys_[static_cast<std::size_t>(selectedLane_)].clear();
	}

	void sanitizeLane(std::size_t laneIndex) {
		if (laneIndex >= kBangCount) return;

		auto & lane = timelineKeys_[laneIndex];
		for (auto & frame : lane) {
			frame = std::clamp(frame, startFrame_, endFrame_);
		}

		std::sort(lane.begin(), lane.end());
		lane.erase(std::unique(lane.begin(), lane.end()), lane.end());
	}

	void sanitizeAllLanes() {
		for (std::size_t i = 0; i < kBangCount; ++i) {
			sanitizeLane(i);
		}
	}

	void updateTimelineBounds() {
		const auto totalSteps = static_cast<ImGui::FrameIndexType>(std::max<std::size_t>(16, getTotalSteps()));
		startFrame_ = 0;
		endFrame_ = std::max<ImGui::FrameIndexType>(1, totalSteps) - 1;
		currentFrame_ = std::clamp(currentFrame_, startFrame_, endFrame_);
	}

	std::size_t getTotalSteps() const {
		return static_cast<std::size_t>(bars_.get()) * 16u;
	}

	std::string getLaneLabel(std::size_t laneIndex) const {
		if (laneIndex < bangs_.size()) return bangs_[laneIndex].getName();
		return ofToString(laneIndex);
	}

	std::string getLaneTimelineId(std::size_t laneIndex) const {
		return "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  " + getLaneLabel(laneIndex) + "##lane_" + ofToString(laneIndex);
	}

	std::string formatStepMusical(ImGui::FrameIndexType step) const {
		const ImGui::FrameIndexType clamped = std::max<ImGui::FrameIndexType>(0, step);
		const ImGui::FrameIndexType bar = clamped / 16 + 1;
		const ImGui::FrameIndexType beat = (clamped % 16) / 4 + 1;
		const ImGui::FrameIndexType sixteenth = clamped % 4 + 1;
		return "Bar " + ofToString(bar) + " Beat " + ofToString(beat) + " 1/16 " + ofToString(sixteenth);
	}

	void saveSceneToDisk() const {
		try {
			ofJson root;
			root["version"] = 1;
			root["bpm"] = bpm_.get();
			root["bars"] = bars_.get();
			root["currentFrame"] = currentFrame_;
			root["loop"] = loop_.get();
			root["play"] = play_.get();

			root["lanes"] = ofJson::array();
			for (std::size_t i = 0; i < kBangCount; ++i) {
				ofJson lane;
				lane["index"] = static_cast<int>(i);
				lane["name"] = getLaneLabel(i);
				lane["mute"] = laneMute_[i];
				lane["solo"] = laneSolo_[i];
				lane["keys"] = ofJson::array();

				for (const auto frame : timelineKeys_[i]) {
					lane["keys"].push_back(frame);
				}

				root["lanes"].push_back(lane);
			}

			const bool ok = ofSavePrettyJson(scenePathAbsolute_, root);
			if (!ok) {
				ofLogError("SurfingNeoSequencer") << "Unable to save scene: " << scenePathAbsolute_;
			}
		} catch (const std::exception & exception) {
			ofLogError("SurfingNeoSequencer") << "Scene save exception: " << exception.what();
		}
	}

	void loadSceneFromDisk() {
		try {
			ofFile file(scenePathAbsolute_);
			if (!file.exists()) {
				ofLogWarning("SurfingNeoSequencer") << "Scene file not found: " << scenePathAbsolute_;
				return;
			}

			const ofJson root = ofLoadJson(scenePathAbsolute_);
			if (root.is_discarded()) {
				ofLogError("SurfingNeoSequencer") << "Invalid JSON scene file: " << scenePathAbsolute_;
				return;
			}

			if (root.contains("bpm")) {
				bpm_ = ofClamp(root["bpm"].get<float>(), bpm_.getMin(), bpm_.getMax());
			}
			if (root.contains("bars")) {
				bars_ = ofClamp(root["bars"].get<int>(), bars_.getMin(), bars_.getMax());
			}
			if (root.contains("loop")) {
				loop_ = root["loop"].get<bool>();
			}
			if (root.contains("play")) {
				play_ = root["play"].get<bool>();
			}

			if (root.contains("lanes") && root["lanes"].is_array()) {
				for (auto & lane : timelineKeys_) {
					lane.clear();
				}

				const auto & lanesJson = root["lanes"];
				const std::size_t count = std::min<std::size_t>(kBangCount, lanesJson.size());
				for (std::size_t i = 0; i < count; ++i) {
					const auto & lane = lanesJson[i];

					laneMute_[i] = lane.value("mute", false);
					laneSolo_[i] = lane.value("solo", false);

					if (lane.contains("keys") && lane["keys"].is_array()) {
						timelineKeys_[i].reserve(lane["keys"].size());
						for (const auto & key : lane["keys"]) {
							if (key.is_number_integer()) {
								timelineKeys_[i].push_back(key.get<ImGui::FrameIndexType>());
							}
						}
					}

					sanitizeLane(i);
				}
			}

			updateTimelineBounds();
			if (root.contains("currentFrame") && root["currentFrame"].is_number_integer()) {
				currentFrame_ = std::clamp(root["currentFrame"].get<ImGui::FrameIndexType>(), startFrame_, endFrame_);
			}
		} catch (const std::exception & exception) {
			ofLogError("SurfingNeoSequencer") << "Scene load exception: " << exception.what();
		}
	}
};
