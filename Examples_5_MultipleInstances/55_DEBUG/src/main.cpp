#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	float w = 1500;
	ofSetupOpenGL(w, w / (16 / 9.f), OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
