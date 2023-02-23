#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	params.setName("paramsGroup");
	params.add(bPrevious.set("<"));
	params.add(bNext.set(">"));
	params.add(bEnable1.set("Enable1", false));
	params.add(bEnable2.set("Enable2", false));
	params.add(bEnable3.set("Enable3", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));

	//--

	ui.setName("ofApp"); // Optional naming to separate settings folders and avoid sharing some ui states.
	ui.setup(); // Can be omitted in many scenarios..

	// WIP: TODO: Note that some empty/undesired folders are created into bin/data. This must be fixed...

	// This object will receive and store this local ui into a pointer to populate widgets on there: inside the class draw method.
	C.setUiPtr(&ui);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return;

	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			// ImGui widgets are placed here.
			// ofParamaters widgets helpers be easy populate,
			// But you can populate raw ImGui too.

			//--

			// These are some of the available useful internal toggles.
			// Note the minimize, auto resize, debug, extra, log...
			// and other boolean/toggles are handled and store into the ofxSurfingGui object. 
			// Then they will be shared between classes objects if they share the same ui.
			ui.AddMinimizerToggle(false);
			ui.AddAutoResizeToggle(false);
			ui.AddSpacingBigSeparated();

			//--

			ui.AddLabelBig("MULTIPLE CLASSES");
			ui.AddLabel("WITH DIFFERENT ofxSurfingImGui INSTANTIATION APPROACHES");
			ui.AddSpacing();

			// Show / hide each class window
			SurfingGuiTypes style = OFX_IM_TOGGLE_ROUNDED_MEDIUM;
			ui.Add(A.bGui, style);
			ui.Add(B.bGui, style);
			ui.Add(C.bGui, style);
			ui.Add(D.bGui, style);

			// This is a separator line with spacing
			ui.AddSpacingBigSeparated();

			//--

			ui.AddLabel("These are exposed or public ofParams from the classes objects but populated here");

			if (ui.BeginTree("ofParams")) {

				ui.AddLabel("A");
				ui.Add(A.amount2);
				ui.Add(A.shapeType2);
				ui.AddLabel("B");
				ui.Add(B.separation);
				ui.Add(B.lineWidth);
				ui.AddLabel("C");
				ui.Add(C.speed);
				ui.Add(C.lineWidth);
				ui.AddLabel("D");
				ui.Add(D.separation);
				ui.Add(D.lineWidth);

				ui.EndTree();
			}

			ui.AddSpacingBigSeparated();

			//--

			// This is an ofParameterGroup
			// contained ofParams are populated 
			// as their default widgets styles
			ui.AddGroup(params);

			//--

			// This is a ofParam widget but customized instead of using the default styled
			ui.Add(amount, OFX_IM_VSLIDER);

			// This is a ofParam widget but customized instead of using the default styled
			ui.Add(bPrevious, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

			//--

			ui.EndWindow();
		}

		// Note that will draw the window. Do not calls Begin/End inside the class object!
		A.draw();

		// We want to draw widgets inside the class (eg: to not expose public ofParams here in ofApp) 
		// but using the local instantiated ofxSurfingGui object! (not an ui internally instantiated in the class)
		D.draw(&ui);
	}
	ui.End();

	//--

	// This two objects will call Begin/End internally
	
	B.draw(); 
	// this one has his own ui instance! 
	// So is not linked to the local ofApp ui. 
	// (some internal settings are neither shared)
	
	C.draw(); 
	// this one shares the ui instance from ofApp! 
	// It's passed by reference on setup.
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}