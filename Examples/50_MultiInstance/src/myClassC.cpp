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
	if (ui == nullptr) return;
	if (!bGui) return;

	ui->Begin();
	{
		if (ui->BeginWindow(bGui))
		{
			ui->AddMinimizerToggle();
			ui->AddAutoResizeToggle();
			ui->AddSpacingBigSeparated();

			ui->AddGroup(params, SurfingGuiGroupStyle_Collapsed);;

			ui->AddSpacingHugeSeparated();
			ui->AddLabelHuge("ADVACED");
			ui->AddLabelBig("This is a passed (to C object) render function but defined in ofApp! (instead of inside the C class)");
			ui->AddLabel("std::function<void()>");

			if (functionDraw != nullptr) functionDraw();

			ui->EndWindow();
		}
	}
	ui->End();
};