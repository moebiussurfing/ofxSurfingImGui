---
name: ofxsurfingimgui-gui-builder
description: Build, refactor, and scale openFrameworks GUIs using ofxSurfingImGui. Use when asked to create control panels, multi-window interfaces, docking layouts, iOS touch-friendly UI, or multi-instance/shared-context GUI architectures. Use when mapping ofParameter/ofParameterGroup data to widgets, special windows, and persistent UI state.
---

# ofxSurfingImGui GUI Builder

## Execution rule

Implement changes directly. Do not stop at planning unless the user explicitly asks for plan-only output.

## Core workflow

1. Identify the target UI shape.
- Detect whether the request is single-window, multi-window, docking, iOS/touch, or multi-instance.
- Infer missing details from existing `ofParameter` definitions and current project structure.

2. Choose mode.
- Use `ui.setup()` for standard desktop control panels.
- Use `IM_GUI_MODE_INSTANTIATED_DOCKING_RAW` for manual docking flows.
- Use `IM_GUI_MODE_INSTANTIATED_DOCKING_RAW_AUTOHANDLER` for simpler docking automation.
- Use `IM_GUI_MODE_INSTANTIATED_DOCKING` for layout-preset workflows.

3. Apply lifecycle contract.
- Keep strict frame pairing: `ui.Begin()` -> windows/widgets -> `ui.End()`.
- Keep strict window pairing: `BeginWindow*` -> `EndWindow*`.
- Use `ui.startup()` when using complex multi-window/preset flows.

4. Build windows.
- Use regular windows for small/medium GUIs.
- Use `addWindowSpecial(...)` + `BeginWindowSpecial(...)` for panel engines and editor-like apps.
- Use `addWindowExtra(...)` for utility windows.

5. Map parameters to widgets.
- Use `ui.Add(...)` and `ui.AddGroup(...)` as default.
- Prefer compact/expanded behavior via `ui.bMinimize` and `ui.isMaximized()`.
- Use larger styles for touch targets.
- Use raw ImGui only when layout needs exceed helper coverage.

6. Add modules only when relevant.
- Log: `ui.bLog`, `ui.AddToLog(...)`.
- Notifier: `ui.bNotifier`, `ui.AddToNotifier(...)`.
- Debug/profiler: `ui.bDebugDebuggerImGui`, profiler macros if needed.
- Theme/editor/image/console modules only when explicitly useful.

7. Add persistence.
- Set stable manager name before setup when multiple managers are possible: `ui.setName("...")`.
- Save UI state with `ui.save()` in `exit()` when deterministic save timing is needed.
- Save app parameters using `ofxImGuiSurfing::saveGroup/loadGroup`.

## Validation checklist

- Mode matches requested behavior.
- No missing `Begin/End` pairs.
- Window visibility toggles are explicit and coherent.
- Names/IDs are stable and collision-safe.
- iOS/touch UI avoids tiny dense controls.
- Persistence strategy is clear and consistent.

## Reference map inside this repository

- `Examples_0_Basic`: minimal lifecycle and first window.
- `Examples_1_Widgets`: widget/style usage patterns.
- `Examples_2_Modules`: log/notifier/debugger/theme/editor modules.
- `Examples_3_Engines`: special windows, docking, layout presets.
- `Examples_5_MultipleInstances`: shared vs per-class manager patterns.
- `Examples_6_iOS`: touch-oriented UI patterns.
- `architecture.md`: architecture rationale and design constraints.
- `skills.md`: reusable assistant-oriented implementation playbook.
