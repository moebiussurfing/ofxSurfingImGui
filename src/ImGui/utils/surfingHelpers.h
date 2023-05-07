#pragma once

//#ifndef OF_APP_DEFINED_ofxSurfingHelpers

//----

#include "ofMain.h"

#include <random>
#include <iostream>
using namespace std;

//namespace ofxSurfingHelpers//TODO:
namespace ofxImGuiSurfing
{
	// Monitors helpers

	// WARNING! For my personal setup!
	// I have three FHD monitors: 
	// Left monitor is portrait. 
	// Central and Right monitor are landscape.

	//--------------------------------------------------------------
	inline void setMonitorsLayout(int pos, bool bPortrait, bool bStandardFrameRate)
	{
		// main monitor, and in fact all the monitors, 
		// are expected as FHD 1920x1080.
		// in my case my main monitor is landscape and central
		// and the left and right monitors are portrait.
		// you can modify for your own layout!

		if (bStandardFrameRate) {
			ofSetFrameRate(60);
			ofSetVerticalSync(false);
		}

		int x, y, w, h;

		// window bar height on WIN_32.
		int yOffset = 38;
		int hOffset = 12;

		x = y = 0;
		y = yOffset;

		w = bPortrait ? 1080 : 1920;
		h = bPortrait ? 1920 : 1080;
		h -= hOffset;

		if (pos == -1) x = bPortrait ? -1080 : -1920;
		else if (pos == 1) x = 1920;

		ofSetWindowPosition(x, y);
		ofSetWindowShape(w, h);
	};

	// Legacy
	//--------------------------------------------------------------
	inline void setMonitorsLayout(int layout = 0, bool bStandardFrameRate = true)
	{
		if (bStandardFrameRate) {
			ofSetFrameRate(60);
			ofSetVerticalSync(false);
		}

		// window bar height on WIN_32.
		int h = 38;
		int offset = 12;
		int hw = h - offset;
		if (layout == 0)
		{
			// move app window to the left monitor (from main) as portrait
			ofSetWindowPosition(-1080, h);
			ofSetWindowShape(1080, 1920 - hw);
		}
		else if (layout == 1)
		{
			// move app window  to the right monitor (from main) as landscape 
			ofSetWindowPosition(1920, h);
			ofSetWindowShape(1920, 1080 - hw);
		}
		else if (layout == 2)
		{
			// move app window  to the left monitor (from main) as landscape
			ofSetWindowPosition(-1920, h);
			ofSetWindowShape(1920, 1080 - hw);
		}
	};

	// Images drawing
	/*
	//--------------------------------------------------------------
	inline void SurfDrawImageFullScreenFit(ofFloatImage& imageFloat, ofScaleMode scaleMode = OF_SCALEMODE_FIT)
	{
		ofRectangle rr(0, 0, imageFloat.getWidth(), imageFloat.getHeight());
		rr.scaleTo(ofGetCurrentViewport(), scaleMode);
		imageFloat.draw(rr.x, rr.y, rr.width, rr.height);
	}
	//--------------------------------------------------------------
	inline void SurfDrawImageFullScreenFit(ofImage& image, ofScaleMode scaleMode = OF_SCALEMODE_FIT)
	{
		ofRectangle rr(0, 0, image.getWidth(), image.getHeight());
		rr.scaleTo(ofGetCurrentViewport(), scaleMode);
		image.draw(rr.x, rr.y, rr.width, rr.height);
	}
	//--------------------------------------------------------------
	inline void SurfDrawImageAtBottom(ofImage& image, bool bLine=true)
	{
		ofPushStyle();

		ofRectangle r{ 0,0, image.getWidth(),image.getHeight() };
		r.scaleTo(ofGetCurrentViewport(), OF_SCALEMODE_FIT);
		r.translateY(ofGetHeight() - r.getBottomLeft().y);
		ofSetColor(255, 255);
		image.draw(r.x, r.y, r.getWidth(), r.getHeight());
		if (bLine) {
			ofSetColor(0, 200);
			ofSetLineWidth(3);
			ofDrawLine(r.getTopLeft(), r.getTopRight());
		}
		ofPopStyle();
	}
	*/

	//----

	// ofParams Serializers

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
	};

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
	};

	//----

	// Shorten versions:
	// will use a default path
	//--------------------------------------------------------------
	inline bool load(ofParameterGroup& g)
	{
		return loadGroup(g);
	};

	//--------------------------------------------------------------
	inline bool save(ofParameterGroup& g)
	{
		return saveGroup(g);
	};

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
	};

	//----

	//------------------------------------------------------------------------------
	// Animator functions taken from
	// https://github.com/tcoppex/ofxFontSampler/blob/main/example/src/ofApp.cpp

	// The purpose of this anonymous namespace is to provide an internal implementation detail that should not be exposed outside the ofxImGuiSurfing namespace
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

		///* Noise function used by the gradient scaling. */
		//float Noise(const ofPoint& vertex = ofPoint(1, -1)) {
		//	//return /*24.0f **/ ofNoise(0.005f*vertex + 0.5f*ofGetElapsedTimeMillis()*0.0002f);

		//	return ofNoise(0.05f * vertex + 0.5f * ofGetElapsedTimeMillis() * 0.002f);
		//}

		//static constexpr int32_t kCharsetSize = 26;

	}  // namespace

	//--

	/*
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
	*/

	//-

	// Get a blink faded to use as alpha on gui button when "active-listening-mode" enabled
	// ie: Blink when a new preset is editing
	//--------------------------------------------------------------
	inline float getFadeBlink(float min = 0.20, float max = 0.80, float freq = 0.15) {

		float a = ofMap(glm::sin(freq * ofGetFrameNum()), -1, 1, min, max);

		return a;
	}

	//----

	// Logarithmic functions
	// Recommended for Audio gain 
	// or some frequency variables. 

	inline float reversedExponentialFunction(float y) {
		return log10(y);
	}

	inline float exponentialFunction(float x) {
		return pow(10, x);
	}

	// Wrong way->slider widget returns a value between 0 and 100, 
	// divide that by 100 and multiply every sample by that value
	// Better way->slider widget returns a value between 0 and 100, 
	// divide that by 100, then square it, and multiply every sample by that value
	inline float squaredFunction(float v) {//pass gain
		return (v * v);
	}

	//--

	/*

	EXAMPLE

	ofEventListener listener;
	ofParameter<float> vIn;
	ofParameter<float> vOut1;
	ofParameter<float> vOut2;
	ofParameter<float> vOut3;

	vIn.set("vIn", 0.5f, 0.f, 1.f);
	vOut1.set("vOut1", 0.5f, 0.f, 1.f);
	vOut2.set("vOut2", 0.5f, 0.f, 1.f);
	vOut3.set("vOut3", 0.5f, 0.f, 1.f);

	// Callback for vIn
	// convert input linear to log
	listener = vIn.newListener([this](float& v) {

		vOut1 = ofxSurfingHelpers::reversedExponentialFunction(vIn * 10.f);
		vOut2 = ofxSurfingHelpers::exponentialFunction(vIn) / 10.f;
		vOut3 = ofxSurfingHelpers::squaredFunction(vIn);

		ofLogNotice() << v << " -> " << vOut1.get() << " : " << vOut2.get();
	});

	*/

	//----

	// Simple Smooth

	/*

	Example use:
	ofxSurfingHelpers::ofxKuValueSmooth(out, int, smooth);

	*/

	//--------------------------------------------------------------
	template <typename T>
	inline void ofxKuValueSmooth(T& value, T target, float smooth) {
		value += (target - value) * (1 - smooth);
	}

	//--------------------------------------------------------------
	template <typename T>
	void ofxKuValueSmoothDirected(T& value, T target, float smooth0, float smooth1) {
		float smooth = (target < value) ? smooth0 : smooth1;
		ofxKuValueSmooth(value, target, smooth);
	}
};

//----

//#endif // OF_APP_DEFINED_ofxSurfingHelpers