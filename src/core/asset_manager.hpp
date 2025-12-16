/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/02 21:40
  filename:  ElefantBlaster/ElefantBlasterClient/core/asset_manager.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_CORE_ASSET_MANAGER_HPP
#define ELEFANT_BLASTER_CLIENT_CORE_ASSET_MANAGER_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <string>
#include <vector>

#include "definitions/macro.hpp"

#include "effects/animation.hpp"

#include "entities/map_tile.hpp"
#include "entities/player.h"
#include "entities/spoil.hpp"

#include "states/sdl_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
struct AssetTexture {
  SDL_Texture *sdl_texture;
  SDL_FRect rect;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

class AssetManager {
 public:
  AssetManager(SDLState &sdl_state);
  virtual ~AssetManager();

  static AssetManager& Instance() { return *instance_; }

  bool Initialize();

  void Load();

  float SpriteSize() { return sprite_size_; }

  AssetTexture MapTexture(MapTileType type);
  AssetTexture SpoilTexture(SpoilType type);

  SDL_Texture* DragonEggGstTexture() { return dragon_egg_gst_texture_; }

  SDL_Texture* PlayerTexture(PlayerNo no) { return player_textures_[no]; }
  SDL_FRect PlayerStandRect(MoveDir dir);
  Animation PlayerAnimation(MoveDir dir);
  SDL_FRect PlayerAnimationRect(MoveDir dir);

 private:
  void Unload();
  SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &filepath);

 private:
  SDLState &sdl_state_;

  float sprite_size_;

  std::vector<AssetTexture> map_textures_;
  std::vector<AssetTexture> spoil_textures_;

  SDL_Texture *dragon_egg_gst_texture_;

  std::vector<SDL_Texture *> player_textures_;
  std::vector<SDL_FRect> player_stand_rects_;
  std::vector<Animation> player_animations_;
  std::vector<SDL_FRect> player_animation_rects_;

  static AssetManager* instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AssetManager);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_CORE_ASSET_MANAGER_HPP
// -----------------------------------------------------------------------------
