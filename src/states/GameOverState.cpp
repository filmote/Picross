#include "GameOverState.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void GameOverState::activate(StateMachine & machine) {
	
	(void)machine;
	this->index = 2;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void GameOverState::update(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto justPressed = arduboy.justPressedButtons();
  auto pressed = arduboy.pressedButtons();

	
	// Handle other input ..

	if (justPressed & A_BUTTON) {
		if (this->index == 0) {
			machine.changeState(GameStateType::PlayGame); 
		}
		if (this->index == 1) {
			machine.changeState(GameStateType::TitleScreen); 
		}
	}

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void GameOverState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

	Message message;

}

