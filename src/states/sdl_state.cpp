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
 SDLState* SDLState::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

SDLState::SDLState()
    : inited_(false),
      width_(1800),
      height_(1000),
      logW_(1500),
      logH_(948),
      window_(nullptr),
      renderer_(nullptr),
      keys_(SDL_GetKeyboardState(nullptr)) {}
// -----------------------------------------------------------------------------

SDLState::~SDLState() {
  Cleanup();
}
// -----------------------------------------------------------------------------

bool SDLState::IsInited() {
  return inited_;
}
// -----------------------------------------------------------------------------

bool SDLState::Initialize() {
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
      Cleanup();
      result = false;
    }
  }

  if (result) {
    // create the renderer
    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (!renderer_) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", nullptr);
      Cleanup();
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

  inited_ = result;

  return result;
}
// -----------------------------------------------------------------------------

void SDLState::Cleanup() {
  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
  }
  if (window_) {
    SDL_DestroyWindow(window_);
  }
  SDL_Quit();
}
// -----------------------------------------------------------------------------
