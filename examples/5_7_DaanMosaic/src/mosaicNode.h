#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "imgui_stdlib.h"
#include "imgui_node_canvas.h"

#include "mosaicParameters.h"

#define MAX_PARAMS 36

struct PatchLink{
    int                     id;
    int                     type;
    int                     fromOutletID;
    int                     toObjectID;
    int                     toInletID;
};

class mosaicNode : public ofxVPHasUID {

public:

    mosaicNode() {
        mosaicNode(-1);
    }
    mosaicNode(int _id) : ofxVPHasUID("mosaicNode"), myFloatParam("myFloatName"), myStringParam("myStringName"), myIntParam("myIntName") {
        this->_id = _id;
        height = 300;
        width = 300;
        x = 10;
        y = 10;
    }

    void setup();
    void update(std::map<int,std::shared_ptr<mosaicNode>> &nodes);
    void draw();
    void drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas );

    bool connectFrom(std::map<int,std::shared_ptr<mosaicNode>> &nodes, int fromObjectID, int fromOutlet, int toInlet, int linkType);
    void disconnectFrom(std::map<int,std::shared_ptr<mosaicNode>> &nodes, int objectInlet);
    void disconnectLink(std::map<int,std::shared_ptr<mosaicNode>> &nodes, int linkID);


    // ID
    int                                             _id;

    // Links
    std::vector<std::shared_ptr<PatchLink>>         linksTo;

    // Params
    void*                                           _inletParams[MAX_PARAMS];
    void*                                           _outletParams[MAX_PARAMS];

    int                                             numInlets;
    int                                             numOutlets;
    int getNumInlets();
    int getNumOutlets();
    int getIsResizable();
    int getIsTextureObject();

    // Empty params content
    std::vector<float>                              *empty;
    ofImage                                         *kuro;


    float x, y, width, height;

    // Parameters
    //std::vector<std::shared_ptr<AbstractParameter> >parameters; // I tried with make_shared... which is a garbage collector, which in fact we don't really need as Parameters will ensure instances' validity ?
    std::vector<AbstractParameter*> parameters;

    // Customise this node (to be in a derived mosaicNode)
    // Static Parameters
    Parameter<float> myFloatParam;
    Parameter<std::string> myStringParam;
    Parameter<int> myIntParam;
    std::list< Parameter<int> > myDynamicParams; // note: cannot be vector, it re-allocates stored items, unvalidating pointers / references !
};
