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
      MapManager(sdl_state_, asset_manager_),
      inited_(false) {
  if (!sdl_state_.Initialize()) {
    return;
  }

  if (!asset_manager_.Initialize()) {
    return;
  }

  if (!MapManager::Initialize()) {
    return;
  }

  TestParsePlayers();

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

  uint64_t prev_time = SDL_GetTicks();

  // start the game loop
  bool running = true;
  while (running) {
    uint64_t now_time = SDL_GetTicks();
    float delta_time = (now_time - prev_time) / 1000.0f;
    // delta_time = 0.0001f;
    SDL_Event event = {};
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT: {
          running = false;
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

    // update all objects
    Update(delta_time);

    // perform drawing commands
    SDL_SetRenderDrawColor(sdl_state_.Renderer(), 20, 10, 30, 255);
    SDL_RenderClear(sdl_state_.Renderer());

    // draw all objects
    Draw();

    // display some debug info
    SDL_SetRenderDrawColor(sdl_state_.Renderer(), 255, 255, 255, 255);
    SDL_RenderDebugTextFormat(sdl_state_.Renderer(), 5, 5, "Pos: [%.02f:%.02f] Frame: %lu",
        player1_->movement.screen_pos_current.x,
        player1_->movement.screen_pos_current.y,
        player1_->movement.animation.CurrentFrame());

    // swap buffers and present
    SDL_RenderPresent(sdl_state_.Renderer());

    prev_time = now_time;
  }
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
  /*
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
  */
  std::string strPlayer1 =
    "{\n                                                  \
         \"id\": \"player1-xxx\",\n                       \
         \"currentPosition\": {\n                         \
           \"col\": 1,\n                                  \
           \"row\": 3\n                                   \
         },\n                                             \
         \"speed\": 230,\n                                \
         \"power\": 1,\n                                  \
         \"delay\": 2000,\n                               \
         \"lives\": 1000,\n                               \
         \"score\": 0,\n                                  \
         \"box\": 0,\n                                    \
         \"dragonEggSpeed\": 0,\n                         \
         \"dragonEggAttack\": 0,\n                        \
         \"dragonEggDelay\": 0,\n                         \
         \"dragonEggMystic\": 0,\n                        \
         \"dragonEggMysticAddEgg\": 0,\n                  \
         \"dragonEggMysticMinusEgg\": 0,\n                \
         \"dragonEggMysticIsolateGate\": 0,\n             \
         \"gstEggBeingAttacked\": 0,\n                    \
         \"quarantine\": 0\n                              \
     }";
  json jPlayer1 = json::parse(strPlayer1);
  UpdatePlayer(jPlayer1);

  /*
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
  */
  std::string strPlayer2 =
    "{\n                                                  \
         \"id\": \"player2-xxx\",\n                       \
         \"currentPosition\": {\n                         \
           \"col\": 1,\n                                  \
           \"row\": 10\n                                  \
         },\n                                             \
         \"speed\": 230,\n                                \
         \"power\": 1,\n                                  \
         \"delay\": 2000,\n                               \
         \"lives\": 1000,\n                               \
         \"score\": 0,\n                                  \
         \"box\": 0,\n                                    \
         \"dragonEggSpeed\": 0,\n                         \
         \"dragonEggAttack\": 0,\n                        \
         \"dragonEggDelay\": 0,\n                         \
         \"dragonEggMystic\": 0,\n                        \
         \"dragonEggMysticAddEgg\": 0,\n                  \
         \"dragonEggMysticMinusEgg\": 0,\n                \
         \"dragonEggMysticIsolateGate\": 0,\n             \
         \"gstEggBeingAttacked\": 0,\n                    \
         \"quarantine\": 0\n                              \
     }";
  json jPlayer2 = json::parse(strPlayer2);
  UpdatePlayer(jPlayer2);
}
// -----------------------------------------------------------------------------
