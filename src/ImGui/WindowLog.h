#pragma once

#include "ofMain.h"

//#include "ofxSurfingImGui.h"
#include "ofxImGui.h"

//// Fbo ImGui Window
//// from ofxMyUtil from https://github.com/Iwanaka
//
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

		//--------------------------------------------------------------
		ImGuiLogWindow() : mLogSize(20), mLog(std::deque<std::string>()) {}

		//--------------------------------------------------------------
		~ImGuiLogWindow() {}

		//--------------------------------------------------------------
		void SetLogSize(unsigned long size) { mLogSize = size; }

		//--------------------------------------------------------------
		void Clear() { mLog.clear(); }

	private:

		unsigned long mLogSize;
		std::deque<std::string> mLog;
		//};

	public:

		//ofParameter<bool> bGui{"Show", true};

		//--------------------------------------------------------------
		// ImGuiLogWindow
		//--------------------------------------------------------------

		//TODO: add colors
		//enum IM_GUI_LOG_STYLE
		//{
		//	IM_GUI_LOG_STYLE_0 = 0,
		//	IM_GUI_LOG_STYLE_1,
		//	IM_GUI_LOG_STYLE_2
		//};
		//IM_GUI_LOG_STYLE style = IM_GUI_LOG_STYLE_0

		//--------------------------------------------------------------
		//void AddTextToFile(std::string str, std::string path, bool append = false, bool withTimeStamp = false);

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
		//void ImGui(std::string name = "Log", ofParameter<bool>& bGui)
		void ImGui(ofParameter<bool>& bGui)
		{
			if (!bGui) return;

			std::string name = bGui.getName();

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
			flags |= ImGuiWindowFlags_NoScrollbar;
			//flags |= ImGuiWindowFlags_;

			ImGuiCond cond = ImGuiCond_FirstUseEver;
			const int LOG_WINDOW_SIZE = 250;
			float w = ofGetWidth();
			float h = ofGetHeight();
			ImGui::SetNextWindowPos(ImVec2(w - LOG_WINDOW_SIZE - 10, 20), cond);
			ImGui::SetNextWindowSize(ImVec2(LOG_WINDOW_SIZE, h - 100), cond);

			//if (!ImGui::Begin(name.c_str(), NULL, flags))
			if (!ImGui::Begin(name.c_str(), (bool*)&bGui.get(), flags))
			{
				ImGui::End(); return;
			}
			{
				float _w1 = ofxImGuiSurfing::getWidgetsWidth(1);
				float _h = 1.5f * ofxImGuiSurfing::getWidgetsHeightUnit();
				float _sp = ofxImGuiSurfing::GetFrameHeightWithSpacing();

				static int _pre = -1;
				float hl = ofxImGuiSurfing::getWidgetsHeightUnit();

				// auto fit
				int _count = (ImGui::GetWindowHeight() - _h - _sp) / (float)hl;
				if (_count != _pre) {
					_pre = _count;
					SetLogSize(_count + 1);
				}

				ImGui::Spacing();

				if (ImGui::Button("Clear", ImVec2(_w1, _h)))
				{
					Clear();
				}

				ofxImGuiSurfing::AddSpacingSeparated();

				ImGui::Spacing();

				ImGui::BeginChild("Logs");
				{
					auto logs = mLog;

					//TODO:
					// macOS bug
					//for each (string l in logs)

					for (auto& l : logs)
					{
						ImGui::TextWrapped("%s", l.c_str());
					}
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}
	};
}
