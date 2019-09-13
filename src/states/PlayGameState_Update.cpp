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


	// Normal play ..

	if ((justPressed & LEFT_BUTTON) && this->puzzle.getX() > 0)															this->puzzle.decX();
	if ((justPressed & RIGHT_BUTTON) && this->puzzle.getX() < this->puzzle.getSize() - 1)		this->puzzle.incX();
	if ((justPressed & UP_BUTTON) && this->puzzle.getY() > 0)																this->puzzle.decY();
	if ((justPressed & DOWN_BUTTON) && this->puzzle.getY() < this->puzzle.getSize() - 1)		this->puzzle.incY();

	if (!this->gameOver) {

		uint8_t xPos = this->marginLeft + (this->puzzle.getX() * Constants::GridWidthX);
		uint8_t yPos = this->marginTop + (this->puzzle.getY() * Constants::GridWidthY);

		if (xPos >= 119) {
			this->xOffset = xPos - 119;
		}
		else {
			this->xOffset = 0;
		}

		if (yPos >= 55) {
			this->yOffset = yPos - 55;
		}
		else {
			this->yOffset = 0;
		}
Serial.print(xOffset);
Serial.print(" ");
Serial.println(yOffset);

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
	else {

		if (this->counter < 64) {

			this->counter++;
			
		}
		else {

			if (justPressed & A_BUTTON) {

				machine.changeState(GameStateType::SelectPuzzle);

			}

		}

	}

}