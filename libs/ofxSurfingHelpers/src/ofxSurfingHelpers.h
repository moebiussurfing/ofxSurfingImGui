
#pragma once

#include "ofMain.h"

//---------
//
// OPTIONAL

//#define USE_FAST_SERIALIZER // test improve serialize performance..

#include "ofxSurfingConstants.h"

//#ifdef USE_IM_GUI
//#include "ofxSurfing_ImGui.h"
//#endif

#ifdef USE_ofxGui
#include "ofxSurfing_ofxGui.h"
#endif

//
//#define USE_JSON		// uncomment to use default xml instead json for ofParameterGroup de/serializers
//#define USE_XML		// uncomment to use default xml instead json for ofParameterGroup de/serializers
//
//---------


#include "ofxSurfing_Timers.h"
#include "ofxSurfing_Widgets.h"


namespace ofxSurfingHelpers {
	
	//----

	// SERIALIZERS

	//TODO:
	//testing for improve performance
	//changing the mode we trig the loaded params..
	//public:
	//private:

	inline void ofDeserializeSilent(const ofJson & json, ofAbstractParameter & parameter) {
		if (!parameter.isSerializable()) {
			return;
		}
		std::string name = parameter.getEscapedName();
		if (json.find(name) != json.end()) {
			if (parameter.type() == typeid(ofParameterGroup).name()) {
				ofParameterGroup & group = static_cast <ofParameterGroup &>(parameter);
				for (auto & p : group) {
					ofDeserializeSilent(json[name], *p);
				}
			}
			else {
				if (parameter.type() == typeid(ofParameter <int>).name() && json[name].is_number_integer()) {
					parameter.cast <int>().setWithoutEventNotifications(json[name].get<int>());
					//parameter.cast <int>() = json[name].get<int>();
				}
				else if (parameter.type() == typeid(ofParameter <float>).name() && json[name].is_number_float()) {
					parameter.cast <float>().setWithoutEventNotifications(json[name].get<float>());
					//parameter.cast <float>() = json[name].get<float>();
				}
				else if (parameter.type() == typeid(ofParameter <bool>).name() && json[name].is_boolean()) {
					parameter.cast <bool>().setWithoutEventNotifications(json[name].get<bool>());
					//parameter.cast <bool>() = json[name].get<bool>();
				}
				else if (parameter.type() == typeid(ofParameter <int64_t>).name() && json[name].is_number_integer()) {
					parameter.cast <int64_t>().setWithoutEventNotifications(json[name].get<int64_t>());
					//parameter.cast <int64_t>() = json[name].get<int64_t>();
				}
				else if (parameter.type() == typeid(ofParameter <std::string>).name()) {
					parameter.cast <std::string>().setWithoutEventNotifications(json[name].get<std::string>());
					//parameter.cast <std::string>() = json[name].get<std::string>();
				}
				else {
					parameter.fromString(json[name]);
				}
			}
		}
	}

	//---

	// xml
#ifndef USE_JSON
	//--------------------------------------------------------------
	inline bool loadGroup(ofParameterGroup &g, string path)
	{
		ofLogVerbose(__FUNCTION__) << g.getName() << " to " << path;
		ofLogVerbose(__FUNCTION__) << "\nofParameters: \n\n" << g.toString();

		ofXml settings;
		bool b = settings.load(path);

		if (b) ofLogVerbose(__FUNCTION__) << "Loading: " << g.getName() << " at " << path;
		else ofLogError(__FUNCTION__) << "Error loading: " << g.getName() << " at " << path;

		ofDeserialize(settings, g);

		return b;
	}

	//--------------------------------------------------------------
	inline bool saveGroup(ofParameterGroup &g, string path)
	{
		ofLogVerbose(__FUNCTION__) << g.getName() << " to " << path;
		ofLogVerbose(__FUNCTION__) << "\nofParameters: \n\n" << g.toString();

		//CheckFolder(path);

		ofXml settings;
		ofSerialize(settings, g);
		bool b = settings.save(path);

		if (b) ofLogVerbose(__FUNCTION__) << "Save: " << g.getName() << " at " << path;
		else ofLogError(__FUNCTION__) << "Error saving: " << g.getName() << " at " << path;
		return b;
	}
#endif

	//----

#ifdef USE_JSON
	//--------------------------------------------------------------
	inline bool loadGroup(ofParameterGroup &g, string path = "", bool debug = true)
	{
		if (path == "") path = g.getName() + "_Settings.json";
		//if (path == "") path = "settings.json";

		if (debug)
		{
			ofLogNotice(__FUNCTION__) << g.getName() << " to " << path;
			ofLogNotice(__FUNCTION__) << "\nofParameters: \n\n" << g.toString();
		}
		else
		{
			ofLogVerbose(__FUNCTION__) << g.getName() << " to " << path;
			ofLogVerbose(__FUNCTION__) << "\nofParameters: \n\n" << g.toString();
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
		//if (path == "") path = "settings.json";
		if (path == "") path = g.getName() + "_Settings.json";

		if (debug) {
			ofLogNotice(__FUNCTION__) << g.getName() << " to " << path;
			ofLogNotice(__FUNCTION__) << "\nofParameters: \n\n" << g.toString();
		}
		else
		{
			ofLogVerbose(__FUNCTION__) << g.getName() << " to " << path;
			ofLogVerbose(__FUNCTION__) << "\nofParameters: \n\n" << g.toString();
		}

		//ofxSurfingHelpers::CheckFolder(path);

		ofJson settings;
		ofSerialize(settings, g);
		bool b = ofSavePrettyJson(path, settings);

		if (b) ofLogVerbose(__FUNCTION__) << "Save: " << g.getName() << " at " << path;
		else ofLogError(__FUNCTION__) << "Error saving: " << g.getName() << " at " << path;

		return b;
	}
#endif

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


	///* RETURN FILE EXTENSION */
	//inline string getFileName(string _str, bool _trimExt = false) {
	//	string name = "";
	//	int slashPos = _str.rfind('/');

	//	if (slashPos != string::npos) {
	//		name = _str.substr(slashPos + 1);

	//		if (_trimExt)
	//			name = getFilePathTrimExtension(name);
	//	}

	//	return name;
	//}

	//inline string getFileFolderPath(string _str) {
	//	string name = "";
	//	int slashPos = _str.rfind('/');

	//	if (slashPos != string::npos) {
	//		name = _str.substr(0, slashPos);
	//	}

	//	return name;
	//}

	//inline string getFileExtension(string _str) {
	//	string ext = "";
	//	int extPos = _str.rfind('.');

	//	if (extPos != string::npos) {
	//		ext = _str.substr(extPos + 1);
	//	}

	//	return ext;
	//}

	//inline string getFilePathTrimExtension(string _str) {
	//	string ext = "";
	//	int extPos = _str.rfind('.');

	//	if (extPos != string::npos) {
	//		ext = _str.substr(0, extPos);
	//	}

	//	return ext;
	//}

	//inline int getNumWords(std::string str)
	//{
	//	int word_count(0);
	//	std::stringstream ss(str);
	//	std::string word;
	//	while (ss >> word) ++word_count;
	//	return word_count;
	//}

	//---

	// original code copied from
	// ofxFilikaUtils.h
#define SECS_PER_MIN 60
#define SECS_PER_HOUR 3600
	//--------------------------------------------------------------
	inline std::string calculateTime(float _time) {

		int seconds;
		int minutes;
		int mins_left;
		int secs_left;

		seconds = (/*gameTimeSeconds - */int(_time));
		minutes = (/*gameTimeSeconds - */int(_time)) / SECS_PER_MIN;
		mins_left = minutes % SECS_PER_MIN;
		secs_left = seconds % SECS_PER_MIN;

		std::string mins;
		std::string secs;

		if (mins_left < 10) {
			mins = "0" + ofToString(mins_left);
		}
		else {
			mins = ofToString(mins_left);
		}

		if (secs_left < 10) {
			secs = "0" + ofToString(secs_left);
		}
		else {
			secs = ofToString(secs_left);
		}

		//cout << ofGetElapsedTimeMillis() / 1000 << endl;
		//cout << "remaining time : " << mins_left << " : " <<  secs_left << endl;
		//cout << "remaining time : " << mins << " : " <<  secs << endl;

		if (mins_left < 0 || secs_left < 0)
			return "00:00";
		else
			return (mins + ":" + secs);
	}


	//----

	// linear to exponential conversion
	//https://forum.openframeworks.cc/t/how-to-add-a-new-feature-to-someones-addon-exponential-scale-ofxguiextended-sliders/36909/2
	//ofParameter<float> exponentialValue;
	//ofxGuiFloatFunctionSlider* functionSlider = group->add<ofxGuiFloatFunctionSlider>(exponentialValue.set("exponential", 2, 1, 10000));
	//functionSlider->setFunctions(exponentialFunction, reversedExponentialFunction);

	//// and here are example functions :

	//float exponentialFunction(float x) {
	//	return pow(10, x);
	//}

	//float reversedExponentialFunction(float y) {
	//	return log10(y);
	//}


	//----

////https://github.com/companje/ofxExtras/blob/master/src/ofxExtras.cpp
//	void ofxSetColorHSB(int h, int s, int b, int a) {
//    unsigned char hsv[] = {(unsigned char)h,(unsigned char)s,(unsigned char)b};
//    unsigned char rgb[] = {0,0,0};
//
//    if (hsv[2] == 0); // black
//	else if (hsv[1] == 0) { rgb[0]=b;  rgb[1]=b; rgb[2]=b; } // grays
//    else {
//        float h = hsv[0] * 6. / 255.;
//        float s = hsv[1] / 255.;
//        int hCategory = (int) floorf(h);
//        float hRemainder = h - hCategory;
//        unsigned char pv = (unsigned char) ((1.f - s) * hsv[2]);
//        unsigned char qv = (unsigned char) ((1. - s * hRemainder) * hsv[2]);
//        unsigned char tv = (unsigned char) ((1. - s * (1.-hRemainder)) * hsv[2]);
//        switch (hCategory) {
//            case 0: rgb[0] = hsv[2]; rgb[1] = tv; rgb[2] = pv; break; //r
//            case 1: rgb[0] = qv; rgb[1] = hsv[2]; rgb[2] = pv; break; //g
//            case 2: rgb[0] = pv; rgb[1] = hsv[2]; rgb[2] = tv; break;
//            case 3: rgb[0] = pv; rgb[1] = qv; rgb[2] = hsv[2]; break; //b
//            case 4: rgb[0] = tv; rgb[1] = pv; rgb[2] = hsv[2]; break;
//            case 5: rgb[0] = hsv[2]; rgb[1] = pv; rgb[2] = qv; break; //back to r
//        }
//    }
//    ofSetColor(rgb[0],rgb[1],rgb[2],a);
//}

};
//namespace
// ofxSurfingHelpers

//--

//// randoms
//#include <random>
////#include <iostream>
////https://forum.openframeworks.cc/t/normal-gaussian-random-generator/11469/4?u=moebiussurfing
//class MyRandom
//{
//public:
//	float NextGaussian(const float center, const float standard_dev)
//	{
//		std::random_device rd;
//		std::mt19937 mt(rd());
//		std::normal_distribution<float> distribution(center, standard_dev);
//		return distribution(mt);
//	}
//	float NextReal(const float lower, const float upper)
//	{
//		std::random_device rd;
//		std::mt19937 mt(rd());
//		std::uniform_real_distribution<float> distribution(lower, upper);
//		return distribution(mt);
//	}
//};

