
#pragma once


/*

	This class has methods to get the window panel sizes,
	for layout helping, spacing and separators helpers,
	windows constraints,
	...etc

*/


#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "SurfingGuiSugar.h"
#include "SurfingGuiConstants.h"

#include "SurfingHelpers.h"
//using namespace ofxSurfingHelpers;

//------------------

// Layout Helpers

// Useful layout helpers.
// For responsive behavior. 
// Gets the ImGui window dimensions.
// To update / recalculate the sizes / width 
// to fit the panel window shape.

namespace ofxImGuiSurfing
{
	//--------------------------------------------------------------
	inline float getWidgetsSpacingX()
	{
		return ImGui::GetStyle().ItemSpacing.x; // x spacing between widgets
	}

	//--------------------------------------------------------------
	inline float getWidgetsSpacingY()
	{
		return ImGui::GetStyle().ItemSpacing.y; // y spacing between widgets
	}

	//--------------------------------------------------------------
	inline float getWidgetsHeightRelative(int amntRows = -1) // height is relative to ImGui theme
	{
		float h;
		if (amntRows == -1)
		{
			h = ImGui::GetFrameHeight();
		}
		else
		{
			float __spcy = ImGui::GetStyle().ItemSpacing.y;
			float __h100 = ImGui::GetContentRegionAvail().y;
			h = __h100 / amntRows - __spcy / amntRows;
		}

		return h;
	}
	//--------------------------------------------------------------
	inline float getTextLineHeightWithSpacing() {
		return ImGui::GetTextLineHeightWithSpacing();
	}

	//--

	// Kind of Legacy
	// Will be DEPRECATED with the new API V2.

	// Updates all the common useful sizes in one line.
	// We will update the sizes on any gui drawing point, 
	// like inside a new folder, sub-folder that could be indented 
	// and full size is being modified. 
	// Then we need to refresh sizes!
	//--------------------------------------------------------------
	inline void refreshImGui_WidgetsSizes(float& __spcx, float& __spcy, float& __w100, float& __h100, float& __w99, float& __w50, float& __w33, float& __w25, float& __h, bool bWithScroll = false)
	{
		__spcx = ImGui::GetStyle().ItemSpacing.x; // x spacing between widgets
		__spcy = ImGui::GetStyle().ItemSpacing.y; // y spacing between widgets

		__w100 = ImGui::GetContentRegionAvail().x; // full window panel width

		//TODO:
		// Not good when multiple levels..
		// All widths a bit smaller to avoid lateral scroll bar
		if (bWithScroll)
		{
			ImGuiStyle* style = &ImGui::GetStyle();
			__w100 -= style->ScrollbarSize + __spcx;
			//__w100 -= 0.8f * style->ScrollbarSize;
			//__w100 -= __spcx;
		}

		__w50 = (__w100 - __spcx * 1) / 2;
		__w33 = (__w100 - __spcx * 2) / 3;
		__w25 = (__w100 - __spcx * 3) / 4;
		__w99 = __w100 - __spcx;
		__h100 = ImGui::GetContentRegionAvail().y; // full window panel height
		__h = getWidgetsHeightRelative(); // relative to theme
	}

	// Another alternative
	// Just the more relevant sizes
	//--------------------------------------------------------------
	inline void refreshImGui_WidgetsSizes(float& __w100, float& __w50, float& __w33, float& __w25, float& __h)
	{
		float __spcx = ImGui::GetStyle().ItemSpacing.x;
		float __spcy = ImGui::GetStyle().ItemSpacing.y;
		__w100 = ImGui::GetContentRegionAvail().x;
		float __h100 = ImGui::GetContentRegionAvail().y;
		__w50 = (__w100 - __spcx * 1) / 2;
		__w33 = (__w100 - __spcx * 2) / 3;
		__w25 = (__w100 - __spcx * 3) / 4;
		__h = getWidgetsHeightRelative();
	}

	//--

	//--------------------------------------------------------------
	inline void refreshImGui_WidgetWidth(float& w, int amntColumns = -1)
	{
		float __spcx = ImGui::GetStyle().ItemSpacing.x;
		float __w100 = ImGui::GetContentRegionAvail().x;
		if (amntColumns == -1)
		{
			w = __w100;
		}
		else
		{
			w = __w100 / amntColumns - __spcx / amntColumns;
		}
	}

	//--------------------------------------------------------------
	inline void refreshImGui_WidgetHeight(float& h, int amntRows = -1)
	{
		if (amntRows == -1 || amntRows == 1)
		{
			h = getWidgetsHeightRelative();
		}
		else
		{
			float __spcy = ImGui::GetStyle().ItemSpacing.y;
			float __h100 = ImGui::GetContentRegionAvail().y;
			h = __h100 / amntRows - __spcy / amntRows;
		}
	}

	// Get all the REAL available space inside the window, 
	// but counting the spacing and padding too!
	// Notice that is NOT the window size / shape itself!
	//--------------------------------------------------------------
	inline float getWindowContentWidth()
	{
		return ImGui::GetContentRegionAvail().x;
	}
	//--------------------------------------------------------------
	inline float getWindowContentHeight()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	// Legacy
	//--------------------------------------------------------------
	inline float getPanelWidth()
	{
		return ImGui::GetContentRegionAvail().x;
	}
	//--------------------------------------------------------------
	inline float getPanelHeight()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	//--

	// Get current window shape
	//--------------------------------------------------------------
	inline ofRectangle getWindowShape()
	{
		return ofRectangle(
			ImGui::GetWindowPos().x,
			ImGui::GetWindowPos().y,
			ImGui::GetWindowWidth(),
			ImGui::GetWindowHeight());
	}

	//--------------------------------------------------------------
	inline float getWidgetsWidth(int amntColumns = -1)
	{
		float w;
		float __spcx = ImGui::GetStyle().ItemSpacing.x;
		float __w100 = ImGui::GetContentRegionAvail().x;
		if (amntColumns == -1 || amntColumns == 1)
		{
			w = __w100;
		}
		else
		{
			w = (__w100 - __spcx * (amntColumns - 1)) / amntColumns;
		}

		return w;
	}

	// LEGACY
	// Note that this is not the shape of the complete window, from the borders!
	// Just the available space after applying inner paddings!
	//--------------------------------------------------------------
	inline float getWindowWidth()
	{
		return ImGui::GetContentRegionAvail().x;
		//return getWidgetsWidth();
	}
	//--------------------------------------------------------------
	inline float getWindowHeight()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	//--------------------------------------------------------------
	inline float getFontSize()
	{
		ImGuiContext& g = *GImGui;
		ImFont* font = g.Font;
		return g.FontSize;
	}

	// NEW API:
	//--------------------------------------------------------------
	inline void SameLineIfAvailForWidth(float w = 200)//TODO; not checking each widget..
	{
		if (ImGui::GetContentRegionAvail().x > w) ImGui::SameLine();
	}
	//--------------------------------------------------------------
	inline float getWindowWidthAvail()
	{
		return ImGui::GetContentRegionAvail().x;
	}
	//--------------------------------------------------------------
	inline float getWindowHeightAvail()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	// Height related to the theme. Uses font size and frame padding!
	//--------------------------------------------------------------
	inline float getWidgetsHeightUnit()
	{
		return ImGui::GetFrameHeight();
		//return getWidgetsHeightRelative();
	}

	//--------------------------------------------------------------
	inline float getWidgetsHeight(int amntRows = -1)
	{
		// Notice that passing 1 will be full window height!
		// that can be trouble when auto resize window is allowed.
		// that's bc we pass the amount of widgets we will want to fit per row!
		// If we want one row of widgets, the widget height 
		// will be the window available free height!

		float h;
		if (amntRows == -1)
		{
			h = getWidgetsHeightUnit();
		}
		else
		{
			float __spcy = ImGui::GetStyle().ItemSpacing.y;
			float __h100 = ImGui::GetContentRegionAvail().y;
			h = __h100 / amntRows - __spcy / amntRows;
			h -= __spcy;
		}

		return h;
	}

	// More Helpers
	// Get ImVec2 size for fast populate buttons
	//--------------------------------------------------------------
	inline ImVec2 getWidgetsShapeDefault()
	{
		ImVec2 vv(getWidgetsWidth(), getWidgetsHeight());

		return vv;
	}

	//--------------------------------------------------------------
	inline ImVec2 getWidgetsShapeBig()
	{
		return getWidgetsShapeDefault();
	}

	//--------------------------------------------------------------
	inline ImVec2 getWidgetsShapeSmall()
	{
		ImVec2 vv(getWidgetsWidth(), getWidgetsHeight() / 2);

		return vv;
	}

	// Available height from current drawlist position
	//--------------------------------------------------------------
	inline float getWindowHeightFree()
	{
		//return getWidgetsHeight(1);
		return ImGui::GetContentRegionAvail().y;
	}
	//--------------------------------------------------------------
	inline float getWindowWidthFree()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	//--

	// Debug Helpers
	// Print the free space we have 
	// for widgets currently on the window.
	//--------------------------------------------------------------
	inline void DebugContentRegionAvailX() { // Put after the widget you want to measure to set the preceded SameLineFit
		float wx = ImGui::GetContentRegionAvail().x;
		string s = ofToString(wx);
		ImGui::SameLine();
		ImGui::Text("%s", s.c_str());
	}
	//--------------------------------------------------------------
	inline void DebugContentRegionAvailY() {
		float wy = ImGui::GetContentRegionAvail().y;
		string s = ofToString(wy);
		ImGui::SameLine();
		ImGui::Text("%s", s.c_str());
	}
	//--------------------------------------------------------------
	inline void DebugContentRegionAvail() {
		float wx = ImGui::GetContentRegionAvail().x;
		float wy = ImGui::GetContentRegionAvail().y;
		string s = ofToString(wx) + ", " + ofToString(wy);
		ImGui::SameLine();
		ImGui::Text("%s", s.c_str());
	}

	//--

	// An alternative to SameLine() 
	// but conditioned if it's finally applied or not.
	// This method can be used to pass widgets 
	// to next line when available space is lower.
	// Then we can make sure that widgets 
	// will fit inside the window when 
	// the window it's resized to a lower size.
	// So, widgets will not been drawn out of the visible part of the window.
	// If available content region is lower than passed minAvailableSpaceToNotBreakLine
	// then we won't call SameLine, and we will break the line.
	// bDebug allows print the available space, 
	// to help tweak the passed minAvailableSpaceToNotBreakLine.
	//TODO: these is a workaround bc must be tweaked by hand. i.e. 
	// each widget has his size, and will change even changing the text...
	//--------------------------------------------------------------
	inline void SameLineFit(float minAvailableSpaceToNotBreakLine = 200, bool bDebug = false)
	{
		float w = minAvailableSpaceToNotBreakLine;
		if (w == -1) ImGui::SameLine();

		float wx = ImGui::GetContentRegionAvail().x;
		if (bDebug)
		{
			string s = ofToString(wx - w);
			ImGui::SameLine();
			ImGui::Text("%s", s.c_str());
		}
		if (wx > w) ImGui::SameLine();
	}

	//----

	// Spacing and Separator Helpers

	//--------------------------------------------------------------
	inline void AddSpacingSmall()
	{
		int spacingy = 1;
		ImGui::Dummy(ImVec2(0.0f, (float)spacingy)); // spacing
	}

	//--------------------------------------------------------------
	inline void AddSpacingDouble()
	{
		ImGui::Spacing();
		ImGui::Spacing();
	}

	//--------------------------------------------------------------
	inline void AddSpacing()
	{
		ImGui::Spacing();
	}

	//--------------------------------------------------------------
	inline void AddSeparator()
	{
		ImGui::Spacing();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
	}
	//--------------------------------------------------------------
	inline void AddSeparated()
	{
		ImGui::Spacing();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
	}

	//--------------------------------------------------------------
	inline void AddSeparatorVertical()
	{
		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
	}
	//--------------------------------------------------------------
	inline void AddSeparatedVertical()
	{
		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
	}

	//--------------------------------------------------------------
	inline void AddSpacingBig()//triple space
	{
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
	}

	//--------------------------------------------------------------
	inline void AddSpacingBigSeparated()
	{
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
		ImGui::Spacing();
		ImGui::Spacing();
	}

	//--------------------------------------------------------------
	inline void AddSpacingSeparated()
	{
		ImGui::Spacing();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
		ImGui::Spacing();
	}

	//--------------------------------------------------------------
	inline void AddSpacingHuge()
	{
		AddSpacingBig();
		AddSpacingBig();
		AddSpacingBig();
		AddSpacingBig();
	}

	//--------------------------------------------------------------
	inline void AddSpacing(size_t amountLines)
	{
		for (size_t i = 0; i < amountLines; i++)
		{
			AddSpacing();
		}
	}

	//--------------------------------------------------------------
	inline void AddSpacingHugeSeparated()
	{
		AddSpacingBig();
		AddSpacingBig();
		AddSpacingSeparated();
		AddSpacingBig();
		AddSpacingBig();
	}

	/*
	//--------------------------------------------------------------
	inline void AddSpaceY(int spacingy = 2)
	{
		ImGui::Dummy(ImVec2(0.0f, (float)spacingy)); // spacing
	}
	//--------------------------------------------------------------
	inline void AddSpaceX(int spacingx = 2)
	{
		ImGui::Dummy(ImVec2((float)spacingx, 0.0f)); // spacing
	}
	*/

	// Default font size 
	// has here we don't have the GuiManger power...
	//--------------------------------------------------------------
	inline void AddLabel(string text)
	{
		ImGui::TextWrapped("%s", text.c_str());
	}

	//---

	// Right Align Helpers

	// Push left from the right border window.
	// Adds x spacing to right align widgets! 
	// i.e. 
	// by passing the expected width of the widget 
	// you are moving the next widget position 
	// to the right window border.
	// Example: 
	// align right minus 21px
	// AddSpacingToRightAlign(21);
	//--------------------------------------------------------------
	inline void AddSpacingToRightAlign(float width = 100)
	{
		float pad = ImGui::GetStyle().WindowPadding.x;
		//float pad = ImGui::GetStyle().ItemSpacing.x;

		float wwidget = ImGui::GetContentRegionAvail().x - pad - width;
		ImGui::Dummy(ImVec2{ wwidget,0 });
		ImGui::SameLine();
	}

	// Displace next widgets from the default spacing.
	// Useful to force position some widgets, 
	// that we don't like the default spacing.
	// Example: 
	// push up 15px:
	// AddSpacingOffset(ImVec2{ 0,-15 });
	//--------------------------------------------------------------
	inline void AddSpacingOffset(ImVec2 diff)
	{
		auto dl = ImGui::GetWindowDrawList();
		auto pf = ImGui::GetCursorPos();
		auto pt = pf + diff;
		ImGui::SetCursorPos(pt);
	}
	//--------------------------------------------------------------
	inline void AddSpacingX(float x)
	{
		AddSpacingOffset(ImVec2{ x, 0 });
	}
	//--------------------------------------------------------------
	inline void AddSpacingY(float y)
	{
		AddSpacingOffset(ImVec2{ 0, y });
	}

	// Adds horizontal spacing to center a widget.
	//--------------------------------------------------------------
	inline void AddSpacingPad(float width = 100)
	{
		ImGui::Dummy(ImVec2{ width, 0 });
		ImGui::SameLine();
	}

	//--------------------------------------------------------------
	inline void AddHeaderHeight()
	{
		float ho = 0;
		ho += 2 * ImGui::GetStyle().WindowBorderSize;
		ho += ImGui::GetWindowHeight() - ImGui::GetContentRegionAvail().y;//header height
		ofxImGuiSurfing::AddSpacingY(ho);
	}

	//--------------------------------------------------------------
	inline void RemoveHeaderHeight()
	{
		float ho = 0;
		ho += 2 * ImGui::GetStyle().WindowBorderSize;
		ho += ImGui::GetWindowHeight() - ImGui::GetContentRegionAvail().y;//header height
		ofxImGuiSurfing::AddSpacingY(-ho);
	}

	// Pass a name to get the expected default button size by considering the text label.
	//--------------------------------------------------------------
	inline float getWidgetButtomToggleWidth(string name, bool bExtraPad = false)
	{
		const char* text = name.c_str();
		ImGuiStyle& style = ImGui::GetStyle();

		float sp1 = style.ItemInnerSpacing.x;
		float sp2 = style.ItemSpacing.x;//not strictly related to theme.

		float space = ImGui::CalcTextSize(text).x;
		space += sp1;
		space += sp1;
		space += sp1;//a custom extra
		if (bExtraPad) space += sp2;

		return space;
	}
	// Pass a bool param to get the expected default button size by considering the text label.
	//--------------------------------------------------------------
	inline float getWidgetButtomToggleWidth(ofParameter<bool>& b, bool bExtraPad = false)
	{
		string name = b.getName();
		return getWidgetButtomToggleWidth(name);
	}

	////--------------------------------------------------------------
	//inline void AddSpacingX(float x = 100)
	//{
	//	AddSpacingPad(x);
	//}

	//--

	// A header with a centered text
	/*
	EXAMPLE

	int w = 250;
	int h = 150;
	ImGui::Spacing();
	ImGui::BeginChild("Options", ImVec2(w, h), true);
	ofxImGuiSurfing::AddHeader("Options");
	ImGui::Spacing();
	ImGui::PushItemWidth((120.0f));
	static int maxTokens = 5;
	ImGui::InputInt("Max Tokens", &maxTokens);
	static float presencePenalty = 5;
	ImGui::InputFloat("Presence Penalty", &presencePenalty);
	static bool echo = false;
	ImGui::Checkbox("Enable Echo", &echo);
	ImGui::EndChild();
	*/
	//--------------------------------------------------------------
	inline void AddHeader(const char* text)
	{
		auto windowWidth = ImGui::GetWindowSize().x;
		ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize(text).x) * 0.5f);
		ImGui::Text(text);
		ImGui::Spacing();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
	}

	//----

	// Constraints Helpers

	/*
	ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0),    ImVec2(-1, FLT_MAX));      // Vertical only
	ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1),    ImVec2(FLT_MAX, -1));      // Horizontal only
	ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
	ImGui::SetNextWindowSizeConstraints(ImVec2(300, 0),   ImVec2(400, FLT_MAX));     // Width 300-400
	ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0),     ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);// Always Square
	ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0),     ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Step, (void*)100);// Fixed Step
	*/

	//--------------------------------------------------------------
	inline void SetWindowContraints(ImVec2 width, ImVec2 height)
	{
		ImGui::SetNextWindowSizeConstraints(ImVec2(width.x, height.x), ImVec2(width.y, height.y));
	}
	//TODO: Notice that can't be called both, they collide.
	//--------------------------------------------------------------
	inline void SetWindowContraintsWidth(float widthMin, float widthMax = -1)
	{
		if (widthMax == -1) widthMin = widthMax;
		ImGui::SetNextWindowSizeConstraints(ImVec2(widthMin, 0), ImVec2(widthMax, FLT_MAX));
	}
	//--------------------------------------------------------------
	inline void SetWindowContraintsHeight(float heightMin, float heightMax = -1)
	{
		if (heightMax == -1) heightMax = heightMin;
		ImGui::SetNextWindowSizeConstraints(ImVec2(0, heightMin), ImVec2(FLT_MAX, heightMax));
	}

	//----

	// Tree folders

	//TODO: 
	// Could improve by doing open state 
	// handled by imgui.ini. 
	// Now is forced!
	// Could make a custom serializer by adding 
	// all the trees to the GuiManager instance!
	//--------------------------------------------------------------
	inline bool BeginTree(string label)
	{
		//ImGuiTreeNodeFlags flagsTree = ImGuiTreeNodeFlags_None;
		ImGuiTreeNodeFlags flagsTree = ImGuiTreeNodeFlags_Framed;

		return (ImGui::TreeNodeEx(label.c_str(), flagsTree));
	}

	//--------------------------------------------------------------
	inline bool BeginTree(string label, bool open /*= true*/, ImGuiTreeNodeFlags flagsTree = ImGuiTreeNodeFlags_Framed)
	{
		if (open) flagsTree += ImGuiTreeNodeFlags_DefaultOpen;

		//TODO:
		//return (ImGui::TreeNodeEx(label.c_str(), flagsTree, ImGuiCond_FirstUseEver));
		return (ImGui::TreeNodeEx(label.c_str(), flagsTree));
	}

	//--------------------------------------------------------------
	inline void EndTree()
	{
		ImGui::TreePop();
	}

	//---

	// Blink Helpers

	// Will blink the contained text 
	// on widgets between begin/end
	//--------------------------------------------------------------
	inline void BeginBlinkFrame(bool bBlink = true)
	{
		if (bBlink)
		{
			// Border when selected
			float a = 0.5f;
			float borderLineWidth = 1.0f;
			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
			ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			float blinkValue = getFadeBlink();
			a = ofClamp(blinkValue, BLINK_MIN, BLINK_MAX);
			borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
		}
	}
	//--------------------------------------------------------------
	inline void EndBlinkFrame(bool bBlink = true)
	{
		if (bBlink)
		{
			ImGui::PopStyleColor();
			ImGui::PopStyleVar(1);
		}
	}

	// Will make darker the contained 
	// text on widgets between begin/end
	// (kind of widget disabled) 
	//--------------------------------------------------------------
	inline void BeginDarkenText(bool bEnable = true)
	{
		if (bEnable)
		{
			float a = FACTOR_DARKEN;

			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 c_ = style->Colors[ImGuiCol_Text];
			ImVec4 c = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			ImGui::PushStyleColor(ImGuiCol_Text, c);
		}
	}
	//--------------------------------------------------------------
	inline void EndDarkenText(bool bEnable = true)
	{
		if (bEnable)
		{
			ImGui::PopStyleColor();
		}
	}

	//--------------------------------------------------------------
	inline void BeginBlinkText(bool bBlink = true, bool bSoft = false)
	{
		if (bBlink)
		{
			float a = 1.f;
			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 c_ = style->Colors[ImGuiCol_Text];
			ImVec4 c = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			float v = 0;
			if (!bSoft) {
				v = getFadeBlink();
				a = ofClamp(v, BLINK_MIN, BLINK_MAX);
			}

			else
			{//soft
				a = getFadeBlink(0.77, 1, 0.2f);
			}
			//{//soft
			//	v = getFadeBlink();
			//	a = ofClamp(v, 0.6, 1);
			//}
			//{//soft
			//	//v = getFadeBlink(1.0, 0.5, 0.15);
			//	v = getFadeBlink(0.f, 0.2f, 0.2);
			//	v = 1 - v;
			//	a = ofClamp(v, 0.85, 1.f);
			//}

			c = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			ImGui::PushStyleColor(ImGuiCol_Text, c);
		}
	}
	//--------------------------------------------------------------
	inline void EndBlinkText(bool bBlink = true)
	{
		if (bBlink)
		{
			ImGui::PopStyleColor();
		}
	}

	//--------------------------------------------------------------
	inline void BeginBlinkTextDisabled(bool bBlink = true)
	{
		if (bBlink)
		{
			float a = 1.f;
			//float a = 0.5f;
			ImGuiStyle* style = &ImGui::GetStyle();
			const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
			ImVec4 c = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			float v = getFadeBlink();
			a = ofClamp(v, BLINK_MIN, BLINK_MAX);
			c = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

			ImGui::PushStyleColor(ImGuiCol_TextDisabled, c);
		}
	}
	//--------------------------------------------------------------
	inline void EndBlinkTextDisabled(bool bBlink = true)
	{
		if (bBlink)
		{
			ImGui::PopStyleColor();
		}
	}

	// Border Highlight without blinking
	//--------------------------------------------------------------
	inline void BeginBorderFrame()
	{
		float a = 1.f;
		float borderLineWidth = 1.0f;
		ImGuiStyle* style = &ImGui::GetStyle();
		const ImVec4 c_ = style->Colors[ImGuiCol_TextDisabled];
		ImVec4 borderLineColor = ImVec4(c_.x, c_.y, c_.z, c_.w * a);

		ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
	}
	//--------------------------------------------------------------
	inline void EndBorderFrame()
	{
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(1);
	}

	// Disable spacing between item 
	//--------------------------------------------------------------
	inline void BeginDisableItemSpacing()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	}
	//--------------------------------------------------------------
	inline void EndDisableItemSpacing()
	{
		ImGui::PopStyleVar();
	}

	// Change text color
	//--------------------------------------------------------------
	inline void PushColorText(ofColor color)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ofFloatColor(color)));
	}
	//--------------------------------------------------------------
	inline void PopColorText()
	{
		ImGui::PopStyleColor();
	}

	//----

	// Make widgets a bit smaller.
	// Normalized Prc related to window width.
	// Useful when sliders make to grow the window automatically.
	//--------------------------------------------------------------
	inline void PushWidth(float prc)
	{
		float w = prc * ImGui::GetContentRegionAvail().x;
		ImGui::PushItemWidth(w);
	}
	//--------------------------------------------------------------
	inline void PopWidth()
	{
		ImGui::PopItemWidth();
	}

	// Set minimum height for widgets and removes inner y spacing too.
	//--------------------------------------------------------------
	inline void PushMinimalHeights()
	{
		// make all smaller heights
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec2 sp1 = style->ItemSpacing;
		ImVec2 sp2 = style->FramePadding;
		sp1 = ImVec2{ sp1.x, 1.f };
		sp2 = ImVec2{ 0, 0 };

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, sp1);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, sp2);
	}
	//--------------------------------------------------------------
	inline void PopMinimalHeights()
	{
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
	}

	//----

	// Debug Widgets Helpers
	// Useful for developing new custom widgets.

	/*
	EXAMPLE
	// draws a point where drawlist / cursors is currently pointing
	IMGUI_SUGAR__TEST_POINT;
	*/

	//--

	// Draws a point on current cursor passing color
#define IMGUI_SUGAR__DEBUG_POINT(argColor) ImGui::GetWindowDrawList()->AddCircleFilled(ImGui::GetCursorScreenPos(), 1, ImGui::GetColorU32(argColor), 25);

// Passing color and point
#define IMGUI_SUGAR__DEBUG_POINT2(argColor, argPoint) ImGui::GetWindowDrawList()->AddCircleFilled(argPoint, 1, ImGui::GetColorU32(argColor), 25);

	//--

	// Draws a point on the ImGui cursor position 
	// for debugging when designing widgets
	// 
	//#define IMGUI_SUGAR__TEST_POINT \
	//	{ \
	//		ImDrawList* draw_list = ImGui::GetWindowDrawList(); \
	//		const ImVec2 pdebug = ImGui::GetCursorScreenPos(); \
	//		draw_list->AddCircleFilled(ImVec2(pdebug.x, pdebug.y), 2, IM_COL32(255, 0, 255, 255)); \
	//	} \
	//
	//#define IMGUI_SUGAR__TEST_POINT \
	//	ImDrawList* draw_list = ImGui::GetWindowDrawList(); \
	//		const ImVec2 pdebug = ImGui::GetCursorScreenPos(); \
	//		draw_list->AddCircleFilled(ImVec2(pdebug.x, pdebug.y), 2, IM_COL32(255, 0, 255, 255)); \

	//----

} // namespace ofxImGuiSurfing
