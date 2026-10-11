/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/02 16:16
  filename:  ElefantBlaster/ElefantBlasterClient/core/sdl_state.cpp

  purpose:   Define SDLState class for managing SDL initialization and state.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <SDL3/SDL.h>

#include "core/sdl_state.hpp"
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
      presentation_mode_(SDL_LOGICAL_PRESENTATION_LETTERBOX),
      window_(nullptr),
      renderer_(nullptr),
      keys_(SDL_GetKeyboardState(nullptr)) {
  instance_ = this;
}
// -----------------------------------------------------------------------------

SDLState::~SDLState() {
  Cleanup();
  instance_ = nullptr;
}
// -----------------------------------------------------------------------------

bool SDLState::IsInited() {
  return inited_;
}
// -----------------------------------------------------------------------------

bool SDLState::Initialize() {
  bool result = true;
  bool res;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
    result = false;
  }

  if (result) {
    // create the window
    window_ = SDL_CreateWindow("Elefant Blaster", width_, height_, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_HIDDEN);
    if (!window_) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
      SDL_Quit();
      result = false;
    }
  }

  if (result) {
    res = SDL_SetWindowMinimumSize(window_, logW_ * 0.5f, logH_ * 0.5f);
    if (!res) {
      SDL_Log("Can't set window minimum size. %s", SDL_GetError());
    }
  }

  if (result) {
    // create the renderer
    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (!renderer_) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", nullptr);
      SDL_DestroyWindow(window_);
      window_ = nullptr;
      SDL_Quit();
      result = false;
    }
  }

  if (result) {
    // configure presentation
    result = SDL_SetRenderLogicalPresentation(
        renderer_, logW_, logH_, presentation_mode_);
    if (!result) {
      SDL_DestroyRenderer(renderer_);
      renderer_ = nullptr;
      SDL_DestroyWindow(window_);
      window_ = nullptr;
      SDL_Quit();
    }
  }

  if (result) {
    // enable vsync
    res = SDL_SetRenderVSync(renderer_, -1);
    if (!res) {
      SDL_Log("Can't enable VSync with param -1. %s. Try again with param 1", SDL_GetError());
      res = SDL_SetRenderVSync(renderer_, 1);
      if (!res) {
        SDL_Log("Can't enable VSync with param 1. %s", SDL_GetError());
      }
    }
  }

  inited_ = result;

  return inited_;
}
// -----------------------------------------------------------------------------

void SDLState::Cleanup() {
  if (!inited_) {
    return;
  }

  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }
  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }
  SDL_Quit();

  inited_ = false;
}
// -----------------------------------------------------------------------------

void SDLState::ShowWindow() {
  // print some information about the window
  SDL_ShowWindow(window_);
  {
    int width, height, bbwidth, bbheight;
    SDL_GetWindowSize(window_, &width, &height);
    SDL_GetWindowSizeInPixels(window_, &bbwidth, &bbheight);
    SDL_Log("Window size: %ix%i", width, height);
    SDL_Log("Backbuffer size: %ix%i", bbwidth, bbheight);
    if (width != bbwidth){
      SDL_Log("This is a highdpi environment.");
    }
  }
}
// -----------------------------------------------------------------------------
