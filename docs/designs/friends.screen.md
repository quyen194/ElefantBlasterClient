# Friends

Mockup: mockups/index.html#friends · Mobile: portrait · Status: proposal (may be dropped)
From: Main Menu, Lobby (Invite) · To: Lobby, Spectator HUD, Player Profile

## Purpose
See which friends are online, invite them to your room, join or watch theirs.

## Elements
- Add friend: name search + `Add`.
- Requests: incoming requests with accept ✓ / decline ✕ (badge with count).
- Friends list, each row: avatar with status dot, name, status line, actions.
  - green = online (`Online · Main menu`)
  - orange = in match (`In match · Friday Night Blast · 03:12`)
  - grey = offline (`Offline · 2 h ago`)
- Invite card (shown on any screen): `<friend> invited you to <room>` → `Join` / ✕.

## Actions
| Control | When | Result |
| --- | --- | --- |
| Invite | you are in a room, friend online | Friend gets the invite card |
| Watch | friend in a match | Spectator HUD on that match |
| Profile | always | Player Profile |
| Remove / Block | row menu | Confirm dialog |

## States
- Empty list: "Add friends by name, or share your room code".
- Guest: screen not available.

## Mobile
Tab in the bottom bar. Segmented `Friends | Requests`. Invite card is a banner at the top.

## Server
- Friendship table (pending / accepted / blocked).
- Presence: online / in room / in match, pushed to friends.
- Invite packet (expires after 60 s).

## Open questions
- Keep this screen, or rely only on room codes for playing with friends?
