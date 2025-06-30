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
	
	//--
	
	// Gui manager
	ofxSurfingGui ui;
	
	void setupImGui();
	
	void drawImGui();
	void drawImGuiApp();
	void drawImGuiSpecialWindows();
	
	void drawImGuiSpecialWindow0();
	void drawImGuiSpecialWindow1();
	void drawImGuiSpecialWindow2();
	void drawImGuiSpecialWindow3();
	void drawImGuiSpecialWindow4();
	
	ofParameter<bool> bGui { "APP", true };
	
	//--
	
	// Docking Helpers Stuff
	
	ofParameter<bool> bGui_DockingHelp { "DOCKING HELP", true };
	
	// To learning purposes
	// but also to be used as template for your projects.
	void updateImGuiDockingHelpers();
	void drawImGuiDockingHelp();
	
	// An extra window with some triggers
	// for hard-coded layout modifications.
	void doDockingReset(); // Reset the layout to a hard-coded default layout.
	
	// Flags
	bool bFlagDockingReset = false;
	
	//--
	
	// Manager to Save/Load Layout manually
	string path = "myLayout.ini";
};
