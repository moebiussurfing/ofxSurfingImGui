//
//  Preview.cpp
//  ImGUI
//
//  Created by Akira Hayasaka on 2017/04/25.
//
//

#include "Preview.hpp"

Preview::Preview() :
sirokan_mov_path("movies/fingers.mov")
//sirokan_mov_path("movies")
//sirokan_mov_path("/Users/Akira/Project/20170213GrandCore/sirokan_small_mov/sirokan_small.mov")
{
    vid.load(sirokan_mov_path);
    ofLog() << "num frame = " << vid.getTotalNumFrames();
    ofLog() << "dur = " << vid.getDuration();
    
    ofAddListener(Global::ui->toggle_play_event, this, &Preview::togglePlaying);
    ofAddListener(Global::ui->preview_frame_change_event, this, &Preview::setFrame);
}

Preview::~Preview()
{
    
}

void Preview::update()
{
    if (vid.isPlaying())
        Global::ui->selected_frame = vid.getCurrentFrame();
        
    vid.update();
}

void Preview::draw()
{
    vid.draw(0, 0, APP_W, APP_H);
}

void Preview::togglePlaying()
{
    if (!vid.isPlaying())
    {
        vid.setPaused(false);
        vid.play();
    }
    else
        vid.setPaused(true);
}
