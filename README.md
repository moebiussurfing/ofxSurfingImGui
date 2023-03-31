<br>

<h1>
  
ofxSurfingImGui.  
A [Dear ImGui](https://github.com/ocornut/imgui) **Toolkit**  
for [openFrameworks](https://openframeworks.cc/) projects.  
  
</h1>

<h3>
  
( An extension for [ofxImGui](https://github.com/Daandelange/ofxImGui/tree/develop). )    
  
</h3>

#### WORK IN PROGRESS!

<br>

## FEATURES

- **Simple Setup**:
  - Simplified user **workflow**.
  - Many useful **Internal states** and persistent settings:
    - Minimize, debug, extra, advanced, auto resize...
    - Log, Notifier and windows visibility and distribution. 
- **Multiple instances**:
  - Many windows around your classes and **ofxAddons**.
  - All together without colliding.
- **ofParameter Helpers**:
  - Many RAW **DearImGui widgets** adapted.
  - Added custom useful widgets.
- Useful **API methods** and **Snippets**: 
  - Help on populate **Windows** and **Widgets**.
  - **Speed-Up** responsive **Layout Helpers**.
- Four active **Font Sizes** for labels and paragraphs.
- Extra **Mouse Control**: 
  - Wheel for tweaking:
    -  _+Ctrl_ to finetune.
  - Right-Click:
    - To Reset to param Center.
    - _+Ctrl_ to Reset to Min.
    - _+Alt_ to Reset to Max.
- **Windows Organizer**:
    - Aligner, cascade and Group/Linker.
- **Log System**:
    - With custom tags.
- **Notifier System**:
    - With custom layout and styles.
- **Text Editor**: 
    - Language marks.
    - Font sizes, color themes.
    - Clipboard access and **undo/redo** history.
- **Image Inspector**:
    - With pixel color picker.
- **Themes**:
    - With styles **Editor** and serializers. ( WIP )
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

[EXAMPLES SCREENSHOTS](/Examples/README.md)  
 
# EXAMPLE: 00_HelloWorld

![](/Examples/00_HelloWorld/Capture.PNG)  

<details>
  <summary>CODE</summary>
  
#### ofApp.h

```.cpp
#include "ofxSurfingImGui.h"

ofxSurfingGui ui;
ofParameter<bool> bGui{ "Show", true };

ofParameter<bool> bEnable{ "Enable", true };
ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
ofParameterGroup params{ "MyGroup", bEnable, speed };
```

#### ofApp.cpp

```.cpp
void ofApp::draw() 
{
    ui.Begin();
    {
        /* Put windows here */

        if (ui.BeginWindow(bGui))
        {
            /* Put widgets here */

            ui.AddLabelBig("00_HelloWorld");
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

* [ofxImGui](https://github.com/Daandelange/ofxImGui/tree/develop): Dear ImGui v1.89.4 / BackEnd:  
  - The **AWESOME** [@Daandelange](https://github.com/Daandelange)'s **FORK**.
  - You **MUST use this one**! 

<details>
  <summary>OTHER</summary>  
  
* [ofxSurfingImGuiExtra](https://github.com/moebiussurfing/ofxSurfingImGuiExtra) / _**New WIP examples** and new incoming widgets: a **Testing Sandbox**._
* [ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp) / _Not required. Only for some examples._
* [ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers) / _Not required. Only for some examples._
* [imgui/wiki/Useful-Extensions](https://github.com/ocornut/imgui/wiki/Useful-Extensions#image-manipulation) / 3rd party modules/widgets that could be integrated.
* [imgui/labels/gallery](https://github.com/ocornut/imgui/labels/gallery) / Inspiration gallery from user's apps.

</details>

### DATA FILES

* **JetBrainsMono-Bold.ttf**: The font file for the default theme.  
* [assets.zip](assets.zip): (Optional) More font files from the same family. To put into each project `OF_APP/bin/data/`.  

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

## CURRENT SYSTEMS

- **Windows 10** / **VS 2022**
    * GitHub [OF patch-release](https://github.com/openframeworks/openFrameworks/tree/patch-release) branch.
    * Last official release [OF 0.11.2](https://openframeworks.cc/download/).
- **macOS 12.5 Monterey** / **Xcode 14.2** [OF 0.11.2](https://openframeworks.cc/download/). ( **Intel** )  
    * Not tested on **M1/M2 Apple Silicon** yet. ( Testers are welcome! ).

<br>

# AUTHOR

An addon by **moebiusSurfing**.  
*( ManuMolina ) 2021-2023*  

## THANKS

_**SUPER THANKS** to [@Daandelange](https://github.com/Daandelange) for **HIS AWESOME ofxImGui (maintained) FORK**, and some **macOS** fixes._  
_Thanks to [@alptugan](https://github.com/alptugan) for **macOS** testing and some fixes._  
_All source snippets and widgets from other authors are linked into header files as credits. Thanks!_  

## LICENSE

**MIT LICENSE**
