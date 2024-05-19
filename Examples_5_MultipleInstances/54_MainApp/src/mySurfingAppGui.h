#pragma once
#include "ofMain.h"

class SurfingGuiManager;
// Forward declaring
// as it creates issues 
// to include ofxSurfingImGui.h in the h files.

class ofApp;

// An extra class
#include "myClassA.h"

namespace mySurfingApp
{
	class Gui
	{
	public:
		Gui(ofApp*);
		virtual ~Gui();

		unique_ptr<SurfingGuiManager> ui = nullptr;

		void setup();

	private:
		void setupImGui();

	public:
		bool isMouseOverGui();
		bool isMouseOverInputText();

		void draw();

		ofParameter<bool> bGui{ "mySurfingApp", true };

		ofParameter<bool> bGuiCameras{ "Cameras", true };
		ofParameter<bool> bGuiData{ "Data", false };
		ofParameter<bool> bGuiOutput{ "Output", true };
		ofParameter<bool> bGuiSync{ "Sync", true };
		ofParameter<bool> bGuiTrackerData{ "Tracker Data", true };
		ofParameter<bool> bGuiTrackerInputs{ "Tracker Inputs", true };
		ofParameter<bool> bGuiSettings{ "Settings", false };

	private:
		ofApp* mainApp = nullptr;

	private:
		myClassA A;
	};
}
