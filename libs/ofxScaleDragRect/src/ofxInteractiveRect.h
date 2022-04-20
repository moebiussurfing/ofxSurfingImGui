//
//  interactiveRect.h
//
//  Created by Roy Macdonald on 8/15/12.
//  Copyright (c) 2012 micasa. All rights reserved.
//
//  Updated by Aaron Richards on 13/05/2014.
//  Updated by moebiusSurfing 2020, 2021
//


/*

TODO:

+ blink on editing
+ add border drawer, edit... on param group ready to add to a gui
+ multiple positions left-rigth..etc
+ double click to enable edit mode. Using MSAInteractive
+ aspect ratio like camera mode,
+ add helpers to rect fit, expand etc..
+ fix rare from center scaling on text box widget
+ add mouse scroll drag and scale ctrl / alt
+ add mouse drag scale from center (get from ofxSCENE-SVG)
+ lock x, y, w, h upper/bottom drag borders
+ lock min/max size for the rect and avoid flipping..
+ path setteable

*/


#pragma once

#include "ofMain.h"

#define BORDER_DRAG_SIZE 11

// Timing tools
namespace
{
	/* Return a linear value in range [0,1] every delay (in seconds). */
	//--------------------------------------------------------------
	float Tick(float delay = 1.0f) {
		return fmodf(ofGetElapsedTimeMillis() / 1000.0f, delay) / delay;
	}

	/* Return a linear value in range [0,1] every delay (in seconds),
	 with value equal 0 at boundaries, and 1 at delay / 2. */
	 //--------------------------------------------------------------
	float Bounce(float delay = 1.0f) {
		return 0.5f*(1.0 + glm::sin(Tick(delay) * glm::two_pi<float>()));
	}
} // namespace

//--------------------------------------------------------------
class ofxInteractiveRect : public ofRectangle
{

private:
	ofColor colorBorderDraggable = { ofColor::yellow }; // Draggable borders
	ofColor colorEditingHover{ ofColor(50, 20) }; // Rect fill when editing
	ofColor colorEditingPressedBorder{ ofColor(50, 200) }; // Borders
	ofColor colorEditingMoving{ ofColor(127, 127) }; // Borders. fill color when hover and moving the rectangle

	bool bDrawBroder = true;

public:
	//--------------------------------------------------------------
	ofParameter<ofRectangle>& getParameter() {
		return rectParam;
	}
private:
	ofParameter<ofRectangle> rectParam{ "recetParam", ofRectangle(), ofRectangle(), ofRectangle() };
	void Changed_Rect(ofRectangle & r);

	// Rounded
	bool bRounded = false;
	float rounded = 5.0;
public:
	//--------------------------------------------------------------
	void setRounded(float r) {
		if (r > 0) bRounded = true;
		else bRounded = false;
		rounded = r;
	}

	//TODO:
private:
	bool bLockX = false;
	bool bLockY = false;
	bool bLockW = false;
	bool bLockH = false;
	
	bool bTransparent = false;

public:
	void setLockX(bool b) { bLockX = b; };
	void setLockY(bool b) { bLockY = b; };
	void setLockW(bool b) { bLockW = b; };
	void setLockH(bool b) { bLockH = b; };

public:
	ofParameter<bool> bLockResize{ "Lock Resize", false };
	ofParameter<bool> bLock{ "Lock", false };

	//TODO:
	ofParameter<bool> bLockAspectRatio{ "Lock AspectRatio", false };
	//--------------------------------------------------------------
	void setLockAspectRatio(bool b) {
		bLockAspectRatio = b;
	}

	//--------------------------------------------------------------
	void setLockResize(bool b) {
		bLockResize = b;
	}
	//--------------------------------------------------------------
	void setLock(bool b) {
		bLock = b;
	}
	//--------------------------------------------------------------
	void setTransparent() {
		bTransparent = true;
		setColorEditingHover(ofColor(0, 0));
		setColorEditingMoving(ofColor(0, 0)); 
	}

	//--------------------------------------------------------------
	void setColorBorderDraggable(const ofColor c) {
		colorBorderDraggable = c;
	}
	//--------------------------------------------------------------
	void setColorEditingHover(const ofColor c) {
		colorEditingHover = c;
	}
	//--------------------------------------------------------------
	void setColorEditingPressedBorder(const ofColor c) {
		colorEditingPressedBorder = c;
	}
	//--------------------------------------------------------------
	void setColorEditingMoving(const ofColor c) {
		colorEditingMoving = c;
	}

	//--------------------------------------------------------------
	bool isMouseOver() {
		bool b = inside(ofGetMouseX(), ofGetMouseY());

		return b;
	}
private:
	bool bAllScreenMouse = false;

public:
	//--------------------------------------------------------------
	void setAllScreenMouse(bool b) {
		bAllScreenMouse = b;
	}

	ofxInteractiveRect(string name, string path = "");
	virtual ~ofxInteractiveRect();

	void enableEdit(bool enable = true);
	void disableEdit();
	void toggleEdit();
	bool isEditing() { return bIsEditing; }

	void draw();
	void drawBorder();

	bool loadSettings(string name = "", string path = "", bool loadJson = false);
	void saveSettings(string name = "", string path = "", bool saveJson = false);

	//TODO:
	//store name and path to allow autosave..
private:
	bool bAutoSave = true;

public:
	//--------------------------------------------------------------
	void setAutoSave(bool b = true) {
		bAutoSave = b;

		if (b)
		{
			loadSettings();
		}
	}

public:
//private:
	void mouseMoved(ofMouseEventArgs & mouse);
	void mousePressed(ofMouseEventArgs & mouse);
	void mouseDragged(ofMouseEventArgs & mouse);
	void mouseReleased(ofMouseEventArgs & mouse);

	void mouseScrolled(ofMouseEventArgs & mouse);
	void mouseEntered(ofMouseEventArgs & mouse);
	void mouseExited(ofMouseEventArgs & mouse);

public:
	float getRectX() { return x; }
	float getRectY() { return y; }
	float getRectWidth() { return width; }
	float getRectHeight() { return height; }

private:
	string name;
	string path;

public:
	ofRectangle getRect();
	//--------------------------------------------------------------
	void setRect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

private:
	ofJson toJson();
	void fromJson(const ofJson& j);

	ofXml toXml();
	bool fromXml(const ofXml& x);

public:
	ofParameter<bool> bEditMode{ "EDIT BOX", false };
	void Changed_EditMode(bool & b);

protected:
	bool bIsEditing;
	bool bMove;
	bool bIsOver;
	bool bLeft, bRight, bUp, bDown;
	bool bPressed;
	glm::vec2 mousePrev;

	std::string prefixName = "Rectangle_";

	//--

	// Restore/reset position and shape
public:
	//--------------------------------------------------------------
	void setCentered()
	{
		setPosition(ofGetWidth() / 2 - getWidth() / 2, ofGetHeight() / 2 - getHeight() / 2);
	}
	//--------------------------------------------------------------
	void setRestoreSize()
	{
		setWidth(800);
		setHeight(800 / (16 / 9.f));
	}
	//--------------------------------------------------------------
	void setRestore()
	{
		setRestoreSize();
		setCentered();
	}
};
