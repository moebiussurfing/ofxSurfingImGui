#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() 
{
	// Parameters
	params.setName("paramsGroup"); // main container
	params2.setName("paramsGroup2"); // nested
	params3.setName("paramsGroup3"); // nested
	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable1.set("Enable1", false));
	params.add(bEnable2.set("Enable2", false));
	params.add(bEnable3.set("Enable3", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params2.add(params3);
	params.add(params2);

	// Can be omitted in most scenarios..
	//ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			// ImGui widgets are placed here.
			// ofParamaters widgets helpers be easy populate,
			// But you can populate raw ImGui too.

			// This is an ofParameterGroup
			// contained params are populated 
			// as their default widgets styles
			ui.AddGroup(params);

			// This is a separator line 
			ui.AddSpacingBigSeparated();

			// This is a param widget
			ui.Add(amount2, OFX_IM_VSLIDER);

			// This is a param widget
			ui.Add(bPrevious, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

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