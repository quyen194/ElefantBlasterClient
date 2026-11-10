/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/10/10 15:03
  filename:  ElefantBlaster/ElefantBlasterClient/core/imgui_state.cpp

  purpose:   Define ImguiState class for managing Imgui initialization and state.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <algorithm>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <SDL3/SDL.h>

#include "core/imgui_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
ImguiState* ImguiState::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

ImguiState::ImguiState(SDLState& sdl_state, AssetManager& asset_manager)
    : inited_(false),
      sdl_state_(sdl_state),
      asset_manager_(asset_manager),
      ui_scale_(1.0f) {
  instance_ = this;
}
// -----------------------------------------------------------------------------

ImguiState::~ImguiState() {
  Cleanup();
  instance_ = nullptr;
}
// -----------------------------------------------------------------------------

bool ImguiState::Initialize() {
  bool result = true;

  SDL_Window* window = sdl_state_.Window();
  SDL_Renderer *renderer = sdl_state_.Renderer();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsDark();

  base_style_ = ImGui::GetStyle();

  if (result) {
    asset_manager_.LoadImFonts();
  }

  if (result) {
    result = ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    if (!result) {
      ImGui::DestroyContext();
    }
  }

  if (result) {
    result = ImGui_ImplSDLRenderer3_Init(renderer);
    if (!result) {
      ImGui_ImplSDL3_Shutdown();
      ImGui::DestroyContext();
    }
  }

  inited_ = result;

  return inited_;
}
// -----------------------------------------------------------------------------

void ImguiState::Cleanup() {
  if (!inited_) {
    return;
  }

  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  inited_ = false;
}
// -----------------------------------------------------------------------------

void ImguiState::BeginFrame() {
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();

  ImGuiIO& io = ImGui::GetIO();
  if (io.DisplaySize.x > 0.0f && io.DisplaySize.y > 0.0f) {
    // TODO(ui): use ui::ComputeLayout() here once all screens use ui::Layout (Phase 4).
    float ui_scale = std::min(io.DisplaySize.x / sdl_state_.LogW(),
                              io.DisplaySize.y / sdl_state_.LogH());
    if (ui_scale != ui_scale_) {
      ui_scale_ = ui_scale;
      ImGuiStyle& style = ImGui::GetStyle();
      style = base_style_;
      style.ScaleAllSizes(ui_scale_);
    }
  }

  ImGui::NewFrame();
}
// -----------------------------------------------------------------------------

void ImguiState::EndFrame() {
  SDL_Renderer *renderer = sdl_state_.Renderer();

  ImGui::Render();

  int w = sdl_state_.LogW();
  int h = sdl_state_.LogH();
  SDL_RendererLogicalPresentation mode = sdl_state_.PresentationMode();
  SDL_GetRenderLogicalPresentation(renderer, &w, &h, &mode);

  SDL_SetRenderLogicalPresentation(
      renderer, 0, 0, SDL_LOGICAL_PRESENTATION_DISABLED);

  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

  SDL_SetRenderLogicalPresentation(renderer, w, h, mode);
}
// -----------------------------------------------------------------------------

bool ImguiState::OnEvent(SDL_Event &event) {
  return ImGui_ImplSDL3_ProcessEvent(&event);
}
// -----------------------------------------------------------------------------

bool ImguiState::WantMouse() {
  return ImGui::GetIO().WantCaptureMouse;
}
// -----------------------------------------------------------------------------

bool ImguiState::WantKeyboard() {
  return ImGui::GetIO().WantCaptureKeyboard;
}
// -----------------------------------------------------------------------------
