#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	// add to custom tags to log system
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
	if (!bGui) return;
	// Not mandatory, but
	// this will allow to hide the Log Window too. 
	// That's bc is auto drawn when calling ui.End()!

	ui.Begin();
	{
		// Close the Window by pressing the top right X.
		// This state is handled internally by bGui bool param!
		// Press space to toggle bGui and show it again.

		if (ui.BeginWindow(bGui))
		{
			string s = "HELP\n\n";
			s += "Enable the Log Window using the above rounded toggle.\n\n";
			s += "Drag the mouse and click left or right button outside or inside the UI, ";
			s += "move speed slider... \n\nThen go look into the Log Window!";
			s += "\n\nPress SPACE to show/hide the UI.";

			ui.AddLogToggle(); // populate a toggle for the internal show log param.
			ui.AddMinimizerToggle(); // populate a toggle for the internal minimized param.

			//if (!ui.isMinimized()) 
			if (ui.isMaximized()) // does the same than the above line
			{
				ui.AddKeysToggle(); // populate a toggle for the internal keys enabler param.
				string s2 = "Keys Enabler will allow some \ninternal key commands.\n";
				s2 += "Press ` to toggle the Minimizer state.\n";
				s2 += "Press L to toggle the Log Window visible.";
				ui.AddTooltip(s2); // a tooltip will be pinned to the previous widget!
			}

			ui.AddSpacingBigSeparated();

			// two different presentations depending if minimized or not
			if (ui.isMinimized()) // minimized
			{
				ui.Add(speed, OFX_IM_HSLIDER_SMALL_NO_LABELS); // smaller with no name and no value number
				ui.AddTooltip(speed, true, false); // tool-tip with name and value
				ui.AddSpacingDouble();
				ui.AddTooltipHelp(s);
			}
			else // not minimized aka maximized
			{
				ui.AddLabelBig("Hello World 2", true, true); // make it uppercase and add an extra space

				ui.AddSpacingDouble();
				ui.BeginBlinkText();
				ui.AddLabel(s);
				ui.EndBlinkText();

				ui.AddSpacingBigSeparated();
				ui.Add(speed, OFX_IM_HSLIDER);
				ui.Add(bEnable, OFX_IM_TOGGLE_BIG_BORDER_BLINK); // blinks when true
				if (bEnable)
				{
					ui.AddSpacing();
					ui.AddSpacingSeparated();

					// A right aligned extra minimizer
					// but using a local bool param.
					// not that is not stored into settings file,
					// but other internal toggles it does!
					static ofParameter<bool> bMin{ "", true };
					ui.AddMinimizerXsToggle(bMin);
					if (!bMin)
					{
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
	if (key == 'f') ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (ui.isMouseOverGui()) return; // don't log if we are touching the ui

	string sb = "";
	if (button == 0) sb = "LEFT";
	else if (button == 2) sb = "RIGHT";
	string s = "Mouse Click " + ofToString(x) + "," + ofToString(y) + " " + sb;

	ui.AddToLog(s, myTag2);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	if (ui.isMouseOverGui()) return; // don't log if we are touching the ui

	string s = "Mouse Drag  " + ofToString(x) + "," + ofToString(y);

	ui.AddToLog(s, "VERBOSE");
}

//--------------------------------------------------------------
void ofApp::exit()
{
}