# Round Result

Mockup: mockups/index.html#round · Mobile: landscape · Status: draft
From: In-Game HUD (round ends) · To: Match Start (next round), Post-Game Results

## Purpose
Show who won the round and the round score.

## Elements
Wood sign `ROUND 2 / 3`, round winner with avatar and reason (`Last elephant standing · 02:48`),
every player with round-win stars, status line (`Tied 1–1. Round 3 decides the match.`),
host: `Next Round`; others: `Waiting for host…`.

## Behaviour
- Auto-continue after 15 s so an idle host cannot block the room.
- Draw round (same moment, same score): title `DRAW`, no star given.
- 2 wins after round 2 → Post-Game Results directly. After round 3 the most round wins takes it.
- All 3 rounds drawn → one tiebreak round (`TIEBREAK` sign); after it the match may still be a draw.
- Each player row also shows the round score (balks, eggs, GST hits).
