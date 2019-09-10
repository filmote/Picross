#include "SelectPuzzleState.h"

#include "../utils/Constants.h"
#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void SelectPuzzleState::activate(StateMachine & machine) {

  (void)machine;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void SelectPuzzleState::update(StateMachine & machine) { 

	auto & arduboy = machine.getContext().arduboy;
	auto justPressed = arduboy.justPressedButtons();


  if (justPressed & A_BUTTON) {



    Serial.println("------------------------");

    uint8_t idx = 0;
    uint8_t width = pgm_read_byte(&Puzzles::Puzzle_01[idx++]);
    uint8_t height = pgm_read_byte(&Puzzles::Puzzle_01[idx++]);
    uint8_t height8 = (height % 8 == 0 ? height / 8 : (height / 8) + 1);

    EEPROM.update(Constants::PuzzleWidth, width);
    EEPROM.update(Constants::PuzzleHeight, height);

    for (uint8_t y = 0; y < height8; y++){

      for (uint8_t x = 0; x < width; x++){

        uint8_t data = pgm_read_byte(&Puzzles::Puzzle_01[idx++]);

        for (uint8_t z = 0; z < 8; z++) {

          uint8_t value = (data & (1 << z)) > 0 ? 1 : 0;
          EEPROM.update(Constants::PuzzleStart + (y * 8 * width) + (z * width) + x, value);
//          EEPROM.update(Constants::PuzzleStart + (y * 8 * width) + (z * width) + x, value << 4);
        }

      }

    }

    for (uint8_t y = 0; y < height; y++){

      uint8_t series[5] = { 0, 0, 0, 0, 0 };
      int8_t seriesIdx = -1;

      uint8_t lastData = 0;

      for (uint8_t x = 0; x < width; x++){

        uint8_t data = EEPROM.read(Constants::PuzzleStart + (y * width) + x);


        if (lastData != data) {
          if (data == 1) {
            seriesIdx++;
          }
          lastData = data;

        }
        if (data == 1) {
          series[seriesIdx]++;
        }

      }


      for (uint8_t x = 0; x < 5; x++){
        Serial.print(series[x]);
        Serial.print(",");

      }
      Serial.println("");

    }

 		machine.changeState(GameStateType::PlayGame); 

  }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void SelectPuzzleState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;

  Sprites::drawOverwrite(56, 26, Puzzles::Puzzle_00, 0);

}
