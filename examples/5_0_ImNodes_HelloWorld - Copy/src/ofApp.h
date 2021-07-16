#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"	

#include "node_editor.h"
#include <imnodes.h>
#include <imgui.h>

//namespace example
//{
//	namespace
//	{
//		class HelloWorldNodeEditor
//		{
//		public:
//			void show()
//			{
//				ImGui::Begin("simple node editor");
//
//				ImNodes::BeginNodeEditor();
//				ImNodes::BeginNode(1);
//
//				ImNodes::BeginNodeTitleBar();
//				ImGui::TextUnformatted("simple node :)");
//				ImNodes::EndNodeTitleBar();
//
//				ImNodes::BeginInputAttribute(2);
//				ImGui::Text("input");
//				ImNodes::EndInputAttribute();
//
//				ImNodes::BeginOutputAttribute(3);
//				ImGui::Indent(40);
//				ImGui::Text("output");
//				ImNodes::EndOutputAttribute();
//
//				ImNodes::EndNode();
//				ImNodes::EndNodeEditor();
//
//				ImGui::End();
//			}
//		};
//
//		static HelloWorldNodeEditor editor;
//	} // namespace
//
//	void NodeEditorInitialize() { ImNodes::SetNodeGridSpacePos(1, ImVec2(200.0f, 200.0f)); }
//
//	void NodeEditorShow() { editor.show(); }
//
//	void NodeEditorShutdown() {}
//
//} // namespace example


class ofApp : public ofBaseApp {

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

	bool initialized = true;
};
