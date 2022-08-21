ofxSurfingImGui
=============================

## OVERVIEW

An [ImGui](https://github.com/ocornut/imgui) **Toolkit** for **openFrameworks** projects.  

( _Some examples, complementary docs and more testing projects are now moved to [ofxSurfingImGuiExtra](https://github.com/moebiussurfing/ofxSurfingImGuiExtra)._ )  

## WORK IN PROGRESS!

[Examples Screenshots](https://github.com/moebiussurfing/ofxSurfingImGui/tree/master/Examples)  

<details>
  <summary>SCREENSHOTS</summary>
  <p>

#### Widgets & Layout Engine

![](https://github.com/moebiussurfing/ofxSurfingImGuiExtra/blob/master/readme_media/image/1_Widgets_Sliders2.PNG)  

#### Layout Presets Engine & Docking

![](https://github.com/moebiussurfing/ofxSurfingImGuiExtra/blob/master/readme_media/gif/3_0_Layout_Docking2.gif)  
  </p>

</details>

## FEATURES

- Easy **Setup** and **Layout**.
- **ofParameter Helpers**.
- **ImGui Widgets** ported to **oF ofParameters**.
- Useful methods and **snippets** to **speed-up layout** and **workflow**.
- A **Layout Presets Engine**.
- **Docking Helpers**.
- Cool **Themes**.
- **Mouse Wheel** control with finetune (*+Ctrl*).

## CODE

ofApp.h
ofApp.h
```.cpp
#include "ofxSurfingImGui.h"

ofxSurfingGui ui;
ofParameter<bool> bGui{"Show Gui", true};
ofParameterGroup params;
..
```
ofApp.cpp
```.cpp
void ofApp::draw() 
{
    ui.begin();
    {
        if (ui.beginWindow(bGui))
        {
            // ImGui widgets goes here.
            ui.AddGroup(params);
            ..
            ui.endWindow();
        }
    }
    ui.end();
}
```

<details>
  <summary>More ImGui Widgets</summary>
  <p>

- Big Toggles and Buttons

- Vertical and Horizontal Sliders

- Range Sliders

- Styled Knobs

- Tree folders

- Inactive, hidden or locked styles

- Hide labels and values

- DearWidgets

- Gradient Color Designer

- Matrix Selectors

- Enum combos selectors

- Progress bars and waiting spinners

- Files Browser

- Curve Editors

- Bubbles Notifier System
  
  </p>
  </details>

## DEPENDENCIES

* [ofxImGui](https://github.com/Daandelange/ofxImGui/)  
  - THE _AWESOME_ [@Daandelange](https://github.com/Daandelange)'s **FORK**.
  - You **MUST** use this one! 
* [ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers)
* [ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp). / _Not required. For examples._  

`data.zip` assets like some font files to put into `OF_APP/bin/.`  

**NOTE**: The font file for the currently used theme is **JetBrainsMono-Bold.ttf**. If that font is not located, then it will search for a legacy font called **telegrama_render.otf**. If none of that fonts are located (then `/data` can also be empty), it will work too, but using the default bundled font from **ImGui**.  

<details>
  <summary>Why an ofxImGui FORK?</summary>
  <p>

- What's new on the [@Daandelange FORK](https://github.com/Daandelange/ofxImGui/) vs [legacy](https://github.com/jvcleave/ofxImGui) **ofxImGui** ? 
  
  - Multi context / instances: 
    
    - Several windows from different add-ons without colliding.  
  
  - Easy to update to future **NEW ImGui** versions.  
    Currently this fork is linked to the [develop branch](https://github.com/jvcleave/ofxImGui/tree/develop) on the original **ofxImGui** from **@jvcleave**.  
    And will be probably merged into the master branch.  
    
    </p>
    </details>

## CURRENT SYSTEMS

- **Windows 10** / **VS 2022** / GitHub [patch-release](https://github.com/openframeworks/openFrameworks/tree/patch-release) branch.  
- **macOS 11.6.7 Big Sur** / **Xcode 13.2.1** / **oF 0.11.2**

## AUTHOR

An add-on by **moebiusSurfing**.  
*( ManuMolina ) 2021-2022*  

## THANKS

_All source snippets and widgets from other authors are linked into header files. Thanks!_  
_Thanks [@alptugan](https://github.com/alptugan) for macOS testing._  

## LICENSE

**MIT License**
