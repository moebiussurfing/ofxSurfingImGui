#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetWindowPosition(1920, 20);

	//guiManager.setImGuiAutodraw(true); // -> required when only one single ImGui instance is instantiated on all the oF project.
	//guiManager.setImGuiDockingModeCentered(false);
	//guiManager.setup();

	guiManager.setup(IM_GUI_MODE_INSTANTIATED);

	//-

	// ofParameters
	params1.setName("paramsGroup1");// main
	params1.add(bMode1.set("Mode1", false));
	params1.add(bMode2.set("Mode2", false));
	params1.add(bMode3.set("Mode3", false));
	params1.add(bMode4.set("Mode4", false));
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));

	//--

	guiManager.addWindowSpecial(bMode1);
	guiManager.addWindowSpecial(bMode2);

	guiManager.initiatieSpecialWindows();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		//-

		const auto viewport = ImGui::GetMainViewport();

		ImGuiDockNodeFlags vFlags = ImGuiDockNodeFlags_None;

		auto m_LastSize = viewport->Size;

		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		auto host_window_flags = 0;
		//host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
		//host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		//if (vFlags & ImGuiDockNodeFlags_PassthruCentralNode)
		//	host_window_flags |= ImGuiWindowFlags_NoBackground;

		ImGuiID m_DockSpaceID = 0;
		m_DockSpaceID = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(m_DockSpaceID, ImVec2(0.0f, 0.0f), vFlags);

		//--

		drawMainWindow();

		//--

		//// maximize window
		//float x = ofGetWindowPositionX();
		//float y = ofGetWindowPositionY();
		//float w = ofGetWindowWidth();
		//float h = ofGetWindowHeight();
		//ImVec4 vViewport(x, y, w, h);
		//ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
		//ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiCond_Once);

		if (!bInitiated)
		{
			bInitiated = true;
		}

		//-

		ImVec2 vSize(1000, 1000);
		ImGui::DockBuilderRemoveNode(m_DockSpaceID); // Clear out existing layout
		ImGui::DockBuilderAddNode(m_DockSpaceID, ImGuiDockNodeFlags_DockSpace); // Add empty node
		ImGui::DockBuilderSetNodeSize(m_DockSpaceID, vSize);

		const auto leftPaneDefaultWidth = 200.0f;
		const auto rightPaneDefaultWidth = 200.0f;
		const auto bottomPaneDefaultWidth = 200.0f;
		const auto topPaneDefaultWidth = 200.0f;

		auto dockMainID = m_DockSpaceID; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
		const auto dockLeftID = ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Left, leftPaneDefaultWidth / vSize.x, nullptr, &dockMainID);
		const auto dockRightID = ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Right, rightPaneDefaultWidth / vSize.x, nullptr, &dockMainID);
		const auto dockBottomID = ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Down, bottomPaneDefaultWidth / vSize.y, nullptr, &dockMainID);
		const auto dockTopID = ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Up, topPaneDefaultWidth / vSize.y, nullptr, &dockMainID);

		//-

		ImGui::DockBuilderDockWindow("Window0", dockLeftID);

		if (guiManager.beginWindow("Window0", NULL, ImGuiWindowFlags_None))
		{
			ImGui::Text("Test guiManager.beginWindow(0)");
			ImGui::SliderFloat(lineWidth.getName().c_str(),
				(float*)&lineWidth.get(), lineWidth.getMin(), lineWidth.getMax());
		}
		guiManager.endWindow();

		ImGui::DockBuilderFinish(dockLeftID);

		//-

		ImGui::DockBuilderDockWindow("Window1", dockRightID);

		if (guiManager.beginWindow("Window1", NULL, ImGuiWindowFlags_None))
		{
			ImGui::Text("Test guiManager.beginWindow(1)");
			static int _value = 0;
			ImGui::InputInt("InputInt", &_value);
			ImGui::SliderInt("SliderInt", &_value, 0, 10);
			ImGui::DragInt("DragInt", &_value);
		}
		guiManager.endWindow();

		ImGui::DockBuilderFinish(dockRightID);

		ImGui::DockBuilderFinish(m_DockSpaceID);

		//--

		// Using some helpers
		guiManager.drawSpecialWindowsPanels(); // -> Main Panels Controller

		if (guiManager.getSpecialWindowsEnableGlobal())
		{
			if (guiManager.beginWindowSpecial(0))
			{
				ImGui::Text("Test guiManager.beginWindow(0)");
				ImGui::SliderFloat(lineWidth.getName().c_str(),
					(float*)&lineWidth.get(), lineWidth.getMin(), lineWidth.getMax());
			}
			guiManager.endWindow();

			if (guiManager.getVisible(1)) {
				if (guiManager.beginWindowSpecial(1))
				{
					ImGui::Text("Test guiManager.beginWindow(1)");
					static int _value = 0;
					ImGui::InputInt("InputInt", &_value);
					ImGui::SliderInt("SliderInt", &_value, 0, 10);
					ImGui::DragInt("DragInt", &_value);
				}
				guiManager.endWindow();
			}
		}

		//-

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		guiManager.beginWindow("Window 1", &bOpen1, window_flags);
		{
			drawWidgets();
		}
		guiManager.endWindow();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofApp::drawMainWindow()
{
	ImGuiWindowFlags window_flags;
	window_flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	{
		ImGui::Begin("Show Windows", &bOpen0, window_flags);
		{
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);

			//ofxImGuiSurfing::ToggleRoundedButton(6&guiManager.getVisible(0).get());
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.getVisible(0));
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.getVisible(1));

			guiManager.drawAdvanced();
		}
		ImGui::End();
	}
}

//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	guiManager.AddGroup(params1);
}
