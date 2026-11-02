# Match Replay

Mockup: mockups/index.html#replay · Mobile: portrait · Status: draft
From: Main Menu, Profile · To: Replay Viewer

## Purpose
Find and watch past matches.

## Elements
- Tabs: `Matches` | `Training · this session`.
- Filters: name/ID, date range, map, allow bots.
- Table: ID, name, map, players, date, duration; selected row.
- Detail panel: preview, top 4, `Watch Replay`.

## Watching
`Watch Replay` opens the [Replay Viewer](replay_viewer.screen.md).

## States
Empty list; training tab empty ("Training replays appear here until you log out").

## Mobile
Cards with preview and a play button.

## Server
Replay list (ranked), per-session training replays, replay download/stream.
