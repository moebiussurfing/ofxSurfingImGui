#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	//-

	// parameters
	params1.setName("paramsGroup1"); // main container
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));

	params2.setName("paramsGroup2"); // nested
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));

	params3.setName("paramsGroup3"); // nested
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));

	//-

	guiManager.setImGuiDocking(true);
	// -> required false to allow custom docking layout. 
	// instead of the default centralized.
	guiManager.setImGuiDockingModeCentered(true);
	//guiManager.setImGuiDockingModeCentered(false);

	guiManager.setImGuiAutodraw(true); // -> required when only one ImGui instance (= n oother addons using ImGui)
	guiManager.setup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		if (!binitiated) {
			binitiated = true;
			app_LayoutManager.setup();
			ofLogNotice(__FUNCTION__) << "Initialized done";
		}

		//app_LayoutManager.mainFrame.
		// Run the Coking Layout manager!
		app_LayoutManager.draw();

		{
			static bool bOpen0 = true;
			static bool bOpen1 = true;
			static bool bOpen2 = true;

			//---------

			// Main Window

			// A raw standard raw ImGui window
			{
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
				if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

				ImGui::Begin("Show Windows", &bOpen0, window_flags);
				{
					// round toggles widgets
					ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);
					ofxImGuiSurfing::ToggleRoundedButton("Show Window 2", &bOpen2);

					ImGui::Dummy(ImVec2(0, 5)); // spacing

					ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize); // a public bool variable to allow handle auto-resize. Applied here to all the windows.
				}
				ImGui::End();
			}

			//--------

			// Place intems inside:
			// Dock Window Top

			//TODO: how to check if a pane is visible?
			//TODO: how to draw widgets inside the pane?
			//TODO: how to use from outside the class object??
			//app_LayoutManager.mainFrame.

			/*
			if (bOpen1)
			{
				guiManager.beginWindow("Top", &bOpen1, ImGuiWindowFlags_None);
				{
					//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
					////flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
					//flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed
					//ofxImGuiSurfing::AddGroup(params3, flags);

					guiManager.AddGroup(params3);

					guiManager.drawAdvancedSubPanel();
				}
				guiManager.endWindow();
			}
			*/

			//---------

			// Place intems inside:
			// Dock Window Central
			/*
			if (bOpen2)
			{
				guiManager.beginWindow("Central", &bOpen2, ImGuiWindowFlags_None);
				{
					float _w100 = ofxImGuiSurfing::getWidgetsWidth(1); // full width
					float _w50 = ofxImGuiSurfing::getWidgetsWidth(2); // half width
					float _h = ofxImGuiSurfing::getWidgetsHeightRelative(); // standard height

					// Two custom toggles
					if (ofxImGuiSurfing::AddBigToggle(bEnable)) {} // this is full width (_w100) with standard height (_h)
					//if (ofxImGuiSurfing::AddBigToggle(bEnable, _w100, _h)) {} // same width but half height

					// Two custom buttons in the same line/row
					// 50% width aka two widgets on current same line/row
					if (ofxImGuiSurfing::AddBigButton(bPrevious, _w50, _h*2)) {
						lineWidth -= 0.1;
						bPrevious = false;
					}
					ImGui::SameLine();
					if (ofxImGuiSurfing::AddBigButton(bNext, _w50, _h*2)) {
						lineWidth += 0.1;
						bNext = false;
					}

					// Three standard widget params
					ofxImGuiSurfing::AddParameter(bEnable);
					ofxImGuiSurfing::AddParameter(separation);
					ofxImGuiSurfing::AddParameter(shapeType);
				}
				guiManager.endWindow();
			}
			*/

			//-----
		}
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::exit()
{
	app_LayoutManager.exit();
}