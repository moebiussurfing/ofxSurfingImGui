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

	// WIP: TODO: Note that some empty/undesired folders now are created into bin/data. This must be fixed...

	// This C object will receive and store this local ui into a pointer to populate widgets on there: inside the class draw method.
	C.setUiPtr(&ui);

	// Advanced
	callback_t myFunctionDraw = std::bind(&ofApp::drawWidgets, this);
	//std::function<void()> myFunctionDraw = std::bind(&ofApp::drawWidgets, this);
	C.setDrawWidgetsFunction(myFunctionDraw);

	//ui.startup();
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
		ui.AddStyle(bEnable2, OFX_IM_TOGGLE_SMALL_BORDER_BLINK);
		ui.AddStyle(bEnable3, OFX_IM_TOGGLE_SMALL_BORDER_BLINK);
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
			ui.Add(B.bGui, style);
			ui.Add(C.bGui, style);
			ui.Add(D.bGui, style);

			// This is a separator line with more spacing
			ui.AddSpacingBigSeparated();

			//--

			ui.AddLabel("These are exposed \nor public ofParams \nfrom the classes objects \nbut populated here");
			// This approach is an alternative approach: 
			// instead of drawing the widgets inside each class object, 
			// and having to pass by reference the ui from here / the parent ofApp 
			// or requiring instantiating another new ui inside each object.

			// A folder / tree populating widgets styled as default. 
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
			// Note that using this above approach, we could also create a window 
			// for populating these widgets: the widgets from each object.
			// (Should be out of this above window but in between Begin/End)
			/*
			if (ui.BeginWindow(C.bGui))
			{
				ui.Add(C.speed);
				ui.Add(C.lineWidth);

				ui.EndWindow();
			}
			*/

			if (ui.isMaximized()) {

				ui.AddSpacingBigSeparated();

				//--

				// This is an ofParameterGroup.
				// Contained ofParams are populated 
				// as their default widgets styles
				// (but we could queue custom styles for each param too 
				// that will be applied when populating the group widgets)
				// Note that these ofParams are local in ofApp.
				ui.AddGroup(params);

				//--

				// This is a ofParam widget but customized instead of using the default styled
				ui.Add(amount, OFX_IM_VSLIDER);

				// This is a ofParam widget but customized instead of using the default styled
				ui.Add(bPrevious, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			}

			//--

			ui.EndWindow();
		}

		// Note that will draw the window. Do not calls Begin/End inside the class object!
		A.draw();

		// We want to draw widgets inside the class (eg: to not expose public ofParams here in ofApp) 
		// but using the local instantiated ofxSurfingGui object! 
		// (There´s not an ofxSurfingImGui ui internally instantiated in the class object! Neither a referenced pointer stored.)
		D.draw(&ui);

		//--

		if (ui.bDebug) ui.getGuiPtr()->drawOfxImGuiDebugWindow();
	}
	ui.End();

	//--

	// This two objects will call Begin/End internally
	// so, they will go outside the above used Begin/End.

	B.draw();
	// this one has his own ofxSurfingImGui ui instance! 
	// So it´s not linked to the local ofApp ui. 
	// (some internal settings are neither shared 
	// and also will have a separated bin/data folder for some persistent stored settings.)

	C.draw();
	// this one shares the ofxSurfingImGui ui instance from ofApp! 
	// Note that it has been passed by reference on ofApp::setup.
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}
