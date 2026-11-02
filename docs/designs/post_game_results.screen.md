# Post-Game Results

Mockup: mockups/index.html#results · Mobile: portrait · Status: draft
From: Round Result (match over) · To: Match Lobby, Main Menu, Match Replay

## Purpose
Final standings and what the player earned.

## Elements
- Banner from the real result: `VICTORY!` for the winner, `DRAW!` when the match ends drawn,
  otherwise `2ND PLACE!`, `3RD PLACE!`…
- Round summary: one cell per round played (win star, draw, or the round winner's avatar).
- `Match #00123 · Island Chaos · 8P Deathmatch · 10:00`.
- Final scoreboard ordered by round wins, then total score: pos, player (crown on 1st), rounds won,
  score, K (lives taken), D (lives lost); own row highlighted. Tied players share a position.
- Your performance: kills, deaths, assists, K/D, power-ups used, blocks destroyed.
- Rewards: base EXP, placement bonus, kill bonus, performance; total; level-up bar.
- Actions: `Save Replay`, `Rematch`, `Main Menu`, `Back to Lobby` (primary).

## Training mode
No rewards block and no level bar; `Watch replay` and `Play again` instead of `Save Replay` / `Rematch`.

## Mobile
Own result first (place, score, +EXP), rewards, top-5 list, `Back to Lobby` sticky, small secondary row.

## Server
Final results and EXP breakdown computed by the server.
