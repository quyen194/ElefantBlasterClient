/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/11/10 05:38
  filename:  ElefantBlaster/ElefantBlasterClient/ui/layout.hpp

  purpose:   Map design-space coordinates (1x mockup px) to screen coordinates.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_UI_LAYOUT_HPP
#define ELEFANT_BLASTER_CLIENT_UI_LAYOUT_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <imgui.h>

#include <SDL3/SDL_rect.h>
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace ui {
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
constexpr ImVec2 kDesignLandscape = {1500.0f, 948.0f};
constexpr ImVec2 kDesignPortrait = {390.0f, 844.0f};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct Rect {
  ImVec2 min;
  ImVec2 max;
  ImVec2 Size() const { return max - min; }
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Maps design-space coordinates (1x mockup px) to screen coordinates.
struct Layout {
  ImVec2 display = {};  // io.DisplaySize (window points)
  ImVec2 safe_min = {}; // safe area (notch / rounded corners), screen coords
  ImVec2 safe_max = {};
  ImVec2 design = {};   // kDesignLandscape or kDesignPortrait
  bool portrait = false;
  float scale = 1.0f;   // design px -> screen px
  ImVec2 origin = {};   // top-left of the design rect on screen

  ImVec2 P(float x, float y) const;   // design point  -> screen point
  ImVec2 S(float w, float h) const;   // design size   -> screen size
  float S(float v) const;             // design length -> screen length
  Rect R(float x,
         float y,
         float w,
         float h) const;              // design rect -> screen rect
  ImVec2 FromRight(float dx, float y) const;    // dx from safe right edge
  ImVec2 FromBottom(float x, float dy) const;   // dy from safe bottom edge
  ImVec2 FromBottomRight(float dx, float dy) const;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

Layout ComputeLayout(ImVec2 display, const SDL_Rect& safe);
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
} // namespace ui
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_UI_LAYOUT_HPP
// -----------------------------------------------------------------------------
