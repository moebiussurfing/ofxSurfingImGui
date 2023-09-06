#include "myClassA.h"

//--------------------------------------------------------------
myClassA::myClassA() 
{
}

//--------------------------------------------------------------
myClassA::~myClassA()
{
}

//--------------------------------------------------------------
void myClassA::setup()
{
	parameters.setName("paramsGroupA");
	parameters.add(shapeType2.set("shapeType2", 0, -50, 50));
	parameters.add(size2.set("size2", 100, 0, 100));
	parameters.add(amount2.set("amount2", 10, 0, 25));

	//--

#if 0
	// Can be omitted in many scenarios..
	ui_.setup();
	ui_.startup();
#endif
}

//--------------------------------------------------------------
void myClassA::drawImGui()
{
	if (!bGui) return;

	ui_.Begin();
	{
		if (ui_.BeginWindow(bGui))
		{
			ui_.AddGroup(parameters);

			ui_.EndWindow();
		}
	}
	ui_.End();
}
