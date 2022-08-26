#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() 
{
	ofSetWindowPosition(-1920, 25);

	ui.setup();

	// flip for natural direction
	ui.setMouseWheelFlip(false); 
	
	ui.startup();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ui.Begin();
	{
		string name = "Knobs";
		ImGuiColorEditFlags _flagw = 
			ui.bAutoResize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;

		static SurfingGuiTypes style; // knobs style

		//--

		IMGUI_SUGAR__WINDOWS_CONSTRAINTSW;

		ui.BeginWindow(name.c_str(), NULL, _flagw);
		{
			ui.Add(ui.bMinimize, OFX_IM_TOGGLE_ROUNDED);
			ui.Add(ui.bAutoResize, OFX_IM_TOGGLE_ROUNDED);
			ui.AddSpacing();
			if (!ui.bMinimize) {
				if (ui.BeginTree("Extra", false)) // closed
				{
					ui.Add(ui.bAdvanced, OFX_IM_TOGGLE_ROUNDED_SMALL);
					ui.AddSpacing();
					ui.Add(ui.bMouseWheel, OFX_IM_TOGGLE_ROUNDED_MINI);
					ui.Add(ui.bMouseWheelFlip, OFX_IM_TOGGLE_ROUNDED_MINI);
					ui.EndTree();
				}
				ui.AddSpacingBigSeparated();
			}

			//--

			// 2. NEW Styled Knobs ofParams
			{
				if (!ui.bMinimize) {
					ui.AddLabelHuge("NEW STYLED KNOBS");
					ui.AddLabelBig("from Simon Altschuler");
					ui.AddLinkURL("https://github.com/altschuler/imgui-knobs", "https://github.com/altschuler/imgui-knobs");
					ui.AddSpacingBig();
					ui.AddLabelBig("Style Selector", true);
				}
				ui.AddSpacing();

				{
					// Style selector
					
					vector<string> knobStyles;
					knobStyles.push_back("TICKKNOB");
					knobStyles.push_back("DOTKNOB");
					knobStyles.push_back("WIPERKNOB");
					knobStyles.push_back("WIPERONLYKNOB");
					knobStyles.push_back("WIPERDOTKNOB");
					knobStyles.push_back("STEPPEDKNOB");
					knobStyles.push_back("SPACEKNOB");
					const int sz = (int)(knobStyles.size()) - 1;
					static ofParameter<int> index{ "Style", 0, 0, sz };
					
					ui.Add(index, OFX_IM_KNOB, 4);
					ui.Add(index, OFX_IM_HSLIDER_NO_LABELS);


					ui.AddComboButtonDualLefted(index, knobStyles);
					switch (index)
					{
					case 0: style = OFX_IM_KNOB_TICKKNOB; break;
					case 1: style = OFX_IM_KNOB_DOTKNOB; break;
					case 2: style = OFX_IM_KNOB_WIPERKNOB; break;
					case 3: style = OFX_IM_KNOB_WIPERONLYKNOB; break;
					case 4: style = OFX_IM_KNOB_WIPERDOTKNOB; break;
					case 5: style = OFX_IM_KNOB_STEPPEDKNOB; break;
					case 6: style = OFX_IM_KNOB_SPACEKNOB; break;
					}
				}

				// Flag
				// NEW to the API
				static bool bImGuiKnobFlags_NoTitle = false;
				static bool bImGuiKnobFlags_NoInput = false;
				static bool bImGuiKnobFlags_TooltipValue = true;
				static bool bImGuiKnobFlags_DragHorizontal = true;
				SurfingGuiFlags flags = SurfingGuiFlags_None;
				if (bImGuiKnobFlags_NoTitle) flags += SurfingGuiFlags_NoTitle;
				if (bImGuiKnobFlags_NoInput) flags += SurfingGuiFlags_NoInput;
				if (bImGuiKnobFlags_TooltipValue) flags += SurfingGuiFlags_TooltipValue;
				if (bImGuiKnobFlags_DragHorizontal) flags += SurfingGuiFlags_DragHorizontal;

				if (!ui.bMinimize) {
					ui.AddSpacingBigSeparated();
					ui.AddLabelHuge("NEW API with Flags", false, true);
					SurfingGuiTypes s = OFX_IM_TOGGLE_ROUNDED_MINI;
					ui.AddToggle("NoTitle", bImGuiKnobFlags_NoTitle, s);
					ui.AddToggle("NoInput", bImGuiKnobFlags_NoInput, s);
					ui.AddToggle("TooltipValue", bImGuiKnobFlags_TooltipValue, s);
					ui.AddToggle("DragHorizontal", bImGuiKnobFlags_DragHorizontal, s);
				}
				ui.AddSpacingBig();

				// Draw
				// NEW API, including flags
				ui.Add(valueKnob1, style, 2, flags);
				ui.SameLine();
				ui.Add(valueKnob2, style, 2, flags);
			}

			//----

			/*
			if (0)
			{
				// 1. Legacy Non Styled Knobs ofParams
				{
					ui.AddSpacingBigSeparated();
					ui.AddLabelHuge("LEGACY NON STYLED KNOBS");
					ui.AddSpacing();
					ui.Add(valueKnob1, OFX_IM_KNOB, 4, true);
					ui.Add(valueKnob2, OFX_IM_KNOB, 4, true);
					ui.Add(valueKnob3, OFX_IM_KNOB, 4, true);
					ui.Add(valueKnob4, OFX_IM_KNOB, 4, false);
					ui.AddSpacingHugeSeparated();
				}
			}
			*/

			ui.EndWindow();
		}

		//--

		IMGUI_SUGAR__WINDOWS_CONSTRAINTS_BIG;

		if (ui.BeginWindow("Another Window"))
		{
			// Draw
			// Legacy API
			if (!ui.bMinimize) ui.AddLabelHuge("Legacy API without Flags", false, true);
			ui.Add(valueKnob3, style, 4, true);
			ui.Add(valueKnob4, style, 4, true);
			ui.Add(valueKnob5, style, 4, true);
			ui.Add(valueKnob6, style, 4, false);

			ui.AddSpacingBigSeparated();

			if (!ui.bMinimize) ui.AddLabelHuge("4 More Hardcoded", false, true);
			ui.Add(valueKnob5, OFX_IM_KNOB_TICKKNOB, 4, true);
			ui.Add(valueKnob6, OFX_IM_KNOB_WIPERONLYKNOB, 4, true);
			ui.Add(valueKnob7, OFX_IM_KNOB_WIPERDOTKNOB, 4, true);
			ui.Add(valueKnob8, OFX_IM_KNOB_STEPPEDKNOB, 4, false);

			ui.EndWindow();
		}

		//--

		// His toggle (bAdvanced) must be enabled to be drawn
		ui.DrawWindowAdvanced();
	}
	ui.End();
}
