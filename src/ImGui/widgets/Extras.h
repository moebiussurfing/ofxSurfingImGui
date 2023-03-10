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
#include "imgui_plot.h"

#include "ofHelpers.h" // For AddImage()

#include "Sliders.h"
// to enable sliders for the big vertical floating slider. 
//#include "WidgetsManager.h"//TODO: to enable mouse..

//----

// Some interesting widgets candidates 
// to be added to the add-on.
// Some widgets are already included!

// Cute widgets!
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
	// Useful data 
	// to be passed to some widgets
	struct SliderMarks
	{
		float pad;
		float thick;
		float value;
		ofColor color;
	};

	//----

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
		ImGui::TextDisabled("(?)");
		//ImGui::TextDisabled("?");

		if (ImGui::IsItemHovered()) {
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 15.0f);
			ImGui::TextWrapped(desc);
			//ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
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

	//TODO. add flip
	// 2D Pad for two float vars
	// Taken from
	// https://github.com/d3cod3/ofxVisualProgramming
	// https://github.com/d3cod3/ofxVisualProgramming/blob/66e7d578fab47a413e7604efe208bd276ab2927c/src/core/imgui_controls.cpp#L287
	// Warning. Probably should be normalized.
	//--------------------------------------------------------------
	inline bool AddPad2D(float* _x, float* _y, ImVec2 sz = ImVec2{ -1,-1 }, bool bFlipx = false, bool bFlipy = false)
	{
		// visuals
		enum { LINE_WIDTH = 2 }; // handlers: small lines width
		enum { GRAB_RADIUS = 6 }; // handlers: circle radius

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

		// Prepare canvas

		float dimx;
		float dimy;
		dimx = w;
		dimy = h;

		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		ImGuiStyle& style = GImGui->Style;
		ImGuiWindow* Window = ImGui::GetCurrentWindow();

		ImVec2 Canvas(dimx, dimy);
		ImRect bb(Window->DC.CursorPos, Window->DC.CursorPos + Canvas);
		ImGui::ItemSize(bb);

		float rounding = style.FrameRounding;

		// Bg
		draw_list->
			AddRectFilled(bb.GetTL(), bb.GetBR(), ImGui::GetColorU32(ImGuiCol_FrameBg), rounding);

		// Boxes
		const int amt = 4;

		// Background grid

		if (Canvas.x >= amt)
		{
			//for (int i = 0; i <= Canvas.x; i += static_cast<int>((Canvas.x / amt)))
			// Now we exclude first and last lines bc drawing bg rectangle!

			float wb = static_cast<int>((Canvas.x / amt));
			for (int i = wb; i <= Canvas.x - wb; i += wb)
			{
				draw_list->
					AddLine(
						ImVec2(bb.Min.x + i, bb.Min.y),
						ImVec2(bb.Min.x + i, bb.Max.y - 1),
						IM_COL32(255, 255, 255, 20));
			}
		}

		// Grid

		if (Canvas.y >= amt)
		{
			float hb = static_cast<int>((Canvas.y / amt));
			for (int i = hb; i <= Canvas.y - hb; i += hb)
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
			AddRect(bb.GetTL(), bb.GetBR() + ImVec2{ 1,1 }, ImGui::GetColorU32(ImGuiCol_Border), rounding);

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

				//--

				// Set values to vars!
				*_x = _pos.x;
				*_y = _pos.y;

				////flipped
				//if (bFlipx) *_x = _pos.x;
				//else *_x = (1 - _pos.x);
				//if (bFlipx) *_y = _pos.y;
				//else *_y = (1 - _pos.y);

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

	// 2D Pad for two float parameters
	//--------------------------------------------------------------
	inline bool AddPad2D(ofParameter<float>& x, ofParameter<float>& y, ImVec2 sz = ImVec2{ -1,-1 }, bool bFlipx = false, bool bFlipy = false)
	{
		//ImGui::Spacing();

		string s = "PLOT ";
		//s += x.getName();
		//s += " / ";
		//s += y.getName();
		ImGui::Text(s.c_str());

		float t1 = x.get();
		float t2 = y.get();

		if (ofxImGuiSurfing::AddPad2D(&t1, &t2, ImVec2{ sz.x, sz.y }, bFlipx, bFlipy))
		{
			x.set(t1);
			y.set(t2);

			return true;
		}
		return false;
	}

	//--

	//--------------------------------------------------------------
	inline void AddPlot(ofParameter<float>& parameter, ImVec2 sz/* = ImVec2(-1, -1)*/, vector<SliderMarks>* marks = nullptr, bool bMinimized = false, float scale = 1.f, bool bOverlayAvg = false)
	{
		//TODO: note than param should be normalized.. ?

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

		//--

		ImGui::PushID("##PLOT");

		static float min = parameter.getMin();

		static float max;
		float g = 1.f;
		{
			if (scale == 0.f)
			{
				g = 1.f;//fix 
				//cout << g;
			}
			else
			{
				// re scaled
				const float MAX_SCALE = 4.f;
				g = ofMap(scale, 0.f, 1.f, 1.f, (1.f / (float)(MAX_SCALE * scale)), true);
			}

			max = parameter.getMax() * g;
		}

		static std::string name = parameter.getName();

		if (!bMinimized) ImGui::Text(name.c_str());

		static bool bOn = true;
		if (!bMinimized) {
			ImGui::Checkbox("On", &bOn);
		}
		// maximized force on
		else {
			if (!bOn) bOn = true;
		}

		// Fill an array of contiguous float values to plot
		// Tip: If your float aren't contiguous but part of a structure, 
		// you can pass a pointer to your first float
		// and the sizeof() of your structure in the "stride" parameter.

		static const size_t duration = 60 * 4;//fps * secs

		static float values[duration] = {};

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

		// Label Avg
		//static bool bOverlayAvg = true;
		//static char overlay[32] = "";
		char overlay[32] = "";
		if (bOverlayAvg)
		{
			float average = 0.0f;
			for (int n = 0; n < IM_ARRAYSIZE(values); n++)
				average += values[n];
			average /= (float)IM_ARRAYSIZE(values);
			sprintf(overlay, "AVG %.2f", average);//one decimal
		}

		ImGui::PlotLines("", values, IM_ARRAYSIZE(values), values_offset, overlay, min, max, sz);

		//--

		// Marks

		if (marks != nullptr)
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			ImVec2 cursor = ImGui::GetCursorScreenPos();
			float ypad = ImGui::GetStyle().ItemSpacing.y;

			for (auto& m : *marks)
			{
				//scaled
				float f = m.value * (1.f / g);
				float v = ofMap(f, 0, 1, parameter.getMin(), parameter.getMax(), true);
				float y = cursor.y - ypad - (v * sz.y);
				float x1 = cursor.x - m.pad;
				float x2 = x1 + sz.x + 2 * m.pad;

				if (f < parameter.getMax())//don't draw if it's out of plot
					draw_list->AddLine(ImVec2(x1, y), ImVec2(x2, y), ImGui::GetColorU32(m.color), m.thick);
			}
		}

		ImGui::PopID();
	}
	//--------------------------------------------------------------
	inline void AddPlot(ofParameter<float>& parameter)
	{
		ImVec2 sz = ImVec2(-1, -1);
		vector<SliderMarks>* marks = nullptr;
		AddPlot(parameter, sz, marks);
	}
	//--------------------------------------------------------------
	inline void AddPlot(ofParameter<float>& parameter, vector<SliderMarks>* marks, bool bMinimized = false, float scale = 1.f, bool bOverlayAvg = false)
	{
		ImVec2 sz = ImVec2(-1, -1);
		AddPlot(parameter, sz, marks, bMinimized, scale, bOverlayAvg);
	}
	////--------------------------------------------------------------
	//inline void AddPlot(ofParameter<float>& parameter, ImVec2 sz = ImVec2(-1, -1), vector<SliderMarks>* marks)
	//{
	//	AddPlot(parameter, sz, marks);
	//}

	//----

	// LEGACY
	//--------------------------------------------------------------
	inline void AddVoidWidget()
	{
		// Unit height
		float h = ImGui::GetIO().FontDefault->FontSize + ImGui::GetStyle().FramePadding.y * 2;
		float w = 10;

		//TODO:
		ImGui::InvisibleButton("_inv_", ImVec2(w, h), ImGuiButtonFlags_None);

		//ImGui::InvisibleButton("_inv_", ImVec2(w, h), ImGuiButtonFlags_Disabled);
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

	//TODO: some method could be redundant, should remove.

	//--------------------------------------------------------------
	inline void AddProgressBar(const float vPrc, float max = 1.0f, bool bNoText = true)
	{
		const float _w100 = ImGui::GetContentRegionAvail().x;
		const float pad = 0;

		//TODO:
		//char* overlay = 0;
		//if (bNoText) overlay = "";

		// Draw progress bar
		float _prc;
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4 color;

		// Fill bar color
		color = style->Colors[ImGuiCol_SliderGrabActive];
		//color = style->Colors[ImGuiCol_ButtonHovered]; // a bit dark
		// We can force change this color on theme... only used here. Better to fit the theme style.

		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, color);

		if (max == 1.0f) _prc = vPrc;
		else _prc = ofMap(vPrc, 0, max, 0.f, 1.0f);

		// make text transparent
		if (bNoText) ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 0));
		{
			ImGui::ProgressBar(_prc, ImVec2(_w100 - pad, 0));
		}
		if (bNoText) ImGui::PopStyleColor();

		ImGui::PopStyleColor();
	}

	//--------------------------------------------------------------
	inline void AddProgressBar(ofParameter<float>& pPrc, float max = -1.0f, bool bNoText = false)
	{
		// Always starts on 0.0f but max can be 1.0f, 100..
		if (max == -1.0f) ofxImGuiSurfing::AddProgressBar(pPrc.get(), pPrc.getMax(), bNoText);
		else ofxImGuiSurfing::AddProgressBar(pPrc.get(), 1.0f, bNoText);
	}

	//--------------------------------------------------------------
	inline void AddProgressBar(ofParameter<float>& pPrc, bool bNoText)
	{
		AddProgressBar(pPrc, -1.f, bNoText);
	}

	//--------------------------------------------------------------
	inline void AddProgressBar(const int vPrc, int max = 100, bool bNoText = false)
	{
		float _w100 = ImGui::GetContentRegionAvail().x;
		float pad = 0;

		// draw progress bar
		float _prc;
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4 color;

		color = style->Colors[ImGuiCol_SliderGrabActive];
		//color = style->Colors[ImGuiCol_ButtonHovered];
		//we can force change this color on theme... only used here

		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, color);

		if (max == 100) _prc = vPrc / 100.f;
		else _prc = ofMap(vPrc, 0, max, 0.f, 1.0f);

		if (bNoText) ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 0));

		ImGui::ProgressBar(_prc, ImVec2(_w100 - pad, 0));

		if (bNoText) ImGui::PopStyleColor();

		ImGui::PopStyleColor();
	}

	//--------------------------------------------------------------
	inline void AddProgressBar(ofParameter<int>& pPrc, int max = -1, bool bNoText = false)
	{
		// Always starts on 0.0f but max can be 1.0f, 100..
		if (max == -1) AddProgressBar(pPrc.get(), pPrc.getMax(), bNoText);
		else AddProgressBar(pPrc.get(), max, bNoText);
	}

	//--

	// TODO: could add not normalized min max
	// TODO: should add text label
	// Take from https://github.com/ocornut/imgui/issues/5263

	// TODO: there's a small offset on border that could be fixed by inspiring from:
	// Original code from ProgressBar
	/*
	// size_arg (for each axis) < 0.0f: align to end, 0.0f: auto, > 0.0f: specified size
	void ImGui::ProgressBar(float fraction, const ImVec2& size_arg, const char* overlay)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;

		ImVec2 pos = window->DC.CursorPos;
		ImVec2 size = CalcItemSize(size_arg, CalcItemWidth(), g.FontSize + style.FramePadding.y * 2.0f);
		ImRect bb(pos, pos + size);
		ItemSize(size, style.FramePadding.y);
		if (!ItemAdd(bb, 0))
			return;

		// Render
		fraction = ImSaturate(fraction);
		RenderFrame(bb.Min, bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);
		bb.Expand(ImVec2(-style.FrameBorderSize, -style.FrameBorderSize));
		const ImVec2 fill_br = ImVec2(ImLerp(bb.Min.x, bb.Max.x, fraction), bb.Max.y);
		RenderRectFilledRangeH(window->DrawList, bb, GetColorU32(ImGuiCol_PlotHistogram), 0.0f, fraction, style.FrameRounding);

		// Default displaying the fraction as percentage string, but user can override it
		char overlay_buf[32];
		if (!overlay)
		{
			ImFormatString(overlay_buf, IM_ARRAYSIZE(overlay_buf), "%.0f%%", fraction * 100 + 0.01f);
			overlay = overlay_buf;
		}

		ImVec2 overlay_size = CalcTextSize(overlay, NULL);
		if (overlay_size.x > 0.0f)
			RenderTextClipped(ImVec2(ImClamp(fill_br.x + style.ItemSpacing.x, bb.Min.x, bb.Max.x - overlay_size.x - style.ItemInnerSpacing.x), bb.Min.y), bb.Max, overlay, NULL, &overlay_size, ImVec2(0.0f, 0.5f), &bb);
	}
	*/

	//--------------------------------------------------------------
	inline void AddProgressBarVertical(const char* label, const float value, const ImVec2& sz)
	{
		const float min_value = 0;
		const float max_value = 1;

		auto& style = ImGui::GetStyle();
		auto draw_list = ImGui::GetWindowDrawList();
		auto cursor_pos = ImGui::GetCursorScreenPos();

		float thickness = 1.f;

		float fraction = (value - min_value) / max_value;

		ImVec2 rect_start{ cursor_pos };
		ImVec2 rect_size{ sz.x, sz.y };
		ImVec2 rect_end{ rect_start + rect_size };

		//ImVec2 rect_sizeInner{ sz.x , sz.y };
		ImVec2 rect_sizeInner{ sz.x - 2 * thickness, sz.y - 2 * thickness };

		ImVec2 rect_fill{ rect_sizeInner * ImVec2{ 1, fraction } };
		ImVec2 rect_fill2{ rect_sizeInner * ImVec2{ 1, 1 - fraction } };

		// Bg
		draw_list->AddRectFilled(rect_start, rect_start + rect_size, ImGui::GetColorU32(ImGuiCol_FrameBg), style.FrameRounding);

		ImVec2 r1{ rect_start.x + thickness, rect_start.y + thickness + rect_fill2.y };
		//ImVec2 r1{ rect_start.x, rect_start.y + rect_fill2.y };

		ImVec2 r2{ r1.x + rect_fill.x, r1.y + rect_fill.y };

		ImDrawFlags flags = ImDrawFlags_None;
		//flags += ImDrawFlags_RoundCornersBottom;
		//flags += ImDrawFlags_RoundCornersTop;
		if (value == 1) flags += ImDrawFlags_RoundCornersAll;
		else flags += ImDrawFlags_RoundCornersBottom;
		//if (value == 1) flags += ImDrawFlags_RoundCornersMask_;

		// Fill
		if (value != 0)//workaround 
		{
			draw_list->AddRectFilled(
				r1,
				r2,
				ImGui::GetColorU32(ImGuiCol_SliderGrabActive),
				style.FrameRounding,
				flags
			);
		}

		// Border
		draw_list->AddRect(rect_start, rect_start + rect_size, ImGui::GetColorU32(ImGuiCol_Border), style.FrameRounding);


		//const string value_text = is_h ? format("{:.2f}", value) : format("{:.1f}", value);
		//draw_list->AddText(rect_start + (rect_size - CalcTextSize(value_text.c_str())) / 2, GetColorU32(ImGuiCol_Text), value_text.c_str());
		//if (label) {
		//    draw_list->AddText(
		//        rect_start + ImVec2{ is_h ? rect_size.x + style.ItemInnerSpacing.x : (rect_size.x - label_size.x) / 2, style.FramePadding.y + (is_h ? 0 : rect_size.y) },
		//        GetColorU32(ImGuiCol_Text), label);
		//}

        ImGui::SetCursorScreenPos(rect_end);

	};
	//--------------------------------------------------------------
	inline void AddProgressBarVertical(ofParameter<float>& pPrc, ImVec2& sz)
	{
		ImGui::BeginGroup();

		auto label = pPrc.getName().c_str();
		const float value = pPrc.get();

		AddProgressBarVertical(label, value, sz);

		ImGui::EndGroup();
	};

	//----

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

			// I'm very weirdly unable to bind this...
			//ofxImGuiSurfing::AddImage(*tex, ofVec2f(drawW, drawH));

			ImGui::SetCursorPos(cursor_pos);

		}
	}

	//--

	// Taken from: 
	// https://github.com/d3cod3/ofxVisualProgramming/blob/66e7d578fab47a413e7604efe208bd276ab2927c/src/core/imgui_helpers.h#L134
	// Originally from: https://github.com/soulthreads/imgui-plot
	//--------------------------------------------------------------
	inline void drawWaveform(ImVec2 sz, float* data, int dataSize, float thickness, ImU32 color, float retinaScale = 1.0f) {

		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImGuiStyle& style = GImGui->Style;
		ImGuiWindow* Window = ImGui::GetCurrentWindow();
		ImVec2 Canvas(sz.x, sz.y);
		ImRect bb(Window->DC.CursorPos, Window->DC.CursorPos + Canvas);

		//int IMGUI_EX_NODE_FOOTER_HEIGHT = 20;

		// draw signal background
		//drawList->AddRectFilled(bb.Min, bb.Max, IM_COL32_BLACK);
		//drawList->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + sz, IM_COL32_BLACK);

		// draw signal plot
		ImGuiEx::PlotConfig conf;
		conf.values.ys = data;
		conf.values.count = dataSize;
		conf.values.color = color;

		conf.scale.min = 0;
		conf.scale.max = 1;

		conf.tooltip.show = true;
		conf.tooltip.format = "sample  %.0f \n   rms  %.2f";

		//conf.grid_x.show = true;
		//conf.grid_x.size = 1024;
		//conf.grid_x.subticks = 4;

		//conf.grid_y.show = true;
		//conf.grid_y.size = 0.5f;
		//conf.grid_y.subticks = 1;

		conf.frame_size = sz;

		//conf.scale.type = ImGuiEx::PlotConfig::Scale::Linear;
		//conf.scale.type = ImGuiEx::PlotConfig::Scale::Log10;//crashes

		//conf.selection = true;

		conf.line_thickness = thickness;

		ImGuiEx::Plot("PLOT", conf);
	}

	// Data must be a vector of normalized (0,1) floats 
	// EXAMPLE:
	// int MAX = 1024;//h
	// vector<float> history;
	// history.assign(MAX, 0.0);//setup
	// history.push_back(value);//add value
	// if (history.size() >= MAX) {// refresh
	//		history.erase(history.begin(), history.begin() + 1);
	//}
	// 

	//--------------------------------------------------------------
	inline void AddWaveform(string name, float* data, uint32_t size, bool bWindowed = true, ImVec2 sz = ImVec2(-1, -1), bool bNoHeader = false, vector<SliderMarks>* marks = nullptr)
	{
		bool b = false;
		if (bWindowed)
		{
			// default size
			float ww = 400;
			float r = (9 / 16.f);
			float hh = ww * r;
			ImGui::SetNextWindowSize(ImVec2{ ww, hh }, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSizeConstraints(ImVec2{ 100, 100 * r }, ImVec2{ (float)ofGetWidth(), (float)ofGetHeight() });

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
			if (bNoHeader) flags += ImGuiWindowFlags_NoDecoration;
			b = ImGui::Begin(name.c_str(), NULL, flags);
			if (!b) {
				ImGui::End();
				return;
			}
		}

		float spx = ofxImGuiSurfing::getWidgetsSpacingX();
		float w;
		float h;
		if (sz.x == -1) {
			w = ofxImGuiSurfing::getWindowWidthAvail() /*+ spx*/;//fix
		}
		else w = sz.x;
		if (sz.y == -1) {
			if (!bWindowed) h = ofxImGuiSurfing::getWidgetsHeightUnit() * 4;
			else h = ofxImGuiSurfing::getWindowHeightAvail();
		}
		else h = sz.y;
		sz = ImVec2(w, h);

		if ((bWindowed && b) || !bWindowed)
		{
			// fix workaround 
			// wrong padding layout..
			ofxImGuiSurfing::AddSpacingOffset(ImVec2{ 1.5f * spx, 0 });

			//ImVec2 cursor = ImGui::GetCursorPos();

			ofxImGuiSurfing::drawWaveform(
				sz,
				&data[0],
				size,
				1.f,
				ImGui::GetColorU32(ImGuiCol_PlotLines));

			//--

			// Marks

			if (marks != nullptr)
			{
				//float xpad = ImGui::GetStyle().ItemSpacing.x;
				float ypad = ImGui::GetStyle().ItemSpacing.y;
				ImDrawList* draw_list = ImGui::GetWindowDrawList();
				ImVec2 cursor = ImGui::GetCursorScreenPos();

				for (auto& m : *marks)
				{
					float v = m.value;
					float y = cursor.y - ypad - (v * sz.y);
					float x1 = cursor.x - m.pad;
					float x2 = x1 + sz.x + 2 * m.pad;

					draw_list->AddLine(ImVec2(x1, y), ImVec2(x2, y), ImGui::GetColorU32(m.color), m.thick);
				}
			}
		}

		if (bWindowed && b)
		{
			ImGui::End();
		}
	};

	////--------------------------------------------------------------
	//inline void AddWaveform(string name, float* data, uint32_t size, vector<SliderMarks>* marks = nullptr)
	//{
	//	AddWaveform(name, data, size, true, ImVec2(-1, -1), false, marks);
	//};

	//--

	// EXAMPLE:
	// 
	// .h
	// static constexpr size_t nBandsToGet = 128;
	// std::array<float, nBandsToGet> fftSmoothed{ {0} };
	// std::vector<float> data;
	// 
	// .cpp
	// ofxImGuiSurfing::AddFFT(bGui_FFT.getName(), &data, 1.f);
	// 
	// audioIn(ofSoundBuffer& input)
	// float* val = ofSoundGetSpectrum(nBandsToGet);
	// for (int i = 0; i < nBandsToGet; i++) {
	//		fftSmoothed[i] *= 0.96f;
	//		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = ofClamp(val[i], 0, 1);
	// }
	// data.clear();
	// for (size_t i = 0; i < nBandsToGet; i++)
	// {
	//		data.push_back(fftSmoothed[i]);
	// }
	// TODO: add method to pass arrays too float* data?
	//--------------------------------------------------------------
	inline void AddFFT(string name, std::vector<float>* data, float max, bool bWindowed = true, ImVec2 sz = ImVec2(-1, -1), bool bNoHeader = false, float start = 0.f, float end = 1.f)
	{
		bool bFill = true;

		bool b = false;
		if (bWindowed)
		{
			float ww = 300;
			float r = (9 / 16.f);
			float hh = ww * r;
			ImGui::SetNextWindowSize(ImVec2{ ww, hh }, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSizeConstraints(ImVec2{ 10, 10 }, ImVec2{ (float)ofGetWidth(), (float)ofGetHeight() });

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
			if (bNoHeader) flags += ImGuiWindowFlags_NoDecoration;
			b = ImGui::Begin(name.c_str(), NULL, flags);
			if (!b) {
				ImGui::End();
				return;
			}
		}

		float w;
		float h;
		if (sz.x == -1) {//full width 
			float spx = ImGui::GetStyle().ItemSpacing.x;
			w = ofxImGuiSurfing::getWindowWidth();
		}
		else w = sz.x;
		if (sz.y == -1) {//4 units height
			float spy = ImGui::GetStyle().ItemSpacing.y;
			h = ofxImGuiSurfing::getWindowHeightAvail();
			//h = ofxImGuiSurfing::getWidgetsHeightUnit();
		}
		else h = sz.y;
		sz = ImVec2(w, h);


		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImGuiStyle& style = GImGui->Style;
		ImGuiWindow* Window = ImGui::GetCurrentWindow();

		ImVec2 Canvas(sz.x, sz.y);
		ImRect bb(Window->DC.CursorPos, Window->DC.CursorPos + Canvas);


		if ((bWindowed && b) || !bWindowed)
		{

			// Bg
			float rounding = style.FrameRounding;
			drawList->AddRectFilled(bb.GetTL(), bb.GetBR(), ImGui::GetColorU32(ImGuiCol_FrameBg), rounding);

			// Plot

			//auto c = ImGui::GetColorU32(ImGuiCol_PlotLines);
			// alpha 
			ImVec4 _c = style.Colors[ImGuiCol_PlotLines];
			float a = 0.5f;
			auto c = ImGui::GetColorU32(ImVec4(_c.x, _c.y, _c.z, a * _c.w));

			ImGuiEx::PlotBands(drawList, w, h, data, max, c, start, end, bFill);

			// Border
			drawList->AddRect(bb.GetTL(), bb.GetBR(), ImGui::GetColorU32(ImGuiCol_Border), rounding);
		}

		if (bWindowed && b)
		{
			ImGui::End();
		}
	}

	//--

	// Value must be normalized (0,1)
	//--------------------------------------------------------------
	inline void AddVU(string name, float value, bool bHorizontal = false, bool bWindowed = true, ImVec2 sz = ImVec2(-1, -1), bool bNoHeader = false, float padding = 1.f, int divisions = 20)
	{
		// last frame window shape
		static float w_;
		static float h_;

		static bool bMustRefresh = false;

		//--

		bool b = false;//opened
		if (bWindowed)
		{
			//TODO
			bool bFlipped = false;
			static bool bHorizontal_ = bHorizontal;
			if (bHorizontal_ != bHorizontal || bMustRefresh)
			{
				bHorizontal_ = bHorizontal;
				bMustRefresh = false;

				ImGui::SetNextWindowSize(ImVec2{ w_, h_ }, ImGuiCond_Always);
				bFlipped = true;
			}

			if (!bFlipped)
			{
				// default
				float ww = 60;
				float hh = ww * 10;
				ImGui::SetNextWindowSize(ImVec2{ ww, hh }, ImGuiCond_FirstUseEver);
			}

			ImGui::SetNextWindowSizeConstraints(
				ImVec2{ 1, 1 },
				ImVec2{ (float)ofGetWidth(), (float)ofGetHeight() });

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
			if (bNoHeader) flags += ImGuiWindowFlags_NoDecoration;

			b = ImGui::Begin(name.c_str(), NULL, flags);
			if (!b) {
				ImGui::End();
				return;
			}
		}

		float w;
		float h;
		//if (!bFlipped)
		{
			if (sz.x == -1) {
				w = ofxImGuiSurfing::getWindowWidthAvail();
			}
			else w = sz.x;
			if (sz.y == -1) {
				if (!bWindowed) h = ofxImGuiSurfing::getWidgetsHeightUnit() * 4;
				else h = ofxImGuiSurfing::getWindowHeightAvail();
			}
			else h = sz.y;
			sz = ImVec2(w, h);
		}

		if ((bWindowed && b) || !bWindowed)
		{
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			ImGuiEx::VUMeter(drawList, w, h, value, bHorizontal, padding, divisions);
		}

		// memorizes window shape on last frame!
		w_ = ImGui::GetWindowWidth();
		h_ = ImGui::GetWindowHeight();

		// flip window
		// maintain correct ratio
		if (bHorizontal)
		{
			if (h_ > w_)
			{
				//bHorizontal = false;

				float tmp = h_;
				h_ = w_;
				w_ = tmp;
				bMustRefresh = true;
			}
		}
		else
		{
			if (h_ < w_)
			{
				//bHorizontal = true;

				float tmp = h_;
				h_ = w_;
				w_ = tmp;
				bMustRefresh = true;
			}
		}

		if (bWindowed && b)
		{
			ImGui::End();
		}
	}

	//--

	// A big slider windowed but transparent.
	// values are to add level lines like thresholds.
	// 
	// EXAMPLE1
	// ofxImGuiSurfing::AddSliderBigVerticalFloating(control);
	// 
	// EXAMPLE2
	// Optionally we can color the grab slider and to pass some colored markers too:
	//ofColor colorGrab = ofColor::pink;
	//vector<SliderMarks> marks;
	//SliderMarks m1;
	//m1.color = ofColor::yellow;
	//m1.value = deviceIn_vuValue;
	//marks.push_back(m1);
	//SliderMarks m2;
	//m2.color = ofColor::orange;
	//m2.value = ofMap(glm::cos(ofGetElapsedTimef()), -1, 1, 0, 1, true);
	//marks.push_back(m2);
	//ofxImGuiSurfing::AddSliderBigVerticalFloating(threshold, ImVec2(-1, -1), true, &colorGrab, &marks);


	//--------------------------------------------------------------
	inline void AddSliderBigVerticalFloating(ofParameter<float>& p, ImVec2 sz = ImVec2(-1, -1), bool bNoTitle = true, ofColor* colorGrab = nullptr, vector<SliderMarks>* marks = nullptr)
	{
		ImGui::BeginGroup();

		static bool bDone = false;
		if (!bDone)
		{
			bDone = true;

			ImGuiCond flagsCond = ImGuiCond_None;
			flagsCond |= ImGuiCond_FirstUseEver;
			flagsCond = ImGuiCond_FirstUseEver;

			// window shapes
			static float ww;
			static float hh;
			static float xx;
			static float yy;

			int padx = 10;
			int pady = 10;
			int pady2 = 50;

			if (sz.x == -1) {
				//full width 
				//float spx = ImGui::GetStyle().ItemSpacing.x;
				//ww = ofxImGuiSurfing::getWindowWidthAvail() ;

				ww = 150;
				xx = ofGetWidth() - ww - padx;
			}
			else ww = sz.x;
			if (sz.y == -1) {
				//full height
				//float spy = ImGui::GetStyle().ItemSpacing.y;
				//hh = ofxImGuiSurfing::getWindowHeightAvail();

				yy = pady;
				hh = ofGetHeight() - yy - pady;
			}
			else hh = sz.y;

			//--

			ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
			ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
		}

		//--

		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(40, 200));
		{
			// transparent window Bg
			// without scroll bar
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			window_flags |= ImGuiWindowFlags_NoBackground;
			window_flags |= ImGuiWindowFlags_NoScrollbar;

			if (bNoTitle) window_flags |= ImGuiWindowFlags_NoTitleBar;

			bool b = ImGui::Begin(p.getName().c_str(), NULL, window_flags);
			if (!b) {
				ImGui::End();
				return;
			}

			if (b)
			{
				float x1, x2, gap, yy, ww, hh;
				float linew;
				ImDrawList* draw_list = ImGui::GetWindowDrawList();
				ImVec2 cursor = ImGui::GetCursorScreenPos();
				float w0 = ofxImGuiSurfing::getWindowWidthAvail();
				hh = ofxImGuiSurfing::getWindowHeightAvail();

				//--

				// Line dividers
				bool bDrawDividers = false;
				if (bDrawDividers)
				{
					// center only
					const int div = 2;
					// 4 lines / quarters
					//const int div = 4;

					const float linea = 0.4f;

					auto c = ImGui::GetStyle().Colors[ImGuiCol_Border];
					//auto c = ImVec4(0, 0, 0, 1.f);//black
					//auto c = ImGui::GetStyle().Colors[ImGuiCol_SeparatorActive];

					ImVec4 cm;
					//ImVec4 cm = ImVec4(c.x, c.y, c.z, c.w * linea);

					// markers zones
					for (size_t i = 0; i < div - 1; i++)
					{
						// more stronger for the center line 
						if (!(i % 2 == 0) && (i == div / 2 - 1))
						{
							cm = ImVec4(c.x, c.y, c.z, c.w * MIN(1, linea * 1.0f));
							linew = 2.f;

							gap = w0 * 0.07f; // x padding to borders
							ww = w0 - 2 * gap;
							x1 = cursor.x + gap;
							x2 = x1 + ww;
						}
						else // other lines
						{
							cm = ImVec4(c.x, c.y, c.z, c.w * linea);
							linew = 1.f;

							gap = w0 * 0.1f; // x padding to borders
							ww = w0 - 2 * gap;
							x1 = cursor.x + gap;
							x2 = x1 + ww;
						}

						yy = cursor.y + (i + 1) * (1 / (float)div) * hh;

						draw_list->AddLine(ImVec2(x1, yy), ImVec2(x2, yy), ImGui::GetColorU32(cm), linew);
					}
				}

				//--

				// Marks

				if (marks != nullptr)
				{
					ww = ofxImGuiSurfing::getWindowWidthAvail();

					for (auto& m : *marks)
					{
						x1 = cursor.x - m.pad;
						x2 = x1 + ww + 2 * m.pad;

						ofColor c = m.color;
						float v = m.value;

						float y = cursor.y + (1.f - v) * hh;

						linew = m.thick;
						draw_list->AddLine(ImVec2(x1, y), ImVec2(x2, y), ImGui::GetColorU32(c), linew);
					}
				}

				//--

				// V Slider

				// change grab slider
				if (colorGrab != nullptr) {
					ImVec4 cg = ImVec4(*colorGrab);
					auto c1 = ImGui::GetColorU32(cg);
					auto c2 = ImGui::GetColorU32(ImVec4(cg.x, cg.y, cg.z, 0.5f * cg.w));
					ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, c1);
					ImGui::PushStyleColor(ImGuiCol_SliderGrab, c2);
				}

				// change Bg
				auto c0 = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
				ImVec4 _cBg = ImVec4(c0.x, c0.y, c0.z, c0.w * 0.2);
				ImGui::PushStyleColor(ImGuiCol_FrameBg, _cBg);
				ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _cBg);
				ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _cBg);
				{
					ImVec2 sz = ImVec2(-1.f, -1.f);
					bool bNoName = true;
					bool bNoNumber = true;

					ofxImGuiSurfing::AddVSlider(p, sz, bNoName, bNoNumber);
				}
				ImGui::PopStyleColor(3);

				// change grab slider
				if (colorGrab != nullptr)
				{
					ImGui::PopStyleColor(2);
				}

				//// tooltip
				//string s = p.getName() + " " + ofToString(p.get(), 2);
				////ofxImGuiSurfing::AddTooltip(s);
				//if (ImGui::IsItemHovered())
				//{
				//	ImGui::BeginTooltip();
				//	//ImGui::PushTextWrapPos(ImGui::GetFontSize() * 100.0f);
				//	ImGui::TextWrapped(s.c_str());
				//	//ImGui::PopTextWrapPos();
				//	ImGui::EndTooltip();
				//}

				// end window
				if (b)
				{
					ImGui::End();
				}
			}
		}
		ImGui::PopStyleVar();

		//string s
		//ofxImGuiSurfing::AddTooltip(s);

		//--

		//TODO: add mouse

		//bool b = true;
		//ofxImGuiSurfing::AddMouseWheel(b);
		//IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
		//bool bReturn = GetMouseWheel();
		//ofxImGuiSurfing::AddMouseWheel(p);
		//ofxImGuiSurfing::AddMouseWheel(p, false);
		//ofxImGuiSurfing::AddMouseClickRightReset(p);

		//bool bReturn = false;
		//bool bMouseWheel = true;
		//IMGUI_SUGAR__WIDGETS_POP_WIDTH;
		//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
		//if (bMouseWheel) bReturn |= GetMouseWheel();
		//if (bMouseWheel) bReturn |= AddMouseClickRightReset(p);

		//--

		ImGui::EndGroup();
	}

} // namespace


//----


// Some experimental stuff,
// GL or rare ImGui demos.

//--

// This is a class for 
// Rotating a text (and icon demo)
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

	int rotation_start_index = -1;

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
		//ImRotateEnd(0.0005f * ImGui::GetTickCount(), center);
        ImRotateEnd(0.0005f * ofGetLastFrameTime(), center);

		// icon 
		//ImRotateStart(); ImGui::SameLine();
		//ImGui::Text(ICON_MD_BRIGHTNESS_5);
		//center = ImRotationCenter();
		//ImRotateEnd(0.005f * ::GetTickCount() * !ImGui::IsItemHovered(), center);
	}
};

//namespace ofxImGuiSurfing
//{
//	// Helper function to apply blur effect on an ImGui window
//	void ApplyBlur(ImGuiWindow window) {
//		ImGuiContext& g = GImGui;
//		ImVec2 pad_pos = window->DC.CursorPos;
//		ImVec2 pad_size = window->Size;
//		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
//		ImGui::BeginChild("##blur", pad_size, true, 0);
//		ImGui::PopStyleVar();
//		ImGui::GetWindowDrawList()->AddRectFilled(pad_pos, ImVec2(pad_pos.x + pad_size.x, pad_pos.y + pad_size.y), ImColor(0, 0, 0, 128));
//		ImGui::EndChild();
//	}
//
//	// Usage example
//	void Example() {
//		ImGui::Begin("Blurred window");
//		ImGui::Text("This window has a blur effect applied to it.");
//		ApplyBlur(ImGui::GetCurrentWindow());
//		ImGui::End();
//	}
//
//}
