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

	ofxSurfing_ImGui_Manager ui;
	
	ofParameter<bool> bGui;//global

	MyClass() {
		bGui.set("MyClass", true); // all the gui

		bGui_1.set("myClass Win1", true);
		bGui_2.set("myClass Win2", true);
		bGui_3.set("myClass Win3", true);

		b1.set("b1", true);
		b2.set("b2", true);
		b3.set("b3", true);
		b4.set("b4", true);
		b5.set("b5", true);
		b6.set("b6", true);

		ui.setName("MyClass");
		ui.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);
		ui.setup();
		// queue special windows
		ui.addWindowSpecial(bGui_1);
		ui.addWindowSpecial(bGui_2);
		ui.addWindowSpecial(bGui_3, false);//disables auto resize mode
		ui.startup();
	};

	~MyClass() {};

	void draw() {
		//fix
		if (ofGetFrameNum() == 1) {
			bGui_1 = true;
			bGui_2 = true;
			bGui_3 = true;
		}

		if (!bGui) return;

		ui.begin();
		{
			if (ui.beginWindowSpecial(bGui_1))
			{
				ui.Add(ui.bGui_HelpersSpecialWindows, OFX_IM_TOGGLE_ROUNDED_BIG);
				if(ui.bGui_HelpersSpecialWindows) ui.AddLabel("This is an internal window to easy auto populate a Window with all the queued Special Windows.", false);
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("This an auto resized window.", false);
				ui.AddLabel("Distributed Toggles on a two columns layout.", false);
				ui.Add(b1, OFX_IM_TOGGLE_BIG);

				// two columns with responsive and big toggles
				ImGui::Columns(2, "", true);
				{
					int w = 1 * ofxImGuiSurfing::getWindowContentWidth();//gets window column width
					int h1 = 5 * ofxImGuiSurfing::getWidgetsHeightUnit();//one unit of widgets height
					ofxImGuiSurfing::AddToggle(b3, ImVec2(w, h1));
					int h2 = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
					//int h2 = ofxImGuiSurfing::getWindowContentHeight();//get all the available height
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

				ui.endWindowSpecial();
			}

			if (ui.beginWindowSpecial(bGui_2))
			{
				ui.Add(b2, OFX_IM_TOGGLE_BIG);
				ui.Add(b3, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(b4, OFX_IM_TOGGLE_ROUNDED_BIG);
				ui.Add(b5, OFX_IM_CHECKBOX);
				ui.Add(b6, OFX_IM_CHECKBOX);

				ui.endWindowSpecial();
			}

			// make some constraints
			if (bGui_3) 
			{
				ImVec2 size_min = ImVec2(100, 300);
				ImVec2 size_max = ImVec2(1000, 1000);
				ImGui::SetNextWindowSizeConstraints(size_min, size_max);
			}
			if (ui.beginWindowSpecial(bGui_3))
			{
				ui.AddLabelBig("This a non auto resized window.", false);
				ui.AddLabel("Distributed Toggles on a Responsive Layout of one column.", false);

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

				ui.endWindowSpecial();
			}

			ui.drawWindowSpecialWindows();
		}
		ui.end();
	}
};
