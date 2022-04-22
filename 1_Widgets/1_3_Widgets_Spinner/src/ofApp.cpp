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

	// customize font
	std::string path = "assets/fonts/telegrama_render.otf"; // assets folder
	ofxImGuiSurfing::setDefaultFont(gui, path, 12);

	//-

	// theme
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
}

//--------------------------------------------------------------
void ofApp::draw() {

	gui.begin();
	{
		ImGui::Begin("Progress Indicators");

		const ImU32 col1 = ImGui::GetColorU32(ImGuiCol_Text);
		const ImU32 col2 = ImGui::GetColorU32(ImGuiCol_Text);
		ImGui::Spinner("##spinner", 15, 6, col1);
		ImGui::BufferingBar("##buffer_bar", 0.7f, ImVec2(400, 6), col2, col1);
		
		ImGui::Dummy(ImVec2(0, 30));
		
		ImVec4* colors = ImGui::GetStyle().Colors;
		ImVec4 col3 = colors[ImGuiCol_Text];
		ImVec4 col4 = colors[ImGuiCol_TextDisabled];
		ImGui::LoadingIndicatorCircle("loading", 40, col3, col4, 10, 5);
				ImGui::Spacing();

		//-

		// Progress bar
		static ofParameter<float>p{ "time", 0, 0, 1 };
		p = ofMap(ofGetFrameNum() % 60, 0, 60, 0, 1);
		ofxImGuiSurfing::AddProgressBar(p);
		//OFX_IM_PROGRESS_BAR_NO_TEXT:
		ofxImGuiSurfing::AddProgressBar(p, -1, true);
		//guiManager.Add(timer_Progress, OFX_IM_PROGRESS_BAR_NO_TEXT);//-> To use when using a guiManager

		ImGui::End();
	}
	gui.end();
}
