
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_ofHelpers.h"

/*
	TODO:

	+ fix re position when closed first queued window
	+ add reset layout
	+ store sorting queue ?
	+ cascade windows engine
*/


using namespace ofxImGuiSurfing;

//----

namespace ofxImGuiSurfing
{
	// One Window
	//--------------------------------------------------------------
	class WindowPanel {

	public:

		//--------------------------------------------------------------
		WindowPanel() {
		}

		//--------------------------------------------------------------
		~WindowPanel() {
		}

		//--------------------------------------------------------------
		void getState()
		{
			rShape = ofRectangle(
				ImGui::GetWindowPos().x,
				ImGui::GetWindowPos().y,
				ImGui::GetWindowWidth(),
				ImGui::GetWindowHeight());
		}

	public:

		ofParameter<bool> bEnable{ "bEnable", true };
		ofParameter<ofRectangle> rShape{ "rShape", ofRectangle(0,0,0,0), ofRectangle(0,0,0,0), ofRectangle(1920,1080,1920,1080) };
		ofParameter<int> pos{ "IndexPos", -1, -1, 0 };
		int id = -1;

	public:

		//--------------------------------------------------------------
		void runState(bool bForced = false)
		{
			bool b1st;

			if (!bForced) b1st = (pos == 0);
			else b1st = false;

			ImGuiCond flagCond;
			if (b1st) flagCond = ImGuiCond_Appearing; // only first window can be moved
			else flagCond = ImGuiCond_Always; // Others are locked

			ImGui::SetNextWindowPos(ImVec2(rShape.get().getX(), rShape.get().getY()), flagCond);
			//ImGui::SetNextWindowSize(ImVec2(rShape.get().getWidth(), rShape.get().getHeight()), flagCond);
		}

		//--------------------------------------------------------------
		ofRectangle getRectangle() const
		{
			return rShape.get();
		}

		//--------------------------------------------------------------
		glm::vec2 getPosition() const
		{
			return glm::vec2(rShape->x, rShape->y);
		}

		//--------------------------------------------------------------
		float getWidth() const
		{
			return rShape->getWidth();
		}

		//--------------------------------------------------------------
		void setPosition(glm::vec2 pos)
		{
			rShape->x = pos.x;
			rShape->y = pos.y;
		}

		//--------------------------------------------------------------
		void setRectangle(ofRectangle r)
		{
			rShape = r;
		}
	};


	//----


	//--------------------------------------------------------------

	// Container Manager for all the manager special windows to handle.

	class WindowPanels
	{
	public:

		//--------------------------------------------------------------
		WindowPanels()
		{
			ofAddListener(params_Enablers.parameterChangedE(), this, &WindowPanels::Changed_Params_Enablers);
			ofAddListener(params.parameterChangedE(), this, &WindowPanels::Changed_Params);

			amountQueue.addListener(this, &WindowPanels::Changed_counterQueue);

			//-

			params_User.clear();

			params_User.add(bModeLinkedWindowsSpecial);
			params_User.add(bOrientation);
			params_User.add(bFitSizes);
			params_User.add(bHeaders);
			params_User.add(pad);
			params_User.add(position_Anchor);

			params_User.add(bGui_WindowsSpecials);
			params_User.add(bGui_ShowAll);
		}

		//--------------------------------------------------------------
		~WindowPanels()
		{
			ofRemoveListener(params_Enablers.parameterChangedE(), this, &WindowPanels::Changed_Params_Enablers);
			ofRemoveListener(params.parameterChangedE(), this, &WindowPanels::Changed_Params);

			// Save
			ofxImGuiSurfing::saveGroup(params_WindowsSpecials, path_Settings);
		}

		//--

	public:

		ofParameter<bool> bGui_WindowsSpecials{ "_Organizer", true }; // toggle gui to draw main window.
		ofParameter<bool> bGui_ShowAll{ "Show All", true }; // extra toggle to hide / show all the queued windows.
		ofParameter<bool> bModeLinkedWindowsSpecial{ "Link Windows",  false };
		ofParameter<bool> bOrientation{ "Orientation", false };
		ofParameter<bool> bFitSizes{ "Fit Sizes",  false };
		ofParameter<bool> bHeaders{ "Hide Headers", true };
		ofParameter<int> pad{ "Padding", 0, 0, 25 };
		ofParameter<glm::vec2> position_Anchor{ "Position Anchor", glm::vec2(10,10), glm::vec2(0,0), glm::vec2(1920,1080) };

	private:

		bool bResetLayout = false;

	public:

		//--------------------------------------------------------------
		bool isIntitiated() {
			return panels.size() > 0;
		}

	private:

		ofParameter<bool> bLockedWidth{ "Lock Width", false };
		ofParameter<bool> bLockedHeight{ "Lock Height", false };

		float width_max = 0;
		float height_max = 0;

		std::vector<WindowPanel> panels; // all the added panels
		std::string path_Global = "";
		std::string path_Settings = "_WindowsSpecial.json";

	public:

		//--------------------------------------------------------------
		void setPath(std::string path)
		{
			path_Global = path;
			ofxSurfingHelpers::CheckFolder(path_Global);
			path_Settings = path_Global + "guiManager_" + params_WindowsSpecials.getName() + ".json";
		}

	private:

		std::vector<int> panelsQueue; // just the enabled (visible) panels
		ofParameter<int> amountQueue{ "amountQueue", 0, 0, 0 }; // count how many visible/queued

		ofParameterGroup params_Enablers{ "Enablers" };
		ofParameterGroup params_WindowsSpecials{ "WindowsSpecials" };
		ofParameterGroup params{ "Params" };

		// Cascade orientation
		enum wOrientation
		{
			W_HORIZ = 0,
			W_VERT,
			W_COUNT
		};
		wOrientation orientation;
		ofParameter<int> iOrientation{ "Orient", 0, 0, W_COUNT - 1 };
		//std::vector<string> sOrientation{ "HORIZONTAL", "VERTICAL" };

		bool bHideWindows = false; //-> To disable when using the full layout engine. 

	public:

		//--------------------------------------------------------------
		void setHideWindows(bool b) {

			bHideWindows = b;

			if (bHideWindows) {
				bGui_ShowAll = true;
				bGui_ShowAll.setSerializable(false);
			}
		}

		//-

		ofParameterGroup params_User{ "Organizer" }; // To use on a external GUI 

	public:

		//--------------------------------------------------------------
		ofParameterGroup& getParamsUser() {
			return params_User;
		}

	private:

		//--------------------------------------------------------------
		void Changed_counterQueue(int& i)
		{
			ofLogNotice() << __FUNCTION__;

			// Return if not changed
			static int pre = -1;
			if (pre == i) return;
			else pre = i;

			ofLogNotice() << __FUNCTION__ << " Counter #" << amountQueue;

			doOrganize();
		}

		//--------------------------------------------------------------
		void Changed_Params(ofAbstractParameter& e)
		{
			std::string name = e.getName();

			ofLogVerbose() << __FUNCTION__ << " " << name << " : " << e;

			//-

			if (0) {}

			//-

			//TODO: should recalculate..

			else if (name == bHeaders.getName())
			{
				doSetWindowsPositions();
			}

			//-

			else if (name == bGui_ShowAll.getName())
			{
				// workaround 
				// to avoid bad dimension on startup
				bOrientation = bOrientation;
			}

			//-

			else if (name == bFitSizes.getName())
			{
				//fix
				if (bFitSizes) {
					bOrientation = bOrientation;
				}
			}

			//-

			else if (name == iOrientation.getName())
			{
				static int pre = -1;
				if (iOrientation != pre) pre = iOrientation;
				else return; // not changed then skip

				if (iOrientation == 0) bOrientation.set(false);
				else bOrientation.set(true);

				//if (bFitSizes)
				{
					if (iOrientation == 0) {
						bLockedWidth = false;
						bLockedHeight = true;
					}
					else {
						bLockedWidth = true;
						bLockedHeight = false;
					}
				}

				doSetWindowsPositions();
			}

			//-

			else if (name == bOrientation.getName())
			{
				if (!bOrientation) iOrientation = 0;
				else iOrientation = 1;

				doSetWindowsPositions();
			}

			//-

			else if (name == position_Anchor.getName())
			{
				// Position linked to first queued window
				if (panelsQueue.size() == 0 || panels.size() == 0) return;
				int id = panelsQueue[0];
				panels[id].setPosition(position_Anchor.get());

				doSetWindowsPositions();
			}
		}

		//--------------------------------------------------------------
		void Changed_Params_Enablers(ofAbstractParameter& e)
		{
			std::string name = e.getName();

			ofLogVerbose() << __FUNCTION__ << " " << name << " : " << e;

			//-

			// Check toggle enablers

			int i = 0;
			for (auto& p : panels)
			{
				if (name == p.bEnable.getName()) // Check wich one is clicked
				{
					ofLogNotice() << __FUNCTION__ << " Enabler #" << i << " " << (p.bEnable.get() ? "TRUE" : "FALSE");

					if (p.bEnable) // Add 
					{
						if (p.pos == -1) // It was hidden
						{
							p.pos = panelsQueue.size();
							panelsQueue.push_back(p.id);
							amountQueue = panelsQueue.size();

							return;
						}
					}
					else // Remove
					{
						for (int i = 0; i < panelsQueue.size(); i++)
						{
							if (p.id == panelsQueue[i]) // If it's on queue, remove it from there
							{
								bool bSort = false;

								position_Anchor = p.getPosition();//refresh

								if (p.pos == 0)//warn if it's the first window
								{
									ofLogWarning() << __FUNCTION__ << " Closing window ID #" << p.id << ", the first one!";
									bSort = true;
								}

								p.pos = -1;

								// remove
								panelsQueue.erase(panelsQueue.begin() + i);
								amountQueue = panelsQueue.size();

								////TODO:
								//if (bSort)
								//{
								//	doRepositione();
								//}

								return;
							}
						}
					}
					return;
				}
				i++;
			}
		}

		//--------------------------------------------------------------
		void doOrganize()
		{
			ofLogNotice() << __FUNCTION__;

			// Reorganize sorting indexes

			// Disable all
			for (int i = 0; i < panels.size(); i++)
			{
				panels[i].pos = -1;
				panels[i].bEnable.setWithoutEventNotifications(false);
			}

			for (int i = 0; i < panelsQueue.size(); i++) // search each item into queue
			{
				int id = panelsQueue[i];
				int pos = i;

				panels[id].pos = pos;
				panels[id].bEnable.setWithoutEventNotifications(true);
			}
		}

			//TODO:
		//--------------------------------------------------------------
		void doResetLayout()
		{

			ofLogNotice() << __FUNCTION__;

			if (panelsQueue.size() < 2 || panelsQueue.size() == 0)
			{
				ofLogWarning() << __FUNCTION__ << " Skip!";
				return;
			}

			// 1st
			{
				glm::vec2 posPre{ 10, 10 };
				int id = panelsQueue[0];
				panels[id].setPosition(posPre);
			}

			for (int i = 1; i < panelsQueue.size(); i++) // search each item into queue
			{
				glm::vec2 posPre;

				int idPre = panelsQueue[i - 1];
				posPre = panels[idPre].getPosition();

				int id = panelsQueue[i];
				panels[id].setPosition(posPre);
			}

			//for (int i = 1; i < panelsQueue.size(); i++) // search each item into queue
			//{
			//	int id = panelsQueue[i];
			//	runState(id, true);
			//}

			//doSetWindowsPositions(); 
			//doOrganize(); 
		}

	public:

		//--------------------------------------------------------------
		void add(ofParameter<bool>& e) // add panels on setup
		{
			ofLogNotice() << __FUNCTION__ << e.getName();

			WindowPanel p;
			p.id = panels.size();
			p.pos = -1;
			p.bEnable.makeReferenceTo(e);
			params_Enablers.add(e);
			panels.push_back(p);

			amountQueue.setMax(panels.size() - 1);
		}

	public:

		//--------------------------------------------------------------
		void doApplyMaxDimensions()
		{
			if (ofGetFrameNum() < 2) return;

			if (!bFitSizes) return;//skip

			if (bLockedWidth && bLockedHeight) {
				ImGui::SetNextWindowSize(ImVec2(width_max, height_max));
			}
			else if (bLockedWidth) {
				ImGui::SetNextWindowSize(ImVec2(width_max, 0));
			}
			else if (bLockedHeight) {
				ImGui::SetNextWindowSize(ImVec2(0, height_max));
			}
		}

		//--------------------------------------------------------------
		void initiate()
		{
			ofLogNotice() << __FUNCTION__;

			//--

			// Disable all
			for (auto& p : params_Enablers)
			{
				if (p->type() == typeid(ofParameter<bool>).name())
				{
					ofParameter<bool> pm = p->cast<bool>();
					pm = false;
				}
			}

			// To get notified by the callbacks
			params.add(bGui_ShowAll);
			params.add(bOrientation);
			params.add(iOrientation);
			params.add(bHeaders);
			params.add(bFitSizes);
			params.add(position_Anchor);

			// To store session settings
			params_WindowsSpecials.add(bGui_WindowsSpecials);
			params_WindowsSpecials.add(bGui_ShowAll);
			params_WindowsSpecials.add(bModeLinkedWindowsSpecial);
			params_WindowsSpecials.add(bOrientation);
			params_WindowsSpecials.add(position_Anchor);
			params_WindowsSpecials.add(pad);
			params_WindowsSpecials.add(bFitSizes);
			params_WindowsSpecials.add(bLockedWidth);
			params_WindowsSpecials.add(bLockedHeight);
			params_WindowsSpecials.add(bHeaders);

			// Each window enabler will be added here..
			// all of theme has been added during setup
			params_WindowsSpecials.add(params_Enablers);

			startup();
		}

		//--------------------------------------------------------------
		void startup()
		{
			ofLogNotice() << __FUNCTION__;

			//--

			// Load Settings
			ofxImGuiSurfing::loadGroup(params_WindowsSpecials, path_Settings);

			//-

			// Position linked to first queued window
			if (panelsQueue.size() == 0 || panels.size() == 0) return;
			int id = panelsQueue[0];
			panels[id].setPosition(position_Anchor.get());

			bOrientation = bOrientation;
			//bLockedWidth = bLockedWidth;
			//bLockedHeight = bLockedHeight;
		}

		//--

	//private:

	//	void refreshQueues()
	//	{
	//	}

	//	void getStates()
	//	{
	//	}

	//	void runStates()
	//	{
	//	}

	public:

		//--------------------------------------------------------------
		void getState(int i)
		{
			panels[i].getState();
		}

		//--------------------------------------------------------------
		void runState(int i, bool bForced = false)
		{
			panels[i].runState(bForced);
			doApplyMaxDimensions();
		}

	public:

		//--------------------------------------------------------------
		void setNameWindowsSpecialsEnableGlobal(std::string name) {
			bGui_ShowAll.setName(name);
		}

		//--------------------------------------------------------------
		void beginWindow(string name, bool* bOpen = NULL, ImGuiWindowFlags flags = ImGuiWindowFlags_None)
		{
			ImGui::Begin(name.c_str(), bOpen, flags);
		}

		//--------------------------------------------------------------
		void drawWidgets(bool bMinimized = false)
		{
			float _h = getWidgetsHeight();
			float _w1 = getWidgetsWidth(1);
			float _w2 = getWidgetsWidth(2);

			// Enable

			ofxImGuiSurfing::AddBigToggle(bModeLinkedWindowsSpecial);

			//TODO: Trig
			//if (0)
			if (ImGui::Button("Reset", ImVec2(_w1, _h)))
			{
				bResetLayout = true;
			}

			ImGui::Spacing();

			if (bModeLinkedWindowsSpecial)
			{
				// Orientation
				string ss = bOrientation ? "Vertical" : "Horizontal";
				float h = 1.25 * ImGui::GetFrameHeight();
				float w = h * 1.55f;

				ofxImGuiSurfing::AddToggleRoundedButton(bOrientation, ss, ImVec2(w, h));
				ofxImGuiSurfing::AddToggleRoundedButton(bFitSizes);

				ImGui::Spacing();
			}

			//-

			{
				// Windows

				if (!bHideWindows)
				{
					ofxImGuiSurfing::AddSpacingSeparated();

					static bool bOpen = false;
					ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);

					if (ImGui::CollapsingHeader("WINDOWS", _flagw))
					{
						ImGui::Spacing();

						if (ImGui::Button("All", ImVec2(_w2, _h)))
						{
							for (auto& p : panels) {
								p.bEnable = true;
							}
						}
						ImGui::SameLine();
						if (ImGui::Button("None", ImVec2(_w2, _h)))
						{
							for (auto& p : panels) {
								p.bEnable = false;
							}
						}

						ImGui::Spacing();

						//--

						// Global Enable 

						ofxImGuiSurfing::AddToggleRoundedButton(bGui_ShowAll, ImVec2(2 * _h, 2 * (2 / 3.f) * _h));//medium
						//ofxImGuiSurfing::AddToggleRoundedButtonNamed(bGui_ShowAll, ImVec2(-1, -1));//small

						if (bGui_ShowAll)
						{
							for (auto& p : panels)
							{
								ImGui::Indent();
								ofxImGuiSurfing::AddToggleRoundedButton(p.bEnable, ImVec2(2 * _h, 2 * (2 / 3.f) * _h));
								//ofxImGuiSurfing::AddBigToggle(p.bEnable, ImVec2(-1, -1));
								ImGui::Unindent();
							}

							ImGui::Spacing();
						}
					}
				}

				//ImGui::Spacing();

				// Settings
				if (bModeLinkedWindowsSpecial)
					if (!bMinimized)
					{
						// Controls
						{
							ofxImGuiSurfing::AddSpacingSeparated();

							static bool bOpen = false;
							ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);

							if (ImGui::CollapsingHeader("SETTINGS", _flagw))
							{
								ImGui::PushItemWidth(getPanelWidth() * 0.5f);
								{
									ofxImGuiSurfing::AddStepperInt(pad);
									ofxImGuiSurfing::AddParameter(bHeaders);
								}
								ImGui::PopItemWidth();

								//-

								ofxImGuiSurfing::AddSpacingSeparated();

								// Debug

								static ofParameter<bool> bDebug{ "Debug", false };
								ofxImGuiSurfing::AddToggleRoundedButton(bDebug);
								ImGui::Spacing();
								if (bDebug)
								{
									ImGui::Indent();

									ofxImGuiSurfing::AddParameter(bLockedWidth);
									ofxImGuiSurfing::AddParameter(bLockedHeight);
									ImGui::Spacing();
									
									ofxImGuiSurfing::AddSpacingSeparated();

									ImGui::Spacing();
									ImGui::TextWrapped("Special Windows:\n");
									ImGui::Spacing();

									std::string ss1 = "";
									int i = 0;
									for (auto& p : panels)
									{
										//ss1 += "[" + ofToString(i) + "] ";
										ss1 += " #" + ofToString(p.pos);
										ss1 += "\n";
										ss1 += ofToString(p.getRectangle());
										ss1 += "\n";
										ss1 += "\n";

										i++;
									}
									ImGui::TextWrapped(ss1.c_str());
									
									ofxImGuiSurfing::AddSpacingSeparated();

									std::string ss2 = "Queue:\n\n";
									for (int i = 0; i < panelsQueue.size(); i++)
									{
										if (i != 0) ss2 += ", ";
										ss2 += ofToString(panelsQueue[i]);
									}
									ImGui::TextWrapped(ss2.c_str());
									
									ofxImGuiSurfing::AddSpacingSeparated();

									std::string ss3 = "";
									ss3 += "Amount:\n\n";
									ss3 += ofToString(panelsQueue.size());
									ImGui::TextWrapped(ss3.c_str());
									
									ofxImGuiSurfing::AddSpacingSeparated();

									ImGui::Unindent();
								}
							}
						}
					}
			}
		}

		//--------------------------------------------------------------
		void endWindow()
		{
			ImGui::End();
		}

		//private:
		//	//--------------------------------------------------------------
		//	void doRepositione()
		//	{
		//		////TODO:
		//		//return;
		//		//ofLogNotice() << __FUNCTION__ << " " << position_Anchor.get();
		//		//if (panelsQueue.size() == 0 || panels.size() == 0) return;
		//		//int id = panelsQueue[0];
		//		//panels[id].setPosition(position_Anchor.get());
		//	}

	public:

		//--------------------------------------------------------------
		void update() {

			//TODO:
			// Reset layout
			if (bResetLayout)
			{
				bResetLayout = false;

				doResetLayout();

				return;
			}

			//--
			 
			// Read 1st queued position to the anchor
			if (panelsQueue.size() == 0 || panels.size() == 0) return;
			int id = panelsQueue[0];
			position_Anchor.set(panels[id].getPosition());

			//--

			// Apply all links to windows
			if (bModeLinkedWindowsSpecial) doSetWindowsPositions();
		}

	private:

		//--------------------------------------------------------------
		void doSetWindowsPositions()
		{
			if (panelsQueue.size() == 0 || panels.size() == 0) return;

			ofRectangle rCurr;
			ofRectangle rNext;

			//-

			// All windows with the same max width
			if (bLockedWidth || bLockedHeight)
			{
				for (int i = 0; i < panelsQueue.size(); i++)
				{
					int id = panelsQueue[i];
					rCurr = panels[id].getRectangle();
					if (bLockedWidth) if (width_max < rCurr.getWidth()) width_max = rCurr.getWidth();
					if (bLockedHeight) if (height_max < rCurr.getHeight()) height_max = rCurr.getHeight();
				}
			}

			//-

			for (int i = 0; i < panelsQueue.size() - 1; i++) // Exclude the lastone
			{
				int id, idNext;

				id = panelsQueue[i];
				idNext = panelsQueue[i + 1];

				rCurr = panels[id].getRectangle();
				rNext = panels[idNext].getRectangle();

				if (iOrientation == W_HORIZ)
				{
					glm::vec2 p = rCurr.getTopRight();
					rNext.setPosition(p.x + pad, p.y);
					panels[idNext].setRectangle(rNext);
				}
				else if (iOrientation == W_VERT)
				{
					glm::vec2 p = rCurr.getBottomLeft();
					rNext.setPosition(p.x, p.y + pad);
					panels[idNext].setRectangle(rNext);
				}
			}
		}
	};
}
