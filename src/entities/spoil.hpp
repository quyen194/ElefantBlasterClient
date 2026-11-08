/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/05 16:18
  filename:  ElefantBlaster/ElefantBlasterClient/entities/spoil.h

  purpose:   Define Spoil structure for spoil entities.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_ENTITIES_SPOIL_HPP
#define ELEFANT_BLASTER_CLIENT_ENTITIES_SPOIL_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <map>
#include <string>

#include <aries_base/utils/get_default.hpp>
#include <glm/glm.hpp>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace _AssetSpoilType {
enum T {
  kDragonEggMystic,
  kDragonEggAttack,
  kDragonEggDelay,
  kDragonEggSpeed,
  kMax,
};
};
typedef _AssetSpoilType::T AssetSpoilType;
// -----------------------------------------------------------------------------
inline const std::string GetId(const AssetSpoilType e) {
  static const std::map<AssetSpoilType, std::string> kMap = {
      {AssetSpoilType::kDragonEggMystic,  "AssetSpoilType_DragonEggMystic"},
      {AssetSpoilType::kDragonEggAttack,  "AssetSpoilType_DragonEggAttack"},
      {AssetSpoilType::kDragonEggDelay,   "AssetSpoilType_DragonEggDelay"},
      {AssetSpoilType::kDragonEggSpeed,   "AssetSpoilType_DragonEggSpeed"},
  };

  return aries_base::utils::GetDefault(kMap, e, std::string("Unknown"));
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace _SpoilType {
enum T {
  kDragonEggSpeed = 3,
  kDragonEggAttack = 4,
  kDragonEggDelay = 5,
  kDragonEggMystic = 6,
};
};
typedef _SpoilType::T SpoilType;
// -----------------------------------------------------------------------------
inline const std::string GetId(const SpoilType e) {
  static const std::map<SpoilType, std::string> kMap = {
      {SpoilType::kDragonEggMystic,  "AssetSpoilType_DragonEggMystic"},
      {SpoilType::kDragonEggAttack,  "AssetSpoilType_DragonEggAttack"},
      {SpoilType::kDragonEggDelay,   "AssetSpoilType_DragonEggDelay"},
      {SpoilType::kDragonEggSpeed,   "AssetSpoilType_DragonEggSpeed"},
  };

  return aries_base::utils::GetDefault(kMap, e, std::string("Unknown"));
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct Spoil {
  SpoilType type;
  glm::vec2 map_pos;
  glm::vec2 screen_pos;
  SDL_Texture *texture = nullptr;
  SDL_FRect rect;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_ENTITIES_SPOIL_HPP
// -----------------------------------------------------------------------------
