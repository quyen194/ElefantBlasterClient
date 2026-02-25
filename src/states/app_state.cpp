/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/06 6:10
  filename:  ElefantBlaster/ElefantBlasterClient/states/app_state.cpp

  purpose:   Define AppState class for managing the application state.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <glm/glm.hpp>

#include <SDL3/SDL.h>

#include "states/app_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
 AppState* AppState::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

AppState::AppState()
    : sdl_state_(),
      asset_manager_(sdl_state_),
      match_state_(sdl_state_, asset_manager_),
      app_quit_(SDL_APP_CONTINUE) {
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

  if (!asset_manager_.Initialize()) {
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

  // draw all objects
  OnDraw();

  // swap buffers and present
  SDL_RenderPresent(sdl_state_.Renderer());

  app_time_ = now_time;
}
// -----------------------------------------------------------------------------

void AppState::OnUpdate(float delta_time) {
  match_state_.OnUpdate(delta_time);
}
// -----------------------------------------------------------------------------

void AppState::OnDraw() {
  match_state_.OnDraw();
}
// -----------------------------------------------------------------------------

void AppState::OnEvent(SDL_Event &event) {
  switch (event.type) {
    case SDL_EVENT_QUIT: {
      app_quit_ = SDL_APP_SUCCESS;
    } break;

    case SDL_EVENT_WINDOW_RESIZED: {
      sdl_state_.SetWidth(event.window.data1);
      sdl_state_.SetHeight(event.window.data2);
    } break;

    case SDL_EVENT_KEY_DOWN: {
      OnHandleKeyInput(event.key);
    } break;
  }
}
// -----------------------------------------------------------------------------

void AppState::OnHandleKeyInput(SDL_KeyboardEvent &key_event) {
  match_state_.OnHandleKeyInput(key_event);
}
// -----------------------------------------------------------------------------
