# Leaderboard

Mockup: mockups/index.html#leaderboard · Mobile: portrait · Status: draft
From: Main Menu, Profile · To: Player Profile

## Purpose
Ranking of players and of developer bots.

## Elements
- Tabs: `Players` | `Bots`.
- Filters: period (`This week` / `Season` / `All time`), region.
- Podium for the top 3 (avatars, crown on #1).
- Table: rank, player, level, W/L, K/D, EXP. Bots table: rank, bot, creator, W/L, rating.
- Your own row (`#127`) always visible and highlighted, even when it is not on the current page.

## Actions
| Control | Result |
| --- | --- |
| Row | Player Profile |
| Your row | Scroll / page to your position |

## States
Loading; not ranked yet ("Play 5 ranked matches to get a rank"); guest sees the board without a
"you" row.

## Mobile
Podium on top, list with rank, avatar, name, EXP only; "You #127" bar pinned above the tab bar.

## Server
Paged ranking query by tab + period + region; own rank.
