#pragma once

#include "ofMain.h"

#include <random>
#include <iostream>
using namespace std;

/*

	TODO:

*/

// namespace ofxSurfingHelpers
namespace ofxImGuiSurfing
{
	// Monitors helpers

	// WARRNING! For my personal setup!
	// I have three FHD monitors: 
	// Left monitor is portrait. 
	// Central and Right monitor are landscape.
	//--------------------------------------------------------------
	inline void SurfSetMyMonitor(int layout = 0)
	{
		int h = 38; // window bar height on WIN_32
		int offset = 12;
		int hw = h - offset;
		if (layout == 0) { // left portrait
			ofSetWindowPosition(-1080, h);
			ofSetWindowShape(1080, 1920 - hw);
		}
		else if (layout == 1) { // landscape right
			ofSetWindowPosition(1920, h);
			ofSetWindowShape(1920, 1080 - hw);
		}
		else if (layout == 2) { // landscape left
			ofSetWindowPosition(-1920, h);
			ofSetWindowShape(1920, 1080 - hw);
		}
	}

	//----

	// Serializers

	//----

	//--------------------------------------------------------------
	inline bool loadGroup(ofParameterGroup& g, string path = "", bool debug = true)
	{
		if (path == "")
		{
			path = g.getName() + "_Settings.json"; // a default filename
			ofLogWarning("ofxSurfingHelpers") << "loadGroup " << "Path is empty! Using a default instead!";
		}

		if (debug)
		{
			ofLogNotice("ofxSurfingHelpers") << "loadGroup `" << g.getName() << "` to `" << path << "`";
			ofLogNotice("ofxSurfingHelpers") << "ofParameters: \n\n  " << g.toString();
		}

		ofJson settings;
		settings = ofLoadJson(path);

#ifndef USE_FAST_SERIALIZER
		ofDeserialize(settings, g);
#endif
#ifdef USE_FAST_SERIALIZER
		ofDeserializeSilent(settings, g);
#endif

		// Returns false if no file preset yet.
		ofFile f;
		bool b = f.doesFileExist(path);
		if (b) ofLogNotice("ofxSurfingHelpers") << "loadGroup: `" << g.getName() << "` at `" << path << "`";
		else ofLogError("ofxSurfingHelpers") << "Error loading: `" << g.getName() << "` at `" << path << "` Not found!";

		return b; // Returns true if it's ok
	}

	//--------------------------------------------------------------
	inline bool saveGroup(ofParameterGroup& g, string path = "", bool debug = true)
	{
		if (path == "") {
			path = g.getName() + "_Settings.json";
			ofLogWarning("ofxSurfingHelpers") << "saveGroup " << "Path is empty! Using a default instead!";
		}

		if (debug) {
			ofLogNotice("ofxSurfingHelpers") << g.getName() << " to `" << path << "`";
			ofLogNotice("ofxSurfingHelpers") << "ofParameters: \n\n  " << g.toString();
		}

		// Create folder if folder do not exist!
		// From now, will not rerquire to call manually:
		//ofxSurfingHelpers::CheckFolder(path);

		if (!ofDirectory::doesDirectoryExist(ofFilePath::getEnclosingDirectory(path))) {
			ofFilePath::createEnclosingDirectory(path);
			ofLogWarning("ofxSurfingHelpers") << "Created enclosing folder for: " << path;
		}

		ofJson settings;
		ofSerialize(settings, g);
		bool b = ofSavePrettyJson(path, settings);

		if (b) ofLogVerbose("ofxSurfingHelpers") << "Save: `" << g.getName() << "` at " << path;
		else ofLogError("ofxSurfingHelpers") << "Error saving: `" << g.getName() << "` at " << path;

		return b;
	}

	//----

	// Shorten versions:
	// will use a default path
	//--------------------------------------------------------------
	inline bool load(ofParameterGroup& g)
	{
		return loadGroup(g);
	}

	//--------------------------------------------------------------
	inline bool save(ofParameterGroup& g)
	{
		return saveGroup(g);
	}

	//--

	// Files

	//--------------------------------------------------------------
	// Check if a folder path exist and creates one if not
	// why? many times when you try to save a file, 
	// this is not possible and do not happens 
	// bc the container folder do not exist
	//--------------------------------------------------------------
	inline void CheckFolder(string _path)
	{
		//ofLogNotice("ofxSurfingHelpers")<<(__FUNCTION__) << _path;

		//TODO: A clean alternative..
		/*
		///string jsonfilepath;
		if (!ofDirectory::doesDirectoryExist(ofFilePath::getEnclosingDirectory(jsonfilepath))) {
			ofFilePath::createEnclosingDirectory(jsonfilepath);
		}
		*/

		//if (ofFile::doesFileExist(_path)) {

		//// Workaround to avoid error when folders are folder/subfolder
		//auto _fullPath = ofSplitString(_path, "/");
		//for (int i = 0; i < _fullPath.size(); i++) {
		//	ofLogNotice("ofxSurfingHelpers")<<(__FUNCTION__) << ofToString(i) << " " << _fullPath[i];
		//}

		// /bin/data/
		ofDirectory dataDirectory(ofToDataPath(_path, true));

		// Check if folder path exist
		if (!dataDirectory.isDirectory())
		{
			ofLogError("ofxSurfingHelpers") << (__FUNCTION__) << "FOLDER NOT FOUND! TRYING TO CREATE...";

			// Try to create folder
			bool b = dataDirectory.createDirectory(ofToDataPath(_path, true), false, true);
			//bool b = dataDirectory.createDirectory(ofToDataPath(_path, true));
			// Added enable recursive to allow create nested subfolders if required

			// Debug if creation has been succeded
			if (b) ofLogNotice("ofxSurfingHelpers") << "CREATED '" << _path << "' SUCCESSFULLY!";
			else ofLogError("ofxSurfingHelpers") << "UNABLE TO CREATE '" << _path << "' FOLDER!";
		}
		else
		{
			ofLogVerbose("ofxSurfingHelpers") << _path << " Found!";// nothing to do
		}
	}



	//----

}; // namespace  

//namespace ofxSurfingHelpers
namespace ofxImGuiSurfing
{
	//------------------------------------------------------------------------------
	// Animator functions taken from
	// https://github.com/tcoppex/ofxFontSampler/blob/main/example/src/ofApp.cpp

	namespace
	{
		/* Return a linear value in range [0,1] every delay (in seconds). */
		float Tick(float delay = 1.0f) {
			return fmodf(ofGetElapsedTimeMillis() / 1000.0f, delay) / delay;
		}

		/* Return a linear value in range [0,1] every delay (in seconds),
		 with value equal 0 at boundaries, and 1 at delay / 2. */
		float Bounce(float delay = 1.0f) {
			return 0.5f * (1.0 + glm::sin(Tick(delay) * glm::two_pi<float>()));
		}

		/* Noise function used by the gradient scaling. */
		float Noise(const ofPoint& vertex = ofPoint(1, -1)) {
			//return /*24.0f **/ ofNoise(0.005f*vertex + 0.5f*ofGetElapsedTimeMillis()*0.0002f);

			return ofNoise(0.05f * vertex + 0.5f * ofGetElapsedTimeMillis() * 0.002f);
		}

		static constexpr int32_t kCharsetSize = 26;

	}  // namespace

	//--

	inline float NextGaussian(const float center, const float standard_dev)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::normal_distribution<float> distribution(center, standard_dev);
		return distribution(mt);
	}
	inline float NextReal(const float lower, const float upper)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> distribution(lower, upper);
		return distribution(mt);
	}

	//-

	// Get a blink faded to use as alpha on gui button when "active-listening-mode" enabled
	// ie: Blink when a new preset is editing
	//--------------------------------------------------------------
	inline float getFadeBlink(float min = 0.20, float max = 0.80, float freq = 0.15) {

		float a = ofMap(glm::sin(freq * ofGetFrameNum()), -1, 1, min, max);

		return a;
	}
};