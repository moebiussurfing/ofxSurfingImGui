#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(60);

	gui.setup();

	// style
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	ofxImGuiSurfing::setDefaultFont(gui, "assets/fonts/telegrama_render.otf", 16);

	notify.init();
}

//--------------------------------------------------------------
void ofApp::draw() {

	gui.begin();
	{
		notify.render();
	}
	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	ofLogVerbose(__FUNCTION__) << key;
}