#pragma once

#include "ofMain.h"

class CircleCycle
{
public:

	void ofxArcStrip(float innerRadius, float outerRadius, float startAngle, float stopAngle) {  //radians
#ifndef TARGET_OPENGLES
		float delta = fabs(stopAngle - startAngle);
		if (delta < .00001) return; //don't draw if arc to small
		int n = 200 * delta / TWO_PI; //a full circle=200 segments
		if (n == 0) return;
		glBegin(GL_TRIANGLE_STRIP); //GL_TRIANGLE_STRIP); //change to GL_LINE_LOOP);  for hollow
		for (int i = 0; i <= n; i++) {
			float f = -ofMap(i, 0, n, startAngle, stopAngle);
			float x1 = innerRadius * cos(f);
			float y1 = innerRadius * sin(f);
			float xRect = outerRadius * cos(f);
			float yRect = outerRadius * sin(f);
			glVertex2f(x1, y1);
			glVertex2f(xRect, yRect);
		}
		glEnd();
#endif
	}

	void ofxArc(float radius, float startAngle, float stopAngle, int detail) { //radians
#ifndef TARGET_OPENGLES
		glBegin(GL_LINE_STRIP);
		for (int i = 0, n = detail; i <= n; i++) {
			float f = -ofMap(i, 0, n, startAngle, stopAngle);
			float x = radius * cos(f);
			float y = radius * sin(f);
			glVertex2f(x, y);
		}
		glEnd();
#endif
	}


	void setFps(float _fps)
	{
		dt = 1.0f / _fps;
		speedRatio = _fps / 10.0f;
	}
	void setColor(ofColor _color)
	{
		color.set(_color);
	}
	void setColorBackground(ofColor _color)
	{
		colorBg.set(_color);
	}
	void setAlpha(float _alpha)
	{
		int a = ofMap(_alpha, 0.0f, 1.0f, 0, 255);
		alphaMax = a;

		ofColor c = ofColor(colorBg);
		colorBg = ofColor(c.r, c.g, c.b, alphaMax);
	}
	void setSpeed(float _speed)
	{
		ofClamp(_speed, 0.01f, 1.0f);
		animSpeed = _speed;
	}
	void setRadius(float _size)
	{
		radiusMax = _size;
		radiusMin = radiusMax * 0.4;
	}
	void setRadiusMin(float _size)
	{
		radiusMin = _size;
	}
	void setRadiusMax(float _size)
	{
		radiusMax = _size;
	}
	void setPosition(glm::vec2 _pos)
	{
		position = glm::vec2(_pos);
	}
	void setEnableBorder(bool b)
	{
		bBorder = b;
	}
	float getValue()
	{
		float f = ofClamp(1.0f - animCounter, 0.f, 1.f);
		return f;
	}
	float getRadius()
	{
		return radiusMax;
	}

	float getX()
	{
		return position.x;
	}
	float getY()
	{
		return position.y;
	}
	glm::vec2 getPosition()
	{
		return position;
	}

private:
	ofParameter<float> animSpeed;
	ofColor color;
	ofColor colorBg;
	float radiusMax;
	float radiusMin;
	glm::vec2 position;
	int alphaMax;
	int alphaMin;
	bool bBorder = true;

	float dt;
	float animCounter;
	bool animRunning;
	float alpha;
	float line;

	float speedRatio = 6.0f;
	float value;

	//-

	bool bLabel = false;
	bool bTitle = false;

public:
	void setEnableLabel(bool b) {
		bLabel = b;
	}

	void setFont(string str, int size = 10) {
		fontCycleSize = size;
		std::string path = "assets/fonts/mono.ttf";
		if (!fontCycle.loadFont(path, fontCycleSize))
			fontCycle.loadFont(OF_TTF_MONO, fontCycleSize);
	}

private:
	ofTrueTypeFont fontCycle;
	float fontCycleSize;
	std::string label;
	std::string tittle;
public:
	void setLabel(std::string _label) {
		label = _label;
	}
	void setTitle(std::string _label) {
		tittle = _label;
		bTitle = true;
	}

	//-

public:
	CircleCycle() {
		//float res = ofGetCircleResolution();
		//cout << "res:" << res<<endl;
		ofSetCircleResolution(100);

		color.set(255, 255, 255);
		colorBg.set(0, 0, 0, 32);
		alphaMax = 220;
		alphaMin = 100;

		setFps(60);
		alpha = 0.0f;
		position = glm::vec2(200, 200);
		animSpeed.set("animSpeed", .5f, 0.01f, 1.f);

		radiusMax = 100;
		radiusMin = radiusMax * 0.8;

		setSpeed(0.2);
		line = 2.0f;

		label = "";
		fontCycleSize = 10;
		std::string path = "assets/fonts/mono.ttf";
		if (!fontCycle.loadFont(path, fontCycleSize))
			fontCycle.loadFont(OF_TTF_MONO, fontCycleSize);
	};

	~CircleCycle() {};

	void bang()
	{
		animCounter = 0.0f;//anim from 0.0 to 1.0
	}

	void draw(float v)
	{
		ofPushStyle();

		v = ofClamp(v, 0.f, 1.f);

		//background dark
		ofFill();
		ofSetColor(colorBg);
		ofPushMatrix();
		ofTranslate(position);
		ofxArcStrip(radiusMin, radiusMax, ofDegToRad(0), ofDegToRad(360));
		ofPopMatrix();

		animRunning = animCounter <= 1.0f;
		if (animRunning) animCounter += speedRatio * animSpeed * dt;

		ofFill();
		if (animRunning)
		{
			alpha = ofMap(animCounter, 0, 1, alphaMax, alphaMin, true);
		}
		else
		{
			alpha = alphaMin;
		}
		ofPushMatrix();
		ofTranslate(position);
		ofSetColor(color.r, color.g, color.b, alpha);//faded alpha
		float _off = 90;
		float _rad = ofMap(v, 0, 1, ofDegToRad(0 + _off), ofDegToRad(360 + _off));
		//float _rad = ofMap(v, 1, 0, ofDegToRad(360 + _off), ofDegToRad(0 + _off));
		//ofxArcStrip(radiusMin, radiusMax, ofDegToRad(0 + _off), _rad);
		ofxArcStrip(radiusMin, radiusMax, _rad, ofDegToRad(0 + _off));
		ofPopMatrix();

		// TODO:
		//if (bBorder)
		//{
		//	ofNoFill();
		//	if (radiusMax > 20)	ofSetLineWidth(line);
		//	else ofSetLineWidth(1.0f);
		//	ofSetColor(color, alphaMax * 0.2f + alpha * 0.8f);
		//	//ofSetColor(color, alpha);
		//	ofDrawCircle(position, radiusMax);
		//}

		// labels
		if (bLabel || bTitle)
		{
			ofPushStyle();
			if (bLabel) fontCycle.drawString(label, getX() - fontCycleSize, getY() + 0.5*fontCycleSize);
			if (bTitle) fontCycle.drawString(tittle, 
				getX() - fontCycle.getStringBoundingBox(tittle,0,0).getWidth()*0.5, 
				getY() - radiusMax - 0.5*fontCycleSize - 5);
			//if (bTitle) fontCycle.drawString(tittle, getX() - radiusMax, getY() - radiusMax - 0.5*fontCycleSize);// left upper corner
			ofPopStyle();
		}

		ofPopStyle();
	}

	//void draw(glm::vec2 pos, float size) {
	//	position = pos;
	//	radiusMax = size;
	//	radiusMin = radiusMax * 0.8;

	//	draw();
	//}
};

