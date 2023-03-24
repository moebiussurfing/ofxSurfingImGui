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

- Super Easy **setup**.
- **Multiple instances** around your classes and **ofxAddons**.
- **ofParameter helpers**:
  - Many RAW **DearImGui widgets** adapted.
  - Added custom useful widgets.
- Useful **API methods** and **Snippets**: 
  - Help on **Windows** and **Widgets**.
  - **Speed-Up** responsive Layout helpers.
  - Simplify **workflow**.
  - Internal params and persistent settings.
- Four active **font sizes** for labels and paragraphs.
- Extra **Mouse Control**: 
  - Wheel for tweaking:
    -  _+Ctrl_ to finetune.
  - Right-click:
    - To Reset to param center.
    - _+Ctrl_ to Reset to min.
    - _+Alt_ to Reset to max.
- **Themes** with **Editor** ( WIP ).
- Windows Organizer, aligner, cascade and group/linker.
- **Log System** with custom tags.
- **Notifier System**.
- **Text Editor** ( WIP )
- **Layout Presets Engine**. ( WIP )
- **Docking Helpers**. ( WIP )

<br>

<details>
  <summary>WIDGETS LIST</summary>
  <p>
    
- Big Toggles and Buttons.
- Vertical and Horizontal Sliders.
- Range Sliders.
- Styled Knobs.
- Tree and indented folders.
- Floating tooltips, labels and values.
- Dropdown / Combo index selector and names.
- Matrix buttons to an index selector.
- Bundled widgets like arrows linked to int params for browsing.
- DearWidgets.
- Gradient Color Designer.
- Progress bars and waiting spinners.
- Files Browser.
- Curve Editors.
- Log and Notifier System.
- Text Editor, for live coding or text content.
- Profile Plotters.
- ...
  
  </p>
  </details>

<br>
<br>

[EXAMPLES SCREENSHOTS](/Examples/README.md)  
 
<br>
  
## EXAMPLE: HelloWorld

<br>

![](/Examples/00_HelloWorld/Capture.PNG)  

<details>
  <summary>CODE</summary>

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

</details>

<br>

## DEPENDENCIES

* [ofxImGui](https://github.com/Daandelange/ofxImGui/tree/develop) Dear ImGui v1.89.4 / BackEnd_:  
  - The **AWESOME** [@Daandelange](https://github.com/Daandelange)'s **FORK**.
  - You **MUST use this one**! 
  
* [ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers):  
  - _Removed and partially integrated into core soon_.

* [assets.zip](assets.zip):
  - Located in the add-on root path. Mainly font file(s) to put into each project `OF_APP/bin/data/`.  

<br>

<details>
  <summary>NOTE ABOUT THE FONTS</summary>

The single font file for the currently used theme is **JetBrainsMono-Bold.ttf**. If that font is not located, then it will search for a legacy font called **telegrama_render.otf**. If none of that fonts are located, it will work too, but using the default bundled font from **ImGui**. (So `/data` can also be completely empty too.) 

</details>

<details>
  <summary>WHY ANOTHER ofxImGui FORK?</summary>
  <p>

- What's new on the [@Daandelange FORK](https://github.com/Daandelange/ofxImGui/tree/develop) vs the [legacy](https://github.com/jvcleave/ofxImGui) **ofxImGui** from [@jvcleave](https://github.com/jvcleave)? 
  
  - Multi context / instances: 
    
    - Several windows from different add-ons without colliding.  
  
  - Easy to update to future **NEW ImGui** releases.  
    Currently this fork is linked to the [develop branch](https://github.com/jvcleave/ofxImGui/tree/develop) on the original **ofxImGui** from **@jvcleave**.  
    And will be probably merged into the master branch.  
    
    </p>
    </details>

<br>

* [ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp) / _Not required. Only for some examples._

<br>

## CURRENT SYSTEMS

- **Windows 10** / **VS 2022** / 
    * GitHub [OF patch-release](https://github.com/openframeworks/openFrameworks/tree/patch-release) branch.
    * Last official release [OF 0.11.2](https://openframeworks.cc/download/).
- **macOS 12.5 Monterey** / **Xcode 14.2** / [Intel] / [OF 0.11.2](https://openframeworks.cc/download/). 
   

<br>

# AUTHOR

An add-on by **moebiusSurfing**.  
*( ManuMolina ) 2021-2023*  

## THANKS

_**SUPER THANKS** to [@Daandelange](https://github.com/Daandelange) for **HIS AWESOME ofxImGui (mantained) FORK** and some **macOS** fixes._  

_Thanks to [@alptugan](https://github.com/alptugan) for **macOS** testing and some fixes._  

_All source snippets and widgets from other authors are linked into header files as credits. Thanks!_  

## LICENSE

**MIT License**
