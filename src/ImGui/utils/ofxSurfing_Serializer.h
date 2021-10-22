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

#ifndef USE_FAST_SERIALIZER
	ofDeserialize(settings, g);
#endif
#ifdef USE_FAST_SERIALIZER
	ofDeserializeSilent(settings, g);
#endif

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

//-

// 3. FILES

//--------------------------------------------------------------
// check if a folder path exist and creates one if not
// why? many times when you try to save a file, this is not possible and do not happens bc the container folder do not exist
//--------------------------------------------------------------
inline void CheckFolder(string _path)
{
	//ofLogNotice(__FUNCTION__) << _path;

	//// workaround to avoid error when folders are folder/subfolder
	//auto _fullPath = ofSplitString(_path, "/");
	//for (int i = 0; i < _fullPath.size(); i++) {
	//	ofLogNotice(__FUNCTION__) << ofToString(i) << " " << _fullPath[i];
	//}

	ofDirectory dataDirectory(ofToDataPath(_path, true));// /bin/data/

	// check if folder path exist
	if (!dataDirectory.isDirectory())
	{
		ofLogError(__FUNCTION__) << "FOLDER NOT FOUND! TRYING TO CREATE...";

		// try to create folder
		//bool b = dataDirectory.createDirectory(ofToDataPath(_path, true));
		bool b = dataDirectory.createDirectory(ofToDataPath(_path, true), false, true);
		// added enable recursive to allow create nested subfolders if required

		// debug if creation has been succeded
		if (b) ofLogNotice(__FUNCTION__) << "CREATED '" << _path << "' SUCCESSFULLY!";
		else ofLogError(__FUNCTION__) << "UNABLE TO CREATE '" << _path << "' FOLDER!";
	}
	else
	{
		ofLogVerbose(__FUNCTION__) << _path << " Found!";// nothing to do
	}
}

};

