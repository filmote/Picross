#pragma once

#include "../utils/GameContext.h"
#include "../utils/GameState.h"
#include "../utils/Enums.h"
#include "../images/Images.h"
#include "../entities/Entities.h"
#include "BaseState.h"

class PlayGameState : public BaseState {

  private:

    Player player;


  public:	
  
    void activate(StateMachine & machine) override;
    void update(StateMachine & machine) override;
    void render(StateMachine & machine) override;

  private:


};




