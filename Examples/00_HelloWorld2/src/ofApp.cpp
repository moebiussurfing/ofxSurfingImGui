#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ui.AddLogTag(myTag1, ofColor::yellow);
	ui.AddLogTag(myTag2, ofColor::orange);

	// callback to log
	listener = speed.newListener([this](float& v) {
		ofLogNotice() << v;

	string s = speed.getName() + ": " + ofToString(speed.get(), 1);
	ui.AddToLog(s, myTag1);
		});

}

//--------------------------------------------------------------
void ofApp::update()
{
	if (ofGetFrameNum() % 60 == 0) {
		static int count = 0;
		string s = "COUNT " + ofToString(++count);
		ui.AddToLog(s, "NOTICE");
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ui.Begin();
	{
		if (ui.BeginWindow(bGui))
		{
			// A right aligned extra minimizer
			static ofParameter<bool> bMin{ "", false };
			ui.AddMinimizerXsToggle(bMin);
			if (!bMin)
			{
				ui.AddLogToggle(); // populate a toggle for the internal show log param.
				ui.AddMinimizerToggle(); // populate a toggle for the internal minimized param.

				// two different presentations depending if minimized or not
				if (ui.isMinimized()) // minimized
				{
					ui.Add(speed, OFX_IM_HSLIDER_SMALL_NO_LABELS); // smaller with no name and no value number
					ui.AddTooltip(speed, true, false); // tool-tip with name and value
				}
				else // not minimized aka maximized
				{
					ui.AddLabelBig("Hello World 2", true, true); // make uppercase and an extra space

					ui.Add(speed, OFX_IM_HSLIDER_BIG);
					ui.Add(bEnable, OFX_IM_TOGGLE_BIG_BORDER_BLINK); // blink when true

					if (bEnable)
					{
						ui.AddSpacingSeparated();
						ui.AddGroup(params, SurfingGuiGroupStyle_Collapsed); // collapsed on startup
					}
				}
			}

			ui.EndWindow();
		}
	}
	ui.End();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	ui.AddToLog("KEY: " + ofToString(char(key)), "WARNING");

	if (key == ' ') bGui = !bGui;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	string sb = "";
	if (button == 0) sb = "LEFT";
	else if (button == 2) sb = "RIGHT";
	string s = "Mouse Click " + ofToString(x) + "," + ofToString(y) + " " + sb;

	ui.AddToLog(s, myTag2);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	string s = "Mouse Drag  " + ofToString(x) + "," + ofToString(y);

	ui.AddToLog(s, "VERBOSE");
}