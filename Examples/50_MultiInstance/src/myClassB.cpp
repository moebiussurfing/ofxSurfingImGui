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
	//ui.setup();
};

//--------------------------------------------------------------
void myClassB::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddMinimizerToggle(false);
			ui.AddAutoResizeToggle(true);

			ui.AddGroup(params, SurfingGuiGroupStyle_Collapsed);

			ui.EndWindow();
		}
	}
	ui.End();
};