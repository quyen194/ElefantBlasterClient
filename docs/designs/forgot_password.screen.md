# Forgot Password

Mockup: mockups/index.html#forgot · Mobile: portrait · Status: draft (UI only for now)
From: Login · To: Login

## Purpose
Reset a forgotten password with a code sent by email.

## Elements
- Cloud panel with wood sign `RESET`.
- Step bar: `Account` → `Code` → `New password`.
- Step 1: field `Account or email`, button `Send code`.
- Step 2: masked email (`q•••••2@gmail.com`), six code boxes, `Resend in 0:42`.
- Step 3: `New` and `Confirm` password fields, `Reset Password` button.
- `Back to login` link.

## Actions
| Control | Result |
| --- | --- |
| Send code | Always shows step 2, even when the account does not exist |
| Code boxes | Auto-advance; pasting a 6-char code fills all boxes |
| Resend | Enabled after 60 s |
| Reset Password | Set new password → Login with a success toast |

## States
- Wrong code → boxes shake, "Code is incorrect (2 tries left)".
- Code expired → back to step 1.
- Too many tries → "Try again later".

## Mobile
Code boxes use the numeric/uppercase keyboard; support paste from email.

## Server (later)
- Request code, verify code, set password. Codes expire (10 min), limited tries.
- Never reveal whether an account exists.
