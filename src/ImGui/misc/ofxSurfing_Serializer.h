#pragma once

#include "ofMain.h"

namespace ofxImGuiSurfing {

//---------------------

/* some helper tools */

// serializers
//--------------------------------------------------------------
inline bool loadGroup(ofParameterGroup &g, string path = "", bool debug = true)
{
	if (path == "") path = "Settings.json";

	if (debug)
	{
		ofLogNotice(__FUNCTION__) << g.getName() << " to " << path;
		ofLogNotice(__FUNCTION__) << "parameters: \n\n" << g.toString();
	}
	else
	{
		ofLogVerbose(__FUNCTION__) << g.getName() << " to " << path;
		ofLogVerbose(__FUNCTION__) << "parameters: \n\n" << g.toString();
	}

	ofJson settings;
	settings = ofLoadJson(path);


	bool b = !settings.is_null();//TODO:
	//bool b = true;//TODO:

	//bool b = settings.is_null;
	//if (b) ofLogVerbose(__FUNCTION__) << "Load: " << g.getName() << " at " << path;
	//else ofLogError(__FUNCTION__) << "Error loading: " << g.getName() << " at " << path;

	return b;//returns true if its ok
}

//--------------------------------------------------------------
inline bool saveGroup(ofParameterGroup &g, string path = "", bool debug = true)
{
	if (path == "") path = "Settings.json";

	if (debug) {
		ofLogNotice(__FUNCTION__) << g.getName() << " to " << path;
		ofLogNotice(__FUNCTION__) << "parameters: \n\n" << g.toString();
	}
	else
	{
		ofLogVerbose(__FUNCTION__) << g.getName() << " to " << path;
		ofLogVerbose(__FUNCTION__) << "parameters: \n\n" << g.toString();
	}

	//ofxSurfingHelpers::CheckFolder(path);

	ofJson settings;
	ofSerialize(settings, g);
	bool b = ofSavePrettyJson(path, settings);

	if (b) ofLogVerbose(__FUNCTION__) << "Save: " << g.getName() << " at " << path;
	else ofLogError(__FUNCTION__) << "Error saving: " << g.getName() << " at " << path;

	return b;
}
};

