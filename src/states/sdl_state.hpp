/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/02 16:17
  filename:  ElefantBlaster/ElefantBlasterClient/states/sdl_state.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_STATES_SDL_STATE_HPP
#define ELEFANT_BLASTER_CLIENT_STATES_SDL_STATE_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include "definitions/macro.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class SDLState {
 public:
  SDLState();
  virtual ~SDLState();

  bool initialize();
  void cleanup();

  bool isInited();

  inline void SetWidth(int value) { width_ = value; }
  inline void SetHeight(int value) { height_ = value; }

  inline int Width() const { return width_; }
  inline int Height() const { return height_; }
  inline int LogW() const { return logW_; }
  inline int LogH() const { return logH_; }

  SDL_Window *Window() const { return window_; }
  SDL_Renderer *Renderer() const { return renderer_; }

  bool Key(int index) const { return keys_[index]; }

 private:
  bool inited;

  int width_;
  int height_;
  int logW_;
  int logH_;

  SDL_Window *window_;
  SDL_Renderer *renderer_;

  const bool *keys_;

 private:
  DISALLOW_COPY_AND_ASSIGN(SDLState);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_STATES_SDL_STATE_HPP
// -----------------------------------------------------------------------------
