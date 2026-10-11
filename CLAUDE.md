# ElefantBlasterClient

The game client: SDL3 (+ SDL_image/ttf/mixer) rendering, Dear ImGui for UI, nlohmann::json for (current) game messages, glm for math. Targets Windows/Linux/macOS, **Web (Emscripten)** and **Android** (`android/` Gradle project wraps the CMake build as a shared lib). Mentor mode: see workspace `CLAUDE.md`. This is the project under most active development.

codebase-memory project: `K-git-ElefantBlaster-ElefantBlasterClient`. Ignore `android/app/src/main/java/org/libsdl/` (SDL's Java glue, third-party) and `libs/`.

> `README.md` describes an early **planned** layout (`Core/`, `Entities/Bomb.h`, …) that does not match the real tree — trust the source map below.

## Runtime flow

- `entrypoint.cpp` uses **SDL3 main callbacks** (`SDL_MAIN_USE_CALLBACKS`): `SDL_AppInit` → `SDL_AppEvent` → `SDL_AppIterate` → `SDL_AppQuit`. No hand-written main loop (required for Web/Android).
- `AppState` (singleton) owns every subsystem **by value**, constructed in dependency order and injected by reference: `SDLState` → `AssetManager` → `ImguiState` → `LoginState`, `MatchState`.
- Frame: `OnLoop()` computes `delta_time` → `OnUpdate(dt)` → clear → `ImguiState::BeginFrame()` → `OnDraw()` → `ImguiState::EndFrame()` → `SDL_RenderPresent`.
- Screen state machine: `State` enum (`definitions/states.hpp`: kLogin, kMainMenu, kMatchList, kLobby, kMatch); `AppState` switches on `state_` in `OnUpdate/OnDraw/OnHandleKeyInput`. Only `kLogin` and `kMatch` have state classes today. Each state class exposes `Initialize/OnUpdate/OnDraw/OnEvent|OnHandleKeyInput`.
- Events: system events first, then `ImguiState::OnEvent`, then game input only if `!WantKeyboard()` (ImGui has priority).

## Source map (`src/`, include root)

| Dir | Contents |
|-----|----------|
| `core/` | `AppState`, `SDLState`, `ImguiState`, `AssetManager` — see `src/core/CLAUDE.md` |
| `states/` | `LoginState` (ImGui login form), `MatchState` (tile map, players, spoils; implements `MapUpdater`) |
| `entities/` | Plain structs: `Player`, `MapTile`/`DynamicMapTile`, `Spoil` |
| `effects/` | `Animation` (sprite-sheet frames), `Movement` (grid-to-screen interpolation, `MoveDir`), `Timer` |
| `map/` | `MapUpdater` interface: apply server JSON to map entities |
| `network/` | `NetClient` (currently only an Emscripten WebSocket implementation; native path is a stub), `protocol_def.hpp` (`ServerMsgType`) |
| `definitions/` | `macro.hpp` (a local copy of aries_base's macros), `states.hpp` |

## Game protocol & design docs

- `docs/protocols/{client_msg,server_msg}/**.json` — JSON samples of the game protocol (join-game, drive-player, ticktack-player events like bomb-setup/exploded, player-start/stop-moving…). `ServerMsgType` mirrors these.
- `docs/designs/_ui_flows.md` + `*.screen.md` — screen flow (login/guest, lobby, room, in-game, results…) and ASCII mockups. Use them to judge whether new UI matches the intended flow.
- `MatchState::TestParsePlayers()` feeds hard-coded JSON — the match screen runs on fake data until networking exists.

## Assets & build

- `assets/` (graphics, fonts Roboto, `configs_default.json`) is copied next to the binary; on Web it is preloaded at `/assets`; on Android it goes into the APK assets. Always build paths with `AssetManager::R("graphics/...")` — never hard-code `"assets/..."`.
- Build only through the workspace root presets (e.g. `x64-Debug`, `Emscripten-Web-Debug`, `Android-arm64-Debug`). SDL, SDL_image, SDL_ttf, SDL_mixer, imgui, protobuf are built from source via FetchContent (slow first configure); websocketpp is linked only on desktop.
- Logical resolution is fixed at **1500×948** (letterbox); default window 1800×1000, resizable, high-DPI, min size = half logical size.
