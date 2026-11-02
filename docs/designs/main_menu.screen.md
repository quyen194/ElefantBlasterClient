# Main Menu

Mockup: mockups/index.html#menu · Mobile: portrait · Status: draft
From: Login, any Back · To: every top-level screen

## Purpose
Home screen after login.

## Elements
- Top bar: logo, `Logout`, player chip (avatar, name, level, EXP).
- Main buttons: `Create Match`, `Join Match`, `Match Replay`, `Browse Maps`.
- Secondary buttons: `Leaderboard`, `Profile`, `Friends`, `How to Play`, `Settings`, `Developer`.
- Online counter: `1,284 online · 96 rooms`.

## Actions
Each button opens its screen. `Logout` asks for confirmation if a training replay exists
("Training replays from this session will be deleted").

## States
- Guest: hide `Create Match`, `Friends`, `Developer`; `Join Match` becomes `Watch Matches`.
- Pending friend requests / invites: badge on `Friends`.

## Mobile
- Logo on top, four main buttons full width.
- Bottom tab bar: Home · Friends · Ranks · Profile · Settings. `How to Play` and `Developer`
  move into Settings.

## Server
Online counter (players, rooms), pushed every few seconds.
