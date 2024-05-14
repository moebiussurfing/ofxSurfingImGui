#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//ofSetWindowPosition(-1920, 26);

	names.clear();
	names.push_back("zero");
	names.push_back("one");
	names.push_back("two");
	names.push_back("three");

	index.setMin(0);
	index.setMax(names.size() - 1);

	//----

	setupGui();
}

//--------------------------------------------------------------
void ofApp::setupGui()
{
	ui.setup();

	//--

	// Help box

	string s;
	s = R"(TO LEARN A BIT MORE
ABOUT THE API:

- Spacing and separators.
- Commonly useful minimizer toggle.
- Tool - tips for widgets.
- The Log and Notifier Windows.
- Custom Log tags.
- Mouse over gui getter.
- Note persistence of previous sessions for some settings.
- Text labels.
- Some key - commands examples.
- Make blink widgets.
- Make font bigger on widgets.
- Set a widget inactive.
- Reset UI methods.
- Quaternion parameter.
- This Help info.
)";

	ui.setHelpAppTitle("HELP 02_HelloWorld2");//TODO
	ui.setHelpAppText(s);
	ui.setHelpAppFontStyle(2);//bigger font

	//--

	// Log

	// Add to custom tags to log system
	ui.AddLogTag(myTag1, ofColor::turquoise);
	ui.AddLogTag(myTag2, ofColor::orange);

	// Callback to log
	listener = speed.newListener([this](float& v) {
		ofLogNotice() << v;

		string s = speed.getName() + ": " + ofToString(speed.get(), 1);
		ui.AddToLog(s, myTag1);
		});

	ui.setLogLevel(OF_LOG_ERROR);

	//--

	tabs.setUiPtr(&ui);

	//--
	
	//ui.startup(); // Optional for many scenarios!
}

//--------------------------------------------------------------
void ofApp::update()
{
	// Log/Notify every second
	int d = ofMap(speed, 0, 1, 120, 15);
	if (ofGetFrameNum() % d == 0) {
		static int count = 0;
		string s = "COUNT " + ofToString(++count);

		//ui.AddToLog(s, "NOTICE");
		//ui.AddToNotifier(s, "NOTICE");
		ui.AddToLogAndNotifier(s, "NOTICE");//both
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawGui();

	if (bGui_Quat) drawSceneQuat();
}

//--------------------------------------------------------------
void ofApp::drawGui()
{
	// Not mandatory, but apart of hiding all the below drawn windows,
	// this will allow to hide the Log an Notifier Windows too. 
	// That's bc is auto Log Window drawn when calling ui.End()!
	if (!bGui) return;

	ui.Begin();
	{
		drawGuiMain();

		drawGuiCombos();
		drawGuiQuat();
		drawGuiTabs();
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawGuiMain()
{
	// Close the Window by pressing the top right X.
	// This state is handled internally by bGui bool param!
	// Press space to toggle bGui and show it again.

	static bool bConstraint = 0;
	if (bGui && bConstraint) {
		IMGUI_SUGAR__WINDOWS_CONSTRAINTS;
	}
	if (ui.BeginWindow(bGui))
	{
		string s = "HELP\n\n";
		s += "Enable the Log Window using the above rounded toggle.\n\n";
		s += "Drag the mouse and click left or right button outside or inside the UI, ";
		s += "move speed slider... \n\nThen go look into the Log Window!";
		s += "\n\nPress SPACE to show/hide the UI.";

		// Easy populate toggles for useful internal params.
		ui.AddHelpToggle();
		ui.AddLogToggle();
		ui.AddNotifierToggle();
		ui.AddNotifierToggleEditor();
		//ui.Add(ui.bGui_TopMenuBar, OFX_IM_TOGGLE_ROUNDED);
		ui.AddSpacingSeparated();
		ui.AddMinimizerToggle();
		ui.AddSpacing();

		// Global Scale
		if (ui.isMaximized()) ui.DrawWidgetsGlobalScale();
		else ui.DrawWidgetsGlobalScaleMini();

		// Maximized mode
		//if (!ui.isMinimized()) 
		// does the same than the above line
		if (ui.isMaximized())
		{
			ui.AddDebugToggle();
			ui.AddExtraToggle();
			ui.AddKeysToggle(); // populate a toggle for the internal keys enabler param.
			string s2 = "Keys Enabler \n\nwill allow some \ninternal key commands.\n\n";
			s2 += "Press ` to toggle the Minimizer state.\n";
			s2 += "Press L to toggle the Log Window visible.";
			ui.AddTooltip(s2); // a tooltip will be pinned to the previous widget!
			ui.AddSpacingSeparated();

			ui.AddAutoResizeToggle();
			ui.AddSpacing();
			ui.AddToggle("Constraints", bConstraint, OFX_IM_CHECKBOX);
		}

		ui.AddSpacingBigSeparated();

		//--

		static ofParameter<bool> bMin{ "##1", true };
		ui.AddMinimizerXsToggle(bMin);
		if (!bMin)
		{
			ui.Add(bEnable, OFX_IM_TOGGLE_BIG_BORDER_BLINK); // blinks when true

			s = "Will enable:\n\n";
			s += "1. Bigger font\n";
			s += "   (on above HELP text)\n";
			s += "2. Blink text\n";
			s += "3. Show/hide bottom widgets\n";
			s += "4. When Enabled is false, \nSpeed will be deactivated";
			ui.AddTooltip(s);

			ui.AddSpacingBigSeparated();

			// Two different presentations depending if minimized or not
			if (ui.isMinimized()) // Minimized
			{
				ui.Add(speed, OFX_IM_HSLIDER_SMALL_NO_LABELS); // smaller with no name and no value number
				ui.AddTooltip(speed, true, false); // tool-tip with name and value
				ui.AddSpacingDouble();

				// make font bigger
				if (bEnable) ui.PushFontStyle(OFX_IM_FONT_BIG);
				ui.AddTooltipHelp(s);
				if (bEnable) ui.PopFontStyle();
			}
			else // Maximized (aka not minimized)
			{
				// make it uppercase and add an extra space (true, true)
				if (bEnable) ui.AddLabelHuge("00_HelloWorld2", true, true);
				else ui.AddLabelBig("00_HelloWorld2", true, true);

				ui.AddSpacingDouble();

				// make it blink
				if (bEnable) ui.BeginBlinkText();
				// make font bigger
				if (bEnable) ui.PushFontStyle(OFX_IM_FONT_BIG);

				ui.AddLabel(s);

				if (bEnable) ui.PopFontStyle();
				if (bEnable) ui.EndBlinkText();

				ui.AddSpacingBigSeparated();

				if (!bEnable) {
					ui.PushInactive();
					ui.Add(speed, OFX_IM_HSLIDER);
					ui.PopInactive();
					s = "Widget is deactivated\nwhen Enabled is false\nSo can not be touched.";
					ui.AddLabel(s);
				}
				else {
					ui.Add(speed, OFX_IM_HSLIDER);
					s = "Widget is activated\nwhen Enabled\nSo it can be touched.";
					ui.AddTooltip(s);
				}

				// Raw imgui 
				float speed_ = speed;
				if (ImGui::SliderFloat("Speed", &speed_, 0, 1)) {
					speed = speed_;
				}

				//--

				if (bEnable)
				{
					ui.AddSpacing();
					ui.AddSpacingSeparated();
					ui.AddSpacingDouble();

					// A right aligned extra minimizer
					// but using a local bool param.
					// not that is not stored into settings file,
					// but other internal toggles it does!
					static ofParameter<bool> bMin{ "##2", true };
					ui.AddMinimizerXsToggle(bMin);
					if (!bMin)
					{
						ui.AddGroup(params, SurfingGuiGroupStyle_Collapsed); // collapsed on startup
					}
				}
			}
		}

		//--

		ui.AddSpacingBigSeparated();

		ui.AddToggle("Quat", bGui_Quat, OFX_IM_TOGGLE_BIG);
		ui.Add(bGui_Tabs, OFX_IM_TOGGLE_BIG);
		ui.Add(bGui_Combos, OFX_IM_TOGGLE_BIG);

		//--

		if (ui.isMaximized()) {
			ui.AddSpacingBigSeparated();

			ui.DrawWidgetsResetUI();//populate ResetUI button directly.
			//ui.resetUISettings();//exposed method.
		}

		//--

		//TODO: 
		// Testing animations/tween
		ui.AddSpacingBigSeparated();

		static bool enable_animation = 1;
		ImGui::Checkbox("Animation", &enable_animation);

		float w = ui.getWidgetsWidth();
		float h = 30;

		float trickFloat = ImTricks::Animations::FastLerpFloat("trickFloat", enable_animation, 0.f, 1.f, 0.05f);
		ImColor colorLerped = ImTricks::Animations::FastColorLerp(ImColor(255, 0, 0), ImColor(0, 255, 0), trickFloat);

		ui.AddSpacingY(ui.getWidgetsSpacingY());
		auto p = ImGui::GetCursorScreenPos();
		float rounding = 4;
		ImGui::GetWindowDrawList()->AddRectFilled(p, p + ImVec2(w, h), colorLerped, rounding);
		ui.AddSpacingY(h);

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawGuiTabs()
{
	if (bGui_Tabs) {
		ImGui::SetNextWindowSize({ 200,200 }, ImGuiCond_FirstUseEver);
	}
	if (ui.BeginWindow(bGui_Tabs))
	{
		if (ui.isMaximized() && ui.bDebug) tabs.drawEditor();

		//IMGUI_SUGAR__DEBUG_POINT(ofColor::orange);

		tabs.BeginTabBar("OF_APP");
		{
			////TODO: fixing bottom line
			//IMGUI_SUGAR__DEBUG_POINT(ofColor::orange);
			//auto p0 = ImGui::GetCursorScreenPos();
			//auto p1 = p0 + ImVec2{0, (float)tabs.customItemSpacing.get().y};
			////auto p1 = p0 + ImVec2{0, ui.getWidgetsHeightUnit()};
			////p1 = p1 - ImVec2{0, (float)tabs.customItemSpacing.get().y};
			//IMGUI_SUGAR__DEBUG_POINT(ofColor::blue, p1);

			if (tabs.BeginTabItem("Tab0"))
			{
				ImGui::Text("hello0");
				static float v0 = 0;
				ImGui::SliderFloat("slider", &v0, 0, 1);
				ImGui::Text("hello0");
				ImGui::Text("Stage Manager");
				ImGui::SameLine();
				ImGui::Button("button");
				ui.AddLabelBig("hello0");

				tabs.EndTabItem(0);
			}

			//IMGUI_SUGAR__DEBUG_POINT(ofColor::orange);
			if (tabs.BeginTabItem("Tab1"))
			{
				ui.AddLabelBig("hello1");
				static float v1 = 0;
				ImGui::SliderFloat("slider1", &v1, 0, 1);
				ImGui::Text("hello1");
				ImGui::SameLine();
				ImGui::Text("Network Adapter");
				ImGui::Text("hello1");
				ImGui::Button("button");

				tabs.EndTabItem(1);
			}

			if (tabs.BeginTabItem("Tab2"))
			{
				ImGui::Text("hello2");
				ImGui::Button("button");
				ImGui::Text("License");
				ImGui::SameLine();
				ui.AddLabelBig("hello2");
				static float v2 = 0;
				ImGui::SliderFloat("slider2", &v2, 0, 1);

				tabs.EndTabItem(2);
			}
		}
		tabs.EndTabBar();

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawGuiCombos()
{
	if (ui.BeginWindow(bGui_Combos)) {

		// Debug combo
		ui.Add(index);
		ui.AddLabelBig("Names");
		for (size_t i = 0; i < names.size(); i++)
		{
			string s = "#" + ofToString(i) + " " + names[i];
			if (i == index) ui.AddLabelBig(s);
			else ui.AddLabel(s);
		}
		ui.AddSpacing();

		string s = "hello";

		ui.AddCombo(index, names);
		ui.AddTooltipHelp(s);

		ui.EndWindow();
	}
}

//--------------------------------------------------------------
void ofApp::drawGuiQuat()
{
	// This is a raw ImGui window
	if (bGui_Quat)
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		if (ui.bAutoResize) flags += ImGuiWindowFlags_AlwaysAutoResize;

		if (ImGui::Begin("Test Quaternions", &bGui_Quat, flags))
		{
			string s;

			ui.AddLabelBig("Quaternion");
			s = "ofParameter<glm::quat> \n\t"
				"curRot{\"QuatRot\", \n\t"
				"glm::quat(0, 1, 0, 0), \n\t"
				"glm::quat(-1, -1, -1, -1), \n\t"
				"glm::quat(1, 1, 1, 1)};";
			ui.AddLabelBig(s);
			ui.AddSpacingBigSeparated();

			s = "ui.Add(curRot);";
			ui.AddLabelBig(s);
			ui.Add(curRot);
			ui.AddSpacingBigSeparated();

			s = "ui.Add(curRot, \n\tOFX_IM_MULTIDIM"
				"\n\t_SPLIT_SLIDERS);";
			ui.AddLabelBig(s);
			ui.Add(curRot, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
			ui.AddSpacingBigSeparated();

			s = "ui.Add(curRot, \n\tOFX_IM_MULTIDIM"
				"\n\t_SPLIT_SLIDERS\n\t_FOLDERED);";
			ui.AddLabelBig(s);
			ui.Add(curRot, OFX_IM_MULTIDIM_SPLIT_SLIDERS_FOLDERED);
		}
		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ui.AddToLog("KEY: " + ofToString(char(key)), "WARNING");

	if (key == ' ') bGui = !bGui;
	if (key == 'f') ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (ui.isMouseOverGui()) return; // don't log if we are touching the ui

	lastMouse = glm::vec2(x, y);

	string sb = "";
	if (button == 0) sb = "LEFT";
	else if (button == 2) sb = "RIGHT";
	string s = "Mouse Click " + ofToString(x) + "," + ofToString(y) + " " + sb;

	ui.AddToLog(s, myTag2);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	if (ui.isMouseOverGui()) return; // don't log if we are touching the ui

	glm::vec2 mouse(x, y);
	glm::quat yRot = glm::angleAxis(ofDegToRad(x - lastMouse.x) * dampen, glm::vec3(0, 1, 0));
	glm::quat xRot = glm::angleAxis(ofDegToRad(y - lastMouse.y) * dampen, glm::vec3(-1, 0, 0));
	curRot.set(xRot * yRot * curRot.get());
	lastMouse = mouse;

	string s = "Mouse Drag  " + ofToString(x) + "," + ofToString(y);

	ui.AddToLog(s, "VERBOSE");
}

//--------------------------------------------------------------
void ofApp::exit()
{
	ui.saveSettings(); // manually save the internal settings on exit
}

//--------------------------------------------------------------
void ofApp::drawSceneQuat() {
	ofPushStyle();
	ofSetColor(ofColor::white, 16);
	ofNoFill();
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 40);
	auto axis = glm::axis(curRot.get());
	ofRotateDeg(ofRadToDeg(glm::angle(curRot.get())), axis.x, axis.y, axis.z);
	ofDrawSphere(0, 0, 0, 200);
	ofPopMatrix();
	ofPopStyle();
}