# UI design specs

Each `*.screen.md` file is the **spec** of one screen: what it shows, what each control does, which
states it must handle and how it behaves on phones. The **look** lives in the interactive mockup:
open [mockups/index.html](mockups/index.html) in a browser (every screen has a `#id` anchor).

- Layout targets: desktop/web (logical 1500×948, letterboxed) and phones.
- Phones run **portrait**, except gameplay screens and the map editor, which run **landscape**
  (`Mobile: landscape` in the header of those specs): Match Start, In-Game HUD, Pause Menu,
  Eliminated, Round Result, Spectator HUD, Replay Viewer, Map Editor.
- Art comes from `assets/graphics/` (sprites, tiles, eggs, dialog art). Backgrounds:
  `home/background_h.png` (landscape: desktop, web, landscape phone screens) and
  `home/background_v.png` (portrait phone screens), both drawn "cover"; the portrait one is anchored
  to the bottom so the elephants stay visible. UI elements (buttons, panels,
  chips, icons) will be exported from the mockup into `assets/graphics/ui/` once the design is final.
- Overall navigation: [_ui_flows.md](_ui_flows.md). Gameplay rules: [game_rules.md](game_rules.md).
- UI elements to export (names, 9-slice, colours, fonts): [ui_kit.md](ui_kit.md).

## Spec template

```
# <Screen>
Mockup: mockups/index.html#<id> · Mobile: portrait|landscape · Status: draft|final
From: … · To: …

## Purpose      one or two sentences
## Elements     what is on screen, top to bottom
## Actions      control → who can use it → result
## States       loading, empty, error, guest, host, …
## Mobile       what changes on a phone
## Server       packets / data the screen needs
## Open questions
```

## Screens

| Group | Screen | Spec | Mobile |
| --- | --- | --- | --- |
| Entry | Connecting | [connecting](connecting.screen.md) | portrait |
| Entry | Login | [login_as_player](login_as_player.screen.md) | portrait |
| Entry | Login as Guest | [login_as_guest](login_as_guest.screen.md) | portrait |
| Entry | Create Account | [create_account](create_account.screen.md) | portrait |
| Entry | Forgot Password | [forgot_password](forgot_password.screen.md) | portrait |
| Menu | Main Menu | [main_menu](main_menu.screen.md) | portrait |
| Menu | How to Play | [how_to_play](how_to_play.screen.md) | portrait |
| Menu | Friends | [friends](friends.screen.md) | portrait |
| Menu | Player Profile | [player_profile](player_profile.screen.md) | portrait |
| Menu | Leaderboard | [leaderboard](leaderboard.screen.md) | portrait |
| Menu | Settings | [settings](settings.screen.md) | portrait |
| Menu | Developer Portal | [developer_portal](developer_portal.screen.md) | portrait |
| Match | Join Match | [join_match](join_match.screen.md) | portrait |
| Match | Join Private Room | [join_private_room](join_private_room.screen.md) | portrait |
| Match | Create Match | [create_match](create_match.screen.md) | portrait |
| Match | Match Lobby | [match_lobby](match_lobby.screen.md) | portrait |
| Match | Training Room | [training_room](training_room.screen.md) | portrait |
| Match | Rotate Device | [rotate_device](rotate_device.screen.md) | portrait (phone only) |
| Match | Match Start | [match_start](match_start.screen.md) | landscape |
| Match | In-Game HUD | [in_game_hud](in_game_hud.screen.md) | landscape |
| Match | Pause Menu | [pause_menu](pause_menu.screen.md) | landscape |
| Match | Eliminated | [eliminated](eliminated.screen.md) | landscape |
| Match | Round Result | [round_result](round_result.screen.md) | landscape |
| Match | Spectator HUD | [spectator_hud](spectator_hud.screen.md) | landscape |
| Match | Post-Game Results | [post_game_results](post_game_results.screen.md) | portrait |
| Match | Match Replay | [match_replay](match_replay.screen.md) | portrait |
| Match | Replay Viewer | [replay_viewer](replay_viewer.screen.md) | landscape |
| Maps | Browse Maps | [browse_maps](browse_maps.screen.md) | portrait |
| Maps | Map Editor | [map_editor](map_editor.screen.md) | landscape |
| System | System Dialogs | [system_dialogs](system_dialogs.screen.md) | portrait |
