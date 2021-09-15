#include "simpleNode.h"

std::list< simpleNode* > simpleNode::allNodes = std::list< simpleNode* >();

//--------------------------------------------------------------
void simpleNode::setup() {
	bEdit.set("Edit", false);
}

//--------------------------------------------------------------
void simpleNode::update() {
	float* value1 = &this->_inValue;
	float* value2 = &this->_inValue2;
	// Sync data
	if (this->_inConnection1) {
		if (simpleNode* n = getNode(_inConnection1.nodeID)) {
			switch (_inConnection1.varID) {
				//                case 1:
				//                    value1 = &n->_inValue;
				//                    break;
				//                case 2:
				//                    value1 = &n->_inValue2;
				//                    break;
			case 3:
				value1 = &n->_outValue;
				break;
			default:
				break;
			}

		}
	}
	if (this->_inConnection2) {
		if (simpleNode* n = getNode(_inConnection2.nodeID)) {
			switch (_inConnection2.varID) {
				//                case 1:
				//                    value2 = &n->_inValue;
				//                    break;
				//                case 2:
				//                    value2 = &n->_inValue2;
				//                    break;
			case 3:
				value2 = &n->_outValue;
				break;
			default:
				break;
			}

		}
	}

	// Operate on data
	switch (this->_mode) {
	case operationMode_add:
		this->_outValue = *value1 + *value2;
		break;
	case operationMode_multiply:
		this->_outValue = *value1 * *value2;
		break;
	case operationMode_subtract:
		this->_outValue = *value1 - *value2;
		break;
	case operationMode_divide:
		if (*value2 == 0.f)
			this->_outValue = 0.f;
		else
			this->_outValue = *value1 / *value2;
		break;
	case operationMode_none:
	default:
		this->_outValue = *value1; // pass trough
		break;

	}
}

//--------------------------------------------------------------
void simpleNode::draw() {

}
//--------------------------------------------------------------
void simpleNode::drawObjectNodeGui(ImGuiEx::NodeCanvas& _nodeCanvas) {

	ImVec2 imPos(this->x, this->y);
	ImVec2 imSize(this->width, this->height);

	if (_nodeCanvas.BeginNode(this->_nodeName.c_str(), this->_nodeName.c_str(), imPos, imSize, 2, 1, true, false)) {

		ofxImGuiSurfing::AddToggleRoundedButton(bEdit);
		if (bEdit) {
			// Draw GUI
			ImGui::TextUnformatted("Arithmetic operations !");

			// Change arithmetic operation
			ImGui::Separator();
			static const char* operationModeNames[] = { "None", "Add", "Subtract", "Multiply", "Divide" };

			if (ImGui::BeginListBox("Operation mode", ImVec2(100, 80))) {
				for (int availableMode = operationMode_none; availableMode <= operationMode_divide; availableMode++) {
					const bool is_selected = (_mode == availableMode);
					if (ImGui::Selectable(operationModeNames[availableMode], is_selected))
						this->_mode = (operationMode)availableMode;

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndListBox();
			}

			ImGui::Dummy(ImVec2(10, 10)); ImGui::Spacing();

			// Display node data
			if (this->_inConnection1) {
				simpleNode* other = getNode(this->_inConnection1.nodeID);
				//ImGui::Text("Input number : %f", (other!=nullptr) ? other->_outValue : this->_inValue );
				ImGui::DragFloat("Input number", (other != nullptr) ? &other->_outValue : &this->_inValue);
			}
			else
				ImGui::DragFloat("Input number", &this->_inValue);

			// Operator mode visualisation
			switch (this->_mode) {
			case operationMode_add:
				ImGui::TextUnformatted("     + ");
				break;
			case operationMode_multiply:
				ImGui::TextUnformatted("     x ");
				break;
			case operationMode_subtract:
				ImGui::TextUnformatted("     - ");
				break;
			case operationMode_divide:
				if (this->_inValue2 == 0.f)
					ImGui::TextUnformatted("     / (cannot divide by zero!)");
				else
					ImGui::TextUnformatted("     / ");
				break;
			case operationMode_none:
			default:
				ImGui::TextUnformatted("     ?? ");
				break;
			}
		}

		// Show modifier value
		if (this->_inConnection2) {
			simpleNode* other = getNode(this->_inConnection2.nodeID);
			ImGui::DragFloat("Modifier number", (other != nullptr) ? &other->_outValue : &this->_inValue);
		}
		else
			ImGui::DragFloat("Modifier number", &this->_inValue2);

		ImGui::TextUnformatted("     = ");
		//ImGui::Text("Output number : %f ", this->_outValue );
		ImGui::DragFloat("Output number", &this->_outValue);

		// Check menu state
		if (_nodeCanvas.doNodeMenuAction(ImGuiExNodeMenuActionFlags_DeleteNode)) {
			// ...
			std::cout << "Deleting nodes is unimplemented in this example !" << std::endl;
		}
		//else if( _nodeCanvas.doNodeMenuAction(ImGuiExNodeMenuActionFlags_CopyNode) ){
		//          ofGetWindowPtr()->setClipboardString( this->serialize() );
		//}
		else if (_nodeCanvas.doNodeMenuAction(ImGuiExNodeMenuActionFlags_DuplicateNode)) {
			// ...
			std::cout << "Duplicating nodes is unimplemented in this example !" << std::endl;
		}

		// PINS
		std::string inVarAddr1 = std::string(to_string(this->_id)).append("_").append(to_string(1));
		if (ImGuiExNodePinResponse pinAction = _nodeCanvas.AddNodePin(inVarAddr1.c_str(), "Input Number", _inPinPos1, "float", 0, IM_COL32(255, 255, 0, 255), (bool)_inConnection1, ImGuiExNodePinsFlags_Left)) {
			// Perform Connect ?
			if (pinAction.flag == ImGuiExNodePinActionFlags_ConnectPin) {
				// Connect with pinAction.otherUid
				this->connectFrom(NodeVarReference::fromString(std::string(pinAction.otherUid)), NodeVarReference(this->_id, 1));
			}
			// Perform Disconnect ?
//            else if( pinAction.flag == ImGuiExNodePinActionFlags_DisconnectPin ){
//                std::cout << "Disconnecting " << this->_nodeName << "'s outlet 1 with : " << pinAction.otherUid << std::endl;
//                this->disconnectVar( 1 );
//            }
		}
		std::string inVarAddr2 = std::string(to_string(this->_id)).append("_").append(to_string(2));
		if (ImGuiExNodePinResponse pinAction = _nodeCanvas.AddNodePin(inVarAddr2.c_str(), "Modifier Number", _inPinPos2, "float", 0, IM_COL32(255, 255, 0, 255), (bool)_inConnection2, ImGuiExNodePinsFlags_Left)) {
			// Perform Connect ?
			if (pinAction.flag == ImGuiExNodePinActionFlags_ConnectPin) {
				// Connect with pinAction.otherUid
				this->connectFrom(NodeVarReference::fromString(std::string(pinAction.otherUid)), NodeVarReference(this->_id, 2));
			}
			// Perform Disconnect ?
//            else if( pinAction.flag == ImGuiExNodePinActionFlags_DisconnectPin ){
//                std::cout << "Disconnecting " << this->_nodeName << "'s outlet 2 with : " << pinAction.otherUid << std::endl;
//                this->disconnectVar( 2 );
//            }
		}
		// Outlets
		std::string outVarAddr = std::string(to_string(this->_id)).append("_").append(to_string(3));
		if (ImGuiExNodePinResponse pinAction = _nodeCanvas.AddNodePin(outVarAddr.c_str(), "Result", _outPinPos1, "float (Result)", 0, IM_COL32(255, 255, 0, 255), (bool)_outConnection1, ImGuiExNodePinsFlags_Right)) {
			// Perform Connect ?
			if (pinAction.flag == ImGuiExNodePinActionFlags_ConnectPin) {
				// Connect with pinAction.otherUid
				this->connectFrom(NodeVarReference(this->_id, 3), NodeVarReference::fromString(std::string(pinAction.otherUid)));
				//std::cout << "Connecting " << this->_nodeName << "'s outlet 3 with : " << pinAction.otherUid << std::endl;
			}
			// Perform Disconnect ?
//            else if( pinAction.flag == ImGuiExNodePinActionFlags_DisconnectPin ){
//                std::cout << "Disconnecting " << this->_nodeName << "'s outlet 3 with : " << pinAction.otherUid << std::endl;
//                //this->disconnectVar( 3 );
//            }
		}
	}

	// Close Node
	_nodeCanvas.EndNode();

	// Draw pin links (from inlets only (single links), they automatically connect to outlets (can have multiple links))
	if (this->_inConnection1) {
		if (simpleNode* other = getNode(this->_inConnection1.nodeID)) {
			auto linkAction = _nodeCanvas.AddLink(other->_outPinPos1, _inPinPos1, IM_COL32(255, 255, 0, 255), "float");
			if (linkAction == ImGuiExNodeLinkActionFlags_Disconnect) {
				//std::cout << "Disconnecting " << this->_nodeName << "'s inlet 1" << std::endl;
				this->disconnectVar(1);
			}
		}
	}
	if (this->_inConnection2) {
		if (simpleNode* other = getNode(this->_inConnection2.nodeID)) {
			auto linkAction = _nodeCanvas.AddLink(other->_outPinPos1, _inPinPos2, IM_COL32(255, 255, 0, 255), "float");
			if (linkAction == ImGuiExNodeLinkActionFlags_Disconnect) {
				//std::cout << "Disconnecting " << this->_nodeName << "'s inlet 2" << std::endl;
				this->disconnectVar(2);
			}
		}
	}

	// Update pos & size (_nodeCanvas.beginNode() can change it)
	if (imPos.x != this->x)
		this->x = imPos.x;
	if (imPos.y != this->y)
		this->y = imPos.y;
	if (imSize.x != this->width)
		this->width = imSize.x;
	if (imSize.y != this->height)
		this->height = imSize.y;
}

//--------------------------------------------------------------
bool simpleNode::connectFrom(NodeVarReference fromRef, NodeVarReference toRef) {
	std::cout << "Connecting " << fromRef.nodeID << "_" << fromRef.varID << " with " << toRef.nodeID << "_" << toRef.varID << std::endl;
	if (fromRef && toRef) {
		simpleNode* toNode = getNode(toRef.nodeID);
		simpleNode* fromNode = getNode(fromRef.nodeID);

		if (toNode != nullptr && fromNode != nullptr) {
			toNode->disconnectVar(toRef.varID);

			// Bind from
			switch (fromRef.varID) {
				//                case 1:
				//                    targetNode->_inConnection1 = NodeVarReference( this->_id, 3 );
				//                    break;
				//                case 2:
				//                    targetNode->_inConnection2 = NodeVarReference( this->_id, 3 );
				//                    break;
			case 3:
				fromNode->_outConnection1 = toRef;
				break;
			default:
				break;
			}

			// Bind to
			switch (toRef.varID) {
			case 1:
				toNode->_inConnection1 = fromRef;
				break;
			case 2:
				toNode->_inConnection2 = fromRef;
				break;
				//                case 3:
				//                    fromNode->_outConnection1 = toRef;
				//                    break;
			default:
				break;
			}

			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------
bool simpleNode::disconnectVar(int varID) {
	std::cout << "Diconnect Command on " << this->_nodeName << ", variable slot " << varID << std::endl;
	NodeVarReference linkBackup;
	switch (varID) {
	case 1:
		linkBackup = this->_inConnection1;
		this->_inConnection1 = NodeVarReference(-1, -1);
		if (linkBackup) {
			auto other = getNode(linkBackup.nodeID);
			std::cout << "Diconnecting other " << other << " = " << (other != nullptr ? other->_nodeName : "xxx") << std::endl;
			if (other != nullptr) other->disconnectVar(linkBackup.varID);
		}

		break;
	case 2:
		linkBackup = this->_inConnection2;
		this->_inConnection2 = NodeVarReference(-1, -1);
		if (linkBackup) {
			auto other = getNode(linkBackup.nodeID);
			std::cout << "Diconnecting other " << other << " = " << (other != nullptr ? other->_nodeName : "xxx") << std::endl;
			if (other != nullptr) other->disconnectVar(linkBackup.varID);
		}
		break;
	case 3:
		linkBackup = this->_outConnection1;
		this->_outConnection1 = NodeVarReference(-1, -1);
		if (linkBackup) {
			auto other = getNode(linkBackup.nodeID);
			std::cout << "Diconnecting other " << other << " = " << (other != nullptr ? other->_nodeName : "xxx") << std::endl;
			if (other != nullptr) other->disconnectVar(linkBackup.varID);
		}
		break;
	default:
		break;
	}
	return true;
}

//bool simpleNode::disconnectFrom(NodeVarReference from, NodeVarReference to){
//    return false;
//}
