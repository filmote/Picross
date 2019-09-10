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


  // Populate puzzle ..

  if (justPressed & A_BUTTON) {

    uint16_t idx = 0;
    uint8_t maxSeriesRow = 0;
    uint8_t maxSeriesCol = 0;

    uint8_t width = pgm_read_byte(&Puzzles::Puzzle_01[idx++]);
    uint8_t height = pgm_read_byte(&Puzzles::Puzzle_01[idx++]);
    uint8_t height8 = (height % 8 == 0 ? height / 8 : (height / 8) + 1);

    EEPROM.update(Constants::PuzzleWidth, width);
    EEPROM.update(Constants::PuzzleHeight, height);

    for (uint16_t y = 0; y < height8; y++){

      for (uint16_t x = 0; x < width; x++){

        uint8_t data = pgm_read_byte(&Puzzles::Puzzle_01[idx++]);

        for (uint8_t z = 0; z < 8; z++) {

          uint8_t val = (data & (1 << z)) > 0 ? static_cast<uint8_t>(GridValue::SelectedInImage) : 0;
          uint16_t memLoc = Constants::PuzzleStart + (y * 8 * width) + (z * width) + x;

          EEPROM.update(memLoc, val);

        }

      }

    }


    // Rows ..

    for (uint8_t y = 0; y < height; y++){

      uint8_t series[6] = { 0, 0, 0, 0, 0, 0 };
      int8_t seriesIdx = -1;

      uint8_t lastData = 0;

      for (uint8_t x = 0; x < width; x++){

        uint8_t data = EEPROM.read(Constants::PuzzleStart + (y * width) + x);

        if (lastData != data) {

          if (data == static_cast<uint8_t>(GridValue::SelectedInImage)) {
            seriesIdx++;
            if (seriesIdx == 5) break;
          }
          lastData = data;

        }

        if (data == static_cast<uint8_t>(GridValue::SelectedInImage)) {
          series[seriesIdx]++;
        }

      }


      for (uint8_t z = 0; z < 6; z++){

        if (series[z] > 0 && maxSeriesRow < z + 1) maxSeriesRow = z + 1;
        EEPROM.update(Constants::PuzzleRows + (y * 6) + z, series[z]);

      }

    }


    // Column Headers ..
    
    for (uint8_t x = 0; x < width; x++){

      uint8_t series[6] = { 0, 0, 0, 0, 0, 0 };
      int8_t seriesIdx = -1;

      uint8_t lastData = 0;

      for (uint8_t y = 0; y < height; y++){

        uint8_t data = EEPROM.read(Constants::PuzzleStart + (y * width) + x);

        if (lastData != data) {

          if (data == static_cast<uint8_t>(GridValue::SelectedInImage)) {
            seriesIdx++;
            if (seriesIdx == 5) break;
          }
          lastData = data;

        }

        if (data == static_cast<uint8_t>(GridValue::SelectedInImage)) {
          series[seriesIdx]++;
        }

      }

      for (uint8_t z = 0; z < 6; z++){

        if (series[z] > 0 && maxSeriesCol < z + 1) maxSeriesCol = z + 1;
        EEPROM.update(Constants::PuzzleCols + (x * 6) + z, series[z]);

      }

    }

    EEPROM.update(Constants::PuzzleMaxRows, maxSeriesRow);
    EEPROM.update(Constants::PuzzleMaxCols, maxSeriesCol);

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
