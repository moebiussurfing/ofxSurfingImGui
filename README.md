ofxSurfingImGui
=============================

## Overview
**ofxSurfingImGui** is a helper add-on with _Snippets / Helpers / LayoutManagement / Widgets_ to easy integrate **ImGui** into **openFrameworks**.

## Features 
* Requires the _awesome_ @**Daandelange**'s fork: 
	- easy to update to new ImGui versions and multi context/instances.
* **ImGui Widgets**: big toggles and buttons, range sliders, DearWidgets...etc.
* **Layout Manager** to speed up **windows creation** and fit-widgets-width-to-window sizes.
* Included my **Dark Theme**.

### IMPORTANT CHANGES (vs ofxImGui helper)  
- Simplified **OF Helpers** to use **ofParameters** easy. 
	* _ImHelpers.h_ has been rewritted to _ofxSurfing_ImGui_Helpers.h_.
	* Widgets, windows and tree now are more customizable. 
- Removed old windows/tree methods. Now must use **RAW ImGui** code.
- Removed all the WindowOpen/Settings stuff.
- Removed all the old _GetUniqueName_ engine from **ofxImGui**. 
	* Now using PushId(1)/PopID() on each widget.

## Examples Screenshots

### 1_Widgets
* **ofParameter** helpers with full/half width buttons, range sliders and DearWidgets.  

![image](/docs/Capture1.PNG?raw=true "image")  

![image](/docs/Capture2.PNG?raw=true "image")  

### 2_Layout
* Uses **ofxSurfing_ImGui_LayoutManager.h**  
* Speed up ImGui layouts with **ofParameter** helpers.  

![image](/docs/Capture3.PNG?raw=true "image")  

## Usage
* Look at the examples.

## Dependencies
[ofxImGui](https://github.com/Daandelange/ofxImGui/tree/ofParameters-Helpers-Test) from @**Daandelange**  

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
