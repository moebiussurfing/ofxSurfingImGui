#pragma once

//t this header includes all the ImGui classes: layout, helpers and widgets

#include "ofMain.h"

#include "ofxImGui.h"
#include "ImGui/ofxSurfing_ImGui.h"
#include "ImGui/ofxSurfing_ImGui_LayoutManager.h"
#include "ImGui/ofxSurfing_ImGui_Themes.h"
#include "ImGui/ofxSurfing_ImGui_Widgets.h"
#include "ImGui/ofxSurfing_ImGui_RangeSlider.h"
#include "ImGui/dear_widgets/dear_widgets.h"

//using ofxSurfingHelpers = ofxSurfingHelpers::ImGui;

/*

	//---------
	// SNIPPETS
	//---------

	//-

	// 01. get window position for advanced layout paired position

	//.h
	//standalone window not handled by .ini layout
	//but for the app settings
	float widthGuiLayout;
	float heightGuiLayout;
	ofParameter<glm::vec2> positionGuiLayout{ "Gui Layout Position",
	glm::vec2(ofGetWidth() / 2,ofGetHeight() / 2),//center
		glm::vec2(0,0),
		glm::vec2(ofGetWidth(), ofGetHeight())
	};

	//.cpp
	//get window position for advanced layout paired position
	auto posx = ImGui::GetWindowPos().x;
	auto posy = ImGui::GetWindowPos().y;
	widthGuiLayout = ImGui::GetWindowWidth();
	heightGuiLayout = ImGui::GetWindowHeight();
	positionGuiLayout = glm::vec2(posx, posy);

	//-

*/