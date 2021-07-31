#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);

	gui.setup();

	// style
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	ofxImGuiSurfing::setDefaultFont(gui);

	// fix?
	fileBrowser.current_path = ofToDataPath("", true);

	//ofDirectory dataDirectory(ofToDataPath("", true));
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetBackgroundColor(24);

	ofDrawBitmapStringHighlight(strPath, 20, 400);
	ofDrawBitmapStringHighlight(strPathName, 20, 420);

	gui.begin();

	ImGui::Begin("Browser");

	//std::string& label
	//fileBrowser.setIsRetina(false);

	ImVec2& sz_xy = ImVec2(600, 600);
	std::string valid_types = "xml";
	std::string nameProposal = "nameProposal";

	fileBrowser.showFileDialog("label", imgui_addons::ImGuiFileBrowser::DialogMode::SELECT, sz_xy, valid_types);


	//if (ofxImGuiSurfing::drawGui_FileDialog()) 
	//{
	//	ofLogWarning(__FUNCTION__) << "filePath     : " << ofxImGuiSurfing::filePath;
	//	ofLogWarning(__FUNCTION__) << "filePathName : " << ofxImGuiSurfing::filePathName;
	//	strPath = filePath;
	//	strPathName = filePathName;
	//}

	ImGui::End();

	gui.end();
}