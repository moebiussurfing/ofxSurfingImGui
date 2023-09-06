#include "myClassB.h"

//--------------------------------------------------------------
myClassB::myClassB() {
	setup();
};

//--------------------------------------------------------------
myClassB::~myClassB() {
};

//--------------------------------------------------------------
void myClassB::setup()
{
	params.setName("paramsGroupB");
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));

	//--

	// Can be omitted in many scenarios..
	ui.setName("myClassB"); // Optional naming to separate settings folders and avoid sharing some ui states.
	ui.setup();
};

//--------------------------------------------------------------
void myClassB::draw()
{
	if (!bGui) return;

	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddMinimizerToggle();
			ui.AddAutoResizeToggle();
			ui.AddSpacingBigSeparated();

			if (ui.isMaximized()) ui.AddGroup(params, SurfingGuiGroupStyle_Collapsed);
			ui.Add(speed, OFX_IM_KNOB_DOTKNOB, 2, true);
			ui.Add(separation, OFX_IM_KNOB_DOTKNOB, 2);

			ui.EndWindow();
		}
	}
	ui.End();
};