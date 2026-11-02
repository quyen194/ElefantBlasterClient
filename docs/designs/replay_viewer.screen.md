# Replay Viewer

Mockup: mockups/index.html#viewer · Mobile: landscape · Status: draft
From: Match Replay (`Watch`), Training Room (session replays), Post-Game Results (training: `Watch replay`) · To: Match Replay

## Purpose
Watch a finished match like the In-Game HUD, with full playback control.

## Elements
- Top: `Replays` (back), wood sign `REPLAY · <map>`, match id + date, camera mode
  `Follow` | `Free cam` | `Overview`.
- Map 26×14 rendered exactly like the HUD (same sprites, bombs, explosions, eggs).
- Right (desktop): scoreboard **at the current replay time**; events list (kills, round start/end)
  with timestamps.
- Timeline bar: back 10 s, play/pause, `05:32 / 10:00`, seek track with markers
  (red = kill, yellow = round end), `Next kill`, speed `0.5× | 1× | 2× | 4×`.
- Key hints: Space play/pause, ← → ±10 s, N next kill, 1–4 camera, [ ] speed.

## Actions
| Control | Result |
| --- | --- |
| Drag / click track | Seek |
| Event row, marker | Jump to that moment (a few seconds before it) |
| Next kill | Jump to the next kill marker |
| Camera chip / 1–4 | Follow that player |

## States
Loading replay (progress), replay expired (training replay after logout → "This replay is gone"),
end of replay → `Watch again` / `Back to replays`.

## Mobile (landscape)
Map on top, timeline overlaid at the bottom; tap the map to show/hide controls (like a video player);
player chip top-right switches camera.

## Server / data
- Replay = periodic state snapshots (every few seconds) + events/inputs in between.
  Seeking loads the nearest snapshot and simulates forward to the target time.
- Ranked replays stored with the match; training replays only in the host's session store.
