#pragma once

#include "ofMain.h"

// Useful links
// https://github.com/nem0/LumixEngine/blob/timeline_gui/external/imgui/imgui_user.inl#L814

// ImGui Widgets
// - toogles and buttons
// - bool and ofParameter<bool> types

//------------------------------

#include "ofxImGui.h"
#include "imgui_internal.h"

#include "ofxSurfing_ImGui_LayoutHelpers.h"

#include "ofxSurfing_Timers.h"
//#include "ofxSurfingHelpers.h"

//------------------------------

namespace ofxImGuiSurfing
{
	////TODO:
	////test an unique_name_engine workaround..
	//static int counterBigToggle = 0;

	//-

	//--------------------------------------------------------------
	inline bool AddBigButton(ofParameter<bool>& parameter, float w = -1, float h = -1)// button but using a bool not void param
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

		if (bPre != parameter) return true;
		else return false;
	}

	// ambiguous..

	////--------------------------------------------------------------
	//inline bool AddBigButton(ofParameter<bool>& parameter)// button but using a bool not void param
	//{
	//	ImVec2 sz = ImVec2(-1.f, -1.f);
	//	AddBigButton(parameter, sz);
	//}

	////--------------------------------------------------------------
	//inline bool AddBigButton(ofParameter<bool>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f))// button but using a bool not void param
	//{
	//	AddBigButton(parameter, sz.x, sz.y);
	//}

	//-

	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<bool>& parameter, float w = -1, float h = -1)// button but using a bool not void param
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

	//----

	//example: blink white border depending on state
	//if you want to overwrite the border color, like when blinking.. Yo need to set border to false
	//float a;
	//bool b = myToggleState.get();
	//if (b) a = ofxSurfingHelpers::getFadeBlink();
	//else a = 1.0f;
	//if (b) ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)ImColor::HSV(0.5f, 0.0f, 1.0f, a));//white blink border
	//ofxSurfing::AddBigToggle(myToggleState, _w100, _h, false);
	//if (b) ImGui::PopStyleColor();

	// TODO: seems not working well linked to the param.. requires better unique name?
	//--------------------------------------------------------------
	inline bool AddBigToggle(ofParameter<bool>& parameter, float w = -1, float h = -1, bool border = false, bool bBlink = false)
	{
		// border when selected
		float a = 0.5f;
		float borderLineWidth = 1.0;
		ImGuiStyle *style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		// blink
		if (bBlink) {
			float blinkValue = ofxSurfingHelpers::getFadeBlink();
			a = ofClamp(blinkValue, 0.25, 0.75);
			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		}

		//-

		bool bDrawBorder = true;

		std::string name = parameter.getName();
		auto tmpRef = parameter.get();
		bool bPre = tmpRef;

		//--

		// default
		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
		//if (h == -1) h = ofxImGuiSurfing::getWidgetsHeightRelative();
		//if (h == -1) h = BUTTON_BIG_HEIGHT / 2;

		bool _boolToggle = tmpRef;  // default pre value, the button is disabled 

		if (_boolToggle) // was enabled
		{
			// Warning: notice that each state has a different button, so we need to push different ID's!
			// Warning: in this case we need to use the name to became the toggle functional
			// that means that we can maybe collide not unique names! 
			//string n = "#BT" + name + ofToString(counterBigToggle++);
			//ofLogNotice(__FUNCITON__) << n;
			string n = "##BIGTOGGLE_on_" + name + ofToString(1);
			ImGui::PushID(n.c_str());

			// border to selected
			if (border)
			{
				bDrawBorder = true;
				ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
			}

			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonHovered];
			const ImVec4 colorButton = style->Colors[ImGuiCol_ButtonActive];
			//const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];
			//const ImVec4 colorButton = style->Colors[ImGuiCol_ButtonHovered];

			const ImVec4 colorHover = style->Colors[ImGuiCol_ButtonHovered];
			//enabled color
			//ImVec4 colorHover2 = style->Colors[ImGuiCol_CheckMark];
			//ImVec4 colorHover2 = ImVec4(colorHover.x, colorHover.y*0, colorHover.z*0, colorHover.w * 1.0);
			//ImVec4 colorHover2 = ImVec4(colorHover.x, colorHover.y, colorHover.z, colorHover.w * 0.75);
			ImVec4 colorHover2 = ImVec4(colorHover.x, colorHover.y, colorHover.z, colorHover.w * 1.0);

			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorHover2);
			ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover2);

			ImGui::Button(name.c_str(), ImVec2(w, h));

			if (ImGui::IsItemClicked(0)) // powerOff
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

			ImGui::PopID();
		}
		else // was disabled
		{
			string n = "##BIGTOGGLE_off_" + name + ofToString(1);
			ImGui::PushID(n.c_str());

			//const ImVec4 colorOn = style->Colors[ImGuiCol_SliderGrabActive];
			//const ImVec4 colorOn = style->Colors[ImGuiCol_CheckMark];
			//const ImVec4 colorOn = { 1,0,0,1 };
			const ImVec4 colorOn = style->Colors[ImGuiCol_FrameBg];
			//const ImVec4 colorOn = style->Colors[ImGuiCol_ButtonActive];
			//const ImVec4 colorOn = style->Colors[ImGuiCol_ButtonHovered];

			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];
			//const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
			//const ImVec4 colorHover = colorOn;
			//const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
			ImVec4 colorTextDisabled = style->Colors[ImGuiCol_Text];
			colorTextDisabled = ImVec4(colorTextDisabled.x, colorTextDisabled.y, colorTextDisabled.z,
				colorTextDisabled.w * TEXT_INACTIVE_ALPHA);

			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			ImGui::PushStyleColor(ImGuiCol_Button, colorOn);
			//ImGui::PushStyleColor(ImGuiCol_Button, colorHover);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorActive);
			ImGui::PushStyleColor(ImGuiCol_Text, colorTextDisabled);

			if (ImGui::Button(name.c_str(), ImVec2(w, h)))
			{
				_boolToggle = true;
				tmpRef = _boolToggle;
				parameter.set(tmpRef);
			}

			ImGui::PopStyleColor(4);

			ImGui::PopID();
		}

		//-

		if (parameter.get() != bPre) return true; // changed
		else return false;
	}

	//--

	// Two states with two names. also with blinking with swetteable alplha border
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
				blinkValue = ofxSurfingHelpers::getFadeBlink();
			}
			float a;
			if (b) a = blinkValue;
			//if (b) a = 1 - tn;
			else a = 1.0f;
			a = ofClamp(a, 0, 1);
			if (b) ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(c_.x, c_.y, c_.z, c_.w * a));
			//if (b) ImGui::PushStyleColor(ImGuiCol_Border, (ImVec4)ImColor::HSV(0.5f, 0.0f, 1.0f, a));
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
	inline bool AddIntStepped(ofParameter<int>& parameter)
	{
		bool bChanged = false;
		auto tmpRefi = parameter.get();
		const ImU32 u32_one = 1;
		static bool inputs_step = true;

		string name = parameter.getName();
		string n = "##STEPPERint" + name + ofToString(1);
		ImGui::PushID(n.c_str());

		if (ImGui::InputScalar(parameter.getName().c_str(), ImGuiDataType_U32, (int *)&tmpRefi, inputs_step ? &u32_one : NULL, NULL, "%u"))
		{
			tmpRefi = ofClamp(tmpRefi, parameter.getMin(), parameter.getMax());
			parameter.set(tmpRefi);

			bChanged = true;
		}

		ImGui::PopID();

		return bChanged;
	}

	//----

	// vsliders
	// TODO: move label on top/bottom
	// float
	//--------------------------------------------------------------
	inline bool AddVSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false)
	{
		//TODO:
		//default (-1,-1) is full panel shape

		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetContentRegionAvail().y;

		float spcx = ImGui::GetStyle().ItemSpacing.x;
		float spcy = ImGui::GetStyle().ItemSpacing.y;

		//if (sz.x == -1) sz.x = w;
		//if (sz.y == -1) sz.y = h;
		if (sz.x == -1) sz.x = w - spcx;
		if (sz.y == -1) sz.y = h - spcy;

		//ImGui::BeginGroup();
		ImGui::PushID(("##VSLIDER" + name).c_str());

		if (bNoName) {
			//ImGui::Text(name.c_str());
			name = "";
		}

		if (ImGui::VSliderFloat(name.c_str(), sz, &tmpRef, parameter.getMin(), parameter.getMax()))
		{
			parameter.set(tmpRef);

			bChanged = true;
		}

		ImGui::PopID();
		//ImGui::EndGroup();

		return bChanged;
	}

	// int
	//--------------------------------------------------------------
	inline bool AddVSlider(ofParameter<int>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), bool bNoName = false)
	{
		//TODO:
		//default is full panel shape

		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetContentRegionAvail().y;

		float spcx = ImGui::GetStyle().ItemSpacing.x;
		float spcy = ImGui::GetStyle().ItemSpacing.y;

		//if (sz.x == -1) sz.x = w;
		//if (sz.y == -1) sz.y = h;
		if (sz.x == -1) sz.x = w - spcx;
		if (sz.y == -1) sz.y = h - spcy;

		ImGui::PushID(("##VSLIDER" + name).c_str());
		if (bNoName) name = "";

		if (ImGui::VSliderInt(name.c_str(), sz, &tmpRef, parameter.getMin(), parameter.getMax()))
		{
			parameter.set(tmpRef);

			bChanged = true;
		}

		ImGui::PopID();
		return bChanged;
	}

	//--

	//--------------------------------------------------------------
	inline bool AddBigSlider(ofParameter<float>& parameter, float w = -1, float h = -1, string format = "%.3f")// button but using a bool not void param
	{
		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = BUTTON_BIG_HEIGHT;//TODO: get widget height

		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		string n = "##BIGSLIDER" + name + ofToString(1);
		ImGui::PushID(n.c_str());

		ImGuiStyle *style = &ImGui::GetStyle();

		const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
		const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

		ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);

		//if (ImGui::SliderFloat(name.c_str(), &tmpRef,  parameter.getMin(), parameter.getMax(), ImVec2(w, h)))
		if (ImGui::SliderFloat(name.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), format.c_str()))
		{
			ofLogNotice(__FUNCTION__) << name << ": BANG";

			//tmpRef = parameter.get();
			parameter.set(tmpRef);

			bChanged = true;
		}

		ImGui::PopStyleColor(3);

		ImGui::PopID();

		return bChanged;
	}

	//--------------------------------------------------------------
	inline bool AddBigSlider(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1.f, -1.f), string format = "%.3f")// button but using a bool not void param
	{
		return AddBigSlider(parameter, sz.x, sz.y, format);
	}

	//--------------------------------------------------------------
	inline bool AddDragFloatSlider(ofParameter<float>& parameter/*, float w = 100*/)// button but using a bool not void param
	{
		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();
		float v_speed = 0.001f;//1ms

		string n = "##DRAGSLIDERfloat" + name + ofToString(1);
		ImGui::PushID(n.c_str());

		//bool ImGui::DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		if (ImGui::DragFloat(name.c_str(), &tmpRef, v_speed, parameter.getMin(), parameter.getMax()))
		{
			parameter.set(tmpRef);
			bChanged = true;
		}

		ImGui::PopID();

		return bChanged;
	}

	//--

	//--------------------------------------------------------------
	// rounded toggle buttons: 
	// https://github.com/ocornut/imgui/issues/1537
	// bool & ofParameter<bool>

	//--------------------------------------------------------------
	inline bool ToggleRoundedButton(const char* str_id, bool* v, ImVec2 vv = ImVec2(-1, -1))
	{
		ImVec2 prevCursorPos = ImGui::GetCursorScreenPos();

		bool bchanged = false;
		bool bref = v;

		float width;
		float radius;
		float height;

		string n = "##TOGGLEBUTTON" + ofToString(1);
		ImGui::PushID(n.c_str());
		{
			ImVec4* colors = ImGui::GetStyle().Colors;
			ImVec2 p = ImGui::GetCursorScreenPos();
			ImDrawList* draw_list = ImGui::GetWindowDrawList();

			if (vv.x == -1 && vv.y == -1)
			{
				height = ImGui::GetFrameHeight();
				width = height * 1.55f;
				radius = height * 0.50f;
			}
			else
			{
				width = vv.x;
				radius = vv.y * 0.5f;
				height = vv.y;
			}

			ImGui::InvisibleButton(str_id, ImVec2(width, height));
			if (ImGui::IsItemClicked()) {
				*v = !*v;
				bchanged = true;
			}

			ImGuiContext& gg = *GImGui;
			float ANIM_SPEED = 0.085f;
			if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
				float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);

			//--

			// 1. bg

			// hover
			if (ImGui::IsItemHovered())
			{
				//draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height),
				//	ImGui::GetColorU32(*v ? colors[ImGuiCol_FrameBgActive] : colors[ImGuiCol_FrameBg]), height * 0.5f);

				ImU32 c1;
				if (*v) {
					c1 = IM_COL32(255 * colors[ImGuiCol_FrameBgActive].x, 255 * colors[ImGuiCol_FrameBgActive].y, 255 * colors[ImGuiCol_FrameBgActive].z, 255);
				}
				else {
					c1 = IM_COL32(255 * colors[ImGuiCol_FrameBgActive].x, 255 * colors[ImGuiCol_FrameBgActive].y, 255 * colors[ImGuiCol_FrameBgActive].z, 255);
				}
				draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), c1, height * 0.5f);
			}

			// no hover
			else
			{
				//draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height),
				//	ImGui::GetColorU32(*v ? colors[ImGuiCol_ButtonActive] : colors[ImGuiCol_FrameBgActive]), height * 0.5f);

				ImU32 c1;
				if (*v) {
					c1 = IM_COL32(255 * colors[ImGuiCol_FrameBgActive].x, 255 * colors[ImGuiCol_FrameBgActive].y, 255 * colors[ImGuiCol_FrameBgActive].z, 255);
				}
				else {
					c1 = IM_COL32(255 * colors[ImGuiCol_FrameBgActive].x, 255 * colors[ImGuiCol_FrameBgActive].y, 255 * colors[ImGuiCol_FrameBgActive].z, 255);
				}
				draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), c1, height * 0.5f);
			}

			//colors[ImGuiCol_ButtonActive] : colors[ImGuiCol_ButtonHovered]), height * 0.5f);

			//-

			// 2. circle

			ImU32 c1 = IM_COL32(255 * colors[ImGuiCol_SliderGrab].x, 255 * colors[ImGuiCol_SliderGrab].y, 255 * colors[ImGuiCol_SliderGrab].z, 255);
			//ImU32 c1 = IM_COL32(255 * colors[ImGuiCol_Button].x, 255 * colors[ImGuiCol_Button].y, 255 * colors[ImGuiCol_Button].z, 255);
			draw_list->AddCircleFilled(ImVec2(p.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f),
				p.y + radius), radius - 1.5f, c1);

			//----

			//if (ImGui::IsItemHovered())
			//	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height),
			//		ImGui::GetColorU32(*v ?
			//			colors[ImGuiCol_ButtonActive] : colors[ImGuiCol_ButtonHovered]), height * 0.5f);
			//else
			//	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height),
			//		ImGui::GetColorU32(*v ?
			//			colors[ImGuiCol_ButtonActive] : colors[ImGuiCol_ButtonHovered]), height * 0.5f);

			//ImU32 c1 = IM_COL32(255 * colors[ImGuiCol_Button].x, 255 * colors[ImGuiCol_Button].y, 255 * colors[ImGuiCol_Button].z, 255);

			//draw_list->AddCircleFilled(ImVec2(p.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f),
			//	p.y + radius), radius - 1.5f, c1);

			////ImGui::SameLine(0,10);
			//ImGui::SameLine();
			//ImGui::AlignTextToFramePadding();//BUG: bad alignment..
			//ImGui::Text(str_id);

			ImGui::SameLine();
			float fontSize = ImGui::GetFontSize();
			const ImVec2 p1 = ImGui::GetCursorScreenPos();
			const float offset_xt = 0;
			const float offset_yt = height / 2 - fontSize / 2;
			//ImGui::Text(name.c_str(), ImVec2(p1.x + offset_x, p1.y));
			//ImU32 ct = ImGui::GetColorU32(IM_COL32(255, 0, 0, 255));
			const ImU32 ct = ImGui::GetColorU32(ImGuiCol_Text);
			const ImVec2 pt = ImVec2(p1.x + offset_xt, p1.y + offset_yt);
			//draw_list->AddCircle(pt, 2, cc);
			draw_list->AddText(pt, ct, str_id);

			//const float offset_xc = 0;
			//const float _yy = 4;
			////const float offset_yc = height + ImGui::GetStyle().ItemSpacing.y;
			//const float offset_yc = height + ImGui::GetStyle().ItemSpacing.y + _yy;
			//const ImVec2 pc = ImVec2(prevCursorPos.x + offset_xc, prevCursorPos.y + offset_yc);
			//ImGui::SetCursorScreenPos(pc);
			////ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().IndentSpacing * 0.5f);
			const auto sizetx = ImGui::CalcTextSize(str_id);
			//ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - size.x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));
			ImGui::Dummy(ImVec2(/*width +*/ sizetx.x + ImGui::GetStyle().FramePadding.x * 1.0f, 0));

		}
		ImGui::PopID();

		//TODO: add return
		// look into check box widget
		return bchanged;

		//return (bool*)v;
	}

	//-

	// ofParameter bool toggle
	//TODO:
	// there's a bug that when using
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
		else bReturn = false;


		//fix
		//return (tmpRef != parameter.get());
		return bReturn;
	}

	//--

	/*

	// ofParameter bool toggle
	//TODO:
	// there's a bug that when using
	// ImGui::Dummy(ImVec2(0.0f, 2.0f));
	// after the button it adds more spacing
	//--------------------------------------------------------------
	inline bool AddToggleRoundedButton(ofParameter<bool>& parameter, ImVec2 v = ImVec2(-1, -1))
	{
		ImVec2 prevCursorPos = ImGui::GetCursorScreenPos();

		auto tmpRef = parameter.get();
		std::string name = parameter.getName();

		string n = "##TOGGLEROUNDEDBUTTON" + name + ofToString(1);
		ImGui::PushID(n.c_str());

		ImVec4* colors = ImGui::GetStyle().Colors;
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float width;
		float radius;
		float height;

		if (v.x == -1 && v.y == -1)
		{
			height = ImGui::GetFrameHeight();
			width = height * 1.55f;
			radius = height * 0.50f;
		}
		else
		{
			width = v.x;
			radius = v.y * 0.5f;
			height = v.y;
		}

		ImGui::InvisibleButton(name.c_str(), ImVec2(width, height));
		if (ImGui::IsItemClicked())
		{
			tmpRef = !tmpRef;

			parameter.set(tmpRef);
		}

		ImGuiContext& gg = *GImGui;
		float ANIM_SPEED = 0.085f;
		if (gg.LastActiveId == gg.CurrentWindow->GetID(name.c_str()))// && g.LastActiveIdTimer < ANIM_SPEED)
			float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);

		//--

		// 1. bg

		// hover
		if (ImGui::IsItemHovered())
		{
			//draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height),
			//	ImGui::GetColorU32(*v ? colors[ImGuiCol_FrameBgActive] : colors[ImGuiCol_FrameBg]), height * 0.5f);

			ImU32 c1;
			if (tmpRef) {
				c1 = IM_COL32(255 * colors[ImGuiCol_FrameBgActive].x, 255 * colors[ImGuiCol_FrameBgActive].y, 255 * colors[ImGuiCol_FrameBgActive].z, 255);
			}
			else {
				c1 = IM_COL32(255 * colors[ImGuiCol_FrameBgActive].x, 255 * colors[ImGuiCol_FrameBgActive].y, 255 * colors[ImGuiCol_FrameBgActive].z, 255);
			}
			draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), c1, height * 0.5f);
		}

		// no hover
		else {
			//draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height),
			//	ImGui::GetColorU32(*v ? colors[ImGuiCol_ButtonActive] : colors[ImGuiCol_FrameBgActive]), height * 0.5f);

			ImU32 c1;
			if (tmpRef) {
				c1 = IM_COL32(255 * colors[ImGuiCol_FrameBgActive].x, 255 * colors[ImGuiCol_FrameBgActive].y, 255 * colors[ImGuiCol_FrameBgActive].z, 255);
			}
			else {
				c1 = IM_COL32(255 * colors[ImGuiCol_FrameBgActive].x, 255 * colors[ImGuiCol_FrameBgActive].y, 255 * colors[ImGuiCol_FrameBgActive].z, 255);
			}
			draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), c1, height * 0.5f);
		}

		//colors[ImGuiCol_ButtonActive] : colors[ImGuiCol_ButtonHovered]), height * 0.5f);

		//-

		// 2. circle

		ImU32 c1 = IM_COL32(255 * colors[ImGuiCol_SliderGrab].x, 255 * colors[ImGuiCol_SliderGrab].y, 255 * colors[ImGuiCol_SliderGrab].z, 255);
		//ImU32 c1 = IM_COL32(255 * colors[ImGuiCol_Button].x, 255 * colors[ImGuiCol_Button].y, 255 * colors[ImGuiCol_Button].z, 255);
		draw_list->AddCircleFilled(ImVec2(p.x + radius + (tmpRef ? 1 : 0) * (width - radius * 2.0f),
			p.y + radius), radius - 1.5f, c1);

		//----

		//ImGui::Text(name.c_str());

		ImGui::SameLine();
		float fontSize = ImGui::GetFontSize();
		const ImVec2 p1 = ImGui::GetCursorScreenPos();
		const float offset_xt = 0;
		const float offset_yt = height / 2 - fontSize / 2;
		//ImGui::Text(name.c_str(), ImVec2(p1.x + offset_x, p1.y));
		//ImU32 ct = ImGui::GetColorU32(IM_COL32(255, 0, 0, 255));
		const ImU32 ct = ImGui::GetColorU32(ImGuiCol_Text);
		const ImVec2 pt = ImVec2(p1.x + offset_xt, p1.y + offset_yt);
		//draw_list->AddCircle(pt, 2, cc);
		draw_list->AddText(pt, ct, name.c_str());

		const float offset_xc = 0;
		//int ypad = 2;
		const float _yy = 4;
		const float offset_yc = height + ImGui::GetStyle().ItemSpacing.y * 2 + _yy;
		const ImVec2 pc = ImVec2(prevCursorPos.x + offset_xc, prevCursorPos.y + offset_yc);
		ImGui::SetCursorScreenPos(pc);

		ImGui::PopID();

		return tmpRef;// used

		//-

		//// fix align

		//ImVec2 alignment = ImVec2(100, 100);

		////char name[32];
		////sprintf(name, "(%.1f,%.1f)", alignment.x, alignment.y);
		////if (x > 0) ImGui::SameLine();
		////ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, alignment);
		////ImGui::Selectable(name, &selected[3 * y + x], ImGuiSelectableFlags_None, ImVec2(80, 80));
		////ImGui::PopStyleVar();

		//ImGui::SameLine();
		//ImGui::Text(name.c_str(), alignment.x, alignment.y);
		//ImGui::PopID();

		//return tmpRef;

		//--

		/*
		//label

		//// Render
		//const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
		//RenderNavHighlight(bb, id);
		//RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);

		//ImVec2 pos = window->DC.CursorPos;
		//if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		//	pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
		//ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

		//const ImRect bb(pos, pos + size);
		//ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
		//ImGui::RenderTextClipped(.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

		////ImGui::SameLine(0, 10);
		////ImGui::SameLine(0, 0.5);
		//ImGui::SameLine();
		////ImGui::Dummy(ImVec2(-1.0f, 10.0f));
		//ImGui::Text(name.c_str());


		//TODO. aligning
		//const char* fmt;
		//va_list args;
		//ImVec2 size_arg(100, 30);
		//ImVec2 align(0, 0);

		//ImGuiWindow* window = ImGui::GetCurrentWindow();

		////ImGuiContext& g = *GetCurrentContext();
		////
		////auto g = ImGui::GetStyle();
		////const ImGuiStyle& style = g.Style;
		////const char* text_end = g.TempBuffer + ImFormatStringV(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), fmt, args);
		////const ImVec2 label_size = ImGui::CalcTextSize(g.TempBuffer, text_end, true, 0.0f);
		////const ImGuiID id = window->GetID(g.TempBuffer, text_end);



		//ImVec2 pos = window->DC.CursorPos;
		////if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrentLineTextBaseOffset)
		//	//pos.y += window->DC.CurrentLineTextBaseOffset - style.FramePadding.y;
		//ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);


		//const ImRect bb(pos, pos + size);
		//ImGui::ItemSize(bb, style.FramePadding.y);
		//ImGui::RenderTextClipped(bb.Min, bb.Max, g.TempBuffer, text_end, &label_size, align);


		ImGui::PopID();

		return tmpRef;// used
		*/
};
