#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	parameters.setName("paramsGroup");
	parameters.add(bPrevious.set("<"));
	parameters.add(bNext.set(">"));
	parameters.add(bEnable1.set("Enable1", false));
	parameters.add(bEnable2.set("Enable2", false));
	parameters.add(bEnable3.set("Enable3", false));
	parameters.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	parameters.add(separation.set("separation", 50, 1, 100));
	parameters.add(speed.set("speed", 0.5, 0, 1));
	parameters.add(shapeType.set("shapeType", 0, -50, 50));
	parameters.add(size.set("size", 100, 0, 100));
	parameters.add(amount.set("amount", 10, 0, 25));

	//--

	ui.setName("ofApp"); // Optional naming to separate settings folders and avoid sharing some ui states.
	ui.setup(); // Can be omitted in many scenarios..

	//--

	// A and D objects will receive ui pointer as a referenced argument!

	//--

	// B
	B.setUiPtr(&ui);

	//--

	// C
	// This C object will receive and store this local ui into a pointer to populate widgets on there: inside the class draw method.
	C.setUiPtr(&ui);

	// Advanced function
	callback_t myFunctionDraw = std::bind(&ofApp::drawWidgets, this);
	C.setDrawWidgetsFunction(myFunctionDraw);

	//--

	ui.startup(); // Can be omitted in many scenarios..
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return; // this is the global show visible toggle

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
			ui.AddSpacingBigSeparated();

			//ui.DrawWidgetsGlobalScaleMini();
			//ui.AddSpacingBigSeparated();

			//--

			ui.AddLabelBig("MULTIPLE CLASSES");
			ui.AddLabel("WITH THEIR WIDGETS POPULATION.");
			ui.AddLabel("A main single 'ofxSurfingGui ui' instance.");
			ui.AddLabel("Passed as argument on drawImGui or referenced on setup.");
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
			// we get internal parameters from the class objects. 
			if (ui.BeginTree("ofParams"))
			{
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

				//--

				// This is a ofParam widget but customized instead of using the default styled
				ui.Add(amount, OFX_IM_VSLIDER);

				// This is a ofParam widget but customized instead of using the default styled
				ui.Add(bPrevious, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			}

			//--

			ui.EndWindow();
		}

		//--

		// Note that will draw the window with their content. 
		// Do not calls Begin/End inside the class object!

		A.drawImGui(&ui);

		B.drawImGui();

		C.drawImGui();

		D.drawImGui(&ui);
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	ui.AddSpacingBigSeparated();
	ui.AddLabelBig("Hello std::function<void()>");
	ui.AddLabel("Where is the drawer?");

	static bool b = true;
	ImGui::Checkbox("b", &b);
	if (b) {
		ImGui::Text("It's defined in (parent) ofApp, \nnot myClassC object!");
		ImGui::Text("Passed in ofApp/setup()");
		ui.AddSpacing();
	}

	static float val1 = 0;
	ImGui::SliderFloat("val1", &val1, -1, 1);

	static float val2 = 0.5f;
	ImGui::SliderFloat("val2", &val2, -1, 1);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}
