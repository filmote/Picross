#pragma once

#include <stdint.h>
#include "Utils.h"
#include "../entities/Entities.h"

struct Message {
  String message;
  uint8_t lines;
  uint8_t width;
  uint8_t left;
  bool renderRequired = false;
};


class GameStats {

  public: 

    GameStats() { };

  void resetGame() {

    // player1.resetHand(true);
    // player2.resetHand(true);

  }

};