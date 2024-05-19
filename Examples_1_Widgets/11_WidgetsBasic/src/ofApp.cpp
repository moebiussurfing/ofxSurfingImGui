#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	bGui.set("bGui", true);

	// These toggles are very useful to handle the windows show/hide states.
	// Improves and speed-up also the API and some Layout Presets Engine aspects.
	bGui_1.set("Window 1", true);
	bGui_2.set("Window 2", true);
	bGui_3.set("Window 3", true);
	bGui_4.set("Window 4", true);

	//--

	// Parameters
	setupParams();

	//--

	//// Optional ImGui
	//// Set mouse wheel natural direction
	//ui.setMouseWheelFlip(true);
}

//--------------------------------------------------------------
void ofApp::setupParams()
{
	bPrevious.set("<");
	bNext.set(">");

	value.set("value", 0.f, -MAX_D, MAX_D);
	valueMin.set("valueMin", 0.f, -MAX_D, MAX_D);
	valueMax.set("valueMax", 0.f, -MAX_D, MAX_D);
	position.set("Position", glm::vec3(0.f), glm::vec3(-MAX_D), glm::vec3(MAX_D));
	rotation.set("Rotation", glm::vec3(0.f), glm::vec3(-2.f * MAX_D), glm::vec3(2.f * MAX_D));
	lineWidth2.set("linew2", 0.5, 0, 1);
	separation2.set("sep2", 50, 1, 100);
	shapeType2.set("shape2", 0, -50, 50);
	amount2.set("amount2", 10, 0, 25);
	speed3.set("speed3", 0.5, 0, 1);
	knob1.set("knob1", 0.5f, 0.f, 1.0f);
	knob2.set("knob2", 5.f, -10.f, 10.0f);
	shapeType3.set("shape3", 0, -50, 50);
	size3.set("size3", 100, 0, 100);
	shapeType4.set("shape4", 0, -50, 50);
	size4.set("size4", 100, 0, 100);
	lineWidth4.set("linew4", 0.5, 0, 1);
	separation4.set("sep4", 50, 1, 100);
	speed4.set("speed4", 0.5, 0, 1);
	color1.set("color1", ofColor(0, 0, 255, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255));
	color2.set("color2", ofFloatColor(0, 1, 0, 1), ofColor(0, 0, 0, 0), ofColor(1, 1, 1, 1));

	//--

	// Groups

	params1.setName("params1");
	params2.setName("params2");
	params3.setName("params3");
	params4.setName("params4");

	params1.add(bGui_1);
	params1.add(bGui_2);
	params1.add(bGui_3);
	params1.add(bGui_4);
	params1.add(position);
	params1.add(rotation);

	params2.add(lineWidth2);
	params2.add(separation2);

	params3.add(speed3);
	params3.add(shapeType3);
	params3.add(knob1);
	params3.add(knob2);
	params3.add(size3);

	params4.add(size4);
	params4.add(speed4);
	params4.add(shapeType4);
	params4.add(lineWidth4);
	params4.add(separation4);
	params4.add(color1);
	params4.add(color2);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return;

	ui.Begin();
	{
		drawImWindowMain();

		drawImWindow1();
		drawImWindow2();
		drawImWindow3();
		drawImWindow4();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawImWindowMain()
{
	if (ui.BeginWindow(bGui))
	{
		ui.AddLabelBig("Examples/\n01_\nWidgetsBasic");
		ui.AddSpacingBig();

		ui.AddMinimizerToggle();
		ui.AddTooltip("This internal toggle is very useful \nconditioning hiding some stuff \nto simplify our gui layout.");
		if (ui.isMaximized()) {
			ui.AddAutoResizeToggle();
			ui.Add(ui.bGui_Aligners, OFX_IM_TOGGLE_ROUNDED_MINI);
		}

		ui.AddSpacingSeparated();

		ui.AddLabelBig("> Show \nWindows", true, true);
		ui.AddSpacing();

		ui.Add(bGui_1, OFX_IM_TOGGLE_ROUNDED_BIG);
		ui.AddTooltip("Some widgets");

		ui.Add(bGui_2, OFX_IM_TOGGLE_ROUNDED_BIG);
		ui.AddTooltip("Some ImGui Raw");

		ui.Add(bGui_3, OFX_IM_TOGGLE_ROUNDED_BIG);
		ui.AddTooltip("H & V Sliders");

		ui.Add(bGui_4, OFX_IM_TOGGLE_ROUNDED_BIG);
		ui.AddTooltip("Sliders & Knobs");
		
		//--

		if (ui.isMaximized()) {

			// An useful bundle of internal control/settings
			ui.AddSpacingSeparated();
			ui.DrawAdvancedBundle();
		}

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow1()
{
	// We can constraint next window shape
	// that's useful when long widget names can resize the window too much,
	// bc we are using auto resize flags in most of the case.
	static bool bConstraint = false;
	// take care that window is enabled (bGui_1), to not apply constraints to other window instead!
	if (bGui_1 && bConstraint) 
	{
		IMGUI_SUGAR__WINDOWS_CONSTRAINTS;
	}

	if (ui.BeginWindow(bGui_1))
	{
		if (!ui.bMinimize)
		{
			// This is a helper to populate widgets 
			// from raw cpp types, not an ofParameter.
			// could be useful sometimes.
			ui.AddToggle("Constraint", bConstraint);
			ui.AddTooltip("We can constraint this Window shape \n(applied to next window shape \nafter the\nIMGUI_SUGAR__WINDOWS_CONSTRAINTS \ncall!)");
			ui.AddSpacingBigSeparated();

			ui.AddLabelHuge("Multidims", true, true);
			
			ui.AddLabelBig("> One default for Multidim");
			ui.Add(rotation); // default
			ui.AddSpacingBigSeparated();

			ui.AddLabelBig("> One Multidim \nSplitted");
			ui.Add(rotation, OFX_IM_MULTIDIM_SPLIT_SLIDERS); // split components
			ui.AddSpacingBigSeparated();

			ui.AddLabelBig("> One Multidim \nSplitted and foldered");
			ui.Add(position, OFX_IM_MULTIDIM_SPLIT_SLIDERS_FOLDERED); // split components
			ui.AddSpacingBigSeparated();

			ui.Add(lineWidth2); // no arg. default style
			ui.Add(separation2); // no arg. default style
			ui.AddSpacingBigSeparated();
		}

		//--

		ui.AddLabelBig("> An ImGui Raw \nTree with Styles Engine");

		if (ui.BeginTree("EDIT")) // This is helped tree using the add-on API
		{
			// When using raw trees,
			// It's required to refresh indenting/responsive layout width!
			// That's to not break the responsive layouting engine.
			ui.refreshLayout();

			ui.AddSpacing();

			// ofParama<void> types requires button style! 
			// will not work with toggle styles!
			ui.Add(bPrevious, OFX_IM_BUTTON_BIG, 2, true); // next on same line
			ui.Add(bNext, OFX_IM_BUTTON_BIG, 2);

			if (!ui.bMinimize)
			{
				ui.AddSpacingSeparated();
				ui.AddLabelBig("> Two \nofParameter\nGroup's");
				ui.AddGroup(params2);
				ui.AddGroup(params4);
			}

			ui.EndTree();
		}

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow2()
{
	if (ui.BeginWindow(bGui_2))
	{
		ui.AddLabelHuge("> ImGui Raw without Styles Engine");
		ui.AddSpacingBig();

		// We can make the header bigger
		ui.PushFontStyle(OFX_IM_FONT_BIG);
		bool b = ImGui::TreeNodeEx("EXPAND", ImGuiTreeNodeFlags_DefaultOpen);
		ui.AddSpacingBig();
		ui.PopFontStyle();

		if (b) // This is a raw ImGui tree
		{
			if (!ui.bMinimize)
			{
				ImGui::TextWrapped("> Four custom V SLIDERS!");
				ImGui::Spacing();
				ImGui::TextWrapped("> No auto Responsive! No Mouse Wheel!");
				ImGui::Spacing();
				ofxImGuiSurfing::AddSpacingBigSeparated();
			}

			float w = ui.getWidgetsWidth(2); // manually responsive. 2 widgets (half size) per row.
			float h = 200;

			// custom sizes
			ofxImGuiSurfing::AddVSlider(speed3, ImVec2(w, h), true);
			ImGui::SameLine();
			ofxImGuiSurfing::AddVSlider(speed4, ImVec2(w, h), true);

			ofxImGuiSurfing::AddVSlider(size3, ImVec2(w, h), true);
			ImGui::SameLine();
			ofxImGuiSurfing::AddVSlider(size4, ImVec2(w, h), true);

			ImGui::TreePop();
		}

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow3()
{
	if (ui.BeginWindow(bGui_3))
	{
		if (!ui.bMinimize)
		{
			ui.AddLabelBig("> Four Vertical Sliders \nNo Labels but with Tooltips \nwith value and name.");
			ui.AddSpacing();
			ui.Add(speed3, OFX_IM_VSLIDER_NO_LABELS, 4, true);
			ui.AddTooltip(speed3, true, false);
			ui.Add(speed4, OFX_IM_VSLIDER_NO_LABELS, 4, true);
			ui.AddTooltip(speed4, true, false);
			ui.Add(size3, OFX_IM_VSLIDER_NO_LABELS, 4, true);
			ui.AddTooltip(size3, true, false);
			ui.Add(size4, OFX_IM_VSLIDER_NO_LABELS, 4);
			ui.AddTooltip(size4, true, false);

			ui.AddSpacingSeparated();
		}

		ui.AddLabelHuge("> Four Horizontal Sliders Custom");
		ui.AddSpacing();
		ui.Add(speed3, OFX_IM_HSLIDER_NO_NAME);
		ui.Add(speed4, OFX_IM_HSLIDER_NO_LABELS);
		ui.AddTooltip(speed4);//no name
		ui.Add(size3, OFX_IM_HSLIDER_SMALL_NO_NUMBER);
		ui.Add(size4, OFX_IM_HSLIDER_SMALL);

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow4()
{
	if (ui.BeginWindow(bGui_4))
	{
		if (!ui.bMinimize)
		{
			ui.AddLabelBig("> Two Horizontal Sliders. \nWithout Labels in One Row\nwith a Tooltip");
			ui.AddSpacingBig();
			ui.Add(speed3, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, true);
			ui.AddTooltip(speed3, true, false);
			ui.Add(speed4, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, false);
			ui.AddTooltip(speed4, true, false);
			ui.AddSpacingBig();

			ui.AddSpacingSeparated();
		}

		ui.AddLabelHuge("> Four Knobs");

		SurfingGuiTypes s = OFX_IM_KNOB_TICKKNOB;
		//SurfingGuiTypes s = OFX_IM_KNOB_STEPPEDKNOB;

		ui.Add(speed3, s, 2, true);
		ui.Add(speed4, s, 2);
		ui.AddSpacing();
		ui.Add(size3, s, 2, true);
		ui.Add(size4, s, 2);
		
		ui.AddSpacingBigSeparated();

		ui.AddLabelBig("> An \nofParameter\nGroup");
		ui.AddGroup(params3);

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}