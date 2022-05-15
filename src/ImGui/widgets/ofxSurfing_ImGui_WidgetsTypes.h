
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"

#include "ofxSurfing_ImGui_ofHelpers.h"
#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_WidgetsTypesConstants.h"
#include "ofxSurfing_ImGui_WidgetsTypesUniqueNames.h"

//-

#include <list>
#include <iostream>
#include <boost/range/adaptor/reversed.hpp>

//#define HEIGHT_SCROLL_GROUP 200
#define HEIGHT_SCROLL_GROUP 400

//-

namespace ofxImGuiSurfing
{
	class ofxSurfing_ImGui_WidgetsTypes
	{
		//--

		// Widgets Sizes
		// Common sizes to use when recalculating layout dimensions.

	private:

		float _spcx;
		float _spcy;
		float _w100;
		float _w50;
		float _w33;
		float _w25;
		float _w99;
		float _h100;
		float _h;

		// -> This common sizes must be updated during draw to refresh when window panels resizing 
		// or to addapt to tree/groups or indentation changes.

	public:

		ofParameter<bool> bMouseWheel{ "MouseWheel", false };

		//--

	private:

		// Refresh current panel shape to update widgets sizes.
		//--------------------------------------------------------------
		void refreshPanelShape(bool bWithScroll = false)
		{
			ofxImGuiSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h, bWithScroll);
		}
		//--------------------------------------------------------------
		void refresh(bool bWithScroll = false) // short name
		{
			refreshPanelShape(bWithScroll);
		}

	public:

		//--------------------------------------------------------------
		void refreshLayout(bool bWithScroll = false) // short name
		{
			refreshPanelShape(bWithScroll);
		}

		//-

		//--------------------------------------------------------------
		class SurfingImGuiTypes_Style
		{
		public:
			std::string name = "-1";
			SurfingImGuiTypes type = OFX_IM_DEFAULT;
			int amtPerRow = 1;
			bool bSameLine = false;
			int spacing = -1;
		};

		//-

		//--------------------------------------------------------------
		class SurfingImGuiTypesGroup_Style
		{
		public:
			std::string name = "-1";
			SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
		};

		//-

		// To queue the styles for each param here
		vector<SurfingImGuiTypes_Style> widgetsStyles;

		// To queue the group styles
		vector<SurfingImGuiTypesGroup_Style> groupsStyles;

		// To queue all the rendered params to pushId's
		ofParamUniqueName uniqueName;

		//--------------------------------------------------------------
		void resetUniqueNames() {
			uniqueName.reset();
		}

		//--------------------------------------------------------------
		ofxSurfing_ImGui_WidgetsTypes()
		{
			widgetsStyles.clear();

			uniqueName.reset();
		}

		//-

		//--------------------------------------------------------------
		SurfingImGuiTypes_Style getStyle(ofAbstractParameter& aparam) {

			// https://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop
			//std::list<int> x{ 2, 3, 5, 7, 11, 13, 17, 19 };
			//for (auto i : boost::adaptors::reverse(x))
			//	std::cout << i << '\n';
			//for (auto i : x)
			//	std::cout << i << '\n';
			//for (auto c : boost::adaptors::reverse(widgetsStyles)) // reverse?

			for (auto &c : widgetsStyles)
			{
				if (c.name == aparam.getName()) // param was added to the queue
				{
					return c;
				}
			}

			//-

			// Style not found for this param:
			// if return has not been called yet here,
			// then there's no conf added (AddStyle) for the parameter
			// we return a kind of error type to be detected
			// and to be drawn with the default style.
			SurfingImGuiTypes_Style cError;
			return cError;

			//SurfingImGuiTypes_Style confDefault;
			//confDefault.name = aparam.getName();
			//confDefault.bSameLine = false;
			//confDefault.amtPerRow = 1;
			//confDefault.spacing = -1;
			//return confDefault;
		}

		//-

		//--------------------------------------------------------------
		SurfingImGuiTypesGroup_Style getStyleGroup(ofParameterGroup& group) {
			for (auto &c : groupsStyles)
			{
				if (c.name == group.getName()) // param was added to the queue
				{
					return c;
				}
			}

			SurfingImGuiTypesGroup_Style cError;
			return cError;
		}

		//-

	public:

		// Queue a customization config for future populate a param widget
		//--------------------------------------------------------------
		void AddStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		{
			SurfingImGuiTypes_Style c;
			c.name = aparam.getName();
			c.type = type;
			c.bSameLine = bSameLine;
			c.amtPerRow = amtPerRow;
			c.spacing = spacing;

			widgetsStyles.push_back(c);
		}
		// This call by name is usefull when the param style is out of the current scope
		//--------------------------------------------------------------
		void AddStyle(std::string name, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		{
			SurfingImGuiTypes_Style c;
			c.name = name;
			c.type = type;
			c.bSameLine = bSameLine;
			c.amtPerRow = amtPerRow;
			c.spacing = spacing;

			widgetsStyles.push_back(c);
		}

		//-

	public:

		// Queue a customization config for future populate a group
		//--------------------------------------------------------------
		void AddStyleGroup(ofParameterGroup& group, SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
		{
			SurfingImGuiTypesGroup_Style c;
			c.name = group.getName();
			c.type = type;
			c.flags = flags;

			groupsStyles.push_back(c);
		}
		//--------------------------------------------------------------
		void AddStyleGroup(std::string name, SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
		{
			SurfingImGuiTypesGroup_Style c;
			c.name = name;
			c.type = type;
			c.flags = flags;

			groupsStyles.push_back(c);
		}

		//--

		// Update styles on runtime
	//private:
		//// Legacy api
		////--------------------------------------------------------------
		//void UpdateStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
		//{
		//	for (auto &c : widgetsStyles)
		//	{
		//		if (c.name == aparam.getName()) // param was in the queue list
		//		{
		//			c.type = type;
		//			c.bSameLine = bSameLine;
		//			c.amtPerRow = amtPerRow;
		//			c.spacing = spacing;
		//			return;
		//		}
		//	}
		//	ofLogWarning(__FUNCTION__) << "Widget " << aparam.getName() << " not found on styles list!";
		//	return;
		//}
		////--------------------------------------------------------------
		//void UpdateStyle(std::string name, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
		//{
		//	for (auto &c : widgetsStyles)
		//	{
		//		if (c.name == name) // param was in the queue list
		//		{
		//			c.type = type;
		//			c.bSameLine = bSameLine;
		//			c.amtPerRow = amtPerRow;
		//			c.spacing = spacing;
		//			return;
		//		}
		//	}
		//	ofLogWarning(__FUNCTION__) << "Widget " << name << " not found on styles list!";
		//	return;
		//}

	public:

		//--------------------------------------------------------------
		void UpdateStyleGroup(std::string name, SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
		{
			for (auto &c : groupsStyles)
			{
				if (c.name == name)
				{
					c.type = type;
					c.flags = flags;
					return;
				}
			}
			ofLogWarning(__FUNCTION__) << "Group " << name << " not found on styles list!";
			return;
		}
		//--------------------------------------------------------------
		void UpdateStyleGroup(ofParameterGroup& group, SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
		{
			for (auto &c : groupsStyles)
			{
				if (c.name == group.getName())
				{
					c.type = type;
					c.flags = flags;
					return;
				}
			}
			ofLogWarning(__FUNCTION__) << "Group " << group.getName() << " not found on styles list!";
			return;
		}

		//TODO:
		// Add style remover

		//----

	public:

		// Update styles on runtime
		//--------------------------------------------------------------
		void UpdateStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		{
			for (auto &c : widgetsStyles)
			{
				if (c.name == aparam.getName()) // param was in the queue list
				{
					c.type = type;
					c.bSameLine = bSameLine;
					c.amtPerRow = amtPerRow;
					c.spacing = spacing;
					return;
				}
			}
			ofLogWarning(__FUNCTION__) << "Widget " << aparam.getName() << " not found on styles list. Added!";
			AddStyle(aparam, type, amtPerRow, bSameLine, spacing);
			return;
		}
		//--------------------------------------------------------------
		void UpdateStyle(std::string name, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		{
			for (auto &c : widgetsStyles)
			{
				if (c.name == name) // param was in the queue list
				{
					c.type = type;
					c.bSameLine = bSameLine;
					c.amtPerRow = amtPerRow;
					c.spacing = spacing;
					return;
				}
			}
			ofLogWarning(__FUNCTION__) << "Widget " << name << " not found on styles list. Added!";
			AddStyle(name, type, amtPerRow, bSameLine, spacing);
			return;
		}

		//----

	public:
		//TODO:
		// If we are not using the Types Engine, we will bypass the creation of widgets on ofxSurfing_ImGui_Helpers
		// then we will populate each widget type as the default appearance!
		//--------------------------------------------------------------
		bool isOperative()
		{
			return (widgetsStyles.size() > 0);
		}
		//--------------------------------------------------------------
		bool isEmpty()
		{
			return (!isOperative());
		}
		//--------------------------------------------------------------
		void clear() {
			widgetsStyles.clear();
			groupsStyles.clear();
		}

		////TODO: GetUniqueName?
		////--------------------------------------------------------------
		//bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars = 255, bool multiline = false)
		//{
		//	auto tmpRef = parameter.get();
		//	char * cString = new char[maxChars];
		//	strcpy(cString, tmpRef.c_str());
		//	auto result = false;
		//	if (multiline)
		//	{
		//		if (ImGui::InputTextMultiline(GetUniqueName(parameter), cString, maxChars))
		//		{
		//			parameter.set(cString);
		//			result = true;
		//		}
		//	}
		//	else if (ImGui::InputText(GetUniqueName(parameter), cString, maxChars))
		//	{
		//		parameter.set(cString);
		//		result = true;
		//	}
		//	delete[] cString;
		//	return result;
		//}

		//-

		//bool Add(ofAbstractParameter& aparam, ofxSurfing_ImGui_WidgetsTypes type) {
		//	Add(bMode1, SurfingImGuiTypesGroups::OFX_IM_TOGGLE_SMALL, 3, true);
		//}

		//-

		//void AddStyle(std::string name, SurfingImGuiTypes type) {
		//	SurfingImGuiTypes_Style e;
		//	e.name = name;
		//	e.type = type;
		//	widgetsStyles.push_back(e);
		//}

		//-

		//--------------------------------------------------------------
		SurfingImGuiTypes getType(ofAbstractParameter& aparam)
		{
			std::string name = aparam.getName();
			SurfingImGuiTypes rtype = SurfingImGuiTypes(OFX_IM_DEFAULT);

			auto type = aparam.type();
			bool isBool = type == typeid(ofParameter<bool>).name();
			if (!isBool) return rtype;

			for (auto w : widgetsStyles)
			{
				if (w.name == name)
				{
					rtype = SurfingImGuiTypes(w.type);
				}
			}

			return rtype;
		}

		//----

		// Render now a parameter with a related ImGui widget with a custom style.
		// Remember that must be called inside an guiManager::Begin/End() !

		//TODO:
		// new api

		//public:
		////-----------------------------------------------------------------
		//bool Add(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		//{
		//	return Add(aparam, type, bSameLine, amtPerRow, spacing);
		//}

	public:

		//-----------------------------------------------------------------
		bool Add(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		{
			// Will flag to true to do the final steps: sameline and spacing configs.
			bool bDone = false;

			// Will flag to notify if the ofParam widget changed.
			bool bReturn = false;

			// Set the next Widget shape size width/height reading from the function arguments:
			float _ww; // widget width
			if (amtPerRow == 2) _ww = _w50; // half size
			else if (amtPerRow == 3) _ww = _w33; // third size
			else if (amtPerRow == 4) _ww = _w25; // quarter size
			else _ww = _w100; // full width

			//----

			// 1. Handle hidden, disabled and inactive tags:

			//-

			// If setted as hidden dont draw, but apply same line and spacing and return
			if (type == OFX_IM_HIDDEN)
			{
				uniqueName.push();
				{
					// Extra options
					if (bSameLine) ImGui::SameLine();
					if (spacing != -1)
					{
						ImGui::Dummy(ImVec2(0.0f, (float)spacing)); // spacing
					}
				}
				uniqueName.pop();

				return false;
			}

			//-

			// If setted as hidden dont draw, but apply same line and spacing and return
			else if (type == OFX_IM_DISABLED)
			{
				uniqueName.push();
				{
					// Extra options
					if (bSameLine) ImGui::SameLine();
					if (spacing != -1)
					{
						float h = ImGui::GetIO().FontDefault->FontSize + ImGui::GetStyle().FramePadding.y * 2;
						ImGui::InvisibleButton("_inv_", ImVec2(10, h), ImGuiButtonFlags_Disabled);

						ImGui::Dummy(ImVec2(0.0f, (float)spacing)); // spacing
					}
				}
				uniqueName.pop();

				return false;
			}

			//----

			// Disable mouse interaction
			else if (type == OFX_IM_INACTIVE)
			{
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);

				bDone = true;
			}

			//--------

			// 2. Detect Type of the ofAbstractParameter:

			auto ptype = aparam.type();

			// Filter expected ofParam Types

			bool isBool = ptype == typeid(ofParameter<bool>).name();
			bool isFloat = ptype == typeid(ofParameter<float>).name();
			bool isInt = ptype == typeid(ofParameter<int>).name();
			bool isString = ptype == typeid(ofParameter<std::string>).name();
			bool isColor = ptype == typeid(ofParameter<ofColor>).name();
			bool isFloatColor = ptype == typeid(ofParameter<ofFloatColor>).name();
			bool isMultiDimVec2 = ptype == typeid(ofParameter<glm::vec2>).name();
			bool isMultiDimVec3 = ptype == typeid(ofParameter<glm::vec3>).name();
			bool isMultiDimVec4 = ptype == typeid(ofParameter<glm::vec4>).name();

			//TODO:
			// is not called with groups here.. ?
			//bool isGroup = ptype == typeid(ofParameterGroup).name();
			//if (isGroup) 
			//{
			//	refreshPanelShape();
			//	return false;
			//}

			//--------

			// 2.1. Bool

			if (isBool)
			{
				ofParameter<bool> p = aparam.cast<bool>();
				auto tmpRef = p.get();

				uniqueName.push();
				{
					switch (type)
					{

					case OFX_IM_INACTIVE:
					{
						// default:
						std::string name = p.getName();
						if (ImGui::Checkbox(p.getName().c_str(), (bool *)&tmpRef))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						bReturn = false;
					}
					break;

					case OFX_IM_DEFAULT:
					case OFX_IM_CHECKBOX:
					{
						// default:
						std::string name = p.getName();
						if (ImGui::Checkbox(p.getName().c_str(), (bool *)&tmpRef))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						bReturn = false;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_BUTTON_SMALL:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_BUTTON:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 1.25f);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_BUTTON_BIG:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 2);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_BUTTON_BIG_XXL:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 3);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_BUTTON_BIG_XXXL:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 4);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

						//--

					case OFX_IM_TOGGLE_SMALL:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 1.25f);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BIG:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 2);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BIG_XXL:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 3);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BIG_XXXL:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 4);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

						//-

					case OFX_IM_TOGGLE_SMALL_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BIG_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 2, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BIG_XXL_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 3, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BIG_XXXL_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 4, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

						//-

					case OFX_IM_TOGGLE_SMALL_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h* 1.25f, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BIG_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 2, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 3, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 4, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

						//--

					case OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI:
						bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p, ImVec2(1.1625f * _h, 0.75f * _h), true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL:
						bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM:
						bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p, ImVec2(2 * _h, 2 * (2 / 3.f) * _h));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;

					case OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG:
						bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p, ImVec2(3 * _h, 2 * _h));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						break;
					}
				}
				uniqueName.pop();

				bDone = true;//bools
			}

			//-

			// 2.2. String

			else if (isString)
			{
				ofParameter<std::string> p = aparam.cast<std::string>();
				auto tmpRef = p.get();

				uniqueName.push();
				{
					switch (type)
					{
					case OFX_IM_DEFAULT:
					case OFX_IM_TEXT_DISPLAY:
					{
						//IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						ImGui::Text(tmpRef.c_str());
						//IMGUI_SUGAR__WIDGETS_POP_WIDTH;
					}
					break;

					case OFX_IM_TEXT_INPUT:
					{
						//IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						ImGui::Text(tmpRef.c_str());
						//ofxImGuiSurfing::AddParameter(p);//cant be included?
						//IMGUI_SUGAR__WIDGETS_POP_WIDTH;
					}
					break;

					case OFX_IM_TEXT_BIG:
					{
						//IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						ImGui::TextWrapped(tmpRef.c_str());
						//IMGUI_SUGAR__WIDGETS_POP_WIDTH;
					}
					break;

					//TODO: guiManager fonts are not available on this scope!
					//case OFX_IM_LABEL:
					//{
					//	//IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
					//	AddLabel(p);
					//	//IMGUI_SUGAR__WIDGETS_POP_WIDTH;
					//}
					//break;
					//case OFX_IM_LABEL_BIG:
					//{
					//	//IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
					//	AddLabelBig(p);
					//	//IMGUI_SUGAR__WIDGETS_POP_WIDTH;
					//}
					//break;

					}
				}
				uniqueName.pop();

				bDone = true;//strings
			}

			//-

			// 2.3. Float

			else if (isFloat)
			{
				ofParameter<float> p = aparam.cast<float>();
				auto tmpRef = p.get();

				uniqueName.push();
				{
					switch (type)
					{
					case OFX_IM_INACTIVE:
					{
						std::string name = p.getName();
						bReturn = false;
						IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						if (ImGui::SliderFloat(p.getName().c_str(), (float *)&tmpRef, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
					}
					break;

					case OFX_IM_DEFAULT:
					case OFX_IM_SLIDER:
					{
						std::string name = p.getName();
						bReturn = false;
						IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						if (ImGui::SliderFloat(p.getName().c_str(), (float *)&tmpRef, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//--

					// H Slider

					// mini

					case OFX_IM_HSLIDER_MINI:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_MINI), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_MINI_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_MINI), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_MINI_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_MINI), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_MINI_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_MINI), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//-

					case OFX_IM_HSLIDER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//-

					case OFX_IM_HSLIDER_SMALL:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_SMALL), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_SMALL), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_SMALL), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_SMALL), false, true));
						if (bMouseWheel) if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//-

					case OFX_IM_HSLIDER_BIG:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, 2 * _h), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, 2 * _h), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, 2 * _h), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, 2 * _h), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//--

					// V Slider

					case OFX_IM_VSLIDER:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_VSLIDER_NO_NAME:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_VSLIDER_NO_NUMBER:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_VSLIDER_NO_LABELS://no number and no name
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//--

					// Progress Bar

					case OFX_IM_PROGRESS_BAR:
					{
						ofxImGuiSurfing::AddProgressBar(p);
						bReturn = false;
					}
					break;

					case OFX_IM_PROGRESS_BAR_NO_TEXT:
					{
						ofxImGuiSurfing::AddProgressBar(p, -1, true);
						bReturn = false;
					}
					break;

					//--

					// Drag

					case OFX_IM_DRAG:
					{
						const float speed = 0.01f;
						bReturn = false;
						IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						if (ImGui::DragFloat(p.getName().c_str(), (float *)&tmpRef, speed, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//--

					// Knob

					case OFX_IM_KNOB:
					{
						bReturn = (ofxImGuiSurfing::AddKnob(p, false, _ww));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//case OFX_IM_KNOB_SMALL:
					//{
					//	bReturn = (ofxImGuiSurfing::AddKnob(p, false, _ww));
					//	if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					//}
					//break;

					case OFX_IM_KNOB_TRAIL:
					{
						bReturn = (ofxImGuiSurfing::AddKnob(p, true, _ww));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//-- 

					//TODO:
					case OFX_IM_COMBO_MULTI:
					{
						float pad = ImGui::GetStyle().FramePadding.x;

						bReturn |= (ofxImGuiSurfing::AddDragFloatSlider(p));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);

						bReturn |= ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww * 0.25f - pad, _ww * 0.75f), true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						ImGui::SameLine();
						bReturn |= (ofxImGuiSurfing::AddKnob(p, false, _ww * 0.75f));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);

						bReturn |= ofxImGuiSurfing::AddStepperFloat(p);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//--

					// Stepper

					case OFX_IM_STEPPER:
					{
						bReturn = AddStepperFloat(p);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);

						//const float step = 0.001f;
						//const float stepFast = 0.1f;
						//auto tmpRef = p.get();
						//bReturn = false;
						//IMGUI_SUGAR__STEPPER_WIDTH_PUSH;
						//if (ImGui::InputFloat(p.getName().c_str(), (float *)&tmpRef, step, stepFast))
						//{
						//	tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax());
						//	p.set(tmpRef);
						//	bReturn = true;
						//}
						//IMGUI_SUGAR__STEPPER_WIDTH_POP;
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;
					}
				}
				uniqueName.pop();

				bDone = true;//floats
			}

			//-

			// 2.4. Int

			else if (isInt)
			{
				ofParameter<int> p = aparam.cast<int>();
				auto tmpRef = p.get();

				uniqueName.push();
				{
					switch (type)
					{

					case OFX_IM_INACTIVE:
					{
						bReturn = false;
						IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						if (ImGui::SliderInt(p.getName().c_str(), (int *)&tmpRef, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
					}
					break;

					case OFX_IM_DEFAULT:
					case OFX_IM_SLIDER:
					{
						bReturn = false;
						IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						if (ImGui::SliderInt(p.getName().c_str(), (int *)&tmpRef, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//--

					// H Slider

					case OFX_IM_HSLIDER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//-

					case OFX_IM_HSLIDER_SMALL:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h / 2), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h / 2), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h / 2), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h / 2), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//-

					case OFX_IM_HSLIDER_BIG:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, 2 * _h), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, 2 * _h), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, 2 * _h), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, 2 * _h), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//--

					// V Slider

					case OFX_IM_VSLIDER:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_VSLIDER_NO_NAME:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_VSLIDER_NO_NUMBER:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_VSLIDER_NO_LABELS://no number and no name
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//-

					// Progress Bar

					case OFX_IM_PROGRESS_BAR:
					{
						std::string name = p.getName();
						ofxImGuiSurfing::AddProgressBar(p);
						bReturn = false;
					}
					break;

					case OFX_IM_PROGRESS_BAR_NO_TEXT:
					{
						ofxImGuiSurfing::AddProgressBar(p, -1, true);
						bReturn = false;
					}
					break;

					//-

					// Drag

					case OFX_IM_DRAG:
					{
						const float speed = 0.1;
						bReturn = false;
						IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						if (ImGui::DragInt(p.getName().c_str(), (int *)&tmpRef, speed, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//--

					//TODO:
					// only implemented for floats

					// Knob

					case OFX_IM_KNOB:
					{
						bReturn = (ofxImGuiSurfing::AddKnob(p, false, _ww));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					case OFX_IM_KNOB_TRAIL:
					{
						bReturn = (ofxImGuiSurfing::AddKnob(p, true, _ww));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					//--

					// Stepper

					case OFX_IM_STEPPER:
					{
						bReturn = AddStepperInt(p);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);

						//const int step = 1;
						//const int stepFast = 5;
						//auto tmpRef = p.get();
						//bReturn = false;
						//IMGUI_SUGAR__STEPPER_WIDTH_PUSH;
						//if (ImGui::InputInt(p.getName().c_str(), (int *)&tmpRef, step, stepFast))
						//{
						//	tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax());
						//	p.set(tmpRef);
						//	bReturn = true;
						//}
						//IMGUI_SUGAR__STEPPER_WIDTH_POP;
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;

					}
				}
				uniqueName.pop();

				bDone = true;//int
			}

			//-

			// 2.5. Color

			else if (isFloatColor)
			{
				ofParameter<ofFloatColor> p = aparam.cast<ofFloatColor>();
				auto tmpRef = p.get();

				uniqueName.push();
				{
					float _h = ofxImGuiSurfing::getWidgetsHeightUnit();

					ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;
					flags |= ImGuiColorEditFlags_NoInputs;
					flags |= ImGuiColorEditFlags_NoLabel;
					flags |= ImGuiColorEditFlags_NoTooltip;

					if (type == OFX_IM_DEFAULT) bReturn = ofxImGuiSurfing::AddParameter(p);

					else if (type == OFX_IM_COLOR_INPUT) bReturn = ofxImGuiSurfing::AddParameter(p);

					else if (type == OFX_IM_COLOR_NO_ALPHA) {
						bReturn = ofxImGuiSurfing::AddParameter(p, false);
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}

					//TODO:
					else if (type == OFX_IM_COLOR_NO_NAME) {
						//ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoLabel;
						//bReturn = ofxImGuiSurfing::AddParameter(p, false, flags);
						bReturn = ofxImGuiSurfing::AddParameter(p, false);
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}

					else if (type == OFX_IM_COLOR_BOX) ImGui::ColorButton("", tmpRef, flags);
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH) ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, _h));
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH_BIG) ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, 2 * _h));
				}
				uniqueName.pop();

				bDone = true;//colors
			}

			else if (isColor)
			{
				ofParameter<ofColor> p = aparam.cast<ofColor>();
				auto tmpRef = p.get();

				uniqueName.push();
				{
					ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;
					flags |= ImGuiColorEditFlags_NoInputs;
					flags |= ImGuiColorEditFlags_NoLabel;
					flags |= ImGuiColorEditFlags_NoTooltip;

					if (type == OFX_IM_DEFAULT) bReturn = ofxImGuiSurfing::AddParameter(p);

					else if (type == OFX_IM_COLOR_INPUT) bReturn = ofxImGuiSurfing::AddParameter(p);

					else if (type == OFX_IM_COLOR_NO_ALPHA) {
						bReturn = ofxImGuiSurfing::AddParameter(p, false);
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}

					//TODO:
					else if (type == OFX_IM_COLOR_NO_NAME) {
						bReturn = ofxImGuiSurfing::AddParameter(p, false);
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
						//ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoLabel;
						//bReturn = ofxImGuiSurfing::AddParameter(p, false, flags);
					}

					else if (type == OFX_IM_COLOR_BOX) ImGui::ColorButton("", tmpRef, flags);
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH) ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, _h));
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH_BIG) ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, 2 * _h));
				}
				uniqueName.pop();

				bDone = true;//colors
			}

			//--------

			// 2.6. Multidim vec2/vec3/vec4

			else if (isMultiDimVec2)
			{
				uniqueName.push();
				{
					ofParameter<glm::vec2> p = aparam.cast<glm::vec2>();

					switch (type)
					{
					case OFX_IM_MULTIDIM_SPLIT_SLIDERS:
					{
						bReturn = ofxImGuiSurfing::AddParameter(p, true); //-> Should include sugar inside
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p);
					}
					break;
					}
				}
				uniqueName.pop();

				bDone = true;//vec2
			}

			else if (isMultiDimVec3)
			{
				uniqueName.push();
				{
					ofParameter<glm::vec3> p = aparam.cast<glm::vec3>();

					switch (type)
					{
					case OFX_IM_MULTIDIM_SPLIT_SLIDERS:
					{
						bReturn = ofxImGuiSurfing::AddParameter(p, true);
					}
					break;
					}
				}
				uniqueName.pop();

				bDone = true;//vec3
			}

			else if (isMultiDimVec4)
			{
				uniqueName.push();
				{
					ofParameter<glm::vec4> p = aparam.cast<glm::vec4>();

					switch (type)
					{
					case OFX_IM_MULTIDIM_SPLIT_SLIDERS:
					{
						bReturn = ofxImGuiSurfing::AddParameter(p, true);
					}
					break;
					}
				}
				uniqueName.pop();

				bDone = true;//vec4
			}


			//--------

			// 3. Closing, Ending last step.

			if (bDone) //-> A widget has been populated, then we can apply the extra arguments..
			{
				// Extra options
				// - Same line flag.
				// - Final y spacing.

				if (bSameLine) ImGui::SameLine();
				if (spacing != -1 && spacing != 0)
				{
					ImGui::Dummy(ImVec2(0.0f, (float)spacing)); // spacing
				}
			}

			//--

			if (type == OFX_IM_INACTIVE)
			{
				ImGui::PopItemFlag();
			}

			//----

			return bReturn;
		}


		//-------

		// Groups (ofParameterGroup)

	public:

		//--------------------------------------------------------------
		void AddGroup(ofParameterGroup& group)
		{
			AddGroup(group, ImGuiTreeNodeFlags_None, OFX_IM_GROUP_DEFAULT);
		}

		//--------------------------------------------------------------
		void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT)
		{
			bool bIsOpen = false;
			bool bMustHideGroup = false;
			bool bMustCloseTree = false; //TODO: -> add new

			// Handle names/pushID's
			// This is the root/first group
			// Level is about how many deep on nested groups we are

			////TODO:
			// -> Must remove all return calls inside below to not break pushIDs if we want to use ID's!
			ImGui::PushID(("##GROUP_" + group.getName()).c_str());
			{
				// A. 
				// This is the root parent group/header:
				//--------------------------------------------------------------

				if (uniqueName.getLevel() == 0) //-> This should notify it's the root parent group..
				{
					// Group Style:
					// If a group style is queued, we will overwrite the default style for each type.

					auto c = getStyleGroup(group);
					if (c.name != "-1")
					{
						typeGroup = SurfingImGuiTypesGroups(c.type);
						flags = c.flags;
					}
					bMustHideGroup = (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN);

					//-

					// 1. Openings

					if (!bMustHideGroup)
					{
						{
							if (0) {}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN_HEADER)
							{
								bIsOpen = true; // not really closed but not rendered!
								bMustCloseTree = false; // ? should depends of the tree type.. ? //TODO: important!
							}
							else if (
								typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_DEFAULT ||
								typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
							{
								// workaround
								bool bOpen = (flags == ImGuiTreeNodeFlags_DefaultOpen);
								ImGui::SetNextTreeNodeOpen(bOpen, ImGuiCond_Appearing);

								bIsOpen = ImGui::CollapsingHeader(group.getName().c_str(), flags);
								bMustCloseTree = false; // we dont need to close tree!
							}
							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE)
							{
								// workaround bc tree has no flags..
								bool bOpen = (flags == ImGuiTreeNodeFlags_DefaultOpen);
								ImGui::SetNextTreeNodeOpen(bOpen, ImGuiCond_Appearing);

								bIsOpen = ImGui::TreeNode(group.getName().c_str());
								bMustCloseTree = bIsOpen;
							}
							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
							{
								bIsOpen = ImGui::TreeNodeEx(group.getName().c_str(), flags);
								bMustCloseTree = bIsOpen;
							}
							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
							{
								// A. Height variable to amount widgets..
								//auto& style = ImGui::GetStyle();
								//float hratio = 1.0; // 1. is the same height of items (considerates that font size is 14)
								//int h = 14;
								//int hh = style.FramePadding.y + style.ItemSpacing.y + h;
								//int hhh = parameterGroup->size() * hratio * hh;

								// B. Height hardcoded
								int hhh = HEIGHT_SCROLL_GROUP;
								bIsOpen = ImGui::CollapsingHeader(group.getName().c_str(), flags);
								bMustCloseTree = false;

								if (bIsOpen)
								{
									ImGui::Indent();
									ImGui::BeginChild(group.getName().c_str(), ImVec2(0, hhh), false);
								}
							}
							//else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_WINDOWED)
							//{
							//}
						}

						//-

						// 2. Header already rendered

						uniqueName.setOpen(bIsOpen); //TODO: ?

						//-

						// 4. To re calculate layout sizes after headers and indenting.

						refreshLayout();

						//-

						// 5. Skip all nested groups and their params

						if (!bIsOpen)
						{
							ImGui::PopID();
							return;
						}
					}
				}

				//----

				// 5. Parameters

				// Here, this is not the root/first group.
				// We go populate the params widgets

				for (auto parameter : group)
				{
					// 5.1 Group Parameter

					// B. 
					// The param is a Group
					// This will not be the Group from the 0'th/root/parent level.
					//--------------------------------------------------------------

					auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);

					if (parameterGroup) // Will detect nested groups recursively
					{
						refreshLayout(); // ?
						uniqueName.pushGroup(); //TODO: should be in another place ?

						// -> Unique id for possible name repeated params inside many groups.
						std::string ss = "##" + ofToString(uniqueName.getLevel()) + parameterGroup->getName();
						ImGui::PushID(ss.c_str());
						{
							auto c = getStyleGroup(*parameterGroup);
							if (c.name != "-1") // the overwrite
							{
								typeGroup = SurfingImGuiTypesGroups(c.type); // overwrite main type
								flags = c.flags;
							}

							std::string name = parameterGroup->getName();

							//----

							if (0) {}

							// Hidden
							//else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDE_ALL_HEADERS)
							//{
							//	AddGroup(*parameterGroup, flags, typeGroup);
							//}
							//else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_ONLY_FIRST_HEADER)
							//{
							//	ImGui::Indent();
							//	bool b = ImGui::CollapsingHeader(parameterGroup->getName().c_str(), flags);
							//	if (b) AddGroup(*parameterGroup, flags, typeGroup);
							//	ImGui::Unindent();
							//}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN)
							{
								// Must skip contained params
							}
							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN_HEADER)
							{
								ImGui::Indent();
								refreshLayout(); // ?
								AddGroup(*parameterGroup, flags, typeGroup);
								ImGui::Unindent();
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_DEFAULT)
							{
								ImGui::Indent();
								refreshLayout(); // ?
								bool b = ImGui::CollapsingHeader(name.c_str(), flags);
								if (b) AddGroup(*parameterGroup, flags, typeGroup);
								ImGui::Unindent();
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
							{
								ImGui::Indent();
								refreshLayout(); // ?
								bool b = ImGui::CollapsingHeader(name.c_str(), flags);
								if (b) AddGroup(*parameterGroup, flags, typeGroup);
								ImGui::Unindent();
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE)
							{
								//TODO:
								// workaround bc tree has no flags..
								bool bOpen = (flags == ImGuiTreeNodeFlags_DefaultOpen);
								ImGui::SetNextTreeNodeOpen(bOpen, ImGuiCond_Appearing);

								if (ImGui::TreeNode(name.c_str()))
								{
									ImGui::Indent();
									refreshLayout(); // ?
									AddGroup(*parameterGroup, flags, typeGroup);
									ImGui::Unindent();

									ImGui::TreePop();
								}
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
							{
								if (ImGui::TreeNodeEx(name.c_str(), flags))
								{
									ImGui::Indent();
									refreshLayout(); // ?
									AddGroup(*parameterGroup, flags, typeGroup);
									ImGui::Unindent();

									ImGui::TreePop();
								}
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
							{
								// Scrollable zone

								// A. Height variable to amount of widgets..
								//auto& style = ImGui::GetStyle();
								//float hratio = 1.0; // 1. is the same height of items (considerates that font size is 14)
								//int h = 14;
								//int hh = style.FramePadding.y + style.ItemSpacing.y + h;
								//int hhh = parameterGroup->size() * hratio * hh;

								// B. Height hardcoded
								int hhh = HEIGHT_SCROLL_GROUP;

								//-

								bool b = ImGui::CollapsingHeader(name.c_str(), flags);
								if (b)
								{
									ImGui::Indent();
									ImGui::BeginChild(name.c_str(), ImVec2(0, hhh), false);
									refreshLayout(true); // ?
									AddGroup(*parameterGroup, flags, typeGroup);
									ImGui::EndChild();
									ImGui::Unindent();
								}
							}
						}
						ImGui::PopID();

						//--

						// Group content iteration done!
						continue;
					}

					//----

					// 5.2 Not group parameters 

					// Try everything we know how to handle.
					// We will filter known styles for know types.
					// Some params could not have styles types!
					// Uses "ofxSurfing_ImGui_ofHelpers.h"

					//TODO:
					// Should add styles yet for unknow types!

					//--

					//// Skip params inside the group if is not opened or collapsed.
					//bool binclude = false;
					////binclude = (uniqueName.isOpen(uniqueName.getLevel());
					//binclude = (uniqueName.getLevel() == 0 && bIsOpen) || (uniqueName.getLevel() != 0);
					//if (binclude)
					{
						//--

						// Multidim params vec2/vec3/vec4

#if OF_VERSION_MINOR >= 10

						auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
						if (parameterVec2f)
						{
							auto c = getStyle(*parameterVec2f);
							if (c.name != "-1") AddParameter(*parameterVec2f);//if not added style for this param
							else {
								if (c.type == OFX_IM_MULTIDIM_SPLIT_SLIDERS) ofxImGuiSurfing::AddParameter(*parameterVec2f, true);
								else AddParameter(*parameterVec2f);
							}
							continue;
						}

						//-

						auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
						if (parameterVec3f)
						{
							auto c = getStyle(*parameterVec3f);
							if (c.name == "-1") AddParameter(*parameterVec3f);
							else {
								if (c.type == OFX_IM_MULTIDIM_SPLIT_SLIDERS) ofxImGuiSurfing::AddParameter(*parameterVec3f, true);
								else AddParameter(*parameterVec3f);
							}
							continue;
						}

						//-

						auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
						if (parameterVec4f)
						{
							auto c = getStyle(*parameterVec4f);
							if (c.name != "-1") AddParameter(*parameterVec4f);
							else {
								if (c.type == OFX_IM_MULTIDIM_SPLIT_SLIDERS) ofxImGuiSurfing::AddParameter(*parameterVec4f, true);
								else AddParameter(*parameterVec4f);
							}
							continue;
						}
#endif
						//--

						//TODO:
						// Unknown types
						// Should add styles for old ofVec...

						auto parameterOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(parameter);
						if (parameterOfVec2f)
						{
							AddParameter(*parameterOfVec2f);
							continue;
						}
						auto parameterOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(parameter);
						if (parameterOfVec3f)
						{
							AddParameter(*parameterOfVec3f);
							continue;
						}
						auto parameterOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(parameter);
						if (parameterOfVec4f)
						{
							AddParameter(*parameterOfVec4f);
							continue;
						}

						//--

						//auto parameterOfFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
						//if (parameterOfFloatColor)
						//{
						//	AddParameter(*parameterOfFloatColor);
						//	continue;
						//}
						//auto parameterOfColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
						//if (parameterOfColor)
						//{
						//	AddParameter(*parameterOfColor);
						//	continue;
						//}

						//--

						// Float

						auto parameterFloat = std::dynamic_pointer_cast<ofParameter<float>>(parameter);
						if (parameterFloat)
						{
							auto c = getStyle(*parameterFloat);
							// if the parameter widget is not added explicitly, will populate it as the default appearance
							if (c.name != "-1")
							{
								Add(*parameterFloat, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							// default style
							else
							{
								//AddParameter(*parameterFloat);
								// fixing to allow mouse wheel..
								Add(*parameterFloat, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							continue;
						}

						//--

						// Int

						auto parameterInt = std::dynamic_pointer_cast<ofParameter<int>>(parameter);
						if (parameterInt)
						{
							auto c = getStyle(*parameterInt);
							if (c.name != "-1")
							{
								Add(*parameterInt, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							else
							{
								//AddParameter(*parameterInt);
								// fixing to allow mouse wheel..
								Add(*parameterInt, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							continue;
						}

						//--

						// Bool

						auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
						if (parameterBool)
						{
							auto c = getStyle(*parameterBool);
							if (c.name != "-1")
							{
								Add(*parameterBool, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							else
							{
								//AddParameter(*parameterBool);
								// fixing to allow mouse wheel..
								Add(*parameterBool, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							continue;
						}

						//--

						// String

						auto parameterString = std::dynamic_pointer_cast<ofParameter<std::string>>(parameter);
						if (parameterString)
						{
							auto c = getStyle(*parameterString);
							if (c.name != "-1")
							{
								Add(*parameterString, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							else
							{
								Add(*parameterString, OFX_IM_DEFAULT);
								//AddParameter(*parameterString);
							}
							continue;
						}

						//-

						// Float color

						auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
						if (parameterFloatColor)
						{
							auto c = getStyle(*parameterFloatColor);
							// if the parameter widget is not added explicitly, will populate it as the default appearance
							if (c.name != "-1")
							{
								Add(*parameterFloatColor, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							// default style
							else
							{
								//AddParameter(*parameterFloatColor);
								// fixing to allow mouse wheel..
								Add(*parameterFloatColor, c.type, c.amtPerRow, c.bSameLine, c.spacing);

							}
							continue;
						}

						//-

						// Color

						auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
						if (parameterColor)
						{
							auto c = getStyle(*parameterColor);
							// if the parameter widget is not added explicitly, will populate it as the default appearance
							if (c.name != "-1")
							{
								Add(*parameterColor, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							// default style
							else
							{
								//AddParameter(*parameterColor);
								// fixing to allow mouse wheel..
								Add(*parameterColor, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							continue;
						}

						//--

						// If we arrive here, the param type is unknown and will be ignored, not rendered on the panel.
						if (parameter->getName() == "" && parameter->getName() == " ")
							ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName() << "'";
					}
				}

				//------

				// 3. Closings

				// Handle names/pushID's
				if (uniqueName.getLevel() == 0)
				{
					if (bIsOpen)
					{
						if (0) {}

						else if
							(
								typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_DEFAULT ||
								typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
						{
							// Do not requires closing/pop
						}
						else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE)
						{
							if (bMustCloseTree) ImGui::TreePop();
						}
						else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
						{
							if (bMustCloseTree) ImGui::TreePop();
						}
						else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
						{
							ImGui::EndChild();
							ImGui::Unindent();
							// Don't needs close tree bc uses a collapsingHeader tree on begin
						}
					}

					//-

					//ImGui::PopID(); // Group main
					////}
				}
			}
			////TODO:
			ImGui::PopID();
		}
	};

	//--

} // namespace ofxSurfing
