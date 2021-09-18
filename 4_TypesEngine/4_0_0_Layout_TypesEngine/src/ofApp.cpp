#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	//-

	// Prepare parameters

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
	
	// Instantiate
	guiManager.setSettingsFilename("4_0_0_Layout_TypesEngine"); // -> Optional customize filename for the settings file for multiple instances.
	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	//-

	setupCustomizators();

	resetStyles(); // -> Workaround: loading settings not working..

	ofxImGuiSurfing::loadGroup(paramsSettings, "Settings.json");
}

//--------------------------------------------------------------
void ofApp::setupCustomizators() {

	// Debug custom types and group flags
	bCustom = true;

	typeFlags1.set("typeFlags1", 1, 0, 4);
	typeFlags2.set("typeFlags2", 1, 0, 4);
	typeFlags3.set("typeFlags3", 1, 0, 4);

	int sz = (int)SurfingImGuiTypesGroups::OFX_IM_GROUP_NUM_TYPES;
	typeGroup1.set("typeGroup1", 0, 0, sz - 2);
	typeGroup2.set("typeGroup2", 0, 0, sz - 2);
	typeGroup3.set("typeGroup3", 0, 0, sz - 2);

	paramsSettings.setName("Settings");
	paramsSettings.add(typeFlags1);
	paramsSettings.add(typeFlags2);
	paramsSettings.add(typeFlags3);
	paramsSettings.add(typeGroup1);
	paramsSettings.add(typeGroup2);
	paramsSettings.add(typeGroup3);
	paramsSettings.add(guiManager.bAutoResize);

	ofAddListener(paramsSettings.parameterChangedE(), this, &ofApp::Changed_Params);

	//--

	// -> Not checked on runtime! ONLY ON SETUP
	if (bCustom) {
		setupStyles();
	}
	else {
		clearStyles();
	}
}

//--------------------------------------------------------------
void ofApp::setupStyles() {

	guiManager.clear(); // TODO: -> Call from beginWindow/group

	// Two widgets same line
	guiManager.AddStyle(bMode1, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 2);
	guiManager.AddStyle(bMode2, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, false, 2);

	// Two widgets same line
	guiManager.AddStyle(bMode3, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 2);
	guiManager.AddStyle(bMode4, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, false, 2, 10);

	// One line per widget
	guiManager.AddStyle(bModeA, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1);
	guiManager.AddStyle(bModeB, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1);
	guiManager.AddStyle(bModeC, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1);
	guiManager.AddStyle(bModeD, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 1, 10);

	// Two widgets same line big
	guiManager.AddStyle(bPrevious, SurfingImGuiTypes::OFX_IM_BUTTON_BIG, true, 2);
	guiManager.AddStyle(bNext, SurfingImGuiTypes::OFX_IM_BUTTON_BIG, false, 2, 10);

	guiManager.AddStyle(shape3, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(size3, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(amount3, SurfingImGuiTypes::OFX_IM_DRAG, false, 2, 10);

	// More widgets
	guiManager.AddStyle(line2, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(speed2, SurfingImGuiTypes::OFX_IM_DRAG);

	//--

	// Customize groups
	guiManager.AddGroupStyle(params1, SurfingImGuiTypesGroups(typeGroup1.get()), flags_typeFlags1);
	guiManager.AddGroupStyle(params2, SurfingImGuiTypesGroups(typeGroup2.get()), flags_typeFlags2);
	guiManager.AddGroupStyle(params3, SurfingImGuiTypesGroups(typeGroup3.get()), flags_typeFlags3);
}

//--------------------------------------------------------------
void ofApp::clearStyles() {
	guiManager.clear(); // TODO: -> Call from beginWindow/group
}

//--------------------------------------------------------------
void ofApp::resetStyles() {
	typeGroup1 = 0;
	typeGroup2 = 0;
	typeGroup3 = 0;

	typeFlags1 = 1;
	typeFlags2 = 1;
	typeFlags3 = 1;
}

//--------------------------------------------------------------
void ofApp::refreshFlag(int indexFlagType, ImGuiTreeNodeFlags &flag, std::string &flagInfo) {

	std::string s0 = "ImGuiTreeNodeFlags_None";
	std::string s1 = "ImGuiTreeNodeFlags_DefaultOpen";
	std::string s2 = "ImGuiTreeNodeFlags_Framed";
	std::string s3 = "ImGuiTreeNodeFlags_Bullet";
	std::string s4 = "ImGuiTreeNodeFlags_NoTreePushOnOpen";

	ImGuiTreeNodeFlags fg = ImGuiTreeNodeFlags_None;
	if (indexFlagType == 0) { flagInfo = s0; }
	else if (indexFlagType == 1) { flagInfo = s1; fg |= ImGuiTreeNodeFlags_DefaultOpen; } // to start closed
	else if (indexFlagType == 2) { flagInfo = s2; fg |= ImGuiTreeNodeFlags_Framed; } // to draw dark tittle bar
	else if (indexFlagType == 3) { flagInfo = s3; fg |= ImGuiTreeNodeFlags_Bullet; } // bullet mark
	else if (indexFlagType == 4) { flagInfo = s4; fg |= ImGuiTreeNodeFlags_NoTreePushOnOpen; } // no push
	else flagInfo = s0;

	flag = fg;

	ofLogNotice(__FUNCTION__) << indexFlagType << ", " << flag << ", " << flagInfo;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		drawImGui();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

	guiManager.beginWindow("ofApp", NULL, flags);
	{
		AddToggleRoundedButton(guiManager.bAutoResize);

		if (ToggleRoundedButton("bCustom", &bCustom))
		{
			if (bCustom) {
				setupStyles();
			}
			else {
				clearStyles();
			}
		}

		if (bCustom) ImGui::TextWrapped("Customized Style for the Group.");
		else ImGui::TextWrapped("Default Style for the Group.");

		ImGui::Spacing();

		//-

		if (bCustom) {

			static bool bReset = false;
			if (ToggleRoundedButton("bReset", &bReset))
			{
				if (bReset) {
					bReset = false;

					resetStyles();
				}
			}

			//-

			static bool bLoadSettings = false;
			if (ToggleRoundedButton("bLoadSettings", &bLoadSettings))
			{
				if (bLoadSettings) {
					bLoadSettings = false;

					ofxImGuiSurfing::loadGroup(paramsSettings, "Settings.json");
					//setupStyles();
				}
			}


			//-

			// To debug ImGui group flags when rendering groups
			// Test customize group/window folders and flags
			{
				ofxImGuiSurfing::AddSpaceY(10);

				// set group types and flags

				ImGui::Separator();
				ImGui::Text(params1.getName().c_str());
				ofxImGuiSurfing::AddParameter(typeGroup1);
				ImGui::Text(getSurfingImGuiTypesGroupsName(typeGroup1).c_str());
				ofxImGuiSurfing::AddParameter(typeFlags1);
				ImGui::Text(flagInfo1.c_str());
				ImGui::Spacing();

				ImGui::Separator();
				ImGui::Text(params2.getName().c_str());
				ofxImGuiSurfing::AddParameter(typeGroup2);
				ImGui::Text(getSurfingImGuiTypesGroupsName(typeGroup2).c_str());
				ofxImGuiSurfing::AddParameter(typeFlags2);
				ImGui::Text(flagInfo2.c_str());
				ImGui::Spacing();

				ImGui::Separator();
				ImGui::Text(params3.getName().c_str());
				ofxImGuiSurfing::AddParameter(typeGroup3);
				ImGui::Text(getSurfingImGuiTypesGroupsName(typeGroup3).c_str());
				ofxImGuiSurfing::AddParameter(typeFlags3);
				ImGui::Text(flagInfo3.c_str());
				ImGui::Spacing();
			}
		}
	}
	guiManager.endWindow();

	//-

	drawImGuiGroup();
}

//--------------------------------------------------------------
void ofApp::drawImGuiGroup()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

	guiManager.beginWindow("ofParameterGroup", NULL, flags);
	{
		ImGui::Spacing();
		ImGui::TextWrapped("NOTE\nNotice that some combinations of flags/styles can't be combined.\nOr some flags also should be queued and here only one type at the same time is used..");
		//TODO:
		// Some headers still not working
		ImGui::Spacing();
		ImGui::TextWrapped("ofParameterGroup render ->");
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		//-

		// Render group

		// A. Direct styled
		//guiManager.AddGroup(params1, flags_typeFlags, SurfingImGuiTypesGroups(typeGroup1.get()));
		////guiManager.AddGroup(params3, flags_typeFlags, SurfingImGuiTypesGroups(typeGroup2.get()));

		// B. Styled previously on setup
		guiManager.AddGroup(params1);
		//guiManager.AddGroup(params2);
		//guiManager.AddGroup(params3);
	}
	guiManager.endWindow();
}

// Callback for a parameter group  
//--------------------------------------------------------------
void ofApp::Changed_Params(ofAbstractParameter &e)
{
	string name = e.getName();
	ofLogNotice(__FUNCTION__) << name << " : " << e;

	// Group style type
	if (name == typeGroup1.getName())
	{
		refreshFlag(typeFlags1, flags_typeFlags1, flagInfo1);
		setupStyles();
	}
	if (name == typeGroup2.getName())
	{
		refreshFlag(typeFlags2, flags_typeFlags2, flagInfo2);
		setupStyles();
	}
	if (name == typeGroup3.getName())
	{
		refreshFlag(typeFlags3, flags_typeFlags3, flagInfo3);
		setupStyles();
	}

	// Group flag type
	if (name == typeFlags1.getName())
	{
		refreshFlag(typeFlags1, flags_typeFlags1, flagInfo1);
		setupStyles();
	}
	if (name == typeFlags2.getName())
	{
		refreshFlag(typeFlags2, flags_typeFlags2, flagInfo2);
		setupStyles();
	}
	if (name == typeFlags3.getName())
	{
		refreshFlag(typeFlags3, flags_typeFlags3, flagInfo3);
		setupStyles();
	}
}

//--------------------------------------------------------------
void ofApp::exit() {

	ofRemoveListener(paramsSettings.parameterChangedE(), this, &ofApp::Changed_Params);

	ofxImGuiSurfing::saveGroup(paramsSettings, "Settings.json");
}