#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

// Required for the advanced feature
#include <functional>
using callback_t = std::function<void()>;

class myClassC
{
public:

	myClassC();
	~myClassC();

	void setup();
	void draw();

private:
	ofxSurfingGui* ui = nullptr;
public:
	void setUiPtr(ofxSurfingGui* _ui);

public:
	ofParameterGroup params;
	ofParameter<float> lineWidth;
	ofParameter<float> separation;
	ofParameter<float> speed;
	ofParameter<int> shapeType;

	ofParameter<bool> bGui{ "myClassC", true };

	//--

	// Pointer to store a function
	callback_t functionDraw = nullptr;
	//std::function<void()> functionDraw = nullptr;

	// Set external widgets to be inserted!
	void setDrawWidgetsFunction(callback_t f = nullptr) {
		functionDraw = f;
	};
};
