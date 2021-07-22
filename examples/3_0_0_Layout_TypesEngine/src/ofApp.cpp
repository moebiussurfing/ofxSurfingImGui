#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	//-

	// debug custom types
	bCustom = true;
	int sz = (int)SurfingImGuiTypesGroups::OFX_IM_GROUP_NUM_TYPES;
	typeFlags.set("typeFlags", 1, 0, 4);

	typeGroup1.set("typeGroup1", 0, 0, sz - 1);
	typeGroup2.set("typeGroup2", 0, 0, sz - 1);
	typeGroup3.set("typeGroup3", 0, 0, sz - 1);

	paramsSettings.setName("Settings");
	paramsSettings.add(typeFlags);
	paramsSettings.add(typeGroup1);
	paramsSettings.add(typeGroup2);
	paramsSettings.add(typeGroup3);

	//-

	// prepare parameters

	params1.setName("paramsGroup1");
	params2.setName("paramsGroup2");
	params3.setName("paramsGroup3");

	bEnable.set("Enable", false);
	shapeType.set("shapeType", 0, -50, 50);

	params1.add(line1.set("line1", 0.5, 0, 1));
	params1.add(separation1.set("separation1", 50, 1, 100));
	params1.add(speed1.set("speed1", 0.5, 0, 1));
	params1.add(size1.set("size1", 100, 0, 100));
	params1.add(amount1.set("amount1", 10, 0, 25));

	params2.add(sep2min.set("sep2min", 25.f, 1, 100));
	params2.add(sep2max.set("sep2max", 75.f, 1, 100));
	params2.add(speed2.set("speed2", 0.5, 0, 1));
	params2.add(line2.set("line2", 0.5, 0, 1));
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
	params3.add(shape3.set("shape3", 0, -50, 50));
	params3.add(size3.set("size3", 100, 0, 100));
	params3.add(amount3.set("amount3", 10, 0, 25));
	params3.add(bEnable);
	params3.add(shapeType);

	params2.add(params3);
	params1.add(params2);

	//--

	//guiManager.setAutoSaveSettings(true); // -> enables stor/recall some settings from previous app session
	guiManager.setImGuiAutodraw(true);
	guiManager.setup(); // this instantiates and configures ofxImGui inside the class object.
	//guiManager.bAutoResize = false;

	//--

	// -> not checked on runtime! ONLY ON SETUP
	if (bCustom) {
		SetupStyles();
	}
	else {
		ClearStyles();
	}

	// settings
	ofxImGuiSurfing::loadGroup(paramsSettings);
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

	// one line per widget
	guiManager.AddStyle(bModeA, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1);
	guiManager.AddStyle(bModeB, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1);
	guiManager.AddStyle(bModeC, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1);
	guiManager.AddStyle(bModeD, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1, 10);

	// two widgets same line big
	guiManager.AddStyle(bPrevious, SurfingImGuiTypes::OFX_IM_BUTTON_BIG, true, 2);
	guiManager.AddStyle(bNext, SurfingImGuiTypes::OFX_IM_BUTTON_BIG, false, 2, 10);

	guiManager.AddStyle(shape3, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(size3, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(amount3, SurfingImGuiTypes::OFX_IM_DRAG, false, 2, 10);

	// more widgets
	guiManager.AddStyle(line2, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(speed2, SurfingImGuiTypes::OFX_IM_DRAG);

	//--

	//// customize groups
	//guiManager.AddGroupStyle(params3, SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE);
	//guiManager.AddGroupStyle(params2, SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE_EX);
	////guiManager.AddGroupStyle(params2, SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN);
	////guiManager.AddGroupStyle(params2, SurfingImGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE);

	// customize groups
	guiManager.AddGroupStyle(params1, SurfingImGuiTypesGroups(typeGroup1.get()));
	guiManager.AddGroupStyle(params2, SurfingImGuiTypesGroups(typeGroup2.get()));
	guiManager.AddGroupStyle(params3, SurfingImGuiTypesGroups(typeGroup3.get()));
}

//--------------------------------------------------------------
void ofApp::ClearStyles() {
	guiManager.clear(); // TODO: -> call from beginWindow/group
}

//--------------------------------------------------------------
void ofApp::updateFlags()
{
	// The group of parameters will be customized tree/folder types
	// Notice that will be applied to all the nested groups inside this parent/root ofParameterGroup
	flags_typeFlags = ImGuiTreeNodeFlags_None;
	if (typeFlags == 0) { flagInfo = "ImGuiTreeNodeFlags_None"; }
	if (typeFlags == 1) { flagInfo = "ImGuiTreeNodeFlags_DefaultOpen"; flags_typeFlags |= ImGuiTreeNodeFlags_DefaultOpen; } // to start closed
	if (typeFlags == 2) { flagInfo = "ImGuiTreeNodeFlags_Framed"; flags_typeFlags |= ImGuiTreeNodeFlags_Framed; } // to draw dark tittle bar
	if (typeFlags == 3) { flagInfo = "ImGuiTreeNodeFlags_Bullet"; flags_typeFlags |= ImGuiTreeNodeFlags_Bullet; } // bullet mark
	if (typeFlags == 4) { flagInfo = "ImGuiTreeNodeFlags_NoTreePushOnOpen"; flags_typeFlags |= ImGuiTreeNodeFlags_NoTreePushOnOpen; } // no push
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		drawWindow();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawWindow()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

	guiManager.beginWindow("ofApp", NULL, flags);
	{
		AddToggleRoundedButton(guiManager.bAutoResize);

		if (ToggleRoundedButton("bCustom", &bCustom))
		{
			if (bCustom) {
				SetupStyles();
			}
			else {
				ClearStyles();
			}
		}
		if (bCustom) ImGui::TextWrapped("Customized Style for the Group.");
		else ImGui::TextWrapped("Default Style for the Group.");

		//ImGui::Dummy(ImVec2(0, 5)); // spacing
		ofxImGuiSurfing::AddSpaceY(5); // same than above line

		//-

		ImGui::Separator();
		ofxImGuiSurfing::AddSpaceY(5);
		ImGui::TextWrapped("Customize Styles for Groups/Trees:");
		ofxImGuiSurfing::AddSpaceY(5);

		//-

		// To debug ImGui group flags when rendering groups
		{
			// test customize group/window folders and flags
			if (ofxImGuiSurfing::AddParameter(typeFlags)) {
				updateFlags();
			}
			ImGui::Text(flagInfo.c_str());

			ofxImGuiSurfing::AddSpaceY(5);

			// group type
			if (ofxImGuiSurfing::AddParameter(typeGroup1)) { SetupStyles(); }
			ImGui::Text(getGroupInfo(typeGroup1).c_str());
			if (ofxImGuiSurfing::AddParameter(typeGroup2)) { SetupStyles(); }
			ImGui::Text(getGroupInfo(typeGroup2).c_str());
			if (ofxImGuiSurfing::AddParameter(typeGroup3)) { SetupStyles(); }
			ImGui::Text(getGroupInfo(typeGroup3).c_str());
		}
	}
	guiManager.endWindow();

	//-

	guiManager.beginWindow("ofParameterGroup", NULL, flags);
	{
		ofxImGuiSurfing::AddSpaceY(10);
		ImGui::TextWrapped("ofParameterGroup render:");
		ofxImGuiSurfing::AddSpaceY(10);

		//-

		// Render group

		// direct
		//guiManager.AddGroup(params1, flags_typeFlags, SurfingImGuiTypesGroups(typeGroup1.get()));
		////guiManager.AddGroup(params3, flags_typeFlags, SurfingImGuiTypesGroups(typeGroup2.get()));

		// styled
		guiManager.AddGroup(params1);
		//guiManager.AddGroup(params2);
		//guiManager.AddGroup(params3);
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofxImGuiSurfing::saveGroup(paramsSettings);
}
