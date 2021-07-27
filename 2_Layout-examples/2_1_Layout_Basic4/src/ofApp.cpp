#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(1920, 20);

	guiManager.setImGuiAutodraw(true); // -> required when only one single ImGui instance is instantiated on all the oF project.
	guiManager.setup();

	//-

	// ofParameters
	params1.setName("paramsGroup1");// main
	params1.add(bMode1.set("Mode1", false));
	params1.add(bMode2.set("Mode2", false));
	params1.add(bMode3.set("Mode3", false));
	params1.add(bMode4.set("Mode4", false));
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));

	//--

	guiManager.addWindow((string)"myWindow0");
	guiManager.addWindow((string)"myWindow1");
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		drawMainWindow();

		//--

		float x = ofGetWindowPositionX();
		float y = ofGetWindowPositionY();
		float w = ofGetWindowWidth();
		float h = ofGetWindowHeight();
		ImVec4 vViewport(x, y, w, h);
		ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiCond_Once);

		if (!bInitiated)
		{
			bInitiated = true;
		}

		//-

		if (guiManager.beginWindow(0)) {
			ImGui::Text("Test guiManager.beginWindow(0)");
			//ImGui::SliderFloat(lineWidth.getName().c_str(), (float*)&lineWidth.get());
		}
		guiManager.endWindow();

		if (guiManager.beginWindow(1)) {
			ImGui::Text("Test guiManager.beginWindow(1)");
		}
		guiManager.endWindow();

		//-

		//	guiManager.beginWindow("Window 1", &bOpen1, window_flags);
		//	{
		//		drawWidgets();
		//	}
		//	guiManager.endWindow();
		//}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawMainWindow()
{
	ImGuiWindowFlags window_flags;
	window_flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	{
		ImGui::Begin("Show Windows", &bOpen0, window_flags);
		{
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);

			//ofxImGuiSurfing::ToggleRoundedButton(6&guiManager.getShow(0).get());

			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.getShow(0));
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.getShow(1));

			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);
		}
		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	//guiManager.AddGroup(params1);
}
