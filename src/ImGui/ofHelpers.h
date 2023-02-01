
#pragma once

/*

	ofParameter Helpers
	to easily render different widgets styles
	for each ofParm and different types.
*/

/*
	TODO:

	fix mouse wheel for multi dim params

	Add customization for nested groups
	pass some list of arguments
	to customize items/groups
	to be rendered with different styles:
	https://github.com/Daandelange/ofxImGui/issues/6#issuecomment-832174921

*/

//----

#include "ofxImGui.h"
#include "Widgets.h"
#include "GuiConstants.h"

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
		ImGui::SetItemUsingMouseWheel();
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

	// Adds mouse wheel control to the last previous param widget (templated float/int)
	//--------------------------------------------------------------
	template<typename ParameterType>
	inline void AddMouseWheel(ofParameter<ParameterType>& ap, bool bFlip = false)
	{
		//TODO: 
		// Workaround
		// Allow customization
		// Forced to default behavior/resolution stepping.
		float resolution = -1;

		bool bIsUnknown = false;
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
		else if (info == typeid(bool)) // Bool
		{
			bIsbool = true;
		}
		else if (info == typeid(void)) // Void
		{
			bIsVoid = true;
		}

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

		// Unknown Types
		else
		{
			bIsUnknown = true;
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
				if (bIsbool) sTooltip = dynamic_cast<ofParameter<bool>&>(ap).get() ? "TRUE" : "FALSE";
				else if (bIsInt) sTooltip = ofToString(dynamic_cast<ofParameter<int>&>(ap).get());
				else if (bIsFloat) sTooltip = ofToString(dynamic_cast<ofParameter<float>&>(ap).get(), 2);
			}

			ImGui::SetItemUsingMouseWheel();

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

						//TODO:
						// Must be fixed bc each dim slider could work independently...

						// MULTIDIM

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

								if (_range < MOUSE_WHEEL_STEPS)
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
									// step resolution to guaranties that 100 steps walks the full range!
									float _resolution = _range / MOUSE_WHEEL_STEPS;
									resolution = MAX(1, _resolution);

									if (!bCtrl)
									{
										_step = resolution;
									}
									else
									{
										_step = resolution * MOUSE_WHEEL_FINETUNE_CTRL_RATIO;
									}
								}

								// MOUSE_WHEEL_STEPS is 100 or 1000 steps for all the param range
							}

							// Minimum step is one unit!
							_step = MAX(1, _step);

							//--

							int step = wheel * _step;

							// make minim one unit

							//if (step < 0) {
							//	step = MIN(-1, step);
							//}
							//else {
							//	step = MAX(1, step);
							//}

							//// negative
							//if (step < 0 && step > -1) step = MIN(- 1, step);
							//
							//// positive
							//else if (step > 0 && step < 1) MAX(1, step);

							// mouse wheel flipped
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
								// MOUSE_WHEEL_STEPS is 100 steps spread into all the param range
								resolution = (p.getMax() - p.getMin()) / MOUSE_WHEEL_STEPS;
							}

							float step = wheel * (!bCtrl ? resolution : resolution * (float)MOUSE_WHEEL_FINETUNE_CTRL_RATIO);

							if (bFlip) p -= step;
							else p += step;

							p = ofClamp(p, p.getMin(), p.getMax()); // clamp
						}
					}
				}

				if (bCtrl || bAlt)
				{
					if (sTooltip != "-1")
					{
						if (ImGui::IsItemHovered())
						{
							ImGui::BeginTooltip();
							//ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
							ImGui::Text(sTooltip.c_str());
							//ImGui::PopTextWrapPos();
							ImGui::EndTooltip();
						}
					}
				}
			}
		}
	}

	//--------------------------------------------------------------
	inline void AddMouseWheel(bool& p) // toggle boolean state with mouse wheel
	{
		ImGui::SetItemUsingMouseWheel();

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

	template<typename ParameterType>
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

		if (0) {}

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
			ofLogWarning("ofxSurfingImGui") << "AddMouseClickRightReset : Could not add mouse wheel to " << ap.getName();

			return false;
		}

		//--

		if (0) {}

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
				ofParameter<glm::vec2> p = ap.cast<glm::vec2>();
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
				ofParameter<glm::vec3> p = ap.cast<glm::vec3>();
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
				ofParameter<glm::vec4> p = ap.cast<glm::vec4>();
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
			else {
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
			else {
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
		if (!bEnabled) return;

		//TODO:
		// delayed. not work ?
		//if (IsItemHovered() && GImGui->HoveredIdTimer > 1000) 
		//if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 500)

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextWrapped(text.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//--

	// Pass the param and will auto populate a tooltip with the param name and value.
	//--------------------------------------------------------------
	template<typename ParameterType>
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
		if (isFloat) s += ofToString(ap.get(), 3);//improve format
		else if (isInt) s += ofToString(ap.get());
		else if (isBool) s += ofToString((ap.get() ? "TRUE" : "FALSE"));

		AddTooltip(s);
	}

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
	bool AddParameter(ofParameter<glm::ivec2>& p, bool bfoldered = false);
	bool AddParameter(ofParameter<glm::ivec3>& p, bool bfoldered = false);
	bool AddParameter(ofParameter<glm::ivec4>& p, bool bfoldered = false);

	//TODO:
	bool AddParameter(ofParameter<glm::vec2>& p, bool bsplit = false, bool bfoldered = false);
	// split each arg to big sliders. make a folder container.
	bool AddParameter(ofParameter<glm::vec3>& p, bool bsplit = false, bool bfoldered = false);
	// split each arg to big sliders. make a folder container.
	bool AddParameter(ofParameter<glm::vec4>& p, bool bsplit = false, bool bfoldered = false);
	// split each arg to big sliders. make a folder container.
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

	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& p, std::string format = "%.3f");

	//--

	template<typename ParameterType>
	bool AddText(ofParameter<ParameterType>& p, bool label = true);

	bool AddRadio(ofParameter<int>& p, std::vector<std::string> labels, int columns = 1);

	bool AddCombo(ofParameter<int>& p, std::vector<std::string> labels, bool bRaw = false);

	//--

	bool AddSlider(ofParameter<float>& p, const char* format = "%.3f", float power = 1.0f);

	bool AddRange(const std::string& name, ofParameter<int>& pMin, ofParameter<int>& pMax, int speed = 1);
	bool AddRange(const std::string& name, ofParameter<float>& pMin, ofParameter<float>& pMax, float speed = 0.01f);

#if OF_VERSION_MINOR >= 10
	bool AddRange(const std::string& name, ofParameter<glm::vec2>& pMin, ofParameter<glm::vec2>& pMax, float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec3>& pMin, ofParameter<glm::vec3>& pMax, float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec4>& pMin, ofParameter<glm::vec4>& pMax, float speed = 0.01f);
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

	template<typename DataType>
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

	//bool AddStepper(ofParameter<int>& p, int step = -1, int stepFast = -1);
	//bool AddStepper(ofParameter<float>& p, float step = -1, float stepFast = -1);

	//--------------------------------------------------------------
	inline bool AddStepperInt(ofParameter<int>& p)
	{
		bool bChanged = false;
		auto tmpRefi = p.get();
		const ImU32 u32_one = 1;
		static bool inputs_step = true;

		string name = p.getName();
		string n = "##STEPPERint" + name;// +ofToString(1);
		ImGui::PushID(n.c_str());

		IMGUI_SUGAR__STEPPER_WIDTH_PUSH;

		if (ImGui::InputScalar(p.getName().c_str(), ImGuiDataType_S32, (int*)&tmpRefi, inputs_step ? &u32_one : NULL, NULL, "%d"))
		{
			tmpRefi = ofClamp(tmpRefi, p.getMin(), p.getMax());
			p.set(tmpRefi);

			bChanged = true;
		}

		IMGUI_SUGAR__STEPPER_WIDTH_POP;

		ImGui::PopID();

		return bChanged;
	}

	//--------------------------------------------------------------
	inline bool AddStepperFloat(ofParameter<float>& p)
	{
		float res = 100.f;
		float step = (p.getMax() - p.getMin()) / res;
		float stepFast = 100.f * step;

		auto tmpRef = p.get();
		bool bReturn = false;

		string name = p.getName();
		string n = "##STEPPERfloat" + name;
		ImGui::PushID(n.c_str());

		IMGUI_SUGAR__STEPPER_WIDTH_PUSH_FLOAT;

		if (ImGui::InputFloat(p.getName().c_str(), (float*)&tmpRef, step, stepFast))
		{
			tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax());//clamp
			p.set(tmpRef);
			bReturn = true;
		}

		IMGUI_SUGAR__STEPPER_WIDTH_POP_FLOAT;

		ImGui::PopID();

		return bReturn;
	}

	//--

	// Stepper alternative
	// To be used to not draw the label. 
	// Useful to use on combo of widgets 
	// to populate one single variable!
	//--------------------------------------------------------------
	template<typename ParameterType>
	bool AddStepper(ofParameter<ParameterType>& p, bool bNoLabel = false)
	{
		bool bReturn = false;
		string name = p.getName();
		auto tmpRef = p.get();

		const auto& t = typeid(ParameterType);
		bool isFloat = (t == typeid(float));
		bool isInt = (t == typeid(int));
		if (!isFloat && !isInt) {
			ofLogWarning("ofxSurfingImGui") <<
				"Stepper: ofParam type named " + name + " is not a Float or an Int";
			return false;
		}

		// Int
		const ImU32 u32_one = 1;
		static bool inputs_step = true;

		// Float
		float res = 100.f;
		float step = (p.getMax() - p.getMin()) / res;
		float stepFast = 100.f * step;

		string n = "##STEPPER" + name;
		string label = ofToString(bNoLabel ? "" : name);

		ImGui::PushID(n.c_str());

		if (bNoLabel) ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
		else IMGUI_SUGAR__STEPPER_WIDTH_PUSH_FLOAT;

		if (isFloat)
			if (ImGui::InputFloat(label.c_str(), (float*)&tmpRef, step, stepFast))
			{
				tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax());//clamp
				p.set(tmpRef);
				bReturn = true;
			}
			else if (isInt)
				if (ImGui::InputScalar(label.c_str(), ImGuiDataType_S32,
					(int*)&tmpRef, inputs_step ? &u32_one : NULL, NULL, "%d"))
				{
					tmpRef = ofClamp(tmpRef, p.getMin(), p.getMax());
					p.set(tmpRef);
					bReturn = true;
				}

		if (bNoLabel) ImGui::PopItemWidth();
		else IMGUI_SUGAR__STEPPER_WIDTH_POP_FLOAT;

		ImGui::PopID();

		return bReturn;
	}

	//----

	// These are mainly the original ofxImGui methods:
	// Clean of my API stuff / styles,
	// and with the default styles.
	//--------------------------------------------------------------
	template<typename ParameterType>
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
	template<typename ParameterType>
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
	template<typename DataType>
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

	bool VectorCombo(const char* label, int* currIndex, std::vector<std::string>& values, bool bRaw = false);
	bool VectorListBox(const char* label, int* currIndex, std::vector<std::string>& values);

	//TODO:
	static bool VectorCombo2(ofParameter<int> pIndex, std::vector<std::string> fileNames, bool braw = false);

	//TODO:
	// Combo list. 
	// Selector index directly with an int ofParam
	// without name label
	//--------------------------------------------------------------
	static bool VectorCombo2(ofParameter<int> pIndex, std::vector<std::string> fileNames, bool braw)
	{
		if (fileNames.empty()) return false;

		string t = "##" + pIndex.getName();
		ImGui::PushID(t.c_str());

		int i = pIndex.get();
		bool b = (ofxImGuiSurfing::VectorCombo(" ", &i, fileNames));
		if (b) {
			i = ofClamp(i, pIndex.getMin(), pIndex.getMax());//avoid crashes
			pIndex.set(i);
			ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "Combo: " << pIndex.getName() << " " << ofToString(pIndex);
		}

		ImGui::Spacing();

		ImGui::PopID();

		return b;
	}

	//--

	//TODO: WIP:
	// Hard to be implemented here..
	// Must replace a bunch of GuiManager to move it here...
	// A bundle of controls
	// for a single param
	//--------------------------------------------------------------
	template<typename ParameterType>
	static bool AddComboBundle(ofParameter<ParameterType>& p, bool bMinimized = false)
	{
		string name = p.getName();

		bool bReturn = false;

		const auto& t = typeid(ParameterType);
		const bool isFloat = (t == typeid(float));
		const bool isInt = (t == typeid(int));

		if (!isFloat && !isInt) {
			ofLogWarning("ofxSurfingImGui") << "AddComboBundle: ofParam type named " + name + " is not a Float or Int";
			return false;
		}

		//TODO:
		//// Label
		//if (!bMinimized) this->AddLabelHuge(p.getName(), true, true);
		//else this->AddLabelBig(p.getName(), true, true);

		//// Stepper
		//bReturn += this->Add(p, OFX_IM_STEPPER_NO_LABEL);
		////bReturn += this->Add(p, bMinimized ? OFX_IM_STEPPER : OFX_IM_STEPPER_NO_LABEL);

		//// Slider
		//bReturn += this->Add(p, bMinimized ? OFX_IM_HSLIDER_MINI_NO_LABELS : OFX_IM_HSLIDER_SMALL_NO_LABELS);

		// Arrows
		ImGui::PushButtonRepeat(true); // -> pushing to repeat trigs
		{
			float step = 0;
			if (isInt) step = 1;
			else if (isFloat) step = (p.getMax() - p.getMin()) / 100.f;

			//if (this->AddButton("<", bMinimized ? OFX_IM_BUTTON_MEDIUM : OFX_IM_BUTTON_BIG, 2))
			//{
			//	p -= step;
			//	p = ofClamp(p, p.getMin(), p.getMax());
			//	bReturn += true;
			//}
			//ImGui::SameLine();
			//if (this->AddButton(">", bMinimized ? OFX_IM_BUTTON_MEDIUM : OFX_IM_BUTTON_BIG, 2))
			//{
			//	p += step;
			//	p = ofClamp(p, p.getMin(), p.getMax());
			//	bReturn += true;
			//}
		}
		ImGui::PopButtonRepeat();

		if (!bMinimized)
		{
			// Knob
			//this->Add(p, OFX_IM_KNOB_DOTKNOB);
			float w = this->getWidgetsWidth(1);
			ImGuiKnobFlags flags = 0;
			flags += ImGuiKnobFlags_NoInput;
			flags += ImGuiKnobFlags_NoTitle;
			flags += ImGuiKnobFlags_ValueTooltip;//not works
			//flags += ImGuiKnobFlags_DragHorizontal;
			bReturn += ofxImGuiSurfing::AddKnobStyled(p, OFX_IM_KNOB_DOTKNOB, w, OFX_IM_FORMAT_KNOBS, flags);

			//// mouse
			//if (this->bMouseWheel) {
			//	ofxImGuiSurfing::AddMouseWheel(p, this->bMouseWheelFlip.get());
			//	ofxImGuiSurfing::GetMouseWheel();
			//	ofxImGuiSurfing::AddMouseClickRightReset(p);
			//}

			// tooltip
			this->AddTooltip(p, true, false);
		}

		return bReturn;
	}

	//----
} // namespace ofxImGuiSurfing
