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
	{
		int sz = (int)SurfingImGuiTypesGroups::OFX_IM_GROUP_NUM_TYPES - 1;
		typeFlags.set("typeFlags", 1, 0, 4);
		typeGroups.set("typeGroups", 0, 0, sz);
	}

	//-

	// windows
	bOpenMain = true;
	bOpen1 = true;
	bOpen2 = true;

	//-

	// prepare parameters

	params1.setName("paramsGroup1");
	params2.setName("paramsGroup2");
	params3.setName("paramsGroup3");

	bEnable.set("Enable", false);
	shapeType.set("shapeType", 0, -50, 50);

	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));
	//params1.add(shapeType);
	//params1.add(bEnable);

	params3.add(separation3min.set("separation3min", 25.f, 1, 100));
	params3.add(separation3max.set("separation3max", 75.f, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(bEnable);

	params1.add(params3);

	//-

	params2.add(bMode1.set("Mode1", false));
	params2.add(bMode2.set("Mode2", false));
	params2.add(bMode3.set("Mode3", false));
	params2.add(bMode4.set("Mode4", false));
	params2.add(bModeA.set("ModeA", false));
	params2.add(bModeB.set("ModeB", false));
	params2.add(bModeC.set("ModeC", false));
	params2.add(bModeD.set("ModeD", false));
	params2.add(bPrevious.set("<", false));
	params2.add(bNext.set(">", false));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params2.add(bEnable);

	//--

	guiManager.setImGuiAutodraw(true);
	guiManager.setup(); // this instantiates and configures ofxImGui inside the class object.

	//-

	// Queue widgets styles to customize when they will be drawn inside an ofParameterGroup
	// If the parameter widget is not added explicitly, will be populated with the default appearance.

	// NOTE:
	// This added style conf will be applied in all the appearances of the param widgets inside all groups.
	// We can overwrite this customization only draing the simple param "by hand".
	// ie:
	// guiManager.Add(bMode3, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 3, 2);+

	//-

	// -> not checked on runtime! ONLY ON SETUP
	if (bCustom2) {
		SetupStyles();
	}
	else {
		ClearStyles();
	}

	guiManager.bAutoResize = false;
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

	//// A. two widgets same line small
	//guiManager.AddStyle(bPrevious, SurfingImGuiTypes::OFX_IM_BUTTON_SMALL, true, 2);
	//guiManager.AddStyle(bNext, SurfingImGuiTypes::OFX_IM_BUTTON_SMALL, false, 2, 10);
	// B. two widgets same line big
	guiManager.AddStyle(bPrevious, SurfingImGuiTypes::OFX_IM_BUTTON_BIG, true, 2);
	guiManager.AddStyle(bNext, SurfingImGuiTypes::OFX_IM_BUTTON_BIG, false, 2, 10);

	guiManager.AddStyle(shapeType2, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(size2, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(amount2, SurfingImGuiTypes::OFX_IM_DRAG, false, 2, 10);

	// more widgets
	guiManager.AddStyle(lineWidth3, SurfingImGuiTypes::OFX_IM_STEPPER);
	guiManager.AddStyle(speed3, SurfingImGuiTypes::OFX_IM_DRAG);

	//enable this to disable mouse interaction for these widgets
	//guiManager.AddStyle(separation3min, SurfingImGuiTypes::OFX_IM_INACTIVE);
	//guiManager.AddStyle(separation3max, SurfingImGuiTypes::OFX_IM_INACTIVE, false, 10);
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

	guiManager.begin();
	{
		if (bOpenMain) drawWindowMain();
		if (bOpen1) drawWindow1();
		if (bOpen2) drawWindow2();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawWindowMain() {

	// window main
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		// reset window
		{
			if (bReset1)
			{
				bReset1 = false;
				bReset2 = true;
				ImGuiCond flag = ImGuiCond_Always;
				ImGui::SetNextWindowPos(ImVec2(10, 10));
				ImGui::SetNextWindowSize(ImVec2(200, (float)MAX_WINDOW_HEIGHT));
			}
		}

		//-

		ImGui::Begin("Show Windows");
		{
			if (ImGui::Button("Reset Layout", ofxImGuiSurfing::getWidgetsShapeSmall()))
			{
				bReset1 = true;
			}

			ImGui::Dummy(ImVec2(0, 5));

			// round toggles
			ToggleRoundedButton("Show Window 1", &bOpen1);
			ToggleRoundedButton("Show Window 2", &bOpen2);

			ImGui::Dummy(ImVec2(0, 5));

			AddToggleRoundedButton(guiManager.bAutoResize, ImVec2(50, 30));

			ImGui::Dummy(ImVec2(0, 150)); // spacing

			//----

			ImGui::Text("DEBUG STYLES TYPES");

			ImGui::Dummy(ImVec2(0, 10)); // spacing
			ImGui::Separator();
			ImGui::Dummy(ImVec2(0, 10)); // spacing

			//-

			ToggleRoundedButton("bCustom1", &bCustom1);
			if (bCustom1) ImGui::TextWrapped("Customized style for some ofParams Widgets");
			else ImGui::TextWrapped("Default Style for ofParams Widgets");

			ImGui::Dummy(ImVec2(0, 5)); // spacing
			ImGui::Separator();
			ImGui::Dummy(ImVec2(0, 5)); // spacing

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
			if (bCustom2) ImGui::TextWrapped("Customized Style for Window 2 Group.");
			else ImGui::TextWrapped("Default Style for Window 2 Group.");

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

			// get position
			{
				auto posx = ImGui::GetWindowPos().x;
				auto posy = ImGui::GetWindowPos().y;
				float __w = ImGui::GetWindowWidth();
				float __h = ImGui::GetWindowHeight();
				pos0.x = posx + __w + PADDING_PANELS;
				pos0.y = posy;
			}

			//-

			// testing

			ofxImGuiSurfing::AddSpaceY(10);

			AddToggleRoundedButton(bEnable, ImVec2(50, 30));

		}
		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::drawWindow1() {

	// window 1
	{
		// a window but using my ofxSurfing_ImGui_LayoutManager.h class helper

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		// reset window
		{
			if (bReset2)
			{
				bReset2 = false;
				bReset3 = true;
				ImGuiCond flag = ImGuiCond_Always;
				ImGui::SetNextWindowPos(ImVec2(pos0.x, pos0.y), flag);
				ImGui::SetNextWindowSize(ImVec2(200, (float)MAX_WINDOW_HEIGHT));
			}
		}

		guiManager.beginWindow("Window 1", &bOpen1, window_flags);
		{
			//--

			// using widgets

			// 0. Default bool param
			ofxImGuiSurfing::AddParameter(bEnable);

			ImGui::Dummy(ImVec2(0, 10)); // spacing

			//-

			// 2. Parameters inside an ofParameterGroup
			// queue params configs to populate after when drawing they container group
			{
				guiManager.AddGroup(params1, flags_typeFlags, SurfingImGuiTypesGroups(typeGroups.get()));

				//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
				//flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
				//flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed
				//ofxImGuiSurfing::AddGroup(params1, flags);
			}

			//-

			ImGui::Dummy(ImVec2(0, 10)); // spacing

			// 1. Single parameters (out of a paramGroup)
			// instant populate customized widgets

			// A
			if (bCustom1)
			{
				guiManager.refresh();

				ImGui::Text("* bCustom1 = true");
				ImGui::Text("customized");
				ImGui::Dummy(ImVec2(0, 5)); // spacing

				// This is the defalut helpers ussage for the official ofxImGui Helpers:
				//ofxImGuiSurfing::AddParameter(lineWidth); 
				// (Notice that this will be affected if there's an added conf (AddStyle) for this param)

				// 1.0.1
				//ofxImGuiSurfing::AddParameter(bMode4);
				// 1.0.2
				// This forces the style no matter if a conf is added (AddStyle) for this param
				guiManager.Add(bModeA, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG); // -> now this is the default bool 
				guiManager.Add(bModeA, SurfingImGuiTypes::OFX_IM_CHECKBOX); // -> deprecated check box as default bool

				// 1.1 Toggle full width
				guiManager.Add(bModeB, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG);

				// 1.2 A float param
				guiManager.Add(lineWidth, SurfingImGuiTypes::OFX_IM_SLIDER); // force draw
				guiManager.Add(lineWidth, SurfingImGuiTypes::OFX_IM_DRAG);
				guiManager.Add(lineWidth, SurfingImGuiTypes::OFX_IM_STEPPER, false, 2, 20); // crashes?

				// 1.3 Three small toggle widgets in one row
				// with 20px vert spacing at end
				//guiManager.refresh(); // update sizes to current window shape
				guiManager.Add(bModeA, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, true, 3);
				guiManager.Add(bModeB, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, true, 3);
				guiManager.Add(bModeC, SurfingImGuiTypes::OFX_IM_TOGGLE_SMALL, false, 3, 2);
				guiManager.Add(bModeD);
			}

			// B
			// default ofxImGui styles
			else
			{
				ImGui::Text("* bCustom1 = false");
				ImGui::Text("default style");
				ImGui::Dummy(ImVec2(0, 5)); // spacing

				ofxImGuiSurfing::AddParameter(bModeA);
				ofxImGuiSurfing::AddParameter(bModeA);
				ofxImGuiSurfing::AddParameter(bModeB);

				ofxImGuiSurfing::AddParameter(lineWidth);
				ofxImGuiSurfing::AddParameter(lineWidth);
				ofxImGuiSurfing::AddParameter(lineWidth);

				ofxImGuiSurfing::AddParameter(bModeA);
				ofxImGuiSurfing::AddParameter(bModeB);
				ofxImGuiSurfing::AddParameter(bModeC);
				ofxImGuiSurfing::AddParameter(bModeD);
			}

			//-

			// get position
			{
				auto posx = ImGui::GetWindowPos().x;
				auto posy = ImGui::GetWindowPos().y;
				float __w = ImGui::GetWindowWidth();
				float __h = ImGui::GetWindowHeight();
				pos1.x = posx + __w + PADDING_PANELS;
				pos1.y = posy;
			}
		}
		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawWindow2() {

	// window 2
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		// reset window
		{
			if (bReset3)
			{
				bReset3 = false;
				ImGuiCond flag = ImGuiCond_Always;
				ImGui::SetNextWindowPos(ImVec2(pos1.x, pos1.y), flag);
				ImGui::SetNextWindowSize(ImVec2(200, (float)MAX_WINDOW_HEIGHT));
			}
		}

		//-

		// A. without flags (default)
		guiManager.beginWindow("Window 2", &bOpen2, window_flags);
		{
			if (bCustom2) {
				ImGui::Text("* bCustom2 = true");
				ImGui::Text("customized");
				ImGui::Dummy(ImVec2(0, 5)); // spacing
			}
			else {
				ImGui::Text("* bCustom2 = false");
				ImGui::Text("default style");
				ImGui::Dummy(ImVec2(0, 5)); // spacing
			}

			guiManager.AddGroup(params2, flags_typeFlags, SurfingImGuiTypesGroups(typeGroups.get()));

			//-

			/*
			// B. using flags
			{
				// group parameter with customized tree/folder type
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
				flags |= ImGuiTreeNodeFlags_Framed;
				flags |= ImGuiTreeNodeFlags_DefaultOpen;

				ofxImGuiSurfing::AddGroup(params2, flags);
			}
			*/

			//-

			// extra. 
			// Another widgets pack
			{
				static bool bMore = false;
				//ImGui::Dummy(ImVec2(0, 20)); // spacing
				ofxImGuiSurfing::AddSpaceY(); // simplified above Dummy
				ImGui::Separator();
				ofxImGuiSurfing::AddSpaceY();
				ImGui::Text("MORE WIDGETS");
				ofxImGuiSurfing::AddSpaceY(5);
				ofxImGuiSurfing::ToggleRoundedButton("Draw", &bMore);

				if (bMore) drawMoreWidgets();
			}

			//// 1.4 spacing
			//ImGui::Dummy(ImVec2(0, 10)); // spacing

			//// 1.5 A row of four big toggles
			//guiManager.Add(bMode1, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 4);
			//guiManager.Add(bMode2, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 4);
			//guiManager.Add(bMode3, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 4);
			//guiManager.Add(bMode4, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, false, 4);

		}
		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawMoreWidgets() {

	// All below these are pure params widgets without window/tree/group/container

	//-

	ImGui::Text("Range Sliders | ofParameters");

	AddRangeParam("separation3", separation3min, separation3max, "%.3f  %.3f", 1.0f);

	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	//-

	// add an ofParameterGroup

	ImGui::Text("An ofParameterGroup | params3");

	//// Rememeber the "old" notation from original ofxGui:
	//auto mainSettings = ofxImGui::Settings();
	//ofxImGui::AddGroup(params3, mainSettings);

	//-

	// currently we can customize the tree/group types passing tree flags, 
	// and also these Surfing styles from "ofxSurfing_ImGui_WidgetsTypesConstants.h"

	//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	//flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
	//flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed
	//guiManager.AddGroup(params3, flags, SurfingImGuiTypesGroups::OFX_IM_GROUP_DEFAULT);

	// we will use the gui selectable debugger styles
	guiManager.AddGroup(params3, typeFlags, SurfingImGuiTypesGroups(typeGroups.get()));

	// spacing
	ofxImGuiSurfing::AddSpaceY(20);

	//-

	// some custom widgets

	ImGui::Text("Range Sliders | int/float types");

	// range_slider.h
	static float v1 = 0;
	static float v2 = 1;
	static float v_min = 0;
	static float v_max = 1;
	static float v3 = 0;
	static float v4 = 1;
	ofxImGuiSurfing::RangeSliderFloat("Range 1", &v1, &v2, v_min, v_max, "%.1f  %.1f", 1.0f);
	ofxImGuiSurfing::RangeSliderFloat("Range 2", &v3, &v4, v_min, v_max);

	// float/int types
	// vanilla range slider
	static float begin = 10, end = 90;
	static int begin_i = 100, end_i = 1000;
	ImGui::DragFloatRange2("Range 3", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
	ImGui::DragIntRange2("Range 4", &begin_i, &end_i, 5, 0, 0, "%.0fcm", "%.0fcm");

	ImGui::Dummy(ImVec2(0.0f, 2.0f));

	//-

	if (bCustom1)
	{
		// A row of four big toggles
		ImGui::Text("* bCustom1 = true");
		ImGui::Text("customized");
		ImGui::Dummy(ImVec2(0, 5)); // spacing

		guiManager.Add(bModeA, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 4);
		guiManager.Add(bModeB, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 4);
		guiManager.Add(bModeC, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, true, 4);
		guiManager.Add(bModeD, SurfingImGuiTypes::OFX_IM_TOGGLE_BIG, false, 4);
	}
	else // default ofxImGui styles
	{
		ImGui::Text("* bCustom1 = false");
		ImGui::Text("default style");
		ImGui::Dummy(ImVec2(0, 5)); // spacing

		ofxImGuiSurfing::AddParameter(bModeA);
		ofxImGuiSurfing::AddParameter(bModeB);
		ofxImGuiSurfing::AddParameter(bModeC);
		ofxImGuiSurfing::AddParameter(bModeD);
	}
}
