#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetWindowPosition(1920, 25);

	guiManager.setSettingsFilename("1_Widgets"); // -> customize filename
	guiManager.setup(IM_GUI_MODE_INSTANTIATED);
	
	pos1.set("pos1", glm::vec3(0.f), glm::vec3(-MAX_CAMERA_DISTANCE), glm::vec3(MAX_CAMERA_DISTANCE));
	pos2.set("pos2", glm::vec3(0.f), glm::vec3(-2.f*MAX_CAMERA_DISTANCE), glm::vec3(2.f*MAX_CAMERA_DISTANCE));

	bEnable1.set("bEnable1", false);
	bEnable2.set("bEnable2", false);
	bEnable3.set("bEnable3", false);

	bPrevious.set("<", false);
	bNext.set(">", false);

	params.setName("params");
	params.add(pos1);
	params.add(pos2);

	params2.setName("params2");
	lineWidth.set("lineWidth", 0.5, 0, 1);
	separation.set("separation", 50, 1, 100);
	params2.add(lineWidth);
	params2.add(separation);
	params.add(params2);

	//params3.setName("paramsGroup3");// nested
	//params.add(speed.set("speed", 0.5, 0, 1));
	//params.add(shapeType.set("shapeType", 0, -50, 50));
	//params.add(size.set("size", 100, 0, 100));
	//params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	//params2.add(size2.set("size2", 100, 0, 100));
	//params2.add(amount2.set("amount2", 10, 0, 25));
	//params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	//params3.add(separation3.set("separation3", 50, 1, 100));
	//params3.add(speed3.set("speed3", 0.5, 0, 1));
}

//--------------------------------------------------------------
void ofApp::draw() {

	guiManager.begin();
	{
		guiManager.beginWindow();
		{
			//if (ImGui::TreeNode("Tree"))
			//{
			//	guiManager.Add(bEnable1);
			//	guiManager.Add(bEnable2);
			//	guiManager.Add(bEnable3);
			//	ImGui::TreePop();
			//}

			//guiManager.clear();
			guiManager.AddGroup(params); // -> BUG: first level crashes!

			ImGui::Spacing();
			//ofxImGuiSurfing::AddParameter(pos1, true);
			guiManager.Add(pos1, OFX_IM_MULTIDIM_SPLIT_SLIDERS);
			ImGui::Spacing();
			
			ofxImGuiSurfing::AddToggleRoundedButton(bPrevious);
			ImGui::SameLine();
			ofxImGuiSurfing::AddToggleRoundedButton(bNext);
			ImGui::SameLine();
			ofxImGuiSurfing::AddToggleRoundedButton(bEnable1);
		}
		guiManager.endWindow();
	}
	guiManager.end();
}
