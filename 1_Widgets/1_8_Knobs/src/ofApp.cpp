#include "ofApp.h"

/*

TODO:
	
	fix names colliding
	add style tags to full integrate into layout engine

*/

//--------------------------------------------------------------
void ofApp::setup(){

	guiManager.setup();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	guiManager.begin();
	{
		{
			ImGuiColorEditFlags _flagw;
			string name;

			_flagw = guiManager.bAutoResize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;

			name = "Knobs";
			guiManager.beginWindow(name.c_str(), NULL, _flagw);
			{
				guiManager.Add(guiManager.bAutoResize);
				
				ofxImGuiSurfing::AddSpacingHuge();

				//-

				// Non Styled Knobs ofParams
				//guiManager.Add(valueKnob1, OFX_IM_KNOB, 4, true);
				//guiManager.Add(valueKnob2, OFX_IM_KNOB, 4, true);
				//guiManager.Add(valueKnob3, OFX_IM_KNOB, 4, true);
				//guiManager.Add(valueKnob4, OFX_IM_KNOB, 4, false);

				//ofxImGuiSurfing::AddKnob(valueKnob2);
				
				//-
				
				// Styled Knobs ofParams

				ImGui::Text("Styled Knobs ofParams");
				ofxImGuiSurfing::AddSpacingDouble();

				ofxImGuiSurfing::AddKnobStyled(valueKnob1, OFX_IMGUI_KNOB_TICKKNOB, 80, "%.1f");
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob2, OFX_IMGUI_KNOB_DOTKNOB, 80, "%.1f dB");
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob3, OFX_IMGUI_KNOB_WIPERKNOB, 80, "%.3f");
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob4, OFX_IMGUI_KNOB_WIPERONLYKNOB, 80, "%.4g");

				ofxImGuiSurfing::AddSpacingHuge();

				ofxImGuiSurfing::AddKnobStyled(valueKnob5, OFX_IMGUI_KNOB_TICKKNOB, 120);
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob6, OFX_IMGUI_KNOB_DOTKNOB, 120);

				ofxImGuiSurfing::AddKnobStyled(valueKnob7, OFX_IMGUI_KNOB_WIPERKNOB, 120);
				ImGui::SameLine();
				ofxImGuiSurfing::AddKnobStyled(valueKnob8, OFX_IMGUI_KNOB_WIPERONLYKNOB, 120);

				//-

				ofxImGuiSurfing::AddSpacingHugeSeparated();

				//--

				// TODO:
				// Raw knobs
				// customize colors to fit my theme
				// implement ofParam helpers and styles

				static float value1 = 0;
				static float value2 = 0;
				static float value3 = 0;
				static float value4 = 0;
				static float value5 = 0;
				static float value6 = 0;
				static float value7 = 0;

				ImGui::Text("Raw Knobs");
				ofxImGuiSurfing::AddSpacingDouble();
				
				float size = 80;
				if (ImGuiKnobs::TickKnob("Value 1", &value1, -6.0f, 6.0f, "%.1fdB", size))
				{
				}
				ImGui::SameLine();

				if (ImGuiKnobs::DotKnob("Value 2", &value2, -6.0f, 6.0f, "%.1fdB", size))
				{
				}
				ImGui::SameLine();

				if (ImGuiKnobs::WiperKnob("Value 3", &value3, -6.0f, 6.0f, "%.1fdB", size))
				{
				}
				ImGui::SameLine();

				if (ImGuiKnobs::WiperOnlyKnob("Value 4", &value4, -6.0f, 6.0f, "%.1f", size))
				{
				}
				ImGui::SameLine();
				
				if (ImGuiKnobs::WiperDotKnob("Value 5", &value5, -6.0f, 6.0f, "%.2f", size))
				{
				}
				ImGui::SameLine();
				
				if (ImGuiKnobs::SteppedKnob("Value 6", &value6, -6.0f, 6.0f, "%.3f", size))
				{
				}
				ImGui::SameLine();
				
				if (ImGuiKnobs::SpaceKnob("Value 7", &value7, -6.0f, 6.0f, "%.4f", size))
				{
				}

				//--

				ofxImGuiSurfing::AddSpacingHuge();
				
				ImGuiKnobFlags flag;

				ImGui::Text("Flags NoTitle/NoInput/ValueTooltip");
				ofxImGuiSurfing::AddSpacingDouble();
				
				flag = ImGuiKnobFlags_NoTitle;
				if (ImGuiKnobs::WiperOnlyKnob("Value-1", &value1, -6.0f, 6.0f, "%.1f", 0, flag))
				{
				}
				ImGui::SameLine();
				
				flag = ImGuiKnobFlags_NoInput;
				if (ImGuiKnobs::WiperOnlyKnob("Value-2", &value2, -6.0f, 6.0f, "%.1f", 0, flag))
				{
				}
				ImGui::SameLine();
				
				flag = ImGuiKnobFlags_ValueTooltip;
				if (ImGuiKnobs::WiperOnlyKnob("Value-3", &value3, -6.0f, 6.0f, "%.1f", 0, flag))
				{
				}
				ImGui::SameLine();
				
				flag = ImGuiKnobFlags_NoInput | ImGuiKnobFlags_NoTitle | ImGuiKnobFlags_ValueTooltip;
				if (ImGuiKnobs::WiperOnlyKnob("Value-4", &value4, -6.0f, 6.0f, "%.1f", 0, flag))
				{
				}

				//TODO
				static int myInt = 0;
				float _myInt = myInt;
				if (ImGuiKnobs::TickKnob("myInt", &_myInt, -6, 6, "%d", size))
				{
					myInt = _myInt;
				}
			}
			guiManager.endWindow();
		}
	}
	guiManager.end();
}
