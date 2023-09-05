#include "myClassA.h"

//--------------------------------------------------------------
myClassA::myClassA() {
	setup();
}

//--------------------------------------------------------------
myClassA::~myClassA() {
}

//--------------------------------------------------------------
void myClassA::setup()
{
	params2.setName("paramsGroupA");
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));

	//--

	// Can be omitted in many scenarios..
	//ui.setup();
}

//--------------------------------------------------------------
void myClassA::draw()
{
	if (!bGui) return;

	//ui.Begin(); // Note that we could avoid Begin/End bc only drawing this window.
	{
		if (ui.BeginWindow(bGui))
		{
			ui.AddGroup(params2);

			ui.EndWindow();
		}
	}
	//ui.End();
}