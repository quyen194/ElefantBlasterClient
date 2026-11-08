# Create Account

Mockup: mockups/index.html#register · Mobile: portrait · Status: draft
From: Login · To: Main Menu, Login

## Purpose
Register a new player account.

## Elements
- Cloud panel with wood sign `SIGN UP` (needs its own art; the login dialog has "LOGIN" baked in).
- Fields (label above, kit `input` / `input_focus` + icon, same as Login): `Account`, `Email` (optional),
  `Password`, `Confirm password`.
- Password strength bar under Password.
- `I agree to the Terms of Play` checkbox.
- `Create Account` button, `I already have an account` link.

## Actions
| Control | Result |
| --- | --- |
| Create Account | Register → logged in → Main Menu (How to Play opens on first login) |
| I already have an account | Login |

## States
- Validate on blur: account length and characters, password length, confirm matches.
- Create disabled until valid and terms accepted.
- Account taken → message under Account.
- Sending → spinner.

## Mobile
Four fields: scroll the focused field above the keyboard. Email field uses the email keyboard.

## Server
- Register request; password is hashed server-side (PBKDF2, already in aries_base).
- Email kept for password reset.
