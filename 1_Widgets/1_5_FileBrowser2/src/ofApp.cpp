#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);

	gui.setup();

	// style
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	ofxImGuiSurfing::setDefaultFont(gui);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetBackgroundColor(24);

	ofDrawBitmapStringHighlight(strFileName, 20, ofGetHeight() - 20);
	ofDrawBitmapStringHighlight(strPath, 20, ofGetHeight() - 40);

	gui.begin();
	{
		ImGui::Begin("Browser");
		{
			ImGui::Checkbox("show", &show);

			std::string valid_types;
			//valid_types = "xml";
			valid_types = "*.*";
			//valid_types = ".xml";
			
			std::string nameProposal = "nameProposal";
			std::string text = "Browse your files";

			mode = ofxImGuiSurfing::ImGuiFileBrowser::DialogMode::OPEN;
			//mode = ofxImGuiSurfing::ImGuiFileBrowser::DialogMode::SAVE;
			//mode = ofxImGuiSurfing::ImGuiFileBrowser::DialogMode::SELECT;

			bool b = getFileDialog(fileBrowser, &show, text, mode, valid_types);
			if (b) {
				strPath = fileBrowser.selected_fn;
				strFileName = fileBrowser.selected_path;
			}
		}
		ImGui::End();
	}
	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	show = !show;
}

// https://github.com/d3cod3/ofxVisualProgramming/blob/master/src/objects/data/FileToData.cpp
//    // file dialog
//    if(ImGuiEx::getFileDialog(fileDialog, openFileFlag, "Open a previously saved Mosaic data file", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ".txt", "", scaleFactor)){
//        ofLog(OF_LOG_NOTICE,"START IMPORTING DATA");
//        ofFile file (fileDialog.selected_path);
//        tmpFileName = file.getFileName();
//        filepath = file.getAbsolutePath();
//        loadDataFile(filepath);
//    }

//if (ofxImGuiSurfing::drawGui_FileDialog()) 
//{
//	ofLogWarning(__FUNCTION__) << "filePath     : " << ofxImGuiSurfing::filePath;
//	ofLogWarning(__FUNCTION__) << "filePathName : " << ofxImGuiSurfing::filePathName;
//	strPath = filePath;
//	strPathName = filePathName;
//}