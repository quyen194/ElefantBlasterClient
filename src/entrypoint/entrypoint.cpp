/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/02 15:52
  filename:  ElefantBlaster/ElefantBlasterClient/entrypoint/entrypoint.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include <SDL3/SDL.h>

#include "states/sdl_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#ifdef _WIN32
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif  // _WIN32
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

int main(int argc, char *argv[]) {
  // init game window
  SDLState sdl_state;

  if (!sdl_state.isInited()) {
    return 1;
  }

  return 0;
}
// -----------------------------------------------------------------------------
