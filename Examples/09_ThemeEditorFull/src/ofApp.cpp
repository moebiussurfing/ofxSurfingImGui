#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxSurfingHelpers::setMonitorsLayout(-1, true, true);

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
