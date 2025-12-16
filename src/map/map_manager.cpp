/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/05 17:14
  filename:  ElefantBlaster/ElefantBlasterClient/map/map_manager.cpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#include <glm/glm.hpp>

#include <SDL3/SDL.h>

#include "core/asset_manager.hpp"
#include "states/sdl_state.hpp"
#include "map/map_manager.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

MapManager::MapManager(SDLState &sdl_state, AssetManager &asset_manager)
    : sdl_state_(sdl_state),
      asset_manager_(asset_manager),
      screen_pos_(50, 50) {}
// -----------------------------------------------------------------------------

MapManager::~MapManager() {
}
// -----------------------------------------------------------------------------

bool MapManager::Initialize() {
  Load();

  return true;
}
// -----------------------------------------------------------------------------

void MapManager::Draw(float deltaTime) {
  SDL_Renderer *renderer = sdl_state_.Renderer();
  float sprite_size = asset_manager_.SpriteSize();

  for (MapTile tile : layer_tiles_) {
    SDL_FRect dst = {
        screen_pos_.x + tile.screen_pos.x,    // x
        screen_pos_.y + tile.screen_pos.y,    // y
        tile.rect.w,                          // w
        tile.rect.h,                          // h
    };

    SDL_RenderTexture(renderer, tile.texture, &tile.rect, &dst);
  }
}
// -----------------------------------------------------------------------------

void MapManager::Load() {
  const int rows = 14;
  const int cols = 26;
  int map[rows][cols] = {
      { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
      { 1,0,0,0,2,2,2,2,0,0,2,2,3,2,2,2,2,2,2,2,2,1,3,5,2,1 },
      { 1,0,0,3,3,3,3,1,1,1,3,2,3,2,2,2,2,3,2,2,2,1,3,2,2,1 },
      { 1,0,0,3,2,2,2,0,3,0,2,2,3,2,2,2,0,2,3,2,2,1,3,2,2,1 },
      { 1,1,0,3,2,0,0,0,0,0,0,2,3,2,2,0,0,2,2,3,2,2,1,3,2,1 },
      { 1,4,1,3,2,0,3,1,1,1,1,1,3,2,0,0,2,2,2,3,2,0,2,3,2,1 },
      { 1,1,1,3,2,0,0,3,2,2,2,2,2,2,0,2,2,2,2,3,2,0,0,2,2,1 },
      { 1,1,1,3,2,0,0,2,2,2,3,2,2,2,0,2,2,2,2,3,2,0,0,2,2,1 },
      { 1,4,1,3,2,0,3,1,1,1,1,1,3,2,0,0,2,2,2,3,2,0,2,3,2,1 },
      { 1,1,0,3,2,0,0,0,0,0,0,2,3,2,2,0,0,2,2,3,2,2,1,3,2,1 },
      { 1,0,0,3,2,2,2,0,3,0,2,2,3,2,2,2,0,2,3,2,2,1,3,2,2,1 },
      { 1,0,0,3,3,3,3,1,1,1,3,2,3,2,2,2,2,3,2,2,2,1,3,2,2,1 },
      { 1,0,0,0,2,2,2,2,0,0,2,2,3,2,2,2,2,2,2,2,2,1,3,5,2,1 },
      { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
  };

  float sprite_size = asset_manager_.SpriteSize();

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      MapTile obj;
      obj.type = static_cast<MapTileType>(map[r][c]);
      obj.map_pos = glm::vec2(c, r);
      obj.screen_pos = glm::vec2(c * sprite_size, r * sprite_size);
      AssetTexture aText = asset_manager_.MapTexture(obj.type);
      obj.texture = aText.sdl_texture;
      obj.rect = aText.rect;

      switch (obj.type) {
        case MapTileType::kGrass: {
        } break;

        case MapTileType::kWall: {
        } break;

        case MapTileType::kBalk: {
        } break;

        case MapTileType::kTeleportGate: {
        } break;

        case MapTileType::kQuarantineZone: {
        } break;

        case MapTileType::kDragonEggGst: {
        } break;
      }

      layer_tiles_.push_back(obj);
    }
  }
}
// -----------------------------------------------------------------------------
