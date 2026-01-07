# Dependency Errors Log

**Evaluator:** GK222JW

**Date:** 2026-01-04

## Missing Dependencies identified on Arch Linux

### 1. `gdbus-codegen`

- **Error:** `Program 'gdbus-codegen' not found or not executable`
- **Context:** Required for generating code from D-Bus introspection XML.
- **Solution:** Install `glib2-devel` package.

### 2. `scdoc`

- **Error:** `which: no scdoc in (...)`
- **Context:** Required for building manual pages.
- **Solution:** Install `scdoc` package.

### 3. `iniparser`

- **Error:** `iniparser library is required` (during `libcava` subproject configuration)
- **Context:** Required for Cava (audio visualizer) module support.
- **Solution:** Install `iniparser` package.

### 4. `glib2-devel` headers

- **Error:** Implicitly related to `gdbus-codegen` missing.
- **Context:** Development headers for GLib.
- **Solution:** Install `glib2-devel`.

## Recommended Install Command

```bash
sudo pacman -S glib2-devel scdoc iniparser pugixml fftw
```

## All Dependencies (Reference)

### Core Dependencies

* `gtkmm3`
* `jsoncpp`
* `libsigc++`
* `fmt`
* `wayland`
* `chrono-date`
* `spdlog`
* `xkbregistry`

### Module-Specific Dependencies

* `libgtk-3-dev` (gtk-layer-shell)
* `gobject-introspection` (gtk-layer-shell)
* `libgirepository1.0-dev` (gtk-layer-shell)
* `libpulse` (Pulseaudio module)
* `libnl` (Network module)
* `libappindicator-gtk3` (Tray module)
* `libdbusmenu-gtk3` (Tray module)
* `libmpdclient` (MPD module)
* `libsndio` (sndio module)
* `libevdev` (KeyboardState module)
* `upower` (UPower battery module)

### Build Dependencies

* `cmake`
* `meson`
* `scdoc`
* `wayland-protocols`
