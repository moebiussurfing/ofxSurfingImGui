#include "ofApp.h"

#define MAX_CAMERA_DISTANCE 500.0f

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowPosition(-1920, 25);
	ofSetWindowShape(1920, 1080 - 25);

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
	position.set("Position", glm::vec3(0.f), glm::vec3(-MAX_CAMERA_DISTANCE), glm::vec3(MAX_CAMERA_DISTANCE));
	rotation.set("Rotation", glm::vec3(0.f), glm::vec3(-2.f * MAX_CAMERA_DISTANCE), glm::vec3(2.f * MAX_CAMERA_DISTANCE));
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

	//--

	// ImGui

	// Instantiate

	guiManager.setup();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::draw()
{
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
		guiManager.AddLabelHuge("Examples/\n01_Widgets\nBasic");
		guiManager.Add(guiManager.bMinimize, OFX_IM_TOGGLE_ROUNDED_MEDIUM);

		guiManager.AddLabelHuge("> Show Windows");

		guiManager.Add(bGui_1, OFX_IM_TOGGLE_ROUNDED_BIG);
		guiManager.AddTooltip("Some widgets");

		guiManager.Add(bGui_2, OFX_IM_TOGGLE_ROUNDED_BIG);
		guiManager.AddTooltip("Some ImGui Raw");

		guiManager.Add(bGui_3, OFX_IM_TOGGLE_ROUNDED_BIG);
		guiManager.AddTooltip("H & V Sliders");

		guiManager.Add(bGui_4, OFX_IM_TOGGLE_ROUNDED_BIG);
		guiManager.AddTooltip("Sliders & Knobs");

		guiManager.drawAdvanced();

		guiManager.endWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawImWindow1()
{
	if (guiManager.beginWindow(bGui_1))
	{
		if (!guiManager.bMinimize)
		{
			guiManager.AddLabelBig("> Two Multidims \nSplitted and foldered");
			guiManager.Add(position, OFX_IM_MULTIDIM_SPLIT_SLIDERS);//split components
			guiManager.Add(rotation, OFX_IM_MULTIDIM_SPLIT_SLIDERS_FOLDERED);//split components
			guiManager.AddSpacingBigSeparated();

			guiManager.Add(lineWidth2);//no arg. default style
			guiManager.Add(separation2);//no arg. default style

			guiManager.AddSpacingBigSeparated();
		}

		//--

		guiManager.AddLabelBig("> An ImGui Raw \nTree with Styles Engine");

		if (ImGui::CollapsingHeader("EDIT", ImGuiWindowFlags_None))
		{
			// When using raw trees,
			// It's required to refresh indenting/responsive layout width!
			// That's to not break the responsive layouting engine.
			guiManager.refreshLayout();

			guiManager.AddSpacingBig();

			guiManager.Add(bPrevious, OFX_IM_TOGGLE_BIG, 2, true);//next on same line
			guiManager.Add(bNext, OFX_IM_TOGGLE_BIG, 2);
			
			guiManager.AddSpacingSeparated();

			guiManager.Add(speed3, OFX_IM_VSLIDER_NO_LABELS);// hide labels
			guiManager.Add(speed4, OFX_IM_VSLIDER_NO_LABELS);
			
			guiManager.AddSpacingSeparated();

			if (!guiManager.bMinimize)
			{
				guiManager.AddLabelBig("> Two \nofParameter\nGroup's");

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
	if (guiManager.beginWindow(bGui_2))
	{
		guiManager.AddLabelBig("> ImGui Raw without Styles Engine");

		if (ImGui::TreeNodeEx("EXPAND", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (!guiManager.bMinimize)
			{
				ImGui::TextWrapped("> Four custom V SLIDERS!");
				ImGui::Spacing();
				ImGui::TextWrapped("> No auto Responsive! No Mouse Wheel!");
				ImGui::Spacing();
				ofxImGuiSurfing::AddSpacingBigSeparated();
			}

			float w = guiManager.getWidgetsWidth(2);//manually responsive
			float h = 200;

			//custom sizes
			ofxImGuiSurfing::AddVSlider(speed3, ImVec2(w, h), true);
			ImGui::SameLine();
			ofxImGuiSurfing::AddVSlider(speed4, ImVec2(w, h), true);

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
	if (guiManager.beginWindow(bGui_3))
	{
		if (!guiManager.bMinimize)
		{
			guiManager.AddLabelBig("> Four Vertical Sliders No Labels");

			guiManager.Add(speed3, OFX_IM_VSLIDER_NO_LABELS, 4, true);
			guiManager.Add(speed4, OFX_IM_VSLIDER_NO_LABELS, 4, true);
			guiManager.Add(size3, OFX_IM_VSLIDER_NO_LABELS, 4, true);
			guiManager.Add(size4, OFX_IM_VSLIDER_NO_LABELS, 4);

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

		guiManager.Add(speed3, OFX_IM_KNOB, 2, true);
		guiManager.Add(speed4, OFX_IM_KNOB, 2);
		
		guiManager.AddSpacing();

		guiManager.Add(size3, OFX_IM_KNOB, 2, true);
		guiManager.Add(size4, OFX_IM_KNOB, 2);

		guiManager.AddSpacingBigSeparated();
		
		guiManager.AddLabelBig("> An \nofParameter\nGroup");

		guiManager.AddGroup(params3);

		guiManager.endWindow();
	}
}