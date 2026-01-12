# Manual Testing Log

## Session 1: Initial Build System verification

**Date:** 2026-01-04
**Tester:** GK222JW
**Goal:** Verify if the project builds out-of-the-box on the current environment.
**Steps:**

1. Ran `meson build` (incorrect command, corrected to `meson setup build`).
2. Ran `meson setup build`.
   **Results:**

- Build configuration failed.
- Error 1: `gdbus-codegen` not found (missing `glib2-devel`).
- Error 2: `scdoc` missing.
- Error 3: `iniparser` missing for `libcava` subproject.
  **Status:** 🔴 Failed

## Session 2: Configuration Path Verification

**Date:** 2026-01-04
**Tester:**  GK222JW
**Goal:** specific custom configuration loading and file structure.
**Steps:**

1. Attempted to copy config from `/etc/xdg/waybar` (failed, files not present).
2. Located source resources in `resources/config.jsonc`.
3. Copied to local test directory `test-configs/chaos-config.json`.
   **Results:**

- Confirmed default resources are located in `resources/` source folder.
- Successfully set up isolation test config.
  **Status:** 🟢 Passed

## Session 3: Dependency Resolution Plan

**Date:** 2026-01-07
**Tester:** GK222JW
**Goal:** Identify and document exact missing packages for Arch Linux environment.
**Steps:**

1. Analyzed build logs.
2. Verified package names in `pacman` (`glib2-devel`, `scdoc`, `iniparser`).
3. Created `DEPENDENCY_ERRORS.md` to track resolution.
   **Results:**

- Clear path to fix build errors documented.
  **Status:** 🟡 In Progress (Ready for verify)

## Session 4: UI Stress Testing - Rapid Reloading & Invalid Configs

**Date:** 2026-01-07
**Tester:** gk222jw
**Goal:** Attempt to crash the application by feeding it malformed configurations and triggering rapid state changes.
**Steps:**

1. **Action:** Launched Waybar with `test-configs/chaos-config.json`.
2. **Action:** Injected syntax errors into JSON (unclosed keys, trailing commas) and saved violently to trigger hot-reload.
   * *Result:* Waybar correctly outputted JSON parsing errors to stderr and did not crash. It kept the previous valid state or showed an error bar.
3. **Action:** Rapidly sent `SIGUSR2` (reload signal) in a loop `while true; do pkill -SIGUSR2 waybar; sleep 0.1; done`.
   * *Result:* UI flickered intently. Memory usage spiked slightly but stabilized. No segmentation fault observed.
     **Status:** 🟢 Passed (Robust against reload spam)

## Session 5: Content Overflow & "Chaos" Style Injection

**Date:** 2026-01-07
**Tester:** GK222JW
**Goal:** Break the layout engine by forcing unexpected content sizes.
**Steps:**

1. **Action:** Edited `custom/media` module to output a string of 5000 emoji characters.
   * *Result:* The bar expanded horizontally off-screen (Wayland handles this by clipping usually). Did not crash, but rendered useless unusable.
2. **Action:** Applied `chaos-style.css` with:
   ```css
   * { font-size: 200px; padding: 100px; margin: -50px; }
   ```

   * *Result:* GTK Inspector showed massive geometry calculations. The bar covered the entire screen. Interaction became impossible, but the process remained running.
3. **Action:** Set update interval to `0.001s` (1ms) for the battery module.
   * *Result:* CPU usage for Waybar increased to ~15%. UI remained responsive.
     **Status:** 🟡 Passed (Layout broke as expected, but application stability held)

## Session 6: Interaction Spam & Tooltip Edge Cases

**Date:** 2026-01-07
**Tester:** GK222JW
**Goal:** Trigger race conditions in event handlers.
**Steps:**

1. **Action:** Hovered rapidly between the Taskbar and Tray modules to trigger tooltip animations.
   * *Result:* Tooltips appeared/disappeared correctly.
2. **Action:** Clicked the "Workspaces" buttons while changing DPMS state (simulated monitor disconnect).
3. **Action:** Spammed scroll events on the PulseAudio module (volume change) while simultaneously muting/unmuting via external keybinds.
   * *Result:* Volume bar updated lag-free. No visual desync observed between bar state and actual audio state.
     **Status:** 🟢 Passed

## Session 7: "Release The Kraken" - Visual & Resource Stress

**Date:** 2026-01-07
**Tester:** GK222JW
**Goal:** Tests CSS layout engine resilience and custom script execution under high load/invalid states.
**Configuration:** `release-the-kraken-config.json` + `release-the-kraken-style.css`
**Steps:**

1. **Action:** Configured custom module `custom/kraken` to echo emoji-heavy string.
2. **Action:** Applied CSS with conflicting borders, negative margins, and global font overrides (`32px`, `Comic Sans`).
3. **Action:** Executed with `GDK_BACKEND=wayland`.
   **Results:**

- **Warning:** `[warning] Requested height: 30 is less than the minimum height: 81 required by the modules`.
- **Behavior:** Bar resized automatically to accommodate massive content (81px height).
- **Behavior:** "Permission denied" errors on input devices (expected permissions issue, not a crash).
- **Stability:** Application did NOT crash. Handled layout constraints gracefully (expanded).
  **Status:** 🟢 Passed (Resilient layout engine)

## Session 8: Logic Bombs - Recursion & Formatting

**Date:** 2026-01-07
**Tester:** GK222JW
**Goal:** Attack the configuration parser and string formatter (C++ `fmt` lib).
**Configuration:** `recursion-bomb.jsonc` (includes itself) & `test-configs/format-crash.jsonc` (invalid format strings).
**Steps:**

1. **Action:** Configured recursive include loop.
   * *Result:* Waybar logged `[warning] Unable to find resource file`. Included path resolution logic prevented infinite recursion loop safely.
2. **Action:** Configured a clock module with invalid python-style format string `"{:d}"` and overflow width `"{:999999999}"`.
   * *Result:* Waybar caught the exceptions: `[error] clock: format error: invalid width or precision`.
   * *Stability:* Modules failed to render text but application **kept running**.
     **Status:** 🟢 Passed (Exception handling is robust)

## Session 9: The "Module Spam" - Resource Exhaustion

**Date:** 2026-01-07
**Tester:** GK222JW
**Goal:** Force a crash by exhausting graphical resources (Cairo/GDK limits).
**Configuration:** `test-configs/spam-config.jsonc` (Generated: 1000 active clock modules).
**Steps:**

1. **Action:** Generated JSON with 1000 independent clock modules.
2. **Action:** Launched application.
   * *Log:* `Bar configured (width: 24000, height: 18)`.
   * *Error:* `(waybar:30740): Gdk-CRITICAL **: ... Unable to create Cairo image surface: invalid value (typically too big)`.
   * *Result:* **Core Dump / Crash**.
     **Status:** 🔴 Failed (Application successfully crashed via Allocation Failure)

## Session 10: New Scenarios Test
**Date:** 2026-01-07
**Tester:** GK222JW
**Goal:** Verify system stability under edge-case configurations.

### Scenario A: Zombie Processes (Script Timeout)
**Config:** `test-configs/zombie-script.jsonc` (Sleep 10s, Interval 1s)
**Result:** Passed.
- The bar launched successfully.
- Custom module execution did not block the main interface (asynchronous handling verified).
- No zombies detected accumulating in the process list during the short run.

### Scenario B: Corrupt Image Data
**Config:** `test-configs/corrupt-image.jsonc` (Image path = `/dev/urandom`)
**Result:** Passed (Graceful Failure).
- Log Output: `CRITICAL **: unhandled exception ... Couldn’t recognize the image file format`.
- **Verdict:** GTK/GdkPixbuf handled the exception. The application printed critical errors but **did not crash**. It continued running with the broken module invisible.

### Scenario C: CSS Infinite Animation Stress
**Config:** `test-configs/animation-stress.jsonc` + `css`
**Result:** Passed.
- High-speed CSS animations (0.01s duration) ran smoothly.
- Application resizing logic was triggered repeatedly due to font-size changes in the animation keyframes (`Requested height X is less than minimum...`), causing log spam but no functional failure.

