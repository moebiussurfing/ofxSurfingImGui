
/*
* SurfingImGuizmo.h
* 
*/

//--

#pragma once

#include "ofMain.h"

#include "ofxImGuizmo.h"
#include "ofxSurfingHelpersLite.h"
#include "ofxSurfingImGui.h"

//----

class SurfingImGuizmo {
public:
	SurfingImGuizmo() { setup(); }
	~SurfingImGuizmo() { }

	vector<string> namesTools { "Translate", "Scale", "Rotate" };
	ofParameter<int> indexTool { "Tool", 0, 0, 2 };
	ofParameter<bool> mode { "Mode", true };
	ofParameter<bool> bEnableShow { "Gizmo", true };
	ofParameter<bool> bKeys { "Keys", true };

private:
	ImGuizmo::OPERATION op_;
	ImGuizmo::MODE mode_;

	ofEventListener listenerIndex;
	ofEventListener listenerMode;

	void setup() {
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
	}

public:
	void drawImGuiUser(ofxSurfingGui & ui) {
		//ui.AddLabelBig("Node Gizmo");
		ui.Add(bEnableShow, OFX_IM_TOGGLE_ROUNDED);
		ui.AddSpacing();
		if (bEnableShow) {
			//ui.AddComboButton(indexTool, namesTools);//TODO: missing button
			ui.AddCombo(indexTool, namesTools);
			ui.Add(bKeys);
			string s = "";
			if (bKeys) {
				s += "w: Translate\n";
				s += "e: Scale\n";
				s += "r: Rotate\n";
				s += "Tab: Next Tool\n";
				s += "Space: World/Local";
			}
			ui.AddTooltip(s);
		}
	}

public:
	bool drawImGuizmo(ofCamera * camera, ofNode * node) {
		if (camera == nullptr) return false;
		if (!bEnableShow) return false;
		ImGuizmo::BeginFrame();
		bool b = ImGuizmo::Manipulate(*camera, *node, op_, mode_);
		return b;
	}

public:
	void keyPressed(int key) {
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
		case OF_KEY_TAB: {
			int t = indexTool;
			t++;
			if (t > indexTool.getMax()) t = 0;
			indexTool.set(t);
		} break;
		case ' ':
			//mode_ = mode_ == ImGuizmo::LOCAL ? ImGuizmo::WORLD : ImGuizmo::LOCAL;
			mode = !mode;
			break;
		}
	}
};