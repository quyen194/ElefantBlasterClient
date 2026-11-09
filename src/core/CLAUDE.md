# core/ — app shell, SDL, ImGui, assets

## Ownership & init order

`AppState` holds `SDLState`, `AssetManager`, `ImguiState`, `LoginState`, `MatchState` as members (declaration order = construction order; references are passed in the ctor init list). Each subsystem also exposes a static `Instance()` pointing at that member — it is only valid after `AppState` is constructed.

`AppState::Initialize()` order matters:
1. `SDLState::Initialize` — window (hidden), renderer, logical presentation, VSync (tries adaptive `-1`, falls back to `1`).
2. `ImguiState::Initialize` — context, dark style saved as `base_style_`, **fonts via `AssetManager::LoadImFonts()`**, SDL3 + SDLRenderer3 backends.
3. `AssetManager::Initialize` — textures/animations (needs the renderer).
4. State classes, then `SDLState::ShowWindow()`.

Cleanup runs in reverse in destructors; any `Initialize` failure path must undo what it created (pattern already used in `SDLState::Initialize`).

## Two coordinate systems (the tricky part)

- **Game rendering** uses SDL *logical presentation* `1500×948` with `SDL_LOGICAL_PRESENTATION_LETTERBOX`: draw in logical units, SDL scales + letterboxes to the window.
- **ImGui** works in window pixels (`io.DisplaySize`). Rendering ImGui draw data while logical presentation is active misplaces/mis-scales it, so `ImguiState::EndFrame()` temporarily **disables logical presentation**, calls `ImGui_ImplSDLRenderer3_RenderDrawData`, then restores the previous mode.
- **UI scale**: in `BeginFrame()`, `ui_scale_ = min(DisplaySize.x / LogW, DisplaySize.y / LogH)` (same factor as letterbox). When it changes, style is reset from `base_style_` and `ScaleAllSizes(ui_scale_)` is applied (scaling must always start from the unscaled base, never compound). Font size is scaled at use site: `ImGui::PushFont(font, base_px * imgui_state_.UiScale())`, and widget sizes are multiplied by `UiScale()` too.
- When reviewing any UI/hit-testing code, ask: is this value in logical units, window pixels, or high-DPI pixels?

## Input routing

`AppState::OnEvent`: quit/resize first → `ImguiState::OnEvent` (forwards to `ImGui_ImplSDL3_ProcessEvent`) → game key handling only when `!imgui_state_.WantKeyboard()`. Mouse-driven game input should likewise check `WantMouse()`.

## AssetManager

- Paths: `R(relative)` prefixes the per-platform base (`assets` desktop, `/assets` Web, `""` Android, bundle Resources dir on iOS).
- Sprite sheets are sliced into `AssetTexture{texture, rect}` per tile/spoil type and per-direction player `Animation`s; `SpriteSize()` is the tile size used by `MatchState` to map grid → screen.
- Fonts (ImGui 1.92 dynamic fonts, size chosen at `PushFont(font, size)`):
  - UI kit: `ImFontTitle()` = Lilita One with Nunito Black merged in (Lilita has no Vietnamese glyphs), `ImFontBody()` = Nunito Bold (default font, base size 15), `ImFontBodyStrong()` = Nunito Black.
  - Legacy Roboto Regular/Medium/Bold (`ImFontRegular()` etc.) are still loaded until old screens move to the UI kit fonts.
