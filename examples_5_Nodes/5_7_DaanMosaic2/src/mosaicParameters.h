// - - - - - - - - - -

// Notes on implementation choices :

// VIRTUALS and ABSTRACTS RELATIONSHIP
// To make abstracts (typed objects with common methods and a fixed footprint for holding them in lists), we need the virtual keyword to define an "entry door". Virtuals are resolved on run-time, which is not the fastest; with -02 compile optimisation, they become faster; to be tested/benched. In the optimal scenario, this (calling a method from an abstract) should be the only valid reason for using virtuals. Think `virtual myApiMethod();`. Intern functions better use static crtp.
// Alternatively, to prevent virtuals usage, we could use c++11 functors. On instantiation, you register a function address, then call it when you need to. More like a simplified static event notifier.

// TEMPLATES
// Most definitions need to be in the .h file because of Implicit template instantiation.
// Tool tor seeing how the compiler "builds" your templated code : https://cppinsights.io/

// - - - - - - - - - -

// Good reads :
// - https://www.fluentcpp.com/2017/05/16/what-the-crtp-brings-to-code/

// - - - - - - - - - -

// TODO // ROADMAP :

// 2 - Enforce data types and link types.

// 3 - implement all the other classes from the VPParams scheme @Github#22

// 4 - implement more complex connections

// 5 - implement the load/save mechanism

// 6 - test it

// 7 - clean the code

// 8 - integrate in Mosaic/ofxVisualProgramming

// Perfectioning :
// - const correctness
// - private / protected / public
// - mark some members mutable ? (mutables can change when the [self/parent] instance is marked const)

// - - - - - - - - - -

#pragma once
#ifndef MOSAIC_PARAMETERS
#define MOSAIC_PARAMETERS

#include <iostream>
#include <list>

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_node_canvas.h"
#include "ofxVPHasUid.h"
#include "ofxXmlSettings.h"

// - - - - - - - - - -

// Define link types.
// Todo: make this a factory.
// all possible links
enum LinkType : unsigned char { // unsigned char has a smaller footprint
    VP_LINK_UNDEFINED   = 255, // NULLPTR / UNDEFINED_TYPE equivalence ??
    VP_LINK_NUMERIC     = 0,
    VP_LINK_STRING      = 1,
    VP_LINK_ARRAY       = 2,
    VP_LINK_TEXTURE     = 3,
    VP_LINK_AUDIO       = 4,
    VP_LINK_SPECIAL     = 5,
    VP_LINK_PIXELS      = 6,
};

template<typename ENUM, typename KEY_TYPE, ENUM ...INDEXES >
struct EnumIterator {
public:
    constexpr EnumIterator() = default;
    ~EnumIterator() = default;

    using Enum_t = ENUM;
    using Value_t = KEY_TYPE;

    static constexpr const std::size_t numKeys = { sizeof...(INDEXES) };
    static constexpr const Enum_t keys[sizeof...(INDEXES)] = { INDEXES... };
//    static constexpr const std::array<const Enum_t, sizeof...(INDEXES) > keys = {
//        {INDEXES...}
//    };

    // Iterator support
    static constexpr const Enum_t& begin() noexcept { return keys[0]; };
    static constexpr const Enum_t& end() noexcept { return keys[numKeys-1]; };
    // pointer begin() & end()
    static constexpr const Enum_t* const pBegin() noexcept { return &keys[0]; };
    static constexpr const Enum_t* const pEnd() noexcept { return (&keys[numKeys-1]+1); };

//	constexpr explicit EnumValue(const EnumValue &) = default;
//	constexpr EnumValue &operator=(const EnumValue &) = default;
//
//	constexpr operator TYPE() const {return value_;}
//	constexpr TYPE value() const {return value_;}
    // Give implicit direct access to underlying data
    //constexpr const operator KEY_TYPE() const {return keys;}
    //constexpr Enum value() const { return keys; }
//	constexpr const Enum operator ++( const Enum _value){
//		return keys[keys.find(_value)];
//	}

    // ValueType to Enum type (constrain to possible values)
    static constexpr const Enum_t& getEnumFromKeyType( const Value_t& _value ) {
        // If key exists, return key. Else return not found value (pEnd())
        return (Enum_t)((static_cast<const Value_t>(static_cast<const Enum_t>(_value)) == _value)? _value : *keys.pEnd() );
    }
    // Allows getting the enum value by index
    static constexpr const Enum_t& getEnumByIndex( const std::size_t& _index ) {
        return keys[ _index ];
    }
    // Returns the index of a given Enum
    static constexpr std::size_t getIndexOfEnum( const Enum_t& _enum ) {
        return std::distance(&keys[0], std::find(&keys[0], &keys[numKeys-1], _enum)) < numKeys ? std::distance(&keys[0], std::find(&keys[0], &keys[numKeys-1], _enum)) : -1;
    }

    // Array access
    inline constexpr const Enum_t& operator [](const std::size_t& _index) const { // index-based access
        //return (Enum) keys[ _index % (numKeys-1)];
        return getEnumByIndex(_index);
    }
    // Char operator, constrain to closest valid value
    inline constexpr const Enum_t& operator [](const Value_t& _value) const {
        return getEnumFromChar(_value);
    }
};
template<typename ENUM, typename KEY_TYPE, ENUM ...INDEXES >
constexpr const ENUM EnumIterator<ENUM, KEY_TYPE, INDEXES...>::keys[]; // has to be declared too !
//constexpr const std::array<const ENUM, sizeof...(INDEXES)> EnumIterator<ENUM, KEY_TYPE, INDEXES...>::keys;

// LinkType iterator utility
//static constexpr const EnumIterator<LinkType, unsigned char, LinkType::VP_LINK_UNDEFINED, LinkType::VP_LINK_NUMERIC, LinkType::VP_LINK_STRING, LinkType::VP_LINK_ARRAY, LinkType::VP_LINK_TEXTURE, LinkType::VP_LINK_PIXELS, LinkType::VP_LINK_AUDIO, LinkType::VP_LINK_SPECIAL> LinkTypeIterator;
//using LinkTypeIterator = EnumIterator<LinkType, unsigned char, LinkType::VP_LINK_UNDEFINED, LinkType::VP_LINK_NUMERIC, LinkType::VP_LINK_STRING, LinkType::VP_LINK_ARRAY, LinkType::VP_LINK_TEXTURE, LinkType::VP_LINK_PIXELS, LinkType::VP_LINK_AUDIO, LinkType::VP_LINK_SPECIAL>;
#define DEFINE_ENUM_ITERATOR(NAME, ENUM, TYPE, VALUES...)\
    using NAME = EnumIterator<ENUM, TYPE , VALUES >;\
    inline ENUM operator++(ENUM& c, int) { /* post increment operator */ \
        if(c == *NAME::pEnd()){ /* Feature: loop once pEnd has been reached */ \
            return NAME::begin();\
        }\
        \
        int found = NAME::getIndexOfEnum(c);\
        if( found != -1 ){\
            c = NAME::getEnumByIndex(found+1);\
            return NAME::getEnumByIndex(found);\
        }\
        else{ return NAME::end(); }\
    }; \
    inline ENUM operator++(ENUM& c) { /* pre-increment operator */ \
        if(c == *NAME::pEnd()){ /* Feature: loop once pEnd has been reached */ \
            return NAME::begin(); \
        } \
        \
        int found = NAME::getIndexOfEnum(c); \
        if( found != -1 ){ \
            c = NAME::getEnumByIndex(found+1); \
            return c; \
        } \
        else return NAME::end(); \
    }; \

// Declare all link types once here
// Precomposer has access to 1st line, template composer to both.
#define VP_ALL_LINK_TYPES LinkType::VP_LINK_UNDEFINED, LinkType::VP_LINK_NUMERIC, LinkType::VP_LINK_STRING, LinkType::VP_LINK_ARRAY, LinkType::VP_LINK_TEXTURE, LinkType::VP_LINK_PIXELS, LinkType::VP_LINK_AUDIO, LinkType::VP_LINK_SPECIAL
DEFINE_ENUM_ITERATOR(LinkTypeIterator, LinkType, unsigned char, VP_ALL_LINK_TYPES);

// Todo: remove these
#define COLOR_NUMERIC           ofColor(210,210,210,255)
#define COLOR_STRING            ofColor(200,180,255,255)
#define COLOR_ARRAY             ofColor(120,255,120,255)
#define COLOR_PIXELS            ofColor(0,  180,140,255)
#define COLOR_TEXTURE           ofColor(120,255,255,255)
#define COLOR_AUDIO             ofColor(255,255,120,255)
#define COLOR_SCRIPT            ofColor(255,128,128,255)
#define COLOR_SPECIAL           ofColor(255,255,255,255)
#define COLOR_UNDEFINED         ofColor(0,  0,  0,  255)

// C++ typelist, recursive implementation
template <typename ... Types>
struct TypeList {
    //using myTypes = ;
    constexpr TypeList(){};
};

//static constexpr TypeList<> VPAllLinkDataTypes(); // needed ?
//static constexpr TypeList<> VPAllLinkTypes();

// Inner type setup
template <LinkType VP_LINK_TYPE>
struct ofxVPLinkTypeInfo;

// Data type to link type conversion (This is non-standard in C++14, fallback below)
// Will be individually overruled by data types
template<typename DATA_TYPE>
static constexpr const LinkType& getLinkTypeFromDataType();

// Data type to link name conversion (static)
template<typename DATA_TYPE>
inline const char* getLinkNameFromDataType() { // from link type
    return ofxVPLinkTypeInfo< getLinkTypeFromDataType<DATA_TYPE>() >::linkName;
};

// Get Link name from type (static)
template<LinkType LINK_TYPE>
static constexpr const char* getLinkName(){
    return ofxVPLinkTypeInfo< LINK_TYPE >::linkName;
};

// Macro Helper to output 1 line per argument, 1 to 10 args.
#define ROUTE_DATA_TO_MACRO_10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME
#define ROUTE_DATA_TO_MACRO_SIMPLE( VALS... ) ROUTE_DATA_TO_MACRO_10( VALS, DATA_MACRO_10, DATA_MACRO_9, DATA_MACRO_8, DATA_MACRO_7, DATA_MACRO_6, DATA_MACRO_5, DATA_MACRO_4, DATA_MACRO_3, DATA_MACRO_2, DATA_MACRO_1 )
#define DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1 ) THEMACRO(ARG1, VARIABLE1)
#define DATA_MACRO_2( THEMACRO, ARG1, VARIABLE1, VARIABLE2) DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1) DATA_MACRO_1(THEMACRO, ARG1, VARIABLE2)
#define DATA_MACRO_3( THEMACRO, ARG1, VARIABLE1, VARIABLE2, VARIABLE3)  DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1) DATA_MACRO_2( THEMACRO, ARG1, VARIABLE2, VARIABLE3)
#define DATA_MACRO_4( THEMACRO, ARG1, VARIABLE1, VARIABLE2, VARIABLE3, VARIABLE4)  DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1) DATA_MACRO_3( THEMACRO, ARG1, VARIABLE2, VARIABLE3, VARIABLE4)
#define DATA_MACRO_5( THEMACRO, ARG1, VARIABLE1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5) DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1) DATA_MACRO_4( THEMACRO, ARG1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5)
#define DATA_MACRO_6( THEMACRO, ARG1, VARIABLE1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6) DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1) DATA_MACRO_5( THEMACRO, ARG1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6)
#define DATA_MACRO_7( THEMACRO, ARG1, VARIABLE1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7) DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1) DATA_MACRO_6( THEMACRO, ARG1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7)
#define DATA_MACRO_8( THEMACRO, ARG1, VARIABLE1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7, VARIABLE8) DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1) DATA_MACRO_7( THEMACRO, ARG1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7, VARIABLE8)
#define DATA_MACRO_9( THEMACRO, ARG1, VARIABLE1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7, VARIABLE8, VARIABLE9) DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1) DATA_MACRO_8( THEMACRO, ARG1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7, VARIABLE8, VARIABLE9)
#define DATA_MACRO_10( THEMACRO, ARG1, VARIABLE1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7, VARIABLE8, VARIABLE9, VARIABLE10) DATA_MACRO_1( THEMACRO, ARG1, VARIABLE1) DATA_MACRO_9( THEMACRO, ARG1, VARIABLE2, VARIABLE3, VARIABLE4, VARIABLE5, VARIABLE6, VARIABLE7, VARIABLE8, VARIABLE9, VARIABLE10)

// Helper func for the definition below
#define DECLARE_DATA2LINKTYPE(TYPE, DATA...) ROUTE_DATA_TO_MACRO_SIMPLE( DATA )( DECLARE_DATA2LINKTYPE1, TYPE, DATA )
#define DECLARE_DATA2LINKTYPE1(TYPE, DATA) \
    template<> constexpr const LinkType& getLinkTypeFromDataType< DATA >(){ return ofxVPLinkTypeInfo< TYPE >::linkType; };
//    template<> constexpr LinkType getLinkTypeFromDataType< DATA >(){ return TYPE; };

// Static link information (compile-time constructed)
#define VP_REGISTER_LINKTYPE(TYPE, NAME, R, G, B, SUBTYPES...)\
    template <>\
    struct ofxVPLinkTypeInfo< TYPE > {\
    public:\
      using allSubTypes = TypeList< SUBTYPES >;\
      static constexpr const unsigned char color[4] = { R,  G,  B, 255 };\
      static const ofColor ofColour;\
      /*static inline const ofColor ofColourOldToDelete(){ return ofColor( R, G, B, 255 ); };*/ \
      static constexpr const ImU32 imguiColor ={ IM_COL32(R,G,B,255) };\
      static constexpr const LinkType linkType = { TYPE };\
      static constexpr const char linkName[sizeof(NAME)] = { NAME }; \
    };\
    DECLARE_DATA2LINKTYPE(TYPE,SUBTYPES)\

// End Define
class Special{};// tmp
//class Data{};// tmp
VP_REGISTER_LINKTYPE( VP_LINK_UNDEFINED, "Undefined", 0  , 0  , 0,   void           )
VP_REGISTER_LINKTYPE( VP_LINK_NUMERIC,   "Numeric"  , 210, 210, 210, int, float, double     )
VP_REGISTER_LINKTYPE( VP_LINK_STRING,    "String"   , 200, 180, 255, std::string    )
VP_REGISTER_LINKTYPE( VP_LINK_ARRAY,     "Data"     , 120, 255, 120, int[], float[] )
VP_REGISTER_LINKTYPE( VP_LINK_TEXTURE,   "Texture"  , 120, 255, 255, ofTexture      )
VP_REGISTER_LINKTYPE( VP_LINK_AUDIO,     "Audio"    , 255, 255, 120, ofSoundBuffer  )
VP_REGISTER_LINKTYPE( VP_LINK_SPECIAL,   "Special"  , 255, 255, 255, Special        )
VP_REGISTER_LINKTYPE( VP_LINK_PIXELS,    "Pixels"   , 0  , 180, 140, ofPixels       )

// Fallback template
template<typename DATA_TYPE>
static constexpr const LinkType& getLinkTypeFromDataType() {
    return ofxVPLinkTypeInfo<VP_LINK_UNDEFINED>::linkType;
 };

//#define IF_ELSE_SWITCH( CONDITION, STATEMENT, VARIABLES... ) ROUTE_DATA_TO_MACRO_10( VARIABLES, IF_ELSE_SWITCH10, IF_ELSE_SWITCH9, IF_ELSE_SWITCH8, IF_ELSE_SWITCH7, IF_ELSE_SWITCH6, IF_ELSE_SWITCH5, IF_ELSE_SWITCH4, IF_ELSE_SWITCH3, IF_ELSE_SWITCH2, IF_ELSE_SWITCH1 )( CONDITION, STATEMENT, VARIABLES )
#define IF_ELSE_SWITCH( VARIABLES... ) \
    ROUTE_DATA_TO_MACRO_SIMPLE( VARIABLES )( IF_ELSE_SWITCH1, NULL, VARIABLES )

// Get link name, dynamic
inline constexpr const char* getLinkName(const LinkType& _linkType){
    // C++14 will allow a for-loop in here ?
    // for( LinkTypeIterator::Value_t linkType : LinkTypeIterator::keys){
    //    if( _linkType==linkType ) return ofxVPLinkTypeInfo<linkType   >::linkName;
    // }
    //ofxVPLinkTypeInfo
    //return ofxVPLinkTypeInfo< VP_LINK_UNDEFINED >::linkName;
    return
            // Compiles to multiple lines like :
            // _linkType == VP_LINK_NUMERIC ?  ofxVPLinkTypeInfo<VP_LINK_NUMERIC   >::linkName :
#define IF_ELSE_SWITCH1(ARG1, VARIABLE1) \
            _linkType == VARIABLE1 ? ofxVPLinkTypeInfo< VARIABLE1 >::linkName :
            IF_ELSE_SWITCH( VP_ALL_LINK_TYPES )
#undef IF_ELSE_SWITCH1
            // default value
            ofxVPLinkTypeInfo<VP_LINK_UNDEFINED >::linkName ;
};


// compile-time utility for converting type-values to assiociated linktype
// maybe ?
//#define GET_LINKTYPE(X) _Generic( (X), \
//    long double: VP_LINK_NUMERIC, \
//    float: VP_LINK_NUMERIC, \
//    int: VP_LINK_NUMERIC, \
//    std::string : VP_LINK_STRING, \
//    char[]: VP_LINK_STRING, \
//    array: VP_LINK_ARRAY, \
//    ofTexture: VP_LINK_TEXTURE, \
//    ofSoundBuffer: VP_LINK_SPECIAL, \
//    ofAudioBuffer: VP_LINK_AUDIO, \
//    ofPixels: VP_LINK_PIXELS, \
//    default: VP_LINK_UNDEFINED  \
//)(X)

// Constexpr utilities, with optimisation compile flags (-O3), this should be as fast as a switch statement
template<constexpr const int I=LinkTypeIterator::numKeys-1>
inline constexpr const char* getLinkName(const LinkType& _linkType){
    // A bit tricky, a kind of recursive switch, for each enum, array search
    return ( LinkTypeIterator::getEnumByIndex(I) ==_linkType)?ofxVPLinkTypeInfo< LinkTypeIterator::getEnumByIndex(I) >::linkName : getLinkName<(I-1)>( _linkType );//
};
template<>
inline constexpr const char* getLinkName<0>(const LinkType& _linkType){
    // C++14 feature, but it compiles with clang in C++11, gives more informative errors when it can't compile as a consexpr
    //constexpr const LinksIterator::Enum_t& CUR = LinksIterator::getEnumByIndex(0);
    return ( LinkTypeIterator::getEnumByIndex(0) ==_linkType)? ofxVPLinkTypeInfo< LinkTypeIterator::getEnumByIndex(0) >::linkName : "UNNAMED_LINK";
};

//template<typename DATA_TYPE>
//inline LinkType& getLinkType() { // from value type to link type
//    static LinkType link_undefined = VP_LINK_UNDEFINED;
//    return link_undefined;
//};
//template<typename DATA_TYPE>
//static constexpr LinkType getLinkTypeFromDataType = VP_LINK_UNDEFINED;

// Get link type from data type
//template<typename DATA_TYPE>  // Value-call maps to typename-call
//inline constexpr LinkType& getLinkTypeFromDataType() {
//    //return getLinkTypeFromDataType<DATA_TYPE>;
//    return ofxVPLinkTypeInfo< getLinkTypeFromDataType<DATA_TYPE>() >::linkType;
//};

inline const ofColor getLinkColor(const LinkType& _linkType) { // from link type
    switch (_linkType) {
        case VP_LINK_NUMERIC:       return ofxVPLinkTypeInfo<VP_LINK_NUMERIC>::ofColour;
        case VP_LINK_STRING:        return ofxVPLinkTypeInfo<VP_LINK_STRING>::ofColour;
//        case VP_LINK_ARRAY:         return ofxVPLinkTypeInfo<VP_LINK_ARRAY>::ofColour;
//        case VP_LINK_TEXTURE:       return ofxVPLinkTypeInfo<VP_LINK_TEXTURE>::ofColour;
//        case VP_LINK_AUDIO:         return ofxVPLinkTypeInfo<VP_LINK_AUDIO>::ofColour;
//        case VP_LINK_SPECIAL:       return ofxVPLinkTypeInfo<VP_LINK_SPECIAL>::ofColour;
//        case VP_LINK_PIXELS:        return ofxVPLinkTypeInfo<VP_LINK_PIXELS>::ofColour;
        //case VP_LINK_SCRIPT:        return COLOR_SCRIPT;
        default:                    return ofxVPLinkTypeInfo<VP_LINK_UNDEFINED>::ofColour;
    }
};
// This function returns the type from a runtime variable (dynamic).
static constexpr ImU32 getLinkImguiColor(const LinkType& _linkType) { // from link type
//    const ofColor& color = getLinkColor(_linkType);
//    return IM_COL32(color.r*255, color.g*255, color.b*255, color.a*255);
//    switch (_linkType) {
//        case VP_LINK_NUMERIC:       return ofxVPLinkTypeInfo<VP_LINK_NUMERIC>::imguiColor; break;
//        case VP_LINK_STRING:        return ofxVPLinkTypeInfo<VP_LINK_STRING>::imguiColor; break;
//        case VP_LINK_ARRAY:         return ofxVPLinkTypeInfo<VP_LINK_ARRAY>::imguiColor;
//        case VP_LINK_TEXTURE:       return ofxVPLinkTypeInfo<VP_LINK_TEXTURE>::imguiColor;
//        case VP_LINK_AUDIO:         return ofxVPLinkTypeInfo<VP_LINK_AUDIO>::imguiColor;
//        case VP_LINK_SPECIAL:       return ofxVPLinkTypeInfo<VP_LINK_SPECIAL>::imguiColor;
//        case VP_LINK_PIXELS:        return ofxVPLinkTypeInfo<VP_LINK_PIXELS>::imguiColor;
        //case VP_LINK_SCRIPT:        return COLOR_SCRIPT;
//        default:                    return ofxVPLinkTypeInfo<VP_LINK_UNDEFINED>::imguiColor; break;
//    }
      return
            _linkType == VP_LINK_NUMERIC ?  ofxVPLinkTypeInfo<VP_LINK_NUMERIC   >::imguiColor :
            _linkType == VP_LINK_STRING  ?  ofxVPLinkTypeInfo<VP_LINK_STRING    >::imguiColor :
            _linkType == VP_LINK_ARRAY   ?  ofxVPLinkTypeInfo<VP_LINK_ARRAY     >::imguiColor :
            _linkType == VP_LINK_TEXTURE ?  ofxVPLinkTypeInfo<VP_LINK_TEXTURE   >::imguiColor :
            _linkType == VP_LINK_AUDIO   ?  ofxVPLinkTypeInfo<VP_LINK_AUDIO     >::imguiColor :
            _linkType == VP_LINK_SPECIAL ?  ofxVPLinkTypeInfo<VP_LINK_SPECIAL   >::imguiColor :
            _linkType == VP_LINK_PIXELS  ?  ofxVPLinkTypeInfo<VP_LINK_PIXELS    >::imguiColor :
                                            ofxVPLinkTypeInfo<VP_LINK_UNDEFINED >::imguiColor;
};
static constexpr ImU32 getLinkImguiColor(const LinkType& _linkType);


// - - - - - - - - - -
enum OFXVP_MODIFIER_ {
    OFXVP_MODIFIER_UNKNOWN = 0,
    OFXVP_MODIFIER_INLET = 1,
    OFXVP_MODIFIER_SCRIPTING = 2,
    OFXVP_MODIFIER_TYPE_CONVERTOR = 3,
};

inline std::string getModifierName(const OFXVP_MODIFIER_& _modifier) {
    switch (_modifier) {
        case OFXVP_MODIFIER_INLET :
            return "OFXVP_MODIFIER_INLET";
            break;
        case OFXVP_MODIFIER_SCRIPTING:
            return "OFXVP_MODIFIER_SCRIPTING";
            break;
        case OFXVP_MODIFIER_TYPE_CONVERTOR:
            return "OFXVP_MODIFIER_TYPE_CONVERTOR";
            break;
        default:
            break;
    }
    return "OFXVP_MODIFIER_UNKNOWN";
};



// - - - - - - - - - -
// To move to an included file ?
enum VPErrorCode_ {
    VPErrorCode_UNDEFINED = 0,
    VPErrorCode_LINK = 1,
    VPErrorCode_MODIFIER = 2,
};
enum VPErrorStatus_ {
    VPErrorStatus_UNDEFINED = 0,
    VPErrorStatus_NOTICE = 1,
    VPErrorStatus_WARNING = 2,
    VPErrorStatus_CRITICAL = 3,
};
struct VPError {
public:
    VPError( enum VPErrorCode_ _code=VPErrorCode_UNDEFINED, const VPErrorStatus_ _status=VPErrorStatus_UNDEFINED, std::string _message = "Unknown error.") : message(_message), code(_code), status(_status) {

    };
    const std::string message;
    const enum VPErrorCode_ code;
    const enum VPErrorStatus_ status;
    friend std::ostream & operator << (std::ostream& _out, const VPError& _e);
};
std::ostream& operator << (std::ostream& _out, const VPError& _e);
// - - - - - - - - - -

class AbstractHasInlet;
class AbstractHasOutlet;

class AbstractPinLink /*: public ofxVPHasUID*/ { // todo: does this need an UID ?
public:
    AbstractPinLink( AbstractHasInlet& _parent ) : /*ofxVPHasUID("PinLink"),*/ toPin(_parent) {

    };
    virtual ~AbstractPinLink(){};

    bool isConnected = false;
    //bool isEnabled; // needed ??
    AbstractHasOutlet* fromPin = nullptr;
    AbstractHasInlet& toPin;
};

// - - - - - - - - - -

// A Parameter can be seen as an augmented data storage.
// Augmented: an (inlet) modifier mechanism, gui visualizations/controls, load/save/restore.
// Optional: They CAN be extended with data outlets.
class AbstractHasModifier;
class AbstractParameter : public ofxVPHasUID {
public:
    //AbstractParameter() : ofxVPHasUID("AbstractParameter") {};
    AbstractParameter( std::string _paramName = "AbstractParameter") : ofxVPHasUID(_paramName){
        // Remember / Register
        allParams.push_back(this);
        //std::cout << "New Abstract Param = " << this << std::endl;
    };

    virtual ~AbstractParameter(){
        // de-register param
        std::vector<AbstractParameter*>::iterator exists = std::find(allParams.begin(), allParams.end(), this );
        if( exists != allParams.end() ){
            allParams.erase(exists);
        }
    };

    // API methods
    virtual bool saveToXML(ofxXmlSettings& _xml) const = 0;
    virtual bool loadFromXML(ofxXmlSettings& _xml) = 0;
    virtual std::string serialize(const bool& _serializeStoredValue=false) const = 0;
    virtual bool unserialize( const std::string& _value, const bool& _unserializeToStoredValue=false ) = 0;
    //virtual void update() = 0; // needed ?
    virtual void drawImGuiEditable() = 0;
    virtual void drawImGui() = 0; // needed ?
    // these 2 prevent the need of virtual inheritance, which keeps things easier
    virtual AbstractHasModifier& getAsHasModifier() = 0;
    virtual bool hasOutlet() const = 0;
    virtual AbstractHasOutlet& getAsOutlet() = 0; // todo: rename method with "try" in it, as it needs a catch
    virtual bool getIsEditable() const {
        return isEditable;
    };
    virtual void drawImGuiParamPin(ImGuiEx::NodeCanvas& _nodeCanvas, const bool& _drawInlet=false) = 0;

    // conversion
    AbstractParameter& getAsAbstract(){ return *this; };

    // Factory (tmp in here as a static)
    static const std::vector<AbstractParameter*>& getAllParams() { return allParams; };//const_cast< std::vector< AbstractParam* > >(allParams); };
protected:
    static std::vector<AbstractParameter*> allParams;
private:
    bool isEditable = true;
};

// - - - - - - - - - -
// Ensures an interface between outlets and inlets (which inherit from :haspin)
class HasPin {
public:
    HasPin(const LinkType& _linkType = VP_LINK_UNDEFINED) : linkType( _linkType ) {
        //std::cout << "New Pin : " << ToString(_linkType) << " - " << std::endl;
    };
    virtual ~HasPin(){};

    // Pin event listeners
    virtual void onPinConnected()=0; // todo : add the link as argument here ?
    virtual void onPinDisconnected()=0; // todo : add the link as argument here ?

    virtual const std::string& getPinLabel() const = 0;

    ImVec2 pinPosition;
    const LinkType& linkType;
    //ofxVPHasUID::stringKeyType owningObjectID; // needed ?

private :
    // This is an abstract you have to implement to detach pin data
    //virtual void detach() = 0;
};

// - - - - - - - - - -
template<typename ACCEPT_TYPE> class HasInlet;
template<typename ACCEPT_TYPE> class HasOutlet;
class AbstractHasInlet;
template<typename T>
class PinLink : public AbstractPinLink {
public:
    PinLink( HasInlet<T>& _parent ) : AbstractPinLink( _parent ), toPinTyped(_parent){

    };
    virtual ~PinLink(){};

    HasOutlet<T>* fromPinTyped = nullptr;
    const HasInlet<T>& toPinTyped;
};

// - - - - - - - - - -
class AbstractHasInlet : public HasPin {
public:
    AbstractHasInlet( const LinkType& _linkType ) : HasPin(_linkType) {};

    virtual bool acceptsLinkType( const LinkType& _linktype ) = 0;
    //virtual accept();
    bool connectWithOutlet(std::string _paramUID){
        // Try to get the instance
        if( AbstractParameter* abstractParam = ofxVPHasUID::getTypedInstanceByUID<AbstractParameter>(_paramUID) ){
            if(abstractParam->hasOutlet()){
                try {
                    if( this->connectWithOutlet( abstractParam->getAsOutlet() ) ){
                        // Connection done ! :)
                        return true;
                    }
                    else {
                        ofLogNotice("Parameter") << "The inlet param (me) did not accept a connection with "<< _paramUID << ". Maybe it doesn't accept my data type ?";
                    }
                } catch (...) {
                    ofLogNotice("Parameter") << "Could not parse outlet " << _paramUID << " as an outlet !" << std::endl;
                }
            }
        }
        else {
            ofLogNotice("Parameter") << "Could not parse " << _paramUID << " as a parameter ! Not connecting." << std::endl;
        }

        return false;
    };
    virtual bool connectWithOutlet( AbstractHasOutlet& _outlet ) = 0; // return bool or PinLink&  ?
    virtual bool disconnectPin() = 0;

    // Events
    virtual void onPinConnected() override = 0;
    virtual void onPinDisconnected() override = 0;
    virtual void triggerValueChanged() = 0; // todo
    //virtual const std::string& getPinLabel() const override = 0;

    std::shared_ptr<AbstractPinLink> connectedLink; // todo: not to be shared_ptr ?

    ImVec2 inletPosition = ImVec2(0,0); // Public so ImGui can change it
};

template<typename ACCEPT_TYPE>
class HasInlet : public AbstractHasInlet {
public:
    HasInlet() : AbstractHasInlet( getLinkTypeFromDataType< ACCEPT_TYPE >() ) {};
    virtual ~HasInlet(){

    };

    virtual bool acceptsOutletInstance( HasOutlet<ACCEPT_TYPE>& _outletInstance ) const = 0;


//    virtual const std::string& getPinLabel() const override {

//    };
};

template<typename T> class ParamModifier;
template<typename T> class ParamInletModifier;

class AbstractHasOutlet : public HasPin {
public:
    AbstractHasOutlet( const LinkType& _linkType ) : HasPin(_linkType) {
        //std::cout << "AbstractHasOutlet() " << (AbstractHasOutlet*)this << " type = " << (this->linkType) << "/" << getLinkName(this->linkType) << " | " <<  (&this->linkType) << "/" << &_linkType << std::endl;
    };

    template<typename MODIFIER_TYPE>
    MODIFIER_TYPE& getTypedOutlet() { // Todo : add try in method name, as it can throw
        // Ensure correct usage by allowing only deriveds of AbstractHasOutlet
        static_assert(std::is_base_of<AbstractHasOutlet, MODIFIER_TYPE>::value, "MODIFIER_TYPE should inherit from AbstractHasOutlet* !!!");

        try {
            // Try get native type
            MODIFIER_TYPE* typedOutlet = dynamic_cast<MODIFIER_TYPE*>(this);
            if( !typedOutlet || typedOutlet==nullptr ){
                throw 888; // todo: throw VPError
            };
            return *typedOutlet;
        } catch (...) {
            std::cout << "Catched WRONG TYPE CONVERSION! (normal behaviour)" << std::endl;
            throw 777; // todo: re-throw VPError
        }
    };

    virtual const AbstractPinLink& tryGetPinLink(const int& _index) = 0;
    virtual int getNumConnections() const = 0;

    // todo
    //std::vector<AbstractPinLink*> pinLinks;

    //const std::string dataLabel;
    //const LinkType linkType;
    virtual void visualiseData() = 0; // todo : implement this
    const bool& dataHasChanged() const {
        return bFlagDataChanged;
    }
    ImVec2 outletPosition = ImVec2(0,0); // Public so ImGui can change it
protected:
    bool bFlagDataChanged = false;
};

template<typename OUTPUT_TYPE>
class HasOutlet : public AbstractHasOutlet {
public:
    HasOutlet() : AbstractHasOutlet( getLinkTypeFromDataType< OUTPUT_TYPE >() ) {
        //std::cout << "HasOutlet = " << getLinkType< OUTPUT_TYPE >() << " / "  << getLinkName(this->linkType) << std::endl;
    };
    virtual ~HasOutlet() {
        // todo: notify others
    };
    // todo
    // store dataref ?
//    HasOutlet<ACCEPT_TYPE>& getAsOutlet(){
//        return *this;
//    };

    // todo: un-virtual this by assigning a constant reference to HasOutlet's data value (?)
    virtual const OUTPUT_TYPE& getOutputValue() = 0;

    virtual int getNumConnections() const override {
        return connectedPinLinks.size();
    };

    bool registerPinLink(PinLink<OUTPUT_TYPE>& _link){
        // check
        if( (AbstractHasOutlet*) _link.fromPin == (AbstractHasOutlet*) this ){
            // todo: verify correct link type ?

            // register
            connectedPinLinks.push_back( &_link );

            return true;
        }

        return false;
    };

    // Note: called after onPinConnected() (is this the wished behaviour?)
    bool unRegisterPinLink(PinLink<OUTPUT_TYPE>& _link){
        // check
        if( (AbstractHasOutlet*) _link.fromPin == (AbstractHasOutlet*) this ){
            // todo: verify correct link type ?

            // unregister
            connectedPinLinks.remove( &_link );

            return true;
        }

        return false;
    };

    virtual AbstractPinLink& tryGetPinLink(const int& _index) override {
        if( connectedPinLinks.size() > _index ){
            int i = 0;
            for(auto it=connectedPinLinks.cbegin(); it!=connectedPinLinks.cend(); it++){
                if(i==_index){
                    //PinLink<OUTPUT_TYPE>*const ret = *it;
                    return **it;// static_cast<const AbstractPinLink&>(**it);
                }
                i++;
            }
        }

        throw VPError(VPErrorCode_LINK, VPErrorStatus_NOTICE, "This index doesn't exist in the connected links list.");
    };

    virtual void onPinConnected() override {
        //std::cout << "HasOutlet::onPinConnected();"<< std::endl;
    };
    virtual void onPinDisconnected() override {
        //std::cout << "HasOutlet::onPinDisconnected();"<< std::endl;
    };

    // Don't rename the functions as this allows usage with range-based iterators.
    typename std::list< PinLink<OUTPUT_TYPE>* >::const_iterator begin() const noexcept {
        return connectedPinLinks.cbegin();
    };
    typename std::list< PinLink<OUTPUT_TYPE>* >::const_iterator end() const noexcept {
        return connectedPinLinks.cend();
    };

private:
    // todo: this should probably be AbstractPinlink to allow easier type-compatibility
    std::list< PinLink<OUTPUT_TYPE>* > connectedPinLinks; // only references, not owned
};

class abstractParamModifier {
protected:
    abstractParamModifier( const AbstractHasModifier& _parent, const enum OFXVP_MODIFIER_& _modifierType ) : parent(_parent), modifierType(_modifierType) {

    }
public:
    virtual bool isEditable() const = 0;
    const AbstractHasModifier& parent;
    const enum OFXVP_MODIFIER_ modifierType;// = OFXVP_MODIFIER_UNKNOWN;
};

// The address-of operator (&) can only be used with an lvalue.
//#define IS_LVALUE(x) ( (sizeof &(x)), (x) )

class AbstractHasModifier { // todo: rename to AbstractHasModifiers
public:
    AbstractHasModifier(const LinkType& _linkType, const void* _underlyingValue) : underlyingValueAddr(_underlyingValue), modifierLinkType(_linkType){
        //assert( std::is_rvalue_reference<const LinkType&>::value ); // _linkType must be a variable reference ! Dummy-protect against volatile memory
        //std::cout << "AbstractHasModifier() " << (AbstractHasModifier*)this << " type = " << (this->modifierLinkType) << " / " << getLinkName(this->modifierLinkType) << " | " <<  (&this->modifierLinkType) << "/" << &_linkType << " - " << IS_LVALUE(_linkType) << std::endl;
    };
    virtual ~AbstractHasModifier(){};
    //virtual bool addModifier() = 0;
    const AbstractHasModifier& getAbstractHasModifier() {
        return static_cast<const AbstractHasModifier&>(*this);
    };

    // ABSTRACT API METHODS
    template<typename MODIFIER_TYPE>
    MODIFIER_TYPE& getOrCreateModifier_deletethisfunc() { // todo: Whole function to be removed ?
        // Ensure correct usage by allowing only deriveds of abstractParamModifier
        static_assert(std::is_base_of<abstractParamModifier, MODIFIER_TYPE>::value, "MODIFIER_TYPE should inherit from abstractParamModifier* !!!");

        // search existing ones
        for(abstractParamModifier* apm : abstractParamModifiers){
            if( apm->modifierType == MODIFIER_TYPE::modifierType ){// OFXVP_MODIFIER_INLET ){
                try {
                    return static_cast<MODIFIER_TYPE>(*apm);
                } catch (...) {
                    throw VPError(VPErrorCode_MODIFIER, VPErrorStatus_WARNING, "Could not cast from abstractModifier to the desired typed modifier.");
                    break;
                }
            }
        }

        // nothing found ? Create new modifier
//        auto* newModifierInstance = new MODIFIER_TYPE( *this );
//        abstractParamModifiers.push_back( newModifierInstance );
//        return *newModifierInstance;
        // From here, we cannot push to paramModifiers, only to abstractParamModifiers, which will lose information.
        throw VPError( VPErrorCode_MODIFIER, VPErrorStatus_NOTICE, "The modifier was not found and can not yet be added." );
    };
    template<typename MODIFIER_TYPE>
    bool hasModifier() const {
        // Ensure correct usage by allowing only deriveds of abstractParamModifier
        static_assert(std::is_base_of<abstractParamModifier, MODIFIER_TYPE>::value, "MODIFIER_TYPE should inherit from abstractParamModifier* !!!");
        //static_assert( std::is_same< decltype(MODIFIER_TYPE::modifierType), decltype(abstractParamModifier::modifierType) >::value , " This modifier has no modifierType value. Please define one in your class. ");
        static_assert( MODIFIER_TYPE::modifierType, " This modifier has no modifierType value. Please define one in your class. ");

        // Sadly, doesn't work as this templated function is implicitly instanciated before MODIFIER_TYPE::modifierType
        //return this->hasModifier( MODIFIER_TYPE::modifierType );

        // Fallback
        for(abstractParamModifier* apm : abstractParamModifiers){
            if( apm->modifierType == MODIFIER_TYPE::modifierType ){
                return true;
                break;
            }
        }
        return false;
    };

    bool hasModifier( const OFXVP_MODIFIER_& _type ) const {
        for(abstractParamModifier* apm : abstractParamModifiers){
            if( apm->modifierType == _type ){
                return true;
                break;
            }
        }
        return false;
    };
    abstractParamModifier* tryGetAbstractModfier( const OFXVP_MODIFIER_& _type ) const {
        for(abstractParamModifier* apm : abstractParamModifiers){
            if( apm->modifierType == _type ){
                return apm;
                break;
            }
        }
        return nullptr;
    };

    int getNumModifiers() const {
        return abstractParamModifiers.size();
    };

    virtual const std::string& getHasModifierName() const = 0;
    virtual ImVec2& getInletPosition() = 0;

    // TYPED API METHODS
    virtual bool connectWithOutlet( AbstractHasOutlet& _outlet ) = 0; // to return bool or PinLink&  ?

    std::list<abstractParamModifier*> abstractParamModifiers;
    const void* underlyingValueAddr;

    const LinkType& modifierLinkType; // wrong ? should be in hasOutlet ?
};

template<typename ACCEPT_TYPE>
class HasModifier : public AbstractHasModifier {
public:
    HasModifier( const ACCEPT_TYPE& _underlyingValue  ) : AbstractHasModifier( getLinkTypeFromDataType<ACCEPT_TYPE>() , &_underlyingValue ) {
        //std::cout << "HasModifier() type = " << getLinkTypeFromDataType<ACCEPT_TYPE>() << " - " << (this->AbstractHasModifier::linkType) << std::endl;
    };
    virtual ~HasModifier(){
        for(ParamModifier<ACCEPT_TYPE>* modifier : paramModifiers){
            delete modifier;
        }
        paramModifiers.clear();
        abstractParamModifiers.clear();
    };
    virtual bool addModifier() /*override*/ { // todo : Remove this func ? (replaced by getOrCreateModifier....)
        // tmp, only inletmodifiers
        const AbstractHasModifier& tmp = this->getAbstractHasModifier();
        paramModifiers.push_back( new ParamInletModifier<ACCEPT_TYPE>( tmp ) );
        abstractParamModifiers.push_back( paramModifiers.back() ); // always keep abstracts synced
        return true;
    };
    bool connectWithOutlet(std::string _paramUID){
        // Try to get the instance
        if( AbstractParameter* abstractParam = ofxVPHasUID::getTypedInstanceByUID<AbstractParameter>(_paramUID) ){
            if(abstractParam->hasOutlet()){
                try {
                    if( this->connectWithOutlet( abstractParam->getAsOutlet() ) ){
                        // Connection done ! :)
                        return true;
                    }
                    else {
                        ofLogNotice("Parameter") << "The inlet param (me) did not accept a connection with "<< _paramUID << ". Maybe it doesn't accept my data type ?";
                    }
                } catch (...) {
                    ofLogNotice("Parameter") << "Could not parse outlet " << _paramUID << " as an outlet !" << std::endl;
                }
            }
        }
        else {
            ofLogNotice("Parameter") << "Could not parse " << _paramUID << " as a parameter ! Not connecting." << std::endl;
        }

        return false;
    };
    virtual bool connectWithOutlet( AbstractHasOutlet& _outlet ) override {
        //std::cout << "HasModifier<T=" << getLinkName<ACCEPT_TYPE>() << ">::connectWithOutlet() --> connecting parameter" << std::endl;

        // pre-check if potentialy compatible. todo
        // Don't connect with self !
//        if( !acceptsLinkType( _outlet.linkType ) ){
//        if( ACCEPT_TYPE != _outlet.linkType ){
//            std::cout << "Parameter<T>::connectWithOutlet() --> incompatible link type !" << std::endl;
//            return false;
//        }

        // get inlet modifier
        ParamInletModifier<ACCEPT_TYPE>& inletModifier = this->getOrCreateModifier< ParamInletModifier<ACCEPT_TYPE> >();
        bool ret = inletModifier.connectWithOutlet(_outlet);

        //std::cout << "Parameter<T>::HasModifier::connectWithOutlet() --> succeeded = " << ret << std::endl;
        return ret;
    };

    virtual ImVec2& getInletPosition() override final {
        ParamInletModifier<ACCEPT_TYPE>& inletModifier = this->getOrCreateModifier< ParamInletModifier<ACCEPT_TYPE> >();

        return inletModifier.inletPosition;
    };

    template<typename MODIFIER_TYPE>
    MODIFIER_TYPE& getOrCreateModifier() {
        // Ensure correct usage by allowing only deriveds of abstractParamModifier
        static_assert(std::is_base_of<abstractParamModifier, MODIFIER_TYPE>::value, "MODIFIER_TYPE should inherit from abstractParamModifier* !!!");
        // Warning for uncompletely-implemented modifiers
        static_assert( ( MODIFIER_TYPE::modifierType ), "This modifier has no modifierType implemented. Please add one to yours.");

        // Search for any existing one
        for(ParamModifier<ACCEPT_TYPE>* pm : paramModifiers){
            if( pm->modifierType == MODIFIER_TYPE::modifierType ){
                try {
                    return static_cast< MODIFIER_TYPE& >(*pm);
                } catch(...){
                    ofLogWarning("Parameter<T>::getOrCreateModifier()") << "Misbehaviour ! The inletmodifier type exists but is not parseable as the requested sub-type. (this should never happen)";
                    break; // return new instance
                }
            }
        }

        // nothing found ? Create new modifier
        MODIFIER_TYPE* newModifierInstance = new MODIFIER_TYPE( *this );
        paramModifiers.push_back( newModifierInstance );
        abstractParamModifiers.push_back( newModifierInstance );
        //std::cout << "Created a brand new modifier !" << std::endl;
        return *newModifierInstance;
    };

protected:
    std::list<ParamModifier<ACCEPT_TYPE>*> paramModifiers; // stores ptr but owns them. Be sure to clean memory! Mirrored in AbstractHasModifiers::abstractParamModifiers
};

// Todo : rename this to ofxVPParameter
template<typename DATA_TYPE, bool ENABLE_OUTLET=true>
//class Parameter : public HasInlet<DATA_TYPE>, public AbstractParameter {
class Parameter : public HasModifier<DATA_TYPE>, public std::conditional<ENABLE_OUTLET, HasOutlet<DATA_TYPE>, void>::type, public AbstractParameter {
public:
    using HasModifier<DATA_TYPE>::paramModifiers;

    Parameter( std::string _paramName = "Parameter", DATA_TYPE _value = DATA_TYPE() ) : HasModifier<DATA_TYPE>(dataValue), std::conditional<ENABLE_OUTLET, HasOutlet<DATA_TYPE>, void>::type(), AbstractParameter(_paramName), dataValue(_value) {
//# ifdef OFXVP_DEBUG_PARAMS
//        ofLogNotice(std::string(OFXVP_DEBUG_PARAMS_PREPEND)+"_primary") <<  __PRETTY_FUNCTION__;
//# endif
        //std::cout << "After " << this->getUID() << " (done)" << std::endl;
        //std::cout <<  __PRETTY_FUNCTION__ << std::endl;
        //if( ENABLE_OUTLET && this->linkType != this->modifierLinkType){
            //std::cout << this->getUID() << " " << (AbstractHasModifier*)this << ". Linktypes ( "<< this->AbstractHasModifier::linkType <<"["<< getLinkTypeFromDataType< DATA_TYPE >() << "|" << getLinkNameFromDataType<DATA_TYPE>() << "|" << getLinkName(this->AbstractHasModifier::linkType) << "]" <<" / "<< this->AbstractHasOutlet::linkType << "["<< getLinkTypeFromDataType< DATA_TYPE >() << "]" <<" ) = " << getLinkName(this->AbstractHasModifier::linkType) << " - " << getLinkName(this->AbstractHasOutlet::linkType) << std::endl;
            //std::cout << this->getUID() << " "<< (AbstractHasModifier*)this << ".-----"
                      //<< "Linktypes ( HasModifier:"<< this->modifierLinkType << " @ "<< &this->modifierLinkType << " - HasOutlet:" << this->linkType << " @ "<< &this->linkType  << ")" // - HasInlet:" << this->AbstractHasInlet::linkType
                      //<<"["<< getLinkTypeFromDataType< DATA_TYPE >() << "|" << getLinkNameFromDataType<DATA_TYPE>() << "|" << getLinkName(this->AbstractHasModifier::linkType) << "]" <<" / "<< this->AbstractHasOutlet::linkType << "["<< getLinkTypeFromDataType< DATA_TYPE >() << "]" <<" ) = " << getLinkName(this->AbstractHasModifier::linkType) << " - " << getLinkName(this->AbstractHasOutlet::linkType)
                      //<< reinterpret_cast<AbstractHasInlet*>(this) // Wtf ?!
                      //<< (AbstractHasInlet*)this
                      //<< "&VP_LINKTYPE_STRING=" << getLinkTypeFromDataType<std::string>()
                      //<< std::endl;
        //}

        // Check correct behaviour if this assert is triggered. (undefined behavior for now)
        assert( !ENABLE_OUTLET || this->modifierLinkType == this->linkType );// "Inlet and Outlet have different linktypes. This is not yet supported. Please use 2 distinct parameters instead." );
        assert( this->modifierLinkType != VP_LINK_UNDEFINED ); // Undefined link type. You have to give one !
    };

    // - - - - - - - - - -
    // Abstract functions
    // From HasModifier<DATA_TYPE>
    // virtual void addModifier() override {};

    // - - - - - - - - - -
    // From HasOutlet
    virtual typename std::enable_if<ENABLE_OUTLET>::type
    visualiseData() override {};
    //virtual void onPinConnected() override {};
    //virtual void onPinDisconnected() override {};
    //virtual void triggerValueChanged() override {};
//    if ( ENABLE_OUTLET ) {
//        return true;
//    }
//    else {
//        return false;
//    }
    virtual const DATA_TYPE& getOutputValue() override final {
        //std::cout << "getOutputValue() [from]=" << &this->getBaseValue() << " [to]=" << &this->getValue() << std::endl;
        return this->getValue();
    };

    // From AbstractParameter
    virtual bool saveToXML(ofxXmlSettings& _xml) const override {
        if(_xml.pushTag("mosaicParam", _xml.addTag("mosaicParam") )){
            //_xml.addValue("nodeType", nodeType );
            _xml.addValue("UID", getUID() );
            _xml.addValue("DisplayName", getDisplayName() );
            _xml.addValue("StoredValue", storedValue );

            _xml.popTag();
        }

        return true; // todo
    };
    // _xml.PushTag() must be inside the mosaicParam prior to calling this method
    virtual bool loadFromXML(ofxXmlSettings& _xml) override {

        // Set name
        if(!this->changeName( _xml.getValue("DisplayName", getDisplayName()), _xml.getValue("UID", getUID()) )){
            // todo: how to handle errored name changes ?
            return false;
        }
        //displayName = _xml.getValue("DisplayName", getDisplayName() );
        //myUID = _xml.getValue("UID", getUID() );

        // load data
        this->storedValue = _xml.getValue("StoredValue", storedValue );
        this->dataValue = this->storedValue;
        this->bFlagDataChanged = true;

        return true;
    };
    virtual std::string serialize(const bool& _serializeStoredValue=false) const override {
        std::ostringstream serialized;
        if(_serializeStoredValue) serialized << this->storedValue;
        else serialized << this->dataValue;

        if(serialized.tellp()>0){ // tellp = size()
            return serialized.str();
        }
        // error ?
        return "[unable-to-serialize]";
    };
    virtual bool unserialize( const std::string& _value, const bool& _unserializeToStoredValue=false ) override {
        ofLogNotice("Parameter::unserialize()") << "Please implement this method in your parameter.";

        return false; // todo
    };
    //void update() = 0; // needed ?
    void drawImGuiEditable() override {
        // Default falls back to uneditable method
        this->drawImGui();
    };
    void drawImGui() override {
        // Fallback behaviour for any type : Try to display without editing capabilities.
        // Echo serialized value
        ImGui::LabelText( this->getDisplayName().c_str(), "%s", this->serialize().c_str() );
        //ImGui::LabelText( this->getDisplayName().c_str(), "%s (unable to display)", typeid(*this).name() );
    };
    virtual bool getIsEditable() const override {
        if(  AbstractParameter::getIsEditable() && paramModifiers.size() > 0 ){
            return this->paramModifiers.back()->isEditable();
        }
        return AbstractParameter::getIsEditable();
    };
    virtual AbstractHasModifier& getAsHasModifier() override {
        return *this;
    };
    virtual const std::string& getHasModifierName() const override {
        return getDisplayName();
    };
    virtual const std::string& getPinLabel() const override {
        return getDisplayName(); // or return UID ?
    };
    virtual bool hasOutlet() const override final {
        return ENABLE_OUTLET;
    };
    // todo: enable only if : virtual typename std::enable_if<ENABLE_OUTLET>::type
    virtual AbstractHasOutlet& getAsOutlet() override final {
        if( this->hasOutlet() ){
            try {
                return static_cast<AbstractHasOutlet&>(*this);
            }
            catch(...){
                // Throw error below
            }
        }

        // impossible to parse non-outlet param to outlet param.
        throw VPError(VPErrorCode_LINK, VPErrorStatus_NOTICE, std::string("Cannot get outlet of parameter «") + this->getUID() + "» : it hasn't got an outlet !");

    };

    // Non abstract API functions (typed)

    // Returns baseValue() which gets the constant parameter value from derived classes.
    // Eventually replace that reference with a modified one, if modifiers exist. (variable routing function)
    const DATA_TYPE& getValue() const {
        // todo: Check/Fix references, allow to re-assign references ? References should be re-assignable, but point to const values so they cannot be messed with.
        // Ressource: https://isocpp.org/wiki/faq/references#reseating-refs
        switch(this->paramModifiers.size()) {
            case 0: {
                // return base
                return this->getBaseValue();
                break;
            }
            case 1: {
                return this->paramModifiers.back()->transformValue( this->getBaseValue() );
                break;
            }
            default: {
                // chain modifiers
                const DATA_TYPE* retValue = &this->getBaseValue();// const_cast<const DATA_TYPE*>(&this->getBaseValue());
                for(ParamModifier<DATA_TYPE>* modifier : this->paramModifiers){
                    retValue = &modifier->transformValue(*retValue);
                }
                return *retValue;
                break;
            }
        }
        return dataValue;
    };
    DATA_TYPE getValueCopy() const {
        return dataValue;
    };
    virtual const DATA_TYPE& getBaseValue() const { // base value
        return dataValue;
    }
    bool setBaseValue( const DATA_TYPE& _newValue){
        dataValue = _newValue;
        return true;
    };
    // Experimental: alternative method to getValue() the value dereferencing the pointer
    const DATA_TYPE& operator->(){
        return getValue();
    }

    // Utilities
    // Cast Parameter<type> to type (assignment operator)
    const DATA_TYPE& operator=(const Parameter<DATA_TYPE, ENABLE_OUTLET>& _param) const{
        return getValue();
    }
    // Move assignment operator
//    DATA_TYPE& operator=(const Parameter<DATA_TYPE,ENABLE_OUTLET>&& _param){
//        return getValue();
//    }
    // implicit conversion operator
    operator const DATA_TYPE&() { return getValue(); }

    // todo: forbid copy constructor to prevent creating accidental copies and only allow refs ?

    // ImGui Helpers
protected:
    void ImGuiListenForParamDrop(){ // todo: remove this method
        if ( ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("VPPARAM_OUTLET_TO_INLET")){
                //IM_ASSERT(payload->DataSize == sizeof(ofxVPHasUID::stringKeyType::value_type*));
                ofxVPHasUID::stringKeyType outletParmName = static_cast<ofxVPHasUID::stringKeyType::value_type*>(payload->Data);//static_cast<std::string*>((*data));
                std::cout << "Dropped target on source(outlet)=" << outletParmName << " --> target(inlet)=" << this->getUID() << std::endl;

                // try to connect
                if( ofxVPHasUID* outletHasUID = ofxVPHasUID::getInstanceByUID(outletParmName) ){
                    // Don't connect with self !
                    if( static_cast<ofxVPHasUID*>(this) == outletHasUID ){
                        ofLogVerbose("Parameter") << "Notice: Not connecting the parameter with itself !" << std::endl;
                    }
                    else {
                        // try to parse it as a parameter
                        if( AbstractParameter* outletAbstract = dynamic_cast<AbstractParameter*>(outletHasUID)){
                            if(outletAbstract->hasOutlet()){
                                try {
                                    if( this->getAsHasModifier().connectWithOutlet( outletAbstract->getAsOutlet() ) ){
                                        // Connection done ! :)
                                    }
                                    else {
                                        ofLogNotice("Parameter") << "The inlet param " << this->getUID() << " (me) did not accept a connection with "<< outletParmName << ". Maybe it doesn't accept my data type ?";
                                    }
                                } catch (...) {
                                    ofLogNotice("Parameter") << "Could not parse outlet " << outletParmName << " as an outlet !" << std::endl;
                                }
                            }
                        }
                        else {
                            ofLogNotice("Parameter") << "Could not parse " << outletParmName << " to a parameter !" << std::endl;
                        }
                    }
                }
                else {
                    std::cout << "Cannot find an instance named: " << outletParmName << "." << std::endl;
                }
            } // end VPPARAM_OUTLET_TO_INLET

            // Handle dropping a parameter connection request
            else if ( ENABLE_OUTLET ){
                if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("VPPARAM_INLET_TO_OUTLET")){
                    //IM_ASSERT(payload->DataSize == sizeof(ofxVPHasUID::stringKeyType::value_type*));
                    ofxVPHasUID::stringKeyType inletParmName = static_cast<ofxVPHasUID::stringKeyType::value_type*>(payload->Data);//static_cast<std::string*>((*data));

                    // try to connect
                    if( ofxVPHasUID* inletHasUID = ofxVPHasUID::getInstanceByUID(inletParmName) ){
                        // Don't connect with self !
                        if( static_cast<ofxVPHasUID*>(this) == inletHasUID ){
                            ofLogNotice("Parameter") << "Notice: Not connecting the parameter with itself !" << std::endl;
                        }
                        else {
                            // try to parse it as a parameter
                            if( AbstractParameter* inletAbstract = dynamic_cast<AbstractParameter*>(inletHasUID)){
                                try {
                                    if( inletAbstract->getAsHasModifier().connectWithOutlet( this->getAsOutlet() ) ){
                                        // Connection done ! :)
                                    }
                                    else {
                                        ofLogNotice("Parameter") << "The param inlet " << inletParmName << " did not accept a connection with me. Matbye it doesn't accept my data type ?" << std::endl;
                                    }
                                } catch (...) {
                                    ofLogNotice("Parameter") << "The param outlet " << this->getUID() << "(me) is not parsable as an outlet !" << std::endl;
                                }
                            }
                            else {
                                ofLogNotice("Parameter") << "Could not parse " << inletParmName << " to a parameter !" << std::endl;
                            }
                        }
                    }
                    else {
                        std::cout << "Cannot find an instance named :" << inletParmName << "." << std::endl;
                    }
                    std::cout << "Dropped target on source(outlet)=" << this->getUID() << " --> target(inlet)=" << inletParmName << std::endl;
                }
            } // end VPPARAM_INLET_TO_OUTLET

            ImGui::EndDragDropTarget();
        }
    };
    // Use _drawInlet to choose between inlet/outlet - left/right
    virtual void drawImGuiParamPin(ImGuiEx::NodeCanvas& _nodeCanvas, const bool& _drawInlet=false) override final {
        // Show source connect handle
        if( _drawInlet || (ENABLE_OUTLET) ){
            //if(!_drawInlet) ImGui::SameLine();
//            ImGui::Button(_drawInlet?"<--":"-->");
//            if( ImGui::BeginDragDropSource(ImGuiDragDropFlags_None) ){
//                //ImGui::SetDragDropPayload("TEST", ((std::string::value_type**) this->getUID().c_str() ), sizeof(std::string::value_type*), ImGuiCond_Once);    // Set payload to carry the index of our item (could be anything)
//                const ofxVPHasUID::stringKeyType& UID = this->getUID();
//                ImGui::SetDragDropPayload(_drawInlet?"VPPARAM_INLET_TO_OUTLET":"VPPARAM_OUTLET_TO_INLET", UID.data(), UID.size()+1, ImGuiCond_Once);    // Set payload to carry the index of our item (could be anything)
//                ImGui::Text(_drawInlet?"Connect %s (inlet) with an outlet...":"Connect %s (outlet) with an inlet...", UID.c_str());
//                ImGui::EndDragDropSource();
//            }
            //if(_drawInlet) ImGui::SameLine();
            //_nodeCanvas.AddNodePin( this->getUID().c_str(), this->getHasModifierName().c_str(), this->inletPosition, getLinkName(this->AbstractHasModifier::linkType), IM_COL32(255,255,255,255), this->getNumModifiers()>0, _drawInlet?ImGuiExNodePinsFlags_Left:ImGuiExNodePinsFlags_Right );
        }

        // Draw inlet Pin
        if(_drawInlet /*&& this->getIsEditable()*/){
            // Parse connection status
            AbstractHasModifier& paramHasModifier = this->getAsHasModifier();
            bool isConnected = false;
            if( paramHasModifier.getNumModifiers()>0 && this->hasModifier( OFXVP_MODIFIER_INLET ) ){
                //this->template hasModifier<ParamInletModifier<DATA_TYPE> >()
                ParamInletModifier<DATA_TYPE>& inlet = this->template getOrCreateModifier< ParamInletModifier<DATA_TYPE> >();
                isConnected = inlet.isConnected();
            }
            // Draw pin
            //std::cout << this->AbstractHasModifier::linkType << " / " << paramHasModifier.linkType ;//<< std::endl;
            ImGuiExNodePinResponse pinData = _nodeCanvas.AddNodePin( this->getUID().c_str(), this->getHasModifierName().c_str(), this->getInletPosition(), getLinkName(this->modifierLinkType), paramHasModifier.modifierLinkType, getLinkImguiColor(paramHasModifier.modifierLinkType), isConnected, ImGuiExNodePinsFlags_Left );
            if(pinData){
                if( pinData.flag == ImGuiExNodePinActionFlags_ConnectPin ){
                    if( this->connectWithOutlet( std::string( pinData.otherUid ) ) ){
                        // do nothing, continue as normal
                    }
                    else {
                        ofLogNotice("Parameter::drawImGuiParamPin()") << "Me, the inlet " << this->getUID() << " refused to connect with outlet =" << pinData.otherUid;
                    }
                }
                else if( pinData.flag == ImGuiExNodePinActionFlags_DisconnectPin ){
                    // ...
                }
                else {
                    ofLogNotice("Parameter::drawImGuiParamPin()") << "Unimplemented menu action. This might need your attention !";
                }
            }

        }
        // Draw outlet pin
        else if( /*!_drawInlet &&*/ ENABLE_OUTLET){
            try {
                // Todo: paramOutlet could also be typed...
                AbstractHasOutlet& paramOutlet = this->getAsOutlet();

                bool hasConnections = paramOutlet.getNumConnections() > 0;
                ImGuiExNodePinResponse pinData = _nodeCanvas.AddNodePin( this->getUID().c_str(), paramOutlet.getPinLabel().c_str(), paramOutlet.outletPosition, getLinkName(paramOutlet.linkType), paramOutlet.linkType, getLinkImguiColor(paramOutlet.linkType), hasConnections, ImGuiExNodePinsFlags_Right );
                if( pinData ){
                    if( pinData.flag == ImGuiExNodePinActionFlags_ConnectPin ){
                        // get other as inlet
                        if( AbstractHasModifier* inlet = ofxVPHasUID::getTypedInstanceByUID<AbstractHasModifier>( pinData.otherUid )){
                            //AbstractHasInlet inlet = absInlet->getAsHasModifier();
                            if( inlet->connectWithOutlet( paramOutlet ) ){
                                // do nothing, continue as normal
                            }
                            else {
                                ofLogNotice("Parameter::drawImGuiParamPin()") << "The inlet " << pinData.otherUid << " refused to connect with me=" << paramOutlet.getPinLabel();
                            }
                        }
                        else {
                            ofLogWarning("Parameter::drawImGuiParamPin()") << "Could not parse the UID " << pinData.otherUid << " as an inlet !";
                        };
                    }
                    else if( pinData.flag == ImGuiExNodePinActionFlags_DisconnectPin ){
                        // ...
                    }
                    else {
                        ofLogNotice("Parameter::drawImGuiParamPin()") << "Unimplemented PinAction. This might need your attention !";
                    }
                }

                // Draw Links
                if(hasConnections){
                    HasOutlet<DATA_TYPE>& typedOutlet = paramOutlet.getTypedOutlet< HasOutlet<DATA_TYPE> >();

                    //for( const PinLink<DATA_TYPE>* link : typedOutlet ){ // not for erasing
                    for( auto it = typedOutlet.begin(); it != typedOutlet.end(); ){
                        const PinLink<DATA_TYPE>* link = *it;
                        ++it; // advance iterator now so we can erase the link without crashing the loop
                        if(!link || link->fromPinTyped == nullptr || !link->fromPinTyped ){
                            continue;
                        }

                        if( ImGuiExNodeLinkActionFlags_ linkResult = _nodeCanvas.AddLink( link->fromPinTyped->outletPosition, link->toPinTyped.inletPosition, ofxVPLinkTypeInfo< getLinkTypeFromDataType< DATA_TYPE >() >::imguiColor, "LABEL" ) ){
                            // Disconnect ?
                            if( linkResult == ImGuiExNodeLinkActionFlags_Disconnect ){
                                //++it;
                                link->toPin.disconnectPin();
                            }
                            else {
                                if( linkResult != ImGuiExNodeLinkActionFlags_None){
                                    ofLogNotice("Parameter::drawImGuiParamPin()") << "Unimplemented LinkAction. This might need your attention !";
                                }
                            }
                        }
                    }
                }
            } catch (...) {
                // Ignore errors (normal behaviour)
            }
        }
    }

    // tmp method ?
    void ImGuiShowInfoMenu(){
        if( ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered() ) {
            isMenuOpen = !isMenuOpen;
        }
        if( isMenuOpen ){
            this->ImGuiPrintParameterInfo();
        }
    }

    void ImGuiPrintParameterInfo(){
        // Name
        ImGui::Text( "UID: %s", this->getUID().c_str() );
        ImGui::Text( "LinkType: %s", getLinkNameFromDataType<DATA_TYPE>() );
        ImGui::Separator();

        // Outlet info
        if( this->hasOutlet() ){
            try {
                HasOutlet<DATA_TYPE>& outlet = *this;//->getAsOutlet();
                ImGui::Text("Outlet information" );
                ImGui::Text("Connected outlets : %i", outlet.getNumConnections() );
                for(int i=0; i < outlet.getNumConnections(); i++){
                    try {
                        AbstractPinLink& pl = outlet.tryGetPinLink(i);
                        ImGui::PushID(i);
                        ImGui::Text("Outlet %i = %s (%s)", i, pl.toPin.getPinLabel().c_str(), getLinkName(pl.toPin.linkType) );
                        ImGui::SameLine();
                        if( ImGui::SmallButton("Disconnect") ){
                            pl.toPin.disconnectPin();
                        }
                        ImGui::PopID();
                    }
                    catch(...){
                        ImGui::Text("Inlet %i", i);
                    }
                }
            } catch(...) {
                ImGui::LabelText( "InletModifier", "%s", "Error/Unavailable" );
            }
        }
        else {
            ImGui::Text("No Outlet on this param..." );
        }
        ImGui::Separator();

        // Modifiers info
        ImGui::Text("Modifiers information" );
        ImGui::LabelText("Num Modifiers", "%i", this->getNumModifiers() );
        for(ParamModifier<DATA_TYPE>* modifier : paramModifiers){
            ImGui::Text("ModifierType: %s", getModifierName( modifier->modifierType ).c_str() );
        }
        ImGui::Separator();
        // InletModifier info
        try {
            if( this->template hasModifier< ParamInletModifier< DATA_TYPE > >() ){
                ParamInletModifier< DATA_TYPE >& paramInlet = const_cast< Parameter<DATA_TYPE,ENABLE_OUTLET>& >( *this ).template getOrCreateModifier< ParamInletModifier<DATA_TYPE> >();
                ImGui::LabelText( "InletModifier", "Connected: %s", paramInlet.myLink.isConnected?"yes":"no" );

                if(paramInlet.myLink.isConnected ){
                    ImGui::SameLine();
                    if( ImGui::SmallButton("Disconnect") ){
                        paramInlet.disconnectPin();
                    }
                }
            }
            else {
                 ImGui::LabelText( "InletModifier", "%s", "None" );
            }
        } catch(...) {
            ImGui::LabelText( "InletModifier", "%s", "Error/Unavailable" );
        }

        // Value information
        ImGui::Separator();
        std::ostringstream storedValue;     std::ostringstream outputValue;     std::ostringstream baseValue;
        storedValue << this->dataValue;     outputValue << this->getValue();    baseValue << this->getBaseValue();
        ImGui::LabelText("storedValue", "%s",   storedValue.str().c_str() );
        ImGui::LabelText("baseValue", "%s",     baseValue.str().c_str());
        ImGui::LabelText("outputValue", "%s",   outputValue.str().c_str() );
    }

public:// private:
    DATA_TYPE dataValue; // base value
    DATA_TYPE storedValue; // for save/load
private:
     bool isMenuOpen = false;
};


// - - - - - - - - - -

template<typename T>
class ParamModifier : public abstractParamModifier {
public:
    ParamModifier(  const AbstractHasModifier& _parent, const enum OFXVP_MODIFIER_& _modifierType  ) : abstractParamModifier( _parent, _modifierType ){}
    virtual ~ParamModifier(){};
    virtual const inline T& transformValue(const T& _originalValue) const = 0;
};

template<typename MODIFIER_TYPE>
class ParamInletModifier : public ParamModifier<MODIFIER_TYPE>, public HasInlet<MODIFIER_TYPE> {
// todo : make constructor private to force deriving this class ?
public:
    ParamInletModifier( const AbstractHasModifier& _parent ) : ParamModifier<MODIFIER_TYPE>( _parent, OFXVP_MODIFIER_INLET /*getLinkName<MODIFIER_TYPE>() +" (Inlet)"*/), HasInlet<MODIFIER_TYPE>(), myLink(*this) {

    }
    virtual ~ParamInletModifier(){
        disconnectPin();
    };

    // Note: inline is needed so it can be defined once later in the code. Defining it here lead to duplicated symbols linker errors.
    // Todo : move it to .cpp file ?
    virtual const inline MODIFIER_TYPE& transformValue(const MODIFIER_TYPE& _originalValue) const override {
        //std::cout << "ParamModifier<T>::transformValue() UNTYPED !!!!" << std::endl;
        if( myLink.isConnected ){
            return myLink.fromPinTyped->getOutputValue();
        }

        // Or leave the value untouched
        return _originalValue;
    }

    virtual bool isEditable() const override {
        return !myLink.isConnected; // todo: is this right ?
    }

    bool isConnected() const {
        return myLink.isConnected;
    }

    // - - - - - - - - - -
    // Virtuals from HasInlet
    bool acceptsLinkType( const LinkType& _linktype ) override {
        return this->AbstractHasInlet::linkType == _linktype;
        // todo : make this work for similar link types ? ( ex: int/float/double = numeric)
    };
    // This function is for checking an instance on runtime, prevents connecting to self
    virtual bool acceptsOutletInstance( HasOutlet<MODIFIER_TYPE>& _outletInstance ) const override {
        // todo: also check if _outletInstance == [the HasOutlet eventually associated with the inlet via the parameter]
        return &_outletInstance.getOutputValue() != abstractParamModifier::parent.underlyingValueAddr;
    };
    virtual bool connectWithOutlet( AbstractHasOutlet& _outlet ) override {
        //std::cout << "Modifier<T>::connectWithOutlet() --> connecting parameter" << std::endl;
        if( !acceptsLinkType( _outlet.linkType ) ){
            ofLogNotice("ParamInletModifier::ConnectWithOutlet()") << "Incompatible link type ! (" << getLinkNameFromDataType<MODIFIER_TYPE>() << " <<  vs " << getLinkName(_outlet.linkType) << ")" << std::endl;
            return false;
        }

        // Disconnect (if connected)
        if(!disconnectPin()){
            ofLogVerbose("ParamInletModifier") << "Could not disconnect current connected pin. (probably weird behaviour)";
            return false;
        }

        // Connect
        try {
            myLink.fromPinTyped = &_outlet.getTypedOutlet< HasOutlet<MODIFIER_TYPE> >();
            myLink.fromPin = static_cast<AbstractHasOutlet*>(myLink.fromPinTyped);
            // throw if ptr didn't cast, should never happen.
            if(myLink.fromPin == nullptr) throw 999;
        } catch(...){
            myLink.isConnected = false;
            myLink.fromPinTyped = nullptr;
            myLink.fromPin = nullptr;
            std::cout << "Cannot get typed outlet, probably this is an uncompatible abstract, or it has no outlet." << std::endl;
            //disconnectPin();
            return false;
        }

        if( !acceptsOutletInstance( *myLink.fromPinTyped ) ){
            ofLogNotice("ParamInletModifier::ConnectWithOutlet()") << "Incompatible link instance ! (" << _outlet.getPinLabel() << " and " << this->getPinLabel() <<", most probably you tried to create a connection loop)" << std::endl;
            myLink.isConnected = false;
            myLink.fromPinTyped = nullptr;
            myLink.fromPin = nullptr;
            return false;
        }

        // Register @ fromPin
        if(!myLink.fromPinTyped->registerPinLink(myLink)){
            ofLogNotice("ParamInletModifier::ConnectWithOutlet()") << this->getPinLabel() << " could not register @ parameter outlet " << myLink.fromPin->getPinLabel();
            myLink.isConnected = false;
            myLink.fromPinTyped = nullptr;
            myLink.fromPin = nullptr;
            return false;
        }

        myLink.isConnected = true;

        // Trigger events
        myLink.fromPinTyped->onPinConnected();
        this->onPinConnected(); // myLink.toPin.onPinConnected();

        //std::cout << "Modifier<T>::connectWithOutlet() succeeded ! " << myLink.fromPin->linkType << " --> " << myLink.toPin.linkType << std::endl;
        return true;
    };
    virtual bool disconnectPin() override { // maybe : return void, always succeed to disconnect ?
        if(myLink.isConnected){
            // unregister
            if(myLink.fromPin!=nullptr && myLink.fromPinTyped!=nullptr){
                myLink.fromPinTyped->unRegisterPinLink(myLink);

                // notify outlet
                myLink.fromPin->onPinDisconnected();
                // notify self
                this->onPinDisconnected(); // myLink.toPin.onPinDisconnected();
            }
            // disconnect
            myLink.fromPin = nullptr;
            myLink.fromPinTyped = nullptr;
            myLink.isConnected = false;

            return true;
        }
        // already disconnected
        return true;
    }
    virtual void onPinConnected() override {
        // todo
        //std::cout << "ParamInletModifier::onPinConnected();"<< std::endl;
    };
    virtual void onPinDisconnected() override {
        //std::cout << "ParamInletModifier::onPinDisconnected();"<< std::endl;
    };
    virtual void triggerValueChanged() override {};
    virtual const std::string& getPinLabel() const override {
        return this->parent.getHasModifierName();
    };

    // - - - - - - - - - -
    //mutable bool isConnected;
    PinLink<MODIFIER_TYPE> myLink;

    const static enum OFXVP_MODIFIER_ modifierType = OFXVP_MODIFIER_INLET;
};

#endif
