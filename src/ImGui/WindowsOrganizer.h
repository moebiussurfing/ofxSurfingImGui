#pragma once

#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators
#include "imgui_internal.h"
#include "ofxImGui.h"

#include "LayoutHelpers.h"
#include "ofHelpers.h"

#include "WindowPanel.h"

/*

	TODO:

	+ improve disabling stuff (ie: update listener) when special windows are not used.
	+ make that a window can be master.
		then always at first position.
		re sorting to first when appears.
	+ fix bug crash when closing windows using the x.
	+ store sorting queue ?
	+ enable moving from all panels.

*/


using namespace ofxImGuiSurfing;
//using namespace ofxSurfingHelpers;

//----

namespace ofxImGuiSurfing
{
	//--------------------------------------------------------------

	// Container Manager for all the manager special windows to handle.

	class WindowsOrganizer
	{
	public:
		//--------------------------------------------------------------
		WindowsOrganizer()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::Constructor";

			ofAddListener(params_WindowsPanels.parameterChangedE(), this, &WindowsOrganizer::Changed_WindowsPanels);
			ofAddListener(params_Controls.parameterChangedE(), this, &WindowsOrganizer::Changed_Settings);
			ofAddListener(params_Callbacks.parameterChangedE(), this, &WindowsOrganizer::Changed_Callbacks);

#ifdef SURFING_IMGUI__CREATE_EXIT_LISTENER
			//TODO: 
			// Fix exit exceptions on RF..
			int minValue = std::numeric_limits<int>::min();
			ofAddListener(ofEvents().exit, this, &WindowsOrganizer::exit, minValue);
#endif

			//--

			// Exclude
			bAlignWindowsY.setSerializable(false);
			bAlignWindowsX.setSerializable(false);
			bAlignWindowsCascade.setSerializable(false);
			bAlignWindowsReset.setSerializable(false);

			//path_Global = nameLabel + SURFING_IMGUI__DEFAULT_PATH_GLOBAL + ofToString("/");
			setPathGlobal(path_Global);
		}

		//--------------------------------------------------------------
		~WindowsOrganizer()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::Destructor!";

			ofRemoveListener(params_WindowsPanels.parameterChangedE(), this, &WindowsOrganizer::Changed_WindowsPanels);
			ofRemoveListener(params_Controls.parameterChangedE(), this, &WindowsOrganizer::Changed_Settings);
			ofRemoveListener(params_Callbacks.parameterChangedE(), this, &WindowsOrganizer::Changed_Callbacks);

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_EXIT
			if (!bDoneExit)
			{
				exit();

				ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) << "Forced exit() in destructor!";
				ofLogWarning("ofxSurfingImGui") << (__FUNCTION__) << "exit() was not called yet...";
			}
			else
			{
				ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) <<
					"Succesfully omitted calling exit() in destructor. It was already done!";
			}
#endif
		}

		//--

	public:
		// Subscribed after app
#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES
		//--------------------------------------------------------------
		void update()
		{
			//ofLogNotice("ofxSurfingImGui") << (__FUNCTION__);
			//if (!bDoneStartupDelayed) return;

			if (bFlagSaveSettings) {
				bFlagSaveSettings = false;
				saveSettings();
			}
		}
#endif

		//--

	private:
		bool bDoneExit = false;

#ifdef SURFING_IMGUI__CREATE_EXIT_LISTENER
		//--------------------------------------------------------------
		void exit(ofEventArgs& e)
		{
			ofLogNotice("ofxSurfingImGui") << (__FUNCTION__) << "exit(ofEventArgs& e)";

			exit();
		}
#endif

	private:
		//--------------------------------------------------------------
		void exit()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::exit()";

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_EXIT
			saveSettings();
#endif

			bDoneExit = true;
		}

	private:
#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES
		bool bFlagSaveSettings = false;
#endif

	public:
		ofParameter<bool> bEnableFileSettings{ "EnableSettings", true };
		//private:
			//bool bEnableFileSettings = true;
			////--------------------------------------------------------------
			//void setEnableFileSettings(bool b)
			//{
			//	// must call before setup. IMPORTANT: if you are using multiple instances of this add-on, must set only one to true or settings will not be handled correctly!
			//	bEnableFileSettings = b;
			//}

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES
		//--------------------------------------------------------------
		void saveSettingsFlag()
		{
			bFlagSaveSettings = true;
		}
#endif
		//--------------------------------------------------------------
		void saveSettings()
		{
			if (!bEnableFileSettings) return;

			if (bDoneInitialized)
			{
				ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::saveSettings()";

				// Save
				saveGroup(params_AppSettings, path_Settings, false);
			}
			else
			{
				ofLogWarning("ofxSurfingImGui") << "WindowsOrganizer::saveSettings() Skipped Saving settings";
				ofLogWarning("ofxSurfingImGui") << "WindowsOrganizer::saveSettings() bDoneInitialized was unexpectedly false!";
			}
		}

		//--------------------------------------------------------------
		void resetSettings()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::resetSettings()";

			bLinked = false;
			bOrientation = false;
			bAlignShapes = true;
			bAlignShapesX = true;
			bAlignShapesY = false;
			bHeaders = true;
			pad = 0;
		}

		//--------------------------------------------------------------
		void reset()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::reset()";

			bGui_Organizer = false;
			bGui_Aligners = false;
			bGui_SpecialWindows = false;

			// hide all windows
			for (auto& p : windowsPanels)
			{
				p.bGui = false;
			}

			resetSettings();
		}

		//--

	public:
		ofParameter<bool> bDebug{ "Debug", false };

		//--

		//TODO:
		// this is taken from ofxSurfingPresets
		enum SurfingAlignMode
		{
			SURFING_ALIGN_HORIZONTAL = 0,
			SURFING_ALIGN_VERTICAL
		};

		SurfingAlignMode modeAlignWindows = SURFING_ALIGN_HORIZONTAL;

		//--------------------------------------------------------------
		void doAlignWindowsY()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::doAlignWindowsY()";

			ImGuiContext* GImGui = ImGui::GetCurrentContext();
			ImGuiContext& g = *GImGui;

			float _yMin = 1000;
			// set an y max to bottom. store the more hight/upper, lower y window coordinate

			ImVector<ImGuiWindow*> windows;
			for (ImGuiWindow* window : g.WindowsFocusOrder)
			{
				if (window->WasActive)
				{
					string n = ofToString(window->Name);

					//TODO:
					// fails some windows?
					// skip "non named" windows. usually menus.
					const string prefix = "##";
					if (n.substr(0, prefix.size()) == prefix) continue;

					// skip log window (hardcoded name..)
					if ("LOG" == ofToString(window->Name)) continue;

					// skip: don't align the Organizer or Aligners Windows!
					if (bGui_Aligners.getName() == ofToString(window->Name)) continue;
					if (bGui_Organizer.getName() == ofToString(window->Name)) continue;
					if (bGui_SpecialWindows.getName() == ofToString(window->Name)) continue;

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
					// skip: don't align the Organizer or Aligners Windows!
					if (bGui_Aligners.getName() == ofToString(windows[n]->Name)) continue;
					if (bGui_Organizer.getName() == ofToString(windows[n]->Name)) continue;
					if (bGui_SpecialWindows.getName() == ofToString(windows[n]->Name)) continue;

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
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::doAlignWindowsX()";

			ImGuiContext* GImGui = ImGui::GetCurrentContext();
			ImGuiContext& g = *GImGui;

			float _xMin = 1920; // store the more hight/upper, lower y window coordinate

			ImVector<ImGuiWindow*> windows;
			for (ImGuiWindow* window : g.WindowsFocusOrder)
			{
				if (window->WasActive)
				{
					string n = ofToString(window->Name);

					//TODO:
					// fails some windows?
					// skip "non named" windows. usually menus.
					const string prefix = "##";
					if (n.substr(0, prefix.size()) == prefix) continue;

					// skip log window (hardcoded name..)
					if ("LOG" == ofToString(window->Name)) continue;

					// skip: don't align the Organizer or Aligners Windows!
					if (bGui_Aligners.getName() == ofToString(window->Name)) continue;
					if (bGui_Organizer.getName() == ofToString(window->Name)) continue;
					if (bGui_SpecialWindows.getName() == ofToString(window->Name)) continue;

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
					// skip: don't align the Organizer or Aligners Windows!
					if (bGui_Aligners.getName() == ofToString(windows[n]->Name)) continue;
					if (bGui_Organizer.getName() == ofToString(windows[n]->Name)) continue;
					if (bGui_SpecialWindows.getName() == ofToString(windows[n]->Name)) continue;

					ImVec2 pos;
					pos = windows[n]->Pos;
					pos.x = _xMin;
					windows[n]->Pos = pos;
				}
			}
		}

		//----

	public:
		// Link Organizer toggle
		ofParameter<bool> bGui_Organizer{ "ORGANIZER", false };

		// Aligners toggle
		ofParameter<bool> bGui_Aligners{"ALIGNERS", false};

		// Special Windows toggle
		ofParameter<bool> bGui_SpecialWindows{"SPECIAL WINDOWS", false};

		// Extra global toggle to hide / show all the queued special windows.
		ofParameter<bool> bGui_ShowWindowsGlobal{"_ShowWindows", true};

		//--

	public:
		//triggers
		ofParameter<bool> bAlignWindowsX{ "AlignX", false };
		ofParameter<bool> bAlignWindowsY{"AlignY", false};
		ofParameter<bool> bAlignWindowsCascade{"Cascade", false};
		ofParameter<bool> bAlignWindowsReset{"Reset", false};

		//will be linked as makeReferenceTo. So these names will be overwritten
		ofParameter<bool> bLinked{"LINK", false};
		ofParameter<bool> bOrientation{"Orientation", false}; // false=horizontal. true=vertical
		ofParameter<bool> bAlignShapes{"Align Shapes", true};
		ofParameter<bool> bAlignShapesX{"ShapesX", true};
		ofParameter<bool> bAlignShapesY{"ShapesY", false};
		ofParameter<bool> bHeaders{"Headers", true};
		ofParameter<int> pad{"Pad", 0, 0, 25};

		//TODO:
		ofParameter<glm::vec2> position_Anchor{"Position Anchor",
			glm::vec2(10, 10), glm::vec2(0, 0), glm::vec2(1920, 1080)};

		//--

	public:
		//--------------------------------------------------------------
		bool isInitiated()
		{
			return (windowsPanels.size() > 0 && bDoneInitialized);
		}

		//private:
		std::vector<WindowPanel> windowsPanels;
		// All the added panels. 
		// Hidden windows are not removed from here! 
		// Just will not be drawn. Will be hidden.

	private:
		bool bDISABLE_CALLBACKS = true;

		float width_max = 0;
		float height_max = 0;

		string path_Settings;
		string pathSuffix = "UI_Organizer.json";
		string path_Global = SURFING_IMGUI__DEFAULT_PATH_GLOBAL;
		string nameLabel = SURFING_IMGUI__DEFAULT_NAME_LABEL;

		bool bDoneInitialized = false;
		bool bDoneStartupDelayed = false;

	public:
		//--------------------------------------------------------------
		void setName(string _name)
		{
			this->nameLabel = _name;
		}

		//--------------------------------------------------------------
		void setPathGlobal(string path)
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::sePathGlobal:" << path;

			path_Global = path;
			path_Settings = path_Global + nameLabel + "_" + pathSuffix;
		}

	private:
		// Just the enabled (visible) panels (not all the added panels). 
		// Hidden windows are removed from here!
		std::vector<int> queueWindowsVisible;

		ofParameterGroup params_WindowsPanels{ "SpecialWindows" };
		ofParameterGroup params_AppSettings{ "Organizer" };

		bool bHideWindowsToggles = false; //-> To disable when using the full layout engine. 

	public:
		//--------------------------------------------------------------
		void setHideWindows(bool b)
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::setHideWindows:" << b;

			bHideWindowsToggles = b;

			if (bHideWindowsToggles)
			{
				bGui_ShowWindowsGlobal = true;
				bGui_ShowWindowsGlobal.setSerializable(false);
			}
		}

		//-

	private:
		ofParameterGroup params_Panels{ "Panels" }; // just to organize on the json file
		ofParameterGroup params_Callbacks{ "Callbacks" };

	public:
		ofParameterGroup params_Controls{ "Organizer Settings" }; // To use on a external GUI 

	public:
		//--------------------------------------------------------------
		ofParameterGroup& getParamsSettings()
		{
			return params_Controls;
		}

	private:
		//--------------------------------------------------------------
		void Changed_Settings(ofAbstractParameter& e)
		{
			//if (bDISABLE_CALLBACKS) return;

			string name = e.getName();

			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::Changed_Settings: " << name << " : " << e;

			//--

			//if (0)
			//{
			//}
			//else if (name == " ")
			//{
			//}

			//--

			//else if (name == position_Anchor.getName())
			//{
			//	// Position linked to first queued window
			//	if (queueWindowsVisible.size() == 0 || windowsPanels.size() == 0) return;
			//	// get the index of the first window
			//	int id = queueWindowsVisible[0];
			//	windowsPanels[id].setPosition(position_Anchor.get());
			//	doApplyLinkWindows();
			//}

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES
			bFlagSaveSettings = true;
#endif		
		}

		//--------------------------------------------------------------
		void Changed_Callbacks(ofAbstractParameter& e)
		{
			//if (bDISABLE_CALLBACKS) return;

			string name = e.getName();

			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::Changed_Callbacks: " << name << " : " << e;

			//--

			if (0)
			{
			}

			// Align Windows Helpers

			//--

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
		}

		//--

		//--------------------------------------------------------------
		void Changed_WindowsPanels(ofAbstractParameter& e) // each window show toggle changed
		{
			if (windowsPanels.size() == 0) return;

			if (bDISABLE_CALLBACKS) return;

			bDISABLE_CALLBACKS = true; // Now is attending here..

			string name = e.getName();

			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::Changed_WindowsPanels: " << name << " : " << e;

			//--			

			// Check Toggle Enablers
			// For each Special Window toggle
			// Iterate (all) unsorted and some may hidden windows!

			for (auto& p : windowsPanels)
			{
				// A bGui toggle is pressed...
				// The toggles that are showers for each special window.
				// Check which one is changed (enabled or disabled)

				if (p.bGui.getName() == name)
				{
					ofLogNotice("ofxSurfingImGui") << "id:" << p.id <<
						" indexPos:" << p.indexPos << " bGui:" << (p.bGui.get() ? "TRUE" : "FALSE");

					//--

#ifdef SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES
					bFlagSaveSettings = true;
#endif			
					//--

					// Just ENABLED / Add it 
					if (p.bGui)
					{
						if (p.indexPos == -1)
						{
							// It was hidden. Now will be queued and visible at end of the queue!
							// put new window at end of the queue
							queueWindowsVisible.push_back(p.id);
							// which one (from the full queue with all visible or not) is it
							p.indexPos = queueWindowsVisible.size() - 1; // get last index/size

							doReOrganize(); //not required?

							//TODO:
							doApplyLinkWindows();

							bDISABLE_CALLBACKS = false;
							return;
						}
						else
						{
							ofLogWarning("ofxSurfingImGui") <<
								"Should not be indexPos -1 for the window p.id:" << p.id <<
								" that was hidden until now";

							bDISABLE_CALLBACKS = false;

							//TODO:
							doReOrganize();
							doApplyLinkWindows();

							return;
						}
					}

					//--

					// Just DISABLED / Remove it
					else
					{
						if (p.indexPos == -1)
						{
							ofLogWarning("ofxSurfingImGui") <<
								"Should not be -1 ... if p.id:" << p.id << " was enabled until now";

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
							// The currently hidden window is the first!

							if (p.indexPos == 0)
							{
								ofLogWarning("ofxSurfingImGui") <<
									"Closing First! Window ID p.id:" << p.id;

								// Remove the window from the queue, from the position where it was:
								queueWindowsVisible.erase(queueWindowsVisible.begin());

								if (queueWindowsVisible.size() != 0)
								{
									//TODO:
									int id = queueWindowsVisible[0]; // get the index of first window
									windowsPanels[id].setPosition(position_Anchor.get());
								}

								p.indexPos = -1; // mark as not visible/hidden
							}

							//--

							// The hidden window is not the first!

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

							bFlagForceNext = true;

							//--

							bDISABLE_CALLBACKS = false;

							return;
						}
					}
				}
			}

			bDISABLE_CALLBACKS = false;
		}

	private:
		//--------------------------------------------------------------
		void doReOrganize()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::doReOrganize()";

			if (queueWindowsVisible.size() == 0 || windowsPanels.size() == 0) return;

			//--

			// Reorganize sorting indexes

			// 1. Disable all

			for (int i = 0; i < windowsPanels.size(); i++)
			{
				windowsPanels[i].indexPos = -1;
				windowsPanels[i].bGui.setWithoutEventNotifications(false);
			}

			//--

			// 2. Iterate each item of the queue and set the current position index

			for (int i = 0; i < queueWindowsVisible.size(); i++)
			{
				int id = queueWindowsVisible[i];

				windowsPanels[id].indexPos = i;
				windowsPanels[id].bGui.setWithoutEventNotifications(true);
			}
		}

		//--

	public:
		//--------------------------------------------------------------
		void doAlignWindowsReset()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::doAlignWindowsReset()";

			ImGuiContext* GImGui = ImGui::GetCurrentContext();
			ImGuiContext& g = *GImGui;
			ImVector<ImGuiWindow*> windows;

			struct myWin
			{
				ImVec2 pos;
				ImVec2 sz;
				int id;
				string name;
				ImGuiWindow* ImWin;
			};

			struct myclass
			{
				bool operator()(myWin w1, myWin w2) { return (w1.pos.x < w2.pos.x); }
			} myobject;

			vector<myWin> myWins;

			int _id = 0;
			for (ImGuiWindow* window : g.WindowsFocusOrder)
			{
				if (window->WasActive)
				{
					string n = ofToString(window->Name);

					//TODO:
					// fails some windows?
					// skip "non named" windows. usually menus.
					const string prefix = "##";
					if (n.substr(0, prefix.size()) == prefix) continue;

					// skip log window (hardcoded name..)
					if ("LOG" == ofToString(window->Name)) continue;

					// skip: don't align the Organizer or Aligners Windows!
					if (bGui_Aligners.getName() == n) continue;
					if (bGui_Organizer.getName() == n) continue;
					if (bGui_SpecialWindows.getName() == n) continue;

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

			// Sort, the more to-the-left window 
			// will be used as anchor!
			std::sort(myWins.begin(), myWins.end(), myobject);

			float w = myWins[0].sz.x;
			float h = myWins[0].sz.y;

			// anchor
			float x = myWins[0].pos.x + w + pad;
			float y = myWins[0].pos.y;

			for (int i = 1; i < myWins.size(); i++)
			{
				// skip
				// vertical goes different
				if (bOrientation)
				{
					bool bskip = false;
					for (size_t k = 0; k < queueWindowsVisible.size(); k++)
					{
						string name = windowsPanels[k].bGui.getName();
						if (myWins[i].ImWin->Name == name)
						{
							if (name != windowsPanels[0].bGui.getName()) bskip = true;
							break;
						}
					}
					if (bskip) continue;
				}

				myWins[i].ImWin->Pos.x = x;
				myWins[i].ImWin->Pos.y = y;

				w = myWins[i].sz.x;
				x = x + w + pad;
			}
		}

		//--------------------------------------------------------------
		void doAlignWindowsCascade()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::doAlignWindowsCascade()";

			float _padx = 117;
			float _pady = 25;

			//--

			ImGuiContext* GImGui = ImGui::GetCurrentContext();
			ImGuiContext& g = *GImGui;
			ImVector<ImGuiWindow*> windows;

			struct myWin
			{
				ImVec2 pos;
				ImVec2 sz;
				int id;
				string name;
				ImGuiWindow* ImWin;
			};

			struct myclass
			{
				bool operator()(myWin w1, myWin w2) { return (w1.pos.x < w2.pos.x); }
			} myobject;

			vector<myWin> myWins;

			int _id = 0;
			for (ImGuiWindow* window : g.WindowsFocusOrder)
			{
				if (window->WasActive)
				{
					string n = ofToString(window->Name);

					//TODO:
					// fails some windows?
					// skip "non named" windows. usually menus.
					const string prefix = "##";
					if (n.substr(0, prefix.size()) == prefix) continue;

					// skip Log window (hardcoded name..)
					if ("LOG" == ofToString(window->Name)) continue;

					// skip: Don't align neither the Organizer or Aligners Windows!
					if (bGui_Aligners.getName() == ofToString(window->Name)) continue;
					if (bGui_Organizer.getName() == ofToString(window->Name)) continue;
					if (bGui_SpecialWindows.getName() == ofToString(window->Name)) continue;

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

			// Anchor for all the next windows
			float x, y;
#if 0
			// Get first window
			x = myWins[0].pos.x + diffx;
			y = myWins[0].pos.y + diffy;
#else
			// Force to left corner position
			x = 100;
			y = 100;
#endif

			for (int i = 1; i < myWins.size(); i++)
			{
				// skip
				// vertical goes different
				if (bOrientation)
				{
					bool bskip = false;
					for (size_t k = 0; k < queueWindowsVisible.size(); k++)
					{
						string name = windowsPanels[k].bGui.getName();
						if (myWins[i].ImWin->Name == name)
						{
							if (name != windowsPanels[0].bGui.getName()) bskip = true;
							break;
						}
					}
					if (bskip) continue;
				}

				myWins[i].ImWin->Pos.x = x;
				myWins[i].ImWin->Pos.y = y;

				x = x + diffx;
				y = y + diffy;

				// Focus sorted..
				//string n = myWins[i].name;
				//ImGui::Begin(n.c_str());
				FocusWindow(myWins[i].ImWin);
				//ImGui::End();
			}
		}

		//--------------------------------------------------------------
		string getWindowMoreLefted()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::getWindowMoreLefted()";

			ImGuiContext* GImGui = ImGui::GetCurrentContext();
			ImGuiContext& g = *GImGui;
			ImVector<ImGuiWindow*> windows;

			struct myWin
			{
				ImVec2 pos;
				ImVec2 sz;
				int id;
				string name;
				ImGuiWindow* ImWin;
			};

			struct myclass
			{
				bool operator()(myWin w1, myWin w2) { return (w1.pos.x < w2.pos.x); }
			} myobject;

			vector<myWin> myWins;

			int _id = 0;
			for (ImGuiWindow* window : g.WindowsFocusOrder)
			{
				if (window->WasActive)
				{
					// skip: don't align the Organizer or Aligners Windows!
					if (bGui_Aligners.getName() == ofToString(window->Name)) continue;
					if (bGui_Organizer.getName() == ofToString(window->Name)) continue;
					if (bGui_SpecialWindows.getName() == ofToString(window->Name)) continue;

					myWin w;
					w.ImWin = window;
					w.pos = window->Pos;
					w.sz = window->Size;
					w.name = window->Name;
					w.id = _id++;
					myWins.push_back(w);
				}
			}

			if (myWins.size() == 0)
			{
				string s = "-1";
				return s;
			}

			// Sort, the more to-the-left window 
			// will be used as anchor!
			std::sort(myWins.begin(), myWins.end(), myobject);

			return myWins[0].name;
		}

		//----

	public:
		//--------------------------------------------------------------
		void add(ofParameter<bool>& e) // Will be called when Add Special Windows. 
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::add() " << e.getName();

			// Queue toggle
			params_WindowsPanels.add(e);

			// Queue window
			WindowPanel p;
			p.id = windowsPanels.size(); // which special window is
			p.indexPos = -1; // what position on visible windows queue. -1 = hidden
			p.bGui.makeReferenceTo(e); // is visible

			windowsPanels.push_back(p);

			////TODO:
			//// better using pointers?
			//// not working
			//WindowPanel p;
			//windowsPanels.push_back(p);
			//windowsPanels.back().id = windowsPanels.size();
			//windowsPanels.back().indexPos = -1;
			//windowsPanels.back().bGui.makeReferenceTo(e);
		}

	public:
		//--------------------------------------------------------------
		void doAlignShapesNextWindow() // must be called using runShapeState, called on begin() phase!
		{
			//ofLogVerbose("ofxSurfingImGui") <<"\n"<< (__FUNCTION__);

			if (ofGetFrameNum() == 1) return; // skip first frame to be sure that all it's prepared.

			//--

			if (bOrientation) // vertical
			{
				if (bAlignShapesX) ImGui::SetNextWindowSize(ImVec2(width_max, 0));
			}
			else // horizontal
			{
				if (bAlignShapesY) ImGui::SetNextWindowSize(ImVec2(0, height_max));
			}
		}

		//----

		//--------------------------------------------------------------
		void setupInitiate()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::setupInitiate()";
			ofLogNotice("ofxSurfingImGui") << nameLabel;

			//--

			params_Panels.add(bGui_ShowWindowsGlobal);
			params_Panels.add(bGui_Aligners);
			params_Panels.add(bGui_Organizer);
			params_Panels.add(bGui_SpecialWindows);
			params_Controls.add(params_Panels);

			params_Controls.add(bLinked);
			params_Controls.add(bOrientation);
			params_Controls.add(bAlignShapes);
			params_Controls.add(bAlignShapesX);
			params_Controls.add(bAlignShapesY);
			params_Controls.add(bHeaders);
			params_Controls.add(pad);
			params_Controls.add(position_Anchor);

			// Settings Group
			params_AppSettings.add(params_Controls);

			// Each window enabler will be added here..
			// all of theme has been added during setup
			params_AppSettings.add(params_WindowsPanels);

			//--

			params_Callbacks.add(bAlignWindowsY);
			params_Callbacks.add(bAlignWindowsX);
			params_Callbacks.add(bAlignWindowsCascade);
			params_Callbacks.add(bAlignWindowsReset);

			//--

			startup();
		}

		//--------------------------------------------------------------
		void startup()
		{
			ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::startup()";
			ofLogNotice("ofxSurfingImGui") << nameLabel;

			//--

			bDISABLE_CALLBACKS = false;

			if (windowsPanels.size() != 0) bDoneInitialized = true;

			//--

			// Load Settings
			if (bDoneInitialized) loadSettings();


			//--

			if (queueWindowsVisible.size() == 0 || windowsPanels.size() == 0)
			{
				ofLogWarning("ofxSurfingImGui") << (__FUNCTION__);
				ofLogWarning("ofxSurfingImGui") << "Some Special Windows queue is empty!";
			}
			else
			{
				// Position linked to first queued window
				int id = queueWindowsVisible[0];
				windowsPanels[id].setPosition(position_Anchor.get());
			}

			//--

			////TODO:
			//doReOrganize();

			//TODO:
			if (bLinked) doApplyLinkWindows();
		}

		////--------------------------------------------------------------
		//void startupDelayed()
		//{
		//	// Force some fixes

		//	ofLogNotice("ofxSurfingImGui") << "WindowsOrganizer::startupDelayed()";
		//	ofLogNotice("ofxSurfingImGui") << nameLabel;

		//	// Load Settings
		//	if (bDoneInitialized) loadSettings();

		//	bDoneStartupDelayed = true;

		//	//--

		//	//bOrientation = bOrientation;
		//	////bLockedWidth = bLockedWidth;
		//	////bLockedHeight = bLockedHeight;

		//	//bAlignShapes = bAlignShapes;
		//	//bAlignShapesX = bAlignShapesX;
		//	//bAlignShapesY = bAlignShapesY;
		//	////bAlignShapes_PRE = bAlignShapesX;
		//	////bAlignShapesX = !bAlignShapesX;
		//}

		//--------------------------------------------------------------
		void loadSettings()
		{
			if (!bEnableFileSettings) return;

			loadGroup(params_AppSettings, path_Settings);
		}

		//--

	private:
		bool bFlagForceNext = false; // workaround required / to be used when hiding first window!

	public:
		//--------------------------------------------------------------
		void getShapeState(int i)
		{
			windowsPanels[i].getShapeState();
		}

		//--------------------------------------------------------------
		void runShapeState(int i) // Sets position. To be effective, must be called just before begin()!
		{
			if (windowsPanels.size() == 0) return;
			if (queueWindowsVisible.size() == 0) return;
			if (i > windowsPanels.size() - 1) return;

			ofRectangle r = windowsPanels[i].getShape();

			ImGuiCond flagCond;

			int id = queueWindowsVisible[0]; // get the index of first window

			// force engine
			bool bforce = false;
			if (bFlagForceNext)
			{
				bFlagForceNext = false;
				bforce = true;
			}

			if (bforce)
			{
				////TODO:
				//// workaround
				//float x = position_Anchor.get().x;
				//float y = position_Anchor.get().y;
				//glm::vec2 p = glm::vec2(x, y);
				//windowsPanels[id].setPosition(p);

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
			if (bAlignShapes) doAlignShapesNextWindow();
		}

		//--

	public:
		//--------------------------------------------------------------
		void setNameWindowsSpecialsEnableGlobal(string name)
		{
			bGui_ShowWindowsGlobal.setName(name);
		}

		//--

		// Get the name of the last special window (the window at the end of current drawn queue)
		//--------------------------------------------------------------
		string getWindowSpecialLast() const
		{
			string name = "-1";
			if (queueWindowsVisible.size() == 0) return name; //all are hidden

			int ilast = queueWindowsVisible.back();
			name = windowsPanels[ilast].bGui.getName();

			return name;
		}

		// Get the position of the last special window (the window at the end of current drawn queue / at right)
		//--------------------------------------------------------------
		glm::vec2 getWindowSpecialLastTopRight() const
		{
			glm::vec2 p = glm::vec2(-1, -1);
			if (queueWindowsVisible.size() == 0) return p; //skip when all are hidden

			int ilast = queueWindowsVisible.back();
			p = windowsPanels[ilast].getRectangle().getTopRight();

			return p;
		}

		// Get the position of the first special window (the window at the begin of current drawn queue / at left )
		//--------------------------------------------------------------
		glm::vec2 getWindowSpecialLastTopLeft() const
		{
			glm::vec2 p = glm::vec2(-1, -1);
			if (queueWindowsVisible.size() == 0) return p; //skip when all are hidden

			int ifirst = queueWindowsVisible[0];
			p = windowsPanels[ifirst].getRectangle().getTopLeft();

			return p;
		}

		//--

		//TODO:
		// Set anchor first window from a parent scope:
		// That feature allows to link grouped windows from many contexts / add-ons.
		//--------------------------------------------------------------
		void setWindowSpecialFirstPosition(glm::vec2 pos)
		{
			if (queueWindowsVisible.size() == 0) return; //skip when all are hidden
			int ifirst = queueWindowsVisible[0];
			glm::vec2 p(pos.x + pad, pos.y); //TODO: forced to horizontal align.
			windowsPanels[ifirst].setPosition(p);

			//TODO:
			// Force
			//runShapeState(ifirst);
		}

		//----

		//--------------------------------------------------------------
		void drawWidgetsAligners(bool bMinimized = false)
		{
			ofxImGuiSurfing::AddSpacing();
			ofxImGuiSurfing::AddBigButton(bAlignWindowsReset);
			ofxImGuiSurfing::AddSmallButton(bAlignWindowsCascade);

			if (!bMinimized)
			{
				float h = ofxImGuiSurfing::getWidgetsHeightUnit();
				float w2 = ofxImGuiSurfing::getWidgetsWidth(2);
				ofxImGuiSurfing::AddSmallButton(bAlignWindowsY, ImVec2(w2, h));
				ImGui::SameLine();
				ofxImGuiSurfing::AddSmallButton(bAlignWindowsX, ImVec2(w2, h));
			}
		}

		//--------------------------------------------------------------
		void drawWidgetsWindows(bool bMinimized = false)
		{
			float _h = getWidgetsHeight();
			float _w1 = getWidgetsWidth(1);
			float _w2 = getWidgetsWidth(2);
			
			// Global Enable 
			ImGui::Spacing();
			bool b = !bGui_ShowWindowsGlobal;//blink
			if (b) ofxImGuiSurfing::BeginBlinkText();
			ofxImGuiSurfing::AddToggleRoundedButton(bGui_ShowWindowsGlobal); //medium
			if (b) ofxImGuiSurfing::EndBlinkText();
			//ImGui::Spacing();

			if (bGui_ShowWindowsGlobal)
			{
				if (!bMinimized)
				{
					ImGui::Spacing();

					if (ImGui::Button("All", ImVec2(_w2, _h)))
					{
						for (auto& p : windowsPanels)
						{
							p.bGui = true;
						}
					}
					ImGui::SameLine();
					if (ImGui::Button("None", ImVec2(_w2, _h)))
					{
						for (auto& p : windowsPanels)
						{
							p.bGui = false;
						}
					}

					ImGui::Spacing();
				}

				//--

				// Windows
				ImGui::Indent();
				for (auto& p : windowsPanels)
				{
					ofxImGuiSurfing::AddBigToggle(p.bGui);
					//ofxImGuiSurfing::AddToggleRoundedButton(p.bGui);
				}
				ImGui::Unindent();

				//ImGui::Spacing();
			}
		}

		//--------------------------------------------------------------
		void drawWidgetsOrganizer(bool bMinimized = false)
		{
			float _h = getWidgetsHeight();
			float _w1 = getWidgetsWidth(1);
			float _w2 = getWidgetsWidth(2);

			//--

			// Windows

			if (!bGui_SpecialWindows)
			{
				if (!bHideWindowsToggles)
				{
					ImGuiColorEditFlags _flagw = ImGuiWindowFlags_None;
					//ImGuiColorEditFlags _flagw = (bDebug ? ImGuiWindowFlags_NoCollapse : ImGuiWindowFlags_None);

					if (ImGui::CollapsingHeader("WINDOWS", _flagw))
					{
						drawWidgetsWindows();
					}

					if (bGui_ShowWindowsGlobal) ofxImGuiSurfing::AddSpacingSeparated();
				}
			}

			//--

			if (bGui_ShowWindowsGlobal) {

				// Linked

				ofxImGuiSurfing::AddBigToggle(bLinked, _w1, 2 * _h, true, true); //blinking

				if (bLinked)
				{
					// Orientation

					ofxImGuiSurfing::AddSpacing();

					//string ss = bOrientation ? "VERTICAL" : "HORIZONTAL";
					//float h = 1.25 * ImGui::GetFrameHeight();
					//float w = h * 1.55f;
					////ofxImGuiSurfing::AddToggleRoundedButton(bOrientation, ss, ImVec2(w, h));

					ofxImGuiSurfing::AddToggleNamed(bOrientation, "VERTICAL", "HORIZONTAL");

					//ImGui::Spacing();
				}

				//--

				// Aligners

				if (!bGui_Aligners) {
					ofxImGuiSurfing::AddSpacingSeparated();

					if (ImGui::CollapsingHeader("ALIGNERS"))
					{
						drawWidgetsAligners();
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

								bool bNoLabel = false;
								bool bRaw = 0;
								ofxImGuiSurfing::AddStepper(pad, bNoLabel, bRaw);

								ofxImGuiSurfing::AddToggleRoundedButton(bAlignShapes);
								if (bAlignShapes)
								{
									ImGui::Indent();
									if (bOrientation) //vertical
										ofxImGuiSurfing::AddToggleRoundedButton(bAlignShapesX);

									if (!bOrientation) //horizontal
										ofxImGuiSurfing::AddToggleRoundedButton(bAlignShapesY);
									ImGui::Unindent();
								}

								if (ImGui::Button("Reset##SETTINGS")) {
									this->resetSettings();
								}
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

								ImGui::Spacing();
								ImGui::TextWrapped("SPECIAL WINDOWS \n");
								ofxImGuiSurfing::AddSpacingSeparated();
								ImGui::Spacing();

								// Anchor
								string ss4 = "";
								ss4 += "Anchor \n\n";
								ss4 += ofToString(position_Anchor.get());
								if (queueWindowsVisible.size() > 0)
								{
									int id = queueWindowsVisible[0]; // first visible windows acts as anchor!
									ss4 += "\n";
									ss4 += "" + ofToString(id);
								}

								ImGui::TextWrapped("%s", ss4.c_str());
								ofxImGuiSurfing::AddSpacingSeparated();

								// Queue visible
								string ss2 = "Queue Visible \n\n";
								for (int i = 0; i < queueWindowsVisible.size(); i++)
								{
									if (i != 0) ss2 += ", ";
									ss2 += ofToString(queueWindowsVisible[i]);
								}
								ImGui::TextWrapped("%s", ss2.c_str());
								ofxImGuiSurfing::AddSpacingSeparated();

								// All the panels
								string ss1 = "";
								int i = 0;
								for (auto& p : windowsPanels)
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
								ImGui::TextWrapped("%s", ss1.c_str());
								ofxImGuiSurfing::AddSpacingSeparated();

								// Windows
								string ss5 = "All Windows ON\n\n";
								for (int i = 0; i < windowsPanels.size(); i++)
								{
									if (i != 0) ss5 += ", ";
									ss5 += ofToString(windowsPanels[i].id);
								}
								ImGui::TextWrapped("%s", ss5.c_str());
								ofxImGuiSurfing::AddSpacingSeparated();

								ss1 = "Callbacks " + ofToString(bDISABLE_CALLBACKS ? "OFF" : "ON");
								ImGui::TextWrapped("%s", ss1.c_str());

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
		void refreshUpdate()
		{
			//--

			//// Startup Delayed
			//if (ofGetFrameNum() == 1 && !bDoneStartupDelayed)
			//{
			//	startupDelayed();
			//}

			//--

			// Skip
			if (queueWindowsVisible.size() == 0 || windowsPanels.size() == 0)
			{
				//TODO:
				// workaround 
				// to solve that sometimes hiding/showing windows are translated to the right..
				// force to improve when showing back 
				for (size_t i = 0; i < windowsPanels.size(); i++)
				{
					windowsPanels[i].setPosition(position_Anchor.get());
				}

				return;
			}

			//--

			// Read 1st queued position to the anchor
			// Required to allow move first window by the user!
			//TODO: we could allow to move all windows with another engine..
			int id = queueWindowsVisible[0];
			glm::vec2 p = windowsPanels[id].getPosition();
			position_Anchor.setWithoutEventNotifications(p);

			//--

			// Update / Apply all links to windows
			if (bLinked) doApplyLinkWindows();
		}

		//--

	private:
		//public:

		//--------------------------------------------------------------
		void doApplyLinkWindows() // Sets the position for all the visible windows.
		{
			if (queueWindowsVisible.size() == 0 || windowsPanels.size() == 0) return;

			//--

			// 1. All windows with the same max width

			// Take measures to apply on next doAlignShapesNextWindow() call!

			if (bAlignShapes)
			{
				for (int i = 0; i < queueWindowsVisible.size(); i++)
				{
					int id = queueWindowsVisible[i];
					ofRectangle r = windowsPanels[id].getRectangle();

					// measure maxims w/h from all the windows to align shapes!
					if (width_max < r.getWidth()) width_max = r.getWidth();
					if (height_max < r.getHeight()) height_max = r.getHeight();
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
				// the original id of each window
				id = queueWindowsVisible[i];

				// first visible windows acts as anchor!
				if (i == 0)
				{
					x = position_Anchor.get().x;
					y = position_Anchor.get().y;
				}
				p = glm::vec2(x, y);
				windowsPanels[id].setPosition(p);

				//--

				if (bOrientation) // vertical
				{
					h = windowsPanels[id].getHeight();
					y = y + h + pad;
				}
				else // horizontal
				{
					w = windowsPanels[id].getWidth();
					x = x + w + pad;
				}
			}
		}
	};
}
