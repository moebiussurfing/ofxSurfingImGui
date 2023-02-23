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

	// Can be omitted in many scenarios..
	//ui.setup();
	C.setUiPtr(ui);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddMinimizerToggle(false);
			ui.AddAutoResizeToggle(false);
			ui.AddSpacingBigSeparated();

			ui.Add(A.bGui, OFX_IM_TOGGLE_ROUN);

			//--

			// ImGui widgets are placed here.
			// ofParamaters widgets helpers be easy populate,
			// But you can populate raw ImGui too.

			// This is an ofParameterGroup
			// contained ofParams are populated 
			// as their default widgets styles
			ui.AddGroup(params);

			// This is a separator line 
			ui.AddSpacingBigSeparated();

			//--

			// This is a ofParam widget but customized instead of default styled
			ui.Add(amount, OFX_IM_VSLIDER);

			// This is another ofParam widget but customized instead of default styled
			ui.Add(bPrevious, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

			//--

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}