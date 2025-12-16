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

#include "entities/map_tile.h"
#include "entities/player.h"
#include "entities/spoil.h"

#include "map/map_updater.h"

#include "states/sdl_state.h"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class MapManager : public MapUpdater {
 public:
  MapManager(SDLState &sdl_state, AssetManager &asset_manager);
  virtual ~MapManager();

  bool Initialize();

  void Update(float delta_time);
  void Draw();

  void UpdatePlayers(json &obj);
  void UpdatePlayer(json &obj);

  void MovePlayer(Player *player, MoveDir dir);
  void MovePlayer(Player *player, glm::vec2 pos_start, glm::vec2 pos_end);

 private:
  void Load();

 private:
  SDLState &sdl_state_;
  AssetManager &asset_manager_;

 protected:
  float sprite_size_;
  glm::vec2 screen_pos_;
  std::vector<MapTile*> layer_tiles_;
  std::vector<DynamicMapTile*> dynamic_tiles_;
  std::vector<Spoil> layer_spoils_;
  std::vector<Player*> layer_players_;

  Player *player1_;

 private:
  DISALLOW_COPY_AND_ASSIGN(MapManager);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_MAP_MAP_MANAGER_HPP
// -----------------------------------------------------------------------------
