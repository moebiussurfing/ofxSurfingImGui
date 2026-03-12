# RULES.md

## 1. PURPOSE
Defines the minimal operational rules for the AI coding agent to safely interact with this openFrameworks project.

## 2. SCOPE
- The agent may read and edit files only inside the `/src` folder.
- Never modify or delete content in `/libs`, `/bin`, `/data`, or addons.
- Creating new files is allowed only after user confirmation.
- For an OF (openFrameworks) project placed into `openframeworks\apps\myApps\myProject\`.
  - There are some important folders where the AI AGENT could ask read permision to improve OF context knowledge:
    - `..\..\libs\openFrameworks\ofMain.h` -> The main class header that is included in all OF app project
    - `..\..\libs\openFrameworks` -> All the included OF Core classes
    - `..\..\addons` -> An app could use some addons that are placed here. The project will must name these addons in `addons.make` file.
  
## 3. CHANGE POLICY
- Do **not** alter existing functionality unless explicitly requested.
- Do **not** remove or rename functions, parameters, or variables without approval.
- Always ask before refactoring or restructuring code.
- When suggesting changes, explain their purpose and potential side effects.

## 4. CODE CONSISTENCY
- Follow the style, patterns, and naming defined in `AGENTS.md`.
- Comment in **English only**.
- Keep modular structure and avoid mixing unrelated logic.

## 5. SAFETY & DEPENDENCIES
- Do **not** introduce new libraries, addons, or dependencies unless approved.
- Avoid raw file system operations or external scripts.
- Do not execute system commands.

## 6. COMMUNICATION
- Ask the user before making assumptions.
- Offer alternatives when multiple solutions are possible.
- Keep all explanations short, clear, and technical.

## 7. PRIORITIES
1. Preserve existing behavior.
2. Maintain readability and modularity.
3. Optimize performance only when safe and necessary.

## 8. PROJECT OPERATIONS
- Do **not** edit documentation or markdown files massively; always ask before doing so.
- Do **not** perform any `git commit`, `push`, or version control actions automatically.
  - You may **suggest** a commit when several code changes have accumulated.
- Do **not** compile, run, or execute the project automatically.
  - The developer is responsible for manual builds and runs.
