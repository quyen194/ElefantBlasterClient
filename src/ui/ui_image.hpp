/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/11/09 15:41
  filename:  ElefantBlaster/ElefantBlasterClient/ui/ui_image.hpp

  purpose:   Define UiImage, a UI kit image with its 1x size, 9-slice and tint flag.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_UI_UI_IMAGE_HPP
#define ELEFANT_BLASTER_CLIENT_UI_UI_IMAGE_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <imgui.h>
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
struct SDL_Texture;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct UiImage {
  SDL_Texture* texture = nullptr; // owned by AssetManager
  ImVec2 size = {};               // 1x design px (w, h)
  bool has_slice = false;
  float slice_top = 0.0f;         // 1x px
  float slice_right = 0.0f;       // 1x px
  float slice_bottom = 0.0f;      // 1x px
  float slice_left = 0.0f;        // 1x px
  bool tint = false;              // should fill color
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_UI_UI_IMAGE_HPP
// -----------------------------------------------------------------------------
