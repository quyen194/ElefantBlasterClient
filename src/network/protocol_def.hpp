/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/09 10:27
  filename:  ElefantBlaster/ElefantBlasterClient/network/protocol_def.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_NETWORK_PROTOCOL_DEF_HPP
#define ELEFANT_BLASTER_CLIENT_NETWORK_PROTOCOL_DEF_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace _ServerMsgType {
enum T {
  kJoinGame,
  kDrivePlayer,
  kGameStart,
  kGameUpdate,
  kGamePause,
  kGameEnd,
  kPlayerJoined,
  kPlayerStartMoving,
  kPlayerStopMoving,
  kPlayerEndMoving,
  kPlayerPickSpoil,
  kPlayerBeIsolated,
  kPlayerBackToPlayground,
  kBombSetup,
  kBombExploded,
  kMax,
};
}
typedef _ServerMsgType::T ServerMsgType;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_NETWORK_PROTOCOL_DEF_HPP
// -----------------------------------------------------------------------------
