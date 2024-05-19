/*
 *
 *  BigTextInput.h
 *
 *  This widget is a big text input widget.
 *  Useful to integrate typeable text input widgets.
 *	For example: prompts, query search.
 *  Features single line with hint and multi-line.
 *  Many style customizations.
 *  Responsive layout.
 *  Persistent settings.
 *
 */

 /*

	 TODO

	 + add text color
	 + fix submit responsive workflow
	 + allow set number lines and fix responsive
		 improve multi-line size
	 + make submit button zone as a second column
	 + add reload last text
	 + add browse history

 */

 //--

#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"
#include "imgui_stdlib.h"
#include "Spinners2.h"
//#include "imspinner.h"

// Required for custom callback when submit button pressed
#include <functional>
using callback_t = std::function<void()>;

class BigTextInput
{
public:
	BigTextInput()
	{
		ofAddListener(ofEvents().update, this, &BigTextInput::update);
		ofAddListener(ofEvents().windowResized, this, &BigTextInput::windowResized);
	}

	~BigTextInput()
	{
		exit();
	}

	void setup()
	{
		typeInputName.setSerializable(false);
		bDebug.setSerializable(false);

		paramsWindow.add(bGui);
		paramsWindow.add(bGui_Config);
		paramsWindow.add(bGui_Headers);
		paramsWindow.add(bGui_Bg);
		paramsWindow.add(bGui_ResizePin);
		paramsWindow.add(bGui_LockMove);
		g.add(paramsWindow);
		g.add(bDebug);

		paramsMain.add(colorBubble);
		paramsMain.add(colorTxt);
		paramsMain.add(windowY);
		paramsMain.add(bBottomTextInput);
		paramsMain.add(windowPadX);
		paramsMain.add(sizeBubbleX);
		paramsMain.add(sizeBubbleY);
		paramsMain.add(rounded);
		paramsMain.add(bLabel);
		paramsMain.add(typeInput);
		paramsMain.add(typeInputName);
		paramsMain.add(sizeFont);
		paramsMain.add(padTextX);
		paramsMain.add(padTextY);
		params.add(paramsMain);

		paramsSubmit.add(padSubmitX);
		paramsSubmit.add(bButtonsLeft);
		paramsSubmit.add(bButtonRight);
		paramsSubmit.add(bSmallerSizeTextButton);
		params.add(paramsSubmit);

		paramsShadow.add(bShadow);
		paramsShadow.add(colorShadow);
		paramsShadow.add(positionshadow);
		params.add(paramsShadow);

		paramsBorder.add(bBorder);
		paramsBorder.add(colorBorder);
		paramsBorder.add(thicknessBorder);
		params.add(paramsBorder);

		g.add(params);
		// params goes to ui
		// g do not goes to ui. just for serialize settings.

		// Presets
		paramsPreset.add(paramsMain);
		paramsPreset.add(paramsSubmit);
		paramsPreset.add(paramsShadow);
		paramsPreset.add(paramsBorder);

		//--

		eTypeInput = typeInput.newListener([this](int& v)
			{
				switch (typeInput.get())
				{
				case 0: typeInputName = typeInputNames[0];
					break;
				case 1: typeInputName = typeInputNames[1];
					break;
				case 2: typeInputName = typeInputNames[2];
					break;
				default: typeInputName = "unknown";
					break;
				}
			});

		//workflow: edit
		eDebug = bDebug.newListener([this](bool& b)
			{
				bGui_Headers = bDebug;
				bGui_ResizePin = bDebug;
				bGui_Bg = bDebug;
				bIntegrate = !bDebug;
				bBlink = !bDebug;
			});

		eWindowY = windowY.newListener([this](float& v)
			{
				doFlagResetWindow();
			});
		eWindowPadX = windowPadX.newListener([this](float& v)
			{
				doFlagResetWindow();
			});
		eBottombTextInput = bBottomTextInput.newListener([this](bool& b)
			{
				doFlagResetWindow();
			});

		//eButton = bButtonRight.newListener([this](bool& b)
		//	{
		//		if (bButtonRight) bButtonsLeft = 0;
		//		else if (!bButtonsLeft) bButtonsLeft = 1;
		//	});
		//eButtons = bButtonsLeft.newListener([this](bool& b)
		//	{
		//		if (bButtonsLeft) bButtonRight = 0;
		//		else if (!bButtonRight) bButtonRight = 1;
		//	});

		//default 
		// doResetConfig();
		doResetAll();

		//--

		bDoneSetup = 1;
	}

	bool bOverTextInput = 0;

public:
	ofParameter<string> textInput{ "Text", "" }; // last submit text
	// could be used as receiver/destination of the input text widget
	// and also the event listener toi be used as callback
	// to be notified and to receive/get the submitted text.

	ofParameter<bool> bGui{"TextInput", true}; // show widget
	ofParameter<bool> bGui_Config{"Config TextInput", false}; // show config
	ofParameter<bool> bDebug{"Debug", false}; // debug/edit mode
	ofParameter<bool> bGui_LockMove{"Lock", false};

	ofColor getColor() const { return colorBubble.get(); }
	ofParameter<bool> bWaiting{"Waiting", 0}; // to be commanded from parent scope!
	int typeWaiting = 0;

	ofParameter<ofColor> colorBubble { "ColBg", ofColor(64), ofColor(), ofColor() };
	ofParameter<ofColor> colorTxt { "ColTxt", ofColor(255), ofColor(), ofColor() };

	ofParameterGroup paramsPreset{ "BigTextInput" };
	ofParameter<bool> bBottomTextInput{"Bottom", false}; //flip y direction
	ofParameter<float> windowY{"WindowY", 0, 0, 1};
	ofParameter<float> windowPadX{"WindowPadX", 0, 0, 1};
	ofParameter<float> rounded{"Rounded", 0, 0, 1};

private:
	ofParameterGroup params{ "TextInputBubble" };
	ofParameter<bool> bGui_Global{"BigTextInput", true}; //TODO:

private:
	ofParameterGroup g{ "BigTextInput" };

	ofParameterGroup paramsWindow{ "Window" };
	ofParameterGroup paramsMain{ "Main" };

	ofParameter<bool> bGui_Headers{"Headers", true};
	ofParameter<bool> bGui_Bg{"Bg", true};
	ofParameter<bool> bGui_ResizePin{"Resizer", true};

	ofParameter<bool> bLabel{"Label", false}; //TODO:
	ofParameter<int> sizeFont{"FontSize", 0, 0, 3};
	ofEventListener eWindowY;
	ofEventListener eWindowPadX;
	ofEventListener eBottombTextInput;

	ofParameter<float> sizeBubbleX{"SizeX", 1.f, 0, 1};
	ofParameter<float> sizeBubbleY{"SizeY", 1.f, 0, 1};
	ofParameter<float> padTextX{"PadTextX", 0.f, 0, 1};
	ofParameter<float> padSubmitX{"PadSubmitX", 1.f, 0, 1};
	ofParameter<float> padTextY{"PadTextY", 0.f, -1, 1};
	ofParameter<int> typeInput{"TypeImGui", 0, 0, 2};
	ofParameter<string> typeInputName{"TypeName", ""};
	ofEventListener eTypeInput;
	vector<string> typeInputNames{"InputText", "InputTextWithHint", "InputTextMultiline"};

	ofParameterGroup paramsShadow{ "Shadow" };
	ofParameter<bool> bShadow{"Shadow", false};
	ofParameter<ofColor> colorShadow{"ColShw", ofColor::black, ofColor(), ofColor()};
	ofParameter<glm::vec2> positionshadow{"PosShw", glm::vec2(0), glm::vec2(0), glm::vec2(1.f)};

	ofParameterGroup paramsBorder{ "Border" };
	ofParameter<bool> bBorder{"Border", false};
	ofParameter<ofColor> colorBorder{"ColBrd", ofColor::black, ofColor(), ofColor()};
	ofParameter<float> thicknessBorder{"Thickness", 1.f, 0, 5.f};

	ofParameterGroup paramsSubmit{ "SubmitButton" };
	ofParameter<bool> bSmallerSizeTextButton{"SmallerText", true};
	ofParameter<bool> bButtonsLeft{"Left Buttons", true};
	ofParameter<bool> bButtonRight{"Right Button", true};

	bool bBlink = 1; //hint text bubble blink when empty
	bool bIntegrate = 1; //put the internal input text transparent

	ofEventListener eDebug;

	string strHint = "Prompt";
	string strLabel = "TextInput";
	string strSubmit = "Submit";

	bool bFlagResetWindow = 0;

private:
	//settings file
	string path_Global = ""; //main folder where nested folder goes inside
	string path_Settings = "BigTextInput_Settings.json";

public:
	void setPathGlobal(std::string path)
	{
		path_Global = path;
		ofxImGuiSurfing::CheckFolder(path_Global);
	}

	void setName(std::string name)
	{
		g.setName(name);
		bGui.setName(name);

		string s = name;
		s += ofToString("_Settings.json");
		path_Settings = s;

		ofxImGuiSurfing::CheckFolder(path_Global);
	}

public:
	void setHint(string s) { strHint = s; };
	void setLabel(string s) { strLabel = s; };
	void setSubmit(string s) { strSubmit = s; };
	void setText(string s) { text = s; };
	void setFocus() { bFlagGoFocus = 1; };

private:
	bool bFlagGoFocus = 0;

	//--

	// Advanced submit callback
private:
	// Pointer to store a function
	callback_t functionCallbackSubmit = nullptr;
	callback_t functionCallbackClear = nullptr;
	callback_t functionCallbackKeys = nullptr;
	callback_t functionDrawImGuiContextMenu = nullptr;

public:
	void setDrawWidgetsFunctionContextMenu(callback_t f = nullptr)
	{
		functionDrawImGuiContextMenu = f;
	}

	void setFunctionCallbackSubmit(callback_t f = nullptr)
	{
		functionCallbackSubmit = f;
	}

	void setFunctionCallbackClear(callback_t f = nullptr)
	{
		functionCallbackClear = f;
	}

	void setFunctionCallbackKeys(callback_t f = nullptr)
	{
		functionCallbackKeys = f;
	}

	//TODO:
	// trying to notify to the parent scope that a key is pressed (to trig sounds) 
	// WIP do not works.
	/*
	int callback(ImGuiInputTextCallbackData* data)
	{
		if (data->EventFlag & ImGuiInputTextFlags_CallbackEdit)
		{
			if (functionCallbackKeys != nullptr) functionCallbackKeys();

			if (data->BufTextLen == 1 && (data->Buf[0] >= 'a' || data->Buf[0] <= 'z'))
			{
				data->Buf[0] = (char)toupper((char)data->Buf[0]);
				data->BufDirty = true;
			}
		}
		return 0;
	}
	*/

private:
	// Set external widgets to be inserted!
	callback_t functionDraw = nullptr;
public:
	void setDrawWidgetsFunction(callback_t f = nullptr)
	{
		functionDraw = f;
	};

public:
	// To get the text when notified.
	string getText() const { return textInput.get(); }

	void doEnterKey()
	{
		doSubmit(textInput);
	}

private:
	void doSubmit(string s)
	{
		textInput = s;
		ofLogNotice("ofxSurfingImGui::doSubmit") << s;

		// Trigs callback to parent / ofApp
		if (functionCallbackSubmit != nullptr) functionCallbackSubmit();
	}

	string text = "";

	//--

private:
	bool bDoneSetup = 0;
	bool bDoneStartup = 0;

	void startup()
	{
		string s;
		if (path_Global == "") s = path_Settings;
		else s = path_Global + "/" + path_Settings;
		ofxImGuiSurfing::loadGroup(g, s);

		//--

		bDoneStartup = 1;
	}

	void exit()
	{
		ofRemoveListener(ofEvents().update, this, &BigTextInput::update);
		ofRemoveListener(ofEvents().windowResized, this, &BigTextInput::windowResized);

		string s;
		if (path_Global == "") s = path_Settings;
		else s = path_Global + "/" + path_Settings;
		ofxImGuiSurfing::saveGroup(g, s);
	}

	void update(ofEventArgs& args)
	{
		if (!bDoneSetup) setup();
		else if (!bDoneStartup)
		{
			startup();
		}
	}

	void windowResized(ofResizeEventArgs& resize)
	{
		static float _w = -1;
		static float _h = -1;
		bool b = 0;
		if (_w != resize.width)
		{
			_w = resize.width;
			b = 1;
		}
		if (_h != resize.height)
		{
			_h = resize.height;
			b = 1;
		}
		if (!b) return; // skip if not changed

		ofLogVerbose("ofxSurfingImGui::BigTextInput::windowResized") << resize.width << "," << resize.height;
		doFlagResetWindow();
	}

public:
	void setupStyles(ofxSurfingGui& ui)
	{
		// Init Style
		static bool b = 0;
		if (!b)
		{
			b = 1;
			ui.AddStyle(typeInputName, OFX_IM_TEXT_DISPLAY); //hide label. disable input mode.
			ui.AddStyleGroup(paramsSubmit, OFX_IM_GROUP_COLLAPSED);
			ui.AddStyleGroup(paramsShadow, OFX_IM_GROUP_COLLAPSED);
			ui.AddStyleGroup(paramsBorder, OFX_IM_GROUP_COLLAPSED);
		}
	}

	void draw(ofxSurfingGui& ui)
	{
		setupStyles(ui);

		//--

		drawImGui_Config(ui);
		drawImGui_Widget(ui);
	}

	bool isVisible() {
		return (bGui || bGui_Config);
	}

private:
	// Configuration window
	// Settings will be presistent
	void drawImGui_Config(ofxSurfingGui& ui)
	{
		if (!bGui_Config) return;

		if (ui.BeginWindow(bGui_Config))
		{
			ui.Add(bGui, OFX_IM_TOGGLE_ROUNDED_MEDIUM);
			ui.AddMinimizerToggle();
			ui.AddSpacing();

			ui.Add(bDebug, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			ui.AddSpacingBigSeparated();

			if (ui.isMaximized())
			{
				ui.AddLabelBig("Window");
				if (bDebug)
				{
					ui.Add(bGui_Headers, OFX_IM_TOGGLE_ROUNDED);
					ui.Add(bGui_Bg, OFX_IM_TOGGLE_ROUNDED);
				}
				ui.Add(bGui_LockMove, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_ResizePin, OFX_IM_TOGGLE_ROUNDED);
			}
			else
			{
				ui.Add(bGui_LockMove, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_ResizePin, OFX_IM_TOGGLE_ROUNDED);
			}
			ui.AddSpacingBigSeparated();

			ui.AddGroup(params);
			ui.AddSpacing();

			if (ui.isMaximized() && bDebug)
			{
				ImGui::Checkbox("Integrate", &bIntegrate);
				ImGui::Checkbox("Blink", &bBlink);
			}
			ui.AddSpacingSeparated();

			if (ui.AddButton(("Reset"), OFX_IM_BUTTON))
			{
				doResetConfig();
			}
			/*
			if (ui.AddButton(("Reset Config"), OFX_IM_BUTTON_SMALL, 2))
			{
				doResetConfig();
				// doResetAll();
			}
			ui.SameLine();
			if (ui.AddButton(("Reset Window"), OFX_IM_BUTTON_SMALL, 2))
			{
				//TODO: default
				// windowY = 0.9;
				// windowPadX = 0.2;

				doFlagResetWindow();
			}
			*/

			ui.AddSpacing();

			ui.EndWindow();
		}
	}

	// The main widget!
	void drawImGui_Widget(ofxSurfingGui& ui)
	{
		if (!bGui) return;

		static float x, y, w, h;

		//--

		if (bFlagResetWindow)
		{
			bFlagResetWindow = 0;
			doResetWindow();
		}

		//--

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
		if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
		if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

		// Constraints
		//ImVec2 size_min = ImVec2(700, bButtonsLeft ? 150 : 100);
		ImVec2 size_min = ImVec2(700, 200); //allow spin height
		ImVec2 size_max = ImVec2(FLT_MAX, FLT_MAX);
		ImGui::SetNextWindowSizeConstraints(size_min, size_max);

		bool bUpper = 1; //uppercase for labels

		//--

		if (ui.BeginWindow(bGui, window_flags))
		{
			//TODO: remove pad
			// RemoveHeaderHeight();
			//if (!bGui_Headers) ofxImGuiSurfing::AddSpacingY(ImGui::GetStyle().WindowPadding.y);

			if (!bGui_Headers) AddHeaderHeight();

			const char* label = strLabel.c_str();
			const char* hint = strHint.c_str();

			//--

			void* user_data = NULL;
			static bool isChanged = false;

			float xx, yy;
			float _wTextBB;
			float _padSubmitX;
			float xxBb, yyBb;

			w = ImGui::GetContentRegionAvail().x;
			h = ImGui::GetContentRegionAvail().y;

			ui.PushFontStyle(SurfingFontTypes(sizeFont.get()));

			ImDrawList* draw_list = ImGui::GetWindowDrawList();

			ImVec2 p = ImGui::GetCursorScreenPos();
			//ImDrawFlags flags = ImDrawFlags_None;

			//--

			// Bubble Draw

			float pxBubble = (1 - sizeBubbleX) * (w * 0.25f);
			float pyBubble = (1 - sizeBubbleY) * (h * 0.25f);

			x = p.x + pxBubble;
			y = p.y + pyBubble;

			w -= 2 * pxBubble;
			h -= 2 * pyBubble;

			w -= 2 * (1 - sizeBubbleX);
			h -= 2 * (1 - sizeBubbleY);

			// Bubble bounding box rectangle
			ImRect rBB(x, y, w, h);

			float round = rounded * (h / 2);

			// Shadow
			if (bShadow)
			{
				ImU32 col2 = ImGui::GetColorU32(colorShadow.get());
				float _diffMax = h * 0.2;
				ImVec2 _diff = positionshadow * ImVec2(_diffMax, _diffMax);
				draw_list->AddRectFilled(rBB.Min + _diff, rBB.Min + _diff + rBB.Max, col2, round);
			}

			// Bubble
			{
				ImU32 col = ImGui::GetColorU32(colorBubble.get());
				draw_list->AddRectFilled(rBB.Min, rBB.Min + rBB.Max, col, round);

				//TODO:
				// draw a floating context menu with some widgets
				if (functionDrawImGuiContextMenu != nullptr)
				{
					ImVec2 p_ = ImGui::GetCursorScreenPos();
					ImGui::InvisibleButton("MyInvisibleButton", ImVec2(w, h));
					ImGui::SetCursorPos(p_);
					functionDrawImGuiContextMenu();
				}
			}

			// Border
			if (bBorder)
			{
				ImU32 col2 = ImGui::GetColorU32(colorBorder.get());
				draw_list->AddRect(rBB.Min, rBB.Min + rBB.Max, col2, round, ImDrawFlags_None, thicknessBorder);
			}

			// Spacing for ImGui::TextInput widget
			float _hTextBB = ui.getWidgetsHeightUnit(); //one line

			// Offset to center in the bubble
			xx = ImGui::GetCursorPosX();
			yy = ImGui::GetCursorPosY();

			xx += padTextX * (w * 0.25f);
			//xx += _offsetx;
			xx += pxBubble;

			float hl = ui.getWidgetsHeightUnit();
			yy += h / 2;
			yy += padTextY * (h * 0.25f);
			yy += pyBubble;

			yy -= hl / 2;

			////TODO:
			//if (bDebug) {
			//	ImRect r2(10, 10, 50, 50);
			//	//ImRect r2(xx, yy, _ww, _hh);
			//	draw_list->AddRect(r2.Min, r2.Min + r2.Max, IM_COL32(255, 0, 0, 255), 0);
			//}

			//float _offsetx = scalex * (w / 2);
			//float _ww = w - 2 * _offsetx;

			//TODO:
			_wTextBB = w;
			_wTextBB -= padTextX * (w * 0.25f);

			_padSubmitX = ofMap(padSubmitX, 1, 0, 0, w * 0.25);
			_wTextBB -= _padSubmitX;
			//_wBb -= pxBubble/2;

			//--

			ImGui::SetCursorPosX(xx);
			ImGui::SetCursorPosY(yy);

			//--

			// Text Input

			if (bLabel)
			{
			}
			else
			{
				label = "##label"; //remove
			}

			bool _bBlink = bBlink && (text == "");

			ImGuiInputTextFlags _flags = ImGuiInputTextFlags_None;
			_flags |= ImGuiInputTextFlags_CallbackEdit;
			//_flags |= ImGuiInputTextFlags_CallbackCharFilter;
			//_flags |= ImGuiInputTextFlags_CallbackResize;

			PushItemWidth(_wTextBB);
			{
				if (_bBlink) ui.BeginBlinkTextDisabled();
				if (bIntegrate)
				{
					ImVec4 c = ImVec4(0, 0, 0, 0); //transparent
					ImGui::PushStyleColor(ImGuiCol_Border, c);
					ImGui::PushStyleColor(ImGuiCol_FrameBg, c);
				}
				ImGui::PushStyleColor(ImGuiCol_Text, colorTxt.get());

				//hint prompt 
				float a = getFadeBlink();
				ImVec4 cd = ImVec4(colorTxt.get().r / 255.f, colorTxt.get().g / 255.f, colorTxt.get().b / 255.f, a);
				//transparent
				ImGui::PushStyleColor(ImGuiCol_TextDisabled, cd);

				// Focus to be ready to type
				if (bFlagGoFocus == 1)
				{
					bFlagGoFocus = 0;
					ImGui::SetKeyboardFocusHere(0); // Move keyboard focus to the InputTextWithHint widget
					ImGui::SetItemDefaultFocus(); // Set the focus to the first item in the widget
				}

				// Capitalize first char
#if 0
				//TODO: can be passed functionCallbackKeys
				auto callback = [](ImGuiInputTextCallbackData* data) -> int
				{
					if (data->EventFlag & ImGuiInputTextFlags_CallbackEdit)
					{
						//if (functionCallbackKeys != nullptr) functionCallbackKeys();//TODO:

						if (data->BufTextLen == 1 && (data->Buf[0] >= 'a' || data->Buf[0] <= 'z'))
						{
							data->Buf[0] = (char)toupper((char)data->Buf[0]);
							data->BufDirty = true;
						}
					}
					return 0;
			};
#else
				ImGuiInputTextCallback callback = NULL;
#endif

				if (typeInput == 0)
				{
					// A
					isChanged = ImGui::InputText(label, &text, _flags, callback);
					//isChanged = ImGui::InputText(label, &text, _flags, callback, user_data);
				}
				else if (typeInput == 1)
				{
					// B
					isChanged = ImGui::InputTextWithHint(label, hint, &text, _flags, callback);
				}
				else if (typeInput == 2)
				{
					// C
					_hTextBB = 2 * ui.getWidgetsHeightUnit(); //two lines
					//// int nlines = ofMap(rBB.GetHeight(), 0, ui.getWidgetsHeightUnit())
					// int nlines = rBB.GetHeight() / ui.getWidgetsHeightUnit();
					// nlines = MAX(1, nlines + 1);
					// _hTextBB = nlines * ui.getWidgetsHeightUnit(); //n lines
					// cout << "nlines:" << nlines << endl;

					ui.AddSpacingY(-_hTextBB * 0.25);
					ImVec2 _sz = ImVec2(_wTextBB, _hTextBB);
					isChanged = ImGui::InputTextMultiline(label, &text, _sz, _flags, callback);
				}

				bOverTextInput = ImGui::IsItemHovered();

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
				if (bIntegrate) ImGui::PopStyleColor(2);
				if (_bBlink) ui.EndBlinkTextDisabled();
		}
			PopItemWidth();

			ui.PopFontStyle();

			// Store position after text input bb
			//IMGUI_SUGAR__DEBUG_POINT(ofColor::red);
			xxBb = ImGui::GetCursorPosX();
			yyBb = ImGui::GetCursorPosY();

			static bool bPosMiniButRight = 0; //pos left or right

			//--

			// Submit Button

			//if (bButtonRight)
			{
				ui.PushFontStyle(SurfingFontTypes(sizeFont.get()));

				if (bSmallerSizeTextButton) ui.PushFontStyle(SurfingFontTypes(MAX(0, sizeFont.get() - 1)));

				string s = strSubmit;
				if (bUpper) { s = ofToUpper(s); }

				// size
				float padx = 1.5 * ui.getFontSize();
				float pady = 0.7 * ui.getFontSize();
				ImVec2 szBt(padx + ImGui::CalcTextSize(s.c_str()).x, pady + ui.getWidgetsHeightUnit());

				//TODO: layout
				float _xx = xx + _wTextBB + 0.2 * szBt.x;
				float _yy = yy;
				if (typeInput == 2)
				{
					_yy -= hl / 2;
				}
				_yy += _hTextBB / 2;
				_yy -= szBt.y / 2;

				ImGui::SetCursorPosX(_xx);
				ImGui::SetCursorPosY(_yy);

				// Submit

				if (bButtonRight)
				{
					// add transparency
					ImVec4 c = ImGui::GetStyle().Colors[ImGuiCol_Text];
					ImVec4 _c = ImVec4(c.x, c.y, c.z, c.w * 0.7);
					ImGui::PushStyleColor(ImGuiCol_Text, _c);
					if (ImGui::Button(s.c_str(), szBt))
					{
						doSubmit(text);
						text = "";
					}
					ImGui::PopStyleColor();
				}

				if (bSmallerSizeTextButton) ui.PopFontStyle();

				//ImGui::SameLine();

				// Below Submit button
				// Insert external widgets if already settled!
				if (bPosMiniButRight)
					if (functionDraw != nullptr)
					{
						ImGui::SetCursorPosX(_xx + szBt.x - 22);
						ui.AddSpacingY(10);
						functionDraw();
					}
#if(1)
				// Spinner
				float xo = 0;
				float yo = 10;
				xo += (szBt.x / 2);
				xo -= 14;
				ImGui::SetCursorPosX(_xx + xo);
				if (!bButtonRight) ImGui::SetCursorPosY(_yy + yo);
				else ui.AddSpacingY(4);
				ImSpinner::Spinner(bWaiting, typeWaiting);
#endif

				ui.PopFontStyle();
			}
			//else {
			//	// Spinner
			//	//float xo = 0;
			//	//xo += (szBt.x / 2);
			//	//xo -= 14;
			//	//ImGui::SetCursorPosX(_xx + xo);
			//	ImSpinner::Spinner(bWaiting, typeWaiting);
			//}

			//--

			// Clear and Submit buttons

			if (bButtonsLeft)
			{
				// Back cursor to text bb
				float x_ = padTextX * (w * 0.25f);
				x_ += ImGui::GetStyle().ItemInnerSpacing.x;
				float y_ = ImGui::GetStyle().ItemInnerSpacing.y;

				ImGui::SetCursorPosX(xxBb + x_);
				ImGui::SetCursorPosY(yyBb + y_);

				float padx = 1.25 * ui.getFontSize();
				float pady = 0.5 * ui.getFontSize();

				if (!bButtonRight)
				{
					string s1 = strSubmit + "##SUBMIT2"; //avoid collide
					string s2 = "Clear";
					if (bUpper)
					{
						s1 = ofToUpper(s1);
						s2 = ofToUpper(s2);
					}

					// Submit
					ImVec2 sz1(padx + ImGui::CalcTextSize(strSubmit.c_str()).x, pady + ui.getWidgetsHeightUnit());
					if (ImGui::Button(s1.c_str(), sz1))
					{
						doSubmit(text);
						text = "";
					}
					ImGui::SameLine();

					// Clear
					ImVec2 sz2(padx + ImGui::CalcTextSize(s2.c_str()).x, pady + ui.getWidgetsHeightUnit());
					if (ImGui::Button(s2.c_str(), sz2))
					{
						if (bDebug) ui.AddToLog("BigTextInput -> Clear", OF_LOG_ERROR);
						text = "";
						doSubmit(text);
					}
				}
				else
				{
					// Only clear
					string s2 = "Clear";

					ImVec2 inspc = ImGui::GetStyle().ItemInnerSpacing;
					padx = 1.25 * ui.getFontSize() + 2 * inspc.x;
					// padx = 1.25 * ui.getFontSize();
					// padx = 0.f * ui.getFontSize() + 2 * inspc.x;
					// pady = 0.f * ui.getFontSize();
					// pady = 2 * inspc.y;
					pady = inspc.y;

					// Size
					ImVec2 szBt(padx + ImGui::CalcTextSize(s2.c_str()).x, pady + ui.getWidgetsHeightUnit());

					if (bUpper) { s2 = ofToUpper(s2); }

					// Clear
					if (ImGui::Button(s2.c_str(), szBt))
					{
						if (bDebug) ui.AddToLog("BigTextInput -> Clear", OF_LOG_ERROR);
						text = "";

						// workflow
						//doSubmit(text);

						// Trigs callback to parent / ofApp
						if (functionCallbackClear != nullptr) functionCallbackClear();
					}

					// Left position 
					if (!bPosMiniButRight)
					{
						// Insert external widgets if already settled!
						if (functionDraw != nullptr)
						{
							ImVec2 inspc = ImGui::GetStyle().ItemInnerSpacing;
							ImGui::SetCursorPosX(xx + inspc.x + 3);
							functionDraw();
						}
					}
				}
			}

			//--

			// Get Enter key as submit button
			//bool b = ImGui::GetIO().WantTextInput; // only when focused on text input
			bool b = 1;
			if (b && ImGui::IsKeyPressed(ImGuiKey_Enter))
			{
				doSubmit(text);
				text = "";
			}

			//--

			ui.EndWindow();

			if (isChanged)
			{
				isChanged = 0;
				if (bDebug) ui.AddToLog("BigTextInput -> " + text, OF_LOG_VERBOSE);
			}
	}
}

	//--

public:
	// Reset
	void doResetAll()
	{
		doResetConfig();
		doFlagResetWindow();
	}

	void doResetConfig()
	{
		bBottomTextInput = 0; //flip
		windowY = 0.02; //top
		// windowY = 0.9;//bottom

		windowPadX = 0.2;

		//colorBubble = ofColor(32, 255);
		//colorBorder = ofColor(0, 0);
		colorShadow = ofColor(32, 64);

		typeInput = 1; //hint
		sizeFont = 2;
		rounded = .5;
		sizeBubbleX = sizeBubbleY = 1;

		bDebug = 0;
		bBlink = 0;
		bLabel = 0;

		padSubmitX = 0.2;
		bButtonRight = 1;
		bButtonsLeft = 1;
		bSmallerSizeTextButton = 1;
		padTextX = 0.3;

		bShadow = true;
		positionshadow = glm::vec2(0.f, 0.25);

		bBorder = 1;
		thicknessBorder = 1.5f;
	}

	void doFlagResetWindow() { bFlagResetWindow = 1; }

private:
	void doResetWindow()
	{
		//TODO:
		// bool b=0;
		// static float _heightReset = -1;
		// static float _padxReset = -1;
		// if (windowY != _heightReset) _heightReset = windowY;
		// if (windowPadX != _padxReset) _padxReset = windowPadX;
		//
		// //TODO: default
		// windowY.setWithoutEventNotifications(0.9);
		// windowPadX.setWithoutEventNotifications(0.2);

		//--

		float xx, yy, ww, hh, pad; //bubble bb

		//--

		// x

		//to borders
		// pad = 120;
		pad = ofMap(windowPadX, 0, 1,
			0, 0.15 * ofGetWidth(),
			true);

		xx = pad; //x centered
		ww = ofGetWidth() - (2 * pad); //width

		//--

		// y

		hh = 175; //bubble height

		// yy = ofGetHeight() / 2 - hh / 2; //v centered

		float ho = 0;
		ho += ofxImGuiSurfing::getWidgetsHeightUnit();
		// ho += ImGui::GetWindowHeight() - ImGui::GetContentRegionAvail().y; //header height

		//ratio to the top border
		if (!bBottomTextInput)
		{
			yy = ofMap(windowY, 0, 1,
				hh * 0.5 - ho, ofGetHeight() - hh * 0.5 - ho,
				true); //height centered
			yy -= hh * 0.5f;
		}
		//ratio to the bottom  border
		else
		{
			yy = ofMap(windowY, 1, 0,
				hh * 0.5 - ho, ofGetHeight() - hh * 0.5 - ho,
				true); //height centered
			yy -= hh * 0.5f;
		}

		ImGuiCond flagsCond = ImGuiCond_None;
		flagsCond |= ImGuiCond_FirstUseEver;
		flagsCond = ImGuiCond_None;

		ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
		ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);

		// store rectangle to help on layout
		rWindow = ofRectangle(xx, yy, ww, hh);
	}

	ofRectangle rWindow;

public:
	ofRectangle getWindowRectangle() { return rWindow; }

	bool isMouseOverInputText()
	{
		return bOverTextInput;
	}
};
