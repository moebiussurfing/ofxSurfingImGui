#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(-1920, 25);

	guiManager.setImGuiAutodraw(true);
	guiManager.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Panels", &bOpen0, window_flags);
		{
			ofxImGuiSurfing::ToggleRoundedButton("Show 1", &bOpen1);
			//ofxImGuiSurfing::ToggleRoundedButton("Show 2", &bOpen2);

			ImGui::Dummy(ImVec2(0, 10)); // spacing


		}
		ImGui::End();

		//-

		drawWidgets();
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	if (!initialized) {
		initialized = true;
	}

	//// Graph Editor
	//ImGui::Begin("Graph Editor", &bOpen0, ImGuiWindowFlags_None);
	//static GraphEditor::Options options;
	//static GraphEditorDelegate delegate;
	//static GraphEditor::ViewState viewState;
	//static GraphEditor::FitOnScreen fit = GraphEditor::Fit_None;
	//static bool showGraphEditor = true;
	//if (ImGui::CollapsingHeader("Graph Editor"))
	//{
	//	ImGui::Checkbox("Show GraphEditor", &showGraphEditor);
	//	GraphEditor::EditOptions(options);
	//}
	//ImGui::End();

	//ImGui::Begin("ImGuizmo/GraphEditor");
	//{
	//	if (showGraphEditor)
	//	{
	//		ImGui::Begin("Graph Editor", NULL, 0);
	//	
	//		if (ImGui::Button("Fit all nodes"))
	//		{
	//			fit = GraphEditor::Fit_AllNodes;
	//		}
	//		ImGui::SameLine();
	//		if (ImGui::Button("Fit selected nodes"))
	//		{
	//			fit = GraphEditor::Fit_SelectedNodes;
	//		}
	//		GraphEditor::Show(delegate, options, viewState, true, &fit);

	//		ImGui::End();
	//	}
	//}
	//ImGui::End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key = ' ') {
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
}