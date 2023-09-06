#pragma once

/*

	Helpers mainly for hardcoded themes.

*/

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

using namespace ImGui;

//--

#include "Combos.h"

#include "SurfingThemes.h"

//----

#if(0)
// ImGui Theme serializer
// Taken from: https://github.com/pegvin/ImGooeyStyles
#include "imgui_styles.h"
//#include "imgui_styles.cpp"

// Standalone 
/*
EXAMPLE
ofxImGuiSurfing::SurfingThemes::loadThemeFileByName("t22222.ini");
*/
namespace ofxImGuiSurfing
{
	namespace SurfingThemes
	{
		static string pathThemes = "";

		enum THEME_STYLE
		{
			THEME_NIGHT = 0,
			THEME_DAY
		};

		static THEME_STYLE themeStyle = THEME_NIGHT;

		inline bool loadThemeFileByName(string name) {
			ofLogNotice("ofxSurfingImGui::loadThemeFileByName") << name;
			string pathTheme = pathThemes + name;
			string p = ofToDataPath(pathTheme);
			ofLogNotice("ofxSurfingImGui::loadThemeFileByName") << "Load from " << p;
			ImGui::LoadStyleFrom(p.c_str());

			ofFile f;
			return f.doesFileExist(p);
		};

		inline bool loadThemeFile(string path, bool bAbsolute = false) {
			ofLogNotice("ofxSurfingImGui::loadThemeFile") << path << " bAbsolute:" << bAbsolute;
			string p;
			if (bAbsolute) p = path;
			else p = ofToDataPath(path);
			ofLogNotice("ofxSurfingImGui::loadThemeFile") << "Load from " << p;
			ImGui::LoadStyleFrom(p.c_str());

			ofFile f;
			return f.doesFileExist(p);
		};
	}
}
#endif

//---

namespace ofxImGuiSurfing
{
	static int indexThemeHardcoded = -1;
	static int amountThemes = 0;
	static bool bUpdate = false;

	//----

	//--------------------------------------------------------------
	//inline void resetTheme() {
	//	ImGui::GetStyle() = ImGuiStyle();
	//};

	//--------------------------------------------------------------
	static void setIndexThemeHardcoded(int i) {
		indexThemeHardcoded = i;
		bUpdate = true;
	}

	//--------------------------------------------------------------
	inline bool drawWidgetsThemeHardcodedSelector(const char* label)
	{
		int i = indexThemeHardcoded;

		//TODO: should be static..
		static std::vector<std::string> names;

		static bool bDone = 0;
		if (!bDone) {
			bDone = 1;
			names.clear();
			names.push_back("Dark");
			names.push_back("Light");
			names.push_back("Classic");
			names.push_back("moebiusSurfingV2");
			names.push_back("moebiusSurfing");
			names.push_back("moebiusSurfing Blue");
			names.push_back("Grey");
			names.push_back("Sequentity");
			names.push_back("Olekristensen");
			names.push_back("FlatDryWineGreen");
			names.push_back("T3");
			names.push_back("ModernDark");
			names.push_back("Blender");
			names.push_back("Cyberpunk");
			names.push_back("Nord");
			names.push_back("Unreal");
			names.push_back("VisualStudioRounded");
			names.push_back("VisualStudio");
			names.push_back("Photoshop");
			names.push_back("MaterialFlat");
			names.push_back("Enemymouse");
			names.push_back("DeepDark");
			names.push_back("Darcula");
			names.push_back("Xemu");
			names.push_back("Yave");
			names.push_back("ImStyle");
			names.push_back("AiekickGreenBlue");
			names.push_back("AiekickRedDark");
			names.push_back("DraculaStyle");
			names.push_back("Maksasj");
			names.push_back("SimongeilfusCinder");
			names.push_back("ThemeAdobeSpectrum");

			amountThemes = names.size();
		}

		bool b1 = false;
		bool b2 = false;

		ImVec2 sz1(ImGui::GetContentRegionAvail().x, ImGui::GetFrameHeight());
		ImVec2 sz2(ImGui::GetContentRegionAvail().x / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 1.5f * ImGui::GetFrameHeight());

		//--

		// Keys

		bool bL = ImGui::IsKeyPressed(ImGuiKey_LeftArrow);
		bool bR = ImGui::IsKeyPressed(ImGuiKey_RightArrow);

		//--

		// Combo

		b2 = (ofxImGuiSurfing::VectorCombo(&i, names));

		//string name = "Hardcoded Themes";
		//float w = ImGui::CalcTextSize(name.c_str()).x + /*ImGui::GetStyle().WindowPadding.x +*/ ImGui::GetStyle().ItemSpacing.x + ImGui::GetStyle().ItemInnerSpacing.x;

		//ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - w);
		//b2 = (ofxImGuiSurfing::VectorCombo(name.c_str(), &i, names, 1));
		//ImGui::PopItemWidth();

		//--

		// Browse

		ImGui::PushButtonRepeat(true);
		if (ImGui::Button("<", sz2) || bL) {
			i--;
			i = ofClamp(i, 0, names.size() - 1);
			indexThemeHardcoded = i;
			ofLogNotice("ofxSurfingImGui") << "Index: " << i;
			b1 = true;
		}
		ImGui::SameLine();
		if (ImGui::Button(">", sz2) || bR) {
			i++;
			i = ofClamp(i, 0, names.size() - 1);
			indexThemeHardcoded = i;
			ofLogNotice("ofxSurfingImGui") << "Index: " << i;
			b1 = true;
		}
		ImGui::PopButtonRepeat();
		ImGui::Spacing();

		//--

		if (b1 || b2 || bUpdate)
		{
			//TODO; workaround
			if (bUpdate) {
				i = indexThemeHardcoded;
				bUpdate = false;
			}

			i = ofClamp(i, 0, names.size() - 1);//avoid crashes
			indexThemeHardcoded = i;
			ofLogNotice("ofxSurfingImGui") << "Combo: " << i;

			switch (indexThemeHardcoded)
			{
			case 0: resetTheme(); ImGui::StyleColorsDark(); break;
			case 1: resetTheme(); ImGui::StyleColorsLight(); break;
			case 2: resetTheme(); ImGui::StyleColorsClassic(); break;
			case 3: ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing(bEnableLayout, bEnableColors); break;
			case 4: ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2(bEnableLayout, bEnableColors); break;
			case 5: ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingBlue(); break;
			case 6: ofxImGuiSurfing::ImGui_ThemeGrey(); break;
			case 7: ofxImGuiSurfing::ImGui_ThemeSequentity(); break;
			case 8: ofxImGuiSurfing::ImGui_ThemeOlekristensen(); break;
			case 9: ofxImGuiSurfing::ImGui_ThemeFlatDryWineGreen(); break;
			case 10: ofxImGuiSurfing::ImGui_ThemeT3(); break;
			case 11: ofxImGuiSurfing::ImGui_ThemeModernDark(); break;
			case 12: ofxImGuiSurfing::ImGui_ThemeBlender(); break;
			case 13: ofxImGuiSurfing::ImGui_ThemeCyberpunk(); break;
			case 14: ofxImGuiSurfing::ImGui_ThemeNord(); break;
			case 15: ofxImGuiSurfing::ImGui_ThemeUnreal(); break;
			case 16: ofxImGuiSurfing::ImGui_ThemeVisualStudioRounded(); break;
			case 17: ofxImGuiSurfing::ImGui_ThemeVisualStudio(); break;
			case 18: ofxImGuiSurfing::ImGui_ThemePhotoshop(); break;
			case 19: ofxImGuiSurfing::ImGui_ThemeMaterialFlat(); break;
			case 20: ofxImGuiSurfing::ImGui_ThemeEnemymouse(); break;
			case 21: ofxImGuiSurfing::ImGui_ThemeDeepDark(); break;
			case 22: ofxImGuiSurfing::ImGui_ThemeDarcula(); break;
			case 23: ofxImGuiSurfing::ImGui_ThemeXemu(); break;
			case 24: ofxImGuiSurfing::ImGui_ThemeYave(); break;
			case 25: ofxImGuiSurfing::ImGui_ThemeImStyle(); break;
			case 26: ofxImGuiSurfing::ImGui_ThemeAiekickGreenBlue(); break;
			case 27: ofxImGuiSurfing::ImGui_ThemeAiekickRedDark(); break;
			case 28: ofxImGuiSurfing::ImGui_ThemeDraculaStyle(); break;
			case 29: ofxImGuiSurfing::ImGui_ThemeMaksasj(); break;
			case 30: ofxImGuiSurfing::ImGui_ThemeSimongeilfusCinder(); break;
			case 31: ofxImGuiSurfing::ImGui_ThemeAdobeSpectrum(); break;
			}
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------
	inline void drawThemeHardcodedSelector(ImGuiStyle* ref)
	{
		//TODO: not working?
		// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to
		// (without a reference style pointer, we will use one compared locally as a reference)
		ImGuiStyle& style = ImGui::GetStyle();
		static ImGuiStyle ref_saved_style;

		//TODO: not working?
		// Default to using internal storage as reference
		static bool init = true;
		if (init && ref == NULL) ref_saved_style = style;
		init = false;
		if (ref == NULL) ref = &ref_saved_style;

		// arrows and combo themes list
		if (ofxImGuiSurfing::drawWidgetsThemeHardcodedSelector("Colors##Selector")) ref_saved_style = style;

		if (ImGui::Button("Reload##BROWSER")) {
			//reload current
			bUpdate = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Random")) {
			//reload a random index
			indexThemeHardcoded = ofRandom(0, amountThemes);
			bUpdate = true;
		}

		ImGui::Spacing();

		//ImGui::Separator();
		//ImGui::Spacing();
		//ImGui::Spacing();
		//TODO:
		//ImGui::ShowFontSelector("Fonts##Selector");
	}

	//----

	/*
	// TODO
	// adding theme editor
	// [Internal] Display details for a single font, called by ShowStyleEditor().
	//--------------------------------------------------------------
	inline static void NodeFont2(ImFont* font)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		bool font_details_opened = ImGui::TreeNode(font, "Font: \"%s\"\n%.2f px, %d glyphs, %d file(s)",
			font->ConfigData ? font->ConfigData[0].Name : "", font->FontSize, font->Glyphs.Size, font->ConfigDataCount);
		ImGui::SameLine(); if (ImGui::SmallButton("Set as default")) { io.FontDefault = font; }
		if (!font_details_opened)
			return;

		ImGui::PushFont(font);
		ImGui::Text("The quick brown fox jumps over the lazy dog");
		ImGui::PopFont();
		ImGui::DragFloat("Font scale", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");   // Scale only this font
		ImGui::SameLine(); HelpMarker(
			"Note than the default embedded font is NOT meant to be scaled.\n\n"
			"Font are currently rendered into bitmaps at a given size at the time of building the atlas. "
			"You may oversample them to get some flexibility with scaling. "
			"You can also render at multiple sizes and select which one to use at runtime.\n\n"
			"(Glimmer of hope: the atlas system will be rewritten in the future to make scaling more flexible.)");
		ImGui::Text("Ascent: %f, Descent: %f, Height: %f", font->Ascent, font->Descent, font->Ascent - font->Descent);
		ImGui::Text("Fallback character: '%c' (U+%04X)", font->FallbackChar, font->FallbackChar);
		ImGui::Text("Ellipsis character: '%c' (U+%04X)", font->EllipsisChar, font->EllipsisChar);
		const int surface_sqrt = (int)sqrtf((float)font->MetricsTotalSurface);
		ImGui::Text("Texture Area: about %d px ~%dx%d px", font->MetricsTotalSurface, surface_sqrt, surface_sqrt);
		for (int config_i = 0; config_i < font->ConfigDataCount; config_i++)
			if (font->ConfigData)
				if (const ImFontConfig* cfg = &font->ConfigData[config_i])
					ImGui::BulletText("Input %d: \'%s\', Oversample: (%d,%d), PixelSnapH: %d, Offset: (%.1f,%.1f)",
						config_i, cfg->Name, cfg->OversampleH, cfg->OversampleV, cfg->PixelSnapH, cfg->GlyphOffset.x, cfg->GlyphOffset.y);

		if (ImGui::TreeNode("Glyphs", "Glyphs (%d)", font->Glyphs.Size))
		{
			// Display all glyphs of the fonts in separate pages of 256 characters
			const ImU32 glyph_col = ImGui::GetColorU32(ImGuiCol_Text);
			for (unsigned int base = 0; base <= IM_UNICODE_CODEPOINT_MAX; base += 256)
			{
				// Skip ahead if a large bunch of glyphs are not present in the font (test in chunks of 4k)
				// This is only a small optimization to reduce the number of iterations when IM_UNICODE_MAX_CODEPOINT
				// is large // (if ImWchar==ImWchar32 we will do at least about 272 queries here)
				if (!(base & 4095) && font->IsGlyphRangeUnused(base, base + 4095))
				{
					base += 4096 - 256;
					continue;
				}

				int count = 0;
				for (unsigned int n = 0; n < 256; n++)
					if (font->FindGlyphNoFallback((ImWchar)(base + n)))
						count++;
				if (count <= 0)
					continue;
				if (!ImGui::TreeNode((void*)(intptr_t)base, "U+%04X..U+%04X (%d %s)", base, base + 255, count, count > 1 ? "glyphs" : "glyph"))
					continue;
				float cell_size = font->FontSize * 1;
				float cell_spacing = style.ItemSpacing.y;
				ImVec2 base_pos = ImGui::GetCursorScreenPos();
				ImDrawList* draw_list = ImGui::GetWindowDrawList();
				for (unsigned int n = 0; n < 256; n++)
				{
					// We use ImFont::RenderChar as a shortcut because we don't have UTF-8 conversion functions
					// available here and thus cannot easily generate a zero-terminated UTF-8 encoded string.
					ImVec2 cell_p1(base_pos.x + (n % 16) * (cell_size + cell_spacing), base_pos.y + (n / 16) * (cell_size + cell_spacing));
					ImVec2 cell_p2(cell_p1.x + cell_size, cell_p1.y + cell_size);
					const ImFontGlyph* glyph = font->FindGlyphNoFallback((ImWchar)(base + n));
					draw_list->AddRect(cell_p1, cell_p2, glyph ? IM_COL32(255, 255, 255, 100) : IM_COL32(255, 255, 255, 50));
					if (glyph)
						font->RenderChar(draw_list, cell_size, cell_p1, glyph_col, (ImWchar)(base + n));
					if (glyph && ImGui::IsMouseHoveringRect(cell_p1, cell_p2))
					{
						ImGui::BeginTooltip();
						ImGui::Text("Codepoint: U+%04X", base + n);
						ImGui::Separator();
						ImGui::Text("Visible: %d", glyph->Visible);
						ImGui::Text("AdvanceX: %.1f", glyph->AdvanceX);
						ImGui::Text("Pos: (%.2f,%.2f)->(%.2f,%.2f)", glyph->X0, glyph->Y0, glyph->X1, glyph->Y1);
						ImGui::Text("UV: (%.3f,%.3f)->(%.3f,%.3f)", glyph->U0, glyph->V0, glyph->U1, glyph->V1);
						ImGui::EndTooltip();
					}
				}
				ImGui::Dummy(ImVec2((cell_size + cell_spacing) * 16, (cell_size + cell_spacing) * 16));
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	*/

}; // namespace
