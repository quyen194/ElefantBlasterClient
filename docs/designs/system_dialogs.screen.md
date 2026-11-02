# System Dialogs

Mockup: mockups/index.html#dialogs · Mobile: portrait · Status: draft
Used by: every screen

## Purpose
Shared patterns for messages. Build them once as reusable ImGui components.

## Patterns
- **Blocking dialog** (`BeginPopupModal`): icon, title, text, buttons right-aligned, destructive
  button red and on the right. Example: `Connection lost`, reconnecting attempt 2 of 5 + progress,
  `Back to Login` / `Retry now` (cannot be dismissed).
- **Confirm**: `Leave match?`, `Stay` / `Leave`. On phones this is a bottom sheet; tapping outside
  closes it.
- **Error with a way out**: `Room is full`, `OK` / `Quick Join instead`.
- **Toast**: short success info (`Replay saved`), top center, 2 s, never blocks input.
- **Invite card**: see Friends.

## Rules
Only one blocking dialog at a time; toasts queue. Text says what happened and what to do next.
