#pragma once

#include "ofxImGui.h"
#include "ofMain.h"
//#include "imgui/imgui.h" // for ImGuiColorEditFlags

/* Simple API to address my particular dev midi setup. */
/* Allows binding values to a particular midi controller and ImGui at the same time. */

/* Initialize the library (opens midi devices). Call once at app start. */
void devmidiInit();
/* Poll the midi data. Call once every frame, before the app reads the inputs. */
void devmidiUpdate();
/* Terminate the library (closes midi devices). Call once at app end. */
void devmidiTerm();

/* Standard ImGui Slider. On knob click, print the value to console and to clipboard. */
bool twisterSliderFloat(const char* id, int knob, float* v, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
bool twisterSliderFloat2(const char* id, int knob0, int knob1, float* v, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
bool twisterSliderFloat3(const char* id, int knob0, int knob1, int knob2, float* v, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
bool twisterSliderFloat4(const char* id, int knob0, int knob1, int knob2, int knob3, float* v, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
/* On knob click, reset value to the specified default. */
bool twisterSliderFloatClickDefault(const char* id, int knob, float* v, float v_default, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
bool twisterSliderFloat2ClickDefault(const char* id, int knob0, int knob1, float* v, float* v_defaults, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
bool twisterSliderFloat3ClickDefault(const char* id, int knob0, int knob1, int knob2, float* v, float* v_defaults, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
bool twisterSliderFloat4ClickDefault(const char* id, int knob0, int knob1, int knob2, int knob3, float* v, float* v_defaults, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
/* On knob click, toggle the value to min or max (whichever is farther from the current value). */
bool twisterSliderFloatClickToggle(const char* id, int knob, float* v, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
bool twisterSliderFloat2ClickToggle(const char* id, int knob0, int knob1, float* v, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
bool twisterSliderFloat3ClickToggle(const char* id, int knob0, int knob1, int knob2, float* v, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
bool twisterSliderFloat4ClickToggle(const char* id, int knob0, int knob1, int knob2, int knob3, float* v, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f);
/* Standard ImGui Color Edit. On knob click, print the value to console and to clipboard. */
bool twisterColorEdit3(const char* id, int knob0, int knob1, int knob2, float col[3], ImGuiColorEditFlags flags = 0);
bool twisterColorEdit4(const char* id, int knob0, int knob1, int knob2, int knob3, float col[4], ImGuiColorEditFlags flags = 0);
/* On knob click, reset value to the specified default. */
bool twisterColorEdit3ClickDefault(const char* id, int knob0, int knob1, int knob2, float col[3], float col_default[3], ImGuiColorEditFlags flags = 0);
bool twisterColorEdit4ClickDefault(const char* id, int knob0, int knob1, int knob2, int knob3, float col[4], float col_default[4], ImGuiColorEditFlags flags = 0);

/* Standard ImGui Button operated by knob click. */
bool twisterKnobButton(const char* id, int knob);
/* Raw knob value. */
int  twisterKnobValue(int knob);
/* Raw knob value delta from previous to current frame. */
int  twisterKnobDelta(int knob);
/* Was the knob pressed. */
bool twisterKnobPress(int knob);
/* Was the knob released. */
bool twisterKnobRelease(int knob);
/* Is the knob being held down. */
bool twisterKnobDown(int knob);

/* Standard ImGui Button. */
bool fighterButton(const char* id, int button);
/* Standard ImGui Radio Button. */
bool fighterRadioButton(const char* id, int button, int* v, int v_button);
/* Standard ImGui Checkbox. */
bool fighterCheckbox(const char* id, int button, bool* v);
/* A checkbox that is toggled both on Press and Release. The effect is a 'down' or 'momentary' checkbox. */
bool fighterCheckboxMomentary(const char* id, int button, bool* v);
/* Was the button pressed. */
bool fighterPress(int button);
/* Was the button released. */
bool fighterRelease(int button);
/* Is the button down. */
bool fighterDown(int button);

/*  - Custom convenience wrappers based on app-specific vector structs. */
/*  - Printing functions for when a knob is clicked.                    */
#include "devmidi_custom.h"