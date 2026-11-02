# How to Play

Mockup: mockups/index.html#tutorial · Mobile: portrait · Status: draft
From: Main Menu (opens automatically on first login) · To: Main Menu, Training Room

## Purpose
Teach the rules in five short steps. Full rules: [game_rules.md](game_rules.md).

## Chapters
1. Move & drop bombs: controls per platform (WASD/Space, D-pad/bomb button).
2. Bombs: a dropped bomb blocks the way once you step off it. Blasts go in a cross and stop at the
   first balk (which breaks) or wall (which does not); bombs set off other bombs.
3. Dragon eggs (power-ups):
   - Speed: move faster
   - Attack: blast reaches 1 more tile
   - Delay: shorter wait between two bomb drops, so you can drop bombs more often
   - Mystic: gives one of the three effects above at random
4. Special tiles:
   - Teleport gate: stepping in sends you into your own Quarantine zone.
   - Quarantine zone: walled in by unbreakable stone. You cannot move or drop bombs; after a
     10 s countdown you are released at a random spot without a bomb.
   - Dragon Egg GST: every player has one. It blocks movement and blasts like a wall; each blast that
     hits yours costs you 1 point; it never breaks.
5. Lives, points & winning: 3 lives per round; losing one sends you to your Quarantine zone, then
   you come back invulnerable for 3 s. Points: +1 per balk, +1 per egg, +3 per life you take, -2 if your own bomb
   gets you, -1 each time your GST egg is hit (even by your own bomb).
   Last elephant standing wins the round (same moment: higher score; same score: draw). Best of 3
   rounds, 2 wins end it early, one tiebreak round if all 3 are draws; the match can end in a draw.

## Elements
- Desktop: chapter list on the left (current highlighted, read ones ticked); slide on the right
  with title, text, illustration built from real sprites; dots; `Back`, `Next`, `Try it in Training`.
- Phone: one slide per page, swipe, dots, `Next` (sticky), `Skip`.

## Actions
| Control | Result |
| --- | --- |
| Next / swipe | Next chapter; on the last one: `Done` → Main Menu |
| Chapter (desktop) | Jump to chapter |
| Try it in Training | Create a training room with bots |
| Skip | Main Menu, mark tutorial as seen |

## Server
Store "tutorial seen" per account (or locally for guests).
