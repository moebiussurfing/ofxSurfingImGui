# ofxSurfingImGui Skills Guide

## Goal

Use this guide to help an assistant create production-ready GUIs for new openFrameworks projects using `ofxSurfingImGui`, quickly and consistently.

The intent is to convert a user request like "build me a GUI for this app" into a clear implementation strategy that matches real patterns from this repository.

---

## What this guide should enable

When a user asks for a new interface, the assistant should be able to:

1. Choose the correct UI architecture mode (`basic`, `special windows`, `docking`, `iOS touch`, `multi-instance`).
2. Generate a clean `ofApp` integration with `ofxSurfingGui` and `ofParameter`-based state.
3. Build useful window structure and widget mapping from parameters.
4. Add optional modules (log, notifier, debugger, editor, theme) only when relevant.
5. Preserve stable lifecycle and persistence behavior.

---

## Trigger phrases

Apply this guide when requests include phrases such as:

- "create a GUI"
- "add control panel"
- "use ofxSurfingImGui"
- "make this app configurable"
- "add docking"
- "multi-window GUI"
- "touch/iOS GUI"

---

## Required input contract

Before generating code, infer or collect these items:

1. Parameters to expose (names, ranges, defaults, type).
2. Desired window topology:
   - single window
   - multiple named windows
   - special windows managed by organizer
3. Platform target:
   - desktop
   - iOS/touch
4. Layout style:
   - no docking
   - raw docking
   - layout presets engine
5. Persistence expectation:
   - UI state only
   - UI + domain parameters

If some items are missing, choose sensible defaults and proceed.

---

## Mode selection rules

Choose one primary mode:

1. `IM_GUI_MODE_INSTANTIATED`
Use for most apps and first iterations.

2. `IM_GUI_MODE_INSTANTIATED_DOCKING_RAW`
Use when user explicitly wants docking behavior and manual docking control.

3. `IM_GUI_MODE_INSTANTIATED_DOCKING_RAW_AUTOHANDLER`
Use when user wants docking with less manual orchestration.

4. `IM_GUI_MODE_INSTANTIATED_DOCKING`
Use when user wants docking plus layout presets/workspace workflows.

For iOS, keep window count low and prioritize bigger controls and touch-friendly spacing.

---

## Default implementation blueprint

Follow this sequence unless the user asks otherwise.

1. **State model**
- Define `ofParameter` and `ofParameterGroup` first.
- Add one top-level visibility toggle: `ofParameter<bool> bGui{"GUI", true};`.
- For multi-window UIs, add one toggle per window (`bGui_Main`, `bGui_Audio`, etc.).

2. **UI manager declaration**
- Add `ofxSurfingGui ui;` in class scope.

3. **Setup**
- Call `ui.setName("ProjectOrModuleName")` before setup when multiple UI managers may exist.
- Call `ui.setup(...)` with the selected mode.
- Add `ui.startup()` when explicit startup control is needed (recommended for complex/multi-window flows).

4. **Draw frame contract**
- Always use strict pairing:
  - `ui.Begin();`
  - draw windows/widgets
  - `ui.End();`

5. **Window contract**
- Standard windows:
  - `if (ui.BeginWindow(bGui_Window)) { ... ui.EndWindow(); }`
- Special windows:
  - register in setup: `ui.addWindowSpecial(...)`
  - draw in frame: `if (ui.BeginWindowSpecial(index_or_toggle)) { ... ui.EndWindowSpecial(...); }`

6. **Docking contract**
- In raw docking flows:
  - `ui.BeginDocking();`
  - draw docked windows
  - `ui.EndDocking();`

7. **Exit/persistence**
- Optionally call `ui.save();` in `exit()` for deterministic state persistence.
- For app parameters, use `ofxImGuiSurfing::saveGroup(...)` and `loadGroup(...)`.

---

## Widget mapping rules

Use parameter type and intent to choose controls:

- `bool`: toggle family (`OFX_IM_TOGGLE_*`, rounded variants).
- `float/int`: slider/stepper/drag/knob styles.
- grouped state: `ui.AddGroup(group, style)`.
- compact layouts: `ui.isMaximized()` gates (show advanced controls only when expanded).
- touch/iOS: prefer bigger controls (`BIG` variants, large spacing).

Prefer `ui.Add(...)` and `ui.AddGroup(...)` over raw ImGui for consistency.
Use raw ImGui only for special layout cases and refresh layout when needed.

---

## Optional modules (enable only when requested)

1. **Log system**
- Use `ui.bLog` and `ui.AddToLog(...)`.
- Add tags when event categories matter.

2. **Notifier system**
- Use `ui.bNotifier` and `ui.AddToNotifier(...)`.

3. **Debugger/profiler**
- Use `ui.bDebugDebuggerImGui` and profiler macros if performance instrumentation is requested.

4. **Theme workflows**
- Expose theme toggles/edit windows only when user asks for skinning/theme editing.

5. **Editor/Image/Console modules**
- Add as independent optional tool windows.

---

## Multi-instance strategies

Use one of these intentionally:

1. **Shared manager pointer (`ofxSurfingGui*`)**
- Best for unified visual behavior across modules.

2. **One manager per class**
- Best for strict isolation and independent settings.
- Always give each manager a unique `setName(...)`.

3. **Dedicated GUI service object**
- Best for larger apps where UI orchestration is separated from domain logic.

---

## Output quality checklist

Before finishing, validate:

1. `Begin/End` and `BeginWindow/EndWindow` pairs are complete.
2. Selected mode matches requested features.
3. Visibility toggles exist for each window and are named clearly.
4. No duplicate or unstable window names.
5. Parameter ranges/defaults are coherent and usable.
6. Optional modules are only added when useful.
7. Persistence pathing strategy is clear (`ui.save`, `saveGroup/loadGroup`, `setName`).
8. iOS/touch layouts avoid dense tiny controls.

---

## Fast prompt templates for users

These are examples users can give to the assistant:

1. "Create a basic single-window GUI for these parameters using ofxSurfingImGui."
2. "Build a 4-window special-window layout (Main, Audio, Video, Debug) with organizer toggles."
3. "Set up raw docking with window presets for an editor-like workflow."
4. "Make an iOS-friendly GUI with large touch widgets and minimal panel complexity."
5. "Refactor this app to one shared `ofxSurfingGui*` across modules."
6. "Add log and notifier modules to this existing GUI and route key events into both."

---

## Source pattern map (from this repository)

Use these folders as canonical references:

- `Examples_0_Basic`: minimal lifecycle and first-window patterns.
- `Examples_1_Widgets`: widget style coverage and grouped parameter layouts.
- `Examples_2_Modules`: log/notifier/debugger/theme/editor integrations.
- `Examples_3_Engines`: special windows, docking, layout presets engines.
- `Examples_5_MultipleInstances`: shared-vs-local manager architecture.
- `Examples_6_iOS`: touch-first adaptations and iOS constraints.

When generating new UI code, prefer patterns already proven in these folders.
