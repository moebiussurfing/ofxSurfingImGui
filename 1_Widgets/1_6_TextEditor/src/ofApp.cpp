#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(60);

	gui.setup();

	// style
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	ofxImGuiSurfing::setDefaultFont(gui, "assets/fonts/telegrama_render.otf", 16);

	textEditor.setup();
	textEditor.loadText(ofToDataPath("text1.txt", true));
}

//--------------------------------------------------------------
void ofApp::draw() {

	bMouseOverGui = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);

	gui.begin();
	{
		textEditor.draw();
	}
	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (bMouseOverGui) return; // skip when editing

	ofLogVerbose(__FUNCTION__) << key;
	switch (key)
	{
	case '1': {
		string path = ofToDataPath("text1.txt", true);
		textEditor.loadText(path);
		break;
	}
	case '2': {
		string path = ofToDataPath("text2.txt", true);
		textEditor.loadText(path);
		break;
	}
	case '3': {
		string str = "García Castellón pone la X de Kitchen a Fernández Díaz\n y tapona la investigación a Rajoy, \nla cúpula del PP y \nel CNI El juez \ndetermina que la decisión \nde espiar a Bárcenas con \nfondos reservados para evitar problemas judiciales \nal presidente y a Cospedal no \ntrascendió del Ministerio del Interior.\nEl cierre de la instrucción llega \ncuando Anticorrupción apunta al CNI en \nel episodio del 'falso cura\n' e investiga una segunda Kitchen \nen la cárcel";
		textEditor.setText(str);
		break;
	}
	}
}