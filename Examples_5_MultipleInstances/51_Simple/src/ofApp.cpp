#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	parameters.setName("paramsGroup");
	parameters.add(bPrevious.set("<"));
	parameters.add(bNext.set(">"));
	parameters.add(bEnable1.set("Enable1", false));
	parameters.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	parameters.add(separation.set("separation", 50, 1, 100));
	parameters.add(size.set("size", 100, 0, 100));
	parameters.add(amount.set("amount", 10, 0, 25));

	//--

	//ui.setName("ofApp"); // Optional naming to separate settings folders and avoid sharing some ui states.

#if 0
	// Can be omitted in many scenarios..
	ui.setup(); 
	ui.startup();
#endif

	//--

	A.setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return; // this is the global show visible toggle

	//--

	// custom styles
	static bool b = 1;
	if (b) {
		b = 0;
		ui.ClearStyles();
		ui.AddStyle(bPrevious, OFX_IM_BUTTON_SMALL, 2, true);
		ui.AddStyle(bNext, OFX_IM_BUTTON_SMALL, 2, false);
		ui.AddStyle(bEnable1, OFX_IM_TOGGLE_SMALL_BORDER_BLINK);
	}

	//--

	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			// ImGui widgets are placed here.
			// ofParamaters widgets helpers be easy populate,
			// But you can populate raw ImGui too.

			//--

			// These are some of the available useful internal toggles.
			// Note the minimize, auto resize, debug, extra, advanced, log window...
			// and other boolean/toggles are handled and store into the ofxSurfingGui object. 
			// Then they will be shared between classes objects if they share the same ui. 
			// (Or independent if do not shares the ui.)
			ui.AddMinimizerToggle();
			ui.AddAutoResizeToggle();
			ui.AddDebugToggle();
			//ui.AddAdvancedToggle();

			ui.AddSpacingBigSeparated();

			//ui.DrawWidgetsGlobalScaleMini();
			//ui.AddSpacingBigSeparated();

			//--

			ui.AddLabelBig("MULTIPLE CLASSES");
			ui.AddLabel("WITH DIFFERENT ofxSurfingImGui INSTANTIATION APPROACHES");
			ui.AddSpacing();

			// Show / hide each class window
			SurfingGuiTypes style = OFX_IM_TOGGLE_ROUNDED_MEDIUM; // a style shared between widgets
			ui.Add(A.bGui, style);

			// This is a separator line with more spacing
			ui.AddSpacingBigSeparated();

			//--

			ui.AddLabel("These are exposed \nor public ofParams \nfrom the classes objects \nbut populated here");

			if (ui.isMaximized())
			{
				ui.AddSpacingBigSeparated();

				//--

				// This is an ofParameterGroup.
				// Contained ofParams are populated 
				// as their default widgets styles
				// (but we could queue custom styles for each param too 
				// that will be applied when populating the group widgets)
				// Note that these ofParams are local in ofApp.
				ui.AddGroup(parameters);
			}

			//--

			ui.EndWindow();
		}

		//--

		//A.drawImGuiWindow();

		//--

		// An internal ofxImGui debug method
		if (ui.bDebug) ui.getGuiPtr()->drawOfxImGuiDebugWindow();
	}
	ui.End();

	//--

	A.drawImGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}
