/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/04 21:46
  filename:  ElefantBlaster/ElefantBlasterClient/map/map_manager.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_MAP_MAP_MANAGER_HPP
#define ELEFANT_BLASTER_CLIENT_MAP_MAP_MANAGER_HPP
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#include <vector>

#include "definitions/macro.hpp"

#include "entities/map_tile.hpp"
#include "entities/spoil.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class MapManager {
 public:
  MapManager(SDLState &sdl_state, AssetManager &asset_manager);
  virtual ~MapManager();

  bool Initialize();

  void Update(float deltaTime);
  void Draw();

 private:
  void Load();

 private:
  SDLState &sdl_state_;
  AssetManager &asset_manager_;

 private:
  glm::vec2 screen_pos_;
  std::vector<MapTile*> layer_tiles_;
  std::vector<DynamicMapTile*> dynamic_tiles_;
  std::vector<Spoil> layer_spoils_;

 private:
  DISALLOW_COPY_AND_ASSIGN(MapManager);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_MAP_MAP_MANAGER_HPP
// -----------------------------------------------------------------------------
