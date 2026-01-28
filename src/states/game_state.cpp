/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/06 6:10
  filename:  ElefantBlaster/ElefantBlasterClient/states/game_state.cpp

  purpose:   Define GameState class for managing the main game state.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <glm/glm.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL.h>

#include "states/game_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
 GameState* GameState::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

GameState::GameState()
    : sdl_state_(),
      asset_manager_(sdl_state_),
      MapManager(sdl_state_, asset_manager_),
      app_quit_(SDL_APP_CONTINUE) {
}
// -----------------------------------------------------------------------------

GameState::~GameState() {
  instance_ = nullptr;
}
// -----------------------------------------------------------------------------

GameState* GameState::CreateInstance() {
  instance_ = new GameState();
  return instance_;
}
// -----------------------------------------------------------------------------

bool GameState::Initialize() {
  if (!sdl_state_.Initialize()) {
    return false;
  }

  if (!asset_manager_.Initialize()) {
    return false;
  }

  if (!MapManager::Initialize()) {
    return false;
  }

  sdl_state_.ShowWindow();

  TestParsePlayers();

  app_time_ = SDL_GetTicks();

  return true;
}
// -----------------------------------------------------------------------------

void GameState::OnLoop() {
  uint64_t now_time = SDL_GetTicks();
  float delta_time = (now_time - app_time_) / 1000.0f;
  // delta_time = 0.0001f;

  // update all objects
  Update(delta_time);

  // perform drawing commands
  SDL_SetRenderDrawColor(sdl_state_.Renderer(), 20, 10, 30, 255);
  SDL_RenderClear(sdl_state_.Renderer());

  // draw all objects
  Draw();

  // display some debug info
  SDL_SetRenderDrawColor(sdl_state_.Renderer(), 255, 255, 255, 255);
  SDL_RenderDebugTextFormat(sdl_state_.Renderer(), 5, 5, "Pos: [%.02f:%.02f] Frame: %d",
      player1_->movement.screen_pos_current.x,
      player1_->movement.screen_pos_current.y,
      player1_->movement.animation.CurrentFrame());

  // swap buffers and present
  SDL_RenderPresent(sdl_state_.Renderer());

  app_time_ = now_time;
}
// -----------------------------------------------------------------------------

void GameState::Update(float delta_time) {
  MapManager::Update(delta_time);
}
// -----------------------------------------------------------------------------

void GameState::Draw() {
  MapManager::Draw();
}
// -----------------------------------------------------------------------------

void GameState::OnEvent(SDL_Event &event) {
  switch (event.type) {
    case SDL_EVENT_QUIT: {
      app_quit_ = SDL_APP_SUCCESS;
    } break;

    case SDL_EVENT_WINDOW_RESIZED: {
      sdl_state_.SetWidth(event.window.data1);
      sdl_state_.SetHeight(event.window.data2);
    } break;

    case SDL_EVENT_KEY_DOWN: {
      HandleKeyInput(player1_, event);
    } break;
  }
}
// -----------------------------------------------------------------------------

void GameState::HandleKeyInput(Player *player, SDL_Event &event) {
  switch (event.key.scancode) {
    case SDL_SCANCODE_LEFT: {
      if (!player->is_moving) {
        MapManager::MovePlayer(player, MoveDir::kLeft);
      }
    } break;
    case SDL_SCANCODE_RIGHT: {
      if (!player->is_moving) {
        MapManager::MovePlayer(player, MoveDir::kRight);
      }
    } break;
    case SDL_SCANCODE_UP: {
      if (!player->is_moving) {
        MapManager::MovePlayer(player, MoveDir::kUp);
      }
    } break;
    case SDL_SCANCODE_DOWN: {
      if (!player->is_moving) {
        MapManager::MovePlayer(player, MoveDir::kDown);
      }
    } break;
  }
}
// -----------------------------------------------------------------------------

void GameState::TestParsePlayers() {
  std::string strPlayer1 = R"(
      {
        "id": "player1-xxx",
        "currentPosition": {
          "col": 1,
          "row": 3
        },
        "speed": 230,
        "power": 1,
        "delay": 2000,
        "lives": 1000,
        "score": 0,
        "box": 0,
        "dragonEggSpeed": 0,
        "dragonEggAttack": 0,
        "dragonEggDelay": 0,
        "dragonEggMystic": 0,
        "dragonEggMysticAddEgg": 0,
        "dragonEggMysticMinusEgg": 0,
        "dragonEggMysticIsolateGate": 0,
        "gstEggBeingAttacked": 0,
        "quarantine": 0
      }
  )";
  json jPlayer1 = json::parse(strPlayer1);
  UpdatePlayer(jPlayer1);

  std::string strPlayer2 = R"(
      {
         "id": "player2-xxx",
         "currentPosition": {
           "col": 1,
           "row": 10
         },
         "speed": 230,
         "power": 1,
         "delay": 2000,
         "lives": 1000,
         "score": 0,
         "box": 0,
         "dragonEggSpeed": 0,
         "dragonEggAttack": 0,
         "dragonEggDelay": 0,
         "dragonEggMystic": 0,
         "dragonEggMysticAddEgg": 0,
         "dragonEggMysticMinusEgg": 0,
         "dragonEggMysticIsolateGate": 0,
         "gstEggBeingAttacked": 0,
         "quarantine": 0
      }
  )";
  json jPlayer2 = json::parse(strPlayer2);
  UpdatePlayer(jPlayer2);
}
// -----------------------------------------------------------------------------
