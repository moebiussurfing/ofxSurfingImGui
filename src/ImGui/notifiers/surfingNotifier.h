#pragma once
#include "ofMain.h"

#include "imgui_tricks.hpp"

#include "surfingHelpers.h"
//using namespace ofxImGuiSurfing;

class SurfingNotifier
{
public:
	SurfingNotifier()
	{
		//setup();

		//TODO:
		// Fix exit exceptions on RF..
		int minValue = std::numeric_limits<int>::min();
		ofAddListener(ofEvents().exit, this, &SurfingNotifier::exit, minValue);
		
		bGui.makeReferenceTo(ImTricks::NotifyManager::bGui);
	};

	~SurfingNotifier()
	{
		ofRemoveListener(ofEvents().exit, this, &SurfingNotifier::exit);
		//exit();
	};

public:
	void setPath(string path) {
		path_Global = path;
	};

	ofParameter<bool> bGui{ "Debug Notifier", false };

private:
	std::string path_Global = "";
	std::string name_Settings = "SurfingGui_Notifier_Settings.json";

	bool bDoneSetup = false;

public:
	void setup()
	{
		buildTagsDefault();
		ImTricks::NotifyManager::doReset();

		ofxImGuiSurfing::loadGroup(ImTricks::NotifyManager::params, path_Global + name_Settings);

		bDoneSetup = true;
	};

private:
	void exit(ofEventArgs& e)
	{
		exit();
	};
	void exit() 
	{
		//TODO:
		//disable to test RF crash
		//ofxImGuiSurfing::saveGroup(ImTricks::NotifyManager::params, path_Global + name_Settings);
	};

public:
	void draw(bool bDebug_ = false, vector<ImFont*>* fonts = nullptr)
	{
		if (!bDoneSetup) { setup(); }

		ImTricks::NotifyManager::HandleNotifies(ImGui::GetForegroundDrawList(), fonts);

		if (bDebug_) ImTricks::NotifyManager::drawImGuiControls();
	};

	void setIndexFont(int index) {
		index = ofClamp(index, 0, 3);//clamp hardcoded
		ImTricks::NotifyManager::indexFont = index;
	};

	void setDuration(int duration) {
		ImTricks::NotifyManager::duration = duration;
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
		ofLogWarning("ofxSurfingImGui:SurfingNotifier::buildTagsDefault");

		AddTag({ "INFO", ofColor::white });
		AddTag({ "VERBOSE", ofColor::white });
		AddTag({ "NOTICE", ofColor::green });
		AddTag({ "WARNING", ofColor::yellow });
		AddTag({ "ERROR", ofColor::red });
		AddTag({ "FATAL_ERROR", ofColor::red });
	};

public:
	void doReset() { ImTricks::NotifyManager::doReset(); };
	void doClear() { ImTricks::NotifyManager::doClear(); };

	//TODO: allow customize
	void AddTag(tagData tag)
	{
		ofLogWarning("ofxSurfingImGui:SurfingNotifier::AddTag")
			<< "name: " << tag.name << ":" << tag.color;

		tags.push_back(tag);
	};

	void Add(string text, string nameTag)
	{
		NotifyState s;

		ofLogWarning("ofxSurfingImGui:SurfingNotifier::Add") << "tag: " << nameTag;

		if (nameTag == string("INFO")) s = ImTrickNotify_Info;
		else if (nameTag == string("VERBOSE")) s = ImTrickNotify_Verbose;
		else if (nameTag == string("NOTICE")) s = ImTrickNotify_Notice;
		else if (nameTag == string("WARNING")) s = ImTrickNotify_Warning;
		else if (nameTag == string("ERROR")) s = ImTrickNotify_Error;
		else if (nameTag == string("FATAL_ERROR")) s = ImTrickNotify_Error;
		else s = ImTrickNotify_Info;

		ImTricks::NotifyManager::AddNotify(text, s);
	};

	void Add(std::string msg, ofLogLevel logLevel)
	{
		ofLogWarning("ofxSurfingImGui:SurfingNotifier::Add") << "logLevel: " << logLevel;

		if (logLevel == OF_LOG_VERBOSE) Add(msg, "VERBOSE");
		else if (logLevel == OF_LOG_NOTICE) Add(msg, "NOTICE");
		else if (logLevel == OF_LOG_WARNING) Add(msg, "WARNING");
		else if (logLevel == OF_LOG_ERROR || logLevel == OF_LOG_FATAL_ERROR) Add(msg, "ERROR");
		else
		{
			ofLogWarning("ofxSurfingImGui:SurfingNotifier") << "ofLogLevel " << ofToString((short)logLevel) << " Unknown";
			Add(msg, "UNKNOWN");//will post as info
		}
	};

private:



};