#include "ofxMyUtilIO.h"
#include "ofJson.h"

//--------------------------------------------------------------
// ofxMyUtil IO
//--------------------------------------------------------------
using namespace ofxMyUtil;
using namespace std;
//--------------------------------------------------------------
// *** Sample code ***
// stringstream ss;
// ss << "{\"One\":{\"a\":1,\"b\":\"test\"}}";
// ofBuffer buf(ss.str().c_str(), ss.str().size());
// ofxMyUtil::IO::jsonToFile(buf);
//--------------------------------------------------------------
bool IO::JsonToFile(const string &Buf, string Path, bool Pretty) 
{
	try
	{
		auto json = ofJson::parse(Buf);
		if (Pretty) return ofSavePrettyJson(Path, json);
		else return ofSaveJson(Path, json);
	}
	catch (const exception&)
	{
		return 0;
	}
	return 1;
}

//--------------------------------------------------------------
bool IO::JsonToFile(const ofBuffer &Buf, std::string Path, bool Pretty) 
{
	return JsonToFile(Buf.getText(), Path, Pretty);
}

//--------------------------------------------------------------
bool IO::FboToFile(const ofFbo &Fbo, string Path, ofImageType Type, ofImageQualityType Quality) 
{
	ofPixels pix;
	pix.allocate(Fbo.getWidth(), Fbo.getHeight(), Type);
	Fbo.readToPixels(pix);

	return ofSaveImage(pix, Path, Quality);
}

//--------------------------------------------------------------
bool IO::TextureToFile(const ofTexture &Tex, std::string Path, ofImageType Type, ofImageQualityType Quality) 
{
	ofPixels pix;
	pix.allocate(Tex.getWidth(), Tex.getHeight(), Type);
	Tex.readToPixels(pix);

	return ofSaveImage(pix, Path, Quality);
}

//--------------------------------------------------------------
bool IO::CheckExitsFile(const string& Path, const float& RetryTime) 
{
	ofFile file(Path);
	float currentTime = ofGetElapsedTimef();
	float retryTime = RetryTime;
	float meusureTime = 0.0;

	while (file.exists() || meusureTime <= retryTime) 
	{
		meusureTime = ofGetElapsedTimef() - currentTime;

		if (file.exists()) return true;
		if (meusureTime >= retryTime) return false;
	}

	return false;
}

//--------------------------------------------------------------
bool IO::CreateDir(const string& Path) 
{
	//ofDirectory dir(path);
	//return ofDirectory::createDirectory(path);
	filesystem::path p(Path);
	boost::system::error_code e;
	bool check = filesystem::exists(p, e);

	if (!check || !e) 
	{
		bool create = filesystem::create_directory(Path, e);
		if (create) return 1;
	}
	return 0;
}

//--------------------------------------------------------------
bool IO::TextToFile(const string& Path, const stringstream& Args, bool Append)
{
	//ofFile f(path, ofFile::ReadWrite);
	//if (!f.exists()) f.create();

	filebuf fb;
	if (Append) fb.open(Path, ios::app);
	else fb.open(Path, ios::out);

	if (!fb.is_open()) return false;

	ostream os(&fb);
	stringstream ss(Args.str());

	if (ss.fail()) return false;

	string temp;
	while (getline(ss, temp)) 
	{
		if (temp != "") 
		{
			os << temp << endl;
		}
	}

	fb.close();
	return true;
}

//--------------------------------------------------------------
bool IO::TextToFile(const string& Path, const char *Args, bool Append) 
{
	stringstream ss; ss << Args;
	return TextToFile(Path, ss, Append);
}

//--------------------------------------------------------------
bool IO::TextToFile(const std::string& Path, std::string Args, bool Append) 
{
	stringstream ss; ss << Args;
	return TextToFile(Path, ss, Append);
}