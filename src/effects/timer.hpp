/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/04 20:25
  filename:  ElefantBlaster/ElefantBlasterClient/effects/timer.hpp

  purpose:   Define Timer class for managing time intervals.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_EFFECTS_TIMER_HPP
#define ELEFANT_BLASTER_CLIENT_EFFECTS_TIMER_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <cmath>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class Timer {
 public:
  Timer(float length) : length_(length), time_(0), total_time_(0), timeout_(false) {}

  void Step(float delta_time) {
    time_ += delta_time;
    if (time_ >= length_) {
      time_ = fmodf(time_, length_);
    }
    total_time_ += delta_time;
  }

  void Reset() { time_ = 0; }

  float GetLength() const { return length_; }
  float GetTime() const { return time_; }
  float GetTotalTime() const { return total_time_; }
  bool IsTimeout() const { return timeout_; }

 private:
  float length_;
  float time_;
  float total_time_;
  bool timeout_;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_EFFECTS_TIMER_HPP
// -----------------------------------------------------------------------------
