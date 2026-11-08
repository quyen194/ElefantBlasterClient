/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/02 21:40
  filename:  ElefantBlaster/ElefantBlasterClient/core/asset_manager.hpp

  purpose:   Manage game assets including textures and animations.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_CORE_ASSET_MANAGER_HPP
#define ELEFANT_BLASTER_CLIENT_CORE_ASSET_MANAGER_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

#include <imgui.h>

#include "definitions/macro.hpp"

#include "effects/animation.hpp"

#include "entities/map_tile.hpp"
#include "entities/player.hpp"
#include "entities/spoil.hpp"

#include "core/sdl_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
struct AssetTexture {
  SDL_Texture *sdl_texture;
  SDL_FRect rect;
};
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

class AssetManager {
 public:
  AssetManager(SDLState &sdl_state);
  virtual ~AssetManager();

  static AssetManager& Instance() { return *instance_; }

  bool Initialize();

  bool Load();

  bool LoadImFonts();
  ImFont* ImFontRegular() { return font_regular_; }
  ImFont* ImFontMedium() { return font_medium_; }
  ImFont* ImFontBold() { return font_bold_; }

  float SpriteSize() { return sprite_size_; }

  const AssetTexture* GetAssetTexture(const std::string& id);

  SDL_FRect PlayerStandRect(MoveDir dir);
  Animation PlayerAnimation(MoveDir dir);
  SDL_FRect PlayerAnimationRect(MoveDir dir);

  const UiImage* GetUiImage(const std::string& name) const;

 private:
  bool LoadUiKit();
  void Unload();
  static std::filesystem::path R(std::filesystem::path path);
  SDL_Texture* loadTexture(SDL_Renderer* renderer,
                           const std::filesystem::path& filepath,
                           SDL_ScaleMode scale_mode = SDL_SCALEMODE_NEAREST);

 private:
  SDLState &sdl_state_;

  AssetTexture background_h_;
  AssetTexture background_v_;
  AssetTexture dialog_login_bg_v_;

  ImFont* font_regular_;
  ImFont* font_medium_;
  ImFont* font_bold_;

  float sprite_size_;

  std::unordered_map<std::string, AssetTexture> asset_textures_;

  std::vector<SDL_FRect> player_stand_rects_;
  std::vector<Animation> player_animations_;
  std::vector<SDL_FRect> player_animation_rects_;

  std::unordered_map<std::string, UiImage> ui_images_;
  int ui_kit_scale_;

  std::vector<SDL_Texture*> textures_;

 private:
  static AssetManager* instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AssetManager);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_CORE_ASSET_MANAGER_HPP
// -----------------------------------------------------------------------------
