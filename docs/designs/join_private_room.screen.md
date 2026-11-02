# Join Private Room

Mockup: mockups/index.html#joincode · Mobile: portrait · Status: draft
From: Join Match (`Enter code`, or a Private room) · To: Match Lobby

## Purpose
Join a room that is not open to everyone.

## Elements
- Modal (desktop) / bottom sheet (phone) with wood sign `PRIVATE ROOM`.
- Six room-code boxes (`B7K2Q9`), password field.
- Preview once the code is valid: room name, map, players.
- `Cancel`, `Join Room`.

## Rules
- **Locked**: host closed the room; nobody can join.
- **Private**: anyone with the code and password can join.
- Codes use A–Z and 2–9 without look-alikes (no 0/O, 1/I).
- The lobby shows the room code so the host can share it.

## States
Unknown code, wrong password, room full, room already started.

## Server
Resolve code → room preview; join with password.
