#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	gui.setup();
}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.Begin();
	{
		if (ofxImGuiSurfing::drawGui_FileDialog()) {
			ofLogNotice() << "filePath     : " << ofxImGuiSurfing::filePath;
			ofLogNotice() << "filePathName : " << ofxImGuiSurfing::filePathName;
			strPath = filePath;
			strPathName = filePathName;
		}
	}
	gui.End();

	// display last picked file
	if (strPath != "" || strPathName != "") {
		ofDrawBitmapStringHighlight(strPath, 20, 40);
		ofDrawBitmapStringHighlight(strPathName, 20, 420);
	}
}