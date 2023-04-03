
#pragma once


// OVERVIEW:
/*

	This is the main header for that toolkit/ofxAddon.
	The only one you need to include into your ofApp/Class!

*/

//----

// BUGS:
/*

	Fix int H sliders
	Fix knobs, int knobs etc

	Strings params inside paramGroups are not rendered ?

	It seems than special windows engine
		puts all toggles to false by default ?
		should store state to simply handling that maually/externally

*/

// TODO:
/*

	IDEAS
	- context menu / right mouse click
		expose auto resize/minimize/etc
		add debug info pos,sz for each window.
	- remove use namespace ImGui global or split from ofxImGuiSurfing.. to clarify auto complete.
	- add isFirsTimeStartup() to allow force default settings.

	STYLE
	+ check toggles color theme. correlate with slider grab.
		hover do not change color!
		the fix the knobs colors too.
		push buttons could be darken as if it was a 3D button..
	+ enable floating windows/context.
	+ fix param colors.
	+ fix param string not drawn.
	+ remake theme loader using void * functions.
	+ add tooltip with paragrag/ wrapped.

	API UPDATE v3
	/ ofParams helpers.
	+ pass ImVec2 to all widgets.
	+ make templated for all types.
	+ add multi choice flags.
	+ add a mode to show all tooltips at same time,
		kind of a help mode.
		that requires deep remake of the core.

	HELPERS
	+ fix range slider to a new widget.
		add drag from range center.
	+ useful for multi dim params.
	https://github.com/yumataesu/ofxImGui_v3/blob/master/src/Helper.cpp
	+ fix toggles do not trigs/return true when changes ?
	+ add clickable label toggle widget.
	+ add tool-tip types on styles on a new ui.Add(..arg
	https://github.com/d3cod3/ofxMosaicPlugin/blob/master/src/core/imgui_helpers.h
	+ API v2: fix nested groups with different styles
		+ next / nested groups headers are weird hidden sometimes ?
		+ nested groups are (inheriting) expanded when parent is expanded.

	GENERAL
	+ add disabler for avoid store settings.
	+ fix draw in front the ImGui. not working drawing OF_EVENT_ORDER_AFTER_APP.
		something WIP with bAutoDraw..
	+ fix workflow handling layout presets breaks when Link is enabled.
	+ fix reset aligners that populates out of the view port.
		must apply only over special windows maybe ?

	DOCKING ( WIP )
	+ allow panel and presets dockeable too!
	+ fix make dockeable all windows on same space.
	+ fix multiple dock spaces that are colliding/one over another.
	+ fix view-port rectangle preview.
	+ add video view-port example.
	+ docking overlaps sometimes on layout management.

	SMALL THINGS
	+ remake mode free move and move locked simpler.
		a flag for each window ?
	+ aspect ratio/fit modes for game view port.
	+ fix log ofxImGuiSurfing::WindowsOrganizer::isInitiated:

	NEW FEATURES
	+ auto midi knobs to FX:
		set the master 6 knobs.
		auto assign to these 6 knobs.
		from current GUI editing / first plane page.

	FEATURE
	+ Probably not required.
		But could think about linking multiple instances.
		Or populate as a kind of static to share between instances ?
		for example, to share organizer windows:
		// Link internal stuff
		ui.getGuiToggleOrganizer().makeReferenceTo(myClassObject.ui.getGuiToggleOrganizer());
		Probably a better fix/workaround is to rename each common windows on each gui manager instance
		or the pad between windows setting. we could pass pointers to all instances.

*/

// NOTES:
/*

	Docking Help
	https://github.com/ocornut/imgui/issues/2109

	Docking Demo
	https://github.com/ocornut/imgui/blob/1ad1429c6df657f9694b619d53fa0e65e482f32b/imgui_demo.cpp#L7399-L7408

	Tool-Bar Example
	https://gist.github.com/moebiussurfing/b7652ba1ecbd583b7c4f18e25a598551

*/

//----


//--------------------------------------------------------------

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

//#include "ImHelpers.h"//from ofxImGui

//--------------------------------------------------------------

// This header includes the main classes: 
// Layout, helpers and all my Surfing widgets.
// Some others are moved out of the /src folder 
// bc they are less commonly used.
// You must include them manually from 
// OFX_ADDON/_LIBS if you want to use it in your project.

#include "GuiManager.h"

//--------------------------------------------------------------

// Alias and namespace's

using namespace ofxImGuiSurfing;
using ofxImGuiSurfing::SurfingFontTypes;
//using namespace ofxImGuiSurfing;

// Short alias for the main gui manager class.
// To be used into ofApp.
#define ofxSurfingGui SurfingGuiManager//TODO: works but could be weak..
//using ofxSurfingGui = SurfingGuiManager;//TODO: fails..
//typedef SurfingGuiManager ofxSurfingGui;//breaks all 

//--------------------------------------------------------------

// Done!

// Look documentation into: 
// "ofxSurfingImGui.cpp"