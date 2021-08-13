//
//  Preview.hpp
//  ImGUI
//
//  Created by Akira Hayasaka on 2017/04/25.
//
//

#ifndef Preview_hpp
#define Preview_hpp

#include "ofMain.h"
#include "Constants.h"
#include "Globals.hpp"

class Preview
{
public:
    
    Preview();
    ~Preview();
    
    void update();
    void draw();
    
    void togglePlaying();
    void stop() { vid.stop(); };
    void setFrame(int& frame) { vid.setFrame(frame); };
    void setPaused(const bool bPause) { vid.setPaused(bPause); };
    int getTtlNumFrame() { return vid.getTotalNumFrames(); };
    bool isPlaying() { return vid.isPlaying(); }
    
private:
    
    string sirokan_mov_path;
    
    ofVideoPlayer vid;
};

#endif /* Preview_hpp */
