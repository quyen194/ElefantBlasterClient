# In-Game HUD

Mockup: mockups/index.html#hud · Mobile: landscape · Status: draft
From: Match Start · To: Pause Menu, Eliminated, Round Result

## Purpose
Everything a player needs while playing, without covering the map.

## Elements
- Top: player chips (avatar, name, points, **lives ♥♥♥**; eliminated players faded), timer + `ROUND 2 / 3`,
  ping, pause button.
- Map 26×14 drawn with SDL (whole map visible, no camera scroll, so no mini-map). The player's own
  GST egg and Quarantine zone get a ring in their colour.
- A GST egg that was just hit is drawn as a dashed ring in its owner's colour with a 3 s countdown
  (the tile is walkable meanwhile); it stays a ring while a player or a bomb blocks its return.
- Floating score popups: `+1` (balk, egg), `+3` (life taken), `-2` (own bomb) at the spot, `-1` over a GST egg when it is hit.
- Under the map: own power-ups with egg sprites (Speed ×2, Attack ×3, Delay ×1; a Mystic egg shows
  as the effect it rolled) and the bomb
  cooldown (`0.8s`; shrinks with each Delay egg). On phones the bomb button shows the cooldown as a ring.
- Right column (desktop): compact scoreboard (Tab shows the full one), kill feed, chat.
- Key hints: WASD move, Space bomb, E power-up, Tab scoreboard, Enter chat, Esc pause.

## Quarantined state
After stepping into a Teleport gate **or losing a life** (one heart empties with a short shake),
the player sits in their Quarantine zone for 10 s:
- Countdown ring + seconds above the player's sprite; banner `QUARANTINED · out in 7s`.
- Movement and bomb controls dimmed (phone: D-pad and bomb button greyed out).
- When released, a short flash marks the random spot where the player reappears.
- **Invulnerable 3 s** after release: the sprite blinks with a shield ring and a 3 s ring timer;
  blasts do not hurt and bombs can be walked through.
- Opponents see the countdown above the quarantined player too.

## Mobile (landscape)
- Map fills the height.
- Joystick / D-pad bottom-left, big bomb button bottom-right (setting: left-handed swaps them).
- Timer top center, own score top-left, opponents + pause top-right, kill feed as a toast.

## Server
Game state stream; HUD reads it, never predicts scores.
