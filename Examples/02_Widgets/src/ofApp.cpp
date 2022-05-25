#include "ofApp.h"

#define MAX_CAMERA_DISTANCE 500.0f

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetWindowPosition(-1920, 25);

	//--

	bGui.set("bGui", true);

	// These toggles are very useful to handle the windows show/hide states.
	// Improves and speed-up also the API and some Layout Presets Engine aspects.
	bGui_1.set("Window 1", true);
	bGui_2.set("Window 2", true);
	bGui_3.set("Window 3", true);
	bGui_4.set("Window 4", true);

	//--

	// Parameters

	bPrevious.set("<", false);
	bNext.set(">", false);
	value.set("value", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
	valueMin.set("valueMin", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
	valueMax.set("valueMax", 0.f, -MAX_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
	pos_1.set("pos_1", glm::vec3(0.f), glm::vec3(-MAX_CAMERA_DISTANCE), glm::vec3(MAX_CAMERA_DISTANCE));
	rot_1.set("rot_1", glm::vec3(0.f), glm::vec3(-2.f * MAX_CAMERA_DISTANCE), glm::vec3(2.f * MAX_CAMERA_DISTANCE));
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
	params1.add(pos_1);
	params1.add(rot_1);

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

	//// -> Nesting Groups
	//params2.add(params3);
	//params1.add(params2);
	//params1.add(params4);

	//--

	// ImGui

	// Instantiate

	guiManager.setup();

	//--

	// Make some styling.
	// Will be used ONLY when populating widgets on groups content.
	{
		guiManager.clearStyles();
		guiManager.AddStyle(color1, OFX_IM_COLOR_NO_ALPHA);
		guiManager.AddStyle(color2, OFX_IM_COLOR_NO_NAME);
	}

	//--

	// Load session settings
	ofxSurfingHelpers::loadGroup(params1);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//ofClear(color1);

	//--

	if (!bGui) return;

	guiManager.begin();
	{
		drawImWindowMain();

		drawImWindow1();
		drawImWindow2();
		drawImWindow3();
		drawImWindow4();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawImWindowMain()
{
	if (guiManager.beginWindow(bGui))
	{
		guiManager.AddLabelHuge("Examples/\n01_Widgets_Simple");

		guiManager.AddLabelBig("> Helpers");

		// The manager has some useful params for common funcions.

		// The minimize toggle will help us to hide stuff on our winwows
		// to simplify a bit the GUI when some windgets are not required to be visible.
		guiManager.Add(guiManager.bMinimize, OFX_IM_TOGGLE_ROUNDED_MEDIUM);

		if (!guiManager.bMinimize) // -> We will use an 'if' when we want to hide some widgets zone.
		{
			guiManager.AddSpacingSeparated();

			guiManager.Add(guiManager.bExtra, OFX_IM_TOGGLE_ROUNDED);
			if (guiManager.bExtra)
			{
				guiManager.Indent();
				{
					guiManager.Add(guiManager.bHelp, OFX_IM_TOGGLE_ROUNDED);
					guiManager.AddTooltip("Enables some Tooltips");
					guiManager.Add(guiManager.bHelpInternal, OFX_IM_TOGGLE_ROUNDED);
					guiManager.Add(guiManager.bKeys, OFX_IM_TOGGLE_ROUNDED);
					guiManager.Add(guiManager.bAutoResize, OFX_IM_TOGGLE_ROUNDED);
					guiManager.Indent();
					guiManager.Add(bConstraint, OFX_IM_TOGGLE_ROUNDED_SMALL);
					guiManager.Unindent();

					guiManager.AddSpacingSeparated();

					guiManager.Add(guiManager.bAdvanced, OFX_IM_TOGGLE_ROUNDED);
					if (guiManager.bAdvanced)
					{
						guiManager.Indent();
						{
							guiManager.Add(guiManager.bDebug, OFX_IM_TOGGLE_ROUNDED_MINI);
							guiManager.Add(guiManager.bLog, OFX_IM_TOGGLE_ROUNDED_MINI);
							guiManager.Add(guiManager.bMouseWheel, OFX_IM_TOGGLE_ROUNDED_MINI);
						}
						guiManager.Unindent();
					}
				}
				guiManager.Unindent();
			}
		}

		guiManager.AddSpacingBigSeparated(); // space separted

		//if (!guiManager.bMinimize)
		{
			guiManager.AddLabelHuge("> Show Windows");

			guiManager.Indent(); // indent
			{
				guiManager.Add(bGui_1, OFX_IM_TOGGLE_ROUNDED_BIG);
				if (guiManager.bHelp) guiManager.AddTooltip("Some widgets");

				guiManager.Add(bGui_2, OFX_IM_TOGGLE_ROUNDED_BIG);
				if (guiManager.bHelp) guiManager.AddTooltip("Some ImGui Raw");

				guiManager.Add(bGui_3, OFX_IM_TOGGLE_ROUNDED_BIG);
				if (guiManager.bHelp) guiManager.AddTooltip("H & V Sliders");

				guiManager.Add(bGui_4, OFX_IM_TOGGLE_ROUNDED_BIG);
				if (guiManager.bHelp) guiManager.AddTooltip("Sliders & Knobs");
			}
			guiManager.Unindent(); // unindent
		}

		guiManager.AddSpacingBig();

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow1()
{
	//if (bConstraint) IMGUI_SUGAR__WINDOWS_CONSTRAINTS;
	//-> Constrait next window dimensions to be smaller.
	// Will limit the size and autoexpanding size on this situation.

	if (guiManager.beginWindow(bGui_1))
	{
		if (!guiManager.bMinimize)
		{
			guiManager.AddLabelBig("> A Multidim Splitted");
			guiManager.Add(pos_1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);//split components
			guiManager.AddSpacingBigSeparated();

			guiManager.Add(lineWidth2);//no arg. default style
			guiManager.Add(separation2);//no arg. default style
			guiManager.AddSpacingBigSeparated();
		}

		//--

		guiManager.AddLabel("An ImGui Raw Tree with Styles Engine");

		static bool bOpen = true;
		ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
		if (ImGui::CollapsingHeader("EDIT", _flagw))
		{
			// When using raw trees,
			// It's required to refresh indenting/responsive layout width!
			// That's to not break the responsive layouting engine.
			guiManager.refreshLayout();

			guiManager.AddSpacing();

			if (guiManager.Add(bPrevious, OFX_IM_TOGGLE_BIG, 2, true))//next on same line
			{
				bPrevious = false;
				speed3 = speed3 - ((speed3.getMax() - speed3.getMin()) * 0.100f);
				speed3 = ofClamp(speed3--, speed3.getMin(), speed3.getMax());
			}
			if (guiManager.Add(bNext, OFX_IM_TOGGLE_BIG, 2))
			{
				bNext = false;
				speed3 = speed3 + ((speed3.getMax() - speed3.getMin()) * 0.100f);
				speed3 = ofClamp(speed3, speed3.getMin(), speed3.getMax());
			}
			guiManager.AddSpacingSeparated();

			guiManager.Add(speed3, OFX_IM_VSLIDER_NO_LABELS);// hide labels
			guiManager.Add(speed4, OFX_IM_VSLIDER_NO_LABELS);
			guiManager.AddSpacingSeparated();

			if (!guiManager.bMinimize)
			{
				guiManager.AddGroup(params2);
				guiManager.AddGroup(params4);
				guiManager.AddSpacingBig();
			}
		}

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow2()
{
	if (bConstraint) IMGUI_SUGAR__WINDOWS_CONSTRAINTS_BIG;

	if (guiManager.beginWindow(bGui_2))
	{
		guiManager.AddLabelBig("> ImGui Raw without Styles Engine");

		static bool bOpen = true;//force open
		ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
		_flagt |= ImGuiTreeNodeFlags_Framed;
		if (ImGui::TreeNodeEx("EXPAND", _flagt))
		{
			// statics vars are useful sometimes for fast prototyping on ImGui
			static ofParameter<bool> bBig{ "Big", false };

			if (!guiManager.bMinimize)
			{
				ImGui::Checkbox("Big", (bool*)&bBig.get());
				ImGui::Spacing();

				ImGui::TextWrapped("> Four custom V SLIDERS!");
				ImGui::Spacing();
				ImGui::TextWrapped("> No auto Responsive! No Mouse Wheel!");
				ImGui::Spacing();
				ofxImGuiSurfing::AddSpacingBigSeparated();
			}

			float w = guiManager.getWidgetsWidth(4);//manually responsive
			float h = bBig ? 500 : 100;

			//custom sizes
			ofxImGuiSurfing::AddVSlider(speed3, ImVec2(w, h), true);
			ImGui::SameLine();
			ofxImGuiSurfing::AddVSlider(speed4, ImVec2(w, h), true);
			ImGui::SameLine();
			ofxImGuiSurfing::AddVSlider(size3, ImVec2(w, h), true);
			ImGui::SameLine();
			ofxImGuiSurfing::AddVSlider(size4, ImVec2(w, h), true);

			ImGui::TreePop();
		}

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow3()
{
	if (bConstraint) IMGUI_SUGAR__WINDOWS_CONSTRAINTS_BIG;
	//-> Constrait next window dimensions to be bigger.
	// Will helpo to read the labels in this situation.

	if (guiManager.beginWindow(bGui_3))
	{
		// Using columns
		guiManager.AddLabelHuge("> Four Vertical Sliders \n");
		guiManager.AddSpacing(); // space

		//TODO:
		// this is a worwaround toi align sliders counting labels..
		ImGui::Columns(4, "_", false);
		{
			guiManager.Add(speed3, OFX_IM_VSLIDER, 4, true);
			ImGui::NextColumn();
			guiManager.Add(speed4, OFX_IM_VSLIDER, 4, true);
			ImGui::NextColumn();
			guiManager.Add(size3, OFX_IM_VSLIDER, 4, true);
			ImGui::NextColumn();
			guiManager.Add(size4, OFX_IM_VSLIDER, 4);
		}
		ImGui::Columns(1);

		guiManager.AddSpacingSeparated();

		//--

		if (!guiManager.bMinimize)
		{
			guiManager.AddLabelBig("> Four Vertical Sliders No Name");

			guiManager.Add(speed3, OFX_IM_VSLIDER_NO_NAME, 4, true);
			guiManager.Add(speed4, OFX_IM_VSLIDER_NO_NAME, 4, true);
			guiManager.Add(size3, OFX_IM_VSLIDER_NO_NAME, 4, true);
			guiManager.Add(size4, OFX_IM_VSLIDER_NO_NAME, 4);
			guiManager.AddSpacingSeparated();
		}

		guiManager.AddLabelHuge("> Four Horizontal Sliders Custom");
		guiManager.Add(speed3, OFX_IM_HSLIDER_NO_NAME);
		guiManager.Add(speed4, OFX_IM_HSLIDER_NO_LABELS);
		guiManager.Add(size3, OFX_IM_HSLIDER_SMALL_NO_NUMBER);
		guiManager.Add(size4, OFX_IM_HSLIDER_SMALL);

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow4()
{
	if (bConstraint) IMGUI_SUGAR__WINDOWS_CONSTRAINTS_BIG;
	//-> Constrait next window dimensions to be bigger.
	// Will helpo to read the labels in this situation.

	if (guiManager.beginWindow(bGui_4))
	{
		if (!guiManager.bMinimize)
		{
			guiManager.AddLabelBig("> Two Horizontal Sliders. Without Labels in One Row");
			guiManager.Add(speed3, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, true);
			guiManager.Add(speed4, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, false);
			guiManager.AddSpacingSeparated();
		}

		guiManager.AddLabelHuge("> Four Knobs");
		guiManager.Add(speed3, OFX_IM_KNOB, 4, true);
		guiManager.Add(speed4, OFX_IM_KNOB, 4, true);
		guiManager.Add(size3, OFX_IM_KNOB, 4, true);
		guiManager.Add(size4, OFX_IM_KNOB, 4);

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;

	// Test some Themes
	if (key == '1') {
		ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();
	}
	if (key == '2') {
		ofxImGuiSurfing::ImGui_Xemu();
	}
	if (key == '3') {
		ofxImGuiSurfing::ImGui_ThemeYave();
	}
	if (key == '4') {
		ofxImGuiSurfing::ImGui_ThemeSequentity();
	}
	if (key == '5') {
		ofxImGuiSurfing::ImGui_ThemeModernDark();
	}
	if (key == '6') {
		ofxImGuiSurfing::ImGui_ThemeOlekristensen();
	}
}

//--------------------------------------------------------------
void ofApp::exit() {

	// Save session settings
	ofxSurfingHelpers::saveGroup(params1);
}