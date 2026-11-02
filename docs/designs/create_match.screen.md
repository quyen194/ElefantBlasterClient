# Create Match

Mockup: mockups/index.html#create · Mobile: portrait · Status: draft
From: Main Menu, Browse Maps (`Play`) · To: Match Lobby, Training Room

## Purpose
Configure and open a new room.

## Elements
- Settings: room name, max players (4/6/8), allow bots + max bots, mode (`Ranked` | `Training`),
  `Private room` + password.
- Map picker: search, visibility chips (Official / Public / Private), grid of map cards
  (preview, name, visibility, `up to N` players), selected card highlighted.
- Maps that support fewer players than `Max players` are greyed out ("Too small for 8 players")
  and cannot be selected. Lowering `Max players` re-enables them; raising it clears an invalid choice.
- Selected map summary + `Create Match` at the end of the form.

## Actions
`Create Match` → Lobby (Ranked) or Training Room (Training). Max bots is disabled when bots are off.

## States
Name empty → default `<player>'s room`. Map list loading / empty for filters.
Only registered players can create rooms.

## Mobile
Settings card, map grid in 2 columns, filter behind a chip, `Create Match` sticky at the bottom.

## Server
Create-room request; map list.
