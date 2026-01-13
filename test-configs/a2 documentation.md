## Project Description:

Waybar is a customizable status bar for Linux desktops that utilises Wayland. Its purpose is to provide important information about your system, like battery percentage, network data, volume, etc. It's highly customizable for each user, allowing you to display more information, such as the workspace you're using, the highlighted tab, and show times and weather, among others.
It aims to give Linux users an option to use a different status bar on Wayland desktops, replacing older status bars like Polybar or i3status.

## Functional Specifications:

Waybar is designed to run on multiple compositors, including Hyprland, Sway, River, Niri, and DWL.
Key functional expectations:

- Provide common system information modules (battery, network, Bluetooth, audio/volume, time).
- Support multiple outputs (monitors) and multi-monitor configurations.
- Allow styling via CSS to change colours, fonts and layout.
- Allow configuration and extension via JSON (or JSONC) and custom modules/scripts.

## Risk Analysis:

The risks seen using Waybar are with the user's dependency on Waybar for the system's status information. If Waybar crashes, the system will continue to run; however, the users won’t be able to see any of the system's information, such as battery, volume, time, etc, which can lead to a disappointing experience for the user. Fixing the issue can also cause problems for the user, as they might have to restart Waybar or, in the worst case, need to reinstall the application.

## Project History:

Past:
Waybar was released on the 10th of August 2018, and it originally had only a few features for the status bar and only had support for sway at the time. It also could load in custom scripts, meaning that it was always customisable, but not to the extent that it can today (CSS configurations were really weak), and there was a lack of built-in modules to choose from.

Present:
The latest version of Waybar was released on August 8, 2025, and has been significantly expanded since its initial release, offering users a wider range of built-in modules to choose from. The custom scripts have also been expanded on, with CSS being way more integrated and easier to use, making it easier for the user to change the actual design of the status bar. More importantly, Waybar also has far more support for more desktop compositors like Hyprland and River.

Future:
There is no official roadmap for Waybar’s releases, and it is instead decided by the features its community is interested in seeing next.

## Security & Accessibility

Security:

- Waybar runs as a user process and does not require root privileges for normal operation; this reduces attack surface compared with privileged daemons. However, custom modules and scripts executed by Waybar run with the user's permissions and can perform arbitrary actions — they are a potential vector for malicious or buggy code. Be cautious when using untrusted modules.
- Waybar depends on several external libraries; vulnerabilities in those dependencies may affect security.

Accessibility:

- Waybar benefits from GTK's built-in accessibility support, but explicit accessibility engineering is limited in places (see `ACCESSIBILITY_REPORT.md`). Icon-only modules without descriptive text or tooltips can be inaccessible to screen readers; consider adding explicit accessible names and configurable accessibility labels in configs.

## Quality Judgement
Checklist (scores 1-5):
- Completeness: 3 — core sections present, missing config examples and mitigation steps.
- Accuracy: 3 — mostly accurate; initial draft contained terminology and typo issues (some corrected in the doc).
- Clarity & Structure: 3 — structure is acceptable but could be reorganised and expanded.
- Evidence & Traceability: 2 — no inline links to test artifacts; recommend linking `BUGS.md`, `ACCESSIBILITY_REPORT.md`, `TESTING_LOG.md`.
- Accessibility Coverage: 3 — accessibility discussed but lacks actionable fixes; see `ACCESSIBILITY_REPORT.md`.
- Actionability & Recommendations: 2 — risks stated but lacking concrete mitigations.

Key recommendations:
- Fix terminology and typos (e.g., replace accidental "Wayland" uses where `Waybar` is meant). This has been partially applied.
- Add a minimal JSONC configuration example demonstrating a safe, minimal setup.
- Add a short 'Mitigations' subsection under Risk Analysis with steps to recover from crashes (e.g., restart commands, safe-mode configs).
- Cross-link supporting artifacts: `BUGS.md` (for crash reports), `ACCESSIBILITY_REPORT.md` (for a11y findings), and `TESTING_LOG.md` (for verification evidence).
- Add a short 'How to contribute' pointer or link to the project's issue/PR process so users can propose fixes and track progress.

Notes:
- I updated `a2 documentation.md` earlier to correct the Functional and Security/Accessibility sections (typos and clarity). The file now contains a brief pointer to this judgement file.

##
