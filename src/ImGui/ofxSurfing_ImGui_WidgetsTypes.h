#pragma once

#include "ofMain.h"

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
		
		void refreshPanelWidth()
		{
			ofxSurfingHelpers::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);
		}

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

		vector<ImWidgetSurfingELEMENT> widgetsConfs;

		ImWidgetSurfingType::ImWidgetSurfingType() {
			widgetsConfs.clear();
		}
		
		void AddWidgetConf(ofAbstractParameter& aparam, ImWidgetSurfingTYPE type) {
			string name = aparam.getName();
			ImWidgetSurfingELEMENT e;
			e.name = name;
			e.type = type;
			widgetsConfs.push_back(e);
		}

		void AddWidgetConf(string name, ImWidgetSurfingTYPE type) {
			ImWidgetSurfingELEMENT e;
			e.name = name;
			e.type = type;
			widgetsConfs.push_back(e);
		}

		ImWidgetSurfingTYPE getType(ofAbstractParameter& aparam) {
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

		bool Add(ofAbstractParameter& aparam, ImWidgetSurfingTYPE type = IMGUI_WIDGET_TYPE_DEFAULT, int amtPerRow = 1, bool bSameLine = false, int spacing = -1) {
			auto ptype = aparam.type();
			bool isBool = ptype == typeid(ofParameter<bool>).name();
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

				//-

				// extra options
				if(bSameLine) ImGui::SameLine();
				if (spacing != -1) {
					ImGui::Dummy(ImVec2(0.0f, (float)spacing));// spacing
				}
			}

			return bReturn;
		}
	};
}// namespace ofxSurfing