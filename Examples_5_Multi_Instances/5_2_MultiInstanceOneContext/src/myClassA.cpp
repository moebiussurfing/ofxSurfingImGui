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
	parametersA.setName("paramsGroupA");
	parametersA.add(shapeType2.set("shapeType2", 0, -50, 50));
	parametersA.add(size2.set("size2", 100, 0, 100));
	parametersA.add(amount2.set("amount2", 10, 0, 25));
}

//--------------------------------------------------------------
void myClassA::drawImGui(ofxSurfingGui* ui)
{
	if (ui == nullptr) return;
	if (!bGui) return;

	if (ui->BeginWindow(bGui))
	{
		ui->AddGroup(parametersA);

		ui->EndWindow();
	}
}