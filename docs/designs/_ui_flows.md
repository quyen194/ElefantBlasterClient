Launch
 ├─> Connection Screen (auto-connect central server)
 │    ├─ Normal Player → input account/pass + select Login → Main Lobby (full privileges)
 │    └─ Login as Guest → Guest Connection Screen → input nickname → Main Lobby (Spectator only)
 └─> Bot → no UI displayed, only sends BotJoin packet + roomID → auto-join room → auto Ready

Main Lobby
 ├─ [ Create Room ] (available only to Normal Players)
 ├─ Room List (infinite scroll, displays: ID | Name | Players/Max | Map | Locked | Training)
 ├─ Quick Join (automatically finds an unlocked room with available slots)
 └─ Training Maps Browser (visible only when Training Mode is enabled)

Create Room Modal
 → Select Map (Official / Public / Private)
 → Room Name
 → Max Players (4/6/8)

Room Lobby (Waiting state)
 → Everyone joins as Spectator by default
 → Lists:
    • Player slots (1–8): PlayerName Ready / Not Ready / —
    • Spectator list (separate scrollable section)
 → Personal buttons: [ Ready ] / [ Not Ready ] / [ Leave ]
 → Host-only buttons (visible only to the Host):
    • [ Start Game ] [ Lock Room ] [ Transfer Host ▾ ] [ Kick ] (next to each Player)

In-Game
 ├─ Player mode → normal playing HUD
 ├─ Spectator mode → Observer HUD (with playback speed control, full-size mini-map)
 └─ Host mode → Observer HUD + full control buttons

Round End → Result Screen → if not enough rounds completed → Host presses Next Round
Match End → Return to Room Lobby (host can Start again or Close Room)
