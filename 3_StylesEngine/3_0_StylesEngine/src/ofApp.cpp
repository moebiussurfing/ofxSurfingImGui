#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	//-

	// Prepare Parameters

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
	guiManager.setSettingsFilename("3_0_StylesEngine"); // -> Optional customize filename for the settings file for multiple instances.
	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	//--

	setupCustomizators();

	resetStyles(); // -> Workaround: loading settings not working..

	ofxImGuiSurfing::loadGroup(paramsSettings);

	//--

	// Reset
	if (bCustom)
	{
		setupImGuiStyles();
	}
	else
	{
		clearStyles();
	}
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
	// Window ofApp
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

		guiManager.beginWindow("ofApp", NULL, flags);
		{
			// Modes

			// Autoresize
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize, ImVec2(1.55f * 30, 30));

			// Custom
			if (ofxImGuiSurfing::ToggleRoundedButton("bCustom", &bCustom, ImVec2(1.55f * 30, 30)))
			{
				if (bCustom)
				{
					setupImGuiStyles();
				}
				else
				{
					clearStyles();
				}
			}

			ImGui::Spacing();

			if (bCustom) ImGui::TextWrapped("Customized Style for the ofParameters Widgets in the Group.");
			else ImGui::TextWrapped("Default Style for the ofParameters Widgets in the Group.");

			ofxImGuiSurfing::AddSpacingBig();

			//-

			if (bCustom) {

				ImGui::TextWrapped("> Notice that some styles can't be combined, or some of them will be ignored in some situations.");

				ofxImGuiSurfing::AddSpacingHuge();

				ImGui::TextWrapped("> Set the controls to test the different types of Group/Trees/Header modes");

				ofxImGuiSurfing::AddSpacingBig();
				ofxImGuiSurfing::AddSpacingBig();

				//--

				// To debug ImGui group flags when rendering groups
				// Test customize group/window folders and flags
				{
					// Set group types and flags

					// Group 1 Styles selectors
					ImGui::Text(params1.getName().c_str());
					ofxImGuiSurfing::AddParameter(typeGroup1);
					ImGui::Text(getSurfingImGuiTypesGroupsName(typeGroup1).c_str());
					ofxImGuiSurfing::AddParameter(typeFlags1);
					ImGui::Text(flagInfo1.c_str());
					ImGui::Spacing();

					// Group 2 Styles selectors
					ImGui::Indent();
					{
						ImGui::Separator();
						ImGui::Text(params2.getName().c_str());
						ofxImGuiSurfing::AddParameter(typeGroup2);
						ImGui::Text(getSurfingImGuiTypesGroupsName(typeGroup2).c_str());
						ofxImGuiSurfing::AddParameter(typeFlags2);
						ImGui::Text(flagInfo2.c_str());
						ImGui::Spacing();

						// Group 3 Styles selectors
						ImGui::Indent();
						{
							ImGui::Separator();
							ImGui::Text(params3.getName().c_str());
							ofxImGuiSurfing::AddParameter(typeGroup3);
							ImGui::Text(getSurfingImGuiTypesGroupsName(typeGroup3).c_str());
							ofxImGuiSurfing::AddParameter(typeFlags3);
							ImGui::Text(flagInfo3.c_str());
							ImGui::Spacing();
						}
						ImGui::Unindent();
					}
					ImGui::Unindent();
				}

				//--

				ofxImGuiSurfing::AddSpacingHuge();

				float w1 = ofxImGuiSurfing::getWidgetsWidth(1);
				float w2 = ofxImGuiSurfing::getWidgetsWidth(2);
				float h = 1.5f * ofxImGuiSurfing::getWidgetsHeightUnit();

				// Load / Save Styles
				if (ImGui::Button("Load Styles", ImVec2(w2, h)))
				{
					ofxImGuiSurfing::loadGroup(paramsSettings);
				}
				ImGui::SameLine();
				if (ImGui::Button("Save Styles", ImVec2(w2, h)))
				{
					ofxImGuiSurfing::saveGroup(paramsSettings);
				}
				// Reset Styles
				if (ImGui::Button("Reset Styles", ImVec2(w1, h)))
				{
					resetStyles();
				}

				ofxImGuiSurfing::AddSpacingBig();
			}

			guiManager.drawAdvanced();
		}
		guiManager.endWindow();
	}

	//-

	// Window for test Groups
	drawImGuiGroup();
}

//--------------------------------------------------------------
void ofApp::drawImGuiGroup()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

	guiManager.beginWindow("ofParameterGroup", NULL, flags);
	{
		// Render a Group

		// A. Direct Styled
		//guiManager.AddGroup(params1, flags_typeFlags, SurfingImGuiTypesGroups(typeGroup1.get()));

		// B. Styled Previously on Setup Styles
		guiManager.AddGroup(params1);
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::setupCustomizators() {

	// Debug custom types and group flags
	bCustom = false;

	typeFlags1.set("typeFlags1", 1, 0, 4);
	typeFlags2.set("typeFlags2", 1, 0, 4);
	typeFlags3.set("typeFlags3", 1, 0, 4);

	int sz = (int)OFX_IM_GROUP_NUM_TYPES;

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
}

//--------------------------------------------------------------
void ofApp::setupImGuiStyles() {

	// Clear queued Styles first.
	guiManager.clearStyles();

	guiManager.AddStyle(bMode1, OFX_IM_TOGGLE_BIG, 2, true);
	// Two widgets per row. Sameline for the next.
	guiManager.AddStyle(bMode2, OFX_IM_TOGGLE_BIG, 2);
	// Two widgets per row. Not Sameline for the next

	guiManager.AddStyle(bMode3, OFX_IM_TOGGLE_BIG, 2, true);
	// Two widgets same line
	guiManager.AddStyle(bMode4, OFX_IM_TOGGLE_BIG, 2, false, 10);
	// Two widgets per row. Not Sameline for the next. 10 y pix ending spacing

	guiManager.AddStyle(bEnable, OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);

	// One line per widget
	guiManager.AddStyle(bModeA, OFX_IM_TOGGLE_SMALL);
	guiManager.AddStyle(bModeB, OFX_IM_TOGGLE_SMALL);
	guiManager.AddStyle(bModeC, OFX_IM_TOGGLE_SMALL);
	guiManager.AddStyle(bModeD, OFX_IM_TOGGLE_SMALL, 1, false, 10); // 10 y pix ending spacing

	// Two Big toggle widgets same line
	guiManager.AddStyle(bPrevious, OFX_IM_BUTTON_BIG, 2, true);
	guiManager.AddStyle(bNext, OFX_IM_BUTTON_BIG, 2, false, 10);

	guiManager.AddStyle(shape3, OFX_IM_STEPPER);
	guiManager.AddStyle(size3, OFX_IM_VSLIDER, 2);//half width
	guiManager.AddStyle(amount3, OFX_IM_HSLIDER, 4, false, 10);//quater width

	// More widgets
	guiManager.AddStyle(line2, OFX_IM_STEPPER);
	guiManager.AddStyle(speed2, OFX_IM_DRAG);

	//--

	// -> That's the important Groups stuff: 
	// What we will use in our projects:

	// Customize each Group Style
	guiManager.AddStyleGroup(params1, SurfingImGuiTypesGroups(typeGroup1.get()), flags_typeFlags1);
	guiManager.AddStyleGroup(params2, SurfingImGuiTypesGroups(typeGroup2.get()), flags_typeFlags2);
	guiManager.AddStyleGroup(params3, SurfingImGuiTypesGroups(typeGroup3.get()), flags_typeFlags3);
}

//--------------------------------------------------------------
void ofApp::clearStyles() {
	guiManager.clearStyles(); // TODO: -> Call from beginWindow/group
}

//--------------------------------------------------------------
void ofApp::resetStyles() {
	
	// types
	typeGroup1 = 0;
	typeGroup2 = 0;
	typeGroup3 = 0;

	// falgs
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

// Callback for a parameter group  
//--------------------------------------------------------------
void ofApp::Changed_Params(ofAbstractParameter &e)
{
	string name = e.getName();
	ofLogNotice(__FUNCTION__) << name << " : " << e;

	if (0) {}

	// Group Style Type

	else if (name == typeGroup1.getName())
	{
		refreshFlag(typeFlags1, flags_typeFlags1, flagInfo1);
		setupImGuiStyles();
	}
	else if (name == typeGroup2.getName())
	{
		refreshFlag(typeFlags2, flags_typeFlags2, flagInfo2);
		setupImGuiStyles();
	}
	else if (name == typeGroup3.getName())
	{
		refreshFlag(typeFlags3, flags_typeFlags3, flagInfo3);
		setupImGuiStyles();
	}

	// Group Flag Type

	else if (name == typeFlags1.getName())
	{
		refreshFlag(typeFlags1, flags_typeFlags1, flagInfo1);
		setupImGuiStyles();
	}
	else if (name == typeFlags2.getName())
	{
		refreshFlag(typeFlags2, flags_typeFlags2, flagInfo2);
		setupImGuiStyles();
	}
	else if (name == typeFlags3.getName())
	{
		refreshFlag(typeFlags3, flags_typeFlags3, flagInfo3);
		setupImGuiStyles();
	}
}

//--------------------------------------------------------------
void ofApp::exit() {

	ofRemoveListener(paramsSettings.parameterChangedE(), this, &ofApp::Changed_Params);

	ofxImGuiSurfing::saveGroup(paramsSettings);
}