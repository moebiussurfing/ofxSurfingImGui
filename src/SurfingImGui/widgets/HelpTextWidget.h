#pragma once
#include "ofMain.h"

/*

	- make simpler Example.

*/

//--

class HelpTextWidget
{
public:
	HelpTextWidget()
	{
	}

	~HelpTextWidget()
	{
		CleanupCustomFonts();
	}

private:
	std::string text = "HelpTextWidget\nEmpty content";
	std::string title = "myHelpWidget KeyCommands";

	bool bBg = true; // transparent Bg
	bool bHeader = true;
	bool bHeaderTitle = true;
	bool bTitleSettled = false;
	bool bBlink = 0;

	bool bMouseLeft = false;
	bool bMouseRight = false;
	bool bMouseDrag = false;

	//TODO
	//public:
	//	bool bResponsive = true;//autoresize window to text paragraph width
	//	void setEnableResponsive(bool b = true) { bResponsive = b; }

public:
	void setEnableBlink(bool b = true) { bBlink = b; }
	void setEnableHeader(bool b = true) { bHeader = b; }
	void setEnableHeaderTitle(bool b = true) { bHeaderTitle = b; }

	ofParameter<bool> bGui{ "HelpTextWidget", true };

	void setTitle(string _title, bool bCapitalize = true)
	{
		ofLogNotice("ofxSurfingImGui:HelpTextWidget") << "Title: " << _title;
		title = _title;
		if (bCapitalize) title = ofToUpper(title);
		bTitleSettled = true;
	}

	void setText(string _text, bool bSlient = true)
	{
		if (bSlient) ofLogVerbose("ofxSurfingImGui:HelpTextWidget") << "Text: " << _text;
		else ofLogNotice("ofxSurfingImGui:HelpTextWidget") << "Text: " << _text;

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

		//TODO:
		// Combination mouse clicks (left+right) to close window
		if (!bHeader)
		{
			if (bMouseLeft && bMouseRight)
			{
				bMouseLeft = bMouseRight = bMouseDrag = false;
				bGui = false;
			}
		}

		// Adapt window size to font size
		//if (!bResponsive) 
		{
			switch (fontIndex)
			{
			case 0: case 4: IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MEDIUM; break;//default
			case 1: case 5: IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_BIG; break;//big
			case 2: case 6: IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_FULL; break;//huge
			case 3: case 7: IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_MAX; break;//hugeXXL
			}
		}

		// Window rounded 
#if 0
		float r = 3;
#else
		float r = ImGui::GetStyle().WindowRounding;
#endif

		float p = 25; // window padding to borders

		// Spacing after title
		string sp = "\n";

		//--

		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		if (!bHeader) flags += ImGuiWindowFlags_NoDecoration;
		if (!bBg) flags += ImGuiWindowFlags_NoBackground;

		//if (bResponsive)
		{
			flags += ImGuiWindowFlags_AlwaysAutoResize;
		}

		// Bg color
		ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_TitleBgActive);
		//ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_Header);
		//ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_HeaderActive);
		//ImVec4 cbg = ImGui::GetStyleColorVec4(ImGuiCol_FrameBgHovered);

#if 1
		// No alpha Bg
		//float cbga = 1.f;
		float cbga = ImGui::GetStyleColorVec4(ImGuiCol_TitleBgActive).w;
		//float cbga = ImGui::GetStyleColorVec4(ImGuiCol_Header).w;
		//float cbga = ImGui::GetStyleColorVec4(ImGuiCol_HeaderActive).w;
#else
		// Alpha Bg
		float cbga = 0.88;//less opacity than window bg color style,
		// float cbga = 0.84;//less opacity than window bg color style,
#endif

		// Push
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(cbg.x, cbg.y, cbg.z, cbga));

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ p, p });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, r);

		if (bBlink)
		{
			ImVec4 tc = ImGui::GetStyleColorVec4(ImGuiCol_Text);
			float ta = ofxImGuiSurfing::getFadeBlink();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(tc.x, tc.y, tc.z, tc.w * ta));
		}

		bool tmp = bGui.get();

		//--

		// Window

		string sTitle;

		//sTitle = bTitleSettled ? title : bGui.getName();
		sTitle = bGui.getName();

		if (!bHeaderTitle) sTitle = "##" + sTitle;//hide text

		ImGui::Begin(sTitle.c_str(), (bool*)&tmp, flags);
		{
			//--

			// 1. Title

			if (!bHeader || bTitleSettled)
			{
				string s = title;
				//string s = title + sp;

				//TODO
#ifdef SURFING_IMGUI__USE_CUSTOM_FONTS_PTR
				if (customFontsPtr != nullptr)
				{
					if (fontIndex.get() < customFontsPtr->size())
					{
						std::vector<ImFont*>& cf = *customFontsPtr;
						int i = MIN(fontIndex.get() + 1, cf.size() - 1);//make it bigger
						ImGui::PushFont(cf[i]);
						//if(bResponsive) 
						//ImGui::Text(s.c_str());
						ImGui::TextWrapped(s.c_str());
						ImGui::PopFont();
						cf.clear();
						//delete customFontsPtr;//?
					}
					else ImGui::TextWrapped(s.c_str());
				}
				else ImGui::TextWrapped(s.c_str());//use default font only
#else
				if (!bUsingPtr)
				{
					if (fontIndex.get() < customFonts.size())
					{
						int i;
						if (fontIndex.get() == 3 || fontIndex.get() == 7) i = fontIndex.get();
						else i = MIN(fontIndex.get() + 1, customFonts.size() - 1);
						ImGui::PushFont(customFonts[i]);
						//ImGui::Text(s.c_str());
						ImGui::TextWrapped(s.c_str());
						ImGui::PopFont();
					}
					else ImGui::TextWrapped(s.c_str());
				}
#endif
			}

			//--

			// 2. Body

			{
				string s = sp + text;
				//string s = text;

				//TODO
#ifdef SURFING_IMGUI__USE_CUSTOM_FONTS_PTR
				if (customFontsPtr != nullptr)
				{
					if (fontIndex.get() < customFontsPtr->size())
					{
						std::vector<ImFont*>& cf = *customFontsPtr;
						int i = MIN(fontIndex.get(), cf.size() - 1);
						ImGui::PushFont(cf[i]);
						ImGui::TextWrapped(s.c_str());
						ImGui::PopFont();
						cf.clear();
						//delete customFontsPtr;//?
					}
					else ImGui::TextWrapped(s.c_str());//use default font only
				}
				else ImGui::TextWrapped(s.c_str());
#else
				if (!bUsingPtr)
				{
					if (fontIndex.get() < customFonts.size())
					{
						int i = MIN(fontIndex.get(), customFonts.size() - 1);
						ImGui::PushFont(customFonts[i]);
						ImGui::TextWrapped(s.c_str());
						ImGui::PopFont();
					}
					else ImGui::TextWrapped(s.c_str());
				}
#endif
			}

			//--

			//TODO:
			// Left + right mouse closes window
			if (!bHeader)
			{
				//TODO
				// set keystroke order
				//if()
				//{
				//	bMouseDrag = true;
				//}

				// left
				if (!bMouseLeft)
				{
					if (ImGui::IsMouseClicked(0))
					{
						bMouseLeft = true;
						if (!bMouseRight) bMouseDrag = true;
					}
				}
				if (bMouseLeft) if (ImGui::IsMouseReleased(0)) bMouseLeft = false;

				// right
				if (!bMouseRight) if (ImGui::IsMouseClicked(1)) bMouseRight = true;
				if (bMouseRight) if (ImGui::IsMouseReleased(1)) bMouseRight = false;

				// debug
				//string s = "";
				//(bMouseLeft ? s = "x" : s = "-");
				//s += " ";
				//(bMouseRight ? s += "x" : s += "-");
				//ImGui::Text(s.c_str());
			}
		}
		ImGui::End();

		//--

		if (bGui.get() != tmp) bGui.set(tmp);

		// Pop
		ImGui::PopStyleVar(3);

		ImGui::PopStyleColor();

		if (bBlink) ImGui::PopStyleColor();
	}

	//--

public:
	ofParameter<int> fontIndex{ "Font", 0, 0, 0 };
	vector<std::string> namesCustomFonts;
	vector<std::string>* namesCustomFontsPtr = nullptr;
private:
	vector<ImFont*> customFonts;

	//TODO: WIP
	vector<ImFont*>* customFontsPtr = nullptr;
	bool bUsingPtr = false;

public:
	void setFontIndex(int i) {
		i = ofClamp(i, 0, customFonts.size() - 1);
		fontIndex = i;
	}

public:
	void setCustomFonts(vector<ImFont*> f, vector<std::string> namesCustomFonts_)
	{
		customFonts = f;
		if (customFonts.size() == 0)
		{
			ofLogError("ofxSurfingImGui:HelpTextWidget") << "It looks that not any extra font styles are added!";
		}
		fontIndex.setMax(customFonts.size() - 1);

		namesCustomFonts = namesCustomFonts_;
	}

#ifdef SURFING_IMGUI__USE_CUSTOM_FONTS_PTR
	//TODO; to avoid update when new font are added!
	void setCustomFontsPtr(vector<ImFont*>* f, vector<std::string>* namesCustomFontsPtr_)
	{
		if (customFontsPtr == nullptr) return;//skip if already done?

		customFontsPtr = f;
		bUsingPtr = true;

		if (customFontsPtr->size() == 0)
		{
			ofLogError("ofxSurfingImGui:HelpTextWidget") << "It looks that not any extra font styles are added!";
		}
		fontIndex.setMax(customFontsPtr->size() - 1);

		if (namesCustomFontsPtr_ == nullptr) namesCustomFontsPtr = namesCustomFontsPtr_;
	}
#endif

private:
	// Cleanup function to delete the vector
	void CleanupCustomFonts()
	{
		if (customFontsPtr != nullptr)
		{
			delete customFontsPtr;
		}
		if (namesCustomFontsPtr != nullptr)
		{
			delete namesCustomFontsPtr;
		}
	}
};
