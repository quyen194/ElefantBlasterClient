# Match Start

Mockup: mockups/index.html#countdown · Mobile: landscape · Status: draft
From: Lobby, Rotate Device, Round Result (next round) · To: In-Game HUD

## Purpose
Show the map and the opponents, then count down 3-2-1.

## Elements
Dimmed map, `ROUND 1 / 3 · ISLAND CHAOS · FIRST TO 2` (tiebreak: `TIEBREAK ROUND`), player avatars with `VS`, big countdown
number, `GET READY!` sign.

## Behaviour
- Input locked until 0.
- The server sends the start timestamp; every client counts down to the same moment.
- Late or slow-loading clients join when ready and see the countdown already running.
