#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	guiManager.setImGuiAutodraw(true); // -> required when only one single ImGui instance is instantiated on all the oF project.
	guiManager.setup(); // ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).

	// ofParameters
	params.setName("paramsGroup");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params.add(bMode1.set("Mode1", false));
	params.add(bMode2.set("Mode2", false));
	params.add(bMode3.set("Mode3", false));
	params.add(bMode4.set("Mode4", false));
	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable.set("Enable", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params2.add(params3);
	params.add(params2);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		static bool bOpen0 = true;
		static bool bOpen1 = true;
		ImGuiWindowFlags window_flags;

		//---------

		window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("Show Windows", &bOpen0, window_flags);
		{
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);

			//-

			// extra menu
			{
				ImGui::Dummy(ImVec2(0, 5)); // spacing

				ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bExtra);
				if (guiManager.bExtra)
				{
					ImGui::Indent();

					ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
					if (guiManager.bExtra) guiManager.drawAdvancedSubPanel();

					ImGui::Unindent();
				}
			}
		}
		ImGui::End();

		//---------

		if (bOpen1)//should work standalone
		{
			window_flags = ImGuiWindowFlags_None;
			//window_flags |= ImGuiWindowFlags_; 

			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			guiManager.beginWindow("Window 1", &bOpen1, window_flags);
			{
				drawWidgets();
			}
			guiManager.endWindow();
		}
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::drawWidgets() {
	// A group of parameters with customized tree/folder type
	// will be applied to all nested groups inside this parent group

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
	flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed

	ofxImGuiSurfing::AddGroup(params, flags);

}