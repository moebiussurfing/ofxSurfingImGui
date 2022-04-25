//
//  interactiveRect.cpp
//
//  Created by Roy Macdonald on 8/15/12.
//  Copyright (c) 2012 micasa. All rights reserved.
//
//  Updated by Aaron Richards on 13/05/2014.
//	Updated by moebiusSurfing 2021

#include "ofxInteractiveRect.h"

//--------------------------------------------------------------
ofxInteractiveRect::ofxInteractiveRect(string name, string path)
{
	bEditMode.addListener(this, &ofxInteractiveRect::Changed_EditMode);
	rectParam.addListener(this, &ofxInteractiveRect::Changed_Rect);

	bLockResize = false;
	bLock = false;

	bIsEditing = false;
	bMove = false;
	bLeft = false;
	bRight = false;
	bUp = false;
	bDown = false;
	bIsOver = false;
	this->name = name;
	//this->path = "";

	setRect(10, 10, 400, 400);
	if (bAutoSave) loadSettings();

	// Some grey coloring
	setColorBorderDraggable(ofColor(0, 128));
	setColorEditingPressedBorder(ofColor(0, 128));
	setColorEditingMoving(ofColor(128, 32));
}

//--------------------------------------------------------------
ofxInteractiveRect::~ofxInteractiveRect()
{
	bEditMode.removeListener(this, &ofxInteractiveRect::Changed_EditMode);
	rectParam.removeListener(this, &ofxInteractiveRect::Changed_Rect);

	if (bAutoSave) saveSettings();
}

//--------------------------------------------------------------
void ofxInteractiveRect::enableEdit(bool enable)
{
	ofLogVerbose(__FUNCTION__) << "Rect " << this->name << " edit : " << (string)(enable ? "true" : "false");

	if (enable != bIsEditing)
	{
		if (enable)
		{
			ofRegisterMouseEvents(this);
		}
		else
		{
			ofUnregisterMouseEvents(this);
			//saveSettings();
		}
		bIsEditing = enable;

		bEditMode.setWithoutEventNotifications(bIsEditing);
	}
}

//--------------------------------------------------------------
void ofxInteractiveRect::disableEdit()
{
	enableEdit(false);
}

//--------------------------------------------------------------
void ofxInteractiveRect::toggleEdit()
{
	enableEdit(!bIsEditing);
}

//--------------------------------------------------------------
ofRectangle ofxInteractiveRect::getRect()
{
	return ofRectangle(x, y, width, height);
}

//--------------------------------------------------------------
void ofxInteractiveRect::saveSettings(string name, string path, bool saveJson)
{
	if (name != "")
	{
		this->name = name;
	}

	if (path != "")
	{
		this->path = path;
	}

	string filename = this->path + prefixName + this->name;

	if (saveJson) {
		filename += ".json";
		ofSaveJson(filename, toJson());
	}
	else {
		filename += ".xml";
		toXml().save(filename);
	}

	ofLogVerbose(__FUNCTION__) << filename;
}

ofJson ofxInteractiveRect::toJson()
{
	ofJson j;//("interactiveRect");

	j["x"] = this->ofRectangle::x;
	j["y"] = this->ofRectangle::y;
	j["width"] = this->ofRectangle::width;
	j["height"] = this->ofRectangle::height;
	j["name"] = this->name;
	j["path"] = this->path;
	j["isEditing"] = this->bIsEditing;
	return j;
}

void ofxInteractiveRect::fromJson(const ofJson& j)
{
	if (j == nullptr) return;//TODO: crash

	j["x"].get_to(this->ofRectangle::x);
	j["y"].get_to(this->ofRectangle::y);
	j["width"].get_to(this->ofRectangle::width);
	j["height"].get_to(this->ofRectangle::height);
	j["name"].get_to(this->name);
	j["path"].get_to(this->path);
	bool editing;

	j["isEditing"].get_to(editing);
	enableEdit(editing);
}

ofXml ofxInteractiveRect::toXml()
{
	ofXml xml;
	auto r = xml.appendChild("interactiveRect");

	r.appendChild("path").set(this->path);
	r.appendChild("x").set(this->ofRectangle::x);
	r.appendChild("y").set(this->ofRectangle::y);
	r.appendChild("width").set(this->ofRectangle::width);
	r.appendChild("height").set(this->ofRectangle::height);
	r.appendChild("name").set(this->name);
	r.appendChild("isEditing").set(this->bIsEditing);

	return xml;
}

bool ofxInteractiveRect::fromXml(const ofXml& xml)
{
	auto r = xml.getChild("interactiveRect");
	if (r)
	{
		this->path = r.getChild("path").getValue();
		this->ofRectangle::x = r.getChild("x").getFloatValue();
		this->ofRectangle::y = r.getChild("y").getFloatValue();
		this->ofRectangle::width = r.getChild("width").getFloatValue();
		this->ofRectangle::height = r.getChild("height").getFloatValue();
		this->name = r.getChild("name").getValue();
		enableEdit(r.getChild("isEditing").getBoolValue());

		return true;
	}

	return false;
}

//--------------------------------------------------------------
bool ofxInteractiveRect::loadSettings(string name, string path, bool loadJson)
{
	if (name != "")
	{
		this->name = name;
	}

	if (path != "")
	{
		this->path = path;
	}

	string filename = this->path + prefixName + this->name;

	if (loadJson)
	{
		filename += ".json";

		//avoid crash
		ofFile file;
		file.open(filename);
		if (!file.exists()) return false;

		fromJson(ofLoadJson(filename));
		return true;

	}
	else {
		filename += ".xml";

		//avoid crash
		ofFile file;
		file.open(filename);
		if (!file.exists()) return false;

		ofXml xml;
		if (xml.load(filename))
		{
			if (fromXml(xml))
			{
				return true;
			}
		}
	}
	ofLogVerbose(__FUNCTION__) << "unable to load : " << filename;

	rectParam.set(this->getRect());

	return false;
}

//TODO:
//--------------------------------------------------------------
void ofxInteractiveRect::drawBorder()
{
	if (bTransparent) return;

	//-

	ofPushStyle();
	ofNoFill();
	ofSetLineWidth(2.0);
	if (bEditMode) ofSetColor(ofColor(colorEditingMoving.r, colorEditingMoving.g, colorEditingMoving.b, colorEditingMoving.a * Bounce()));
	else ofSetColor(colorEditingMoving);
	if (bRounded) ofDrawRectRounded(*this, rounded);
	else ofDrawRectangle(*this);
	ofPopStyle();
}

//--------------------------------------------------------------
void ofxInteractiveRect::draw()
{
	if (bTransparent) return;

	//-

	if (bIsEditing)
	{
		ofPushStyle();

		// Hover
		if (bIsOver)
		{
			// Border
			ofNoFill();
			if (!bPressed)
			{
				//ofSetColor(ofColor(ofColor::orange, 128));
				ofSetColor(colorEditingHover);
			}
			else
			{
				//ofSetColor(ofColor(ofColor::red, 128));
				ofSetColor(colorEditingPressedBorder);
			}

			if (bRounded) ofDrawRectRounded(*this, rounded);
			else ofDrawRectangle(*this);
		}

		// Border
		//else 
		{
			drawBorder(); // will blink
		}

		// Fill
		ofFill();
		if (bMove) // when moving
		{
			ofSetColor(colorEditingMoving);

			if (bRounded) ofDrawRectRounded(*this, rounded);
			else ofDrawRectangle(*this);
		}
		else // when static
		{
			// Draggable borders

			ofSetColor(colorBorderDraggable.r, colorBorderDraggable.g, colorBorderDraggable.b, colorBorderDraggable.a * 0.5);

			if (bUp)
			{
				ofDrawRectRounded(x, y, width, BORDER_DRAG_SIZE, rounded);
			}
			else if (bDown)
			{
				ofDrawRectRounded(x, y + height - BORDER_DRAG_SIZE, width, BORDER_DRAG_SIZE, rounded);
			}
			if (bLeft)
			{
				ofDrawRectRounded(x, y, BORDER_DRAG_SIZE, height, rounded);
			}
			else if (bRight)
			{
				ofDrawRectRounded(x + width - BORDER_DRAG_SIZE, y, BORDER_DRAG_SIZE, height, rounded);
			}
		}

		ofPopStyle();
	}
}

//--------------------------------------------------------------
void ofxInteractiveRect::mouseMoved(ofMouseEventArgs & mouse)
{
	if (bLock) return;

	if (!bPressed)
	{
		bIsOver = inside(mouse.x, mouse.y);

		bLeft = false;
		bRight = false;
		bUp = false;
		bDown = false;

		if (bIsOver)
		{
			bMove = true;

			if (!bLockResize)
			{
				if (mouse.x < x + BORDER_DRAG_SIZE && mouse.x > x && !bLockW)
				{
					bLeft = true;
					bMove = false;
				}
				else if (mouse.x < x + width && mouse.x > x + width - BORDER_DRAG_SIZE && !bLockW)
				{
					bRight = true;
					bMove = false;
				}

				if (mouse.y > y && mouse.y < y + BORDER_DRAG_SIZE && !bLockH)
				{
					bUp = true;
					bMove = false;
				}
				else if (mouse.y > y + height - BORDER_DRAG_SIZE && mouse.y < y + height && !bLockH)
				{
					bDown = true;
					bMove = false;
				}
			}
		}
		else
		{
			bMove = false;
		}
	}
}

//--------------------------------------------------------------
void ofxInteractiveRect::mousePressed(ofMouseEventArgs & mouse)
{
	if (bLock) return;

	mousePrev = mouse;
	bPressed = true;

	if (!bAllScreenMouse) bIsOver = inside(mouse.x, mouse.y);
	else bIsOver = true;

	bLeft = false;
	bRight = false;
	bUp = false;
	bDown = false;

	if (bIsOver)
	{
		bMove = true;

		if (!bLockResize)
		{
			if (mouse.x < x + BORDER_DRAG_SIZE && mouse.x > x && !bLockW)
			{
				bLeft = true;
				bMove = false;
			}
			else if (mouse.x < x + width && mouse.x > x + width - BORDER_DRAG_SIZE && !bLockW)
			{
				bRight = true;
				bMove = false;
			}
			if (mouse.y > y && mouse.y < y + BORDER_DRAG_SIZE && !bLockH)
			{
				bUp = true;
				bMove = false;
			}
			else if (mouse.y > y + height - BORDER_DRAG_SIZE && mouse.y < y + height && !bLockH)
			{
				bDown = true;
				bMove = false;
			}
		}
	}
	else
	{
		bMove = false;
	}
}

//--------------------------------------------------------------
void ofxInteractiveRect::mouseDragged(ofMouseEventArgs & mouse)
{
	if (bLock) return;

	//if (!bLockResize) 
	{
		if (bUp && !bLockX)
		{
			y += mouse.y - mousePrev.y;
			height += mousePrev.y - mouse.y;
		}
		else if (bDown && !bLockY)
		{
			height += mouse.y - mousePrev.y;
		}
		if (bLeft && !bLockW)
		{
			x += mouse.x - mousePrev.x;
			width += mousePrev.x - mouse.x;
		}
		else if (bRight && !bLockH)
		{
			width += mouse.x - mousePrev.x;
		}
	}

	if (bMove)
	{
		x += mouse.x - mousePrev.x;
		y += mouse.y - mousePrev.y;
	}

	mousePrev = mouse;
}

//--------------------------------------------------------------
void ofxInteractiveRect::mouseReleased(ofMouseEventArgs & mouse)
{
	if (bLock) return;

	//if (!bLockResize) 
	{
		bLeft = false;
		bRight = false;
		bUp = false;
		bDown = false;
	}
	bMove = false;
	bPressed = false;

	// clamp inside the window
	int _min = 20;
	width = ofClamp(width, _min, ofGetWidth());
	height = ofClamp(height, _min, ofGetHeight());

	rectParam.set(this->getRect());
}

//--------------------------------------------------------------
void ofxInteractiveRect::Changed_EditMode(bool & b)
{
	ofLogNotice(__FUNCTION__) << b;

	enableEdit(b);
}

//--------------------------------------------------------------
void ofxInteractiveRect::Changed_Rect(ofRectangle & r)
{
	ofLogNotice(__FUNCTION__) << r;

	this->set(r);
}

//--------------------------------------------------------------
void ofxInteractiveRect::mouseScrolled(ofMouseEventArgs & mouse) {}
void ofxInteractiveRect::mouseEntered(ofMouseEventArgs & mouse) {}
void ofxInteractiveRect::mouseExited(ofMouseEventArgs & mouse) {}