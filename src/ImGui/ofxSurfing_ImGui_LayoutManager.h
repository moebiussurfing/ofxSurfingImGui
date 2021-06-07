#pragma once

#include "ofMain.h"

#include "ofxSurfing_ImGui_Themes.h"
#include "ofxSurfing_ImGui_WidgetsButtons.h"
//#include "ofxSurfing_ImGui_Helpers.h" //TODO: breaks addvanced/widgets items..

//using namespace ImGui;
namespace ofxSurfingHelpers
{
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
	inline void getImGui_WidgetWidth(float &w, int amntColumns = -1)
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
	inline void getImGui_WidgetHeight(float &h, int amntRows = -1)
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

}//namespace ofxSurfingHelpers

//----

class ofxSurfing_ImGui_LayoutManager
{

public:
	ofxSurfing_ImGui_LayoutManager();
	~ofxSurfing_ImGui_LayoutManager();

	//-

	// main API

public:
	void setup();
	void setup(ofxImGui::Gui & gui);
	void begin();
	void end();

	void beginWindow(string name, bool* p_open, ImGuiWindowFlags window_flags);
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

	ofxImGui::Settings mainSettings = ofxImGui::Settings();
	ImFont* customFont = nullptr;

public:
	ofParameter<bool> bGui{ "Show Gui", true };
	ofParameter<bool> auto_resize{ "Auto Resize", true };//auto resize panel
	ofParameter<bool> bLockMouseByImGui{ "Mouse Locked", false };//mouse is over gui
	//ofParameter<bool> auto_lockToBorder{ "Lock GUI", false };//force position

	bool isMouseOverGui() {
		return bLockMouseByImGui;
	}

private:
	bool bUseAdvancedSubPanel = false;//enable advanced sub panel

	//panels minimal sizes
	float xx = 10;
	float yy = 10;
	float ww = PANEL_WIDGETS_WIDTH;
	float hh = 20;
	//float hh = PANEL_WIDGETS_HEIGHT;

	//-

public:
	//--------------------------------------------------------------
	void drawAdvancedSubPanel() {
		ImGui::Dummy(ImVec2(0.0f, 2.0f));

		if (ImGui::CollapsingHeader("ADVANCED"))
		{
			//ofxSurfingHelpers::refreshImGui_WidgetsSizes();//fails

			float _w;
			float _h;
			// this is full width (_w100) with standard height (_h)
			ofxSurfingHelpers::getImGui_WidgetWidth(_w, 1);
			ofxSurfingHelpers::getImGui_WidgetHeight(_h, -1);

			ImGui::Button("TEST", ImVec2(_w, _h));

			ofxSurfingHelpers::AddBigToggle(auto_resize, _w, _h / 2);
			ofxSurfingHelpers::AddBigToggle(bLockMouseByImGui, _w, _h / 2);
			//ofxSurfing::AddParameter(auto_resize);
			//ofxSurfing::AddParameter(bLockMouseByImGui);

			//ofxSurfing::AddParameter(auto_lockToBorder);
		}
	}


	/*

	// SNIPPET

	guiManager.begin();
	{
		auto mainSettings = ofxImGui::Settings();
		ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
		string name = "myWindow";

		////widgets sizes
		//float _spcx;
		//float _spcy;
		//float _w100;
		//float _h100;
		//float _w99;
		//float _w50;
		//float _w33;
		//float _w25;
		//float _h;

		if (ofxImGui::BeginWindow(name.c_str(), mainSettings, _flagw))
		{
			ofxSurfingHelpers::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

			//drawParams();

			guiManager.drawAdvancedSubPanel();
		}
		ofxImGui::EndWindow(mainSettings);
	}
	guiManager.end();

	*/

	//--------------------------------------------------------------
	//    void drawRangue();

	//--------------------------------------------------------------
	//void setUseAdvancedSubPanel(bool b) {
	//	bUseAdvancedSubPanel = b;
	//}

	//-

	// TODO:
	// windows helpers...
	// problems bc if(ofxImGui)

	//void beginWindow(string name);
	//void endWindow();
	//void beginWindow(string name){
	//static bool auto_resize = true;

	//ImGuiWindowFlags flagsw = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;

	////flagsw |= ImGuiCond_FirstUseEver;
	////if (auto_lockToBorder) flagsw |= ImGuiCond_Always;
	////else flagsw |= ImGuiCond_FirstUseEver;
	////ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsw);
	////ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsw);

	//ImGui::PushFont(customFont);
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));
	//{
	//	std::string n = "myPanelName";
	//	if (ofxImGui::BeginWindow(n.c_str(), mainSettings, flagsw))
	//	{
	//	}
};

//}//namespace ofxSurfingHelpers
