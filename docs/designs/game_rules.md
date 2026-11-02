# Game rules

Gameplay rules the UI (How to Play, HUD, Map Editor, results screens) and the server must agree on.
Map tiles come from `entities/map_tile.hpp`, eggs from `entities/spoil.hpp`.

## Map and players

- Each player slot owns a fixed **set** stored in the map file: spawn point + Quarantine zone +
  Dragon Egg GST.
- A map's **max players = number of complete sets**. Create Match only offers maps that support the
  chosen player count.
- The current built-in map (`MatchState::Load()`) has 2 Quarantine zones and 2 GST eggs, so it
  supports 2 players.

## Bombs

- A player drops a bomb on the tile they stand on and may step off it; once they have moved to a
  neighbouring tile the bomb becomes an **obstacle**: nobody (owner included) can walk through it.
- The blast goes in a cross (up, down, left, right). Base range is extended by Attack eggs.
- The blast stops at the first obstacle:
  - **Balk** (brick, `kBalk`): the first balk hit is destroyed; the blast does not continue past it.
  - **Wall** (stone, `kWall`): not destroyed and not passed.
- A bomb hit by a blast explodes too (chain).

## Dragon eggs (power-ups, `SpoilType`)

| Egg | Effect |
| --- | --- |
| Speed | Move faster |
| Attack | Blast reaches 1 more tile |
| Delay | Shorter wait between two bomb drops, so bombs can be dropped more often |
| Mystic | One of Speed / Attack / Delay, chosen at random |

Eggs stack until the round ends. Destroyed balks may drop eggs.

## Dragon Egg GST (`kDragonEggGst`)

- Each player is assigned one GST egg on the map (part of their set).
- While present, a GST egg is an **obstacle like a Wall**: blasts stop at it and players cannot
  walk onto it.
- When a blast hits a GST egg, **its owner loses 1 point** and the egg **disappears for 3 s**.
  While it is gone the tile is free: players can walk through it.
- After 3 s the egg comes back on the same tile, unless the tile is blocked:
  - a **player** standing there: the egg waits until the tile is free;
  - a **bomb** on the tile: the egg waits until that bomb has exploded and its blast has ended;
  - **fire only** (a blast passing over the tile) does **not** stop the egg from coming back.
- The egg is never destroyed for good and can be hit any number of times.

## Lives, Teleport and Quarantine

- Every player starts each round with **3 lives**.
- Losing a life (caught by a blast) or stepping into a **Teleport gate** sends the player into
  **their own Quarantine zone**.
- A Quarantine zone is fully enclosed by Walls: the player cannot move or drop bombs, and blasts
  cannot reach them.
- After **10 s** the player is released to a random tile with **no bomb** on it (tiles on fire are
  not avoided).
- After release the player is **invulnerable for 3 s**: blasts do not hurt them and they can walk
  through bombs. If they stand on a bomb when the 3 s end, they may step off it, like a bomb they
  just dropped.
- Losing the third life eliminates the player for the rest of the round.

## Score (per round)

| Event | Points |
| --- | --- |
| Destroy a balk | +1 |
| Pick up a dragon egg (any spoil) | +1 |
| Take another player's life (your blast hits them) | +3 |
| Your own blast takes your own life | −2 |
| A blast hits your GST egg | −1 to the egg's owner, whoever dropped the bomb (own bombs included) |

When blasts from several players hit someone at the same moment, **every** one of those bomb owners
scores for it (+3 each; the victim's own bomb counts as −2 for the victim). The victim loses only one
life.

## Round

- A round ends when one elephant is left standing; that player wins the round.
- If the last players lose their last life at the same moment, the **higher score** wins the round.
  Same score: the round is a **draw** (nobody wins it).

## Match

- A match has **3 rounds**. The player with the most round wins takes the match.
- A player who wins the first 2 rounds wins immediately (round 3 is not played).
- If all 3 rounds are draws, **one** extra tiebreak round is played (never more than one).
- The final result can be a **draw**.
- **Final standings** (any number of players): by round wins, then by total score over all rounds.

**Ownership of a blast**: every blast belongs to the owner of the bomb it came from, even when that
bomb was set off by someone else's blast (chain). Example: A's blast sets off B's bomb and B's blast
takes C's life, so B gets +3 and A gets nothing. The same applies to balks destroyed and GST eggs hit.
