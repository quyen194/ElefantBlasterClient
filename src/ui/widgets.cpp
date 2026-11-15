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
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct LabelStyle {
  ImU32 text;
  ImU32 shadow;  // 0 = no shadow
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

// Widgets run every frame: warn about a missing image only once per name.
void WarnMissingImageOnce(const std::string& name) {
  static std::unordered_set<std::string> warned;
  if (warned.insert(name).second) {
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                "UI kit: missing image '%s', drawing fallback",
                name.c_str());
  }
}
// -----------------------------------------------------------------------------

LabelStyle LabelStyleFor(const std::string& variant) {
  std::string v = variant;
  if (v.rfind("sm_", 0) == 0) {
    v = v.substr(3);
  }
  if (v == "blue") {
    return {kWhite, IM_COL32(0x1b, 0x4f, 0xa8, 0xff)};
  }
  if (v == "red") {
    return {kWhite, IM_COL32(0x8e, 0x1e, 0x18, 0xff)};
  }
  if (v == "green") {
    return {kWhite, IM_COL32(0x1d, 0x62, 0x19, 0xff)};
  }
  return {kGtext, 0};
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
}  // namespace
// -----------------------------------------------------------------------------

bool GameButton(const char* id,
                const char* label,
                const char* variant,
                ImVec2 size,
                float scale,
                bool enabled,
                float font_px) {
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
    ImVec2 m(kKitMargin * scale, kKitMargin * scale);
    DrawNineSlice(dl, *ui_image, p_min - m, p_max + m, scale);
  }

  ImGui::PushFont(asset_manager.ImFontTitle(), font_px * scale);

  const char* label_end = ImGui::FindRenderedTextEnd(label);
  ImVec2 ts = ImGui::CalcTextSize(label, label_end);
  ImVec2 pos = p_min + (size - ts) / 2;
  if (state == "pressed") {
    pos.y += 2 * scale;
  }
  LabelStyle ls = LabelStyleFor(variant);
  if (ls.shadow != 0) {
    dl->AddText(pos + ImVec2(0, 2 * scale), ls.shadow, label, label_end);
  }
  dl->AddText(pos, ls.text, label, label_end);

  ImGui::PopFont();

  if (!enabled) {
    ImGui::EndDisabled();
  }

  return clicked;
}
// -----------------------------------------------------------------------------

bool AuthField(const char* id,
               const char* label,
               const char* icon,
               const char* hint,
               char* buf,
               size_t buf_size,
               ImGuiInputTextFlags flags,
               float fs,
               float scale,
               float width) {
  AssetManager& asset_manager = AssetManager::Instance();
  ImDrawList* dl = ImGui::GetWindowDrawList();

  // 1. Label (drawn directly, then the cursor is moved below it by hand)
  ImVec2 top = ImGui::GetCursorScreenPos();
  float label_px = fs * 0.8f * scale;
  ImGui::PushFont(asset_manager.ImFontTitle(), label_px);
  dl->AddText({top.x + 4.0f * scale, top.y}, kNavy, label);
  ImGui::PopFont();

  // 2. Box geometry
  float text_px = fs * scale;
  ImVec2 size = {width, fs * 2.2f * scale};
  ImVec2 box_min(top.x, top.y + label_px * 1.1f + 3.0f * scale);
  ImVec2 box_max = box_min + size;

  // 3. Foreground channel: transparent InputText over the box
  dl->ChannelsSplit(2);
  dl->ChannelsSetCurrent(1);  // foreground: InputText draws here

  ImGui::PushStyleColor(ImGuiCol_FrameBg, 0);
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, 0);
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, 0);
  ImGui::PushStyleColor(ImGuiCol_Text, kGtext);
  ImGui::PushStyleColor(ImGuiCol_TextDisabled, kHint);
  ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
  float pad_left = (0.6f + 1.05f + 0.45f) * fs * scale;
  float pad_top = (size.y - text_px) / 2;
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {pad_left, pad_top});
  ImGui::PushFont(asset_manager.ImFontBody(), text_px);

  ImGui::SetCursorScreenPos(box_min);
  ImGui::SetNextItemWidth(width);
  bool result = ImGui::InputTextWithHint(id, hint, buf, buf_size, flags);
  bool active = ImGui::IsItemActive();  // now refers to the InputText

  ImGui::PopFont();
  ImGui::PopStyleVar(2);
  ImGui::PopStyleColor(5);

  // 4. Background channel: box + icon, drawn below the text
  dl->ChannelsSetCurrent(0);  // background: drawn below channel 1

  ImVec2 m(kKitMargin * scale, kKitMargin * scale);
  if (const UiImage* box = asset_manager.GetUiImage(active ? "input_focus" : "input")) {
    DrawNineSlice(dl, *box, box_min - m, box_max + m, scale);
  }
  if (const UiImage* ic = asset_manager.GetUiImage(icon)) {
    float s = 1.05f * fs * scale;
    ImVec2 ic_min(box_min.x + 0.6f * fs * scale,
                  box_min.y + (size.y - s) * 0.5f);
    DrawImage(
        dl, *ic, ic_min, ic_min + ImVec2(s, s), active ? kNavy : kIconIdle);
  }

  dl->ChannelsMerge();

  return result;
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
} // namespace ui
// -----------------------------------------------------------------------------
