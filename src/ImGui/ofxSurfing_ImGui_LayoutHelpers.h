#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"

// This class have widgets size constants ands method to get the window panel sizes.

//-------

// CONSTANTS

//#define OFX_IMGUI_ABSOLUTE_HEIGHT // vs relative to theme

#define PANEL_WIDGETS_WIDTH 250 // will be applied as minimal panel shape
#define PANEL_WIDGETS_HEIGHT 100
#define PANEL_WIDGETS_WIDTH_MIN 250 // will be applied as minimal panel shape
#define PANEL_WIDGETS_HEIGHT_MIN 20

//#ifdef OFX_IMGUI_ABSOLUTE_HEIGHT // vs relative to theme
#define BUTTON_BIG_HEIGHT 50
//#endif

#define BUTTON_COLOR_SIZE 40
#define BUTTON_SLIM_HEIGHT2 20
#define SLIDER_HEIGHT 20
#define COLOR_STRIP_COLOR_HEIGHT 15
#define WIDGETS_HEIGHT 50 // will be applied to tbuttons/toggles heights
#define WIDGET_PARAM_PADDING 120 // will be applied to the ofParams sliders. 110 must be the max labels width of params names

#define TEXT_INACTIVE_ALPHA 0.30f // for use on toggle buttons

//-------


/* Layout Helpers */

// useful layout helpers 
// to update / recalculate the sizes/width to fit the panel window shape

namespace ofxImGuiSurfing
{
	//--------------------------------------------------------------
	inline float getWidgetsHeightRelative(int amntRows = -1)
	{
		float h;
		if (amntRows == -1)
		{
			const int proportional = 1;
			//const int proportional = 2;

			if (ImGui::GetIO().FontDefault == nullptr) h = BUTTON_BIG_HEIGHT; // avoid crash when not customized font
			else h = proportional * (ImGui::GetIO().FontDefault->FontSize + ImGui::GetStyle().FramePadding.y * 2); // multiply the them widget height
		}
		else
		{
			float __spcy = ImGui::GetStyle().ItemSpacing.y;
			float __h100 = ImGui::GetContentRegionAvail().y;
			h = __h100 / amntRows - __spcy / amntRows;
		}

		return h;
	}

	// we will update the sizes on any gui drawing point, like inside a new foldered sub-window that could be indendeted and full size is being 
	//--------------------------------------------------------------
	inline void refreshImGui_WidgetsSizes(float& __spcx, float& __spcy, float& __w100, float& __h100, float& __w99, float& __w50, float& __w33, float& __w25, float& __h)
	{
		__spcx = ImGui::GetStyle().ItemSpacing.x;
		__spcy = ImGui::GetStyle().ItemSpacing.y;
		__w100 = ImGui::GetContentRegionAvail().x;
		__h100 = ImGui::GetContentRegionAvail().y;
		__w99 = __w100 - __spcx;
		__w50 = (__w100 - __spcx * 1) / 2;
		__w33 = (__w100 - __spcx * 2) / 3;
		__w25 = (__w100 - __spcx * 3) / 4;
		//__h = BUTTON_BIG_HEIGHT;
		__h = getWidgetsHeightRelative();
	}

	//--------------------------------------------------------------
	// just the more relevant sizes
	inline void refreshImGui_WidgetsSizes(float& __w100, float& __w50, float& __w33, float& __w25, float& __h)
	{
		float __spcx = ImGui::GetStyle().ItemSpacing.x;
		float __spcy = ImGui::GetStyle().ItemSpacing.y;
		__w100 = ImGui::GetContentRegionAvail().x;
		float __h100 = ImGui::GetContentRegionAvail().y;
		__w50 = (__w100 - __spcx * 1) / 2;
		__w33 = (__w100 - __spcx * 2) / 3;
		__w25 = (__w100 - __spcx * 3) / 4;
		//__h = BUTTON_BIG_HEIGHT;
		__h = getWidgetsHeightRelative();
	}

	//--

	// example: 
	// allows to make exact width of n widgets to fit panel size for two buttons or columns per row:
	//float w = getWidgetsWidth(2); // half width button
	//if (ImGui::Button("_Button", ImVec2(w, h))) {}

	//--------------------------------------------------------------
	inline void refreshImGui_WidgetWidth(float &w, int amntColumns = -1)
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
	inline void refreshImGui_WidgetHeight(float &h, int amntRows = -1)
	{
		if (amntRows == -1 || amntRows == 1)
		{
			h = BUTTON_BIG_HEIGHT;
		}
		else
		{
			float __spcy = ImGui::GetStyle().ItemSpacing.y;
			float __h100 = ImGui::GetContentRegionAvail().y;
			h = __h100 / amntRows - __spcy / amntRows;
		}
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
	inline float getWidgetsHeight(int amntRows = -1)
	{
		float h;
		if (amntRows == -1)
		{
			h = BUTTON_BIG_HEIGHT;
		}
		else
		{
			float __spcy = ImGui::GetStyle().ItemSpacing.y;
			float __h100 = ImGui::GetContentRegionAvail().y;
			h = __h100 / amntRows - __spcy / amntRows;
		}

		return h;
	}

} // namespace ofxImGuiSurfing