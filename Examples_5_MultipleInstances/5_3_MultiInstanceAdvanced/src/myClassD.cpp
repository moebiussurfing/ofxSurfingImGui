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
	params.setName("paramsGroupD");
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
};

//--------------------------------------------------------------
void myClassD::draw(ofxSurfingGui* _ui)
{
	if (_ui == nullptr) return;
	//if (!bGui) return; // Note that we could avoid Begin/End bc only drawing this window.

	//_ui->Begin();
	{
		if (_ui->BeginWindow(bGui))
		{
			_ui->AddGroup(params);
			_ui->Add(speed, OFX_IM_HSLIDER);
			_ui->Add(shapeType, OFX_IM_HSLIDER_SMALL_NO_LABELS);
			_ui->AddTooltip(shapeType); // a tooltip with name and value

			_ui->EndWindow();
		}
	}
	//_ui->End();
};