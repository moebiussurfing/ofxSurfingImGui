
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
		class SurfingImGuiStyle
		{
		public:
			SurfingImGuiTypes type = OFX_IM_DEFAULT;
			std::string name = "-1";
			int amtPerRow = 1;
			bool bSameLine = false;
			int spacing = -1;
		};

		//-

		// To queue the styles for each param here
		vector<SurfingImGuiStyle> widgetsStyles;

		// to queue all the rendered params to pushId's
		ofParamUniqueName uniqueName;

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
		SurfingImGuiStyle getStyle(ofAbstractParameter& aparam) {

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
			SurfingImGuiStyle cError;
			cError.name = "-1";
			return cError;

			//SurfingImGuiStyle confDefault;
			//confDefault.name = aparam.getName();
			//confDefault.bSameLine = false;
			//confDefault.amtPerRow = 1;
			//confDefault.spacing = -1;
			//return confDefault;
		}

		//-

		//TODO:
		// add remover element?

		// queue a customization config for future populate a param widget
		//--------------------------------------------------------------
		void AddStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1)
		{
			SurfingImGuiStyle c;
			c.name = aparam.getName();
			c.type = type;
			c.bSameLine = bSameLine;
			c.amtPerRow = amtPerRow;
			c.spacing = spacing;

			widgetsStyles.push_back(c);
		}

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
		//	SurfingImGuiStyle e;
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
					if (ImGui::SliderFloat(p.getName().c_str(), (float *)&tmpRef, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						bReturn = true;
					}
					bReturn = false;
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
					if (ImGui::SliderInt(p.getName().c_str(), (int *)&tmpRef, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						bReturn = true;
					}
					bReturn = false;
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

		//--

		// groups

		void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT)
		{
			refreshLayout();

			//--

			for (auto parameter : group)
			{
				// group

				auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);

				if (parameterGroup) // detects nested groups
				{
					//uniqueName.getTag // TODO: to improve a bit more secured
					ImGui::PushID(parameterGroup->getName().c_str()); 
					// ->  unique id for repeated params inside many groups
					
					{
						if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_ONLY_FIRST_HEADER)
						{
							AddGroup(*parameterGroup, flags, typeGroup);
						}
						else
						{
							if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_HIDDE_ALL_HEADERS)
							{
								AddGroup(*parameterGroup, flags, typeGroup);
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_COLLAPSED)
							{
								bool b = ImGui::CollapsingHeader(parameterGroup->getName().data(), flags);
								if (b) AddGroup(*parameterGroup, flags, typeGroup);
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_DEFAULT)
							{
								ImGui::Indent();
								bool b = ImGui::CollapsingHeader(parameterGroup->getName().data(), flags);
								if (b) AddGroup(*parameterGroup, flags, typeGroup);
								ImGui::Unindent();
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE)
							{
								if (ImGui::TreeNode(parameterGroup->getName().data()))
								{
									ImGui::Indent();
									AddGroup(*parameterGroup, flags, typeGroup);
									ImGui::Unindent();

									ImGui::TreePop();
								}
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_TREE_EX)
							{
								if (ImGui::TreeNodeEx(parameterGroup->getName().data(), flags))
								{
									AddGroup(*parameterGroup, flags, typeGroup);

									ImGui::TreePop();
								}
							}

							else if (typeGroup == SurfingImGuiTypesGroups::OFX_IM_GROUP_SCROLLABLE)
							{
								auto& style = ImGui::GetStyle();
								int hh = 40;
								int h = style.FramePadding.y + style.ItemSpacing.y + hh;

								ImGui::BeginChild(parameterGroup->getName().data(), ImVec2(0, parameterGroup->size() * h), false);

								AddGroup(*parameterGroup);

								ImGui::EndChild();
							}
						}
					}

					ImGui::PopID();

					//-

					continue;
				}

				//----

				// Uses "ofxSurfing_ImGui_ofHelpers.h"

				// Parameter, try everything we know how to handle.

//#if OF_VERSION_MINOR >= 10
//				auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
//				if (parameterVec2f)
//				{
//					AddParameter(*parameterVec2f);
//					continue;
//				}
//				auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
//				if (parameterVec3f)
//				{
//					AddParameter(*parameterVec3f);
//					continue;
//				}
//				auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
//				if (parameterVec4f)
//				{
//					AddParameter(*parameterVec4f);
//					continue;
//				}
//#endif
//				auto parameterOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(parameter);
//				if (parameterOfVec2f)
//				{
//					AddParameter(*parameterOfVec2f);
//					continue;
//				}
//				auto parameterOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(parameter);
//				if (parameterOfVec3f)
//				{
//					AddParameter(*parameterOfVec3f);
//					continue;
//				}
//				auto parameterOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(parameter);
//				if (parameterOfVec4f)
//				{
//					AddParameter(*parameterOfVec4f);
//					continue;
//				}
//				auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
//				if (parameterFloatColor)
//				{
//					AddParameter(*parameterFloatColor);
//					continue;
//				}
//				auto parameterColor = std::dynamic_pointer_cast<ofParameter<ofColor>>(parameter);
//				if (parameterColor)
//				{
//					AddParameter(*parameterColor);
//					continue;
//				}

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

				//--

				ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName();
			}
		}

	};

	//--

} // namespace ofxSurfing
