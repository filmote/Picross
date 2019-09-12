#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "BaseState.h"

class SelectPuzzleState : public BaseState {

  private:

    uint16_t puzzleIndex = 0;
    void populatePuzzle(uint8_t puzzleIndex);

  public:
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

};