#pragma once

#include "ofxiOS.h"

#include "ofxSurfingImGui.h"

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
	
	ofxSurfingGui ui;
	ofParameter<bool> bGui{ "ofApp", true };
	
	ofParameter<bool> bEnable{ "Enable", true };
	ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
	ofParameter<float> value{ "Value", 1.f, 0.f, 10.f };
	ofParameter<int> index{ "Index", 1, 0, 5 };
	ofParameterGroup params{ "MyParamGroup", bEnable, speed, value, index };

	void drawDebug();
};
