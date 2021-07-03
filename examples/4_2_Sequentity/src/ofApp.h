#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"	

#include "Surfing_Sequentity.h"	
//#include "Surfing_ImSequencer.h"	


/* NOT WORKING */


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxSurfing_ImGui_Manager guiManager;
		void drawWidgets();
		void drawTimeline();

		//Surfing_ImSequencer sequencer;

		bool bOpen0 = true;
		bool bOpen1 = true;
		bool bOpen2 = false;

		bool bPlay = false;
};
