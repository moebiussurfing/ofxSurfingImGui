#include "ofApp.h"
#include "ofxSurfingImGui.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	parameters.setName("paramsGroup");
	parameters.add(bPrevious.set("<"));
	parameters.add(bNext.set(">"));
	parameters.add(bEnable1.set("Enable1", false));
	parameters.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	parameters.add(separation.set("separation", 50, 1, 100));
	parameters.add(size.set("size", 100, 0, 100));
	parameters.add(amount.set("amount", 10, 0, 25));

	//--

	gui = make_unique<mySurfingApp::Gui>(this);

	gui->setup();
}

//------------------------------------------------------------------------------------------
void ofApp::update()
{
	if (gui)
	{
		bool b = gui->isMouseOverGui();

		// Example
		// Enables mouse cam control only when mouse is not over gui.
		//if (b && camera.getMouseInputEnabled())
		//{
		//	camera.disableMouseInput();
		//}
		//else if (!b && !camera.getMouseInputEnabled())
		//{
		//	camera.enableMouseInput();
		//}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return; // this is the global show visible toggle

	if (gui) gui->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}
