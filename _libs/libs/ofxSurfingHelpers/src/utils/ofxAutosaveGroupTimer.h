
#pragma once

#include "ofMain.h"

class ofxAutosaveGroupTimer
{

public:
	string fileExtension = ".xml";

	string path_Params = "settings";
	string path_GLOBAL = "ofxAutosaveGroupTimer";

	ofParameterGroup paramsControl;

	vector<ofParameterGroup> params;
	void addGroup(ofParameterGroup g);

	//autosave
	ofParameter<bool> ENABLE_AutoSave;
	uint64_t timerLast_Autosave = 0;
	ofParameter<int> timeToAutosave;

	//easy callback
	bool bMustUptate = false;
	bool isTimedOut() {
		if (bMustUptate) {
			bMustUptate = false;//already checked. disable
			return true;
		}
		else return false;
	}

	ofxAutosaveGroupTimer();
	~ofxAutosaveGroupTimer();

	void update();

	void loadParams(ofParameterGroup &g, string path);
	void saveParams(ofParameterGroup &g, string path);

	void saveAllGroups();
};