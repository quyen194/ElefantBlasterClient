# Player Profile

Mockup: mockups/index.html#profile · Mobile: portrait · Status: draft
From: Main Menu, Leaderboard, Friends, Lobby · To: Match Replay, Leaderboard, Developer Portal

## Purpose
A player's level, stats and recent matches.

## Elements
- Header: avatar, name, level pill, global rank, EXP bar (`12,450 / 15,000 EXP`).
- Stat tiles: Matches played · Win rate (W/L) · K/D · Playtime · Blocks destroyed · Eggs collected.
- Recent matches: date, map, mode, K, D, result (`Win +50 EXP`).
- Own profile: `Edit Profile`, `API Settings` (→ Developer Portal), `View Leaderboard`.
- Someone else's profile: `Add friend` / `Invite`, no edit buttons.

## Actions
| Control | Result |
| --- | --- |
| Recent match row / View all | Match Replay filtered to this player |
| Edit Profile | Change avatar (elephant skin) and display name |

## States
- Loading skeleton; no matches yet → "Play your first match".
- Training matches never appear here.

## Mobile
Header centered, stats 2×2, recent matches as compact rows. Profile is a bottom tab (no Back).

## Server
Profile stats (ranked matches only), recent match list.
