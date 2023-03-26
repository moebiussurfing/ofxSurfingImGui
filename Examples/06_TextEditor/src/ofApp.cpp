#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);

	ofxImGuiSurfing::SurfSetMyMonitor(1);

	ui.setup();

	textEditor.setup("myEditor");
	//load("SurfingTextEditor_Settings.json");
	textEditor.loadText(ofToDataPath("SurfingTextEditor_Settings.json", true));
	textEditor.setCustomFonts(ui.getFontsPtr(), ui.getFontsNames());

	// custom keywords
	textEditor.addKeyword("CPP");
	textEditor.addKeyword("C++");
	textEditor.addKeyword("the");
	textEditor.addKeyword("a");
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
	case '1': load("SurfingTextEditor_Settings.json"); break;
	case '2': load("files/text1.txt"); break;
	case '3': load("files/text2.txt"); break;
	case '4': {
		string str = "Garc�a Castell�n pone la X de Kitchen a Fern�ndez D�az\n y tapona la investigaci�n a Rajoy, \nla c�pula del PP y \nel CNI El juez \ndetermina que la decisi�n \nde espiar a B�rcenas con \nfondos reservados para evitar problemas judiciales \nal presidente y a Cospedal no \ntrascendi� del Ministerio del Interior.\nEl cierre de la instrucci�n llega \ncuando Anticorrupci�n apunta al CNI en \nel episodio del 'falso cura\n' e investiga una segunda Kitchen \nen la c�rcel";
		textEditor.setText(str);
		break;
	}
	}
}

//--------------------------------------------------------------
void ofApp::load(string _path) {
	string path = ofToDataPath(_path, true);
	textEditor.loadText(path);
}
