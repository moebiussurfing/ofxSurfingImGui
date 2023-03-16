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

	namespace NotifyManager {

		std::vector<NotifyStruct> notifies;

		float offsetx = 0;

		//const int wmaxDef = 0;//flick bug
		const int wmaxDef = 200;

		//TODO: add editor to save settings
		// hardcoded
		int duration = 3000;
		float wmax = wmaxDef;//getting max width o all bubbles. starting pad
		float pdx0 = 20;//pad to right x border 
		float pdy0 = 20;//pad to bottom y border 
		float pdx = 15;//text in
		float pdy = 15;//text in
		float spy = 15;//spacing between bubbles
		float rd = 3.f;//rounded bubble if != 0.
		float rdmk = 1.f;//rounded left mark
		float wmk = 5.f;//width colored left mark
		float pbmk = 0.f;//padding left mark
		bool bAlignRight = true;
		bool bUseColor = true;


		//TODO:
		int indexFont = 0;//default
		//int indexFont = 1;//big
		//int indexFont = 2;//huge

		void drawImGuiControls()
		{
			ImGui::Begin("Debug Notifier");

			ImGui::SliderInt("indexFont", &indexFont, 0, 3);
			ImGui::SliderInt("duration", &duration, 300, 10000);
			ImGui::SliderFloat("pdx0", &pdx0, 0, 100);
			ImGui::SliderFloat("pdy0", &pdy0, 0, 100);
			ImGui::SliderFloat("pdx", &pdx, 0, 100);
			ImGui::SliderFloat("pdy", &pdy, 0, 100);
			ImGui::SliderFloat("spy", &spy, 0, 100);
			ImGui::SliderFloat("rd", &rd, 0, 100);
			ImGui::SliderFloat("rdmk", &rdmk, 0, 100);
			ImGui::SliderFloat("wmk", &wmk, 0, 100);
			ImGui::SliderFloat("pbmk", &pbmk, 0, 100);
			ImGui::Checkbox("bAlignRight", &bAlignRight);
			if(!bAlignRight) ImGui::SliderFloat("wmax", &wmax, 100, 800);
			ImGui::Checkbox("bUseColor", &bUseColor);
			if (ImGui::Button("Reset"))
			{
				duration = 3000;
				wmax = 100;//starting pad
				pdx0 = 20;//pad to right x border 
				pdy0 = 20;//pad to bottom y border 
				pdx = 15;//text in
				pdy = 15;//text in
				spy = 15;//spacing between bubbles
				rd = 3.f;//rounded bubble if != 0.
				rdmk = 1.f;//rounded left mark
				wmk = 5.f;//width colored left mark
				pbmk = 0.f;//padding left mark
				bAlignRight = true;
				bUseColor = true;

				clear();
			}
			ImGui::SameLine();
			if (ImGui::Button("Clear")) clear();

			ImGui::End();
		};

		ImVec2 bbox = ImVec2(500, 100);

		void AddNotify(std::string message, NotifyState state)
		{
			uint64_t t = GetTickCount64();//TODO: WIN_32 only!
			notifies.push_back({ message, state, t + duration });//store end time
		};

		void clear() {
			notifies.clear();
			wmax = wmaxDef;//reset
		};

		void HandleNotifies(ImDrawList* draw, std::vector<ImFont*>* fonts)
		{
			if (notifies.empty()) {
				wmax = wmaxDef;//reset
				return;
			}
			const auto szScreen = ImGui::GetIO().DisplaySize;

			//ImVec2 NotifyPos = szScreen - ImVec2(0, bbox.y);

			ImVec2 NotifyPos;
			if (!bAlignRight) NotifyPos = szScreen - ImVec2(wmax, bbox.y);
			else NotifyPos = szScreen - ImVec2(0, bbox.y);

			// padding to bottom right/down borders
			NotifyPos -= ImVec2(pdx0, pdy0);

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

				bbox = szText + ImVec2(pdx + pdx, pdy + pdy);

				if (bbox.x > wmax) wmax = bbox.x;
				//NotifyPos -= ImVec2(wmax, 0);

				ImVec2 NotifyPos_;

				//TODO: right align text
				if (bAlignRight) {
					offsetx = szText.x;
					NotifyPos_ = NotifyPos - ImVec2(offsetx + pdx + pdx, 0); // Offset
				}
				else {
					offsetx = 0;
					NotifyPos_ = NotifyPos; // No offset
				}

				ImVec2 NotifyEndPos = NotifyPos_ + bbox;

				//1. bbox bg
				draw->AddRectFilled(NotifyPos_, NotifyEndPos,
					ImGui::GetColorU32(ImGuiCol_PopupBg),
					((rd == 0) ? ImGui::GetStyle().PopupRounding : rd));

				ImColor StateColor;
				switch (notify.state)
				{
				case ImTrickNotify_Verbose: StateColor = ImColor(ofColor::white); break;
				case ImTrickNotify_Notice: StateColor = ImColor(ofColor::green); break;
				case ImTrickNotify_Warning: StateColor = ImColor(ofColor::yellow); break;
				case ImTrickNotify_Error: StateColor = ImColor(ofColor::red); break;
				case ImTrickNotify_Info: default: StateColor = ImColor(ofColor::white); break;
				}

				// 2. Text
				const auto TextPos = NotifyPos_ + ImVec2(pdx, pdy);

				//3. bbox left colored mark 
				draw->AddRectFilled(ImVec2(NotifyPos_.x - wmk - pbmk, NotifyPos_.y),
					ImVec2(NotifyPos_.x - pbmk, NotifyPos_.y + bbox.y), StateColor, rdmk);

				ImU32 c;
				if (bUseColor) c = ImGui::GetColorU32(ImVec4(StateColor));
				else c = ImGui::GetColorU32(ImGuiCol_Text);

				draw->AddText(TextPos, c, notify.message.c_str());

				if (bbox.x > wmax) wmax = bbox.x;

				// Spacing up!
				NotifyPos.y -= bbox.y;
				NotifyPos.y -= spy;
			};

			//--

			uint64_t t = GetTickCount64();//TODO: WIN_32 only!

			// iterate all notes
			for (auto& n : notifies)
			{
				// skip/continue if passed end time for each message
				if (t > n.time) continue;

				DrawNotify(n);
			}

			//--

			if (bPushed)
			{
				ImGui::PopFont();
			}

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