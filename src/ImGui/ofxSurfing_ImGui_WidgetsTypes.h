
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"

#include "ofxSurfing_ImGui_LayoutHelpers.h"

#include "ofxSurfing_ImGui_ofHelpers.h"
//#include "ofxSurfing_ImGui_LayoutHelpers.h"
//#include "ofxSurfing_ImGui_Widgets.h"

#include "ofxSurfing_ImGui_WidgetsTypesConstants.h"
#include "ofxSurfing_ImGui_WidgetsTypesUniqueNames.h"

//-

#include <list>
#include <iostream>
#include <boost/range/adaptor/reversed.hpp>

//-

namespace ofxImGuiSurfing
{
	class ofxSurfing_ImGui_WidgetsTypes
	{
		//--

		// widgets sizes

	private:

		float _spcx;
		float _spcy;
		float _w100;
		float _w99;
		float _w50;
		float _w33;
		float _w25;
		float _h100;
		float _h;

		//--

	public:

		// refresh current panel shape to update widgets sizes
		//--------------------------------------------------------------
		void refreshPanelShape()
		{
			ofxImGuiSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);
		}
		//--------------------------------------------------------------
		void refresh() // short name
		{
			refreshPanelShape();
		}
		//--------------------------------------------------------------
		void refreshLayout() // short name
		{
			refreshPanelShape();
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

		// to queue all the rendered params to pushId's
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

			// if return has not been called yet here,
			// then there's no conf added (AddStyle) for the parameter
			// we return a kind of error type to be detected
			// and to be drawn with the default style.
			SurfingImGuiTypes_Style cError;
			cError.name = "-1";
			return cError;

			//SurfingImGuiTypes_Style confDefault;
			//confDefault.name = aparam.getName();
			//confDefault.bSameLine = false;
			//confDefault.amtPerRow = 1;
			//confDefault.spacing = -1;
			//return confDefault;
		}

		//-

		//TODO:
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
			cError.name = "-1";
			return cError;
		}

		//--

		//TODO:
		// add remover / update style element o runtime?
		//--------------------------------------------------------------
		void UpdateStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT)
		{
			//widgetsStyles.getPosition(aparam)
			//update style

			//SurfingImGuiTypes_Style c;
			//c.name = aparam.getName();
			//c.type = type;
			//c.bSameLine = bSameLine;
			//c.amtPerRow = amtPerRow;
			//c.spacing = spacing;

			//widgetsStyles.push_back(c);
		}

		// queue a customization config for future populate a param widget
		//--------------------------------------------------------------
		void AddStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
		{
			SurfingImGuiTypes_Style c;
			c.name = aparam.getName();
			c.type = type;
			c.bSameLine = bSameLine;
			c.amtPerRow = amtPerRow;
			c.spacing = spacing;

			widgetsStyles.push_back(c);
		}

		// queue a customization config for future populate a group
		//--------------------------------------------------------------
		void AddGroupStyle(ofParameterGroup& group, SurfingImGuiTypesGroups type = OFX_IM_GROUP_DEFAULT, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
		{
			SurfingImGuiTypesGroup_Style c;
			c.name = group.getName();
			c.type = type;
			c.flags = flags;

			groupsStyles.push_back(c);
		}

		//--

		//TODO:
		// if we are not using the Types Engine, we will bypass the creation of widgets on ofxSurfing_ImGui_Helpers
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

		//void AddStyle(string name, SurfingImGuiTypes type) {
		//	SurfingImGuiTypes_Style e;
		//	e.name = name;
		//	e.type = type;
		//	widgetsStyles.push_back(e);
		//}

		//-

		//--------------------------------------------------------------
		SurfingImGuiTypes getType(ofAbstractParameter& aparam)
		{
			string name = aparam.getName();
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

		//-

		// render now a parameter ImGui widget
		// remember that must be called inside an ImGui::Begin/End() aka ImGui window/panel !
		//--------------------------------------------------------------
		bool Add(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
		{
			bool bDone = false;

			// if setted as hidden dont draw, but apply same line and spacing and return
			if (type == OFX_IM_HIDDEN)
			{
				uniqueName.push();

				// extra options
				if (bSameLine) ImGui::SameLine();
				if (spacing != -1)
				{
					ImGui::Dummy(ImVec2(0.0f, (float)spacing));// spacing
				}

				uniqueName.pop();
				return false;
			}

			// if setted as hidden dont draw, but apply same line and spacing and return
			else if (type == OFX_IM_DISABLED)
			{
				uniqueName.push();

				// extra options
				if (bSameLine) ImGui::SameLine();
				if (spacing != -1)
				{
					float h = ImGui::GetIO().FontDefault->FontSize + ImGui::GetStyle().FramePadding.y * 2;
					ImGui::InvisibleButton("_inv_", ImVec2(10, h), ImGuiButtonFlags_Disabled);

					ImGui::Dummy(ImVec2(0.0f, (float)spacing));// spacing
				}

				uniqueName.pop();
				return false;
			}

			// disable mouse interaction
			else if (type == OFX_IM_INACTIVE)
			{
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			}

			//----

			auto ptype = aparam.type();

			bool isBool = ptype == typeid(ofParameter<bool>).name();
			bool isFloat = ptype == typeid(ofParameter<float>).name();
			bool isInt = ptype == typeid(ofParameter<int>).name();
			bool isString = ptype == typeid(ofParameter<string>).name();
			bool isColor = ptype == typeid(ofParameter<ofColor>).name();
			bool isFloatColor = ptype == typeid(ofParameter<ofFloatColor>).name();

			// is not called with groups here..
			//bool isGroup = ptype == typeid(ofParameterGroup).name();
			//if (isGroup) 
			//{
			//	refreshPanelShape();
			//	return false;
			//}

			bool bReturn = false;

			// set widget width/size reading from the function arguments
			float _ww;
			if (amtPerRow == 2) _ww = _w50;
			else if (amtPerRow == 3) _ww = _w33;
			else if (amtPerRow == 4) _ww = _w25;
			else _ww = _w100;

			//-

			// bool

			if (isBool)
			{
				ofParameter<bool> p = aparam.cast<bool>();
				auto tmpRef = p.get();

				uniqueName.push();

				switch (type)
				{

				case OFX_IM_DEFAULT:
				case OFX_IM_CHECKBOX:
				case OFX_IM_INACTIVE:
				{
					// default:
					string name = p.getName();
					if (ImGui::Checkbox(p.getName().c_str(), (bool *)&tmpRef))
					{
						p.set(tmpRef);
						bReturn = true;
					}
					uniqueName.pop();
					bReturn = false;
				}
				break;

				case OFX_IM_BUTTON_SMALL:
					bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h);
					break;

				case OFX_IM_BUTTON_BIG:
					bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 2);
					break;

				case OFX_IM_BUTTON_BIG_XXL:
					bReturn = ofxImGuiSurfing::AddBigButton(p, _ww, _h * 3);
					break;

				case OFX_IM_TOGGLE_SMALL:
					bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h);
					break;

				case OFX_IM_TOGGLE_BIG:
					bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 2);
					break;

				case OFX_IM_TOGGLE_BIG_XXL:
					bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 3);
					break;

				case OFX_IM_TOGGLE_SMALL_BORDER:
					bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h, true);
					break;

				case OFX_IM_TOGGLE_BIG_BORDER:
					bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 2, true);
					break;

				case OFX_IM_TOGGLE_BIG_XXL_BORDER:
					bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 3, true);
					break;

				case OFX_IM_TOGGLE_SMALL_BORDER_BLINK:
					bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h, true, true);
					break;

				case OFX_IM_TOGGLE_BIG_BORDER_BLINK:
					bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 2, true, true);
					break;

				case OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK:
					bReturn = ofxImGuiSurfing::AddBigToggle(p, _ww, _h * 3, true, true);
					break;

				case OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL:
					bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p);
					break;

				case OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG:
					bReturn = ofxImGuiSurfing::AddToggleRoundedButton(p, ImVec2(3 * _h, 2 * _h));
					break;
				}

				uniqueName.pop();

				bDone = true;
			}

			//-

			// string

			else if (isString)
			{
				ofParameter<string> p = aparam.cast<string>();
				auto tmpRef = p.get();

				uniqueName.push();

				switch (type)
				{
				case OFX_IM_DEFAULT:
				case OFX_IM_TEXT_DISPLAY:
				{
					ImGui::Text(tmpRef.c_str());
				}
				break;

				case OFX_IM_TEXT_INPUT:
				{
					ImGui::Text(tmpRef.c_str());
					//ofxImGuiSurfing::AddParameter(p);//cant be included?
				}
				break;

				case OFX_IM_TEXT_BIG:
				{
					ImGui::TextWrapped(tmpRef.c_str());
				}
				break;
				}

				uniqueName.pop();

				bDone = true;
			}

			//-

			// float

			else if (isFloat)
			{
				ofParameter<float> p = aparam.cast<float>();
				auto tmpRef = p.get();

				uniqueName.push();

				switch (type)
				{
				case OFX_IM_DEFAULT:
				case OFX_IM_SLIDER:
				case OFX_IM_INACTIVE:
				{
					string name = p.getName();
					ImGui::PushItemWidth(-WIDGET_PARAM_PADDING);
					if (ImGui::SliderFloat(p.getName().c_str(), (float *)&tmpRef, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						bReturn = true;
					}
					bReturn = false;
					ImGui::PopItemWidth();
				}
				break;

				case OFX_IM_PROGRESS_BAR:
				{
					ofxImGuiSurfing::AddProgressBar(p);
					bReturn = false;
				}
				break;

				case OFX_IM_DRAG:
				{
					const float speed = 0.01f;
					if (ImGui::DragFloat(p.getName().c_str(), (float *)&tmpRef, speed, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						bReturn = true;
					}
					bReturn = false;
				}
				break;

				case OFX_IM_STEPPER:
				{
					const float step = 0.001f;
					const float stepFast = 0.1f;
					auto tmpRef = p.get();
					string name = p.getName();
					if (ImGui::InputFloat(p.getName().c_str(), (float *)&tmpRef, step, stepFast))
					{
						p.set(tmpRef);
						bReturn = true;
					}
					bReturn = false;
				}
				break;
				}

				uniqueName.pop();

				bDone = true;
			}

			//-

			// int

			else if (isInt)
			{
				ofParameter<int> p = aparam.cast<int>();
				auto tmpRef = p.get();
				uniqueName.push();

				switch (type)
				{

				case OFX_IM_DEFAULT:
				case OFX_IM_SLIDER:
				case OFX_IM_INACTIVE:
				{
					ImGui::PushItemWidth(-WIDGET_PARAM_PADDING);
					if (ImGui::SliderInt(p.getName().c_str(), (int *)&tmpRef, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						bReturn = true;
					}
					bReturn = false;
					ImGui::PopItemWidth();
				}
				break;

				case OFX_IM_DRAG:
				{
					const float speed = 0.1;
					if (ImGui::DragInt(p.getName().c_str(), (int *)&tmpRef, speed, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						bReturn = true;
					}
					bReturn = false;
				}
				break;

				case OFX_IM_STEPPER:
				{
					const int step = 1;
					const int stepFast = 5;
					auto tmpRef = p.get();
					if (ImGui::InputInt(p.getName().c_str(), (int *)&tmpRef, step, stepFast))
					{
						p.set(tmpRef);
						bReturn = true;
					}
					bReturn = false;
				}
				break;

				case OFX_IM_PROGRESS_BAR:
				{
					string name = p.getName();
					ofxImGuiSurfing::AddProgressBar(p);
					bReturn = false;
				}
				break;

				}

				uniqueName.pop();

				bDone = true;
			}

			//-

			// color

			else if (isFloatColor)
			{
				ofParameter<ofFloatColor> p = aparam.cast<ofFloatColor>();
				auto tmpRef = p.get();
				uniqueName.push();

				ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;
				flags |= ImGuiColorEditFlags_NoInputs;
				flags |= ImGuiColorEditFlags_NoLabel;
				flags |= ImGuiColorEditFlags_NoTooltip;

				if (type == OFX_IM_COLOR_INPUT)
					bReturn = ofxImGuiSurfing::AddParameter(p);

				else if (type == OFX_IM_COLOR_BOX)
					ImGui::ColorButton("", tmpRef, flags);

				uniqueName.pop();
				bDone = true;
			}

			else if (isColor)
			{
				ofParameter<ofColor> p = aparam.cast<ofColor>();
				auto tmpRef = p.get();
				uniqueName.push();

				ImGuiColorEditFlags flags = ImGuiColorEditFlags_None;
				flags |= ImGuiColorEditFlags_NoInputs;
				flags |= ImGuiColorEditFlags_NoLabel;
				flags |= ImGuiColorEditFlags_NoTooltip;

				if (type == OFX_IM_COLOR_INPUT)
					bReturn = ofxImGuiSurfing::AddParameter(p);

				else if (type == OFX_IM_COLOR_BOX)
					ImGui::ColorButton("", tmpRef, flags);

				uniqueName.pop();
				bDone = true;
			}

			//-

			if (bDone)
			{
				// extra options
				if (bSameLine) ImGui::SameLine();
				if (spacing != -1 && spacing != 0)
				{
					ImGui::Dummy(ImVec2(0.0f, (float)spacing)); // spacing
				}
			}

			if (type == OFX_IM_INACTIVE)
			{
				ImGui::PopItemFlag();
			}

			//----

			return bReturn;
		}

		//-----

		// Groups

		//TODO:

	public:
		//--------------------------------------------------------------
		void AddGroup(ofParameterGroup& group)
		{
			AddGroup(group, ImGuiTreeNodeFlags_None, OFX_IM_GROUP_DEFAULT);
		}
		//--------------------------------------------------------------
		void AddGroup(ofParameterGroup& group, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT)
		{
			AddGroup(group, ImGuiTreeNodeFlags_None, typeGroup);
		}
		//--------------------------------------------------------------
		void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None)
		{
			AddGroup(group, flags, OFX_IM_GROUP_DEFAULT);
		}

	public:
		//private:

		//--------------------------------------------------------------
		void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT)
		{
			bool bOpen = false;
			bool bHide = false;

			// handle names/pushID's
			// this is the root/first group
			// level is about how many deep on nested groups we are

			if (uniqueName.getLevel() == 0)
			{
				ImGui::PushID(("##_" + group.getName()).c_str());

				bool bCloseTree = false;

				// if a group style is queued. we overwrite the default style
				auto c = getStyleGroup(group);
				if (c.name != "-1")
				{
					typeGroup = SurfingImGuiTypesGroups(c.type);
					flags = c.flags;
				}

				//bool bHide = false;
				bHide = (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN_HEADER ||
					typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN);

				if (bHide)
				{
					//AddGroup(group, flags, typeGroup); // skip rendering any header, just the content
					bOpen = true; // to avoid below skip. kind of open. just hidding header
				}

				// 1. openings
				if (!bHide)
				{
					if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_DEFAULT ||
						typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
					{
						bOpen = ImGui::CollapsingHeader(group.getName().c_str(), flags);
					}
					else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE)
					{
						bOpen = ImGui::TreeNode(group.getName().c_str());
					}
					else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
					{
						bOpen = ImGui::TreeNodeEx(group.getName().c_str(), flags);
					}
					else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
					{
						// A. height variable to amount widgets..
						//auto& style = ImGui::GetStyle();
						//float hratio = 1.0; // 1. is the same height of items (considerates that font size is 14)
						//int h = 14;
						//int hh = style.FramePadding.y + style.ItemSpacing.y + h;
						//int hhh = parameterGroup->size() * hratio * hh;
						// B. height hardcoded
						int hhh = 200;

						bOpen = ImGui::CollapsingHeader(group.getName().c_str(), flags);
						if (bOpen)
						{
							ImGui::Indent();
							ImGui::BeginChild(group.getName().c_str(), ImVec2(0, hhh), false);
							//AddGroup(*parameterGroup, flags, typeGroup);
						}
					}
				}

				uniqueName.pushGroup(); //TODO: should be in another place
				uniqueName.setOpen(bOpen); //TODO:

				// 2. skip
				if (!bOpen)
				{
					//ImGui::PopID(); //TODO: BUG:
					return;
				}

				//-

				ImGui::PopID(); //TODO: BUG:
			}

			//--

			// measure layout sizes
			refreshLayout();

			//--

			// Here, this is not the root/first group.
			// We go populate the params widgets
			
			for (auto parameter : group)
			{
				// group

				auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);

				if (parameterGroup) // detects nested groups
				{
					// ->  unique id for repeated params inside many groups
					ImGui::PushID(parameterGroup->getName().c_str());

					{
						//if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_ONLY_FIRST_HEADER)
						//{
						//	AddGroup(*parameterGroup, flags, typeGroup); // skip rendering any header, just the content
						//}
						//else
						{
							SurfingImGuiTypesGroups typeGroup_PRE = typeGroup;
							ImGuiTreeNodeFlags flags_PRE = flags;

							bool bRestore = false;
							auto c = getStyleGroup(*parameterGroup);
							if (c.name != "-1")
							{
								typeGroup = SurfingImGuiTypesGroups(c.type); // overwrite main type
								flags = c.flags;
								bRestore = true;
							}

							//--

							// hidden

							if (false) {}

							//else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDE_ALL_HEADERS)
							//{
							//	AddGroup(*parameterGroup, flags, typeGroup);
							//}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN_HEADER)
							{
								AddGroup(*parameterGroup, flags, typeGroup);
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDEN)
							{
							}

							//else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_ONLY_FIRST_HEADER)
							//{
							//	ImGui::Indent();
							//	bool b = ImGui::CollapsingHeader(parameterGroup->getName().c_str(), flags);
							//	if (b) AddGroup(*parameterGroup, flags, typeGroup);
							//	ImGui::Unindent();
							//}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_DEFAULT)
							{
								ImGui::Indent();
								bool b = ImGui::CollapsingHeader(parameterGroup->getName().c_str(), flags);
								if (b) AddGroup(*parameterGroup, flags, typeGroup);
								ImGui::Unindent();
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
							{
								bool b = ImGui::CollapsingHeader(parameterGroup->getName().c_str(), flags);
								if (b) AddGroup(*parameterGroup, flags, typeGroup);
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE)
							{
								if (ImGui::TreeNode(parameterGroup->getName().c_str()))
								{
									ImGui::Indent();
									AddGroup(*parameterGroup, flags, typeGroup);
									ImGui::Unindent();

									ImGui::TreePop();
								}
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
							{
								if (ImGui::TreeNodeEx(parameterGroup->getName().c_str(), flags))
								{
									AddGroup(*parameterGroup, flags, typeGroup);

									ImGui::TreePop();
								}
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
							{
								// A. height variable to amount widgets..
								//auto& style = ImGui::GetStyle();
								//float hratio = 1.0; // 1. is the same height of items (considerates that font size is 14)
								//int h = 14;
								//int hh = style.FramePadding.y + style.ItemSpacing.y + h;
								//int hhh = parameterGroup->size() * hratio * hh;
								// B. height hardcoded
								int hhh = 200;

								//ImGui::Text((parameterGroup->getName() + ":").c_str());
								bool b = ImGui::CollapsingHeader(parameterGroup->getName().c_str(), flags);
								if (b)
								{
									ImGui::Indent();
									ImGui::BeginChild(parameterGroup->getName().c_str(), ImVec2(0, hhh), false);

									AddGroup(*parameterGroup, flags, typeGroup);

									ImGui::EndChild();
									ImGui::Unindent();
								}
							}

							//-

							// TODO: this is not being used...
							// restore previous type
							if (bRestore) {
								typeGroup = typeGroup_PRE;
								flags = flags_PRE;
							}
						}
					}

					ImGui::PopID(); // group iterated

					//-

					continue;
				}

				//----


				// Parameter, try everything we know how to handle.
				// but do not have styles types!

				{
					// Uses "ofxSurfing_ImGui_ofHelpers.h"
					//TODO:
					// no styles yet for unknow types!

#if OF_VERSION_MINOR >= 10
					auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
					if (parameterVec2f)
					{
						AddParameter(*parameterVec2f);
						continue;
					}
					auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
					if (parameterVec3f)
					{
						AddParameter(*parameterVec3f);
						continue;
					}
					auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
					if (parameterVec4f)
					{
						AddParameter(*parameterVec4f);
						continue;
					}
#endif
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

					//----

					// known styles for know types

					// float
					auto parameterFloat = std::dynamic_pointer_cast<ofParameter<float>>(parameter);
					if (parameterFloat)
					{
						auto c = getStyle(*parameterFloat);
						// if the parameter widget is not added explicitly, will populate it as the default appearance
						if (c.name != "-1")
						{
							Add(*parameterFloat, c.type, c.bSameLine, c.amtPerRow, c.spacing);
						}
						// default style
						else
						{
							AddParameter(*parameterFloat);
						}
						continue;
					}

					// int
					auto parameterInt = std::dynamic_pointer_cast<ofParameter<int>>(parameter);
					if (parameterInt)
					{
						auto c = getStyle(*parameterInt);
						if (c.name != "-1")
						{
							Add(*parameterInt, c.type, c.bSameLine, c.amtPerRow, c.spacing);
						}
						else
						{
							AddParameter(*parameterInt);
						}
						continue;
					}

					// bool
					auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
					if (parameterBool)
					{
						auto c = getStyle(*parameterBool);
						if (c.name != "-1")
						{
							Add(*parameterBool, c.type, c.bSameLine, c.amtPerRow, c.spacing);
						}
						else
						{
							AddParameter(*parameterBool);
						}
						continue;
					}

					// string
					auto parameterString = std::dynamic_pointer_cast<ofParameter<std::string>>(parameter);
					if (parameterString)
					{
						auto c = getStyle(*parameterString);
						if (c.name != "-1")
						{
							Add(*parameterString, c.type, c.bSameLine, c.amtPerRow, c.spacing);
						}
						else
						{
							AddParameter(*parameterString);
						}
						continue;
					}

					// float color
					auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
					if (parameterFloatColor)
					{
						auto c = getStyle(*parameterFloatColor);
						// if the parameter widget is not added explicitly, will populate it as the default appearance
						if (c.name != "-1")
						{
							Add(*parameterFloatColor, c.type, c.bSameLine, c.amtPerRow, c.spacing);
						}
						// default style
						else
						{
							AddParameter(*parameterFloatColor);
						}
						continue;
					}

					// color
					auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
					if (parameterColor)
					{
						auto c = getStyle(*parameterColor);
						// if the parameter widget is not added explicitly, will populate it as the default appearance
						if (c.name != "-1")
						{
							Add(*parameterColor, c.type, c.bSameLine, c.amtPerRow, c.spacing);
						}
						// default style
						else
						{
							AddParameter(*parameterColor);
						}
						continue;
					}

					//--

					if (parameter->getName() == "" && parameter->getName() == " ")
						ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName() << "'";
				}
			}

			// 3. closings
			// handle names/pushID's
			if (uniqueName.getLevel() == 0)
			{
				if (bOpen)
				{
					if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_DEFAULT ||
						typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
					{
						// do not requires closing/pop
					}
					else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE)
					{
						if (!bHide) ImGui::TreePop();
					}
					else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
					{
						if (!bHide) ImGui::TreePop();
					}
					else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
					{
						ImGui::EndChild();
						ImGui::Unindent();
					}
				}

				//-

				//ImGui::PopID(); // group main
				//}
			}
		}
	};

	//--

} // namespace ofxSurfing
