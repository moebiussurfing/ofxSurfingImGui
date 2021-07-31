#pragma once

/* The maximum number of inputs in one MIDI device (spec). */
#define MIDI_INPUT_COUNT_MAX 128

enum {
	MIDI_CONTINUOUS_CONTROLLER_ABSOLUTE = 0,
	MIDI_CONTINUOUS_CONTROLLER_RELATIVE = 1,
};

struct MIDIDeviceConfig {
	const char* name;
	int continuous_mode;
	MIDIDeviceConfig(const char* _name, int _continuous_mode = MIDI_CONTINUOUS_CONTROLLER_ABSOLUTE) : name(_name), continuous_mode(_continuous_mode) {}
};

struct MIDIState {
	int note_ons[MIDI_INPUT_COUNT_MAX];
	int note_offs[MIDI_INPUT_COUNT_MAX];
	int value[MIDI_INPUT_COUNT_MAX];
};

/* Initialize given a list of device configurations. */
/* The order of the configurations determines the device id which is used to get state. */
void midiInit(MIDIDeviceConfig* configs, int configs_count);

/* Close all active midi devices. */
void midiTerm();

/* Get the state for a given config index, which corresponds to the array order that was passed to init. */
/* If there is more than one device of that type, use num to select which one. */
/* Returns true if the device was found and valid state was written. Otherwise, false is returned, and state is untouched. */
bool midiGetState(MIDIState* state_out, int config_idx, int num = 0);