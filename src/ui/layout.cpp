/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/11/10 05:41
  filename:  ElefantBlaster/ElefantBlasterClient/ui/layout.cpp

  purpose:   Implement the design-space layout (scale, origin, edge anchors).
*********************************************************************/


// -----------------------------------------------------------------------------
#include <algorithm>

#include <SDL3/SDL.h>

#include "ui/layout.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace ui {
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

ImVec2 Layout::P(float x, float y) const {
  return origin + ImVec2(x, y) * scale;
}
// -----------------------------------------------------------------------------

ImVec2 Layout::S(float w, float h) const { return ImVec2(w, h) * scale; }
// -----------------------------------------------------------------------------

float Layout::S(float v) const { return v * scale; }
// -----------------------------------------------------------------------------

Rect Layout::R(float x, float y, float w, float h) const {
  return {P(x, y), P(x + w, y + h)};
}
// -----------------------------------------------------------------------------

ImVec2 Layout::FromRight(float dx, float y) const {
  return ImVec2(safe_max.x - dx * scale, origin.y + y * scale);
}
// -----------------------------------------------------------------------------

ImVec2 Layout::FromBottom(float x, float dy) const {
  return ImVec2(origin.x + x * scale, safe_max.y - dy * scale);
}
// -----------------------------------------------------------------------------

ImVec2 Layout::FromBottomRight(float dx, float dy) const {
  return ImVec2(safe_max - ImVec2(dx, dy) * scale);
}
// -----------------------------------------------------------------------------

Layout ComputeLayout(ImVec2 display, const SDL_Rect& safe) {
  ImVec2 safe_min(static_cast<float>(safe.x), static_cast<float>(safe.y));
  ImVec2 safe_max(static_cast<float>(safe.x + safe.w),
                  static_cast<float>(safe.y + safe.h));

  Layout l;
  l.display = display;
  l.safe_min = safe_min;
  l.safe_max = safe_max;
  l.portrait = display.y > display.x;
  l.design = l.portrait ? kDesignPortrait : kDesignLandscape;

  ImVec2 safe_size = safe_max - safe_min;
  if (safe_size.x <= 0.0f || safe_size.y <= 0.0f) {   // minimized window
    return l;                               // scale = 1, origin = 0
  }

  l.scale =
      std::min(safe_size.x / l.design.x, safe_size.y / l.design.y);  // contain
  l.origin = safe_min + (safe_size - l.design * l.scale) * 0.5f;     // centre
  return l;
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
} // namespace ui
// -----------------------------------------------------------------------------
