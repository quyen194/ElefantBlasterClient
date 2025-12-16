/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/09 9:07
  filename:  ElefantBlaster/ElefantBlasterClient/network/net_client.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_NETWORK_NET_CLIENT_HPP
#define ELEFANT_BLASTER_CLIENT_NETWORK_NET_CLIENT_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include "definitions/macro.hpp"

#include "map/map_updater.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class NetClient : public MapUpdater {
 public:
  NetClient();
  virtual ~NetClient();

 private:
  DISALLOW_COPY_AND_ASSIGN(NetClient);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_NETWORK_NET_CLIENT_HPP
// -----------------------------------------------------------------------------
