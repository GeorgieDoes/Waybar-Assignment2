# Accessibility Evaluation Report

**Evaluator:** GK222JW
**Date:** 2026-01-07
**Application:** Waybar v0.14.0 (Git)
**Framework:** GTK+ 3 (gtkmm)

## Summary

Waybar relies almost entirely on standard GTK+ widgets, which provide baseline accessibility support (integration with AT-SPI). However, specific custom accessibility implementations (ARIA roles equivalent, explicit descriptions for icon-only modules) appear to be minimal or absent in the source code.

## Findings

### 1. Default Toolkit Support (Passed)

Since Waybar is built on `gtkmm` (C++ bindings for GTK+), it inherits the built-in accessibility features of GTK widgets.

- **Text Labels:** `Gtk::Label` widgets are automatically readable by screen readers (Orca).
- **Tooltips:** Most modules use `set_tooltip_text` or `set_tooltip_markup`. This is confirmed in modules like `power_profiles_daemon`, `battery`, etc. Tooltips provide essential context for screen reader users when focusing on a widget.

### 2. Code-Level Accessibility Mechanics
The application achieves its current level of accessibility through **Platform Inheritance** rather than explicit implementation:
*   **Object Hierarchy:** Modules typically instantiate `Gtk::Label`, `Gtk::Button`, or `Gtk::Box`.
*   **AT-SPI Integration:** In GTK 3, every `Gtk::Widget` automatically implements the `AtkImplementor` interface.
    *   When a `Gtk::Label` is created in code (e.g., `label_ = Gtk::manage(new Gtk::Label());`), GTK internally creates a corresponding `GtkLabelAccessible` object.
    *   This internal object exposes the text content of the label to the **Accessibility Toolkit (ATK)** layer.
    *   The ATK layer communicates via D-Bus with screen readers (like Orca) using the **AT-SPI2** protocol.
*   **Zero-Cost Compliance:** Because Waybar code updates the `label_.set_text()` method to show battery percentage or clock time, the accessible name of that object is automatically updated in the accessibility tree without the developer writing extra code.

### 3. Explicit Accessibility Code (Failed/Missing)

A search for `Atk` (Accessibility Toolkit) and `get_accessible()`/`set_accessible_*` in the source code returned **zero** meaningful results in the user source files (only found in binary build artifacts).

- **Implication:** The developers have not manually added accessibility descriptions to non-text elements (like icons, progress bars, or custom drawing areas).
- **Impact:** Modules that rely solely on icons (e.g., status icons, charts) without tooltips may be invisible to screen readers.

### 4. Keyboard Navigation (Partial)

Waybar is a dock/bar. Standards typically require bars to be navigable via keyboard shortcuts.

- Waybar supports `mode` handling (Sway/Hyprland), but focusing the bar itself depends on the compositor's keyboard capabilities, not just Waybar.
- Interactive modules (Workspaces, Taskbar, Tray) inherit `Gtk::Button` behavior, making them theoretically clickable if focus can be moved to the bar.

## Recommendations for Improvement (Higher Grade)

1. **Add `Atk` Properties:** Explicitly set accessible names/descriptions for icon-only widgets.
   ```cpp
   // Example fix recommendation
   button->get_accessible()->set_name("Workspace 1");
   button->get_accessible()->set_description("Active workspace");
   ```
2. **Configurable A11y Fields:** Allow users to define `accessibility-label` format in the JSON config, similar to `tooltip-format`.

## Conclusion

Waybar has **Basic/Implicit** accessibility due to its GTK roots but lacks **Dedicated** accessibility engineering. It is usable for text-heavy configs but potentially blocking for icon-centric setups.
