#pragma once

#include "ofMain.h"

//links
//https://github.com/nem0/LumixEngine/blob/timeline_gui/external/imgui/imgui_user.inl#L814

//------------------------------
//
#include "ofxImGui.h"
#include "ofxSurfing_ImGui_Themes.h"
#include "imgui_internal.h"

//----

namespace ofxSurfingHelpers {

	//--------------------------------------------------------------
	// ImGui Widgets
	// why? my custom ImGui helpers
	//--------------------------------------------------------------
	////https://github.com/ocornut/imgui/issues/1537
	//--------------------------------------------------------------
	inline bool AddBigButton(ofParameter<bool>& parameter, float w = -1, float h = -1)// button but using a bool not void param
	{
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		bool bPre = tmpRef;

		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = BUTTON_BIG_HEIGHT;//TODO: get widget height

		ImGuiStyle *style = &ImGui::GetStyle();
		const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
		const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

		ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);

		ImGui::PushID(1);
		if (ImGui::Button(name.c_str(), ImVec2(w, h)))
		{
			ofLogVerbose(__FUNCTION__) << name << ": BANG";

			tmpRef = true;
			parameter.set(tmpRef);
		}
		ImGui::PopID();

		ImGui::PopStyleColor(3);

		if (bPre != parameter) return true;
		else return false;
	}

	//--------------------------------------------------------------
	inline bool AddSmallButton(ofParameter<bool>& parameter, float w = -1, float h = -1)// button but using a bool not void param
	{
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = BUTTON_BIG_HEIGHT;//TODO: get widget height

		ImGuiStyle *style = &ImGui::GetStyle();
		const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
		const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

		ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);

		ImGui::PushID(1);
		if (ImGui::Button(name.c_str(), ImVec2(w, h)))
		{
			tmpRef = true;
			parameter.set(tmpRef);
		}
		ImGui::PopID();

		ImGui::PopStyleColor(3);

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
	//ofxSurfingHelpers::AddBigToggle(myToggleState, _w100, _h, false);
	//if (b) ImGui::PopStyleColor();

	// TODO: seems not working well linked to the param.. requires better unique name?
	//--------------------------------------------------------------
	inline bool AddBigToggle(ofParameter<bool>& parameter, float w = -1, float h = -1, bool border = true)
	{
		auto tmpRef = parameter.get();
		std::string name = parameter.getName();

		bool bPre = tmpRef;

		ImGuiStyle *style = &ImGui::GetStyle();

		//--

		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = BUTTON_BIG_HEIGHT;//TODO: get widget height

		// border to selected

		const ImVec4 borderLineColor = style->Colors[ImGuiCol_Separator];

		float borderLineWidth = 1.0;
		bool bDrawBorder = false;

		bool _boolToggle = tmpRef;  // default pre value, the button is disabled 

		if (_boolToggle == true)// enabled
		{
			// border to selected
			if (_boolToggle && border)
			{
				bDrawBorder = true;
				ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
			}

			// warning: in this case we need to use the name to became the toggle functional
			// that means that we can mayube collide not unique names! 
			string n = "#"+ name + ofToString(1);
			ImGui::PushID(n.c_str());

			//ImGui::PushID(name.c_str()); 
			//ImGui::PushID(1);// fail
			//ImGui::PushID(name.c_str(), 1); // fail
			//ImGui::PushID(1, name.c_str()); // fail 

			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];
			const ImVec4 colorButton = style->Colors[ImGuiCol_ButtonHovered];
			const ImVec4 colorHover = style->Colors[ImGuiCol_ButtonHovered];
			ImVec4 colorHover2 = ImVec4(colorHover.x, colorHover.y, colorHover.z, colorHover.w * 0.75);

			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorHover2);
			ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover2);

			ImGui::Button(name.c_str(), ImVec2(w, h));
			if (ImGui::IsItemClicked(0))
			{
				_boolToggle = !_boolToggle;
				tmpRef = _boolToggle;
				parameter.set(tmpRef);
			}

			ImGui::PopStyleColor(3);

			ImGui::PopID();

			//-

			if (bDrawBorder && border)
			{
				ImGui::PopStyleColor();
				ImGui::PopStyleVar(1);
			}
		}
		else// disabled
		{
			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];
			const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
			const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
			ImVec4 colorTextDisabled = style->Colors[ImGuiCol_Text];
			colorTextDisabled = ImVec4(colorTextDisabled.x, colorTextDisabled.y, colorTextDisabled.z,
				colorTextDisabled.w * TEXT_INACTIVE_ALPHA);

			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			ImGui::PushStyleColor(ImGuiCol_Button, colorHover);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorActive);
			ImGui::PushStyleColor(ImGuiCol_Text, colorTextDisabled);

			ImGui::PushID(1);
			if (ImGui::Button(name.c_str(), ImVec2(w, h)))
			{
				_boolToggle = true;
				tmpRef = _boolToggle;
				parameter.set(tmpRef);
			}
			ImGui::PopID();

			ImGui::PopStyleColor(4);
		}

		if (parameter.get() != bPre) return true;
		else return false;
	}

	// two states names
	//--------------------------------------------------------------
	inline bool AddBigToggleNamed(ofParameter<bool>& parameter, float w = -1, float h = -1, std::string nameTrue = "-1", std::string nameFalse = "-1")
	{
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		bool bPre = tmpRef;
		
		ImGuiStyle *style = &ImGui::GetStyle();

		//--

		float _spc = ImGui::GetStyle().ItemInnerSpacing.x;

		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = BUTTON_BIG_HEIGHT;//TODO: get widget height

		if (nameTrue == "-1") nameTrue = name;
		if (nameFalse == "-1") nameFalse = name;

		//--

		bool _boolToggle = tmpRef;  // default value, the button is disabled 

		// enabled
		if (_boolToggle == true)
		{
			const ImVec4 colorActive = style->Colors[ImGuiCol_Separator];
			const ImVec4 colorButton = style->Colors[ImGuiCol_ButtonHovered];
			const ImVec4 colorHover = style->Colors[ImGuiCol_ButtonHovered];

			ImGui::PushID(nameTrue.c_str());
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
			const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];
			const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
			const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
			ImVec4 colorTextDisabled = style->Colors[ImGuiCol_Text];

			ImGui::PushID(nameTrue.c_str());
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);
			ImGui::PushStyleColor(ImGuiCol_Button, colorHover);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
			ImGui::PushStyleColor(ImGuiCol_Text, colorTextDisabled);

			ImGui::PushID(1);
			if (ImGui::Button(nameFalse.c_str(), ImVec2(w, h))) {
				_boolToggle = true;
				tmpRef = _boolToggle;
				parameter.set(tmpRef);
			}
			ImGui::PopID();

			ImGui::PopStyleColor(4);
			ImGui::PopID();
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

		ImGui::PushID(1);
		if (ImGui::InputScalar(parameter.getName().c_str(), ImGuiDataType_U32, (int *)&tmpRefi, inputs_step ? &u32_one : NULL, NULL, "%u"))
		{
			tmpRefi = ofClamp(tmpRefi, parameter.getMin(), parameter.getMax());
			parameter.set(tmpRefi);

			bChanged = true;
		}
		ImGui::PopID();

		return bChanged;
	}

	//--------------------------------------------------------------
	inline bool AddBigSlider(ofParameter<float>& parameter, float w = -1, float h = -1)// button but using a bool not void param
	{
		if (w == -1) w = ImGui::GetContentRegionAvail().x;
		if (h == -1) h = BUTTON_BIG_HEIGHT;//TODO: get widget height

		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();

		ImGuiStyle *style = &ImGui::GetStyle();

		const ImVec4 colorButton = style->Colors[ImGuiCol_Button];
		const ImVec4 colorHover = style->Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style->Colors[ImGuiCol_ButtonActive];

		ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colorHover);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, colorActive);

		//TODO:
		ImGui::PushID(1);
		if (ImGui::SliderFloat(name.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), "ratio = %.3f"))
		//if (ImGui::SliderFloat(name.c_str(), &tmpRef,  parameter.getMin(), parameter.getMax(), ImVec2(w, h)))
		{
			ofLogNotice(__FUNCTION__) << name << ": BANG";

			//tmpRef = parameter.get();
			parameter.set(tmpRef);

			bChanged = true;
		}
		ImGui::PopID();

		ImGui::PopStyleColor(3);

		return bChanged;
	}

	//--------------------------------------------------------------
	inline bool AddDragFloatSlider(ofParameter<float>& parameter/*, float w = 100*/)// button but using a bool not void param
	{
		bool bChanged = false;
		auto tmpRef = parameter.get();
		string name = parameter.getName();
		float v_speed = 0.001f;//1ms

		ImGui::PushID(1);
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

	//// TODO:
	////--------------------------------------------------------------
	//inline int ImGui_ButtonsMatrix(int amountButtons, ofParameter<int> selectorTarget, string name)
	//{
	//	{
	//		int _selected = -1;
	//		//preset selector
	//		//toggle button matrix
	//		ImVec2 button_sz(40, 40);
	//		//Manually wrapping
	//		//(we should eventually provide this as an automatic layout feature, but for now you can do it manually)
	//		//ImGui::Text("PRESET SELECTOR:");
	//		ImGuiStyle& style = ImGui::GetStyle();
	//		int _amtButtons = mainGroupAmtPresetsFav;
	//		float _windowVisible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
	//		for (int n = 0; n < _amtButtons; n++)
	//		{
	//			ImGui::PushID(n);
	//			//string name = ofToString((char)(bKeys[0][n]));
	//			//customize colors
	//			{
	//				if (PRESET_Selected_IndexMain.get() == n)//when selected
	//				{
	//					const ImVec4 colorActive = style.Colors[ImGuiCol_ButtonHovered];//changes the color
	//					ImGui::PushStyleColor(ImGuiCol_Button, colorActive);
	//				}
	//				else {
	//					const ImVec4 colorButton = style.Colors[ImGuiCol_Button];//do not changes the color
	//					ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
	//				}
	//				//draw button
	//				if (ImGui::Button(name.c_str(), button_sz))
	//				{
	//					//populatePreset(n);//trig load preset
	//					_selected = n;
	//				}
	//				//customize colors
	//				ImGui::PopStyleColor();
	//			}
	//			float last_button_x2 = ImGui::GetItemRectMax().x;
	//			float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
	//			if (n + 1 < _amtButtons && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
	//			ImGui::PopID();
	//		}
	//		return _selected;
	//	}
	//}

	//--

	// spinner progress indicator
	//https://github.com/ocornut/imgui/issues/1901
	//https://discourse.dearimgui.org/t/spinner-modified-code-from-issue-1901/22

	//namespace ImGui {
	//
	//	bool BufferingBar(const char* label, float value, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col) {
	//		ImGuiWindow* window = GetCurrentWindow();
	//		if (window->SkipItems)
	//			return false;
	//
	//		ImGuiContext& g = *GImGui;
	//		const ImGuiStyle& style = g.Style;
	//		const ImGuiID id = window->GetID(label);
	//
	//		ImVec2 pos = window->DC.CursorPos;
	//		ImVec2 size = size_arg;
	//		size.x -= style.FramePadding.x * 2;
	//
	//		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	//		ItemSize(bb, style.FramePadding.y);
	//		if (!ItemAdd(bb, id))
	//			return false;
	//
	//		// Render
	//		const float circleStart = size.x * 0.7f;
	//		const float circleEnd = size.x;
	//		const float circleWidth = circleEnd - circleStart;
	//
	//		window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
	//		window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), fg_col);
	//
	//		const float t = g.Time;
	//		const float r = size.y / 2;
	//		const float speed = 1.5f;
	//
	//		const float a = speed * 0;
	//		const float b = speed * 0.333f;
	//		const float c = speed * 0.666f;
	//
	//		const float o1 = (circleWidth + r) * (t + a - speed * (int)((t + a) / speed)) / speed;
	//		const float o2 = (circleWidth + r) * (t + b - speed * (int)((t + b) / speed)) / speed;
	//		const float o3 = (circleWidth + r) * (t + c - speed * (int)((t + c) / speed)) / speed;
	//
	//		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, bg_col);
	//		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, bg_col);
	//		window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, bg_col);
	//	}
	//
	//	bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
	//		ImGuiWindow* window = GetCurrentWindow();
	//		if (window->SkipItems)
	//			return false;
	//
	//		ImGuiContext& g = *GImGui;
	//		const ImGuiStyle& style = g.Style;
	//		const ImGuiID id = window->GetID(label);
	//
	//		ImVec2 pos = window->DC.CursorPos;
	//		ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);
	//
	//		const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	//		ItemSize(bb, style.FramePadding.y);
	//		if (!ItemAdd(bb, id))
	//			return false;
	//
	//		// Render
	//		window->DrawList->PathClear();
	//
	//		int num_segments = 30;
	//		int start = abs(ImSin(g.Time*1.8f)*(num_segments - 5));
	//
	//		const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
	//		const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;
	//
	//		const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);
	//
	//		for (int i = 0; i < num_segments; i++) {
	//			const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
	//			window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
	//				centre.y + ImSin(a + g.Time * 8) * radius));
	//		}
	//
	//		window->DrawList->PathStroke(color, false, thickness);
	//	}
	//
	//}
		//namespace ImGui 
		//{
	//using ComVec4 = const ImVec4 &;
	//auto Spinner(float radius, float thickness, int num_segments, float speed, ComVec4 color) -> void {
	//	//auto ImGui::Spinner(float radius, float thickness, int num_segments, float speed, ComVec4 color) -> void {
	//	auto window = GetCurrentWindow();
	//	if (window->SkipItems)
	//		return;
	//
	//	auto &g = *GImGui;
	//	const auto &style = g.Style;
	//	auto &&pos = ImGui::GetCursorPos();
	//	ImVec2 size{ radius * 2, radius * 2 };
	//	const ImRect bb{ pos, pos + size };
	//	ItemSize(bb);
	//	if (!ItemAdd(bb, 0))
	//		return;
	//
	//	auto time = static_cast<float>(g.Time) * speed;
	//	window->DrawList->PathClear();
	//	int start = static_cast<int>(abs(ImSin(time) * (num_segments - 5)));
	//	const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
	//	const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;
	//	const auto &&centre = pos + radius;
	//	for (auto i = 0; i < num_segments; i++) {
	//		const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
	//		window->DrawList->PathLineTo({ centre.x + ImCos(a + time * 8) * radius,
	//									  centre.y + ImSin(a + time * 8) * radius });
	//	}
	//	window->DrawList->PathStroke(GetColorU32(color), false, thickness);
	//}

	//}


	// rounded toggle buttons: bool & ofParameter<bool>
	//--------------------------------------------------------------
	inline void ToggleButton(const char* str_id, bool* v)
	{
		ImGui::PushID(1);

		ImVec4* colors = ImGui::GetStyle().Colors;
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float height = ImGui::GetFrameHeight();
		float width = height * 1.55f;
		float radius = height * 0.50f;

		ImGui::InvisibleButton(str_id, ImVec2(width, height));
		if (ImGui::IsItemClicked()) *v = !*v;
		ImGuiContext& gg = *GImGui;
		float ANIM_SPEED = 0.085f;
		if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
			float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);
		if (ImGui::IsItemHovered())
			draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f)), height * 0.5f);
		else
			draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f)), height * 0.50f);
		draw_list->AddCircleFilled(ImVec2(p.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

		ImGui::SameLine();
		ImGui::Text(str_id);

		ImGui::PopID();
	}

	// ofParameter bool toggle
	//--------------------------------------------------------------
	inline bool AddToggleRounded(ofParameter<bool>& parameter, ImVec2 v = ImVec2(-1, -1))
	{
		ImGui::PushID(1);

		auto tmpRef = parameter.get();
		std::string name = parameter.getName();

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

		if (ImGui::IsItemHovered())
			draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height),
				ImGui::GetColorU32(tmpRef ?
					colors[ImGuiCol_ButtonActive] : colors[ImGuiCol_ButtonHovered]), height * 0.5f);
		else
			draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height),
				ImGui::GetColorU32(tmpRef ?
					colors[ImGuiCol_ButtonActive] : colors[ImGuiCol_ButtonHovered]), height * 0.5f);

		//draw_list->AddCircleFilled(ImVec2(p.x + radius + (tmpRef ? 1 : 0) * (width - radius * 2.0f), 
		//	p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

		ImU32 c1 = IM_COL32(255 * colors[ImGuiCol_Button].x, 255 * colors[ImGuiCol_Button].y, 255 * colors[ImGuiCol_Button].z, 255);

		draw_list->AddCircleFilled(ImVec2(p.x + radius + (tmpRef ? 1 : 0) * (width - radius * 2.0f),
			p.y + radius), radius - 1.5f, c1);

		//--

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

		//ImGui::SameLine(0, 10);
		//ImGui::SameLine(0, 0.5);
		ImGui::SameLine();
		//ImGui::Dummy(ImVec2(-1.0f, 10.0f));
		ImGui::Text(name.c_str());


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
	}

};