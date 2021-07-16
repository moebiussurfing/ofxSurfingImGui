#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"	

//-

#include "color_node_editor.cpp"

//-

#include "node_editor.h"
#include <imnodes.h>
#include <imgui.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <ios> // for std::streamsize
#include <stddef.h>
#include <vector>

//-

static example::ColorNodeEditor color_editor;

//void NodeEditorInitialize()
//{
//	ImNodesIO& io = ImNodes::GetIO();
//	io.LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
//}
//
//void NodeEditorShow() { color_editor.show(); }
//
//void NodeEditorShutdown() {}

//-

class ofApp : public ofBaseApp {
public:

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxSurfing_ImGui_Manager guiManager;

	void drawWidgets();

	bool bOpen0 = true;
	bool bOpen1 = true;
	bool bOpen2 = false;

	bool initialized = false;
};
