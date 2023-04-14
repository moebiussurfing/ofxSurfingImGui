#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(1);

	ui.setup();
	e.setUiPtr(&ui);

	// We can force load one of the bundled Themes:
	// Must be called after setup() 
	// to overwrite the default loaded theme:
	ImGui::StyleColorsLight();
	//ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingBlue();

	ofxSurfingHelpers::load(e.params);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		e.draw();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ofxSurfingHelpers::save(e.params);
}