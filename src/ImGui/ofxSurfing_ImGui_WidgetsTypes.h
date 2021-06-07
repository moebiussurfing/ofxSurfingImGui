#pragma once

#include "ofMain.h"

//#include "ranges.h"
#include <list>
#include <iostream>
#include <boost/range/adaptor/reversed.hpp>

#include "ofxImGui.h"
#include "imgui_internal.h"

#include "ofxSurfing_ImGui_LayoutManager.h"
#include "ofxSurfing_ImGui_WidgetsButtons.h"

namespace ofxSurfing {

	class ImWidgetSurfingType {

	public:

		// widgets sizes
		float _spcx;
		float _spcy;
		float _w100;
		float _h100;
		float _w99;
		float _w50;
		float _w33;
		float _w25;
		float _h;

		//-

		// refresh current panel shape to update widgets sizes
		void refreshPanelShape()
		{
			ofxSurfingHelpers::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);
		}

		//-

		enum ImWidgetSurfingTYPE
		{
			IMGUI_WIDGET_TYPE_DEFAULT = 0,
			//bool
			IMGUI_WIDGET_TYPE_BOOL_CHECK,
			IMGUI_WIDGET_TYPE_BOOL_BUTTON_SMALL,
			IMGUI_WIDGET_TYPE_BOOL_BUTTON_BIG,
			IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL,
			IMGUI_WIDGET_TYPE_BOOL_TOGGLE_BIG,
			//float/int
			IMGUI_WIDGET_TYPE_SLIDER,
			IMGUI_WIDGET_TYPE_STEPPER,
			IMGUI_WIDGET_TYPE_DRAG,
			//IMGUI_WIDGET_TYPE_TEXT_BIG,
			NUM_IMWIDGET_TYPES
		};

		//-

		class surfingImWidgetConf {
		public:
			ImWidgetSurfingTYPE type = IMGUI_WIDGET_TYPE_DEFAULT;
			std::string name = "";
			int amtPerRow = 1;
			bool bSameLine = false;
			int spacing = -1;
		};

		//-

		vector<surfingImWidgetConf> widgetsConfs;

		ImWidgetSurfingType::ImWidgetSurfingType() {
			widgetsConfs.clear();
		}

		//-

		surfingImWidgetConf getWidgetConf(ofAbstractParameter& aparam) {

			// https://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop
			//std::list<int> x{ 2, 3, 5, 7, 11, 13, 17, 19 };
			//for (auto i : boost::adaptors::reverse(x))
			//	std::cout << i << '\n';
			//for (auto i : x)
			//	std::cout << i << '\n';

			//for (auto c : boost::adaptors::reverse(widgetsConfs))
			for (auto c : widgetsConfs)
			{
				if (c.name == aparam.getName()) // param was added to the queue
				{
					return c;
				}
			}

			surfingImWidgetConf confError;
			confError.name = "-1";
			return confError;
		}

		//-

		// queue a customization config for future populate a param widget
		void AddWidgetConf(ofAbstractParameter& aparam, ImWidgetSurfingTYPE type, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		{
			surfingImWidgetConf c;
			c.name = aparam.getName();
			c.type = type;
			c.amtPerRow = amtPerRow;
			c.bSameLine = bSameLine;
			c.spacing = spacing;

			widgetsConfs.push_back(c);
		}

		//-

		//bool Add(ofAbstractParameter& aparam, ImWidgetSurfingType type) {
		//	Add(bMode1, ImWidgetSurfingType::IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL, 3, true);
		//}

		//-

		//void AddWidgetConf(string name, ImWidgetSurfingTYPE type) {
		//	surfingImWidgetConf e;
		//	e.name = name;
		//	e.type = type;
		//	widgetsConfs.push_back(e);
		//}

		//-

		ImWidgetSurfingTYPE getType(ofAbstractParameter& aparam)
		{
			string name = aparam.getName();
			ImWidgetSurfingTYPE rtype = ImWidgetSurfingTYPE(IMGUI_WIDGET_TYPE_DEFAULT);

			auto type = aparam.type();
			bool isBool = type == typeid(ofParameter<bool>).name();
			if (!isBool) return rtype;

			for (auto w : widgetsConfs)
			{
				if (w.name == name)
				{
					rtype = ImWidgetSurfingTYPE(w.type);
				}
			}

			return rtype;
		}

		//-

		// populate a parameter ImGui widget
		bool Add(ofAbstractParameter& aparam, ImWidgetSurfingTYPE type = IMGUI_WIDGET_TYPE_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1)
		{
			auto ptype = aparam.type();
			bool isBool = ptype == typeid(ofParameter<bool>).name();
			bool isFloat = ptype == typeid(ofParameter<float>).name();
			bool isInt = ptype == typeid(ofParameter<int>).name();
			bool bReturn = false;

			float _ww;
			if (amtPerRow == 1) _ww = _w100;
			else if (amtPerRow == 2) _ww = _w50;
			else if (amtPerRow == 3) _ww = _w33;
			else if (amtPerRow == 4) _ww = _w25;

			if (isBool)
			{
				ofParameter<bool> p = aparam.cast<bool>();
				auto tmpRef = p.get();

				switch (type)
				{
				case IMGUI_WIDGET_TYPE_BOOL_BUTTON_SMALL:
					bReturn = ofxSurfingHelpers::AddBigButton(p, _ww, _h / 2);
					break;

				case IMGUI_WIDGET_TYPE_BOOL_BUTTON_BIG:
					bReturn = ofxSurfingHelpers::AddBigButton(p, _ww, _h);
					break;

				case IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL:
					bReturn = ofxSurfingHelpers::AddBigToggle(p, _ww, _h / 2);
					break;

				case IMGUI_WIDGET_TYPE_BOOL_TOGGLE_BIG:
					bReturn = ofxSurfingHelpers::AddBigToggle(p, _ww, _h);
					break;

				case IMGUI_WIDGET_TYPE_DEFAULT:
				case IMGUI_WIDGET_TYPE_BOOL_CHECK:
				default:
				{
					ImGui::PushID(1);
					if (ImGui::Checkbox(p.getName().c_str(), (bool *)&tmpRef))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				}
				break;
				}
			}

			//-

			if (isFloat)
			{
				ofParameter<float> p = aparam.cast<float>();
				auto tmpRef = p.get();

				switch (type)
				{
				case IMGUI_WIDGET_TYPE_DEFAULT:
				case IMGUI_WIDGET_TYPE_SLIDER:
				{
					ImGui::PushID(1);
					if (ImGui::SliderFloat(p.getName().c_str(), (float *)&tmpRef, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;

				case IMGUI_WIDGET_TYPE_DRAG:
				{
					const float speed = 0.01f;
					ImGui::PushID(1);
					if (ImGui::DragFloat(p.getName().c_str(), (float *)&tmpRef, speed, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;

				case IMGUI_WIDGET_TYPE_STEPPER:
				{
					const float step = 0.001f;
					const float stepFast = 0.1f;
					auto tmpRef = p.get();
					ImGui::PushID(1);
					if (ImGui::InputFloat(p.getName().c_str(), (float *)&tmpRef, step, stepFast))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;
				}
			}

			//-

			if (isInt)
			{
				ofParameter<int> p = aparam.cast<int>();
				auto tmpRef = p.get();

				switch (type)
				{
				case IMGUI_WIDGET_TYPE_DEFAULT:
				case IMGUI_WIDGET_TYPE_SLIDER:
				{
					ImGui::PushID(1);
					if (ImGui::SliderInt(p.getName().c_str(), (int *)&tmpRef, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;

				case IMGUI_WIDGET_TYPE_DRAG:
				{
					const float speed = 1;
					ImGui::PushID(1);
					if (ImGui::DragInt(p.getName().c_str(), (int *)&tmpRef, speed, p.getMin(), p.getMax()))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;

				case IMGUI_WIDGET_TYPE_STEPPER:
				{
					const int step = 1;
					const int stepFast = 5;
					auto tmpRef = p.get();
					ImGui::PushID(1);
					if (ImGui::InputInt(p.getName().c_str(), (int *)&tmpRef, step, stepFast))
					{
						p.set(tmpRef);
						ImGui::PopID();
						bReturn = true;
					}
					ImGui::PopID();
					bReturn = false;
				} break;
				}
			}

			//-

			// extra options
			if (bSameLine) ImGui::SameLine();
			if (spacing != -1) {
				ImGui::Dummy(ImVec2(0.0f, (float)spacing));// spacing
			}

			//-

			return bReturn;
		}
	};
}// namespace ofxSurfing