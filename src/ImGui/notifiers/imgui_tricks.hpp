#pragma once

//#define SURFING_IMGUI_NOTIFIER_DEFAULT_DURATION 8000

#define USE_IM_GUI_TRICKS_PARAMS 
#define USE_IM_GUI_TRICKS_PRESETS

#define USE_IM_GUI_TRICKS_LAMBDA//TODO: could improve performance making this function non lambda?

//#define USE_IM_GUI_TRICKS_PARAMS 
// -> define in your project (ie: ofApp.h) before including ofxSufringImGui

// Modified version originally 
// taken from https://github.com/ALEHACKsp/imgui-tricks

//TODO:
// Must be added if < C++17
namespace std
{
	template<typename T>
	const T& clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : (value > max ? max : value);
	}
}


/*
* ImGui Tricks v1.02+ (modified by @moebiusSurfing
* ImTricks is a library that simplifies and increases the functionality of ImGui.
* At the moment, ImTricks adds functions to speed up the creation of animated menus,
* adds a notification system, and also adds support for ImColor in ColorEdit3/ColorEdit4.
*
* Made with love by pers0na2.
*/

//#include <windows.h>

// C++
#include <map>
#include <string>
#include <vector>
#include <algorithm>

// OF
#include <ofColor.h>
#include <ofParameter.h>

#ifndef USE_IM_GUI_TRICKS_PARAMS
#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#else
#include "ofHelpers.h" // for OF
#endif

//#define SURFING_IMGUI__USE_NOTIFIER_ANIMS

enum NotifyState : int {
	ImTrickNotify_Info = 0,
	ImTrickNotify_Verbose = 1,
	ImTrickNotify_Notice = 2,
	ImTrickNotify_Warning = 3,
	ImTrickNotify_Error = 4
};

namespace ImTricks {

#ifdef SURFING_IMGUI__USE_NOTIFIER_ANIMS
	/*
	// The Animations namespace contains everything you need to easily create animations in your ImGui menus.
	*/
	namespace Animations {

		/*
		// Usage:
		// int trickInt = ImTricks::Animations::FastLerpInt("trickInt", enable_animation, 0, 255, 15);
		// draw->AddRectFilled(p, p + ImVec2(30, 30), ImColor(255, 255, 255, trickInt));
		*/
		extern int FastLerpInt(const char* identifier, bool state, int min, int max, int speed);

		/*
		// Usage:
		// float trickFloat = ImTricks::Animations::FastLerpInt("trickFloat", enable_animation, 0.f, 1.f, 0.05f);
		// draw->AddRectFilled(p, p + ImVec2(30, 30), ImColor(1.f, 1.f, 1.f, trickFloat));
		*/
		extern float FastLerpFloat(const char* identifier, bool state, float min, float max, float speed);

		/*
		// Usage:
		//	float trickFloat = ImTricks::Animations::FastLerpFloat("header", check, 0.f, 1.f, 0.05f);
		//	draw->AddRectFilled(p, p + ImVec2(513, 30), ImTricks::Animations::FastColorLerp(ImColor(255, 0, 0), ImColor(0, 255, 0), trickFloat));
		*/
		extern ImColor FastColorLerp(ImColor start, ImColor end, float stage);
	}
#endif

	/*
	// The NotifyManager namespace contains everything you need to easily create notifications in your interface.
	*/
	namespace NotifyManager {

		struct NotifyStruct {
			std::string message;
			NotifyState state;
			uint64_t time;
		};

		extern std::vector<NotifyStruct> notifies;

		/*
		// Description:
		// Responsible for adding notifications to the display queue.
		//
		//	if (ImGui::Button("Create Notify", { 120, 25 }))
		//		ImTricks::NotifyManager::AddNotify("The notification was displayed successfully.", ImTrickNotify_Success);
		*/
		extern void AddNotify(std::string message, NotifyState state);

		/*
		// Description:
		// Call a function in your render. This function is responsible for displaying and monitoring notifications.
		//
		// Usage:
		// ImTricks::NotifyManager::HandleNotifies(ImGui::GetForegroundDrawList());
		*/
		extern void HandleNotifies(ImDrawList* draw = ImGui::GetForegroundDrawList(), std::vector<ImFont*> *fonts = nullptr);

		extern void drawImGuiEditorControls();
		extern void doClear();
		extern void doReset();
		extern void doSetMini();

#ifndef USE_IM_GUI_TRICKS_PARAMS
		extern int indexFont;
		extern int duration;
#else
		extern ofParameter<int> indexFont;
		extern ofParameter<int> duration;
		extern ofParameterGroup params;
		extern ofParameter<bool> bGui;
#endif
	}

	/*
	namespace Widgets {
		extern void ColorEdit3(const char* label, ImColor& color, ImGuiColorEditFlags flags = NULL);
		extern void ColorEdit4(const char* label, ImColor& color, ImGuiColorEditFlags flags = NULL);
	}
	*/
}
