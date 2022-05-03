 
 ## WORK IN PROGRESS!

```
NOT FINISHED. A BIT BUGGY YET.
API WILL CHANGE.  
SOME EXAMPLES CAN BE REDUNDANT OR INCOMPLETE  
OR NEEDING TO BE UPDATED TO API CHANGES.
```



<details>
  <summary>RELEVANT CHANGES vs official ofxImGui ofParameter/ImHelpers</summary>
  <p>

- Simplified and improved **oF Helpers** to use **ofParameters**. 
  * _ImHelpers.h_ has been rewritten to _ofxSurfing_ImGui_ofHelpers.h_.
  * Now the _ofParameter_ widgets, _Windows_ and _Group/Trees_ are more customizable. 
  * Removed all the old internal _Windows/Tree_, _WindowOpen/Settings_ and _GetUniqueName_ methods from **ofxImGui**. 
  * Currently using a _PushId()/PopID()_ approach on each widget.  
    
- **NEW: _Layout/Styles Management_.**
- **NEW: _Docking helpers with an Engine for Layout Presets_.**
    </p>
    </details>




#### AVAILABLE CUSTOMIZATIONS:

    - Hide the parameter widget respecting the void space or not.
    - Make a parameter inactive disabling mouse interaction.  
    - Set an ImGui::SameLine() after the widget, to draw the next params at the same line.  
    - Add a final vertical spacing after the widget.  
    - Set the widget width to fit the panel width, passing the number of widgets per row/line.  
    - Queue styles for incoming parameters inside a group.  

#### API

```c++
void AddStyle(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1);
bool Add(ofAbstractParameter& aparam, SurfingImGuiTypes type = OFX_IM_DEFAULT, bool bSameLine = false, int amtPerRow = 1, int spacing = -1);
void AddGroup(ofParameterGroup& group, ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None, SurfingImGuiTypesGroups typeGroup = OFX_IM_GROUP_DEFAULT);
```



#### FEATURES

Instead of the **ofxImGui** behavior, where you can't change the param widget style, we will have:  
- A more powerful **Layout Engine** to improve: "responsive" layouts and customized widgets.  
- Draw each **ofParameter** type with different styles. 
- Especially useful when **ofParameters** are into an **ofParameterGroup**.  
- Queue settings for an **ofParameter** to define configurations to be applied when the widget is drawn when drawing a group. 
- You can hide or exclude some params to be drawn, to disable the mouse interaction, or to draw his void spacing. 
- You can customize how **ofParameterGroup** / **ImGui::Tree** are presented.



<BR>

<details>
  <summary>Some Reference Links</summary>
  <p>

https://github.com/altschuler/imgui-knobs -> Cute Knobs  
https://github.com/HankiDesign/awesome-dear-imgui -> Collected widgets  
https://github.com/soufianekhiat/DearWidgets -> Cute widgets already included  
https://github.com/yumataesu/ImGui_Widgets -> oF ready widgets  
https://github.com/aiekick/ImTools/tree/main/LayoutManager -> Layout helpers  
https://github.com/Organic-Code/ImTerm -> Interesting terminal to look into  
https://github.com/d3cod3/ofxVisualProgramming -> oF node patched system for inspiration  
https://github.com/d3cod3/Mosaic -> oF node patched system for inspiration  
https://github.com/mnesarco/imgui_sugar/blob/main/imgui_sugar.hpp -> Useful ImGui style macros  
https://github.com/njazz/AutomationCurveEditor -> Curve editor for param automations  
https://github.com/leiradel/ImGuiAl -> Some widgets    


<details>
  <summary>Title</summary>
  <p>

There's not an automatic-fully-functional, save preset/load theme designer!  
![image](/docs/2_Layout/2_4_Layout_ThemeEditor.PNG?raw=true "image")  
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



<details>
  <summary>SOME EXAMPLE CASES</summary>
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
  <summary>TODO</summary>
  <p>

* macOS testing and fixing. Any help on this is appreciated!  
* Split repo to simplify current examples. Move extra examples to new repo.
* Fix Bugs on all the ofParameter Helpers/Styles/Docking sections.
* Create some selected examples to simplify learning.
* Add more ImGui raw widgets/add-ons with examples.
* Convert some more widgets to ofParameters.
  </p>
</details>