#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"	
#include "ofxSurfing_ofxGui.h"	

#include "basic-interaction-example.h" // -> here is the patching code

#include "ofxPatchbay.h"
#include "ofxGui.h"
#include "ofxMyUtilImGui.h"

/*

+	add plots
+	add pins during runtime

*/


class ofApp : public ofBaseApp {

public:
	ofxMyUtil::Im::ImGuiLogWindow ImLog;

public:
	void setup();
	void update();
	void updateGenerators();
	void draw();
	void exit();
	void keyPressed(int key);

	ofxSurfing_ImGui_Manager guiManager;
	
	Example example;

	void drawWidgets();

	bool bOpen0 = true;
	bool bLog= true;
	bool bOpen1 = true;
	bool bOpen2 = false;
	bool bGenerators = true;

	bool initialized = false;

	ofEventListener listener_NewLink;
	ofEventListener listener_RemovedLink;

	void Changed_Params(ofAbstractParameter &e);
	ofParameterGroup params{ "Params" };

	//-
	
	void setupPatches();
	void updatePatches();
	void drawPatches();
	void keyPressedPatches(int key);

	ofxPatchbay patchbay;

	// controllers
	ofParameter<float>pController0{ "pController0", 0, 0, 1 };
	ofParameter<float>pController1{ "pController1", 0, 0, 1 };
	ofParameter<float>pController2{ "pController2", 0, 0, 1 };
	ofParameter<float>pController3{ "pController3", 0, 0, 1 };

	// targets
	ofParameter<float>pTarget0{ "pTarget0", 0, 0, 1 };
	ofParameter<float>pTarget1{ "pTarget1", 0, 0, 1 };
	ofParameter<float>pTarget2{ "pTarget2", 0, 0, 1 };
	ofParameter<float>pTarget3{ "pTarget3", 0, 0, 1 };

	// gui
	ofxPanel guiControllers;
	ofxPanel guiTargets;
	ofParameterGroup gControllers{ "gControllers" };
	ofParameterGroup gTargets{ "gTargets" };

	string str2 = "";

	// scene
	ofRectangle rect;
	float scale;
	ofColor color = ofColor(255, 0, 0);


};
