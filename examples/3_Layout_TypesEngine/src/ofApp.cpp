#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	guiManager.setup();

	//-

	// parameters
	params.setName("paramsGroup");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
	params2.add(bMode1.set("Mode1", false));
	params2.add(bMode2.set("Mode2", false));
	params2.add(bMode3.set("Mode3", false));
	params2.add(bMode4.set("Mode4", false));
	params2.add(bPrevious.set("<", false));
	params2.add(bNext.set(">", false));
	params2.add(bEnable.set("Enable", false));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params.add(params3);
	params.add(params2);

	//-

	// queue widgets to customize when they will be drawn inside an ofParameterGroup
	// if the parameter widget is not added explicitly, will be populated as the default appearance

	//bools
	widgetsManager.AddWidgetConf(bEnable, ImGuiWidgetsTypesManager::IM_TOGGLE_BIG);
	widgetsManager.AddWidgetConf(bPrevious, ImGuiWidgetsTypesManager::IM_BUTTON_SMALL, true, 2);
	widgetsManager.AddWidgetConf(bNext, ImGuiWidgetsTypesManager::IM_BUTTON_SMALL, false, 2, 20);
	//widgetsManager.AddWidgetConf(bMode4, ImGuiWidgetsTypesManager::IM_CHECKBOX, false, 1, 10);
	//floats
	//widgetsManager.AddWidgetConf(lineWidth, ImGuiWidgetsTypesManager::IM_SLIDER);
	widgetsManager.AddWidgetConf(separation, ImGuiWidgetsTypesManager::IM_STEPPER);
	widgetsManager.AddWidgetConf(speed, ImGuiWidgetsTypesManager::IM_DRAG, false, 1, 10);
	//ints
	widgetsManager.AddWidgetConf(shapeType, ImGuiWidgetsTypesManager::IM_SLIDER);
	widgetsManager.AddWidgetConf(size, ImGuiWidgetsTypesManager::IM_STEPPER);
	widgetsManager.AddWidgetConf(amount, ImGuiWidgetsTypesManager::IM_DRAG, false, 1, 10);
	//bools
	widgetsManager.AddWidgetConf(bMode1, ImGuiWidgetsTypesManager::IM_TOGGLE_SMALL, true, 2);
	widgetsManager.AddWidgetConf(bMode2, ImGuiWidgetsTypesManager::IM_TOGGLE_SMALL, false, 2);
	widgetsManager.AddWidgetConf(bMode3, ImGuiWidgetsTypesManager::IM_TOGGLE_SMALL, true, 2);
	widgetsManager.AddWidgetConf(bMode4, ImGuiWidgetsTypesManager::IM_TOGGLE_SMALL, false, 2);

	//hide
	widgetsManager.AddWidgetConf(speed3, ImGuiWidgetsTypesManager::IM_HIDDEN, false, -1, 50);
	widgetsManager.AddWidgetConf(size2, ImGuiWidgetsTypesManager::IM_HIDDEN, false, -1, 50);
	widgetsManager.AddWidgetConf(bPrevious, ImGuiWidgetsTypesManager::IM_HIDDEN);
	widgetsManager.AddWidgetConf(bNext, ImGuiWidgetsTypesManager::IM_HIDDEN);
	widgetsManager.AddWidgetConf(lineWidth, ImGuiWidgetsTypesManager::IM_HIDDEN);

	//TODO: fails. fix
	guiManager.auto_resize = false;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		//TODO:
		// trying workaround to fix getUniqueName troubles..
		widgetsManager.resetIndex();

		static bool bOpen0 = true;
		static bool bOpen1 = true;
		static bool bOpen2 = false;

		//-----

		// window 0 (main)

		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.auto_resize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::Begin("Show Windows", &bOpen0, window_flags);
			{
				// round toggles

				ofxSurfingHelpers::ToggleButton("bOpen1", &bOpen1);
				ofxSurfingHelpers::ToggleButton("bOpen2", &bOpen2);

				ImGui::Dummy(ImVec2(0, 5));

				ofxSurfingHelpers::AddToggleRounded(guiManager.auto_resize);
			}
			ImGui::End();
		}
		//---------

		// window 1

		// using my own simpler helpers API: 
		// ofxSurfing_ImGui_Helpers.h

		if (bOpen1)
		{
			// a window but using my ofxSurfing_ImGui_LayoutManager.h class helper

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.auto_resize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			guiManager.beginWindow("window 1", &bOpen1, window_flags);//bOpen1 not working..
			{
				// 1. single params

				// (instant populate)
				{
					widgetsManager.refreshPanelShape(); // update sizes to current window shape
					widgetsManager.Add(bEnable, ImGuiWidgetsTypesManager::IM_TOGGLE_SMALL); // full width

					if (widgetsManager.Add(bPrevious, ImGuiWidgetsTypesManager::IM_BUTTON_BIG, true, 2)) // half width + same line
					{
						lineWidth.setWithoutEventNotifications(lineWidth.get() - 0.1f);//fail
					}
					if (widgetsManager.Add(bNext, ImGuiWidgetsTypesManager::IM_BUTTON_BIG, false, 2, 20))// half width + 20px vert spacing
					{
						lineWidth.setWithoutEventNotifications(lineWidth.get() + 0.1f);//fail
					}

					//widgetsManager.Add(lineWidth, ImGuiWidgetsTypesManager::IM_SLIDER);
					//widgetsManager.Add(lineWidth, ImGuiWidgetsTypesManager::IM_DRAG);
					widgetsManager.Add(lineWidth, ImGuiWidgetsTypesManager::IM_STEPPER, false, 2, 20);

					// three widgets in one same row with 20px vert spacing before the next row
					widgetsManager.refreshPanelShape(); // update sizes to current window shape
					widgetsManager.Add(bMode1, ImGuiWidgetsTypesManager::IM_TOGGLE_SMALL, true, 3);
					widgetsManager.Add(bMode2, ImGuiWidgetsTypesManager::IM_TOGGLE_SMALL, true, 3);
					widgetsManager.Add(bMode3, ImGuiWidgetsTypesManager::IM_TOGGLE_SMALL, false, 3, 2);

					widgetsManager.Add(bMode4, ImGuiWidgetsTypesManager::IM_CHECKBOX);
					//ImGui::Dummy(ImVec2(0, 20);// spacing
				}

				//-

				// 2. group of params

				// (queue to populate after)
				{
					// group of parameters with customized tree/folder type
					// will be applied to all nested groups inside this parent
					// customization is defined above on setup(): widgetsManager.AddWidgetConf(..

					ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
					flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
					flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed

					//widgetsManager.refreshPanelShape(); // update sizes to current window shape
					ofxSurfing::AddGroup(params, flags);
				}
			}
			guiManager.endWindow();
		}

		//---------

		// window 2

		// using my own simpler helpers API: ofxSurfing_ImGui_Helpers.h

		if (bOpen2)
		{
			float _spcx; // space between widgets
			float _spcy; // space between widgets
			float _w100; // full width
			float _h100; // full height
			float _w99; // a bit less than full width
			float _w50; // half width
			float _w33; // third width
			float _w25; // quarter width
			float _h; // standard height

			// a window but using my ofxSurfing_ImGui_LayoutManager.h class

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.auto_resize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			guiManager.beginWindow("window 2", &bOpen2, window_flags);
			{
				// we will update the sizes on any gui drawing point, like inside a new foldered sub-window that could be indendeted and full size is being smaller.
				ofxSurfingHelpers::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

				//-

				if (ofxSurfingHelpers::AddBigToggle(bEnable)) {}// this is full width (_w100) with standard height (_h)
				if (ofxSurfingHelpers::AddBigToggle(bEnable, _w100, _h / 2)) {} // same width but half height

				// 50% with / two widgets same line/row
				if (ofxSurfingHelpers::AddBigButton(bPrevious, _w50, _h)) {
					lineWidth -= 0.1;
					bPrevious = false;
				}
				ImGui::SameLine();
				if (ofxSurfingHelpers::AddBigButton(bNext, _w50, _h)) {
					lineWidth += 0.1;
					bNext = false;
				}

				//-

				ImGui::Dummy(ImVec2(0.0f, 5.0f));// spacing

				// do not updates for below group. Must call:
				widgetsManager.refreshPanelShape();

				// group parameter with customized tree/folder type
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
				flags |= ImGuiTreeNodeFlags_Framed;
				flags |= ImGuiTreeNodeFlags_DefaultOpen;
				ofxSurfing::AddGroup(params2, flags);

				//-

				// an advanced panels with some typical toggle for extra config (autosize, get mouse over, lock..etc)
				guiManager.drawAdvancedSubPanel();
			}
			guiManager.endWindow();
		}

		//-
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawWidgets() {

	// these are pure widgets without window/tree/container

	auto mainSettings = ofxImGui::Settings();

	// typical width sizes from 1 (_w100) to 4 (_w25) widgets per row
	float _spcx;
	float _spcy;
	float _w100;
	float _h100;
	float _w99;
	float _w50;
	float _w33;
	float _w25;
	float _h;

	// update to current window shape
	ofxSurfingHelpers::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);// we will update the sizes on any gui drawing point, like inside a new foldered sub-window that could be indendeted and full size is being smaller.

	// add an ofParameterGroup
	ofxImGui::AddGroup(params3, mainSettings);

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
	ImGui::RangeSliderFloat("range1", &v1, &v2, v_min, v_max, "%.3f  %.3f", 1.0f);
	ImGui::RangeSliderFloat("range2", &v3, &v4, v_min, v_max);

	// vanilla range slider
	static float begin = 10, end = 90;
	static int begin_i = 100, end_i = 1000;
	ImGui::DragFloatRange2("range float", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
	ImGui::DragIntRange2("range int", &begin_i, &end_i, 5, 0, 0, "Min: %.0f units", "Max: %.0f units");

	ImGui::Dummy(ImVec2(0.0f, 2.0f));
}
