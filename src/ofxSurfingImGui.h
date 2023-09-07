
/*

	OVERVIEW:

	This is the main header for this ImGui Toolkit/ofxAddon for OF.
	It's the only one that you strictly need to include into your ofApp/Class!


	TODO, BUGS, IDEAS, NOTES, DOCUMENTATION, SNIPPETS, EXAMPLES 
	--> ofxSurfingImGui.cpp

*/


//--------------------------------------------------------------

#pragma once
#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // access to math operators
#include "imgui_internal.h"

#include "ofxImGui.h"

//#include "ImHelpers.h" // from ofxImGui

//--------------------------------------------------------------

// This header includes the main classes: 
// Layout, helpers and all my Surfing widgets.
// Some others are moved out of the /src folder 
// bc they are less commonly used.
// You must include them manually from 
// OFX_ADDON/_LIBS if you want to use it in your project.

#include "SurfingGuiManager.h"

//--------------------------------------------------------------

// Alias and namespace's

using namespace ofxImGuiSurfing;
using ofxImGuiSurfing::SurfingFontTypes;

// Short alias for the main gui manager class.
// To be used into ofApp.
// TODO: it works but could be weak..?
#define ofxSurfingGui SurfingGuiManager

//using ofxSurfingGui = SurfingGuiManager; // TODO: fails..
//typedef SurfingGuiManager ofxSurfingGui; // breaks all 