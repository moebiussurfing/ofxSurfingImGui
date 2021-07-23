#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	//-

	// debug custom types and group flags
	bCustom = true;

	typeFlags1.set("typeFlags1", 1, 0, 4);
	typeFlags2.set("typeFlags2", 1, 0, 4);
	typeFlags3.set("typeFlags3", 1, 0, 4);

	int sz = (int)SurfingImGuiTypesGroups::OFX_IM_GROUP_NUM_TYPES;
	typeGroup1.set("typeGroup1", 0, 0, sz - 2);
	typeGroup2.set("typeGroup2", 0, 0, sz - 2);
	typeGroup3.set("typeGroup3", 0, 0, sz - 2);

	ofAddListener(paramsSettings.parameterChangedE(), this, &ofApp::Changed_Params);

	paramsSettings.setName("Settings");
	paramsSettings.add(typeFlags1);
	paramsSettings.add(typeFlags2);
	paramsSettings.add(typeFlags3);
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

	// settings
	ofxImGuiSurfing::loadGroup(paramsSettings);

	//--

	// -> not checked on runtime! ONLY ON SETUP
	if (bCustom) {
		setupStyles();
	}
	else {
		clearStyles();
	}
}

//--------------------------------------------------------------
void ofApp::setupStyles() {

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
	////guiManager.AddGroupStyle(params2, SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN_HEADER);
	////guiManager.AddGroupStyle(params2, SurfingImGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE);

	// customize groups
	guiManager.AddGroupStyle(params1, SurfingImGuiTypesGroups(typeGroup1.get()), flags_typeFlags1);
	guiManager.AddGroupStyle(params2, SurfingImGuiTypesGroups(typeGroup2.get()), flags_typeFlags2);
	guiManager.AddGroupStyle(params3, SurfingImGuiTypesGroups(typeGroup3.get()), flags_typeFlags3);
}

//--------------------------------------------------------------
void ofApp::clearStyles() {
	guiManager.clear(); // TODO: -> call from beginWindow/group
}

//--------------------------------------------------------------
void ofApp::refreshFlag(int indexType, ImGuiTreeNodeFlags &flag, std::string &flagInfo) {

	std::string s0 = "ImGuiTreeNodeFlags_None";
	std::string s1 = "ImGuiTreeNodeFlags_DefaultOpen";
	std::string s2 = "ImGuiTreeNodeFlags_Framed";
	std::string s3 = "ImGuiTreeNodeFlags_Bullet";
	std::string s4 = "ImGuiTreeNodeFlags_NoTreePushOnOpen";
	
	ImGuiTreeNodeFlags fg = ImGuiTreeNodeFlags_None;
	if (indexType == 0) { flagInfo = s0; }
	else if (indexType == 1) { flagInfo = s1; fg |= ImGuiTreeNodeFlags_DefaultOpen; } // to start closed
	else if (indexType == 2) { flagInfo = s2; fg |= ImGuiTreeNodeFlags_Framed; } // to draw dark tittle bar
	else if (indexType == 3) { flagInfo = s3; fg |= ImGuiTreeNodeFlags_Bullet; } // bullet mark
	else if (indexType == 4) { flagInfo = s4; fg |= ImGuiTreeNodeFlags_NoTreePushOnOpen; } // no push
	else flagInfo = s0;

	ofLogNotice(__FUNCTION__) << indexType << "," << flag << "," << flagInfo;
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

		//ImGui::Dummy(ImVec2(0, 5)); // spacing
		ofxImGuiSurfing::AddSpaceY(5); // same than above line

		//-

		if (bCustom) {

			static bool bReset = false;
			if (ToggleRoundedButton("bReset", &bReset))
			{
				if (bReset) {
					bReset = false;
					typeGroup1 = 0;
					typeGroup2 = 0;
					typeGroup3 = 0;
					typeFlags1 = 1;
					typeFlags2 = 1;
					typeFlags3 = 1;
				}
			}

			//-

			// To debug ImGui group flags when rendering groups
			// test customize group/window folders and flags
			{
				ofxImGuiSurfing::AddSpaceY(5);

				// group types and flags

				ofxImGuiSurfing::AddParameter(typeGroup1);
				ImGui::Text(getSurfingImGuiTypesGroupsName(typeGroup1).c_str());
				//ImGui::Text(getGroupInfo(typeGroup1).c_str());
				ofxImGuiSurfing::AddParameter(typeFlags1);
				ImGui::Text(flagInfo1.c_str());
				ofxImGuiSurfing::AddSpaceY();

				ofxImGuiSurfing::AddParameter(typeGroup2);
				ImGui::Text(getSurfingImGuiTypesGroupsName(typeGroup2).c_str());
				//ImGui::Text(getGroupInfo(typeGroup2).c_str());
				ofxImGuiSurfing::AddParameter(typeFlags2);
				ImGui::Text(flagInfo2.c_str());
				ofxImGuiSurfing::AddSpaceY();

				ofxImGuiSurfing::AddParameter(typeGroup3);
				ImGui::Text(getSurfingImGuiTypesGroupsName(typeGroup3).c_str());
				//ImGui::Text(getGroupInfo(typeGroup3).c_str());
				ofxImGuiSurfing::AddParameter(typeFlags3);
				ImGui::Text(flagInfo3.c_str());
				ofxImGuiSurfing::AddSpaceY();
			}
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

		// A. direct
		//guiManager.AddGroup(params1, flags_typeFlags, SurfingImGuiTypesGroups(typeGroup1.get()));
		////guiManager.AddGroup(params3, flags_typeFlags, SurfingImGuiTypesGroups(typeGroup2.get()));

		// B. styled
		guiManager.AddGroup(params1);
		//guiManager.AddGroup(params2);
		//guiManager.AddGroup(params3);
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::exit() {

	ofRemoveListener(paramsSettings.parameterChangedE(), this, &ofApp::Changed_Params);

	ofxImGuiSurfing::saveGroup(paramsSettings);
}

// callback for a parameter group  
//--------------------------------------------------------------
void ofApp::Changed_Params(ofAbstractParameter &e)
{
	string name = e.getName();
	ofLogNotice(__FUNCTION__) << name << " : " << e;

	// group type
	if (name == typeGroup1.getName() ||
		name == typeGroup2.getName() ||
		name == typeGroup3.getName())
	{
		setupStyles();
	}

	// group flag type
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
		refreshFlag(typeFlags2, flags_typeFlags3, flagInfo3);
		setupStyles();
	}
}