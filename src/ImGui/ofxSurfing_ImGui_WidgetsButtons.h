#pragma once

#include "ofMain.h"

// ImGui Widgets
// Toogles and buttons.
// For bool and ofParameter<bool> types.

//------------------------------

#include "ofxImGui.h"
#include "imgui_internal.h"

#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_WidgetsTypesConstants.h"
#include "misc/ofxSurfing_Timers.h"

//#include "ofxSurfing_ImGui_ofHelpers.h" //-> TODO: can't make work the above sugar here..

//------------------------------

namespace ofxImGuiSurfing
{
	//-

	// Big Buttons and toggles for bool ofParams

	//--------------------------------------------------------------
	inline bool AddBigButton(ofParameter<bool>& parameter, float w = -1, float h = -1) // button but using a bool not void param
	{
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		string n = "##BIGBUTTON" + name + ofToString(1);
		ImGui::PushID(n.c_str());

		bool bPre = tmpRef;

		if (w == -1) w = ImGui::GetContentRegionAvail().x; // full width
		if (h == -1) h = 2 * ofxImGuiSurfing::getWidgetsHeightRelative();

		ImGuiStyle *style = &ImGui::GetStyle();
		const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
		const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

		ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);

		if (ImGui::Button(name.c_str(), ImVec2(w, h)))
		{
			ofLogVerbose(__FUNCTION__) << name << ": BANG";

			tmpRef = true;
			parameter.set(tmpRef);
		}

		ImGui::PopStyleColor(3);

		ImGui::PopID();

		//IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(parameter);

		if (bPre != parameter) return true;
		else return false;
	}

	//--------------------------------------------------------------
	inline bool AddBigButton(ofParameter<bool>& parameter, ImVec2 bb = ImVec2(-1, -1)) {
		return AddBigButton(parameter, bb.x, bb.y);
	}

	//-

	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<bool>& parameter, float w = -1, float h = -1) // button but using a bool not void param
	{
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		string n = "##SMALLBUTTON" + name + ofToString(1);
		ImGui::PushID(n.c_str());

		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = ofxImGuiSurfing::getWidgetsHeightRelative();

		ImGuiStyle *style = &ImGui::GetStyle();
		const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
		const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

		ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
		if (ImGui::Button(name.c_str(), ImVec2(w, h)))
		{
			tmpRef = true;
			parameter.set(tmpRef);
		}

		ImGui::PopStyleColor(3);

		ImGui::PopID();

		return tmpRef;
	}

	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<bool>& parameter, ImVec2 bb = ImVec2(-1, -1)) {
		AddSmallButton(parameter, bb.x, bb.y);
	}

	//----

	//--------------------------------------------------------------
	inline bool AddBigToggle(ofParameter<bool>& parameter, float w = -1, float h = -1, bool border = false, bool bBlink = false)
	{
		// Border when selected
		float a = 0.5f;
		float borderLineWidth = 1.0;
		ImGuiStyle *style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

		// Blink
		if (bBlink) {
			float blinkValue = ofxImGuiSurfing::getFadeBlink();
			a = ofClamp(blinkValue, 0.25, 0.75);
			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		}

		//-

		bool bDrawBorder = true;

		std::string name = parameter.getName();
		auto tmpRef = parameter.get();
		bool bPre = tmpRef;

		//--

		// Default
		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();

		bool _boolToggle = tmpRef; // default pre value, the button is disabled 

		if (_boolToggle) // was enabled
		{
			// Warning: notice that each state has a different button, so we need to push different ID's!
			// Warning: in this case we need to use the name to became the toggle functional
			// that means that we can maybe collide not unique names! 
			//string n = "#BT" + name + ofToString(counterBigToggle++);
			//ofLogNotice(__FUNCITON__) << n;
			string n = "##BIGTOGGLE_on_" + name + ofToString(1);
			ImGui::PushID(n.c_str());
			{
				// Border to selected
				if (border)
				{
					bDrawBorder = true;
					ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
					ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
				}

				const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonHovered];
				const ImVec4 colorButton = style->Colors[ImGuiCol_ButtonActive];
				const ImVec4 colorHover = style->Colors[ImGuiCol_ButtonHovered];
				ImVec4 colorHover2 = ImVec4(colorHover.x, colorHover.y, colorHover.z, colorHover.w * 1.0);

				ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorHover2);
				ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover2);

				ImGui::Button(name.c_str(), ImVec2(w, h));

				if (ImGui::IsItemClicked(0)) // PowerOff
				{
					_boolToggle = false;
					tmpRef = false;
					parameter.set(tmpRef);
				}

				ImGui::PopStyleColor(3);

				if (bDrawBorder && border)
				{
					ImGui::PopStyleColor();
					ImGui::PopStyleVar(1);
				}
			}
			ImGui::PopID();
		}
		else // was disabled
		{
			string n = "##BIGTOGGLE_off_" + name + ofToString(1);
			ImGui::PushID(n.c_str());
			{
				const ImVec4 colorOn = style->Colors[ImGuiCol_FrameBg];
				const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

				ImVec4 colorTextDisabled = style->Colors[ImGuiCol_Text];
				colorTextDisabled = ImVec4(colorTextDisabled.x, colorTextDisabled.y, colorTextDisabled.z,
					colorTextDisabled.w * TEXT_INACTIVE_ALPHA);

				ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
				ImGui::PushStyleColor(ImGuiCol_Button, colorOn);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorActive);
				ImGui::PushStyleColor(ImGuiCol_Text, colorTextDisabled);

				if (ImGui::Button(name.c_str(), ImVec2(w, h)))
				{
					_boolToggle = true;
					tmpRef = _boolToggle;
					parameter.set(tmpRef);
				}

				ImGui::PopStyleColor(4);
			}
			ImGui::PopID();
		}

		//-

		if (parameter.get() != bPre) return true; // changed
		else return false;
	}

	//--------------------------------------------------------------
	inline bool AddBigToggle(ofParameter<bool>& parameter, ImVec2 bb = ImVec2(-1, -1), bool border = false, bool bBlink = false) {
		AddBigToggle(parameter, bb.x, bb.y, border, bBlink);
	}

	//--

	// Two states with two names. Also with blinking with setteable alpha border
	//--------------------------------------------------------------
	inline bool AddBigToggleNamed(ofParameter<bool>& parameter, float w = -1, float h = -1, std::string nameTrue = "-1", std::string nameFalse = "-1", bool bBlink = false, float blinkValue = -1.0f)
	{
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		//-

		bool bPre = tmpRef;

		ImGuiStyle *style = &ImGui::GetStyle();

		//-

		bool b = tmpRef;

		if (bBlink)
		{
			const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];

			if (blinkValue == -1) {
				blinkValue = ofxImGuiSurfing::getFadeBlink();
			}
			float a;
			if (b) a = blinkValue;
			else a = 1.0f;
			a = ofClamp(a, 0, 1);
			if (b) ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(c_.x, c_.y, c_.z, c_.w * a));
		}

		//--

		float _spc = ImGui::GetStyle().ItemInnerSpacing.x;

		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = 2 * ofxImGuiSurfing::getWidgetsHeightRelative();

		if (nameTrue == "-1") nameTrue = "##BIGTOGGLENAMED_on_" + name;
		if (nameFalse == "-1") nameFalse = "##BIGTOGGLENAMED_off_" + name;

		//--

		bool _boolToggle = tmpRef;  // default value, the button is disabled 

		// enabled
		if (_boolToggle == true)
		{
			ImGui::PushID(nameTrue.c_str());

			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonHovered];
			const ImVec4 colorButton = style->Colors[ImGuiCol_ButtonActive];
			const ImVec4 colorHover = style->Colors[ImGuiCol_ButtonHovered];

			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);

			ImGui::Button(nameTrue.c_str(), ImVec2(w, h));
			if (ImGui::IsItemClicked(0))
			{
				_boolToggle = !_boolToggle;
				tmpRef = _boolToggle;
				parameter.set(tmpRef);
			}

			ImGui::PopStyleColor(3);

			ImGui::PopID();
		}

		// disabled
		else
		{
			ImGui::PushID(nameTrue.c_str());

			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];
			const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
			const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
			ImVec4 colorTextDisabled = style->Colors[ImGuiCol_Text];

			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			ImGui::PushStyleColor(ImGuiCol_Button, colorHover);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
			ImGui::PushStyleColor(ImGuiCol_Text, colorTextDisabled);

			if (ImGui::Button(nameFalse.c_str(), ImVec2(w, h))) {
				_boolToggle = true;
				tmpRef = _boolToggle;
				parameter.set(tmpRef);
			}

			ImGui::PopStyleColor(4);

			ImGui::PopID();
		}

		//-

		if (bBlink && b)
		{
			ImGui::PopStyleColor();
		}

		//--

		return (bPre != tmpRef);
	}

	//--------------------------------------------------------------
	inline bool AddBigToggleNamed(ofParameter<bool>& parameter, ImVec2 bb = ImVec2(-1, -1), std::string nameTrue = "-1", std::string nameFalse = "-1", bool bBlink = false, float blinkValue = -1.0f)
	{
		AddBigToggleNamed(parameter, bb.x, bb.y, nameTrue, nameFalse, bBlink, blinkValue);
	}

	//----

	//--------------------------------------------------------------

	// Rounded Toggle Buttons

	// Take from:
	// https://github.com/ocornut/imgui/issues/1537
	// bool & ofParameter<bool>

#define USE_BORDER_ROUNDE_TOGGLES // -> Enable to draw circle borders on the rounded toggle..

	//--------------------------------------------------------------
	inline bool ToggleRoundedButton(const char* str_id, bool* v, ImVec2 vv = ImVec2(-1, -1))
	{
		//TODO:
		// Should fix mouse over/inner pos checking to fix mouse wheel control..

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec4* colors = ImGui::GetStyle().Colors;

		bool bchanged = false;

		float width;
		float radius;
		float height;

		string n = "##TOGGLEROUNDBUTTON" + ofToString(1);
		ImGui::PushID(n.c_str());
		{
			if ((vv.x == -1) && (vv.y == -1)) // default size
			{
				height = ImGui::GetFrameHeight();
				width = height * 1.55f;
			}
			else // received by args
			{
				width = vv.x;
				height = vv.y;
			}
			radius = height / 2.0f;

			ImGui::InvisibleButton(str_id, ImVec2(width, height));

			bool is_active = ImGui::IsItemActive();
			bool is_hovered = ImGui::IsItemHovered();

			if (ImGui::IsItemClicked())
			{
				*v = !*v;//flip bool

				bchanged = true;
			}

			//-

			//TODO:
			// Animated
			float t = *v ? 1.0f : 0.0f;
			ImGuiContext& g = *GImGui;
			float ANIM_SPEED = 0.08f;
			//if (g.LastActiveId == g.CurrentWindow->GetID(str_id) && g.LastActiveIdTimer < ANIM_SPEED)
			if (g.LastActiveId == g.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
			{
				float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
				t = *v ? (t_anim) : (1.0f - t_anim);
			}
			//const ImU32 frame_col = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.56f, 0.83f, 0.26f, 1.0f), t));

			//--

			// 1. Background Zone

			ImU32 frame_col;
			ImU32 cf;
			//cf = IM_COL32(255, 0, 255, 255);

			// State true
			if (*v) 
			{
				frame_col = ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBg : ImGuiCol_FrameBgHovered);
				cf = frame_col;
			}
			// State false
			else
			{
				frame_col = ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
				cf = frame_col;
			}

			draw_list->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), cf, height * 0.5f);

			//-

			// 1.2 Border Background Zone

			// A. Reduced alpha
#ifdef USE_BORDER_ROUNDE_TOGGLES
			//const float a = (is_active ? 0.8 : 0.5);
			//const ImVec4 c = ImVec4(colors[ImGuiCol_Border].x, colors[ImGuiCol_Border].y, colors[ImGuiCol_Border].z, colors[ImGuiCol_Border].w * a);
			//const ImU32 cb = ImGui::GetColorU32(c);

			// B. No alpha changes
			const ImU32 cb = ImGui::GetColorU32(colors[ImGuiCol_Border]);

			draw_list->AddRect(pos, ImVec2(pos.x + width, pos.y + height), cb, height * 0.5f);
#endif
			//-

			// 2.1 Small Circle

			ImU32 c1 = IM_COL32(255 * colors[ImGuiCol_SliderGrab].x, 255 * colors[ImGuiCol_SliderGrab].y, 255 * colors[ImGuiCol_SliderGrab].z, 255);
#ifndef USE_BORDER_ROUNDE_TOGGLES
			draw_list->AddCircleFilled(ImVec2(pos.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f), pos.y + radius), radius - 1.5f, c1);
#endif
			//-

			// 2.2 Border Small Circle

#ifdef USE_BORDER_ROUNDE_TOGGLES
			//draw_list->AddCircleFilled(ImVec2(pos.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f), pos.y + radius), radius - 1.5f - 1, c1);//a bit of offset
			//draw_list->AddCircle(ImVec2(pos.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f), pos.y + radius), radius - 1.5f, cb);

			draw_list->AddCircleFilled(ImVec2(pos.x + radius + t * (*v ? 1 : 0) * (width - radius * 2.0f), pos.y + radius), radius - 1.5f - 1, c1);//a bit of offset
			draw_list->AddCircle(ImVec2(pos.x + radius + (*v ? 1 : 0) * t * (width - radius * 2.0f), pos.y + radius), radius - 1.5f, cb);
#endif
			//TODO:
			//ofxImGuiSurfing::AddMouseWheel();

			//-

			// 3. Text Label

			ImGui::SameLine();
			float fontSize = ImGui::GetFontSize();
			const ImVec2 p1 = ImGui::GetCursorScreenPos();
			const float offset_xt = 0;
			const float offset_yt = height / 2 - fontSize / 2;
			const ImU32 ct = ImGui::GetColorU32(ImGuiCol_Text);
			const ImVec2 pt = ImVec2(p1.x + offset_xt, p1.y + offset_yt);

			draw_list->AddText(pt, ct, str_id);

			//-

			// 4. Frame ?

			const auto sizetx = ImGui::CalcTextSize(str_id);
			ImGui::Dummy(ImVec2(sizetx.x + ImGui::GetStyle().FramePadding.x * 1.0f, 0)); // ?
		}
		ImGui::PopID();

		return bchanged;
	}

	//-

	// ofParameter bool rounded toggle

	//TODO:
	// There's a bug that when using
	// ImGui::Dummy(ImVec2(0.0f, 2.0f));
	// after the button it adds more spacing
	//--------------------------------------------------------------
	inline bool AddToggleRoundedButton(ofParameter<bool>& parameter, ImVec2 vv = ImVec2(-1, -1))
	{
		bool bReturn = false;
		auto tmpRef = parameter.get();

		if (ToggleRoundedButton(parameter.getName().c_str(), (bool *)&tmpRef, vv))
		{
			parameter.set(tmpRef);
			bReturn = true;
		}

		return bReturn;
	}

	// Two names depending of the bool state
	//--------------------------------------------------------------
	inline bool AddToggleRoundedButtonNamed(ofParameter<bool>& parameter, ImVec2 vv = ImVec2(-1, -1), std::string nameTrue = "-1", std::string nameFalse = "-1")
	{
		bool bReturn = false;
		auto tmpRef = parameter.get();
		std::string name;

		if (nameTrue == "-1" || nameFalse == "-1") name = parameter.getName();
		else {
			if ((bool *)&tmpRef) name = nameTrue;
			else name = nameFalse;
		}

		if (ToggleRoundedButton(name.c_str(), (bool *)&tmpRef, vv))
		{
			parameter.set(tmpRef);
			bReturn = true;
		}

		return bReturn;
	}
};
