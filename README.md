ofxSurfingImGui
=============================

#### WORK IN PROGRESS
### **BUG 1**:  
	* When adding many times a parameter or others with a not unique name.  
	* Widgets collides between them. Only some instance work well. (Sometimes)  
### **BUG 2**:  
	* Layout engine fails a bit on nesting indented groups.  
	* Broken width recalculation and "unlimited" growing when auto-size.  
	* Workaround fix using CollapsingHeader instead of TreeNodeEx but I would like the indented nested groups.

---------------------------------------------------------

## Overview
**ofxSurfingImGui** is a helper add-on with _Snippets / Helpers / LayoutManagement / Widgets_ to easy integrate **ImGui** into **openFrameworks**.

## Features 
* Requires the _awesome_ @**Daandelange**'s fork: 
    - Why? Easy to update to future **new ImGui** versions and multi context/instances.
* **ImGui Widgets**: big toggles and buttons, range sliders, DearWidgets...etc.
* **Layout Manager** to speed up **windows creation** and fit-widgets-width-to-window sizes.
* Included my **Dark Theme**.

### IMPORTANT CHANGES (vs ofxImGui helpers)  
- Simplified **OF Helpers** to use **ofParameters** easy and better. 
    * _ImHelpers.h_ has been rewritten to _ofxSurfing_ImGui_Helpers.h_.
    * Widgets, windows/trees now are more customizable. 
	* Removed old windows/tree methods. Now must use **RAW ImGui** code.
	* Removed all the WindowOpen/Settings stuff.
	* Removed all the old _GetUniqueName_ engine from **ofxImGui**. 
    * Now using PushId(1)/PopID() on each widget.

## Examples Screenshots

### 1_Widgets
* Shows **ofParameter** helpers with full/half/third/quarter width buttons, toggles, DearWidgets, range sliders and ofxImGui standard params.  

<!-- ![image](/docs/Capture1.PNG?raw=true "image")   -->
<img src="docs/Capture1.PNG" width="80%" height="80%">

---------------------------------------------------------

### 2_Layout_Basic
* Uses **ofxSurfing_ImGui_LayoutManager.h**  
* Speed up ofxImGui instantiation, windows and layouts. 
* Includes **ofParameter** helpers and extra widgets.  

<!-- ![image](/docs/Capture2.PNG?raw=true "image")   -->
<img src="docs/Capture2.PNG" width="80%" height="80%">

---------------------------------------------------------

### 3_Layout_TypesEngine
* Uses **ofxSurfing_ImGui_WidgetsTypes.h** and **ofxSurfing_ImGui_Helpers.h**
* A more powerfull **Layout Engine** to improve "responsive" layouts.
* Draw each **ofParameter** types with different appearance.
    * Example 1: Draw a **float parameter** as slider (default), drag nuber or/and +/- stepper box.
    * Example 2: Draw a **bool parameter** as a check box (default), or as a big toggle button with custom dimensions.
* Especially useful when params are into an **ofParameterGroup**.

* Queue settings for a parameter to define configurations to be applied when the widget is drawn. 
* Available customization options:
    * Hide the parameter.
    * Set an **ImGui::SameLine** after the widget.
    * Add a final vertical spacing after the widget.
    * Set the widget width to divide the panel width and fit a defined amount of widgets per row/line.

<!-- ![image](/docs/Capture4.PNG?raw=true "image")   -->
<img src="docs/Capture4.PNG" width="80%" height="80%">

---------------------------------------------------------

## Usage
* Look at the examples.

## Dependencies
[ofxImGui](https://github.com/Daandelange/ofxImGui/tree/ofParameters-Helpers-Test) from @**Daandelange**  
[ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp) [Not required. For some examples only]  

## Useful Links
https://github.com/HankiDesign/awesome-dear-imgui  
https://github.com/soufianekhiat/DearWidgets  
https://github.com/yumataesu/ImGui_Widgets  
https://github.com/njazz/AutomationCurveEditor  
https://github.com/leiradel/ImGuiAl  
https://github.com/aiekick/ImTools/tree/main/LayoutManager  

## TODO
* Add more examples and ImGui RAW widgets.

## Tested Systems
- **Windows10** / **VS2017** / **OF ~0.11**

## Author
An addon by **@moebiusSurfing**  
*( ManuMolina ) 2021*  

## License
**MIT License**
