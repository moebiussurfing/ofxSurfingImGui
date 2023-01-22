<br>

<h1>

ofxSurfingImGui.  
A [DearImGui](https://github.com/ocornut/imgui) **Toolkit**  
for **openFrameworks** projects.  

</h1>

<br>
<br>

## WORK IN PROGRESS!

<br>
<br>

( _Some **new examples**, testing or new incoming widgets, and complementary docs are **now moved** to [ofxSurfingImGuiExtra](https://github.com/moebiussurfing/ofxSurfingImGuiExtra) as a **Testing Sandbox**._ )  

<br>

# FEATURES

- Easy **setup**.
- **Multiple instances** around your classes and **ofxAddons**.
- **ofParameter helpers**:
  - Many RAW **DearImGui widgets** ported.
  - Added custom useful widgets.
- Useful **API methods** and **snippets**: 
  - Help on **windows** and **widgets**.
  - **Speed-Up** responsive layout.
  - Simplify **workflow**.
  - Internal params and persistent settings.
- 4 active **font sizes**.
- Extra **Mouse Control**: 
  - Wheel for tweaking:
    -  _+Ctrl_ to finetune.
  - Right-click:
    - To reset to param center.
    - _+Ctrl_ to reset to min.
    - _+Alt_ to reset to max.
- **Themes** and editor.
- Windows organizer, aligner and linker.
- **Log System** with custom tags.
- **Notifier System**. ( WIP )
- **Layout Presets Engine**. ( WIP )
- **Docking Helpers**. ( WIP )

<br>

<details>
  <summary>MORE IMGUI WIDGETS</summary>
  <p>
    
- Big Toggles and Buttons.
- Vertical and Horizontal Sliders.
- Range Sliders.
- Styled Knobs.
- Tree folders.
- Inactive, hidden or locked styles.
- Floating tooltip, labels and values.
- Dropdown / Combo index selector and names.
- Matrix buttons to an index selector.
- Bundled widgets like arrows linked to int params browsing.
- DearWidgets.
- Gradient Color Designer.
- Progress bars and waiting spinners.
- Files Browser.
- Curve Editors.
- Bubbles Notifier System.
- Profile Plotters.
  
  </p>
  </details>

<br>

[EXAMPLES SCREENSHOTS](/Examples/README.md)  
 
<br>
  
## EXAMPLE: HelloWorld

<br>

![](/Examples/00_HelloWorld/Capture.PNG)  

### ofApp.h

```.cpp
#include "ofxSurfingImGui.h"

ofxSurfingGui ui;
ofParameter<bool> bGui{ "Show", true };

ofParameter<bool> bEnable{ "Enable", true };
ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
ofParameterGroup params{ "MyGroup", bEnable, speed };
```

### ofApp.cpp

```.cpp
void ofApp::draw() 
{
    ui.Begin();
    {
        /* Put windows here */

        if (ui.BeginWindow(bGui))
        {
            /* Put widgets here */

            ui.AddLabelBig("HELLO WORLD");
            ui.AddSpacing();
            ui.Add(bEnable, OFX_IM_TOGGLE_BIG_BORDER_BLINK);
            ui.Add(speed, OFX_IM_HSLIDER);
            ui.AddSpacingSeparated();
            ui.AddGroup(params, SurfingGuiGroupStyle_Collapsed);

            ui.EndWindow();
        }
    }
    ui.End();
}
```

<br>

## DEPENDENCIES

* [ofxImGui](https://github.com/Daandelange/ofxImGui/)  
  - THE **AWESOME** [@Daandelange](https://github.com/Daandelange)'s **FORK**.
  - You **MUST USE THIS ONE**! 
* [ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers)

* [assets.zip](assets.zip): located in the add-on root path. Mainly font file(s) to put into each project `OF_APP/bin/data/`.  

<br>

<details>
  <summary>NOTE ABOUT THE FONTS</summary>

The font file for the currently used theme is **JetBrainsMono-Bold.ttf**. If that font is not located, then it will search for a legacy font called **telegrama_render.otf**. If none of that fonts are located (then `/data` can also be empty), it will work too, but using the default bundled font from **ImGui**.  

</details>

<details>
  <summary>WHY ANOTHER ofxImGui FORK?</summary>
  <p>

- What's new on the [@Daandelange FORK](https://github.com/Daandelange/ofxImGui/) vs [legacy](https://github.com/jvcleave/ofxImGui) **ofxImGui** ? 
  
  - Multi context / instances: 
    
    - Several windows from different add-ons without colliding.  
  
  - Easy to update to future **NEW ImGui** versions.  
    Currently this fork is linked to the [develop branch](https://github.com/jvcleave/ofxImGui/tree/develop) on the original **ofxImGui** from **@jvcleave**.  
    And will be probably merged into the master branch.  
    
    </p>
    </details>

<br>

* [ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp) / _Not required. Only for some examples._

<br>

## CURRENT SYSTEMS

- **Windows 10** / **VS 2022** / 
    * GitHub [patch-release](https://github.com/openframeworks/openFrameworks/tree/patch-release) branch.
    * Last official release [oF 0.11.2](https://openframeworks.cc/download/).
- **macOS 11.6.7 Big Sur** / **Xcode 13.2.1** / [oF 0.11.2](https://openframeworks.cc/download/).

<br>

# AUTHOR

An add-on by **moebiusSurfing**.  
*( ManuMolina ) 2021-2023*  

## THANKS

_**SUPER THANKS** to [@Daandelange](https://github.com/Daandelange) for **HIS AWESOME ofxImGui FORK**._  
_All source snippets and widgets from other authors are linked into header files as credits. Thanks!_  
_Thanks to [@alptugan](https://github.com/alptugan) for **macOS** testing._  

## LICENSE

**MIT License**
