#pragma once
#include <string>
#include "ofFileUtils.h"
#include "ofFbo.h"
#include "ofTexture.h"
#include "ofImage.h"

//--------------------------------------------------------------
// ofxMyUtil IO
//--------------------------------------------------------------

namespace ofxMyUtil {
	namespace IO {

		bool JsonToFile(const std::string &Buf, std::string Path, bool Pretty = true);
		bool JsonToFile(const ofBuffer &Buf, std::string Path, bool Pretty = true);

		bool FboToFile(const class ofFbo &Fbo,  std::string Path, 
			ofImageType Type = ofImageType::OF_IMAGE_COLOR,
			ofImageQualityType Quality = ofImageQualityType::OF_IMAGE_QUALITY_BEST);

		bool TextureToFile(const ofTexture &Tex, std::string Path, 
			ofImageType Type = ofImageType::OF_IMAGE_COLOR,
			ofImageQualityType Quallity = ofImageQualityType::OF_IMAGE_QUALITY_BEST);

		bool CheckExitsFile(const std::string& Path, const float& RetryTime);
		bool CreateDir(const std::string& Path);

		bool TextToFile(const std::string& Path, const std::stringstream& Args, bool Append = false);
		bool TextToFile(const std::string& Path, const char *Args, bool Append = false);
		bool TextToFile(const std::string& Path, std::string Args, bool Append = false);

		//template <typename T>
		//bool loadJsonAsKey(const nlohmann::json::value_type &j, T& val, T initVal) {
		//	if (j.is_null()) { 
		//		val = initVal; return false; 
		//	}
		//	else { 
		//		val = j.get<T>(); return true; 
		//	}
		//}

	}
}