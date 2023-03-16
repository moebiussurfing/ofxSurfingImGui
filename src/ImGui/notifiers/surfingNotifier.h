#pragma once
#include "ofMain.h"

#include "imgui_tricks.hpp"

class SurfingNotifier
{
public:
	SurfingNotifier() {
		buildTagsDefault();
	};

	~SurfingNotifier() {
	};

	void draw()
	{
		ImTricks::NotifyManager::HandleNotifies(ImGui::GetForegroundDrawList());
	};

private:

	struct tagData
	{
		string name;
		ofColor color;
	};

	vector<tagData> tags;
	void buildTagsDefault()
	{
		AddTag({ "INFO", ofColor::white });
		AddTag({ "VERBOSE", ofColor::white });
		AddTag({ "NOTICE", ofColor::green });
		AddTag({ "WARNING", ofColor::yellow });
		AddTag({ "ERROR", ofColor::red });
	};

public:
	void AddTag(tagData tag)
	{
		tags.push_back(tag);
	};

	void Add(string text, string nameTag) {
		NotifyState s;

		ofLogWarning("ofxSurfingImGui:SurfingNotifier") << "tag: " << nameTag;

		if (nameTag == string("INFO")) s = ImTrickNotify_Default;
		else if (nameTag == string("VERBOSE")) s = ImTrickNotify_Default;
		else if (nameTag == string("NOTICE")) s = ImTrickNotify_Success;
		else if (nameTag == string("WARNING")) s = ImTrickNotify_Warning;
		else if (nameTag == string("ERROR")) s = ImTrickNotify_Danger;
		else s = ImTrickNotify_Default;

		const char* message = text.c_str();
		//cout << __FUNCTION__ << ":" << message << endl;

		ImTricks::NotifyManager::AddNotify(message, s);
		//ImTricks::NotifyManager::AddNotify("The notification was displayed ", s);
		//ImTricks::NotifyManager::AddNotify(text.c_str(), s);
	};

	void Add(std::string msg, ofLogLevel logLevel)
	{
		if (logLevel == OF_LOG_VERBOSE) Add(msg, "VERBOSE");
		else if (logLevel == OF_LOG_NOTICE) Add(msg, "NOTICE");
		else if (logLevel == OF_LOG_WARNING) Add(msg, "WARNING");
		else if (logLevel == OF_LOG_ERROR || logLevel == OF_LOG_FATAL_ERROR) Add(msg, "ERROR");
		else
		{
			ofLogWarning("ofxSurfingImGui:SurfingNotifier") << "ofLogLevel " << ofToString((short)logLevel) << " Unknown";
		}
	};

private:



};