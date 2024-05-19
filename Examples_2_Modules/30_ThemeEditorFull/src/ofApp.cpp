#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//ofxSurfingHelpers::setMonitorsLayout(-1, false, true);
	ofxSurfingHelpers::setMonitorsLayout(1, true, true);//right monitor and portrait

	ui.setup();

	//--

	// Font Helpers
	f.setUiPtr(&ui);
	f.setup();

	//--

	// Theme Editor
	e.setPathGlobal(ui.getPath());
	e.setUiPtr(&ui);
	e.setup();

	//ui.setLogLevel(OF_LOG_SILENT);
}

//--------------------------------------------------------------
void ofApp::update()
{
	f.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow("ofApp"))
		{
			ui.AddSpacingBig();
			ui.Add(f.bGui, OFX_IM_TOGGLE_ROUNDED_BIG);
			ui.Add(e.bGui, OFX_IM_TOGGLE_ROUNDED_BIG);
			ui.AddSpacingBigSeparated();
			ui.AddAutoResizeToggle();
			ui.AddSpacingBig();

			//--

			// Select day/night theme
			ui.DrawWidgetsTheme();

			ui.EndWindow();
		}
	}

	//--

	f.drawImGui();

	//--

	// The Editor Windows
	// Apply picked as font style
	ui.PushFontByIndex();
	{
		e.draw();

#if 0
		ImGui::Begin("MyDemoWindow");
		ImGui::Text("Hello World");
		ImGui::Button("Button");
		ImGui::End();
#endif
	}
	ui.PopFontByIndex();

	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ofLogNotice("ofApp") << "keyPressed: " << (char)key;

	if (key == OF_KEY_LEFT) { ui.doLoadPreviousFont(); }
	else if (key == OF_KEY_RIGHT) { ui.doLoadNextFont(); }

	else if (key == OF_KEY_F5) { f.doLoadFontsFromFolder("/assets/fonts2/"); }
}

/*

	//------------------------------------------------------------------------------------------
	void Gui::drawImGuiMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			{
				string n = "Reality Field";
				float w = 140;
				ImGui::SetNextWindowSize(ImVec2(w, 0));
				if (ui->BeginMenu(n.c_str()))
				{
					if (ImGui::MenuItem("Exit"))
					{
						ofExit();
					}

					ui->EndMenu();
				}
			}

			//--

			if (ui->BeginMenu("File"))
			{
				if (mainApp) {
					if (ui->MenuItemButton("Load Project")) {
						mainApp->loadSettingsDialog();
					}
					if (ui->MenuItemButton("Save Project")) {
						mainApp->saveSettingsDialog();
					}
				}
				ui->EndMenu();
			}

			if (ui->BeginMenu("Trackers"))
			{
				//ofxImGuiSurfing::AddParameter(encoderManager.outputObj.outputRate);

				if (ImGui::MenuItem("Zero All Of Type From Selected"))
				{
					if (mainApp) mainApp->trackerManager.zeroAllOfType();
				}

				ui->EndMenu();
			}

			// Stage Manager
			if (mainApp) mainApp->stage.drawImGui(ui.get(), true);

			if (ui->BeginMenu("Windows"))
			{
				ui->MenuItemToggle(bGuiCameras);
				ui->MenuItemToggle(bGuiOutput);
				ui->MenuItemToggle(bGuiSync);
				ui->MenuItemToggle(bGuiTrackerData);
				ui->MenuItemToggle(bGuiTrackerInput);
				ui->MenuItemToggle(bGuiData);
				//			ui->MenuItemToggle(bGuiEasyCamera);
				ui->AddSpacingSeparated();

				if (ui->MenuItemButton("All")) {
					bool b = true;
					//bGuiEasyCamera = b;
					bGuiCameras = b;
					bGuiOutput = b;
					bGuiSync = b;
					bGuiTrackerData = b;
					bGuiTrackerInput = b;
					bGuiData = b;
				};
				if (ui->MenuItemButton("None")) {
					bool b = false;
					//bGuiEasyCamera = b;
					bGuiCameras = b;
					bGuiOutput = b;
					bGuiSync = b;
					bGuiTrackerData = b;
					bGuiTrackerInput = b;
					bGuiData = b;
				};

				ui->AddSpacingSeparated();

				ui->MenuItemToggle(bGuiDebugMain);

				ui->EndMenu();
			}

			if (ui->BeginMenu("Help"))
			{
				if (ui->MenuItemButton("Report Bug"))
				{
					ShellExecute(nullptr, nullptr, TEXT("https://loledvirtual.com/forum/public/t/reality-field"),
						nullptr, nullptr, SW_SHOW);
				}

				if (ui->MenuItemButton("Documentation"))
				{
					ShellExecute(nullptr, nullptr, TEXT("https://loledvirtual.com/realityfield/documentation/"), nullptr,
						nullptr, SW_SHOW);
				}

				ui->EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

*/