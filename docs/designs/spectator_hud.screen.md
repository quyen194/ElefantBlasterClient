# Spectator HUD

Mockup: mockups/index.html#spectator · Mobile: landscape · Status: draft
From: Join Match (Watch), Eliminated, Friends (Watch) · To: Join Match, Post-Game Results

## Purpose
Watch a live match.

## Elements
- Top: `Exit`, `SPECTATING · <player>`, `● LIVE`, room id.
- Left: cameras (players with keys 1–4, `Free camera` 5), match info (map, mode, elapsed / left).
- Center: map; camera mode `Follow` | `Free cam` | `Overview`.
- Right: live scoreboard, kill feed.
- Key hints: 1–5 switch camera, F follow, M map.

## Notes
- No playback speed while live (cannot run ahead of real time). Speed and seeking belong to
  the [Replay Viewer](replay_viewer.screen.md).

## Mobile (landscape)
Map in the center, camera avatars as a column on the left, small scoreboard top-right.

## Server
Spectator stream (may be delayed a few seconds to prevent ghosting).
