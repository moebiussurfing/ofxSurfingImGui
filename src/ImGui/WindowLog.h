#pragma once

/*

	TODO:

	pass arg when add, not required index

	add tags manually. ie:
		OSC, MIDI,

	add filter search from ImGui Demo
	https://github.com/ocornut/imgui/issues/300

*/


#include "ofMain.h"

#include "ofxImGui.h"
//#include "ofHelpers.h"
//#include "ofxSurfingImGui.h"

namespace ofxImGuiSurfing
{
	/*

	USAGE:
	LOGGER LOG;

	log.add("[info] test i");
	log.add("[warning] test w");
	log.add("[error] test e");

	log.draw("Logger", ImGui::GetCursorPos(), {300, 250}, false);

	*/


	//----

	class SurfingLog
	{
	public:

		//--------------------------------------------------------------
		SurfingLog()
		{
			// Infinite mode
			this->clear();

			// Buffered mode
			//sizeLogBuffered = 20;
			queLogBuffered = std::deque<std::string>();
			this->clearBuffered();

			buildTagsDefault();

			params.add(bPause, bAutoScroll, bBuffered, sizeLogBuffered, bOptions);

			ofAddListener(params.parameterChangedE(), this, &SurfingLog::Changed_Params);

		};

		//--------------------------------------------------------------
		~SurfingLog()
		{
			this->clear();
			this->clearBuffered();

			ofRemoveListener(params.parameterChangedE(), this, &SurfingLog::Changed_Params);
		};


	private:

		ofParameter<bool> bPause{ "PAUSE" , false };
		ofParameter<bool> bAutoScroll{ "Auto Scroll" , true };
		ofParameter<bool> bBuffered{ "Limited" , false };
		ofParameter<int> sizeLogBuffered{ "Size", 20, 0, 100 };
		ofParameter<bool> bOptions{ "OPTIONS", false };

		void Changed_Params(ofAbstractParameter& e)
		{
			std::string n = e.getName();
			ofLogNotice("SurfingLog") << n << ": " << e;

			if (n == sizeLogBuffered.getName())
			{
				int diff = queLogBuffered.size() - sizeLogBuffered.get();
				if (diff > 0) {
					for (size_t i = 0; i < diff; i++)
					{
						queLogBuffered.pop_front();
					}
				}
			}
		}

	public:

		ofParameterGroup params{ "Logs" };

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
			AddTag({ "[INFO]", ofColor::white });
			AddTag({ "[VERBOSE]", ofColor::white });
			AddTag({ "[NOTICE]", ofColor::green });
			AddTag({ "[WARNING]", ofColor::yellow });
			AddTag({ "[ERROR]", ofColor::red });
		}

	public:

		// add custom tags passing name and color
		void AddTag(tagData tag)
		{
			tags.push_back(tag);
		}

		//--

	private:

		void addBuffered(string msg) {
			queLogBuffered.emplace_back(msg);
			if (sizeLogBuffered.get() < queLogBuffered.size())
				queLogBuffered.pop_front();

			this->scroll_to_bottom = true;
		}

		//void add(const char* fmt, ...) 
		void add(string msg, ...)
		{
			const char* fmt = msg.c_str();
			char buf[1024];
			va_list args;
			va_start(args, fmt);
			vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
			buf[IM_ARRAYSIZE(buf) - 1] = 0;
			va_end(args);
			buff.push_back(strdup(buf));

			this->scroll_to_bottom = true;
		};

		void clear() {
			for (int i = 0; i < buff.Size; i++)
				free(buff[i]);
			buff.clear();
		};

		void draw() {
			float p = 0;
			float w = ofxImGuiSurfing::getWidgetsWidth(1);
			float h = ofxImGuiSurfing::getWindowHeightFree();
			bool bBorder = true;//used?

			draw("Logger", ImGui::GetCursorPos(), { w - p, h - p }, bBorder);
		};

		void draw(const char* str_id, const ImVec2 pos, const ImVec2 size, const bool border)
		{
			ImGui::SetCursorPos(pos);

			ImGuiWindowFlags flags = ImGuiWindowFlags_None;

			// border not used?
			ImGui::BeginChild(str_id, size, border, flags);
			{
				for (int i = 0; i < buff.Size; i++) {
					const char* item = buff[i];

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

					if (has_color)
						ImGui::PushStyleColor(ImGuiCol_Text, color);

					//--

					// draw text
					ImGui::TextWrapped(item);
					//ImGui::TextUnformatted(item);

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

		void drawBuffered()
		{
			//TODO: 
			// must fix
			// auto fit
			// set buffer log size to fit the window
			if (sizeLogBuffered.get() == 0)
			{
				static int _pre = -1;
				float _h = 1.f * ofxImGuiSurfing::getWidgetsHeightUnit();
				float _h1 = ofxImGuiSurfing::getWidgetsHeightUnit();
				float _sph = ofxImGuiSurfing::GetFrameHeightWithSpacing();
				int _count = (ImGui::GetWindowHeight() - _h - _sph) / (float)_h1;
				if (_count != _pre) {
					_pre = _count;

					sizeLogBuffered = (_count + 1);
					//setLogBufferedSize(_count + 1);
				}
			}

			//--

			ImGui::BeginChild("LoggerBuffered");
			{
				//TODO:
				// macOS bug
				//for each (string l in logs)

				for (auto& m : queLogBuffered)
				{
					const char* item = m.c_str();

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

					if (has_color)
						ImGui::PushStyleColor(ImGuiCol_Text, color);

					//--

					ImGui::TextWrapped("%s", m.c_str());

					//--

					if (has_color)
						ImGui::PopStyleColor();

					//--

					//if (bAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
					//	ImGui::SetScrollHereY(1.0f);

					if (bAutoScroll)
					{
						if (this->scroll_to_bottom)
							ImGui::SetScrollHereY(1.0f);
						this->scroll_to_bottom = false;
					}
				}
			}
			ImGui::EndChild();

		};

	private:

		ImVector<char*> buff;
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

		////--------------------------------------------------------------
		//void setLogBufferedSize(int size) { sizeLogBuffered = size; };

		//--------------------------------------------------------------
		void clearBuffered() { queLogBuffered.clear(); };

	private:

		std::deque<std::string> queLogBuffered;

	public:

		//TODO:
		//--------------------------------------------------------------
		void Add(std::string msg, string nameTag)
		{
			// search if tag exists
			for (size_t i = 0; i < tags.size(); i++)
			{
				if (nameTag == tags[i].name) {
					Add(msg, (int)i);
					return;
				}
			}

			// tag do not exists
			// print as default
			ofLogWarning("SurfingLog") << "The tag " << nameTag << " do not exist. We will use the default tag.";
			Add(msg);
		}

		//--------------------------------------------------------------
		void Add(std::string msg, int itag = -1)
		{
			if (bPause) return;

			string s = "";
			string stag = "";

			////TODO: right align
			//switch (itag)
			//{
			//case -1:
			//case 0: stag = "   [INFO] "; break;
			//case 1: stag = "[VERBOSE] "; break;
			//case 2: stag = " [NOTICE] "; break;
			//case 3: stag = "[WARNING] "; break;
			//case 4: stag = "  [ERROR] "; break;
			//}

			if (itag < tags.size())
			{
				stag = tags[itag].name;
				s += stag;
				s += " ";
			}
			s += msg;

			//--

			if (!bBuffered) {
				add(s);
			}
			else {
				addBuffered(s);
			}
		};

	public:

		//--------------------------------------------------------------
		void drawImGui(ofParameter<bool>& bGui)
		{
			if (!bGui) return;

			std::string name = bGui.getName();
			ImGuiWindowFlags flags;
			flags = ImGuiWindowFlags_None;
			flags |= ImGuiWindowFlags_NoScrollbar;

			// Window shape
			{
				const int LOG_WINDOW_SIZE = 240;//minimal width
				float hmin = (bOptions.get() ? 190 : 130);//minimal height
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

			float _w = ofxImGuiSurfing::getWidgetsWidth(1);
			float _h = 1.25f * ofxImGuiSurfing::getWidgetsHeightUnit();
			float _spx = ofxImGuiSurfing::getWidgetsSpacingX();

			//--

			float _hh = ofxImGuiSurfing::getWidgetsHeightUnit();
			ofxImGuiSurfing::AddToggleRoundedButton(bOptions, 1.25 * _hh, true);
			ImGui::Spacing();
			if (bOptions)
			{
				float _w2 = ofxImGuiSurfing::getWidgetsWidth(2);
				ofxImGuiSurfing::AddBigToggle(bPause, ImVec2(_w2, _h), true, true);
				ImGui::SameLine();
				if (ImGui::Button("CLEAR", ImVec2(_w2, _h)))
				{
					this->clear();
					this->clearBuffered();
				}
				ofxImGuiSurfing::AddSpacing();
				ofxImGuiSurfing::AddToggleRoundedButton(bAutoScroll, _hh, true);

				ofxImGuiSurfing::AddCheckBox(bBuffered);
				//ofxImGuiSurfing::AddToggleRoundedButton(bBuffered, _hh, true);
				if (bBuffered)
				{
					ofxImGuiSurfing::SameLine();

					//TODO: not working
					//ImGui::DragInt("Size", &sizeLogBuffered, 1, 100);
					//ofxImGuiSurfing::AddParameter(sizeLogBuffered);
					// fix
					{
						ImGui::PushItemWidth(90);
						string name = sizeLogBuffered.getName();
						auto tmpRefi = sizeLogBuffered.get();
						string n = "##STEPPERint" + name;// +ofToString(1);
						const ImU32 u32_one = 1;
						ImGui::PushID(n.c_str());
						if (ImGui::InputScalar(sizeLogBuffered.getName().c_str(), ImGuiDataType_S32, (int*)&tmpRefi, &u32_one, NULL, "%d"))
						{
							tmpRefi = ofClamp(tmpRefi, sizeLogBuffered.getMin(), sizeLogBuffered.getMax());
							sizeLogBuffered.set(tmpRefi);
						}
						ImGui::PopID();
						ImGui::PopItemWidth();
					}

				}

				//string s;
				//if (bBuffered)s = "Limited Size";
				//else s = "Infinite Size";
				//ofxImGuiSurfing::AddTooltip(s);
			}
			//--

			ofxImGuiSurfing::AddSpacingSeparated();
			ofxImGuiSurfing::AddSpacing();

			//--

			if (!bBuffered)
			{
				draw();
			}
			else
			{
				drawBuffered();
			}

			//--

			ImGui::End();
		}
	};

}




//---




/*
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
*/

//----


// TODO:
// Save log file to disk
// from ofxMyUtil from https://github.com/Iwanaka

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