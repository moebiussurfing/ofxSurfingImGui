#pragma once

/*

	TODO:

	add tags manually. ie:
		OSC, MIDI, 
	
	check if intuitive direction
	
	add filter search from ImGui Demo
	https://github.com/ocornut/imgui/issues/300

*/


#include "ofMain.h"

#include "ofxImGui.h"
//#include "ofxSurfingImGui.h"

namespace ofxImGuiSurfing
{
	//TODO:
	//ofLogLevel l = OF_LOG_VERBOSE;
	//ofSetLogLevel(l);

	//TODO: add colors
	//enum IM_GUI_LOG_STYLE
	//{
	//	IM_GUI_LOG_STYLE_0 = 0,
	//	IM_GUI_LOG_STYLE_1,
	//	IM_GUI_LOG_STYLE_2
	//};
	//IM_GUI_LOG_STYLE style = IM_GUI_LOG_STYLE_0

	class SurfingLog
	{
	public:

		//--------------------------------------------------------------
		SurfingLog() {
			this->clear();
		};

		//--------------------------------------------------------------
		~SurfingLog() {
			this->clear();
		};

		////--------------------------------------------------------------
		//SurfingLog() : mLogSize(20), mLog(std::deque<std::string>()) {
		//	this->clear();
		//}

		////TODO:
		//// create styles
		////std::map<std::string, ofLogLevel> m{ {"CPU", 10}, {"GPU", 15}, {"RAM", 20} };
		//struct logTag
		//{
		//	string tag;
		//	ofColor color;
		//};

		//----

	private:

		/*

		Usage:
		Logger log;

		log.add("[info] test i");
		log.add("[warning] test w");
		log.add("[error] test e");

		log.draw("Logger", ImGui::GetCursorPos(), {300, 250}, false);

		*/

		void add(const char* fmt, ...) {
			char	buf[1024];
			va_list args;
			va_start(args, fmt);
			vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
			buf[IM_ARRAYSIZE(buf) - 1] = 0;
			va_end(args);
			buff.push_back(strdup(buf));

			this->scroll_to_bottom = true;
		}

		void clear() {
			for (int i = 0; i < buff.Size; i++)
				free(buff[i]);
			buff.clear();
		}

		void draw(const char* str_id, const ImVec2 pos, const ImVec2 size, const bool border)
		{
			//border not used

			ImGui::SetCursorPos(pos);

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
			//flags |= ImGuiWindowFlags_NoScrollbar;

			ImGui::BeginChild(str_id, size, border, flags);
			{
				for (int i = 0; i < buff.Size; i++) {
					const char* item = buff[i];

					ImVec4 color;
					bool has_color = false;

					ImGuiStyle* style = &ImGui::GetStyle();
					const ImVec4 c = style->Colors[ImGuiCol_Text];
					ofFloatColor c1 = ofColor::green;
					ofFloatColor c2 = ofColor::yellow;
					ofFloatColor c3 = ofColor::red;
					ofFloatColor c4 = ofColor::orange;

					if (strstr(item, "[INFO]")) {
						color = c;
						has_color = true;
					}

					else if (strstr(item, "[VERBOSE]")) {
						color = c;
						has_color = true;
					}

					else if (strstr(item, "[NOTICE]")) {
						color = ImVec4(c1);
						has_color = true;
					}

					else if (strstr(item, "[WARNING]")) {
						color = ImVec4(c2);
						has_color = true;
					}

					else if (strstr(item, "[ERROR]")) {
						color = ImVec4(c3);
						has_color = true;
					}

					else if (strncmp(item, "# ", 2) == 0) {
						color = ImVec4(c4);
						has_color = true;
					}

					if (has_color)
						ImGui::PushStyleColor(ImGuiCol_Text, color);

					//--

					//ImGui::TextUnformatted(item);
					ImGui::TextWrapped(item);

					//--

					if (has_color)
						ImGui::PopStyleColor();
				}

				//--

				if (bAutoScroll)
				{
					if (this->scroll_to_bottom)
						ImGui::SetScrollHereY(1.0f);
					this->scroll_to_bottom = false;
				}

				//ImGui::SetCursorPos({ pos.x + size.x - 66, pos.x + size.y - 36 });
				//if (ImGui::Button("Clear", { 50, 20 }))
				//	this->clear();
			}
			ImGui::EndChild();
		}

	private:

		ImVector<char*> buff;
		bool scroll_to_bottom;

		static char* strdup(const char* s) {
			IM_ASSERT(s);
			size_t len = strlen(s) + 1;
			void* buf = malloc(len);
			IM_ASSERT(buf);
			return (char*)memcpy(buf, (const void*)s, len);
		}

		ofParameter<bool> bPause{ "PAUSE" , false };
		ofParameter<bool> bAutoScroll{ "Auto Scroll" , true };

		//--

	//public:

		////--------------------------------------------------------------
		//void SetLogSize(unsigned long size) { mLogSize = size; }

		////--------------------------------------------------------------
		//void Clear() { mLog.clear(); }

	//private:

		//unsigned long mLogSize;
		//std::deque<std::string> mLog;

	//public:

		//ofParameter<bool> bGui{"Show", true};

		//--------------------------------------------------------------
		//void AddTextToFile(std::string str, std::string path, bool append = false, bool withTimeStamp = false);

	public:

		//TODO:
		//--------------------------------------------------------------
		void Add(std::string msg, int tag = -1)
		{
			if (bPause) return;

			string s = "";
			string stag = "";

			//TODO:
			switch (tag)
			{
			case -1:
			case 0: stag = "   [INFO] "; break;
			case 1: stag = "[VERBOSE] "; break;
			case 2: stag = " [NOTICE] "; break;
			case 3: stag = "[WARNING] "; break;
			case 4: stag = "  [ERROR] "; break;
			}

			s += stag;
			s += " ";
			s += msg;

			add(s.c_str());

			//--

			//mLog.emplace_back(msg);
			//if (mLogSize < mLog.size()) mLog.pop_front();
		}

	public:

		//--------------------------------------------------------------
		void drawImGui(ofParameter<bool>& bGui)
		{
			if (!bGui) return;

			std::string name = bGui.getName();

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
			flags |= ImGuiWindowFlags_NoScrollbar;
			//flags |= ImGuiWindowFlags_;

			// window shape
			{
				ImGuiCond cond = ImGuiCond_FirstUseEver;
				const int LOG_WINDOW_SIZE = 240;

				// app window
				float w = ofGetWidth();
				float h = ofGetHeight();

				ImGui::SetNextWindowPos(ImVec2(w - LOG_WINDOW_SIZE - 10, 20), cond);
				ImGui::SetNextWindowSize(ImVec2(LOG_WINDOW_SIZE, h - 100), cond);

				ImVec2 size_min = ImVec2(LOG_WINDOW_SIZE, LOG_WINDOW_SIZE);
				ImVec2 size_max = ImVec2(FLT_MAX, FLT_MAX);
				ImGui::SetNextWindowSizeConstraints(size_min, size_max);
			}

			//--

			if (!ImGui::Begin(name.c_str(), (bool*)&bGui.get(), flags))
			{
				ImGui::End();
				return;
			}

			float _w = ofxImGuiSurfing::getWidgetsWidth(1);
			float _h = 1.25f * ofxImGuiSurfing::getWidgetsHeightUnit();
			float _spx = ofxImGuiSurfing::getWidgetsSpacingX();

			/*
			{
				static int _pre = -1;

				float hl = ofxImGuiSurfing::getWidgetsHeightUnit();
				float _sph = ofxImGuiSurfing::GetFrameHeightWithSpacing();

				// auto fit
				int _count = (ImGui::GetWindowHeight() - _h - _sph) / (float)hl;
				if (_count != _pre) {
					_pre = _count;
					SetLogSize(_count + 1);
				}

				ofxImGuiSurfing::AddSpacing();
				if (ImGui::Button("CLEAR", ImVec2(_w, _h)))
				{
					Clear();
				}

				static bool bAutoScroll = false;
				ImGui::Checkbox("Auto Scroll", &bAutoScroll);

				ofxImGuiSurfing::AddSpacingSeparated();
				ofxImGuiSurfing::AddSpacing();
			}
			*/

			ofxImGuiSurfing::AddSpacing();

			ofxImGuiSurfing::AddBigToggle(bPause, ImVec2(_w * 0.25, _h), true, true);
			
			ImGui::SameLine();

			if (ImGui::Button("CLEAR", ImVec2(_w * 0.75 - _spx, _h)))
			{
				this->clear();
			}
			ofxImGuiSurfing::AddSpacing();

			float _hh = ofxImGuiSurfing::getWidgetsHeightUnit();
			ofxImGuiSurfing::AddToggleRoundedButton(bAutoScroll, ImVec2(1.15f * _hh, 1.15f * (2 / 3.f) * _hh), true);

			//ImGui::Checkbox("Auto Scroll", &bAutoScroll);

			ofxImGuiSurfing::AddSpacingSeparated();
			ofxImGuiSurfing::AddSpacing();

			//--

			bool bBorder = true;
			float p = 0;
			float w = ofxImGuiSurfing::getWidgetsWidth(1);
			float h = ofxImGuiSurfing::getWindowHeightFree();
			draw("Logger", ImGui::GetCursorPos(), { w - p, h - p }, bBorder);

			//draw("Logger", ImGui::GetCursorPos(), { 300, 250 }, bBorder);

			//--

			/*
			ImGui::BeginChild("Logs");
			{
				auto logs = mLog;

				//TODO:
				// macOS bug
				//for each (string l in logs)

				for (auto& l : logs)
				{
					ImGui::TextWrapped("%s", l.c_str());

					if (bAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
						ImGui::SetScrollHereY(1.0f);
				}
			}
			ImGui::EndChild();
			*/

			ImGui::End();
		}
	};
}



//----


// TODO:
// Save log file to disk
// from ofxMyUtil from https://github.com/Iwanaka
//
// 
// 

////--------------------------------------------------------------
//void SurfingLog::AddTextToFile(std::string str, std::string path, bool append, bool withTimeStamp) {
//	AddText(str);
//	if (withTimeStamp) str = ofGetTimestampString() + " " + str;
//	TextToFile(path, str, append);
//}

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