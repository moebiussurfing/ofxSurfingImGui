#pragma once

#include "ofMain.h"

/*
	This classes can split a glm:vec (2, 3 and 4 dims) ofParameter to the float elements ofParams.
	And the multidim glm params will be auto linked to the float parts.
	All is autoupdated and is public exposed to be populated into a gui,
	with the elements separated.
	Surely is a dirty approach, ald could be better done.
	by moebiusSurfing.

*/

/*
//params.add(camEulerAngles_Split.x);
//params.add(camEulerAngles_Split.y);
//params.add(camEulerAngles_Split.z);
//params.add(camLookAt_Split.x);
//params.add(camLookAt_Split.y);
//params.add(camLookAt_Split.z);
*/


/*

// Example
// ofApp.h
#pragma once

#include "ofMain.h"

#include "glmSplit.h"
#include "ofxGui.h"

//--

class ofApp : public ofBaseApp {

public:

	ofxPanel gui;
	ofxPanel guiSplitter;

	ofParameter<glm::vec2> v2{ "myVec2", glm::vec2(0.25), glm::vec2(0), glm::vec2(1) };
	ofParameter<glm::vec3> v3{ "myVec3", glm::vec3(0.25), glm::vec3(0), glm::vec3(1) };

	surfingGlmSplitter2 sp_v2;
	surfingGlmSplitter3 sp_v3;

	void setup() {
		sp_v2.setup(v2);
		sp_v3.setup(v3);

		gui.setup("glm:vec");
		gui.setPosition(10, 10);
		gui.add(v2);
		gui.add(v3);

		guiSplitter.setup("glmsplit:float");
		guiSplitter.setPosition(300, 10);
		guiSplitter.add(sp_v2.floats);
		guiSplitter.add(sp_v3.floats);
	};

	void draw() {
		gui.draw();
		guiSplitter.draw();
	};
};

*/

//TODO:

/*
class surfingGlmSplitter4
{
public:
	surfingGlmSplitter4() {};
	~surfingGlmSplitter4() {};

	//TODO:
	bool bNormalized = false; // 0 to 1
	bool bSigned = false; // -1 to +1

private:
	ofEventListener listenerParams;

public:
	ofParameter<float> x{ "x", 0, 0, 1 };
	ofParameter<float> y{ "y", 0, 0, 1 };
	ofParameter<float> z{ "z", 0, 0, 1 };
	ofParameter<float> w{ "w", 0, 0, 1 };

private:
	ofParameterGroup params{ "params" };

public:
	ofParameterGroup floats{ "Floats" };

	ofParameter<glm::vec4> vecRef{ "-1",glm::vec4(0.5),glm::vec4(0),glm::vec4(1) };

private:
	void set(ofParameter<glm::vec4> _v) {
		x.set(_v.get().x);
		y.set(_v.get().y);
		z.set(_v.get().z);
		w.set(_v.get().w);

		// limits
		x.setMin(_v.getMin().x);
		y.setMin(_v.getMin().y);
		z.setMin(_v.getMin().z);
		w.setMin(_v.getMin().w);
		x.setMax(_v.getMax().x);
		y.setMax(_v.getMax().y);
		z.setMax(_v.getMax().z);
		w.setMax(_v.getMax().w);
	}

public:
	void setup(ofParameter<glm::vec4> &_v) {
		vecRef.makeReferenceTo(_v);

		std::string n = _v.getName();
		x.setName(n + " x");
		y.setName(n + " y");
		z.setName(n + " z");
		w.setName(n + " w");

		set(_v);

		params.setName(n);
		params.add(vecRef);

		params.add(x);
		params.add(y);
		params.add(z);
		params.add(w);

		floats.setName(_v.getName());
		floats.add(x);
		floats.add(y);
		floats.add(z);
		floats.add(w);

		setup();
	}

private:
	void setup() {

		listenerParams = params.parameterChangedE().newListener([&](ofAbstractParameter&p) {
			string name = p.getName();

			static bool bdisable = false;

			if (name == "-1")
			{
				return;
			}

			if (name == vecRef.getName()) {
				x.setWithoutEventNotifications(vecRef.get().x);
				y.setWithoutEventNotifications(vecRef.get().y);
				z.setWithoutEventNotifications(vecRef.get().z);
				w.setWithoutEventNotifications(vecRef.get().w);

				x = x;
				y = y;
				z = z;
				w = w;
			}

			else {
				if (p.type() == typeid(ofParameter<float>).name())
				{
					ofParameter<float> pm = p.cast<float>();
					ofLogNotice() << "glmSplitter : " << name << " : " << pm.get();
				}
				else { return; }

				if (!bNormalized) {
					if (name == x.getName())
					{
						vecRef.set(glm::vec4(x, y, z, w));
					}
					else if (name == y.getName())
					{
						vecRef.set(glm::vec4(x, y, z, w));
					}
					else if (name == z.getName())
					{
						vecRef.set(glm::vec4(x, y, z, w));
					}
					else if (name == w.getName())
					{
						vecRef.set(glm::vec4(x, y, z, w));
					}
				}
				else if (bNormalized && !bSigned) {
					if (name == x.getName())
					{
						vecRef.set(glm::vec4(
							ofMap(x, 0, 1, vecRef.getMin().x, vecRef.getMax().x),
							ofMap(y, 0, 1, vecRef.getMin().y, vecRef.getMax().y),
							ofMap(z, 0, 1, vecRef.getMin().z, vecRef.getMax().z),
							ofMap(w, 0, 1, vecRef.getMin().w, vecRef.getMax().w)));
					}
					else if (name == y.getName())
					{
						vecRef.set(glm::vec4(x, y, z, w));
					}
					else if (name == z.getName())
					{
						vecRef.set(glm::vec4(x, y, z, w));
					}
					else if (name == w.getName())
					{
						vecRef.set(glm::vec4(x, y, z, w));
					}
				}
			}
		});

		ofLogNotice() << __FUNCTION__;
	};
};
*/

//--------------------------------------------------------------

class surfingGlmSplitter3
{
public:
	surfingGlmSplitter3() {};
	~surfingGlmSplitter3() {};

	bool bNamesShort = false;
	bool bNormalized = false; // 0, 1
	bool bSigned = false; // -1, 1

private:
	ofEventListener listenerParams;

public:
	ofParameter<float> x{ "x", 0, 0, 1 };
	ofParameter<float> y{ "y", 0, 0, 1 };
	ofParameter<float> z{ "z", 0, 0, 1 };

private:
	ofParameterGroup params{ "params" };

public:
	ofParameterGroup floats{ "Floats" };

	ofParameter<glm::vec3> vecRef{ "-1",glm::vec3(0.5),glm::vec3(0),glm::vec3(1) };

private:
	void set(ofParameter<glm::vec3> _v) {
		x.set(_v.get().x);
		y.set(_v.get().y);
		z.set(_v.get().z);

		// limits
		if (!bNormalized) {
			x.setMin(_v.getMin().x);
			y.setMin(_v.getMin().y);
			z.setMin(_v.getMin().z);
			x.setMax(_v.getMax().x);
			y.setMax(_v.getMax().y);
			z.setMax(_v.getMax().z);
		}
		else if (bNormalized && !bSigned) {
			x.setMin(0.f);
			y.setMin(0.f);
			z.setMin(0.f);
			x.setMax(1.0f);
			y.setMax(1.0f);
			z.setMax(1.0f);
		}
		else //if (bNormalized && bSigned) 
		{
			x.setMin(-1.f);
			y.setMin(-1.f);
			z.setMin(-1.f);
			x.setMax(1.0f);
			y.setMax(1.0f);
			z.setMax(1.0f);
		}
	}

public:
	void setup(ofParameter<glm::vec3> &_v) {
		vecRef.makeReferenceTo(_v);

		std::string n = _v.getName();
		x.setName(bNamesShort ? "x" : n + " x");
		y.setName(bNamesShort ? "y" : n + " y");
		z.setName(bNamesShort ? "z" : n + " z");

		set(_v);

		params.setName(n);
		params.add(vecRef);

		params.add(x);
		params.add(y);
		params.add(z);

		floats.setName(_v.getName());
		floats.add(x);
		floats.add(y);
		floats.add(z);

		setup();
	}

private:
	void setup() {

		listenerParams = params.parameterChangedE().newListener([&](ofAbstractParameter&p) {
			string name = p.getName();

			static bool bdisable = false;

			if (name == "-1")
			{
				return;
			}

			// Some coord of VEC changed:
			if (name == vecRef.getName()) {
				if (!bNormalized)
				{
					x.setWithoutEventNotifications(vecRef.get().x);
					y.setWithoutEventNotifications(vecRef.get().y);
					z.setWithoutEventNotifications(vecRef.get().z);
				}
				else if (bNormalized && !bSigned)
				{
					x.setWithoutEventNotifications(ofMap(vecRef.get().x, vecRef.getMin().x, vecRef.getMax().x, 0, 1));
					y.setWithoutEventNotifications(ofMap(vecRef.get().y, vecRef.getMin().y, vecRef.getMax().y, 0, 1));
					z.setWithoutEventNotifications(ofMap(vecRef.get().z, vecRef.getMin().z, vecRef.getMax().z, 0, 1));
				}
				else //if (bNormalized && bSigned)
				{
					x.setWithoutEventNotifications(ofMap(vecRef.get().x, vecRef.getMin().x, vecRef.getMax().x, -1, 1));
					y.setWithoutEventNotifications(ofMap(vecRef.get().y, vecRef.getMin().y, vecRef.getMax().y, -1, 1));
					z.setWithoutEventNotifications(ofMap(vecRef.get().z, vecRef.getMin().z, vecRef.getMax().z, -1, 1));
				}

				x = x;
				y = y;
				z = z;
			}

			// Some splitted coord changed:
			else {
				if (p.type() == typeid(ofParameter<float>).name())
				{
					ofParameter<float> pm = p.cast<float>();
					ofLogNotice() << "glmSplitter : " << name << " : " << pm.get();
				}
				else { return; }

				if (!bNormalized)
				{
					if (name == x.getName())
					{
						vecRef.set(glm::vec3(x, y, z));
					}
					else if (name == y.getName())
					{
						vecRef.set(glm::vec3(x, y, z));
					}
					else if (name == z.getName())
					{
						vecRef.set(glm::vec3(x, y, z));
					}
				}
				else if (bNormalized && !bSigned)
				{
					if (name == x.getName())
					{
						vecRef.set(glm::vec3(
							ofMap(x, 0, 1, vecRef.getMin().x, vecRef.getMax().x),
							ofMap(y, 0, 1, vecRef.getMin().y, vecRef.getMax().y),
							ofMap(z, 0, 1, vecRef.getMin().z, vecRef.getMax().z)));
					}
					else if (name == y.getName())
					{
						vecRef.set(glm::vec3(
							ofMap(x, 0, 1, vecRef.getMin().x, vecRef.getMax().x),
							ofMap(y, 0, 1, vecRef.getMin().y, vecRef.getMax().y),
							ofMap(z, 0, 1, vecRef.getMin().z, vecRef.getMax().z)));
					}
					else if (name == z.getName())
					{
						vecRef.set(glm::vec3(
							ofMap(x, 0, 1, vecRef.getMin().x, vecRef.getMax().x),
							ofMap(y, 0, 1, vecRef.getMin().y, vecRef.getMax().y),
							ofMap(z, 0, 1, vecRef.getMin().z, vecRef.getMax().z)));
					}
				}
				else //if (bNormalized && bSigned) 
				{
					if (name == x.getName())
					{
						vecRef.set(glm::vec3(
							ofMap(x, -1, 1, vecRef.getMin().x, vecRef.getMax().x),
							ofMap(y, -1, 1, vecRef.getMin().y, vecRef.getMax().y),
							ofMap(z, -1, 1, vecRef.getMin().z, vecRef.getMax().z)));
					}
					else if (name == y.getName())
					{
						vecRef.set(glm::vec3(
							ofMap(x, -1, 1, vecRef.getMin().x, vecRef.getMax().x),
							ofMap(y, -1, 1, vecRef.getMin().y, vecRef.getMax().y),
							ofMap(z, -1, 1, vecRef.getMin().z, vecRef.getMax().z)));
					}
					else if (name == z.getName())
					{
						vecRef.set(glm::vec3(
							ofMap(x, -1, 1, vecRef.getMin().x, vecRef.getMax().x),
							ofMap(y, -1, 1, vecRef.getMin().y, vecRef.getMax().y),
							ofMap(z, -1, 1, vecRef.getMin().z, vecRef.getMax().z)));
					}
				}
			}
		});

		ofLogNotice() << __FUNCTION__;
	};
};

//--------------------------------------------------------------

/*
class surfingGlmSplitter2
{
public:
	surfingGlmSplitter2() {};
	~surfingGlmSplitter2() {};

private:
	ofEventListener listenerParams;

public:
	ofParameter<float> x{ "x", 0, 0, 1 };
	ofParameter<float> y{ "y", 0, 0, 1 };

private:
	ofParameterGroup params{ "params" };

public:
	ofParameterGroup floats{ "Floats" };

	ofParameter<glm::vec2> vecRef{ "-1",glm::vec2(0.5),glm::vec2(0),glm::vec2(1) };

private:
	void set(ofParameter<glm::vec2> _v) {
		x.set(_v.get().x);
		y.set(_v.get().y);

		// limits
		x.setMin(_v.getMin().x);
		y.setMin(_v.getMin().y);
		x.setMax(_v.getMax().x);
		y.setMax(_v.getMax().y);
	}

public:
	void setup(ofParameter<glm::vec2> &_v) {
		vecRef.makeReferenceTo(_v);

		std::string n = _v.getName();
		x.setName(n + " x");
		y.setName(n + " y");

		set(_v);

		params.setName(n);
		params.add(vecRef);

		params.add(x);
		params.add(y);

		floats.setName(_v.getName());
		floats.add(x);
		floats.add(y);

		setup();
	}

private:
	void setup() {

		listenerParams = params.parameterChangedE().newListener([&](ofAbstractParameter&p) {
			string name = p.getName();

			static bool bdisable = false;

			if (name == "-1")
			{
				return;
			}

			if (name == vecRef.getName()) {
				x.setWithoutEventNotifications(vecRef.get().x);
				y.setWithoutEventNotifications(vecRef.get().y);

				x = x;
				y = y;
			}

			else {
				if (p.type() == typeid(ofParameter<float>).name())
				{
					ofParameter<float> pm = p.cast<float>();
					ofLogNotice() << "glmSplitter : " << name << " : " << pm.get();
				}
				else { return; }

				// get the values doing casting. we check the type first
				if (name == x.getName())
				{
					vecRef.set(glm::vec2(x, y));
				}
				else if (name == y.getName())
				{
					vecRef.set(glm::vec2(x, y));
				}
			}
		});

		ofLogNotice() << __FUNCTION__;
	};
};
*/