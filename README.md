ofxSurfingImGui
=============================

## Overview

An **ImGui** Toolkit for **openFrameworks** projects.  

Setup and Layout Management, **ofParameter Helpers** and **ImGui Widgets** ported to **oF**, Docking Helpers with a Layout Presets Engine, and useful snippets.  

Some examples and testing projects are now moved to [ofxSurfingImGuiExtra](https://github.com/moebiussurfing/ofxSurfingImGuiExtra).  

More Info [README_DEV](/README_DEV.md)  

![image](/docs/1_Widgets/1_Widgets_Sliders2.PNG?raw=true "image")  


## FEATURES

* Requires the _AWESOME_ @**Daandelange**'s [ofxImGui](https://github.com/Daandelange/ofxImGui/) fork: 
  - Why? 
    - Easy to update to future **NEW ImGui** versions.  
    - Multi context/instances: you can use several windows from different add-ons without colliding.  
* **ImGui Widgets**: 
  - Big Toggles and Buttons
  - Vertical and Horizontal Sliders
  - Range Sliders
  - Styled Knobs
  - Inactive, hidden, locked widgets
  - Show or hide labels and values
  - DearWidgets
  - Gradient Color Designer
  - Matrix Selector
  - Progress bars and waiting spinners
  - Files Browser
  - Curve Editors
  - Mouse Wheel control

* **Layout Manager** to speed up **windows creation** and responsive _auto-fit-widgets-width-to-window_ sizes.
* **Layout Presets Engine with Docking** and app sections handling.
* Included my **Dark Theme**.

## INDEX

### 1. [WIDGETS](#1-widgets-1)

### 2. [LAYOUT](#2-layout-1)

### 3. [STYLES](#3-styles-1)

### 4. [LAYOUTS & DOCKING](4-layouts--docking-wip-1) [WIP]


<BR>

## 1. WIDGETS

Shows **ofParameter** helpers with full/half/third/quarter width Buttons, Toggles, DearWidgets, Range Sliders, Bezier Curve, Spinner/Progress Indicators, and **ofxImGui** standard parameters.  

<details>
  <summary>1_1_Widgets_DearWidgets</summary>
  <p>

Includes Range Sliders with **ofParameters**, responsive Button/Toggles and the AWESOME [DearWidgets](https://github.com/soufianekhiat/DearWidgets) from **@soufianekhiat**.  
![image](/docs/1_Widgets/1_1_Widgets_DearWidgets.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>1_2_Widgets_Curve</summary>
  <p>

Includes Bezier Curves and usable timed Tween/Easing functions.  
![image](/docs/1_Widgets/1_2_Widgets_Curve.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>1_3_Widgets_Spinner</summary>
  <p>

Includes waiting and progress spinners.  
![image](/docs/1_Widgets/1_3_Widgets_Spinner.gif?raw=true "image")  
  </p>
</details>

<details>
  <summary>1_4_Widgets_Surfing</summary>
  <p>

Includes a **matrix button clicker selector** linked to an **ofParameter<int>** (aka preset index), small tooltips, spin clicker, and the awesome gradient engine from [@galloscript](https://twitter.com/galloscript) from his [Github Gist](https://gist.github.com/galloscript/8a5d179e432e062550972afcd1ecf112).  
![image](/docs/1_Widgets/1_4_Widgets_Surfing.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>1_5_FileBrowser</summary>
  <p>

![image](/docs/1_Widgets/1_5_FileBrowser.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>1_8_Knobs</summary>
  <p>

![image](/docs/1_Widgets/1_8_Knobs.PNG?raw=true "image")  
  </p>
</details>

<BR>

## 2. LAYOUT

Speed up **ofxImGui** instantiation (auto draw, viewport mode, fonts...), windows, and layouts.  
Includes **ofParameter** helpers, widget sizes, and extra widgets.  
_Notice that below at point **3. TYPES ENGINE**, there's a better NEW API!_ 

<details>
  <summary>Example Code</summary>
  <p>

  ![image](/docs/2_Layout/2_1_2_Layout_Basic.PNG?raw=true "image")  

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
                  // This acts as callback. 
                  // No parameter listener required.
                }
                ImGui::SameLine();
                if (ofxImGuiSurfing::AddBigButton(b3, _w2, _h)) {
                  // This acts as callback. 
                  // No parameter listener required.
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

![image](/docs/2_Layout/2_1_Layout_Basic.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>2_0_Layout_ofParamaters</summary>
  <p>

Includes **ofParameter** and **ofParameterGroup** helpers and customize how groups are presented: collapsed/expanded, hidden header, **ImGui::Tree/ImGui::TreeEx** ...etc.  
[BROKEN]  
![image](/docs/2_Layout/2_0_Layout_ofParamaters.gif?raw=true "image")  
  </p>
</details>

<details>
  <summary>2_4_Layout_ThemeEditor</summary>
  <p>

This is a helper for tweaking your Themes: testings sizes, layout, and colors, and alternate fonts.  

Notice that you need to export the newly modified theme code through the clipboard and paste it to a new function/theme manually.  
There's not an automatic-fully-functional, save preset/load theme designer!  
![image](/docs/2_Layout/2_4_Layout_ThemeEditor.PNG?raw=true "image")  
  </p>
</details>

<BR>

## 3. STYLES

One step forward for **ofHelpers**:  

* Fast **ofParameter**s widgets layout: responsive-auto_fit width, height, amount items per row, and different styles for the same types or even repeated parameters with different styles.  

* Also **ofParameterGroup** and their inside **ofParameters**, can be customized too with different **ImGui::Tree** settings, collapsed and nested.  

<details>
  <summary>Vertical and Horizontal Sliders</summary>
  <p>

![image](/docs/1_Widgets/1_Widgets_Sliders.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>Grouped Vertical and Horizontal Sliders</summary>
  <p>

![image](/docs/1_Widgets/1_Widgets_Sliders2.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>Nested Styled Groups</summary>
  <p>

![image](/docs/4_Docking/4_0_0_Layout_TypesEngine.PNG?raw=true "image")  
  </p>
</details>

<details>
  <summary>Layout Engine</summary>
  <p>

![image](/docs/4_Docking/4_0_1_Layout_TypesEngine.PNG?raw=true "image")  
  </p>
</details>

<BR>

## 4. LAYOUTS & DOCKING [WIP]

Examples to improve the layout of Docking Spaces. 

* Learn to split docking spaces by code, or using mouse control by the user.
* Docking helpers. **Engine Manager** to create layout presets.
<details>
  <summary>3_0_Layout_Docking2</summary>
  <p>

#### LAYOUT PRESETS ENGINE

* Fast adding of windows to the **Gui Manager**.
* Auto populates **Control Panels** to handle layout presets.
* Cute workflow for Management.
* You can add extra parameters to the presets too. 

![image](/docs/3_StylesEngine/3_0_Layout_Docking2.gif?raw=true "gif")  
  </p>
</details>

<details>
  <summary>3_0_Layout_Docking3</summary>
  <p>

This example shows how to populate many ImGui windows from different scopes on the same viewport.  
Uses different approaches: from ofApp, from an add-on/class, or with Surfing Layout tools as guiManager.  
Also useful to check viewport modes, docking merging windows or auto draw modes.  

![image](/docs/3_StylesEngine/3_0_Layout_Docking3.PNG?raw=true "png")  
  </p>
</details>

<BR>

## Dependencies
[ofxImGui](https://github.com/Daandelange/ofxImGui/) : AWESOME FORK from @**Daandelange**  
[ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers)  

[ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp) : For some examples only. [ _Optional_ ]  

**/data/** folder contains some font files that we use in the examples.  

## Tested Systems
- **Windows10** / **VS2017** / **OF ~0.11**

## Author
An addon by **@moebiusSurfing**  
*( ManuMolina ) 2021-2022*  

### Thanks
_All source snippets from other authors are linked into header files. Thanks!_

### License
**MIT License**
