# Connecting

Mockup: mockups/index.html#splash · Mobile: portrait · Status: draft
From: app launch · To: Login, or Main Menu when a remembered session is still valid

## Purpose
Load assets and connect to the central server before anything else is shown.

## Elements
- Background art, large logo.
- Progress bar: real asset loading progress (textures, fonts, sounds).
- Status chip: `Connecting to <region>…` → `Connected · <region> · <ping> ms`.
- One random gameplay tip.
- Version string (bottom).

## Actions
None. The screen moves on by itself.

## States
- Loading assets → connecting → connected (go to Login).
- Remembered session token valid → go straight to Main Menu.
- Connection failed → "Connection lost" dialog (see System Dialogs) with Retry / Quit.
- Client too old for the server → dialog "Update required" (desktop: link to download page; web: reload).

## Mobile
Same layout stacked vertically.

## Server
- Version handshake on connect.
- Optional: validate a remembered session token.
