#pragma once

#include "ofMain.h"

#include "ofxImGui.h"

// Fbo ImGui Window
// from ofxMyUtil from https://github.com/Iwanaka

//namespace ofxImGuiSurfing {
//
//	//--------------------------------------------------------------
//	inline bool TextToFile(const string& Path, const stringstream& Args, bool Append)
//	{
//		//ofFile f(path, ofFile::ReadWrite);
//		//if (!f.exists()) f.create();
//
//		filebuf fb;
//		if (Append) fb.open(Path, ios::app);
//		else fb.open(Path, ios::out);
//
//		if (!fb.is_open()) return false;
//
//		ostream os(&fb);
//		stringstream ss(Args.str());
//
//		if (ss.fail()) return false;
//
//		string temp;
//		while (getline(ss, temp))
//		{
//			if (temp != "")
//			{
//				os << temp << endl;
//			}
//		}
//
//		fb.close();
//		return true;
//	}
//	//--------------------------------------------------------------
//	inline bool TextToFile(const string& Path, const char *Args, bool Append)
//	{
//		stringstream ss; ss << Args;
//		return TextToFile(Path, ss, Append);
//	}
//	//--------------------------------------------------------------
//	inline bool TextToFile(const std::string& Path, std::string Args, bool Append)
//	{
//		stringstream ss; ss << Args;
//		return TextToFile(Path, ss, Append);
//	}
//}

namespace ofxImGuiSurfing {

	//--------------------------------------------------------------
	// classes
	//--------------------------------------------------------------

	class ImGuiLogWindow
	{

	public:

		ImGuiLogWindow() : mLogSize(50), mLog(std::deque<std::string>()) {}
		~ImGuiLogWindow() {}

		//void AddText(std::string str);
		//void AddTextToFile(std::string str, std::string path, bool append = false, bool withTimeStamp = false);
		void SetLogSize(unsigned long size) { mLogSize = size; }
		//void ImGui(const std::string &name);
		void Clear() { mLog.clear(); }

	private:

		unsigned long mLogSize;
		std::deque<std::string> mLog;
		//};

	public:

		//--------------------------------------------------------------
		// ImGuiLogWindow
		//--------------------------------------------------------------
		void AddText(std::string str)
		{
			mLog.emplace_back(str);
			if (mLogSize < mLog.size()) mLog.pop_front();
		}

		////--------------------------------------------------------------
		//void ImGuiLogWindow::AddTextToFile(std::string str, std::string path, bool append, bool withTimeStamp) {
		//	AddText(str);
		//	if (withTimeStamp) str = ofGetTimestampString() + " " + str;
		//	TextToFile(path, str, append);
		//}

		//--------------------------------------------------------------
		void ImGui(const std::string &name) {

			if (!ImGui::Begin(name.c_str())) { ImGui::End(); return; }
			ImGui::BeginChild("Logs");
			auto logs = mLog;
            //macOS bug
//			for each (string l in logs)
//			{
//				ImGui::TextWrapped("%s", l.c_str());
//			}
			ImGui::EndChild();
			ImGui::End();
		}
	};
}
