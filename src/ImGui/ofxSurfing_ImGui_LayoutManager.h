#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "ofxSurfing_ImGui_WidgetsButtons.h"

//-------

/* LAYOUT HELPERS */

// useful layout helpers 
// to update sizes/width to panel window shape
namespace ofxImGuiSurfing
{
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
		__h = BUTTON_BIG_HEIGHT;
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

//-------

/* LAYOUT MANGAGER ENGINE */

//--------------------------------------------------------------
class ofxSurfing_ImGui_Manager
{

public:
	ofxSurfing_ImGui_Manager();
	~ofxSurfing_ImGui_Manager();

	//-

	// main API

public:
	void setup(); // MODE A: ofxImGui is instantiated inside the class, the we can forgot of declare ofxImGui here (ofApp scope).
	void setup(ofxImGui::Gui & gui); // MODE B: can be instantiated out of the class, locally

	void begin();
	void end();

	void beginWindow(std::string name = "Window"); // -> simpler
	void beginWindow(std::string name, bool* p_open, ImGuiWindowFlags window_flags);
	void endWindow();

	void draw(); // to manual draw..

	bool addFont(std::string path, int size);

	//-

public:
	// Force autodraw
	//--------------------------------------------------------------
	void setImGuiAutodraw(bool b) { bAutoDraw = b; } // must be called before setup! default is false. For ImGui multi-instance.
	// Force shared context
	//--------------------------------------------------------------
	void setImGuiSharedMode(bool b) { gui.setSharedMode(b); }

private:
	void setup_ImGui();
	bool bAutoDraw; // must be false when multiple ImGui instances created!

	ofxImGui::Gui * guiPtr = NULL;
	ofxImGui::Gui gui;

	ofxImGui::Settings mainSettings = ofxImGui::Settings(); // should remove..
	ImFont* customFont = nullptr;

	//--------------------------------------------------------------
	bool isMouseOverGui() {
		return bMouseOverGui;
	}

private:
	bool bUseAdvancedSubPanel = true; // enable advanced sub panel

	// panels minimal sizes
	float xx = 10;
	float yy = 10;
	float ww = PANEL_WIDGETS_WIDTH_MIN;
	float hh = 20;
	//float hh = PANEL_WIDGETS_HEIGHT_MIN;

	//-

	// exposed useful public params
public:
	ofParameterGroup params_Advanced{ "ADVANCED" };

	ofParameter<bool> bGui{ "Show Gui", true };
	ofParameter<bool> bAutoResize{ "Auto Resize", true }; // auto resize panel
	ofParameter<bool> bExtra{ "Extra", false };
	ofParameter<bool> bAdvanced{ "Advanced", false };
	ofParameter<bool> bDebug{ "Debug", false };
	ofParameter<bool> bMinimize{ "Minimize", false };

private:
	ofParameter<bool> bMouseOverGui{ "Mouse OverGui", false }; // mouse is over gui
	//ofParameter<bool> auto_lockToBorder{ "Lock GUI", false }; // force position

public:

	// an extra common panel with some usefull toggles:
	// auto-resize, debug mouse over gui, ...

	//--------------------------------------------------------------
	void drawAdvancedSubPanel() {

		if (!bAdvanced) return;
		if (!bUseAdvancedSubPanel) return;

		//--

		//ImGui::Dummy(ImVec2(0.0f, 2.0f));
		ImGui::Indent();
		if (ImGui::CollapsingHeader("ADVANCED"))
		{
			ofxImGuiSurfing::AddToggleRoundedButton(bAutoResize);
			ofxImGuiSurfing::AddToggleRoundedButton(bDebug);
			ofxImGuiSurfing::AddToggleRoundedButton(bMouseOverGui);

			//ofxImGuiSurfing::refreshImGui_WidgetsSizes();//fails
			// this is full width (_w100) with standard height (_h)
			//float _w;
			//float _h;
			//_w = ofxImGuiSurfing::getWidgetsWidth(1);
			//_h = ofxImGuiSurfing::getWidgetsHeight(-1);
			//ofxImGuiSurfing::AddBigToggle(bAutoResize, _w, _h / 2);
			//ofxImGuiSurfing::AddBigToggle(bExtra, _w, _h / 2);
			//ofxImGuiSurfing::AddBigToggle(bMouseOverGui, _w, _h / 2);
		}
		ImGui::Unindent();
	}

	//--------------------------------------------------------------
	void setUseAdvancedSubPanel(bool b) {
		bUseAdvancedSubPanel = b;
	}

	//-

	////TODO:
	//public:
	//SurfingTypes widgetsManager;
	//void refreshShape() {
	//widgetsManager.refreshPanelShape(); // update sizes to current window shape
	//}
};
