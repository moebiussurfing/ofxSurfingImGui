#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);

	devmidiInit();
	//midiInit()

	val = new float();

	gui.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	devmidiUpdate();
}

//--------------------------------------------------------------
void ofApp::exit() {
	devmidiTerm();
}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.begin();

	ImGui::Text("Hello");
	ImGui::SliderFloat("Float", &floatValue, 0.0f, 1.0f);
	
	twisterSliderFloat("test", 20, val);

	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	ofLogVerbose(__FUNCTION__) << key;
	switch (key)
	{
	case 's':
	{
		break;
	}
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	ofLogVerbose(__FUNCTION__) << key;

}


void ofApp::mouseScrolled(float x, float y)
{
	ofLogVerbose(__FUNCTION__) << "x: " << x << " y: " << y;
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
