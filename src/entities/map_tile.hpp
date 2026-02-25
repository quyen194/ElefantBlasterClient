/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/05 4:52
  filename:  ElefantBlaster/ElefantBlasterClient/entities/map_tile.hpp

  purpose:   Define MapTile structures for static and dynamic map tiles.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_ENTITIES_MAP_TILE_HPP
#define ELEFANT_BLASTER_CLIENT_ENTITIES_MAP_TILE_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

#include "effects/animation.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace _AssetTileType {
enum T {
  kBalk,
  kWall,
  kGrass,
  kTeleportGate,
  kQuarantineZone,
  kDragonEggGst,
  kMax,
};
}
typedef _AssetTileType::T AssetTileType;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace _MapTileType {
enum T {
  kGrass = 0,
  kWall = 1,
  kBalk = 2,
  kTeleportGate = 3,
  kQuarantineZone = 4,
  kDragonEggGst = 5,
};
}
typedef _MapTileType::T MapTileType;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct MapTile {
  virtual ~MapTile() {}

  MapTileType type;
  glm::vec2 map_pos;
  glm::vec2 screen_pos;
  SDL_Texture *texture = nullptr;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct StaticMapTile : public MapTile {
  SDL_FRect rect;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct DynamicMapTile : public MapTile {
  Animation animation;
  SDL_Texture *bg_texture = nullptr;
  SDL_FRect bg_rect;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_ENTITIES_MAP_TILE_HPP
// -----------------------------------------------------------------------------
