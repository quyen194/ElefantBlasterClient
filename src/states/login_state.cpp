/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/29 05:09
  filename:  ElefantBlaster/ElefantBlasterClient/states/login_state.cpp

  purpose:   Define LoginState class for managing the login state.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include "states/login_state.hpp"
#include "ui/colors.hpp"
#include "ui/draw.hpp"
#include "ui/layout.hpp"
#include "ui/widgets.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace {
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
struct LoginDesign {
  float logo[4];    // x, y, w, h (design px)
  float dialog[4];
  float form[4];
  float fs;         // auth field font size
  float gap;        // vertical gap between form rows
  float button_h;   // Login button height
  float chip[4];    // connection chip (x, y, w, h)
  float create[4];  // "Create account" ghost button
  float guest[4];   // "Watch as guest" ghost button
  float link_fs;    // ghost button font size
};
// -----------------------------------------------------------------------------

constexpr LoginDesign kLoginLandscape = {{164, 231, 560, 373},  // logo
                                         {849, 109, 487, 730},  // dialog
                                         {917, 368, 351, 347},  // form
                                         22,                    // fs
                                         14,                    // gap
                                         61,                    // button_h
                                         {355, 622, 178, 33},   // chip
                                         {239, 673, 200, 50},   // create
                                         {449, 673, 200, 50},   // guest
                                         20};                   // link_fs

constexpr LoginDesign kLoginPortrait = {{45, 32, 300, 200},     // logo
                                        {15, 225, 360, 540},    // dialog
                                        {62, 417, 266, 256},    // form
                                        16,                     // fs
                                        10,                     // gap
                                        48,                     // button_h
                                        {49, 787, 70, 33},      // chip
                                        {127, 787, 133, 33},    // create
                                        {268, 787, 74, 33},     // guest
                                        15};                    // link_fs

constexpr float kRowH = 22.0f;      // "Remember me" row height (design px)
constexpr float kRowFont = 15.0f;   // "Remember me" / link font size
constexpr const char* kClientVersion = "v0.3.0-dev";  // TODO: from CMake
constexpr ImGuiWindowFlags kOverlayFlags =
    ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground |
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
// -----------------------------------------------------------------------------

void DrawStatusChip(ImDrawList* dl,
                    AssetManager& am,
                    const ui::Rect& r,
                    ImU32 dot_col,
                    const char* text,
                    float s) {
  if (const UiImage* img = am.GetUiImage("status_chip")) {
    ImVec2 m(ui::kKitMargin * s, ui::kKitMargin * s);
    ui::DrawNineSlice(dl, *img, r.min - m, r.max + m, s);
  }

  const float h = r.Size().y;
  ImVec2 dot(r.min.x + h * 0.5f, r.min.y + h * 0.5f);

  dl->AddCircleFilled(
      dot, 7.5f * s, (dot_col & ~IM_COL32_A_MASK) | IM_COL32(0, 0, 0, 64));
  dl->AddCircleFilled(dot, 4.5f * s, dot_col);

  ImFont* font = am.ImFontBodyStrong();
  const float px = 14.0f * s;

  ImVec2 pos(dot.x + 12.5f * s, r.min.y + (h - px) * 0.5f);

  dl->AddText(font, px, pos, ui::kWhite, text);
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
} // namespace
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

LoginState::LoginState(SDLState& sdl_state,
                       AssetManager& asset_manager,
                       ImguiState& imgui_state)
    : sdl_state_(sdl_state),
      asset_manager_(asset_manager),
      imgui_state_(imgui_state),
      username_{0},
      password_{0},
      remember_(false) {}
// -----------------------------------------------------------------------------

LoginState::~LoginState() {
  Cleanup();
}
// -----------------------------------------------------------------------------

bool LoginState::Initialize() {
  return true;
}
// -----------------------------------------------------------------------------

void LoginState::Cleanup() {
}
// -----------------------------------------------------------------------------

void LoginState::OnDraw() {
  SDL_Rect safe = sdl_state_.SafeArea();
  ui::Layout L = ui::ComputeLayout(ImGui::GetIO().DisplaySize, safe);

  const LoginDesign& d = L.portrait ? kLoginPortrait : kLoginLandscape;
  ui::Rect logo = L.R(d.logo[0], d.logo[1], d.logo[2], d.logo[3]);
  ui::Rect dialog = L.R(d.dialog[0], d.dialog[1], d.dialog[2], d.dialog[3]);
  ui::Rect form = L.R(d.form[0], d.form[1], d.form[2], d.form[3]);
  ui::Rect chip = L.R(d.chip[0], d.chip[1], d.chip[2], d.chip[3]);
  ui::Rect create = L.R(d.create[0], d.create[1], d.create[2], d.create[3]);
  ui::Rect guest = L.R(d.guest[0], d.guest[1], d.guest[2], d.guest[3]);

  // draw background
  ImDrawList* bg = ImGui::GetBackgroundDrawList();
  const AssetTexture* bg_tex = asset_manager_.GetAssetTexture(
      L.portrait ? "home/background_v" : "home/background_h");
  if (bg_tex) {
    ui::DrawCover(bg,
                  bg_tex->sdl_texture,
                  {bg_tex->rect.w, bg_tex->rect.h},
                  {0, 0},
                  L.display);
  }

  // draw veil
  const ImU32 veil_dark  = IM_COL32(8, 18, 58, 140);   // .55
  const ImU32 veil_light = IM_COL32(8, 18, 58, 26);    // .10
  const ImU32 veil_clear = IM_COL32(8, 18, 58, 0);     // 0
  if (L.portrait) {
    // vertical: top .10 -> bottom .55, full screen
    bg->AddRectFilledMultiColor({0, 0},
                                L.display,
                                veil_light,  // upper left
                                veil_light,  // upper right
                                veil_dark,   // bottom right
                                veil_dark);  // bottom left
  }
  else {
    // horizontal: left .55 -> 0 at 45% width; nothing to the right
    ImVec2 p_max(L.display.x * 0.45f, L.display.y);
    bg->AddRectFilledMultiColor({0, 0},
                                p_max,
                                veil_dark,   // upper left
                                veil_clear,  // upper right
                                veil_clear,  // bottom right
                                veil_dark);  // bottom left
  }

  // draw logo
  if (const AssetTexture* t = asset_manager_.GetAssetTexture("home/logo")) {
    bg->AddImage(ui::TexRef(t->sdl_texture), logo.min, logo.max);
  }

  // draw dialog
  if (const AssetTexture* t =
          asset_manager_.GetAssetTexture("home/dlg_login_back")) {
    bg->AddImage(ui::TexRef(t->sdl_texture), dialog.min, dialog.max);
  }

  // draw connection chip
  const char* chip_text =
      L.portrait ? "42 ms" : "Connected \xC2\xB7 asia-1 \xC2\xB7 42 ms";
  DrawStatusChip(bg,
                 asset_manager_,
                 chip,
                 IM_COL32(0x3f, 0xd3, 0x5a, 0xff),
                 chip_text,
                 L.scale);

  // draw version (bottom-right of the safe area, desktop only)
  if (!L.portrait) {
    ImFont* vf = asset_manager_.ImFontBody();
    const float vpx = 12.0f * L.scale;
    ImVec2 ts = vf->CalcTextSizeA(vpx, FLT_MAX, 0.0f, kClientVersion);
    ImVec2 br = L.FromBottomRight(18.0f, 12.0f);
    bg->AddText(vf, vpx, br - ts, IM_COL32(255, 255, 255, 204), kClientVersion);
  }

  // draw form
  const float s = L.scale;
  const float w = form.Size().x;
  const float field_h = d.fs * 0.8f * 1.1f + 3.0f + d.fs * 2.2f;  // design px
  const float total_h = (2 * field_h + kRowH + d.button_h + 3 * d.gap) * s;

  ImVec2 m(ui::kKitMargin * s, ui::kKitMargin * s);
  ImGui::SetNextWindowPos(form.min - m);
  ImGui::SetNextWindowSize(form.Size() + m * 2.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, m);  // before Begin
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0.0f, d.gap * s});
  ImGui::Begin("##login_form", nullptr, kOverlayFlags);

  // centre the whole stack vertically inside the form rect
  ImGui::SetCursorPosY(m.y + (form.Size().y - total_h) * 0.5f);

  // Account + Password
  ui::AuthField("##account",
                "Account",
                "icon_user",
                "Your account",
                username_,
                sizeof(username_),
                0,
                d.fs,
                s,
                w);
  bool submit = ui::AuthField(
      "##password",
      "Password",
      "icon_lock",
      "Password",
      password_,
      sizeof(password_),
      ImGuiInputTextFlags_Password | ImGuiInputTextFlags_EnterReturnsTrue,
      d.fs,
      s,
      w);

  // Remember me (left) + Forgot password? (right)
  ImDrawList* dl = ImGui::GetWindowDrawList();
  ImGui::PushFont(asset_manager_.ImFontBodyStrong(), kRowFont * s);
  const float row_h = kRowH * s;
  const float text_y_off = (row_h - kRowFont * s) * 0.5f;

  const char* kRemember = "Remember me";
  const float box = 22.0f * s;
  const float gap_x = 8.0f * s;
  ImVec2 row_min = ImGui::GetCursorScreenPos();
  float remember_w = box + gap_x + ImGui::CalcTextSize(kRemember).x;
  if (ImGui::InvisibleButton("##remember", {remember_w, row_h})) {
    remember_ = !remember_;
  }
  if (const UiImage* img = asset_manager_.GetUiImage(
          remember_ ? "checkbox_on" : "checkbox_off")) {
    ImVec2 b_min(row_min.x, row_min.y + (row_h - box) * 0.5f);
    ImVec2 m(ui::kKitMargin * s, ui::kKitMargin * s);
    ui::DrawImage(dl, *img, b_min - m, b_min + ImVec2(box, box) + m);
  }
  dl->AddText(
      {row_min.x + box + gap_x, row_min.y + text_y_off}, ui::kGtext, kRemember);

  const char* kForgot = "Forgot password?";
  float forgot_w = ImGui::CalcTextSize(kForgot).x;
  ImGui::SameLine(m.x + w - forgot_w);                 // right-aligned
  ImVec2 link_min = ImGui::GetCursorScreenPos();
  if (ImGui::InvisibleButton("##forgot", {forgot_w, row_h})) {
    SDL_Log("Login: forgot password clicked");   // TODO: go to Forgot Password
  }
  bool link_hover = ImGui::IsItemHovered();
  if (link_hover) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
  }
  ImU32 link_col = link_hover ? ui::kNavy : ui::kLink;
  float text_y = link_min.y + text_y_off;
  dl->AddText({link_min.x, text_y}, link_col, kForgot);
  dl->AddLine({link_min.x, text_y + kRowFont * s + 1.0f * s},
              {link_min.x + forgot_w, text_y + kRowFont * s + 1.0f * s},
              link_col, 1.5f * s);
  ImGui::PopFont();

  // Login button (disabled while a field is empty)
  bool can_submit = username_[0] != '\0' && password_[0] != '\0';
  if (ui::GameButton("##login",
                     "Login",
                     "yellow",
                     {w, d.button_h * s},
                     s,
                     can_submit,
                     L.portrait ? 20.0f : 26.0f)) {
    submit = true;
  }

  ImGui::End();
  ImGui::PopStyleVar(2);   // ItemSpacing, WindowPadding

  // ghost buttons under the logo
  ui::Rect links = {create.min, guest.max};
  ImGui::SetNextWindowPos(links.min - m);
  ImGui::SetNextWindowSize(links.Size() + m * 2.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, m);
  ImGui::Begin("##login_links", nullptr, kOverlayFlags);

  const char* variant = L.portrait ? "sm_ghost" : "ghost";
  ImGui::SetCursorScreenPos(create.min);
  if (ui::GameButton("##create",
                     "Create account",
                     variant,
                     create.Size(),
                     L.scale,
                     true,
                     d.link_fs)) {
    SDL_Log("Login: create account clicked");  // TODO: go to Create Account
  }
  ImGui::SetCursorScreenPos(guest.min);
  if (ui::GameButton("##guest",
                     L.portrait ? "Guest" : "Watch as guest",
                     variant,
                     guest.Size(),
                     L.scale,
                     true,
                     d.link_fs)) {
    SDL_Log("Login: watch as guest clicked");  // TODO: go to Login as Guest
  }

  ImGui::End();
  ImGui::PopStyleVar();

  if (submit && can_submit) {
    OnSubmit();
  }
}
// -----------------------------------------------------------------------------

void LoginState::OnSubmit() {
  // Never log the password.
  SDL_Log("Login: submit account '%s' (remember=%d)", username_, remember_);
  // TODO(4e): send to server, switch to Sending state
}
// -----------------------------------------------------------------------------

void LoginState::OnEvent(SDL_Event &event) {
}
// -----------------------------------------------------------------------------
