
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"

#include "ofHelpers.h"
#include "LayoutHelpers.h"

#include "GuiConstants.h"
#include "GuiUniqueNames.h"

//-

#include <list>
#include <iostream>
#include <boost/range/adaptor/reversed.hpp>

//-

namespace ofxImGuiSurfing
{
	class WidgetsManager
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

		// This common sizes must be updated during draw to refresh when window panels resizing,
		// when indenting, when going into or out of a tree/folder...etc 
		// To adapt to that changes.

	public:

		ofParameter<bool> bMouseWheel{ "Mouse Wheel", false };
		ofParameter<bool> bMouseWheelFlip{ "Flip Wheel" , false };

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
			SurfingGuiTypes type = OFX_IM_DEFAULT;
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
			SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT;
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
		WidgetsManager()
		{
			widgetsStyles.clear();

			uniqueName.reset();
		};

		//--------------------------------------------------------------
		~WidgetsManager()
		{
		};

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

			for (auto& c : widgetsStyles)
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
			for (auto& c : groupsStyles)
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
		void AddStyle(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
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
		void AddStyle(std::string name, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
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
		void AddStyleGroup(ofParameterGroup& group, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
		{
			SurfingImGuiTypesGroup_Style c;
			c.name = group.getName();
			c.type = type;
			c.flags = flags;

			groupsStyles.push_back(c);
		}
		//--------------------------------------------------------------
		void AddStyleGroup(std::string name, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
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
		//void UpdateStyle(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
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
		//void UpdateStyle(std::string name, SurfingGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
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
		void UpdateStyleGroup(std::string name, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
		{
			for (auto& c : groupsStyles)
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
		void UpdateStyleGroup(ofParameterGroup& group, SurfingGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
		{
			for (auto& c : groupsStyles)
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
		void UpdateStyle(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		{
			for (auto& c : widgetsStyles)
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
		void UpdateStyle(std::string name, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		{
			for (auto& c : widgetsStyles)
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

		//bool Add(ofAbstractParameter& aparam, WidgetsManager type) {
		//	Add(bMode1, SurfingGuiTypesGroups::OFX_IM_TOGGLE_SMALL, 3, true);
		//}

		//-

		//void AddStyle(std::string name, SurfingGuiTypes type) {
		//	SurfingImGuiTypes_Style e;
		//	e.name = name;
		//	e.type = type;
		//	widgetsStyles.push_back(e);
		//}

		//-

		//--------------------------------------------------------------
		SurfingGuiTypes getType(ofAbstractParameter& aparam)
		{
			std::string name = aparam.getName();
			SurfingGuiTypes rtype = SurfingGuiTypes(OFX_IM_DEFAULT);

			auto type = aparam.type();
			bool isBool = type == typeid(ofParameter<bool>).name();
			if (!isBool) return rtype;

			for (auto w : widgetsStyles)
			{
				if (w.name == name)
				{
					rtype = SurfingGuiTypes(w.type);
				}
			}

			return rtype;
		}

		//----

		// Helpers to get some layout dimensions
		// we get the sizes from the canvas layout!

		//-----------------------------------------------------------------
		float getWidgetWidthOnRowPerAmount(int amount) {
			switch (amount)
			{
			case 1: return _w100; break;
			case 2: return _w50; break;
			case 3: return _w33; break;
			case 4: return _w25; break;
			default: return 10; break;
			}
		}

		//----

		// Render now a parameter with a related ImGui widget with a custom style.
		// Remember that must be called inside an ui::Begin/End() !

	public:

		//TODO:
		// WIP:
		//--------------------------------------------------------------
		bool Add(ofAbstractParameter& aparam, SurfingGuiTypes type, int amtPerRow, SurfingGuiFlags flags = SurfingGuiFlags_None)
		{
			return Add(aparam, type, amtPerRow, false, -1, flags);
		}

		//--

		//TODO new API
		// Final step method, Draws using an absolute width
		//-----------------------------------------------------------------
		bool Add(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, float width = -1, bool bSameLine = false, int spacing = -1, SurfingGuiFlags flags = SurfingGuiFlags_None)
		{
			if (width == -1) {
				ofLogWarning("ofxSurfingImGui") << (__FUNCTION__);
				ofLogWarning("ofxSurfingImGui") << "Width not passed! We will apply 100% width.";

				width = _w100;
				//return false;
			}

			float _ww = width;

			// Will flag to true to do the final steps: 
			// same line and spacing config by args.
			bool bDone = false;

			// Will flag to notify if the ofParam widget changed.
			bool bReturn = false;

			//----

			//TODO: all the mouse wheel stuff could be moved to return place in one place only.
			// 1. Handle hidden, disabled and inactive tags:

			//--

			// If settled as hidden don't draw, but apply same line and spacing and return

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

			//--

			//TODO:
			// If settled as hidden we don't draw it, 
			// but apply same line and spacing args and return!

			else if (type == OFX_IM_DISABLED)
			{
				uniqueName.push();
				{
					if (bSameLine) ImGui::SameLine();

					if (spacing != -1)
					{
						//TODO: could be take from style argument, not hard coded like that
						float h = (ImGui::GetIO().FontDefault->FontSize + ImGui::GetStyle().FramePadding.y * 2);
						ImGui::InvisibleButton("_inv_", ImVec2(10, h), ImGuiButtonFlags_None);
						ImGui::Dummy(ImVec2(0.0f, (float)spacing)); // spacing
					}
				}
				uniqueName.pop();

				return false;
			}

			//--

			else if (type == OFX_IM_SPACING)
			{
				uniqueName.push();
				{
					if (bSameLine) ImGui::SameLine();

					//TODO: could be take from style argument, not hard coded like that
					float h = 0.25f * (ImGui::GetIO().FontDefault->FontSize + ImGui::GetStyle().FramePadding.y * 2);
					ImGui::InvisibleButton("_inv_", ImVec2(10, h), ImGuiButtonFlags_None);

					if (spacing != -1)
					{
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

			const bool isVoid = ptype == typeid(ofParameter<void>).name();
			const bool isBool = ptype == typeid(ofParameter<bool>).name();
			const bool isFloat = ptype == typeid(ofParameter<float>).name();
			const bool isInt = ptype == typeid(ofParameter<int>).name();
			const bool isString = ptype == typeid(ofParameter<std::string>).name();
			const bool isColor = ptype == typeid(ofParameter<ofColor>).name();
			const bool isFloatColor = ptype == typeid(ofParameter<ofFloatColor>).name();
			const bool isMultiDimVec2 = ptype == typeid(ofParameter<glm::vec2>).name();
			const bool isMultiDimVec3 = ptype == typeid(ofParameter<glm::vec3>).name();
			const bool isMultiDimVec4 = ptype == typeid(ofParameter<glm::vec4>).name();
			const bool isRectangle = ptype == typeid(ofParameter<ofRectangle>).name();

			//TODO:
			// is not called with groups here.. ?
			//bool isGroup = ptype == typeid(ofParameterGroup).name();
			//if (isGroup) 
			//{
			//	refreshPanelShape();
			//	return false;
			//}

			//--------

			// 2.0 VOID

			if (isVoid)
			{
				ofParameter<void> p = aparam.cast<void>();

				uniqueName.push();
				{
					switch (type)
					{

					case OFX_IM_DEFAULT:
					case OFX_IM_BUTTON_SMALL:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h);
						// TODO: should implement wheel for void type.
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 1.25f);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_MEDIUM:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 1.5f);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 2);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_XXL:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 3);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_XXXL:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 4);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;
					}
				}
				uniqueName.pop();

				bDone = true; // void
			}

			//--

			// 2.1 BOOL

			else if (isBool)
			{
				ofParameter<bool> p = aparam.cast<bool>();
				auto tmpRef = p.get();

				uniqueName.push();
				{
					switch (type)
					{

					case OFX_IM_INACTIVE:
					{
						// Default
						std::string name = p.getName();
						if (ImGui::Checkbox(p.getName().c_str(), (bool*)&tmpRef))
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
						// Default
						std::string name = p.getName();
						if (ImGui::Checkbox(p.getName().c_str(), (bool*)&tmpRef))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						bReturn = false;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					case OFX_IM_BUTTON_SMALL:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 1.25f);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_MEDIUM:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 1.5f);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 2);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_XXL:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 3);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_XXXL:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 4);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

						//-

						// Border 

					case OFX_IM_BUTTON_SMALL_BORDER:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BORDER:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 1.25f, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_MEDIUM_BORDER:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 1.5f, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_BORDER:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 2, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_XXL_BORDER:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 3, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_XXXL_BORDER:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 4, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

						//-

						// Border Blink
					case OFX_IM_BUTTON_SMALL_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 1.25f, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_MEDIUM_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 1.5f, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 2, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_XXL_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 3, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_BUTTON_BIG_XXXL_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 4, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

						//--

					case OFX_IM_TOGGLE_SMALL:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 1.25f);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_MEDIUM:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 1.5f);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BIG:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 2);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BIG_XXL:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 3);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BIG_XXXL:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 4);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

						//--

						// Border

					case OFX_IM_TOGGLE_SMALL_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 1.25f, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_MEDIUM_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 1.5f, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BIG_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 2, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BIG_XXL_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 3, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BIG_XXXL_BORDER:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 4, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

						//-

						// Border Blink

					case OFX_IM_TOGGLE_SMALL_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 1.25f, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_MEDIUM_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 1.5f, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BIG_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 2, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 3, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK:
						bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 4, true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

						//--

						// Rounded Toggles

					case OFX_IM_TOGGLE_ROUNDED_MINI:
					case OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI://Legacy
						bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p, ImVec2(1.15f * _h, 1.15f * (2 / 3.f) * _h), true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_ROUNDED_SMALL:
					case OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL://Legacy
						bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p, ImVec2(1.35f * _h, 1.35f * (2 / 3.f) * _h));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_ROUNDED:
					case OFX_IM_TOGGLE_BUTTON_ROUNDED://Legacy
						bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_ROUNDED_MEDIUM:
					case OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM://Legacy
						bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p, ImVec2(2 * _h, 2 * (2 / 3.f) * _h));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;

					case OFX_IM_TOGGLE_ROUNDED_BIG:
					case OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG://Legacy
						bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p, ImVec2(2.5f * _h, 2.5f * (2 / 3.f) * _h));
						//bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p, ImVec2(3 * _h, 2 * _h));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
						break;
					}
				}
				uniqueName.pop();

				bDone = true; // BOOLS
			}

			//--

			// 2.2. STRING

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

					case OFX_IM_TEXT_INPUT://TODO:
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

					//TODO: ui fonts are not available on this scope!
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

				bDone = true; // STRINGS
			}

			//--

			// 2.3 FLOAT

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
						if (ImGui::SliderFloat(p.getName().c_str(), (float*)&tmpRef, p.getMin(), p.getMax()))
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
						if (ImGui::SliderFloat(p.getName().c_str(), (float*)&tmpRef, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					// H Slider

					// Mini

					case OFX_IM_HSLIDER_MINI:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_MINI), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_MINI_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_MINI), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_MINI_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_MINI), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_MINI_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_MINI), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//-

					case OFX_IM_HSLIDER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//-

					case OFX_IM_HSLIDER_SMALL:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_SMALL), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_SMALL), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_SMALL), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h * OFX_IM_WIDGETS_RATIO_SMALL), false, true));
						if (bMouseWheel) if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					case OFX_IM_HSLIDER_BIG:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, OFX_IM_WIDGETS_RATIO_BIG * _h), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, OFX_IM_WIDGETS_RATIO_BIG * _h), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, OFX_IM_WIDGETS_RATIO_BIG * _h), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, OFX_IM_WIDGETS_RATIO_BIG * _h), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					// V Slider

					case OFX_IM_VSLIDER:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_VSLIDER_NO_NAME:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_VSLIDER_NO_NUMBER:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_VSLIDER_NO_LABELS://no number and no name
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
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

					// Draggable number

					case OFX_IM_DRAG:
					{
						const float speed = 0.01f;
						bReturn = false;
						IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						if (ImGui::DragFloat(p.getName().c_str(), (float*)&tmpRef, speed, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					// Knobs

					case OFX_IM_KNOB:
					{
						bReturn = (ofxImGuiSurfing::AddKnob(p, false, _ww));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//case OFX_IM_KNOB_SMALL:
					//{
					//	bReturn = (ofxImGuiSurfing::AddKnob(p, false, _ww));
					//	if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
					//}
					//break;

					case OFX_IM_KNOB_TRAIL:
					{
						bReturn = (ofxImGuiSurfing::AddKnob(p, true, _ww));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//----

					//TODO:
					// Adding NEW style knobs, 
					// taken from Simon Altschuler https://github.com/altschuler/imgui-knobs

					case OFX_IM_KNOB_TICKKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_TICKKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_DOTKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_DOTKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_WIPERKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_WIPERKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_WIPERONLYKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_WIPERONLYKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_WIPERDOTKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_WIPERDOTKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_STEPPEDKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_STEPPEDKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_SPACEKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_SPACEKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//---- 

					//TODO:
					// Populate many widgets for one single parameter variable
					case OFX_IM_COMBO_MULTI:
					{
						float pad = ImGui::GetStyle().FramePadding.x;

						bReturn |= (ofxImGuiSurfing::AddDragFloatSlider(p));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();

						bReturn |= ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww * 0.25f - pad, _ww * 0.75f), true, true);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();

						ImGui::SameLine();

						bReturn |= (ofxImGuiSurfing::AddKnob(p, false, _ww * 0.75f));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();

						bReturn |= ofxImGuiSurfing::AddStepperFloat(p);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					// Stepper

					case OFX_IM_STEPPER:
					{
						bReturn = AddStepperFloat(p);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();

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
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
					}
					break;
					}
				}
				uniqueName.pop();

				bDone = true;//floats
			}

			//--

			// 2.4 INT

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
						if (ImGui::SliderInt(p.getName().c_str(), (int*)&tmpRef, p.getMin(), p.getMax()))
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
						if (ImGui::SliderInt(p.getName().c_str(), (int*)&tmpRef, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					// H Slider

					case OFX_IM_HSLIDER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
					}
					break;

					case OFX_IM_HSLIDER_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					case OFX_IM_HSLIDER_SMALL:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h / 2), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h / 2), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h / 2), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_SMALL_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, _h / 2), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					case OFX_IM_HSLIDER_BIG:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, OFX_IM_WIDGETS_RATIO_BIG * _h), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_LABELS:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, OFX_IM_WIDGETS_RATIO_BIG * _h), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_NAME:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, OFX_IM_WIDGETS_RATIO_BIG * _h), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_HSLIDER_BIG_NO_NUMBER:
					{
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddHSlider(p, ImVec2(_ww, OFX_IM_WIDGETS_RATIO_BIG * _h), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					// V Slider

					case OFX_IM_VSLIDER:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), false, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_VSLIDER_NO_NAME:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), true, false));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_VSLIDER_NO_NUMBER:
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), false, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_VSLIDER_NO_LABELS://no number and no name
					{
						const float gap = 2;//fix oversize
						std::string name = p.getName();
						bReturn = (ofxImGuiSurfing::AddVSlider(p, ImVec2(_ww - gap, _h * 5), true, true));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

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

					//--

					// Draggable number

					case OFX_IM_DRAG:
					{
						const float speed = 0.1;
						bReturn = false;
						IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
						if (ImGui::DragInt(p.getName().c_str(), (int*)&tmpRef, speed, p.getMin(), p.getMax()))
						{
							p.set(tmpRef);
							bReturn = true;
						}
						IMGUI_SUGAR__WIDGETS_POP_WIDTH;
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//--

					//TODO:
					// only implemented for floats

					// Legacy

					// Knob

					case OFX_IM_KNOB:
					{
						bReturn = (ofxImGuiSurfing::AddKnob(p, false, _ww));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_TRAIL:
					{
						bReturn = (ofxImGuiSurfing::AddKnob(p, true, _ww));
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//----

					//TODO:
					// Adding NEW style knobs, 
					// taken from Simon Altschuler https://github.com/altschuler/imgui-knobs

					case OFX_IM_KNOB_TICKKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_TICKKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_DOTKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_DOTKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_WIPERKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_WIPERKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_WIPERONLYKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_WIPERONLYKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_WIPERDOTKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_WIPERDOTKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_STEPPEDKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_STEPPEDKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					case OFX_IM_KNOB_SPACEKNOB:
					{
						bReturn = ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_SPACEKNOB, _ww, "%.1f", flags);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();
					}
					break;

					//---- 

					// Stepper

					case OFX_IM_STEPPER:
					{
						bReturn = AddStepperInt(p);
						if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
						if (bMouseWheel) bReturn |= GetMouseWheel();

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
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
					}
					break;

					}
				}
				uniqueName.pop();

				bDone = true;//int
			}

			//--

			// 2.5 COLOR

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

					if (type == OFX_IM_DEFAULT)
						bReturn = ofxImGuiSurfing::AddParameter(p);
					else if (type == OFX_IM_COLOR_INPUT)
						bReturn = ofxImGuiSurfing::AddParameter(p);
					else if (type == OFX_IM_COLOR_NO_ALPHA)
						bReturn = ofxImGuiSurfing::AddParameter(p, false);
					else if (type == OFX_IM_COLOR_NO_INPUTS)
						bReturn = ofxImGuiSurfing::AddParameter(p, false, ImGuiColorEditFlags_NoInputs);
					else if (type == OFX_IM_COLOR_NO_NAME)
						bReturn = ofxImGuiSurfing::AddParameter(p, false, ImGuiColorEditFlags_NoLabel);
					else if (type == OFX_IM_COLOR_BOX)
						ImGui::ColorButton("", tmpRef, flags);
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH)
						ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, _h));
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH_BIG)
						ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, 2 * _h));

					//TODO: must merge..or to use a box with tooltips
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH_CONTROLS) {
						flags = ImGuiColorEditFlags_None;
						flags |= ImGuiColorEditFlags_NoInputs;
						flags |= ImGuiColorEditFlags_NoLabel;
						flags |= ImGuiColorEditFlags_NoTooltip;
						ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
						bReturn = ofxImGuiSurfing::AddParameter(p, false, flags);
						ImGui::PopItemWidth();
						ImGui::SameLine();
						ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, _h));
					}
				}
				uniqueName.pop();

				bDone = true; // COLORS
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

					if (type == OFX_IM_DEFAULT)
						bReturn = ofxImGuiSurfing::AddParameter(p);

					else if (type == OFX_IM_COLOR_INPUT)
						bReturn = ofxImGuiSurfing::AddParameter(p);
					else if (type == OFX_IM_COLOR_NO_ALPHA)
						bReturn = ofxImGuiSurfing::AddParameter(p, false);
					else if (type == OFX_IM_COLOR_NO_NAME)
						bReturn = ofxImGuiSurfing::AddParameter(p, false, ImGuiColorEditFlags_NoLabel);
					else if (type == OFX_IM_COLOR_NO_INPUTS)
						bReturn = ofxImGuiSurfing::AddParameter(p, false, ImGuiColorEditFlags_NoInputs);
					else if (type == OFX_IM_COLOR_BOX)
						ImGui::ColorButton("", tmpRef, flags);
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH)
						ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, _h));
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH_BIG)
						ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, 2 * _h));

					//TODO: must merge..or to use a box with tooltips
					else if (type == OFX_IM_COLOR_BOX_FULL_WIDTH_CONTROLS) {
						flags = ImGuiColorEditFlags_None;
						flags |= ImGuiColorEditFlags_NoInputs;
						flags |= ImGuiColorEditFlags_NoLabel;
						flags |= ImGuiColorEditFlags_NoTooltip;
						ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
						bReturn = ofxImGuiSurfing::AddParameter(p, false, flags);
						ImGui::PopItemWidth();
						ImGui::SameLine();
						ImGui::ColorButton("", tmpRef, flags, ImVec2(ImGui::GetContentRegionAvail().x, _h));
					}

				}
				uniqueName.pop();

				bDone = true; // COLORS
			}

			//--------

			// 2.6 MULTIDIM VEC2 / VEC3 / VEC4

			else if (isMultiDimVec2)
			{
				uniqueName.push();
				{
					ofParameter<glm::vec2> p = aparam.cast<glm::vec2>();

					switch (type)
					{
					case OFX_IM_MULTIDIM_SPLIT_SLIDERS:
					{
						bReturn = ofxImGuiSurfing::AddParameter(p, true);
						//TODO:
						//-> Should include sugar inside
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
					}
					break;

					case OFX_IM_MULTIDIM_SPLIT_SLIDERS_FOLDERED:
					{
						bReturn = ofxImGuiSurfing::AddParameter(p, true, true);
						//TODO:
						//-> Should include sugar inside
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
					}
					break;

					default:
						bReturn = ofxImGuiSurfing::AddParameter(p);
						break;
					}
				}
				uniqueName.pop();

				bDone = true; // VEC2
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

					case OFX_IM_MULTIDIM_SPLIT_SLIDERS_FOLDERED:
					{
						bReturn = ofxImGuiSurfing::AddParameter(p, true, true); //-> Should include sugar inside
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
					}
					break;

					default:
						bReturn = ofxImGuiSurfing::AddParameter(p);
						break;
					}
				}
				uniqueName.pop();

				bDone = true; // VEC3
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

					case OFX_IM_MULTIDIM_SPLIT_SLIDERS_FOLDERED:
					{
						bReturn = ofxImGuiSurfing::AddParameter(p, true, true); //-> Should include sugar inside
						//if (bMouseWheel) IMGUI_SUGAR__SLIDER_ADD_MOUSE_WHEEL(p, bMouseWheelFlip.get());
					}
					break;

					default:
						bReturn = ofxImGuiSurfing::AddParameter(p);
						break;
					}
				}
				uniqueName.pop();

				bDone = true; // VEC4
			}

			//--

			else if (isRectangle)
			{
				uniqueName.push();
				{
					ofParameter<ofRectangle> p = aparam.cast<ofRectangle>();

					bReturn = ofxImGuiSurfing::AddParameter(p);
				}
				uniqueName.pop();

				bDone = true; // RECTANGLE
			}


			//--------

			// 3. Closing, Ending last step.

			// -> A widget has been populated, then we can apply the extra arguments..
			if (bDone)
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


		//--

		//-----------------------------------------------------------------
		bool Add(ofAbstractParameter& aparam, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1, SurfingGuiFlags flags = SurfingGuiFlags_None)
		{
			//// Will flag to true to do the final steps: 
			//// same line and spacing config by args.
			//bool bDone = false;

			//// Will flag to notify if the ofParam widget changed.
			//bool bReturn = false;

			// Set the next Widget shape size width/height 
			// reading from the function arguments:

			float _ww; // The width that we will apply to that widget.

			if (amtPerRow == 2) _ww = _w50; // half size
			else if (amtPerRow == 3) _ww = _w33; // third size
			else if (amtPerRow == 4) _ww = _w25; // quarter size
			else _ww = _w100; // full width

			return this->Add(aparam, type, _ww, bSameLine, spacing, flags);
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
		void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen, SurfingGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT, ImGuiCond cond = ImGuiCond_Once)
		{
			bool bIsOpen = false;
			bool bMustHideGroup = false;
			bool bMustCloseTree = false; //TODO: -> add new
			bool bMustDisableIndenting = false;

			bool bSkipNoSerializable = false; //TODO: add to the ui object! to allow more customization.

			// Handle names/pushID's
			// This is the root/first group
			// Level is about how many deep on nested groups we are

			//TODO:
			// -> Must remove all return calls inside below to not break pushIDs if we want to use ID's!

			ImGui::PushID(("##GROUP_" + group.getName()).c_str());
			{
				// A. 
				// This is the root parent group/header:
				//--------------------------------------------------------------

				//-> This should notify it's the root parent group..
				if (uniqueName.getLevel() == 0)
				{
					// Group Style:
					// If a group style is queued, we will overwrite the default style for each type.

					auto c = getStyleGroup(group);
					if (c.name != "-1")
					{
						typeGroup = SurfingGuiTypesGroups(c.type);
						flags = c.flags;
					}
					bMustHideGroup = (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_HIDDEN);

					//--

					// 1. Openings

					if (!bMustHideGroup)
					{
						if (0) {}

						else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_HIDDEN_HEADER)
						{
							bIsOpen = true; // not really closed but not rendered!
							bMustCloseTree = false; // ? should depends of the tree type.. ? //TODO: important!
							bMustDisableIndenting = true;
						}

						else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_DEFAULT ||
							typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
						{
							// workaround
							bool bOpen = (flags == ImGuiTreeNodeFlags_DefaultOpen);
							ImGui::SetNextItemOpen(bOpen, cond);
							//ImGui::SetNextItemOpen(bOpen, ImGuiCond_Appearing);

							bIsOpen = ImGui::CollapsingHeader(group.getName().c_str(), flags);
							bMustCloseTree = false; // we dont need to close tree!
						}

						else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_TREE)
						{
							// workaround bc tree has no flags..
							bool bOpen = (flags == ImGuiTreeNodeFlags_DefaultOpen);
							ImGui::SetNextItemOpen(bOpen, cond);
							//ImGui::SetNextItemOpen(bOpen, ImGuiCond_Appearing);

							bIsOpen = ImGui::TreeNode(group.getName().c_str());
							bMustCloseTree = bIsOpen;
						}

						else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
						{
							bIsOpen = ImGui::TreeNodeEx(group.getName().c_str(), flags);
							bMustCloseTree = bIsOpen;
						}

						else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
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
						//else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_WINDOWED)
						//{
						//}
					}

					//--

					// 2. Header already rendered

					uniqueName.setOpen(bIsOpen); //TODO: ?

					//--

					// 4. To re calculate layout sizes after headers and indenting.

					refreshLayout();

					//--

					// 5. Skip all nested groups and their params

					if (!bIsOpen)
					{
						ImGui::PopID();
						return;
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

					// Will detect nested groups recursively
					if (parameterGroup)
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
								typeGroup = SurfingGuiTypesGroups(c.type); // overwrite main type
								flags = c.flags;
							}

							std::string name = parameterGroup->getName();

							//----

							if (0) {}

							// Hidden
							//else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_HIDDE_ALL_HEADERS)
							//{
							//	AddGroup(*parameterGroup, flags, typeGroup);
							//}
							//else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_ONLY_FIRST_HEADER)
							//{
							//	ImGui::Indent();
							//	bool b = ImGui::CollapsingHeader(parameterGroup->getName().c_str(), flags);
							//	if (b) AddGroup(*parameterGroup, flags, typeGroup);
							//	ImGui::Unindent();
							//}

							else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_HIDDEN)
							{
								// Must skip contained params
							}

							else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_HIDDEN_HEADER)
							{
								if (!bMustDisableIndenting) ImGui::Indent();
								{
									refreshLayout(); // ?

									AddGroup(*parameterGroup, flags, typeGroup);
								}
								if (!bMustDisableIndenting) ImGui::Unindent();
							}

							else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_DEFAULT)
							{
								ImGui::Indent();
								refreshLayout(); // ?
								bool b = ImGui::CollapsingHeader(name.c_str(), flags);
								if (b) AddGroup(*parameterGroup, flags, typeGroup);
								ImGui::Unindent();
							}

							else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
							{
								ImGui::Indent();
								refreshLayout(); // ?
								bool b = ImGui::CollapsingHeader(name.c_str(), flags);
								if (b) AddGroup(*parameterGroup, flags, typeGroup);
								ImGui::Unindent();
							}

							else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_TREE)
							{
								//TODO:
								// workaround bc tree has no flags..
								bool bOpen = (flags == ImGuiTreeNodeFlags_DefaultOpen);
								ImGui::SetNextItemOpen(bOpen, cond);
								//ImGui::SetNextItemOpen(bOpen, ImGuiCond_Appearing);

								if (ImGui::TreeNode(name.c_str()))
								{
									ImGui::Indent();
									refreshLayout(); // ?
									AddGroup(*parameterGroup, flags, typeGroup);
									ImGui::Unindent();

									ImGui::TreePop();
								}
							}

							else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
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

							else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
							{
								// Scrollable zone

								// A. Height variable to amount of widgets..
								//auto& style = ImGui::GetStyle();
								//float hratio = 1.0; // 1. is the same height of items (considerate that font size is 14)
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
					// Should add styles yet for unknown types!

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

						// FLOAT

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

						// INT

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

						// BOOL

						auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
						if (parameterBool)
						{
							//TODO:
							if (bSkipNoSerializable)
							{
								if (!parameterBool->isSerializable()) continue;
							}

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

						// STRING

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
								//Add(*parameterString, OFX_IM_DEFAULT);
								////AddParameter(*parameterString);
							}
							continue;
						}

						//--

						// FLOAT COLOR

						auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
						if (parameterFloatColor)
						{
							auto c = getStyle(*parameterFloatColor);
							// if the parameter widget is not added explicitly, will populate it as the default appearance
							if (c.name != "-1")
							{
								Add(*parameterFloatColor, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							// Default style
							else
							{
								//AddParameter(*parameterFloatColor);
								// fixing to allow mouse wheel..
								Add(*parameterFloatColor, c.type, c.amtPerRow, c.bSameLine, c.spacing);

							}
							continue;
						}

						//--

						// COLOR

						auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
						if (parameterColor)
						{
							auto c = getStyle(*parameterColor);

							// If the parameter widget is not added explicitly, will populate it as the default appearance
							if (c.name != "-1")
							{
								Add(*parameterColor, c.type, c.amtPerRow, c.bSameLine, c.spacing);
							}
							// Default style
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

						else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_DEFAULT ||
							typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
						{
							// Do not requires closing/pop
						}

						else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_TREE)
						{
							if (bMustCloseTree) ImGui::TreePop();
						}

						else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
						{
							if (bMustCloseTree) ImGui::TreePop();
						}

						else if (typeGroup == SurfingGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
						{
							ImGui::EndChild();
							ImGui::Unindent();

							// Don't needs to close tree bc uses a collapsingHeader tree when begins!
						}
					}

					//-

					//ImGui::PopID(); // Group main
					////}
				}
			}

			//TODO:
			ImGui::PopID();
		}
	};

	//--

} // namespace ofxSurfing
