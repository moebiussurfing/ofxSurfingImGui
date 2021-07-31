#include "ofApp.h"

void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);
    ofSetFrameRate(60);
    
    Global::ui = make_shared<UI>();
    preview = make_shared<Preview>();
    Global::ui->num_preview_frame = preview->getTtlNumFrame();
    
    product.load("images/image3.jpg");
    product.resize(product.getWidth() * 0.5, product.getHeight() * 0.5);

    //product.load("/Users/Akira/Project/20170213GrandCore/UIDesign/product.png");
    //product.resize(product.getWidth() * 0.15, product.getHeight() * 0.15);
    
    testIdx = 0;
}

void ofApp::exit()
{
    Global::ui.reset();
}

void ofApp::update()
{
    preview->update();
}

void ofApp::draw()
{
    preview->draw();
    
    Global::ui->draw();
    
    ofDrawBitmapStringHighlight("fps:" + ofToString(ofGetFrameRate(), 2), 10, 10);
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    product.draw(ofGetWidth()/2, ofGetHeight()/2);
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void ofApp::keyPressed(int key)
{
    if (key == ' ')
        preview->togglePlaying();
}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
