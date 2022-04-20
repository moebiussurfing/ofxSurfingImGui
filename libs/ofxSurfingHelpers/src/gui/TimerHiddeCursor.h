#pragma once

#include "ofMain.h"

//USE:
//call to restart timer when moving mouse, pressing key...etc
//	refreshCursor();

class TimerHiddeCursor
{
public:

	TimerHiddeCursor() {
	//hidden mouse
	lastmove = ofGetElapsedTimeMillis();
	ofShowCursor();
	bMouseHidden = false;
	};

~TimerHiddeCursor() {};
	
	//auto hide mouse
	uint64_t lastmove;
	int timerHideMouse = 10000;
	bool bMouseHidden = false;

	//--------------------------------------------------------------
	void update()
	{

//hidden mouse
	if (ofGetElapsedTimeMillis() - lastmove > timerHideMouse)
	{
		bMouseHidden = true;
		ofHideCursor();
	}
}

	//hidden mouse
	//--------------------------------------------------------------
	void refreshCursor() {
		lastmove = ofGetElapsedTimeMillis();
		if (bMouseHidden) {
			ofShowCursor();
			bMouseHidden = false;
		}
	}
};

