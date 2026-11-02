# Training Room

Mockup: mockups/index.html#training · Mobile: portrait · Status: draft
From: Create Match (Mode = Training), How to Play · To: Match Start

## Purpose
A practice room: same match rules, nothing is recorded.

## Rules
- Not counted on the leaderboard, no EXP, not in match history or profile stats.
- Replays are kept on the server **only for the host's current login session** and deleted on logout.
- Anyone can join from the room list (pill `Training`); everything else works like the Match Lobby
  (Ready, Invite, room code, host Kick / Lock / Transfer / Start).

## Elements
- Banner: `TRAINING · Not ranked · Not saved to match history · Replays are kept only until you log out`.
- Slots like the lobby; bots have a difficulty select (Easy / Normal / Hard) and a remove button.
  Empty slots: `Add bot`, `Invite friend`.
- "This session's replays": list with `Watch` (→ Replay Viewer); "Cleared when you log out."
- Footer: `Leave`, `Ready`, `Invite`, room code, host: `Change map`, `Start Training`.

## Flow
Start → Rotate Device (phone) → Match Start → HUD … → Post-Game Results in training mode
(no EXP / rank block, `Watch replay`, `Play again`).

## Server
Training flag on the room; per-session replay store keyed by the host's session id.
