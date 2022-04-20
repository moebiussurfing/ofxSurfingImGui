#pragma once

#include "ofMain.h"

#include "ofxSurfingConstants.h"

#include "ofxGui.h"

// more helpers to custpmize:
// https://github.com/openframeworks/openFrameworks/pull/6479
// https://github.com/openframeworks/openFrameworks/issues/6470

// snippets
//#include "ofxSurfing_ofxGui.h"
//ofxSurfingHelpers::setThemeDark_ofxGui();

//#define FONT_PATH_DEFAULT "assets/fonts/overpass-mono-bold.otf"
//#define FONT_SIZE_DEFAULT 9

#define FONT_PATH_DEFAULT "assets/fonts/telegrama_render.otf"
#define FONT_SIZE_DEFAULT 8

namespace ofxSurfingHelpers
{

	//--------------------------------------------------------------
	// My ofxGui Dark Theme
	//--------------------------------------------------------------

	//// legacy. Now default is the mini version.
	////--------------------------------------------------------------
	//inline void setThemeDark_ofxGui(std::string pathFont = FONT_PATH_DEFAULT, int size = FONT_SIZE_DEFAULT, bool bMini = false)
	//{
	//	//setThemeDarkMini_ofxGui();
	//	setThemeDark_ofxGui(FONT_PATH_DEFAULT, FONT_SIZE_DEFAULT, true);
	//}
	//--------------------------------------------------------------
	inline void setThemeDark_ofxGui(std::string pathFont = FONT_PATH_DEFAULT, int size = FONT_SIZE_DEFAULT, bool bMini = false)
	{
		if (bMini) {
			size = 7;
		}

		ofFile file(pathFont);
		if (file.exists())
		{
			ofxGuiSetFont(pathFont, size);
		}
		else {
			ofLogError(__FUNCTION__) << "file " << pathFont << " not found!";
		}

		//-

		//ofxGuiSetDefaultHeight(20);
		//ofxGuiSetBorderColor(32);
		//ofxGuiSetFillColor(ofColor(24));
		//ofxGuiSetTextColor(ofColor::white);
		//ofxGuiSetHeaderColor(ofColor(12));
		//ofxGuiSetBackgroundColor(ofColor::black);

		//-


		ofFloatColor cHead = ofFloatColor(0.05f, 0.05f, 0.05f, 0.90f);
		//ofFloatColor cBg = ofFloatColor(0.12f, 0.12f, 0.12f, 0.8f);
		ofFloatColor cBg = ofFloatColor(0.16f, 0.16f, 0.16f, 0.8f);
		ofFloatColor cBorder = ofFloatColor(0.10f, 0.10f, 0.10f, 0.7f);
		ofFloatColor cSlider = ofFloatColor(0.03f, 0.03f, 0.03f, 0.8f);
		ofFloatColor cText = ofFloatColor(0.76f, 0.76f, 0.76f, 0.94f);
		//ofFloatColor cBut = ofFloatColor(0.18f, 0.18f, 0.18f, 1.00f);

		ofxGuiSetHeaderColor(cHead);
		ofxGuiSetBackgroundColor(cBg);
		ofxGuiSetBorderColor(cBorder);
		ofxGuiSetFillColor(cSlider);
		ofxGuiSetTextColor(cText);

		// default
		//ofxGuiSetDefaultHeight(18);
		//ofxGuiSetTextPadding(4);

		if (bMini) {
			ofxGuiSetDefaultHeight(18);
			ofxGuiSetTextPadding(4);
			//ofxGuiSetDefaultHeight(17);
			//ofxGuiSetTextPadding(8);
		}
		else {
			ofxGuiSetDefaultHeight(21);
			ofxGuiSetTextPadding(14);
		}
	}

	//--------------------------------------------------------------
	inline void setThemeDarkMini_ofxGui() {
		setThemeDark_ofxGui(FONT_PATH_DEFAULT, FONT_SIZE_DEFAULT, true);
	}

}; // ofxSurfingHelpers


//--

// App code to live customize styles,
// but using master branch
//
//public:
//	ofxPanel gui2;
//	ofParameter<float> spacing = { "spacing", 1, 0, 100 };
//	ofParameter<float> spacingNext = { "spacing next", 3, 0, 300 };
//	ofParameter<float> childrenLeftIndent = { "children Left Indent", 4, 0, 200 };
//	ofParameter<float> childrenRightIndent = { "children Right Indent", 0, 0, 200 };
//	void spacingChanged(float&);
//	ofEventListeners listeners;
//
////--------------------------------------------------------------
//void ofApp::spacingChanged(float&) {
//	ofxGuiGroup::elementSpacing = spacing;
//	ofxGuiGroup::groupSpacing = spacingNext;
//	ofxGuiGroup::childrenLeftIndent = childrenLeftIndent;
//	ofxGuiGroup::childrenRightIndent = childrenRightIndent;
//	gui_App.sizeChangedCB();
//	//{
//	//	if (key == '1') {
//	//		auto & g = gui.getGroup("params");
//	//		if (g.isMinimized()) {
//	//			g.maximize();
//	//		}
//	//		else {
//	//			g.minimize();
//	//		}
//	//	}
//	//	else if (key == '2') {
//	//		auto & g = gui.getGroup("params");
//	//		if (g.isHeaderEnabled()) {
//	//			g.disableHeader();
//	//		}
//	//		else {
//	//			g.enableHeader();
//	//		}
//	//	}
//	//	else if (key == '3') {
//	//		if (gui.isMinimized()) {
//	//			gui.maximize();
//	//		}
//	//		else {
//	//			gui.minimize();
//	//		}
//	//	}
//	//	else if (key == '4') {
//	//		if (gui.isHeaderEnabled()) {
//	//			gui.disableHeader();
//	//		}
//	//		else {
//	//			gui.enableHeader();
//	//		}
//	//	}
//	//	else if (key == '5') {
//	//		auto & g = gui.getGroup("params1");
//	//		g.setup("params1");
//	//		if (g.isMinimized()) {
//	//			g.maximize();
//	//		}
//	//		else {
//	//			g.minimize();
//	//		}
//	//	}
//	//}
//}
//
// Setup
//gui2.setup();
//gui2.add(spacing);
//gui2.add(spacingNext);
//gui2.add(childrenLeftIndent);
//gui2.add(childrenRightIndent);
//listeners.push(spacing.newListener(this, &ofApp::spacingChanged));
//listeners.push(spacingNext.newListener(this, &ofApp::spacingChanged));
//listeners.push(childrenLeftIndent.newListener(this, &ofApp::spacingChanged));
//listeners.push(childrenRightIndent.newListener(this, &ofApp::spacingChanged));
