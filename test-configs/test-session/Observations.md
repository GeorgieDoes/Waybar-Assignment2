# General Observations

Based on all previous sessions dedicated to exploring and 
testing waybar; we have found that, despite Waybar being
designed as a modular system, some components are tightly
coupled. Specifically the Pulseaudio module, which depends
on PulseAudio contextx (), GTK widgets, and an internal state
arrays. As such, to isolate the SUT, we needed to mock these
dependancies, and inject fake states.

From this, we make infere that built in modules that 
interface with linux subsystems or daemons are tightly 
coupled. Using pulseaudio as an example, this module
is highly coupled to PulseAudio/Pipewire. Should one 
of these daemons not be running, the modules will fail,
often silently so. Making isolated testing a bit harder.