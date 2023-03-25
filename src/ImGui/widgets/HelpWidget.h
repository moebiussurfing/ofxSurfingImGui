#pragma once

#include "ofMain.h"

//#include "ofxSurfingImGui.h"
//using ofxSurfingGui = SurfingGuiManager;//?

class HelpWidget
{
public:
	HelpWidget() {};
	~HelpWidget() {};

private:

	////SurfingGuiManager *ui = nullptr;
	//ofxSurfingGui *ui = nullptr;

	std::string text = "HelpWidget\nEmpty content";
	std::string title = "myHelpWidget";

	bool bBg = true;

public:

	//void setUiPtr(SurfingGuiManager* _ui) {
	//	ui = _ui;
	//}

	bool bHeader = false;
	bool bBlink = 0;

	void setEnableHeader(bool b) { bHeader = b; }

	ofParameter<bool> bGui{ "HelpWidget", true };

	void setTitle(string _title, bool bCapitalize = true)
	{
		ofLogVerbose("ofxSurfingImGui:HelpWidget") << "setTitle:" << _title;
		title = _title;

		if (bCapitalize) title = ofToUpper(title);
	}

	void setText(string _text)
	{
		ofLogVerbose("ofxSurfingImGui:HelpWidget") << "SetText:" << _text;
		text = _text;
	}

	void setName(string name)
	{
		bGui.setName(name);
		title = name;
	}

	void draw()
	{
		if (!bGui) return;

		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		if (!bHeader) flags += ImGuiWindowFlags_NoDecoration;
		if (!bBg) flags += ImGuiWindowFlags_NoBackground;
		flags += ImGuiWindowFlags_AlwaysAutoResize;

		float r = 3;
		float p = 30;

		//ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_FrameBgHovered);
		ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_HeaderActive);

		float abg = 0.9;
		//float abg = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg).w;

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(cbg.x, cbg.y, cbg.z, abg));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ p,p });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, r);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		if (bBlink) {
			ImVec4 tc = ImGui::GetStyleColorVec4(ImGuiCol_Text);
			float ta = ofxImGuiSurfing::getFadeBlink();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(tc.x, tc.y, tc.z, tc.w * ta));
		}

		bool tmp = bGui.get();
		ImGui::Begin(bGui.getName().c_str(), (bool*)&tmp, flags);
		{
			// Title
			if (!bHeader)
			{
				string s = title + "\n\n";

				//if (ui != nullptr) ui->AddLabelBig(s.c_str());
				//else ImGui::TextWrapped(s.c_str());

				if (customFonts.size() > 2) {
					ImGui::PushFont(customFonts[1]);
					ImGui::TextWrapped(s.c_str());
					ImGui::PopFont();
				}
				else ImGui::TextWrapped(s.c_str());
			}

			//if (ui != nullptr) ui->AddLabel(text.c_str());
			//else ImGui::TextWrapped(text.c_str());

			// Body
			{
				string s = text;
				if (customFonts.size() > 2) {
					ImGui::PushFont(customFonts[0]);
					ImGui::TextWrapped(s.c_str());
					ImGui::PopFont();
				}
				else ImGui::TextWrapped(s.c_str());
			}

		}
		ImGui::End();
		if (bGui.get() != tmp) bGui.set(tmp);

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
		if (bBlink) ImGui::PopStyleColor();
	}

private:
	vector<ImFont*> customFonts;
	//ofParameter<int> indexSizeFont{ "Font", 0, 0, 0 };
	//vector<string> namesCustomFonts;

	//TODO:
public:
	void setCustomFonts(vector<ImFont*> f)
	{
		customFonts = f;

		if (customFonts.size() == 0) {
			ofLogError("ofxSurfingImGui:HelpWidget") << "It looks that not any extra font styles are added!";

		}

		//indexSizeFont.setMax(customFonts.size() - 1);

		////TODO: 
		//// WARNING! 
		//// these names could be copied to GuiManager too!
		//// take care if both sizes fonts/names changed! 
		//// this is hardcoded now!
		//// Font sizes
		//namesCustomFonts.clear();
		//namesCustomFonts.push_back("DEFAULT");
		//namesCustomFonts.push_back("BIG");
		//namesCustomFonts.push_back("HUGE");
		//namesCustomFonts.push_back("HUGE_XXL");
	};
};