#include "PlayGameState.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void PlayGameState::activate(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
	auto & gameStats = machine.getContext().gameStats;

  this->maxSeriesRow = EEPROM.read(Constants::PuzzleMaxRows);
  this->maxSeriesCol = EEPROM.read(Constants::PuzzleMaxCols);

	this->marginLeft = 3 + this->maxSeriesRow * 5;
	this->marginTop = 2 + this->maxSeriesCol * 7;

	this->counter = 0;
	this->gameOver = false;

}

