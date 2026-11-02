# Login

Mockup: mockups/index.html#login · Mobile: portrait · Status: draft
From: Connecting, Logout · To: Main Menu, Create Account, Forgot Password, Login as Guest

## Purpose
Sign in with an existing account.

## Elements
- Background art; logo (left on desktop, top on phone).
- Dialog art `dlg_login_back.png` with:
  - `Account` field and `Password` field, both drawn on `label_input_box.png`
    (label in the blue part, value in the white part).
  - `Remember me` checkbox, `Forgot password?` link.
  - `Login` button (primary).
- Under the logo: connection chip, `Create account`, `Watch as guest`.
- Version string.

## Actions
| Control | Result |
| --- | --- |
| Login / Enter key | Send credentials → Main Menu |
| Remember me | Server issues a session token, stored locally; next launch skips Login |
| Forgot password? | Forgot Password |
| Create account | Create Account |
| Watch as guest | Login as Guest |
| Tab | Account → Password → Login |

## States
- Idle; Login disabled while either field is empty.
- Sending: button shows a spinner, fields read-only.
- Wrong account or password: one message for both ("Account or password is incorrect"),
  password field cleared, focus back on it.
- Too many attempts: "Try again in N s".
- Not connected: Login disabled, chip shows the problem.

## Mobile
- Dialog fits portrait well (scaled by width).
- Soft keyboard covers the lower half: scroll the dialog so the focused field stays visible.
- Password field uses the password keyboard (no autocorrect).

## Server
- Login request → session token (+ remember token when asked).
- Rate-limit attempts per account and per IP.

## Open questions
- Store the remember token where on each platform (file, browser storage, Android keystore)?
