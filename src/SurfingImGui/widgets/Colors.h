#pragma once

#include "ofMain.h"

//------------------------------

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "SurfingGuiConstants.h"

#include "SurfingHelpers.h"

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

//--

//// https://github.com/companje/ofxExtras/blob/master/src/ofxExtras.cpp
//	void ofxSetColorHSB(int h, int s, int b, int a) {
//    unsigned char hsv[] = {(unsigned char)h,(unsigned char)s,(unsigned char)b};
//    unsigned char rgb[] = {0,0,0};
//
//    if (hsv[2] == 0); // black
//	else if (hsv[1] == 0) { rgb[0]=b;  rgb[1]=b; rgb[2]=b; } // grays
//    else {
//        float h = hsv[0] * 6. / 255.;
//        float s = hsv[1] / 255.;
//        int hCategory = (int) floorf(h);
//        float hRemainder = h - hCategory;
//        unsigned char pv = (unsigned char) ((1.f - s) * hsv[2]);
//        unsigned char qv = (unsigned char) ((1. - s * hRemainder) * hsv[2]);
//        unsigned char tv = (unsigned char) ((1. - s * (1.-hRemainder)) * hsv[2]);
//        switch (hCategory) {
//            case 0: rgb[0] = hsv[2]; rgb[1] = tv; rgb[2] = pv; break; //r
//            case 1: rgb[0] = qv; rgb[1] = hsv[2]; rgb[2] = pv; break; //g
//            case 2: rgb[0] = pv; rgb[1] = hsv[2]; rgb[2] = tv; break;
//            case 3: rgb[0] = pv; rgb[1] = qv; rgb[2] = hsv[2]; break; //b
//            case 4: rgb[0] = tv; rgb[1] = pv; rgb[2] = hsv[2]; break;
//            case 5: rgb[0] = hsv[2]; rgb[1] = pv; rgb[2] = qv; break; //back to r
//        }
//    }
//    ofSetColor(rgb[0],rgb[1],rgb[2],a);
//}