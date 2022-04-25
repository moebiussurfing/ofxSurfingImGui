#pragma once

#include "ofMain.h"

class CircleBeat
{
public:

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
		radiusMin = radiusMax*0.2;
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
	bool bBorder = true;

	float dt;
	float animCounter;
	bool animRunning;
	float alpha;
	float line;

	float speedRatio = 6.0f;

	//-

public:
	CircleBeat() {
		//float res = ofGetCircleResolution();
		//cout << "res:" << res<<endl;
		//ofSetCircleResolution()
		ofSetCircleResolution(100);

		color.set(255, 255, 255);
		colorBg.set(0, 0, 0, 200);
		alphaMax = 200;

		dt = 1.0f / 60.f;
		alpha = 0.0f;
		position = glm::vec2(200, 200);
		animSpeed.set("animSpeed", 0.5f, 0.01f, 1.f);

		radiusMax = 100;
		radiusMin = radiusMax * 0.8;

		line = 2.0f;
	};

	~CircleBeat() {};

	void bang()
	{
		animCounter = 0.0f;//anim from 0.0 to 1.0
	}

	void update()
	{
		animRunning = animCounter <= 1.0f;
		if (animRunning)
			animCounter += speedRatio * animSpeed * dt;
	}

	void draw()
	{
		//update();

		ofPushStyle();
		
		//background dark
		ofFill();
		ofSetColor(colorBg);
		ofDrawCircle(position, radiusMax);

		if (animRunning)
		{
			ofFill();
			alpha = ofMap(animCounter, 0, 1, alphaMax, 0);
			float _radius = ofMap(animCounter, 0, 1, radiusMax, radiusMin);

			ofSetColor(color.r, color.g, color.b, alpha);//faded alpha
			ofDrawCircle(position, _radius);
		}

		if (bBorder)
		{
			ofNoFill();
			if (radiusMax > 20)	ofSetLineWidth(line);
			else ofSetLineWidth(1.0f);

			ofSetColor(color, alphaMax * 0.2f + alpha * 0.8f);
			//ofSetColor(color, alpha);

			ofDrawCircle(position, radiusMax);
		}

		ofPopStyle();
	}

	void draw(glm::vec2 pos, float size) {
		position = pos;
		radiusMax = size;
		radiusMin = radiusMax * 0.8;

		draw();
	}
};

