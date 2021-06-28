#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	setup_ImGui();
}

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	ImGuiConfigFlags flags = ImGuiConfigFlags_DockingEnable;
	bool bRestore = true;
	bool bMouse = false;
	bool bAutoDraw = true;
	// NOTE: it seems that must be false when multiple ImGui instances created!

	gui.setup(nullptr, bAutoDraw, flags, bRestore, bMouse);

	//-

	// theme
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing();
}

//--------------------------------------------------------------
void ofApp::draw() {

	gui.begin();
	{
		ImGui::Begin("Progress Indicators");

		const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
		const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

		ImGui::Spinner("##spinner", 15, 6, col);
		ImGui::BufferingBar("##buffer_bar", 0.7f, ImVec2(400, 6), bg, col);

		ImGui::Dummy(ImVec2(0, 30));
		ImGui::LoadingIndicatorCircle("loading", 40, ImVec4(1, 0, 0, 1), ImVec4(0, 1, 0, 1), 10, 5);

		//ImGui::Spinner2("label", 40, 5, col);

		ImGui::End();
	}
	gui.end();
}
