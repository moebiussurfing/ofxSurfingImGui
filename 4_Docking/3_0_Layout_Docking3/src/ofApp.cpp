#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	setupParams();

	//--

	// A.
	gui.setup(nullptr, false, ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable, true);
	//gui.setup(NULL, true, ImGuiConfigFlags_None, true, false);

	//--

	// B.
	setupImGuiManager();

	//--

	// C.
	guiInstance.setup();

	//--

	// D.
#define AMOUNT_INSTANCES 3
	for (int i = 0; i < AMOUNT_INSTANCES; i++) {
		addImGuiWindow();
	}

	//--

	// E.
	setupImGuiSpecialWindows();
}

//--------------------------------------------------------------
void ofApp::setupImGuiManager() {

#ifdef TEST__LOCAL_IM_GUI
	guiManager.setup(IM_GUI_MODE_NOT_INSTANTIATED); // -> must be inside a gui.begin()/end()
#endif

	//-

#ifdef TEST__MULTIINSTANCE_IM_GUI
	//guiManager.setup(); // -> requires guiManager.begin()/end()
	guiManager.setup(IM_GUI_MODE_INSTANTIATED); // -> requires guiManager.begin()/end()
#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//// log
	//if (ofGetFrameNum() % 120 == 0) {
	//	guiManager.log_RectWindows();
	//}

	// We manipulate vector out of the drawing context Begin/NewFrame...
	if (bFlagClear) {
		bFlagClear = false;
		clearImGuiWindows();
	}

	//--

	// Docking stuff: draws a rectangle to see the free space viewport on central dockspace
	gui.begin();
	setupDocking();
	gui.end();

	//--

	// A.
#ifdef TEST__LOCAL_IM_GUI
	gui.begin();
	{
		ImGui::Text("ofApp-ofxImGui");
		// one window
		ImGui::Begin("ofApp-TEST");
		static float value;
		ImGui::SliderFloat("value", &value, 0, 1);
		ImGui::End();

		// other windows
		drawImGui();
		// using the raw ImGui widgets without instantiate ImGui begin/end
		//guiManager.begin/end(); // if used begin/end it's bypassed internally when using .setup(IM_GUI_MODE_NOT_INSTANTIATED). can be uncommented
	}
	gui.end();
#endif

	//-

#ifdef TEST__MULTIINSTANCE_IM_GUI
	// one window
	// A.
	gui.begin();
	{
		ImGui::Begin("ofApp-ofxImGui");
		ImGui::Text("ofApp-ofxImGui");
		static float value;
		ImGui::SliderFloat("value", &value, 0, 1);
		ImGui::End();
	}
	gui.end();

	// B.
	// other windows
	guiManager.begin(); // bypassed when using IM_GUI_MODE_NOT_INSTANTIATED
	{
		drawImGui();
	}
	guiManager.end();
#endif

	//-

	// C.
	guiInstance.draw();

	//-

	// D.
	// add-on vector of guiManager windows (ofxSurfing_ImGui_Manager)
	for (auto &g : guiInstances) {
		g->draw();
	}

	//-

	// Some isolated windows
	gui.begin(); // -> Why it works without begin/end ??
	{
		// Draw a few windows
		static int val0 = 0, val1 = 0, val2 = 0, val3 = 0, val4 = 0, val5 = 0;
		drawWindow("ofApp-ofxImGui-DockableWindow", val0, 50, 100, ImGuiWindowFlags_None);
		drawWindow("ofApp-ofxImGui-Window1", val1, 300, 100, ImGuiWindowFlags_None);
		drawWindow("ofApp-ofxImGui-Window2", val2, 50, 350, ImGuiWindowFlags_None);
		drawWindow("ofApp-ofxImGui-Window3", val3, 300, 350, ImGuiWindowFlags_None);
		drawWindow("ofApp-ofxImGui-Window4", val4, 550, 100, ImGuiWindowFlags_None);
		ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID); // Attach a window to a viewport = prevent popping it out
		drawWindow("ofxImGui-Stuck in main window", val5, 550, 350, ImGuiWindowFlags_None);
	}
	gui.end();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(255, 255, 0, 128));

	// B.
	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

	guiManager.beginWindow("ofApp-guiManager", NULL, flags);
	{
		ImGui::Text("guiManager");
		AddToggleRoundedButton(guiManager.bAutoResize);
		static ofParameter<bool> bCustom{ "bCustom", false };
		AddToggleRoundedButton(bCustom);
		if (bCustom) ImGui::TextWrapped("Customized Style for the Group.");
		else ImGui::TextWrapped("Default Style for the Group.");
		static float value;
		ImGui::SliderFloat("value", &value, 0, 1);
	}
	guiManager.endWindow();

	//-

	drawImGuiGroup();

	ImGui::PopStyleColor(1);

	//-

	// E.
	drawImGuiSpecialWindows();
}

//--------------------------------------------------------------
void ofApp::setupImGuiSpecialWindows()
{
	guiManager.addWindowSpecial("mySpecialWin0");//index 0
	guiManager.addWindowSpecial("mySpecialWin1");//index 1
	guiManager.addWindowSpecial("mySpecialWin2");//index 2
	guiManager.addWindowSpecial("mySpecialWin3", true);//index 3 // -> powered toggle allows advanced controls
}

//--------------------------------------------------------------
void ofApp::drawImGuiSpecialWindows()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 255, 128)); // This styles the special windows

	if (guiManager.beginWindowSpecial())
	{
		static int _value = 0.5;
		ImGui::Text("guiManager-SpecialWin");
		ImGui::InputInt("InputInt", &_value);
		ImGui::SliderInt("SliderInt", &_value, 0, 10);
		ImGui::DragInt("DragInt", &_value);

		guiManager.endWindowSpecial();
	}

	if (guiManager.beginWindowSpecial())
	{
		static int _value = 0.5;
		ImGui::Text("guiManager-SpecialWin");
		ImGui::InputInt("InputInt", &_value);
		ImGui::SliderInt("SliderInt", &_value, 0, 10);
		ImGui::DragInt("DragInt", &_value);

		guiManager.endWindowSpecial();
	}

	if (guiManager.beginWindowSpecial())
	{
		static int _value = 0.5;
		ImGui::Text("guiManager-SpecialWin");
		ImGui::InputInt("InputInt", &_value);
		ImGui::SliderInt("SliderInt", &_value, 0, 10);
		ImGui::DragInt("DragInt", &_value);

		guiManager.endWindowSpecial();
	}

	if (guiManager.beginWindowSpecial())
	{
		static int _value = 0.5;
		ImGui::Text("guiManager-SpecialWin");
		ImGui::InputInt("InputInt", &_value);
		ImGui::SliderInt("SliderInt", &_value, 0, 10);
		ImGui::DragInt("DragInt", &_value);

		guiManager.endWindowSpecial();
	}

	ImGui::PopStyleColor(1);
}

//--------------------------------------------------------------
void ofApp::drawImGuiGroup()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

	guiManager.beginWindow("ofApp-guiManager-ofParameterGroup", NULL, flags);
	{
		ImGui::Text("guiManager");
		AddToggleRoundedButton(guiManager.bAutoResize);
		ImGui::TextWrapped("guiManager-ofParameterGroupguiManager-ofParameterGroupguiManager-ofParameterGroupguiManager-ofParameterGroupguiManager-ofParameterGroupguiManager-ofParameterGroup");
		ImGui::TextWrapped("ofParameterGroup render ->");

		ofxImGuiSurfing::AddGroup(params1);
		//guiManager.AddGroup(params1); // -> fails! must fix
	}
	guiManager.endWindow();
}

//--------------------------------------------------------------
void ofApp::setupParams() {

	params1.setName("paramsGroup1");
	params2.setName("paramsGroup2");
	params3.setName("paramsGroup3");
	bEnable.set("Enable", false);
	shapeType.set("shapeType", 0, -50, 50);
	params1.add(line1.set("line1", 0.5, 0, 1));
	params1.add(separation1.set("separation1", 50, 1, 100));
	params1.add(speed1.set("speed1", 0.5, 0, 1));
	params1.add(size1.set("size1", 100, 0, 100));
	params1.add(amount1.set("amount1", 10, 0, 25));
	params2.add(sep2min.set("sep2min", 25.f, 1, 100));
	params2.add(sep2max.set("sep2max", 75.f, 1, 100));
	params2.add(speed2.set("speed2", 0.5, 0, 1));
	params2.add(line2.set("line2", 0.5, 0, 1));
	params2.add(bEnable);
	params3.add(bMode1.set("Mode1", false));
	params3.add(bMode2.set("Mode2", false));
	params3.add(bMode3.set("Mode3", false));
	params3.add(bMode4.set("Mode4", false));
	params3.add(bModeA.set("ModeA", false));
	params3.add(bModeB.set("ModeB", false));
	params3.add(bModeC.set("ModeC", false));
	params3.add(bModeD.set("ModeD", false));
	params3.add(bPrevious.set("<", false));
	params3.add(bNext.set(">", false));
	params3.add(shape3.set("shape3", 0, -50, 50));
	params3.add(size3.set("size3", 100, 0, 100));
	params3.add(amount3.set("amount3", 10, 0, 25));
	params3.add(bEnable);
	params3.add(shapeType);
	params2.add(params3);
	params1.add(params2);
}

//--------------------------------------------------------------
void ofApp::addImGuiWindow() {
	static int i = 0;
	i++;

	myAddon *_guiInstance = new myAddon();

	string n = "myAddon-guiManager-VECTOR-" + ofToString(i);
	_guiInstance->setup(ofToString(n), i, i * 200, i * 100);
	guiInstances.emplace_back(_guiInstance);
}

//--------------------------------------------------------------
void ofApp::clearImGuiWindows()
{
	////TODO:
	////destructor ??
	////do not works...

	//for (auto &g : guiInstances) {
	//	delete g;
	//}

	for (int i = 0; i < guiInstances.size(); i++) {
		delete guiInstances[i];
	}
}

//--------------------------------------------------------------
void ofApp::setupDocking()
{
	// Make docked windows red transparent, to demonstrate drawing behind them.
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(200, 0, 0, 128)); // This styles the docked windows

	ImGuiDockNodeFlags dockingFlags = ImGuiDockNodeFlags_PassthruCentralNode; // Make the docking space transparent
	// Fixes imgui to expected behaviour, having a transparent central node in passthru mode.
	// Alternative: Otherwise add in ImGui::DockSpace() [±line 14505] : if (flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;
	ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));

	//dockingFlags |= ImGuiDockNodeFlags_NoDockingInCentralNode; // Uncomment to always keep an empty "central node" (a visible oF space)
	//dockingFlags |= ImGuiDockNodeFlags_NoTabBar; // Uncomment to disable creating tabs in the main view

	// Define the ofWindow as a docking space
	ImGuiID dockNodeID = ImGui::DockSpaceOverViewport(NULL, dockingFlags); // Also draws the docked windows
	ImGui::PopStyleColor(2);

	ImGuiDockNode* dockNode = ImGui::DockBuilderGetNode(dockNodeID);
	if (dockNode) {
		ImGuiDockNode* centralNode = ImGui::DockBuilderGetCentralNode(dockNodeID);
		// Verifies if the central node is empty (visible empty space for oF)
		if (centralNode && centralNode->IsEmpty()) {
			ImRect availableSpace = centralNode->Rect();
			//availableSpace.Max = availableSpace.Min + ImGui::GetContentRegionAvail();
			ImGui::GetForegroundDrawList()->AddRect(availableSpace.GetTL() + ImVec2(8, 8), availableSpace.GetBR() - ImVec2(8, 8), IM_COL32(255, 50, 50, 255));

			ImVec2 viewCenter = availableSpace.GetCenter();
			// Depending on the viewports flag, the XY is either absolute or relative to the oF window.
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) viewCenter = viewCenter - ImVec2(ofGetWindowPositionX(), ofGetWindowPositionY());

			ofPushStyle();
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofSetColor(255, 0, 0, 2);
			ofNoFill();

			ofDrawRectangle(
				viewCenter.x,
				viewCenter.y,
				availableSpace.GetSize().x - 6,
				availableSpace.GetSize().y - 6
			);
			ofNoFill();
			ofSetColor(255, 255, 255, 30);
			ofDrawRectangle(
				(viewCenter.x),
				(viewCenter.y),
				(availableSpace.GetSize().x - 20)*fmodf(abs(sin(ofGetElapsedTimef())), 1.f),
				(availableSpace.GetSize().y - 20)*fmodf(abs(sin(ofGetElapsedTimef())), 1.f)
			);
			ofSetRectMode(OF_RECTMODE_CORNER);
			ofPopStyle();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == ' ')
	{
		addImGuiWindow();
	}

	//if (key == OF_KEY_BACKSPACE)
	//{
	//	bFlagClear = true;
	//}
}

//--------------------------------------------------------------
void ofApp::exit()
{
	clearImGuiWindows();
}