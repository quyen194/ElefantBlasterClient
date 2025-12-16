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
#include "entities/spoil.hpp"
#include "states/sdl_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace _PlayerDir {
enum T {
  kDown,
  kUp,
  kLeft,
  kRight,
  kMax,
};
};
typedef _PlayerDir::T PlayerDir;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace _PlayerNo {
enum T {
  k1,
  k2,
  kMax,
};
};
typedef _PlayerNo::T PlayerNo;
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

  AssetTexture MapTexture(MapTileType object) { return map_textures_[object]; }
  AssetTexture SpoilTexture(SpoilType object) { return map_textures_[object]; }

  SDL_Texture* DragonEggGstTexture() { return dragon_egg_gst_texture_; }

  Animation PlayerAnimation() { return player_animation_; }
  SDL_Texture* PlayerTexture(PlayerNo no) { return player_textures_[no]; }

 private:
  void Unload();
  SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &filepath);

 private:
  SDLState &sdl_state_;

  float sprite_size_;

  std::vector<AssetTexture> map_textures_;
  std::vector<AssetTexture> spoil_textures_;

  SDL_Texture *dragon_egg_gst_texture_;

  Animation player_animation_;
  std::vector<SDL_Texture *> player_textures_;

  static AssetManager* instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AssetManager);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_CORE_ASSET_MANAGER_HPP
// -----------------------------------------------------------------------------
