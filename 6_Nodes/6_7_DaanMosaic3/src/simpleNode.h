#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"
//#include "ofxImGui.h"
#include "imgui_stdlib.h"
#include "imgui_node_canvas.h"

// This is a very basic node engine
// It's not recommended to use it, it's only here to demonstrate how to implement the imgui_node_canvas GUI with your own node engine.

struct NodeVarReference {
    NodeVarReference() : nodeID(-1), varID(-1) {};
    NodeVarReference(int _nodeID, int _varID) : nodeID(_nodeID), varID(_varID) {};
    int                     nodeID = -1;
    int                     varID = -1;
    explicit operator bool() {
        return this->nodeID >= 0 && this->varID >= 0;
    };
    std::string toString(){ return std::string( to_string(this->nodeID) ).append("_").append( to_string(this->varID) ); };
    static NodeVarReference fromString(std::string s){
        int nodeID = -1;
        int varID = -1;
        std::size_t pos = s.find("_");
        if(pos != std::string::npos){
            nodeID = std::stoi(s.substr(0, pos));
            varID = std::stoi(s.substr(pos+1));
        }
        return NodeVarReference(nodeID, varID);
    };
};

enum operationMode {
    operationMode_none = 0,
    operationMode_add = 1,
    operationMode_subtract = 2,
    operationMode_multiply = 3,
    operationMode_divide = 4,
};

class simpleNode {

public:

    simpleNode() {
        simpleNode(-1);
    }
    simpleNode(int _id) {
        this->_id = _id;
        this->_nodeName = std::string("Node ").append( std::to_string( _id ) );

        height = 300;
        width = 300;

        // auto_layout
        x = 10 + (20 + width)*_id;
        y = 10;//(10 + height)*_id;

        allNodes.push_back(this);
    }

    ~simpleNode(){
        std::list< simpleNode* >::iterator me = std::find( allNodes.begin(), allNodes.end(), this );
        if( me != allNodes.end() )
            allNodes.erase(me);
    }

    void setup();
    void update();
    void draw();
    void drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas );

    static bool connectFrom(NodeVarReference from, NodeVarReference to);
    //static bool disconnectFrom(NodeVarReference from, NodeVarReference to);
    bool disconnectVar(int varID);

    // Attributes
    int                 _id;
    std::string         _nodeName;
    operationMode       _mode = operationMode_none;
    float               x, y, width, height;

    // Parameters
    float               _inValue = 0; // pin data
    float               _inValue2 = 0; // pin data
    float               _outValue = 0; // pin data
    NodeVarReference    _inConnection1;
    NodeVarReference    _inConnection2;
    NodeVarReference    _outConnection1;
    ImVec2              _inPinPos1, _inPinPos2, _outPinPos1;

    // All nodes, singleton register
    static std::list< simpleNode* > allNodes;
    static simpleNode* getNode( int nodeID ){
        for (std::list<simpleNode*>::iterator it = allNodes.begin(); it != allNodes.end(); ++it){
            if( (*it)->_id == nodeID ) return *it;
        }
        return nullptr;
    };

	ofParameter<bool> bEdit;

};
