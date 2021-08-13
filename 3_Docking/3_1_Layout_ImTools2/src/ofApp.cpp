#include "ofApp.h"

void ofApp::Init()
{
	LoadConfigFile("config.xml");

	LayoutManager::Instance()->Init("Layouts", "Default Layout");
	LayoutManager::Instance()->AddPane(SamplePane::Instance(), "Sample", (1 << 0), PaneDisposal::LEFT, true, false);
	LayoutManager::Instance()->AddPane(TopPane::Instance(), "Top", (1 << 1), PaneDisposal::TOP, true, true);
	LayoutManager::Instance()->AddPane(RightPane::Instance(), "Right", (1 << 2), PaneDisposal::RIGHT, true, false);
	//LayoutManager::Instance()->AddPane(SamplePane::Instance(), "Sample", (1 << 1), PaneDisposal::RIGHT, true, false);
	//LayoutManager::Instance()->AddPane(LeftPane::Instance(), "Left", (1 << 0), PaneDisposal::LEFT, true, true);
	//LayoutManager::Instance()->AddPane(BottomPane::Instance(), "Bottom", (1 << 2), PaneDisposal::BOTTOM, true, true);
	//LayoutManager::Instance()->AddPane(CentralPane::Instance(), "Central", (1 << 4), PaneDisposal::CENTRAL, true, true);

	LayoutManager::Instance()->AddSpecificPaneToExisting("Sample", "Top");
}

void ofApp::Unit()
{
	SaveConfigFile("config.xml");
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	//-

	// parameters
	params1.setName("paramsGroup1"); // main container
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));

	params2.setName("paramsGroup2"); // nested
	params2.add(shapeType2.set("shapeType2", 0, -50, 50));
	params2.add(size2.set("size2", 100, 0, 100));
	params2.add(amount2.set("amount2", 10, 0, 25));

	params3.setName("paramsGroup3"); // nested
	params3.add(lineWidth3.set("lineWidth3", 0.5, 0, 1));
	params3.add(separation3.set("separation3", 50, 1, 100));
	params3.add(speed3.set("speed3", 0.5, 0, 1));

	//-

	guiManager.setImGuiDocking(1);
	// -> required false to allow custom docking layout. 
	// instead of the default centralized.
	guiManager.setImGuiDockingModeCentered(0);

	guiManager.setImGuiAutodraw(true); // -> required when only one ImGui instance (= n oother addons using ImGui)
	//guiManager.setImGuiDockingShift(true);
	guiManager.setup();
}

//////////////////////////////////////////////////////////////////////////////
//// DRAW ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void ofApp::Display(ImVec2 vSize)
{
	if (ImGui::BeginMainMenuBar())
	{
		LayoutManager::Instance()->DisplayMenu(vSize);

		if (ImGui::BeginMenu("ImGui"))
		{
			ImGui::MenuItem("Show ImGui Demo", "", &m_ShowImGui);
			ImGui::MenuItem("Show ImGui Metric/Debug", "", &m_ShowMetric);

			ImGui::EndMenu();
		}

		// ImGui Infos
		auto io = ImGui::GetIO();
		const auto label = ct::toStr("Dear ImGui %s (Docking)", ImGui::GetVersion());
		const auto size = ImGui::CalcTextSize(label.c_str());
		ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - size.x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));
		ImGui::Text("%s", label.c_str());

		ImGui::EndMainMenuBar();
	}

	if (LayoutManager::Instance()->BeginDockSpace(ImGuiDockNodeFlags_PassthruCentralNode))
	{
		//MainFrame::sCentralWindowHovered |= LayoutManager::Instance()->IsDockSpaceHoleHovered();

		LayoutManager::Instance()->EndDockSpace();
	}

	_widgetId = LayoutManager::Instance()->DisplayPanes(_widgetId);

	LayoutManager::Instance()->InitAfterFirstDisplay(vSize);

	LayoutManager::Instance()->DrawDialogsAndPopups();

	if (m_ShowImGui) ImGui::ShowDemoWindow(&m_ShowImGui);
	if (m_ShowMetric) ImGui::ShowMetricsWindow(&m_ShowMetric);
}

std::string ofApp::getXml(const std::string& vOffset, const std::string& vUserDatas)
{
	UNUSED(vUserDatas);

	std::string str;

	str += LayoutManager::Instance()->getXml(vOffset, "app");

	return str;
}

bool ofApp::setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas)
{
	UNUSED(vUserDatas);

	// The value of this child identifies the name of this element
	std::string strName;
	std::string strValue;
	std::string strParentName;

	strName = vElem->Value();
	if (vElem->GetText())
		strValue = vElem->GetText();
	if (vParent != 0)
		strParentName = vParent->Value();

	LayoutManager::Instance()->setFromXml(vElem, vParent, "app");

	return true;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin(); // global begin
	{
		if (!binitiated) {
			binitiated = true;
			{
				Init();
			}

			ofLogNotice(__FUNCTION__) << "Initialized done";
		}

		//-

		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::Begin("DockSpace", nullptr, window_flags);
		{
			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				//dockspace_flags |= ImGuiConfigFlags_DockingEnable

				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, viewport->Size, dockspace_flags);
				//ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

				//-

				//int display_w, display_h;
				int display_w = 500, display_h = 500;
				ImVec2 size;
				ImGuiIO& io = ImGui::GetIO();

				////io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
				////io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Viewport
				////io.FontAllowUserScaling = true; // activate zoom feature with ctrl + mousewheel
				//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
				//{
				//	ImGuiViewport* viewport = ImGui::GetMainViewport();
				//	if (viewport)
				//	{
				//		size = viewport->WorkSize;
				//	}
				//}
				//else
				//{
				//	size = ImVec2((float)display_w, (float)display_h);
				//}

				ImGuiViewport* viewport = ImGui::GetMainViewport();
				if (viewport)
				{
					size = viewport->WorkSize;
				}

				ImVec2 vSize = size;

				Display(vSize);

				/*
				if (ImGui::BeginMainMenuBar())
				{
					LayoutManager::Instance()->DisplayMenu(vSize);

					if (ImGui::BeginMenu("ImGui"))
					{
						ImGui::MenuItem("Show ImGui Demo", "", &m_ShowImGui);
						ImGui::MenuItem("Show ImGui Metric/Debug", "", &m_ShowMetric);

						ImGui::EndMenu();
					}

					// ImGui Infos
					auto io = ImGui::GetIO();
					const auto label = ct::toStr("Dear ImGui %s (Docking)", ImGui::GetVersion());
					const auto size = ImGui::CalcTextSize(label.c_str());
					ImGui::ItemSize(ImVec2(ImGui::GetContentRegionAvail().x - size.x - ImGui::GetStyle().FramePadding.x * 2.0f, 0));
					ImGui::Text("%s", label.c_str());

					ImGui::EndMainMenuBar();
				}

				//-

				if (LayoutManager::Instance()->BeginDockSpace(ImGuiDockNodeFlags_PassthruCentralNode))
				{
					//MainFrame::sCentralWindowHovered |= LayoutManager::Instance()->IsDockSpaceHoleHovered();

					LayoutManager::Instance()->EndDockSpace();
				}

				_widgetId = LayoutManager::Instance()->DisplayPanes(_widgetId);

				LayoutManager::Instance()->InitAfterFirstDisplay(vSize);
				LayoutManager::Instance()->DrawDialogsAndPopups();

				if (m_ShowImGui) ImGui::ShowDemoWindow(&m_ShowImGui);
				if (m_ShowMetric) ImGui::ShowMetricsWindow(&m_ShowMetric);


				//LayoutManager::Instance()->DrawWidgets(_widgetId);
				//LayoutManager::Instance()->ShowSpecificPane(PaneDisposal::LEFT);
				*/

				//--------

				// Place intems inside:
				// Dock Window Top

				//TODO: how to check if a pane is visible?
				//TODO: how to draw widgets inside the pane?
				//TODO: how to use from outside the class object??
				//app_LayoutManager.mainFrame.

				//--

				{
					static bool bOpen0 = true;
					static bool bOpen1 = true;
					static bool bOpen2 = true;

					//---------

					// Main Window

					// A raw standard raw ImGui window
					{
						ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
						if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

						ImGui::Begin("Show Windows", &bOpen0, window_flags);
						{
							// round toggles widgets
							ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);
							ofxImGuiSurfing::ToggleRoundedButton("Show Window 2", &bOpen2);

							ImGui::Dummy(ImVec2(0, 5)); // spacing

							ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize); // a public bool variable to allow handle auto-resize. Applied here to all the windows.
						}
						ImGui::End();
					}

					/*
					if (bOpen1)
					{
						guiManager.beginWindow("Top", &bOpen1, ImGuiWindowFlags_None);
						{
							//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
							////flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
							//flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed
							//ofxImGuiSurfing::AddGroup(params3, flags);

							guiManager.AddGroup(params3);

							guiManager.drawAdvancedSubPanel();
						}
						guiManager.endWindow();
					}
					*/

					//---------

					// Place intems inside:
					// Dock Window Central
					/*
					if (bOpen2)
					{
						guiManager.beginWindow("Central", &bOpen2, ImGuiWindowFlags_None);
						{
							float _w100 = ofxImGuiSurfing::getWidgetsWidth(1); // full width
							float _w50 = ofxImGuiSurfing::getWidgetsWidth(2); // half width
							float _h = ofxImGuiSurfing::getWidgetsHeightRelative(); // standard height

							// Two custom toggles
							if (ofxImGuiSurfing::AddBigToggle(bEnable)) {} // this is full width (_w100) with standard height (_h)
							//if (ofxImGuiSurfing::AddBigToggle(bEnable, _w100, _h)) {} // same width but half height

							// Two custom buttons in the same line/row
							// 50% width aka two widgets on current same line/row
							if (ofxImGuiSurfing::AddBigButton(bPrevious, _w50, _h*2)) {
								lineWidth -= 0.1;
								bPrevious = false;
							}
							ImGui::SameLine();
							if (ofxImGuiSurfing::AddBigButton(bNext, _w50, _h*2)) {
								lineWidth += 0.1;
								bNext = false;
							}

							// Three standard widget params
							ofxImGuiSurfing::AddParameter(bEnable);
							ofxImGuiSurfing::AddParameter(separation);
							ofxImGuiSurfing::AddParameter(shapeType);
						}
						guiManager.endWindow();
					}
					*/

					//-----

				} // docking
			}
		}
		ImGui::End();
	}
	guiManager.end(); // global end
}

//--------------------------------------------------------------
void ofApp::exit()
{
	Unit();
}