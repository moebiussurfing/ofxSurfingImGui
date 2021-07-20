#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetFrameRate(60);
	ofSetWindowPosition(-1920, 25);

	//guiManager.setImGuiAutodraw(true);
	//guiManager.setup();
	this->gui.setup();

	//-

	// Set pan-zoom canvas
	canvas.disableMouseInput();
	canvas.setbMouseInputEnabled(true);
	canvas.toggleOfCam();
	//easyCam.enableOrtho();

	//updateCanvasViewport();


	//// TESTING SCENARIO, ADD 3 NODES

	//nodesMap[0] = std::shared_ptr<mosaicNode>(new mosaicNode(0));
	//nodesMap[1] = std::shared_ptr<mosaicNode>(new mosaicNode(1));
	//nodesMap[2] = std::shared_ptr<mosaicNode>(new mosaicNode(2));

	//// setup nodes
	//for (map<int, shared_ptr<mosaicNode>>::iterator it = nodesMap.begin(); it != nodesMap.end(); it++) {
	//	it->second->setup();
	//}


	//// TESTING CONNECT/DISCONNECT

	//nodesMap[0]->connectFrom(nodesMap, 2, 0, 0, VP_LINK_NUMERIC);
	//nodesMap[1]->connectFrom(nodesMap, 2, 1, 1, VP_LINK_STRING);
	//nodesMap[1]->connectFrom(nodesMap, 2, 0, 1, VP_LINK_STRING);
	//// new way ?
	////nodesMap[0]->parameters.front()->connectWith( nodesMap[1]->parameters.front() );
}

//--------------------------------------------------------------
void ofApp::update() {
	updateCanvasViewport();
	ofSetWindowTitle("Mosaic Engine Tester");

	// update nodes
	for (map<int, shared_ptr<mosaicNode>>::iterator it = nodesMap.begin(); it != nodesMap.end(); it++) {
		it->second->update(nodesMap);
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

	ofEnableAlphaBlending();
	ofSetCurveResolution(50);
	ofSetColor(255);
	ofSetLineWidth(1);


	this->gui.begin();
	{
		// Init canvas
		nodeCanvas.SetTransform(canvas.getTranslation(), canvas.getScale());//canvas.getScrollPosition(), canvas.getScale(true) );

		canvas.begin(canvasViewport);

		ofEnableAlphaBlending();
		ofSetCurveResolution(50);
		ofSetColor(255);
		ofSetLineWidth(1);

		this->gui.begin();
		ImGui::SetNextWindowPos(canvasViewport.getTopLeft(), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(canvasViewport.width, canvasViewport.height), ImGuiCond_Always);
		bool isCanvasVisible = nodeCanvas.Begin("ofxVPNodeCanvas");

		// END VP DRAW

		if (isCanvasVisible) {
			// draw nodes (will be in PatchObject)
			for (map<int, shared_ptr<mosaicNode>>::iterator it = nodesMap.begin(); it != nodesMap.end(); it++) {
				shared_ptr<mosaicNode> node = it->second;

				// Let objects draw their own Gui
				//node->drawObjectNodeGui( _nodeCanvas );
				//node->draw();
				node->drawObjectNodeGui(nodeCanvas);

			}

		}

		// Close canvas
		if (isCanvasVisible) nodeCanvas.End();
	}
	// We're done drawing to IMGUI
	this->gui.end();



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
void ofApp::drawObjectNodeGui(ImGuiEx::NodeCanvas& _nodeCanvas) {




	ImVec2 imPos(this->x, this->y);
	ImVec2 imSize(this->width, this->height);

	if (_nodeCanvas.BeginNode(this->getUID().c_str(), this->getDisplayName(), imPos, imSize, this->getNumInlets(), this->getNumOutlets(), this->getIsResizable(), this->getIsTextureObject())) {

		// Check menu state
		if (_nodeCanvas.doNodeMenuAction(ImGuiExNodeMenuActionFlags_DeleteNode)) {
			// ...
		}
		//else if( _nodeCanvas.doNodeMenuAction(ImGuiExNodeMenuActionFlags_CopyNode) ){
		//          ofGetWindowPtr()->setClipboardString( this->serialize() );
			// ofNotifyEvent(copyEvent, nId); ?
		//}
		else if (_nodeCanvas.doNodeMenuAction(ImGuiExNodeMenuActionFlags_DuplicateNode)) {
			// ...
		}

		ImGui::Spacing(); ImGui::Spacing();

		// Draw Pins from parameters
		if (false)for (AbstractParameter* param : this->parameters) {
			//param->drawImGuiParamPin(nodeCanvas, true);
			//param->drawImGuiParamPin(nodeCanvas, false);
			continue;
			// Draw inlet Pin
			if (param->getIsEditable()) {
				AbstractHasModifier& paramHasModifier = param->getAsHasModifier();
				_nodeCanvas.AddNodePin(param->getUID().c_str(), paramHasModifier.getHasModifierName().c_str(), paramHasModifier.getInletPosition(), getLinkName(paramHasModifier.modifierLinkType), paramHasModifier.modifierLinkType, IM_COL32(255, 255, 255, 255), paramHasModifier.getNumModifiers() > 0, ImGuiExNodePinsFlags_Left);
			}
			// Draw outlet pin
			try {
				AbstractHasOutlet& paramOutlet = param->getAsOutlet();
				bool hasConnections = paramOutlet.getNumConnections() > 0;
				_nodeCanvas.AddNodePin(param->getUID().c_str(), paramOutlet.getPinLabel().c_str(), paramOutlet.outletPosition, getLinkName(paramOutlet.linkType), paramOutlet.linkType, IM_COL32(255, 255, 255, 255), hasConnections, ImGuiExNodePinsFlags_Right);
				if (hasConnections) {
					//nodeCanvas.addConnection();
				}
			}
			catch (...) {
				// Ignore errors, normal behaviour
			}
		}

		// Let objects draw their own Gui



		// Automatic Parameters drawing.
		ImGui::Separator();
		ImGui::TextUnformatted("NEW PARAMETER API");
		ImGui::Separator();

		// Draw Pins from parameters
		for (AbstractParameter* param : this->parameters) {
			param->drawImGuiParamPin(_nodeCanvas, true);
			param->drawImGuiParamPin(_nodeCanvas, false);
		};

		for (AbstractParameter* param : this->parameters) {
			if (param == nullptr) continue;

			//param->drawImGuiParamPin(_nodeCanvas, true);
			param->drawImGuiEditable();
			//param->drawImGuiParamPin(_nodeCanvas, false);
		};



	}
	// Close Node
	_nodeCanvas.EndNode();

	// Update pos & size
	if (imPos.x != this->x)
		this->x = imPos.x;
	if (imPos.y != this->y)
		this->y = imPos.y;
	if (imSize.x != this->width)
		this->width = imSize.x;
	if (imSize.y != this->height)
		this->height = imSize.y;

	//canvasTranslation   = _nodeCanvas.GetCanvasTranslation();
	//canvasScale         = _nodeCanvas.GetCanvasScale();
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
void ofApp::mouseScrolled(ofMouseEventArgs &e) {

	if (ImGui::IsAnyItemActive() || nodeCanvas.isAnyNodeHovered() || ImGui::IsAnyItemHovered())// | ImGui::IsAnyWindowHovered() )
		return;

	canvas.mouseScrolled(e);
}

void ofApp::updateCanvasViewport() {
	canvasViewport.set(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

//--------------------------------------------------------------
void ofApp::exit() {
}