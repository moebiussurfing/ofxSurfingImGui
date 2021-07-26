#pragma once

#include "ofMain.h"

#include "mosaicNode.h"
#include "ofxInfiniteCanvas.h"
#include "imgui_node_canvas.h"

// WIP

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);

	void mouseMoved(ofMouseEventArgs &e);
	void mouseDragged(ofMouseEventArgs &e);
	void mousePressed(ofMouseEventArgs &e);
	void mouseReleased(ofMouseEventArgs &e);
	void mouseScrolled(ofMouseEventArgs &e);

	void drawWidgets();
	bool bOpen0 = true;
	bool bOpen1 = true;
	bool bOpen2 = false;
	bool initialized = false;

	void updateCanvasViewport();

	std::map<int, std::shared_ptr<mosaicNode>> nodesMap;

	// GUI
	ofxImGui::Gui gui;
	ofxInfiniteCanvas               canvas;
	//ofEasyCam                       easyCam;
	ofRectangle                     canvasViewport;
	//ofxImGui::Gui*                  ofxVPGui;
	ImGuiEx::NodeCanvas             nodeCanvas;


	void drawObjectNodeGui(ImGuiEx::NodeCanvas& _nodeCanvas);
	float x = 10, y = 10, width = 500, height = 500;

};
