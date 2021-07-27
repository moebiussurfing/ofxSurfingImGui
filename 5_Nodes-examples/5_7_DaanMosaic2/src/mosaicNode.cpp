#include "mosaicNode.h"

//--------------------------------------------------------------
void mosaicNode::setup(){

    // fixed node content to one inlet/outlet/param for each type

    // VP_LINK_NUMERIC
    _inletParams[0] = new float();
    *(float *)&_inletParams[0] = 0.0f;

    _outletParams[0] = new float();
    *(float *)&_outletParams[0] = 0.0f;

    // VP_LINK_STRING
    _inletParams[1] = new std::string();
    *static_cast<std::string *>(_inletParams[1]) = "";

    _outletParams[1] = new std::string();
    *static_cast<std::string *>(_outletParams[1]) = "";

    // VP_LINK_ARRAY
    _inletParams[2] = new std::vector<float>();
    _outletParams[2] = new std::vector<float>();

    // VP_LINK_TEXTURE
    _inletParams[3] = new ofTexture();
    _outletParams[3] = new ofTexture();

    // VP_LINK_AUDIO
    _inletParams[4] = new ofSoundBuffer();
    _outletParams[4] = new ofSoundBuffer();

    // VP_LINK_PIXELS
    _inletParams[5] = new ofPixels();
    _outletParams[5] = new ofPixels();

    // init num inlets/outlets ( to remove in the future? probably)
    numInlets = 6;
    numOutlets = 6;


    // Empty vars init
    empty   = new std::vector<float>();
    kuro    = new ofImage();

    empty->assign(1,0);
    kuro->load("images/kuro.jpg");


    // TESTING INIT shared_ptr<void> params
    *(float *)&_inletParams[0] = 0.0f;

    *static_cast<std::string *>(_inletParams[1]) = "";

    *static_cast<std::vector<float> *>(_inletParams[2]) = *empty;

    *static_cast<ofTexture *>(_inletParams[3]) = kuro->getTexture();

    static_cast<ofTexture *>(_inletParams[3])->readToPixels(*static_cast<ofPixels *>(_inletParams[5]));

    static_cast<ofSoundBuffer *>(_inletParams[4])->set(0.0f);
    static_cast<ofSoundBuffer *>(_outletParams[4])->set(0.0f);

    *static_cast<ofPixels *>(_inletParams[5]) = kuro->getPixels();

    // - - - - - - - - - -
    // Setup parameters (as above, new way)
    //parameters.push_back( std::make_shared< AbstractParameter >( myFloatParam ) );
    parameters.push_back( &myFloatParam );
    parameters.push_back( &myStringParam );
    parameters.push_back( &myIntParam );

    // NEED TO ADD vector<float>

    // NEED TO ADD ofTexture

    // NEED TO ADD ofSoundBuffer

    // NEED TO ADD ofPixels

    // Other way for dynamic params
    myDynamicParams.resize(0);
    int rand = random() % 5;
    //std::cout << "Creating " << rand << " dynamic params in Node " << this->_id << "."<< std::endl;
    for(int i=0; i<rand; i++){
        myDynamicParams.emplace_back( "MyDynamicParameter" );
        AbstractParameter* insertedParam = &myDynamicParams.back();
        parameters.push_back( insertedParam );
        std::cout << "insertedParam @ " << insertedParam << ", name=" << insertedParam->getUID() << std::endl;
    }
    if(false){ // tmp4debug
        std::cout << "After inserting, dynamicParams : ";
        for(AbstractParameter& p : myDynamicParams){
            std::cout << &p << " (" << p.getUID() << "), ";
        }
        std::cout << std::endl;
        std::cout << "After inserting, allParams : ";
        for(AbstractParameter* p : parameters){
            std::cout << p << " (" << p->getUID() << "), ";
        }
        std::cout << std::endl;
    }
}

//--------------------------------------------------------------
void mosaicNode::update(std::map<int,std::shared_ptr<mosaicNode>> &nodes){

    // update links ( connected params dataflow )
    for(int out=0;out<numOutlets;out++){
        for(int i=0;i<static_cast<int>(linksTo.size());i++){
            if(linksTo[i]->fromOutletID == out){
                // send data through links
                nodes[linksTo[i]->toObjectID]->_inletParams[linksTo[i]->toInletID] = _outletParams[out];
            }
        }
    }


    // bypass params from inlets to outlets (basic standard node operation)

    *(float *)&_outletParams[0] = *(float *)&_inletParams[0];

    *static_cast<std::string *>(_outletParams[1]) = *static_cast<std::string *>(_inletParams[1]);

    *static_cast<std::vector<float> *>(_outletParams[2]) = *static_cast<std::vector<float> *>(_inletParams[2]);

    *static_cast<ofTexture *>(_outletParams[3]) = *static_cast<ofTexture *>(_inletParams[3]);

    *static_cast<ofSoundBuffer *>(_outletParams[4]) = *static_cast<ofSoundBuffer *>(_inletParams[4]);

    *static_cast<ofPixels *>(_outletParams[5]) = *static_cast<ofPixels *>(_inletParams[5]);

}

//--------------------------------------------------------------
void mosaicNode::draw(){ // not needed anymore ?
    auto mainSettings = ofxImGui::Settings();

    std::string nodeName = "Node"+ofToString(this->_id);
    if (ofxImGui::BeginWindow(nodeName.c_str(), mainSettings, false))
    {
        ImGui::DragFloat("inlet float --> ", &*(float *)&_inletParams[0]);
        ImGui::SameLine();
        ImGui::Text("outlet float: %s",ofToString(*(float *)&_outletParams[0]).c_str());

        ImGui::InputText("inlet string --> ", static_cast<std::string *>(_inletParams[1]));
        ImGui::SameLine();
        ImGui::Text("outlet string: %s",static_cast<std::string *>(_outletParams[1])->c_str());


        // NEED TO ADD vector<float>

        // NEED TO ADD ofTexture

        // NEED TO ADD ofSoundBuffer

        // NEED TO ADD ofPixels

        // Automatic Parameters drawing.
        ImGui::Separator();
        ImGui::TextUnformatted("NEW PARAMETER API");
        ImGui::Separator();

        for(auto it=parameters.begin(); it!=parameters.end(); ++it){
            (*it)->drawImGuiEditable();
        };
    }
    ofxImGui::EndWindow(mainSettings);
}
//--------------------------------------------------------------
void mosaicNode::drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas ){

    ImVec2 imPos( this->x, this->y );
    ImVec2 imSize( this->width, this->height );

    if(_nodeCanvas.BeginNode( this->getUID().c_str(), this->getDisplayName(), imPos, imSize, this->getNumInlets(), this->getNumOutlets(), this->getIsResizable(), this->getIsTextureObject() )){

        // Check menu state
        if( _nodeCanvas.doNodeMenuAction(ImGuiExNodeMenuActionFlags_DeleteNode) ){
            // ...
        }
        //else if( _nodeCanvas.doNodeMenuAction(ImGuiExNodeMenuActionFlags_CopyNode) ){
        //          ofGetWindowPtr()->setClipboardString( this->serialize() );
            // ofNotifyEvent(copyEvent, nId); ?
        //}
        else if( _nodeCanvas.doNodeMenuAction(ImGuiExNodeMenuActionFlags_DuplicateNode) ){
            // ...
        }

        ImGui::Spacing();ImGui::Spacing();

        // Draw Pins from parameters
        if(false)for( AbstractParameter* param : this->parameters ){
            //param->drawImGuiParamPin(nodeCanvas, true);
            //param->drawImGuiParamPin(nodeCanvas, false);
            continue;
            // Draw inlet Pin
            if(param->getIsEditable()){
                AbstractHasModifier& paramHasModifier = param->getAsHasModifier();
                _nodeCanvas.AddNodePin( param->getUID().c_str(), paramHasModifier.getHasModifierName().c_str(), paramHasModifier.getInletPosition(), getLinkName(paramHasModifier.modifierLinkType), paramHasModifier.modifierLinkType, IM_COL32(255,255,255,255), paramHasModifier.getNumModifiers()>0, ImGuiExNodePinsFlags_Left );
            }
            // Draw outlet pin
            try {
                AbstractHasOutlet& paramOutlet = param->getAsOutlet();
                bool hasConnections = paramOutlet.getNumConnections() > 0;
                _nodeCanvas.AddNodePin( param->getUID().c_str(), paramOutlet.getPinLabel().c_str(),paramOutlet.outletPosition, getLinkName(paramOutlet.linkType), paramOutlet.linkType, IM_COL32(255,255,255,255), hasConnections, ImGuiExNodePinsFlags_Right );
                if(hasConnections){
                    //nodeCanvas.addConnection();
                }
            } catch(...) {
                // Ignore errors, normal behaviour
            }
        }

        // Let objects draw their own Gui



        // Automatic Parameters drawing.
        ImGui::Separator();
        ImGui::TextUnformatted("NEW PARAMETER API");
        ImGui::Separator();

        // Draw Pins from parameters
        for( AbstractParameter* param : this->parameters ){
            param->drawImGuiParamPin(_nodeCanvas, true);
            param->drawImGuiParamPin(_nodeCanvas, false);
        };

        for( AbstractParameter* param : this->parameters ){
            if(param==nullptr) continue;

            //param->drawImGuiParamPin(_nodeCanvas, true);
            param->drawImGuiEditable();
            //param->drawImGuiParamPin(_nodeCanvas, false);
        };



    }
    // Close Node
    _nodeCanvas.EndNode();

    // Update pos & size
    if( imPos.x != this->x )
        this->x = imPos.x;
    if( imPos.y != this->y )
        this->y = imPos.y;
    if( imSize.x != this->width )
        this->width = imSize.x;
    if( imSize.y != this->height )
        this->height = imSize.y;

    //canvasTranslation   = _nodeCanvas.GetCanvasTranslation();
    //canvasScale         = _nodeCanvas.GetCanvasScale();
}

//--------------------------------------------------------------
bool mosaicNode::connectFrom(std::map<int,std::shared_ptr<mosaicNode>> &nodes, int fromObjectID, int fromOutlet, int toInlet, int linkType){

    // CONNECT FROM "SOME" OBJECT WITH THIS ONE (DRAGGING LINK FROM ANOTHER OBJECT TO SOME INLET OF THIS OBJECT)
#ifdef SKIPTHISOLDPART
    bool connected = false;

    if( (nodes[fromObjectID] != nullptr) && (fromObjectID!=this->_id) && (this->_id != -1) ){

        cout << "Mosaic :: "<< "Connect  " << ofToString(fromObjectID) << " to object " << ofToString(this->_id) << endl;

        shared_ptr<PatchLink> tempLink = shared_ptr<PatchLink>(new PatchLink());

        string tmpID = ofToString(fromObjectID)+ofToString(fromOutlet)+ofToString(this->_id)+ofToString(toInlet);

        tempLink->id            = stoi(tmpID);
        tempLink->type          = linkType;
        tempLink->fromOutletID  = fromOutlet;
        tempLink->toObjectID    = this->_id;
        tempLink->toInletID     = toInlet;

        nodes[fromObjectID]->linksTo.push_back(tempLink);

        if(tempLink->type == VP_LINK_NUMERIC){
            this->_inletParams[toInlet] = new float();
        }else if(tempLink->type == VP_LINK_STRING){
            this->_inletParams[toInlet] = new std::string();
        }else if(tempLink->type == VP_LINK_ARRAY){
            this->_inletParams[toInlet] = new std::vector<float>();
        }else if(tempLink->type == VP_LINK_PIXELS){
            this->_inletParams[toInlet] = new ofPixels();
        }else if(tempLink->type == VP_LINK_TEXTURE){
            this->_inletParams[toInlet] = new ofTexture();
        }else if(tempLink->type == VP_LINK_AUDIO){
            this->_inletParams[toInlet] = new ofSoundBuffer();
        }

        connected = true;

    }

    return connected;
#else
    if( (nodes[fromObjectID] != nullptr) && (fromObjectID!=this->_id) && (this->_id != -1) ){
        // todo: if link is connected -> disonnect ?
        //if(this->)

        // Get own parameter to connect
        if( parameters[toInlet] != nullptr){
            AbstractHasModifier& toParam = parameters[toInlet]->getAsHasModifier();
            //AbstractParameter& toFullTmp = *parameters[toInlet];
            //auto& toParamAlt = *parameters[toInlet];
            auto& fromNode = nodes[fromObjectID];
            auto& fromParam = fromNode->parameters[fromOutlet];
            //std::cout << "InletToParam=" << parameters[toInlet]->getUID() << " / " << fromParam->getUID() << std::endl;

            if(!fromParam->hasOutlet()){
                cout << "mosaicNode::connectFrom() : FromParameter ain't got no outlet ! (aborting)"  << endl;
                return false;
            }
            else {
                //AbstractHasInlet& toInlet = toParam
                //fromParam->getAsOutlet().c
                //InletModifier& toParam.getModifier< InletModifier >();
            }

            //toTmp->getAsInlet().onPinConnected();
            std::cout << "mosaicNode::connectFrom() --> connecting parameter, from["<< fromOutlet <<"]=" << fromParam->getUID() << ", to["<< toInlet <<"]=" << parameters[toInlet]->getUID() << endl;//"/" << toTmp->getAsAbstract().dataHasChanged() << "/" << toParam.acceptsLinkType(VP_LINK_NUMERIC) << std::endl;

            //parameters[toInlet]->
            try {
                AbstractHasOutlet& outlet = fromParam->getAsOutlet();
                //fromParam->getAsInlet();
                //assert( &outlet == NULL );
                return toParam.connectWithOutlet( outlet );
            }
            catch(VPError _error){
                std::cout << "Cannot convert to outlet! (normal) -- " << _error << std::endl;
                return false;
            }
            catch(...){
                // Parameter has no outlet !
                std::cout << "Cannot convert to outlet! (normal)" << std::endl;
                return false;
            };
        }
        else {
            ofLogNotice("MosaicNode") << "Pin connection failed : fromOutlet("<< fromOutlet << ") doesn't exist.";
        }
    }
    std::cout << "mosaicNode::connectFrom() --> failed to connect" << std::endl;
    return false;
#endif
}

//--------------------------------------------------------------
void mosaicNode::disconnectFrom(std::map<int,std::shared_ptr<mosaicNode>> &nodes, int objectInlet){

    // DISCONNECT EXISTING LINK FROM INLET (ONLY ONE LINK CAN CONNECT TO AN INLET)

    for(std::map<int,shared_ptr<mosaicNode>>::iterator it = nodes.begin(); it != nodes.end(); it++ ){
        for(int j=0;j<static_cast<int>(it->second->linksTo.size());j++){
            if(it->second->linksTo[j]->toObjectID == this->_id && it->second->linksTo[j]->toInletID == objectInlet){
                // remove link
                vector<bool> tempEraseLinks;
                for(int s=0;s<static_cast<int>(it->second->linksTo.size());s++){
                    if(it->second->linksTo[s]->toObjectID == this->_id && it->second->linksTo[s]->toInletID == objectInlet){
                        tempEraseLinks.push_back(true);
                    }else{
                        tempEraseLinks.push_back(false);
                    }
                }

                std::vector<std::shared_ptr<PatchLink>> tempBuffer;
                tempBuffer.reserve(it->second->linksTo.size()-tempEraseLinks.size());

                for(int s=0;s<static_cast<int>(it->second->linksTo.size());s++){
                    if(!tempEraseLinks[s]){
                        tempBuffer.push_back(it->second->linksTo[s]);
                    }
                }

                it->second->linksTo = tempBuffer;

                break;
            }

        }

    }
}

//--------------------------------------------------------------
void mosaicNode::disconnectLink(std::map<int,std::shared_ptr<mosaicNode>> &nodes, int linkID){

    // DISCONNECT SELECTED LINK (CLICK AND REMOVE)

    for(std::map<int,shared_ptr<mosaicNode>>::iterator it = nodes.begin(); it != nodes.end(); it++ ){
        for(int j=0;j<static_cast<int>(it->second->linksTo.size());j++){
            if(it->second->linksTo[j]->id == linkID){
                // remove link
                vector<bool> tempEraseLinks;
                for(int s=0;s<static_cast<int>(it->second->linksTo.size());s++){
                    if(it->second->linksTo[s]->id == linkID){
                        tempEraseLinks.push_back(true);
                    }else{
                        tempEraseLinks.push_back(false);
                    }
                }

                std::vector<std::shared_ptr<PatchLink>> tempBuffer;
                tempBuffer.reserve(it->second->linksTo.size()-tempEraseLinks.size());

                for(int s=0;s<static_cast<int>(it->second->linksTo.size());s++){
                    if(!tempEraseLinks[s]){
                        tempBuffer.push_back(it->second->linksTo[s]);
                    }
                }

                it->second->linksTo = tempBuffer;

                break;
            }

        }

    }
}

int mosaicNode::getNumInlets(){
    return numInlets;
}
int mosaicNode::getNumOutlets(){
    return parameters.size() + myDynamicParams.size();// numOutlets;
}
int mosaicNode::getIsResizable(){
    return true;
}
int mosaicNode::getIsTextureObject(){
    return false;
}
