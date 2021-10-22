#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	setup_ImGui();

	// Parameters
	params.setName("paramsGroup1");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params.add(indexPreset.set("Preset", 0, 0, 8));
	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable1.set("bEnable1", false));
	params.add(bEnable2.set("Enable2", false));
	params.add(bEnable3.set("Enable3", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params2.add(params3);
	params.add(params2);

	indexPreset.makeReferenceTo(surfingGradient.indexPreset);
}

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	guiManager.setup();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(surfingGradient.color);

	//-

	guiManager.begin();
	{
		{
			// Surfing Widgets 1

			ImGuiColorEditFlags _flagw;
			string name;

			_flagw = guiManager.bAutoResize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;

			name = "SurfingWidgets 1";
			guiManager.beginWindow(name.c_str(), NULL, _flagw);
			{
				// Customize font
				ofxImGuiSurfing::AddParameter(bEnable1);
				ofxImGuiSurfing::AddTooltip("Enable to customize Font.", guiManager.bHelp);

				// Range
				static float f1 = -0.5f;
				static float f2 = 0.75f;
				ofxImGuiSurfing::RangeSliderFloat("Range", &f1, &f2, -1.0f, 1.0f, "(%.3f, %.3f)");

				// Sliders
				ofxImGuiSurfing::AddBigSlider(valueKnob1);
				guiManager.Add(valueKnob2, OFX_IM_HSLIDER);

				// Knobs
				guiManager.Add(valueKnob1, OFX_IM_KNOB, 4); // width size of a quarter of panel width
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnob(valueKnob2);

				// More Wdigets
				draw_SurfingWidgets_1();
			}
			guiManager.endWindow();

			//--

			// Surfing Widgets 2

			name = "SurfingWidgets 2";
			guiManager.beginWindow(name.c_str(), NULL, _flagw);
			{
				draw_SurfingWidgets_2();
			}
			guiManager.endWindow();

			//--

			// Colors Gradient

			surfingGradient.drawImGui();
		}
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_1() {

	// Common width sizes from 1 (_w1) to 4 (_w4) widgets per row
	// Precalculate common widgets % sizes to fit current window "to be responsive"
	// we will update the sizes on any gui drawing point, like inside a new foldered sub-window that could be indendeted and full size is being smaller.
	// Internally takes care of ImGui spacing between widgets.
	float _w1;
	float _w2;
	float _w3;
	float _w4;
	float _h;

	//--

	// 1. An in index selector with a clickable preset matrix
	{
		bool bOpen = true;
		ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
		_flagt |= ImGuiTreeNodeFlags_Framed;

		if (ImGui::TreeNodeEx("An Index Selector", _flagt))
		{
			// Calculate sizes related to window shape/size

			// Required when creating a raw ImGui tree manually.
			// Not required when using the Api helpers/tools.
			// Btw, some standard widgets do not requires to do it.
			{
				guiManager.refreshLayout();
				_w1 = ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
				_w2 = ofxImGuiSurfing::getWidgetsWidth(2); // 2 widgets half width
				_w3 = ofxImGuiSurfing::getWidgetsWidth(3); // 3 widgets third width
				_w4 = ofxImGuiSurfing::getWidgetsWidth(4); // 4 widgets quarter width
				_h = 2 * ofxImGuiSurfing::getWidgetsHeight(); // Double height
			}

			// 1.01 Time counter in seconds 
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			ofxImGuiSurfing::drawTimecode(draw_list, ofGetElapsedTimef());
			ImGui::Spacing();

			ofxImGuiSurfing::AddTooltipHelp("Move the index slider, Click browse buttons or click the matrix numbers");
			ImGui::Spacing();

			// 1.1 Two buttons on same line
			if (ImGui::Button("<", ImVec2(_w2, _h)))
			{
				indexPreset--;
				indexPreset = ofClamp(indexPreset, indexPreset.getMin(), indexPreset.getMax()); // clamp parameter
			}
			ofxImGuiSurfing::AddTooltip("Click to Previous", guiManager.bHelp);
			ImGui::SameLine();

			if (ImGui::Button(">", ImVec2(_w2, _h)))
			{
				indexPreset++;
				indexPreset = ofClamp(indexPreset, indexPreset.getMin(), indexPreset.getMax()); // clamp parameter
			}
			ofxImGuiSurfing::AddTooltip("Click to Next", guiManager.bHelp);

			// 1.2 Slider: the master int ofParam!
			ofxImGuiSurfing::AddParameter(indexPreset);
			ofxImGuiSurfing::AddTooltip("Move the slider index to pick a preset.", guiManager.bHelp);

			// 1.3 Matrix button clicker
			AddMatrixClicker(indexPreset, true, 3); // Responsive layout with 3 widgets per row

			// 1.4 Spin arrows
			int intSpin = indexPreset;
			if (ofxImGuiSurfing::SpinInt("SpinInt", &intSpin))
			{
				intSpin = ofClamp(intSpin, indexPreset.getMin(), indexPreset.getMax()); // clamp to parameter
				indexPreset = intSpin;
			}

			// 1.5 A tooltip over previous widget
			ofxImGuiSurfing::AddTooltip(
				"This is not an ofParameter. "
				"It's Just an int type, so here we are using RAW ImGui widgets! "
				"But remember that we can use ofParameter Helpers instead."
				, guiManager.bHelp);

			// 1.6 An external url link
			ofxImGuiSurfing::AddLinkURL("ofxSurfingImGui@github.com", "https://github.com/moebiussurfing/ofxSurfingImGui");

			ImGui::TreePop();
		}
	}

	ImGui::Spacing();

	//--

	// 2. An ofParameterGroup
	ofxImGuiSurfing::AddGroup(params3);

	ofxImGuiSurfing::AddSpacingSeparated();

	//--

	// 3. Extra Stuff that we can use in our windows.

	// There's common toggles on guiManager to use in our apps: 
	// advanced, extra, help, keys, debug, lock move, etc...

	ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bHelp); // -> Here is used to enable tooltips
	ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bExtra);
	if (guiManager.bExtra)
	{
		ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);
		guiManager.drawAdvanced();
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets_2()
{
	ImGui::SetNextItemOpen(true, ImGuiCond_FirstUseEver);

	// Simple Tree 
	// made using raw ImGui, not with all the power of the add-on Api.

	if (ImGui::TreeNode("ofParams Widgets"))
	{
		ImGui::Indent();
		{
			//// Required when creating a raw ImGui tree and/or indenting manually.
			//// Not required when using the Api helpers/tools.
			//// Btw, some standard widgets do not requires to do it.
			//guiManager.refreshLayout(); // Calculates sizes related to window shape/size now.

			ofxImGuiSurfing::AddParameter(size2);
			ofxImGuiSurfing::AddParameter(amount2);
			ofxImGuiSurfing::AddParameter(separation3);

			ofxImGuiSurfing::AddSpacingSeparated();

			ofxImGuiSurfing::AddGroup(params);
		}
		ImGui::Unindent();
		ImGui::TreePop();
	}
}