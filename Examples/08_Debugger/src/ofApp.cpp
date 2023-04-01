#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxImGuiSurfing::SurfSetMyMonitor(0);//optional. just to set window position 
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		d.draw();
	}
	ui.End();
}