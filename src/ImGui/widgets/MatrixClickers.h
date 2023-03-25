#pragma once


/*

	TODO:

*/


#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "imconfig.h"

#include "GuiConstants.h"

//--

namespace ofxImGuiSurfing
{
	using namespace ImGui;

	//--

	// Preset Clicker Matrix Buttons
	// Index will change when a box is clicked
	// Notice that index must start in 0 like we use on vectors!
	//inline bool AddMatrixClicker(ofParameter<int>& _index, string label = "CLICKER", bool bOpen = false, bool bResponsive = true, int amountBtRow = 3)
	//--------------------------------------------------------------
	inline bool AddMatrixClicker(ofParameter<int>& _index, bool bResponsive = true, int amountBtRow = 3, const bool bDrawBorder = false, float __h = -1, string toolTip = "")
	{
		const int _amt = _index.getMax() - _index.getMin() + 1;
		if (amountBtRow > _amt) amountBtRow = _amt;

		ImGui::Spacing();

		/*
		//TODO:
		// Dragging colors
		enum Mode
		{
			Mode_Copy = 0,
			Mode_Swap
		};
		static int mode = 1;

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &c, sizeof(int));
			if (mode == Mode_Copy) { ImGui::Text("Copy %s", ofToString(c).c_str()); }
			if (mode == Mode_Swap) { ImGui::Text("Swap %s", ofToString(c).c_str()); }

			ImGui::EndDragDropSource();
		}
		*/

		//--

		bool cChanged = false;

		if (__h == -1)
		{
			__h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
		}

		ImGuiStyle* style = &ImGui::GetStyle();
		float a = 0.3;
		ImVec4 borderLineColor = style->Colors[ImGuiCol_TextDisabled];
		float borderLineWidth = 1.0;

		string sid = "##MatrixClicker_" + _index.getName();
		ImGui::PushID(sid.c_str());

		{
			int gap = 1;
			float __spcx = ImGui::GetStyle().ItemSpacing.x;
			float __w100 = ImGui::GetContentRegionAvail().x - gap;

			float _sizex = 5;

			if (!bResponsive) _sizex = 40;
			else
			{
				_sizex = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
			}

			int _amt = _index.getMax() + 1;
			float sizex;

			if (_amt > amountBtRow)
			{
				sizex = _sizex;
			}
			else
			{
				if (_amt == 1)
				{
					sizex = __w100;
				}
				else
				{
					sizex = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
				}
			}

			sizex = MAX(5, sizex);

			//-

			// Toggle button matrix

			ImVec2 sizebt(sizex, __h);

			// Manually wrapping
			// (we should eventually provide this as an automatic layout feature, but for now you can do it manually)

			ImGuiStyle& style2 = ImGui::GetStyle();
			float _windowVisible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

			for (int n = 0; n < _amt; n++)
			{
				bool bBorder = false;

				ImGui::PushID(n);
				{
					string name = ofToString(ofToString(n));

					// Customize colors
					{
						// When selected / active
						if (_index.get() == n)
						{
							if (bDrawBorder) bBorder = true;

							// Changes the colors
							const ImVec4 colorActive = style2.Colors[ImGuiCol_ButtonActive];
							ImGui::PushStyleColor(ImGuiCol_Button, colorActive);
							// Border with alpha
							const ImVec4 colorBorder = ImVec4(0, 0, 0, 0.75f); // hardcoded
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}
						else
						{
							// Do not changes the colors
							const ImVec4 colorButton = style2.Colors[ImGuiCol_Button];
							ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
							const ImVec4 colorBorder = style2.Colors[ImGuiCol_Border];
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}

						// Border
						if (bBorder)
						{
							ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(borderLineColor.x, borderLineColor.y, borderLineColor.z, borderLineColor.w * a));
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
						}

						// Draw button
						if (ImGui::Button(name.c_str(), sizebt))
						{
							_index = n;
							cChanged = true;
						}

						if (toolTip != "")
						{
							ofxImGuiSurfing::AddTooltip2(toolTip);
						}

						// Border
						if (bBorder)
						{
							ImGui::PopStyleVar(1);
							ImGui::PopStyleColor();
						}

						// Customize colors
						ImGui::PopStyleColor(2);
					}

					float last_button_x2 = ImGui::GetItemRectMax().x;
					float next_button_x2 = last_button_x2 + style2.ItemSpacing.x + sizebt.x; // Expected position if next button was on same line

					if (n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
				}
				ImGui::PopID();
			}
		}

		ImGui::PopID();
		ImGui::Spacing();

		if (cChanged) ofLogNotice("ofxSurfingImGui") << "Clicked Matrix " << _index.get();

		return cChanged;
	}

	//--------------------------------------------------------------
	inline bool AddMatrixClicker(ofParameter<int>& _index, float __h)
	{
		bool bResponsive = true;
		int amountBtRow = 3;
		const bool bDrawBorder = false;
		string toolTip = "";
		return AddMatrixClicker(_index, bResponsive, amountBtRow, bDrawBorder, __h, toolTip);
	}

	//TODO: 
	// pass labels vector as a pointer or reference..
	// group all methods to a template or something

	//--------------------------------------------------------------
	inline bool AddMatrixClickerLabels(ofParameter<int>& _index, const std::vector<char> labels, bool bResponsive = true, int amountBtRow = 3, const bool bDrawBorder = false, float __h = -1, string toolTip = "", bool bFlip = false)
	{
		const int _amt = _index.getMax() - _index.getMin() + 1;
		if (amountBtRow > _amt) amountBtRow = _amt;

		ImGui::Spacing();

		bool cChanged = false;

		if (__h == -1)
		{
			__h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
		}

		ImGuiStyle* style = &ImGui::GetStyle();
		float a = 0.3;
		ImVec4 borderLineColor = style->Colors[ImGuiCol_TextDisabled];
		float borderLineWidth = 1.0;

		string sid = "##MatrixClicker_" + _index.getName();
		ImGui::PushID(sid.c_str());
		{
			int gap = 1;
			float __spcx = ImGui::GetStyle().ItemSpacing.x;
			float __w100 = ImGui::GetContentRegionAvail().x - gap;

			float _sizex = 5;

			if (!bResponsive) _sizex = 40;
			else
			{
				_sizex = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
			}

			int _amt = _index.getMax() + 1;
			float __w;

			if (_amt > amountBtRow)
			{
				__w = _sizex;
			}
			else
			{
				if (_amt == 1)
				{
					__w = __w100;
				}
				else
				{
					__w = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
				}
			}

			__w = MAX(5, __w);

			//-

			// Toggle button matrix

			ImVec2 sizebt(__w, __h);

			// Manually wrapping
			// (we should eventually provide this as an automatic layout feature, but for now you can do it manually)

			ImGuiStyle& style2 = ImGui::GetStyle();
			float _windowVisible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

			int _inc;
			if (!bFlip) {
				_inc = 1;
			}
			else {
				_inc = -1;
			}

			for (int _n = 0; _n < _amt; _n++)
			{
				bool bBorder = false;

				int n;
				if (bFlip) {
					n = _amt - 1 - _n;
				}
				else {
					n = _n;
				}

				ImGui::PushID(n);
				{
					string name;

					if (labels.size() == 0) name = ofToString(ofToString(n));
					else
					{
						if (n < labels.size()) name = (labels[n]);
						else name = ofToString(ofToString(n));
					}

					// Customize colors
					{
						// When selected / active
						if (_index.get() == n)
						{
							if (bDrawBorder) bBorder = true;

							// Changes the colors
							const ImVec4 colorActive = style2.Colors[ImGuiCol_ButtonActive];
							ImGui::PushStyleColor(ImGuiCol_Button, colorActive);
							// Border with alpha
							const ImVec4 colorBorder = ImVec4(0, 0, 0, 0.75f); // hardcoded
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}
						else
						{
							// Do not changes the colors
							const ImVec4 colorButton = style2.Colors[ImGuiCol_Button];
							ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
							const ImVec4 colorBorder = style2.Colors[ImGuiCol_Border];
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}

						// Border
						if (bBorder)
						{
							ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(borderLineColor.x, borderLineColor.y, borderLineColor.z, borderLineColor.w * a));
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
						}

						// Draw button
						if (ImGui::Button(name.c_str(), sizebt))
						{
							_index = n;
							cChanged = true;
						}

						if (toolTip != "") {

							ofxImGuiSurfing::AddTooltip2(toolTip);
						}

						// Border
						if (bBorder)
						{
							ImGui::PopStyleVar(1);
							ImGui::PopStyleColor();
						}

						// Customize colors
						ImGui::PopStyleColor(2);
					}

					// The last button width
					float last_button_x2 = ImGui::GetItemRectMax().x;
					// Expected position if next button was on same line
					float next_button_x2 = last_button_x2 + style2.ItemSpacing.x + sizebt.x;

					if (!bFlip) {
						if (n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					}
					else {
						if (_n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					}
				}
				ImGui::PopID();
			}
		}
		ImGui::PopID();

		if (cChanged) ofLogNotice("ofxSurfingImGui") << "Clicked Matrix " << _index.get();

		return cChanged;
	}

	//--------------------------------------------------------------
	inline bool AddMatrixClickerLabels(ofParameter<int>& _index, const std::vector<char> labels, const std::vector<ofColor> colors, bool bResponsive = true, int amountBtRow = 3, const bool bDrawBorder = false, float __h = -1, string toolTip = "", bool bFlip = false)
	{
		const int _amt = _index.getMax() - _index.getMin() + 1;
		if (amountBtRow > _amt) amountBtRow = _amt;

		ImGui::Spacing();

		bool cChanged = false;

		if (__h == -1)
		{
			__h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
		}

		float a = 0.4f;
		//float a = 0.3f;

		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4 borderLineColor = style->Colors[ImGuiCol_TextDisabled];
		float borderLineWidth = 1.0;

		string sid = "##MatrixClicker_" + _index.getName();
		ImGui::PushID(sid.c_str());
		{
			int gap = 1;
			float __spcx = ImGui::GetStyle().ItemSpacing.x;
			float __w100 = ImGui::GetContentRegionAvail().x - gap;

			float _sizex = 5;

			if (!bResponsive) _sizex = 40;
			else
			{
				_sizex = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
			}

			int _amt = _index.getMax() + 1;
			float __w;

			if (_amt > amountBtRow)
			{
				__w = _sizex;
			}
			else
			{
				if (_amt == 1)
				{
					__w = __w100;
				}
				else
				{
					__w = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
				}
			}

			__w = MAX(5, __w);

			//-

			// Toggle button matrix

			ImVec2 sizebt(__w, __h);

			// Manually wrapping
			// (we should eventually provide this as an automatic layout feature, but for now you can do it manually)

			ImGuiStyle& style2 = ImGui::GetStyle();
			float _windowVisible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

			int _inc;
			if (!bFlip) {
				_inc = 1;
			}
			else {
				_inc = -1;
			}

			for (int _n = 0; _n < _amt; _n++)
			{
				bool bBorder = false;
				bool bColored = (_n < colors.size());

				int n;
				if (bFlip) {
					n = _amt - 1 - _n;
				}
				else {
					n = _n;
				}

				ImGui::PushID(n);
				{
					string name;

					if (labels.size() == 0) name = ofToString(ofToString(n));
					else
					{
						if (n < labels.size()) name = (labels[n]);
						else name = ofToString(ofToString(n));
					}

					// Customize colors
					{
						// When selected / active
						if (_index.get() == n)
						{
							if (bDrawBorder) bBorder = true;

							// Changes the colors
							const ImVec4 colorActive = style2.Colors[ImGuiCol_ButtonActive];
							ImGui::PushStyleColor(ImGuiCol_Button, colorActive);
							// Border with alpha
							const ImVec4 colorBorder = ImVec4(0, 0, 0, 0.75f); // hardcoded
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}
						else
						{
							// Do not changes the colors
							const ImVec4 colorButton = style2.Colors[ImGuiCol_Button];
							ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
							const ImVec4 colorBorder = style2.Colors[ImGuiCol_Border];
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}

						// Colored
						if (bColored)
						{
							ImVec4 _c;
							if (n < colors.size()) {
								if (bFlip)_c = colors[colors.size() - n - 1];
								else _c = colors[n];
							}
							else _c = style2.Colors[ImGuiCol_Text];
							ImGui::PushStyleColor(ImGuiCol_Text, _c);

							// Border
							if (bBorder)
							{
								ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(_c.x, _c.y, _c.z, _c.w * a));
								ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
							}
						}
						else
						{
							// Border
							if (bBorder)
							{
								ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(borderLineColor.x, borderLineColor.y, borderLineColor.z, borderLineColor.w * a));
								ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
							}
						}

						// Draw button
						if (ImGui::Button(name.c_str(), sizebt))
						{
							_index = n;
							cChanged = true;
						}

						// Border
						if (bBorder)
						{
							ImGui::PopStyleVar(1);
							ImGui::PopStyleColor();
						}

						// Customize colors
						ImGui::PopStyleColor(2);

						// Colored
						if (bColored) {
							ImGui::PopStyleColor();
						}

						if (toolTip != "") {

							ofxImGuiSurfing::AddTooltip2(toolTip);
						}
					}

					// The last button width
					float last_button_x2 = ImGui::GetItemRectMax().x;
					// Expected position if next button was on same line
					float next_button_x2 = last_button_x2 + style2.ItemSpacing.x + sizebt.x;

					if (!bFlip)
					{
						if (n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					}
					else
					{
						if (_n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					}
				}
				ImGui::PopID();
			}
		}
		ImGui::PopID();

		if (cChanged) ofLogNotice("ofxSurfingImGui") << "Clicked Matrix " << _index.get();

		return cChanged;
	}

	//--------------------------------------------------------------
	inline bool AddMatrixClickerLabelsStrings(ofParameter<int>& _index, const std::vector<string> labels, bool bResponsive = true, int amountBtRow = 3, const bool bDrawBorder = true, float __h = -1, bool bSpaced = true, string toolTip = "", bool bFlip = false)
	{
		const int _amt = _index.getMax() - _index.getMin() + 1;
		if (amountBtRow > _amt) amountBtRow = _amt;

		if (bSpaced) ImGui::Spacing();

		bool cChanged = false;

		// default height size for the toggle buttons
		if (__h == -1)
		{
			__h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
		}

		ImGuiStyle* style = &ImGui::GetStyle();
		float a = 0.3;
		ImVec4 borderLineColor = style->Colors[ImGuiCol_TextDisabled];
		float borderLineWidth = 1.0;

		string sid = "##MatrixClicker_" + _index.getName();
		ImGui::PushID(sid.c_str());

		{
			int gap = 1;
			float __spcx = ImGui::GetStyle().ItemSpacing.x;
			float __w100 = ImGui::GetContentRegionAvail().x - gap;

			float ___w = 5;

			if (!bResponsive) ___w = 40;
			else
			{
				___w = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
			}

			int _amt = _index.getMax() + 1;
			float __w;

			if (_amt > amountBtRow)
			{
				__w = ___w;
			}
			else
			{
				if (_amt == 1)
				{
					__w = __w100;
				}
				else
				{
					__w = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
				}
			}

			__w = MAX(5, __w);

			//-

			// Toggle button matrix

			ImVec2 sizebt(__w, __h);

			// Manually wrapping
			// (we should eventually provide this 
			// as an automatic layout feature, 
			// but for now you can do it manually)

			ImGuiStyle& style2 = ImGui::GetStyle();
			float _windowVisible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

			int _inc;
			if (!bFlip) {
				_inc = 1;
			}
			else {
				_inc = -1;
			}

			for (int _n = 0; _n < _amt; _n++)
			{
				bool bBorder = false;

				int n;
				if (bFlip) {
					n = _amt - 1 - _n;
				}
				else {
					n = _n;
				}

				ImGui::PushID(n);
				{
					string name;

					if (labels.size() == 0) name = ofToString(ofToString(n));
					else
					{
						if (n < labels.size()) name = (labels[n]);
						else name = ofToString(ofToString(n));
					}

					// Customize colors
					{
						// When selected / active
						if (_index.get() == n)
						{
							if (bDrawBorder) bBorder = true;

							// Changes the colors
							const ImVec4 colorActive = style2.Colors[ImGuiCol_ButtonActive];
							ImGui::PushStyleColor(ImGuiCol_Button, colorActive);
							// Border with alpha
							const ImVec4 colorBorder = ImVec4(0, 0, 0, 0.75f); // hardcoded
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}
						else
						{
							// Do not changes the colors
							const ImVec4 colorButton = style2.Colors[ImGuiCol_Button];
							ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
							const ImVec4 colorBorder = style2.Colors[ImGuiCol_Border];
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}

						// Border
						if (bBorder)
						{
							ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(borderLineColor.x, borderLineColor.y, borderLineColor.z, borderLineColor.w * a));
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
						}

						// Draw button
						if (ImGui::Button(name.c_str(), sizebt))
						{
							_index = n;
							cChanged = true;
						}

						// Border
						if (bBorder)
						{
							ImGui::PopStyleVar(1);
							ImGui::PopStyleColor();
						}

						// Customize colors
						ImGui::PopStyleColor(2);

						if (toolTip != "") {

							ofxImGuiSurfing::AddTooltip2(toolTip);
						}
					}

					float last_button_x2 = ImGui::GetItemRectMax().x;
					float next_button_x2 = last_button_x2 + style2.ItemSpacing.x + sizebt.x; // Expected position if next button was on same line

					//if (n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					if (!bFlip) {
						if (n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					}
					else {
						if (_n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					}
				}
				ImGui::PopID();
			}
		}

		ImGui::PopID();

		if (cChanged) ofLogNotice("ofxSurfingImGui") << "Clicked Matrix " << _index.get();

		//if (bSpaced) ImGui::Spacing();
		//if (bSpaced) ImGui::Spacing();

		return cChanged;
	}

	//--------------------------------------------------------------
	inline bool AddMatrixClickerLabelsStrings(ofParameter<int>& _index, const std::vector<string> labels, const std::vector<ofColor> colors, bool bResponsive = true, int amountBtRow = 3, const bool bDrawBorder = true, float __h = -1, bool bSpaced = true, string toolTip = "", bool bFlip = false)
	{
		const int _amt = _index.getMax() - _index.getMin() + 1;
		if (amountBtRow > _amt) amountBtRow = _amt;

		if (bSpaced) ImGui::Spacing();

		bool cChanged = false;

		// default height size for the toggle buttons
		if (__h == -1)
		{
			__h = 2 * ofxImGuiSurfing::getWidgetsHeightUnit();
		}

		ImGuiStyle* style = &ImGui::GetStyle();
		float a = 0.3;
		ImVec4 borderLineColor = style->Colors[ImGuiCol_TextDisabled];
		float borderLineWidth = 1.0;

		string sid = "##MatrixClicker_" + _index.getName();
		ImGui::PushID(sid.c_str());

		{
			int gap = 1;
			float __spcx = ImGui::GetStyle().ItemSpacing.x;
			float __w100 = ImGui::GetContentRegionAvail().x - gap;

			float ___w = 5;

			if (!bResponsive) ___w = 40;
			else
			{
				___w = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
			}

			int _amt = _index.getMax() + 1;
			float __w;

			if (_amt > amountBtRow)
			{
				__w = ___w;
			}
			else
			{
				if (_amt == 1)
				{
					__w = __w100;
				}
				else
				{
					__w = (__w100 - __spcx * (amountBtRow - 1)) / amountBtRow;
				}
			}

			__w = MAX(5, __w);

			//-

			// Toggle button matrix

			ImVec2 sizebt(__w, __h);

			// Manually wrapping
			// (we should eventually provide this as an automatic layout feature, but for now you can do it manually)

			ImGuiStyle& style2 = ImGui::GetStyle();
			float _windowVisible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

			int _inc;
			if (!bFlip) {
				_inc = 1;
			}
			else {
				_inc = -1;
			}

			for (int _n = 0; _n < _amt; _n++)
			{
				bool bBorder = false;
				bool bColored = (_n < colors.size());

				int n;
				if (bFlip) {
					n = _amt - 1 - _n;
				}
				else {
					n = _n;
				}

				ImGui::PushID(n);
				{
					string name;

					if (labels.size() == 0) name = ofToString(ofToString(n));
					else
					{
						if (n < labels.size()) name = (labels[n]);
						else name = ofToString(ofToString(n));
					}

					// Customize colors
					{
						// When selected / active
						if (_index.get() == n)
						{
							if (bDrawBorder) bBorder = true;

							// Changes the colors
							const ImVec4 colorActive = style2.Colors[ImGuiCol_ButtonActive];
							ImGui::PushStyleColor(ImGuiCol_Button, colorActive);
							// Border with alpha
							const ImVec4 colorBorder = ImVec4(0, 0, 0, 0.75f); // hardcoded
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}
						else
						{
							// Do not changes the colors
							const ImVec4 colorButton = style2.Colors[ImGuiCol_Button];
							ImGui::PushStyleColor(ImGuiCol_Button, colorButton);
							const ImVec4 colorBorder = style2.Colors[ImGuiCol_Border];
							ImGui::PushStyleColor(ImGuiCol_Border, colorBorder);
						}

						// Colored
						if (bColored)
						{
							ImVec4 _c;
							if (n < colors.size()) {
								if (bFlip)_c = colors[colors.size() - n - 1];
								else _c = colors[n];
							}
							else _c = style2.Colors[ImGuiCol_Text];
							ImGui::PushStyleColor(ImGuiCol_Text, _c);

							// Border
							if (bBorder)
							{
								ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(_c.x, _c.y, _c.z, _c.w * a));
								ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
							}
						}
						else
						{
							// Border
							if (bBorder)
							{
								ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(borderLineColor.x, borderLineColor.y, borderLineColor.z, borderLineColor.w * a));
								ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth);
							}
						}

						// Draw button
						if (ImGui::Button(name.c_str(), sizebt))
						{
							_index = n;
							cChanged = true;
						}

						// Border
						if (bBorder)
						{
							ImGui::PopStyleVar(1);
							ImGui::PopStyleColor();
						}

						// Customize colors
						ImGui::PopStyleColor(2);

						// Colored
						if (bColored) {
							ImGui::PopStyleColor();
						}

						if (toolTip != "") {

							ofxImGuiSurfing::AddTooltip2(toolTip);
						}
					}

					float last_button_x2 = ImGui::GetItemRectMax().x;
					float next_button_x2 = last_button_x2 + style2.ItemSpacing.x + sizebt.x; // Expected position if next button was on same line

					//if (n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					if (!bFlip)
					{
						if (n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					}
					else
					{
						if (_n + 1 < _amt && next_button_x2 < _windowVisible_x2) ImGui::SameLine();
					}
				}
				ImGui::PopID();
			}
		}

		ImGui::PopID();

		if (cChanged) ofLogNotice("ofxSurfingImGui") << "Clicked Matrix " << _index.get();

		//if (bSpaced) ImGui::Spacing();
		//if (bSpaced) ImGui::Spacing();

		return cChanged;
	}

};