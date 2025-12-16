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

  map_textures_.resize(MapTileType::kMax);
  map_textures_[MapTileType::kGrass].sdl_texture = map_texture;
  map_textures_[MapTileType::kGrass].rect = { AssetTileType::kGrass * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[MapTileType::kWall].sdl_texture = map_texture;
  map_textures_[MapTileType::kWall].rect = { AssetTileType::kWall * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[MapTileType::kBalk].sdl_texture = map_texture;
  map_textures_[MapTileType::kBalk].rect = { AssetTileType::kBalk * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[MapTileType::kTeleportGate].sdl_texture = map_texture;
  map_textures_[MapTileType::kTeleportGate].rect = { AssetTileType::kTeleportGate * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[MapTileType::kQuarantineZone].sdl_texture = map_texture;
  map_textures_[MapTileType::kQuarantineZone].rect = { AssetTileType::kQuarantineZone * sprite_size_, 0, sprite_size_, sprite_size_ };
  map_textures_[MapTileType::kDragonEggGst].sdl_texture = map_texture;
  map_textures_[MapTileType::kDragonEggGst].rect = { AssetTileType::kDragonEggGst * sprite_size_, 0, sprite_size_, sprite_size_ };

  SDL_Texture *spoil_texture = loadTexture(renderer, "assets/graphics/tilesets/spoils.png");

  spoil_textures_.resize(SpoilType::kMax);
  spoil_textures_[SpoilType::kDragonEggMystic].sdl_texture = map_texture;
  spoil_textures_[SpoilType::kDragonEggMystic].rect = { SpoilType::kDragonEggMystic * sprite_size_, 0, sprite_size_, sprite_size_ };
  spoil_textures_[SpoilType::kDragonEggAttack].sdl_texture = map_texture;
  spoil_textures_[SpoilType::kDragonEggAttack].rect = { SpoilType::kDragonEggAttack * sprite_size_, 0, sprite_size_, sprite_size_ };
  spoil_textures_[SpoilType::kDragonEggDelay].sdl_texture = map_texture;
  spoil_textures_[SpoilType::kDragonEggDelay].rect = { SpoilType::kDragonEggDelay * sprite_size_, 0, sprite_size_, sprite_size_ };
  spoil_textures_[SpoilType::kDragonEggSpeed].sdl_texture = map_texture;
  spoil_textures_[SpoilType::kDragonEggSpeed].rect = { SpoilType::kDragonEggSpeed * sprite_size_, 0, sprite_size_, sprite_size_ };

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

SDL_Texture *AssetManager::loadTexture(SDL_Renderer *renderer,
                                       const std::string &filepath) {
  SDL_Texture *tex = IMG_LoadTexture(renderer, filepath.c_str());
  SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
  return tex;
}
// -----------------------------------------------------------------------------
