
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_ofHelpers.h"

/*


TODO:
	+ fix recolotate when closed first window
	+ store sorting queue ?
	+ fix close window using [x]
*/


using namespace ofxImGuiSurfing;

//----

namespace ofxImGuiSurfing
{
	//TODO: 
	// Cascade windows engine..
	//--------------------------------------------------------------
	class WindowPanel {

	public:

		ofParameter<bool> bEnable{ "bEnable", true };
		ofParameter<ofRectangle> rShape{ "rShape", ofRectangle(0,0,0,0), ofRectangle(0,0,0,0), ofRectangle(1920,1080,1920,1080) };
		ofParameter<int> pos{ "IndexPos", -1, -1, 0 };
		int id = -1;

		//--------------------------------------------------------------
		WindowPanel::WindowPanel() {
		}

		//--------------------------------------------------------------
		WindowPanel::~WindowPanel() {
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

		//--------------------------------------------------------------
		void runState()
		{
			bool bMaster = (pos == 0);
			ImGuiCond flagCond;
			if (bMaster) flagCond = ImGuiCond_Appearing; // only first window can be moved
			else flagCond = ImGuiCond_Always; // Others are locked

			ImGui::SetNextWindowPos(ImVec2(rShape.get().getX(), rShape.get().getY()), flagCond);
			//ImGui::SetNextWindowSize(ImVec2(rShape.get().getWidth(), rShape.get().getHeight()), flagCond);

			//bool bSize = false;//TODO:
			//if (bSize) ImGui::SetNextWindowSize(ImVec2(rShape.get().getWidth(), rShape.get().getHeight()), flagCond);
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

	//--------------------------------------------------------------
	class WindowPanels {

	public:

		ofParameter<bool> bGui_Global{ "Show Global", true };
		ofParameter<bool> bHeaders{ "Hide Headers", true };
		ofParameter<bool> bModeLinkedWindowsSpecial{ "Mode Cascade",  false };
		ofParameter<bool> bFitSizes{ "Fit Sizes",  false };

	private:

		ofParameter<bool> bLockedWidth{ "Lock Width", false };
		ofParameter<bool> bLockedHeight{ "Lock Height", false };
		float width_max = 0;
		float height_max = 0;

		std::vector<WindowPanel> panels; // all the added panels
		std::string path_Global = "";
		std::string path_Settings = "WindowsSpecial.json";

	public:

		void setPath(std::string path) {
			path_Global = path;
			path_Settings = path_Global + "GuiManager_" + params_Settings.getName() + ".json";
		}

	private:

		std::vector<int> panelsQueue; // just the enabled (visible) panels
		ofParameter<int> counterQueue{ "counterQueue", 0, 0, 0 }; // count how many visible/queued

		ofParameterGroup params_Enablers{ "Enablers" };
		ofParameterGroup params_Settings{ "WindowsSpecial" };
		ofParameterGroup params{ "Params" };

		// Cascade orientation
		enum wOrientation
		{
			W_HORIZ = 0,
			W_VERT,
			W_COUNT
		};
		wOrientation orientation;
		ofParameter<bool> bOrientation{ "Orientation", false };
		ofParameter<int> iOrientation{ "Orient", 0, 0, W_COUNT - 1 };
		std::vector<string> sOrientation{ "HORIZONTAL", "VERTICAL" };
		ofParameter<int> pad{ "Padding", 0, 0, 25 };

		ofParameter<glm::vec2> position{ "position", glm::vec2(10,10), glm::vec2(0,0), glm::vec2(1920,1080) };

		//--

	public:

		//--------------------------------------------------------------
		WindowPanels::WindowPanels()
		{
			ofAddListener(params_Enablers.parameterChangedE(), this, &WindowPanels::Changed_Params_Enablers);
			ofAddListener(params.parameterChangedE(), this, &WindowPanels::Changed_Params);

			counterQueue.addListener(this, &WindowPanels::Changed_counterQueue);
		}

		//--------------------------------------------------------------
		WindowPanels::~WindowPanels()
		{
			ofRemoveListener(params_Enablers.parameterChangedE(), this, &WindowPanels::Changed_Params_Enablers);
			ofRemoveListener(params.parameterChangedE(), this, &WindowPanels::Changed_Params);

			if (panelsQueue.size() == 0 || panels.size() == 0) return;
			int id = panelsQueue[0];
			position.set(panels[id].getPosition());

			ofxImGuiSurfing::saveGroup(params_Settings, path_Settings);
		}

	private:

		//--------------------------------------------------------------
		void Changed_counterQueue(int &i)
		{
			// Return if not changed
			static int pre = -1;
			if (pre == i) return;
			else pre = i;

			ofLogNotice() << __FUNCTION__ << " Counter #" << counterQueue;

			////TODO:
			//bool b = !(panelsQueue.size() == 0 || panels.size() == 0);
			//if (b) {
			//	int id = panelsQueue[0];
			//	//refresh
			//	position = panels[id].getPosition();
			//}

			doOrganize();
		}

		//--------------------------------------------------------------
		void Changed_Params(ofAbstractParameter &e)
		{
			std::string name = e.getName();

			ofLogVerbose() << __FUNCTION__ << " " << name << " : " << e;

			if (0) {}

			//TODO: should recalculate..
			else if (name == bHeaders.getName())
			{
				doSetWindowsPositions();
			}

			else if (name == bGui_Global.getName())
			{
				//workaround to avoid bad dimension on startup
				bOrientation = bOrientation;
			}

			else if (name == iOrientation.getName())
			{
				static int pre = -1;
				if (iOrientation != pre) pre = iOrientation;
				else return;//not changed then skip

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

			else if (name == bOrientation.getName())
			{
				if (!bOrientation) iOrientation = 0;
				else iOrientation = 1;

				doSetWindowsPositions();
			}
		}

		//--------------------------------------------------------------
		void Changed_Params_Enablers(ofAbstractParameter &e)
		{
			std::string name = e.getName();

			ofLogVerbose() << __FUNCTION__ << " " << name << " : " << e;

			//-

			// Check toggle enablers

			int i = 0;
			for (auto &p : panels)
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
							counterQueue = panelsQueue.size();

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

								position = p.getPosition();//refresh

								if (p.pos == 0)//warn if it's the first window
								{
									ofLogWarning() << __FUNCTION__ << " Closing window ID #" << p.id << ", the first one!";
									bSort = true;
								}

								p.pos = -1;

								// remove
								panelsQueue.erase(panelsQueue.begin() + i);
								counterQueue = panelsQueue.size();

								//TODO:
								if (bSort)
								{
									doRepositione();
								}

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

			// reorganize sorting indexes

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

	public:

		//--------------------------------------------------------------
		void add(ofParameter<bool> &e) // add panels on setup
		{
			ofLogNotice() << __FUNCTION__ << e.getName();

			WindowPanel p;
			p.id = panels.size();
			p.pos = -1;
			p.bEnable.makeReferenceTo(e);
			params_Enablers.add(e);
			panels.push_back(p);

			counterQueue.setMax(panels.size() - 1);
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

			params.add(bGui_Global);
			params.add(bOrientation);
			params.add(iOrientation);
			params.add(bHeaders);
			params.add(bFitSizes);

			params_Settings.add(bGui_Global);
			params_Settings.add(bModeLinkedWindowsSpecial);
			params_Settings.add(bOrientation);
			params_Settings.add(position);
			params_Settings.add(pad);
			params_Settings.add(bFitSizes);
			params_Settings.add(bLockedWidth);
			params_Settings.add(bLockedHeight);
			params_Settings.add(bHeaders);

			params_Settings.add(params_Enablers);

			//--

			// Disable all
			for (auto &p : params_Enablers)
			{
				if (p->type() == typeid(ofParameter<bool>).name())
				{
					ofParameter<bool> pm = p->cast<bool>();
					pm = false;
				}
			}

			//--

			// Startup

			// Load Settings
			ofxImGuiSurfing::loadGroup(params_Settings, path_Settings);

			//-

			if (panelsQueue.size() == 0 || panels.size() == 0) return;
			int id = panelsQueue[0];
			panels[id].setPosition(position.get());

			//bLockedWidth = bLockedWidth;
			//bLockedHeight = bLockedHeight;

			bOrientation = bOrientation;
			//bOrientation = !bOrientation;
			//bOrientation = !bOrientation;
		}

	private:

		void refreshQueues()
		{
		}

		void getStates()
		{
		}

		void runStates()
		{
		}

	public:

		//--------------------------------------------------------------
		void getState(int i)
		{
			panels[i].getState();
		}

		//--------------------------------------------------------------
		void runState(int i)
		{
			panels[i].runState();
			doApplyMaxDimensions();
		}

	public:

		//--------------------------------------------------------------
		void setNameGlobalPanelWindowsSpecial(std::string name) {
			bGui_Global.setName(name);
		}

		//--------------------------------------------------------------
		void beginWindow(string name, bool *bOpen = NULL, ImGuiWindowFlags flags = ImGuiWindowFlags_None)
		{
			ImGui::Begin(name.c_str(), bOpen, flags);
		}

		//--------------------------------------------------------------
		void drawWidgets(bool bMinimized = false)
		{
			float _h = getWidgetsHeight();
			float _w1 = getWidgetsWidth(1);
			float _w2 = getWidgetsWidth(2);

			// Enable mode
			//ofxImGuiSurfing::AddToggleRoundedButtonNamed(bModeLinkedWindowsSpecial);//small
			ofxImGuiSurfing::AddBigToggle(bModeLinkedWindowsSpecial);

			ImGui::Spacing();

			if (bModeLinkedWindowsSpecial) {
				// Orientation
				string ss = bOrientation ? "Vertical" : "Horizontal";
				ofxImGuiSurfing::AddToggleRoundedButton(bOrientation, ss, ImVec2(-1, -1));
				ofxImGuiSurfing::AddToggleRoundedButton(bFitSizes);

				ImGui::Spacing();
			}

			//-

			{
				static bool bOpen = false;
				ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
				if (ImGui::CollapsingHeader("Windows", _flagw))
				{
					// Global Enable 
					//ofxImGuiSurfing::AddToggleRoundedButtonNamed(bGui_Global, ImVec2(-1, -1));//small
					ofxImGuiSurfing::AddToggleRoundedButton(bGui_Global, ImVec2(2 * _h, 2 * (2 / 3.f) * _h));//medium

					if (bGui_Global)
					{
						for (auto &p : panels)
						{
							ImGui::Indent();
							ofxImGuiSurfing::AddToggleRoundedButton(p.bEnable, ImVec2(2 * _h, 2 * (2 / 3.f) * _h));
							//ofxImGuiSurfing::AddBigToggle(p.bEnable, ImVec2(-1, -1));
							ImGui::Unindent();
						}

						ImGui::Spacing();

						if (ImGui::Button("All", ImVec2(_w2, _h)))
						{
							for (auto &p : panels) {
								p.bEnable = true;
							}
						}
						ImGui::SameLine();
						if (ImGui::Button("None", ImVec2(_w2, _h)))
						{
							for (auto &p : panels) {
								p.bEnable = false;
							}
						}
					}
				}

				ImGui::Spacing();

				if (!bMinimized)
				{
					// Controls
					{
						static bool bOpen = false;
						ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
						if (ImGui::CollapsingHeader("Settings", _flagw))
						{
							ImGui::PushItemWidth(getPanelWidth() * 0.5f);
							{
								ofxImGuiSurfing::AddIntStepped(pad);
								ofxImGuiSurfing::AddParameter(bHeaders);
							}
							ImGui::PopItemWidth();

							//-

							// Debug

							static ofParameter<bool> bDebug{ "Debug", false };
							ofxImGuiSurfing::AddToggleRoundedButton(bDebug);
							ImGui::Spacing();
							if (bDebug)
							{
								ImGui::Indent();

								ofxImGuiSurfing::AddParameter(bLockedWidth);
								ofxImGuiSurfing::AddParameter(bLockedHeight);

								std::string ss1 = "";
								int i = 0;
								for (auto &p : panels)
								{
									ss1 += "[" + ofToString(i) + "] ";
									ss1 += ofToString(p.pos);
									ss1 += "\n";
									ss1 += ofToString(p.getRectangle());
									ss1 += "\n";
									ss1 += "\n";

									i++;
								}
								ImGui::TextWrapped(ss1.c_str());
								ImGui::Spacing();

								std::string ss2 = "queue\n";
								for (int i = 0; i < panelsQueue.size(); i++)
								{
									if (i != 0) ss2 += ", ";
									ss2 += ofToString(panelsQueue[i]);
								}
								ImGui::TextWrapped(ss2.c_str());
								ImGui::Spacing();

								std::string ss3 = "";
								ss3 += "amnt\n";
								ss3 += ofToString(panelsQueue.size());
								ImGui::TextWrapped(ss3.c_str());
								ImGui::Spacing();
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

			//doSetWindowsPositions();
		}

	private:

		//--------------------------------------------------------------
		void doRepositione()
		{
			//TODO:
			return;

			ofLogNotice() << __FUNCTION__ << " " << position.get();
			if (panelsQueue.size() == 0 || panels.size() == 0) return;
			int id = panelsQueue[0];
			panels[id].setPosition(position.get());
		}

	public:

		//--------------------------------------------------------------
		void update() {
			doSetWindowsPositions();
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
