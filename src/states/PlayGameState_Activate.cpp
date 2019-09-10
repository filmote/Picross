#include "PlayGameState.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void PlayGameState::activate(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
	auto & gameStats = machine.getContext().gameStats;


	// this->player.setCol(0, 0, 2);
	// this->player.setCol(0, 1, 2);
	// this->player.setCol(0, 2, 2);
	// this->player.setCol(0, 3, 2);

	// this->player.setCol(1, 0, 4);
	// this->player.setCol(1, 1, 2);

	// this->player.setCol(9, 0, 4);
	// this->player.setCol(11, 1, 2);

	// this->player.setRow(0, 0, 2);
	// this->player.setRow(0, 1, 2);
	// this->player.setRow(0, 2, 2);
	// this->player.setRow(0, 3, 3);

	// this->player.setRow(3, 0, 2);
	// this->player.setRow(5, 0, 2);
	// this->player.setRow(9, 0, 2);
	// this->player.setRow(11, 0, 2);




}

