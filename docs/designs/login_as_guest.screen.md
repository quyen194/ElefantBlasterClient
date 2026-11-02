# Login as Guest

Mockup: mockups/index.html#guest · Mobile: portrait · Status: draft
From: Login · To: Main Menu (spectator only), Login

## Purpose
Let someone watch matches without an account.

## Elements
- Same dialog as Login with one field: `Nick` (prefilled `Guest#1234`, editable).
- Hint: "Guests can watch matches. Create an account to play."
- `Watch as Guest` button, `Back to account login` link.

## Actions
| Control | Result |
| --- | --- |
| Watch as Guest | Join as guest → Main Menu with spectator rights only |
| Back to account login | Login |

## States
- Nick empty or invalid (length, characters) → inline message.
- Nick taken by an online player → server appends a number.

## Guest limits (applies everywhere)
- Cannot create matches, take a player slot, add friends, appear on the leaderboard or save replays.
- Join Match shows `Watch` instead of `Join`.

## Mobile
Same as Login.

## Server
Guest join packet with nickname → temporary identity for the session.
