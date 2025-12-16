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

void MapManager::Update(float deltaTime) {
  for (DynamicMapTile *tile : dynamic_tiles_) {
    tile->animation.Step(deltaTime);
  }
}
// -----------------------------------------------------------------------------

void MapManager::Draw() {
  SDL_Renderer *renderer = sdl_state_.Renderer();
  float sprite_size = asset_manager_.SpriteSize();

  for (MapTile *tile : layer_tiles_) {
    switch (tile->type) {
      case MapTileType::kGrass:
      case MapTileType::kWall:
      case MapTileType::kBalk:
      case MapTileType::kTeleportGate:
      case MapTileType::kQuarantineZone: {
        StaticMapTile *obj = dynamic_cast<StaticMapTile*>(tile);
        SDL_FRect dst = {
            screen_pos_.x + obj->screen_pos.x,    // x
            screen_pos_.y + obj->screen_pos.y,    // y
            obj->rect.w,                          // w
            obj->rect.h,                          // h
        };
        SDL_RenderTexture(renderer, obj->texture, &obj->rect, &dst);
      } break;

      case MapTileType::kDragonEggGst: {
        DynamicMapTile *obj = dynamic_cast<DynamicMapTile*>(tile);

        SDL_FRect bg_dst = {
            screen_pos_.x + obj->screen_pos.x,    // x
            screen_pos_.y + obj->screen_pos.y,    // y
            obj->bg_rect.w,                       // w
            obj->bg_rect.h,                       // h
        };
        SDL_RenderTexture(renderer, obj->bg_texture, &obj->bg_rect, &bg_dst);

        float sprite_size = static_cast<float>(obj->texture->w);
        float srcY = obj->animation.CurrentFrame() * sprite_size;
        SDL_FRect src = {
            0,                                    // x
            srcY,                                 // y
            sprite_size,                          // w
            sprite_size,                          // h
        };
        SDL_FRect dst = {
            screen_pos_.x + obj->screen_pos.x,    // x
            screen_pos_.y + obj->screen_pos.y,    // y
            sprite_size,                          // w
            sprite_size,                          // h
        };
        SDL_RenderTexture(renderer, obj->texture, &src, &dst);
      } break;
    }
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
      MapTileType type = static_cast<MapTileType>(map[r][c]);
      switch (type) {
        case MapTileType::kGrass:
        case MapTileType::kWall:
        case MapTileType::kBalk:
        case MapTileType::kTeleportGate:
        case MapTileType::kQuarantineZone: {
          StaticMapTile *obj = new StaticMapTile();
          obj->type = type;
          obj->map_pos = glm::vec2(c, r);
          obj->screen_pos = glm::vec2(c * sprite_size, r * sprite_size);
          AssetTexture aText = asset_manager_.MapTexture(obj->type);
          obj->texture = aText.sdl_texture;
          obj->rect = aText.rect;
          // add to map
          layer_tiles_.push_back(obj);
        } break;

        case MapTileType::kDragonEggGst: {
          DynamicMapTile *obj = new DynamicMapTile();
          obj->type = type;
          obj->map_pos = glm::vec2(c, r);
          obj->screen_pos = glm::vec2(c * sprite_size, r * sprite_size);
          obj->texture = asset_manager_.DragonEggGstTexture();
          obj->animation = Animation(20, 5.0f);
          // this animation have background
          AssetTexture aText = asset_manager_.MapTexture(MapTileType::kGrass);
          obj->bg_texture = aText.sdl_texture;
          obj->bg_rect = aText.rect;
          // add to map
          layer_tiles_.push_back(obj);
          dynamic_tiles_.push_back(obj);
        } break;
      }
    }
  }
}
// -----------------------------------------------------------------------------
