#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	namesStylesColor.push_back("OFX_IM_COLOR");
	namesStylesColor.push_back("OFX_IM_COLOR_INPUTS");
	namesStylesColor.push_back("OFX_IM_COLOR_INPUTS_NO_ALPHA");
	namesStylesColor.push_back("OFX_IM_COLOR_NO_INPUTS");
	namesStylesColor.push_back("OFX_IM_COLOR_NO_INPUTS_NO_ALPHA");
	namesStylesColor.push_back("OFX_IM_COLOR_NO_NAME");
	namesStylesColor.push_back("OFX_IM_COLOR_BOX");
	namesStylesColor.push_back("OFX_IM_COLOR_BOX_FULL_WIDTH");
	namesStylesColor.push_back("OFX_IM_COLOR_BOX_FULL_WIDTH_BIG");
	namesStylesColor.push_back("OFX_IM_COLOR_BOX_FULL_WIDTH_NO_ALPHA");
	namesStylesColor.push_back("OFX_IM_COLOR_BOX_FULL_WIDTH_BIG_NO_ALPHA");

	index.setMax(namesStylesColor.size() - 1);
	listener = index.newListener([this](int& i)
		{
			styleColor = SurfingGuiTypes(i + (int)OFX_IM_COLOR);
	ofLogNotice() << "Style: #" << i << " " << namesStylesColor[i];
		});

	// trig callback
	index = 0;

	//--

	// ofParameters

	params.setName("params");

	c1.set("c1", ofColor::red, ofColor(0), ofColor(255));
	c2.set("c2", ofColor::green, ofColor(0), ofColor(255));
	c3.set("c3", ofColor::blue, ofFloatColor(0), ofFloatColor(1));
	c4.set("c4", ofColor::yellow, ofFloatColor(0), ofFloatColor(1));

	params.add(c1, c2, c3, c4);

	//--

	ui.setup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddLabelBig("Debugger / Tester\nfor ofParam \ncolor widgets");
			ui.AddSpacingBigSeparated();

			ui.Add(ui.bAutoResize);
			ui.AddSpacingBigSeparated();

			ui.Add(index, OFX_IM_HSLIDER_SMALL_NO_LABELS);
			ui.AddComboButtonDualCenteredNames(index, namesStylesColor);
			SurfingGuiTypes _style = SurfingGuiTypes(styleColor);
			ui.AddSpacing();

			ui.AddLabelBig("API Styled");
			ui.Add(c1, _style);
			ui.Add(c2, _style);
			ui.Add(c3, _style);
			ui.Add(c4, _style);

			//--

			ui.AddSpacingSeparated();
			ui.AddLabelBig("Raw");
			auto sz = ImVec2(ui.getWidgetsWidth(), ui.getWidgetsHeightUnit() * 3);
			ofxImGuiSurfing::addColorBox(c1, sz);

			//--

			ui.AddSpacingBigSeparated();
			ui.AddLabelBig("Group");
			ui.AddGroup(params);

			static bool b = false;
			if (!b) {
				b = true;
				ui.AddStyle(c1, OFX_IM_COLOR_BOX_FULL_WIDTH);
				ui.AddStyle(c2, OFX_IM_COLOR_NO_INPUTS_NO_ALPHA);
				ui.AddStyle(c3, OFX_IM_COLOR_NO_NAME);
				ui.AddStyle(c4, OFX_IM_COLOR_INPUTS);
			}

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') {
		bGui = !bGui;
	}

	if (key == ' ') {

	}
}