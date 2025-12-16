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

  bool Connect(const std::string &ip, int port);
  void Disconnect();

 public:
  void OnConnected();
  void OnDisconnected();
  void OnError(int error_code, const std::string &error_message);
  void OnDataRecv(const uint8_t *data, size_t length);

 protected:
  void* socket_;

  std::string ip_;
  int port_;

 private:
  DISALLOW_COPY_AND_ASSIGN(NetClient);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_NETWORK_NET_CLIENT_HPP
// -----------------------------------------------------------------------------
