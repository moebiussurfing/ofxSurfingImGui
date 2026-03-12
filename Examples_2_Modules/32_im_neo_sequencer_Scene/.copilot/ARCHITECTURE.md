# ofxSurfingImGui - architecture and practical usage guide

## Purpose and scope

This document explains how `ofxSurfingImGui` is structured and how to use it effectively in real openFrameworks applications. It is not an exhaustive API reference. Instead, it focuses on the operational architecture you need to build maintainable GUIs quickly, including lifecycle, window management, docking, persistence, modules, and multi-instance patterns.

`ofxSurfingImGui` extends `ofxImGui` with a manager-oriented approach that is tightly integrated with `ofParameter` and `ofParameterGroup`. The typical entry point is:

- `#include "ofxSurfingImGui.h"`
- `ofxSurfingGui ui;` (alias of `SurfingGuiManager`)

---

## 1) Core architecture layers

The addon can be understood as six cooperating layers.

### 1.1 Integration layer (your `ofApp` or classes)

You define app state with `ofParameter` and `ofParameterGroup`, then expose it through the UI manager. This keeps rendering and interaction close to state definitions.

### 1.2 Orchestration layer (`SurfingGuiManager`)

This is the central runtime object. It owns the frame contract (`Begin/End`), internal UI states, setup/startup flow, docking hooks, special windows, layout presets, and module gateways.

### 1.3 Widget adaptation layer (`widgets/*`, `ofHelpers.h`)

This layer maps `ofParameter` types to styled ImGui controls (`Add`, `AddGroup`, slider/toggle variants, knobs, color widgets, text widgets, etc.). It adds quality-of-life behavior such as wheel interaction and compact style variants.

### 1.4 Layout and window engine layer (`LayoutHelpers.h`, `WidgetsManager.h`, `WindowsOrganizer.h`)

This layer handles responsive sizing, per-row distribution, unique IDs, special window orchestration, alignment, cascade, and visibility management.

### 1.5 Module layer (optional systems)

Examples show plug-in modules for common app needs:

- log window (`WindowLog`)
- notifications (`SurfingNotifier`)
- debugger/profiler (`SurfingDebugger`)
- text editor (`SurfingTextEditor`)
- image inspector (`SurfImageInspect`)
- theme editor (`SurfingThemeEditor`)
- console (`SurfingConsole`)

### 1.6 Persistence and utility layer (`utils/SurfingHelpers.h`)

This layer serializes/deserializes parameter groups and internal settings to JSON and works together with ImGui `.ini` layout persistence.

---

## 2) Lifecycle model

Understanding lifecycle is key to avoid fragile GUI behavior.

### 2.1 Construction

`SurfingGuiManager` subscribes to update/draw/key events and initializes parameter structures. It is designed to be robust even when setup calls are omitted in simple prototypes.

### 2.2 Setup phase

Call `ui.setup(...)` in `setup()`.

Common modes:

- `IM_GUI_MODE_INSTANTIATED`: default, no docking.
- `IM_GUI_MODE_INSTANTIATED_DOCKING_RAW`: manual docking orchestration.
- `IM_GUI_MODE_INSTANTIATED_DOCKING_RAW_AUTOHANDLER`: docking with helper workflow.
- `IM_GUI_MODE_INSTANTIATED_DOCKING`: layout presets engine + docking workflow.

For multi-instance projects, call `ui.setName("MyUI")` before `setup()` to isolate settings and reduce collisions.

### 2.3 Startup phase

`startup()` finalizes runtime behavior: theme setup, module initialization, settings loading, optional layout preset setup, and organizer initialization.

If startup/settings are missing on first run, the manager can force default visibility/reset behavior to avoid initial window overlap. This is visible in internal flags and first-run logic.

### 2.4 Frame phase

Contract per frame:

1. `ui.Begin()`
2. draw windows and widgets
3. `ui.End()`

This is non-negotiable for stable behavior. `Begin()` resets ID/layout internals, starts ImGui context, updates engines. `End()` flushes auxiliary windows/modules, finalizes interaction state, and ends the context.

### 2.5 Exit/persistence

`ui.save()` can be called explicitly in `exit()` for deterministic persistence timing. Depending on compile flags, save-on-change and save-on-exit behavior may also be active internally.

---

## 3) Window model and control surface

The addon supports three practical window categories.

### 3.1 Regular windows

Main pattern:

- `if (ui.BeginWindow(bGui)) { ... ui.EndWindow(); }`

Using `ofParameter<bool>` as visibility toggle is a key design choice. It keeps window visibility in the same parameter ecosystem as app state.

### 3.2 Special windows (engine-managed)

You register windows during setup:

- `ui.addWindowSpecial("Window 0")`
- or `ui.addWindowSpecial(bGui_WindowX)`

Then draw with:

- `ui.BeginWindowSpecial(index or toggle)`
- `ui.EndWindowSpecial(...)`

This is the foundation for multi-panel apps and docking workflows.

### 3.3 Extra windows

`addWindowExtra(...)` lets the manager include non-special utility windows in global workflows.

### 3.4 Internal toggles as UI state

Internal parameters like `bMinimize`, `bAutoResize`, `bAdvanced`, `bHelp`, `bLog`, `bNotifier`, `bGui_Organizer`, `bGui_Aligners`, and `bGui_SpecialWindows` act as shared control surface. Examples use these toggles to switch between compact and expanded UI layers.

---

## 4) Docking and layout presets

There are two major docking styles.

### 4.1 Raw docking flow

Used in `DockingRaw*` examples:

1. `ui.Begin()`
2. `ui.BeginDocking()`
3. draw window content
4. `ui.EndDocking()`
5. `ui.End()`

### 4.2 Preset-driven docking flow

Used in layout engine examples with `IM_GUI_MODE_INSTANTIATED_DOCKING`. The manager coordinates panel visibility and ImGui layout states as presets.

Important details:

- Presets include both parameter groups and ImGui `.ini` layout states.
- `setPresetsNames(...)` customizes preset labels.
- `setupLayout(...)` configures preset slots.

This is useful when end users need workflow-ready GUI scenes rather than developer-only control panels.

---

## 5) Widget system and style strategy

The widget layer is intentionally broad: from compact mini controls to large touch-friendly widgets and specialized styles.

Key concepts:

- `ui.Add(parameter, style)` is the central primitive.
- `ui.AddGroup(group, style/group mode)` renders nested structures quickly.
- `ui.AddStyle(...)` pre-binds style rules for parameters and can reduce repetitive code.
- `LayoutHelpers` and `WidgetsManager` keep responsive widths and row packing coherent.
- Unique name/ID helpers prevent collisions when the same parameter is rendered multiple times in different styles.

Raw ImGui remains fully available. Many examples mix `ui.Add(...)` with direct ImGui calls. If you use raw trees/collapsing headers, refreshing layout in those sections is often necessary to preserve sizing consistency.

---

## 6) Persistence model

Two persistence channels coexist.

### 6.1 Internal manager persistence

Manager states are saved in JSON files under the global path (`Gui/` by default), plus ImGui `.ini` layout files.

### 6.2 App parameter persistence

Use helper functions from `SurfingHelpers.h`:

- `loadGroup(ofParameterGroup&, path)`
- `saveGroup(ofParameterGroup&, path)`
- shorthand `load(...)`, `save(...)`

These functions create missing enclosing directories and serialize groups as pretty JSON.

Practical recommendation:

- use manager persistence for UI behavior/layout
- use app group persistence for domain parameters
- keep both explicit in your architecture

---

## 7) Multi-instance patterns

Examples demonstrate three valid architectures.

### 7.1 One manager per class

Each class owns `ofxSurfingGui`. Good isolation, independent state files (especially when each instance sets a unique `setName(...)`).

### 7.2 Shared manager pointer

A main `ofApp` owns one manager and passes `ofxSurfingGui*` to modules. Good for unified look-and-feel and centralized window organization.

### 7.3 Hybrid service object

A dedicated GUI controller class (`mySurfingAppGui` pattern) owns manager and draws windows for other systems. Good for larger applications with strict separation of domain logic and UI orchestration.

---

## 8) Module integration patterns

### 8.1 Log and notifier

You can register custom tags and route events to both systems. This is useful for live tooling dashboards and operator-facing feedback.

### 8.2 Debugger/profiler

`SurfingDebugger` exposes CPU/GPU task macros and ImGui visual diagnostics. It is optional but practical for real-time workloads.

### 8.3 Text editor and image inspector

These modules can be toggled as tool windows inside your normal frame flow.

### 8.4 Theme tooling

Theme editor examples show two workflows:

- ship hardcoded/default themes
- load/save external theme files for runtime iteration

---

## 9) iOS notes

The iOS examples keep the same high-level manager pattern (`ui.setup`, `ui.Begin`, windows, `ui.End`) while adapting control density and touch ergonomics. Big widgets and simplified panel layouts are emphasized. Docking exists in test examples but should be treated as platform-sensitive and validated per target.

---

## 10) Recommended blueprint for new projects

Use this order when starting a fresh GUI.

1. Define parameter model (`ofParameter` + groups).
2. Decide mode (`INSTANTIATED`, `DOCKING_RAW`, or `DOCKING` preset engine).
3. Set stable UI name (`setName`) before setup if multiple managers can exist.
4. Register special windows if you need multi-panel organization.
5. Call `setup`, then `startup` when your flow needs explicit control.
6. Keep strict `Begin -> windows -> End` pairing every frame.
7. Add persistence for both manager state and domain parameter groups.
8. Add modules incrementally (log/notifier/debugger/theme/editor) as app complexity grows.

Following this blueprint reproduces the stable patterns used across `Examples_0_Basic`, `Examples_1_Widgets`, `Examples_2_Modules`, `Examples_3_Engines`, `Examples_5_MultipleInstances`, and `Examples_6_iOS`.
