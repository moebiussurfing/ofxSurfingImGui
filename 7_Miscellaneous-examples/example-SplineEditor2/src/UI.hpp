//
//  UI.hpp
//  ImGUI
//
//  Created by Akira Hayasaka on 2017/04/25.
//
//

#ifndef UI_hpp
#define UI_hpp

#include "ofMain.h"
#include "ofxImGui.h"

class UI
{
public:
    
    UI();
    ~UI(){};
    void setup();
    void draw();
    
    ofxImGui::Gui gui;
    
    int num_preview_frame;
    int selected_frame;
    vector<ImVec2> controlPoints;
    
    ofEvent<int> preview_frame_change_event;
    ofEvent<void> toggle_play_event;
};

#endif /* UI_hpp */
