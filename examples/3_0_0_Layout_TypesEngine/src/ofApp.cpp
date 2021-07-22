#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	//-

	// debug custom types
	bCustom1 = 1; // inmediate customized when populating
	bCustom2 = 1; // constant. pre configured to customize after (ie: inside a group)

	//-

	// debug ImGui flags
	int sz = (int)SurfingImGuiTypesGroups::OFX_IM_GROUP_NUM_TYPES;
	typeFlags.set("typeFlags", 1, 0, 4);
	typeGroups.set("typeGroups", 0, 0, sz - 1);

	//-

	// prepare parameters

	params1.setName("paramsGroup1");
	params2.setName("paramsGroup2");
	params3.setName("paramsGroup3");

	bEnable.set("Enable", false);
	shapeType.set("shapeType", 0, -50, 50);

	params1.add(lineWidth1.set("lineWidth1", 0.5, 0, 1));
	params1.add(separation1.set("separation1", 50, 1, 100));
	params1.add(speed1.set("speed1", 0.5, 0, 1));
	params1.add(size1.set("size1", 100, 0, 100));
	params1.add(amount1.set("amount1", 10, 0, 25));

	params2.add(separation2min.set("separation2min", 25.f, 1, 100));
	params2.add(separation2max.set("separation2max", 75.f, 1, 100));
	params2.add(speed2.set("speed2", 0.5, 0, 1));
	params2.add(lineWidth2.set("lineWidth2", 0.5, 0, 1));
	params2.add(bEnable);

	params3.add(bMode1.set("Mode1", false));
	params3.add(bMode2.set("Mode2", false));
	params3.add(bMode3.set("Mode3", false));
	params3.add(bMode4.set("Mode4", false));
	params3.add(bModeA.set("ModeA", false));
	params3.add(bModeB.set("ModeB", false));
	params3.add(bModeC.set("ModeC", false));
	params3.add(bModeD.set("ModeD", false));
	params3.add(bPrevious.set("<", false));
	params3.add(bNext.set(">", false));
	params3.add(shapeType3.set("shapeType3", 0, -50, 50));
	params3.add(size3.set("size3", 100, 0, 100));
	params3.add(amount3.set("amount3", 10, 0, 25));
	params3.add(bEnable);

	params2.add(params3);
	params1.add(params2);

	//--

	//guiManager.setAutoSaveSettings(true); // -> enables stor/recall some settings from previous app session
	guiManager.setImGuiAutodraw(true);
	guiManager.setup(); // this instantiates and configures ofxImGui inside the class object.
	//guiManager.bAutoResize = false;

	//-

	// -> not checked on runtime! ONLY ON SETUP
	if (bCustom2) {
		SetupStyles();
	}
	else {
		ClearStyles();
	}
}

//--------------------------------------------------------------
void ofApp::SetupStyles() {

	guiManager.clear(); // TODO: -> call from beginWindow/group

	// two widgets same line
	guiManager.AddStyle(bMode1, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 2);
	guiManager.AddStyle(bMode2, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, false, 2);
	// two widgets same line
	guiManager.AddStyle(bMode3, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 2);
	guiManager.AddStyle(bMode4, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, false, 2, 10);

	guiManager.AddStyle(bModeA, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1);
	guiManager.AddStyle(bModeB, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1);
	guiManager.AddStyle(bModeC, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1);
	guiManager.AddStyle(bModeD, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1, 10);

	// two widgets same line big
	guiManager.AddStyle(bPrevious, SurfingImGuiTypes::OFX_IM_BUTTON_BIG, true, 2);
	guiManager.AddStyle(bNext, SurfingImGuiTypes::OFX_IM_BUTTON_BIG, false, 2, 10);

	guiManager.AddStyle(shapeType3, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(size3, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(amount3, SurfingImGuiTypes::OFX_IM_DRAG, false, 2, 10);

	// more widgets
	guiManager.AddStyle(lineWidth2, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(speed2, SurfingImGuiTypes::OFX_IM_DRAG);
}

//--------------------------------------------------------------
void ofApp::ClearStyles() {
	guiManager.clear(); // TODO: -> call from beginWindow/group
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// The group of parameters will be customized tree/folder types
	// Notice that will be applied to all the nested groups inside this parent/root ofParameterGroup
	flags_typeFlags = ImGuiTreeNodeFlags_None;
	if (typeFlags == 0) { flagInfo = "ImGuiTreeNodeFlags_None"; }
	if (typeFlags == 1) { flagInfo = "ImGuiTreeNodeFlags_DefaultOpen"; flags_typeFlags |= ImGuiTreeNodeFlags_DefaultOpen; } // to start closed
	if (typeFlags == 2) { flagInfo = "ImGuiTreeNodeFlags_Framed"; flags_typeFlags |= ImGuiTreeNodeFlags_Framed; } // to draw dark tittle bar
	if (typeFlags == 3) { flagInfo = "ImGuiTreeNodeFlags_Bullet"; flags_typeFlags |= ImGuiTreeNodeFlags_Bullet; } // bullet mark
	if (typeFlags == 4) { flagInfo = "ImGuiTreeNodeFlags_NoTreePushOnOpen"; flags_typeFlags |= ImGuiTreeNodeFlags_NoTreePushOnOpen; } // no push

	//-

	guiManager.begin();
	{
		drawWindow();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawWindow() 
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	//-

	guiManager.beginWindow();
	{
		//ImGui::Text("DEBUG STYLES TYPES");

		////ImGui::Dummy(ImVec2(0, 10)); // spacing
		////ToggleRoundedButton("bCustom1", &bCustom1);
		////if (bCustom1) ImGui::TextWrapped("Customized style for some ofParams Widgets");
		////else ImGui::TextWrapped("Default Style for ofParams Widgets");

		//ImGui::Dummy(ImVec2(0, 5)); // spacing
		//ImGui::Separator();
		//ImGui::Dummy(ImVec2(0, 5)); // spacing

		//-

		// readed on setup only, cant be updated on runtime
		if (ToggleRoundedButton("bCustom2", &bCustom2))
		{
			if (bCustom2) {
				SetupStyles();
			}
			else {
				ClearStyles();
			}
		}
		if (bCustom2) ImGui::TextWrapped("Customized Style for the Group.");
		else ImGui::TextWrapped("Default Style for the Group.");

		//-

		//ImGui::Dummy(ImVec2(0, 5)); // spacing
		ofxImGuiSurfing::AddSpaceY(5); // same than above line
		ImGui::Separator();
		ofxImGuiSurfing::AddSpaceY(5);

		ImGui::TextWrapped("Customize Styles for Groups/Trees:");
		ofxImGuiSurfing::AddSpaceY(5);

		// To debug ImGui flags when rendering groups
		{
			// test customize group/window folders and flags
			ofxImGuiSurfing::AddParameter(typeFlags);
			ImGui::Text(flagInfo.c_str());

			ofxImGuiSurfing::AddParameter(typeGroups);

			string groupInfo;
			if (typeGroups == 0) groupInfo = "OFX_IM_GROUP_DEFAULT";
			else if (typeGroups == 1) groupInfo = "OFX_IM_GROUP_TREE_EX";
			else if (typeGroups == 2) groupInfo = "OFX_IM_GROUP_TREE";
			else if (typeGroups == 3) groupInfo = "OFX_IM_GROUP_COLLAPSED";
			else if (typeGroups == 4) groupInfo = "OFX_IM_GROUP_SCROLLABLE";
			else if (typeGroups == 5) groupInfo = "OFX_IM_GROUP_ONLY_FIRST_HEADER";
			else if (typeGroups == 6) groupInfo = "OFX_IM_GROUP_HIDDE_ALL_HEADERS";

			ImGui::Text(groupInfo.c_str());
			ImGui::TextWrapped("Custom Group/Tree Styles");
		}

		//-

		ofxImGuiSurfing::AddSpaceY(10);
		//AddToggleRoundedButton(bEnable, ImVec2(50, 30));

		//-

		// render group
		guiManager.AddGroup(params1, flags_typeFlags, SurfingImGuiTypesGroups(typeGroups.get()));
		//guiManager.AddGroup(params3, flags_typeFlags, SurfingImGuiTypesGroups(typeGroups.get()));
	}
	guiManager.endWindow();
}