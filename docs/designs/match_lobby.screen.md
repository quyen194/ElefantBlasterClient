# Match Lobby

Mockup: mockups/index.html#lobby · Mobile: portrait · Status: draft
From: Create Match, Join Match, Join Private Room, Post-Game Results · To: Match Start (via Rotate Device on phones)

## Purpose
Wait for players, get ready, start the match.

## Elements
- Room bar: map preview, room name + `#ID`, map / players / spectators count, host map picker,
  `Locked` toggle.
- Player slots 1–8: avatar, name, Human/Bot, Ready / Not ready, crown on the host.
  Host sees `Host` (transfer) and `Kick` on other players' slots. Empty slot: "tap to take slot".
- Spectators list with `Host` (transfer).
- Footer: `Leave`, `Ready`, `Invite`, room code `B7K2Q9`; host: `Lock Room`, `Start Game`.

## Actions
| Control | Who | Result |
| --- | --- | --- |
| Empty slot | anyone (not guest) | Move from spectators into the slot |
| Ready / Not ready | players | Toggle |
| Invite | players | Friends screen |
| Kick / Host | host | Remove player / transfer host (confirm) |
| Lock Room | host | Nobody else can join |
| Start Game | host | Enabled when ≥ 2 players and everyone is ready |
| Leave | anyone | Back to Join Match (host leaving transfers host) |

## States
Not everyone ready (Start disabled with reason), host left (new host notice), kicked (dialog).

## Mobile
Slots as a list; Kick/Host in a row menu; spectators collapsed; footer: Leave, Invite, Ready, Start.

## Server
Room state push (slots, ready, host, lock), lobby chat (optional).
