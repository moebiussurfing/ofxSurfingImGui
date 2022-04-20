
#pragma once

#include "ofMain.h"

#include "ofxSurfingHelpers.h"
#include "ofxInteractiveRect.h"
#include "DoubleClicker.h"
//#include "TextBoxWidget.h"

/*

	TODO:

	+ use ctrl modifier bc thre clicks interferes with double..
	+ add store layout settings
	+ move layout to drag rect class
	+ sum padding from 0, not expanded from center..

*/


/*

This class draws a draggable text box with colored background.
Auto stores and recall the box position between the app sessions.
Doubleclick the box to allow move the position.

Usage Example Snippet:

	// .h
	#include "TextBoxWidget.h"
	TextBoxWidget textBoxWidget;

	// Setup
	{
		// font
		textBoxWidget.setFontName("overpass-mono-bold.otf");
		textBoxWidget.setFontSize(20);

		//textBoxWidget.setFixedHeight(1); //TODO:

		textBoxWidget.setup();
		
		//textBoxWidget.setMode(TextBoxWidget::FREE_LAYOUT);
		textBoxWidget.setMode(TextBoxWidget::BOTTOM_CENTER);
		
		// theme
		textBoxWidget.setTheme(true);//dark
		//textBoxWidget.setTheme(false);//light

		// text
		std::string helpInfo = "";
		helpInfo += "HELP\n";
		helpInfo += "KEY COMMANDS\n";
		helpInfo += "\n";
		helpInfo += "SPACE      : Randomize Parameters\n";
		//helpInfo = ofToUpper(helpInfo); // make uppercase
		
		textBoxWidget.setText(helpInfo);
	}

	// Draw
	{
		textBoxWidget.draw();
	}

*/

//#define LOCK_EDIT_ON_NON_FREE_LAYOUT_MODE

class TextBoxWidget : public ofBaseApp
{

public:

	//--------------------------------------------------------------
	TextBoxWidget()
	{
		// Default

		size_TTF = 10;
		name_TTF = "telegrama_render.otf";

		//size_TTF = 11;
		//name_TTF = "telegrama_render.otf";

		//size_TTF = 10;
		//name_TTF = "overpass-mono-bold.otf";
	}

	//--------------------------------------------------------------
	~TextBoxWidget()
	{
	}

	//-

public:

	enum BOX_LAYOUT
	{
		FREE_LAYOUT = 0,
		BOTTOM_CENTER,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		TOP_CENTER,
		TOP_LEFT,
		TOP_RIGHT,
		CENTER,
		NUM_LAYOUTS
	};

private:

	DoubleClicker doubleClicker;

	BOX_LAYOUT modeLayout = FREE_LAYOUT;
	string str_modeLayout = "";

public:

	//--------------------------------------------------------------
	string getEditing() {
		if (rect_HelpTextBox.isEditing()) return "Editing"; else return "Not Editing";
	}

	//--------------------------------------------------------------
	string getTheme() {
		if (bThemeDarkOrLight) return "Dark"; else return "Light";
	}

	//--------------------------------------------------------------
	string getTextMode() {
		if (bNoText) return "No Text"; else return "Text";
	}

	//--------------------------------------------------------------
	string getMode() {
		str_modeLayout = "UNKNOWN";
		switch (modeLayout)
		{
		case 0: str_modeLayout = "FREE_LAYOUT"; break;
		case 1: str_modeLayout = "BOTTOM_CENTER"; break;
		case 2: str_modeLayout = "BOTTOM_LEFT"; break;
		case 3: str_modeLayout = "BOTTOM_RIGHT"; break;
		case 4: str_modeLayout = "TOP_CENTER"; break;
		case 5: str_modeLayout = "TOP_LEFT"; break;
		case 6: str_modeLayout = "TOP_RIGHT"; break;
		case 7: str_modeLayout = "CENTER"; break;
		default: str_modeLayout = "UNKNOWN LAYOUT"; break;
		}
		return str_modeLayout;
	}

private:

	ofxInteractiveRect rect_HelpTextBox = { "Help_ofxPresetsManager" };
	std::string path_RectHelpBox = "_HelpBox";
	std::string path_Global = "TextBoxWidget/";// can be setted before setup
	std::string path_Name = "appSettings";// subfolder for app session settings

	// font to label clicker boxes
	ofTrueTypeFont myFont;
	std::string path_TTF;
	std::string name_TTF;
	int size_TTF;

	std::string textInfo = "empty content";// info text to display shortcuts or path settings

	ofColor _colorText;// lines and text color
	ofColor _colorButton;// bg selected button
	ofColor _colorBg;// background color
	ofColor _colorShadow;
	bool _bUseShadow;

	bool bCenter = true;
	bool bLeftPosition = false;
	bool bThemeDarkOrLight = true;

	bool bState1 = false;
	bool bState2 = false;

	float round = 5;
	int marginBorders = 50;

	bool bNoText = false;

public:

	//ofParameter<glm::vec2> shape{ "Shape", glm::vec2(1920 / 2, 1080 / 2), glm::vec2(0,0), glm::vec2(19200,1080) };
	//--------------------------------------------------------------
	void setTextMode(bool b) {
		bNoText = !b;
		rect_HelpTextBox.setLockResize(b);
	}
	//--------------------------------------------------------------
	void setNoTextMode(bool b) {
		bNoText = b;
		rect_HelpTextBox.setLockResize(!b);
	}
	//--------------------------------------------------------------
	void setToggleNoTextMode() {
		bNoText = !bNoText;
		rect_HelpTextBox.setLockResize(!bNoText);
	}
	//--------------------------------------------------------------
	void setShape(ofRectangle shape) {
		rect_HelpTextBox.setRect(shape.x, shape.y, shape.getWidth(), shape.getHeight());
	}

public:

	//--------------------------------------------------------------
	void setPath(string path) {
		path_Global = path;
	}

	//--------------------------------------------------------------
	void setFontSize(int size = 10) {
		size_TTF = size;
	}
	//--------------------------------------------------------------
	void setFontName(string name = "telegrama_render.otf") {
		name_TTF = name;
	}

	//--------------------------------------------------------------
	void setup() {

		path_TTF = "assets/fonts/" + name_TTF;
		bool bLoaded = myFont.load(path_TTF, size_TTF, true, true);
		if (!bLoaded) bLoaded = myFont.load(OF_TTF_SANS, size_TTF, true, true);

		_bUseShadow = true;

		setTheme(bThemeDarkOrLight);

		doubleClicker.set(0, 0, ofGetWidth(), ofGetHeight());// default full screen
		doubleClicker.setDebug(false);

		// Default position
		rect_HelpTextBox.setPosition(ofGetWidth() / 2, ofGetHeight() / 2);

		//----

		ofxSurfingHelpers::CheckFolder(path_Global + "/" + path_Name + "/");

		// Load settings
		rect_HelpTextBox.loadSettings(path_RectHelpBox, path_Global + "/" + path_Name + "/", false);

		// We dont need draggable borders and decoration.
		rect_HelpTextBox.setLockResize(true);
		//rect_HelpTextBox.setLockResize(!bNoText);
		rect_HelpTextBox.setTransparent();
	}

	//--------------------------------------------------------------
	void draw() {
		ofPushStyle();

		drawDoubleClickDebug();

		//-

		std::string ss = textInfo;

		float _w = ofGetWidth();
		float _h = ofGetHeight();

		int _padx = 10;
		int _pady = 10;

		int _xx;
		int _yy;

		float _ww;
		float _hh;

		if (bNoText)
		{
			_ww = rect_HelpTextBox.getWidth();
			_hh = rect_HelpTextBox.getHeight();
		}
		else
		{
			_ww = ofxSurfingHelpers::getWidthBBtextBoxed(myFont, ss);
			_hh = ofxSurfingHelpers::getHeightBBtextBoxed(myFont, ss);

			//if(!bFixedHeight) _hh = ofxSurfingHelpers::getHeightBBtextBoxed(myFont, ss);
			//else {
			//	std::string _ss = "";
			//	for (int i = 0; i <numLines; i++) _ss += "I \n";
			//	_hh = ofxSurfingHelpers::getHeightBBtextBoxed(myFont, _ss);
			//}

			rect_HelpTextBox.setHeight(_hh);
			rect_HelpTextBox.setWidth(_ww);
		}

		//-

		if (modeLayout == FREE_LAYOUT) {

			_xx = rect_HelpTextBox.getX();
			_yy = rect_HelpTextBox.getY();
		}

		else if (modeLayout == BOTTOM_CENTER) {

			_xx = _w / 2 - _ww / 2 - _padx;
			_yy = _h - _hh - _pady;
		}
		else if (modeLayout == BOTTOM_LEFT) {

			_xx = _padx;
			_yy = _h - _hh - _pady;
		}
		else if (modeLayout == BOTTOM_RIGHT) {

			_xx = _w - _ww - _padx;
			_yy = _h - _hh - _pady;
		}

		else if (modeLayout == TOP_CENTER) {

			_xx = _w / 2 - _ww / 2 - _padx;
			_yy = _pady;
		}
		else if (modeLayout == TOP_LEFT) {

			_xx = _padx;
			_yy = _pady;
		}
		else if (modeLayout == TOP_RIGHT) {

			_xx = _w - _ww - _padx;
			_yy = _pady;
		}

		else if (modeLayout == CENTER) {

			_xx = _w / 2 - _ww / 2 - _padx;
			_yy = _h / 2 - _hh / 2 - _pady;
		}

		//-

		ofColor colorBg;

		if (modeLayout == FREE_LAYOUT)
		{
			//_colorText, colorBg, _bUseShadow, _colorButton

			if (rect_HelpTextBox.isEditing())
			{
				float a = ofxSurfingHelpers::getFadeBlink();
				ofColor c = ofColor(_colorBg, 255 * a);
				rect_HelpTextBox.draw();

				colorBg = c;
			}
			else
			{
				colorBg = _colorBg;
			}
		}
		else
		{
			colorBg = _colorBg;
		}

		//-

		if (!bNoText)
		{
			int h = (bFixedHeight ? hLocked : -1); // Unlocked to resize related to text size

			ofxSurfingHelpers::drawTextBoxed(myFont, ss, _xx, _yy, _colorText, colorBg, _bUseShadow, _colorButton, marginBorders, round, h);
		}

		ofPopStyle();

		//-

		// Force fit box iniside the window
		{
			float _xmax = _w - _ww - _padx;
			float _ymax = _h - _hh - _pady;
			float _ymin = 3 * _pady;

			if (rect_HelpTextBox.getY() > _ymax)//bottom
			{
				rect_HelpTextBox.setY(_ymax);
			}
			else if (rect_HelpTextBox.getX() < _padx)//left
			{
				rect_HelpTextBox.setX(_padx);
			}
			else if (rect_HelpTextBox.getX() > _xmax)//right
			{
				rect_HelpTextBox.setX(_xmax);
			}
			else if (rect_HelpTextBox.getY() < _ymin)//top
			{
				rect_HelpTextBox.setY(_ymin);
			}
		}

		doubleClicker.set(_xx, _yy, _ww, _hh);
	}

	//-

private:

	//--------------------------------------------------------------
	void drawDoubleClickDebug()
	{
		//--

		// 1. Double click swap edit mode

		//-

		// Allow edit onlly on free layout mode:
#ifdef LOCK_EDIT_ON_NON_FREE_LAYOUT_MODE
		if (modeLayout == FREE_LAYOUT)
#endif
			//-

		{
			if (doubleClicker.isMouseDoubleClick())
				//if (doubleClicker.isMouseTripleClick()) 
			{
				bState1 = !bState1;

				setEdit(bState1);

				// workflow
				if (bState1)
				{
					if (modeLayout != FREE_LAYOUT) modeLayout = FREE_LAYOUT;
				}
				//modeLayout = FREE_LAYOUT;
			}
		}

		//--

		// 2. Triple clicks swap modeLayout mode

		if (doubleClicker.isMouseTripleClick())
			//if (doubleClicker.isMouseDoubleClick())
		{
			bState2 = !bState2;

			int i = modeLayout;
			i++;
			if (i >= NUM_LAYOUTS) { modeLayout = FREE_LAYOUT; }
			else { modeLayout = BOX_LAYOUT(i); }
		}

		//--

		//// Debug colors to bg
		////if (bState2) ofClear(bState1 ? ofColor::blue : ofColor::yellow);
		////else ofClear(bState1 ? ofColor::black : ofColor::white);

		//bool bDebug = false;
		//if (!bDebug) return;

		////-

		//stringstream s;
		//s << "DoubleClick changes color." << endl;
		//s << "TripleClick changes RGB/Black&White." << endl;
		//s << "number Clicks: " << doubleClicker.clickCounter << endl;
		////NOTE:can't check these easycallbakcs twice on same frame
		////s << "doubleClicked: " << "[" << (obj.isMouseDoubleClick() ? "x" : " ") << "]" << endl;
		////s << "tripleClicked: " << "[" << (obj.isMouseTripleClick() ? "x" : " ") << "]" << endl;
		//s << endl;
		//s << "isMouseOver: " << doubleClicker.isMouseOver() << endl;
		//s << "isMousePressed(0): " << doubleClicker.isMousePressed(0) << endl;
		//s << "isMousePressed(1): " << doubleClicker.isMousePressed(1) << endl;
		//s << "isMousePressed(2): " << doubleClicker.isMousePressed(2) << endl;
		//s << "getStateChangeMillis(): " << doubleClicker.getStateChangeMillis();
		//ofDrawBitmapStringHighlight(s.str(), 10, 30);
	}

public:

	//--------------------------------------------------------------
	void setEdit(bool bEdit)
	{
		if (bEdit)
		{
			rect_HelpTextBox.enableEdit();
		}
		else
		{
			rect_HelpTextBox.disableEdit();

			// All app settings
			//save_ControlSettings();
			rect_HelpTextBox.saveSettings(path_RectHelpBox, path_Global + "/" + path_Name + "/", false);
		}
	}

	//--------------------------------------------------------------
	void setTheme(bool bTheme) {
		bThemeDarkOrLight = bTheme;

		// Light theme (false = light)
		if (!bThemeDarkOrLight)
		{
			_colorText = ofColor(0, 255);
			_colorButton = ofColor(255, 64);
			_colorBg = ofColor(225, 64);
		}
		// Dark theme (white lines & black bg) (true = dark)
		else
		{
			_colorText = ofColor(255, 150);
			_colorButton = ofColor(16, 225);
			_colorBg = ofColor(0, 128);
		}
	}

	//--------------------------------------------------------------
	void setToggleTheme() {
		bThemeDarkOrLight = !bThemeDarkOrLight;
	}

	//--------------------------------------------------------------
	void setToggleMode() {
		int i = BOX_LAYOUT(modeLayout);
		i++;
		i = i % NUM_LAYOUTS;
		modeLayout = BOX_LAYOUT(i);
	}

	//--------------------------------------------------------------
	void setMode(BOX_LAYOUT mode) {
		modeLayout = mode;
	}

public:

	//--------------------------------------------------------------
	void setText(string text) {
		textInfo = text;
	}

	//--

//	//TODO:
//	// Should be added to the ofxSurfingHelpers::drawTextBoxed, adding a bool flag to force height..
//	// A workaround to lock the box height to the amount of lines using a 'I' char, 
//	// then it will not depends to the chars of the text. 
//	// An using case could be an only oneline text and his box height will no being different depending on used chars..

private:
	bool bFixedHeight = false;
	float hLocked = -1;
	int numLines = -1;

public:
	//--------------------------------------------------------------
	void setFixedHeight(int _numLines = 1) { // an small tweak to fix box size to an amount of lines
		bFixedHeight = true;
		numLines = _numLines;

		std::string _ss = "";
		for (int i = 0; i < numLines; i++) { _ss += "I" + (i == 0 && i < numLines - 1) ? "" : "\n"; }
		//std::string _ss = "I";
		hLocked = ofxSurfingHelpers::getHeightBBtextBoxed(myFont, _ss);
	}

};

//--