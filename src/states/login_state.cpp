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
#include "ui/draw.hpp"
#include "ui/layout.hpp"
#include "ui/widgets.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace {
// -----------------------------------------------------------------------------
struct LoginDesign {
  float logo[4];  // x, y, w, h (design px)
  float dialog[4];
  float form[4];
};
constexpr LoginDesign kLoginLandscape = {
    {164, 231, 560, 373}, {849, 109, 487, 730}, {917, 368, 351, 347}};
constexpr LoginDesign kLoginPortrait = {
    {45, 32, 300, 200}, {15, 225, 360, 540}, {62, 417, 266, 256}};
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
      username_{0} {}
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
  if (const AssetTexture* t = asset_manager_.GetAssetTexture("home/logo")) {
    bg->AddImage(ui::TexRef(t->sdl_texture), logo.min, logo.max);
  }
  if (const AssetTexture* t =
          asset_manager_.GetAssetTexture("home/dlg_login_back")) {
    bg->AddImage(ui::TexRef(t->sdl_texture), dialog.min, dialog.max);
  }
}
// -----------------------------------------------------------------------------

void LoginState::OnEvent(SDL_Event &event) {
}
// -----------------------------------------------------------------------------
