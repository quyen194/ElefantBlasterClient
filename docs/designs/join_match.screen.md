# Join Match

Mockup: mockups/index.html#join · Mobile: portrait · Status: draft
From: Main Menu · To: Match Lobby, Training Room, Join Private Room, Spectator HUD

## Purpose
Find a room to join or watch.

## Elements
- `Quick Join`, `Enter code`, search (name or ID), map filter, `Allow bots`, refresh.
- Room table: ID, name, map, players (count + fill bar), bots, status, action.
- Status pills: `Waiting`, `In Game`, `Training`, `Private` (lock), `Locked`.
- Pagination (desktop).

## Actions
| Control | Result |
| --- | --- |
| Quick Join | First public, unlocked, ranked room with a free slot → Lobby |
| Join (Waiting / Training) | Lobby / Training Room |
| Join (Private) | Join Private Room with this room preselected |
| Watch (In Game) | Spectator HUD |
| Enter code | Join Private Room |

## States
Empty ("No rooms yet: create one"), loading, room filled while joining → "Room is full" dialog.
Guest: every action is `Watch`.

## Mobile
Each room is a card; infinite scroll; `Quick Join` sticky at the bottom with an `Enter code` icon.

## Server
Room list with live updates (players, status).
