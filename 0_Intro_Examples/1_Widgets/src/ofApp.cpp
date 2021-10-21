#include "ofApp.h"

#define MAX_CAMERA_DISTANCE 500.0f

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetWindowPosition(1920, 25);

	//--

	// Parameters

	bEnable1.set("bEnable1", false);
	bEnable2.set("bEnable2", false);
	bEnable3.set("bEnable3", false);
	bEnable4.set("bEnable4", false);

	bPrevious.set("<", false);
	bNext.set(">", false);

	value.set("value", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
	valueMin.set("valueMin", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
	valueMax.set("valueMax", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);

	pos_1.set("pos_1", glm::vec3(0.f), glm::vec3(-MAX_CAMERA_DISTANCE), glm::vec3(MAX_CAMERA_DISTANCE));
	rot_1.set("rot_1", glm::vec3(0.f), glm::vec3(-2.f*MAX_CAMERA_DISTANCE), glm::vec3(2.f*MAX_CAMERA_DISTANCE));

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

	//--

	// Groups

	params1.setName("params1");
	params2.setName("params2");
	params3.setName("params3");
	params4.setName("params4");

	params1.add(bEnable1);
	params1.add(bEnable2);
	params1.add(bEnable3);
	params1.add(bEnable4);

	params1.add(pos_1);
	params1.add(rot_1);

	params2.add(lineWidth2);
	params2.add(separation2);

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

	// -> Nesting Groups
	params2.add(params3);
	params1.add(params2);
	params1.add(params4);

	//----


	// ImGui

	// Instantiate

	// -> Optional to customize filename for the settings file for multiple instances on the same ofApp.
	//guiManager.setSettingsFilename("1_Widgets"); 

	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	//----

	// Customize Styles

	setupImGuiStyles();

	//-

	// Callbacks to update Custom Styles on runtime

	//--------------------------------------------------------------
	listener_bEnable1 = bEnable1.newListener([this](bool &b) {
		ofLogNotice("bEnable1: ") << (b ? "TRUE" : "FALSE");

		if (bEnable1) {
			guiManager.UpdateStyle(rot_1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
			guiManager.UpdateStyle(pos_1, OFX_IM_DEFAULT);
		}
		else {
			guiManager.UpdateStyle(rot_1, OFX_IM_DEFAULT);
			guiManager.UpdateStyle(pos_1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
		}

		// Notice that:
		// For this bool toggle, we do not will call setupImGuiStyles()
		// We can update these two above params on runtime
		// (without having to clear) previously added ofParams yet.
	});

	//--------------------------------------------------------------
	listener_bEnable2 = bEnable2.newListener([this](bool &b) {
		ofLogNotice("bEnable2: ") << (b ? "TRUE" : "FALSE");

		setupImGuiStyles(); // -> refresh styles on runtime!
	});

	//--------------------------------------------------------------
	listener_bEnable3 = bEnable3.newListener([this](bool &b) {
		ofLogNotice("bEnable3: ") << (b ? "TRUE" : "FALSE");

		setupImGuiStyles(); // -> refresh styles on runtime!
	});

	//--------------------------------------------------------------
	listener_bEnable4 = bEnable4.newListener([this](bool &b) {
		ofLogNotice("bEnable4: ") << (b ? "TRUE" : "FALSE");

		setupImGuiStyles(); // -> refresh styles on runtime!
	});

	//----

	// Sections toggles
	// To hide or show sections

#define NUM_SECTIONS 7
	for (int i = 0; i < NUM_SECTIONS; i++) {
		ofParameter<bool> b{ "Section " + ofToString(i), false };
		bEnablers.emplace_back(b);

		paramsApp.add(b);

		listenerGroup2.push(b.newListener(this, &ofApp::checkPressed));
	}

	//--

	// Startup
	// Load last session state settings

	ofxSurfingHelpers::loadGroup(paramsApp);
	ofxSurfingHelpers::loadGroup(params1);
}

//--------------------------------------------------------------
void ofApp::checkPressed(const void * sender, bool & value) {
	if (attendingEvent) {
		return;
	}

	attendingEvent = true;
	auto param = (ofParameter<bool>*)sender;

	ofLogNotice() << __FUNCTION__ << " : "
		<< (param->getName()) << " "
		<< (param->get() ? "TRUE" : "FALSE");

	if (value == false)
	{
		// Don't let this parameter be deactivated so there's always
		// one active
		param->set(true);
	}
	else
	{
		for (int i = 0; i < NUM_SECTIONS; i++)
		{
			if (param->isReferenceTo(bEnablers[i])) {
				for (int j = 0; j < NUM_SECTIONS; j++)
				{
					if (i == j) continue;
					bEnablers[j].set(false);
				}
			}
		}
	}
	attendingEvent = false;
}

//--------------------------------------------------------------
void ofApp::exit() {

	// Save session state settings
	ofxSurfingHelpers::saveGroup(paramsApp);
	ofxSurfingHelpers::saveGroup(params1);
}

//--------------------------------------------------------------
void ofApp::setupImGuiStyles() {

	// Customize Styles

	guiManager.clearStyles();

	// Notice that:
	// We can update on runtime (without having to clear) previously added ofParams yet.

	// Look on the bEnable1 / bEnable2 / bEnable3 / bEnable4 behaviour: 
	// We recall setupImGuiStyles() when above bool changes to update the styles.

	//-

	// 1. For params

	// Will be applied when rendering a group when drawing his widgets.

	// 1 widget per row. not sameline for the next. 20 pix y spacing at end.

	guiManager.AddStyle(bEnable1, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
	guiManager.AddStyle(bEnable2, OFX_IM_TOGGLE_BIG_BORDER);
	guiManager.AddStyle(bEnable3, OFX_IM_TOGGLE_BIG);
	guiManager.AddStyle(bEnable4, OFX_IM_TOGGLE_BIG);

	//-

	if (bEnable1) {
		guiManager.AddStyle(knob1, OFX_IM_KNOB, 3, true);
		guiManager.AddStyle(knob2, OFX_IM_KNOB, 3, true);
		guiManager.AddStyle(size3, OFX_IM_KNOB, 3, false);
		// 3 widgets per row. sameline for the next
		// 3 widgets per row. sameline for the next
		// 3 widgets per row. not sameline for the next
	}
	else {
		guiManager.AddStyle(knob1, OFX_IM_VSLIDER_NO_LABELS, 3, true);
		guiManager.AddStyle(knob2, OFX_IM_VSLIDER_NO_LABELS, 3, true);
		guiManager.AddStyle(size3, OFX_IM_VSLIDER_NO_LABELS, 3, false);
		// 3 widgets per row. sameline for the next
		// 3 widgets per row. sameline for the next
		// 3 widgets per row. not sameline for the next
	}

	if (bEnable2) {
		guiManager.AddStyle(lineWidth2, OFX_IM_STEPPER);
		guiManager.AddStyle(separation2, OFX_IM_STEPPER);

		//guiManager.AddStyle(lineWidth2, OFX_IM_VSLIDER, 2, true);
		//guiManager.AddStyle(separation2, OFX_IM_VSLIDER, 2, false);
		// 2 widgets per row. sameline for the next
		// 2 widgets per row. not sameline for the next
	}
	else {
		guiManager.AddStyle(lineWidth2, OFX_IM_DEFAULT);
		guiManager.AddStyle(separation2, OFX_IM_DEFAULT);

		//guiManager.AddStyle(lineWidth2, OFX_IM_HSLIDER, 2, true);
		//guiManager.AddStyle(separation2, OFX_IM_HSLIDER, 2, false);
		// 2 widgets per row. sameline for the next
		// 2 widgets per row. not sameline for the next
	}

	if (bEnable3) {
		guiManager.AddStyleGroup(params3, OFX_IM_GROUP_COLLAPSED, ImGuiTreeNodeFlags_DefaultOpen);
	}
	else {
		guiManager.AddStyleGroup(params3, OFX_IM_GROUP_HIDDEN, ImGuiTreeNodeFlags_DefaultOpen);
	}

	if (bEnable4) {
		guiManager.AddStyleGroup(params4, OFX_IM_GROUP_COLLAPSED, ImGuiTreeNodeFlags_DefaultOpen);

		guiManager.AddStyle(lineWidth4, OFX_IM_HSLIDER_NO_NAME, 2, true);
		guiManager.AddStyle(separation4, OFX_IM_HSLIDER_NO_NAME, 2, false);
		// 2 widgets per row. sameline for the next
		// 2 widgets per row. not sameline for the next

		guiManager.AddStyle(shapeType4, OFX_IM_VSLIDER, 1, false, 20);
		// 1 widget per row. not sameline for the next and 20 y pixels spacing at end
	}
	else {
		guiManager.AddStyleGroup(params4, OFX_IM_GROUP_TREE, ImGuiTreeNodeFlags_DefaultOpen);

		guiManager.AddStyle(lineWidth4, OFX_IM_KNOB, 2, true);
		guiManager.AddStyle(separation4, OFX_IM_KNOB, 2, false);
		// 2 widgets per row. sameline for the next
		// 2 widgets per row. not sameline for the next

		guiManager.AddStyle(shapeType4, OFX_IM_HSLIDER, 1, false, 20);
		// 1 widget per row. not sameline for the next and 20 y pixels spaning at end

		guiManager.AddStyle(speed3, OFX_IM_HSLIDER_NO_NAME);
		guiManager.AddStyle(shapeType3, OFX_IM_HSLIDER_NO_NAME);

	}

	//-

	// 2. For Groups / headers / trees

	// WARNING:

	// Notice that:
	// Some flags may be not be supported/combined for some tree types.
	// ie: OFX_IM_GROUP_TREE maybe can not be with ImGuiTreeNodeFlags_DefaultOpen. 
	// and the tree will be closed by default. 
	// That's bc ImGui::TreeNode has no flags, but (when passing ImGuiTreeNodeFlags_DefaultOpen)
	// we are using an internal workaround doing:
	// bool bOpen = true;
	// ImGui::SetNextTreeNodeOpen(bOpen, ImGuiCond_Appearing);

	// Notice that:
	// Nested groups can heritate flags/types from parent ones.
	// Then, in most cases, it's recommended to define all the flags for each group style!

	//guiManager.AddStyleGroup(params1, OFX_IM_GROUP_TREE_EX, ImGuiTreeNodeFlags_DefaultOpen);
	//guiManager.AddStyleGroup(params1, OFX_IM_GROUP_COLLAPSED, ImGuiTreeNodeFlags_DefaultOpen);
	//guiManager.AddStyleGroup(params1, OFX_IM_GROUP_HIDDEN_HEADER, ImGuiTreeNodeFlags_None);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		// 1. Toggle Section Enablers Window
		{
			// Notice that if you use ImGui Raw begin/end methods to create window panels,
			// some widget helpers can be used, but not all. 
			// In this case will made crash the app if you use guiManager.Add(..
			// But it will work if you use ofxImGuiSurfing::AddToggleRoundedButton(..
			// --> *
			//ImGui::Begin("Enablers"); 
			
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			guiManager.beginWindow(ofToString("Enablers"), NULL, window_flags);
			{
				for (int i = 0; i < NUM_SECTIONS; i++)
				{
					guiManager.Add(bEnablers[i], OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM);

					// -> *
					//ofxImGuiSurfing::AddToggleRoundedButton(bEnablers[i]);
				}

				ImGui::Spacing();

				//--------------------------------------------------------------

				// An extra advanced / sub-panel 

				// with some common toggles that we must customize/assign destinations.
				{
					guiManager.drawAdvanced(true);
				}
			}
			guiManager.endWindow();

			// -> *
			//ImGui::End();
		}

		//--------

		// 2. ofApp Window
		{
			//TODO:
			// not working..
			if (guiManager.bReset_Window) {
				guiManager.bReset_Window = false;
				guiManager.resetWindowImGui(true, true);
			}

			//-

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
			if (guiManager.bLockMove) window_flags |= ImGuiWindowFlags_NoMove;
			if (guiManager.bNoScroll) window_flags |= ImGuiWindowFlags_NoScrollbar;

			guiManager.beginWindow("ofApp", NULL, window_flags);
			{
				//--------------------------------------------------------------

				//TODO:
				// TESTING
				// New Range Sliders
				if (bEnablers[0])
				{
					int max = 10000;
					int min = 1;
					static int ilow = 1, ihigh = 5000;
					static int ilow1 = 1, ihigh1 = 5000;
					static int ilow2 = 2, ihigh2 = 5000;
					static float flow = 1, fhigh = 5000;
					static float flow1 = 1, fhigh1 = 5000;
					static float flow2 = 1, fhigh2 = 5000;
					ImGui::RangeSliderInt("CMDS", min, max, ilow, ihigh);
					ImGui::RangeSliderInt("CMDS1", min, max, ilow1, ihigh1);
					ImGui::RangeSliderInt("CMDS2", min, max, ilow2, ihigh2);
					ImGui::RangeSliderFloat("CMDS3f", min, max, flow2, fhigh2);
					ImGui::RangeSliderFloat("CMDS4f", min, max, flow1, fhigh1);
					ImGui::RangeSliderFloat("CMDS5f", min, max, flow, fhigh);

					//ofxImGuiSurfing::AddSpacingSeparated();
				}

				//--------------------------------------------------------------

				// Ranges for multidim glm::vec

				if (bEnablers[1])
				{
					guiManager.refreshLayout();

					static ofParameter<int> coord{ "coord", 0, 0, 2 };
					ofxImGuiSurfing::AddParameter(coord);

					ofxImGuiSurfing::AddParameter(value);
					ofxImGuiSurfing::AddParameter(valueMin);
					ofxImGuiSurfing::AddParameter(valueMax);

					float _h = ofxImGuiSurfing::getWidgetsHeightUnit();
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

					ofxImGuiSurfing::AddRangeOneVec3Param("RangePos", pos_1, valueMin, valueMax, value, coord.get());
					//ImGui::SameLine();
					//ImGui::Text("asdf");

					//ofxImGuiSurfing::AddSpacingSeparated();
				}

				//--------------------------------------------------------------

				// A Multidim (xyz) vec2/vec3/vec4 parameter 

				if (bEnablers[2])
				{
					ImGui::Spacing();

					// Two api patterns can be used:
					guiManager.Add(pos_1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
					//ofxImGuiSurfing::AddParameter(pos_1, true);

					//ofxImGuiSurfing::AddSpacingSeparated();
				}

				//--------------------------------------------------------------

				// Basic folder

				if (bEnablers[3])
				{
					if (ImGui::TreeNode("Tree"))
					{
						guiManager.Add(bEnable1);
						guiManager.Add(bEnable2);
						guiManager.Add(bEnable3);

						ImGui::TreePop();
					}

					//ofxImGuiSurfing::AddSpacingSeparated();
				}

				//--------------------------------------------------------------

				// An ofParameterGroup with monested Groups with params

				//if (0)
				if (bEnablers[4])
				{
					static bool bOpen = false;
					ImGui::SetNextTreeNodeOpen(bOpen, ImGuiCond_Appearing);

					guiManager.AddGroup(params1);

					//ofxImGuiSurfing::AddSpacingSeparated();
				}

				//--------------------------------------------------------------

				// Three rounded toggles

				if (bEnablers[5])
				{
					ofxImGuiSurfing::AddToggleRoundedButton(bPrevious);
					ImGui::SameLine();
					ofxImGuiSurfing::AddToggleRoundedButton(bNext);
					ImGui::SameLine();
					ofxImGuiSurfing::AddToggleRoundedButton(bEnable1);

					//ofxImGuiSurfing::AddSpacingSeparated();
				}

				//--------------------------------------------------------------

				// Vertica/Horizontal Big Sliders

				if (bEnablers[6])
				{
					if (ImGui::TreeNodeEx("Vert/Horiz Sliders", ImGuiTreeNodeFlags_DefaultOpen))
					{
						guiManager.refreshLayout();

						ImGui::TextWrapped("Float and Int ofParameters \ncan be directly rendered as ImGui Widgets \n");
						ImGui::TextWrapped("Try to resize the window panel \nto see the responsive layouting.. \n");

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::Spacing();

						if (ImGui::TreeNodeEx("Raw Mode without Styles Engine"))
						{
							ImGui::TextWrapped("> No Responsive! No Mouse Wheel!\n");

							float w = 40;
							float h = 80;
							ofxImGuiSurfing::AddVSlider(speed3, ImVec2(w, h), true);
							ImGui::SameLine();
							ofxImGuiSurfing::AddVSlider(speed4, ImVec2(w, h), true);
							ImGui::SameLine();
							ofxImGuiSurfing::AddVSlider(size3, ImVec2(w, h), true);
							ImGui::SameLine();
							ofxImGuiSurfing::AddVSlider(size4, ImVec2(w, h), true);

							ImGui::TreePop();
						}
						ofxImGuiSurfing::AddSpacingSeparated();

						//TODO:
						// Must improve the widgets.
						// this is a workaround
						// Using columns to mantain alignment
						ImGui::TextWrapped("> Four Vertical Sliders \n");
						ImGui::Spacing();
						ImGui::Columns(4, "_bigSliders", false);
						guiManager.Add(speed3, OFX_IM_VSLIDER, 4, true);
						ImGui::NextColumn();
						guiManager.Add(speed4, OFX_IM_VSLIDER, 4, true);
						ImGui::NextColumn();
						guiManager.Add(size3, OFX_IM_VSLIDER, 4, true);
						ImGui::NextColumn();
						guiManager.Add(size4, OFX_IM_VSLIDER, 4, false);
						ImGui::Columns(1);

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::TextWrapped("> Four Vertical Sliders \nNo Name \n");
						ImGui::Spacing();
						guiManager.Add(speed3, OFX_IM_VSLIDER_NO_NAME, 4, true);
						guiManager.Add(speed4, OFX_IM_VSLIDER_NO_NAME, 4, true);
						guiManager.Add(size3, OFX_IM_VSLIDER_NO_NAME, 4, true);
						guiManager.Add(size4, OFX_IM_VSLIDER_NO_NAME, 4, false);

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::TextWrapped("> Four Horizontal Sliders \n");
						guiManager.Add(speed3, OFX_IM_HSLIDER_NO_NAME);
						guiManager.Add(speed4, OFX_IM_HSLIDER_NO_LABELS);
						guiManager.Add(size3, OFX_IM_HSLIDER_SMALL_NO_NUMBER);
						guiManager.Add(size4, OFX_IM_HSLIDER_SMALL);

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::TextWrapped("> Two Horizontal Sliders \nWithout Labels in One Row \n");
						guiManager.Add(speed3, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, true);
						guiManager.Add(speed4, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, false);

						ofxImGuiSurfing::AddSpacingSeparated();

						ImGui::TextWrapped("> Four Knobs \n");
						ImGui::Spacing();
						guiManager.Add(speed3, OFX_IM_KNOB, 4, true);
						guiManager.Add(speed4, OFX_IM_KNOB, 4, true);
						guiManager.Add(size3, OFX_IM_KNOB, 4, true);
						guiManager.Add(size4, OFX_IM_KNOB, 4, false);

						ImGui::TreePop();
					}
				}

				//--------------------------------------------------------------
			}
			guiManager.endWindow();
		}
	}
	guiManager.end();
}
