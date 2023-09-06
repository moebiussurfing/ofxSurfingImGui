#pragma once
#include "ofMain.h"

#include "SurfingGuiConstants.h"

#include "imgui_tricks.hpp"

#include "SurfingHelpers.h"
//using namespace ofxImGuiSurfing;

//--

class SurfingNotifier
{
public:
	SurfingNotifier()
	{
#ifdef SURFING_IMGUI__NOTIFIER_SETTINGS_STANDALONE
#ifdef SURFING_IMGUI__CREATE_EXIT_LISTENER
		//TODO:
		// Fix exit exceptions on RF..
		int minValue = std::numeric_limits<int>::min();
		ofAddListener(ofEvents().exit, this, &SurfingNotifier::exit, minValue);
#endif
#endif
		ImTricks::NotifyManager::bGui.makeReferenceTo(bGui_Editor);

		//TODO:
		params = ImTricks::NotifyManager::params;
	}

	~SurfingNotifier()
	{
#ifdef SURFING_IMGUI__CREATE_EXIT_LISTENER
		ofRemoveListener(ofEvents().exit, this, &SurfingNotifier::exit);
#endif
	}

#ifdef SURFING_IMGUI__NOTIFIER_SETTINGS_STANDALONE
private:
	std::string path_Global = "";
	std::string name_Settings = "SurfingGui_Notifier_Settings.json";

public:
	void setPath(string path) {
		path_Global = path;
	}
#endif

public:
	ofParameter<bool> bGui_Editor{ "Notifier Editor", false };
	ofParameterGroup params;

public:
	void setup()
	{
		buildTagsDefault();
		ImTricks::NotifyManager::doReset();

#ifdef SURFING_IMGUI__NOTIFIER_SETTINGS_STANDALONE
		ofxImGuiSurfing::loadGroup(ImTricks::NotifyManager::params, path_Global + name_Settings);
#endif

		bDoneSetup = true;
	}

private:
	bool bDoneSetup = false;

#ifdef SURFING_IMGUI__NOTIFIER_SETTINGS_STANDALONE
private:
#ifdef SURFING_IMGUI__CREATE_EXIT_LISTENER
	void exit(ofEventArgs& e)
	{
		exit();
	}
#endif

public:
	void exit()
	{
		//TODO:
		//disable to test RF crash
		//ofxImGuiSurfing::saveGroup(ImTricks::NotifyManager::params, path_Global + name_Settings);
	}
#endif

public:
	void draw()
	{
		draw(true, &customFonts);
	}
	void draw(bool bGuiEditor, vector<ImFont*>* fonts = nullptr)
	{
		if (!bDoneSetup) { setup(); }

		ImTricks::NotifyManager::HandleNotifies(ImGui::GetForegroundDrawList(), fonts);

		if (bGuiEditor) ImTricks::NotifyManager::drawImGuiEditorControls();
	}

	void setDuration(int duration) {//bubble duration in milliseconds
		ImTricks::NotifyManager::duration = duration;
	}

	void setMini() {
		ImTricks::NotifyManager::doSetMini();
	}
	void setFontMonospacedDefined(bool b = true)
	{
		bDefinedMonospacedFonts = b;

		ImTricks::NotifyManager::indexFont.setMax(customFonts.size() - 1);

		//workflow. pick the mono-spaced
		// if (fontIndex < 4) fontIndex += 4;//set relative mono-spaced by default
	}

	//--

public:

	void setFontIndex(int index) {
		index = ofClamp(index, 0, customFonts.size() - 1);//clamp hardcoded
		ImTricks::NotifyManager::indexFont = index;
	}

	void setCustomFonts(vector<ImFont*> f, vector<string> names)
	{
		setCustomFontsNames(names);
		setCustomFonts(f);
	}
	void setCustomFontsNames(vector<string> names)
	{
		namesCustomFonts = names;
	}
	void setCustomFonts(vector<ImFont*> f)
	{
		customFonts = f;

		if (customFonts.size() == 0)
		{
			ofLogError("ofxSurfingImGui:SurfingLog") << "It looks that not any extra font styles are added!";
		}

		ImTricks::NotifyManager::indexFont.setMax(customFonts.size() - 1);
	}
private:
	vector<ImFont*> customFonts;
	vector<string> namesCustomFonts;

private:
	bool bDefinedMonospacedFonts = false;

private:
	struct tagData
	{
		string name;
		ofColor color;
	};

	vector<tagData> tags;

	void buildTagsDefault()
	{
		ofLogNotice("ofxSurfingImGui:SurfingNotifier") << "buildTagsDefault()";

		AddTag({ "INFO", ofColor::white });
		AddTag({ "VERBOSE", ofColor::white });
		AddTag({ "NOTICE", ofColor::green });
		AddTag({ "WARNING", ofColor::yellow });
		AddTag({ "ERROR", ofColor::red });
		AddTag({ "FATAL_ERROR", ofColor::red });
	}

public:
	void doReset() { ImTricks::NotifyManager::doReset(); }
	void doClear() { ImTricks::NotifyManager::doClear(); }

	//TODO: allow customize
	void AddTag(tagData tag)
	{
		ofLogNotice("ofxSurfingImGui:SurfingNotifier") << "AddTag() name: " << tag.name << ":" << tag.color;

		tags.push_back(tag);
	}

	void Add(string text, string nameTag)
	{
		NotifyState s;

		ofLogNotice("ofxSurfingImGui:SurfingNotifier") << "Add() text:" << text << " tag:" << nameTag;

		if (nameTag == string("INFO")) s = ImTrickNotify_Info;
		else if (nameTag == string("VERBOSE")) s = ImTrickNotify_Verbose;
		else if (nameTag == string("NOTICE")) s = ImTrickNotify_Notice;
		else if (nameTag == string("WARNING")) s = ImTrickNotify_Warning;
		else if (nameTag == string("ERROR")) s = ImTrickNotify_Error;
		else if (nameTag == string("FATAL_ERROR")) s = ImTrickNotify_Error;
		else s = ImTrickNotify_Info;

		ImTricks::NotifyManager::AddNotify(text, s);
	}

	void Add(std::string msg, ofLogLevel logLevel = OF_LOG_NOTICE)
	{
		ofLogNotice("ofxSurfingImGui:SurfingNotifier") << "Add() logLevel: " << logLevel;

		if (logLevel == OF_LOG_VERBOSE) Add(msg, "VERBOSE");
		else if (logLevel == OF_LOG_NOTICE) Add(msg, "NOTICE");
		else if (logLevel == OF_LOG_WARNING) Add(msg, "WARNING");
		else if (logLevel == OF_LOG_ERROR || logLevel == OF_LOG_FATAL_ERROR) Add(msg, "ERROR");
		else
		{
			ofLogNotice("ofxSurfingImGui:SurfingNotifier") << "ofLogLevel " << ofToString((short)logLevel) << " Unknown";
			Add(msg, "UNKNOWN");//will post as info
		}
	}

};