#pragma once
//--------------------------
// classes
#include "ofCircleInfo.h"
#include "ofxMyUtilImGui.h"
#include "ofScaleable.h"
#include "ofThreadSaveImage.h"
#include "SerialMonitor.h"


//--------------------------
// utils
#include "ofxMyUtilConsole.h"
#include "ofxMyUtilEvent.h"
#include "ofxMyUtilGL.h"
#include "ofxMyUtilIO.h"
#include "ofxMyUtilMedia.h"
#include "ofxMyUtilString.h"


namespace ofxMyUtil {

	//配列のサイズを確認する
	#define IWAX_GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))

	//not a number check
	/*template<typename T>
	T isNaNCheck(T val, T defaultVal);
	template<typename T>
	T ofxMyUtil::SP::isNaNCheck(T val, T defaultVal) {
		if (isnan(val)) return defaultVal;
		return val;
	}
	template<>
	float ofxMyUtil::SP::isNaNCheck(float val, float defaultVal) {
		if (isnan(val)) return defaultVal;
		return val;
	}*/

};
