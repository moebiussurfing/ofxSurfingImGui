#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "imgui_tricks.hpp"

class SurfingNotifier
{
public:
	SurfingNotifier() {};
	~SurfingNotifier() {};

	void update()
	{
		ImTricks::NotifyManager::HandleNotifies(ImGui::GetForegroundDrawList());
	};

	struct tagData
	{
		string name;
		ofColor color;
	};

	vector<tagData> tags;
	void AddTag(tagData tag)
	{
		tags.push_back(tag);
	};
	void buildTagsDefault()
	{
		AddTag({ "INFO", ofColor::white });
		AddTag({ "VERBOSE", ofColor::white });
		AddTag({ "NOTICE", ofColor::green });
		AddTag({ "WARNING", ofColor::yellow });
		AddTag({ "ERROR", ofColor::red });
	};

	void doNotify(string text, string nameTag) {
		NotifyState s;

		if (nameTag == string("INFO")) s = ImTrickNotify_Default;
		else if (nameTag == string("VERBOSE")) s = ImTrickNotify_Default;
		else if (nameTag == string("NOTICE")) s = ImTrickNotify_Success;
		else if (nameTag == string("WARNING")) s = ImTrickNotify_Warning;
		else if (nameTag == string("ERROR")) s = ImTrickNotify_Danger;
		else s = ImTrickNotify_Default;

		//ImTricks::NotifyManager::AddNotify("The notification was displayed ", s);
		ImTricks::NotifyManager::AddNotify(text.c_str(), s);
	};

private:



};