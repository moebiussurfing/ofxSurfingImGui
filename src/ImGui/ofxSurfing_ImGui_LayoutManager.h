#pragma once

#include "ofMain.h"

/*

TODO:

+ improve unified namespaces

*/


#include "ofxImGui.h"
#include "ofxSurfing_ImGui_WidgetsButtons.h"
//#include "ofxSurfing_ImGui_WidgetsTypes.h"
//#include "ofxSurfing_ImGui_Themes.h"
//#include "ofxSurfing_ImGui_Helpers.h" //TODO: breaks addvanced/widgets items..

//namespace ofxSurfing = ofxSurfingHelpers;

//using namespace ImGui;
namespace ofxImGuiSurfing
//namespace ofxSurfing
//namespace ofxSurfingHelpers
{
	//--

	// useful layout helpers

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
		__h = BUTTON_BIG_HEIGHT;
	}

	//--

	// example: 
	// allows to make exact width of n widgets to fit panel size for two buttons or columns per row:
	//float w = getImGui_WidgetWidth(2); // half width button
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
	}

	//--------------------------------------------------------------
	inline float getImGui_WidgetWidth(int amntColumns = -1)
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
			//w = __w100 / amntColumns - __spcx / amntColumns;
			w = (__w100 - __spcx * (amntColumns - 1)) / amntColumns;
		}

		return w;
	}
	//--------------------------------------------------------------
	inline float getImGui_WidgetHeight(int amntRows = -1)
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

}//namespace ofxSurfingHelpers

//----

class ofxSurfing_ImGui_Manager
{

	//	//TODO:
	//public:
	//	SurfingWidgetTypes widgetsManager;
		//void refreshShape() {
		//	widgetsManager.refreshPanelShape(); // update sizes to current window shape
		//}

		//--

public:
	ofxSurfing_ImGui_Manager();
	~ofxSurfing_ImGui_Manager();

	//-

	// main API

public:
	void setup();  // MODE A: ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).
	void setup(ofxImGui::Gui & gui); // MODE B: can be instantiated out of the class, locally

	void begin();
	void end();

	void beginWindow(std::string name, bool* p_open, ImGuiWindowFlags window_flags);
	void endWindow();

	//-

public:

	// Force autodraw
	//--------------------------------------------------------------
	void setImGuiAutodraw(bool b) { bAutoDraw = b; }//must be called befor setup!

	// Force shared context
	//--------------------------------------------------------------
	void setSharedMode(bool b) { gui.setSharedMode(b); }

private:
	void setup_ImGui();
	bool bAutoDraw = true;//must be false when multiple ImGui instances created!

	ofxImGui::Gui * guiPtr = NULL;
	ofxImGui::Gui gui;

	ofxImGui::Settings mainSettings = ofxImGui::Settings();// should remove..
	ImFont* customFont = nullptr;

	bool isMouseOverGui() {
		return bLockMouseByImGui;
	}

private:
	bool bUseAdvancedSubPanel = true;//enable advanced sub panel

	//panels minimal sizes
	float xx = 10;
	float yy = 10;
	float ww = PANEL_WIDGETS_WIDTH;
	float hh = 20;
	//float hh = PANEL_WIDGETS_HEIGHT;

	//-

	// exposed useful public params
public:
	ofParameter<bool> bGui{ "Show Gui", true };
	ofParameter<bool> auto_resize{ "Auto Resize", true };//auto resize panel
	ofParameter<bool> bExtra{ "Extra", false};//auto resize panel

private:
	ofParameter<bool> bLockMouseByImGui{ "Mouse OverGui", false };//mouse is over gui
	//ofParameter<bool> auto_lockToBorder{ "Lock GUI", false };//force position

public:

	// an extra common panel with some usefull toggles:
	// auto-resize, debug mouse over gui, ...

	//--------------------------------------------------------------
	void drawAdvancedSubPanel() {

		if (!bUseAdvancedSubPanel) return;

		//--

		ImGui::Dummy(ImVec2(0.0f, 2.0f));

		if (ImGui::CollapsingHeader("ADVANCED"))
		{
			//ofxImGuiSurfing::refreshImGui_WidgetsSizes();//fails

			float _w;
			float _h;

			// this is full width (_w100) with standard height (_h)
			_w = ofxImGuiSurfing::getImGui_WidgetWidth(1);
			_h = ofxImGuiSurfing::getImGui_WidgetHeight(-1);

			ofxImGuiSurfing::AddBigToggle(auto_resize, _w, _h / 2);
			ofxImGuiSurfing::AddBigToggle(bExtra, _w, _h / 2);
			ofxImGuiSurfing::AddBigToggle(bLockMouseByImGui, _w, _h / 2);

			//ImGui::Button("TEST", ImVec2(_w, _h));
			//ofxImGuiSurfing::AddParameter(auto_lockToBorder);
		}
	}

	//--------------------------------------------------------------
	void setUseAdvancedSubPanel(bool b) {
		bUseAdvancedSubPanel = b;
	}
};

//}//namespace ofxSurfingHelpers
