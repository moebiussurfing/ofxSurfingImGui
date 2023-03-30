#include "imgui_tricks.hpp"

namespace ImTricks {

	namespace Animations {

		int FastLerpInt(const char* identifier, bool state, int min, int max, int speed) {

			static std::map<const char*, int> valuesMapInt;
			auto value = valuesMapInt.find(identifier);

			if (value == valuesMapInt.end()) {
				valuesMapInt.insert({ identifier,  0 });
				value = valuesMapInt.find(identifier);
			}

			const float frameRateSpeed = speed * (1.f - ImGui::GetIO().DeltaTime);

			if (state) {
				if (value->second < max)
					value->second += frameRateSpeed;
			}
			else {
				if (value->second > min)
					value->second -= frameRateSpeed;
			}

			value->second = std::clamp(value->second, min, max);

			return value->second;
		}

		float FastLerpFloat(const char* identifier, bool state, float min, float max, float speed) {

			static std::map<const char*, float> valuesMapFloat;
			auto value = valuesMapFloat.find(identifier);

			if (value == valuesMapFloat.end()) {
				valuesMapFloat.insert({ identifier, 0.f });
				value = valuesMapFloat.find(identifier);
			}

			const float frameRateSpeed = speed * (1.f - ImGui::GetIO().DeltaTime);

			if (state) {
				if (value->second < max)
					value->second += frameRateSpeed;
			}
			else {
				if (value->second > min)
					value->second -= frameRateSpeed;
			}

			value->second = std::clamp(value->second, min, max);

			return value->second;
		}

		ImColor FastColorLerp(ImColor start, ImColor end, float stage)
		{
			ImVec4 lerp = ImLerp(
				ImVec4(start.Value.x, start.Value.y, start.Value.z, start.Value.w),
				ImVec4(end.Value.x, end.Value.y, end.Value.z, end.Value.w),
				stage);

			return ImGui::ColorConvertFloat4ToU32(lerp);
		}
	}

	//----

	namespace NotifyManager {

		std::vector<NotifyStruct> notifies;

		float offsetx = 0;

		const int wmaxDef = 0;//flick bug
		//const int wmaxDef = 200;
		float widthMax_ = wmaxDef;//getting max width o all bubbles. starting pad

		//TODO: add editor to save settings
		// hardcoded
#ifndef USE_IM_GUI_TRICKS_PARAMS
		int indexFont = 0;//default
		int duration = 3000;
		int padx = 20;//pad to right x border 
		int pady = 20;//pad to bottom y border 
		int padxInner = 15;//text in
		int padyInner = 15;//text in
		int ySpacing = 15;//spacing between bubbles
		float round = 3.f;//rounded bubble if != 0.
		bool bUseColorMark = true;
		float mkRounded = 1.f;//rounded left mark
		int mkWidth = 5.f;//width colored left mark
		int mkPad = 0.f;//padding left mark
		bool bAlignRight = true;
		bool bRightColorMark = false;
		bool bUseTagColor = true;
		bool bBg = true;
#else
		ofParameter<bool> bGui{ "Debug Notifier", false };
		
		// These init value will be overwritten by calling setup()!
		ofParameter<int> indexFont{ "Font", 1, 0, 3 };
		ofParameter<int> duration{ "Duration", 3000, 300, 10000 };
		ofParameter<int> padx{ "Pad x", 20, -50, 100 };//pad to right x border 
		ofParameter<int> pady{ "Pad y", 20, -50, 100 };//pad to bottom y border 
		ofParameter<int> padxInner{ "Inner Pad x", 15, 0, 100 };//text in
		ofParameter<int> padyInner{ "Inner Pad y", 15, 0, 100 };//text in
		ofParameter<int> ySpacing{ "Spacing y", 5, -50, 100 };//spacing between bubbles
		ofParameter<float> round{ "Round", 3.f, 0, 100 };//rounded bubble if != 0.
		ofParameter<bool> bUseColorMark{ "Color Mark", true };
		ofParameter<bool> bRightColorMark{ "CM Right", false };
		ofParameter<float> mkRounded{ "CM Round", 1.f, 0, 100 };//rounded left mark
		ofParameter<int> mkWidth{ "CM Width",5, 1, 200 };//width colored left mark
		ofParameter<int> mkPad{ "CM Pad", 0, 0, 200 };//padding left mark
		ofParameter<bool> bAlignRight{ "Align Right",true };
		ofParameter<bool> bUseTagColor{ "Tag Color", true };
		ofParameter<bool> bBg{ "Bg", true };

		ofParameterGroup params{ "surfingNotifier", bGui, indexFont, duration, padx,pady,padxInner, padyInner, ySpacing, round, bUseColorMark, mkRounded , mkWidth, mkPad, bAlignRight, bRightColorMark, bUseTagColor, bBg };
#endif

		void doReset()
		{
			widthMax_ = 100;//starting pad

			indexFont = 1;

			duration = 3000;
			padx = 5;//pad to right x border 
			pady = 0;//pad to bottom y border 
			padxInner = 40;//text in
			padyInner = 20;//text in
			ySpacing = 5;//spacing between bubbles
			round = 3.f;//rounded bubble if != 0.
			mkRounded = 1.f;//rounded left mark
			mkWidth = 5;//width colored left mark
			mkPad = 0;//padding left mark
			bAlignRight = true;
			bRightColorMark = false;
			bUseTagColor = true;
			bBg = true;

			doClear();
		}

		void drawImGuiControls()
		{
			if (!bGui) return;

			ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;

			bool tmp = bGui.get();
			bool b = ImGui::Begin(bGui.getName().c_str(), (bool*)&tmp, flags);
			if (bGui.get() != tmp) bGui.set(tmp);

			//ImGui::Begin("Debug surfingNotifier", NULL, flags);
			if (b)
			{
#ifndef USE_IM_GUI_TRICKS_PARAMS

				ImGui::SliderInt("indexFont", &indexFont, 0, 3);
				ImGui::SliderInt("duration", &duration, 300, 10000);
				ImGui::SliderInt("padx", &padx, 0, 100);
				ImGui::SliderInt("pady", &pady, 0, 100);
				ImGui::SliderInt("padxInner", &padxInner, 0, 100);
				ImGui::SliderInt("padyInner", &padyInner, 0, 100);
				ImGui::SliderInt("ySpacing", &ySpacing, 0, 100);
				ImGui::SliderFloat("round", &round, 0, 100);
				ImGui::Checkbox("Color Mark", &bUseColorMark);
				if (bUseColorMark) {
					ImGui::Checkbox("CM Right", &bRightColorMark);
					ImGui::SliderFloat("CM Round", &mkRounded, 0, 100);
					ImGui::SliderInt("CM Width", &mkWidth, 0, 100);
					ImGui::SliderInt("CM Pad", &mkPad, 0, 100);
				}
				ImGui::Checkbox("bAlignRight", &bAlignRight);
				ImGui::Checkbox("bUseTagColor", &bUseTagColor);
				ImGui::Checkbox("bBg", &bBg);
				if (!bAlignRight) ImGui::SliderFloat("widthMax_", &widthMax_, 100, 800);
#else
				ofxImGuiSurfing::AddParameter(duration);
				ofxImGuiSurfing::AddStepper(indexFont);
				ofxImGuiSurfing::AddStepper(padx);
				ofxImGuiSurfing::AddStepper(pady);
				ofxImGuiSurfing::AddStepper(padxInner);
				ofxImGuiSurfing::AddStepper(padyInner);
				ofxImGuiSurfing::AddStepper(ySpacing);
				ofxImGuiSurfing::AddStepper(round);
				ofxImGuiSurfing::AddParameter(bUseColorMark);
				if (bUseColorMark) {
					ImGui::Indent();
					ofxImGuiSurfing::AddParameter(bRightColorMark);
					ofxImGuiSurfing::AddStepper(mkRounded);
					ofxImGuiSurfing::AddStepper(mkWidth);
					ofxImGuiSurfing::AddStepper(mkPad);
					ImGui::Unindent();
				}
				ofxImGuiSurfing::AddParameter(bAlignRight);
				ofxImGuiSurfing::AddParameter(bUseTagColor);
				ofxImGuiSurfing::AddParameter(bBg);
#endif
				if (ImGui::Button("Reset")) { doReset(); }
				ImGui::SameLine();
				if (ImGui::Button("Clear")) doClear();

				ImGui::Spacing();
				ImGui::Spacing();
				string s = "";
				s += "Amount: ";
				s += ofToString(notifies.size(), 0);
				ImGui::Text(s.c_str());
			}

			if (b) ImGui::End();
			//ImGui::End();
		};

		ImVec2 bbox = ImVec2(500, 100);

		void AddNotify(std::string message, NotifyState state)
		{
			uint64_t t = GetTickCount64();//TODO: WIN_32 only!
			notifies.push_back({ message, state, t + duration });//store end time
		};

		void doClear() {
			notifies.clear();
			widthMax_ = wmaxDef;//reset
		};

		void HandleNotifies(ImDrawList* draw, std::vector<ImFont*>* fonts)
		{
			if (notifies.empty()) {
				widthMax_ = wmaxDef;//reset
				return;
			}
			const auto szScreen = ImGui::GetIO().DisplaySize;

			//ImVec2 NotifyPos = szScreen - ImVec2(0, bbox.y);

			ImVec2 NotifyPos;
			if (!bAlignRight) NotifyPos = szScreen - ImVec2(widthMax_, bbox.y);
			else NotifyPos = szScreen - ImVec2(0, bbox.y);

			// padding to bottom right/down borders
			NotifyPos = NotifyPos - ImVec2(padx, pady);
			//NotifyPos -= ImVec2(padx, pady);

			//NotifyPos.y -= ySpacing;
			////NotifyPos.y -= pady;

			// Spacing up!
			if (1) {
				NotifyPos.y -= ySpacing;
			}
			else {
				//TODO:
				// anim
				bool state = 1;
				float min = 0;
				float max = ySpacing;
				float speed = 0.05;
				//float speed = (1000 / 60.f) * 400;
				float offsety_ = Animations::FastLerpFloat("identifier", state, min, max, speed);
				NotifyPos.y -= offsety_;
			}


			//--

			// Push font size
			bool bPushed = false;
			if (fonts != nullptr)
			{
				if (fonts->size() > 0)
				{
					size_t i = indexFont;//pick the size 0 to 3 in ofxsurfingImgui
					size_t sz = fonts->size();
					i = MIN(i, sz - 1);

					ImFont* font = (*fonts)[i];
					ImGui::PushFont(font);
					bPushed = true;
				}
			}

			//--

			// Draw lambda function:

			auto DrawNotify = [=, &draw, &NotifyPos](NotifyStruct notify)
			{
				ImVec2 szText = ImGui::CalcTextSize(notify.message.c_str());

				bbox = szText + ImVec2(padxInner + padxInner, padyInner + padyInner);

				if (bbox.x > widthMax_) widthMax_ = bbox.x;

				ImVec2 NotifyPos_;

				//TODO: right align text
				if (bAlignRight)
				{
					offsetx = szText.x;
					NotifyPos_ = NotifyPos - ImVec2(offsetx + padxInner + padxInner, 0); // Offset
				}
				else
				{
					offsetx = 0;
					NotifyPos_ = NotifyPos; // No offset
				}

				ImVec2 NotifyEndPos = NotifyPos_ + bbox;

				//1. bbox bg
				if (bBg) {
					draw->AddRectFilled(NotifyPos_, NotifyEndPos,
						ImGui::GetColorU32(ImGuiCol_PopupBg),
						((round == 0) ? ImGui::GetStyle().PopupRounding : round));
				}

				ImColor colorState;
				switch (notify.state)
				{
				case ImTrickNotify_Verbose: colorState = ImColor(ofColor::white); break;
				case ImTrickNotify_Notice: colorState = ImColor(ofColor::green); break;
				case ImTrickNotify_Warning: colorState = ImColor(ofColor::yellow); break;
				case ImTrickNotify_Error: colorState = ImColor(ofColor::red); break;
				case ImTrickNotify_Info: default: colorState = ImColor(ofColor::white); break;
				}

				// 2. Text
				const auto TextPos = NotifyPos_ + ImVec2(padxInner, padyInner);

				//3. bbox left colored mark
				if (bUseColorMark)
				{
					if (!bRightColorMark)
						draw->AddRectFilled(ImVec2(NotifyPos_.x - mkWidth - mkPad, NotifyPos_.y),
							ImVec2(NotifyPos_.x - mkPad, NotifyPos_.y + bbox.y), colorState, mkRounded);
					else
						draw->AddRectFilled(ImVec2(NotifyEndPos.x + mkPad, NotifyPos_.y),
							ImVec2(NotifyEndPos.x + mkPad + mkWidth, NotifyPos_.y + bbox.y), colorState, mkRounded);
				}

				ImU32 c;
				if (bUseTagColor) c = ImGui::GetColorU32(ImVec4(colorState));
				else c = ImGui::GetColorU32(ImGuiCol_Text);

				draw->AddText(TextPos, c, notify.message.c_str());

				if (bbox.x > widthMax_) widthMax_ = bbox.x;

				// Spacing up!
				if (1) {
					NotifyPos.y -= bbox.y;
					NotifyPos.y -= ySpacing;
				}
				else {
					//TODO:
					// anim
					bool state = 1;
					float min = 0;
					float max = bbox.y + ySpacing;
					float speed = 0.05;
					//float speed = (1000 / 60.f) * 400;
					float offsety_ = Animations::FastLerpFloat("identifier", state, min, max, speed);
					NotifyPos.y -= offsety_;
				}
			};

			//--

			uint64_t t = GetTickCount64();//TODO: WIN_32 only!

			// iterate all notes
			for (auto& n : notifies)
			{
				// skip/continue if passed end time for each message
				if (t > n.time) {
					continue;
				}

				DrawNotify(n);
			}

			//--

			if (bPushed)
			{
				ImGui::PopFont();
			}

			// remove all elements from the vector whose endTime is less than t
			notifies.erase(std::remove_if(notifies.begin(), notifies.end(),
				[t](const NotifyStruct& n) { return t > n.time; }),
				notifies.end());
		};
	}

	namespace Widgets {
		void ColorEdit3(const char* label, ImColor& color, ImGuiColorEditFlags flags) {
			static float col[3] = { color.Value.x, color.Value.y, color.Value.z };

			if (ImGui::ColorEdit3(label, col, flags))
				color = ImColor(col[0], col[1], col[2]);
		}

		void ColorEdit4(const char* label, ImColor& color, ImGuiColorEditFlags flags) {
			static float col[4] = { color.Value.x, color.Value.y, color.Value.z , color.Value.w };

			if (ImGui::ColorEdit4(label, col, flags))
				color = ImColor(col[0], col[1], col[2], col[3]);
		}
	}

}