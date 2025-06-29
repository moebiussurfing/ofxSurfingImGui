#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setupImGui()
{
	ui.setImGuiViewPort(true); // Allow floating window out the app window.

	//ui.setup();
	ui.setup(IM_GUI_MODE_INSTANTIATED_DOCKING_RAW);

	g.add(bGui_Headers);
	g.add(bGui_Bg);
	g.add(bGui_ResizePin);
	g.add(bGui_LockMove);
	g.add(bGui_Toggle);
	g.add(bGui_Button);
	g.add(bGui_Slider);

	bigTextInput.setHint("Type search");
}

//--------------------------------------------------------------
void ofApp::setup()
{
	setupImGui();

	//--

	ofxImGuiSurfing::loadGroup(g);
}

//--------------------------------------------------------------
void ofApp::update()
{
	
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawImGui();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			ui.DrawWidgetsGlobalScaleMini();
			
			ui.Add(ui.bGui_GameMode, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			ui.AddSpacingBigSeparated();

			ui.AddMinimizerToggle();
			if (ui.isMaximized()) {

				ui.AddLogToggle();
				ui.AddDebugToggle();
				ui.AddAutoResizeToggle();
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("Windows");
				ui.Add(bGui_Headers, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_Bg, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_ResizePin, OFX_IM_TOGGLE_ROUNDED);
				ui.Add(bGui_LockMove, OFX_IM_TOGGLE_ROUNDED);
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("Toggle");
				ui.Add(bGui_Toggle);
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("Buttons");
				ui.Add(bGui_Button);
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("Slider");
				ui.Add(bGui_Slider);
				if (bGui_Slider)
				{
					ui.Add(value);
					ImGui::Checkbox("Colorize", &bColorize);
					if (ui.AddButton("Reset"))
					{
						bResetSlider = 1;
					};
				}
				ui.AddSpacingBigSeparated();

				ui.AddLabelBig("InputText");
				ui.Add(bigTextInput.bGui);
				ui.Add(bigTextInput.bGui_Config);
			}

			ui.EndWindow();
		}

		drawImGui_Slider();
		drawImGui_Toggle();
		drawImGui_Button();
		bigTextInput.draw(ui);

		//--

		ImGui::SetNextWindowSize({ 400,400 }, ImGuiCond_FirstUseEver);

		if (ui.BeginWindow(ui.bGui_GameMode, window_flags))
		{
			// mannually dock here
			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::drawImGui_Slider()
{
	if (bResetSlider)
	{
		bResetSlider = 0;
		doResetSlider();
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(40, 200));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
		if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
		if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

		if (ui.BeginWindow(bGui_Slider, window_flags))
		{
			if (!bGui_Headers) AddHeaderHeight();

#if 0
			// markers zones
			float x1, x2, gap, yy, ww, hh;
			ww = ofxImGuiSurfing::getPanelWidth();
			hh = ofxImGuiSurfing::getPanelHeight();
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			ImVec2 p = ImGui::GetCursorScreenPos();
			float linew = 2.f;
			float linea = 0.15f;
			ImVec4 cm = ImVec4(0.0f, 0.0f, 0.0f, linea);

			gap = 10;
			ww -= 2 * gap;
			x1 = p.x + gap;
			x2 = x1 + ww;

			yy = p.y + 0.33 * hh;
			draw_list->AddLine(ImVec2(x1, yy), ImVec2(x2, yy), ImGui::GetColorU32(cm), linew);

			yy = p.y + 0.66 * hh;
			draw_list->AddLine(ImVec2(x1, yy), ImVec2(x2, yy), ImGui::GetColorU32(cm), linew);
#endif
			//--

			// v slider
			if (bColorize) {
				auto c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
				ImVec4 _cBg = ImVec4(c.x, c.y, c.z, c.w * 0.2);
				ImGui::PushStyleColor(ImGuiCol_SliderGrab, cRange);
				ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, cRangeRaw);
				ImGui::PushStyleColor(ImGuiCol_FrameBg, _cBg);
				ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _cBg);
				ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _cBg);
			}
			{
				ImVec2 sz = ImVec2(-1.f, -1.f);
				bool bNoName = true;
				bool bNoNumber = true;
				bool b = ofxImGuiSurfing::AddVSlider(value, sz, bNoName, bNoNumber);
				ofxImGuiSurfing::AddMouse(value);
				ui.AddTooltip(value);

				string s = ofToString(value.get(), 3);
				if (b) ui.AddToLog(s, OF_LOG_WARNING);
			}
			if (bColorize) ImGui::PopStyleColor(5);

			ui.EndWindow();
		}
	}
	ImGui::PopStyleVar();
}

//--------------------------------------------------------------
void ofApp::doResetSlider()
{
	float xx, yy, ww, hh, pad;

	pad = 20;
	ww = 200 - 2 * ImGui::GetStyle().WindowPadding.x;
	hh = ofGetHeight() - 2 * pad;
	xx = ofGetWidth() - ww - pad;
	yy = pad;

	ImGuiCond flagsCond = ImGuiCond_None;
	flagsCond |= ImGuiCond_FirstUseEver;
	flagsCond = ImGuiCond_None;

	ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
	ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
}

//--

//--------------------------------------------------------------
void ofApp::drawImGui_Toggle()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(40, 200));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
		if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
		if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

		if (ui.BeginWindow(bGui_Toggle, window_flags))
		{
			if (!bGui_Headers) AddHeaderHeight();

			float w = ofxImGuiSurfing::getPanelWidth();
			float h = ofxImGuiSurfing::getPanelHeight();
			ImVec2 sz = ImVec2(w, h);

			int iFont = ofMap(h, 0, ofGetHeight() * RATIO_WIDGETS_FONTS, 0, 3, true);
			ui.PushFontStyle(SurfingFontTypes(iFont));

			auto c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
			ImVec4 _cBg = ImVec4(c.x, c.y, c.z, c.w * 0.2);
			ImGui::PushStyleColor(ImGuiCol_SliderGrab, cRange);
			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, cRangeRaw);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _cBg);
			{
				bool _bBorder = true;
				bool _bBlink = true;
				ofxImGuiSurfing::AddBigToggle(bToggle, sz, _bBorder, _bBlink);
			}
			ImGui::PopStyleColor(5);

			ui.PopFontStyle();

			//--

			ui.EndWindow();
		}
	}
	ImGui::PopStyleVar();
}

//--------------------------------------------------------------
void ofApp::drawImGui_Button()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(40, 200));
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!bGui_Bg) window_flags |= ImGuiWindowFlags_NoBackground;
		//if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoDecoration;
		if (!bGui_Headers) window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (!bGui_ResizePin) window_flags |= ImGuiWindowFlags_NoResize;
		if (bGui_LockMove) window_flags |= ImGuiWindowFlags_NoMove;

		//BeginNoDecoration();

		if (ui.BeginWindow(bGui_Button, window_flags))
		{
			if (!bGui_Headers) AddHeaderHeight();

			float w = ofxImGuiSurfing::getPanelWidth();
			float h = ofxImGuiSurfing::getPanelHeight();
			ImVec2 sz = ImVec2(w, h);

			int iFont = ofMap(h, ofGetHeight()/2, ofGetHeight() * RATIO_WIDGETS_FONTS, 0, 3, true);
			ui.PushFontStyle(SurfingFontTypes(iFont));

			auto c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
			ImVec4 _cBg = ImVec4(c.x, c.y, c.z, c.w * 0.2);
			ImGui::PushStyleColor(ImGuiCol_SliderGrab, cRange);
			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, cRangeRaw);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, _cBg);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, _cBg);

			ui.BeginBlinkText();

			if (ofxImGuiSurfing::AddBigButton(vButton, sz))
			{
			}

			ui.EndBlinkText();

			ImGui::PopStyleColor(5);

			ui.PopFontStyle();

			ui.EndWindow();
		}

		//EndNoDecoration();
	}
	ImGui::PopStyleVar();
}

////--------------------------------------------------------------
//void ofApp::keyPressed(int key)
//{
//	if (ui.isMouseOverInputText()) return;
//	//if (ui.isOverGui()) return;
//
//	if (key == 'g') bGui = !bGui;
//	if (key == 'h') bGui_Headers = !bGui_Headers;
//	if (key == 'b') bGui_Bg = !bGui_Bg;
//	if (key == 'r') bGui_ResizePin = !bGui_ResizePin;
//	if (key == 'l') bGui_LockMove = !bGui_LockMove;
//}

//--------------------------------------------------------------
void ofApp::BeginNoDecoration()
{
	bool b = ui.bDebug;
	/*ImGuiWindowFlags*/ window_flags = ImGuiWindowFlags_None;
	if (b) {
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoDecoration;

		//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 20);

		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
		ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);

		//ImGui::PushStyleColor(ImGuiCol_Border, ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
	}
}

//--------------------------------------------------------------
void ofApp::EndNoDecoration()
{
	bool b = ui.bDebug;
	if (b) {

		//ImGui::PopStyleColor();

		ImGui::PopStyleColor(3);

		//ImGui::PopStyleVar();
	}
}

//--------------------------------------------------------------
void ofApp::exit(){
	
}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
	
}

//--------------------------------------------------------------
void ofApp::lostFocus(){
	
}

//--------------------------------------------------------------
void ofApp::gotFocus(){
	
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){
	
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
	
}

//--------------------------------------------------------------
void ofApp::launchedWithURL(std::string url){
	
}
