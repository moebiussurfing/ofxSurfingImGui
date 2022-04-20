#pragma once

#include "ofMain.h"

/*

	Converts a float ofParam to a normalized one.
	Both will be linked

*/


//--------------------------------------------------------------


class surfingParamNorm
{
public:
	surfingParamNorm() {};
	~surfingParamNorm() {};

	bool bSigned = false;

private:
	ofEventListener listenerParams;

	ofParameterGroup params{ "params" };

public:
	ofParameter<float> pNorm{ "-1", 0, 0, 1 };

private:
	ofParameter<float> pRef{ "-1", 0, 0, 1 };

private:
	void set(ofParameter<float> _v)
	{
		// value
		//pRef.set(_v.get());

		// limits
		if (!bSigned)
		{
			pNorm.setMin(0.f);
			pNorm.setMax(1.0f);
		}
		else
		{
			pNorm.setMin(-1.f);
			pNorm.setMax(1.0f);
		}
	}

public:
	void setup(ofParameter<float> &_v)
	{
		pRef.makeReferenceTo(_v);

		std::string n = _v.getName() + " N";
		pNorm.setName(n);

		set(_v);

		params.clear();
		params.add(pRef);
		params.add(pNorm);

		setup();
	}

private:
	void setup()
	{
		listenerParams = params.parameterChangedE().newListener([&](ofAbstractParameter&p)
		{
			std::string name = p.getName();

			if (name == "-1") // Non initialized
			{
				return;
			}

			else if (name == pNorm.getName())
			{
				if (!bSigned)
				{
					pRef.set(ofMap(pNorm.get(), 0, 1, pRef.getMin(), pRef.getMax(), true));
				}
				else
				{
					pRef.set(ofMap(pNorm.get(), -1, 1, pRef.getMin(), pRef.getMax(), true));
				}
			}

			else if (name == pRef.getName())
			{
				if (!bSigned)
				{
					pNorm.set(ofMap(pRef.get(), pRef.getMin(), pRef.getMax(), 0, 1, true));
				}
				else
				{
					pNorm.set(ofMap(pRef.get(), pRef.getMin(), pRef.getMax(), -1, 1, true));
				}
			}
		});

		pNorm = pNorm;

		ofLogNotice() << __FUNCTION__;
	};
};

//--

/*

	SNIPPET:

	Renders an ImGui widget float ofParam but normalized to 0-1.

	// Distance
	{
		float _v = cameraPresetTo.camDistance.get();
		float _Min = MIN_CAMERA_DISTANCE;
		float _Max = 2 * R_DISTANCE * MAX_CAMERA_DISTANCE;
		static float _vn;
		_vn = ofMap(_v, _Min, _Max, -1.f, 1.f, true);
		if (ImGui::SliderFloat("Dist", &_vn, -1.f, 1.f))
		{
			float vv = ofMap(_vn, -1.f, 1.f, _Min, _Max, true);
			cameraPresetTo.camDistance.set(vv);
		}
	}

*/
