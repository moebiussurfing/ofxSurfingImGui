#include "myClassC.h"

//--------------------------------------------------------------
myClassC::myClassC() {
	setup();
}

//--------------------------------------------------------------
myClassC::~myClassC() {
}

//--------------------------------------------------------------
void myClassC::setUiPtr(ofxSurfingGui* _ui) {
	ui = _ui;
}

//--------------------------------------------------------------
void myClassC::setup()
{
	params.setName("paramsGroupC");
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
};

//--------------------------------------------------------------
void myClassC::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddMinimizerToggle(false);
			ui.AddAutoResizeToggle(false);
			ui.AddSpacingBigSeparated();

			ui.AddGroup(params, SurfingGuiGroupStyle_Collapsed);

			ui.EndWindow();
		}
	}
	ui.End();
};