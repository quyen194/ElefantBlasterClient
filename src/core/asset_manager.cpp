/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/02 21:41
  filename:  ElefantBlaster/ElefantBlasterClient/core/asset_manager.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "states/sdl_state.hpp"

#include "entities/map_tile.hpp"
#include "entities/spoil.hpp"

#include "effects/animation.hpp"
#include "core/asset_manager.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
 AssetManager* AssetManager::instance_ = nullptr;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

AssetManager::AssetManager(SDLState &sdl_state)
     : sdl_state_(sdl_state), sprite_size_(32.0f) {
  instance_ = this;
}
// -----------------------------------------------------------------------------

AssetManager::~AssetManager() {
  Unload();
}
// -----------------------------------------------------------------------------

bool AssetManager::Initialize() {
  Load();

  return true;
}
// -----------------------------------------------------------------------------

void AssetManager::Load() {
  SDL_Renderer *renderer = sdl_state_.Renderer();

  SDL_Texture *map_texture = loadTexture(renderer, "assets/graphics/tilesets/map.png");

  sprite_size_ = static_cast<float>(map_texture->h);

  map_textures_.resize(AssetTileType::kMax);
  map_textures_[AssetTileType::kGrass].sdl_texture = map_texture;
  map_textures_[AssetTileType::kGrass].rect = { AssetTileType::kGrass * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[AssetTileType::kWall].sdl_texture = map_texture;
  map_textures_[AssetTileType::kWall].rect = { AssetTileType::kWall * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[AssetTileType::kBalk].sdl_texture = map_texture;
  map_textures_[AssetTileType::kBalk].rect = { AssetTileType::kBalk * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[AssetTileType::kTeleportGate].sdl_texture = map_texture;
  map_textures_[AssetTileType::kTeleportGate].rect = { AssetTileType::kTeleportGate * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[AssetTileType::kQuarantineZone].sdl_texture = map_texture;
  map_textures_[AssetTileType::kQuarantineZone].rect = { AssetTileType::kQuarantineZone * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[AssetTileType::kDragonEggGst].sdl_texture = map_texture;
  map_textures_[AssetTileType::kDragonEggGst].rect = { AssetTileType::kDragonEggGst * sprite_size_, 0, sprite_size_, sprite_size_ };

  dragon_egg_gst_texture_ = loadTexture(renderer, "assets/graphics/animations/dragon_egg_gst.png");

  SDL_Texture *spoil_texture = loadTexture(renderer, "assets/graphics/tilesets/spoils.png");

  spoil_textures_.resize(AssetSpoilType::kMax);
  spoil_textures_[AssetSpoilType::kDragonEggMystic].sdl_texture = spoil_texture;
  spoil_textures_[AssetSpoilType::kDragonEggMystic].rect = { 0, AssetSpoilType::kDragonEggMystic * sprite_size_, sprite_size_, sprite_size_ };
  spoil_textures_[AssetSpoilType::kDragonEggAttack].sdl_texture = spoil_texture;
  spoil_textures_[AssetSpoilType::kDragonEggAttack].rect = { 0, AssetSpoilType::kDragonEggAttack * sprite_size_, sprite_size_, sprite_size_ };
  spoil_textures_[AssetSpoilType::kDragonEggDelay].sdl_texture = spoil_texture;
  spoil_textures_[AssetSpoilType::kDragonEggDelay].rect = { 0, AssetSpoilType::kDragonEggDelay * sprite_size_, sprite_size_, sprite_size_ };
  spoil_textures_[AssetSpoilType::kDragonEggSpeed].sdl_texture = spoil_texture;
  spoil_textures_[AssetSpoilType::kDragonEggSpeed].rect = { 0, AssetSpoilType::kDragonEggSpeed * sprite_size_, sprite_size_, sprite_size_ };

  player_animation_ = Animation(4, 1.6f);

  player_textures_.resize(PlayerNo::kMax);
  player_textures_[PlayerNo::k1] = loadTexture(renderer, "assets/graphics/animations/player1.png");
  player_textures_[PlayerNo::k2] = loadTexture(renderer, "assets/graphics/animations/player2.png");
}
// -----------------------------------------------------------------------------

void AssetManager::Unload() {
  for (AssetTexture tex : map_textures_) {
    SDL_DestroyTexture(tex.sdl_texture);
  }
  for (AssetTexture tex : spoil_textures_) {
    SDL_DestroyTexture(tex.sdl_texture);
  }
  for (SDL_Texture *tex : player_textures_) {
    SDL_DestroyTexture(tex);
  }
}
// -----------------------------------------------------------------------------

AssetTexture AssetManager::MapTexture(MapTileType type) {
  switch (type) {
    case MapTileType::kGrass:
      return map_textures_[AssetTileType::kGrass];
    case MapTileType::kWall:
      return map_textures_[AssetTileType::kWall];
    case MapTileType::kBalk:
      return map_textures_[AssetTileType::kBalk];
    case MapTileType::kTeleportGate:
      return map_textures_[AssetTileType::kTeleportGate];
    case MapTileType::kQuarantineZone:
      return map_textures_[AssetTileType::kQuarantineZone];
    case MapTileType::kDragonEggGst:
      return map_textures_[AssetTileType::kDragonEggGst];
  }

  return map_textures_[AssetTileType::kGrass];
}
// -----------------------------------------------------------------------------

AssetTexture AssetManager::SpoilTexture(SpoilType object) {
  switch (object) {
    case SpoilType::kDragonEggSpeed:
      return spoil_textures_[AssetSpoilType::kDragonEggSpeed];
    case SpoilType::kDragonEggAttack:
      return spoil_textures_[AssetSpoilType::kDragonEggAttack];
    case SpoilType::kDragonEggDelay:
      return spoil_textures_[AssetSpoilType::kDragonEggDelay];
    case SpoilType::kDragonEggMystic:
      return spoil_textures_[AssetSpoilType::kDragonEggMystic];
  }

  return spoil_textures_[AssetSpoilType::kDragonEggMystic];
}
// -----------------------------------------------------------------------------

SDL_Texture *AssetManager::loadTexture(SDL_Renderer *renderer,
                                       const std::string &filepath) {
  SDL_Texture *tex = IMG_LoadTexture(renderer, filepath.c_str());
  SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
  return tex;
}
// -----------------------------------------------------------------------------
