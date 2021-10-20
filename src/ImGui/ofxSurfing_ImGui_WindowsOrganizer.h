
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_ofHelpers.h"

/*


TODO:

	+ store sorting

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

		WindowPanel::WindowPanel() {
		}

		WindowPanel::~WindowPanel() {
		}

		void getState()
		{
			rShape = ofRectangle(
				ImGui::GetWindowPos().x,
				ImGui::GetWindowPos().y,
				ImGui::GetWindowWidth(),
				ImGui::GetWindowHeight());
		}

		void runState()
		{
			bool bMaster = (pos == 0);
			ImGuiCond flagCond;
			if (bMaster) flagCond = ImGuiCond_Appearing; // only first window can be moved
			else flagCond = ImGuiCond_Always; // Others are locked

			ImGui::SetNextWindowPos(ImVec2(rShape.get().getX(), rShape.get().getY()), flagCond);
			//ImGui::SetNextWindowSize(ImVec2(rShape.get().getWidth(), rShape.get().getHeight()), flagCond);

			bool bSize = false;//TODO:
			if (bSize) ImGui::SetNextWindowSize(ImVec2(rShape.get().getWidth(), rShape.get().getHeight()), flagCond);
		}

		ofRectangle getRectangle() const
		{
			return rShape.get();
		}

		glm::vec2 getPosition() const
		{
			return glm::vec2(rShape->x, rShape->y);
		}

		float getWidth() const
		{
			return rShape->getWidth();
		}

		void setPosition(glm::vec2 pos)
		{
			rShape->x = pos.x;
			rShape->y = pos.y;
		}

		void setRectangle(ofRectangle r)
		{
			rShape = r;
		}
	};

	//--------------------------------------------------------------
	class WindowPanels {

	public:

		ofParameter<bool> bHeaders{ "Hide Headers", true };
		ofParameter<bool> bEnable{ "Enable", true };

	private:

		ofParameter<bool> bLockedWidth{ "Lock Width", false };
		float width_max = 0;

		std::vector<WindowPanel> panels; // all the added panels

	private:

		std::vector<int> panelsQueue; // just the enabled (visible) panels
		ofParameter<int> counterQueue{ "counterQueue", 0, 0, 0 }; // count how many visible/queued

		ofParameterGroup params_Enablers{ "Enablers" };
		ofParameterGroup params_Settings{ "WindowsSettings" };

		// Cascade orientation
		enum wOrientation
		{
			W_HORIZ = 0,
			W_VERT,
			W_COUNT
		};
		wOrientation orientation;
		ofParameter<int> iOrientation{ "Orient", 0, 0, W_COUNT - 1 };
		std::vector<string> sOrientation{ "HORIZONTAL", "VERTICAL" };
		ofParameter<int> pad{ "Pad", 0, 0, 20 };

		ofParameter<glm::vec2> position{ "position", glm::vec2(10,10), glm::vec2(0,0), glm::vec2(1920,1080) };

		//--

	public:

		WindowPanels::WindowPanels()
		{
			ofAddListener(params_Enablers.parameterChangedE(), this, &WindowPanels::Changed_Params);

			counterQueue.addListener(this, &WindowPanels::Changed_counterQueue);
		}

		WindowPanels::~WindowPanels()
		{
			ofRemoveListener(params_Enablers.parameterChangedE(), this, &WindowPanels::Changed_Params);

			if (panelsQueue.size() == 0 || panels.size() == 0) return;
			int id = panelsQueue[0];
			position.set(panels[id].getPosition());

			ofxImGuiSurfing::saveGroup(params_Settings);
		}

	private:

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

		void Changed_Params(ofAbstractParameter &e)
		{
			std::string name = e.getName();
			//ofLogNotice() << __FUNCTION__ << " " << name << " : " << e;

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

		void checkWidthMax()
		{
			if (ofGetFrameNum() < 2) return;

			if (bLockedWidth) {
				ImGui::SetNextWindowSize(ImVec2(width_max, 0));
			}
		}

		void initiate()
		{
			ofLogNotice() << __FUNCTION__;

			params_Settings.add(position);
			params_Settings.add(pad);
			params_Settings.add(iOrientation);
			params_Settings.add(bLockedWidth);
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

			ofxImGuiSurfing::loadGroup(params_Settings);

			if (panelsQueue.size() == 0 || panels.size() == 0) return;
			int id = panelsQueue[0];
			panels[id].setPosition(position.get());

			bLockedWidth = bLockedWidth;
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

		void getState(int i)
		{
			panels[i].getState();
		}

		void runState(int i)
		{
			panels[i].runState();
		}

	public:

		void beginWindow(string name, bool *bOpen = NULL, ImGuiWindowFlags flags = ImGuiWindowFlags_None)
		{
			ImGui::Begin(name.c_str(), bOpen, flags);
		}

		void drawWidgets()
		{
			ofxImGuiSurfing::AddToggleRoundedButtonNamed(bEnable, ImVec2(-1, -1));
			if (bEnable)
			{
				for (auto &p : panels)
				{
					ofxImGuiSurfing::AddBigToggle(p.bEnable, ImVec2(-1, -1));
				}

				ImGui::Spacing();

				{
					float _h = getWidgetsHeight();
					float _w1 = getWidgetsWidth(1);
					float _w2 = getWidgetsWidth(2);
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

			// Controls
			{
				static bool bOpen = false;
				ImGuiColorEditFlags _flagw = (bOpen ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);
				if (ImGui::CollapsingHeader("SETTINGS", _flagw))
				{
					ImGui::PushItemWidth(getPanelWidth() * 0.5f);
					ofxImGuiSurfing::AddIntStepped(pad);
					ofxImGuiSurfing::AddParameter(bHeaders);
					ofxImGuiSurfing::AddParameter(bLockedWidth);
					ofxImGuiSurfing::AddCombo(iOrientation, sOrientation);
					ofxImGuiSurfing::AddParameter(iOrientation);
					ImGui::PopItemWidth();
				}

				ImGui::Spacing();
			}

			//-

			static ofParameter<bool> bDebug{ "Debug", false };
			ofxImGuiSurfing::AddToggleRoundedButton(bDebug);
			ImGui::Spacing();
			if (bDebug)
			{
				ImGui::Indent();
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
				ss3 += "amnt ";
				ss3 += ofToString(panelsQueue.size());
				ImGui::TextWrapped(ss3.c_str());
				ImGui::Spacing();
				ImGui::Unindent();
			}
		}

		void endWindow()
		{
			ImGui::End();

			doSetWindowsPositions();
		}

	private:

		void doRepositione()
		{
			//TODO:
			return;

			ofLogNotice() << __FUNCTION__ << " " << position.get();
			if (panelsQueue.size() == 0 || panels.size() == 0) return;
			int id = panelsQueue[0];
			panels[id].setPosition(position.get());
		}

		void doSetWindowsPositions()
		{
			if (panelsQueue.size() == 0 || panels.size() == 0) return;

			ofRectangle rCurr;
			ofRectangle rNext;

			//-

			// All windows with the same max width
			if (bLockedWidth)
			{
				for (int i = 0; i < panelsQueue.size(); i++)
				{
					int id = panelsQueue[i];
					rCurr = panels[id].getRectangle();
					if (width_max < rCurr.getWidth()) width_max = rCurr.getWidth();
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
