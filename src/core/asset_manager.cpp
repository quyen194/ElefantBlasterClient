/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/02 21:41
  filename:  ElefantBlaster/ElefantBlasterClient/core/asset_manager.cpp

  purpose:   Manage game assets including textures and animations.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <string>
#include <vector>

#if defined(__IOS__)
#include <CoreFoundation/CoreFoundation.h>
#endif

#include <aries_base/utils/strings.hpp>

#include <glm/glm.hpp>

#include <nlohmann/json.hpp>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "core/sdl_state.hpp"

#include "entities/map_tile.hpp"
#include "entities/player.hpp"
#include "entities/spoil.hpp"

#include "core/asset_manager.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
using namespace aries_base;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
constexpr int kUiKitVersion = 1;
// -----------------------------------------------------------------------------
 AssetManager* AssetManager::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

AssetManager::AssetManager(SDLState& sdl_state)
    : sdl_state_(sdl_state), sprite_size_(35.0f), ui_kit_scale_(1) {
  instance_ = this;
}
// -----------------------------------------------------------------------------

AssetManager::~AssetManager() {
  Unload();
}
// -----------------------------------------------------------------------------

bool AssetManager::Initialize() {
  return Load();
}
// -----------------------------------------------------------------------------

bool AssetManager::Load() {
  SDL_Renderer *renderer = sdl_state_.Renderer();
  AssetTexture asset_texture;
  SDL_Texture *texture;

  texture = loadTexture(renderer, R("graphics/tilesets/map.png"));
  if (!texture) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Assets: abort load, missing map tileset");
    return false;
  }

  sprite_size_ = static_cast<float>(texture->h);

  asset_texture.sdl_texture = texture;

  asset_texture.rect = { AssetTileType::kGrass * sprite_size_, 0, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetTileType::kGrass), asset_texture);
  asset_texture.rect = { AssetTileType::kWall * sprite_size_, 0, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetTileType::kWall), asset_texture);
  asset_texture.rect = { AssetTileType::kBalk * sprite_size_, 0, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetTileType::kBalk), asset_texture);
  asset_texture.rect = { AssetTileType::kTeleportGate * sprite_size_, 0, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetTileType::kTeleportGate), asset_texture);
  asset_texture.rect = { AssetTileType::kQuarantineZone * sprite_size_, 0, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetTileType::kQuarantineZone), asset_texture);
  asset_texture.rect = { AssetTileType::kDragonEggGst * sprite_size_, 0, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetTileType::kDragonEggGst), asset_texture);

  texture = loadTexture(renderer, R("graphics/animations/dragon_egg_gst.png"));
  if (!texture) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Assets: abort load, missing dragon egg GST animation");
    return false;
  }

  asset_texture.sdl_texture = texture;
  asset_texture.rect = { 0, 0, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetTileType::kDragonEggGst_Ani), asset_texture);

  texture = loadTexture(renderer, R("graphics/tilesets/spoils.png"));
  if (!texture) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Assets: abort load, missing spoil tileset");
    return false;
  }

  asset_texture.sdl_texture = texture;

  asset_texture.rect = { 0, AssetSpoilType::kDragonEggMystic * sprite_size_, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetSpoilType::kDragonEggMystic), asset_texture);
  asset_texture.rect = { 0, AssetSpoilType::kDragonEggAttack * sprite_size_, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetSpoilType::kDragonEggAttack), asset_texture);
  asset_texture.rect = { 0, AssetSpoilType::kDragonEggDelay * sprite_size_, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetSpoilType::kDragonEggDelay), asset_texture);
  asset_texture.rect = { 0, AssetSpoilType::kDragonEggSpeed * sprite_size_, sprite_size_, sprite_size_ };
  asset_textures_.insert_or_assign(GetId(AssetSpoilType::kDragonEggSpeed), asset_texture);

  for (int i = 0; i < PlayerNo::kMax; i++) {
    std::string filename = utils::string_format("player%02d.png", i + 1);
    texture = loadTexture(renderer, R("graphics/animations/" + filename));
    if (!texture) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                   "Assets: abort load, missing player %d animation", i + 1);
      return false;
    }
    asset_texture.sdl_texture = texture;
    asset_texture.rect = { 0, 0, sprite_size_, sprite_size_ };
    asset_textures_.insert_or_assign(GetId(static_cast<PlayerNo>(i)), asset_texture);
  }

  player_stand_rects_.resize(AssetPlayerDir::kMax);
  player_stand_rects_[AssetPlayerDir::kDown] = { sprite_size_, AssetPlayerDir::kDown * sprite_size_, sprite_size_, sprite_size_ };
  player_stand_rects_[AssetPlayerDir::kUp] = { sprite_size_, AssetPlayerDir::kUp * sprite_size_, sprite_size_, sprite_size_ };
  player_stand_rects_[AssetPlayerDir::kLeft] = { sprite_size_, AssetPlayerDir::kLeft * sprite_size_, sprite_size_, sprite_size_ };
  player_stand_rects_[AssetPlayerDir::kRight] = { sprite_size_, AssetPlayerDir::kRight * sprite_size_, sprite_size_, sprite_size_ };

  player_animations_.resize(AssetPlayerDir::kMax);
  player_animations_[AssetPlayerDir::kDown] = Animation(4, 0.25f);
  player_animations_[AssetPlayerDir::kUp] = Animation(4, 0.25f);
  player_animations_[AssetPlayerDir::kLeft] = Animation(4, 0.25f);
  player_animations_[AssetPlayerDir::kRight] = Animation(4, 0.25f);

  player_animation_rects_.resize(AssetPlayerDir::kMax);
  player_animation_rects_[AssetPlayerDir::kDown] = { 0, AssetPlayerDir::kDown * sprite_size_, sprite_size_, sprite_size_ };
  player_animation_rects_[AssetPlayerDir::kUp] = { 0, AssetPlayerDir::kUp * sprite_size_, sprite_size_, sprite_size_ };
  player_animation_rects_[AssetPlayerDir::kLeft] = { 0, AssetPlayerDir::kLeft * sprite_size_, sprite_size_, sprite_size_ };
  player_animation_rects_[AssetPlayerDir::kRight] = { 0, AssetPlayerDir::kRight * sprite_size_, sprite_size_, sprite_size_ };

  return LoadUiKit();
}
// -----------------------------------------------------------------------------

bool AssetManager::LoadUiKit() {
  SDL_Renderer *renderer = sdl_state_.Renderer();

  size_t json_ui_kit_size;
  void* json_ui_kit = SDL_LoadFile(R("graphics/ui/ui_kit.json").string().c_str(),
                                 &json_ui_kit_size);
  if (!json_ui_kit || json_ui_kit_size == 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "UI kit: can't load json file. %s", SDL_GetError());
    return false;
  }

  std::string str_json_ui_kit =
      std::string((char*) json_ui_kit, json_ui_kit_size);
  nlohmann::json j_root = nlohmann::json::parse(
      str_json_ui_kit.begin(), str_json_ui_kit.end(), nullptr, false);

  SDL_free(json_ui_kit);

  if (j_root.is_discarded()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "UI kit: json parse error");
    return false;
  }

  if (!j_root.contains("version") || !j_root["version"].is_number()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "UI kit: missing or invalid 'version'");
    return false;
  }
  int version = j_root["version"].get<int>();
  if (version != kUiKitVersion) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "UI kit: unsupported version %d (expected %d)",
                 version, kUiKitVersion);
    return false;
  }

  if (!j_root.contains("scale") || !j_root["scale"].is_number()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "UI kit: missing or invalid 'scale'");
    return false;
  }
  ui_kit_scale_ = j_root["scale"].get<int>();
  if (ui_kit_scale_ <= 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "UI kit: invalid scale %d", ui_kit_scale_);
    return false;
  }

  if (!j_root.contains("images") || !j_root["images"].is_array()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "UI kit: missing or invalid 'images' array");
    return false;
  }

  ui_images_.clear();

  for (const auto& j_image : j_root["images"]) {
    UiImage ui_image;

    if (!j_image.contains("name") || !j_image["name"].is_string()) {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: skip image without valid 'name'");
      continue;
    }
    std::string name = j_image["name"].get<std::string>();

    if (ui_images_.find(name) != ui_images_.end()) {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: skip duplicate image '%s'", name.c_str());
      continue;
    }

    if (!j_image.contains("file") || !j_image["file"].is_string()) {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: skip '%s', missing or invalid 'file'", name.c_str());
      continue;
    }
    std::string filename = j_image["file"].get<std::string>();

    if (!j_image.contains("w") || !j_image["w"].is_number()) {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: skip '%s', missing or invalid 'w'", name.c_str());
      continue;
    }
    ui_image.size.x = j_image["w"].get<float>();

    if (!j_image.contains("h") || !j_image["h"].is_number()) {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: skip '%s', missing or invalid 'h'", name.c_str());
      continue;
    }
    ui_image.size.y = j_image["h"].get<float>();

    if (!j_image.contains("px_w") || !j_image["px_w"].is_number()) {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: skip '%s', missing or invalid 'px_w'", name.c_str());
      continue;
    }
    float px_w = j_image["px_w"].get<float>();

    if (!j_image.contains("px_h") || !j_image["px_h"].is_number()) {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: skip '%s', missing or invalid 'px_h'", name.c_str());
      continue;
    }
    float px_h = j_image["px_h"].get<float>();

    if (j_image.contains("slice") && j_image["slice"].is_array() &&
        j_image["slice"].size() == 4 && j_image["slice"][0].is_number() &&
        j_image["slice"][1].is_number() && j_image["slice"][2].is_number() &&
        j_image["slice"][3].is_number()) {
      const auto& jSlices = j_image["slice"];
      ui_image.slice_top = jSlices[0].get<float>();
      ui_image.slice_right = jSlices[1].get<float>();
      ui_image.slice_bottom = jSlices[2].get<float>();
      ui_image.slice_left = jSlices[3].get<float>();
      ui_image.has_slice = true;

      if (ui_image.slice_left + ui_image.slice_right > ui_image.size.x ||
          ui_image.slice_top + ui_image.slice_bottom > ui_image.size.y) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                    "UI kit: '%s' slice [%g, %g, %g, %g] exceeds size %gx%g",
                    name.c_str(), ui_image.slice_top, ui_image.slice_right,
                    ui_image.slice_bottom, ui_image.slice_left,
                    ui_image.size.x, ui_image.size.y);
      }
    }
    else if (!j_image.contains("slice")) {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: '%s' missing 'slice', use none", name.c_str());
      ui_image.has_slice = false;
    }
    else if (j_image["slice"].is_null()) {
      ui_image.has_slice = false;
    }
    else {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: '%s' invalid 'slice' (expected null or 4 numbers), "
                  "use none", name.c_str());
      ui_image.has_slice = false;
    }

    if (!j_image.contains("tint") || !j_image["tint"].is_boolean()) {
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                  "UI kit: '%s' missing or invalid 'tint', use false",
                  name.c_str());
      ui_image.tint = false;
    }
    else {
      ui_image.tint = j_image["tint"].get<bool>();
    }

    SDL_Texture* texture = loadTexture(
        renderer, R("graphics/ui/" + filename), SDL_SCALEMODE_LINEAR);
    if (!texture) {
      continue;
    }
    ui_image.texture = texture;

    float image_w, image_h;
    if (SDL_GetTextureSize(texture, &image_w, &image_h)) {
      if (image_w != px_w || image_h != px_h) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                    "UI kit: '%s' size %gx%g differs from json %gx%g",
                    name.c_str(), image_w, image_h, px_w, px_h);
      }
    }

    ui_images_[name] = ui_image;
  }

  SDL_Log("UI kit: %zu images loaded", ui_images_.size());

  return true;
}
// -----------------------------------------------------------------------------

void AssetManager::Unload() {
  for (SDL_Texture *tex : textures_) {
    SDL_DestroyTexture(tex);
  }
  textures_.clear();
  ui_kit_scale_ = 1;
  ui_images_.clear();
  player_stand_rects_.clear();
  player_animations_.clear();
  player_animation_rects_.clear();
  asset_textures_.clear();
}
// -----------------------------------------------------------------------------

bool AssetManager::LoadImFonts() {
  ImGuiIO& io = ImGui::GetIO();
  font_regular_ = io.Fonts->AddFontFromFileTTF(
      R("fonts/Roboto-Regular.ttf").string().c_str(),
      24.0f,
      nullptr,
      io.Fonts->GetGlyphRangesVietnamese());
  IM_ASSERT(font_regular_ != nullptr && "Failed to load Roboto Regular");

  font_bold_ = io.Fonts->AddFontFromFileTTF(
      R("fonts/Roboto-Bold.ttf").string().c_str(),
      32.0f,
      nullptr,
      io.Fonts->GetGlyphRangesVietnamese());
  IM_ASSERT(font_bold_ != nullptr && "Failed to load Roboto Bold");

  font_medium_ = io.Fonts->AddFontFromFileTTF(
      R("fonts/Roboto-Medium.ttf").string().c_str(),
      28.0f,
      nullptr,
      io.Fonts->GetGlyphRangesVietnamese());
  IM_ASSERT(font_medium_ != nullptr && "Failed to load Roboto Medium");

  // Optional: Set default font for all ImGui
  io.FontDefault = font_regular_;

  return true;
}
// -----------------------------------------------------------------------------

const AssetTexture* AssetManager::GetAssetTexture(const std::string& id) {
  auto it = asset_textures_.find(id);
  return it != asset_textures_.end() ? &it->second : nullptr;
}
// -----------------------------------------------------------------------------

SDL_FRect AssetManager::PlayerStandRect(MoveDir dir) {
  switch (dir) {
    case MoveDir::kLeft:
      return player_stand_rects_[AssetPlayerDir::kLeft];
    case MoveDir::kRight:
      return player_stand_rects_[AssetPlayerDir::kRight];
    case MoveDir::kUp:
      return player_stand_rects_[AssetPlayerDir::kUp];
    case MoveDir::kDown:
      return player_stand_rects_[AssetPlayerDir::kDown];
  }

  return player_stand_rects_[AssetPlayerDir::kDown];
}
// -----------------------------------------------------------------------------

Animation AssetManager::PlayerAnimation(MoveDir dir) {
  switch (dir) {
    case MoveDir::kLeft:
      return player_animations_[AssetPlayerDir::kLeft];
    case MoveDir::kRight:
      return player_animations_[AssetPlayerDir::kRight];
    case MoveDir::kUp:
      return player_animations_[AssetPlayerDir::kUp];
    case MoveDir::kDown:
      return player_animations_[AssetPlayerDir::kDown];
  }

  return player_animations_[AssetPlayerDir::kDown];
}
// -----------------------------------------------------------------------------

SDL_FRect AssetManager::PlayerAnimationRect(MoveDir dir) {
  switch (dir) {
    case MoveDir::kLeft:
      return player_animation_rects_[AssetPlayerDir::kLeft];
    case MoveDir::kRight:
      return player_animation_rects_[AssetPlayerDir::kRight];
    case MoveDir::kUp:
      return player_animation_rects_[AssetPlayerDir::kUp];
    case MoveDir::kDown:
      return player_animation_rects_[AssetPlayerDir::kDown];
  }

  return player_animation_rects_[AssetPlayerDir::kDown];
}
// -----------------------------------------------------------------------------

const UiImage* AssetManager::GetUiImage(const std::string& name) const {
  auto it = ui_images_.find(name);
  return it != ui_images_.end() ? &it->second : nullptr;
}
// -----------------------------------------------------------------------------

std::filesystem::path AssetManager::R(std::filesystem::path path) {
#ifdef __EMSCRIPTEN__
    std::string base_path = "/assets";
#elif defined(__ANDROID__)
  std::string base_path = "";
#elif defined(_WIN32) || defined(__linux__) || defined(__APPLE__)
    std::string base_path = "assets";
#endif

#if !defined(__IOS__)
  return std::filesystem::path(base_path) / path;
#else
  CFBundleRef mainBundle = CFBundleGetMainBundle();
  CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
  char base_path[PATH_MAX];
  if (CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8*)base_path, PATH_MAX)) {
      CFRelease(resourceURL);
      return std::filesystem::path(base_path) / path;
  }
  CFRelease(resourceURL);
  return path; // fallback
#endif
}
// -----------------------------------------------------------------------------

SDL_Texture* AssetManager::loadTexture(SDL_Renderer* renderer,
                                       const std::filesystem::path& filepath,
                                       SDL_ScaleMode scale_mode) {
  SDL_Texture *tex = IMG_LoadTexture(renderer, filepath.string().c_str());
  if (!tex) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't load texture %s. %s",
                 filepath.string().c_str(), SDL_GetError());
    return nullptr;
  }

  SDL_SetTextureScaleMode(tex, scale_mode);
  textures_.push_back(tex);
  return tex;
}
// -----------------------------------------------------------------------------
