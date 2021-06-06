#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_internal.h"

#include "ofxSurfing_ImGui_LayoutManager.h"
#include "ofxSurfing_ImGui_WidgetsButtons.h"

namespace ofxSurfing {

	class ImWidgetSurfingType {
	public:

		enum ImWidgetSurfingTYPE
		{
			IMGUI_WIDGET_TYPE_DEFAULT = 0,
			IMGUI_WIDGET_TYPE_BOOL_CHECK,
			IMGUI_WIDGET_TYPE_BOOL_BUTTON_SMALL,
			IMGUI_WIDGET_TYPE_BOOL_BUTTON_BIG,
			IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL,
			IMGUI_WIDGET_TYPE_BOOL_TOGGLE_BIG,
			//IMGUI_WIDGET_TYPE_SLIDER,
			//IMGUI_WIDGET_TYPE_STEPPER,
			//IMGUI_WIDGET_TYPE_DRAG,
			//IMGUI_WIDGET_TYPE_TEXT_BIG,
			NUM_IMWIDGET_TYPES
		};

		class ImWidgetSurfingELEMENT {
		public:
			ImWidgetSurfingTYPE type;
			std::string name;
		};

		vector<ImWidgetSurfingELEMENT> listWidget;

		ImWidgetSurfingType::ImWidgetSurfingType() {
			listWidget.clear();
		}

		void addWidget(string name, ImWidgetSurfingTYPE type) {
			ImWidgetSurfingELEMENT e;
			e.name = name;
			e.type = type;
			listWidget.push_back(e);
		}

		ImWidgetSurfingTYPE getType(ofAbstractParameter& aparam) {
			string name = aparam.getName();
			ImWidgetSurfingTYPE rtype = ImWidgetSurfingTYPE(IMGUI_WIDGET_TYPE_DEFAULT);

			auto type = aparam.type();
			bool isBool = type == typeid(ofParameter<bool>).name();
			if (!isBool) return rtype;

			for (auto w : listWidget)
			{
				if (w.name == name)
				{
					rtype = ImWidgetSurfingTYPE(w.type);
				}
			}

			return rtype;
		}

		bool populate(ofAbstractParameter& aparam, ImWidgetSurfingTYPE type = IMGUI_WIDGET_TYPE_DEFAULT) {
			auto ptype = aparam.type();
			bool isBool = ptype == typeid(ofParameter<bool>).name();
			bool bReturn = false;

			//widgets sizes
			float _spcx;
			float _spcy;
			float _w100;
			float _h100;
			float _w99;
			float _w50;
			float _w33;
			float _w25;
			float _h;
			ofxSurfingHelpers::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

			if (isBool)
			{
				ofParameter<bool> p = aparam.cast<bool>();
				auto tmpRef = p.get();

				switch (type)
				{
				case IMGUI_WIDGET_TYPE_BOOL_BUTTON_SMALL:
					bReturn = ofxSurfingHelpers::AddBigButton(p, _w100, _h / 2);
					break;

				case IMGUI_WIDGET_TYPE_BOOL_BUTTON_BIG:
					bReturn = ofxSurfingHelpers::AddBigButton(p, _w100, _h);
					break;

				case IMGUI_WIDGET_TYPE_BOOL_TOGGLE_SMALL:
					bReturn = ofxSurfingHelpers::AddBigToggle(p, _w100, _h / 2);
					break;

				case IMGUI_WIDGET_TYPE_BOOL_TOGGLE_BIG:
					bReturn = ofxSurfingHelpers::AddBigToggle(p, _w100, _h);
					break;

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
		}
	};
}// namespace ofxSurfing