#pragma once

#include "ofMain.h"

class HelpWidget
{
public:
	HelpWidget() {};
	~HelpWidget() {};

private:
	std::string text = "HelpWidget\nEmpty content";
	std::string title = "myHelpWidget";

	bool bBg = true;

private:
	bool bHeader = false;
	bool bBlink = 0;

public:
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

		float r = 3; // window rounded 
		float p = 25; // window padding to borders

		// Spacing after title
		//string sp = "\n\n";
		string sp = "\n";

		//--

		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		if (!bHeader) flags += ImGuiWindowFlags_NoDecoration;
		if (!bBg) flags += ImGuiWindowFlags_NoBackground;
		flags += ImGuiWindowFlags_AlwaysAutoResize;

		// bg color
		//ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_FrameBgHovered);
		ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_HeaderActive);

		// alpha
		//float abg = 0.9;
		float abg = ImGui::GetStyleColorVec4(ImGuiCol_HeaderActive).w;
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
				string s = title;
				//string s = title + sp;

				if (customFonts.size() > 2) {
					ImGui::PushFont(customFonts[1]);
					ImGui::TextWrapped(s.c_str());
					ImGui::PopFont();
				}
				else ImGui::TextWrapped(s.c_str());
			}

			// Body
			{
				string s = sp + text;
				//string s = text;

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

public:
	void setCustomFonts(vector<ImFont*> f)
	{
		customFonts = f;

		if (customFonts.size() == 0) {
			ofLogError("ofxSurfingImGui:HelpWidget") << "It looks that not any extra font styles are added!";
		}
	};
};