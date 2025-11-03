/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/02 16:16
  filename:  ElefantBlaster/ElefantBlasterClient/states/sdl_state.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include <SDL3/SDL.h>

#include "states/sdl_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

SDLState::SDLState()
    : width_(800),
      height_(600),
      logW_(640),
      logH_(320),
      window_(nullptr),
      renderer_(nullptr),
      keys_(SDL_GetKeyboardState(nullptr)) {
  inited = initialize();
}
// -----------------------------------------------------------------------------

SDLState::~SDLState() {
  cleanup();
}
// -----------------------------------------------------------------------------

bool SDLState::isInited() {
  return inited;
}
// -----------------------------------------------------------------------------

bool SDLState::initialize() {
  bool result = true;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
    result = false;
  }

  if (result) {
    // create the window
    window_ = SDL_CreateWindow("BomberMan", width_, height_, SDL_WINDOW_RESIZABLE);
    if (!window_) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
      cleanup();
      result = false;
    }
  }

  if (result) {
    // create the renderer
    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (!renderer_) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", nullptr);
      cleanup();
      result = false;
    }
  }

  if (result) {
    // configure presentation
    SDL_SetRenderLogicalPresentation(renderer_,
                                     logW_,
                                     logH_,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);
  }

  return result;
}
// -----------------------------------------------------------------------------

void SDLState::cleanup() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}
// -----------------------------------------------------------------------------
