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

	//-

	// font
	auto &io = ImGui::GetIO();
	auto normalCharRanges = io.Fonts->GetGlyphRangesDefault();

	std::string fontName;
	float fontSize;
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
	params.setName("paramsGroup1");// main container
	params2.setName("paramsGroup2");// nested
	params3.setName("paramsGroup3");// nested
	params.add(indexPreset.set("Preset", 0, 0, 8));
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
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params2.add(params3);
	params.add(params2);

	listener = indexPreset.newListener([this](int &i) {
		ofLogNotice("loadGradient: ") << i;
		loadGradient(indexPreset);
	});

	//--

	// gradient
	gradient.getMarks().clear();
	gradient.addMark(0.0f, ImColor(ofColor(0)));
	gradient.addMark(1.0f, ImColor(ofColor(255)));
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(color);

	//-

	gui.begin();
	{
		ImGuiColorEditFlags _flagw;
		string name;
		{
			// surfing widgets 1
			_flagw = ImGuiWindowFlags_None;
			name = "SurfingWidgets 1";
			ImGui::Begin(name.c_str(), NULL, _flagw);
			{
				draw_SurfingWidgets1();
			}
			ImGui::End();

			// surfing widgets 2
			_flagw = ImGuiWindowFlags_None;
			name = "SurfingWidgets 2";
			ImGui::Begin(name.c_str(), NULL, _flagw);
			{
				draw_SurfingWidgets2();
			}
			ImGui::End();
		}
	}
	gui.end();
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets1() {

	// Common width sizes from 1 (_w100) to 4 (_w25) widgets per row
	// Precalculate common widgets % sizes to fit current window "to be responsive"
	// we will update the sizes on any gui drawing point, like inside a new foldered sub-window that could be indendeted and full size is being smaller.
	// Internally takes care of ImGui spacing between widgets.
	float _w100;
	float _w50;
	float _w33;
	float _w25;
	float _h;
	_w100 = ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
	_w50 = ofxImGuiSurfing::getWidgetsWidth(2);  // 2 widgets half width
	_w33 = ofxImGuiSurfing::getWidgetsWidth(3);  // 3 widgets third width
	_w25 = ofxImGuiSurfing::getWidgetsWidth(4);  // 4 widgets quarter width
	_h = WIDGETS_HEIGHT;

	//--

	// 1. An in index selector with a clickable preset matrix
	{
		bool bOpen = true;
		ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
		_flagt |= ImGuiTreeNodeFlags_Framed;
		if (ImGui::TreeNodeEx("An Index Selector", _flagt))
		{
			// 1.1 Two buttons on same line
			if (ImGui::Button("<", ImVec2(_w50, _h / 2)))
			{
				indexPreset--;
				indexPreset = ofClamp(indexPreset, indexPreset.getMin(), indexPreset.getMax()); // clamp parameter
			}
			ImGui::SameLine();
			if (ImGui::Button(">", ImVec2(_w50, _h / 2)))
			{
				indexPreset++;
				indexPreset = ofClamp(indexPreset, indexPreset.getMin(), indexPreset.getMax()); // clamp parameter
			}

			// 1.2 Slider: the master int ofParam!
			ofxImGuiSurfing::AddParameter(indexPreset);
			ofxImGuiSurfing::HelpMarker("The master int ofParam!");

			// 1.3 Matrix button clicker
			AddMatrixClicker(indexPreset, true, 3); // responsive with 3 widgets per row

			// 1.4 Spin arrows
			int intSpin = indexPreset;
			if (ofxImGuiSurfing::SpinInt("SpinInt", &intSpin))
			{
				intSpin = ofClamp(intSpin, indexPreset.getMin(), indexPreset.getMax()); // clamp to parameter
				indexPreset = intSpin;
			}

			// 1.5 A tooltip over prev widget
			if (ImGui::IsItemHovered()) {
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted("This is not an ofParam. Just an int!");
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			// 1.6 An external url link
			ofxImGuiSurfing::ObjectInfo("ofxSurfingImGui @ github.com", "https://github.com/moebiussurfing/ofxSurfingImGui");
			ImGui::TreePop();
		}
	}

	ImGui::Dummy(ImVec2(0, 10)); // spacing

	//--

	// 2. an ofParameterGroup

	ImGuiTreeNodeFlags flagst;
	flagst = ImGuiTreeNodeFlags_None;
	flagst |= ImGuiTreeNodeFlags_DefaultOpen;
	flagst |= ImGuiTreeNodeFlags_Framed;
	ofxImGuiSurfing::AddGroup(params3, flagst); // -> force to be expanded
	//ofxImGuiSurfing::AddGroup(params3); // -> by default appears collapsed
}

//--------------------------------------------------------------
void ofApp::draw_SurfingWidgets2()
{
	if (ImGui::TreeNode("ofParams Widgets"))
	{
		ofxImGuiSurfing::AddParameter(size2);
		ofxImGuiSurfing::AddParameter(amount2);
		ofxImGuiSurfing::AddParameter(separation3);

		ImGui::TreePop();
	}

	ImGui::Dummy(ImVec2(0, 10)); // spacing

	//--

	// A gradient color tool
	bool bOpen = true;
	ImGuiTreeNodeFlags _flagt = (bOpen ? ImGuiTreeNodeFlags_DefaultOpen : ImGuiTreeNodeFlags_None);
	_flagt |= ImGuiTreeNodeFlags_Framed;

	if (ImGui::TreeNodeEx("A Gradient Widget", _flagt))
	{
		float _h = WIDGETS_HEIGHT;
		float _w100 = ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
		float _w50 = ofxImGuiSurfing::getWidgetsWidth(2);  // 2 widgets half width
		float _w33 = ofxImGuiSurfing::getWidgetsWidth(3);  // 3 widgets per row

		//-

		static bool bEditGrad = false;
		if (ImGui::GradientButton(&gradient))
		{
			//set show editor flag to true/false
			bEditGrad = !bEditGrad;
		}

		//::EDITOR::
		if (bEditGrad)
		{
			static ImGradientMark* draggingMark = nullptr;
			static ImGradientMark* selectedMark = nullptr;

			bool updated = ImGui::GradientEditor(&gradient, draggingMark, selectedMark);
		}

		//-

		ImGui::Dummy(ImVec2(0, 5)); // spacing

		// selector
		ImGui::PushItemWidth(_w50); // make smaller bc too long label
		if (ImGui::SliderFloat("SELECT COLOR PERCENT", &prcGrad, 0, 1))
		{
			//::GET A COLOR::
			float _color[3];
			gradient.getColorAt(prcGrad, _color); // position from 0 to 1
			color.set(_color[0], _color[1], _color[2], 1.0f);
		}
		ImGui::PopItemWidth();

		ImGui::Dummy(ImVec2(0, 5)); // spacing

		//// presets
		//if (ImGui::Button("Gradient1", ImVec2(_w33, _h / 2)))
		//{
		//	indexPreset = 0;
		//}
		//ImGui::SameLine();
		//if (ImGui::Button("Gradient2", ImVec2(_w33, _h / 2)))
		//{
		//	indexPreset = 2;
		//}
		//ImGui::SameLine();
		//if (ImGui::Button("Gradient3", ImVec2(_w33, _h / 2)))
		//{
		//	indexPreset = 3;
		//}

		ImGui::TreePop();
	}
}

//--------------------------------------------------------------
void ofApp::loadGradient(int index) {

	int i = index; 

	if (i == 0) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::blue));
		gradient.addMark(0.3f, ImColor(ofColor::blueViolet));
		gradient.addMark(0.6f, ImColor(ofColor::yellow));
		gradient.addMark(1.0f, ImColor(ofColor::orangeRed));
	}
	else if (i == 1) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(0xA0, 0x79, 0x3D));
		//gradient.addMark(0.2f, ImColor(0xAA, 0x83, 0x47));
		gradient.addMark(0.3f, ImColor(0xB4, 0x8D, 0x51));
		//gradient.addMark(0.4f, ImColor(0xBE, 0x97, 0x5B));
		//gradient.addMark(0.6f, ImColor(0xC8, 0xA1, 0x65));
		gradient.addMark(0.7f, ImColor(0xD2, 0xAB, 0x6F));
		gradient.addMark(0.8f, ImColor(0xDC, 0xB5, 0x79));
		gradient.addMark(1.0f, ImColor(0xE6, 0xBF, 0x83));
	}
	else if (i == 2) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::red));
		gradient.addMark(0.3f, ImColor(ofColor::yellowGreen));
		gradient.addMark(1.0f, ImColor(ofColor::green));
	}
	else if (i == 3) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::blueSteel));
		gradient.addMark(0.3f, ImColor(ofColor::blueViolet));
		gradient.addMark(0.7f, ImColor(ofColor::cornflowerBlue));
		gradient.addMark(1.0f, ImColor(ofColor::cadetBlue));
	}
	else if (i == 4) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::yellow));
		gradient.addMark(0.5f, ImColor(ofColor::lightYellow));
		gradient.addMark(1.0f, ImColor(ofColor::lightGoldenRodYellow));
	}
	else if (i == 5) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::red));
		gradient.addMark(0.5f, ImColor(ofColor::orangeRed));
		gradient.addMark(1.0f, ImColor(ofColor::blueViolet));
	}
	else if (i == 6) {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::lightYellow));
		gradient.addMark(0.5f, ImColor(ofColor::floralWhite));
		gradient.addMark(1.0f, ImColor(ofColor::whiteSmoke));
	}

	// repeat some if index is too big. just for testing..
	else {
		gradient.getMarks().clear();
		gradient.addMark(0.0f, ImColor(ofColor::paleVioletRed));
		gradient.addMark(0.3f, ImColor(ofColor::red));
		gradient.addMark(0.7f, ImColor(ofColor::darkRed));
		gradient.addMark(1.0f, ImColor(ofColor::black));
	}

	//refresh
	float _color[3];
	gradient.getColorAt(prcGrad, _color); // position from 0 to 1
	color.set(_color[0], _color[1], _color[2], 1.0f);
}