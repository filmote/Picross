#include "PlayGameState.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void PlayGameState::update(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
	auto & gameStats = machine.getContext().gameStats;
	auto justPressed = arduboy.justPressedButtons();
	auto pressed = arduboy.pressedButtons();


	if ((justPressed & LEFT_BUTTON) && this->player.getX() > 0)													this->player.decX();
	if ((justPressed & RIGHT_BUTTON) && this->player.getX() < gameStats.gridSize - 1)		this->player.incX();
	if ((justPressed & UP_BUTTON) && this->player.getY() > 0)														this->player.decY();
	if ((justPressed & DOWN_BUTTON) && this->player.getY() < gameStats.gridSize - 1)		this->player.incY();


	if (this->player.getY() >= 3) {
		gameStats.yOffset = ((this->player.getY() - 3) * 9);
	}
	else {
		gameStats.yOffset = 0;
	}

	if (justPressed & A_BUTTON) {

		GridValue current = this->player.getGrid();

		switch (current) {

			case GridValue::Blank:	
			case GridValue::Marked:	
				this->player.setGrid(GridValue::Selected);
				break;

			case GridValue::Selected:	
				this->player.setGrid(GridValue::Blank);
				break;
				
		}
		
	}

	if (justPressed & B_BUTTON) {

		GridValue current = this->player.getGrid();

		switch (current) {

			case GridValue::Blank:	
			case GridValue::Selected:	
				this->player.setGrid(GridValue::Marked);
				break;

			case GridValue::Marked:	
				this->player.setGrid(GridValue::Blank);
				break;
				
		}
		
	}

}