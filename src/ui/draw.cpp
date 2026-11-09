/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/11/09 11:40
  filename:  ElefantBlaster/ElefantBlasterClient/ui/draw.cpp

  purpose:   Implement ImGui draw helpers for UI kit images (plain, 9-slice, cover).
*********************************************************************/


// -----------------------------------------------------------------------------
#include <algorithm>

#include <SDL3/SDL.h>

#include "core/asset_manager.hpp"
#include "ui/draw.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

ImTextureRef ui::TexRef(SDL_Texture* tex) {
  return ImTextureRef((ImTextureID) (intptr_t) tex);
}
// -----------------------------------------------------------------------------

void ui::DrawImage(
    ImDrawList* dl, const UiImage& img, ImVec2 p_min, ImVec2 p_max, ImU32 col) {
  dl->AddImage(TexRef(img.texture),
               {p_min.x, p_min.y},
               {p_max.x, p_max.y},
               {0, 0},
               {1, 1},
               col);
}
// -----------------------------------------------------------------------------

void ui::DrawNineSlice(ImDrawList* dl,
                       const UiImage& img,
                       ImVec2 p_min,
                       ImVec2 p_max,
                       float scale,
                       ImU32 col) {
  if (!img.has_slice) {
    DrawImage(dl, img, p_min, p_max, col);
    return;
  }

  float dst_w = p_max.x - p_min.x;
  float dst_h = p_max.y - p_min.y;

  if (dst_w <= 0.0f || dst_h <= 0.0f) {
    return;
  }

  // Shrink corners uniformly when the rect is smaller than the slices.
  float k = 1.0f;
  float need_w = (img.slice_left + img.slice_right) * scale;
  float need_h = (img.slice_top + img.slice_bottom) * scale;
  if (need_w > dst_w && need_w > 0.0f) {
    k = std::min(k, dst_w / need_w);
  }
  if (need_h > dst_h && need_h > 0.0f) {
    k = std::min(k, dst_h / need_h);
  }
  float cs = scale * k;

  float x[4] = {};
  float y[4] = {};
  float u[4] = {};
  float v[4] = {};

  x[0] = p_min.x;
  x[1] = x[0] + img.slice_left * cs;
  x[2] = p_max.x - img.slice_right * cs;
  x[3] = p_max.x;

  y[0] = p_min.y;
  y[1] = y[0] + img.slice_top * cs;
  y[2] = p_max.y - img.slice_bottom * cs;
  y[3] = p_max.y;

  u[0] = 0;
  u[1] = img.slice_left / img.size.x;
  u[2] = 1 - img.slice_right / img.size.x;
  u[3] = 1;

  v[0] = 0;
  v[1] = img.slice_top / img.size.y;
  v[2] = 1 - img.slice_bottom / img.size.y;
  v[3] = 1;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      dl->AddImage(TexRef(img.texture),
                   {x[i], y[j]},
                   {x[i + 1], y[j + 1]},
                   {u[i], v[j]},
                   {u[i + 1], v[j + 1]},
                   col);
    }
  }
}
// -----------------------------------------------------------------------------

void ui::DrawCover(ImDrawList* dl,
                   SDL_Texture* tex,
                   ImVec2 tex_size,
                   ImVec2 p_min,
                   ImVec2 p_max) {
  float dst_w = p_max.x - p_min.x;
  float dst_h = p_max.y - p_min.y;

  if (!tex || !tex_size.x || !tex_size.y || dst_w <= 0.0f || dst_h <= 0.0f) {
    return;
  }

  float s = std::max(dst_w / tex_size.x, dst_h / tex_size.y);
  float vis_w = dst_w / s;
  float vis_h = dst_h / s;
  ImVec2 uv0((tex_size.x - vis_w) / 2 / tex_size.x,
             (tex_size.y - vis_h) / 2 / tex_size.y);
  ImVec2 uv1(1 - uv0.x, 1 - uv0.y);
  dl->AddImage(TexRef(tex), p_min, p_max, uv0, uv1);
}
// -----------------------------------------------------------------------------
