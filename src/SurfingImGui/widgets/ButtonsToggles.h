#pragma once

#include "ofMain.h"

// ImGui Widgets
// Toogles and buttons.
// For bool and ofParameter<bool> types.

//------------------------------

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "SurfingImGui/LayoutHelpers.h"
#include "SurfingImGui/utils/SurfingGuiConstants.h"
//#include "SurfingImGui/utils/ofxSurfing_Timers.h"

#include "SurfingHelpers.h"


////#include "ofxSurfing_ImGui_ofHelpers.h" //-> TODO: can't make work the above sugar here..
//
//#define OFX_IM_BLINK_MIN 0.2f 
//#define OFX_IM_BLINK_MAX 0.5f 
//
//#define OFX_IM_FACTOR_DARKEN 0.5f 

//------------------------------

namespace ofxImGuiSurfing
{
	//TODO:
	// Move to other widgets header
	//--------------------------------------------------------------
	inline void AddTextBlink(std::string text, bool bBlink = true)
	{
		//bool border = false;

		float a = 0.5f;
		float borderLineWidth = 1.0;
		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_Text];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

		// Blink
		if (bBlink)
		{
			float blinkValue = getFadeBlink();
			a = ofClamp(blinkValue, OFX_IM_BLINK_MIN, OFX_IM_BLINK_MAX);

			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		}

		//--

		// Border to selected
		//if (border)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, borderLineColor);
			//ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
		}

		ImGui::TextWrapped("%s", text.c_str());

		//if (border)
		{
			ImGui::PopStyleColor();
			//ImGui::PopStyleVar(1);
		}
	}

	//----

	// Mini Button and toggles for BOOL ofParams

	//--------------------------------------------------------------
	// Mini button but using a bool param, not a void param
	inline bool AddButtonMini(ofParameter<bool>& p, float w = -1, float h = -1)
	{
		auto tmpRef = p.get();
		std::string name = p.getName();
		bool bPre = tmpRef;


		std::string n = "##BUTTONMINI" + name + ofToString(1);
		ImGui::PushID(n.c_str());
		{
			const auto sztx = ImGui::CalcTextSize(name.c_str());
			if (w == -1) w = sztx.x + 2 * ImGui::GetStyle().ItemInnerSpacing.x;
			if (h == -1) h = ofxImGuiSurfing::getWidgetsHeightUnit();

			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
			const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];
			ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			{
				if (ImGui::Button(name.c_str(), ImVec2(w, h)))
				{
					ofLogVerbose("ofxSurfingImGui") << name << ": BANG";

					tmpRef = true;
					p.set(tmpRef);
				}
			}
			ImGui::PopStyleColor(3);
		}
		ImGui::PopID();

		if (bPre != p) return true;
		else return false;
	}

	//--

	// Mini button but without any bool or void params
	//--------------------------------------------------------------
	inline bool AddButtonMini(string name, float w = -1, float h = -1)
	{
		bool bchanged = false;

		std::string n = "##BUTTONMINI" + name + ofToString(1);
		ImGui::PushID(n.c_str());
		{
			const auto sztx = ImGui::CalcTextSize(name.c_str());
			if (w == -1) w = sztx.x + 2 * ImGui::GetStyle().ItemInnerSpacing.x;
			if (h == -1) h = ofxImGuiSurfing::getWidgetsHeightUnit();

			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
			const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];
			ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			{
				if (ImGui::Button(name.c_str(), ImVec2(w, h)))
				{
					ofLogVerbose("ofxSurfingImGui") << name << ": BANG";

					bchanged = true;
				}
			}
			ImGui::PopStyleColor(3);
		}
		ImGui::PopID();

		return bchanged;;
	}

	//--

	// Big Buttons and toggles for BOOL ofParams

	//--------------------------------------------------------------
	inline bool AddBigButton(ofParameter<bool>& p, float w = -1, float h = -1, bool border = false, bool bBlink = false) // button but using a bool not void param
	{
		// Border when selected

		float a = 0.5f;
		float borderLineWidth = 1.0f;
		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

		// Blink

		if (bBlink)
		{
			float blinkValue = getFadeBlink();
			a = ofClamp(blinkValue, OFX_IM_BLINK_MIN, OFX_IM_BLINK_MAX);

			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		}

		bool bDrawBorder = true;

		//--

		auto tmpRef = p.get();
		std::string name = p.getName();
		bool bPre = tmpRef;
		//fix
		bool bChanged = false;

		std::string n = "##BIGBUTTON" + name + ofToString(1);
		ImGui::PushID(n.c_str());
		{
			if (w == -1) w = ImGui::GetContentRegionAvail().x; // full width
			if (h == -1) h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();

			// Border to selected
			if (border)
			{
				bDrawBorder = true;
				ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
			}

			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
			const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

			ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			{
				if (ImGui::Button(name.c_str(), ImVec2(w, h)))
				{
					ofLogVerbose("ofxSurfingImGui") << name << ": BANG";

					tmpRef = true;
					p.set(tmpRef);
					bChanged = true;
				}
			}
			ImGui::PopStyleColor(3);

			// Border Blink
			if (bDrawBorder && border)
			{
				ImGui::PopStyleColor();
				ImGui::PopStyleVar(1);
			}
		}
		ImGui::PopID();

		//IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);

		//if (bPre != p) return true;
		//else return false;

		return bChanged;
	}

	//--------------------------------------------------------------
	inline bool AddBigButton(ofParameter<bool>& p, ImVec2 bb) {
		return AddBigButton(p, bb.x, bb.y);
	}

	//--

	// Button but using a BOOL not void param
	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<bool>& p, float w, float h)
	{
		auto tmpRef = p.get();
		std::string name = p.getName();

		std::string n = "##SMALLBUTTON" + name + ofToString(1);
		ImGui::PushID(n.c_str());

		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = ofxImGuiSurfing::getWidgetsHeightRelative();

		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
		const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

		ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
		if (ImGui::Button(name.c_str(), ImVec2(w, h)))
		{
			ofLogVerbose("ofxSurfingImGui") << name << ": BANG";
			tmpRef = true;
			p.set(tmpRef);
		}

		ImGui::PopStyleColor(3);

		ImGui::PopID();

		return tmpRef;
	}

	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<bool>& p, ImVec2 bb /*= ImVec2(-1, -1)*/) {
		return AddSmallButton(p, bb.x, bb.y);
	}

	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<bool>& p) // button but using a bool not void param
	{
		return AddSmallButton(p, -1, -1);
	}

	//----

	// TODO: 

	// Big Buttons and toggles for VOID ofParams

	//--------------------------------------------------------------
	inline bool AddBigButton(ofParameter<void>& p, float w = -1, float h = -1, bool border = false, bool bBlink = false)
	{
		bool bReturn = false;
		std::string name = p.getName();


		// Border when selected
		float a = 0.5f;
		float borderLineWidth = 1.0f;
		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		// Blink
		if (bBlink)
		{
			float blinkValue = getFadeBlink();
			a = ofClamp(blinkValue, OFX_IM_BLINK_MIN, OFX_IM_BLINK_MAX);

			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		}
		bool bDrawBorder = true;


		std::string n = "##BIGBUTTON" + name + ofToString(1);
		ImGui::PushID(n.c_str());
		{
			if (w == -1) w = ImGui::GetContentRegionAvail().x; // full width
			if (h == -1) h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();


			// Border to selected
			if (border)
			{
				bDrawBorder = true;
				ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
			}


			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
			const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

			ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			{
				if (ImGui::Button(name.c_str(), ImVec2(w, h)))
				{
					ofLogVerbose("ofxSurfingImGui") << name << ": BANG";
					bReturn = true;
					p.trigger();
				}
			}
			ImGui::PopStyleColor(3);


			// Border Blink
			if (bDrawBorder && border)
			{
				ImGui::PopStyleColor();
				ImGui::PopStyleVar(1);
			}
		}
		ImGui::PopID();

		return bReturn;
	}
	//--------------------------------------------------------------
	inline bool AddBigButton(ofParameter<void>& p, ImVec2 bb /*= ImVec2(-1, -1)*/) {
		return AddBigButton(p, bb.x, bb.y);
	}
	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<void>& p, float w/* = -1*/, float h/* = -1*/) // button but using a bool not void param
	{
		bool bReturn = false;
		std::string name = p.getName();

		std::string n = "##SMALLBUTTON" + name + ofToString(1);
		ImGui::PushID(n.c_str());

		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = ofxImGuiSurfing::getWidgetsHeightRelative();

		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
		const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

		ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
		if (ImGui::Button(name.c_str(), ImVec2(w, h)))
		{
			ofLogVerbose("ofxSurfingImGui") << name << ": BANG";
			bReturn = true;
			p.trigger();
		}

		ImGui::PopStyleColor(3);

		ImGui::PopID();

		return bReturn;
	}
	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<void>& p, ImVec2 bb) {
		return AddSmallButton(p, bb.x, bb.y);
	}
	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<void>& p)
	{
		return AddSmallButton(p, -1, -1);
	}

	//----

	// Big Buttons (for void and boolean) and Toggles for boolean ofParams

	// Legacy
	//--------------------------------------------------------------
	inline bool AddBigToggle(ofParameter<bool>& p, float w = -1, float h = -1, bool border = false, bool bBlink = false)
	{
		// Border when selected

		float a = 0.5f;
		float borderLineWidth = 1.0f;
		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

		// Blink

		if (bBlink)
		{
			float blinkValue = getFadeBlink();
			a = ofClamp(blinkValue, OFX_IM_BLINK_MIN, OFX_IM_BLINK_MAX);

			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		}

		bool bDrawBorder = true;

		//--

		std::string name = p.getName();
		auto tmpRef = p.get();
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
			//std::string n = "#BT" + name + ofToString(counterBigToggle++);

			std::string n = "##BIGTOGGLE_on_" + name + ofToString(1);

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
					p.set(tmpRef);
				}

				ImGui::PopStyleColor(3);

				// Border Blink
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
			std::string n = "##BIGTOGGLE_off_" + name + ofToString(1);
			ImGui::PushID(n.c_str());
			{
				const ImVec4 colorOn = style->Colors[ImGuiCol_FrameBg];
				const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

				ImVec4 colorTextDisabled = style->Colors[ImGuiCol_Text];
				colorTextDisabled = ImVec4(colorTextDisabled.x, colorTextDisabled.y, colorTextDisabled.z,
					colorTextDisabled.w * OFX_IM_TEXT_INACTIVE_ALPHA);

				ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
				ImGui::PushStyleColor(ImGuiCol_Button, colorOn);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorActive);
				ImGui::PushStyleColor(ImGuiCol_Text, colorTextDisabled);

				if (ImGui::Button(name.c_str(), ImVec2(w, h)))
				{
					_boolToggle = true;
					tmpRef = _boolToggle;
					p.set(tmpRef);
				}

				ImGui::PopStyleColor(4);
			}
			ImGui::PopID();
		}

		// Debug point
		if (0)
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			const ImVec2 pdebug = ImGui::GetCursorScreenPos();
			draw_list->AddCircleFilled(ImVec2(pdebug.x, pdebug.y), 2, IM_COL32(255, 0, 255, 255)); // a bit of offset
		}

		//-

		if (p.get() != bPre) return true; // changed
		else return false;
	}

	//--------------------------------------------------------------
	inline bool AddBigToggle(ofParameter<bool>& p, ImVec2 bb, bool border = false, bool bBlink = false) {
		return AddBigToggle(p, bb.x, bb.y, border, bBlink);
	}

	// Refactored names removing "big" tag
	//--------------------------------------------------------------
	inline bool AddToggle(ofParameter<bool>& p, float w = -1, float h = -1, bool border = false, bool bBlink = false)
	{
		return AddBigToggle(p, w, h, border, bBlink);
	}
	//--------------------------------------------------------------
	inline bool AddToggle(ofParameter<bool>& p, ImVec2 bb, bool border = false, bool bBlink = false) {
		return AddToggle(p, bb.x, bb.y, border, bBlink);
	}
	//--------------------------------------------------------------
	inline bool AddSmallToggle(ofParameter<bool>& p) {
		bool border = false;
		bool bBlink = false;
		float h = ofxImGuiSurfing::getWidgetsHeightUnit();
		float w = ofxImGuiSurfing::getWidgetButtomToggleWidth(p);//calc text
		return ofxImGuiSurfing::AddToggle(p, ImVec2(w, h));
	}

	//--

	// Toggles with two states with two names. 
	// Also with blinking mode or with settable alpha border.

	// Legacy
	//--------------------------------------------------------------
	inline bool AddBigToggleNamed(ofParameter<bool>& p, float w = -1, float h = -1, std::string nameTrue = "-1", std::string nameFalse = "-1", bool bBlink = false, float blinkValue = -1.0f)
	{
		auto tmpRef = p.get();
		std::string name = p.getName();

		//-

		bool bPre = tmpRef;

		ImGuiStyle* style = &ImGui::GetStyle();

		//-

		bool b = tmpRef;

		if (bBlink)
		{
			const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];

			if (blinkValue == -1)
			{
				blinkValue = getFadeBlink();
			}
			float a;
			if (b) a = blinkValue;
			else a = 1.0f;

			a = ofClamp(blinkValue, OFX_IM_BLINK_MIN, OFX_IM_BLINK_MAX);

			if (b) ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(c_.x, c_.y, c_.z, c_.w * a));
		}

		//--

		float _spc = ImGui::GetStyle().ItemInnerSpacing.x;

		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = 2 * ofxImGuiSurfing::getWidgetsHeightRelative();

		if (nameTrue == "-1") nameTrue = "##BIGTOGGLENAMED_on_" + name;
		if (nameFalse == "-1") nameFalse = "##BIGTOGGLENAMED_off_" + name;

		//--

		bool _boolToggle = tmpRef; // default value, the button is disabled 

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
				p.set(tmpRef);
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
				p.set(tmpRef);
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
	inline bool AddBigToggleNamed(ofParameter<bool>& p, ImVec2 bb = ImVec2(-1, -1), std::string nameTrue = "-1", std::string nameFalse = "-1", bool bBlink = false, float blinkValue = -1.0f)
	{
		return AddBigToggleNamed(p, bb.x, bb.y, nameTrue, nameFalse, bBlink, blinkValue);
	}

	// Refactored names removing "big" tag
	//--------------------------------------------------------------
	inline bool AddToggleNamed(ofParameter<bool>& p, float w = -1, float h = -1, std::string nameTrue = "-1", std::string nameFalse = "-1", bool bBlink = false, float blinkValue = -1.0f)
	{
		return AddBigToggleNamed(p, w, h, nameTrue, nameFalse, bBlink, blinkValue);
	}
	//--------------------------------------------------------------
	inline bool AddToggleNamed(ofParameter<bool>& p, ImVec2 bb = ImVec2(-1, -1), std::string nameTrue = "-1", std::string nameFalse = "-1", bool bBlink = false, float blinkValue = -1.0f)
	{
		return AddToggleNamed(p, bb.x, bb.y, nameTrue, nameFalse, bBlink, blinkValue);
	}
	//--------------------------------------------------------------
	inline bool AddToggleNamed(ofParameter<bool>& p, std::string nameTrue, std::string nameFalse)
	{
		bool bBlink = false;
		float blinkValue = -1.0f;
		float h = ofxImGuiSurfing::getWidgetsHeightUnit();
		ImVec2 bb = ImVec2(-1, h);
		return AddToggleNamed(p, bb.x, bb.y, nameTrue, nameFalse, bBlink, blinkValue);
		//return AddBigToggleNamed(p, bb.x, bb.y, nameTrue, nameFalse, bBlink, blinkValue);
	}
	////--------------------------------------------------------------
	//inline bool AddToggleNamed(ofParameter<bool>& p, std::string nameTrue, std::string nameFalse)
	//{
	//	bool bBlink = false;
	//	float blinkValue = -1.0f;
	//	float h = ofxImGuiSurfing::getWidgetsHeightUnit();
	//	ImVec2 bb = ImVec2(-1, h);
	//	return AddToggleNamed(p, bb.x, bb.y, nameTrue, nameFalse, bBlink, blinkValue);
	//}

	//--------------------------------------------------------------

	// Rounded Toggle Buttons

	// Taken from:
	// https://github.com/ocornut/imgui/issues/1537
	// Usable with bool & ofParameter<bool>

	// -> Enable to draw circle borders on the rounded toggle.. 
#define USE_BORDER_ROUNDE_TOGGLES 
	// Btw can be disabled like on mini toggle style.

	//--------------------------------------------------------------
	inline bool ToggleRoundedButton(const char* str_id, bool* v, ImVec2 bb = ImVec2(-1, -1), bool bNoBorder = false, bool bNoLabel = false)
	{
		bool bchanged = false;

		ImGui::BeginGroup(); // -> to detect complete isHover
		{
			//TODO:
			// Should fix mouse over/inner position checking to fix mouse wheel control..

			//cf = IM_COL32(255, 0, 255, 255); // test color

			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImVec4* colors = ImGui::GetStyle().Colors;

			float width;
			float radius;
			float height;

			std::string n = "##TOGGLEROUNDBUTTON" + ofToString(1);
			ImGui::PushID(n.c_str());
			{
				if ((bb.x == -1) && (bb.y == -1)) // default size
				{
					height = ImGui::GetFrameHeight();
					width = height * 1.55f;
				}
				else // received by args
				{
					width = bb.x;
					height = bb.y;
				}
				radius = height / 2.0f;

				ImGui::InvisibleButton(str_id, ImVec2(width, height));

				bool is_active = ImGui::IsItemActive();
				bool is_hovered = ImGui::IsItemHovered();

				if (ImGui::IsItemClicked())
				{
					*v = !*v; // flip bool

					bchanged = true;
				}

				//-=

				//TODO:
				// How to animate power off too ?

				// Animated

				float t = *v ? 1.0f : 0.0f;
				ImGuiContext& g = *GImGui;
				float ANIM_SPEED = 0.08f;
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

				// State true
				if (*v)
				{
					frame_col = ImGui::GetColorU32(
						is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBg : ImGuiCol_FrameBgHovered);
					cf = frame_col;
				}

				// State false
				else
				{
					frame_col = ImGui::GetColorU32(
						is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
					cf = frame_col;
				}

				draw_list->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), cf, height * 0.5f);

				//--

				// 1.2 Border Background Zone

				// A. Reduced alpha

				const ImU32 cb = ImGui::GetColorU32(colors[ImGuiCol_Border]);

#ifdef USE_BORDER_ROUNDE_TOGGLES
				if (!bNoBorder)
				{
					// B. No alpha changes
					draw_list->AddRect(pos, ImVec2(pos.x + width, pos.y + height), cb, height * 0.5f);
				}
#endif
				//--

				// 2.1 Small Circle

				ImU32 c1 = IM_COL32(255 * colors[ImGuiCol_SliderGrab].x, 255 * colors[ImGuiCol_SliderGrab].y, 255 * colors[ImGuiCol_SliderGrab].z, 255);

#ifndef USE_BORDER_ROUNDE_TOGGLES
				draw_list->AddCircleFilled(ImVec2(pos.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f), pos.y + radius), radius - 1.5f, c1);
#endif
				//--

				// 2.2 Border Small Circle

#ifdef USE_BORDER_ROUNDE_TOGGLES
				draw_list->AddCircleFilled(ImVec2(pos.x + radius + t * (*v ? 1 : 0) * (width - radius * 2.0f), pos.y + radius), radius - 1.5f - 1, c1);//a bit of offset

				if (!bNoBorder)
				{
					draw_list->AddCircle(ImVec2(pos.x + radius + (*v ? 1 : 0) * t * (width - radius * 2.0f), pos.y + radius), radius - 1.5f, cb);
				}
#endif
				//--

				if (!bNoLabel)
				{
					//TODO:
					//// Align text to right border
					//auto io = ImGui::GetIO();
					//const auto label = ct::toStr("Dear ImGui %s (Docking)", ImGui::GetVersion());
					//const auto size = ImGui::CalcTextSize(label.c_str());
					//ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - size.x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));
					//ImGui::Text("%s", label.c_str());

					ImGui::SameLine();

					//--

					// 3. Text Label

					float fontSize = ImGui::GetFontSize();
					const float offset_xt = 0;
					const float offset_yt = height / 2 - fontSize / 2;
					const ImVec2 p1 = ImGui::GetCursorScreenPos();
					const ImU32 ct = ImGui::GetColorU32(ImGuiCol_Text);
					const ImVec2 pt = ImVec2(p1.x + offset_xt, p1.y + offset_yt);

					draw_list->AddText(pt, ct, str_id);

					//--

					// 4. Adjust frame end ?

					const auto sztx = ImGui::CalcTextSize(str_id);
					float xx = sztx.x + ImGui::GetStyle().FramePadding.x;
					ImGui::Dummy(ImVec2(xx, 0));
				}

				//TODO: sometimes spacing related to other widgets looks weird...
			}
			ImGui::PopID();
		}
		ImGui::EndGroup();

		return bchanged;
	}

	//--

	// ofParameter BOOL rounded toggle

	//TODO:
	// There's a bug that when using
	// ImGui::Dummy(ImVec2(0.0f, 2.0f));
	// after the button it adds more spacing

	//TODO: new widget to use without ofParameters, 
	// to be used by raw c types.
	//--------------------------------------------------------------
	inline bool AddToggleRoundedButton(string label, bool& bState, ImVec2 bb = ImVec2(-1, -1), bool bNoLabel = false)
	{
		bool bNoBorder = false;

		bool bReturn = false;
		auto tmpRef = bState;

		if (ToggleRoundedButton(label.c_str(), (bool*)&tmpRef, bb, bNoBorder, bNoLabel))
		{
			bState = tmpRef;
			bReturn = true;
		}

		return bReturn;
	}

	//--------------------------------------------------------------
	inline bool AddToggleRoundedButton(ofParameter<bool>& p, ImVec2 bb = ImVec2(-1, -1), bool bNoBorder = false, bool bNoLabel = false)
	{
		bool bReturn = false;
		auto tmpRef = p.get();

		if (ToggleRoundedButton(p.getName().c_str(), (bool*)&tmpRef, bb, bNoBorder, bNoLabel))
		{
			p.set(tmpRef);
			bReturn = true;
		}

		return bReturn;
	}

	//--------------------------------------------------------------
	inline bool AddToggleRoundedButton(ofParameter<bool>& p, float height, bool bNoBorder = false, bool bNoLabel = false)
	{
		return AddToggleRoundedButton(p, ImVec2(1.15f * height, 1.15f * (2 / 3.f) * height), bNoBorder, bNoLabel);
	}

	//--------------------------------------------------------------
	inline bool AddToggleRoundedButton(ofParameter<bool>& p, std::string name, ImVec2 bb)
	{
		bool bReturn = false;
		auto tmpRef = p.get();

		if (ToggleRoundedButton(name.c_str(), (bool*)&tmpRef, bb))
		{
			p.set(tmpRef);
			bReturn = true;
		}

		return bReturn;
	}

	//--------------------------------------------------------------
	inline bool AddToggleRoundedMiniXs(ofParameter<bool>& p, bool bNoLabel = true)
	{
		bool bNoBorder = false;
		float _hu = ofxImGuiSurfing::getWidgetsHeightUnit();
		float _ht = 0.8f * _hu;

		ImVec2 bb = ImVec2(1.15f * _ht, 1.15f * (2 / 3.f) * _ht);

		return AddToggleRoundedButton(p, bb, bNoBorder, bNoLabel);
	}

	//--------------------------------------------------------------
	inline bool AddToggleRoundedMiniXsRightAligned(ofParameter<bool>& p, bool bNoLabel = true)
	{
		//bool bNoBorder = false;
		float _hu = ofxImGuiSurfing::getWidgetsHeightUnit();
		float _wu = 1.15f * _hu;
		//float _ht = 0.8f * _hu;
		ofxImGuiSurfing::AddSpacingToRightAlign(_wu);

		//ImVec2 bb = ImVec2(1.15f * _ht, 1.15f * (2 / 3.f) * _ht);
		//return AddToggleRoundedButton(p, bb, bNoBorder, bNoLabel);

		return AddToggleRoundedMiniXs(p, bNoLabel);
	}

	// API short name
	//--------------------------------------------------------------
	inline bool AddToggleRounded(ofParameter<bool>& p, ImVec2 bb = ImVec2(-1, -1))
	{
		return AddToggleRoundedButton(p, bb);
	}

	//--------------------------------------------------------------
	inline bool AddCheckBox(ofParameter<bool>& p)
	{
		bool bReturn = false;
		auto tmpRef = p.get();

		if (ImGui::Checkbox(p.getName().c_str(), (bool*)&tmpRef))
		{
			p.set(tmpRef);
			bReturn = true;
		}

		return bReturn;
	}


	//TODO: 
	// not working..
	// Two names depending of the BOOL state
	//--------------------------------------------------------------
	inline bool AddToggleRoundedButtonNamed(ofParameter<bool>& p, ImVec2 bb = ImVec2(-1, -1), std::string nameTrue = "-1", std::string nameFalse = "-1")
	{
		bool bReturn = false;
		auto tmpRef = p.get();
		std::string name;

		if (nameTrue == "-1" || nameFalse == "-1") name = p.getName();
		else
		{
			if ((bool*)&tmpRef) name = nameTrue;
			else name = nameFalse;
		}

		if (ToggleRoundedButton(name.c_str(), (bool*)&tmpRef, bb))
		{
			p.set(tmpRef);
			bReturn = true;
		}

		return bReturn;
	}
	//--------------------------------------------------------------
	inline bool AddToggleRoundedButtonNamed(ofParameter<bool>& p, std::string nameTrue, std::string nameFalse)
	{
		ImVec2 bb = ImVec2(-1, -1);
		bool bReturn = false;
		auto tmpRef = p.get();
		std::string name;

		if (tmpRef) name = nameTrue;
		else name = nameFalse;

		if (ToggleRoundedButton(name.c_str(), (bool*)&tmpRef, bb))
		{
			p.set(tmpRef);
			bReturn = true;
		}

		return bReturn;
	}

	//----


	//--------------------------------------------------------------
	inline bool AddBigButton(string name, float w = -1, float h = -1, bool border = false, bool bBlink = false)
	{
		bool bReturn = false;

		// Border when selected

		float a = 0.5f;
		float borderLineWidth = 1.0f;
		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

		// Blink

		if (bBlink)
		{
			float blinkValue = getFadeBlink();
			a = ofClamp(blinkValue, OFX_IM_BLINK_MIN, OFX_IM_BLINK_MAX);

			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		}

		bool bDrawBorder = true;

		//--

		std::string n = "##BIGBUTTON" + name + ofToString(1);
		ImGui::PushID(n.c_str());
		{
			// Border to selected
			if (border)
			{
				bDrawBorder = true;
				ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
			}

			if (w == -1) w = ImGui::GetContentRegionAvail().x; // full width
			if (h == -1) h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();

			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
			const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

			ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			{
				if (ImGui::Button(name.c_str(), ImVec2(w, h)))
				{
					ofLogVerbose("ofxSurfingImGui") << name << ": BANG";

					bReturn = true;
				}
			}
			ImGui::PopStyleColor(3);

			// Border Blink
			if (bDrawBorder && border)
			{
				ImGui::PopStyleColor();
				ImGui::PopStyleVar(1);
			}
		}
		ImGui::PopID();

		return bReturn;
	}

	//---

	//--------------------------------------------------------------
	inline bool AddBigToggle(std::string name, bool& p, float w = -1, float h = -1, bool border = false, bool bBlink = false)
	{
		// Border when selected

		float a = 0.5f;
		float borderLineWidth = 1.0f;
		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

		// Blink

		if (bBlink)
		{
			float blinkValue = getFadeBlink();
			a = ofClamp(blinkValue, OFX_IM_BLINK_MIN, OFX_IM_BLINK_MAX);

			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		}

		bool bDrawBorder = true;

		//--

		auto tmpRef = p;
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
			//std::string n = "#BT" + name + ofToString(counterBigToggle++);

			std::string n = "##BIGTOGGLE_on_" + name + ofToString(1);

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
					p = (tmpRef);
				}

				ImGui::PopStyleColor(3);

				// Border Blink
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
			std::string n = "##BIGTOGGLE_off_" + name + ofToString(1);
			ImGui::PushID(n.c_str());
			{
				const ImVec4 colorOn = style->Colors[ImGuiCol_FrameBg];
				const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

				ImVec4 colorTextDisabled = style->Colors[ImGuiCol_Text];
				colorTextDisabled = ImVec4(colorTextDisabled.x, colorTextDisabled.y, colorTextDisabled.z,
					colorTextDisabled.w * OFX_IM_TEXT_INACTIVE_ALPHA);

				ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
				ImGui::PushStyleColor(ImGuiCol_Button, colorOn);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorActive);
				ImGui::PushStyleColor(ImGuiCol_Text, colorTextDisabled);

				if (ImGui::Button(name.c_str(), ImVec2(w, h)))
				{
					_boolToggle = true;
					tmpRef = _boolToggle;
					p = (tmpRef);
				}

				ImGui::PopStyleColor(4);
			}
			ImGui::PopID();
		}

		// Debug point
		if (0)
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			const ImVec2 pdebug = ImGui::GetCursorScreenPos();
			draw_list->AddCircleFilled(ImVec2(pdebug.x, pdebug.y), 2, IM_COL32(255, 0, 255, 255)); // a bit of offset
		}

		//-

		if (p != bPre) return true; // changed
		else return false;
	}

	//--------------------------------------------------------------
	inline bool AddBigToggle(std::string name, bool& p, ImVec2 bb, bool border, bool bBlink) {
		return AddBigToggle(name, p, bb.x, bb.y, border, bBlink);
	}

	//----

	//TODO:
	// Toggle Gradient
	//https://github.com/ocornut/imgui/issues/4722

	//// Header
	//namespace ImGui
	//{
	//	bool ColoredButtonV1(const char* label, const ImVec2& size, ImU32 text_color, ImU32 bg_color_1, ImU32 bg_color_2);
	//}

	//#define IMGUI_DEFINE_MATH_OPERATORS
	//#include "imgui_internal.h"

	// Implementation
	//bool ImGui::ColoredButtonV1(const char* label, const ImVec2& size_arg, ImU32 text_color, ImU32 bg_color_1, ImU32 bg_color_2)
	//--------------------------------------------------------------
	inline bool ColoredButtonV1(const char* label, const ImVec2& size_arg, ImU32 text_color, ImU32 bg_color_1, ImU32 bg_color_2)
	{
		using namespace ImGui;

		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label);
		const ImVec2 label_size = CalcTextSize(label, NULL, true);

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		const ImRect bb(pos, pos + size);
		ItemSize(size, style.FramePadding.y);
		if (!ItemAdd(bb, id))
			return false;

		ImGuiButtonFlags flags = ImGuiButtonFlags_None;
			flags |= ImGuiButtonFlags_Repeat;
		if (g.LastItemData.ItemFlags & ImGuiItemFlags_ButtonRepeat)

		bool hovered, held;
		bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

		// Render
		const bool is_gradient = bg_color_1 != bg_color_2;
		if (held || hovered)
		{
			// Modify colors (ultimately this can be prebaked in the style)
			float h_increase = (held && hovered) ? 0.02f : 0.02f;
			float v_increase = (held && hovered) ? 0.20f : 0.07f;

			ImVec4 bg1f = ColorConvertU32ToFloat4(bg_color_1);
			ColorConvertRGBtoHSV(bg1f.x, bg1f.y, bg1f.z, bg1f.x, bg1f.y, bg1f.z);
			bg1f.x = ImMin(bg1f.x + h_increase, 1.0f);
			bg1f.z = ImMin(bg1f.z + v_increase, 1.0f);
			ColorConvertHSVtoRGB(bg1f.x, bg1f.y, bg1f.z, bg1f.x, bg1f.y, bg1f.z);
			bg_color_1 = GetColorU32(bg1f);
			if (is_gradient)
			{
				ImVec4 bg2f = ColorConvertU32ToFloat4(bg_color_2);
				ColorConvertRGBtoHSV(bg2f.x, bg2f.y, bg2f.z, bg2f.x, bg2f.y, bg2f.z);
				bg2f.z = ImMin(bg2f.z + h_increase, 1.0f);
				bg2f.z = ImMin(bg2f.z + v_increase, 1.0f);
				ColorConvertHSVtoRGB(bg2f.x, bg2f.y, bg2f.z, bg2f.x, bg2f.y, bg2f.z);
				bg_color_2 = GetColorU32(bg2f);
			}
			else
			{
				bg_color_2 = bg_color_1;
			}
		}
		RenderNavHighlight(bb, id);

#if 0
		// V1 : faster but prevents rounding
		window->DrawList->AddRectFilledMultiColor(bb.Min, bb.Max, bg_color_1, bg_color_1, bg_color_2, bg_color_2);
		if (g.Style.FrameBorderSize > 0.0f)
			window->DrawList->AddRect(bb.Min, bb.Max, GetColorU32(ImGuiCol_Border), 0.0f, 0, g.Style.FrameBorderSize);
#endif

		// V2
		int vert_start_idx = window->DrawList->VtxBuffer.Size;
		window->DrawList->AddRectFilled(bb.Min, bb.Max, bg_color_1, g.Style.FrameRounding);
		int vert_end_idx = window->DrawList->VtxBuffer.Size;
		if (is_gradient)
			ShadeVertsLinearColorGradientKeepAlpha(window->DrawList, vert_start_idx, vert_end_idx, bb.Min, bb.GetBL(), bg_color_1, bg_color_2);
		if (g.Style.FrameBorderSize > 0.0f)
			window->DrawList->AddRect(bb.Min, bb.Max, GetColorU32(ImGuiCol_Border), g.Style.FrameRounding, 0, g.Style.FrameBorderSize);

		if (g.LogEnabled)
			LogSetNextTextDecoration("[", "]");
		PushStyleColor(ImGuiCol_Text, text_color);
		RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
		PopStyleColor();

		IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
		return pressed;
	}

	//--
};
