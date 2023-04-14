#pragma once

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "Combos.h"

#include "surfingThemes.h"

using namespace ImGui;

//---

namespace ofxImGuiSurfing
{
	//----

	//--------------------------------------------------------------
	inline bool drawWidgetsThemeSelector(const char* label)
	{
		static int style_idx = -1;
		int i = style_idx;

		//TODO: should be static..
		std::vector<std::string> values;

		values.clear();
		values.push_back("Dark");
		values.push_back("Light");
		values.push_back("Classic");
		values.push_back("moebiusSurfingV2");
		values.push_back("moebiusSurfing");
		values.push_back("moebiusSurfing Blue");
		values.push_back("Grey");
		values.push_back("Sequentity");
		values.push_back("Olekristensen");
		values.push_back("FlatDryWineGreen");
		values.push_back("T3");
		values.push_back("ModernDark");
		values.push_back("Blender");
		values.push_back("Cyberpunk");
		values.push_back("Nord");
		values.push_back("Unreal");
		values.push_back("VisualStudioRounded");
		values.push_back("VisualStudio");
		values.push_back("Photoshop");
		values.push_back("MaterialFlat");
		values.push_back("Enemymouse");
		values.push_back("DeepDark");
		values.push_back("Darcula");
		values.push_back("Xemu");
		values.push_back("Yave");
		values.push_back("ImStyle");
		values.push_back("AiekickGreenBlue");
		values.push_back("AiekickRedDark");
		values.push_back("DraculaStyle");
		values.push_back("Maksasj");

		bool b1 = false;
		bool b2 = false;

		ImVec2 sz1(ImGui::GetContentRegionAvail().x, ImGui::GetFrameHeight());
		ImVec2 sz2(ImGui::GetContentRegionAvail().x / 2 - ImGui::GetStyle().ItemSpacing.x / 2, 2.f * ImGui::GetFrameHeight());

		//--

		bool bL = ImGui::IsKeyPressed(ImGuiKey_LeftArrow);
		bool bR = ImGui::IsKeyPressed(ImGuiKey_RightArrow);

		// Browse

		ImGui::PushButtonRepeat(true);
		if (ImGui::Button("<", sz2) || bL) {
			i--;
			i = ofClamp(i, 0, values.size() - 1);
			style_idx = i;
			ofLogNotice("ofxSurfingImGui") << "Index: " << i;
			b1 = true;
		}
		ImGui::SameLine();
		if (ImGui::Button(">", sz2) || bR) {
			i++;
			i = ofClamp(i, 0, values.size() - 1);
			style_idx = i;
			ofLogNotice("ofxSurfingImGui") << "Index: " << i;
			b1 = true;
		}
		ImGui::PopButtonRepeat();
		ImGui::Spacing();

		//--

		// Combo

		string name = "Theme";
		float w = ImGui::CalcTextSize(name.c_str()).x + /*ImGui::GetStyle().WindowPadding.x +*/ ImGui::GetStyle().ItemSpacing.x + ImGui::GetStyle().ItemInnerSpacing.x;

		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - w);
		b2 = (ofxImGuiSurfing::VectorCombo(name.c_str(), &i, values, 1));
		ImGui::PopItemWidth();

		if (b1 || b2)
		{
			i = ofClamp(i, 0, values.size() - 1);//avoid crashes
			style_idx = i;
			ofLogNotice("ofxSurfingImGui") << "Combo: " << i;

			switch (style_idx)
			{
			case 0: ImGui::StyleColorsDark(); break;
			case 1: ImGui::StyleColorsLight(); break;
			case 2: ImGui::StyleColorsClassic(); break;
			case 3: ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2(); break;
			case 4: ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing(); break;
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
			}
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------
	inline void drawThemeSelector(ImGuiStyle* ref)
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
		if (ofxImGuiSurfing::drawWidgetsThemeSelector("Colors##Selector")) ref_saved_style = style;

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::ShowFontSelector("Fonts##Selector");
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
