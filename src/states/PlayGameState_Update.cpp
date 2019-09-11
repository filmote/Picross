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


	if ((justPressed & LEFT_BUTTON) && this->puzzle.getX() > 0)													this->puzzle.decX();
	if ((justPressed & RIGHT_BUTTON) && this->puzzle.getX() < this->puzzle.getSize() - 1)		this->puzzle.incX();
	if ((justPressed & UP_BUTTON) && this->puzzle.getY() > 0)														this->puzzle.decY();
	if ((justPressed & DOWN_BUTTON) && this->puzzle.getY() < this->puzzle.getSize() - 1)		this->puzzle.incY();


	if (this->puzzle.getY() >= 3) {
		gameStats.yOffset = ((this->puzzle.getY() - 3) * 9);
	}
	else {
		gameStats.yOffset = 0;
	}

	if (justPressed & A_BUTTON) {

		GridValue current = this->puzzle.getGrid();

		switch (current) {

			case GridValue::Blank:	
			case GridValue::Marked:	
				this->puzzle.setGrid(GridValue::Selected);
				break;

			case GridValue::Selected:	
				this->puzzle.setGrid(GridValue::Blank);
				break;
				
		}
		
	}

	if (justPressed & B_BUTTON) {

		GridValue current = this->puzzle.getGrid();

		switch (current) {

			case GridValue::Blank:	
			case GridValue::Selected:	
				this->puzzle.setGrid(GridValue::Marked);
				break;

			case GridValue::Marked:	
				this->puzzle.setGrid(GridValue::Blank);
				break;
				
		}
		
	}

}