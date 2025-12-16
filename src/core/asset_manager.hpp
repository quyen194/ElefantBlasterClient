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
#include "definitions/macro.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace _MapObj {
enum T {
  kBalk,
  kWall,
  kGrass,
  kTeleportGate,
  kQuarantineZone,
  kDragonEggGst,
  kMax,
};
};
typedef _MapObj::T MapObj;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace _SpoilObj {
enum T {
  kDragonEggMystic,
  kDragonEggAttack,
  kDragonEggDelay,
  kDragonEggSpeed,
  kMax,
};
};
typedef _SpoilObj::T SpoilObj;
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

  void load(SDL_Renderer *renderer);
  void unload();

  AssetTexture MapTexture(MapObj object) { return map_textures[object]; }
  AssetTexture SpoilTexture(SpoilObj object) { return map_textures[object]; }

  Animation PlayerAnimation() { return player_animation; }
  SDL_Texture* PlayerTexture(PlayerNo no) { return player_textures[no]; }

 private:
  SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &filepath);

 private:
  SDLState &sdl_state_;
  float sprite_size;

  std::vector<AssetTexture> map_textures;
  std::vector<AssetTexture> spoil_textures;

  Animation player_animation;
  std::vector<SDL_Texture *> player_textures;

 private:
  DISALLOW_COPY_AND_ASSIGN(AssetManager);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_CORE_ASSET_MANAGER_HPP
// -----------------------------------------------------------------------------
