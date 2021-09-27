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

#define MAX_CAMERA_DISTANCE 500.0f
	value.set("value", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
	valueMin.set("valueMin", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
	valueMax.set("valueMax", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
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

	//----

	// Sections
#define NUM_SECTIONS 7
	for (int i = 0; i < NUM_SECTIONS; i++) {
		ofParameter<bool> b{ "Enable " + ofToString(i), false };
		bEnablers.emplace_back(b);
	}

	// Configure
	bEnablers[0] = 1;
	bEnablers[1] = 1;
	bEnablers[6] = 1;
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
	guiManager.AddStyle(knob1, OFX_IM_KNOB, true);//+same line
	guiManager.AddStyle(knob2, OFX_IM_KNOB);

	// for groups
	// Notice that (some) flags are not supported for OFX_IM_GROUP_TREE
	guiManager.AddStyleGroup(params3, OFX_IM_GROUP_TREE_EX, ImGuiTreeNodeFlags_DefaultOpen);
	//guiManager.AddStyleGroup(params4, OFX_IM_GROUP_HIDDEN_HEADER, ImGuiTreeNodeFlags_DefaultOpen);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		if (guiManager.bLockMove) window_flags |= ImGuiWindowFlags_NoMove;

		//not working
		if (guiManager.bReset_Window) {
			guiManager.bReset_Window = false;
			guiManager.resetWindowImGui(true, true);
		}

		guiManager.beginWindow("ofApp", NULL, window_flags);
		{
			if(0)//TESTING
			{
				int max = 10000;
				int min = 1;
				static int ilow = 1, ihigh = 5000;
				static int ilow1 = 1, ihigh1 = 5000;
				static int ilow2 = 2, ihigh2 = 5000;
				static float flow = 1, fhigh = 5000;
				static float flow1 = 1, fhigh1 = 5000;
				static float flow2 = 1, fhigh2 = 5000;
				//ImGui::RangeSliderInt("CMDS", min, max, ilow, ihigh);
				//ImGui::RangeSliderInt("CMDS1", min, max, ilow1, ihigh1);
				//ImGui::RangeSliderInt("CMDS2", min, max, ilow2, ihigh2);
				//ImGui::RangeSliderFloat("CMDS3f", min, max, flow2, fhigh2);
				//ImGui::RangeSliderFloat("CMDS4f", min, max, flow1, fhigh1);
				ImGui::RangeSliderFloat("CMDS5f", min, max, flow, fhigh);
			}

			// Toggle enablers
			{
				for (int i = 0; i < NUM_SECTIONS; i++) {
					ofxImGuiSurfing::AddToggleRoundedButton(bEnablers[i]);
				}
				ImGui::Spacing();
			}

			// Ranges for multidim glm::vec
			if (bEnablers[0])
			{
				ImGui::Spacing();
				guiManager.refreshLayout();

				static ofParameter<int> coord{ "coord", 0, 0, 2 };
				ofxImGuiSurfing::AddParameter(coord);

				ofxImGuiSurfing::AddParameter(value);
				ofxImGuiSurfing::AddParameter(valueMin);
				ofxImGuiSurfing::AddParameter(valueMax);

				float _h= ofxImGuiSurfing::getWidgetsHeightUnit();
				float _w100 = ofxImGuiSurfing::getWidgetsWidth(1);
				float _w50 = ofxImGuiSurfing::getWidgetsWidth(2);

				//IMGUI_SUGAR_SLIDER_WIDTH_PUSH;
				//ofxImGuiSurfing::AddRangeParam("RgVal", valueMin, valueMax, "%.2f  %.2f", 1.0f, ImVec2(_w100, _h), false);
				ofxImGuiSurfing::AddRangeParam("RgVal", valueMin, valueMax, "%.2f  %.2f", 1.0f);
				//IMGUI_SUGAR_SLIDER_WIDTH_POP;

				//ImGui::SameLine();
				//ImGui::Text("asdf");
				//ImGui::SameLine();
				//ImGui::Button("Button1");
				//ImGui::SameLine();
				//ImGui::Button("Button2");
				//ImGui::Spacing();

				ofxImGuiSurfing::AddRangeOneVec3Param("RangePos", pos1, valueMin, valueMax, value, coord.get());
				//ImGui::SameLine();
				//ImGui::Text("asdf");
			}

			// A Multidim (xyz) vec2/vec3/vec4 parameter 
			if (bEnablers[1])
			{
				ImGui::Spacing();

				// Two api patterns can be used:
				guiManager.Add(pos1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
				//ofxImGuiSurfing::AddParameter(pos1, true);
			}

			// Basic folder
			if (bEnablers[2])
			{
				if (ImGui::TreeNode("Tree"))
				{
					ImGui::Spacing();

					guiManager.Add(bEnable1);
					guiManager.Add(bEnable2);
					guiManager.Add(bEnable3);
					ImGui::TreePop();
				}
			}

			// An ofParameterGroup with nested params
			//if (0)
			if (bEnablers[3])
			{
				ImGui::Spacing();

				static bool bOpen = false;
				ImGui::SetNextTreeNodeOpen(bOpen, ImGuiCond_Appearing);

				guiManager.AddGroup(params1, ImGuiTreeNodeFlags_None, OFX_IM_GROUP_DEFAULT);
				//guiManager.AddGroup(params1);
			}


			// Three rounded toggles
			if (bEnablers[4])
			{
				ImGui::Spacing();

				ofxImGuiSurfing::AddToggleRoundedButton(bPrevious);
				ImGui::SameLine();
				ofxImGuiSurfing::AddToggleRoundedButton(bNext);
				ImGui::SameLine();
				ofxImGuiSurfing::AddToggleRoundedButton(bEnable1);
			}

			// Vertical Sliders
			if (bEnablers[5])
			{
				ImGui::Spacing();

				if (ImGui::TreeNode("Vertical Sliders"))
				{
					float w = 70;
					float h = 200;
					ofxImGuiSurfing::AddVSlider(speed3, ImVec2(w, h), true);
					ImGui::SameLine();
					ofxImGuiSurfing::AddVSlider(speed4, ImVec2(w, h), true);
					ImGui::SameLine();
					ofxImGuiSurfing::AddVSlider(size3, ImVec2(w, h), true);
					ImGui::SameLine();
					ofxImGuiSurfing::AddVSlider(size4, ImVec2(w, h), true);
					ImGui::TreePop();
				}
			}

			//-

			// An extra advanced / sub-panel 
			// with some common toggles that we must customize/assign destinations.
			if (bEnablers[6])
			{
				guiManager.drawAdvanced();
			}
		}
		guiManager.endWindow();
	}
	guiManager.end();
}
