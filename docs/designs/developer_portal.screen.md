# Developer Portal

Mockup: mockups/index.html#developer · Mobile: portrait · Status: draft
From: Main Menu, Profile (API Settings) · To: back

## Purpose
Manage the API token and bots that play through the bot API.

## Elements
- API access: token (masked, eye to reveal), `Copy`, `Regenerate`, `Revoke`; status; rate limit
  (100 req/s); usage today (`1,247 / 10,000`) with bar.
- Webhooks: endpoint URL, events (match start, match end, bot error, quota warning), `Save`.
- Active bots: name, status (Live / Off), ping, last active.
- Recent API logs with `View full logs`.

## Actions
`Regenerate` and `Revoke` ask for confirmation and invalidate the old token immediately.

## States
No token yet → `Create token`. Quota near limit → warning row in logs.

## Mobile
Read-only: token (copy), usage, bot status. Webhooks and full logs are desktop only.

## Server
Token CRUD, usage counters, bot presence, log tail.
