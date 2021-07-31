/* Function print the knob values to console or elsewhere. */
/* Define to something like printf, but it only needs to handle a single const char* argument, not formatting. */
#define DEVMIDI_PRINT(str)

/* Some convenience wrappers, specific to this app's vector structs. */
/* For example:
inline bool twisterSliderFloat2ClickDefault(const char* id, int knob0, int knob1, float* v, vec2 v_defaults, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f) {
	return twisterSliderFloat2ClickDefault(id, knob0, knob1, v, (float*)&v_defaults, v_min, v_max, format, power);
}
inline bool twisterSliderFloat3ClickDefault(const char* id, int knob0, int knob1, int knob2, float* v, vec3 v_defaults, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f) {
	return twisterSliderFloat3ClickDefault(id, knob0, knob1, knob2, v, (float*)&v_defaults, v_min, v_max, format, power);
}
inline bool twisterSliderFloat4ClickDefault(const char* id, int knob0, int knob1, int knob2, int knob3, vec4 v, float* v_defaults, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.2f", float power = 1.0f) {
	return twisterSliderFloat4ClickDefault(id, knob0, knob1, knob2, knob3, v, (float*)&v_defaults, v_min, v_max, format, power);
}
inline bool twisterColorEdit3ClickDefault(const char* id, int knob0, int knob1, int knob2, float col[3], vec3 col_default, ImGuiColorEditFlags flags = 0) {
	return twisterColorEdit3ClickDefault(id, knob0, knob1, knob2, col, (float*)&col_default, flags);
}
inline bool twisterColorEdit4ClickDefault(const char* id, int knob0, int knob1, int knob2, int knob3, float col[4], vec4 col_default, ImGuiColorEditFlags flags = 0) {
	return twisterColorEdit4ClickDefault(id, knob0, knob1, knob2, knob3, col, (float*)&col_default, flags);
}
*/