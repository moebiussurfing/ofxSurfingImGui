#pragma once

#include "ofMain.h"
#include "ofxSurfingImGui.h"

class MyClass
{
public:

	ofParameter<bool> bGui_1;
	ofParameter<bool> bGui_2;
	ofParameter<bool> bGui_3;

	ofParameter<bool> b1;
	ofParameter<bool> b2;
	ofParameter<bool> b3;
	ofParameter<bool> b4;
	ofParameter<bool> b5;
	ofParameter<bool> b6;

	ofParameterGroup params{"MyClass"};

	SurfingGuiManager ui;
	
	ofParameter<bool> bGui; // global visible

	MyClass() {
		bGui.set("MyClass", true); // all the gui

		bGui_1.set("myClass Window A", true);
		bGui_2.set("myClass Window B", true);
		bGui_3.set("myClass Window C", true);

		b1.set("b1", true);
		b2.set("b2", true);
		b3.set("b3", true);
		b4.set("b4", true);
		b5.set("b5", true);
		b6.set("b6", true);
	};

	~MyClass() {
		// Session Settings
		ofxSurfingHelpers::saveGroup(params);
	};

	void setupImGui() {

		ui.setName("MyClass");

		// Can be omitted in most scenarios
		// TODO: not the case here! why?
		ui.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
		ui.setup();

		// queue special windows
		ui.addWindowSpecial(bGui_1);
		ui.addWindowSpecial(bGui_2);
		ui.addWindowSpecial(bGui_3, false);//disables auto resize mode

		// Can be omitted in most scenarios
		ui.startup();

		//--

		// Session Settings
		params.add(bGui);
		ofxSurfingHelpers::loadGroup(params);
	};

	void draw() 
	{
		////fix
		//if (ofGetFrameNum() == 1) {
		//	bGui_1 = true;
		//	bGui_2 = true;
		//	bGui_3 = true;
		//}

		if (!bGui) return;

		ui.Begin();
		{
			if (ui.BeginWindowSpecial(bGui_1))
			{
				// Optional: 
				// Some internal useful common toggles are exposed:
				ui.AddLabel("These are internal windows toggles \
					useful to populate related Windows \
					when using Special Windows mode.");
				ui.AddSpacing();
				ui.Add(ui.bGui_Organizer, OFX_IM_TOGGLE_ROUNDED_SMALL);
				ui.Add(ui.bGui_Aligners, OFX_IM_TOGGLE_ROUNDED_MINI);
				ui.Add(ui.bGui_SpecialWindows, OFX_IM_TOGGLE_ROUNDED_MINI);
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("This an auto resized window.");
				ui.AddLabel("Distributed Toggles on a two columns layout.");
				ui.Add(b1, OFX_IM_TOGGLE_BIG);

				// two columns with responsive and big toggles
				ImGui::Columns(2, "", true);
				{
					int w = 1 * ofxImGuiSurfing::getWindowContentWidth();//gets window column width
					int h1 = 5 * ofxImGuiSurfing::getWidgetsHeightUnit();//one unit of widgets height
					ofxImGuiSurfing::AddToggle(b3, ImVec2(w, h1));
					int h2 = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
					ofxImGuiSurfing::AddToggle(b4, ImVec2(w, h2));
				}
				ImGui::NextColumn();
				{
					int w = ofxImGuiSurfing::getWindowContentWidth();//gets window column width
					int h1 = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
					ofxImGuiSurfing::AddToggle(b5, ImVec2(w, h1));
					int h2 = ofxImGuiSurfing::getWindowContentHeight();//get all the available height
					ofxImGuiSurfing::AddToggle(b6, ImVec2(w, h2));
				}
				ImGui::Columns(1);

				ui.EndWindowSpecial();
			}

			//--

			if (ui.BeginWindowSpecial(bGui_2))
			{
				ui.Add(b2, OFX_IM_TOGGLE_BIG);
				ui.Add(b3, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(b4, OFX_IM_TOGGLE_ROUNDED_BIG);
				ui.Add(b5, OFX_IM_CHECKBOX);
				ui.Add(b6, OFX_IM_CHECKBOX);

				ui.EndWindowSpecial();
			}

			//--

			// make some constraints
			if (bGui_3) 
			{
				ImVec2 size_min = ImVec2(100, 300);
				ImVec2 size_max = ImVec2(1000, 1000);
				ImGui::SetNextWindowSizeConstraints(size_min, size_max);
			}
			if (ui.BeginWindowSpecial(bGui_3))
			{
				ui.AddLabelBig("This a non auto resized window.");
				ui.AddLabel("Distributed Toggles on a Responsive Layout of one column.");
				ui.AddSpacing();

				int spcy = ofxImGuiSurfing::getWidgetsSpacingY();
				int w = ofxImGuiSurfing::getWindowContentWidth();//gets window column width

				//calculate widgets height for responsive
				const int _amount = 6;
				int hfull = ofxImGuiSurfing::getWindowContentHeight();
				int h = (hfull - ((_amount - 1) * spcy)) / _amount;

				ofxImGuiSurfing::AddToggle(b1, ImVec2(w, h));
				ofxImGuiSurfing::AddToggle(b2, ImVec2(w, h));
				ofxImGuiSurfing::AddToggle(b3, ImVec2(w, h));
				ofxImGuiSurfing::AddToggle(b4, ImVec2(w, h));
				ofxImGuiSurfing::AddToggle(b5, ImVec2(w, h));
				ofxImGuiSurfing::AddToggle(b6, ImVec2(w, h));

				ui.EndWindowSpecial();
			}
		}
		ui.End();
	}
};
