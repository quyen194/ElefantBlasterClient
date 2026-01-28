/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/02 15:52
  filename:  ElefantBlaster/ElefantBlasterClient/entrypoint/entrypoint.cpp

  purpose:   Define the entry point for the Elefant Blaster client application.
*********************************************************************/


// -----------------------------------------------------------------------------
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>

#include "states/game_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#if defined(_WIN32)
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif  // _WIN32
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

SDL_AppResult SDL_Fail(){
  SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
  return SDL_APP_FAILURE;
}
// -----------------------------------------------------------------------------

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
  GameState* game_state = GameState::CreateInstance();
  *appstate = game_state;

  if (!game_state->Initialize()) {
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}
// -----------------------------------------------------------------------------

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event* event) {
  GameState* game_state = reinterpret_cast<GameState*>(appstate);

  game_state->OnEvent(*event);

  return SDL_APP_CONTINUE;
}
// -----------------------------------------------------------------------------

SDL_AppResult SDL_AppIterate(void *appstate) {
  GameState* game_state = reinterpret_cast<GameState*>(appstate);

  game_state->OnLoop();

  return game_state->AppQuit();
}
// -----------------------------------------------------------------------------

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
  GameState* gamestate = reinterpret_cast<GameState*>(appstate);
  delete gamestate;
}
// -----------------------------------------------------------------------------
