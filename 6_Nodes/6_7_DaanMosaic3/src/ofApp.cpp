#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetFrameRate(60);
	//ofSetWindowPosition(1920, 25);
	ofSetWindowTitle("Mosaic Engine Tester");

	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	//-

	// Set pan-zoom canvas
	canvas.disableMouseInput();
	canvas.setbMouseInputEnabled(true);
	canvas.toggleOfCam();
	//easyCam.enableOrtho();

	updateCanvasViewport();

	//-

	// TESTING SCENARIO, ADD 3 NODES

	nodesMap[0] = std::shared_ptr<simpleNode>(new simpleNode(0));
	nodesMap[1] = std::shared_ptr<simpleNode>(new simpleNode(1));
	nodesMap[2] = std::shared_ptr<simpleNode>(new simpleNode(2));

	// setup nodes
	for (map<int, shared_ptr<simpleNode>>::iterator it = nodesMap.begin(); it != nodesMap.end(); it++) {
		it->second->setup();
	}

	//-

	// TESTING CONNECT/DISCONNECT

	//	nodesMap[0]->connectFrom(nodesMap, 2, 0, 0, VP_LINK_NUMERIC);
	//	nodesMap[1]->connectFrom(nodesMap, 2, 1, 1, VP_LINK_STRING);
	//	nodesMap[1]->connectFrom(nodesMap, 2, 0, 1, VP_LINK_STRING);
	// new way ?
	//nodesMap[0]->parameters.front()->connectWith( nodesMap[1]->parameters.front() );
}

//--------------------------------------------------------------
void ofApp::update() {
	updateCanvasViewport();

	// update nodes
	for (map<int, shared_ptr<simpleNode>>::iterator it = nodesMap.begin(); it != nodesMap.end(); it++) {
		it->second->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofPushView();
	ofPushStyle();
	ofPushMatrix();

	// Init canvas
	nodeCanvas.SetTransform(canvas.getTranslation(), canvas.getScale());//canvas.getScrollPosition(), canvas.getScale(true) );

	canvas.begin(canvasViewport);
	{
		ofEnableAlphaBlending();
		ofSetCurveResolution(50);
		ofSetColor(255);
		ofSetLineWidth(1);

		//-

		this->guiManager.begin();
		{
			ImGui::SetNextWindowPos(canvasViewport.getTopLeft(), ImGuiCond_Always);
			ImGui::SetNextWindowSize(ImVec2(canvasViewport.width, canvasViewport.height), ImGuiCond_Always);

			bool isCanvasVisible = nodeCanvas.Begin("ofxVPNodeCanvas");

			// END VP DRAW

			if (isCanvasVisible) {
				// draw nodes (will be in PatchObject)
				for (map<int, shared_ptr<simpleNode>>::iterator it = nodesMap.begin(); it != nodesMap.end(); it++) {
					shared_ptr<simpleNode> node = it->second;

					// Let objects draw their own Gui
					node->drawObjectNodeGui(nodeCanvas);
				}
			}

			// Close canvas
			if (isCanvasVisible) nodeCanvas.End();

			// Debug
			//ImGui::ShowMetricsWindow();
		}
	
		// We're done drawing to IMGUI
		this->guiManager.end();
	}
	canvas.end();

	ofDisableAlphaBlending();

	ofPopMatrix();
	ofPopStyle();
	ofPopView();

	// Graphical Context
	canvas.update();

	// LIVE PATCHING SESSION
	//drawLivePatchingSession();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(ofMouseEventArgs &e) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(ofMouseEventArgs &e) {
	if (ImGui::IsAnyItemActive() || nodeCanvas.isAnyNodeHovered() || ImGui::IsAnyItemHovered())// || ImGui::IsAnyWindowHovered())
		return;

	canvas.mouseDragged(e);
}

//--------------------------------------------------------------
void ofApp::mousePressed(ofMouseEventArgs &e) {
	if (ImGui::IsAnyItemActive() || nodeCanvas.isAnyNodeHovered() || ImGui::IsAnyItemHovered())
		return;

	canvas.mousePressed(e);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(ofMouseEventArgs &e) {
	if (ImGui::IsAnyItemActive() || nodeCanvas.isAnyNodeHovered() || ImGui::IsAnyItemHovered())
		return;

	canvas.mouseReleased(e);
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(ofMouseEventArgs &e) {

	if (ImGui::IsAnyItemActive() || nodeCanvas.isAnyNodeHovered() || ImGui::IsAnyItemHovered())// | ImGui::IsAnyWindowHovered() )
		return;

	canvas.mouseScrolled(e);
}

//--------------------------------------------------------------
void ofApp::updateCanvasViewport() {
	// Map ofxInfiniteCanvas coords to node canvas. Any other canvas engine should be easy to port.
	canvasViewport.set(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

//--------------------------------------------------------------
void ofApp::exit() {
}
