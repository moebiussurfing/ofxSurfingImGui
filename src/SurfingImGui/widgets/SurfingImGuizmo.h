
/*
* SurfingImGuizmo.h
* 
*/

/*
* EXAMPLE
* 
* 
	//.h
	ofNode node;
	SurfingImGuizmo surfingImGuizmo;

	//.cpp
	surfingImGuizmo.setup("NodeGizmo");

	// imgui begin/end
	surfingImGuizmo.drawImGuiUser(ui);//controls in an imgui window
	surfingImGuizmo.drawImGuizmo(camera, &node);//widget
	
	surfingImGuizmo.keyPressed(key);

	//draw
	camera.begin();
	{
		//node.draw();

		// Applies the node's transformation matrix
		ImGuizmo::beginGuizmoTransform(&node);
		{
			ofDrawBox(25);
		}
		ImGuizmo::endGuizmoTransform();
	}
	camera.end();
*/

//--

#pragma once

#include "ofMain.h"

#include "ofxImGuizmo.h"
#include "ofxSurfingImGui.h"
//#include "ofxSurfingHelpersLite.h"

//----

class SurfingImGuizmo {
public:
	SurfingImGuizmo() { setup(); }
	~SurfingImGuizmo() { }

	ofParameterGroup parameters;
	ofParameter<bool> bEnableShow { "b", true };
	ofParameter<int> indexTool { "Tool", 0, 0, 2 };
	vector<string> namesTools { "Translate", "Scale", "Rotate" };
	ofParameter<bool> mode { "Mode", true };
	ofParameter<bool> bKeys { "Keys", true };

private:
	bool bDoneSetup = false;
	ImGuizmo::OPERATION op_;
	ImGuizmo::MODE mode_;

	ofEventListener listenerIndex;
	ofEventListener listenerMode;
	string name = "";

public:
	void setup(string name_) {
		name = name_;
		setup();
	}

	void setup() {
		if (name == "") name = "Gizmo";
		bEnableShow.setName(name);

		parameters.add(bEnableShow);
		parameters.add(indexTool);
		parameters.add(mode);
		parameters.add(bKeys);

		op_ = ImGuizmo::TRANSLATE;
		listenerIndex = indexTool.newListener([this](int & i) {
			ofLogNotice("SurfingGuizmo") << "indexTool: " << i;
			switch (i) {
			case 0:
				op_ = ImGuizmo::TRANSLATE;
				break;
			case 1:
				op_ = ImGuizmo::SCALE;
				break;
			case 2:
				op_ = ImGuizmo::ROTATE;
				break;
			}
		});

		listenerMode = mode.newListener([this](bool & b) {
			ofLogNotice("SurfingGuizmo") << "mode: " << (b ? "Local" : "Global");
		});

		bDoneSetup = true;
	}

public:
	void drawImGuiUser(ofxSurfingGui & ui) {
		if (!bDoneSetup) setup();

		//ui.AddLabelBig("Node Gizmo");
		ui.Add(bEnableShow, OFX_IM_TOGGLE_ROUNDED);

		if (bEnableShow) {
			ui.AddSpacing();
			//ui.AddComboButton(indexTool, namesTools);//TODO: missing button
			ui.AddCombo(indexTool, namesTools);
			if (ui.AddButton("Next", OFX_IM_BUTTON_SMALL)) {
				nextTool();
			}
			ui.Add(bKeys);
			string s = "";
			if (bKeys) {
				s += "w: Translate\n";
				s += "e: Scale\n";
				s += "r: Rotate\n";
				s += "Tab: Next\n";
				s += "Space: World/Local";
			}
			ui.AddTooltip(s);
		}
	}

public:
	bool drawImGuizmo(ofCamera * camera, ofNode * node) {
		if (!bDoneSetup) setup();

		if (camera == nullptr) return false;
		if (!bEnableShow) return false;
		ImGuizmo::BeginFrame();
		bool b = ImGuizmo::Manipulate(*camera, *node, op_, mode_);
		return b;
	}

public:
	void keyPressed(int key) {
		if (!bDoneSetup) setup();

		if (!bKeys) return;
		switch (key) {
		case 'w':
			//op_ = ImGuizmo::TRANSLATE;
			indexTool.set(0);
			break;
		case 'e':
			//op_ = ImGuizmo::SCALE;
			indexTool.set(1);
			break;
		case 'r':
			//op_ = ImGuizmo::ROTATE;
			indexTool.set(2);
			break;
		case OF_KEY_TAB:
			nextTool();
			break;
		case ' ':
			//mode_ = mode_ == ImGuizmo::LOCAL ? ImGuizmo::WORLD : ImGuizmo::LOCAL;
			mode = !mode;
			break;
		}
	}

	void nextTool() {
		int t = indexTool;
		t++;
		if (t > indexTool.getMax()) t = 0;
		indexTool.set(t);
	}
};