#pragma once

#include "ofxiOS.h"

#include "ofxSurfingImGui.h"

#include "imgui_stdlib.h"
#include "BigTextInput.h"
#define RATIO_WIDGETS_FONTS 0.25f

class ofApp : public ofxiOSApp {
	
public:
	void setup() override;
	void update() override;
	void draw() override;
	void exit() override;
	
	void touchDown(ofTouchEventArgs & touch) override;
	void touchMoved(ofTouchEventArgs & touch) override;
	void touchUp(ofTouchEventArgs & touch) override;
	void touchDoubleTap(ofTouchEventArgs & touch) override;
	void touchCancelled(ofTouchEventArgs & touch) override;
	
	void lostFocus() override;
	void gotFocus() override;
	void gotMemoryWarning() override;
	void deviceOrientationChanged(int newOrientation) override;
	void launchedWithURL(std::string url) override;
	
	//--
	
	ofxSurfingGui ui;
	void setupImGui();
	void drawImGui();
	ofParameter<bool> bGui{ "ofApp", true };

	ofParameter<bool> bGui_Headers{ "Headers", true };
	ofParameter<bool> bGui_Bg{ "Bg", true };
	ofParameter<bool> bGui_ResizePin{ "Resizer", true };
	ofParameter<bool> bGui_UnlockMove{ "Unlock", true };
	ofParameter<bool> bGui_EditLayout{ "EDIT LAYOUT", false };
	ofEventListener listener_bGui_EditLayout;

	void drawImGui_Slider();
	void doResetSlider();
	ofParameter<bool> bGui_Slider{ "Slider", true };
	ofParameter<float> value{ "Value", 0, 0, 1.f };
	ofColor cRange = ofColor::green;
	ofColor cRangeRaw = ofColor::red;
	bool bResetSlider = 0;
	bool bColorize = false;//slider

	ofParameter<bool> bGui_Toggle{ "Toggle", true };
	ofParameter<bool> bToggle{ "Toggle", false };
	void drawImGui_Toggle();

	ofParameter<bool> bGui_Button{ "Button", true };
	ofParameter<void> vButton{ "Button" };
	void drawImGui_Button();

	BigTextInput bigTextInput;

	ofParameterGroup g{ "ofApp" };


	void BeginNoDecoration();
	void EndNoDecoration();
	ImGuiWindowFlags window_flags;
};
