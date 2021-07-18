#include "ofApp.h"

#include "NodesEdit.h"
#include "ofNodeEditor.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);

    gui.setup();
    gui.begin();

    //populate nodes
    nodes.CreateNodeFromType(ImVec2(400,140), ImGui::node_types[0]);
    nodes.CreateNodeFromType(ImVec2(600,300), ImGui::node_types[0]);
    nodes.CreateNodeFromType(ImVec2(100,440), ImGui::node_types[2]);

    gui.end();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::drawImGui() {

    gui.begin();

    float mainmenu_height = 0;

    ImGui::SetNextWindowPos(ImVec2( 0, mainmenu_height ));
    ImGui::SetNextWindowSize(ImVec2( ofGetWidth()-351, ofGetHeight()-mainmenu_height));

    ImGui::Begin("clientspanel", NULL,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus);

    nodes.ProcessNodes();

    ImGui::End();

    gui.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    drawImGui();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}