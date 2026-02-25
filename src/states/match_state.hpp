/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/04 21:46
  filename:  ElefantBlaster/ElefantBlasterClient/map/match_state.hpp

  purpose:   Define MatchState class for managing the game map including tiles and entities.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_STATES_MATCH_STATE_HPP
#define ELEFANT_BLASTER_CLIENT_STATES_MATCH_STATE_HPP
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#include <vector>

#include "definitions/macro.hpp"

#include "core/asset_manager.hpp"

#include "entities/map_tile.hpp"
#include "entities/player.hpp"
#include "entities/spoil.hpp"

#include "map/map_updater.hpp"

#include "states/sdl_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class MatchState : public MapUpdater {
 public:
  MatchState(SDLState &sdl_state, AssetManager &asset_manager);
  virtual ~MatchState();

  bool Initialize();

  void OnUpdate(float delta_time);
  void OnDraw();
  void OnHandleKeyInput(SDL_KeyboardEvent &event);

 private:
  void OnHandleKeyInput(Player *player, SDL_KeyboardEvent &event);

  void UpdatePlayers(json &obj);
  void UpdatePlayer(json &obj);

  void MovePlayer(Player *player, MoveDir dir);
  void MovePlayer(Player *player, glm::vec2 pos_start, glm::vec2 pos_end);

 private:
  void Load();
  void TestParsePlayers();

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
  DISALLOW_COPY_AND_ASSIGN(MatchState);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_STATES_MATCH_STATE_HPP
// -----------------------------------------------------------------------------
