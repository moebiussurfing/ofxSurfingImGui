#pragma once

#include "ofMain.h"

class BarValue
{
private:
	ofTrueTypeFont fontCycle;
	float fontCycleSize;
	std::string label;
	std::string tittle;
	bool bLabel = false;
	bool bTitle = false;
public:
	void setLabel(std::string _label) {
		label = _label;
	}
	void setTitle(std::string _label) {
		tittle = _label;
		bTitle = true;
	}

	void setFont(string str, int size = 10) {
		fontCycleSize = size;
		std::string path = "assets/fonts/mono.ttf";
		if (!fontCycle.loadFont(path, fontCycleSize))
			fontCycle.loadFont(OF_TTF_MONO, fontCycleSize);
	}

public:
	void setColor(ofColor _color)
	{
		color.set(_color);
	}
	void setHeightMax(float _size)
	{
		heightMax = _size;
	}
	void setWidthMax(float _size)
	{
		widthMax = _size;
	}
	void setPosition(glm::vec2 _pos)
	{
		position = glm::vec2(_pos);
	}
	void setEnableBorder(bool b)
	{
		bBorder = b;
	}
	void setValue(float v)
	{
		value = v;
	}
	void setValueMin(float v)
	{
		valueMin = v;
	}
	void setValueMax(float v)
	{
		valueMax = v;
	}
	float getValue()
	{
		return value;
	}
	float getSize()
	{
		return height;
	}
	glm::vec2 getPosition()
	{
		return position;
	}
	float getX()
	{
		return position.x;
	}
	float getY()
	{
		return position.y;
	}

private:
	float value;
	float valueMin;
	float valueMax;

	ofColor color;
	ofColor colorBg;

	float height;
	float width;

	float widthMax;
	float heightMax;

	bool bOrientation;//true is vertical
	bool vFlip = true;

	glm::vec2 position;
	int alphaMax;
	int alpha;
	bool bBorder = true;

	float line;

	//-

public:
	BarValue() {
		color.set(255, 255, 255);
		colorBg.set(0, 0, 0, 200);
		alphaMax = 200;

		position = glm::vec2(200, 200);

		//vertical
		bOrientation = true;
		widthMax = 20;
		heightMax = 100;

		line = 1.0f;

		valueMin = 0;
		valueMax = 1;

		label = "";
		fontCycleSize = 10;
		if (!fontCycle.loadFont("assets/fonts/mono.ttf", fontCycleSize))
			fontCycle.loadFont(OF_TTF_MONO, fontCycleSize);
	};

	~BarValue() {};

	void draw(float val)//is updated here
	{
		value = val;

		ofPushStyle();

		//background dark
		ofFill();
		ofSetColor(colorBg);
		if (bOrientation) {
			ofDrawRectangle(position.x, position.y, widthMax, -heightMax);
		}

		//alpha = ofMap(value, 0, 1, 0, 255);
		alpha = ofMap(value, valueMin, valueMax, 0, 255);

		//border
		if (bBorder)
		{
			ofNoFill();
			ofSetLineWidth(line);
			ofSetColor(color, alphaMax * 0.1f *  + alpha * 0.9f);
			ofDrawRectangle(position.x, position.y, widthMax, -heightMax);
		}

		//value bar
		ofFill();
		ofSetColor(color, alphaMax * 0.1f + alpha * 0.9f);
		//ofSetColor(color, alphaMax);

		float _val = ofMap(value, valueMin, valueMax, 0, 1, false);
		//float _val = value;

		if (bOrientation) {//vertical
			height = _val * heightMax;
			ofDrawRectangle(position.x, position.y, widthMax, -height);
		}
		else {//TODO:
			width = _val * widthMax;
			ofDrawRectangle(position.x, position.y, width, heightMax);
		}

		// labels
		if (bLabel || bTitle)
		{
			ofPushStyle();
			if (bLabel) fontCycle.drawString(label, getX() - fontCycleSize, getY() + 0.5*fontCycleSize);
			//if (bTitle) fontCycle.drawString(tittle,
			//	getX() - widthMax - fontCycle.getStringBoundingBox(tittle, 0, 0).getWidth()*0.5,
			//	getY() - heightMax - 0.5*fontCycleSize - 5);

			if (bTitle) fontCycle.drawString(tittle,
				getX() + widthMax * 0.5 - fontCycle.getStringBoundingBox(tittle, 0, 0).getWidth()*0.5,
				getY() - heightMax - 0.5*fontCycleSize - 5);

			//if (bTitle) fontCycle.drawString(tittle, getX() - radiusMax, getY() - radiusMax - 0.5*fontCycleSize);// left upper corner
			ofPopStyle();
		}

		ofPopStyle();
	}

	void draw(float val, glm::vec2 pos, float w, float h) {
		position = pos;
		widthMax = w;
		heightMax = h;
		value = val;
		draw(value);
	}
};

