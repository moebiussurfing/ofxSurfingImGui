#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetWindowPosition(-1920, 25);

	guiManager.setImGuiAutodraw(true);
	guiManager.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		if (bOpen0) {
			ImGui::Begin("Panels", &bOpen0, window_flags);
			{
				ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
				ofxImGuiSurfing::ToggleRoundedButton("Show 2", &bOpen2);

				ImGui::Dummy(ImVec2(0, 10)); // spacing
			}
			ImGui::End();
		}

		//-

		if (bOpen1) drawWidgets();
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
void ofApp::exit() {
	//// simple-example
	//ed::DestroyEditor(g_Context);
	
	// basic-interaction-example
	example.Application_Finalize();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = ' ') {
	}
}