#include "myClassA.h"

//--------------------------------------------------------------
myClassA::myClassA() {
	setup();
};

//--------------------------------------------------------------
myClassA::~myClassA() {
};

//--------------------------------------------------------------
void myClassA::setup()
{
	params2.setName("paramsGroup2");
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));

	//--

	// Can be omitted in many scenarios..
	//ui.setup();
};

//--------------------------------------------------------------
void myClassA::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddGroup(params2);

			ui.EndWindow();
		}
	}
	ui.End();
};