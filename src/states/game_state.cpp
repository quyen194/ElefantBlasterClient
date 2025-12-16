/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/06 6:10
  filename:  ElefantBlaster/ElefantBlasterClient/states/game_state.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include <glm/glm.hpp>

#include <SDL3/SDL.h>

#include "states/game_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#define MAP_WIDTH
#define MAP_HEIGHT
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

GameState::GameState()
    : sdl_state_(),
      asset_manager_(sdl_state_),
      map_manager_(sdl_state_, asset_manager_),
      inited_(false) {
  if (!sdl_state_.Initialize()) {
    return;
  }

  if (!asset_manager_.Initialize()) {
    return;
  }

  if (!map_manager_.Initialize()) {
    return;
  }

  inited_ = true;
}
// -----------------------------------------------------------------------------

GameState::~GameState() {
}
// -----------------------------------------------------------------------------

void GameState::Loop() {
  if (!inited_) {
    return;
  }

  uint64_t prevTime = SDL_GetTicks();

  // start the game loop
  bool running = true;
  while (running) {
    uint64_t nowTime = SDL_GetTicks();
    float deltaTime = (nowTime - prevTime) / 1000.0f;
    // deltaTime = 0.0001f;
    SDL_Event event = {};
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT: {
          running = false;
        }
        break;

        case SDL_EVENT_WINDOW_RESIZED: {
          sdl_state_.SetWidth(event.window.data1);
          sdl_state_.SetHeight(event.window.data2);
        }
        break;
      }
    }

    // update all objects
    map_manager_.Update(deltaTime);

    // perform drawing commands
    SDL_SetRenderDrawColor(sdl_state_.Renderer(), 20, 10, 30, 255);
    SDL_RenderClear(sdl_state_.Renderer());

    // draw all objects
    map_manager_.Draw();

    // display some debug info
    // SDL_SetRenderDrawColor(sdl_state_.Renderer(), 255, 255, 255, 255);
    // SDL_RenderDebugTextFormat(sdl_state_.Renderer(), 5, 5, "State: %lu", gs.player().data.player.state);

    // swap buffers and present
    SDL_RenderPresent(sdl_state_.Renderer());

    prevTime = nowTime;
  }
}
// -----------------------------------------------------------------------------
