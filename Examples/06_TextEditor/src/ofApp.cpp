#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);

	ui.setup();

	textEditor.setup("myEditor");

	textEditor.loadText(ofToDataPath("SurfingTextEditor_Settings.json", true));
	//textEditor.loadText(ofToDataPath("files/ofxSurfingTextSubtitle_Settings.json", true));
}

//--------------------------------------------------------------
void ofApp::draw() {

	ui.Begin();
	{
		if (ui.BeginWindow("ofApp")) {
			ui.Add(textEditor.bGui, OFX_IM_TOGGLE_ROUNDED);
			ui.EndWindow();
		}

		textEditor.draw();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (ui.isOverInputText()) return; // skip when editing

	ofLogNotice(__FUNCTION__) << key;

	switch (key)
	{
	case '1': {
		string path = ofToDataPath("files/ofxSurfingTextSubtitle_Settings.json", true);
		textEditor.loadText(path);
		break;
	}
	case '2': {
		string path = ofToDataPath("files/text1.txt", true);
		textEditor.loadText(path);
		break;
	}
	case '3': {
		string path = ofToDataPath("files/text2.txt", true);
		textEditor.loadText(path);
		break;
	}
	case '4': {
		string str = "Garc�a Castell�n pone la X de Kitchen a Fern�ndez D�az\n y tapona la investigaci�n a Rajoy, \nla c�pula del PP y \nel CNI El juez \ndetermina que la decisi�n \nde espiar a B�rcenas con \nfondos reservados para evitar problemas judiciales \nal presidente y a Cospedal no \ntrascendi� del Ministerio del Interior.\nEl cierre de la instrucci�n llega \ncuando Anticorrupci�n apunta al CNI en \nel episodio del 'falso cura\n' e investiga una segunda Kitchen \nen la c�rcel";
		textEditor.setText(str);
		break;
	}
	}
}