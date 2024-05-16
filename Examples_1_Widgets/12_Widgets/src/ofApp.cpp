#include "ofApp.h"

#define MAX_D 500.0f

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	//ofSetWindowPosition(-1920, 25);

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
	value.set("value", 0.f, -MAX_D, MAX_D);
	valueMin.set("valueMin", 0.f, -MAX_D, MAX_D);
	valueMax.set("valueMax", 0.f, -MAX_D, MAX_D);
	pos_1.set("pos_1", glm::vec3(0.f), glm::vec3(-MAX_D), glm::vec3(MAX_D));
	rot_1.set("rot_1", glm::vec3(0.f), glm::vec3(-2.f * MAX_D), glm::vec3(2.f * MAX_D));
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
	indexExpanded.set("SELECT EXPANDED", 0, 0, 4);

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
	params1.add(indexExpanded);

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
	//can be omitted in many scenarios
	ui.setup();

	//--

	// Make some styling.
	// Will be used ONLY when populating widgets on groups content.
	{
		ui.clearStyles();
		ui.AddStyle(color1, OFX_IM_COLOR_INPUTS_NO_ALPHA);
		ui.AddStyle(color2, OFX_IM_COLOR_INPUTS_NO_ALPHA);
	}

	//--

	// A simple callback example
	ofAddListener(params1.parameterChangedE(), this, &ofApp::Changed);

	// Load session settings
	ofxImGuiSurfing::load(params1);
	ofxImGuiSurfing::load(params2);
	ofxImGuiSurfing::load(params3);
	ofxImGuiSurfing::load(params4);
}

//--------------------------------------------------------------
void ofApp::Changed(ofAbstractParameter& e)
{
	std::string name = e.getName();
	ofLogNotice("ofApp") << " " << name << " : " << e;

	if (name == bGui.getName()) {}
	if (name == bGui_1.getName()) {}
	if (name == bGui_2.getName()) {}
	if (name == bGui_3.getName()) {}
	if (name == bGui_4.getName()) {}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(color1);

	//--

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
		ui.AddLabelHuge("Examples/\n01_Widgets_Simple", false, true);

		ui.AddLabelBig("> Helpers", true, true);

		// The manager has some useful params for common functions.

		// The minimize toggle will help us to hide stuff on our windows
		// to simplify a bit the GUI when some widgets are not required to be visible.
		ui.Add(ui.bMinimize, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
		ui.AddSpacingSeparated();

		// Align Helpers Window
		ui.Add(ui.bGui_Aligners, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
		
		ui.AddSpacing();
		ui.Add(bConstraint, OFX_IM_TOGGLE_BIG_BORDER_BLINK);

		//--

		if (!ui.bMinimize) // -> We will use an 'if' when we want to hide some widgets zone.
		{
			ui.AddSpacingSeparated();

			ui.Add(ui.bExtra, OFX_IM_TOGGLE_ROUNDED);
			if (ui.bExtra)
			{
				ui.Indent();
				{
					ui.Add(ui.bHelp, OFX_IM_TOGGLE_ROUNDED);
					ui.AddTooltip("Enables some Tooltips");
					ui.Add(ui.bHelpInternal, OFX_IM_TOGGLE_ROUNDED);
					ui.Add(ui.bKeys, OFX_IM_TOGGLE_ROUNDED);
					ui.Add(ui.bAutoResize, OFX_IM_TOGGLE_ROUNDED);
					ui.Indent();
					ui.Add(bConstraint, OFX_IM_TOGGLE_ROUNDED_SMALL);
					ui.Unindent();

					ui.AddSpacingSeparated();

					ui.Add(ui.bAdvanced, OFX_IM_TOGGLE_ROUNDED);
					if (ui.bAdvanced)
					{
						ui.Indent();
						{
							ui.Add(ui.bDebug, OFX_IM_TOGGLE_ROUNDED_MINI);
							ui.Add(ui.bLog, OFX_IM_TOGGLE_ROUNDED_MINI);
							ui.Add(ui.bMouseWheel, OFX_IM_TOGGLE_ROUNDED_MINI);
						}
						ui.Unindent();
					}
				}
				ui.Unindent();
			}
		}

		ui.AddSpacingBigSeparated(); // space separated

		//if (!ui.bMinimize)
		{
			ui.AddLabelHuge("> Show Windows", true, true);

			ui.Indent(); // indent
			{
				ui.Add(bGui_1, OFX_IM_TOGGLE_ROUNDED_BIG);
				if (ui.bHelp) ui.AddTooltip("Some widgets");

				ui.Add(bGui_2, OFX_IM_TOGGLE_ROUNDED_BIG);
				if (ui.bHelp) ui.AddTooltip("Some ImGui Raw");

				ui.Add(bGui_3, OFX_IM_TOGGLE_ROUNDED_BIG);
				if (ui.bHelp) ui.AddTooltip("H & V Sliders");

				ui.Add(bGui_4, OFX_IM_TOGGLE_ROUNDED_BIG);
				if (ui.bHelp) ui.AddTooltip("Sliders & Knobs");
			}
			ui.Unindent(); // unindent
		}

		ui.AddSpacingBig();

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow1()
{
	if (bGui_1 && bConstraint) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;
	//-> Constraint next window dimensions to be smaller.
	// Will limit the size and auto expanding size on this situation.

	if (ui.BeginWindow(bGui_1))
	{
		if (!ui.bMinimize)
		{
			ui.AddLabelHuge("> A Multidim Splitted", true, true);
			ui.Add(pos_1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);//split components
			ui.AddSpacingBigSeparated();

			ui.Add(lineWidth2);//no arg. default style
			ui.Add(separation2);//no arg. default style
			ui.AddSpacingBigSeparated();
		}

		//--

		ui.AddLabelBig("An ImGui Raw Tree with Styles Engine");

		static bool bOpen = true;
		ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
		if (ImGui::CollapsingHeader("EDIT", _flagw))
		{
			// When using raw trees,
			// It's required to refresh indenting / responsive layout width!
			// That's to not break the responsive layouting engine.
			ui.refreshLayout();

			ui.AddSpacing();

			ImGui::PushButtonRepeat(true); // -> Re trig when maintained click!
			{
				if (ui.Add(bPrevious, OFX_IM_TOGGLE_BIG, 2, true)) // Two widgets/row. Next widget on same line.
				{
					// clicked
					bPrevious = false;
					speed3 = speed3 - ((speed3.getMax() - speed3.getMin()) * 0.100f);
					speed3 = ofClamp(speed3--, speed3.getMin(), speed3.getMax());
				}
				if (ui.Add(bNext, OFX_IM_TOGGLE_BIG, 2))
				{
					// clicked
					bNext = false;
					speed3 = speed3 + ((speed3.getMax() - speed3.getMin()) * 0.100f);
					speed3 = ofClamp(speed3, speed3.getMin(), speed3.getMax());
				}
			}
			ImGui::PopButtonRepeat();

			ui.AddSpacingSeparated();

			ui.Add(speed3, OFX_IM_VSLIDER_NO_LABELS); // hide labels
			ui.Add(speed4, OFX_IM_VSLIDER_NO_LABELS);

			if (!ui.bMinimize)
			{
				ui.AddSpacingSeparated();
				ui.AddGroup(params2);
				ui.AddGroup(params4);
				ui.AddSpacingBig();
			}
		}

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow2()
{
	if (bGui_2 && bConstraint) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;

	if (ui.BeginWindow(bGui_2))
	{
		ui.AddLabelBig("> ImGui Raw without Styles Engine");

		// This is raw ImGui notation:
		static bool bOpen = true;//force open
		ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
		_flagt |= ImGuiTreeNodeFlags_Framed;
		if (ImGui::TreeNodeEx("EXPAND", _flagt))
		{
			ui.refreshLayout();//as we used a raw ImGui::Tree, we need to check/update layout manually!

			// statics vars are useful sometimes for fast prototyping on ImGui
			static ofParameter<bool> bBig{ "Big", false };

			if (!ui.bMinimize)
			{
				//ImGui::Checkbox("Big", (bool*)&bBig.get());
				ui.Add(bBig, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
				ImGui::Spacing();

				ImGui::TextWrapped("> Four custom V SLIDERS!");
				ImGui::Spacing();
				ImGui::TextWrapped("> No auto Responsive! No Mouse Wheel!");
				ImGui::Spacing();
				ofxImGuiSurfing::AddSpacingBigSeparated();
			}

			float w = ui.getWidgetsWidth(4);//manually responsive
			float h = bBig ? 500 : 100;

			// custom sizes
			ofxImGuiSurfing::AddVSlider(speed3, ImVec2(w, h), true);
			ImGui::SameLine();
			ofxImGuiSurfing::AddVSlider(speed4, ImVec2(w, h), true);
			ImGui::SameLine();
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
	if (bGui_3 && bConstraint) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL;
	//-> Constrait next window dimensions to be bigger.
	// Will help to read the labels in this situation.

	if (ui.BeginWindow(bGui_3))
	{
		// Using columns
		ui.AddLabelHuge("> Four Vertical Sliders \n", true, true);
		ui.AddSpacing(); // space

		//TODO:
		// this is a workaround to align sliders counting labels..
		ImGui::Columns(4, "_", false);
		{
			ui.Add(speed3, OFX_IM_VSLIDER, 4, true);
			ImGui::NextColumn();
			ui.Add(speed4, OFX_IM_VSLIDER, 4, true);
			ImGui::NextColumn();
			ui.Add(size3, OFX_IM_VSLIDER, 4, true);
			ImGui::NextColumn();
			ui.Add(size4, OFX_IM_VSLIDER, 4);
		}
		ImGui::Columns(1);

		ui.AddSpacingSeparated();

		//--

		if (!ui.bMinimize)
		{
			ui.AddLabelBig("> Four Vertical Sliders No Name", false, true);

			ui.Add(speed3, OFX_IM_VSLIDER_NO_NAME, 4, true);
			ui.Add(speed4, OFX_IM_VSLIDER_NO_NAME, 4, true);
			ui.Add(size3, OFX_IM_VSLIDER_NO_NAME, 4, true);
			ui.Add(size4, OFX_IM_VSLIDER_NO_NAME, 4);
			ui.AddSpacingSeparated();
		}

		ui.AddLabelHuge("> Four Horizontal Sliders Custom", false, true);
		ui.Add(speed3, OFX_IM_HSLIDER_NO_NAME);
		ui.Add(speed4, OFX_IM_HSLIDER_NO_LABELS);
		ui.Add(size3, OFX_IM_HSLIDER_SMALL_NO_NUMBER);
		ui.Add(size4, OFX_IM_HSLIDER_SMALL);

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow4()
{
	if (bGui_4 && bConstraint) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MEDIUM;
	//-> Constraint next window dimensions to be bigger.
	// Will help to read the labels in this situation.

	if (ui.BeginWindow(bGui_4))
	{
		if (!ui.bMinimize)
		{
			ui.AddLabelBig("> Two Horizontal Sliders. Without Labels in One Row", false, true);
			ui.Add(speed3, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, true);
			ui.Add(speed4, OFX_IM_HSLIDER_SMALL_NO_LABELS, 2, false);
			ui.AddSpacingSeparated();
		}

		ui.AddLabelHuge("> Four Knobs", false, true);
		ui.Add(speed3, OFX_IM_KNOB, 4, true);
		ui.Add(speed4, OFX_IM_KNOB, 4, true);
		ui.Add(size3, OFX_IM_KNOB, 4, true);
		ui.Add(size4, OFX_IM_KNOB, 4);
		ui.AddSpacingBigSeparated();

		//--

		// https://github.com/ocornut/imgui/issues/1131
		ui.AddLabelBig("> Three Expandable Groups / Trees ", false, true);
		{
			static ImGuiCond cond = ImGuiCond_None;
			static string label = "";

			bool open1 = false;
			bool open2 = false;
			bool open3 = false;

			if (ui.Add(indexExpanded)) cond = ImGuiCond_Always;
			ui.AddLabel(label, true, true);

			switch (indexExpanded)
			{
			case 0: label = "expand none"; break;
			case 1: open1 = true; label = "expand group one"; break;
			case 2: open2 = true; label = "expand group two"; break;
			case 3: open3 = true; label = "expand group three"; break;
			case 4: open1 = open2 = open3 = true; label = "expand all"; break;
			}

			ui.AddGroup(params2, open1, cond);
			ui.AddGroup(params3, open2, cond);
			ui.AddGroup(params4, open3, cond);
			ui.EndWindow();

			if (cond == ImGuiCond_Always) { cond = ImGuiCond_Once; }
		}
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
		ofxImGuiSurfing::ImGui_ThemeXemu();
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
	ofxImGuiSurfing::save(params1);
	ofxImGuiSurfing::save(params2);
	ofxImGuiSurfing::save(params3);
	ofxImGuiSurfing::save(params4);

	ofRemoveListener(params1.parameterChangedE(), this, &ofApp::Changed);
}