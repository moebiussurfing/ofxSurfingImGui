#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetWindowPosition(-1920, 25);

	ofxSurfingHelpers::setThemeDark_ofxGui();

	guiManager.setImGuiAutodraw(true);
	guiManager.setup();

	setupPatches();

	listener_NewLink = example.bNewLink.newListener([this](bool b) {
		if (b) {
			b = false;
			string msg = "New Link \t " + ofToString(example.lastPinFrom) + " > " + ofToString(example.lastPinTo);

			int iController = -1;
			int iTarget = -1;

			// workaround hardcoded for 4 to 4 elements
			if (example.lastPinFrom >= 2 && example.lastPinFrom <= 5)
			{
				iController = example.lastPinFrom - 2;
			}
			if (example.lastPinTo >= 7 && example.lastPinTo <= 10)
			{
				iTarget = example.lastPinTo - 7;
			}

			if (iController != -1 && iTarget != -1) {
				string msg = "New Link \t " + ofToString(iController) + " > " + ofToString(iTarget);

				patchbay.link(iController, iTarget);

				ImLog.AddText(msg);
				ofLogNotice(__FUNCTION__) << msg;
			}
			else {
				ofLogError(__FUNCTION__) << "Out of range. Link invalid";
			}
		}
	});

	listener_RemovedLink = example.bRemovedLink.newListener([this](bool b) {
		if (b) {
			b = false;
			string msg = "Removed Link \t " + ofToString(example.lastPinFrom) + " > " + ofToString(example.lastPinTo);

			int iController = -1;
			int iTarget = -1;

			// workaround hardcoded for 4 to 4 elements
			if (example.lastPinFrom >= 2 && example.lastPinFrom <= 5)
			{
				iController = example.lastPinFrom - 2;
			}
			if (example.lastPinTo >= 7 && example.lastPinTo <= 10)
			{
				iTarget = example.lastPinTo - 7;
			}

			if (iController != -1 && iTarget != -1) {
				string msg = "Removed Link \t " + ofToString(iController) + " > " + ofToString(iTarget);

				patchbay.unlink(iController, iTarget);

				ImLog.AddText(msg);
				ofLogNotice(__FUNCTION__) << msg;
			}
			else {
				ofLogError(__FUNCTION__) << "Out of range. Link invalid";
			}
		}
	});

	ImLog.SetLogSize(50);

	ofAddListener(params.parameterChangedE(), this, &ofApp::Changed_Params); // setup()

}

//--------------------------------------------------------------
void ofApp::update() {
	updatePatches();
	if (bGenerators) updateGenerators();
}

//--------------------------------------------------------------
void ofApp::updatePatches() {
	patchbay.update();

	guiControllers.setPosition(10, 10);
	guiTargets.setPosition(ofGetWidth() - 200 - 10, 10);
}

//--------------------------------------------------------------
void ofApp::updateGenerators() {
	pController0 = ofxSurfingHelpers::Tick(2.0f);
	pController1 = ofxSurfingHelpers::Bounce(3.0f);
	pController2 = ofxSurfingHelpers::Noise(ofPoint(2, -1));
	pController3 = ofxSurfingHelpers::Bounce(0.5f);
	//pController3 = ofxSurfingHelpers::Noise(ofPoint(-0.5, -0.5));
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawPatches();

	guiManager.begin();
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (bOpen0) {
			ImGui::Begin("Panels", &bOpen0, window_flags);
			{
				ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
				ofxImGuiSurfing::ToggleRoundedButton("Show 2", &bOpen2);

				//ImGui::Dummy(ImVec2(0, 2)); // spacing
				if (ImGui::Button("Disconnect All")) {
					patchbay.disconnectAll();
				}
				ofxImGuiSurfing::ToggleRoundedButton("Generators", &bGenerators);
				ofxImGuiSurfing::ToggleRoundedButton("Log", &bLog);
				
				ImGui::Dummy(ImVec2(0, 10)); // spacing
			}
			ImGui::End();
		}

		//-

		if (bOpen1) drawWidgets();

		if (bLog) {
			ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
			ImLog.ImGui("LOG", ImGuiWindowFlags_None, &bLog);
		}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	if (!initialized) {
		initialized = true;

		//// simple-example
		//g_Context = ed::CreateEditor();

		// basic-interaction-example
		example.Application_Initialize();
	}

	ImGui::Begin("thedmd/imgui-node-editor");
	{
		//// simple-example
		//{
		//	ed::SetCurrentEditor(g_Context);
		//	ed::Begin("My Editor");
		//	int uniqueId = 1;
		//	// Start drawing nodes.
		//	ed::BeginNode(uniqueId++);
		//	ImGui::Text("Node A");
		//	ed::BeginPin(uniqueId++, ed::PinKind::Input);
		//	ImGui::Text("-> In");
		//	ed::EndPin();
		//	ImGui::SameLine();
		//	ed::BeginPin(uniqueId++, ed::PinKind::Output);
		//	ImGui::Text("Out ->");
		//	ed::EndPin();
		//	ed::EndNode();
		//	ed::End();
		//}

		// basic-interaction-example
		example.Application_Frame();
	}
	ImGui::End();
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ofRemoveListener(params.parameterChangedE(), this, &ofApp::Changed_Params); // exit()

	//// simple-example
	//ed::DestroyEditor(g_Context);

	// basic-interaction-example
	example.Application_Finalize();
}

// callback for a parameter group  
//--------------------------------------------------------------
void ofApp::Changed_Params(ofAbstractParameter &e)
{
	string name = e.getName();
	ofLogNotice() << "Changed parameter named: " << name << " : with value " << e;

	string msg = ofToString(name) + " : " + ofToString(e);
	ImLog.AddText(msg);

	//if (name == SHOW_gui.getName())
	//{
	//}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = ' ') {}

	keyPressedPatches(key);
}

//--------------------------------------------------------------
void ofApp::setupPatches() {

	// controllers
	gControllers.add(pController0);
	gControllers.add(pController1);
	gControllers.add(pController2);
	gControllers.add(pController3);

	// targets
	gTargets.add(pTarget0);
	gTargets.add(pTarget1);
	gTargets.add(pTarget2);
	gTargets.add(pTarget3);

	// define controllers
	patchbay.addController(pController0);
	patchbay.addController(pController1);
	patchbay.addController(pController2);
	patchbay.addController(pController3);

	// define targets
	patchbay.addTarget(pTarget0);
	patchbay.addTarget(pTarget1);
	patchbay.addTarget(pTarget2);
	patchbay.addTarget(pTarget3);

	patchbay.setupParameters();

	//-

	if (0)
	{
		// connect
		patchbay.link(0, 0);

		patchbay.link(1, 1);
		patchbay.link(2, 2);
		patchbay.link(3, 3);

		str2 = "PRESET\n";
		str2 += "0 -> 0\n";
		str2 += "1 -> 1\n";
		str2 += "2 -> 2\n";
		str2 += "3 -> 3";
	}

	//-

	// gui
	guiControllers.setup();
	guiControllers.add(gControllers);
	guiTargets.setup();
	guiTargets.add(gTargets);

	rect = ofRectangle(0, 0, 100, 100);

	//-

	params.add(gControllers);
	//params.add(gTargets);
}

//--------------------------------------------------------------
void ofApp::drawPatches() {
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2 * pTarget0, ofGetHeight() / 2 * pTarget1);
	scale = pTarget2;
	ofBackground(32);
	ofSetColor(color.r, color.g, color.b, 255 * pTarget3);
	ofDrawRectangle(rect.x - scale * rect.width / 2, rect.y - scale * rect.height, scale*rect.width, scale*rect.height);
	ofPopMatrix();

	// help
	string str1 = "";
	str1 += "RETURN       : PRINT CONNECTIONS\n";
	str1 += "BACKSPACE    : DISCONNECT ALL\n";
	str1 += "KEYS 1-2-3-4 : PATCHBAY LINKS PRESETS";
	ofDrawBitmapStringHighlight(str1, 20, ofGetHeight() - 100);

	// patching preset
	ofDrawBitmapStringHighlight(str2, ofGetWidth() - 70, ofGetHeight() - 100);

	guiControllers.draw();
	guiTargets.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressedPatches(int key) {

	// set configurations

	if (key == OF_KEY_RETURN) patchbay.printConnections();

	if (key == OF_KEY_BACKSPACE)
	{
		patchbay.disconnectAll();
		str2 = "PRESET\n";
		str2 += "0    0\n";
		str2 += "1    1\n";
		str2 += "2    2\n";
		str2 += "3    3";
	}

	if (key == '1')
	{
		patchbay.disconnectAll();
		patchbay.link(0, 0);
		patchbay.link(1, 1);
		patchbay.link(2, 2);
		patchbay.link(3, 3);

		str2 = "PRESET\n";
		str2 += "0 -> 0\n";
		str2 += "1 -> 1\n";
		str2 += "2 -> 2\n";
		str2 += "3 -> 3";
	}
	if (key == '2')
	{
		patchbay.disconnectAll();
		patchbay.link(0, 3);
		patchbay.link(1, 2);
		patchbay.link(2, 1);
		patchbay.link(3, 0);

		str2 = "PRESET\n";
		str2 += "0 -> 3\n";
		str2 += "1 -> 2\n";
		str2 += "2 -> 1\n";
		str2 += "3 -> 0";
	}
	if (key == '3')
	{
		patchbay.disconnectAll();
		patchbay.link(0, 3);
		patchbay.link(1, 1);
		patchbay.link(2, 2);
		patchbay.link(3, 0);

		str2 = "PRESET\n";
		str2 += "0 -> 3\n";
		str2 += "1 -> 1\n";
		str2 += "2 -> 2\n";
		str2 += "3 -> 0";
	}
	if (key == '4')
	{
		patchbay.disconnectAll();
		patchbay.link(0, 2);
		patchbay.link(1, 3);
		patchbay.link(2, 0);
		patchbay.link(3, 1);

		str2 = "PRESET\n";
		str2 += "0 -> 2\n";
		str2 += "1 -> 3\n";
		str2 += "2 -> 0\n";
		str2 += "3 -> 1";
	}
}