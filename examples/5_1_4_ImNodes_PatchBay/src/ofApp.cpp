#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetWindowPosition(-1920, 25);
	
	setupParams();

	guiManager.setImGuiAutodraw(true);
	guiManager.setup();

	ImNodes::CreateContext();
}

//--------------------------------------------------------------
void ofApp::update() {
	patchbay.update();

	guiInput.setPosition(10, 10);
	guiOutput.setPosition(ofGetWidth() - 200 - 10, 10);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawScene();

	guiManager.begin(); // global begin
	{
		drawWidgets();

		//-
		
		//ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		//if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		//ImGui::Begin("Panels", &bOpen0, window_flags);
		//{
		//	ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
		//}
		//ImGui::End();
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	if (!initialized) {
		initialized = true;
		{
			ImNodes::GetIO().LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
			ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);
			editor.load();
		}
	}

	editor.show();
}

//--------------------------------------------------------------
void ofApp::exit() {
	//example::NodeEditorShutdown();
	{
		ImNodes::PopAttributeFlag();
		editor.save();

		ImNodes::DestroyContext();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = 'a') {
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

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
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

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


//--------------------------------------------------------------
void ofApp::setupParams()
{
	// input params (controllers)
	gInput.add(pi1);
	gInput.add(pi2);
	gInput.add(pi3);
	gInput.add(pi4);

	// output params (targets)
	gOutput.add(po1);
	gOutput.add(po2);
	gOutput.add(po3);
	gOutput.add(po4);

	//-

	// define inputs
	patchbay.addParameter(pi1);
	patchbay.addParameter(pi2);
	patchbay.addParameter(pi3);
	patchbay.addParameter(pi4);
	patchbay.setupParameters();

	//-

	// define and name outputs
	patchbay.registerControllable1f("po1", [&](float value) {
		po1.set(value);
	});
	patchbay.registerControllable1f("po2", [&](float value) {
		po2.set(value);
	});
	patchbay.registerControllable1f("po3", [&](float value) {
		po3.set(value);
	});
	patchbay.registerControllable1f("po4", [&](float value) {
		po4.set(value);
	});

	//-
	
	patchbay.disconnectAll();

	// connect
	patchbay.connect1f("param-1", "po1");
	patchbay.connect1f("param-2", "po2");
	patchbay.connect1f("param-3", "po3");
	patchbay.connect1f("param-4", "po4");

	str2 = "";
	str2 += "1 -> 1 \n";
	str2 += "2 -> 2 \n";
	str2 += "3 -> 3 \n";
	str2 += "4 -> 4";

	//-

	// gui
	guiInput.setup();
	guiInput.add(gInput);
	guiOutput.setup();
	guiOutput.add(gOutput);

	rect = ofRectangle(500, 500, 100, 100);
}

//--------------------------------------------------------------
void ofApp::drawScene() 
{
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2 * po1, ofGetHeight() / 2 * po2);
	scale = po3;
	ofBackground(255 * po4);
	ofSetColor(color);
	ofDrawRectangle(rect.x - scale * rect.width / 2, rect.y - scale * rect.height, scale*rect.width, scale*rect.height);
	ofPopMatrix();

	// help
	string str1 = "PATCH BAY";
	ofDrawBitmapStringHighlight(str1, 20, ofGetHeight() / 2);

	// patching preset
	ofDrawBitmapStringHighlight(str2, ofGetWidth() - 70, ofGetHeight() / 2);

	guiInput.draw();
	guiOutput.draw();
}