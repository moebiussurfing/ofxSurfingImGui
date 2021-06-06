#pragma once

#include "ofMain.h"

//#define PANEL_WIDGETS_WIDTH 250
//#define PANEL_WIDGETS_HEIGHT 100
//#define BUTTON_BIG_HEIGHT 50
//#define BUTTON_COLOR_SIZE 40
//#define BUTTON_SLIM_HEIGHT2 20
//#define COLOR_STRIP_COLOR_HEIGHT 15
//#define WIDGETS_HEIGHT 50
//
//#define TEXT_INACTIVE_ALPHA 0.20f // for use on toggle buttons


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
	inline void refreshImGui_WidgetsSizes(float& __spcx, float& __spcy, float& __w100, float& __h100, float& __w99, float& __w50, float& __w33, float& __w25, float& __h)// we will update the sizes on any gui drawing point, like inside a new foldered sub-window that could be indendeted and full size is being 
	{
		__spcx = ImGui::GetStyle().ItemSpacing.x;
		__spcy = ImGui::GetStyle().ItemSpacing.y;
		__w100 = ImGui::GetContentRegionAvail().x;
		__h100 = ImGui::GetContentRegionAvail().y;
		__w99 = __w100 - __spcx;
		__w50 = __w100 / 2 - __spcx / 2;
		__w33 = __w100 / 3 - __spcx / 3;
		__w25 = __w100 / 4 - __spcx / 4;
		__h = BUTTON_BIG_HEIGHT;
	}

	// example: 
	// allows to make exact width of n widgets to fit panel size for two buttons or columns per row:
	//float __w = getImGui_WidgetWidth(__ww, 2);
	//if (ImGui::Button("_Button", ImVec2(__w, _h))) {}
	//--------------------------------------------------------------
	inline void getImGui_WidgetWidth(float &w, int amntColumns)
	{
		float __spcx = ImGui::GetStyle().ItemSpacing.x;
		float __w100 = ImGui::GetContentRegionAvail().x;
		w = __w100 / amntColumns - __spcx / amntColumns;
	}
	//--------------------------------------------------------------
	inline void getImGui_WidgetHeight(float &h, int amntRows)
	{
		float __spcy = ImGui::GetStyle().ItemSpacing.y;
		float __h100 = ImGui::GetContentRegionAvail().y;
		h = __h100 / amntRows - __spcy / amntRows;
	}

	//----

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

	// button toggle

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

		// button toggle

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
		//ImGui::SliderFloat(namename.c_str(), &parameter.get(), parameter.getMin(), parameter.getMax(), "ratio = %.3f");
		//if (ImGui::SliderFloat(namename.c_str(), parameter.get(),  parameter.getMin(), parameter.getMax(), ImVec2(w, h)))
		{
			ofLogNotice(__FUNCTION__) << name << ": BANG";

			tmpRef = parameter.get();
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

	//cute widgets !
	//https://github.com/soufianekhiat/DearWidgets

	//spin arrows widget
	//https://github.com/ocornut/imgui/issues/2649

	//spinners, loading bars 
	//https://github.com/ocornut/imgui/issues/1901#issuecomment-552185000
	//https://github.com/ocornut/imgui/issues/1901

	//Rotating text and icon demo for dear imgui 
	//https://gist.github.com/ice1000/865c7666d13b945628254aa00bd9d62d


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


	//https://gist.github.com/nariakiiwatani/dabf4cd2d04ad015bb6fabdedef7b2aa
	//namespace ImGui
	//{
	//	static bool SelectFile(const std::string &path, std::string &selected, const std::vector<std::string> &ext = {}) {
	//		bool ret = false;
	//		if (ofFile(path).isDirectory()) {
	//			if (TreeNode(ofFilePath::getBaseName(path).c_str())) {
	//				ofDirectory dir;
	//				if (!ext.empty()) {
	//					dir.allowExt("");
	//					for (auto &&e : ext) {
	//						dir.allowExt(e);
	//					}
	//				}
	//				dir.listDir(path);
	//				for (auto &f : dir) {
	//					ret |= SelectFile(f.path(), selected, ext);
	//				}
	//				TreePop();
	//			}
	//		}
	//		else if (Button(ofFilePath::getFileName(path).c_str())) {
	//			selected = path;
	//			ret = true;
	//		}
	//		return ret;
	//	}
	//}

	//TODO:
	//BUG:
	//when drawing two plots both are sharing variables ?? so only drawing one
	//--------------------------------------------------------------
	inline void AddPlot(ofParameter<float>& parameter, ImVec2 v2 = ImVec2(100, 80.0f))
	{
		ImGui::PushID(1);

		static float min = parameter.getMin();
		static float max = parameter.getMax();
		static std::string name = parameter.getName();
		//ImGui::Text(name.c_str());

		static bool animate = true;

		// Fill an array of contiguous float values to plot
		// Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
		// and the sizeof() of your structure in the "stride" parameter.

		//static const size_t duration = 60 * 4;//fps * secs
		//static float values[duration] = {};
		static float values[120] = {};

		static int values_offset = 0;
		static double refresh_time = 0.0;

		if (!animate || refresh_time == 0.0)
			refresh_time = ImGui::GetTime();
		while (refresh_time < ImGui::GetTime()) // Create data at fixed 60 Hz rate for the demo
		{
			static float phase = 0.0f;
			values[values_offset] = parameter.get();
			//values[values_offset] = cosf(phase);

			values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
			phase += 0.10f * values_offset;
			refresh_time += 1.0f / 60.0f;
		}

		static bool bOverlayAvg = false;
		static char overlay[32] = "";
		if (bOverlayAvg)
		{
			float average = 0.0f;
			for (int n = 0; n < IM_ARRAYSIZE(values); n++)
				average += values[n];
			average /= (float)IM_ARRAYSIZE(values);
			sprintf(overlay, "avg %f", average);
		}

		//ImGui::PushID(1);
		//ImGui::PlotLines("Plot", values, IM_ARRAYSIZE(values), values_offset, overlay, min, max, v2);
		ImGui::PlotLines(name.c_str(), values, IM_ARRAYSIZE(values), values_offset, overlay, min, max, v2);

		//ImGui::PushID(1);
		ImGui::Checkbox("Animate", &animate);

		ImGui::PopID();
	}

	//----

			////TODO:
		////snap engine
		//auto snap = [=](float value, float snap_threshold) -> float {
		//	float modulo = std::fmodf(value, snap_threshold);
		//	float moduloRatio = std::fabsf(modulo) / snap_threshold;
		//	if (moduloRatio < 0.5f)
		//		value -= modulo;
		//	else if (moduloRatio > (1.f - 0.5f))
		//		value = value - modulo + snap_threshold * ((value < 0.f) ? -1.f : 1.f);
		//	return value;
		//};
		////ImGui::Begin(name.data());
		////if (ImGui::IsItemActive()) 
		//{
		//	auto p = ImGui::GetWindowPos();
		//	auto size = ImGui::GetWindowSize();

		//	float x = snap(p.x, 16.f);
		//	float y = snap(p.y, 16.f);
		//	float sizex = snap(size.x, 16.f);
		//	float sizey = snap(size.y, 16.f);
		//	ImGui::SetWindowPos(ImFloor(ImVec2(x, y)));
		//}

};


//-----


//TODO:
//extra widgets
//https://github.com/MacFurax/ofxImGui/blob/docking/libs/imgui/src/imgui_widgets.cpp
namespace ImGui {
	//used by AddKnob
	inline bool KnobNeedleTrail(const char* label, float* p_value, float v_min, float v_max, float trailZero, float radius = 20, float incPrecision = 0.001)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		ImVec2 pos = ImGui::GetCursorScreenPos(); // get top left pos of current widget
		float line_height = ImGui::GetTextLineHeight();
		float space_height = line_height * 0.1; // to add between top, label, knob, value and bottom
		float space_width = radius * 0.1; // to add on left and right to diameter of knob
		ImVec4 widgetRec = ImVec4(pos.x, pos.y, radius*2.0f + space_width * 2.0f, space_height*4.0f + radius * 2.0f + line_height * 2.0f);
		ImVec2 labelLength = ImGui::CalcTextSize(label);

		ImVec2 center = ImVec2(pos.x + space_width + radius, pos.y + space_height * 2 + line_height + radius);

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float ANGLE_MIN = 3.141592f * 0.75f;
		float ANGLE_MAX = 3.141592f * 2.25f;

		ImGui::InvisibleButton(label, ImVec2(widgetRec.z, widgetRec.w));
		bool value_changed = false;
		bool is_active = ImGui::IsItemActive();
		bool is_hovered = ImGui::IsItemHovered();
		if (is_active && io.MouseDelta.x != 0.0f)
		{
			float step = (v_max - v_min) / incPrecision;
			*p_value += io.MouseDelta.x * step;
			if (*p_value < v_min) *p_value = v_min;
			if (*p_value > v_max) *p_value = v_max;
			value_changed = true;
		}

		float t = (*p_value - v_min) / (v_max - v_min);
		float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
		float angle_cos = cosf(angle), angle_sin = sinf(angle);
		float radius_inner = radius * 0.35f;

		float refZeroTrailVal = (trailZero - v_min) / (v_max - v_min);
		float refZeroTrailAngle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * refZeroTrailVal;


		//draw label
		float texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);
		draw_list->AddText(ImVec2(texPos, pos.y + space_height), ImGui::GetColorU32(ImGuiCol_Text), label);
		// draw knob
		if (style.FrameBorderSize > 0.0f)
		{
			draw_list->AddCircleFilled(center, radius + style.FrameBorderSize + 1.0f, ImGui::GetColorU32(ImGuiCol_BorderShadow), 32);
			draw_list->AddCircleFilled(center, radius + style.FrameBorderSize, ImGui::GetColorU32(ImGuiCol_Border), 32);
		}
		// draw outer knob
		draw_list->AddCircleFilled(center, radius, ImGui::GetColorU32(ImGuiCol_FrameBg), 32);

		// draw needle
		/*draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner),
			ImVec2(center.x + angle_cos * (radius-1.5f), center.y + angle_sin * (radius-1.5f)),
			ImGui::GetColorU32(ImGuiCol_SliderGrabActive), 2.0f);*/

		draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner),
			ImVec2(center.x + angle_cos * (radius - 1.5f), center.y + angle_sin * (radius - 1.5f)),
			ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), 2.0f);

		//ImGuiCol_SliderGrab



		// draw needle trail
		if (refZeroTrailAngle < angle)
		{
			draw_list->PathArcTo(center, radius - 4.5f, refZeroTrailAngle, angle, 2 + (4 * (angle - refZeroTrailAngle))); // draw needle trail
		}
		else {
			draw_list->PathArcTo(center, radius - 4.5f, angle, refZeroTrailAngle, 2 + (4 * (refZeroTrailAngle - angle))); // draw needle trail
		}

		draw_list->PathStroke(ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), false, 6.0f);

		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16); // draw inner knob
		//draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_FrameBg), 16); // draw inner knob
		draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_SliderGrabActive : is_hovered ? ImGuiCol_ButtonHovered : ImGuiCol_FrameBg), 16); // draw inner knob

		// draw value
		char temp_buf[64];
		sprintf(temp_buf, "%.2f", *p_value);
		labelLength = ImGui::CalcTextSize(temp_buf);
		texPos = pos.x + ((widgetRec.z - labelLength.x) * 0.5f);

		draw_list->AddText(ImVec2(texPos, pos.y + space_height * 3 + line_height + radius * 2), ImGui::GetColorU32(ImGuiCol_Text), temp_buf);

		return value_changed;
	}
};//ImGui

	//----

namespace ofxSurfingHelpers {

	//TODO:
	//knob

	//bool AddKnob(ofParameter<float>& parameter);
	//bool AddKnob(ofParameter<float>& parameter, float zeroRef);
	//bool AddKnob(std::string label, ofParameter<float>& parameter);
	//bool AddKnob(std::string label, ofParameter<float>& parameter, float zeroRef);

	inline bool AddKnob(ofParameter<float>& parameter)
	{
		std::string name = parameter.getName();
		//string name = parameter.getName();

		auto tmpRef = parameter.get();
		if (ImGui::KnobNeedleTrail(name.c_str(), &tmpRef, parameter.getMin(), parameter.getMax(), parameter.getMin()))
		{
			parameter.set(tmpRef);
			return true;
		}
		return false;
	}

	//inline bool AddKnob(ofParameter<float>& parameter, float zeroRef)
	//{
	//	string name = parameter.getName();
	//	auto tmpRef = parameter.get();
	//	if (ImGui::KnobNeedleTrail(name, &tmpRef, parameter.getMin(), parameter.getMax(), zeroRef))
	//	{
	//		parameter.set(tmpRef);
	//		return true;
	//	}
	//	return false;
	//}

	//inline bool AddKnob(std::string label, ofParameter<float>& parameter)
	//{
	//	string name = parameter.getName();
	//	auto tmpRef = parameter.get();
	//	if (ImGui::KnobNeedleTrail(name, &tmpRef, parameter.getMin(), parameter.getMax(), parameter.getMin()))
	//	{
	//		parameter.set(tmpRef);
	//		return true;
	//	}
	//	return false;
	//}

	//inline bool AddKnob(std::string label, ofParameter<float>& parameter, float zeroRef)
	//{
	//	string name = parameter.getName();
	//	auto tmpRef = parameter.get();
	//	if (ImGui::KnobNeedleTrail(name, &tmpRef, parameter.getMin(), parameter.getMax(), zeroRef))
	//	{
	//		parameter.set(tmpRef);
	//		return true;
	//	}
	//	return false;
	//}

};



//--

// how to set colors
//static float b = 1.0f;
//static float c = 0.5f;
//static int i = 3;// hue colors are from 0 to 7
//ImVec4 _color1 = (ImVec4)ImColor::HSV(i / 7.0f, b, b);
//ImVec4 _color2 = (ImVec4)ImColor::HSV(i / 7.0f, c, c);