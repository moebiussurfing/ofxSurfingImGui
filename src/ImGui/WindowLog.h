#pragma once

/*
	This code is mainly based on the snippet:
	https://github.com/ocornut/imgui/issues/5796#issuecomment-1288128069
	from @karl0st: https://github.com/karl0st
*/

/*

	TODO:

	add timestamp. copy style from protokol

	improve implemented filter.
		could be a little slow bc it handles strings.
		for some situations we should replace by:

	filter search from ImGui Demo
	https://github.com/ocornut/imgui/issues/300
	Better from the ImGui Demo

*/

//----

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_stdlib.h"

//TODO: some widget fails..
//#include "ofHelpers.h"
//#include "ofxSurfingImGui.h"

namespace ofxImGuiSurfing
{
	class SurfingLog
	{
		// columns formatting
	private:

		const int maxTagLength = 8; // first or tag column width. to make tags right aligned.
		const string strSpacer = "   "; // space between tags column and the second column with the message .
		const string strSpacer2 = " ";//not required bc alignment adds some starting spaces
	public:

		ofParameterGroup params{ "Log Settings" };//settings are handled by the parent class. will be serialized on exit and loaded on start.

	private:

		ofParameter<bool> bOptions{ "OPTIONS", false };
		ofParameter<bool> bLimitedBuffered{ "Limited" , false };
		ofParameter<bool> bPause{ "PAUSE" , false };
		ofParameter<bool> bTight{ "Tight" , true };
		ofParameter<bool> bOneLine{ "OneLine" , false };
		ofParameter<bool> bAutoFit{ "AutoFit" , true };
		ofParameter<int> sizeLimitedBuffered{ "AmountLines", 20, 1, 100 };
		ofParameter<bool> bAutoScroll{ "AutoScroll" , true };
		ofParameter<bool> bFilter{ "Filter", true };
		ofParameter<bool> bTimeStamp{ "TimeStamp", false };
		ofParameter<string> strSearch{ "Search", "" };

		int amountLinesCurr = 0;

	public:

		//--------------------------------------------------------------
		SurfingLog()
		{
			// Infinite mode
			this->clearUnlimited();

			// Buffered mode
			//sizeLimitedBuffered = 20;
			bufferBufferedLimited = std::deque<std::string>();
			this->clearBuffered();

			buildTagsDefault();

			params.add(bPause, bTight, bOneLine, bAutoScroll, bLimitedBuffered, sizeLimitedBuffered, bOptions, bAutoFit, bFilter, strSearch, bTimeStamp);

			ofAddListener(params.parameterChangedE(), this, &SurfingLog::Changed_Params);
		};

		//--------------------------------------------------------------
		~SurfingLog()
		{
			this->clearUnlimited();
			this->clearBuffered();

			ofRemoveListener(params.parameterChangedE(), this, &SurfingLog::Changed_Params);
		};


	private:

		void Changed_Params(ofAbstractParameter& e)
		{
			std::string n = e.getName();
			ofLogNotice("SurfingLog") << n << ": " << e;

			if (n == sizeLimitedBuffered.getName())
			{
				int diff = bufferBufferedLimited.size() - sizeLimitedBuffered.get();
				// reduce resize
				if (diff > 0) {
					for (size_t i = 0; i < diff; i++)
					{
						bufferBufferedLimited.pop_front();
					}
				}
			}
		};

		//----

		// Infinite mode

	public:

		struct tagData
		{
			string name;
			ofColor color;
		};

	private:

		vector<tagData> tags;

		void buildTagsDefault()
		{
			// to be used when log a message without tag.
			// will use common text color
			strEmptyTag = "";
			for (size_t i = 0; i < maxTagLength; i++)
			{
				strEmptyTag += " ";
			}

			AddTag({ "INFO", ofColor::white });
			AddTag({ "VERBOSE", ofColor::white });
			AddTag({ "NOTICE", ofColor::green });
			AddTag({ "WARNING", ofColor::yellow });
			AddTag({ "ERROR", ofColor::red });
		}

		string strEmptyTag = "";

		string strAlign(string s) const
		{
			//TODO:
			// to make right aligned
			int l = s.length();
			int diff = maxTagLength - l;
			if (diff > 0) {
				string spre = "";
				for (size_t i = 0; i < diff; i++)
				{
					spre += " ";
				}
				s = spre + s;
			}

			//s += " ";//end spacing

			return s;
		};

	public:

		// add custom tags passing name and color
		void AddTag(tagData tag)
		{
			////TODO:
			//// to make right aligned
			//const int maxTagLength = 10;
			//int l = tag.name.length();
			//int diff = maxTagLength - l;
			//if (diff > 0) {
			//	string spre = "";
			//	for (size_t i = 0; i < diff; i++)
			//	{
			//		spre += " ";
			//	}
			//	tag.name = spre + tag.name;
			//}

			tag.name = strAlign(tag.name);

			tags.push_back(tag);
		};

		//--

		void Clear() {
			this->clearUnlimited();
			this->clearBuffered();
			//this->ClearFilter();
		};

	private:

		void addBuffered(string msg)
		{
			bufferBufferedLimited.emplace_back(msg);
			if (sizeLimitedBuffered.get() < bufferBufferedLimited.size())
			{
				bufferBufferedLimited.pop_front();
			}

			if (bAutoScroll)
				this->scroll_to_bottom = true;
		};

		void addUnlimited(string msg, ...)
		{
			//void add(const char* fmt, ...) 
			const char* fmt = msg.c_str();
			char buf[1024];
			va_list args;
			va_start(args, fmt);
			vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
			buf[IM_ARRAYSIZE(buf) - 1] = 0;
			va_end(args);
			bufferUnlimited.push_back(strdup(buf));

			if (bAutoScroll)
				this->scroll_to_bottom = true;
		};

		void clearUnlimited() {
			for (int i = 0; i < bufferUnlimited.Size; i++)
				free(bufferUnlimited[i]);
			bufferUnlimited.clear();
		};

		void drawUnlimited() {
			float p = 0;//padding
			float w = ofxImGuiSurfing::getWidgetsWidth(1);
			float h = ofxImGuiSurfing::getWindowHeightFree();
			bool bBorder = true;//used?

			drawUnlimited("Logger", ImGui::GetCursorPos(), { w - p, h - p }, bBorder);
		};

		void drawUnlimited(const char* str_id, const ImVec2 pos, const ImVec2 size, const bool border)
		{
			ImGui::SetCursorPos(pos);

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;

			// border not used?
			ImGui::BeginChild(str_id, size, border, flags);
			{
				for (int i = 0; i < bufferUnlimited.Size; i++)
				{
					const char* item = bufferUnlimited[i];
					//char* item = bufferUnlimited[i];

					//--

					// filter
					if (bFilter)
					{
						bool bFound = true;
						string s1 = strSearch.get();
						string s2(item);
						if (s1 != "")
						{
							bFound = ofIsStringInString(s2, s1);
						}
						if (!bFound) continue; // skip if the filter keyword is not found into the text line!
					}

					//--

					ImVec4 color;
					bool has_color = false;

					for (auto t : tags)
					{
						if (strstr(item, t.name.c_str()))
						{
							color = t.color;
							has_color = true;
						}
					}

					if (!has_color)
					{
						string s = strEmptyTag + string(item);
						item = s.c_str();
					}

					if (has_color)
						ImGui::PushStyleColor(ImGuiCol_Text, color);

					//--

					// draw text
					drawText(item);

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
			}
			ImGui::EndChild();
		};

		void drawBufferedLimited()
		{
			ImGui::BeginChild("LoggerBuffered");
			{
				// force log size to current window size
				if (bAutoFit)
				{
					ImGuiContext& g = *GImGui;
					float h = g.FontSize;
					if (!bTight) h += g.Style.FramePadding.y;
					float hFree = ofxImGuiSurfing::getWindowContentHeight();
					int amountLines = hFree / h;
					sizeLimitedBuffered = amountLines;
				}

				//--

				for (auto& m : bufferBufferedLimited)
				{
					// macOS bug
					//for each (string l in logs)

					const char* item = m.c_str();

					//--

					// filter
					if (bFilter)
					{
						bool bFound = true;
						string s1 = strSearch.get();
						if (s1 != "")
						{
							bFound = ofIsStringInString(m, s1);
						}
						if (!bFound) continue; // skip!
					}

					//--

					ImVec4 color;
					bool has_color = false;

					for (auto t : tags)
					{
						if (strstr(item, t.name.c_str()))
						{
							color = t.color;
							has_color = true;
						}
					}

					if (!has_color)
					{
						string s = strEmptyTag + m;
						item = s.c_str();
					}

					if (has_color)
						ImGui::PushStyleColor(ImGuiCol_Text, color);

					//--

					// draw text
					drawText(m.c_str());

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
			}
			ImGui::EndChild();
		};

	private:

		ImVector<char*> bufferUnlimited;
		bool scroll_to_bottom;

		static char* strdup(const char* s) {
			IM_ASSERT(s);
			size_t len = strlen(s) + 1;
			void* buf = malloc(len);
			IM_ASSERT(buf);
			return (char*)memcpy(buf, (const void*)s, len);
		};

		//--

		// Buffered mode

	public:

		//--------------------------------------------------------------
		//void setLogBufferedSize(int size) { sizeLimitedBuffered = size; };

		//--------------------------------------------------------------
		void clearBuffered() { bufferBufferedLimited.clear(); };

	private:

		std::deque<std::string> bufferBufferedLimited;

		//----

	public:

		//TODO:
		//--------------------------------------------------------------
		void Add(std::string msg, string nameTag)
		{
			// A. search if tag exists
			for (size_t i = 0; i < tags.size(); i++)
			{
				nameTag = strAlign(nameTag);

				if (nameTag == tags[i].name) {
					Add(msg, (int)i);
					return;
				}
			}

			// B. tag do not exists
			// print as default
			ofLogWarning("SurfingLog") << "The tag " << nameTag << " do not exist. We will use the default tag.";
			Add(msg);
		};

		//--------------------------------------------------------------
		void Add(std::string msg, int itag = -1)//all add method will pass through this method..
		{
			if (bPause) return;

			string s = "";

			// timestamp
			if (bTimeStamp)
			{
				string timeFormat = "%H:%M:%S ";
				//string timeFormat = "%H:%M:%S.%i ";//Protokol style
				//string timeFormat = "[%H:%M:%S]";
				//string timeFormat = "%H:%M:%S";
				//string timeFormat = "%H-%M-%S-%i";//+ms
				//string timeFormat = "%Y-%m-%d-%H-%M-%S-%i";//+date
				s += ofGetTimestampString(timeFormat);
				//s += strSpacer2;//not required bc alignment adds some starting spaces
			}

			// not passed any tag
			if (itag == -1)
			{
				s += strEmptyTag;
				s += strSpacer;
			}
			// a tag has been passed
			else
			{
				if (itag < tags.size())
				{
					s += tags[itag].name;
					s += strSpacer;
				}
			}

			// messages
			s += msg;

			//--

			if (!bLimitedBuffered) {
				addUnlimited(s);
			}
			else {
				addBuffered(s);
			}
		};

		//----

	public:

		//--------------------------------------------------------------
		void drawImGui(ofParameter<bool>& bGui)
		{
			if (!bGui) return;

			// calculate how many lines are being drawn
			// that depends on modes or settings
			if (bLimitedBuffered) {
				if (bAutoFit) amountLinesCurr = bufferBufferedLimited.size();
				else amountLinesCurr = sizeLimitedBuffered.get();
			}
			else {
				amountLinesCurr = bufferUnlimited.size();
			}

			//--

			std::string name = bGui.getName();
			ImGuiWindowFlags flags;
			flags = ImGuiWindowFlags_None;
			flags |= ImGuiWindowFlags_NoScrollbar;

			string s;

			// Window shape
			{
				const int LOG_WINDOW_SIZE = 240;//minimal width
				float hmin = (bOptions.get() ? 200 : 130);//minimal height
				ImGuiCond cond = ImGuiCond_FirstUseEver;

				// app window
				float w = ofGetWidth();
				float h = ofGetHeight();
				ImGui::SetNextWindowPos(ImVec2(w - LOG_WINDOW_SIZE - 10, 20), cond);
				ImGui::SetNextWindowSize(ImVec2(LOG_WINDOW_SIZE, h - 100), cond);

				// constraints
				ImVec2 size_min = ImVec2(LOG_WINDOW_SIZE, hmin);
				ImVec2 size_max = ImVec2(FLT_MAX, FLT_MAX);
				ImGui::SetNextWindowSizeConstraints(size_min, size_max);
			}

			//--

			if (!ImGui::Begin(name.c_str(), (bool*)&bGui.get(), flags))
			{
				ImGui::End();
				return;
			}

			ofxImGuiSurfing::AddSpacing();

			float _hh = ofxImGuiSurfing::getWidgetsHeightUnit();
			float _h = 1.5f * ofxImGuiSurfing::getWidgetsHeightUnit();
			float _w = ofxImGuiSurfing::getWidgetsWidth(1);
			//float _spx = ofxImGuiSurfing::getWidgetsSpacingX();

			//--

			// pause
			float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);
			ofxImGuiSurfing::AddBigToggle(bPause, ImVec2(_w2, _h), true, true);
			ImGui::SameLine();

			// clear
			if (ImGui::Button("CLEAR", ImVec2(_w2, _h)))
			{
				Clear();
			}
			ofxImGuiSurfing::AddSpacing();

			ofxImGuiSurfing::AddToggleRoundedButton(bOptions, 1.25 * _hh, true);
			ImGui::Spacing();

			//--

			if (bOptions)
			{
				//--

				// Modes toggle: 
				// LIMITED or UNLIMITED

				ofxImGuiSurfing::AddBigToggleNamed(bLimitedBuffered, 140, 0.65 * _h, "LIMITED", "UNLIMITED");
				//ofxImGuiSurfing::AddBigToggle(bLimitedBuffered, 50, _hh, true);
				//ofxImGuiSurfing::AddToggleRoundedButton(bLimitedBuffered, _hh, true);
				//ofxImGuiSurfing::AddCheckBox(bLimitedBuffered);

				// tooltip
				{
					s = (bLimitedBuffered ? "Buffer size \nof lines is limited" : "Buffer size \nof lines is \nunlimited.");
					if (bLimitedBuffered) s += "\n\nYou can set AutoFit \nor to specify an \namount manually.";
					s += "\n\nAmountLines: \n" + ofToString(amountLinesCurr);
					ofxImGuiSurfing::AddTooltip2(s);
				}

				// lines counter
				{
					ImGui::SameLine();
					string s = ofToString(amountLinesCurr);
					ImGui::Text(s.c_str());
				}

				//--

				ImGui::SameLine();
				bool bCopy = ImGui::Button("Copy");
				s = "Copy Log to Clipboard";
				ofxImGuiSurfing::AddTooltip2(s);
				if (bCopy) ImGui::LogToClipboard();

				//--

				ImGui::SameLine();
				bool bExport = ImGui::Button("Export");
				s = "Export Log to \na file in data/ folder";
				ofxImGuiSurfing::AddTooltip2(s);
				if (bExport) exportLogToFile();

				//--

				// filter

				ImGui::SameLine();
				ofxImGuiSurfing::AddCheckBox(bFilter);
				{
					s = bFilter ? "Write your pattern\nto filter log lines" : "Disabled";
					ofxImGuiSurfing::AddTooltip2(s);
				}
				if (bFilter)
				{
					ImGui::SameLine();

					//TODO: take from guiManager
					//ofxImGuiSurfing::blink

					static bool bReturn;
					auto& tmpRef = strSearch.get();
					float _w = 100;
					s = tmpRef.c_str();
					ImGui::PushItemWidth(_w);
					bReturn = ImGui::InputText("##Filter", &s);
					if (bReturn)
					{
						ofLogNotice("ofxSurfingImGui") << "InputText:" << s.c_str();
						strSearch.set(s);
					}
					ImGui::PopItemWidth();
				}

				//--

				//ofxImGuiSurfing::SameLine();

				//--

				{
					//ofxImGuiSurfing::SameLine();
					ofxImGuiSurfing::AddCheckBox(bTimeStamp);
				}

				// limited buffered
				if (bLimitedBuffered)
				{
					ofxImGuiSurfing::SameLine();
					ofxImGuiSurfing::AddCheckBox(bAutoFit);
					s = "Resize buffer to fit window size \nas amount of expected text lines.";
					//s += "\nAmount Lines: " + ofToString(bufferBufferedLimited.size());
					ofxImGuiSurfing::AddTooltip2(s);
					if (!bAutoFit)
					{
						ofxImGuiSurfing::SameLine();

						//TODO: not working
						//ImGui::DragInt("Size", &sizeLimitedBuffered, 1, 100);
						//ofxImGuiSurfing::AddParameter(sizeLimitedBuffered);
						// fix
						{
							ImGui::PushItemWidth(90);
							string name = sizeLimitedBuffered.getName();
							auto tmpRefi = sizeLimitedBuffered.get();
							string n = "##STEPPERint" + name;// +ofToString(1);
							const ImU32 u32_one = 1;
							ImGui::PushID(n.c_str());
							if (ImGui::InputScalar(sizeLimitedBuffered.getName().c_str(), ImGuiDataType_S32, (int*)&tmpRefi, &u32_one, NULL, "%d"))
							{
								tmpRefi = ofClamp(tmpRefi, sizeLimitedBuffered.getMin(), sizeLimitedBuffered.getMax());
								sizeLimitedBuffered.set(tmpRefi);
							}
							ImGui::PopID();
							ImGui::PopItemWidth();
						}
					}
					//else {
					//	ofxImGuiSurfing::SameLine();
					//	string s = ofToString(sizeLimitedBuffered.get());
					//	ImGui::Text(s.c_str());
					//}
				}
				else //unlimited
				{
					ofxImGuiSurfing::SameLine();
					ofxImGuiSurfing::AddCheckBox(bAutoScroll);
					//ImGui::Dummy({ 0,10 });
					//ofxImGuiSurfing::AddToggleRoundedButton(bAutoScroll, _hh, true);
				}

				ofxImGuiSurfing::SameLine();
				ofxImGuiSurfing::AddCheckBox(bTight);
				s = "Compact interline height";
				ofxImGuiSurfing::AddTooltip2(s);

				ofxImGuiSurfing::SameLine();
				ofxImGuiSurfing::AddCheckBox(bOneLine);
				s = (bOneLine ? "Forces one line only.\nAvoids wrapping format." : "Allows multi-line wrapping \nto window width.");
				ofxImGuiSurfing::AddTooltip2(s);

				//string s;
				//if (bLimitedBuffered)s = "Limited Size";
				//else s = "Infinite Size";
				//ofxImGuiSurfing::AddTooltip2(s);
			}

			//--

			ofxImGuiSurfing::AddSpacingSeparated();
			ofxImGuiSurfing::AddSpacing();

			//--

			if (!bLimitedBuffered)
			{
				drawUnlimited();
			}
			else
			{
				drawBufferedLimited();
			}

			//--

			ImGui::End();
		}

		//---

		// TODO:
		// Save log file to disk

		//#include <fstream>
		//#include <string>
		//#include <iostream>

		void exportLogToFile(string path = "")//pass path folder. the name will be auto settled by timestamp
		{
			ofLogNotice("SurfingLog") << "exportLogToFile:" << path;

			if (path == "") path = ofToDataPath("", true);
			path += "\\logs";//add subfolder
			ofxSurfingHelpers::CheckFolder(path);//create folder if required

			string timeFormat = "%Y-%m-%d__%H-%M-%S";//+date/time

			string n = "";//filename with ext
			string s = "";//path complete 

			//filename
			n += "LogSurfing___";
			n += ofGetTimestampString(timeFormat);
			n += ".txt";

			s = path + "\\" + n;

			// A. using ImGui internal methods
			ImGui::LogToFile(-1, s.c_str());

			// log that action too!
			this->Add("LOG FILE:");
			this->Add(n);
			this->Add("SAVED TO:");
			this->Add(path);

			//TODO: could auto open the log file by using system commands

			//--

			//TODO:
			//fails
			//// B. using custom methods
			//string text = "";

			//if (!bLimitedBuffered)
			//{
			//	for (int i = 0; i < bufferUnlimited.Size; i++)
			//	{
			//		const char* item = bufferUnlimited[i];
			//		string _s = string(item);
			//		text += _s;
			//		text += "\n";
			//	}
			//}
			//else
			//{
			//	for (auto& m : bufferBufferedLimited)
			//	{
			//		text += m;
			//		text += "\n";
			//	}
			//}

			//cout << endl << text << endl;

			//std::cin >> text;

			//std::ofstream out(s.c_str());
			//out << text;
			//out.close();
		};

		//--

	private:

		void drawText(const char* item) {
			if (bTight) ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			if (bOneLine) ImGui::TextUnformatted(item);
			else ImGui::TextWrapped(item);
			if (bTight) ImGui::PopStyleVar();
		}

	};//class

}//namespace
