/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/29 05:26
  filename:  ElefantBlaster/ElefantBlasterClient/definitions/states.hpp

  purpose:   Define state-related definitions.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_DEFINITIONS_STATES_HPP
#define ELEFANT_BLASTER_CLIENT_DEFINITIONS_STATES_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

namespace _State {
enum T {
  kLogin,
  kMainMenu,
  kMatchList,
  kLobby,
  kMatch,
};
}
typedef _State::T State;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_DEFINITIONS_STATES_HPP
// -----------------------------------------------------------------------------
