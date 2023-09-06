#include "myClassD.h"

//--------------------------------------------------------------
myClassD::myClassD() {
	setup();
}

//--------------------------------------------------------------
myClassD::~myClassD() {
}

//--------------------------------------------------------------
void myClassD::setup()
{
	parametersD.setName("paramsGroupD");
	parametersD.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	parametersD.add(separation.set("separation", 50, 1, 100));
	parametersD.add(speed.set("speed", 0.5, 0, 1));
	parametersD.add(shapeType.set("shapeType", 0, -50, 50));
	parametersD.add(size.set("size", 100, 0, 100));
	parametersD.add(amount.set("amount", 10, 0, 25));
}

//--------------------------------------------------------------
void myClassD::drawImGui(ofxSurfingGui* ui)
{
	if (ui == nullptr) return;
	if (!bGui) return;

	if (ui->BeginWindow(bGui))
	{
		ui->AddGroup(parametersD);
		ui->Add(speed, OFX_IM_HSLIDER);
		ui->Add(shapeType, OFX_IM_HSLIDER_SMALL_NO_LABELS);
		ui->AddTooltip(shapeType); // a tooltip with name and value

		ui->EndWindow();
	}
}