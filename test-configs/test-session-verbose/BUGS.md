# Bug Report: Resource Exhaustion Crash

**ID:** BUG-001

**Evaluator:** GK222JW
**Title:** Application Crash (Core Dump) when rendering excessive number of modules
**Severity:** High (Crash)
**Component:** Rendering Engine (Cairo/GDK)
**Date Detected:** 2026-01-07
**Environment:** Arch Linux, Wayland, GDK Backend, Git `v0.14.0`

## Description

Waybar crashes with a core dump when attempting to render a configuration containing 1,000 active clock modules. The crash is caused by an allocation failure in the underlying graphics library (Cairo/GDK) when determining the surface size for the bar window.

## Steps to Reproduce

1. **Generate the malicious configuration:**
   Create a file `spam-config.jsonc` with 1,000 distinct module entries. You can use this Python one-liner:

   ```bash
   python3 -c 'import json; print(json.dumps({"layer": "top", "modules-left": [f"clock#{i}" for i in range(1000)], **{f"clock#{i}": {"format": "{:%S}"} for i in range(1000)}}))' > spam-config.jsonc
   ```
2. **Launch Waybar with this configuration:**

   ```bash
   waybar -c ./spam-config.jsonc
   ```
3. **Observe the output.**

## Expected Behavior

The application should either:

- Render a truncated bar.
- Refuse to load the configuration with a warning about excessive width/modules.
- Degrade gracefully without terminating the process.

## Actual Behavior

The application terminates immediately with a segmentation fault/core dump.

**Log Output:**

```
[info] Bar configured (width: 24000, height: 18) for output: eDP-1
(waybar:30740): Gdk-CRITICAL **: ... Unable to create Cairo image surface: invalid value (typically too big) for the size of the input (surface, pattern, etc.)
timeout: the monitored command dumped core
```

## Analysis

The calculated width `24000` pixels (or higher depending on font) likely exceeds the maximum texture size or surface limits of the Wayland compositor or GDK's internal Cairo surface limit (often 32,767). Waybar does not check if the resulting window geometry exceeds display server limits before attempting allocation.
