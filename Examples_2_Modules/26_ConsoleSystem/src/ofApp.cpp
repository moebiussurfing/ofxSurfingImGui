#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::exit()
{
	delete data;
	data = NULL;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	//instantiate data
	data = new dataCustom();
	data->color = ofColor::fuchsia;
	data->lastCommand = "hello";
	data->frameNum = -1;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(data->color);

	//update a var of the data
	data->frameNum = ofGetFrameNum();

	string title = ofToString(data->frameNum);
	ofSetWindowTitle(title);

	string s;

	ui.Begin();
	{
		// Theme
		static bool bTheme = false;
		static bool b = 0;
		if (bTheme) {
			bTheme = 0;
			if (!b) {
				b = 1;
				ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingBlue();
			}
		}

		if (bGui) {
			ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(250, 500), ImGuiCond_FirstUseEver);
		}

		if (ui.BeginWindow(bGui))
		{
			if (!b) {
				if (ui.AddButton("Theme")) {
					bTheme = true;
				}
				ui.AddSpacingSeparated();
			}

			ui.AddLabelBig("dataCustom");
			ui.AddLabel("frameNum:\n" + ofToString(data->frameNum));
			ui.AddLabel("lastCommand:\n" + ofToString(data->lastCommand));
			ui.AddLabel("color:\n" + ofToString(data->color));
			ui.AddSpacingSeparated();

			if (ui.AddButton("HELP")) {
				s = "[ HELP ]";
				addToLog(s);

				c.help_();
				data->lastCommand = "added help";
			}
			if (ui.AddButton("CLEAR")) {
				s = "[ CLEAR ]";
				addToLog(s);

				c.clear_();
				data->lastCommand = "added clear";
			}
			ui.AddSpacingSeparated();

			ui.Add(c._terminalSizeLimit);
			ui.Add(c._maxHistoryLines);
			ui.AddSpacingSeparated();

			ui.AddLabelBig("Post Commands");
			ui.AddLabel("setColor");
			if (ui.AddButton("red", OFX_IM_BUTTON, 2, true)) {
				s = "setColor red";
				c.addLineCommnand(s, data);
			}
			if (ui.AddButton("blue", OFX_IM_BUTTON, 2)) {
				s = "setColor blue";
				c.addLineCommnand(s, data);
			}
			if (ui.AddButton("colorRandom", OFX_IM_BUTTON)) {
				s = "colorRandom";
				c.addLineCommnand(s, data);
			}

			ui.EndWindow();
		}

		//--

		c.show(data);
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	string s;
	if (key == '1') {
		s = "setColor red";
		c.addLineCommnand(s, data);
	}
	else if (key == '2') {
		s = "setColor blue";
		c.addLineCommnand(s, data);
	}
	else if (key == '3') {
		s = "colorRandom";
		c.addLineCommnand(s, data);
	}
	else if (key == '4') {
		c.help_();
		data->lastCommand = "added help";
	}
}

//--------------------------------------------------------------
void ofApp::addToLog(string s)
{
	//return;

	stringstream ss;
	ss << s;

	std::cout << ss.str() << endl;
	ofLog() << ss.str();
}