#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(1);

	ui.setup();

	//--

	e.setPathGlobal(ui.getPath());
	e.setUiPtr(&ui);
	e.setup();

	//TODO: not working
	//ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingBlue();
	//e.loadThemeHardcoded(5);
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
}