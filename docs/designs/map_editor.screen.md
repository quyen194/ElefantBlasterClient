# Map Editor

Mockup: mockups/index.html#editor · Mobile: landscape · Status: draft
From: Browse Maps (Create / Clone) · To: Browse Maps, Training (Test Play)

## Purpose
Build and publish maps.

## Elements
- Top: `Save`, `Test Play`, `Publish`.
- Tools: Brush, Eraser, Spawn point, Fill area, View.
- Tiles (real ones): Grass, Wall, Balk, Teleport, Quarantine, Dragon egg nest; eggs: Speed, Attack,
  Delay, Mystic.
- Canvas: map with grid, cursor highlight, zoom, undo.
- Properties: name, size (default 26×14), visibility. **Max players is not editable**: it is the
  number of spawn ↔ Quarantine pairs placed on the map.
- Spawn tool: placing a spawn point asks for its Quarantine zone, then its GST egg; each set is
  numbered P1…P8 on the canvas. Max players = number of complete sets.
- Layers: terrain, objects, spawns, grid.
- Validation shown live ("Need 6 more spawn points for 8 players"); `Validate`, `Import`, `Export`.
  Rules (see [game_rules.md](game_rules.md)): every player slot needs a complete set (spawn,
  Quarantine zone, GST egg), and every Quarantine zone is fully enclosed by Walls.

## Actions
Test Play opens a Training Room with this map. Publish requires a valid map.

## Mobile (landscape)
Tool rail left, tile palette right, map center (~22 px per tile). Best on tablets.

## Server
Save/load/publish maps; validation repeated on the server.
