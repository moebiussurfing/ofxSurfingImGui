#pragma once

#include "ofMain.h"

//------------------------------

#include "ofxImGui.h"
#include "imgui_internal.h"
#include "GuiConstants.h"
#include "ofxSurfingHelpers.h"
#include "LayoutHelpers.h"

//------------------------------

namespace ofxImGuiSurfing
{
	template<typename ParameterType>
	bool addColorBox(ofParameter<ParameterType>& p, ImVec2 sz = ImVec2(-1, -1), bool bNoAlpha = false)
	{
		string name = p.getName();
		string tag1 = "##POP" + name;
		string tag2 = "##PICK" + name;

		const auto& info = typeid(ParameterType);
		bool isColor = false;
		bool isFloatColor = false;
		if (info == typeid(ofColor))
		{
			isColor = true;
		}
		else if (info == typeid(ofFloatColor))
		{
			isFloatColor = true;
		}
		else
		{
			ofLogWarning("ofxSurfingImGui") << "Color: ofParam type named " + name + " is not an ofColor or an ofFloatColor!";
			return false;
		}

		//--

		bool bReturn = false;

		float w, h;
		if (sz.x == -1 && sz.y == -1)
		{
			w = ofxImGuiSurfing::getWidgetsWidth(1);
			h = ofxImGuiSurfing::getWidgetsHeightUnit();
		}
		else
		{
			w = sz.x;
			h = sz.y;
		}

		ofParameter<ofFloatColor> c;
		c.set(p.getName(),
			ofFloatColor(
				p.get().r / 255.f,
				p.get().g / 255.f,
				p.get().b / 255.f,
				p.get().a / 255.f),
			ofFloatColor(0, 0, 0, 0),
			ofFloatColor(1.f, 1.f, 1.f, 1.f)
		);


		ofFloatColor tmpRef;
		if (isFloatColor) tmpRef = p.get();
		else if (isColor) tmpRef = c.get();

		ImGuiColorEditFlags flags;
		flags = ImGuiColorEditFlags_None;
		//flags |= ImGuiColorEditFlags_NoLabel;
		//flags |= ImGuiColorEditFlags_NoTooltip;
		if (bNoAlpha) flags |= ImGuiColorEditFlags_NoAlpha;

		if (ImGui::ColorButton(name.c_str(), tmpRef, flags, ImVec2(w, h)))
		{
			ImGui::OpenPopup(tag1.c_str());

			bReturn = true;
		}

		if (ImGui::BeginPopup(tag1.c_str()))
		{
			if (bNoAlpha) {
				if (ImGui::ColorPicker3(tag2.c_str(), &tmpRef.r, ImGuiColorEditFlags_None))
				{
					if (isFloatColor) {
						p.set(tmpRef);
					}
					else if (isColor) {
						p.set(ofColor(tmpRef));
					}

					bReturn = true;
				}
			}
			else {
				if (ImGui::ColorPicker4(tag2.c_str(), &tmpRef.r, ImGuiColorEditFlags_None, NULL))
				{
					if (isFloatColor) {
						p.set(tmpRef);
					}
					else if (isColor) {
						p.set(ofColor(tmpRef));
					}

					bReturn = true;
				}
			}
			ImGui::EndPopup();
		}

		return bReturn;
	}
};
