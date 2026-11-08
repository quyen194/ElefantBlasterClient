# UI kit

Mockup: mockups/index.html#uikit · Status: exported 2026-11-04 (137 images)

The UI kit is the contract between the mockup and the client. Every item on the `#uikit` page is
exported as one PNG; ImGui draws everything else (text, solid shapes, sprites from the game sheets).

## Output

- Folder: `assets/graphics/ui/`, file `<name>.png`, rendered at **@2x**, transparent background.
- `assets/graphics/ui/ui_kit.json`: one entry per image:
  `{ "name", "w", "h", "scale": 2, "slice": [top, right, bottom, left] | null, "tint": bool }`.
  Sizes and slices are in 1x pixels; multiply by `scale` for texels.

## Rules

- **No text in images.** Labels, numbers and titles are drawn by ImGui with the type scale below,
  so changing wording or language never needs new art.
- **9-slice** items (buttons, panels, chips, inputs, bars) stretch to any size; draw the 9 parts
  with `AddImage` and UVs computed from `slice`. Corners keep their size, multiplied by `UiScale()`.
- **Tint** items are white; colour them with the `col` argument of `AddImage`
  (player rings, icons).
- Button states: `normal`, `hover` (desktop/web only), `pressed`, `disabled`.
- Avatars need no image: `AddImageRounded` with rounding = half the size crops the player sprite.
- Map tiles, eggs, bombs, explosions, players and dialog art keep coming from their existing sheets.

## Colour tokens

| Token | Value | Use |
| --- | --- | --- |
| navy | `#1b2f6e` | outlines, headings, table header |
| sun | `#ffcf2e` | primary button, title text |
| sky | `#2f8cf0` | secondary button |
| leaf | `#3fa33a` | success, ready, checkbox |
| berry | `#e8473f` | danger, leave |
| gtext | `#1b2a55` | body text on light panels |
| p1 / p2 | `#ff9f1a` / `#3aa8ff` | player colours (rings, quarantine frames) |

## Type

| Font | Use | Sizes (1x, logical 1500×948) |
| --- | --- | --- |
| Lilita One | titles, buttons, numbers | sign 26, button 20 (small 15), panel title 21, timer 30, countdown 160 |
| Nunito 700–900 | body, labels, tables | body 15, small 12–13, table 15 (phone 13), caps label 12 |

Shipped in `assets/fonts/` (SIL OFL, licences next to them): `LilitaOne-Regular.ttf`,
`Nunito-Bold.ttf`, `Nunito-ExtraBold.ttf`, `Nunito-Black.ttf`. Nunito comes as static weights because
ImGui's stb_truetype ignores variable-font axes.

**Lilita One has no Vietnamese glyphs.** For Vietnamese titles, load Lilita One and then merge
Nunito Black into it (`ImFontConfig::MergeMode = true`) so missing glyphs fall back to Nunito.

## Groups

Buttons (2 sizes × 5 colours × 4 states), panels and containers, inputs and selection controls,
bars and timeline, HUD and touch controls, icons (24 px), backdrops. The `#uikit` page is the
authoritative list.

## Re-exporting

1. Change the item in `UIKIT` (mockup `index.html`) and its look in the CSS.
2. Serve `ElefantBlasterClient/` over HTTP (e.g. `python -m http.server`) and open `#uikit`.
3. With a headless browser at `deviceScaleFactor: 2`, make page/container backgrounds transparent and
   screenshot every `[data-ex]` element with a transparent background to
   `assets/graphics/ui/<data-ex>.png`.
4. Rebuild `ui_kit.json` from `UIKIT` (slice, tint, note) and the PNG sizes divided by 2.
