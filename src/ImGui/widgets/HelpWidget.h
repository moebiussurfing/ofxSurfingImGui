#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"

class HelpWidget
{
public:

	HelpWidget() {};
	~HelpWidget() {};

private:

	std::string text = "HelpWidget \nEmpty content"; // info text to display shortcuts or path settings

	std::string path_Global = "HelpWidget/"; // can be settled before setup

public:

	void setup() {
	}

	ofParameter<bool> bGui{ "HelpWidget", true };

	void setText(string _text) {
		ofLogVerbose("ofxSurfingImGui::HelpWidget") << "SetText:" << _text;

		text = _text;
	}

	// Call before setup. Will set path to save settings into.
	void setPath(string path) {
		path_Global = path;
	}
	// Call before setup. Will set the name of the settings file.
	// useful to customize the name when using many instances but on the same folder.
	// Notice that is not required when using a personalized path with setPath(
	void setName(string name) {
		bGui.setName(name);
	}

	void draw() {
		if (!bGui) return;

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration;
		bool* b = (bool*)bGui.get();

		ImGui::Begin(bGui.getName().c_str(), b, flags);

		ImGui::TextWrapped(text.c_str());

		ImGui::End();
	}
};