#include "devmidi.h"
#include "midi_wrap.h"
//#include "imgui/imgui.h"
#include "ofxImGui.h"

#include <stdio.h> // for sprintf_s

/*----------------------------*/
/* Core init/update/teardown. */
/*----------------------------*/

static MIDIDeviceConfig midi_device_config[] =
{
	MIDIDeviceConfig("Midi Fighter Twister", MIDI_CONTINUOUS_CONTROLLER_RELATIVE),
	MIDIDeviceConfig("Midi Fighter 3D"),
};

static int write_idx = 0;
static MIDIState twister[2];
static MIDIState fighter[2];

static MIDIState* twister_prev;
static MIDIState* twister_curr;
static MIDIState* fighter_prev;
static MIDIState* fighter_curr;

void devmidiInit() {
	midiInit(midi_device_config, sizeof(midi_device_config) / sizeof(midi_device_config[0]));
}
void devmidiTerm() {
	midiTerm();
}
void devmidiUpdate() {
	if (midiGetState(&twister[write_idx], 0)) {
	}
	if (midiGetState(&fighter[write_idx], 1)) {
	}
	twister_curr = &twister[write_idx];
	twister_prev = &twister[1 - write_idx];
	fighter_curr = &fighter[write_idx];
	fighter_prev = &fighter[1 - write_idx];
	write_idx = 1 - write_idx;
}

/*--------------------*/
/* Generic functions. */
/*--------------------*/

static bool Press(MIDIState* curr, MIDIState* prev, int button) {
	return (curr->note_ons[button] - prev->note_ons[button]) > 0;
}
static bool Release(MIDIState* curr, MIDIState* prev, int button) {
	return (curr->note_offs[button] - prev->note_offs[button]) > 0;
}
static bool Down(MIDIState* curr, MIDIState* prev, int button) {
	return curr->note_ons[button] > prev->note_offs[button];
}
static bool ButtonPress(const char* id, MIDIState* curr, MIDIState* prev, int button) {
	return ImGui::Button(id) || Press(curr, prev, button);
}
static bool ButtonRelease(const char* id, MIDIState* curr, MIDIState* prev, int button) {
	return ImGui::Button(id) || Release(curr, prev, button);
}
static bool RadioButton(const char* id, MIDIState* curr, MIDIState* prev, int button, int* v, int v_button) {
	bool touched = false;
	if (Press(curr, prev, button)) {
		*v = v_button;
		touched = true;
	}
	return ImGui::RadioButton(id, v, v_button) || touched;
}
static bool Checkbox(const char* id, MIDIState* curr, MIDIState* prev, int button, bool* v) {
	bool touched = false;
	if (Press(curr, prev, button)) {
		*v = !*v;
		touched = true;
	}
	return ImGui::Checkbox(id, v) | touched;
}
static bool CheckboxMomentary(const char* id, MIDIState* curr, MIDIState* prev, int button, bool* v) {
	bool touched = false;
	if (Press(curr, prev, button) || Release(curr, prev, button)) {
		*v = !*v;
		touched = true;
	}
	return ImGui::Checkbox(id, v) | touched;
}
static bool SliderFloat(const char* id, MIDIState* curr, MIDIState* prev, int knob, float* v, float v_min, float v_max, const char* format, float power) {
	float knob_scale = 1.0f / 100.0f;
	if (format) {
		const char* dig = format;
		while (*dig && (*dig++ != '.'));
		if (*dig) {
			knob_scale = 1.0f / powf(10.0f, float(atoi(dig)));
		}
	}
	int del = curr->value[knob] - prev->value[knob];
	float linear_v = power == 1.0f ? *v : powf(*v, 1.0f / power);
	linear_v = min(v_max, max(v_min, linear_v + del * knob_scale));
	*v = power == 1.0f ? linear_v : powf(linear_v, power);

	return ImGui::SliderFloat(id, v, v_min, v_max, format, power) || del != 0;
}
static bool SliderFloatN(int components, const char* id, MIDIState* curr, MIDIState* prev, const int* knobs, float* v, const float* v_defaults, float v_min, float v_max, const char* format, float power) {
	ImGui::BeginGroup();
	ImGui::PushID(id);
	ImGui::PushItemWidth(ImGui::CalcItemWidth() / components);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImGui::GetStyle().ItemInnerSpacing);
	bool touched = false;
	for (int i = 0; i < components; ++i) {
		ImGui::PushID(i);
		touched |= SliderFloat("", curr, prev, knobs[i], v + i, v_min, v_max, format, power);
		ImGui::SameLine();
		if (v_defaults) {
			if (ButtonRelease("def", curr, prev, knobs[i])) {
				v[i] = v_defaults[i];
				touched = true;
			}
			ImGui::SameLine();
		}
		ImGui::PopID();
	}
	ImGui::Text(id);
	ImGui::PopStyleVar();
	ImGui::PopItemWidth();
	ImGui::PopID();
	ImGui::EndGroup();
	return touched;
}
static void Print(int components, const char* id, MIDIState* curr, MIDIState* prev, const int* knobs, float* v, const char* format) {
	bool any_pressed = false;
	for (int i = 0; i < components; ++i)
		any_pressed |= Press(curr, prev, knobs[i]);
	if (any_pressed) {
		static char buff[256];
		sprintf_s(buff, sizeof(buff), "%s: ", id);
		DEVMIDI_PRINT(buff);	
		char* w = buff;
		for (int i = 0; i < components; ++i) {
			if (i > 0)
				w += sprintf_s(w, sizeof(buff), ", ");
			w += sprintf_s(w, sizeof(buff), format, v[i]);
		}
		DEVMIDI_PRINT(buff);
		DEVMIDI_PRINT("\n");
		ImGui::SetClipboardText(buff);
	}
}
static bool SliderFloatNClickPrint(int components, const char* id, MIDIState* curr, MIDIState* prev, const int* knobs, float* v, float* v_defaults, float v_min, float v_max, const char* format, float power) {	
	(void)v_defaults;
	Print(components, id, curr, prev, knobs, v, format);
	return SliderFloatN(components, id, curr, prev, knobs, v, 0, v_min, v_max, format, power);
}
static bool SliderFloatNClickToggle(int components, const char* id, MIDIState* curr, MIDIState* prev, const int* knobs, float* v, float* v_defaults, float v_min, float v_max, const char* format, float power) {
	(void)v_defaults;
	bool touched = false;
	for (int i = 0; i < components; ++i) {
		if (Release(curr, prev, knobs[i])) {
			// Toggle to the extreme that is farthest from the current value.
			if (fabs(v[i] - v_min) < fabs(v[i] - v_max))
				v[i] = v_max;
			else
				v[i] = v_min;
			touched = true;
		}
	}
	return SliderFloatN(components, id, curr, prev, knobs, v, 0, v_min, v_max, format, power) || touched;
}
static bool ColorEditN(int components, const char* id, MIDIState* curr, MIDIState* prev, const int* knobs, float* v, float* v_defaults, ImGuiColorEditFlags flags) {
	if (!v_defaults)
		Print(components, id, curr, prev, knobs, v, "%.3f");

	bool touched = false;
	float edit[4];
	/* Copy color into the edit by default. */
	for (int i = 0; i < components; ++i)
		edit[i] = v[i];
	/* If we are editing in HSV and it's not the native format, convert into that first. */
	bool convert_to_hsv = (flags & ImGuiColorEditFlags_DisplayHSV) && !(flags & ImGuiColorEditFlags_InputHSV);
	if (convert_to_hsv)
		ImGui::ColorConvertRGBtoHSV(v[0], v[1], v[2], edit[0], edit[1], edit[2]);
	/* Perform the editing operation. */
	for (int i = 0; i < components; ++i) {
		int del = curr->value[knobs[i]] - prev->value[knobs[i]];
		edit[i] += del * 1.0f / 256.0f;
		/* In HSV, loop the color. In RGB, saturate it. */
		if ((convert_to_hsv || (flags & ImGuiColorEditFlags_InputHSV)) && i == 0)
			edit[i] = edit[i] - floorf(edit[i]);
		else
			edit[i] = max(0.0f, min(1.0f, edit[i]));
		if (v_defaults) {
			if (Release(curr, prev, knobs[i])) {
				edit[i] = v_defaults[i];
				touched = true;
			}
		}
		touched |= del != 0;
	}
	/* Convert back to RGB if we converted to HSV earlier. */
	if (convert_to_hsv) {
		ImGui::ColorConvertHSVtoRGB(edit[0], edit[1], edit[2], v[0], v[1], v[2]);
		v[3] = edit[3];
	}
	else {
		for (int i = 0; i < components; ++i)
			v[i] = edit[i];
	}

	/* Perform reset to defaults, if needed. */
	if (v_defaults) {
		for (int i = 0; i < components; ++i) {		
			if (Release(curr, prev, knobs[i])) {
				edit[i] = v_defaults[i];
				touched = true;
			}
		}
	}

	if (components == 3)
		return ImGui::ColorEdit3(id, v, flags) || touched;
	else if (components == 4)
		return ImGui::ColorEdit4(id, v, flags) || touched;
	else {
		assert(false);
		return false;
	}
}

/*----------------------------------------------*/
/* Specific functions tuned to the midi device. */
/*----------------------------------------------*/

// I have my device with it's cord up and away from me, and I want knob 0 to be the lower left hand corner.
static int twisterKnobRemap(int knob) {
	// I don't know how to deal with more than 16 knobs yet.
	if (knob > 15) return 0;
	// First we need to flip the button upside down. So remap it to a 4x4, flip the y, then go back to idx.
	int x = knob % 4;
	int y = knob / 4;
	y = 3 - y;
	return x + y * 4;
}
// I have my device with it's cord up away from me, and I want button 0 to be the lower left hand corner.
static int fighterButtonRemap(int button) {
	// I don't know how to deal with more than 16 buttons yet.
	if (button > 15) return 0;
	return 51 - button; // first set of fighter buttons go from 36 to 51
}

bool twisterSliderFloat(const char* id, int knob, float* v, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob) };
	return SliderFloatNClickPrint(1, id, twister_curr, twister_prev, knobs, v, 0, v_min, v_max, format, power);
}
bool twisterSliderFloat2(const char* id, int knob0, int knob1, float* v, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1) };
	return SliderFloatNClickPrint(2, id, twister_curr, twister_prev, knobs, v, 0, v_min, v_max, format, power);
}
bool twisterSliderFloat3(const char* id, int knob0, int knob1, int knob2, float* v, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2) };
	return SliderFloatNClickPrint(3, id, twister_curr, twister_prev, knobs, v, 0, v_min, v_max, format, power);
}
bool twisterSliderFloat4(const char* id, int knob0, int knob1, int knob2, int knob3, float* v, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2), twisterKnobRemap(knob3) };
	return SliderFloatNClickPrint(4, id, twister_curr, twister_prev, knobs, v, 0, v_min, v_max, format, power);
}
bool twisterSliderFloatClickDefault(const char* id, int knob, float* v, float v_default, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob) };
	return SliderFloatN(1, id, twister_curr, twister_prev, knobs, v, &v_default, v_min, v_max, format, power);
}
bool twisterSliderFloat2ClickDefault(const char* id, int knob0, int knob1, float* v, float* v_defaults, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1) };
	return SliderFloatN(2, id, twister_curr, twister_prev, knobs, v, v_defaults, v_min, v_max, format, power);
}
bool twisterSliderFloat3ClickDefault(const char* id, int knob0, int knob1, int knob2, float* v, float* v_defaults, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2) };
	return SliderFloatN(3, id, twister_curr, twister_prev, knobs, v, v_defaults, v_min, v_max, format, power);
}
bool twisterSliderFloat4ClickDefault(const char* id, int knob0, int knob1, int knob2, int knob3, float* v, float* v_defaults, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2), twisterKnobRemap(knob3) };
	return SliderFloatN(4, id, twister_curr, twister_prev, knobs, v, v_defaults, v_min, v_max, format, power);
}
bool twisterSliderFloatClickToggle(const char* id, int knob, float* v, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob) };
	return SliderFloatNClickToggle(1, id, twister_curr, twister_prev, knobs, v, 0, v_min, v_max, format, power);
}
bool twisterSliderFloat2ClickToggle(const char* id, int knob0, int knob1, float* v, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1) };
	return SliderFloatNClickToggle(2, id, twister_curr, twister_prev, knobs, v, 0, v_min, v_max, format, power);
}
bool twisterSliderFloat3ClickToggle(const char* id, int knob0, int knob1, int knob2, float* v, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2) };
	return SliderFloatNClickToggle(3, id, twister_curr, twister_prev, knobs, v, 0, v_min, v_max, format, power);
}
bool twisterSliderFloat4ClickToggle(const char* id, int knob0, int knob1, int knob2, int knob3, float* v, float v_min, float v_max, const char* format, float power) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2), twisterKnobRemap(knob3) };
	return SliderFloatNClickToggle(4, id, twister_curr, twister_prev, knobs, v, 0, v_min, v_max, format, power);
}
bool twisterColorEdit3(const char* id, int knob0, int knob1, int knob2, float col[3], ImGuiColorEditFlags flags) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2) };
	return ColorEditN(3, id, twister_curr, twister_prev, knobs, col, 0, flags);
}
bool twisterColorEdit4(const char* id, int knob0, int knob1, int knob2, int knob3, float col[4], ImGuiColorEditFlags flags) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2), twisterKnobRemap(knob3) };
	return ColorEditN(4, id, twister_curr, twister_prev, knobs, col, 0, flags);
}
bool twisterColorEdit3ClickDefault(const char* id, int knob0, int knob1, int knob2, float col[3], float col_default[3], ImGuiColorEditFlags flags) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2) };
	return ColorEditN(3, id, twister_curr, twister_prev, knobs, col, col_default, flags);
}
bool twisterColorEdit4ClickDefault(const char* id, int knob0, int knob1, int knob2, int knob3, float col[4], float col_default[4], ImGuiColorEditFlags flags) {
	int knobs[] = { twisterKnobRemap(knob0), twisterKnobRemap(knob1), twisterKnobRemap(knob2), twisterKnobRemap(knob3) };
	return ColorEditN(4, id, twister_curr, twister_prev, knobs, col, col_default, flags);
}
bool twisterKnobButton(const char* id, int knob) {
	return ButtonPress(id, twister_curr, twister_prev, twisterKnobRemap(knob));
}
bool fighterRadioButton(const char* id, int button, int* v, int v_button) {
	return RadioButton(id, fighter_curr, fighter_prev, fighterButtonRemap(button), v, v_button);
}
bool fighterCheckbox(const char* id, int button, bool* v) {
	return Checkbox(id, fighter_curr, fighter_prev, fighterButtonRemap(button), v);
}
bool fighterCheckboxMomentary(const char* id, int button, bool* v) {
	return CheckboxMomentary(id, fighter_curr, fighter_prev, fighterButtonRemap(button), v);
}
int  twisterKnobValue(int knob) {
	return twister_curr->value[twisterKnobRemap(knob)];
}
int  twisterKnobDelta(int knob) {
	return twister_curr->value[twisterKnobRemap(knob)] - twister_prev->value[twisterKnobRemap(knob)];
}
bool twisterKnobPress(int knob) {
	return Press(twister_curr, twister_prev, twisterKnobRemap(knob));
}
bool twisterKnobRelease(int knob) {
	return Release(twister_curr, twister_prev, twisterKnobRemap(knob));
}
bool twisterKnobDown(int knob) {
	return Down(twister_curr, twister_prev, twisterKnobRemap(knob));
}
bool fighterButton(const char* id, int button) {
	return ButtonPress(id, fighter_curr, fighter_prev, fighterButtonRemap(button));
}
bool fighterPress(int button) {
	return Press(fighter_curr, fighter_prev, fighterButtonRemap(button));
}
bool fighterRelease(int button) {
	return Release(fighter_curr, fighter_prev, fighterButtonRemap(button));
}
bool fighterDown(int button) {
	return Down(fighter_curr, fighter_prev, fighterButtonRemap(button));
}