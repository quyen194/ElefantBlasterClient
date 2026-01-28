/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/05 17:14
  filename:  ElefantBlaster/ElefantBlasterClient/map/map_manager.cpp

  purpose:   Manage the game map including tiles and entities.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <glm/glm.hpp>

#include <SDL3/SDL.h>

#include "core/asset_manager.hpp"
#include "map/map_manager.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

MapManager::MapManager(SDLState &sdl_state, AssetManager &asset_manager)
    : sdl_state_(sdl_state),
      asset_manager_(asset_manager),
      sprite_size_(35.0f),
      screen_pos_(50, 50),
      player1_(nullptr) {}
// -----------------------------------------------------------------------------

MapManager::~MapManager() {
}
// -----------------------------------------------------------------------------

bool MapManager::Initialize() {
  sprite_size_ = asset_manager_.SpriteSize();

  Load();

  return true;
}
// -----------------------------------------------------------------------------

void MapManager::Update(float delta_time) {
  for (DynamicMapTile *tile : dynamic_tiles_) {
    tile->animation.Step(delta_time);
  }

  for (Player *player : layer_players_) {
    if (player->is_moving) {
      Movement &movement = player->movement;
      movement.animation.Step(delta_time);

      glm::vec2 distance_delta = movement.screen_pos_end - movement.screen_pos_start;
      float distance_total = glm::length(distance_delta);
      float time_moved = movement.animation.GetTotalTime();
      float distance_moved = movement.speed * time_moved;
      if (distance_total > 1.0f &&
          distance_moved < distance_total &&
          glm::length(distance_total - distance_moved) > 1.0f) {
        glm::vec2 dir_norm = distance_delta / distance_total;
        movement.screen_pos_current = movement.screen_pos_start + dir_norm * distance_moved;
      }
      else {
        movement.screen_pos_current = movement.screen_pos_end;
      }

      if (movement.screen_pos_current == movement.screen_pos_end) {
        player->map_pos = movement.map_pos_end;
        player->screen_pos = player->map_pos * sprite_size_;
        player->rect = asset_manager_.PlayerStandRect(movement.dir);
        player->is_moving = false;
      }
    }
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

  for (Spoil obj : layer_spoils_) {
    SDL_FRect dst = {
        screen_pos_.x + obj.screen_pos.x,    // x
        screen_pos_.y + obj.screen_pos.y,    // y
        obj.rect.w,                          // w
        obj.rect.h,                          // h
    };
    SDL_RenderTexture(renderer, obj.texture, &obj.rect, &dst);
  }

  for (Player *player : layer_players_) {
    if (!player->is_moving) {
      SDL_FRect dst = {
          screen_pos_.x + player->screen_pos.x,   // x
          screen_pos_.y + player->screen_pos.y,   // y
          player->rect.w,                         // w
          player->rect.h,                         // h
      };
      SDL_RenderTexture(renderer, player->texture, &player->rect, &dst);
    }
    else {
      Movement &movement = player->movement;
      float sprite_size = static_cast<float>(movement.rect.h);
      float srcX = movement.animation.CurrentFrame() * sprite_size;
      SDL_FRect src = {
          srcX,                 // x
          movement.rect.y,      // y
          movement.rect.w,      // w
          movement.rect.h,      // h
      };
      SDL_FRect dst = {
          screen_pos_.x + movement.screen_pos_current.x,  // x
          screen_pos_.y + movement.screen_pos_current.y,  // y
          movement.rect.w,                                // w
          movement.rect.h,                                // h
      };
      SDL_RenderTexture(renderer, player->texture, &src, &dst);
    }
  }
}
// -----------------------------------------------------------------------------

void MapManager::Load() {
  const int rows = 14;
  const int cols = 26;

  int map_tiles[rows][cols] = {
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

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      MapTileType type = static_cast<MapTileType>(map_tiles[r][c]);
      switch (type) {
        case MapTileType::kGrass:
        case MapTileType::kWall:
        case MapTileType::kBalk:
        case MapTileType::kTeleportGate:
        case MapTileType::kQuarantineZone: {
          StaticMapTile *obj = new StaticMapTile();
          obj->type = type;
          obj->map_pos = glm::vec2(c, r);
          obj->screen_pos = glm::vec2(c * sprite_size_, r * sprite_size_);
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
          obj->screen_pos = obj->map_pos * sprite_size_;
          obj->texture = asset_manager_.DragonEggGstTexture();
          obj->animation = Animation(20, 3.0f);
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

  int map_spoils[rows][cols] = {
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,5,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  };

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      SpoilType type = static_cast<SpoilType>(map_spoils[r][c]);
      switch (type) {
        case SpoilType::kDragonEggSpeed:
        case SpoilType::kDragonEggAttack:
        case SpoilType::kDragonEggDelay:
        case SpoilType::kDragonEggMystic: {
          Spoil obj;
          obj.type = type;
          obj.map_pos = glm::vec2(c, r);
          obj.screen_pos = obj.map_pos * sprite_size_;
          AssetTexture aText = asset_manager_.SpoilTexture(obj.type);
          obj.texture = aText.sdl_texture;
          obj.rect = aText.rect;
          // add to map
          layer_spoils_.push_back(obj);
        } break;
      }
    }
  }
}
// -----------------------------------------------------------------------------

void MapManager::UpdatePlayers(json &obj) {

}
// -----------------------------------------------------------------------------

void MapManager::UpdatePlayer(json &obj) {
  std::string player_id = obj["id"];

  Player *player = nullptr;
  if (!layer_players_.empty()) {
    for (Player *obj : layer_players_) {
      if (obj->server_id == player_id) {
        player = obj;
        break;
      }
    }
  }

  bool new_player = false;

  if (!player) {
    player = new Player();
    new_player = true;

    std::string player_no = player_id.substr(0, 7);
    if (player_no == "player1") {
      player->player_no = PlayerNo::k1;
    }
    else if (player_no == "player2") {
      player->player_no = PlayerNo::k2;
    }

    player->texture = asset_manager_.PlayerTexture(player->player_no);
  }

  player->map_pos.x = obj["currentPosition"]["col"];
  player->map_pos.y = obj["currentPosition"]["row"];
  player->screen_pos = player->map_pos * sprite_size_;
  player->rect = asset_manager_.PlayerStandRect(MoveDir::kDown);

  player->speed = obj["speed"];
  player->power = obj["power"];
  player->delay = obj["delay"];
  player->lives = obj["lives"];
  player->score = obj["score"];
  player->box = obj["box"];
  player->dragonEggSpeed = obj["dragonEggSpeed"];
  player->dragonEggAttack = obj["dragonEggAttack"];
  player->dragonEggDelay = obj["dragonEggDelay"];
  player->dragonEggMystic = obj["dragonEggMystic"];
  player->dragonEggMysticAddEgg = obj["dragonEggMysticAddEgg"];
  player->dragonEggMysticMinusEgg = obj["dragonEggMysticMinusEgg"];
  player->dragonEggMysticIsolateGate = obj["dragonEggMysticIsolateGate"];
  player->gstEggBeingAttacked = obj["gstEggBeingAttacked"];
  player->quarantine = obj["quarantine"];

  if (server_msg_type_ == ServerMsgType::kPlayerStartMoving) {
    int nextX = obj["nextPosition"]["col"];
    int nextY = obj["nextPosition"]["row"];
    MovePlayer(player, player->map_pos, glm::vec2(nextX, nextY));
  }
  else if (server_msg_type_ == ServerMsgType::kPlayerBeIsolated ||
           server_msg_type_ == ServerMsgType::kPlayerBackToPlayground) {
    int prevX = obj["previousPosition"]["col"];
    int prevY = obj["previousPosition"]["row"];
    MovePlayer(player, glm::vec2(prevX, prevY), player->map_pos);
    player->movement.speed = 5000;
  }

  if (new_player) {
    layer_players_.push_back(player);

    if (player->player_no == PlayerNo::k1) {
      player1_ = player;
    }
  }
}
// -----------------------------------------------------------------------------

void MapManager::MovePlayer(Player *player, MoveDir dir) {
  MovePlayer(player, player->map_pos, Movement::DirToPos(player->map_pos, dir));
}
// -----------------------------------------------------------------------------

void MapManager::MovePlayer(Player *player, glm::vec2 pos_start, glm::vec2 pos_end) {
  Movement &movement = player->movement;

  movement.map_pos_start = pos_start;
  movement.map_pos_end = pos_end;
  movement.dir = Movement::PosToDir(pos_start, pos_end);
  movement.screen_pos_start = movement.map_pos_start * sprite_size_;
  movement.screen_pos_end = movement.map_pos_end * sprite_size_;
  movement.screen_pos_current = movement.screen_pos_start;
  movement.speed = static_cast<float>(player->speed);
  movement.animation = asset_manager_.PlayerAnimation(movement.dir);
  movement.rect = asset_manager_.PlayerAnimationRect(movement.dir);

  player->is_moving = true;
}
// -----------------------------------------------------------------------------
