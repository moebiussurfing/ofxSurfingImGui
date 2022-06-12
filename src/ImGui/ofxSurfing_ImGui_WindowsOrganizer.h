
#pragma once

#include "ofMain.h"

#include "ofxImGui.h"
#include "ofxSurfing_ImGui_LayoutHelpers.h"
#include "ofxSurfing_ImGui_ofHelpers.h"

/*

	TODO:

	+ remake to avoid weird flickering on hidding some.
	+ fix re position when closed first queued window.
	+ add addon mode: queue windows (bGui) sorted.
		linked mode will handle the sort priority.
	+ store sorting queue ?

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
		void getShapeState()
		{
			rShape = ofRectangle(
				ImGui::GetWindowPos().x,
				ImGui::GetWindowPos().y,
				ImGui::GetWindowWidth(),
				ImGui::GetWindowHeight());
		}

	public:

		ofParameter<bool> bGui{ "bGui", true };
		ofParameter<ofRectangle> rShape{ "rShape", ofRectangle(0,0,0,0), ofRectangle(0,0,0,0), ofRectangle(1920,1080,1920,1080) };
		ofParameter<int> indexPos{ "IndexPos", -1, -1, 0 };
		int id = -1; // -1 is for not visible ?. or its position on the queue / window from left to right

	public:

		//--------------------------------------------------------------
		ofRectangle getShape() const
		{
			return rShape.get();
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
		float getHeight() const
		{
			return rShape->getHeight();
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

			//-

			params_User.clear();
			params_User.add(bGui_WindowsSpecials);
			params_User.add(bGui_ShowAll);
			params_User.add(bLinkedWindowsSpecial);
			params_User.add(bOrientation);
			params_User.add(orientation_Index);//?
			params_User.add(bAlignShapes);
			params_User.add(bHeaders);
			params_User.add(pad);
			params_User.add(position_Anchor);
			params_User.add(bAlignWindowsY);
			params_User.add(bAlignWindowsX);
			params_User.add(bAlignWindowsCascade);
			params_User.add(bAlignWindowsReset);

			// exclude
			orientation_Index.setSerializable(false);
			bAlignWindowsY.setSerializable(false);
			bAlignWindowsX.setSerializable(false);
			bAlignWindowsCascade.setSerializable(false);
			bAlignWindowsReset.setSerializable(false);
		}

		//--------------------------------------------------------------
		~WindowPanels()
		{
			ofRemoveListener(params_Enablers.parameterChangedE(), this, &WindowPanels::Changed_Params_Enablers);
			ofRemoveListener(params.parameterChangedE(), this, &WindowPanels::Changed_Params);

			// Save
			ofxImGuiSurfing::saveGroup(params_Settings, path_Settings);
		}

		ofParameter<bool> bDebug{ "Debug", false };

		//--

		//TODO:
		// this is taken from ofxSurfingPresets
		enum surfingAlignMode
		{
			SURFING_ALIGN_HORIZONTAL = 0,
			SURFING_ALIGN_VERTICAL
		};
		surfingAlignMode modeAlignWindows = SURFING_ALIGN_HORIZONTAL;

		//--------------------------------------------------------------
		void doAlignWindowsY()
		{
			ofLogNotice(__FUNCTION__);

			ImGuiContext* GImGui = ImGui::GetCurrentContext();
			ImGuiContext& g = *GImGui;

			float _yMin = 1080; // store the more hight/upper, lower y window coordinate

			ImVector<ImGuiWindow*> windows;
			for (ImGuiWindow* window : g.WindowsFocusOrder)
			{
				if (window->WasActive)
				{
					windows.push_back(window);

					// get the more top window y coord
					if (window->Pos.y < _yMin) _yMin = window->Pos.y;
				}
			}

			//--

			if (windows.Size > 0)
			{
				for (int n = 0; n < windows.Size; n++)
				{
					ImVec2 pos;
					pos = windows[n]->Pos;
					pos.y = _yMin;
					windows[n]->Pos = pos;
				}
			}
		}

		//--------------------------------------------------------------
		void doAlignWindowsX()
		{
			ofLogNotice(__FUNCTION__);

			ImGuiContext* GImGui = ImGui::GetCurrentContext();
			ImGuiContext& g = *GImGui;

			float _xMin = 1920; // store the more hight/upper, lower y window coordinate

			ImVector<ImGuiWindow*> windows;
			for (ImGuiWindow* window : g.WindowsFocusOrder)
			{
				if (window->WasActive)
				{
					windows.push_back(window);

					// get the more top window x coord
					if (window->Pos.x < _xMin) _xMin = window->Pos.x;
				}
			}

			//--

			if (windows.Size > 0)
			{
				for (int n = 0; n < windows.Size; n++)
				{
					ImVec2 pos;
					pos = windows[n]->Pos;
					pos.x = _xMin;
					windows[n]->Pos = pos;
				}
			}
		}

		//--

	public:

		ofParameter<bool> bGui_WindowsSpecials{ "ORGANIZER", true }; // toggle gui to draw main window.
		ofParameter<bool> bGui_ShowAll{ "SHOW GLOBAL", true }; // extra global toggle to hide / show all the queued windows.

		ofParameter<bool> bAlignWindowsX{ "AlignX", false };
		ofParameter<bool> bAlignWindowsY{ "AlignY", false };
		ofParameter<bool> bAlignWindowsCascade{ "Cascade", false };
		ofParameter<bool> bAlignWindowsReset{ "Reset",false };

		ofParameter<bool> bLinkedWindowsSpecial{ "LINK",  false };
		ofParameter<bool> bOrientation{ "Orientation", false };
		ofParameter<bool> bAlignShapes{ "Align Shapes",  true };
		ofParameter<bool> bHeaders{ "Headers", true };
		ofParameter<int> pad{ "Pad", 0, 0, 25 };
		ofParameter<glm::vec2> position_Anchor{ "Position Anchor", glm::vec2(10,10), glm::vec2(0,0), glm::vec2(1920,1080) };

		//--

	public:

		//--------------------------------------------------------------
		bool isIntitiated() {
			return windowsSpecialsOrganizer.size() > 0;
		}

	private:

		bool bDISABLE_CALLBACKS = true;

		ofParameter<bool> bLockedWidth{ "Lock Width", false };
		ofParameter<bool> bLockedHeight{ "Lock Height", false };

		float width_max = 0;
		float height_max = 0;

		std::vector<WindowPanel> windowsSpecialsOrganizer; // all the added panels. hidden windows are not removed from here!
		std::string path_Global = "";
		std::string path_Settings = "_WindowsSpecial.json";

	public:

		//--------------------------------------------------------------
		void setPath(std::string path)
		{
			path_Global = path;
			ofxSurfingHelpers::CheckFolder(path_Global);
			path_Settings = path_Global + "guiManager_" + params_Settings.getName() + ".json";
		}

	private:

		// just the enabled (visible) panels (not all the added panels). hidden windows are removed from here!
		std::vector<int> queueWindowsVisible;

		ofParameterGroup params_Enablers{ "Enablers" };
		ofParameterGroup params_Settings{ "WindowsSpecials" };
		ofParameterGroup params{ "Params" }; // for callbacks only

		// Cascade orientation
		enum wOrientation
		{
			W_HORIZ = 0,
			W_VERT,
			W_COUNT
		};
		wOrientation orientation;
		ofParameter<int> orientation_Index{ "Orient", 0, 0, W_COUNT - 1 };
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
		void Changed_Params(ofAbstractParameter& e)
		{
			if (bDISABLE_CALLBACKS) return;

			std::string name = e.getName();

			ofLogVerbose(__FUNCTION__) << " " << name << " : " << e;

			//-

			if (0) {}

			//--

			//else if (name == position_Anchor.getName())
			//{
			//	// Position linked to first queued window
			//	if (queueWindowsVisible.size() == 0 || windowsSpecialsOrganizer.size() == 0) return;
			//	// get the index of the first window
			//	int id = queueWindowsVisible[0];
			//	windowsSpecialsOrganizer[id].setPosition(position_Anchor.get());
			//	doApplyLinkWindows();
			//}

			//--

			// Align Shapes

			else if (name == bAlignShapes.getName())
			{
				//fix
				if (bAlignShapes)
				{
					bOrientation = bOrientation;
				}
			}

			//--

			// Align Windows Helpers

			else if (name == bAlignWindowsReset.getName() && bAlignWindowsReset)
			{
				bAlignWindowsReset = false;

				doAlignWindowsReset();
			}

			else if (name == bAlignWindowsCascade.getName() && bAlignWindowsCascade)
			{
				bAlignWindowsCascade = false;

				doAlignWindowsCascade();
			}

			//--

			else if (name == bAlignWindowsY.getName() && bAlignWindowsY)
			{
				bAlignWindowsY = false;

				doAlignWindowsY();
			}

			else if (name == bAlignWindowsX.getName() && bAlignWindowsX)
			{
				bAlignWindowsX = false;

				doAlignWindowsX();
			}

			//--

			else if (name == orientation_Index.getName())
			{
				static int pre = -1;
				if (orientation_Index != pre) pre = orientation_Index;
				else return; // not changed then skip

				if (orientation_Index == 0) bOrientation.set(false);
				else bOrientation.set(true);

				//if (bAlignShapes)
				{
					if (orientation_Index == 0)
					{
						bLockedWidth = false;
						bLockedHeight = true;
					}
					else
					{
						bLockedWidth = true;
						bLockedHeight = false;
					}
				}
			}

			//--

			else if (name == bOrientation.getName())
			{
				if (!bOrientation) orientation_Index = 0;
				else orientation_Index = 1;
			}

			//--

			else if (name == pad.getName())
			{
			}

			//-

			////TODO: should recalculate..
			//else if (name == bHeaders.getName())
			//{
			//	doApplyLinkWindows();
			//}

			//-

			//else if (name == bGui_ShowAll.getName()) // global show
			//{
			//	// workaround 
			//	// to avoid bad dimension on startup
			//	bOrientation = bOrientation;
			//}
		}

		//--

		//--------------------------------------------------------------
		void Changed_Params_Enablers(ofAbstractParameter& e) // each window show toggle changed
		{
			if (windowsSpecialsOrganizer.size() == 0) return;

			if (bDISABLE_CALLBACKS) return;

			bDISABLE_CALLBACKS = true;

			std::string name = e.getName();

			ofLogNotice(__FUNCTION__) << " " << name << " : " << e;

			//--			

			// Check toggle enablers

			// Iterate (all) unsorted and some may hidden windows!

			for (auto& p : windowsSpecialsOrganizer)
			{
				// A bGui toggle is pressed...
				// The toggles that are showers for each special window.
				// Check which one is changed (enabled or disabled)

				if (p.bGui.getName() == name)
				{
					ofLogNotice(__FUNCTION__) << " id:" << p.id
						<< " indexPos:" << p.indexPos << " bGui:" << (p.bGui.get() ? "TRUE" : "FALSE");

					//--

					// Just ENABLED / Add 

					if (p.bGui)
					{
						if (p.indexPos == -1)
						{
							// It was hidden. Now will be queued and visible at end of the queue!
							// put new window at end of the queue
							queueWindowsVisible.push_back(p.id); // which one (from the full queue with all visible or not) is it
							p.indexPos = queueWindowsVisible.size() - 1; // get last index/size

							doReOrganize();//not required?

							//TODO:
							doApplyLinkWindows();

							bDISABLE_CALLBACKS = false;

							return;
						}
						else
						{
							ofLogError(__FUNCTION__) << "Should not be indexPos -1 for the window " << p.id << " that was hidden until now";

							bDISABLE_CALLBACKS = false;

							//TODO:
							doReOrganize();
							doApplyLinkWindows();

							return;
						}
					}

					//--

					// Just DISABLED / Remove

					//if (!p.bGui)
					else
					{
						if (p.indexPos == -1)
						{
							ofLogError(__FUNCTION__) << "Should not be -1 ... if " << p.id << " was enabled until now";

							bDISABLE_CALLBACKS = false;

							//TODO:
							doReOrganize();
							doApplyLinkWindows();

							return;
						}

						//--

						else
						{
							// Warn if it's the first window to force sort / re arrange!
							// The currently hidded window is the first!

							if (p.indexPos == 0)
							{
								ofLogWarning() << (__FUNCTION__) << "Closing First! Window ID " << p.id;

								// Remove the window from the queue, from the position where it was:
								queueWindowsVisible.erase(queueWindowsVisible.begin());

								if (queueWindowsVisible.size() != 0)
								{
									//TODO:
									int id = queueWindowsVisible[0]; // get the index of first window
									windowsSpecialsOrganizer[id].setPosition(position_Anchor.get());
								}

								p.indexPos = -1; // mark as not visible/hidden
							}

							//--

							// The hidded window is not the first!

							else
							{
								//// Remove the window from the queue, from the position where it was:
								//if (p.indexPos != -1) queueWindowsVisible.erase(queueWindowsVisible.begin());
								//else queueWindowsVisible.erase(queueWindowsVisible.begin() + p.indexPos);
								queueWindowsVisible.erase(queueWindowsVisible.begin() + p.indexPos);

								p.indexPos = -1; // mark as not visible/hidden
							}

							//--

							// We must update all the positions indexes bc we removed one element!
							doReOrganize();

							//TODO:
							doApplyLinkWindows();

							bForceNext = true;

							//--

							bDISABLE_CALLBACKS = false;

							return;
						}
					}
				}
			}

			bDISABLE_CALLBACKS = false;
		}

		//--------------------------------------------------------------
		void doReOrganize()
		{
			ofLogNotice(__FUNCTION__);

			if (queueWindowsVisible.size() == 0 || windowsSpecialsOrganizer.size() == 0) return;

			//--

			// Reorganize sorting indexes

			// 1. Disable all

			for (int i = 0; i < windowsSpecialsOrganizer.size(); i++)
			{
				windowsSpecialsOrganizer[i].indexPos = -1;
				windowsSpecialsOrganizer[i].bGui.setWithoutEventNotifications(false);
			}

			//--

			// 2. Iterate each item of the queue and set the current position index

			for (int i = 0; i < queueWindowsVisible.size(); i++)
			{
				int id = queueWindowsVisible[i];

				windowsSpecialsOrganizer[id].indexPos = i;
				windowsSpecialsOrganizer[id].bGui.setWithoutEventNotifications(true);
			}
		}

		//--

	public:

		//--------------------------------------------------------------
		void doAlignWindowsReset()
		{
			ofLogNotice(__FUNCTION__);

			ImGuiContext* GImGui = ImGui::GetCurrentContext();
			ImGuiContext& g = *GImGui;
			ImVector<ImGuiWindow*> windows;

			struct myWin {
				ImVec2 pos;
				ImVec2 sz;
				int id;
				string name;
				ImGuiWindow* ImWin;
			};

			struct myclass {
				bool operator() (myWin w1, myWin w2) { return (w1.pos.x < w2.pos.x); }
			} myobject;

			vector<myWin> myWins;

			int _id = 0;
			for (ImGuiWindow* window : g.WindowsFocusOrder)
			{
				if (window->WasActive)
				{
					myWin w;
					w.ImWin = window;
					w.pos = window->Pos;
					w.sz = window->Size;
					w.name = window->Name;
					w.id = _id++;
					myWins.push_back(w);
				}
			}
			if (myWins.size() == 0) return; // skip

			// Sort, the more lefted window will be used as anchor!
			std::sort(myWins.begin(), myWins.end(), myobject);

			float w = myWins[0].sz.x;
			float h = myWins[0].sz.y;

			//anchor
			float x = myWins[0].pos.x + w + pad;
			float y = myWins[0].pos.y;

			for (int i = 1; i < myWins.size(); i++)
			{
				myWins[i].ImWin->Pos.x = x;
				myWins[i].ImWin->Pos.y = y;

				w = myWins[i].sz.x;
				x = x + w + pad;
			}
		}

		//--------------------------------------------------------------
		void doAlignWindowsCascade()
		{
			ofLogNotice(__FUNCTION__);

			float _padx = 117;
			float _pady = 25;

			//--

			ofLogNotice(__FUNCTION__);
			ImGuiContext* GImGui = ImGui::GetCurrentContext();
			ImGuiContext& g = *GImGui;
			ImVector<ImGuiWindow*> windows;

			struct myWin {
				ImVec2 pos;
				ImVec2 sz;
				int id;
				string name;
				ImGuiWindow* ImWin;
			};

			struct myclass {
				bool operator() (myWin w1, myWin w2) { return (w1.pos.x < w2.pos.x); }
			} myobject;

			vector<myWin> myWins;

			int _id = 0;
			for (ImGuiWindow* window : g.WindowsFocusOrder)
			{
				if (window->WasActive)
				{
					myWin w;
					w.ImWin = window;
					w.pos = window->Pos;
					w.sz = window->Size;
					w.name = window->Name;
					w.id = _id++;
					myWins.push_back(w);
				}
			}
			if (myWins.size() == 0) return; // skip

			// Sort, the more lefted window will be used as anchor!
			std::sort(myWins.begin(), myWins.end(), myobject);

			float diffx = pad + _padx;
			float diffy = pad + _pady;

			// anchor
			float x = myWins[0].pos.x + diffx;
			float y = myWins[0].pos.y + diffy;

			for (int i = 1; i < myWins.size(); i++)
			{
				myWins[i].ImWin->Pos.x = x;
				myWins[i].ImWin->Pos.y = y;

				x = x + diffx;
				y = y + diffy;

				//// Focus sorted..
				//string n = myWins[i].name;
				//ImGui::Begin(n.c_str());
				FocusWindow(myWins[i].ImWin);
				//ImGui::End();
			}
		}

		//--

	public:

		//--------------------------------------------------------------
		void add(ofParameter<bool>& e) // add Special Windows / panels on setup!
		{
			ofLogNotice(__FUNCTION__) << e.getName();

			params_Enablers.add(e);

			////TODO:
			////better pointers
			//WindowPanel p;
			//windowsSpecialsOrganizer.push_back(p);
			//windowsSpecialsOrganizer.back().id = windowsSpecialsOrganizer.size();
			//windowsSpecialsOrganizer.back().pos = -1;
			//windowsSpecialsOrganizer.back().bGui.makeReferenceTo(e);

			WindowPanel p;

			p.id = windowsSpecialsOrganizer.size(); // which special window is
			p.indexPos = -1; // what position on visible windows queue. -1 = hidden
			p.bGui.makeReferenceTo(e); // is visible

			windowsSpecialsOrganizer.push_back(p);
		}

	public:

		//--------------------------------------------------------------
		void doAlignShapesNextWindow()//must be called using runShapeState, called on begin() phase!
		{
			//ofLogNotice(__FUNCTION__);

			if (ofGetFrameNum() == 1) return;//skip first frame to be sure that it's prepared.
			if (!bAlignShapes) return;//skip.

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
		void setupInitiate()
		{
			ofLogNotice(__FUNCTION__);

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

			//--

			// To get notified by the callbacks
			params.add(params_User);

			//--

			// To store session settings

			params_Settings.add(params_User);

			// Each window enabler will be added here..
			// all of theme has been added during setup
			params_Settings.add(params_Enablers);

			//--

			startup();
		}

		//--------------------------------------------------------------
		void startup()
		{
			ofLogNotice(__FUNCTION__);

			bDISABLE_CALLBACKS = false;

			//--

			// Load Settings
			ofxImGuiSurfing::loadGroup(params_Settings, path_Settings);


			//--

			if (queueWindowsVisible.size() == 0 || windowsSpecialsOrganizer.size() == 0)
			{
			}
			else
			{
				// Position linked to first queued window
				int id = queueWindowsVisible[0];
				windowsSpecialsOrganizer[id].setPosition(position_Anchor.get());
			}

			//--

			// fixes
			//bOrientation = bOrientation;
			//bLockedWidth = bLockedWidth;
			//bLockedHeight = bLockedHeight;
			//bAlignShapes = bAlignShapes;
			//bAlignShapes_PRE = bAlignShapes;
			//bAlignShapes = !bAlignShapes;

			//--

			////TODO:
			//doReOrganize();

			//TODO:
			if (bLinkedWindowsSpecial) doApplyLinkWindows();
		}

		//--
	private:
		bool bForceNext = false; // workaround required / to be used when hidding first window!

	public:

		//--------------------------------------------------------------
		void getShapeState(int i)
		{
			windowsSpecialsOrganizer[i].getShapeState();
		}

		//--------------------------------------------------------------
		void runShapeState(int i) // To be effective, must be called just before begin()!
		{
			ofRectangle r = windowsSpecialsOrganizer[i].getShape();

			ImGuiCond flagCond;

			int id = queueWindowsVisible[0]; // get the index of first window

			// force engine
			bool bforce = false;
			if (bForceNext)
			{
				bForceNext = false;
				bforce = true;
			}

			if (bforce)
			{
				////TODO:
				//// workaround
				//float x = position_Anchor.get().x;
				//float y = position_Anchor.get().y;
				//glm::vec2 p = glm::vec2(x, y);
				//windowsSpecialsOrganizer[id].setPosition(p);

				flagCond = ImGuiCond_Always;
			}
			else
			{
				if (i == id) // first window is free
				{
					flagCond = ImGuiCond_Appearing;
				}
				else // other windows are locked
				{
					flagCond = ImGuiCond_Always;
					//flagCond = ImGuiCond_None;
				}
			}

			// Position
			ImGui::SetNextWindowPos(ImVec2(r.getX(), r.getY()), flagCond);

			// Shape
			doAlignShapesNextWindow();
		}

	public:

		//--------------------------------------------------------------
		void setNameWindowsSpecialsEnableGlobal(std::string name) {
			bGui_ShowAll.setName(name);
		}

		//--------------------------------------------------------------
		void drawWidgetsAlignHelpers(bool bMinimized = false)
		{
			ofxImGuiSurfing::AddSpacing();
			ofxImGuiSurfing::AddBigButton(bAlignWindowsReset);
			ofxImGuiSurfing::AddSmallButton(bAlignWindowsCascade);

			if (!bMinimized) {
				float h = ofxImGuiSurfing::getWidgetsHeightUnit();
				float w2 = ofxImGuiSurfing::getWidgetsWidth(2);
				ofxImGuiSurfing::AddSmallButton(bAlignWindowsY, ImVec2(w2, h));
				ImGui::SameLine();
				ofxImGuiSurfing::AddSmallButton(bAlignWindowsX, ImVec2(w2, h));
			}
		}

		//--------------------------------------------------------------
		void drawWidgetsOrganizer(bool bMinimized = false)
		{
			float _h = getWidgetsHeight();
			float _w1 = getWidgetsWidth(1);
			float _w2 = getWidgetsWidth(2);

			// Enable
			ofxImGuiSurfing::AddBigToggle(bLinkedWindowsSpecial);

			ofxImGuiSurfing::AddSpacing();

			if (bLinkedWindowsSpecial)
			{
				// Orientation
				string ss = bOrientation ? "Vertical" : "Horizontal";
				float h = 1.25 * ImGui::GetFrameHeight();
				float w = h * 1.55f;

				ofxImGuiSurfing::AddToggleRoundedButton(bOrientation, ss, ImVec2(w, h));
				ofxImGuiSurfing::AddToggleRoundedButton(bAlignShapes);

				ImGui::Spacing();
			}

			ofxImGuiSurfing::AddSpacingSeparated();

			if (ImGui::CollapsingHeader("ALIGNERS"))
			{
				drawWidgetsAlignHelpers();
			}

			//-

			{
				// Windows

				if (!bHideWindows)
				{
					ofxImGuiSurfing::AddSpacingSeparated();

					ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
					//ImGuiColorEditFlags _flagw = (bDebug ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);

					if (ImGui::CollapsingHeader("WINDOWS", _flagw))
					{
						if (!bMinimized)
						{
							ImGui::Spacing();

							if (ImGui::Button("All", ImVec2(_w2, _h)))
							{
								for (auto& p : windowsSpecialsOrganizer) {
									p.bGui = true;
								}
							}
							ImGui::SameLine();
							if (ImGui::Button("None", ImVec2(_w2, _h)))
							{
								for (auto& p : windowsSpecialsOrganizer) {
									p.bGui = false;
								}
							}

						}

						ImGui::Spacing();

						//--

						// Global Enable 

						ofxImGuiSurfing::AddToggleRoundedButton(bGui_ShowAll);//medium

						if (bGui_ShowAll)
						{
							ImGui::Indent();
							for (auto& p : windowsSpecialsOrganizer)
							{
								ofxImGuiSurfing::AddToggleRoundedButton(p.bGui);
							}
							ImGui::Unindent();

							ImGui::Spacing();
						}
					}
				}

				//--

				// Settings

				if (!bMinimized)
				{
					// Controls
					{
						ofxImGuiSurfing::AddSpacingSeparated();

						ImGuiColorEditFlags _flagw = (bDebug ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);

						if (ImGui::CollapsingHeader("SETTINGS", _flagw))
						{
							ImGui::PushItemWidth(getPanelWidth() * 0.5f);
							{
								ofxImGuiSurfing::AddParameter(bHeaders);
								ofxImGuiSurfing::AddStepperInt(pad);
							}
							ImGui::PopItemWidth();

							//--

							ofxImGuiSurfing::AddSpacingSeparated();

							// Debug

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
								ImGui::TextWrapped("SPECIAL WINDOWS \n");
								ofxImGuiSurfing::AddSpacingSeparated();
								ImGui::Spacing();

								// Anchor
								std::string ss4 = "";
								ss4 += "Anchor \n\n";
								ss4 += ofToString(position_Anchor.get());
								if (queueWindowsVisible.size() > 0) {
									int id = queueWindowsVisible[0]; // first visible windows acts as anchor!
									ss4 += "\n";
									ss4 += "" + ofToString(id);
								}

								ImGui::TextWrapped(ss4.c_str());
								ofxImGuiSurfing::AddSpacingSeparated();

								// Queue visible
								std::string ss2 = "Queue Visible \n\n";
								for (int i = 0; i < queueWindowsVisible.size(); i++)
								{
									if (i != 0) ss2 += ", ";
									ss2 += ofToString(queueWindowsVisible[i]);
								}
								ImGui::TextWrapped(ss2.c_str());
								ofxImGuiSurfing::AddSpacingSeparated();

								// All the panels
								std::string ss1 = "";
								int i = 0;
								for (auto& p : windowsSpecialsOrganizer)
								{
									ss1 += "" + ofToString(i) + "";
									ss1 += "\n";
									ss1 += "" + ofToString(p.bGui ? "ON" : "OFF");
									ss1 += "\n";
									//ss1 += "id_" + ofToString(p.id) + " ";
									//ss1 += "pos_" + ofToString(p.indexPos);
									//ss1 += "\n";
									ss1 += ofToString(p.getRectangle());
									ss1 += "\n\n";

									i++;
								}
								ImGui::TextWrapped(ss1.c_str());
								ofxImGuiSurfing::AddSpacingSeparated();

								// Windows
								std::string ss5 = "All Windows \n\n";
								for (int i = 0; i < windowsSpecialsOrganizer.size(); i++)
								{
									if (i != 0) ss5 += ", ";
									ss5 += ofToString(windowsSpecialsOrganizer[i].id);
								}
								ImGui::TextWrapped(ss5.c_str());
								ofxImGuiSurfing::AddSpacingSeparated();

								ss1 = "Callbacks " + ofToString(bDISABLE_CALLBACKS ? "OFF" : "ON");
								ImGui::TextWrapped(ss1.c_str());

								ImGui::Unindent();
							}
						}
					}
				}
			}
		}

		//--

	public:

		//--------------------------------------------------------------
		void update()
		{
			//--

			// Skip
			if (queueWindowsVisible.size() == 0 || windowsSpecialsOrganizer.size() == 0)
			{
				//TODO:
				// workaround 
				// to solve that sometimes hidding/showing windows are translated to the right..
				// force to improve when showing back 
				for (size_t i = 0; i < windowsSpecialsOrganizer.size(); i++)
				{
					windowsSpecialsOrganizer[i].setPosition(position_Anchor.get());
				}

				return;
			}

			//--

			// Read 1st queued position to the anchor
			// Required to allow move first window by the user!
			//TODO: we could allow to move all windows with another engine..
			int id = queueWindowsVisible[0];
			glm::vec2 p = windowsSpecialsOrganizer[id].getPosition();
			position_Anchor.setWithoutEventNotifications(p);

			//--

			// Update / Apply all links to windows
			if (bLinkedWindowsSpecial) doApplyLinkWindows();
		}

		//--

	private:

		//--------------------------------------------------------------
		void doApplyLinkWindows() // set the position for all visible windows
		{
			if (queueWindowsVisible.size() == 0 || windowsSpecialsOrganizer.size() == 0) return;

			//--

			// 1. All windows with the same max width

			// Take measures to apply on next doAlignShapesNextWindow() call!

			if (bLockedWidth || bLockedHeight)
			{
				for (int i = 0; i < queueWindowsVisible.size(); i++)
				{
					int id = queueWindowsVisible[i];
					ofRectangle r = windowsSpecialsOrganizer[id].getRectangle();

					// measure maxims w/h from all the windows to align shapes!
					if (bLockedWidth) if (width_max < r.getWidth()) width_max = r.getWidth();
					if (bLockedHeight) if (height_max < r.getHeight()) height_max = r.getHeight();
				}
			}

			//--

			// 2. Position all the visible windows

			float x = 0;
			float y = 0;
			float w = 0;
			float h = 0;

			glm::vec2 p(x, y);

			int id = 0;

			for (int i = 0; i < queueWindowsVisible.size(); i++)
			{
				id = queueWindowsVisible[i]; // the original id of each window

				// first visible windows acts as anchor!
				if (i == 0)
				{
					x = position_Anchor.get().x;
					y = position_Anchor.get().y;
				}
				p = glm::vec2(x, y);
				windowsSpecialsOrganizer[id].setPosition(p);

				//--

				if (orientation_Index == W_HORIZ)
				{
					w = windowsSpecialsOrganizer[id].getWidth();
					x = x + w + pad;
				}
				else if (orientation_Index == W_VERT)
				{
					h = windowsSpecialsOrganizer[id].getHeight();
					y = y + h + pad;
				}
			}
		}
	};
}
