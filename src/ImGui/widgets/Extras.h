#pragma once

/*

	TODO:

*/


#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"
#include "imconfig.h"

#include "GuiConstants.h"
#include "surfingTimers.h"

//----

// Some interesting widgets candidates 
// to be added to the add-on.
// Some widgets are already included!

// Cute widgets !
// https://github.com/soufianekhiat/DearWidgets

// Spin arrows widget
// https://github.com/ocornut/imgui/issues/2649

// Spinners, loading bars 
// https://github.com/ocornut/imgui/issues/1901#issuecomment-552185000
// https://github.com/ocornut/imgui/issues/1901

// Rotating text and icon demo for dear ImGui 
// https://gist.github.com/carasuca/e72aacadcf6cf8139de46f97158f790f

// Mosaic project
// https://github.com/d3cod3/ofxVisualProgramming
// https://github.com/d3cod3/ofxVisualProgramming/blob/master/src/core/imgui_plot.cpp
// https://github.com/d3cod3/ofxVisualProgramming/blob/master/src/core/imgui_helpers.h

// Extra widgets
// https://github.com/MacFurax/ofxImGui/blob/docking/libs/imgui/src/imgui_widgets.cpp

//----

namespace ofxImGuiSurfing
{
	//--------------------------------------------------------------
	inline void AddTooltip2(std::string text, bool bEnabled = true)//call after the pop up trigger widget
	{
		if (!bEnabled) return;

		//if (IsItemHovered() && GImGui->HoveredIdTimer > 1000) // delayed
		//if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 500) // delayed // not work ?

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextWrapped(text.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//--------------------------------------------------------------
	static void AddTooltipHelp(const char* desc) {
		ImGui::TextDisabled("?");
		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			//ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			//ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//--

	//--------------------------------------------------------------
	inline void AddTextTimecode(int seconds, std::string pre = "", bool onDrawList = false, ImVec2 pos = ImVec2(0, 0), float fontScale = 1.0f) {
		int _hours = static_cast<int>(ceil(seconds) / 3600);
		int _minutes = static_cast<int>(ceil(seconds) / 60);
		int _seconds = static_cast<int>(round(seconds)) % 60;

		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		//if (draw_list == NULL)
		//{
		//	draw_list = &ImGui::GetWindowDrawList();
		//}

		string _sh, _sm, _ss;

		if (_hours < 10) {
			_sh = "0" + ofToString(_hours);
		}
		else {
			_sh = ofToString(_hours);
		}

		if (_minutes < 10) {
			_sm = "0" + ofToString(_minutes);
		}
		else {
			_sm = ofToString(_minutes);
		}

		if (_seconds < 10) {
			_ss = "0" + ofToString(_seconds);
		}
		else {
			_ss = ofToString(_seconds);
		}

		if (onDrawList)
		{
			char temp[256];
			sprintf(temp, "%s %s:%s:%s", pre.c_str(), _sh.c_str(), _sm.c_str(), _ss.c_str());
			draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize() * fontScale, pos, IM_COL32_WHITE, temp, NULL, 0.0f);
		}
		else
		{
			ImGui::Text("%s %s:%s:%s", pre.c_str(), _sh.c_str(), _sm.c_str(), _ss.c_str());
		}
	}

	//--------------------------------------------------------------
	inline void AddLabelLinkURL(const char* desc, const char* url, bool bBlink = true)
	{
		// Debug
		static bool bDebug = 0;
		//ImGui::Checkbox("Debug", &bDebug);
		//ImGui::Spacing();

		//--

		//ImGui::BeginGroup(); // -> To detect complete is_hovered

		std::string n = "##AddLabelLinkURL" + ofToString(desc);
		ImGui::PushID(n.c_str());

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImVec4* colors = ImGui::GetStyle().Colors;

		static bool is_clicked = false;
		static bool is_actived = false;
		static bool is_hovered = false;

		float w = getWidgetsWidth(1);
		float h1 = getWidgetsHeightRelative();
		float h = 1 * h1;

		ImVec2 from = ImGui::GetCursorScreenPos();
		if (bDebug) IMGUI_SUGAR__DEBUG_POINT(ofColor::yellow);

		ImVec2 to;

		//--

		// Text
		{
			// Border when selected
			float a = 0.5f;
			const ImVec4 c_ = colors[ImGuiCol_Text];
			ImVec4 colText = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			// Blink
			bool _bBlink = bBlink && is_hovered;
			if (_bBlink)
			{
				a = ofClamp(ofxSurfingHelpers::getFadeBlink(), 0.25, 0.75);
				colText = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
			}

			if (_bBlink) ImGui::PushStyleColor(ImGuiCol_Text, colText);

			{
				ImGui::TextWrapped(desc);
				//is_clicked = ImGui::IsItemClicked();
				//is_actived = ImGui::IsItemActive();
				//is_hovered = ImGui::IsItemHovered();
			}

			if (_bBlink) ImGui::PopStyleColor();

			if (is_clicked)
			{
				ofLogNotice("ofxSurfingImGui") << "Clicked " << ofToString(desc);
				ofLaunchBrowser(url);
			}

			to = ImGui::GetCursorScreenPos();
			if (bDebug) IMGUI_SUGAR__DEBUG_POINT(ofColor::yellow);

			h = to.y - from.y;
		}

		//--

		// Box invisible to click

		// Go up back
		ImGui::SetCursorScreenPos(from);
		//IMGUI_SUGAR__DEBUG_POINT(ofColor::green);

		ImGui::InvisibleButton(desc, ImVec2(w, h), ImGuiButtonFlags_None);
		is_clicked = ImGui::IsItemClicked();
		is_actived = ImGui::IsItemActive();
		is_hovered = ImGui::IsItemHovered();

		//--

		// Box draw

		if (bDebug)
		{
			// Go up back
			ImGui::SetCursorScreenPos(from);
			//IMGUI_SUGAR__DEBUG_POINT(ofColor::green);

			ImVec4 color(1, 1, 1, 1);
			if (is_clicked) color = ImVec4(1, 0, 0, 1);
			if (is_hovered) color = ImVec4(0, 0, 1, 1);
			if (is_actived) color = ImVec4(0, 1, 0, 1);

			float rounding = 2;
			ImDrawFlags flags = ImDrawFlags_None;
			draw_list->AddRect(from, to + ImVec2(w, 0), ImGui::GetColorU32(color), rounding, flags);

			IMGUI_SUGAR__DEBUG_POINT2(ofColor::blue, from);
			IMGUI_SUGAR__DEBUG_POINT2(ofColor::blue, to);
		}

		//--

		ImGui::PopID();

		//ImGui::EndGroup();
	}

	//--------------------------------------------------------------
	inline void AddLinkUrlButton(const char* desc, const char* url, float retinaScale = 1.0f, bool bBlink = true)
	{
		ImGui::InvisibleButton("empty", ImVec2(224 * retinaScale, 1));  // fix widget width

		//TODO:
		bool bUseButton = true;

		static bool isHover = false;

		float w = getWidgetsWidth(1);
		float h = getWidgetsHeightRelative();
		float h2 = 1.5f * h;

		// Border when selected
		float a = 0.5f;
		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_Text];
		ImVec4 colText = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

		// Blink
		static bool _bBlink;
		_bBlink = bBlink && isHover;
		if (_bBlink)
		{
			float blinkValue = ofxSurfingHelpers::getFadeBlink();
			a = ofClamp(blinkValue, 0.25, 0.75);
			colText = ImVec4(c_.x, c_.y, c_.z, c_.w * a);
		}

		//ImGui::TextWrapped("Open Internet Browser");

		ImGui::Spacing();

		if (_bBlink)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, colText);
		}

		if (bUseButton)
		{
			if (ImGui::Button(desc, ImVec2(w, h)))
			{
				ofLaunchBrowser(url);
			}
		}
		else
		{
			//TODO: text clickable..
			ImGui::TextWrapped(desc);
			ImGui::InvisibleButton("##URL", { w, h });
		}

		if (_bBlink)
		{
			ImGui::PopStyleColor();
		}

		isHover = ImGui::IsItemHovered();
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextWrapped("Open Internet Browser");
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//----

	// File Selector

	// Taken from https://gist.github.com/nariakiiwatani/dabf4cd2d04ad015bb6fabdedef7b2aa
	// Buttons selector for files on a folder:
	// Creates a button for each file showing each file names
	//--------------------------------------------------------------
	static bool AddFileSelector(const std::string& path, std::string& selected, /*int &index, */const std::vector<std::string>& ext = {}) {
		bool ret = false;

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetFontSize() * 2;

		if (ofFile(path).isDirectory()) {

			ImGuiTreeNodeFlags flagst;
			flagst = ImGuiTreeNodeFlags_None;
			//flagst |= ImGuiTreeNodeFlags_DefaultOpen;
			flagst |= ImGuiTreeNodeFlags_Framed;
			if (ImGui::TreeNodeEx(ofFilePath::getBaseName(path).c_str(), flagst))

				//if (TreeNode(ofFilePath::getBaseName(path).c_str()))
			{
				ofDirectory dir;
				if (!ext.empty()) {
					dir.allowExt("");
					for (auto&& e : ext) {
						dir.allowExt(e);
					}
				}
				dir.listDir(path);
				for (auto& f : dir) {
					ret |= AddFileSelector(f.path(), selected, ext);
				}
				ImGui::TreePop();
			}
		}
		else if (ImGui::Button(ofFilePath::getFileName(path).c_str(), ImVec2(w, h))) {
			selected = path;
			ret = true;
		}
		return ret;
	}

	//TODO: add index
	//TODO: index not reflected
	// buttons selector for files on a folder:
	// creates a button for each file showing each file names
	//--------------------------------------------------------------
	static bool AddFilesPicker(const std::string& path, std::string& selected, ofParameter<int>& _index, const std::vector<std::string>& ext = {}) {
		bool ret = false;

		float w = ImGui::GetContentRegionAvail().x;
		float h = ImGui::GetFontSize() * 2;

		int i = -1;

		if (ofFile(path).isDirectory()) {

			ImGuiTreeNodeFlags flagst;
			flagst = ImGuiTreeNodeFlags_None;
			//flagst |= ImGuiTreeNodeFlags_DefaultOpen;
			//flagst |= ImGuiTreeNodeFlags_Framed;

			string _labelf = "Files";
			//string _labelf = ofFilePath::getBaseName(path).c_str();

			//if (TreeNode(ofFilePath::getBaseName(path).c_str()))
			if (ImGui::TreeNodeEx(_labelf.c_str(), flagst))
			{
				ofDirectory dir;
				if (!ext.empty()) {
					dir.allowExt("");
					for (auto&& e : ext) {
						dir.allowExt(e);
					}
				}
				dir.listDir(path);

				//int i = 0;
				//for (auto &f : dir) {
				//	string _n = ofToString(i);
				//	ret |= AddFilesPicker(_n.c_str(), selected, ext);
				//	i++;
				//}

				for (auto& f : dir)
				{
					ret |= AddFilesPicker(f.path(), selected, _index, ext);
				}

				ImGui::TreePop();
			}
		}
		else // a file
		{
			i++;
			if (ImGui::Button(ofFilePath::getFileName(path).c_str(), ImVec2(w, h))) {

				selected = path;
				ret = true;

				////TODO: index not reflected
				//if (i != -1) _index = i;
			}
		}
		return ret;
	}

	//------------------------------------------------

	// Taken from
	// https://github.com/d3cod3/ofxVisualProgramming
	// https://github.com/d3cod3/ofxVisualProgramming/blob/66e7d578fab47a413e7604efe208bd276ab2927c/src/core/imgui_controls.cpp#L287

	//--------------------------------------------------------------
	inline bool AddPad2D(float* _x, float* _y, ImVec2 sz = ImVec2{ -1,-1 })
	{
		float w;
		float h;

		//fix bug oversize
		float offset = 4;

		if (sz.x == -1) {//full width 
			float spx = ImGui::GetStyle().ItemSpacing.x;
			w = ofxImGuiSurfing::getWindowWidth() - offset;
		}
		else w = sz.x;
		if (sz.y == -1) {//4 units height
			float spy = ImGui::GetStyle().ItemSpacing.y;
			h = ofxImGuiSurfing::getWidgetsHeightUnit() * 4 - offset;
		}
		else h = sz.y;

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImGuiStyle& style = GImGui->Style;

		// visuals
		enum { LINE_WIDTH = 2 }; // handlers: small lines width
		enum { GRAB_RADIUS = 6 }; // handlers: circle radius

		ImGuiWindow* Window = ImGui::GetCurrentWindow();

		// Prepare canvas

		float dimx;
		float dimy;
		dimx = w;
		dimy = h;

		ImVec2 Canvas(dimx, dimy);
		ImRect bb(Window->DC.CursorPos, Window->DC.CursorPos + Canvas);
		ImGui::ItemSize(bb);

		// Bg
		draw_list->
			AddRectFilled(bb.GetTL(), bb.GetBR(), ImGui::GetColorU32(ImGuiCol_FrameBg));

		// Boxes
		const int amt = 4;

		// Background grid

		if (Canvas.x >= amt)
		{
			for (int i = 0; i <= Canvas.x; i += static_cast<int>((Canvas.x / amt)))
			{
				draw_list->
					AddLine(
						ImVec2(bb.Min.x + i, bb.Min.y),
						ImVec2(bb.Min.x + i, bb.Max.y - 1),
						IM_COL32(255, 255, 255, 20));
			}
		}

		// Grid

		if (Canvas.y >= amt) {
			for (int i = 0; i <= Canvas.y; i += static_cast<int>((Canvas.y / amt)))
			{
				draw_list->
					AddLine(
						ImVec2(bb.Min.x, bb.Min.y + i),
						ImVec2(bb.Max.x - 1, bb.Min.y + i),
						IM_COL32(255, 255, 255, 20));
			}
		}

		// Border

		draw_list->
			AddRect(bb.GetTL(), bb.GetBR() + ImVec2{ 1,1 }, ImGui::GetColorU32(ImGuiCol_Border));

		// Cross lines

		static auto c1 = ImGui::GetColorU32(ImGuiCol_Text);
		static auto c2 = ImGui::GetColorU32(ImGuiCol_Text);
		ImVec4 _c1;

		draw_list->
			AddLine(
				ImVec2(bb.Min.x + (Canvas.x * *_x), bb.Min.y),
				ImVec2(bb.Min.x + (Canvas.x * *_x), bb.Max.y - 1),
				c1, LINE_WIDTH);

		draw_list->
			AddLine(
				ImVec2(bb.Min.x, bb.Min.y + (Canvas.y * *_y)),
				ImVec2(bb.Max.x - 1, bb.Min.y + (Canvas.y * *_y)),
				c1, LINE_WIDTH);


		// Behavior 
		// Drag from circle

		bool bChanged = false;

		ImVec2 prevCursorPos = ImGui::GetCursorScreenPos();

		////TODO:
		// can't make it bigger
		//bool szGrip = 20;
		//ImGui::SetCursorScreenPos(
		//	ImVec2(
		//		bb.Min.x + (Canvas.x * *_x) - szGrip/2,
		//		bb.Min.y + (Canvas.y * *_y) - szGrip/2));
		//ImGui::InvisibleButton("circleGripBtn", ImVec2(szGrip, szGrip));

		ImGui::SetCursorScreenPos(
			ImVec2(
				bb.Min.x + (Canvas.x * *_x) - 4,
				bb.Min.y + (Canvas.y * *_y) - 4));
		ImGui::InvisibleButton("circleGripBtn", ImVec2(8, 8));

		bool bHover = ImGui::IsItemHovered();
		{
			_c1 = style.Colors[bHover ? ImGuiCol_Text : ImGuiCol_TextDisabled];
			c2 = ImGui::GetColorU32(bHover ? ImGuiCol_Text : ImGuiCol_TextDisabled);
		}
		float a = 1;//alpha
		if (bHover) a = ofMap(ofxSurfingHelpers::Bounce(), 0, 1, 0.4, 1);//blink
		c1 = ImGui::GetColorU32(ImVec4(_c1.x, _c1.y, _c1.z, _c1.w * 0.35f * a));//less opacity

		static bool isDraggingCircle = false;
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
		{
			bool bFixLock = false;

			////TODO:
			//// fix bug
			//// over resize width
			//// when dragging right border..
			//float offset = 1;
			//if (ImGui::GetMousePos().x - bb.Min.x >= w - offset)
			//{
			//	bFixLock = true;
			//}
			//if (ImGui::GetMousePos().y - bb.Min.y >= h - offset)
			//{
			//	bFixLock = true;
			//}
			//if (bFixLock)
			//{
			//	//cout << "WARNING" << endl;
			//}

			if (!bFixLock)
			{
				if (!isDraggingCircle)
				{
					isDraggingCircle = true;
				}

				ImVec2 _pos =
					ImClamp(
						ImVec2((ImGui::GetMousePos().x - bb.Min.x) / Canvas.x,
							(ImGui::GetMousePos().y - bb.Min.y) / Canvas.y),

						ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f));

				// Set values to vars!
				*_x = _pos.x;
				*_y = _pos.y;

				bChanged = true;
			}
		}
		else if (ImGui::IsItemDeactivated())
		{
			if (isDraggingCircle) isDraggingCircle = false;
		}

		// Drag circle

		draw_list->
			AddCircleFilled(
				ImVec2(
					bb.Min.x + (Canvas.x * *_x),
					bb.Min.y + (Canvas.y * *_y)),
				GRAB_RADIUS,
				ImGui::GetColorU32(c2), 10);
		//IM_COL32(255, 255, 255, 245), 6);

		ImGui::SetCursorScreenPos(prevCursorPos);

		return bChanged;
	}

	//--------------------------------------------------------------
	inline bool AddPad2D(ofParameter<float>& x, ofParameter<float>& y, ImVec2 sz = ImVec2{ -1,-1 })
	{
		//ImGui::Spacing();

		string s = "PLOT ";
		//s += x.getName();
		//s += " / ";
		//s += y.getName();
		ImGui::Text(s.c_str());

		float t1 = x.get();
		float t2 = y.get();

		if (ofxImGuiSurfing::AddPad2D(&t1, &t2, ImVec2{ sz.x, sz.y }))
		{
			x.set(t1);
			y.set(t2);

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------
	inline void AddPlot(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1, -1))
	{
		float w;
		float h;
		if (sz.x == -1) {
			w = ofxImGuiSurfing::getWindowWidth();
		}
		else w = sz.x;
		if (sz.y == -1) {
			h = ofxImGuiSurfing::getWidgetsHeightUnit() * 4;
		}
		else h = sz.y;

		sz = ImVec2(w, h);

		ImGui::PushID(1);

		static float min = parameter.getMin();
		static float max = parameter.getMax();
		static std::string name = parameter.getName();

		ImGui::Text(name.c_str());

		static bool bOn = true;

		// Fill an array of contiguous float values to plot
		// Tip: If your float aren't contiguous but part of a structure, 
		// you can pass a pointer to your first float
		// and the sizeof() of your structure in the "stride" parameter.

		//static const size_t duration = 60 * 4;//fps * secs
		//static float values[duration] = {};
		static float values[120] = {};

		static int values_offset = 0;
		static double refresh_time = 0.0;

		if (!bOn || refresh_time == 0.0)
			refresh_time = ImGui::GetTime();

		// Create data at fixed 60 Hz rate for the demo
		while (refresh_time < ImGui::GetTime())
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

		ImGui::PlotLines("", values, IM_ARRAYSIZE(values), values_offset, overlay, min, max, sz);
		//ImGui::PlotLines(name.c_str(), values, IM_ARRAYSIZE(values), values_offset, overlay, min, max, sz);

		ImGui::Checkbox("On", &bOn);

		ImGui::PopID();
	}

	//----

	// LEGACY
	//--------------------------------------------------------------
	inline void AddVoidWidget()
	{
		float h = ImGui::GetIO().FontDefault->FontSize + ImGui::GetStyle().FramePadding.y * 2;

		//TODO:
		ImGui::InvisibleButton("_inv_", ImVec2(10, h), ImGuiButtonFlags_None);
		//ImGui::InvisibleButton("_inv_", ImVec2(10, h), ImGuiButtonFlags_Disabled);
		//ImGui::Dummy(ImVec2(0, 2 * ImGui::GetStyle().ItemSpacing.y + 2 * ImGui::GetStyle().ItemInnerSpacing.y)); // hide widget
	}
	//TODO: Useful to hide widgets. Mainly useful when passing paramGroups
	// then we should know the widget size to not destroy the layout..
	//--------------------------------------------------------------
	inline void AddWidgetEmpty()
	{
		AddVoidWidget();
	}

	//--

	//--------------------------------------------------------------
	inline void AddProgressBar2(const float valuePrc, float max = 1.0f, bool noText = true)
	{
		const float _w100 = ImGui::GetContentRegionAvail().x;
		const float pad = 0;

		//TODO:
		//char* overlay = 0;
		//if (noText) overlay = "";

		// Draw progress bar
		float _prc;
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4 color;

		// Fill bar color
		color = style->Colors[ImGuiCol_SliderGrabActive]; 
		//color = style->Colors[ImGuiCol_ButtonHovered]; // a bit dark
		// We can force change this color on theme... only used here. Better to fit the theme style.
		
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, color);

		if (max == 1.0f) _prc = valuePrc;
		else _prc = ofMap(valuePrc, 0, max, 0.f, 1.0f);

		if (noText) ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 0));//transparent
		{
			ImGui::ProgressBar(_prc, ImVec2(_w100 - pad, 0));
		}
		if (noText) ImGui::PopStyleColor();

		ImGui::PopStyleColor();
	}

	//--------------------------------------------------------------
	inline void AddProgressBar(ofParameter<float>& valuePrc, float max = -1.0f, bool noText = false)
	{
		// Always starts on 0.0f but max can be 1.0f, 100..
		if (max == -1.0f) ofxImGuiSurfing::AddProgressBar2(valuePrc.get(), valuePrc.getMax(), noText);
		else ofxImGuiSurfing::AddProgressBar2(valuePrc.get(), 1.0f, noText);
	}

	//--------------------------------------------------------------
	inline void AddProgressBar2(const int valuePrc, int max = 100, bool noText = false)
	{
		float _w100 = ImGui::GetContentRegionAvail().x;
		float pad = 0;

		// draw progress bar
		float _prc;
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4 color;

		color = style->Colors[ImGuiCol_ButtonHovered];//we can force change this color on theme... only used here
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, color);

		if (max == 100) _prc = valuePrc / 100.f;
		else _prc = ofMap(valuePrc, 0, max, 0.f, 1.0f);

		if (noText) ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 0));

		ImGui::ProgressBar(_prc, ImVec2(_w100 - pad, 0));

		if (noText) ImGui::PopStyleColor();

		ImGui::PopStyleColor();
	}

	//--------------------------------------------------------------
	inline void AddProgressBar(ofParameter<int>& valuePrc, int max = -1, bool noText = false)
	{
		// Always starts on 0.0f but max can be 1.0f, 100..
		if (max == -1) AddProgressBar2(valuePrc.get(), valuePrc.getMax(), noText);
		else AddProgressBar2(valuePrc.get(), max, noText);
	}

	//--

	//--------------------------------------------------------------
	inline void drawOfTexture(ofTexture* tex, float& _tw, float& _th, float& posX, float& posY, float& drawW, float& drawH) {
#define IMGUI_EX_NODE_HEADER_HEIGHT 20

		if (tex->isAllocated()) {
			if (tex->getWidth() / tex->getHeight() >= _tw / _th) {
				if (tex->getWidth() > tex->getHeight()) {   // horizontal texture
					drawW = _tw;
					drawH = (_tw / tex->getWidth()) * tex->getHeight();
					posX = 0;
					posY = (_th - drawH) / 2.0f;
				}
				else { // vertical texture
					drawW = (tex->getWidth() * _th) / tex->getHeight();
					drawH = _th;
					posX = (_tw - drawW) / 2.0f;
					posY = 0;
				}
			}
			else { // always considered vertical texture
				drawW = (tex->getWidth() * _th) / tex->getHeight();
				drawH = _th;
				posX = (_tw - drawW) / 2.0f;
				posY = 0;
			}

			ImVec2 cursor_pos = ImGui::GetCursorPos();
			ImGui::SetCursorPos(ImVec2(posX, posY + IMGUI_EX_NODE_HEADER_HEIGHT));

			ofxImGui::AddImage(*tex, ofVec2f(drawW, drawH));

			ImGui::SetCursorPos(cursor_pos);

		}
	}

	//--

#include "imgui_plot.h"

// Taken from: 
// https://github.com/d3cod3/ofxVisualProgramming/blob/66e7d578fab47a413e7604efe208bd276ab2927c/src/core/imgui_helpers.h#L134
//--------------------------------------------------------------
	inline void drawWaveform(ImVec2 dim, float* data, int dataSize, float thickness, ImU32 color, float retinaScale = 1.0f) {

		ImDrawList* drawList = ImGui::GetWindowDrawList();
		int IMGUI_EX_NODE_FOOTER_HEIGHT = 20;

		// draw signal background
		drawList->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + dim, IM_COL32_BLACK);

		// draw signal plot
		ImGuiEx::PlotConfig conf;
		conf.values.ys = data;
		conf.values.count = dataSize;
		conf.values.color = color;
		conf.scale.min = -1;
		conf.scale.max = 1;
		conf.tooltip.show = false;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.grid_x.show = false;
		conf.grid_y.show = false;
		conf.frame_size = ImVec2(dim.x - (20 * retinaScale), dim.y - ((IMGUI_EX_NODE_HEADER_HEIGHT + IMGUI_EX_NODE_FOOTER_HEIGHT) * retinaScale));
		conf.line_thickness = thickness;

		ImGuiEx::Plot("plot", conf);
	}

	//--

} // namespace

//----

// Some experimental stuff,
// GL or rare ImGui demos.

// This is a class for 
// Rotating text (and icon demo) for dear imgui
// https://gist.github.com/carasuca/e72aacadcf6cf8139de46f97158f790f#file-imrotatedemo-cpp

//#include "imgui_internal.h"

//#include "IconsMaterialDesign.h"
//// https://github.com/juliettef/IconFontCppHeaders/blob/main/IconsMaterialDesign.h
//// https://github.com/juliettef/IconFontCppHeaders/blob/master/IconsMaterialDesign_c.h

/*

	EXAMPLE
	This is a rotating text demo.

	if (ui.BeginWindow("DEMO", ImGuiWindowFlags_None))
	{
		ImVec2 diff{ 40, 40 };
		//ImVec2 diff{ ImGui::GetWindowWidth() / 2, ImGui::GetWindowHeight() / 2 };
		ofxImGuiSurfing::AddSpacingOffset(diff);

		demo.ImRotateStart();
		ui.AddLabelHugeXXL("HELLO WORLD");
		demo.ImRotateEnd(0.0005f * ::GetTickCount());

		//demo.ImRotateDemo("HelloWorld");

		ui.EndWindow();
	}

*/

class DemoRotatingText
{
public:

	DemoRotatingText() {};
	~DemoRotatingText() {};

	int rotation_start_index;

	//ImVec2 operator-(const ImVec2& l, const ImVec2& r) { return{ l.x - r.x, l.y - r.y }; }

	void ImRotateStart()
	{
		rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size;
	}

	ImVec2 ImRotationCenter()
	{
		ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX); // bounds

		const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
		for (int i = rotation_start_index; i < buf.Size; i++)
			l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

		return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2); // or use _ClipRectStack?
	}

	void ImRotateEnd(float rad)
	{
		ImVec2 center = ImRotationCenter();
		ImRotateEnd(rad, center);
	}

	void ImRotateEnd(float rad, ImVec2 center /*= ImRotationCenter()*/)
	{
		float s = sin(rad), c = cos(rad);
		center = ImRotate(center, s, c) - center;

		auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
		for (int i = rotation_start_index; i < buf.Size; i++)
			buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
	}

	void ImRotateDemo(string text)
	{
		// text
		ImVec2 center;
		ImRotateStart();
		ImGui::Text(text.c_str());
		center = ImRotationCenter();
		ImRotateEnd(0.0005f * ::GetTickCount(), center);

		// icon 
		//ImRotateStart(); ImGui::SameLine();
		//ImGui::Text(ICON_MD_BRIGHTNESS_5);
		//center = ImRotationCenter();
		//ImRotateEnd(0.005f * ::GetTickCount() * !ImGui::IsItemHovered(), center);
	}
};
