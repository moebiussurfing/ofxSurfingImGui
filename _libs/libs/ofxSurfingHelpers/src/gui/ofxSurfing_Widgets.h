#pragma once

#include "ofMain.h"

namespace ofxSurfingHelpers {

	/*

	 WIDGETS

	*/

	//--


	//--------------------------------------------------------------
	// circular progress bar
	//
	// example:
	//float val = ofMap(ofGetFrameNum() % 200, 0, 200, 0.f, 1.f, true);
	//ofxSurfingHelpers::drawCircleProg(val);
	//--------------------------------------------------------------
	inline void drawCircleProg(float val) {
		ofPushMatrix();
		ofPushStyle();
		ofSetLineWidth(5);

		ofRotateXDeg(-90);

		float radius = 50;
		float ratio = 0.7;

		//float val = 0.5;
		//float progress = val / 100;

		ofPoint point1(150, 120);

		ofNoFill();

		ofDrawRectangle(point1.x, point1.y, 100, 100);
		//int startAngle = -90 * 16;
		//int spanAngle = val * 360 * 16;		
		int startAngle = -90;
		int spanAngle = -90 + val * 360;
		//int spanAngle = progress * 360 * 16;

		//p.drawArc(rectangle, startAngle, spanAngle);
		//void ofPolyline_::arc(float x, float y, float radiusX, float radiusY, float angleBegin, float angleEnd, int circleResolution=20)
		//polyline1.arc(point1, 100, 100, 0, 360);

		ofPolyline polyline1;
		polyline1.lineTo(point1.x, point1.y + radius * ratio);
		polyline1.lineTo(point1.x, point1.y + radius);
		polyline1.arc(point1, radius, radius, startAngle, spanAngle);
		polyline1.arc(point1, radius*ratio, radius*ratio, startAngle, spanAngle);
		//polyline1.lineTo(0, point1.y + radius * ratio);
		//polyline1.lineTo(0, point1.y + radius);
		ofSetColor(ofColor::blue);
		polyline1.draw();

		string str = "prog" + ofToString(val * 100);
		//string str = "prog" + ofToString(progress * 100);
		ofDrawBitmapStringHighlight(str, point1.x, point1.y + 100);

		ofPopStyle();
		ofPopMatrix();
	}


	//--

	//ofDrawBitmapStringHighlight("No empty dock space, nowhere to draw for oF !", posX, posY);
	//ofBitmapFont f;
	//ofRectangle strSize = f.getBoundingBox("No empty dock space, nowhere to draw for oF !", posX, posY);

	//TODO:
	//fix variations..

	//--------------------------------------------------------------
	// draws a transparent box with centered text
	//--------------------------------------------------------------
#define BOX_PADDING 50
	inline void drawTextBoxed(ofTrueTypeFont &font, string text, int x = 0, int y = 0, ofColor font0_Color = 255, ofColor colorBackground = ofColor(0, 247), bool useShadow = false, ofColor colorShadow = 128, int _pad = 50, float _round = 5, int heighForced = -1)
	{
		x += 25;
		y += 33;

		//int _pad = 50;
		//float _round = 5;

		ofPushStyle();
		{
			//float fontSize = font.getSize();

			//TODO:
			// force load a default font
			if (!font.isLoaded())
			{
				font.load(OF_TTF_MONO, 10, true, true, true);
			}

			if (!font.isLoaded())
			{
				ofDrawBitmapStringHighlight(text, x, y);
			}
			else if (font.isLoaded())
			{
				// bbox
				ofSetColor(colorBackground);
				ofFill();

				ofRectangle _r(font.getStringBoundingBox(text, x, y));
				_r.setWidth(_r.getWidth() + _pad);
				_r.setX(_r.getPosition().x - _pad / 2.);
				_r.setY(_r.getPosition().y - _pad / 2.);

				if(heighForced == -1) _r.setHeight(_r.getHeight() + _pad);
				////TODO:
				//if (heighForced == -1) 
				//{
				//	float _h;
				//	bool b = !ofIsStringInString(text, "\n");//if only one line. 
				//	if(b) _h = font.getStringBoundingBox("I", 0, 0).getHeight();//hardcoded height
				//	else _h = _r.getHeight();
				//	_r.setHeight(_h + _pad);
				//}
				else _r.setHeight(heighForced + _pad);

				// Draw
				if(_round<= 0) ofDrawRectangle(_r);
				else ofDrawRectRounded(_r, _round);

				// Text shadow
				if (useShadow)
				{
					ofSetColor(colorShadow);
					font.drawString(text, x + 1, y + 1);
				}

				// Text
				ofSetColor(font0_Color);
				font.drawString(text, x, y);
			}
		}
		ofPopStyle();
	}

	//--------------------------------------------------------------
	// get box width
	//--------------------------------------------------------------

	inline float getWidthBBtextBoxed(ofTrueTypeFont &font, string text) {
		int _pad = BOX_PADDING;
		return (font.getStringBoundingBox(text, 0, 0)).getWidth() + _pad;
	}

	inline float getHeightBBtextBoxed(ofTrueTypeFont &font, string text) {
		int _pad = BOX_PADDING;
		return (font.getStringBoundingBox(text, 0, 0)).getHeight() + _pad;
	}

	inline glm::vec2 getShapeBBtextBoxed(ofTrueTypeFont &font, string text) {
		glm::vec2 sh(getWidthBBtextBoxed(font, text), getHeightBBtextBoxed(font, text));
		return sh;
	}
	
	//--------------------------------------------------------------



	//--------------------------------------------------------------
	//to debug/show mouse position and x,y coordinates to draw points into layouts
	//--------------------------------------------------------------
	inline void draw_Anchor(int x, int y)
	{
		ofPushStyle();
		ofFill();
		ofSetColor(ofColor::red);
		ofDrawCircle(x, y, 3);
		int pad;
		if (y < 15) pad = 20;
		else pad = -20;
		ofDrawBitmapStringHighlight(ofToString(x) + "," + ofToString(y), x, y + pad);
		ofPopStyle();
	}
};

