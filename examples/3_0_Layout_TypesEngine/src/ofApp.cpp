#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	//-

	// debug custom types
	bCustom1 = 0; // inmediate customized when populating
	bCustom2 = 1; // constant. pre configured to customize after (ie: inside a group)

	//-

	// debug ImGui flags
	{
		int sz = (int)SurfingTypes::SurfingTypesGroups::OFX_IM_GROUP_NUM_TYPES - 1;
		typeGroups.set("typeGroups", 0, 0, sz);
		typeFlags.set("typeFlags", 1, 0, 4);
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

	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));
	params1.add(bEnable);

	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
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
	// widgetsManager.Add(bMode3, SurfingTypes::OFX_IM_TOGGLE_SMALL, false, 3, 2);+

	if (bCustom2) // -> not checked on runtime! ONLY ON SETUP
	{
		widgetsManager.clear(); // TODO: -> call from beginWindow/group

		widgetsManager.AddStyle(shapeType2, SurfingTypes::OFX_IM_STEPPER);
		widgetsManager.AddStyle(size2, SurfingTypes::OFX_IM_STEPPER);
		widgetsManager.AddStyle(amount2, SurfingTypes::OFX_IM_DRAG);

		widgetsManager.AddStyle(bEnable, SurfingTypes::OFX_IM_TOGGLE_BIG_XXL, false, 1, 10);

		// two widgets same line small
		widgetsManager.AddStyle(bPrevious, SurfingTypes::OFX_IM_BUTTON_SMALL, true, 2);
		widgetsManager.AddStyle(bNext, SurfingTypes::OFX_IM_BUTTON_SMALL, false, 2, 10);

		// two widgets same line big
		//widgetsManager.AddStyle(bPrevious, SurfingTypes::OFX_IM_BUTTON_BIG, true, 2);
		//widgetsManager.AddStyle(bNext, SurfingTypes::OFX_IM_BUTTON_BIG, false, 2, 10);

		// two widgets same line
		widgetsManager.AddStyle(bMode1, SurfingTypes::OFX_IM_TOGGLE_BIG, true, 2);
		widgetsManager.AddStyle(bMode2, SurfingTypes::OFX_IM_TOGGLE_BIG, false, 2);
		// two widgets same line
		widgetsManager.AddStyle(bMode3, SurfingTypes::OFX_IM_TOGGLE_BIG, true, 2);
		widgetsManager.AddStyle(bMode4, SurfingTypes::OFX_IM_TOGGLE_BIG, false, 2);

		// more widgets
		widgetsManager.AddStyle(lineWidth3, SurfingTypes::OFX_IM_STEPPER);
		widgetsManager.AddStyle(speed3, SurfingTypes::OFX_IM_DRAG);
		widgetsManager.AddStyle(separation3, SurfingTypes::OFX_IM_INACTIVE);
		//widgetsManager.AddStyle(separation3, SurfingTypes::OFX_IM_STEPPER);

		//// hide some params from any on-param-group appearance
		//widgetsManager.AddStyle(speed3, SurfingTypes::OFX_IM_HIDDEN, false, -1, 20);
		//widgetsManager.AddStyle(size2, SurfingTypes::OFX_IM_HIDDEN, false, -1, 20);
		//widgetsManager.AddStyle(bPrevious, SurfingTypes::OFX_IM_HIDDEN);
		//widgetsManager.AddStyle(bNext, SurfingTypes::OFX_IM_HIDDEN);
		//widgetsManager.AddStyle(lineWidth, SurfingTypes::OFX_IM_HIDDEN);
		//widgetsManager.AddStyle(lineWidth, SurfingTypes::OFX_IM_DRAG); // not works?
		//widgetsManager.AddStyle(separation, SurfingTypes::OFX_IM_STEPPER);
		//widgetsManager.AddStyle(separation, SurfingTypes::OFX_IM_STEPPER);
		//widgetsManager.AddStyle(speed, SurfingTypes::OFX_IM_DRAG, false, 1, 10);
		//widgetsManager.AddStyle(shapeType, SurfingTypes::OFX_IM_DRAG);
		//widgetsManager.AddStyle(size, SurfingTypes::OFX_IM_STEPPER);
		//widgetsManager.AddStyle(amount, SurfingTypes::OFX_IM_DRAG, false, 1, 10);
	}

	guiManager.bAutoResize = false;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		//TODO:
		// trying a workaround to fix getUniqueName troubles..
		//ofxImGuiSurfing::resetIndex();

		//-

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
				ImGui::SetNextWindowSize(ImVec2(200, 900));
			}
		}

		//static bool no_close = true;
		//if (no_close) ImGui::Begin("Show Windows", NULL, window_flags);
		//else ImGui::Begin("Show Windows", &bOpenMain, window_flags);

		ImGui::Begin("Show Windows");
		{
			if (ImGui::Button("Reset Layout", ofxImGuiSurfing::getWidgetsShapeSmall()))
			{
				bReset1 = true;
			}

			ImGui::Dummy(ImVec2(0, 5));

			// round toggles
			//ToggleRoundedButton("Avoid Close", &no_close);
			ToggleRoundedButton("Show Window 1", &bOpen1);
			ToggleRoundedButton("Show Window 2", &bOpen2);

			//ImGui::Dummy(ImVec2(0, 5));

			AddToggleRoundedButton(guiManager.bAutoResize, ImVec2(50, 30));

			ImGui::Dummy(ImVec2(0, 30)); // spacing

			//-

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

			ToggleRoundedButton("bCustom2", &bCustom2); // readed on setup only, cant be updated on runtime
			ImGui::TextWrapped("Custom Style for Window 2 Group. Only called at setup()!!");

			//-

			ImGui::Dummy(ImVec2(0, 5)); // spacing
			ImGui::Separator();
			ImGui::Dummy(ImVec2(0, 5)); // spacing

			ImGui::TextWrapped("Customize Styles for Groups/Trees");

			// debug ImGui flags
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
				float pad = 0;
				auto posx = ImGui::GetWindowPos().x;
				auto posy = ImGui::GetWindowPos().y;
				float __w = ImGui::GetWindowWidth();
				float __h = ImGui::GetWindowHeight();
				pos0.x = posx + __w + pad;
				pos0.y = posy;
			}

			//-

			// testing

			//ImGui::Dummy(ImVec2(0, 10)); // spacing
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
				ImGui::SetNextWindowSize(ImVec2(200, 900));
			}
		}

		guiManager.beginWindow("Window 1", &bOpen1, window_flags);
		{
			// Update sizes to current window shape.
			// Warning! Must be called before we use the above API widgetsManager.Add(.. methods!
			// This is to calculate the widgets types sizes to current panel window size.
			widgetsManager.refreshPanelShape();

			//--

			// using widgets

			// 0. Default bool param
			ofxImGuiSurfing::AddParameter(bEnable);

			ImGui::Dummy(ImVec2(0, 10)); // spacing

			//-

			/*
			// 2. Parameters inside an ofParameterGroup
			// queue params configs to populate after when drawing they container group
			{
				// group of parameters with customized tree/folder type
				// will be applied to all nested groups inside this parent
				// customization is defined above on setup(): widgetsManager.AddStyle(..

				//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
				//flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
				//flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed
				//ofxImGuiSurfing::AddGroup(params1, flags);

				// debug ImGui flags
				{
					// A group of parameters with customized tree/folder types
					// will be applied to all the nested groups inside this parent/root ofParameterGroup
					ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
					if (typeFlags == 0) { flagInfo = "ImGuiTreeNodeFlags_None"; }
					if (typeFlags == 1) { flagInfo = "ImGuiTreeNodeFlags_DefaultOpen"; flags |= ImGuiTreeNodeFlags_DefaultOpen; } // to start closed
					if (typeFlags == 2) { flagInfo = "ImGuiTreeNodeFlags_Framed"; flags |= ImGuiTreeNodeFlags_Framed; } // to draw dark tittle bar
					if (typeFlags == 3) { flagInfo = "ImGuiTreeNodeFlags_Bullet"; flags |= ImGuiTreeNodeFlags_Bullet; } // bullet mark
					if (typeFlags == 4) { flagInfo = "ImGuiTreeNodeFlags_NoTreePushOnOpen"; flags |= ImGuiTreeNodeFlags_NoTreePushOnOpen; } // no push

					//ofxImGuiSurfing::AddGroup(params3, flags, SurfingTypesGroups(typeGroups.get()));
					ofxImGuiSurfing::AddGroup(params1, flags, SurfingTypesGroups(typeGroups.get()));
				}
			}
			*/


			//-

			ImGui::Dummy(ImVec2(0, 10)); // spacing

			// 1. Single parameters (out of a paramGroup)
			// instant populate customized widgets

			// A
			if (bCustom1)
			{
				ImGui::Text("* bCustom1 = true");
				ImGui::Text("customized");

				// This is the defalut helpers ussage for the official ofxImGui Helpers:
				//ofxImGuiSurfing::AddParameter(lineWidth); 
				// (Notice that this will be affected if there's an added conf (AddStyle) for this param)

				// 1.0 A check box

				// These lines with draw/render the same style widgets:
				// 1.0.1
				//ofxImGuiSurfing::AddParameter(bMode4);
				// 1.0.2
				// This forces the style no matter if a conf is added (AddStyle) for this param
				widgetsManager.Add(bModeA, SurfingTypes::OFX_IM_BUTTON_BIG); // -> now this is the default bool 
				//widgetsManager.Add(bModeA, SurfingTypes::OFX_IM_CHECKBOX); // -> deprecated check box as default bool

				// 1.1 Toggle full width
				widgetsManager.Add(bModeB, SurfingTypes::OFX_IM_TOGGLE_BIG);

				// 1.2 A float param
				widgetsManager.Add(lineWidth, SurfingTypes::OFX_IM_SLIDER); // force draw
				widgetsManager.Add(lineWidth, SurfingTypes::OFX_IM_DRAG);
				widgetsManager.Add(lineWidth, SurfingTypes::OFX_IM_STEPPER, false, 2, 20); // crashes?

				// 1.3 Three small toggle widgets in one row
				// with 20px vert spacing at end
				//widgetsManager.refreshPanelShape(); // update sizes to current window shape
				widgetsManager.Add(bModeA, SurfingTypes::OFX_IM_TOGGLE_SMALL, true, 3);
				widgetsManager.Add(bModeB, SurfingTypes::OFX_IM_TOGGLE_SMALL, true, 3);
				widgetsManager.Add(bModeC, SurfingTypes::OFX_IM_TOGGLE_SMALL, false, 3, 2);
				widgetsManager.Add(bModeD);
			}

			// B
			// default ofxImGui styles
			else
			{
				ImGui::Text("* bCustom1 = false");
				ImGui::Text("default style");

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
				float pad = 0;
				auto posx = ImGui::GetWindowPos().x;
				auto posy = ImGui::GetWindowPos().y;
				float __w = ImGui::GetWindowWidth();
				float __h = ImGui::GetWindowHeight();
				pos1.x = posx + __w + pad;
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
				ImGui::SetNextWindowSize(ImVec2(200, 900));
			}
		}

		//-

		// A. without flags (default)
		guiManager.beginWindow("Window 2", &bOpen2, window_flags);
		{
			ofxImGuiSurfing::AddGroup(params2);

			//-

			/*
			// B. using flags
			{
				// workaround
				// do not updates for below group.
				// inside AddGroup. Could be related to static widgetsManager instantiation..
				// Must call:
				widgetsManager.refreshPanelShape();

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
				ImGui::Dummy(ImVec2(0, 20)); // spacing
				ImGui::Separator();
				ImGui::Dummy(ImVec2(0, 20)); // spacing
				ImGui::Text("MORE WIDGETS");
				ofxImGuiSurfing::ToggleRoundedButton("Draw", &bMore);
				if (bMore) drawMoreWidgets();
			}

		}
		guiManager.endWindow();

		//// 1.4 spacing
		//ImGui::Dummy(ImVec2(0, 10)); // spacing

		//// 1.5 A row of four big toggles
		//widgetsManager.Add(bMode1, SurfingTypes::OFX_IM_TOGGLE_BIG, true, 4);
		//widgetsManager.Add(bMode2, SurfingTypes::OFX_IM_TOGGLE_BIG, true, 4);
		//widgetsManager.Add(bMode3, SurfingTypes::OFX_IM_TOGGLE_BIG, true, 4);
		//widgetsManager.Add(bMode4, SurfingTypes::OFX_IM_TOGGLE_BIG, false, 4);
	}
}

//--------------------------------------------------------------
void ofApp::drawMoreWidgets() {

	// these are pure widgets without window/tree/container

	// add an ofParameterGroup

	// A
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
	flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed
	ofxImGuiSurfing::AddGroup(params3, flags);

	//// B
	//auto mainSettings = ofxImGui::Settings();
	//ofxImGui::AddGroup(params3, mainSettings);

	// spacing
	ImGui::Dummy(ImVec2(0.0f, 2.0f));// spacing

	//-

	// some custom widgets

	// range_slider.h
	static float v1 = 0;
	static float v2 = 1;
	static float v_min = 0;
	static float v_max = 1;
	static float v3 = 0;
	static float v4 = 1;
	ofxImGuiSurfing::RangeSliderFloat("Range 1", &v1, &v2, v_min, v_max, "%.1f  %.1f", 1.0f);
	ofxImGuiSurfing::RangeSliderFloat("Range 2", &v3, &v4, v_min, v_max);

	// vanilla range slider
	static float begin = 10, end = 90;
	static int begin_i = 100, end_i = 1000;
	ImGui::DragFloatRange2("Range Float", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
	ImGui::DragIntRange2("Range Int", &begin_i, &end_i, 5, 0, 0, "%.0fcm", "%.0fcm");

	ImGui::Dummy(ImVec2(0.0f, 2.0f));

	//-

	if (bCustom1)
	{
		// A row of four big toggles
		ImGui::Text("* bCustom1 = true");
		ImGui::Text("customized");
		widgetsManager.Add(bModeA, SurfingTypes::OFX_IM_TOGGLE_BIG, true, 4);
		widgetsManager.Add(bModeB, SurfingTypes::OFX_IM_TOGGLE_BIG, true, 4);
		widgetsManager.Add(bModeC, SurfingTypes::OFX_IM_TOGGLE_BIG, true, 4);
		widgetsManager.Add(bModeD, SurfingTypes::OFX_IM_TOGGLE_BIG, false, 4);
	}
	else // default ofxImGui styles
	{
		ImGui::Text("* bCustom1 = false");
		ImGui::Text("default style");
		ofxImGuiSurfing::AddParameter(bModeA);
		ofxImGuiSurfing::AddParameter(bModeB);
		ofxImGuiSurfing::AddParameter(bModeC);
		ofxImGuiSurfing::AddParameter(bModeD);
	}
}
