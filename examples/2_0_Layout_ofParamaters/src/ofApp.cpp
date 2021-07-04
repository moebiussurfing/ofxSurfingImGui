#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	guiManager.setImGuiAutodraw(true); // -> required when only one single ImGui instance is instantiated on all the oF project.
	guiManager.setup();
	guiManager.bAutoResize = false;

	int sz = (int)SurfingTypesGroups::IM_GUI_GROUP_AMOUNT - 1;
	typeGroups.set("typeGroups", 0, 0, sz);
	typeFlags.set("typeFlags", 1, 0, 4);

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
void ofApp::draw()
{
	guiManager.begin();
	{
		//TODO:
		//names engine
		//ofxImGuiSurfing::resetNames();
		//ofxImGuiSurfing::windowOpen.resetNames();

		//--

		static bool bOpen0 = true;
		static bool bOpen1 = true;
		static bool bAutoResize = true;

		//--

		{
			ImGuiWindowFlags window_flags;
			window_flags = ImGuiWindowFlags_None;
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Show Windows", &bOpen0, window_flags);
			{
				ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);

				ImGui::Dummy(ImVec2(0, 10)); // spacing

				//-

				// test customize group/window folders and flags
				ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);
				ofxImGuiSurfing::AddParameter(typeFlags);
				ImGui::Text(flagInfo.c_str());

				ofxImGuiSurfing::AddParameter(typeGroups);
				string groupInfo;
				if (typeGroups == 0) groupInfo = "IM_GUI_GROUP_DEFAULT";
				else if (typeGroups == 1) groupInfo = "IM_GUI_GROUP_TREE_EX";
				else if (typeGroups == 2) groupInfo = "IM_GUI_GROUP_TREE";
				else if (typeGroups == 3) groupInfo = "IM_GUI_GROUP_COLLAPSED";
				else if (typeGroups == 4) groupInfo = "IM_GUI_GROUP_SCROLLABLE";
				else if (typeGroups == 5) groupInfo = "IM_GUI_GROUP_ONLY_FIRST_HEADER";
				else if (typeGroups == 6) groupInfo = "IM_GUI_GROUP_HIDDE_ALL_HEADERS";
				ImGui::Text(groupInfo.c_str());
				
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
						if (guiManager.bExtra) guiManager.drawAdvancedSubPanel();

						ImGui::Unindent();
					}
				}
			}
			ImGui::End();
		}

		//--

		if (bOpen1)
		{
			ImGuiWindowFlags window_flags;
			window_flags = ImGuiWindowFlags_None;
			if (bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			guiManager.beginWindow("Window 1", &bOpen1, window_flags);
			{
				drawWidgets();
			}
			guiManager.endWindow();

			//-

			//// an snapped window
			//ofxImGuiSurfing::Begin("Window 1");
			//{
			//	drawWidgets();
			//}
			//ofxImGuiSurfing::End();
		}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawWidgets() {

	// A group of parameters with customized tree/folder type
	// will be applied to all nested groups inside this parent group
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	if (typeFlags == 0) { flagInfo = "ImGuiTreeNodeFlags_None"; }
	if (typeFlags == 1) { flagInfo = "ImGuiTreeNodeFlags_DefaultOpen"; flags |= ImGuiTreeNodeFlags_DefaultOpen; } // to start closed
	if (typeFlags == 2) { flagInfo = "ImGuiTreeNodeFlags_Framed"; flags |= ImGuiTreeNodeFlags_Framed; } // to draw dark tittle bar
	if (typeFlags == 3) { flagInfo = "ImGuiTreeNodeFlags_Bullet"; flags |= ImGuiTreeNodeFlags_Bullet; } // bullet mark
	if (typeFlags == 4) { flagInfo = "ImGuiTreeNodeFlags_NoTreePushOnOpen"; flags |= ImGuiTreeNodeFlags_NoTreePushOnOpen; } // no push

	ofxImGuiSurfing::AddGroup(params1, flags, SurfingTypesGroups(typeGroups.get()));
}
