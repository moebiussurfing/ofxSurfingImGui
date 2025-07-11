<br>
  
<h1>

ofxSurfingImGui.

A [Dear ImGui](https://github.com/ocornut/imgui) **Toolkit**  
for [openFrameworks](https://openframeworks.cc/)  
desktop app projects.  

</h1>

<h3>
  
An extension for [ofxImGui](https://github.com/jvcleave/ofxImGui/tree/develop).    
  
</h3>

<br>

<h3>
<em>
WORK IN PROGRESS!
</em>
</h3>


<br>

# OVERVIEW
- **Bundled batteries** for your full **Desktop OF Apps**.
- **ofParameter** Widgets.
- **Layout** and **Style** Helpers.
- Useful **Modules**/**Systems**.
- **Workflow Engines** for the final user.
- **NEW!** iOS support. ( WIP )

<br>

## FEATURES
- **Simple Setup**:
  - Simplified coder and user **workflow**.
  - Many useful **Internal states** and persistent settings:
    - Minimize, debug, extra, advanced, windows auto resize...
    - Log, Notifier, and windows visibility and distribution. 
    - Global Scale.
- Useful **API methods** and **Snippets**: 
  - Help on populate **Windows** and **Widgets**.
  - **Speed-Up** responsive **Layout Helpers**.
- **ofParameter Helpers**:
  - Many RAW **DearImGui widgets** adapted.
  - Added custom useful widgets.
- **Multiple instances**:
  - Many windows around your classes and **ofxAddons**.
  - All together without colliding.
- Four active **Font Sizes** for labels, widgets, and text paragraphs.
  - Four optional extra fonts for alternate **monospaced** and **non-monospaced**.
- Extra **Mouse Control**: 
  - Wheel for tweaking:
    -  _+Ctrl_ to finetune.
  - Right-Click:
    - To Reset to param **Center**.
    - _+Ctrl_ to Reset to **Min**.
    - _+Alt_ to Reset to **Max**.
- **Themes Editor** example:  ( WIP )
    - **20+ bundled themes** compilation. 
    - Hardcoded and `.ini` files.
    - File serializers, A-B compare, sizes and/or colors.
    - **Manager**, **Demo Window** and **Tester Widgets**.

## MODULES / SYSTEMS
- **Log System**:
    - With custom **tags**.
- **Notifier System**:
    - With **custom** layout and styles.
- **Debugger System**:
    - Metrics: frame rate and frame time.
    - Profiler: Cpu and Gpu measurements.
- **Text Editor System**: 
    - Language marks with custom marked **keywords**.
    - Font sizes, color themes.
    - **Clipboard** access and **undo/redo** history.
- **Image Inspector System**:
    - Zoom with pixel color picker.
- **Console System**: ( WIP )
    - Basic console/**terminal** module.
    - Call methods/**commands** by typing into the console.

## ENGINES
- **Windows Organizer**:
    - Aligner, cascade, and Group/Linker.
- **Layout Presets Engine**. ( WIP )
- **Docking Helpers**. ( WIP )
 
<br>

# SCREENSHOTS

- [Examples_0_Basic](/Examples_0_Basic/README.md)  
- [Examples_1_Widgets](/Examples_1_Widgets/README.md)  
- [Examples_2_Modules](/Examples_2_Modules/README.md)  
- [Examples_3_Engines](/Examples_3_Engines/README.md)  
- [Examples_5_MultipleInstances](/Examples_5_MultipleInstances/README.md)  
- [Examples_6_iOS](/Examples_6_iOS/README.md)  

## EXAMPLE: 00_HelloWorld
![](/Examples_0_Basic/01_HelloWorld/Capture.PNG)
<details>
  <summary>CODE</summary>
  
#### ofApp.h

```.cpp
#pragma once
#include "ofMain.h"

#include "ofxSurfingImGui.h"

class ofApp : public ofBaseApp
{
  public:
  void draw();

  ofParameter<bool> bEnable{ "Enable", true };
  ofParameter<float> speed{ "Speed", .5f, 0.f, 1.f };
  ofParameterGroup params{ "MyGroup", bEnable, speed };

  ofParameter<bool> bGui{ "Show", true };

  ofxSurfingGui ui;
};
```

#### ofApp.cpp

```.cpp

#include "ofApp.h"

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

# REQUERIMENTS

## IMGUI OF BACKEND

* Required: [ofxImGui](https://github.com/jvcleave/ofxImGui/tree/develop) from **@jvcleave**'s repository and **develop** branch.
  - Dear [ImGui v1.91.5](https://github.com/ocornut/imgui) BackEnd for [OF](https://openframeworks.cc/).
  - Is the **AWESOME** [@Daandelange's FORK](https://github.com/Daandelange/ofxImGui/tree/develop). (Now mirrored to **@jvcleave**'s develop branch!)
    - You **MUST use this one**! 
    - **WARNING!** Do not use the [@jvcleave's respository](https://github.com/jvcleave/ofxImGui) **master branch**!

<details>
  <summary>WHY ANOTHER BACKEND FORK?</summary>
  <p>

- What's new on the [@Daandelange's ofxImGui FORK](https://github.com/Daandelange/ofxImGui/tree/develop) vs the [@jvcleave's ORIGINAL REPOSITORY (master branch)](https://github.com/jvcleave/ofxImGui)? 
  - Multi context/instances: 
    - Several ImGui windows from different addons without colliding.  
  - Easy to update to future **NEW ImGui** releases.  
    Currently, this fork is linked to the original [develop branch from @jvcleave](https://github.com/jvcleave/ofxImGui/tree/develop).  
    And will be probably merged into the master branch someday.  
    
 </p>
</details>

## DATA ASSET FILES

* Recommended: [Geist-Bold.ttf](data/assets/fonts/Geist-Bold.ttf)
  - The monospaced font file for the default theme.
  - Put into `OF_APP/bin/data/assets/fonts/`.  
* Optional: [data.zip](data.zip)
  - More font files (non-monospaced alternative) from the same family.
  - Put into each **OF project** `OF_APP/bin/data/`.  
* Extras: [dataExtras.zip](dataExtras.zip) - More fonts, theme files...etc

<details>
  <summary>ABOUT THE FONTS</summary>  
  
The single font file for the currently used theme is **Geist-Bold.ttf**. If that font is not located, it will search for a legacy font called **JetBrainsMono-Bold.ttf**. If none of those fonts are located, it will work too, but using the default embedded **ProggyClean.ttf** font from **ImGui**. (So `OF_APP/bin/data/` can also be completely empty too!) 

</details>

<br>

<details>
  <summary>RELATED LINKS</summary>  
  
* [ofxSurfingImGuiExtra](https://github.com/moebiussurfing/ofxSurfingImGuiExtra)
  - _My **Testing Sandbox** with **New WIP examples** and new incoming widgets._
* [imgui/wiki/Useful-Extensions](https://github.com/ocornut/imgui/wiki/Useful-Extensions#image-manipulation)
  - 3rd party ImGui modules/widgets that could be integrated.
* [imgui/labels/gallery](https://github.com/ocornut/imgui/labels/gallery)
  - Inspiration Gallery from ImGui user's apps.
* [ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp)
  - _Not required. Only for some examples._
* [ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers)
  - _Not required. Only for some examples._
  
</details>

<br>

## CURRENT SYSTEMS

- **Windows 11** / **Visual Studio 2022**. (Main develop)
    * [GitHub](https://github.com/openframeworks/openFrameworks) master branch. (Could break sometimes!)
    * Last official release [OF 0.12.1](https://openframeworks.cc/download/).
    * Previous release **OF 0.12.0** and **OF 0.11.2** have they own branches.
- NEW! iOS simulators and device running iOS 18.5. Simulator _iPad(A16)_ and _iPad (10th / iOS 18.6)_ device.  
- **macOS 16.0 Tahoe beta** / **Xcode 16.4** / Silicon Apple M1. / [OF 0.12.1] 

<details>
  <summary>Older</summary>  

- **macOS 15.5 Sequoia** / **Xcode 16.4** / [OF 0.12.1] / **M1/M2 Apple Silicon**. **iOS** requires testing.
- **macOS 14.5 Sonoma** / **Xcode 15.4** / [OF 0.12+] / **M1/M2 Apple Silicon**. **iOS** requires testing.
- **macOS 12.5 Monterey** / **Xcode 14.2** [OF 0.11.2](https://openframeworks.cc/download/). **Intel**.  

</details>

<br>

## THANKS

_Thanks to [Omar Cornut](https://github.com/ocornut) for the fantastic [Dear ImGui](https://github.com/ocornut/imgui)._  

_**SUPER THANKS** to [@Daandelange](https://github.com/Daandelange) for **HIS AWESOME ofxImGui (maintained) FORK**, and some **macOS** fixes._  

_Thanks to [@roymacdonald](https://github.com/roymacdonald) for **iOS ofxImGui** fixing._  

_Thanks to [@alptugan](https://github.com/alptugan) for **macOS** testing and some fixes._  

_Thanks to [@AndyJarosz](https://github.com/MadlyFX) for financing and using the lib for his [Reality Field Virtual Production System](https://loledvirtual.gumroad.com/l/realityfield) project for [LOLED VIRTUAL](https://loledvirtual.com/)._  

_All source snippets and widgets from other authors are linked into header files as credits. Thanks!_  

<br>

# AUTHOR

An addon by **moebiusSurfing**.  
*( ManuMolina ) 2021-2025*  

<br>

## LICENSE

[**MIT LICENSE**](https://github.com/moebiussurfing/ofxSurfingImGui/blob/master/LICENSE)
