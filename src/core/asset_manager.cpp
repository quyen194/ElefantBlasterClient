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

#include "effects/animation.hpp"
#include "core/asset_manager.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

AssetManager::AssetManager(SDLState& sdl_state)
    : sdl_state_(sdl_state), sprite_size(32.0f) {
  load(sdl_state_.Renderer());
}
// -----------------------------------------------------------------------------

AssetManager::~AssetManager() {
  unload();
}
// -----------------------------------------------------------------------------

void AssetManager::load(SDL_Renderer *renderer) {
  SDL_Texture *map_texture = loadTexture(renderer, "assets/graphics/tilesets/map.png");

  map_textures.resize(MapObj::kMax);
  map_textures[MapObj::kBalk].sdl_texture = map_texture;
  map_textures[MapObj::kBalk].rect = { MapObj::kBalk * sprite_size, 0, sprite_size, sprite_size };
  map_textures[MapObj::kWall].sdl_texture = map_texture;
  map_textures[MapObj::kWall].rect = { MapObj::kWall * sprite_size, 0, sprite_size, sprite_size };
  map_textures[MapObj::kGrass].sdl_texture = map_texture;
  map_textures[MapObj::kGrass].rect = { MapObj::kGrass * sprite_size, sprite_size, sprite_size };
  map_textures[MapObj::kTeleportGate].sdl_texture = map_texture;
  map_textures[MapObj::kTeleportGate].rect = { MapObj::kTeleportGate * sprite_size, 0, sprite_size, sprite_size };
  map_textures[MapObj::kQuarantineZone].sdl_texture = map_texture;
  map_textures[MapObj::kQuarantineZone].rect = { MapObj::kQuarantineZone * sprite_size, 0, sprite_size, sprite_size };
  map_textures[MapObj::kDragonEggGst].sdl_texture = map_texture;
  map_textures[MapObj::kDragonEggGst].rect = { MapObj::kDragonEggGst * sprite_size, 0, sprite_size, sprite_size };

  SDL_Texture *spoil_texture = loadTexture(renderer, "assets/graphics/tilesets/spoils.png");

  spoil_textures.resize(SpoilObj::kMax);
  spoil_textures[SpoilObj::kDragonEggMystic].sdl_texture = map_texture;
  spoil_textures[SpoilObj::kDragonEggMystic].rect = { SpoilObj::kDragonEggMystic * sprite_size, 0, sprite_size, sprite_size };
  spoil_textures[SpoilObj::kDragonEggAttack].sdl_texture = map_texture;
  spoil_textures[SpoilObj::kDragonEggAttack].rect = { SpoilObj::kDragonEggAttack * sprite_size, 0, sprite_size, sprite_size };
  spoil_textures[SpoilObj::kDragonEggDelay].sdl_texture = map_texture;
  spoil_textures[SpoilObj::kDragonEggDelay].rect = { SpoilObj::kDragonEggDelay * sprite_size, 0, sprite_size, sprite_size };
  spoil_textures[SpoilObj::kDragonEggSpeed].sdl_texture = map_texture;
  spoil_textures[SpoilObj::kDragonEggSpeed].rect = { SpoilObj::kDragonEggSpeed * sprite_size, 0, sprite_size, sprite_size };

  player_animation = Animation(4, 1.6f);

  player_textures.resize(PlayerNo::kMax);
  player_textures[PlayerNo::k1] = loadTexture(renderer, "assets/graphics/animations/player1.png");
  player_textures[PlayerNo::k2] = loadTexture(renderer, "assets/graphics/animations/player2.png");
}
// -----------------------------------------------------------------------------

void AssetManager::unload() {
  for (AssetTexture tex : map_textures) {
    SDL_DestroyTexture(tex.sdl_texture);
  }
  for (AssetTexture tex : spoil_textures) {
    SDL_DestroyTexture(tex.sdl_texture);
  }
  for (SDL_Texture *tex : player_textures) {
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
