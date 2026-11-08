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
#include <map>
#include <string>

#include <aries_base/utils/get_default.hpp>
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
  kDragonEggGst_Ani,
  kMax,
};
}
typedef _AssetTileType::T AssetTileType;
// -----------------------------------------------------------------------------
inline const std::string GetId(const AssetTileType e) {
  static const std::map<AssetTileType, std::string> kMap = {
      {AssetTileType::kGrass,             "AssetTileType_Grass"},
      {AssetTileType::kWall,              "AssetTileType_Wall"},
      {AssetTileType::kBalk,              "AssetTileType_Balk"},
      {AssetTileType::kTeleportGate,      "AssetTileType_TeleportGate"},
      {AssetTileType::kQuarantineZone,    "AssetTileType_QuarantineZone"},
      {AssetTileType::kDragonEggGst,      "AssetTileType_DragonEggGst"},
      {AssetTileType::kDragonEggGst_Ani,  "AssetTileType_DragonEggGst_Ani"},
  };

  return aries_base::utils::GetDefault(kMap, e, std::string("Unknown"));
}
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
inline const std::string GetId(const MapTileType e) {
  static const std::map<MapTileType, std::string> kMap = {
      {MapTileType::kGrass,             "AssetTileType_Grass"},
      {MapTileType::kWall,              "AssetTileType_Wall"},
      {MapTileType::kBalk,              "AssetTileType_Balk"},
      {MapTileType::kTeleportGate,      "AssetTileType_TeleportGate"},
      {MapTileType::kQuarantineZone,    "AssetTileType_QuarantineZone"},
      {MapTileType::kDragonEggGst,      "AssetTileType_DragonEggGst"},
  };

  return aries_base::utils::GetDefault(kMap, e, std::string("Unknown"));
}
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
