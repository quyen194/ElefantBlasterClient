# UI flows

Screen specs: see [README.md](README.md). Mockup anchors are given as `#id`.

## Entry

```
Launch
 └─ Connecting (#splash)  load assets + auto-connect central server
     ├─ fail → System Dialogs: "Connection lost" (retry / quit)
     └─ ok   → Login (#login)          (skipped when "Remember me" token is still valid)
               ├─ Login               → Main Menu (registered player)
               ├─ Forgot password?    → Forgot Password (#forgot) → Login
               ├─ Create account      → Create Account (#register) → Main Menu
               └─ Watch as guest      → Login as Guest (#guest) → Main Menu (spectator only)

Bot client: no UI. Sends BotJoin + room id → joins the room → auto Ready.
```

## Menu

```
Main Menu (#menu)
 ├─ Create Match (#create)        registered players only
 ├─ Join Match (#join)            guests: list shows Watch only
 │    ├─ Quick Join               first unlocked, public room with a free slot
 │    └─ Enter code (#joincode)   private room: code + password
 ├─ Match Replay (#replay)        tabs: Matches | Training (this session)
 │    └─ Watch → Replay Viewer (#viewer)   HUD + timeline (seek, speed, next kill)
 ├─ Browse Maps (#browse) → Map Editor (#editor)
 ├─ How to Play (#tutorial)       opens automatically on first login
 ├─ Friends (#friends)            registered players only
 ├─ Profile (#profile) · Leaderboard (#leaderboard) · Settings (#settings) · Developer (#developer)
 └─ Logout → Login                (clears this session's training replays)
```

Phone: Home / Friends / Ranks / Profile / Settings live in a bottom tab bar.

## Rooms

```
Create Match: name · max players (4/6/8) · bots · mode (Ranked | Training) · private + password · map
 ├─ Ranked   → Match Lobby (#lobby)
 └─ Training → Training Room (#training)

Lobby (waiting)
 • Everyone enters as spectator; tap an empty slot to take it.
 • Everyone: Ready / Not Ready, Leave, Invite friends, room code shown.
 • Host only: Start Game, Lock Room, Transfer Host, Kick (not on own slot), change map.
 • Locked  = nobody else can join.  Private = can join with the password.
```

## Match

```
Start Game
 └─ phone held portrait? → Rotate Device (#rotate)
 └─ Match Start (#countdown)   3-2-1, input locked, server sends the start timestamp
     └─ In-Game HUD (#hud)  ⇄  Pause Menu (#pause)   (the match keeps running)
          ├─ player dies → Eliminated (#eliminated) → Spectator HUD (#spectator) after 3 s
          └─ round ends  → Round Result (#round)
               ├─ more rounds → host: Next Round (auto after 15 s) → Match Start
               └─ match won   → Post-Game Results (#results) → Lobby / Rematch / Menu
```

- Spectators and hosts who are not playing use the Spectator HUD.
- Training rooms are listed and joinable like normal rooms; matches use the same screens. Results show
  no EXP or rank and the replay is kept only for the host's current login session.
- Leaving in the middle of a match asks for confirmation (System Dialogs) and hands the slot to a bot.

## Orientation on phones

Portrait everywhere except: Match Start, In-Game HUD, Pause Menu, Eliminated, Round Result,
Spectator HUD, Replay Viewer, Map Editor. Switch with `SDL_HINT_ORIENTATIONS` when entering/leaving those screens.
