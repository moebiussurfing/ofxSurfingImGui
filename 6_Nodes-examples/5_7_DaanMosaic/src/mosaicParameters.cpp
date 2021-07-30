#include "mosaicParameters.h"
#include <string>
#include <initializer_list>

// Initialise static members
std::vector<AbstractParameter*> AbstractParameter::allParams = std::vector<AbstractParameter*>();

//template<> LinkType& getLinkType<long double>() {   static LinkType link_double = VP_LINK_NUMERIC;  return link_double; };
//template<> LinkType& getLinkType<float      >() {   static LinkType link_float = VP_LINK_NUMERIC;   return link_float;  };
//template<> LinkType& getLinkType<int        >() {   static LinkType link_int = VP_LINK_NUMERIC;     return link_int;    };
//template<> LinkType& getLinkType<std::string>() {   static LinkType link_string = VP_LINK_STRING;   return link_string; };
//template<> LinkType& getLinkType<char[]     >() {   static LinkType link_char = VP_LINK_STRING;     return link_char;   };
//template<> LinkType getLinkType<array>() { return VP_LINK_ARRAY; };
//template<> LinkType getLinkType<ofTexture>() { return VP_LINK_TEXTURE; };
//template<> LinkType getLinkType<ofSoundBuffer>() { return VP_LINK_SPECIAL; };
//template<> LinkType getLinkType<ofAudioBuffer>() { return VP_LINK_AUDIO; };
//template<> LinkType getLinkType<ofPixels>() { return VP_LINK_PIXELS; };

//template<> const char* getLinkName<long double>(long double) { return "VP_LINK_NUMERIC"; };
//template<> const char* getLinkName<float>(float) { return "VP_LINK_NUMERIC"; };
//template<> const char* getLinkName<int>(int) { return "VP_LINK_NUMERIC"; };
//template<> const char* getLinkName<std::string>(std::string) { return "VP_LINK_STRING"; };
//template<> const char* getLinkName<char[]>(char[]) { return "VP_LINK_STRING"; };

std::ostream& operator << (std::ostream& _out, const VPError& _e){
    _out << "VPError=[" << _e.code << "/" << _e.status << "] " << _e.message << std::endl;
    return _out;
};

// Set / Declare all linktype data on compile time.
// Note: static constexpr variables need to be defined in the header, AND declared in the .cpp
#define DECLARE_COLOR_FOR(LINKTYPE) constexpr const unsigned char ofxVPLinkTypeInfo< LINKTYPE >::color[4];
#define DEFINE_OFCOLOR_FOR(LINKTYPE) const ofColor ofxVPLinkTypeInfo< LINKTYPE >::ofColour = { ofxVPLinkTypeInfo<LINKTYPE>::color[0], ofxVPLinkTypeInfo<LINKTYPE>::color[1], ofxVPLinkTypeInfo<LINKTYPE>::color[2], ofxVPLinkTypeInfo<LINKTYPE>::color[3] };
#define DECLARE_IMCOLOR_FOR(LINKTYPE) constexpr const ImU32 ofxVPLinkTypeInfo< LINKTYPE >::imguiColor;// = IM_COL32( ofxVPLinkTypeInfo< LINKTYPE >::color[0],ofxVPLinkTypeInfo< LINKTYPE >::color[1], ofxVPLinkTypeInfo< LINKTYPE >::color[2], ofxVPLinkTypeInfo< LINKTYPE >::color[3] );
#define DECLARE_LINKNAME_FOR(LINKTYPE) constexpr const char ofxVPLinkTypeInfo< LINKTYPE >::linkName[];
#define DECLARE_LINKTYPE_FOR(LINKTYPE) constexpr const LinkType ofxVPLinkTypeInfo< LINKTYPE >::linkType;
#define SET_VARIABLES_FOR(LINKTYPE) DECLARE_COLOR_FOR(LINKTYPE) DEFINE_OFCOLOR_FOR(LINKTYPE) DECLARE_IMCOLOR_FOR(LINKTYPE) DECLARE_LINKNAME_FOR(LINKTYPE) DECLARE_LINKTYPE_FOR(LINKTYPE)

SET_VARIABLES_FOR( VP_LINK_UNDEFINED );
SET_VARIABLES_FOR( VP_LINK_NUMERIC );
SET_VARIABLES_FOR( VP_LINK_STRING );
SET_VARIABLES_FOR( VP_LINK_ARRAY );
SET_VARIABLES_FOR( VP_LINK_TEXTURE );
SET_VARIABLES_FOR( VP_LINK_AUDIO );
SET_VARIABLES_FOR( VP_LINK_SPECIAL );
SET_VARIABLES_FOR( VP_LINK_PIXELS );

//ofxVPLinkTypeInfo<VP_LINK_UNDEFINED>::allSubTypesTest myThing;

// - - - - - - - - - -
// TYPE some parameters
// - - - - - - - - - -
// INT SPECIALISATIONS
template<>
void Parameter<int>::drawImGui() {
    ImGui::PushID(this->getUID().c_str()); // todo: do this before calling drawImGui() ?

    ImGui::AlignTextToFramePadding();

    if(!this->getIsEditable()){
        //ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true); // todo: wrap this inner ImGui function into a small ImGuiEx
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }
    //ImGui::SetNextItemWidth(-1); // sets item to take full witdh. Not rendered well for now.
    // todo: remove const_cast somehow ?
    ImGui::DragInt( this->getDisplayName().c_str(), const_cast<int*>(&this->getValue()) );

    if(!this->getIsEditable()){
        //ImGui::PopItemFlag(); // todo: same as above
        ImGui::PopStyleVar();
    }

    // listen for GUI connections
    this->ImGuiListenForParamDrop();

    // tmp, menu
    this->ImGuiShowInfoMenu();

    // outlet connector
    //ImGuiDrawParamConnector();

    ImGui::PopID();
};
template<>
std::string Parameter<int>::serialize(const bool& _serializeStoredValue) const {
    return std::to_string( _serializeStoredValue ? this->storedValue : this->dataValue );
};
template<>
bool Parameter<int>::unserialize( const std::string& _value, const bool& _unserializeToStoredValue ) {
    if(_unserializeToStoredValue) this->storedValue = std::stoi(_value);
    this->dataValue = std::stoi(_value);
    return true;
};
// - - - - - - - - - -
// FLOAT SPECIALISATIONS
template<>
void Parameter<float>::drawImGui() {
    ImGui::PushID(this->getUID().c_str()); // todo: do this before calling drawImGui() ?

    // inlet connector
    //this->drawImGuiParamPin(true);

    if(!this->getIsEditable()){
        //ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true); // todo: wrap this inner ImGui function into a small ImGuiEx
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }
    // todo: remove const_cast somehow ? (undefined c++ behaviour)
    ImGui::DragFloat(this->getDisplayName().c_str(), const_cast<float*>(&this->getValue()) );//const_cast<float*>(&this->getValue()) );
    if(!this->getIsEditable()){
        //ImGui::PopItemFlag(); // todo: same as above
        ImGui::PopStyleVar();
    }

    // listen for GUI connections
    this->ImGuiListenForParamDrop();

    // outlet connector
    //this->drawImGuiParamPin(false);

    // tmp, menu
    this->ImGuiShowInfoMenu();

    ImGui::PopID();
};
template<>
std::string Parameter<float>::serialize(const bool& _serializeStoredValue) const {
    return std::to_string( _serializeStoredValue ? this->storedValue : this->dataValue );
};
template<>
bool Parameter<float>::unserialize( const std::string& _value, const bool& _unserializeToStoredValue ) {
    if(_unserializeToStoredValue) this->storedValue = std::stof(_value);
    this->dataValue = std::stof(_value);

    // todo: bflagDataChanged

    return true;
};
// - - - - - - - - - -
// STRING SPECIALISATIONS
template<>
void Parameter<std::string>::drawImGui() {
    ImGui::PushID(this->getUID().c_str()); // todo: do this before calling drawImGui() ?

    // inlet connector
    //ImGuiDrawParamConnector(true);

    if(!this->getIsEditable()){
        //ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true); // todo: wrap this inner ImGui function into a small ImGuiEx
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }
    // todo: remove const_cast somehow ?
    ImGui::InputText(this->getDisplayName().c_str(), static_cast<std::string *>( const_cast<std::string*>(&this->getValue() )));
    if(!this->getIsEditable()){
        //ImGui::PopItemFlag(); // todo: same as above
        ImGui::PopStyleVar();
    }

    // listen for GUI connections
    ImGuiListenForParamDrop();

    // tmp, menu
    ImGuiShowInfoMenu();

    // outlet connector
    //ImGuiDrawParamConnector();

    ImGui::PopID();
};
template<>
std::string Parameter<std::string>::serialize(const bool& _serializeStoredValue) const {
    return _serializeStoredValue ? this->storedValue : this->dataValue;
};
template<>
bool Parameter<std::string>::unserialize( const std::string& _value, const bool& _unserializeToStoredValue ) {
    if(_unserializeToStoredValue) this->storedValue = _value;
    else this->dataValue = _value;
    return true;
};
