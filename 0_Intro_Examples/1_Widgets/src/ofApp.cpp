#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(1920, 25);

	//--

	// Instantiate
	// -> Optional to customize filename for the settings file for multiple instances on the same ofApp.
	//guiManager.setSettingsFilename("1_Widgets"); 

	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	//--

	// Parameters
	bEnable1.set("bEnable1", false);
	bEnable2.set("bEnable2", false);
	bEnable3.set("bEnable3", false);
	bPrevious.set("<", false);
	bNext.set(">", false);
	pos1.set("pos1", glm::vec3(0.f), glm::vec3(-MAX_CAMERA_DISTANCE), glm::vec3(MAX_CAMERA_DISTANCE));
	rto1.set("rto1", glm::vec3(0.f), glm::vec3(-2.f*MAX_CAMERA_DISTANCE), glm::vec3(2.f*MAX_CAMERA_DISTANCE));
	lineWidth2.set("lineWidth2", 0.5, 0, 1);
	separation2.set("separation2", 50, 1, 100);
	shapeType2.set("shapeType2", 0, -50, 50);
	amount2.set("amount2", 10, 0, 25);
	speed3.set("speed3", 0.5, 0, 1);
	knob1.set("Knob1", 0.5f, 0.f, 1.0f);
	knob2.set("Knob2", 5.f, -10.f, 10.0f);
	shapeType3.set("shapeType3", 0, -50, 50);
	size3.set("size3", 100, 0, 100);
	shapeType4.set("shapeType4", 0, -50, 50);
	size4.set("size4", 100, 0, 100);
	lineWidth4.set("lineWidth4", 0.5, 0, 1);
	separation4.set("separation4", 50, 1, 100);
	speed4.set("speed4", 0.5, 0, 1);

	// Groups
	params1.setName("params1");
	params2.setName("params2");
	params3.setName("params3");
	params4.setName("params4");

	params1.add(pos1);
	params1.add(rto1);

	params2.add(lineWidth2);
	params2.add(separation2);
	params2.add(bEnable1);
	params2.add(bEnable2);
	params2.add(bEnable3);

	params3.add(speed3);
	params3.add(shapeType3);
	params3.add(knob1);
	params3.add(knob2);
	params3.add(size3);

	params4.add(size4);
	params4.add(speed4);
	params4.add(shapeType4);
	params4.add(lineWidth4);
	params4.add(separation4);

	// Nest groups
	params2.add(params3);
	params1.add(params2);
	params1.add(params4);

	//----

	setupStyles();
}

//--------------------------------------------------------------
void ofApp::setupStyles() {

	// Customize Styles
	// Will be applyed when rendering a group when draw.
	guiManager.clearStyles();

	// for params
	guiManager.AddStyle(rto1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
	guiManager.AddStyle(bEnable1, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
	guiManager.AddStyle(bEnable2, OFX_IM_TOGGLE_BIG_BORDER);
	guiManager.AddStyle(bEnable3, OFX_IM_TOGGLE_BIG);
	guiManager.AddStyle(knob1, OFX_IM_KNOB, true);//same line
	guiManager.AddStyle(knob2, OFX_IM_KNOB);

	// for groups
	// Notice that (some) flags are not supported for OFX_IM_GROUP_TREE
	guiManager.AddStyleGroup(params3, OFX_IM_GROUP_TREE_EX, ImGuiTreeNodeFlags_DefaultOpen);
	//guiManager.AddStyleGroup(params4, OFX_IM_GROUP_HIDDEN_HEADER, ImGuiTreeNodeFlags_DefaultOpen);
}

//--------------------------------------------------------------
void ofApp::draw() {

	guiManager.begin();
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		if (guiManager.bLockMove) window_flags |= ImGuiWindowFlags_NoMove;

		guiManager.beginWindow("ofApp", NULL, window_flags);
		{
			// Basic folder
			if (1)
				if (ImGui::TreeNode("Tree"))
				{
					guiManager.Add(bEnable1);
					guiManager.Add(bEnable2);
					guiManager.Add(bEnable3);
					ImGui::TreePop();
				}

			// An ofParameterGroup
			if (1) {
				guiManager.AddGroup(params1); // -> BUG: first level crashes!
			}

			ImGui::Spacing();

			// A multidim (xyz) vec2/vec3/vec4 parameter 
			if (1) {
				// Two api patterns can be used:
				guiManager.Add(pos1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
				//ofxImGuiSurfing::AddParameter(pos1, true);
			}

			ImGui::Spacing();

			// Three rounded toggles
			if (1) {
				ofxImGuiSurfing::AddToggleRoundedButton(bPrevious);
				ImGui::SameLine();
				ofxImGuiSurfing::AddToggleRoundedButton(bNext);
				ImGui::SameLine();
				ofxImGuiSurfing::AddToggleRoundedButton(bEnable1);
			}

			//-

			// An extra advanced / sub-panel 
			// with some common toggles that we must customize/assign destinations.
			if (1)
				guiManager.drawAdvancedControls();
		}
		guiManager.endWindow();
	}
	guiManager.end();
}
