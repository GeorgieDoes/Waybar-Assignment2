# Technical Analysis: Waybar Test Suite and SUT performance

This report is made to evaluate the Systems Under Test (SUTs) for waybar. The report will map existing test cases to 
Functional Requirements (FRs), and Non-Functional Requirements (NFRs). A test session was conducted using the already 
existing unit tests, an analysis of these tests, and the results will be provided. Along with a general gap analysis.

## 1. Environment and Frameworks
- Build system: Meson.
- Testing Framework: Catch2.

## 2. Test Execution Analysis.

A regression was identified in the Hyprland backend suite, along with a minor log error related to a missing CSS file,
in another suite, however, that suite, still passed. For more information, view the testlog file.

### Failure Analysis:
- Location: ../test/hyprland/backend.cpp:52.
- test case: XDGRuntimeDirExistsNoHyprDir.
- Cause: Host Environment leakage.

The test suite inherits the host environmental variables, which leads to the suite detecting a real Hyprland session
signature, (/tmp/hypr/[signature]) instead of the expected mocked signature (/tmp/hypr/instance_sig).

IPC connection errors ([error] Hyprland IPC: Unable to connect?) were also observed. Indicating that the test successfully
resolved a valid runtime path, but could not establish a connection. Implying poor environment isolation, any hermetic test
should only be aware of the resources within its own scope.

### Other observations: Utils
- Log output: [error] Failed to find css file.

This log error was produced by the utils test suite, most likely by a missing asset in the build directory; however, the
test still passed.

## 3. FRs and NFRs

Most requirements have been inferred based on the codebase, or the information provided by the official waybar website and
github repository.

### Functional Requirements
- FR 1: Compositor Integration.
    - The system shall interface with Wayland-based compositors (e.g., Hyprland, Sway) to track workspace states and active windows.
- FR 2: Resource Monitoring
    - The system shall provide modules to poll real-time metrics for CPU, memory, battery, and disk activity.
- FR3: Network Visualizer
    - The system shall display network states, including SSID, signal strength, and throughput.
- FR4: Multimedia Control
    - The system shall provide interfaces for audio management (volume/mute) and display brightness control.
- FR 5: Custom Modules
    - The system shall allow users to execute external scripts/binaries and pipe the output (text or JSON) into the bar.
- FR 6: Config Parsing
    - The system shall load layout and logic settings from structured JSON or JSONC configuration files.
- FR 7: Interactive Support
    - The system shall support user-defined actions (clicks, scrolls) to trigger external commands or scripts.

### Non-Functional Requirements
- NFR 1: CSS-Based Styling
    - Visual appearance (fonts, colors, padding) shall be decoupled from logic and managed via standard CSS.
- NFR 2: Low Overhead
    - The system shall be optimized for minimal CPU and memory footprints to avoid degrading compositor performance.
- NFR 3: Thread Safety
    - (Inferred from SafeSignal) The system must handle inter-thread communication safely without UI-blocking or race conditions.
- NFR 4: Fault Tolerance
    - (Inferred from Defensive Programming) The system should handle malformed config or missing CSS files without crashing.

## 4. Requirement Mapping

Upon review, the following requierments appear to, be covered by the test suites.

#### FR 1: Compositor Integration
- Test: hyprland/backend.cpp (IPCTestFixture).
- Status: Partial coverage, socket logic tested; connection failed.

#### FR 2: Resource Monitoring
- Test: config.cpp (CPU/Memory config parsing).
- Status: Verified configuration logic.

#### FR 6: Configuration Parsing
- Test: JsonParser.cpp / config.cpp.
- Status: Verified (Unicode, JSONC, chain configuration possible).

#### FR 7: Interactive Support
- Test: hyprland-workspaces.json.
- Status: Verified (Scroll/Click action parsing).

#### NFR 1: CSS-Based Styling
- Test: css_reload_helper.cpp.
- Verified (Recursive import logic).

#### NFR 2: Low Resource Overhead
- SafeSignal.cpp.
- Verified (Move semantics/copy counter validation)

FR 3, FR4, NFR 3 and NFR 4 currently lack explicit test coverage in the provided suites.

## 5. Gap Analysis
- Isolation Improvement: Refactor IPCTestFixture to strictly scrub host environment variables to prevent leakage.
- Coverage Expansion: Develop unit tests for Network (FR 3), Multimedia (FR 4) Thread Safety (NFR 3) and Fault Tolerance (NFR 4), logic.
- Stress Testing: Planned injection of corrupted CSS and JSON files to validate graceful degradation.

