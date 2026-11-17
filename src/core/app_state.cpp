/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/06 6:10
  filename:  ElefantBlaster/ElefantBlasterClient/core/app_state.cpp

  purpose:   Define AppState class for managing the application state.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <glm/glm.hpp>

#include <SDL3/SDL.h>

#include "core/app_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
 AppState* AppState::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

AppState::AppState()
    : sdl_state_(),
      asset_manager_(sdl_state_),
      imgui_state_(sdl_state_, asset_manager_),
      login_state_(sdl_state_, asset_manager_, imgui_state_),
      match_state_(sdl_state_, asset_manager_),
      app_quit_(SDL_APP_CONTINUE),
      state_(State::kLogin) {
}
// -----------------------------------------------------------------------------

AppState::~AppState() {
  instance_ = nullptr;
}
// -----------------------------------------------------------------------------

AppState* AppState::CreateInstance() {
  instance_ = new AppState();
  return instance_;
}
// -----------------------------------------------------------------------------

bool AppState::Initialize() {
  if (!sdl_state_.Initialize()) {
    return false;
  }

  if (!imgui_state_.Initialize()) {
    return false;
  }

  if (!asset_manager_.Initialize()) {
    return false;
  }

  if (!login_state_.Initialize()) {
    return false;
  }

  if (!match_state_.Initialize()) {
    return false;
  }

  sdl_state_.ShowWindow();

  app_time_ = SDL_GetTicks();

  return true;
}
// -----------------------------------------------------------------------------

void AppState::OnLoop() {
  uint64_t now_time = SDL_GetTicks();
  float delta_time = (now_time - app_time_) / 1000.0f;
  // delta_time = 0.0001f;

  // update all objects
  OnUpdate(delta_time);

  // perform drawing commands
  SDL_SetRenderDrawColor(sdl_state_.Renderer(), 20, 10, 30, 255);
  SDL_RenderClear(sdl_state_.Renderer());

  imgui_state_.BeginFrame();

  // draw all objects
  OnDraw();

  imgui_state_.EndFrame();

  // swap buffers and present
  SDL_RenderPresent(sdl_state_.Renderer());

  app_time_ = now_time;
}
// -----------------------------------------------------------------------------

void AppState::OnUpdate(float delta_time) {
  switch (state_) {
    case State::kLogin: {
      login_state_.OnUpdate(delta_time);
    } break;

    case State::kMatch: {
      match_state_.OnUpdate(delta_time);
    } break;
  }
}
// -----------------------------------------------------------------------------

void AppState::OnDraw() {
  switch (state_) {
    case State::kLogin: {
      login_state_.OnDraw();
    } break;

    case State::kMatch: {
      match_state_.OnDraw();
    } break;
  }
}
// -----------------------------------------------------------------------------

void AppState::OnEvent(SDL_Event &event) {
  // system events
  switch (event.type) {
    case SDL_EVENT_QUIT: {
      app_quit_ = SDL_APP_SUCCESS;
    } break;

    case SDL_EVENT_WINDOW_RESIZED: {
      sdl_state_.SetWidth(event.window.data1);
      sdl_state_.SetHeight(event.window.data2);
    } break;
  }

  // dear imgui events
  imgui_state_.OnEvent(event);

  // app input events
  switch (event.type) {
    case SDL_EVENT_KEY_DOWN: {
      if (!imgui_state_.WantKeyboard()) {
        OnHandleKeyInput(event.key);
      }
    } break;
  }
}
// -----------------------------------------------------------------------------

bool AppState::OnHandleKeyInput(SDL_KeyboardEvent &key_event) {
  bool processed = false;

  switch (state_) {
    case State::kLogin: {
    } break;

    case State::kMatch: {
      processed = match_state_.OnHandleKeyInput(key_event);
    } break;
  }

  return processed;
}
// -----------------------------------------------------------------------------
