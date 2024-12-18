#pragma once

/*

	ofParameter Helpers

	to easily render any ofParameter
	using different widgets styles for each different types.

	NOTE:
	This class can be included on a header to help with ofParams.
	The will avoid to include the big and full "ofxSurfingImGui.h",
	the one that acts as Gui Manager, but then
	we can not use the full power of the API.

*/


/*
	TODO:

	fix mouse wheel for multi dim params

	Add customization for nested groups
	pass some list of arguments
	to customize items/groups
	to be rendered with different styles:
	https://github.com/Daandelange/ofxImGui/issues/6#issuecomment-832174921


	// imgui logarithmic
	//--------------------------------------------------------------
	bool ofxImGui::AddSlider(ofParameter<float>& parameter, const char* format, bool logarithmic)
	{
		auto tmpRef = parameter.get();
		if (ImGui::SliderFloat(GetUniqueName(parameter), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), format, logarithmic? ImGuiSliderFlags_Logarithmic : ImGuiSliderFlags_None))
		{
			parameter.set(tmpRef);
			return true;
		}
		return false;
	}
*/


//----

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "Widgets.h"
#include "SurfingGuiSugar.h"//includes "GuiConstants.h"
#include "SurfingGuiConstants.h"

#include "HelpTextWidget.h"
//#include "Combos.h"

//----

namespace ofxImGuiSurfing
{
	//----

	// Mouse Extra functionality

	//TODO: ?
	// Mouse Wheel
	// To be notified that param associated changed by the mouse..?
	// Gets only that is pressed as button, not as wheel stepping. 
	// Useful for boolean switching, not used by float/int's.
	//--------------------------------------------------------------
	inline bool GetMouseWheel()
	{
		ImGui::SetItemKeyOwner(ImGuiKey_MouseWheelY);

		bool bReturn = false;

		if (ImGui::IsItemHovered())
		{
			float wheel = ImGui::GetIO().MouseWheel;

			if (wheel)
			{
				if (ImGui::IsItemActive())
				{
					ImGui::ClearActiveID();
				}
				else
				{
					bReturn = true;
				}
			}
		}

		return bReturn;
	}

	// Adds mouse wheel control to the last previous param widget (templated float/int).
	// Put after populate widget!
	//--------------------------------------------------------------
	template <typename ParameterType>
	inline void AddMouseWheel(ofParameter<ParameterType>& ap, bool bFlip = false)
	{
		//#define SURFING_IMGUI__USE_MOUSE_WHEEL_AT_BOOLEANS_VOID 
		// Disable to avoid that mouse wheel dragging scroll windows,
		// trigs button by error!

		//TODO: 
		// Workaround
		// Allow customization
		// Forced to default behavior/resolution stepping.
		float resolution = -1;

		//bool bIsUnknown = false;
		bool bIsVoid = false;
		bool bIsbool = false;
		bool bIsInt = false;
		bool bIsFloat = false;
		bool bIsMultiDim = false;
		bool bIsDim2 = false;
		bool bIsDim3 = false;
		bool bIsDim4 = false;

		string sTooltip = "-1";

		const auto& info = typeid(ParameterType);

		if (info == typeid(float)) // Float
		{
			bIsFloat = true;
		}
		else if (info == typeid(int)) // Int
		{
			bIsInt = true;
		}

#ifdef SURFING_IMGUI__USE_MOUSE_WHEEL_AT_BOOLEANS_VOID
		else if (info == typeid(bool)) // Bool
		{
			bIsbool = true;
		}
		else if (info == typeid(void)) // Void
		{
			bIsVoid = true;
		}
#else 
		else if (info == typeid(bool)) // Bool
		{
			return;
		}
		else if (info == typeid(void)) // Void
		{
			return;
		}
#endif

		//TODO:
		else if (info == typeid(ofDefaultVec2))
		{
			bIsMultiDim = true;
			bIsDim2 = true;
		}
		else if (info == typeid(ofDefaultVec3))
		{
			bIsMultiDim = true;
			bIsDim3 = true;
		}
		else if (info == typeid(ofDefaultVec4))
		{
			bIsMultiDim = true;
			bIsDim4 = true;
		}

		//TODO: add quaternion

		// Unknown Types
		else
		{
			//bIsUnknown = true;
			ofLogWarning("ofxSurfingImGui") << "Could not add mouse wheel to " << ap.getName();

			return;
		}

		//--

		{
			bool bCtrl = ImGui::GetIO().KeyCtrl; // CTRL key to fine tunning
			bool bAlt = ImGui::GetIO().KeyAlt; // ALT key to fine tunning

			// Show floating value
			if (bCtrl || bAlt)
			{
				if (bIsInt) sTooltip = ofToString(dynamic_cast<ofParameter<int>&>(ap).get());
				else if (bIsFloat) sTooltip = ofToString(dynamic_cast<ofParameter<float>&>(ap).get(), 2);

#ifdef SURFING_IMGUI__USE_MOUSE_WHEEL_AT_BOOLEANS_VOID
				else if (bIsbool) sTooltip = dynamic_cast<ofParameter<bool>&>(ap).get() ? "TRUE" : "FALSE";
#endif
			}

			ImGui::SetItemKeyOwner(ImGuiKey_MouseWheelY);

			if (ImGui::IsItemHovered())
			{
				float wheel = ImGui::GetIO().MouseWheel;

				if (wheel)
				{
					if (ImGui::IsItemActive())
					{
						ImGui::ClearActiveID();
					}
					else
					{
						//--

						// Bool

						if (bIsbool)
						{
							// non dynamic causes exception in macOS
							ofParameter<bool> p = dynamic_cast<ofParameter<bool>&>(ap);
							p = !p.get();
						}

						//--

						// Void

						else if (bIsVoid)
						{
							ofParameter<void> p = dynamic_cast<ofParameter<void>&>(ap);
							p.trigger();

							sTooltip = "TRIG";
						}

						//--

						// Multidim

						//TODO:
						// Must be fixed bc each dim slider could work independently...
						// Problems came bc the components are not a param...
						else if (bIsMultiDim)
						{
							/*
							if (resolution == -1)
							{
								//TODO:
								// hardcoded to 0.1 bc each dim could be different scale..
								resolution = 0.1f;
							}

							if (bIsDim2)
							{
								ofParameter<glm::vec2> p = ap.cast<glm::vec2>();
								p += wheel * (bCtrl ? resolution : resolution * 10);
								p = ofClamp(p, p.getMin(), p.getMax()); // clamp
							}
							else if (bIsDim3)
							{
								ofParameter<glm::vec3> p = ap.cast<glm::vec3>();
								p += wheel * (bCtrl ? resolution : resolution * 10);
								p = ofClamp(p, p.getMin(), p.getMax()); // clamp
							}
							else if (bIsDim2)
							{
								ofParameter<glm::vec4> p = ap.cast<glm::vec4>();
								p += wheel * (bCtrl ? resolution : resolution * 10);
								p = ofClamp(p, p.getMin(), p.getMax()); // clamp
							}
							*/
						}

						//--

						// Int

						else if (bIsInt)
						{
							ofParameter<int> p = dynamic_cast<ofParameter<int>&>(ap);

							int _step = 0;

							if (resolution == -1) // default, not defined. must be calculated
							{
								float _range = abs(p.getMax() - p.getMin());

								//TODO: workflow should be improved..

								if (_range < IMGUI_MOUSE_WHEEL_STEPS)
								{
									if (bCtrl)
									{
										_step = 1;
									}
									else
									{
										_step = _range / 10;
									}
								}
								else
								{
									// Step resolution to guaranties 
									// that 100 steps walks the full range!
									float _resolution = _range / IMGUI_MOUSE_WHEEL_STEPS;
									resolution = MAX(1, _resolution);

									if (!bCtrl)
									{
										_step = resolution;
									}
									else
									{
										_step = resolution * IMGUI_MOUSE_WHEEL_FINETUNE_CTRL_RATIO;
									}
								}

								// IMGUI_MOUSE_WHEEL_STEPS is 100 or 1000 steps for all the param range
							}

							// Minimum step is one unit!
							_step = MAX(1, _step);

							//--

							int step = wheel * _step;

							// Make minim one unit

							//if (step < 0) {
							//	step = MIN(-1, step);
							//}
							//else {
							//	step = MAX(1, step);
							//}

							//// Negative
							//if (step < 0 && step > -1) step = MIN(- 1, step);
							//
							//// Positive
							//else if (step > 0 && step < 1) MAX(1, step);

							// Mouse wheel flipped
							if (bFlip) p -= step;
							else p += step;

							p = ofClamp(p, p.getMin(), p.getMax()); // clamp
						}

						//--

						// Float

						else if (bIsFloat)
						{
							ofParameter<float> p = dynamic_cast<ofParameter<float>&>(ap);

							if (resolution == -1)
							{
								// IMGUI_MOUSE_WHEEL_STEPS is 100 steps spread into all the param range
								resolution = (p.getMax() - p.getMin()) / IMGUI_MOUSE_WHEEL_STEPS;
							}

							float step = wheel * (!bCtrl
								? resolution
								: resolution * (float)IMGUI_MOUSE_WHEEL_FINETUNE_CTRL_RATIO);

							if (bFlip) p -= step;
							else p += step;

							p = ofClamp(p, p.getMin(), p.getMax()); // clamp
						}
					}
				}

				//--
#if 0
				// Add overlay when fine-tunning
				// Fine-tunning enabled
				if (bCtrl || bAlt)
				{
					if (sTooltip != "-1")
					{
						if (ImGui::IsItemHovered())
						{
							ImGui::BeginTooltip();
							ImGui::Text("%s", sTooltip.c_str());
							ImGui::EndTooltip();

							//ImGui::BeginTooltip();
							//ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
							//ImGui::Text("%s", sTooltip.c_str());
							//ImGui::PopTextWrapPos();
							//ImGui::EndTooltip();
						}
					}
				}
#endif
			}
		}
	}

	//--------------------------------------------------------------
	inline void AddMouseWheel(bool& p) // toggle boolean state with mouse wheel
	{
		ImGui::SetItemKeyOwner(ImGuiKey_MouseWheelY);

		if (ImGui::IsItemHovered())
		{
			float wheel = ImGui::GetIO().MouseWheel;

			if (wheel)
			{
				if (ImGui::IsItemActive())
				{
					ImGui::ClearActiveID();
				}
				else
				{
					// Bool
					//flip
					p = !p;
				}
			}
		}
	}

	// Put after populate a widget!
	//--------------------------------------------------------------
	template <typename ParameterType>
	inline void AddMouse(ofParameter<ParameterType>& ap, bool bFlip = false)
	{
		ofxImGuiSurfing::AddMouseWheel(ap);

		// No bool
		if (typeid(ParameterType) != typeid(bool))
		{
			//ofxImGuiSurfing::AddMouseClickRightReset(ap);
		}
	}

	//--

	// Modified Clicks

	//--------------------------------------------------------------

	//TODO:
	//inline bool GetMouseDoubleClick()

	inline bool GetMouseClickRightAlt()
	{
		bool bModifier = ImGui::GetIO().KeyAlt;
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right) && bModifier)
		{
			return true;
		}
		return false;
	}

	inline bool GetMouseClickRightCtrl()
	{
		bool bModifier = ImGui::GetIO().KeyCtrl;
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right) && bModifier)
		{
			return true;
		}
		return false;
	}

	inline bool GetMouseClickRight()
	{
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		{
			return true;
		}
		return false;
	}

	//--

	// Reset params when Alt+Click called

	template <typename ParameterType>
	inline bool AddMouseClickRightReset(ofParameter<ParameterType>& ap, bool bToMinByDefault = false)
	{
		// Behavior:
		// right click : resets to center by default
		// ctrl+ : to min
		// alt+ : to max

		//TODO: should remove and DEPRECATE ?
		// bToMinByDefault : true 
		// to use min as default (when no mods) instead of the center value!

		bool bRightClick = GetMouseClickRight();
		if (!bRightClick) return false;

		//--

		// Right clicked

		bool bModCtrl = ImGui::IsKeyDown(ImGuiKey_ModCtrl);
		bool bModAlt = ImGui::IsKeyDown(ImGuiKey_ModAlt);

		bool bChanged = false;

		// param type
		bool bIsUnknown = false;
		bool bIsInt = false;
		bool bIsFloat = false;
		bool bIsMultiDim = false;
		bool bIsDim2 = false;
		bool bIsDim3 = false;
		bool bIsDim4 = false;

		const auto& info = typeid(ParameterType);

		if (0)
		{
		}

		else if (info == typeid(float)) // Float
		{
			bIsFloat = true;
		}
		else if (info == typeid(int)) // Int
		{
			bIsInt = true;
		}

		else if (info == typeid(ofDefaultVec2))
		{
			bIsMultiDim = true;
			bIsDim2 = true;
		}
		else if (info == typeid(ofDefaultVec3))
		{
			bIsMultiDim = true;
			bIsDim3 = true;
		}
		else if (info == typeid(ofDefaultVec4))
		{
			bIsMultiDim = true;
			bIsDim4 = true;
		}

		// Unknown Types
		else
		{
			bIsUnknown = true;
			ofLogWarning("ofxSurfingImGui") << "AddMouseClickRightReset : Could not add mouse wheel to " << ap.
				getName();

			return false;
		}

		//--

		if (0)
		{
		}

		//--

		//TODO:
		// Must be fixed bc each dim slider 
		// could work independently 
		// with the mouse extra controls...

		// Multidim

		else if (bIsMultiDim)
		{
			if (bIsDim2)
			{
				// non dynamic causes exception in macOS
				// example: ofParameter<bool> p = dynamic_cast<ofParameter<bool>&>(ap);
				ofParameter<glm::vec2> p = dynamic_cast<glm::vec2&>(ap);
				//ofParameter<glm::vec2> p = ap.cast<glm::vec2>();
				glm::vec2 _p = p;

				float centerX = p.getMin().x + ((p.getMax().x - p.getMin().x) / 2.f);
				_p.x = ofClamp(centerX, p.getMin().x, p.getMax().x); // clamp
				float centerY = p.getMin().y + ((p.getMax().y - p.getMin().y) / 2.f);
				_p.y = ofClamp(centerY, p.getMin().y, p.getMax().y); // clamp

				if ((!bModCtrl && !bModAlt) && bToMinByDefault) p.set(p.getMin());
				else if (bModCtrl) p.set(p.getMin());
				else if (bModAlt) p.set(p.getMax());
				else p.set(_p);

				bChanged = true;
			}
			else if (bIsDim3)
			{
				//ofParameter<glm::vec3> p = ap.cast<glm::vec3>();
				ofParameter<glm::vec3> p = dynamic_cast<glm::vec3&>(ap);
				glm::vec3 _p = p;

				float centerX = p.getMin().x + ((p.getMax().x - p.getMin().x) / 2.f);
				_p.x = ofClamp(centerX, p.getMin().x, p.getMax().x); // clamp
				float centerY = p.getMin().y + ((p.getMax().y - p.getMin().y) / 2.f);
				_p.y = ofClamp(centerY, p.getMin().y, p.getMax().y); // clamp
				float centerZ = p.getMin().z + ((p.getMax().z - p.getMin().z) / 2.f);
				_p.z = ofClamp(centerZ, p.getMin().z, p.getMax().z); // clamp

				if ((!bModCtrl && !bModAlt) && bToMinByDefault) p.set(p.getMin());
				else if (bModCtrl) p.set(p.getMin());
				else if (bModAlt) p.set(p.getMax());
				else p.set(_p);

				bChanged = true;
			}
			else if (bIsDim4)
			{
				//ofParameter<glm::vec4> p = ap.cast<glm::vec4>();
				ofParameter<glm::vec4> p = dynamic_cast<glm::vec4&>(ap);
				glm::vec4 _p = p;

				float centerX = p.getMin().x + ((p.getMax().x - p.getMin().x) / 2.f);
				_p.x = ofClamp(centerX, p.getMin().x, p.getMax().x); // clamp
				float centerY = p.getMin().y + ((p.getMax().y - p.getMin().y) / 2.f);
				_p.y = ofClamp(centerY, p.getMin().y, p.getMax().y); // clamp
				float centerZ = p.getMin().z + ((p.getMax().z - p.getMin().z) / 2.f);
				_p.z = ofClamp(centerZ, p.getMin().z, p.getMax().z); // clamp
				float centerW = p.getMin().w + ((p.getMax().w - p.getMin().w) / 2.f);
				_p.w = ofClamp(centerW, p.getMin().w, p.getMax().w); // clamp

				if ((!bModCtrl && !bModAlt) && bToMinByDefault) p.set(p.getMin());
				else if (bModCtrl) p.set(p.getMin());
				else if (bModAlt) p.set(p.getMax());
				else p.set(_p);

				bChanged = true;
			}
		}

		//--

		// Int

		else if (bIsInt)
		{
			ofParameter<int> p = dynamic_cast<ofParameter<int>&>(ap);

			if ((!bModCtrl && !bModAlt) && bToMinByDefault) p.set(p.getMin());
			else if (bModCtrl) p.set(p.getMin());
			else if (bModAlt) p.set(p.getMax());
			else
			{
				int center = p.getMin() + ((p.getMax() - p.getMin()) / 2.f);
				p = (int)ofClamp(center, p.getMin(), p.getMax()); // clamp
			}

			bChanged = true;
		}

		//--

		// Float

		else if (bIsFloat)
		{
			ofParameter<float> p = dynamic_cast<ofParameter<float>&>(ap);

			if ((!bModCtrl && !bModAlt) && bToMinByDefault) p.set(p.getMin());
			else if (bModCtrl) p.set(p.getMin());
			else if (bModAlt) p.set(p.getMax());
			else
			{
				float center = p.getMin() + ((p.getMax() - p.getMin()) / 2.f);
				p = ofClamp(center, p.getMin(), p.getMax()); // clamp
			}

			bChanged = true;
		}

		return bChanged;
	}

	//--

	//--------------------------------------------------------------
	inline void AddTooltip(std::string text, bool bEnabled = true)
	{
		if (!bEnabled || text.size() == 0) return;

		//TODO:
		// delayed. not work ?
		//if (IsItemHovered() && GImGui->HoveredIdTimer > 1000) 
		//if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 500)

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextWrapped("%s", text.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//--------------------------------------------------------------
	inline void AddTooltipBlink(std::string text, bool bBlink = true, bool bEnabled = true)
	{
		if (!bEnabled || text.size() == 0) return;

		if (bBlink)BeginBlinkText();
		AddTooltip(text);
		if (bBlink) EndBlinkText();
	}

	//--

	// Pass the param and will auto populate a tooltip with the param name and value.
	//--------------------------------------------------------------
	template <typename ParameterType>
	void AddTooltip(ofParameter<ParameterType>& ap, bool bEnabled = true, bool bNoName = false)
	{
		bool bReturn = false;
		string name = ap.getName();
		auto tmpRef = ap.get();

		const auto& t = typeid(ParameterType);
		bool isFloat = (t == typeid(float));
		bool isInt = (t == typeid(int));
		bool isBool = (t == typeid(bool));
		bool isVoid = (t == typeid(void));

		if (!isFloat && !isInt && !isBool && !isVoid)
		{
			ofLogWarning("ofxSurfingImGui")
				<< "Tooltip: ofParam type named " + name + " is not a Float, Int or Bool";
		}

		string s = "";
		if (!bNoName) s += ap.getName() + "\n";
		if (isFloat) s += ofToString(ap.get(), 3); //improve format
		else if (isInt) s += ofToString(ap.get());
		else if (isBool) s += ofToString((ap.get() ? "TRUE" : "FALSE"));

		AddTooltip(s);
	}

	// //--------------------------------------------------------------
	// void AddTooltip(ofParameter<int>& pindex, std::vector<std::string> fileNames)
	// {
	//     string s = "";
	//     if (pindex.get() < fileNames.size())
	//     {
	//         s = fileNames[pindex.get()];
	//     }
	//     AddTooltip(s);
	// }

	//--

	//TODO:
	// Pinned Tooltip Window
	// 
	// Moving is locked. must be controlled by higher level.
	// Return window dimensions so higher level can handle click / moving window 
	// Taken from:
	// https://github.com/ocornut/imgui/issues/1345
	// https://github.com/mikesart/gpuvis/blob/108d9c358a5f92cae5f79918025b9215a1771628/src/gpuvis_utils.cpp#L790
	// 
	// Example:
	// string str = "wertwertwert";
	// ofRectangle rc{ 100, 100, 100, 100 };
	// AddTooltipPinned("Pinned Tooltip", ImVec2{ 200, 200 }, &rc, str.c_str());
	//--------------------------------------------------------------
	inline void AddTooltipPinned(const char* name, const ImVec2& pos, ofRectangle* prc, const char* str)
	{
		if (str && str[0])
		{
			ImGuiIO& io = ImGui::GetIO();
			const ImVec2 mousepos_orig = io.MousePos;
			ImGuiWindowFlags flags =
				ImGuiWindowFlags_Tooltip |
				ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_AlwaysAutoResize;

			io.MousePos = pos;

			auto x = prc->x;
			auto y = prc->y;
			SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);

			ImGui::Begin(name, NULL, flags);

			//if (name[0] != '#')
			//{
			//	//imgui_text_bg(ImGui::GetStyleColorVec4(ImGuiCol_Header), "%s%s%s",
			//	//	s_textclrs().str(TClr_Bright), name, s_textclrs().str(TClr_Def));
			//}

			ImGui::Text("%s", str);

			if (prc)
			{
				prc->x = ImGui::GetWindowPos().x;
				prc->y = ImGui::GetWindowPos().y;
				prc->width = ImGui::GetWindowSize().x;
				prc->height = ImGui::GetWindowSize().y;
			}

			ImGui::End();

			io.MousePos = mousepos_orig;
		}
	}

	//----------------------

	// ofParameter's Helpers

	void AddGroup(ofParameterGroup& g, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen);

#if OF_VERSION_MINOR >= 10
	bool AddParameter(ofParameter<glm::ivec2>& p, bool bFoldered = false);
	bool AddParameter(ofParameter<glm::ivec3>& p, bool bFoldered = false);
	bool AddParameter(ofParameter<glm::ivec4>& p, bool bFoldered = false);

	//TODO:
	bool AddParameter(ofParameter<glm::vec2>& p, bool bSplit = false, bool bFoldered = false);
	// split each arg to big sliders. make a folder container.
	bool AddParameter(ofParameter<glm::vec3>& p, bool bSplit = false, bool bFoldered = false);
	// split each arg to big sliders. make a folder container.
	bool AddParameter(ofParameter<glm::vec4>& p, bool bSplit = false, bool bFoldered = false);
	// split each arg to big sliders. make a folder container.
	bool AddParameter(ofParameter<glm::quat>& p, bool bSplit = false, bool bFoldered = false);
#endif

	//TODO:
	bool AddParameter(ofParameter<ofVec2f>& p);
	bool AddParameter(ofParameter<ofVec3f>& p);
	bool AddParameter(ofParameter<ofVec4f>& p);

	bool AddParameter(ofParameter<ofColor>& p, bool alpha = true);
	bool AddParameter(ofParameter<ofFloatColor>& p, bool alpha = true);

	//TODO:
	bool AddParameter(ofParameter<ofColor>& p, bool alpha, ImGuiColorEditFlags flags);
	bool AddParameter(ofParameter<ofFloatColor>& p, bool alpha, ImGuiColorEditFlags flags);

	bool AddParameter(ofParameter<ofRectangle>& p);

	bool AddParameter(ofParameter<std::string>& p, size_t maxChars = 255, bool multiline = false);

	bool AddParameter(ofParameter<void>& p, float width = 0);

	template <typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& p, std::string format = "%.3f");

	//--

	template <typename ParameterType>
	bool AddText(ofParameter<ParameterType>& p, bool label = true);

	bool AddRadio(ofParameter<int>& p, std::vector<std::string> labels, int columns = 1);

	//bool AddCombo(ofParameter<int>& p, std::vector<std::string> labels, bool bRaw = false);

	//--

	bool AddSlider(ofParameter<float>& p, const char* format = "%.3f", float power = 1.0f);

	bool AddRange(const std::string& name, ofParameter<int>& pMin, ofParameter<int>& pMax, int speed = 1);
	bool AddRange(const std::string& name, ofParameter<float>& pMin, ofParameter<float>& pMax, float speed = 0.01f);

#if OF_VERSION_MINOR >= 10
	bool AddRange(const std::string& name, ofParameter<glm::vec2>& pMin, ofParameter<glm::vec2>& pMax,
		float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec3>& pMin, ofParameter<glm::vec3>& pMax,
		float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec4>& pMin, ofParameter<glm::vec4>& pMax,
		float speed = 0.01f);
#endif

#if OF_VERSION_MINOR >= 10
	bool AddValues(const std::string& name, std::vector<glm::ivec2>& values, int minValue = 0, int maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::ivec3>& values, int minValue = 0, int maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::ivec4>& values, int minValue = 0, int maxValue = 0);

	bool AddValues(const std::string& name, std::vector<glm::vec2>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::vec3>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<glm::vec4>& values, float minValue = 0, float maxValue = 0);
#endif

	bool AddValues(const std::string& name, std::vector<ofVec2f>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<ofVec3f>& values, float minValue = 0, float maxValue = 0);
	bool AddValues(const std::string& name, std::vector<ofVec4f>& values, float minValue = 0, float maxValue = 0);

	template <typename DataType>
	bool AddValues(const std::string& name, std::vector<DataType>& values, DataType minValue, DataType maxValue);

	void AddImage(const ofBaseHasTexture& hasTexture, const ofVec2f& size);
	void AddImage(const ofTexture& texture, const ofVec2f& size);

#if OF_VERSION_MINOR >= 10
	void AddImage(const ofBaseHasTexture& hasTexture, const glm::vec2& size);
	void AddImage(const ofTexture& texture, const glm::vec2& size);
#endif

	//----

	// Stepper widgets
	// (with +/- buttons to increment/decrement)
	// To be used to not draw the label. 
	// Useful to use on combo of widgets 
	// to populate one single variable!
	//--------------------------------------------------------------
	template <typename ParameterType>
	bool AddStepper(ofParameter<ParameterType>& p, bool bNoLabel = false, bool bRaw = true)
	{
		bool bReturn = false;
		string name = p.getName();
		auto tmpRef = p.get();

		const auto& t = typeid(ParameterType);
		bool isFloat = (t == typeid(float));
		bool isInt = (t == typeid(int));

		if (!isFloat && !isInt)
		{
			ofLogWarning("ofxSurfingImGui") << "Stepper: ofParam type named " + name + " is not a Float or an Int";
			return false;
		}

		// Int
		const ImU32 stepInt = 1;
		static bool inputs_step = true;

		//TODO: added above relative/absolute workflow

		// Float
		float step, stepFast;
#if 0
		float res;
		//step related to param range min/max
		res = 1000.f;
		//res = 10000.f;
		//res = 100.f;
		step = (p.getMax() - p.getMin()) / res;
		stepFast = 100.f * step;
#else
		//TODO:
		step = 0.001f;
		stepFast = 0.01f;
#endif
		string n = "##STEPPER" + name;
		string label = ofToString(bNoLabel ? "" : name);

		ImGui::PushID(n.c_str());

		if (!bRaw)
		{
			if (bNoLabel) ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
			else IMGUI_SUGAR__STEPPER_WIDTH_PUSH;
		}

		if (isFloat)
		{
			if (ImGui::InputFloat(label.c_str(), (float*)&tmpRef, step, stepFast))
			{
				tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax()); //clamp
				p.set(tmpRef);
				bReturn = true;
			}
		}
		else if (isInt)
		{
			if (ImGui::InputScalar(label.c_str(), ImGuiDataType_S32, (int*)&tmpRef, inputs_step ? &stepInt : NULL, NULL,
				"%d"))
			{
				tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax());
				p.set(tmpRef);
				bReturn = true;
			}
		}
		else
		{
			ofLogWarning("ofxSurfingImGui") << "Stepper: Unknown type for " + name + " param";
		}

		if (!bRaw)
		{
			if (bNoLabel) ImGui::PopItemWidth();
			else IMGUI_SUGAR__STEPPER_WIDTH_POP;
		}

		ImGui::PopID();

		return bReturn;
	}

	//--------------------------------------------------------------
	template <typename ParameterType>
	bool AddStepperButtons(ofParameter<ParameterType>& p)
	{
		bool bReturn = false;
		string name = p.getName();
		auto tmpRef = p.get();

		const auto& t = typeid(ParameterType);
		bool isFloat = (t == typeid(float));
		bool isInt = (t == typeid(int));

		float spx = 2;

		// Int
		const ImU32 u32_one = 1;
		//static bool inputs_step = true;

		// Float
		float res = 1000.f;
		//float res = 100.f;
		float step = (p.getMax() - p.getMin()) / res;
		//float stepFast = 100.f * step;

		string n = "##STEPPERBUTTONS" + name;

		ImGui::PushID(n.c_str());

		if (isFloat)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spx, 0));
			if (ImGui::Button("-"))
			{
				tmpRef -= step;
				tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax()); //clamp
				p.set(tmpRef);
				bReturn = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("+"))
			{
				tmpRef += step;
				tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax()); //clamp
				p.set(tmpRef);
				bReturn = true;
			}
			ImGui::PopStyleVar();
		}
		else if (isInt)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spx, 0));
			if (ImGui::Button("-"))
			{
				tmpRef -= u32_one;
				tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax()); //clamp
				p.set(tmpRef);
				bReturn = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("+"))
			{
				tmpRef += u32_one;
				tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax()); //clamp
				p.set(tmpRef);
				bReturn = true;
			}
			ImGui::PopStyleVar();
		}
		else
		{
			ofLogWarning("ofxSurfingImGui") << "StepperButtons: Unknown type for " + name + " param";
		}

		ImGui::PopID();

		return bReturn;
	}

	//----

	// These are mainly the original ofxImGui methods:
	// Clean of my API stuff / styles,
	// and with the default styles.
	//--------------------------------------------------------------
	template <typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& p, std::string format)
	{
		auto tmpRef = p.get();
		const auto& info = typeid(ParameterType);

		//--

		// Float

		if (info == typeid(float))
		{
			IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
			if (ImGui::SliderFloat((p.getName().c_str()), (float*)&tmpRef, p.getMin(), p.getMax(), format.c_str()))
			{
				p.set(tmpRef);
				IMGUI_SUGAR__WIDGETS_POP_WIDTH;
				return true;
			}
			IMGUI_SUGAR__WIDGETS_POP_WIDTH;
			return false;
		}

		//--

		// Int

		else if (info == typeid(int))
		{
			IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
			if (ImGui::SliderInt((p.getName().c_str()), (int*)&tmpRef, p.getMin(), p.getMax()))
			{
				p.set(tmpRef);

				IMGUI_SUGAR__WIDGETS_POP_WIDTH;
				return true;
			}

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;
			return false;
		}

		//--

		// Bool

		else if (info == typeid(bool))
		{
			if (ImGui::Checkbox((p.getName().c_str()), (bool*)&tmpRef))
			{
				p.set(tmpRef);
				return true;
			}

			return false;
		}

		//--

		// Unknown

		if (info.name() == "" || info.name() == " ")
			ofLogWarning("ofxSurfingImGui") << "Could not create GUI element for type " << info.name();

		return false;
	}

	//--

	//--------------------------------------------------------------
	template <typename ParameterType>
	bool AddText(ofParameter<ParameterType>& p, bool label)
	{
		if (label)
		{
			ImGui::LabelText((p.getName().c_str()), ofToString(p.get()).c_str());
		}
		else
		{
			ImGui::Text(ofToString(p.get()).c_str());
		}

		return true;
	}

	//--------------------------------------------------------------
	inline void AddTextBoxWindow(string nameWindow, string text, bool bNoHeader = true)
	{
		nameWindow = ofToUpper(nameWindow);
		const char* name = nameWindow.c_str();
		const char* str = text.c_str();

		if (str && str[0])
		{
			ImGuiWindowFlags flags = ImGuiWindowFlags_None;
			flags += ImGuiWindowFlags_AlwaysAutoResize;
			//flags += ImGuiWindowFlags_NoResize;
			//flags += ImGuiWindowFlags_Tooltip;
			//flags += ImGuiWindowFlags_NoTitleBar;
			//flags += ImGuiWindowFlags_NoMove;
			//flags += ImGuiWindowFlags_NoSavedSettings;

			//if (bNoHeader) flags += ImGuiWindowFlags_NoDecoration;
			if (bNoHeader) flags += ImGuiWindowFlags_NoTitleBar;

			ImGui::Begin(name, NULL, flags);

			//TODO:
			// Should be bigger font..
			ImGui::Text("%s", name);
			ImGui::Spacing();

			ImGui::Text("%s", str);

			ImGui::End();
		}
	}

	//--

	//--------------------------------------------------------------
	template <typename DataType>
	bool AddValues(const std::string& name, std::vector<DataType>& values, DataType minValue, DataType maxValue)
	{
		auto result = false;
		const auto& info = typeid(DataType);
		IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;

		for (int i = 0; i < values.size(); ++i)
		{
			const auto iname = name + " " + ofToString(i);
			if (info == typeid(float))
			{
				result |= ImGui::SliderFloat(GetUniqueName2(iname), *values[i], minValue, maxValue);
			}
			else if (info == typeid(int))
			{
				result |= ImGui::SliderInt(GetUniqueName2(iname), *values[i], minValue, maxValue);
			}
			else if (info == typeid(bool))
			{
				result |= ImGui::Checkbox(GetUniqueName2(iname), *values[i]);
			}
			else
			{
				if (info.name() == "" || info.name() == " ")
					ofLogWarning("ofxSurfingImGui") <<
					"Could not create GUI element for type " << info.name();

				IMGUI_SUGAR__WIDGETS_POP_WIDTH;

				return false;
			}
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return result;
	}

	//----


	// Image and Textures helpers
	// copied from ofxImgui / ImHelpers.h
	//--------------------------------------------------------------
	static ImTextureID GetImTextureID2(const ofTexture& texture)
	{
		return (ImTextureID)(uintptr_t)texture.texData.textureID;
	}

	//--------------------------------------------------------------
	static ImTextureID GetImTextureID2(const ofBaseHasTexture& hasTexture)
	{
		return GetImTextureID2(hasTexture.getTexture());
	}

	//--------------------------------------------------------------
	static ImTextureID GetImTextureID2(GLuint glID)
	{
		return (ImTextureID)(uintptr_t)glID;
	}

	//----

	//TODO:
	//public://added inline 
	static bool bMouseWheel = true; //this was originally an internal from ui

	// Helpers to populate non ofParams,
	// Raw CPP types instead an maintain global styles.
	// To speed up populate widgets without requiring to create ofParameters first.

	//--------------------------------------------------------------
	inline bool AddButton(string label, ImVec2 sz)
	{
		bool bReturn = false;

		float _ww = sz.x;
		float _h = sz.y;

		bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h);

		return bReturn;
	}

	//--------------------------------------------------------------
	inline bool AddButton(string label, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1,
		bool bSameLine = false, int spacing = -1)
	{
		//fixes

		//--

		bool bReturn = false;

		float _h = getWidgetsHeightUnit();

		// widget width
		// we get the sizes from the canvas layout!
		//float _ww = _ui.getWidgetWidthOnRowPerAmount(amtPerRow);//TODO: BUG:
		//TODO: BUG: here we don't have access to manager!
		float _ww = ofxImGuiSurfing::getWidgetsWidth(amtPerRow); //fix

		switch (type)
		{
		case OFX_IM_DEFAULT:
		case OFX_IM_BUTTON_SMALL:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.25f);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.5f);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 2);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 3);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 4);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

			//--

			// Adding more styles

			// Border 

		case OFX_IM_BUTTON_SMALL_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.25f, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.5f, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 2, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 3, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL_BORDER:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 4, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

			//--

			// Border Blink

		case OFX_IM_BUTTON_SMALL_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h, true, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.25f, true, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 1.5f, true, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 2, true, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 3, true, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL_BORDER_BLINK:
			bReturn = ofxImGuiSurfing::AddBigButton(label, _ww, _h * 4, true, true);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		default:
		{
			ofLogWarning(__FUNCTION__) << "Could not create passed style for that widget button!";
			ofLogWarning(__FUNCTION__) << "Widget is ignored and not drawn!";
			break;
		}
		}

		//----

		// Extra options
		// - Same line flag.
		// - Final y spacing.

		if (bSameLine) ImGui::SameLine();
		if (spacing != -1 && spacing != 0)
		{
			ImGui::Dummy(ImVec2(0.0f, (float)spacing)); // spacing
		}

		return bReturn;
	}

	//--

	// Toggle

	// Helpers to populate non ofParams,
	// Raw CPP types instead an maintain global styles.
	// To speed up populate widgets without requiring to create ofParameters first.
	// A toggle passing a name and a boolean to show and get the boolean state.
	//--------------------------------------------------------------
	inline bool AddToggle(string label, bool& bState, ImVec2 sz)
	{
		bool bReturn = false;

		float _ww = sz.x;
		float _h = sz.y;

		bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h);
		if (bMouseWheel) ofxImGuiSurfing::AddMouseWheel(bState);

		return bReturn;
	}

	////--------------------------------------------------------------
	//bool AddToggle(string label, bool& bState)
	//{
	//	int w = ofxImGuiSurfing::getWidgetsWidth(1);
	//	int h = ofxImGuiSurfing::getWidgetsHeightUnit();
	//	ImVec2 sz(w, h);
	//	bool bReturn = false;
	//	float _ww = sz.x;
	//	float _h = sz.y;
	//	bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h);
	//	return bReturn;
	//}

	//--------------------------------------------------------------
	inline bool AddToggle(string label, bool& bState, SurfingGuiTypes type = OFX_IM_DEFAULT, int amtPerRow = 1,
		bool bSameLine = false, int spacing = -1)
	{
		bool bReturn = false;

		// Widget width
		// We get the sizes from the canvas layout!
		float _ww = ofxImGuiSurfing::getWidgetsWidth(amtPerRow); //fix
		//float _ww = _ui.getWidgetWidthOnRowPerAmount(amtPerRow);
		float _h = getWidgetsHeightUnit();

		switch (type)
		{
		case OFX_IM_DEFAULT:
		case OFX_IM_BUTTON_SMALL:
		case OFX_IM_TOGGLE_SMALL:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON:
		case OFX_IM_TOGGLE:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 1.25f);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_MEDIUM:
		case OFX_IM_TOGGLE_MEDIUM:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 1.5f);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG:
		case OFX_IM_TOGGLE_BIG:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 2);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXL:
		case OFX_IM_TOGGLE_BIG_XXL:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 3);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_BUTTON_BIG_XXXL:
		case OFX_IM_TOGGLE_BIG_XXXL:
			bReturn = ofxImGuiSurfing::AddBigToggle(label, bState, _ww, _h * 4);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

			//--

			// Rounded Toggles

		case OFX_IM_TOGGLE_ROUNDED_MINI:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState,
				ImVec2(1.15f * _h, 1.15f * (2 / 3.f) * _h));
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_TOGGLE_ROUNDED_SMALL:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState,
				ImVec2(1.35f * _h, 1.35f * (2 / 3.f) * _h));
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_TOGGLE_ROUNDED:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState);
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_TOGGLE_ROUNDED_MEDIUM:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState, ImVec2(2 * _h, 2 * (2 / 3.f) * _h));
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

		case OFX_IM_TOGGLE_ROUNDED_BIG:
		case OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG: // LEGACY
			bReturn = ofxImGuiSurfing::AddToggleRoundedButton(label, bState, ImVec2(2.5f * _h, 2.5f * (2 / 3.f) * _h));
			if (bMouseWheel) AddMouseWheel(bState);
			if (bMouseWheel) bReturn |= GetMouseWheel();
			break;

			//--

		default:
			ofLogWarning("ofxSurfingImGui") << (__FUNCTION__);
			ofLogWarning("ofxSurfingImGui") << "Could not create passed style for that Toggle widget!";
			break;
		}

		//----

		// Extra options
		// - Same line flag.
		// - Final y spacing.

		if (bSameLine) ImGui::SameLine();
		if (spacing != -1 && spacing != 0)
		{
			ImGui::Dummy(ImVec2(0.0f, (float)spacing)); // spacing
		}

		return bReturn;
	}

	//----

	//--------------------------------------------------------------
	inline bool MenuItemToggle(ofParameter<bool>& pb, bool enabled = true)
	{
		string label = pb.getName();
		bool selected = pb.get();
		const char* shortcut = NULL;
		bool b = ImGui::MenuItem(label.c_str(), shortcut, selected, enabled);
		if (b) pb = !pb;

		return b;
	}
} // namespace ofxImGuiSurfing


#if 0
	/*
	// The Animations namespace contains everything you need to easily create animations in your ImGui menus.
	*/
namespace Animations {

	/*
	// Usage:
	// int trickInt = ImTricks::Animations::FastLerpInt("trickInt", enable_animation, 0, 255, 15);
	// draw->AddRectFilled(p, p + ImVec2(30, 30), ImColor(255, 255, 255, trickInt));
	*/
	extern int FastLerpInt(const char* identifier, bool state, int min, int max, int speed);

	/*
	// Usage:
	// float trickFloat = ImTricks::Animations::FastLerpInt("trickFloat", enable_animation, 0.f, 1.f, 0.05f);
	// draw->AddRectFilled(p, p + ImVec2(30, 30), ImColor(1.f, 1.f, 1.f, trickFloat));
	*/
	extern float FastLerpFloat(const char* identifier, bool state, float min, float max, float speed);

	/*
	// Usage:
	//	float trickFloat = ImTricks::Animations::FastLerpFloat("header", check, 0.f, 1.f, 0.05f);
	//	draw->AddRectFilled(p, p + ImVec2(513, 30), ImTricks::Animations::FastColorLerp(ImColor(255, 0, 0), ImColor(0, 255, 0), trickFloat));
	*/
	extern ImColor FastColorLerp(ImColor start, ImColor end, float stage);
}

namespace Animations {

	int FastLerpInt(const char* identifier, bool state, int min, int max, int speed) {

		static std::map<const char*, int> valuesMapInt;
		auto value = valuesMapInt.find(identifier);

		if (value == valuesMapInt.end()) {
			valuesMapInt.insert({ identifier,  0 });
			value = valuesMapInt.find(identifier);
		}

		const float frameRateSpeed = speed * (1.f - ImGui::GetIO().DeltaTime);

		if (state) {
			if (value->second < max)
				value->second += frameRateSpeed;
		}
		else {
			if (value->second > min)
				value->second -= frameRateSpeed;
		}

		value->second = std::clamp(value->second, min, max);

		return value->second;
	}

	float FastLerpFloat(const char* identifier, bool state, float min, float max, float speed) {

		static std::map<const char*, float> valuesMapFloat;
		auto value = valuesMapFloat.find(identifier);

		if (value == valuesMapFloat.end()) {
			valuesMapFloat.insert({ identifier, 0.f });
			value = valuesMapFloat.find(identifier);
		}

		const float frameRateSpeed = speed * (1.f - ImGui::GetIO().DeltaTime);

		if (state) {
			if (value->second < max)
				value->second += frameRateSpeed;
		}
		else {
			if (value->second > min)
				value->second -= frameRateSpeed;
		}

		value->second = std::clamp(value->second, min, max);

		return value->second;
	}

	ImColor FastColorLerp(ImColor start, ImColor end, float stage)
	{
		ImVec4 lerp = ImLerp(
			ImVec4(start.Value.x, start.Value.y, start.Value.z, start.Value.w),
			ImVec4(end.Value.x, end.Value.y, end.Value.z, end.Value.w),
			stage);

		return ImGui::ColorConvertFloat4ToU32(lerp);
	}
}
#endif


/*
namespace ofxImGuiSurfing
{
	void ColorEdit3(const char* label, ImColor& color, ImGuiColorEditFlags flags) {
		static float col[3] = { color.Value.x, color.Value.y, color.Value.z };

		if (ImGui::ColorEdit3(label, col, flags))
			color = ImColor(col[0], col[1], col[2]);
	}

	void ColorEdit4(const char* label, ImColor& color, ImGuiColorEditFlags flags) {
		static float col[4] = { color.Value.x, color.Value.y, color.Value.z , color.Value.w };

		if (ImGui::ColorEdit4(label, col, flags))
			color = ImColor(col[0], col[1], col[2], col[3]);
	}
}
*/
