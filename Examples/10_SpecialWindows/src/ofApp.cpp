#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowPosition(-1920, 25);

	ofSetLogLevel("ofxSurfingImGui", OF_LOG_SILENT);

	// Parameters
	setupParams();

	//--

	setup_ImGui();
}

//--------------------------------------------------------------
void ofApp::setupParams()
{
	params_0.setName("paramsGroup_0");
	params_0.add(bEnable0.set("Enable0", false));
	params_0.add(speed0.set("speed0", 0.5, 0, 1));
	params_0.add(bPrevious0.set("<", false));
	params_0.add(bNext0.set(">", false));

	params_1.setName("paramsGroup_1");
	params_1.add(bEnable1.set("Enable1", false));
	params_1.add(shapeType1.set("shapeType1", 0, -50, 50));
	params_1.add(size1.set("size1", 100, 0, 100));
	params_1.add(lineWidth1.set("lineWidth1", 0.5, 0, 1));
	params_1.add(separation1.set("separation1", 50, 1, 100));

	params_2.setName("paramsGroup_2");
	params_2.add(bEnable2.set("Enable2", false));
	params_2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params_2.add(size2.set("size2", 100, 0, 100));
	params_2.add(amount2.set("amount2", 10, 0, 25));

	params_3.setName("paramsGroup_3");
	params_3.add(bEnable3.set("Enable3", false));
	params_3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params_3.add(speed3.set("speed3", 0.5, 0, 1));
	params_3.add(separation3.set("separation3", 50, 1, 100));
}

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	bGui.set("ofApp", true);

	// Optional: 
	// Customize name to avoid multiple instances collide.
	// Will create sub folder into bin/data/myOfApp/Gui
	ui.setName("myOfApp");

	// Queue windows
	ui.addWindowSpecial("myWindow 0");
	ui.addWindowSpecial("myWindow 1");
	ui.addWindowSpecial("myWindow 2");
	ui.addWindowSpecial("myWindow 3");
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return;

	ui.Begin();
	{
		draw_MainWindow();

		// special windows
		draw_SurfingWidgets_0();
		draw_SurfingWidgets_1();
		draw_SurfingWidgets_2();
		draw_SurfingWidgets_3();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::draw_MainWindow() {

	// Notice that this is a standard window,
	// not an special window nor their features.
	if (ui.BeginWindow(bGui))
	{
		ui.AddLabelBig("> Hello \nfrom ofApp");
		ui.AddSpacingSeparated();

		// Optional: 
		// Common internal useful toggles
		ui.AddMinimizerToggle();
		ui.AddAutoResizeToggle();
		ui.AddSpacingBigSeparated();

		// Optional: 
		ui.DrawWidgetsResetUI();
		ui.DrawWidgetsGlobalScaleMini();
		ui.AddSpacingBigSeparated();

		// Optional: 
		// Some internal useful common bool toggles are exposed:
		// the main window who contains almost all the others.
		ui.Add(ui.bGui_Organizer, OFX_IM_TOGGLE_ROUNDED);
		ui.Add(ui.bGui_Aligners, OFX_IM_TOGGLE_ROUNDED_MINI);
		ui.Add(ui.bGui_SpecialWindows, OFX_IM_TOGGLE_ROUNDED_MINI);

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_0()
{
	if (ui.BeginWindowSpecial(0))
	{
		ui.AddLabelBig("> Special\nWindow 0");
		ui.Add(bPrevious0, OFX_IM_TOGGLE_BIG, 2, true);//next on same line
		ui.Add(bNext0, OFX_IM_TOGGLE_BIG, 2);
		ui.AddGroup(params_0);
		if(bEnable0) ui.Add(speed0, OFX_IM_VSLIDER_NO_LABELS);// hide labels

		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_1()
{
	if (ui.BeginWindowSpecial(1))
	{
		ui.AddLabelBig("> Special\nWindow 1");
		ui.AddGroup(params_1);
		if (bEnable1) {
			ui.Add(lineWidth1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
			ui.Add(separation1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
			ui.Add(shapeType1, OFX_IM_VSLIDER_NO_LABELS, 4, true);
			ui.Add(size1, OFX_IM_VSLIDER_NO_LABELS, 4);
		}

		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_2()
{
	if (ui.BeginWindowSpecial(2))
	{
		ui.AddLabelBig("> Special\nWindow 2");
		ui.Add(shapeType2, OFX_IM_KNOB_TICKKNOB, 2, true);
		ui.Add(amount2, OFX_IM_KNOB_DOTKNOB, 2);
		ui.Add(size2, OFX_IM_VSLIDER_NO_LABELS);
		ui.AddSpacingBigSeparated();
		ui.AddGroup(params_2);

		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_3()
{
	if (ui.BeginWindowSpecial(3))
	{
		ui.AddLabelBig("> Special\nWindow 3");
		ui.AddGroup(params_3);
		if (bEnable3) {
			ui.AddSpacingSeparated();
			ui.Add(size2, OFX_IM_HSLIDER_BIG);
			ui.Add(lineWidth3, OFX_IM_HSLIDER);
			ui.Add(speed3, OFX_IM_HSLIDER_SMALL);
			ui.Add(separation3, OFX_IM_HSLIDER_MINI);
		}

		ui.EndWindowSpecial();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ui.save();
}