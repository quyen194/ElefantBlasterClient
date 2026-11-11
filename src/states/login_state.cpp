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
struct LoginDesign {
  float logo[4];    // x, y, w, h (design px)
  float dialog[4];
  float form[4];
  float fs;         // auth field font size
  float gap;        // vertical gap between form rows
  float button_h;   // Login button height
};
constexpr LoginDesign kLoginLandscape = {{164, 231, 560, 373},  // logo
                                         {849, 109, 487, 730},  // dialog
                                         {917, 368, 351, 347},  // form
                                         22,                    // fs
                                         14,                    // gap
                                         61};                   // button_h
constexpr LoginDesign kLoginPortrait = {{45, 32, 300, 200},     // logo
                                        {15, 225, 360, 540},    // dialog
                                        {62, 417, 266, 256},    // form
                                        16,                     // fs
                                        10,                     // gap
                                        48};                    // button_h
constexpr float kRowH = 22.0f;      // "Remember me" row height (design px)
constexpr float kRowFont = 15.0f;   // "Remember me" / link font size
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

  // draw form
  const float s = L.scale;
  const float w = form.Size().x;
  const float field_h = d.fs * 0.8f * 1.1f + 3.0f + d.fs * 2.2f;  // design px
  const float total_h = (2 * field_h + kRowH + d.button_h + 3 * d.gap) * s;

  ImGui::SetNextWindowPos(form.min);
  ImGui::SetNextWindowSize(form.Size());
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});  // before Begin
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0.0f, d.gap * s});
  ImGui::Begin("##login_form",
               nullptr,
               ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground |
                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

  // centre the whole stack vertically inside the form rect
  ImGui::SetCursorPosY((form.Size().y - total_h) * 0.5f);

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
  ImGui::SameLine(w - forgot_w);                 // right-aligned
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
  if (ui::GameButton("##login", "Login", "yellow", {w, d.button_h * s}, s,
                     can_submit)) {
    submit = true;
  }

  ImGui::End();
  ImGui::PopStyleVar(2);   // ItemSpacing, WindowPadding

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
