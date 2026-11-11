/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/11/09 16:17
  filename:  ElefantBlaster/ElefantBlasterClient/ui/widgets.hpp

  purpose:   Declare game-styled ImGui widgets drawn with UI kit images.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_UI_WIDGETS_HPP
#define ELEFANT_BLASTER_CLIENT_UI_WIDGETS_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <imgui.h>
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace ui {
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

bool GameButton(const char* id,
                const char* label,
                const char* variant,
                ImVec2 size,
                float scale,
                bool enabled = true,
                float font_px = 20.0f);
// -----------------------------------------------------------------------------
// Label above a 9-slice input box with a tinted icon on the left.
// Returns true when Enter is pressed (if flags has EnterReturnsTrue).
bool AuthField(const char* id,
               const char* label,
               const char* icon,
               const char* hint,
               char* buf,
               size_t buf_size,
               ImGuiInputTextFlags flags,
               float fs,
               float scale,
               float width);
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
} // namespace ui
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_UI_WIDGETS_HPP
// -----------------------------------------------------------------------------
