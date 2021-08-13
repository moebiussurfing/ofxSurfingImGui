#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);

	gui.setup();

	// style
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	ofxImGuiSurfing::setDefaultFont(gui);

	ofDirectory dataDirectory(ofToDataPath("", true));
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetBackgroundColor(24);

	ofDrawBitmapStringHighlight(strPath, 20, 400);
	ofDrawBitmapStringHighlight(strPathName, 20, 420);

	gui.begin();

	if (ofxImGuiSurfing::drawGui_FileDialog()) {
		ofLogWarning(__FUNCTION__) << "filePath     : " << ofxImGuiSurfing::filePath;
		ofLogWarning(__FUNCTION__) << "filePathName : " << ofxImGuiSurfing::filePathName;
		strPath = filePath;
		strPathName = filePathName;
	}

	gui.end();
}