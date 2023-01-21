
#pragma once

/*

	ofParameter Helpers
	to easily render different widgets styles
	for each ofParm and different types.

	TODO:
	+ mouse wheel for multi dim params

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
	inline void AddMouseWheel(ofParameter<ParameterType>& param, bool bFlip = false)
	{
		//TODO: allow customization
		// Forced to default behavior/resolution stepping.
		float resolution = -1;

		bool bUnknown = false;
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

		if (info == typeid(float)) // FLOAT
		{
			bIsFloat = true;
		}
		else if (info == typeid(int)) // INT
		{
			bIsInt = true;
		}
		else if (info == typeid(bool)) // BOOL
		{
			bIsbool = true;
		}
		else if (info == typeid(void)) // VOID
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
			bUnknown = true;
			ofLogWarning("ofxSurfingImGui") << "Could not add mouse wheel to " << param.getName();

			return;
		}

		//--

		{
			bool bCtrl = ImGui::GetIO().KeyCtrl; // CTRL key to fine tunning
			bool bAlt = ImGui::GetIO().KeyAlt; // ALT key to fine tunning

			// Show floating value
			if (bCtrl || bAlt)
			{
				if (bIsbool) sTooltip = dynamic_cast<ofParameter<bool>&>(param).get() ? "TRUE" : "FALSE";
				else if (bIsInt) sTooltip = ofToString(dynamic_cast<ofParameter<int>&>(param).get());
				else if (bIsFloat) sTooltip = ofToString(dynamic_cast<ofParameter<float>&>(param).get(), 2);
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

						// BOOL

						if (bIsbool)
						{
							// non dynamic causes exception in macOS
							ofParameter<bool> p = dynamic_cast<ofParameter<bool>&>(param);
							p = !p.get();
						}

						//--

						// VOID

						else if (bIsVoid)
						{
							ofParameter<void> p = dynamic_cast<ofParameter<void>&>(param);
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
								ofParameter<glm::vec2> p = param.cast<glm::vec2>();
								p += wheel * (bCtrl ? resolution : resolution * 10);
								p = ofClamp(p, p.getMin(), p.getMax()); // clamp
							}
							else if (bIsDim3)
							{
								ofParameter<glm::vec3> p = param.cast<glm::vec3>();
								p += wheel * (bCtrl ? resolution : resolution * 10);
								p = ofClamp(p, p.getMin(), p.getMax()); // clamp
							}
							else if (bIsDim2)
							{
								ofParameter<glm::vec4> p = param.cast<glm::vec4>();
								p += wheel * (bCtrl ? resolution : resolution * 10);
								p = ofClamp(p, p.getMin(), p.getMax()); // clamp
							}
							*/
						}

						//--

						// INT

						else if (bIsInt)
						{
							ofParameter<int> p = dynamic_cast<ofParameter<int>&>(param);

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

						// FLOAT

						else if (bIsFloat)
						{
							// ofParameter<float> p = param.cast<float>();//not dynamic makes error on macOS
							ofParameter<float> p = dynamic_cast<ofParameter<float>&>(param);

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
					// BOOL
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
	inline bool AddMouseClickRightReset(ofParameter<ParameterType>& param, bool bToMinByDefault = false)
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

		// right clicked

		//static bool bModCtrl;
		//static bool bModAlt; 
		bool  bModCtrl = ImGui::IsKeyDown(ImGuiKey_ModCtrl);
		bool bModAlt = ImGui::IsKeyDown(ImGuiKey_ModAlt);
		

		bool bChanged = false;

		// param type
		bool bUnknown = false;
		bool bIsInt = false;
		bool bIsFloat = false;
		bool bIsMultiDim = false;
		bool bIsDim2 = false;
		bool bIsDim3 = false;
		bool bIsDim4 = false;

		const auto& info = typeid(ParameterType);

		if (0) {}

		else if (info == typeid(float)) // FLOAT
		{
			bIsFloat = true;
		}
		else if (info == typeid(int)) // INT
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
			bUnknown = true;
			ofLogWarning("ofxSurfingImGui") << "AddMouseClickRightReset : Could not add mouse wheel to " << param.getName();

			return false;
		}

		//--

		if (0) {}

		//--

		//TODO:
		// Must be fixed bc each dim slider could work independently...

		// MULTIDIM

		else if (bIsMultiDim)
		{
			if (bIsDim2)
			{
				ofParameter<glm::vec2> p = param.cast<glm::vec2>();
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
				ofParameter<glm::vec3> p = param.cast<glm::vec3>();
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
				ofParameter<glm::vec4> p = param.cast<glm::vec4>();
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

		// INT

		else if (bIsInt)
		{
			ofParameter<int> p = dynamic_cast<ofParameter<int>&>(param);

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

		// FLOAT

		else if (bIsFloat)
		{
			ofParameter<float> p = dynamic_cast<ofParameter<float>&>(param);

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
	inline void AddTooltip(std::string text, bool bEnabled = true) // call after the pop up trigger widget
	{
		if (!bEnabled) return;

		//if (IsItemHovered() && GImGui->HoveredIdTimer > 1000) // delayed
		//if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 500) // delayed // not work ?

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

	//--------------------------------------------------------------
	template<typename ParameterType>
	void AddTooltip(ofParameter<ParameterType>& p, bool bEnabled = true, bool bNoName = false)
	{
		bool bReturn = false;
		string name = p.getName();
		auto tmpRef = p.get();

		const auto& t = typeid(ParameterType);
		bool isFloat = (t == typeid(float));
		bool isInt = (t == typeid(int));
		bool isBool = (t == typeid(bool));

		if (!isFloat && !isInt && !isBool) {
			ofLogWarning("ofxSurfingImGui") << "Tooltip: ofParam type named " + name + " is not a Float, Int or Bool";
		}

		string s = "";
		if (!bNoName) s += p.getName() + "\n";
		if (isFloat) s += ofToString(p.get(), 3);//improve format
		else if (isInt) s += ofToString(p.get());
		else if (isBool) s += ofToString((p.get() ? "TRUE" : "FALSE"));

		AddTooltip(s);
	}

	//----------------------

	// ofParameter's Helpers

	void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen);

#if OF_VERSION_MINOR >= 10
	bool AddParameter(ofParameter<glm::ivec2>& parameter, bool bfoldered = false);
	bool AddParameter(ofParameter<glm::ivec3>& parameter, bool bfoldered = false);
	bool AddParameter(ofParameter<glm::ivec4>& parameter, bool bfoldered = false);

	bool AddParameter(ofParameter<glm::vec2>& parameter, bool bsplit = false, bool bfoldered = false);
	// split each arg to big sliders. make a folder container.
	bool AddParameter(ofParameter<glm::vec3>& parameter, bool bsplit = false, bool bfoldered = false);
	// split each arg to big sliders. make a folder container.
	bool AddParameter(ofParameter<glm::vec4>& parameter, bool bsplit = false, bool bfoldered = false);
	// split each arg to big sliders. make a folder container.
#endif

	//TODO:
	bool AddParameter(ofParameter<ofVec2f>& parameter);
	bool AddParameter(ofParameter<ofVec3f>& parameter);
	bool AddParameter(ofParameter<ofVec4f>& parameter);

	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha = true);
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha = true);

	//TODO:
	bool AddParameter(ofParameter<ofColor>& parameter, bool alpha, ImGuiColorEditFlags flags);
	bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha, ImGuiColorEditFlags flags);

	bool AddParameter(ofParameter<ofRectangle>& parameter);

	bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars = 255, bool multiline = false);

	bool AddParameter(ofParameter<void>& parameter, float width = 0);

	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& parameter, std::string format = "%.3f");

	//--

	template<typename ParameterType>
	bool AddText(ofParameter<ParameterType>& parameter, bool label = true);

	bool AddRadio(ofParameter<int>& parameter, std::vector<std::string> labels, int columns = 1);

	bool AddCombo(ofParameter<int>& parameter, std::vector<std::string> labels, bool bRaw = false);

	//-

	bool AddSlider(ofParameter<float>& parameter, const char* format = "%.3f", float power = 1.0f);

	bool AddRange(const std::string& name, ofParameter<int>& parameterMin, ofParameter<int>& parameterMax, int speed = 1);
	bool AddRange(const std::string& name, ofParameter<float>& parameterMin, ofParameter<float>& parameterMax, float speed = 0.01f);

#if OF_VERSION_MINOR >= 10
	bool AddRange(const std::string& name, ofParameter<glm::vec2>& parameterMin, ofParameter<glm::vec2>& parameterMax, float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec3>& parameterMin, ofParameter<glm::vec3>& parameterMax, float speed = 0.01f);
	bool AddRange(const std::string& name, ofParameter<glm::vec4>& parameterMin, ofParameter<glm::vec4>& parameterMax, float speed = 0.01f);
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

	// Stepper widgets. (with +/- buttons to increment/decrement)

	//bool AddStepper(ofParameter<int>& parameter, int step = -1, int stepFast = -1);
	//bool AddStepper(ofParameter<float>& parameter, float step = -1, float stepFast = -1);

	//--------------------------------------------------------------
	inline bool AddStepperInt(ofParameter<int>& parameter)
	{
		bool bChanged = false;
		auto tmpRefi = parameter.get();
		const ImU32 u32_one = 1;
		static bool inputs_step = true;

		string name = parameter.getName();
		string n = "##STEPPERint" + name;// +ofToString(1);
		ImGui::PushID(n.c_str());

		IMGUI_SUGAR__STEPPER_WIDTH_PUSH;

		//if (ImGui::InputScalar(parameter.getName().c_str(), ImGuiDataType_U32, (int*)&tmpRefi, inputs_step ? &u32_one : NULL, NULL, "%u"))

		if (ImGui::InputScalar(parameter.getName().c_str(), ImGuiDataType_S32, (int*)&tmpRefi, inputs_step ? &u32_one : NULL, NULL, "%d"))
		{
			tmpRefi = ofClamp(tmpRefi, parameter.getMin(), parameter.getMax());
			parameter.set(tmpRefi);

			bChanged = true;
		}

		ImGui::PopID();

		IMGUI_SUGAR__STEPPER_WIDTH_POP;

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
		string n = "##STEPPERfloat" + name;// +ofToString(1);
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

	// Stepper aux. to be used to not draw label. 
	// useful to use on combo of widgets to populate one single variable!
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
			ofLogWarning("ofxSurfingImGui") << "Stepper: ofParam type named " + name + " is not a Float or an Int";
			return false;
		}

		//int
		const ImU32 u32_one = 1;
		static bool inputs_step = true;

		//float
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
	// Clean of Styles with the default styles.
	//--------------------------------------------------------------
	template<typename ParameterType>
	bool AddParameter(ofParameter<ParameterType>& parameter, std::string format)
	{
		//std::string format = "%.3f";//TODO:

		auto tmpRef = parameter.get();
		const auto& info = typeid(ParameterType);

		//--

		// FLOAT

		if (info == typeid(float))
		{
			IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
			if (ImGui::SliderFloat((parameter.getName().c_str()), (float*)&tmpRef, parameter.getMin(), parameter.getMax(), format.c_str()))
			{
				parameter.set(tmpRef);
				IMGUI_SUGAR__WIDGETS_POP_WIDTH;
				return true;
			}
			IMGUI_SUGAR__WIDGETS_POP_WIDTH;
			return false;
		}

		//--

		// INT

		else if (info == typeid(int))
		{
			IMGUI_SUGAR__WIDGETS_PUSH_WIDTH;
			if (ImGui::SliderInt((parameter.getName().c_str()), (int*)&tmpRef, parameter.getMin(), parameter.getMax()))
			{
				parameter.set(tmpRef);

				IMGUI_SUGAR__WIDGETS_POP_WIDTH;
				return true;
			}

			IMGUI_SUGAR__WIDGETS_POP_WIDTH;
			return false;
		}

		//--

		// BOOL

		else if (info == typeid(bool))
		{
			if (ImGui::Checkbox((parameter.getName().c_str()), (bool*)&tmpRef))
			{
				parameter.set(tmpRef);
				return true;
			}

			return false;
		}

		//--

		// UNKNOWN

		if (info.name() == "" || info.name() == " ")
			ofLogWarning("ofxSurfingImGui") << "Could not create GUI element for type " << info.name();

		return false;
	}

	//--

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool AddText(ofParameter<ParameterType>& parameter, bool label)
	{
		if (label)
		{
			ImGui::LabelText((parameter.getName().c_str()), ofToString(parameter.get()).c_str());
		}
		else
		{
			ImGui::Text(ofToString(parameter.get()).c_str());
		}

		return true;
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
					ofLogWarning("ofxSurfingImGui") << "Could not create GUI element for type " << info.name();

				IMGUI_SUGAR__WIDGETS_POP_WIDTH;

				return false;
			}
		}

		IMGUI_SUGAR__WIDGETS_POP_WIDTH;

		return result;
	}

	//----

	// Image Textures
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

	//TODO:
	// Must replace a bunch of GuiManager to move it here...
	// 
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
		//// label
		//if (!bMinimized) this->AddLabelHuge(p.getName(), true, true);
		//else this->AddLabelBig(p.getName(), true, true);

		//// stepper
		//bReturn += this->Add(p, OFX_IM_STEPPER_NO_LABEL);
		////bReturn += this->Add(p, bMinimized ? OFX_IM_STEPPER : OFX_IM_STEPPER_NO_LABEL);

		//// slider
		//bReturn += this->Add(p, bMinimized ? OFX_IM_HSLIDER_MINI_NO_LABELS : OFX_IM_HSLIDER_SMALL_NO_LABELS);

		// arrows
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
			// knob
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
