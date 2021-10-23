#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	//----

	// Parameters

	params1.setName("paramsGroup1");
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", false));
	params1.add(bMode1.set("bMode1", false));
	params1.add(bMode2.set("bMode2", true));
	params1.add(bMode3.set("bMode3", false));
	params1.add(bMode4.set("bMode4", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));
	params2.setName("paramsGroup2");
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.setName("paramsGroup3");
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));

	//-----------

	// guiManager

	setupImGui();
}

//--------------------------------------------------------------
void ofApp::setupImGui()
{
	// Instantiate

	guiManager.setup(IM_GUI_MODE_INSTANTIATED_DOCKING);

	//-

	// Layouts Presets

	// Add the windows just with a name:
	// You will use theese added windows easely, 
	// but you must rememeber his index order!
	// Each added window will be added too to the Layout Presets Engine and auto handled.

	guiManager.addWindowSpecial("Main"); // index 0
	guiManager.addWindowSpecial("Audio"); // index 1
	guiManager.addWindowSpecial("Video1"); // index 2
	guiManager.addWindowSpecial("Video2"); // index 3
	guiManager.addWindowSpecial("Expert"); // index 4

	/*

		NOTE:
		Then we can render the windows:
		if (guiManager.beginWindow(0)) // -> This is our helpers to render each window passing the index
		{
			// ..  window widgets goes here!
		}
		guiManager.endWindow();

		NOTICE:
		We can use also raw ImGui methods and widgets,
		combined with the add-on helpers to create windows and widgets too!

	*/

	//-

	// Startup

	guiManager.startup();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		// In between here (begin/end) we can render ImGui windows and widgets.

		//----

		// Here (between beginDocking/endDocking) we can access all the docking space.

		guiManager.beginDocking();
		{
		}
		guiManager.endDocking();

		//--

		// Render windows and widgets now!

		drawImGui();
	}
	guiManager.end();

	//----

	// Log
	logPopulate();
}

//--------------------------------------------------------------
void ofApp::drawImGui()
{
	// -> These are our helpers to render windows using the power of the Layout Engine.

	int index;

	index = 0;
	if (guiManager.getWindowSpecialVisible(index))
	{
		if (guiManager.beginWindowSpecial(index))
		{
			ImGui::Text("myWindow0");

			float _w100 = ofxImGuiSurfing::getWidgetsWidth(1); // full width
			float _w50 = ofxImGuiSurfing::getWidgetsWidth(2); // half width
			float _h = ofxImGuiSurfing::getWidgetsHeightRelative(); // standard height

			if (ofxImGuiSurfing::AddBigToggle(bEnable)) {}
			if (ofxImGuiSurfing::AddBigButton(bPrevious, _w50, _h * 2)) {
				lineWidth -= 0.1;
				bPrevious = false;
			}
			ImGui::SameLine();
			if (ofxImGuiSurfing::AddBigButton(bNext, _w50, _h * 2)) {
				lineWidth += 0.1;
				bNext = false;
			}

			ofxImGuiSurfing::AddParameter(bEnable);
			ofxImGuiSurfing::AddParameter(separation);
			ofxImGuiSurfing::AddParameter(shapeType);

		}
		guiManager.endWindowSpecial(index);
	}

	//----

	index = 1;
	if (guiManager.getWindowSpecialVisible(index))
	{
		if (guiManager.beginWindowSpecial(index))
		{
			ImGui::Text("myWindow1");
			guiManager.AddGroup(params1);
			guiManager.AddGroup(params3, ImGuiTreeNodeFlags_DefaultOpen, OFX_IM_GROUP_DEFAULT);
		}
	}
	guiManager.endWindowSpecial(index);

	//----

	index = 2;
	if (guiManager.getWindowSpecialVisible(index))
	{
		if (guiManager.beginWindowSpecial(index))
		{
			if (ImGui::BeginTabBar("myTabs"))
			{
				if (ImGui::BeginTabItem("Video"))
				{
					string str = "weqweqr qc wcrqw crqwecrqwec rqwec rqwe crqwecrqwecr qervev qervew ecrqwecr qwecrqwe cr qervev qerve";
					ImGui::Text("Blah blah");
					ImGui::TextWrapped(str.c_str());
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Audio"))
				{
					string str = "weq12341 234w eqrqcwcrqwcr 112 1233a dqervewecr qwecrqwe crqw ecr qervev qerve";
					ImGui::Text("Blah blah");
					ImGui::TextWrapped(str.c_str());
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Controls"))
				{
					guiManager.drawAdvanced();
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
		}
	}
	guiManager.endWindowSpecial(index);

	//----

	index = 3;
	if (guiManager.getWindowSpecialVisible(index))
	{
		if (guiManager.beginWindowSpecial(index))
		{
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
			ImGui::Text("Hello, down!");
		}
	}
	guiManager.endWindowSpecial(index);

	//----

	index = 4;
	if (guiManager.getWindowSpecialVisible(index))
	{
		if (guiManager.beginWindowSpecial(index))
		{
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
			ImGui::Text("Hello, left!");
		}
	}
	guiManager.endWindowSpecial(index);
}

//--------------------------------------------------------------
void ofApp::logPopulate()
{
	// Auto populate random log messages.
	int m = ofMap(speed, 1, 0, 2, ofRandom(1) > 0.5 ? 60 : 40);
	if (ofGetFrameNum() % m == 0)
	{
		if (ofNoise(ofGetElapsedTimef()) < 0.4f) return; // skip one third

		std::string ss = ofToString(ofGetFrameNum());
		float _rnd = ofRandom(1);
		if (_rnd < 0.2) guiManager.addLog(ss);
		else if (_rnd < 0.4) guiManager.addLog(ofToString(_rnd));
		else if (_rnd < 0.6) guiManager.addLog(ofToString("---------------" + ofToString((ofRandom(1) < 0.5 ? ".--.-." : "...-.--.."))));
		else if (_rnd < 0.8) guiManager.addLog(ofToString((ofRandom(1) < 0.5 ? "...-." : "--.--") + ofToString("===//...--//-----..")));
		else guiManager.addLog(ofGetTimestampString());
	}
}