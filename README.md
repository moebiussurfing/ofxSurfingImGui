ofxSurfingImGui
=============================

## Overview
An **ImGui** toolkit for **openFrameworks** projects.  

Setup and Layout Management, **RAW ImGui Widgets** ported to oF, **ofParameter Helpers**, and useful Snippets, some WIP or testing projects like Docking helpers, Sequencer or Node patching...   

## WORK IN PROGRESS!  
```
NOT FINISHED. A BIT BUGGY YET...
API WILL CHANGE A BIT.  
SOME EXAMPLES CAN BE REDUNDANT  
OR NOT FINISHED,  
OR NEED TO BE UPDATED TO API CHANGES.
```

<details>
  <summary>RELEVANT oF-RELATED CHANGES (vs official ofxImGui ofParameter/ImHelpers)</summary>
  <p>

- Simplified **oF Helpers** to use **ofParameters** easy and better. 
    * _ImHelpers.h_ has been rewritten to ofxSurfing_ImGui_ofHelpers.h_.
    * Widgets, windows/trees now are more customizable. 
    * Removed all old windows/tree methods.
    * Removed all the _WindowOpen/Settings_ stuff.
    * Removed all the old _GetUniqueName_ engine from **ofxImGui**. 
    * Now using PushId()/PopID() approach on each widget.
    * NEW: All the Layout/Styles Management.
  </p>
</details>

## FEATURES 
* Requires the _awesome_ @**Daandelange**'s [ofxImGui](https://github.com/Daandelange/ofxImGui/) fork: 
    - Why? Easy to update to future **new ImGui** versions and multi context/instances.
* **ImGui Widgets**: big toggles and buttons, range sliders, DearWidgets ...etc.
* **Layout Manager** to speed up **windows creation** and fit-widgets-width-to-window sizes.
* Included my **Dark Theme**.

<BR>

## 1. WIDGETS
Shows **ofParameter** helpers with full/half/third/quarter width buttons, toggles, DearWidgets, range sliders, Bezier Curve, Spinner/Progress Indicators, and ofxImGui standard params.  

<details>
  <summary>1_1_Widgets_DearWidgets</summary>
  <p>

![image](/docs/1_1_Widgets_DearWidgets.PNG?raw=true "image")  
Includes range sliders with **ofParameters**, responsive button/toggles and the awesome [DearWidgets](https://github.com/soufianekhiat/DearWidgets) from **@soufianekhiat**.  
  </p>
</details>

<details>
  <summary>1_2_Widgets_Curve</summary>
  <p>

![image](/docs/1_2_Widgets_Curve.PNG?raw=true "image")  
Includes bezier curves and usable tween/easing functions.  
  </p>
</details>

<details>
  <summary>1_3_Widgets_Spinner</summary>
  <p>

![image](/docs/1_3_Widgets_Spinner.gif?raw=true "image")  
Includes wait and progression spinners.  
  </p>
</details>

<details>
  <summary>1_4_Widgets_Surfing</summary>
  <p>

![image](/docs/1_4_Widgets_Surfing.PNG?raw=true "image")  
Includes a **matrix button clicker selector** linked to an **ofParameter<int>** (aka preset index), small tooltips, spin clicker, and the awesome gradient engine from [@galloscript](https://twitter.com/galloscript) from his [Github Gist](https://gist.github.com/galloscript/8a5d179e432e062550972afcd1ecf112).  
  </p>
</details>

<details>
  <summary>1_5_FileBrowser</summary>
  <p>

![image](/docs/1_5_FileBrowser.PNG?raw=true "image")  
  </p>
</details>

<BR>

## 2. LAYOUT

Uses **ofxSurfing_ImGui_LayoutManager.h**  
Speed up **ofxImGui** instantiation, windows and layouts.  
Includes **ofParameter** helpers, widget sizes and extra widgets.  
_Notice that below at point **3. TYPES ENGINE**, there's a better NEW API!_ 

<details>
  <summary>Example Code</summary>
  <p>
  
  ![image](/docs/2_1_2_Layout_Basic.PNG?raw=true "image")  

ofApp.h
```.cpp
#include "ofxSurfingImGui.h"

ofxSurfing_ImGui_Manager guiManager;

ofParameter<bool> bGui{ "Show Gui", true };

ofParameter<bool> bEnable{ "Enable", true };
ofParameter<bool> b1{ "b1", false };
ofParameter<bool> b2{ "b2", false };
ofParameter<bool> b3{ "b3", false };
```
ofApp.cpp
```.c++
void ofApp::setup() 
{ 
    guiManager.setup(); 
    // Instantiates and configures all the required ofxImGui stuff inside:
    // Font, theme, autodraw, layout store/recall, multi context/instances, ofParams Helpers and other customizations.
}
    
void ofApp::draw() 
{ 
    guiManager.begin();
    if (bGui) // -> This param makes the close button functional
    {
        guiManager.beginWindow("Window", (bool *)&bGui.get(), ImGuiWindowFlags_None);
        {
            ofxImGuiSurfing::AddToggleRoundedButton(bEnable);
            if (bEnable)
            {
                // Precalculate common widgets sizes to fit current window, "to be responsive".
                float _w1 = ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
                float _w2 = ofxImGuiSurfing::getWidgetsWidth(2); // 2 widgets half width
                float _w3 = ofxImGuiSurfing::getWidgetsWidth(3); // 3 widgets third width
                float _w4 = ofxImGuiSurfing::getWidgetsWidth(4); // 4 widgets quarter width
                float _h = ofxImGuiSurfing::getWidgetsHeightRelative(); // one unit height relative to ImGui theme

                //-

                /* Draw RAW ImGui or SurfingWidgets with ofParameters */

                // One widget full with and theme height. The callback is handled by the param listeners.
                ofxImGuiSurfing::AddBigToggle(b1); 

                // Two widgets same line/row with the 50% of window panel width 
                if (ofxImGuiSurfing::AddBigButton(b2, _w2, _h)) {
                  /* This acts as callback. No parameter listener required. */
                }
                ImGui::SameLine();
                if (ofxImGuiSurfing::AddBigButton(b3, _w2, _h)) {
                  
                }

                // Or using raw ImGui
                // Three widgets and fit width in one line
                if (ImGui::Button("START", ImVec2(_w3, _h))) {}
                ImGui::SameLine();
                if (ImGui::Button("STOP", ImVec2(_w3, _h))) {}
                ImGui::SameLine();
                if (ImGui::Button("REPLAY", ImVec2(_w3, _h))) {}
            }
        }
        guiManager.endWindow();
    }
    guiManager.end();
}
```
  </p>
</details>

<details>
  <summary>2_1_Layout_Basic</summary>
  <p>

![image](/docs/2_1_Layout_Basic.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>2_0_Layout_ofParamaters</summary>
  <p>

![image](/docs/2_0_Layout_ofParamaters.gif?raw=true "image")  
Includes **ofParameter** and **ofParameterGroup** helpers and customize how groups are presented: collapsed/expanded, hidden header, **ImGui::Tree/ImGui::TreeEx** ...etc.  
[BROKEN]  
  </p>
</details>

<details>
  <summary>2_4_Layout_ThemeEditor</summary>
  <p>

![image](/docs/2_4_Layout_ThemeEditor.PNG?raw=true "image")  
  </p>

This is a helper for tweaking your Themes: testings sizes, layout, and colors, and alternate fonts.  
Notice that you need to export the new modified theme code trhought the clipboard and to paste to a new function/theme manually.  
There's not an automatic-fully-functional, save preset/load theme designer!  
</details>

<BR>

## 3. DOCKING [WIP]

Examples to improve the layout of docking spaces. 

* Learn to split docking spaces.
* Engine manager to create layout presets.
* docking helpers

<details>
  <summary>2_2_Layout_Docking</summary>
  <p>

![image](/docs/2_2_Layout_Docking.PNG?raw=true "image")  
Learn to Split layout spaces by code.  
  </p>
</details>

<details>
  <summary>2_3_Layout_ImTools</summary>
  <p>

![image](/docs/2_3_Layout_ImTools.PNG?raw=true "image")  
  </p>

Uses [ImTools](https://github.com/aiekick/ImTools) from **@aiekick**: "_Its a class for manage docking panes in an easy way, display (panes, menu, pane dialog), load/save, auto layout, etc..._". **WIP** porting to use into my OF projects.  
</details>

<BR>

## 4. TYPES ENGINE [WIP]

One step forward for ofHelpers:  

* Fast **ofParameter**s widgets layout: responsive-auto_fit width, height, amount items per row, and different styles for the same types or even repeated parameters.  

* Also **ofParameterGroup** and their inside **ofParameters**, can be customized too with different **ImGui::Tree** settings, collapsed and nested.  

#### FEATURES

1. A more powerful **Layout Engine** to improve: "responsive" layouts and customized widgets.  
2. Draw each **ofParameter** types with different styles. (Instead of the **ofxImGui** behavior, where you can't change the param widget style.)  
3. Especially useful when **ofParameters** are into an **ofParameterGroup**.  
4. Queue settings for an **ofParameter** to define configurations to be applied when the widget is drawn when drawing a group. 
5. You can exclude some params to be drawn, to disable the mouse interaction, or to draw his void spacing. 
6. You can customize how **ofParameterGroup** / **ImGui::Tree** are presented.

<details>
  <summary>USAGE CASES</summary>
  <p>

**CASE 1**:  
_Draw an **ofParameter<float>** as slider (default), drag number or/and +/- stepper box._  

**CASE 2**:  
_Draw an **ofParameter<bool>** as a check box (default), or as a big toggle button with custom dimensions._  

**CASE 3**:  
_You added an **ofParameter<bool>** inside an **ofParameterGroup**. Add a style for the type of widget. You want to customize how it will be drawn (instead of using the default style), but when the group is rendered._  
  </p>
</details>

<details>
  <summary>3_0_Layout_TypesEngine</summary>
  <p>

![image](/docs/3_0_Layout_TypesEngine.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>3_1_Layout_TypesEngine</summary>
  <p>

![image](/docs/3_1_Layout_TypesEngine.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>Code</summary>
  <p>

ofApp.h
```.cpp

```

ofApp.cpp
```.cpp

```
  </p>
</details>

#### AVAILABLE CUSTOMIZATIONS:
    - Hide the parameter widget respecting the void space or not, or make it inactive sibaling mouse interation.  
    - Set an ImGui::SameLine( after the widget, to draw more next params at the same line.  
    - Add a final vertical spacing after the widget.  
    - Set the widget width to fit the panel width, passing the amount of widgets per row/line.  

#### API
```c++
void AddStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1);
bool Add(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1);
void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT);
```

<BR>

## 5. TIMELINES AND SEQUENCERS [WIP]

These are testing projects trying to build an operative but very basic timeline, to run very simple animations:  
* A kind of note on/off or clip start/end behavior.
* A curve editor for a float variable automation. 
  
<details>
  <summary>4_1_ImSequencer</summary>
  <p>

![image](/docs/4_1_ImSequencer.PNG?raw=true "image")  
Using [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)  
Still very raw yet, not functional: I need to [finish](https://github.com/CedricGuillemet/ImGuizmo/issues/185) the engine to read the values when frames are playing.  
  </p>
</details>

5_3_Sequentity [BROKEN]  
Using [Sequentity](https://github.com/alanjfs/sequentity). It's being hard to port because of some dependencies...

<BR>

## 6. NODES [WIP]

These are testing [projects](https://github.com/ocornut/imgui/issues/306) with nodes/graph/patching.  
My target is to build a simple engine to patch between **ofParameters**.  
**For example**: _A simple patch-bay to route some **ofParameters** from an audio analyzer to the render scene **ofParameters**._   

<details>
  <summary>5_1_ImNodes_Nelarius</summary>
  <p>

![image](/docs/5_1_ImNodes_Nelarius.PNG?raw=true "image")  
Using [Nelarius/imnodes](https://github.com/Nelarius/imnodes)  
  </p>
</details>

<details>
  <summary>5_2_ofNodeEditor</summary>
  <p>

![image](/docs/5_2_ofNodeEditor.PNG?raw=true "image")  
Using [sphaero/ofNodeEditor](https://github.com/sphaero/ofNodeEditor)  
  </p>
</details>

<details>
  <summary>5_4_ImNodes_rokups</summary>
  <p>

![image](/docs/5_4_ImNodes_rokups.PNG?raw=true "image")  
Using [rokups/ImNodes](https://github.com/rokups/ImNodes)  
  </p>
</details>

<details>
  <summary>5_5_ImNodes_thedmd</summary>
  <p>

![image](/docs/5_5_ImNodes_thedmd.PNG?raw=true "image")  
Using [thedmd/imgui-node-editor](https://github.com/thedmd/imgui-node-editor)  
  </p>
</details>

<details>
  <summary>5_5_2_ImNodes_thedmd-PatchBay</summary>
  <p>

![image](/docs/5_5_2_ImNodes_thedmd-PatchBay.PNG?raw=true "image")  
[**WIP**] Using [ofxPatchbayParams](https://github.com/moebiussurfing/ofxPatchbayParams)  
  </p>
</details>

5_5_ImNodes_thedmd-Blueprints [BROKEN]  
5_6_ImNodes-Graph-ImGuizmo [BROKEN]  

<BR>

## Dependencies
[ofxImGui](https://github.com/Daandelange/ofxImGui/) FORK from @**Daandelange**  
[ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp) [For some examples only]  

## Tested Systems
- **Windows10** / **VS2017** / **OF ~0.11**

## Author
An addon by **@moebiusSurfing**  
*( ManuMolina ) 2021*  

### Thanks
_All source snippets from other authors are linked into header files. Thanks!_

## License
**MIT License**

<BR>

<details>
  <summary>Some reference links</summary>
  <p>

https://github.com/HankiDesign/awesome-dear-imgui  
https://github.com/soufianekhiat/DearWidgets  
https://github.com/yumataesu/ImGui_Widgets  
https://github.com/njazz/AutomationCurveEditor  
https://github.com/leiradel/ImGuiAl  
https://github.com/aiekick/ImTools/tree/main/LayoutManager  
https://github.com/Organic-Code/ImTerm  
  </p>
</details>
<details>
  <summary>TODO</summary>
  <p>

* Add more ImGui RAW widgets with examples.
* Convert to ofParameters for some widgets.
* Fix and solve final ofParams helpers workflow.
* Add multiple layouts presets engine from Paletto.
  </p>
</details>
