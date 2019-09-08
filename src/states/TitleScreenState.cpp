#include "TitleScreenState.h"
#include "../images/Images.h"

constexpr const static uint8_t UPLOAD_DELAY = 16;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void TitleScreenState::activate(StateMachine & machine) {

	auto & gameStats = machine.getContext().gameStats;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void TitleScreenState::update(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto justPressed = arduboy.justPressedButtons();
  auto pressed = arduboy.pressedButtons();

	// Restart ?

	if (pressed & DOWN_BUTTON) {

		if (restart < UPLOAD_DELAY) {
			restart++;
		}
		else {
			arduboy.exitToBootloader();
		}

	}
	else {
		restart = 0;
	}


	// Update counter ..

	if (this->counter < 64) this->counter++;


	// Handle other input ..

	if (justPressed & A_BUTTON) {
		machine.changeState(GameStateType::PlayGame); 
	}

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void TitleScreenState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

	Sprites::drawOverwrite(0, 6, Images::TitleScreen, 0);

	if (this->counter == 64) Sprites::drawOverwrite(48, 53, Images::TitleScreen_PressA, 0);
	
}
