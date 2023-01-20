
#pragma once

/*

	This class have widgets size constants 
	and methods to get the window panel sizes,
	for layout helping, spacing and separators helpers,
	windows constraints,
	...etc

*/

#include "ofMain.h"

//#include "ofxImGui.h"
#include "imgui.h"
#include "imgui_internal.h"

//---

// Fix weird behaviors when too big or too small resized windows

#define WINDOW_WIDTH_THRESHOLD 250 
// when window width is less than that, 
// we will use another layout pattern for some widgets.

#define PADDING_COMBO 0
//#define PADDING_COMBO 15

//----------

// CONSTANTS

// Will be applied as minimum and standard window shape
#define PANEL_WIDGETS_WIDTH 250
#define PANEL_WIDGETS_HEIGHT 100
#define PANEL_WIDGETS_WIDTH_MIN 200
#define PANEL_WIDGETS_HEIGHT_MIN 100

// Legacy
#define PANEL_WIDTH_MIN PANEL_WIDGETS_WIDTH_MIN 
#define PANEL_HEIGHT_MIN PANEL_WIDGETS_HEIGHT_MIN

//--

// DEPRECATED
// Some absolute sizes are deprecated! now we use sizes relatives to the ImGui theme
#define BUTTON_BIG_HEIGHT 50 
#define BUTTON_COLOR_SIZE 40
#define BUTTON_SLIM_HEIGHT2 20

#define WIDGET_SLIDER_HEIGHT 20
#define WIDGET_COLOR_STRIP_COLOR_HEIGHT 15
#define WIDGETS_HEIGHT 50 // will be applied to buttons/toggles heights

#define WIDGET_LABEL_WIDTH 120

//TODO:
#define WIDGET_PARAM_PADDING 0 // text padding: will be applied to the ofParams sliders. 110 must be the max labels width of params names
//#define WIDGET_PARAM_PADDING 40 // text padding: will be applied to the ofParams sliders. 110 must be the max labels width of params names
//#define WIDGET_PARAM_PADDING 120 // text padding: will be applied to the ofParams sliders. 110 must be the max labels width of params names

#define PADDING_PANELS 2 // space between some widgets or panels
#define PADDING_WIDGETS 2 // space between some widgets or panels

#define TEXT_INACTIVE_ALPHA 0.30f // for use on toggle buttons

//----

// Default Font

// Notice that if not any font file is located, will work as ImGui default,
// So you don't need to put any files on bin/data to compile right!

// Legacy Font
#define FONT_DEFAULT_FILE_LEGACY "telegrama_render.otf"
#define FONT_DEFAULT_SIZE_LEGACY 11

// New font
#define FONT_DEFAULT_SIZE 14
#define FONT_DEFAULT_FILE "JetBrainsMono-Bold.ttf"

// Other Candidates

//#define FONT_DEFAULT_SIZE 14
//#define FONT_DEFAULT_FILE "JetBrainsMono-Medium.ttf"

//#define FONT_DEFAULT_SIZE 13
//#define FONT_DEFAULT_FILE "PrgmtB.ttf"

//#define FONT_DEFAULT_SIZE 13
//#define FONT_DEFAULT_FILE "PrgmtR.ttf"

//#define FONT_DEFAULT_SIZE 14
//#define FONT_DEFAULT_FILE "Ruda-Bold.ttf"

//--

//TODO:
//// To help API memo..
//// Can we do that and avoid to create the class functions on GuiManager?
//#define ui.AddSpacingSmall() ofxImGuiSurfing::AddSpacingSmall() 
//#define ui.AddSpacingDouble() ofxImGuiSurfing::AddSpacingDouble() 
//#define ui.AddSpacing() ofxImGuiSurfing::AddSpacing() 
//#define ui.AddSpacingBig() ofxImGuiSurfing::AddSpacingBig() 
//#define ui.AddSpacingBigSeparated() ofxImGuiSurfing::AddSpacingBigSeparated() 
//#define ui.AddSpacingSeparated() ofxImGuiSurfing::AddSpacingSeparated() 
//#define ui.AddSpacingHuge() ofxImGuiSurfing::AddSpacingHuge() 
//#define ui.AddSpacingHugeSeparated() ofxImGuiSurfing::AddSpacingHugeSeparated() 


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
		//__h = BUTTON_BIG_HEIGHT; // hardcoded
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
		//__h = BUTTON_BIG_HEIGHT;
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
			//h = ofxImGuiSurfing::getWidgetsHeightUnit();
			//h = BUTTON_BIG_HEIGHT;
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

	//--------------------------------------------------------------
	inline float getWindowWidth()
	{
		return getWidgetsWidth();
	}

	//--------------------------------------------------------------
	inline float getWidgetsHeightUnit() // uses font size and frame padding
	{
		return getWidgetsHeightRelative();
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
		return getWidgetsHeight(1);
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
		ImGui::Text(s.c_str());
	}
	//--------------------------------------------------------------
	inline void DebugContentRegionAvailY() {
		float wy = ImGui::GetContentRegionAvail().y;
		string s = ofToString(wy);
		ImGui::SameLine();
		ImGui::Text(s.c_str());
	}
	//--------------------------------------------------------------
	inline void DebugContentRegionAvail() {
		float wx = ImGui::GetContentRegionAvail().x;
		float wy = ImGui::GetContentRegionAvail().y;
		string s = ofToString(wx) + ", " + ofToString(wy);
		ImGui::SameLine();
		ImGui::Text(s.c_str());
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
			ImGui::Text(s.c_str());
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
		ImGui::Separator();
	}
	//--------------------------------------------------------------
	inline void AddSeparated()
	{
		ImGui::Spacing();
		ImGui::Separator();
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
	inline void AddSpacingBig()
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
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();
	}

	//--------------------------------------------------------------
	inline void AddSpacingSeparated()
	{
		ImGui::Spacing();
		ImGui::Separator();
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
	inline void AddSpacingHugeSeparated()
	{
		AddSpacingBig();
		AddSpacingBig();
		AddSpacingSeparated();
		AddSpacingBig();
		AddSpacingBig();
	}

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

	// Default font size 
	// has here we don't have the GuiManger power...
	//--------------------------------------------------------------
	inline void AddLabel(string text)
	{
		ImGui::TextWrapped(text.c_str());
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
	//TODO: Notice that can be called both, they collide.
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

} // namespace ofxImGuiSurfing