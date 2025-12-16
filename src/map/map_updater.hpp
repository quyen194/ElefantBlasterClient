/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/09 8:57
  filename:  ElefantBlaster/ElefantBlasterClient/map/map_updater.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_MAP_MAP_UPDATER_HPP
#define ELEFANT_BLASTER_CLIENT_MAP_MAP_UPDATER_HPP
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#include <nlohmann/json.hpp>

#include "network/protocol_def.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
using json = nlohmann::json;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

class MapUpdater {
 public:
  virtual void UpdatePlayers(json &obj) = 0;

 protected:
  ServerMsgType server_msg_type_;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_MAP_MAP_UPDATER_HPP
// -----------------------------------------------------------------------------
