#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofxImGuiSurfing::SurfSetMyMonitor(0);//optional. just to set window position 

	ui.setup();

	T_CPU_SETUP(4);
	T_GPU_SETUP(3);
}

//--------------------------------------------------------------
void ofApp::update()
{
	{
		float v = ofMap(ofGetFrameRate(), 0, 60, 0, 1, true);
		string s = ofToString(ofGetFrameRate(), 0) + " fps";
		s += "    ";
		string ss = "";
		size_t a = 10;
		for (size_t i = 0; i < 10; i++)
		{
			if (i == (size_t)(v * a) - 0) ss += "|";
			else ss += "-";
		}
		s += ss;
		ofSetWindowTitle(s);
	}

	//--

	// Test 
	// slowing down frame rate
	T_CPU_START(0, "STRESS_CPU");
	if (bStressCpu)
	{
		int maxDelay = 40;
		int t = maxDelay;
		power = 0;

		if (bNoise)
		{
			float m;
			float th = 0.5;
			float n = ofNoise(ofGetElapsedTimef(), ofGetElapsedTimef());
			//ofLogNotice() << "noise:" << n;
			if (n > th)
			{
				power = ofMap(n, th, 1, 0, 1, true);
				m = ofMap(n, th, 1, 0, maxDelay, true);
				m += (maxDelay / 2);
				m += power * (maxDelay / 2);
				//m = power * m;

			}
			else  m = maxDelay / 2;
			t = m;
		}

		if (b0) ofSleepMillis(t);
	}
	T_CPU_END(0);

	int t1 = 10;
	T_CPU_START(1, "DO-A");
	if (b1) {
		t1 = ofRandom(2, 10);
		ofSleepMillis(t1);
	}
	T_CPU_END(1);

	T_CPU_START(2, "DO-B");
	if (b2) {
		int t2 = t1 / 2;
		ofSleepMillis(t2);
	}
	T_CPU_END(2);


	T_CPU_START(3, "EXTRA");
	{
		float c = glm::sin(ofGetFrameNum() / 60);
		int s = (int)ofMap(c, -1, 1, 1, 8, true);
		ofSleepMillis(s);
	}
	T_CPU_END(3);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	T_GPU_START(0, "STRESS_GPU");
	ofBackgroundGradient(0, 50, OF_GRADIENT_CIRCULAR);
	if (bStressGpu)
	{
		size_t amt = 10000;
		float r = 20;
		ofPushStyle();
		ofSetCircleResolution(200);
		ofFill();
		ofColor c = ofColor(50, 50);
		ofSetColor(c);
		for (size_t i = 0; i < amt; i++)
		{
			auto p = glm::vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
			ofDrawCircle(p, r);
		}
		ofPopStyle();
	}
	T_GPU_END(0);

	T_GPU_START(1, "SLEEP");
	int t1 = ofRandom(2, 10);
	if (b3) ofSleepMillis(t1);
	T_GPU_END(1);

	drawGui();
}

//--------------------------------------------------------------
void ofApp::drawGui()
{
	if (b4) T_GPU_START(2, "IMGUI");
	ui.Begin();
	{
		if (ui.BeginWindow("ofApp")) {
			ui.Add(ui.bDebugDebugger, OFX_IM_TOGGLE);
			ui.AddSpacingBigSeparated();

			ui.Add(bStressGpu, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			ui.AddSpacing();

			ui.Add(bStressCpu, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
			if (bStressCpu) {
				ui.Add(bNoise);
				ui.Add(power, OFX_IM_PROGRESS_BAR_NO_TEXT);
			}
			ui.AddSpacingSeparated();

			static bool b = false;
			ui.AddToggle("Expand", b);
			if (b) {
				ui.AddLabel("Enable Sections");
				if (ui.AddButton("All", OFX_IM_BUTTON, 2))
				{
					b0 = b1 = b2 = b3 = b4 = 1;
				}
				ui.SameLine();
				if (ui.AddButton("None", OFX_IM_BUTTON, 2))
				{
					b0 = b1 = b2 = b3 = b4 = 0;
				}
				ui.Add(b4, OFX_IM_TOGGLE);
				ui.Add(b3, OFX_IM_TOGGLE);
				ui.Add(b1, OFX_IM_TOGGLE);
				ui.Add(b2, OFX_IM_TOGGLE);
				ui.Add(b0, OFX_IM_TOGGLE);
			}

			ui.EndWindow();
		}
	}
	ui.End();
	if (b4) T_GPU_END(2);

	//TODO:
	//workaround to not fix that we need to feed something.
	//if not, last values will be frozen.
	//we stop measurement, but still drawing the gui
	if (!b4) {
		T_GPU_START(2, "IMGUI");
		T_GPU_END(2);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == ' ') bStressCpu = !bStressCpu;
	if (key == OF_KEY_RETURN) bStressGpu = !bStressGpu;
}