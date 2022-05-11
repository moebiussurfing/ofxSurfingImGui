#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetWindowPosition(1920, 25);

	guiManager.setImGuiAutodraw(true); // -> required when only one single ImGui instance is instantiated on all the oF project.
	guiManager.setup();
	guiManager.bAutoResize = false;

	//-

	// debug ImGui flags
	{
		int sz = SurfingImGuiTypesGroups::OFX_IM_GROUP_NUM_TYPES - 1;
		typeGroups.set("typeGroups", 0, 0, sz);
		typeFlags.set("typeFlags", 1, 0, 4);
	}

	//-

	// ofParameters

	// groups
	params1.setName("paramsGroup1");// main
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested

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

	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params2.add(bMode1);
	params2.add(bMode2);
	params2.add(bMode3);
	params2.add(lineWidth);
	params2.add(separation);
	params2.add(shapeType);

	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params3.add(bMode1);
	params3.add(bMode2);
	params2.add(bMode3);
	params3.add(lineWidth);
	params3.add(separation);
	params3.add(shapeType);
	params3.add(bNext);
	params3.add(separation);
	params3.add(size);

	params2.add(params3);
	params1.add(params2);
}

//--------------------------------------------------------------
void ofApp::drawMainWindow()
{
	ImGuiWindowFlags window_flags;
	window_flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	{
		// This was previously when using ofxImGui original helpers:
		//auto mainSettings = ofxImGui::Settings();
		//if (ofxImGui::BeginWindow("Show Windows", mainSettings, false))
		//{
		//	//... ofParams widgets
		//}
		//ofxImGui::EndWindow(mainSettings);

		//-

		ImGui::Begin("Show Windows", &bOpen0, window_flags);
		{
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);

			ImGui::Dummy(ImVec2(0, 10)); // spacing

			//-

			// debug ImGui flags
			{
				// test customize group/window folders and flags
				ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);
				ofxImGuiSurfing::AddParameter(typeFlags);
				ImGui::Text(flagInfo.c_str());

				ofxImGuiSurfing::AddParameter(typeGroups);
				string groupInfo;
				groupInfo = ofxImGuiSurfing::getSurfingImGuiTypesGroupsName(typeGroups);
				ImGui::Text(groupInfo.c_str());
			}

			ofxImGuiSurfing::ToggleRoundedButton("AutoResize", &bAutoResize);

			//-

			// extra menu
			{
				ImGui::Dummy(ImVec2(0, 10)); // spacing

				ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bExtra);
				if (guiManager.bExtra)
				{
					ImGui::Indent();

					//..more widgets
					ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAdvanced);
					if (guiManager.bExtra) guiManager.drawAdvanced();

					ImGui::Unindent();
				}
			}
		}
		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		drawMainWindow();

		//--

		if (bOpen1)
		{
			ImGuiWindowFlags window_flags;
			window_flags = ImGuiWindowFlags_None;
			if (bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			// window
			guiManager.beginWindow("Window 1", &bOpen1, window_flags);
			{
				drawWidgets();
			}
			guiManager.endWindow();

			//-

			//// This was the API using ofxImGui original helpers
			//{
			//	auto mainSettings = ofxImGui::Settings();
			//	if (ofxImGui::BeginWindow("Helpers", mainSettings, false))
			//	{
			//		ofxImGui::AddGroup(params1, mainSettings);
			//	}
			//	ofxImGui::EndWindow(mainSettings);
			//}
		}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	// some params before and out of the group
	ofxImGuiSurfing::AddParameter(bMode3);
	ofxImGuiSurfing::AddParameter(lineWidth);
	ImGui::Dummy(ImVec2(0, 10)); // spacing

	//--

	// Simple default usage:
	//guiManager.AddGroup(params1);

	//// Customized hardcoded usage:
	//guiManager.AddGroup(params1, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_TREE_EX);

	//-

	// debug ImGui flags
	{
		// A group of parameters with customized tree/folder types
		// will be applied to all the nested groups inside this parent/root ofParameterGroup
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
		if (typeFlags == 0) { flagInfo = "ImGuiTreeNodeFlags_None"; }
		if (typeFlags == 1) { flagInfo = "ImGuiTreeNodeFlags_DefaultOpen"; flags |= ImGuiTreeNodeFlags_DefaultOpen; } // to start closed
		if (typeFlags == 2) { flagInfo = "ImGuiTreeNodeFlags_Framed"; flags |= ImGuiTreeNodeFlags_Framed; } // to draw dark tittle bar
		if (typeFlags == 3) { flagInfo = "ImGuiTreeNodeFlags_Bullet"; flags |= ImGuiTreeNodeFlags_Bullet; } // bullet mark
		if (typeFlags == 4) { flagInfo = "ImGuiTreeNodeFlags_NoTreePushOnOpen"; flags |= ImGuiTreeNodeFlags_NoTreePushOnOpen; } // no push

		guiManager.AddGroup(params1, flags, SurfingImGuiTypesGroups(typeGroups.get()));
	}

	//--

	// some params after and out of the group
	ImGui::Dummy(ImVec2(0, 10)); // spacing
	ofxImGuiSurfing::AddParameter(bMode3);
	ofxImGuiSurfing::AddParameter(lineWidth);
}
