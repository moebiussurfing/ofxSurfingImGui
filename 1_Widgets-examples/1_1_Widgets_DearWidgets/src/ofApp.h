#pragma once

#include "ofMain.h"

//-

#include "ofxImGui.h" // requires  https://github.com/Daandelange/ofxImGui or https://github.com/Daandelange/ofxImGui/tree/ofParameters-Helpers-Test
#include "ImGui/dear_widgets/dear_widgets.h"		// -> to use Dearwidgets
#include "ImGui/ofxSurfing_ImGui_WidgetsButtons.h"	// -> to use my custom toggle/buttons widgets and more
#include "ImGui/ofxSurfing_ImGui_WidgetsExtra.h"	// -> to use extra widgets
#include "ImGui/ofxSurfing_ImGui_RangeSlider.h"		// -> to use int/float ranges
#include "ImGui/ofxSurfing_ImGui_Helpers.h"	        // -> to use ofParameters
#include "ImGui/ofxSurfing_ImGui_LayoutManager.h"	// -> required to use layouting methods like ofxSurfingHelpers::refreshImGui_WidgetsSizes(.. We will stop using "old" ofxImGui here.

//#include "ofxSurfingImGui.h"						// -> This header includes ALL the above classes and some others. 
// You can simplify the workflow just adding only this header if you are planning to use many of the classes of this add-on.

// simplify with namespaces
using namespace ofxImGuiSurfing;

//-

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    
	// for a typical ofxImGui "clean" setup
	void setup_ImGui();
	ofxImGui::Gui gui;
	ImFont* customFont = nullptr;

	// NOTE: on the example 2_Layout_Basic you will see how to use ofxSurfing_ImGui_LayoutManager.h to speed up the ofxImGui instantiation and avoid the above lines.

    void draw_SurfingWidgets();
    void draw_DearWidgets();
    void draw_DearWidgetsColors();
    void draw_MoreWidgets();

    // parameters
    ofParameterGroup params;
    ofParameter<bool> bEnable1;
    ofParameter<bool> bEnable2;
    ofParameter<bool> bEnable3;
    ofParameter<bool> bPrevious;
    ofParameter<bool> bNext;
    ofParameter<float> lineWidth;
    ofParameter<float> separation;
    ofParameter<float> speed;
    ofParameter<int> shapeType;
    ofParameter<int> amount;
    ofParameter<int> size;
    ofParameterGroup params2;
    ofParameter<int> shapeType2;
    ofParameter<int> amount2;
    ofParameter<int> size2;
    ofParameterGroup params3;
    ofParameter<float> lineWidth3;
    ofParameter<float> separation3;
    ofParameter<float> speed3;
    ofParameter<int> shapeType3;
};
