# Settings

Mockup: mockups/index.html#settings · Mobile: portrait · Status: draft
From: Main Menu, Pause Menu · To: back

## Purpose
Audio, controls, display and network options.

## Elements (desktop)
- Graphics: window size, display mode (windowed / fullscreen), UI scale (`Auto` = `UiScale()`),
  FPS limit, V-Sync.
- Audio: master, music, SFX sliders.
- Controls: move up/left/down/right (W/A/S/D), place bomb (Space), use power-up (E), chat (Enter),
  each with `Rebind`.
- Network: region, max ping, show ping.
- Footer: `Reset to Default`, `Apply`.

## Elements (phone)
- Audio sliders.
- Touch controls: D-pad or joystick, button size, left-handed layout, vibration.
- Graphics & network: battery saver, region, show ping.
- Also hosts `How to Play` and `Developer` links (not in the tab bar).

## Actions
`Apply` saves to the per-user config; `Reset to Default` asks for confirmation. Rebind waits for a
key, `Esc` cancels, conflicts are swapped with a message.

## States
Unsaved changes → `Apply` highlighted; leaving asks "Discard changes?".

## Notes
The game draws at logical 1500×948, so "resolution" only means window size.

## Server
None (client config in `assets/configs/`), except region list.
