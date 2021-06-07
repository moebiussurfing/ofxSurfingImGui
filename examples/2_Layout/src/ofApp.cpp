#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(25);

	guiManager.setup(gui); // can be instantiated out of the class, locally
	//guiManager.setup(); // or inside the class, the we can forgot of declare here (ofApp scope).

	// parameters
	params.setName("paramsGroup");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params.add(bMode1.set("Mode1", false));
	params.add(bMode2.set("Mode2", false));
	params.add(bMode3.set("Mode3", false));
	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable.set("Enable", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params2.add(params3);
	params.add(params2);

	// customize widgets
	widgetsManager.AddWidgetConf(bEnable, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL);
	widgetsManager.AddWidgetConf(bPrevious, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_BUTTON_SMALL);
	widgetsManager.AddWidgetConf(bNext, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_BUTTON_BIG);
}

//--------------------------------------------------------------
void ofApp::draw()
{

	guiManager.begin();
	{
		//--

		// window 1

		// using my own simpler helpers API: ofxSurfing_ImGui_Helpers.h
		if (1)
		{
			// a window but using my ofxSurfing_ImGui_LayoutManager.h class

			static bool bOpen1 = true;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

			guiManager.beginWindow("window 1", &bOpen1, window_flags);
			{
				widgetsManager.refreshPanelWidth();

				widgetsManager.Add(bEnable, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL); // full width

				widgetsManager.Add(bPrevious, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_BUTTON_BIG, 2, true); // half width + same line
				widgetsManager.Add(bNext, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_BUTTON_BIG, 2, false, 20);// half width + 20px vert spacing
				
				//ImGui::Dummy(ImVec2(0, 20));// spacing
				
				// three widgets in one same row with 20px vert spacing before the next row
				widgetsManager.Add(bMode1, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL, 3, true);
				widgetsManager.Add(bMode2, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL, 3, true);
				widgetsManager.Add(bMode3, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL, 3, false, 20);

				//ImGui::Dummy(ImVec2(0, 20);// spacing

				//-

				// group of parameters with customized tree/folder type
				// will be applied to all nested groups inside this parent
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
				flags |= ImGuiTreeNodeFlags_Framed;//uncomment to draw dark tittle bar
				//flags |= ImGuiTreeNodeFlags_DefaultOpen;//comment to start closed
				ofxSurfing::AddGroup(params, flags);
			}
			guiManager.endWindow();
		}

		//--

		// window 2

		// using my own simpler helpers API: ofxSurfing_ImGui_LayoutManager.h and ofxSurfing_ImGui_Helpers.h to handle params
		if (1)
		{
			bool bOpen2 = true;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			guiManager.beginWindow("window 2", &bOpen2, window_flags);
			{
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
				flags |= ImGuiTreeNodeFlags_Framed;
				flags |= ImGuiTreeNodeFlags_DefaultOpen;

				ofxSurfing::AddParameter(bEnable);
				ofxSurfing::AddParameter(separation);
				ofxSurfing::AddParameter(shapeType);
			}
			guiManager.endWindow();
		}

		//--

		// window 3

		// using the old ofxGui original API: (Settings/ofxImGui::AddGroup)
		if (0)
		{
			auto mainSettings = ofxImGui::Settings();
			ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
			string name = "window 3";

			if (ofxImGui::BeginWindow(name.c_str(), mainSettings, _flagw))
			{
				drawWidgets();
				ofxSurfingHelpers::AddBigButton(bPrevious, 100, 30);
			}
			ofxImGui::EndWindow(mainSettings);
		}

		//--

		// window 4

		// using my own simpler helpers API: ofxSurfing_ImGui_Helpers.h
		if (0)
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

			static bool bOpen4 = true;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

			guiManager.beginWindow("window 4", &bOpen4, window_flags);
			{
				// we will update the sizes on any gui drawing point, like inside a new foldered sub-window that could be indendeted and full size is being smaller.
				ofxSurfingHelpers::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

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

				// group parameter with customized tree/folder type
				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
				flags |= ImGuiTreeNodeFlags_Framed;
				flags |= ImGuiTreeNodeFlags_DefaultOpen;
				ofxSurfing::AddGroup(params, flags);

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

	//// these are pure widgets without window/tree/container

	//auto mainSettings = ofxImGui::Settings();

	//// typical width sizes from 1 (_w100) to 4 (_w25) widgets per row
	//float _spcx;
	//float _spcy;
	//float _w100;
	//float _h100;
	//float _w99;
	//float _w50;
	//float _w33;
	//float _w25;
	//float _h;
	//ofxSurfingHelpers::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);// we will update the sizes on any gui drawing point, like inside a new foldered sub-window that could be indendeted and full size is being smaller.

	//// an ofParameterGroup
	//ofxImGui::AddGroup(params3, mainSettings);
	//ImGui::Dummy(ImVec2(0.0f, 2.0f));// spacing

	////-

	//// range_slider.h
	//static float v1 = 0;
	//static float v2 = 1;
	//static float v_min = 0;
	//static float v_max = 1;
	//static float v3 = 0;
	//static float v4 = 1;
	//ImGui::RangeSliderFloat("range1", &v1, &v2, v_min, v_max, "%.3f  %.3f", 1.0f);
	//ImGui::RangeSliderFloat("range2", &v3, &v4, v_min, v_max);

	//// vanilla slider
	//static float begin = 10, end = 90;
	//static int begin_i = 100, end_i = 1000;
	//ImGui::DragFloatRange2("range", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
	//ImGui::DragIntRange2("range int (no bounds)", &begin_i, &end_i, 5, 0, 0, "Min: %.0f units", "Max: %.0f units");

	//ImGui::Dummy(ImVec2(0.0f, 2.0f));
}
