#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../images/Images.h"

class GameOverState : public GameState<GameContext, GameStateType> {

  private:

    uint8_t winner = 0;
    uint8_t counter = 0;
    uint8_t index = 0;
    
  public:	
  
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

};

