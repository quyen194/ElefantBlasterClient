/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/11/09 16:17
  filename:  ElefantBlaster/ElefantBlasterClient/ui/widgets.cpp

  purpose:   Implement game-styled ImGui widgets drawn with UI kit images.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <string>
#include <unordered_set>

#include <imgui_internal.h>

#include <SDL3/SDL.h>

#include <aries_base/utils/strings.hpp>

#include "core/asset_manager.hpp"

#include "ui/colors.hpp"
#include "ui/draw.hpp"
#include "ui/widgets.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
using namespace aries_base;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace ui {
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace {

// Widgets run every frame: warn about a missing image only once per name.
void WarnMissingImageOnce(const std::string& name) {
  static std::unordered_set<std::string> warned;
  if (warned.insert(name).second) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                "UI kit: missing image '%s', drawing fallback",
                name.c_str());
  }
}

}  // namespace
// -----------------------------------------------------------------------------

bool GameButton(const char* id,
                const char* label,
                const char* variant,
                ImVec2 size,
                float scale,
                bool enabled) {
  AssetManager& asset_manager = AssetManager::Instance();

  if (!enabled) {
    ImGui::BeginDisabled();
  }

  ImVec2 p_min = ImGui::GetCursorScreenPos();
  bool clicked = ImGui::InvisibleButton(id, size);
  ImVec2 p_max = {p_min.x + size.x, p_min.y + size.y};

  std::string state = "normal";
  if (!enabled) {
    state = "disabled";
  }
  else if (ImGui::IsItemActive()) {
    state = "pressed";
  }
  else if (ImGui::IsItemHovered()) {
    state = "hover";
  }
  std::string name = utils::string_format("btn_%s_%s", variant, state.c_str());

  ImDrawList* dl = ImGui::GetWindowDrawList();

  const UiImage* ui_image = asset_manager.GetUiImage(name);
  if (!ui_image) {
    WarnMissingImageOnce(name);
    dl->AddRectFilled(p_min, p_max, kSun, 8.0f * scale);
  }
  else {
    DrawNineSlice(dl, *ui_image, p_min, p_max, scale);
  }

  ImGui::PushFont(asset_manager.ImFontTitle(), 20.0f * scale);

  const char* label_end = ImGui::FindRenderedTextEnd(label);
  ImVec2 ts = ImGui::CalcTextSize(label, label_end);
  ImVec2 pos = p_min + (size - ts) / 2;
  if (state == "pressed") {
    pos.y += 2 * scale;
  }
  dl->AddText(pos + ImVec2(0, 2 * scale), kNavy, label, label_end);
  dl->AddText(pos, kWhite, label, label_end);

  ImGui::PopFont();

  if (!enabled) {
    ImGui::EndDisabled();
  }

  return clicked;
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
} // namespace ui
// -----------------------------------------------------------------------------
