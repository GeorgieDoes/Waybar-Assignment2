# General Observations
Based on all previous sessions dedicated to exploring and testing waybar, observed that, despite Waybar being designed as a modular system, some components are tightly coupled. Specifically the Pulseaudio module, which depends on PulseAudio contexts, GTK widgets, and an internal state arrays. As such, to isolate the SUT, mock these dependancies and inject artificial internal states.

From this, we infere that built in modules which interface with linux subsystems or daemons are tightly coupled. Using Pulseaudio as an example, this module is highly coupled to PulseAudio/Pipewire. Should one of these daemons not be running, or fail to initialize properly, the modules will silently fail. Making isolated testing a more difficult.

Thus, waybar can be considered modular in terms of build configuration and composition; however, induvidual modules, that interact with low-level system servces, are tightly coupled to their execution environment.

### Practical implications:
- Extensive mocking was required to isolate even small pices of logic.
- Linker errors exposed hidden dependencies between modules.
- Mocking framework would alone stuggled with overcoming architecural coupling.

## Deeper dive
Tight coupling means that a software component depends directly on concrete implementations of other components, or external systems, rather than on an abstract interface, making it harder, to isolate and test independently.

Waybar shows tight coupling by:
- Direct use of PulseAudio / PipeWire C APIs.
- Internal creation and manipulation of GTK widgets.
- Reliance of shared global or internal state.
- Lack of dependency injection or abstration boundries.

As a result, unit test require parts of the system to be exposed or simulated.

## Unit vs Integration Testing.
A finding of interest from this assignment is that Waybar's built-in modules behave closer to integration components then isolated units.

### Unit testing assumes:
- Clear input/output boundaries.
- Minimal side effects.
- Replaceable dependencies (mocks or fakes).

The Pulseaudio module instead:
- Talks directly to system daemons.
- Updates UI elements as part of its core logic.
- Manages state through side effects rather then return values.

This makes actual unit testing of the pulseaudio module impractical, without modifying the production code. The tests written therefore simulate internal state and override behaviour to validate specific logic (e.g., formatting and state prioritization), rather then exercising the full module lifecycle. This effectevly tests internal logic in isolation, instead of the full runtime behaviour of waybar.

## Lessons learned
While Waybar is modular in terms of build configuration and runtime composition, individual modules, particularly those interacting with Linux subsystems, are tightly coupled to their environment.

### Practical implications:
- Extensive mocking required to isolate small pieces of logic.
- Linker errors exposed hidden dependencies between modules.
- Mocking frameworks alone cannot overcome architectural coupling.

### Design insight:
Waybar prioritizes runtime integration and performance over testability and isolation. A reasonable trade-off given its role as a system-level status bar, however, it shifts testing from classical unit tests toward:
- Partial unit tests of internal logic.
- Integration tests in a real system environment.

All this to say, Waybar is compositionally modular, but architecturally coupled.
