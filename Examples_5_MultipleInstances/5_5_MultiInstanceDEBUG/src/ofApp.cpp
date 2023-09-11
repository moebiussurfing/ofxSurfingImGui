#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	params.setName("paramsGroup");
	params2.setName("paramsGroup2");
	params3.setName("paramsGroup3");
	params.add(bPrevious.set("<", false));
	params.add(bNext.set(">", false));
	params.add(bEnable1.set("Enable1", false));
	params.add(bEnable2.set("Enable2", false));
	params.add(bEnable3.set("Enable3", false));
	params.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params.add(separation.set("separation", 50, 1, 100));
	params.add(speed.set("speed", 0.5, 0, 1));
	params.add(shapeType.set("shapeType", 0, -50, 50));
	params.add(size.set("size", 100, 0, 100));
	params.add(amount.set("amount", 10, 0, 25));
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));
	params3.add(shapeType3.set("shapeType3", 0, -50, 50));
	params2.add(params3);
	params.add(params2);

	//--

	ui_.setup();

	for (size_t i = 0; i < NUM_INSTANCES; i++)
	{
#if 1
		string s = "Instance_" + ofToString(i);
		ui[i].setName(s);
#endif

		ui[i].setup();

		//force
		//ui[i].bGui = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return;

	// Show toggles
	ui_.Begin();
	{
		if (ui_.BeginWindow("ofApp"))
		{
			for (size_t i = 0; i < NUM_INSTANCES; i++)
			{
				ui_.Add(ui[i].bGui, OFX_IM_TOGGLE_ROUNDED);
			}

			ui_.EndWindow();
		}

		// Debug
		{
			static bool m_Debug = false;
			static bool m_Demo = false;
			ImGui::Checkbox("Debug", &m_Debug);
			ImGui::Checkbox("Demo", &m_Demo);
			if (m_Debug) ImGui::ShowMetricsWindow(&m_Debug);
			if (m_Demo) ImGui::ShowDemoWindow(&m_Demo);
		}
	}
	ui_.End();

	// Instances window
	for (size_t i = 0; i < NUM_INSTANCES; i++)
	{
		ui[i].Begin();
		{
			if (ui[i].BeginWindow(ui[i].bGui))
			{
				ui_.Add(ui[i].bAutoResize, OFX_IM_TOGGLE_ROUNDED_MINI);
				ui_.Add(ui[i].bMinimize, OFX_IM_TOGGLE_ROUNDED_MINI);
				ui_.AddSpacingSeparated();

				switch (i)
				{
				case 0: ui[i].AddGroup(params); break;
				case 1: ui[i].Add(size2, OFX_IM_HSLIDER); break;
				case 2: ui[i].Add(amount); break;
				case 3: ui[i].Add(shapeType2, OFX_IM_HSLIDER_BIG); break;
				case 4: ui[i].Add(shapeType3, OFX_IM_HSLIDER_MINI_NO_NAME); break;
				case 5: ui[i].Add(size, OFX_IM_VSLIDER); break;
				case 6: ui[i].Add(shapeType, OFX_IM_STEPPER); break;
				}
				ui[i].EndWindow();
			}
		}
		ui[i].End();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') bGui = !bGui;
}