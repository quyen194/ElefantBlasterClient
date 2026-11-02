# Rotate Device

Mockup: mockups/index.html#rotate · Mobile: portrait · Status: draft (phone only)
From: Lobby / Training Room (Start) · To: Match Start

## Purpose
Ask the player to turn the phone sideways before the match.

## Elements
Phone icon animating from portrait to landscape, `ROTATE TO PLAY`, room name,
`Match starts in 5`, `Back to lobby`.

## Behaviour
- Shown only when the device is held portrait at match start.
- Allow landscape with `SDL_HINT_ORIENTATIONS = "LandscapeLeft LandscapeRight"` when entering the
  match, and back to `"Portrait"` when returning to menus.
- Disappears as soon as the window becomes landscape.
- If the countdown ends first, the match starts anyway (the player is not kicked).
