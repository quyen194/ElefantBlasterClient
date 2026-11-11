/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/11/09 11:40
  filename:  ElefantBlaster/ElefantBlasterClient/ui/draw.hpp

  purpose:   Declare ImGui draw helpers for UI kit images (plain, 9-slice, cover).
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_UI_DRAW_HPP
#define ELEFANT_BLASTER_CLIENT_UI_DRAW_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <imgui.h>

#include "ui/ui_image.hpp"
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
struct SDL_Texture;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace ui {
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// UI kit PNGs are exported with this pad (1x px) around the CSS box; it holds
// overflow such as shadows and focus rings. Draw kit images outset by it.
constexpr float kKitMargin = 10.0f;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
ImTextureRef TexRef(SDL_Texture* tex);

void DrawImage(ImDrawList* dl,
               const UiImage& img,
               ImVec2 p_min,
               ImVec2 p_max,
               ImU32 col = IM_COL32_WHITE);
void DrawNineSlice(ImDrawList* dl,
                   const UiImage& img,
                   ImVec2 p_min,
                   ImVec2 p_max,
                   float scale,
                   ImU32 col = IM_COL32_WHITE);
void DrawCover(ImDrawList* dl,
               SDL_Texture* tex,
               ImVec2 tex_size,
               ImVec2 p_min,
               ImVec2 p_max);
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
} // namespace ui
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_UI_DRAW_HPP
// -----------------------------------------------------------------------------
