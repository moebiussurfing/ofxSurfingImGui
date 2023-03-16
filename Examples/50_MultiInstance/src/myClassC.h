#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include <functional>
using callback_t = std::function<void()>;

class myClassC
{
public:

	myClassC();
	~myClassC();

	void setup();
	void draw();
	void setDrawWidgetsFunction(callback_t f = nullptr) {
		functionDraw = f;
	};

	ofxSurfingGui* ui = nullptr;

	void setUiPtr(ofxSurfingGui* _ui);

	ofParameterGroup params;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> shapeType;

	ofParameter<bool> bGui{ "myClassC", true };

	std::function<void()> functionDraw = nullptr;
};
