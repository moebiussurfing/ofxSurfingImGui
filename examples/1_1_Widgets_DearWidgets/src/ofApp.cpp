#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup_ImGui()
{
	ImGuiConfigFlags flags = ImGuiConfigFlags_DockingEnable;
	bool bRestore = true;
	bool bMouse = false;

	bool bAutoDraw = true;
	// NOTE: it seems that must be false when multiple ImGui instances created!

	gui.setup(nullptr, bAutoDraw, flags, bRestore, bMouse);

	auto &io = ImGui::GetIO();
	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();

	//-

	// font
	std::string fontName;
	float fontSize;

	//fontSize = 11;
	//fontName = "telegrama_render.otf";

	fontSize = 16;
	fontName = "overpass-mono-bold.otf";

	std::string _path = "assets/fonts/"; // assets folder
	ofFile fileToRead(_path + fontName); // a file that exists
	bool b = fileToRead.exists();
	if (b) {
		customFont = gui.addFont(_path + fontName, fontSize, nullptr, normalCharRanges);
	}
	if (customFont != nullptr) io.FontDefault = customFont;

	//-

	// theme
	ofxImGuiSurfing::ImGui_ThemeMoebiusSurfing();
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	setup_ImGui();

	// parameters
	params.setName("paramsGroup");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable1.set("Enable1", false));
	params.add(bEnable2.set("Enable2", false));
	params.add(bEnable3.set("Enable3", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params2.add(params3);
	params.add(params2);
}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.begin();
	{
		ImGuiColorEditFlags _flagw;
		string name;

		//ofxImGuiSurfing::AddBigToggle(bEnable1, 100, 50, true);

		//--

		//if (0)
		{

			// 1. dear widgets

			_flagw = ImGuiWindowFlags_None;
			name = "DearWidgets Ranges";
			ImGui::Begin(name.c_str(), NULL, _flagw);
			{
				draw_DearWidgets();
			}
			ImGui::End();

			_flagw = ImGuiWindowFlags_None;
			name = "DearWidgets Colors";
			ImGui::Begin(name.c_str(), NULL, _flagw);
			{
				draw_DearWidgetsColors();
			}
			ImGui::End();

			//TODO:
			//raw demo.h from DearWidgets
			//mostly ported but some errors like c++17 related and others
			//_flagw = ImGuiWindowFlags_None;
			//name = "DearWidgets_ShowDemo";
			//if (ofxImGui::BeginWindow(name.c_str(), mainSettings, _flagw))
			//{
			//	ImWidgets::ShowDemo();
			//}
			//ofxImGui::EndWindow(mainSettings);

			//--

			// 2. surfing widgets
			_flagw = ImGuiWindowFlags_None;
			name = "SurfingWidgets";
			ImGui::Begin(name.c_str(), NULL, _flagw);
			{
				draw_SurfingWidgets();
			}
			ImGui::End();

			//--

			// TESTING MORE WIDGETS
			draw_MoreWidgets();
		}
	}
	gui.end();
}

//--------------------------------------------------------------
void ofApp::draw_DearWidgets() {

	// Dear Widgets
	// raw ImGui code
	{
		static const float fZero = 0.0f;
		static float length = 16.0f;
		static ImWidgets::ImWidgetsLengthUnit currentUnit = ImWidgets::ImWidgetsLengthUnit_Metric;
		ImWidgets::DragLengthScalar("DragLengthScalar", ImGuiDataType_Float, &length, &currentUnit, 1.0f, &fZero, nullptr, ImGuiSliderFlags_None);
	}
	{
		static ImVec2 slider2D;
		ImVec2 boundMin(-1.0f, -1.0f);
		ImVec2 boundMax(1.0f, 1.0f);
		ImWidgets::Slider2DFloat("Slider 2D Float", &slider2D.x, &slider2D.y, boundMin.x, boundMax.x, boundMin.y, boundMax.y, 0.75f);
	}
	{
		static int curX = 0;
		static int curY = 0;
		int minX = -5;
		int minY = -5;
		int maxX = 5;
		int maxY = 5;
		ImWidgets::Slider2DInt("Slider 2D Int", &curX, &curY, &minX, &maxX, &minY, &maxY, 0.75f);
	}
	{
		static ImVec2 min(-0.5f, -0.5f);
		static ImVec2 max(0.5f, 0.5f);

		ImWidgets::RangeSelect2D("Range Select 2D", &min.x, &min.y, &max.x, &max.y, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f);
	}
	{
		static ImVec4 cur3D;
		ImVec4 boundMin(-1.0f, -1.0f, -1.0f, 0.0f);
		ImVec4 boundMax(1.0f, 1.0f, 1.0f, 0.0f);
		ImWidgets::SliderScalar3D("Slider 3D Float", &cur3D.x, &cur3D.y, &cur3D.z,
			boundMin.x, boundMax.x,
			boundMin.y, boundMax.y,
			boundMin.z, boundMax.z,
			0.75f);
	}
	{
		float const width = ImGui::GetContentRegionAvail().x;
		ImVec2 curPos = ImGui::GetCursorScreenPos();
		ImVec2 center = curPos + ImVec2(width, width) * ImVec2(0.5f, 0.5f);
		ImGui::Dummy(ImVec2(width, width));
		static float fZero = 0.0f;
		static float fOne = 1.0f;
		static float fValue = 0.5f;
		for (int i = 0; i < 6; ++i)
		{
			float const fI = (float)i;
			float const cos0 = ImCos(fI * 2.0f * IM_PI / 6.0f);
			float const sin0 = ImSin(fI * 2.0f * IM_PI / 6.0f);

			ImVec2 dir = ImVec2(cos0, sin0);

			ImGui::PushID(i);
			ImWidgets::LineSlider("##LineSliderValue",
				center + dir * ImVec2(32.0f, 32.0f),
				center + dir * ImVec2(width * 0.5f, width * 0.5f),
				IM_COL32(255, 128, 0, 255), ImGuiDataType_Float, &fValue, &fZero, &fOne, ImWidgets::ImWidgetsPointer_Up);
			ImGui::PopID();
		}
		ImGui::SliderFloat("##LineSliderSlodersdgf", &fValue, fZero, fOne);
	}
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets() {

	// NOTE:
	// auto mainSettings = ofxImGui::Settings();
	// Is only required when using window management from ofxImGui::BeginWindow(.. 

	// common width sizes from 1 (_w100) to 4 (_w25) widgets per row
	float _w100;
	float _w50;
	float _w33;
	float _w25;
	float _h;

	// Precalculate common widgets % sizes to fit current window "to be responsive"
	// we will update the sizes on any gui drawing point, like inside a new foldered sub-window that could be indendeted and full size is being smaller.

	// MODE A
	// (Takes care of ImGui spacing between widgets)
	_w100 = ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
	_w50 = ofxImGuiSurfing::getWidgetsWidth(2);  // 2 widgets half width
	_w33 = ofxImGuiSurfing::getWidgetsWidth(3);  // 3 widgets third width
	_w25 = ofxImGuiSurfing::getWidgetsWidth(4);  // 4 widgets quarter width
	_h = WIDGETS_HEIGHT;

	//// MODE B
	//// that's for update all the size using one single line. Useful if you use several sizes and multiple times, or with too much widh changes on your layout..
	//float _spcx;
	//float _spcy;
	//float _w100;
	//float _h100;
	//float _w99;
	//float _w50;
	//float _w33;
	//float _w25;
	//float _h;
	//ofxImGuiSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

	//-

	// 1. an ofParameterGroup
	ofxImGuiSurfing::AddGroup(params3);
	// -> NOTICE that when using ofxGui helpers, ofxImGui::AddGroup must be inside of:
	// if (ofxImGui::BeginWindow(name.c_str(), mainSettings, _flagw)){..}ofxImGui::EndWindow(mainSettings);

	ImGui::Dummy(ImVec2(0.0f, 2.0f));// spacing

	//-

	// 2. ranges using float types

	// range_slider.h
	static float v1 = 0;
	static float v2 = 1;
	static float v_min = 0;
	static float v_max = 1;
	static float v3 = 0;
	static float v4 = 1;
	ofxImGuiSurfing::RangeSliderFloat("range 1", &v1, &v2, v_min, v_max, "%.1f  %.1f", 1.0f);
	ofxImGuiSurfing::RangeSliderFloat("range 2", &v3, &v4, v_min, v_max);

	// vanilla ranges
	static float begin = 10, end = 90;
	static int begin_i = 100, end_i = 1000;
	ImGui::DragFloatRange2("range", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
	ImGui::DragIntRange2("range int", &begin_i, &end_i, 5, 0, 0, "%.0fcm", "%.0fcm");

	//-ofxImGuiSurfing::getImGui_WidgetWidth

	// 3. toggle buttons using ofParameter<bool>

	// add big toggle full width
	ofxImGuiSurfing::AddBigToggle(bEnable1, _w100, _h / 2);
	ofxImGuiSurfing::AddBigToggle(bEnable2, _w50, _h);
	ImGui::SameLine();
	ofxImGuiSurfing::AddBigToggle(bEnable3, _w50, _h);

	ImGui::Dummy(ImVec2(0.0f, 2.0f));// spacing

	// 4. a params group
	ofxImGuiSurfing::AddGroup(params2);
	//ofxImGui::AddGroup(params2, mainSettings);
	// -> notice that when using ofxGui helpers, ofxImGui::AddGroup must be inside of:
	// if (ofxImGui::BeginWindow(name.c_str(), mainSettings, _flagw)){..}ofxImGui::EndWindow(mainSettings);

	// 5. Two buttons on same line
	if (ofxImGuiSurfing::AddBigButton(bPrevious, _w50, _h)) {
		bPrevious = false;
	}
	ImGui::SameLine();
	ofxImGuiSurfing::AddBigButton(bNext, _w50, _h);
	ImGui::Dummy(ImVec2(0.0f, 5.0f));// spacing

	// 6. Full width buttons. half height
	if (ImGui::Button("RANDOMIZE!", ImVec2(_w100, _h / 2)))
	{
	}
	if (ImGui::Button("RESET", ImVec2(_w100, _h / 2)))
	{
	}

	//--

	//// 7. Another params group. (Will crash here)
	//// This only works inside ofxImGui::BeginWindow(..
	//// but using the old ofxImGui helpers
	//// that I have deprecated on my projects.
	//// reasons to deprecate:
	//// - lost of layout ini handling
	//// - avoid ofxImGui::Settings() to simplify
	//auto mainSettings = ofxImGui::Settings();
	//ofxImGui::AddGroup(params, mainSettings);

	//--

	// 8. some buttons in a row

	// Update sizes
	// Is not required if (since the last time was calculated) the panel window width didn't changed. 
	_w100 = ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
	_w50 = ofxImGuiSurfing::getWidgetsWidth(2);  // 2 widgets half width
	_w33 = ofxImGuiSurfing::getWidgetsWidth(3);  // 3 widgets third width
	_w25 = ofxImGuiSurfing::getWidgetsWidth(4);  // 4 widgets quarter width

	static int amnt = 2;
	ImGui::SliderInt("Amount Buttons", &amnt, 1, 4);
	float w;
	if (amnt == 1) w = _w100;
	else if (amnt == 2) w = _w50;
	else if (amnt == 3) w = _w33;
	else if (amnt == 4) w = _w25;
	for (int i = 1; i <= amnt; i++) {
		string n = "Button_" + ofToString(i);
		if (ImGui::Button(n.c_str(), ImVec2(w, _h)))
		{
		}
		if (i != amnt) ImGui::SameLine();
	}

	// 9. Spacing
	ImGui::Dummy(ImVec2(0.0f, 5.0f));

	// 10. Three widgets using another width-layouting approach
	float _hh = 60;
	if (ImGui::Button("b1", ImVec2(_w33, _hh))) {}
	ImGui::SameLine();
	if (ImGui::Button("b2", ImVec2(_w33, _hh))) {}
	ImGui::SameLine();
	if (ImGui::Button("b3", ImVec2(_w33, _hh))) {}

	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	//----
}

//--------------------------------------------------------------
void ofApp::draw_MoreWidgets()
{
	if (ImGui::TreeNode("TEST More Widgets"))
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		// knob1
		//TODO:broken mouse..
		ofxImGuiSurfing::AddKnob(lineWidth, 0.001, 30, 0.1);

		//// knob2
		//ImGui::SameLine();
		//const ImU32 color = ImGui::GetColorU32(ImGuiCol_ButtonActive);
		//float width = 30;
		//float v_min = 0;
		//float v_max = 1;
		//float v_step = 0.001f;
		//static float p_value = 0.5f;
		//ofxImGuiSurfing::KnobFloat(draw_list, width, color, "Value", &p_value, v_min, v_max, v_step);

		//// knob crash
		//float v0 = 0;
		////float *p_value = &v0;
		////static float v = 0;
		////static float v_min = 0.0f;
		////static float v_max = 100.0f;
		//////bool KnobFloat(ImDrawList* draw_list, float width, ImU32 color, const char* label, float* p_value, float v_min, float v_max, float v_step = 50.f);
		//ofxImGuiSurfing::KnobFloat(draw_list, 30, color, "myKnob", &p_value, v_min, v_max, 50);

		//// pad - not working
		////bool Pad2D(ImDrawList* drawList, float width, float height, float *_x, float *_y);
		//static float _x = 50;
		//static float _y = 50;
		////ofxImGuiSurfing::Pad2D(draw_list, 100, 100, &_x, &_y);
		//if (ofxImGuiSurfing::Pad2D(draw_list, 100, 100, &_x, &_y)) {
		//	cout << "XPOS " << _x;
		//	cout << "YPOS " << _y;
		//}

		ofxImGuiSurfing::drawTimecode(draw_list, ofGetElapsedTimef());
		ofxImGuiSurfing::HelpMarker("Urbs, Virus y Bits se propone como un piloto de lo que imaginamos como una escuela que se aproxime a la ciudad desde las humanidades ambientales. Propone un acercamiento a las humanidades ambientales desde las prácticas digitales, artísticas y de invención de ciudad, respondiendo a los desafíos climáticos y de justicia ambiental.");
		ofxImGuiSurfing::ObjectInfo("Open URL Info", "http://google.com");

		ImGui::TextWrapped(
			"This text should automatically wrap on the edge of the window. The current implementation "
			"for text wrapping follows simple rules suitable for English and possibly other languages.");
		ImGui::Spacing();

		ImGui::TreePop();
	}
}

//--------------------------------------------------------------
void ofApp::draw_DearWidgetsColors()
{
	if (ImGui::TreeNode("Widgets"))
	{
		// -> use ImWidgets:: namespace for DearWidgets

		if (ImGui::TreeNode("Hue Selector"))
		{
			float const width = ImGui::GetContentRegionAvail().x;
			float const height = 32.0f;
			static float offset = 0.0f;

			static int division = 32;
			ImGui::DragInt("Division", &division, 1.0f, 2, 256);
			static float alphaHue = 1.0f;
			static float alphaHideHue = 0.125f;
			ImGui::DragFloat("Offset##ColorSelector", &offset, 0.0f, 0.0f, 1.0f);
			ImGui::DragFloat("Alpha Hue", &alphaHue, 0.0f, 0.0f, 1.0f);
			ImGui::DragFloat("Alpha Hue Hide", &alphaHideHue, 0.0f, 0.0f, 1.0f);
			static float hueCenter = 0.5f;
			static float hueWidth = 0.1f;
			static float featherLeft = 0.125f;
			static float featherRight = 0.125f;
			ImGui::DragFloat("featherLeft", &featherLeft, 0.0f, 0.0f, 0.5f);
			ImGui::DragFloat("featherRight", &featherRight, 0.0f, 0.0f, 0.5f);
			ImWidgets::HueSelector("Hue Selector", ImVec2(width, height), &hueCenter, &hueWidth, &featherLeft, &featherRight, division, alphaHue, alphaHideHue, offset);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Density Plot Nearest"))
		{
			ImWidgets::DensityPlotNearest("Dense SS N", [](float x, float y) -> float { return std::sin(x) * std::sin(y); }, 32, 32, -4.0f, 4.0f, -3.0f, 3.0f);
			ImWidgets::DensityPlotNearest("Dense S N", [](float x, float y) -> float { return std::sin(x * y); }, 32, 32, 0.0f, 4.0f, 0.0f, 4.0f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Density Plot Bilinear"))
		{
			ImWidgets::DensityPlotBilinear("Dense SS B", [](float x, float y) -> float { return std::sin(x) * std::sin(y); }, 32, 32, -4.0f, 4.0f, -3.0f, 3.0f);
			ImWidgets::DensityPlotBilinear("Dense S B", [](float x, float y) -> float { return std::sin(x * y); }, 32, 32, 0.0f, 4.0f, 0.0f, 4.0f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Isoline"))
		{
			static int resolution = 128;
			static float isoLines[] = { 0.0f, 0.5f, 0.95f, 1.0f };
			ImGui::SliderInt("Resolution", &resolution, 4, 512);
			static bool bShowSurface = true;
			ImGui::Checkbox("Show Surface", &bShowSurface);
			ImGui::Text("Isoline Values");
			float const width = ImGui::GetContentRegionAvail().x;
			ImGui::PushMultiItemsWidths(4, width);
			ImGui::DragFloat("##IsoLine0", &isoLines[0], 0.001f, -1.0f, 1.0f); ImGui::SameLine();
			ImGui::DragFloat("##IsoLine1", &isoLines[1], 0.001f, -1.0f, 1.0f); ImGui::SameLine();
			ImGui::DragFloat("##IsoLine2", &isoLines[2], 0.001f, -1.0f, 1.0f); ImGui::SameLine();
			ImGui::DragFloat("##IsoLine3", &isoLines[3], 0.001f, -1.0f, 1.0f);

			static ImU32 cols[] = { IM_COL32(255, 0, 0, 255), IM_COL32(255, 255, 0, 255), IM_COL32(255, 0, 255, 255), IM_COL32(0, 255, 0, 255) };
			ImGui::PushMultiItemsWidths(4, width);
			static ImVec4 col;
			col = ImGui::ColorConvertU32ToFloat4(cols[0]);
			if (ImGui::ColorEdit4("##IsoColor0", &col.x))
				cols[0] = ImGui::ColorConvertFloat4ToU32(col);
			ImGui::SameLine();

			col = ImGui::ColorConvertU32ToFloat4(cols[1]);
			if (ImGui::ColorEdit4("##IsoColor1", &col.x))
				cols[1] = ImGui::ColorConvertFloat4ToU32(col);
			ImGui::SameLine();

			col = ImGui::ColorConvertU32ToFloat4(cols[2]);
			if (ImGui::ColorEdit4("##IsoColor2", &col.x))
				cols[2] = ImGui::ColorConvertFloat4ToU32(col);
			ImGui::SameLine();

			col = ImGui::ColorConvertU32ToFloat4(cols[3]);
			if (ImGui::ColorEdit4("##IsoColor3", &col.x))
				cols[3] = ImGui::ColorConvertFloat4ToU32(col);

			ImWidgets::DensityIsolinePlotBilinear("IsoLine 0", [](float x, float y) -> float { return 1.01f * std::sin(x) * std::sin(y); }, bShowSurface, &isoLines[0], 4, &cols[0], 4, resolution, resolution, -4.0f, 4.0f, -3.0f, 3.0f);
			ImWidgets::DensityIsolinePlotBilinear("IsoLine 1", [](float x, float y) -> float { return 1.01f * std::sin(x * y); }, bShowSurface, &isoLines[0], 4, &cols[0], 4, resolution, resolution, -4.0f, 4.0f, -3.0f, 3.0f);

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Analytic Plot"))
		{
			float const width = ImGui::GetContentRegionAvail().x;
			ImGui::Text("ImGui::PlotLines: 128 samples");
			ImGui::Dummy(ImVec2(1.0f, ImGui::GetTextLineHeightWithSpacing()));
			ImGui::PlotLines("##PlotLines", [](void* data, int idx)
			{
				float const x = (((float)idx) / 127.0f) * 8.0f;
				return sin(x * x * x) * sin(x);
			}, nullptr, 128, 0, nullptr, FLT_MAX, FLT_MAX, ImVec2(width, width));
			ImGui::Dummy(ImVec2(1.0f, ImGui::GetTextLineHeightWithSpacing()));

			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 128, 0, 255));
			ImGui::TextWrapped("/!\\ Use carefully and at your risk, this widget can generate very quickly very high number of vertices.\nCondisider the override of ImDrawIdx to ImU32 in your build system.");
			ImGui::PopStyleColor();

			static int initSampleCount = 8;
			ImGui::DragInt("Init Samples Count", &initSampleCount, 1.0f, 4, 16);
			static float minX = 0.0f;
			static float maxX = 8.0f;
			float fMaxX = maxX;
			float fMinX = minX;
			ImGui::DragFloat("Min X", &minX, 0.01f, 0.0f, fMaxX - 0.01f);
			ImGui::DragFloat("Max X", &maxX, 0.01f, fMinX + 0.01f, 16.0f);
			ImGui::Text("DearWidgets:Plot with Dynamic Resampling (Init Samples Count: 8)");
			ImGui::Dummy(ImVec2(1.0f, ImGui::GetTextLineHeightWithSpacing()));
			ImWidgets::AnalyticalPlot("Analytical", [](float const x) { return sin(x * x * x) * sin(x); }, minX, maxX, initSampleCount);
			ImGui::Dummy(ImVec2(1.0f, ImGui::GetTextLineHeightWithSpacing()));
			ImGui::Dummy(ImVec2(1.0f, ImGui::GetTextLineHeightWithSpacing()));

			ImGui::TreePop();
		}
		ImGui::TreePop();
	}

	//-

	if (ImGui::TreeNode("Alpha - Draft - Open Ideas mostly WIP"))
	{
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 128, 0, 255));
		ImGui::TextWrapped("/!\\ Use carefully and at your risk!");
		ImGui::TextWrapped("/!\\ API will change, that at 'first draft' stage.");
		ImGui::TextWrapped("/!\\ PR are welcome to contribute.");
		ImGui::PopStyleColor();

		if (ImGui::TreeNode("Draw"))
		{
			if (ImGui::TreeNode("Chromaticity Draw"))
			{
				static int chromLinesampleCount = 16;
				ImGui::SliderInt("Chromatic Sample Count", &chromLinesampleCount, 3, 256);
				static int resX = 16;
				ImGui::SliderInt("Resolution X", &resX, 3, 256);
				static int resY = 16;
				ImGui::SliderInt("Resolution Y", &resY, 3, 256);
				static int waveMin = 400;
				static int waveMax = 700;
				ImGui::SliderInt("Wavelength Min", &waveMin, 300, waveMax);
				ImGui::SliderInt("Wavelength Max", &waveMax, waveMin, 800);
				char const* observer[] = { "1931 2 deg", "1964 10 deg" };
				char const* illum[] = { "D50", "D65" };
				char const* colorSpace[] = { "AdobeRGB", "AppleRGB", "Best", "Beta", "Bruce", "CIERGB",
					"ColorMatch", "Don_RGB_4", "ECI","Ekta_Space_PS5", "NTSC",
					"PAL_SECAM", "ProPhoto", "SMPTE_C", "sRGB", "WideGamutRGB", "Rec2020" };
				static int curObserver = 0;
				static int curIllum = 1;
				static int curColorSpace = 0;
				ImGui::Combo("Observer", &curObserver, observer, IM_ARRAYSIZE(observer));
				ImGui::Combo("Illuminance", &curIllum, illum, IM_ARRAYSIZE(illum));
				ImGui::Combo("ColorSpace", &curColorSpace, colorSpace, IM_ARRAYSIZE(colorSpace));
				ImDrawList* pDrawList = ImGui::GetWindowDrawList();
				float const width = ImGui::GetContentRegionAvail().x;
				static ImVec4 vMaskColor(1.0f, 0.5f, 0.0f, 1.0f);
				ImGui::ColorEdit4("Mask Color", &vMaskColor.x);
				ImU32 maskColor = ImGui::ColorConvertFloat4ToU32(vMaskColor);

				static ImVec2 vMin(-0.2f, -0.1f);
				static ImVec2 vMax(1.0f, 1.0f);

				ImGui::PushMultiItemsWidths(2, width);
				ImGui::DragFloat("minX", &vMin.x, 0.001f, -1.0f, 0.0f); ImGui::SameLine();
				ImGui::DragFloat("minY", &vMin.y, 0.001f, -1.0f, 0.0f);

				ImGui::PushMultiItemsWidths(2, width);
				ImGui::DragFloat("maxX", &vMax.x, 0.001f, 1.0f, 2.0f); ImGui::SameLine();
				ImGui::DragFloat("maxY", &vMax.y, 0.001f, 1.0f, 2.0f);

				ImVec2 curPos = ImGui::GetCursorScreenPos();
				ImGui::InvisibleButton("##Zone", ImVec2(width, width), 0);
				ImWidgets::DrawChromaticPlotBilinear(
					pDrawList,
					curPos,
					width, width,
					chromLinesampleCount,
					curColorSpace,
					curObserver,
					curIllum,
					resX, resY,
					maskColor,
					waveMin, waveMax,
					vMin.x, vMax.x,
					vMin.y, vMax.y);

				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
}