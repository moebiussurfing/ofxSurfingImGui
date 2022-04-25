#include "ofxAutosaveGroupTimer.h"

//#pragma once

//--------------------------------------------------------------
ofxAutosaveGroupTimer::ofxAutosaveGroupTimer()
{
	params.clear();

	ENABLE_AutoSave.set("ENABLE_AutoSave", true);
	timeToAutosave.set("timeToAutosave", 5000, 100, 10000);
	
	paramsControl.setName("paramsControl");
	paramsControl.add(ENABLE_AutoSave);
	paramsControl.add(timeToAutosave);
}

//--------------------------------------------------------------
ofxAutosaveGroupTimer::~ofxAutosaveGroupTimer()
{
}

//--------------------------------------------------------------
void ofxAutosaveGroupTimer::addGroup(ofParameterGroup g)
{
	params.push_back(g);
}

//--------------------------------------------------------------
void ofxAutosaveGroupTimer::saveAllGroups()
{
	for (int i = 0; i< params.size(); i++)
	{
		string path = path_GLOBAL + "/" + path_Params + "_" + params[i].getName() +fileExtension;
		saveParams(params[i], path);
	}
}

//--------------------------------------------------------------
void ofxAutosaveGroupTimer::update()
{
	//--

	//autosave
	//ENABLE_AutoSave = false;

	if (ENABLE_AutoSave && ofGetElapsedTimeMillis() - timerLast_Autosave > timeToAutosave)
	{
		//easy callback
		bMustUptate = true;

		saveAllGroups();

		//saveParams(params_Control, path_GLOBAL + path_Params_Control);
		
		// bDISABLE_CALLBACKS = true;
		// //get gui position before save
		// positionGui = glm::vec2(gui_Control.getPosition());
		// saveParams(params_Control, path_GLOBAL + path_Params_Control);
		// bDISABLE_CALLBACKS = false;

		//-

		timerLast_Autosave = ofGetElapsedTimeMillis();
		ofLogNotice(__FUNCTION__) << "DONE Autosave";
	}

	//easycallback
	bool b = isTimedOut();
	if (b) {
		ofLogNotice(__FUNCTION__) << "isTimedOut: " << (b?"TRUE":"FALSE");
	}
}


//--------------------------------------------------------------
void ofxAutosaveGroupTimer::loadParams(ofParameterGroup &g, string path)
{
	ofLogNotice(__FUNCTION__) << "loadParams:";
	ofXml settings;
	bool bLoaded = settings.load(path);
	if (!bLoaded)
	{
		ofLogError(__FUNCTION__) << "FILE '" << path << "' NOT FOUND!";
		//errorsDEBUG.addError("ofxAutosaveGroupTimer", "loadParams()", path);
	}
	else
	{
		ofDeserialize(settings, g);
		ofLogNotice(__FUNCTION__) << "LOADED FILE '" << path << "' TO GROUP: '" << g.getName() << "'";
	}
}

//--------------------------------------------------------------
void ofxAutosaveGroupTimer::saveParams(ofParameterGroup &g, string path)
{
	ofLogNotice(__FUNCTION__) << "saveParams:";
	ofXml settings;
	ofSerialize(settings, g);
	bool bSave = settings.save(path);
	if (bSave)
	{
		ofLogNotice(__FUNCTION__) << "SAVED FILE FILE '" << path << "' FROM GROUP: '" << g.getName() << "'";
	}
	else
	{
		ofLogError(__FUNCTION__) << "CAN'T SAVE FILE '" << path << "' FROM GROUP: '" << g.getName() << "'. MAYBE FOLDER NOT ACCESIBLE!";
	}

}
